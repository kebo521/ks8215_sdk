
/**
 * History:
 * ================================================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>    
#include <sys/stat.h>    
#include <sys/time.h>
#include <sys/ipc.h>
//#include <sys/shm.h> 
//#include <linux/shm.h> 
#include<sys/mman.h>

#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 


typedef struct{
	int				pid,sig;	
	unsigned short 	mAppMax,nCurrAppId;
	unsigned short 	nDefAppId,nNouser;
	ST_APP_INFO 	AppInfo[6];
	unsigned short 	mOptMax,nOptId;
	ST_OPT_INFO 	OptInfo[10];
} ST_SYS_MSG;

typedef struct{
	int 			AppExitCode;
	unsigned short 	nCurrAppId,pNextAppId;
	unsigned char  aAppIDStack[20];
	unsigned short	sWriteLen,sReadLen;
	unsigned char  sendBuff[2048];
	unsigned short	rWriteLen,rReadLen;
	unsigned char  readBuff[2048];
} ST_SYS_DATA;


typedef struct{
	int 			shmAid;
	ST_SYS_MSG		*pSysMsg;
	int 			shmDid;
	ST_SYS_DATA	*pSysData;
} ST_SYS_SHM;

ST_SYS_SHM tSt_Sys={0};


//========从src1中查找src2字段=返回匹配src1中的末端地址=======
char *eStrstr(char* src1, const char* src2)
{
	unsigned char *pS1,*pS2;
	//if(src1==NULL || src2==NULL) return NULL;
	pS1=(unsigned char*)src1;
	pS2=(unsigned char*)src2;
	while(*pS1)
	{
		if(*pS1 != *pS2)
		{
			if(pS2 != (unsigned char*)src2)
			{
				pS2=(unsigned char*)src2;
				pS1=(unsigned char*)src1;
			}
			else pS1++;
		}
		else
		{
			pS1++; 
			if(pS2 == (unsigned char*)src2) //记录串1起点(src1+1)
				src1=(char*)pS1;
			pS2++;
			if(*pS2 == '\0')
				return (char*)pS1;
		}
	}
	return NULL;
}

#define SHM_SDK_AID		"../shm_A8215"		//独立数字平台统一定
#define SHM_SDK_DID		"../shm_D8215"		//独立数字平台统一定
#define SHM_AID_NAME		"/dev/ashmem"		//独立数字平台统一定





int OsSysInit(char* pInTag)
{
	#if(0)//def ANDROID_DEF
	tSt_Sys.shmAid = ashmem_create_region(SHM_AID_NAME,sizeof(ST_SYS_MSG));
	if(tSt_Sys.shmAid == -1) 
	{		
		LOG(LOG_ERROR,"ashmem_create_region1->%s Err\r\n",SHM_AID_NAME);		
		return -1;	
	}
	tSt_Sys.pSysMsg = mmap(NULL,sizeof(ST_SYS_MSG),PROT_READ|PROT_WRITE,MAP_SHARED,tSt_Sys.shmAid, 0);


	tSt_Sys.shmDid = ashmem_create_region(SHM_AID_NAME,sizeof(ST_SYS_DATA));
	if(tSt_Sys.shmDid == -1) 
	{		
		LOG(LOG_ERROR,"ashmem_create_region2->%s Err\r\n",SHM_AID_NAME); 	
		return -1;	
	}
	tSt_Sys.pSysMsg = mmap(NULL,sizeof(ST_SYS_DATA),PROT_READ|PROT_WRITE,MAP_SHARED,tSt_Sys.shmDid, 0);
	#else	//---------------------------------------------------------------------------------------------
	char *pShmAid,*pShmDid;
	if(strstr(pInTag,"master"))
	{
		pShmAid=eStrstr(SHM_SDK_AID,"../");
		pShmDid=eStrstr(SHM_SDK_DID,"../");
	}
	else
	{
		pShmAid=SHM_SDK_AID;
		pShmDid=SHM_SDK_DID;
	}
	LOG(LOG_INFO,"pShmAid[%s],pShmDid[%s]\r\n",pShmAid,pShmDid);
	//tSt_Sys.shmAid = shm_open(SHM_SDK_AID, O_RDWR, 0777);// S_IRUSR | S_IWUSR
	tSt_Sys.shmAid = open(pShmAid, O_RDWR);
	if(tSt_Sys.shmAid < 0) 
	{		
		LOG(LOG_ERROR,"ashmem_create_region1->%s [%d]Err\r\n",SHM_AID_NAME,tSt_Sys.shmAid);		
		return -1;	
	}
//	ftruncate(tSt_Sys.shmAid, sizeof(ST_SYS_MSG));
	tSt_Sys.pSysMsg = mmap(NULL, sizeof(ST_SYS_MSG), PROT_READ|PROT_WRITE, MAP_SHARED, tSt_Sys.shmAid, 0);
	if (tSt_Sys.pSysMsg == MAP_FAILED) 
	{		
		LOG(LOG_ERROR,"mmap->A8215 shmAid Err\r\n");		
		return -1;	
	}
	//tSt_Sys.shmAid = shm_open(SHM_SDK_DID, O_RDWR, 0777);// S_IRUSR | S_IWUSR
	tSt_Sys.shmDid = open(pShmDid,O_RDWR);
	if(tSt_Sys.shmDid == -1) 
	{		
		LOG(LOG_ERROR,"ashmem_create_region2->%s Err\r\n",SHM_AID_NAME); 	
		return -1;	
	}
//	ftruncate(tSt_Sys.shmDid, sizeof(ST_SYS_DATA));
	tSt_Sys.pSysData = mmap(NULL,sizeof(ST_SYS_DATA),PROT_READ|PROT_WRITE,MAP_SHARED,tSt_Sys.shmDid, 0);
	if (tSt_Sys.pSysData == MAP_FAILED) 
	{		
		LOG(LOG_ERROR,"mmap->A8215 shmDid Err\r\n");		
		return -1;	
	}


/*
	tSt_Sys.shmAid = shmget(SHM_SDK_AID,sizeof(ST_SYS_MSG),Aperm);		
	if(tSt_Sys.shmAid == -1) 
	{		
		LOG(LOG_ERROR,"shmget->A8215 shmAid Err\r\n");		
		return -1;	
	}
	tSt_Sys.pSysMsg = (ST_SYS_MSG *)shmat(tSt_Sys.shmAid,NULL,0);
	//---------------------------------------------------------------
	tSt_Sys.shmDid = shmget(SHM_SDK_DID,sizeof(ST_SYS_DATA),0666);		
	if(tSt_Sys.shmDid == -1) 
	{		
		LOG(LOG_ERROR,"shmget->D8215 shmDid Err\r\n");		
		return -1;	
	}
	tSt_Sys.pSysData = (ST_SYS_DATA *)shmat(tSt_Sys.shmDid,NULL,0);
	*/
	#endif
	return 0;
}

int OsSaveAppInfo(ST_APP_INFO* pAppInfo)
{
	if(tSt_Sys.pSysMsg)
	{
		int i,max;
		max = tSt_Sys.pSysMsg->mAppMax;
		for(i=0;i<max;i++)
		{
			if(strcmp(pAppInfo->Id,tSt_Sys.pSysMsg->AppInfo[i].Id)==0)
				break;
		}
		if(i < max)
		{//--------应用更新--------
			memcpy(&tSt_Sys.pSysMsg->AppInfo[tSt_Sys.pSysMsg->mAppMax],pAppInfo,sizeof(ST_APP_INFO));
			fsync(tSt_Sys.shmAid);
			//sigqueue(tSt_Sys.pSysMsg->pid,tSt_Sys.pSysMsg->sig,(sigval_t)0);
		}
		else
		{//--------应用安装--------
			if(i >= (sizeof(tSt_Sys.pSysMsg->AppInfo)/sizeof(tSt_Sys.pSysMsg->AppInfo[0])))
				return -3;
			memcpy(&tSt_Sys.pSysMsg->AppInfo[tSt_Sys.pSysMsg->mAppMax],pAppInfo,sizeof(ST_APP_INFO));
			tSt_Sys.pSysMsg->mAppMax++;
		//	fsync(tSt_Sys.shmAid);
			//sigqueue(tSt_Sys.pSysMsg->pid,tSt_Sys.pSysMsg->sig,(sigval_t)0);
		}
		return 0;
	}
	return -5;
}

//================================================================================
extern int APP_main(int argc, char* argv[]);



int main(int argc, char* argv[])
{
	if(argc<1)
	{
		LOG(LOG_ERROR,"main->in(argc[%d]) ERR\r\n",argc);
		return -1;
	}
	OsSysInit(argv[0]);
	return APP_main(argc-2,argv+2);
}
//=============================================================================




void OsLogSetTag(const char *Tag)
{
	int fd = open(Tag,O_RDWR|O_CREAT,0666); 	
	if (fd != -1)		
	{
	/*
		int ret;
		char buff[128];
		time_t timer;//long
		struct tm *pblock;
		timer = time(NULL);
		pblock = localtime(&timer);
		ret=snprintf(buff,sizeof(buff),"============%04d-%02d-%02d %02:%02:%02=============\r\n",pblock->tm_year+1900,pblock->tm_mon,pblock->tm_mday,pblock->tm_hour,pblock->tm_min,pblock->tm_sec);
		write(fd,buff,ret);
		*/
		dup2 (fd, STDOUT_FILENO);			
		close(fd);	
	}
}

int OsLog(LOG_T Prio,const char *fmt,...)
{
	va_list arg;
	if(Prio <  CURR_LOG_T) return -1;
	va_start(arg, fmt);
	vprintf(fmt,arg);
	va_end(arg);
	// vfprintf(FILE *stream,fmt,arg);
	return 0;
}

void OsLogHex(char* msg,void* pBuff,int Len)
{
	#if(CURR_LOG_T >= LOG_INFO)
	const char sHexData[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char sbuff[2048];
	int i,nMax;
	char *pSave,*pEnd;
	unsigned char *p;
	pSave = sbuff;
	pEnd = sbuff+sizeof(sbuff);
	pSave += sprintf(pSave,"%s[%d]:\r\n",msg,Len);
	nMax = 32;
	p = (unsigned char *)pBuff;
	while(Len)
	{
		if(nMax > Len) nMax=Len;

		if((pSave+(3*nMax + 2)) > pEnd)
		{
			//*pSave = '\0'; fputs(sbuff, stdout);
			fwrite(sbuff,1,pSave-sbuff,stdout);
			//printf(sbuff,pSave-sbuff);	//two parameter ->warning: format not a string literal and no format arguments
			pSave = sbuff;
		}
		
		for(i=0;i<nMax;i++)
		{
			*pSave++ = sHexData[*p >> 4];
			*pSave++ = sHexData[*p & 0x0f];
			*pSave++ = ' ';
			p++;
		}
		*pSave++ = '\r';
		*pSave++ = '\n';
		Len -= nMax;
	}
	//*pSave = '\0'; fputs(sbuff, stdout);
	fwrite(sbuff,1,pSave-sbuff,stdout);
	//printf(sbuff,pSave-sbuff); //two parameter ->warning: format not a string literal and no format arguments
	#endif
}


//=====================================================================================================
unsigned long OsGetTickCount(void)
{
	/*
	struct timespec time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time);
	return (time.tv_sec*1000 + time.tv_nsec/1000000);
	*/
	struct timeval time_tv;
	gettimeofday(&time_tv, NULL);
	return (time_tv.tv_sec*1000 + time_tv.tv_usec/1000);
}

void OsGetTime(ST_TIME *Time)
{
/*
	timespec time;
	struct tm tblock;
	clock_gettime(CLOCK_REALTIME, &time); //获取相对于1970到现在的秒数
	localtime_r(&time.tv_sec, &tblock);
*/
	time_t timer;//long
	struct tm *pblock;
	timer = time(NULL);
	pblock = localtime(&timer);
	
	Time->Year = pblock->tm_year + 1900;
	Time->Month=pblock->tm_mon;
	Time->Day=pblock->tm_mday;
	Time->Hour=pblock->tm_hour;
	Time->Minute=pblock->tm_min;
	Time->Second=pblock->tm_sec;
	Time->DayOfWeek=pblock->tm_wday;

}



int OsSetTime(const ST_TIME *Time)
{
	struct tm tblock;  
	struct timeval time_tv;
	tblock.tm_year = Time->Year - 1900;
	tblock.tm_mon = Time->Month;
	tblock.tm_mday = Time->Day;
	tblock.tm_hour = Time->Hour;
	tblock.tm_min = Time->Minute;
	tblock.tm_sec = Time->Second;
    time_tv.tv_sec  = mktime(&tblock);
    time_tv.tv_usec = 0;
    settimeofday(&time_tv, NULL);
	return RET_OK;
	//return ERR_NEED_ADMIN;
}



int OsTimerSet(ST_TIMER *Timer,unsigned long Ms)
{
	Timer->Start = OsGetTickCount();
	Timer->Stop = Timer->Start + Ms;
	Timer->TimeLeft =  Ms;
	return	RET_OK;
}

unsigned long OsTimerCheck(ST_TIMER *Timer)
{
	int currtime;
	currtime = (int)OsGetTickCount();
	currtime = (int)Timer->Stop  - currtime;
	if(currtime <= 0)
		return 0;
	return currtime;
}

void OsSleep(unsigned int Ms)
{
	while(Ms)
	{
		if(Ms>1000)
		{
			sleep(Ms/1000);
			Ms =Ms%1000;
		}
		else
		{
			usleep(Ms*1000);
			Ms = 0;
		}
	}
}


int OsGetAppInfo(ST_APP_INFO AppInfo[],int InfoCnt)
{
	if(tSt_Sys.pSysMsg)
	{
		int i;
		for(i=0;i<tSt_Sys.pSysMsg->mAppMax;i++)
		{
			memcpy(&AppInfo[i],&tSt_Sys.pSysMsg->AppInfo[i],sizeof(ST_APP_INFO));
		}
		return i;
	}
	return ERR_SYS_BAD;
}

int OsGetOptInfo(ST_OPT_INFO OptInfo[],int InfoCnt)
{
	if(tSt_Sys.pSysMsg)
	{
		int i;
		for(i=0;i<tSt_Sys.pSysMsg->mOptMax;i++)
		{
			memcpy(&OptInfo[i],&tSt_Sys.pSysMsg->OptInfo[i],sizeof(ST_OPT_INFO));
		}
		return i;
	}
	return ERR_SYS_BAD;
}


int OsExit(int recode)
{
	if(tSt_Sys.pSysMsg)
	{
		memmove(tSt_Sys.pSysData->aAppIDStack,tSt_Sys.pSysData->aAppIDStack+1,sizeof(tSt_Sys.pSysData->aAppIDStack)-1);
		tSt_Sys.pSysData->aAppIDStack[sizeof(tSt_Sys.pSysData->aAppIDStack)-1]=0;
		tSt_Sys.pSysData->pNextAppId=tSt_Sys.pSysData->aAppIDStack[0];
		if(tSt_Sys.pSysMsg)	
		{
			//shmdt(tSt_Sys.pSysMsg);
			munmap(tSt_Sys.pSysMsg,sizeof(ST_SYS_MSG));		
		}		
		if(tSt_Sys.shmAid != -1)
		{		
			close(tSt_Sys.shmAid);		
			tSt_Sys.shmAid = -1;	
		}		
	}

	if(tSt_Sys.pSysData)	
	{
		//shmdt(tSt_Sys.pSysData);
		munmap(tSt_Sys.pSysData,sizeof(ST_SYS_DATA));		
	}		
	if(tSt_Sys.shmDid != -1)
	{		
		close(tSt_Sys.shmDid);		
		tSt_Sys.shmDid = -1;	
	}
	exit(recode);
}

int OsRunApp(char *AppId, char **Argv, void *Data, RUNAPP_CB CbOut,RUNAPP_CB CbErr)
{
	if(tSt_Sys.pSysMsg)
	{
		int i;
	//	if(tSt_Sys.pSysMsg->nCurrAppId != 0)	//master app id =0
	//		return ERR_NEED_ADMIN;
		
		for(i=0;i<tSt_Sys.pSysMsg->mAppMax;i++)
		{
			if(strcmp(tSt_Sys.pSysMsg->AppInfo[i].Id,AppId)==0)
			{
				//char runData[32];
				u8 id,max=0;
				char *pData;
				tSt_Sys.pSysData->pNextAppId=i;
				memmove(tSt_Sys.pSysData->aAppIDStack+1,tSt_Sys.pSysData->aAppIDStack,sizeof(tSt_Sys.pSysData->aAppIDStack)-1);
				tSt_Sys.pSysData->aAppIDStack[0]=i;
		
				if(Argv)
				{
					while(Argv[max] != ((char*)0)) 
					{
						if(strlen(Argv[max]) == 0)
							break;
						max++;
					}
					tSt_Sys.pSysData->sendBuff[0]=max;
					pData = (char*)tSt_Sys.pSysData->sendBuff+1;
					for(id=0;id<max;id++)
					{
						strcpy(pData,Argv[id]);
						pData += strlen(pData)+1;
					}
					tSt_Sys.pSysData->sWriteLen = (unsigned char*)pData - tSt_Sys.pSysData->sendBuff;
				}
				else
				{
					tSt_Sys.pSysData->sWriteLen = 0;
				}
				exit(0);
			//	sprintf(runData,"%s/%s",tSt_Sys.pSysMsg->AppInfo[i].Id,"app_run");
			//	execv(runData , Argv);
			}
		}
		return ERR_APP_NOT_EXIST;
	}
	return 0;
}


int OsGetAppExitCode(void)
{
	if(tSt_Sys.pSysData)
		return tSt_Sys.pSysData->AppExitCode;
	return ERR_MEM_FAULT;
}

//=Key ->系统配置名字，长度不大于 31 个字节，以“persist.sys.”、“rt.sys.”或“rt.app.”开头“\0”结尾。
//Value ->系统配置参数值，长度不大于 64 个字节，以“\0”结尾，不能为 NULL。
int OsRegSetValue(const char *Key,const char *Value)
{
	char *pTag;
	pTag=eStrstr((char*)Key,"persist.sys.");
	if(pTag)
	{

	}
	pTag=eStrstr((char*)Key,"rt.sys.");
	if(pTag)
	{

	}
	pTag=eStrstr((char*)Key,"rt.app.");
	if(pTag)
	{

	}
	return ERR_SYS_NOT_SUPPORT;
}

int OsRegGetValue(const char *Key, char *Value)
{
	char *pTag;
	pTag=eStrstr((char*)Key,"persist.sys.");
	if(pTag)
	{

	}
	pTag=eStrstr((char*)Key,"rt.sys.");
	if(pTag)
	{

	}
	pTag=eStrstr((char*)Key,"rt.app.");
	if(pTag)
	{

	}
	return ERR_SYS_NOT_SUPPORT;
}

#include <sys/stat.h>

//安装或更新应用软件、应用数据、OPT 包、用户公钥、设备固件以及 Prolin 操作系统固件。
int OsInstallFile(const char *Name,const char *FileName,int FileType)
{
	int fd,len;
	char *pfBuff;
	struct stat tFile;
	fd = open(FileName, O_RDWR);
	if(-1 == fd){
		perror("Open uart error");
	}
	// if(stat(fname,&statbuf)==0)
	fstat(fd, &tFile);
	
	pfBuff=(char*)malloc(tFile.st_size);
	if(pfBuff)
	{
		perror("InstallFile malloc NULL");
	}
	len = read(fd, pfBuff, tFile.st_size);
	close(fd);
	//--------------验证签名---------------------------

	if(tSt_Sys.pSysMsg)
	{
		strcpy(tSt_Sys.pSysMsg->AppInfo[tSt_Sys.pSysMsg->mAppMax].Name ,Name);
		
		tSt_Sys.pSysMsg->mAppMax++;
	}
	


/*
	S_IRUSR:	读权限，文件属主
	S_IWUSR:   写权限，文件属主
	S_IXUSR:	执行权限，文件属主
	S_IRGRP:	读权限，文件所属组
	S_IWGRP:   写权限，文件所属组
	S_IXGRP:	执行权限，文件所属组
	S_IROTH:   读权限，其它用户
	S_IWOTH:  写权限，其它用户
	S_IXOTH:   执行权限，其它用户
*/
	fd = open(Name,O_WRONLY|O_CREAT,S_IWUSR|S_IXUSR|S_IXGRP);	// 执行权限，文件所属组
	len = write(fd, pfBuff, len);
	close(fd);

	return 0;
}

int OsUninstallFile(const char *AppName, int FileType)
{
	remove(AppName);
	return 0;
}


int OsFirmwareUpgrade(const char *FwFileName)
{
	return 0;

}

int OsVerifySign(const char *FileName, int PUKType)
{
	return 0;

}

int OsVerifySignExternal(const char *FileName,const void *SignData, int PUKType)
{
	return 0;

}


void OsGetSysVer(int VerType, char *Version)
{


}


void OsSetKeyTone(int OnOff,int DutyCycle)
{


}











int OsMount(const char *Source,const char *Target,const char *FileSystemType,unsigned long MountFlags,const void *Data)
{
	return 0;

}

int OsUmount(const char *Target, int Flags)
{
	return 0;
}

int OsCryptFormat(const char *Dev, const char *Pwd,const char *FsType)
{
	return 0;
}


int OsCryptUmount(const char *Target)
{
	return 0;
}

int OsLed(int Id, unsigned int Color,const char *dev)
{
	return 0;
}

int OsTerminalConsumeInfo(const char *Key, int *Value)
{
	return 0;
}







