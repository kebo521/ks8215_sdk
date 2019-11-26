/**
 * File:   fbshow.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  snap framebuffer to png file
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "comm_stu.h"


#include <unistd.h>
//#include <stdarg.h>
//#include <fcntl.h>
#include <sys/wait.h>
#include<sys/stat.h>



//#include "main.h"
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>
#include <sys/shm.h>  

#include <sys/types.h>
#include <sys/stat.h>

#include <signal.h>

#include "file_stu.h"
#include "tls_sdk.h"
//#include "sys_sdk.h"


//=========================================================================
#include <stdarg.h>

void API_Trace(char* pMsg,...)
{
	va_list arg;
	va_start(arg, pMsg);
	vprintf(pMsg,arg);	//ret=
	va_end(arg);
}

void APP_Trace_Hex(char* msg,void* pBuff,int Len)
{
	int i;
	printf("%s[%d]:",msg,Len);
	for(i=0;i<Len;i++)
	{
		printf("%02X ",((u8*)pBuff)[i]);
	}
	printf("\r\n");
}

//#define LOG(format, ...) fprintf(stdout, format, __VA_ARGS__)
#define TRACE				API_Trace
#define TRACE_HEX		APP_Trace_Hex




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

#define Tms_TMS_sApp		"tms_run" 
#define	S_SYS_MSG_PATH	"shmaid.bin"
#define SHM_SDK_AID		0xA8215		//��������ƽ̨ͳһ��
#define SHM_SDK_DID		0xD8215		//��������ƽ̨ͳһ��


int InstallMasterAPP(const char* pKspPath,ST_APP_INFO* pAppInfo,void (*ShowBottomProgress)(unsigned char))
{ // ���ļ�ϵͳ�ж�ȡӦ��
	u8  i,tmsSetup,appSetup,resLogoSetup; //ret bit0,logo bit1
	int ks_fd,ret,kspoffset,totalLen,compLen;
	KSP_FILE_HEAD head;
	int		MaxSet,CruSet;
	u8		*pBuffData;
	u32 	fileLen;
	u32 	offset;
	u8					signout[256];
	KSP_SIGN_CONTEXT 	*tKspSignContext;
	TRACE("InstallMasterAPP[%s] Init\r\n",pKspPath);
	//----------------��ȡKSP�ļ�ͷ----------------------------------
	ks_fd=open(pKspPath,O_RDONLY);
	if(ks_fd == -1)
	{
		TRACE("fs read err.\r\n");
		return -1;
	}
	ret = read(ks_fd,&head, sizeof(KSP_FILE_HEAD));
	if(sizeof(KSP_FILE_HEAD) != ret) 
	{
		TRACE("fs read len[%d] err.\r\n",ret);
		close(ks_fd);
		remove(pKspPath);
		return -1;
	}
	TRACE_HEX("head",&head,20);
	if (0 != memcmp(head.Mask, "FKSP", 4)) 
	{
		TRACE("fs read mask err.\r\n");
		close(ks_fd);
		remove(pKspPath);
		return -2;
	}
	kspoffset = sizeof(KSP_FILE_HEAD);
	totalLen= BYTE4_TO_INT(head.DataLen);
	if(totalLen < 16) 
	{
		TRACE("kspoffset[%d],totalLen:%d Err\r\n",kspoffset,totalLen);
		close(ks_fd);
		remove(pKspPath);
		return 1;
	}
	//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CHECK_PACKAGE);
#if(1)
	offset = 0;
	tKspSignContext =(KSP_SIGN_CONTEXT *)signout;
	if(APP_rsa_PrivatekeyPublic((char*)sMaster_Cert_ZT,sizeof(sMaster_Cert_ZT),head.signcode, signout) == 0) // ǩ������֤
	{
		int ret;
		u8 shaResult[32];
		mbedtls_md_context_t ctx;
//		TRACE_HEX("signout",signout,sizeof(KSP_SIGN_CONTEXT));
		//-------------------SHA256��֤--------------------------
		MaxSet = 32*1024;
		pBuffData=(u8*)malloc(MaxSet);
		api_tls_InterFace.hash->md_starts(&ctx,MBEDTLS_MD_SHA256);

		lseek(ks_fd,kspoffset,SEEK_SET);
		while(offset < totalLen) 
		{
			CruSet = totalLen - offset;
			if(CruSet>MaxSet) CruSet=MaxSet;

			ret=read(ks_fd,pBuffData,CruSet);
			//ret=APP_FileReadBuff(pKspPath,kspoffset+offset,pBuffData,CruSet);
			if(ret < CruSet)
			{
				TRACE("APP FileReadBuff CruSet:%d ret:%d\r\n",CruSet,ret);
				break;
			}
			api_tls_InterFace.hash->md_update(&ctx,pBuffData,ret);
			offset += ret;
		}
		api_tls_InterFace.hash->md_finish(&ctx,shaResult,NULL);
		free(pBuffData);
		if(offset == totalLen)
		{
			if (memcmp(shaResult, tKspSignContext->hashResult, 32) != 0) 
			{
				TRACE_HEX("sha256-1", tKspSignContext->hashResult, 32);
				TRACE_HEX("sha256-2", shaResult, 32);
				//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_VERIFY_SIGN_ERR);
				close(ks_fd);
				remove(pKspPath);
				//Sleep(3000);
				return -4;
			}
		}
	}

	if(offset < totalLen)
	{
		TRACE("ks signinfo check err.\r\n");
		//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CALC_SIGN_ERR);
		close(ks_fd);
		remove(pKspPath);
		//Sleep(3000);
		return -3;
	}	
	mkdir(tKspSignContext->app.tag,0666);	//������ӦĿ¼
	chdir(tKspSignContext->app.tag);		//�����ӦĿ¼
#endif
	//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_INSTALLING);
	// д��Ӧ����Ϣ����
	compLen = 0;	
	tmsSetup=0;
	appSetup=0;
	resLogoSetup=0;
  	MaxSet = 32*1024;
	pBuffData=(u8*)malloc(MaxSet);
  	TRACE("write app[%d]\r\n",head.filenum);
	if(ShowBottomProgress) ShowBottomProgress(0);	//��ʼ������
	//-----������--------------
	//�ȹ��ֿ��ļ��������ڸ����ֿ⡣
	//------------------------------
	{
		int 	Tfd;
		char	fileName[16+1];
		char	dir_name[20+3];
		KSP_FILE_ITEM tFileItem;
		//-----�򿪰�װ�ļ�------------
		// ���¶�ȡ�ļ��������ļ�д�����ϵͳ
		for (i = 0; i < head.filenum; i++) 
		{
			// ��һ����
			lseek(ks_fd,kspoffset,SEEK_SET);
			read(ks_fd,&tFileItem,sizeof(tFileItem));
			//APP_FileReadBuff(pKspPath,kspoffset,&tFileItem, sizeof(tFileItem));
			memcpy(fileName,tFileItem.fileName,16);
			fileName[16]='\0';
			fileLen = BYTE4_TO_INT(tFileItem.fileLen);		
			kspoffset += sizeof(tFileItem); 	
			TRACE("filename[%d]:%s,fileLen=%d\r\n",i,fileName,fileLen);		
			Tfd = -1;
			if(0 == strcmp("/hd/tms", fileName)) //TMS�������
			{ 
				strcpy(dir_name,Tms_TMS_sApp);
				//remove(dir_name);
				tmsSetup=1;
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0777);
			}
			else if(0 == strcmp("/hd/app", fileName)) //Ӧ�ø���
			{ 
			
			}
			else	//��Դ����
			{ 
				strcpy(dir_name, fileName);
				if(!(resLogoSetup&0x01))
				{
					if(strcmp("ks.res", fileName) == 0) //�ֿ���Դ
					{ 
						resLogoSetup |= 0x01;
					}
				}
				if(!(resLogoSetup&0x02))
				{
					if(strstr(fileName,"Logo."))//logo ��Դ
					{
						resLogoSetup |= 0x02;
					}
				}
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0666);
			}
			compLen += sizeof(KSP_FILE_ITEM);
			if(Tfd == -1)
			{
				TRACE("API fopen CRNEW[%s]\r\n",dir_name);
				continue;
			}
			//------------ˢ�½�����----------------------
			if(ShowBottomProgress) ShowBottomProgress(compLen*100/totalLen);
			//-------------SetData-----------------------------
			{
				offset = 0;
				while(offset < fileLen) 
				{
					CruSet = fileLen - offset;
					if(CruSet>MaxSet) CruSet=MaxSet;
					// ��Ŀ���ļ�
					lseek(ks_fd,kspoffset+offset,SEEK_SET);
					ret=read(ks_fd,pBuffData,CruSet);
					if(ret != CruSet)
					{
						TRACE("ERR->FileReadBuff->%s,CruSet=%d,ret=%d\r\n",pKspPath,CruSet,ret);
						break;
					}
					// д���ļ�ϵͳ
					//lseek(Tfd,offset,SEEK_SET);
					ret=write(Tfd,pBuffData,CruSet);
					if (ret != CruSet) 
					{
						TRACE("ERR->FileSaveBuff->%s,CruSet=%d,ret=%d\r\n",dir_name,CruSet,ret);
						break;
					}
					offset += CruSet;
					//------------ˢ�½��ȵ�----------------------
					compLen += CruSet;
					if(ShowBottomProgress) ShowBottomProgress(compLen*100/totalLen);
				}
				close(Tfd);
				if(offset < fileLen)
				{
					TRACE("ERR->FileSave->%s ERR[%d<%d]\r\n",dir_name,offset,fileLen);
					remove(dir_name);
				}
			}
			// ���ļ�����
			kspoffset += fileLen;
		}
	}
	close(ks_fd);
	free(pBuffData);
	TRACE("CheckSetup:resLogo=%x,app=%d,tms=%d\r\n",resLogoSetup,appSetup,tmsSetup);
	remove(pKspPath);
	TRACE("API fremove[%s]\r\n",pKspPath);
	//---------------����LOGO-----------------------------------
	if(resLogoSetup&0x02)
	{

	}
	//----------------��װ����-----------------------------------
	if(resLogoSetup&0x01)
	{
	
	}
	//--------------��װ����-----------------------------------
	if(tmsSetup)	//��װ����
	{
		strcpy(pAppInfo->Id,tKspSignContext->app.tag);
		strcpy(pAppInfo->Name,tKspSignContext->app.name_cn);
		strcpy(pAppInfo->Desc,tKspSignContext->app.name_en);
		strcpy(pAppInfo->Artwork,tKspSignContext->app.sdk_ver);
		strcpy(pAppInfo->Vender,tKspSignContext->app.app_time);
		strcpy(pAppInfo->Version,tKspSignContext->app.app_ver);
	}
	return 0;
}

ST_SYS_MSG *pSysMsg=NULL;


void signSaveShmMsg(int signo)
{
	if(pSysMsg)
	{
		int fd = open(S_SYS_MSG_PATH,O_RDWR,0666);
		if (fd != -1)
		{
			write(fd,pSysMsg,sizeof(ST_SYS_MSG));
			close(fd);
		}
	}
}

/*
int my_signal(int sig,void (*handler)(int))
{
    struct sigaction act;
    struct sigaction oldact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(sig, &act, &oldact) < 0)
        return SIG_ERR;

    return (int)oldact.sa_handler;
}
*/

int main(int argc, char* argv[]) 
{
	int ret;
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return -1;
	}
	TRACE("1->InitProcessPool getpid[%d]fork[%d]\r\n",getpid(),pid);
	if(pid != 0)
		return 1;
	pid=setsid();
	TRACE("2->InitProcessPool getpid[%d]setsid[%d]\r\n",getpid(),pid);
	if(pid < 0)
	{
		printf("setsid failed\n");
		return 2;
	}
	//chdir("/");
	{
		int fd;
		fd = open ("/dev/null", O_RDWR, 0);
		if (fd != -1)
		{
			dup2 (fd, STDIN_FILENO);
		//	dup2 (fd, STDOUT_FILENO);
			dup2 (fd, STDERR_FILENO);
			if (fd > 2)
				close(fd);
		}
	}
	TRACE("Create a shared memory Init\r\n");
	//----------------------------------------------------------------
	int shmDid=shmget(SHM_SDK_DID,sizeof(ST_SYS_DATA),0666|IPC_CREAT);  
	if(shmDid == -1)
	{
		TRACE("shared memory shmgetDATA %d\r\n",shmDid);
		return -1;
	}
	ST_SYS_DATA *pSysData=(ST_SYS_DATA *)shmat(shmDid,0,0); //SHM_RDONLY|SHM_RND
	if(pSysData)
	{
		memset(pSysData,0x00,sizeof(ST_SYS_DATA));
	}
	//----------------------------------------------------------------
	int shmAid=shmget(SHM_SDK_AID,sizeof(ST_SYS_MSG),0666|IPC_CREAT);  	
	if(shmAid == -1)
	{
		TRACE("shared memory shmget\r\n");
		return -1;
	}
	
	pSysMsg=(ST_SYS_MSG *)shmat(shmAid,0,0); //SHM_RDONLY|SHM_RND
	if(pSysMsg)
	{
		int fd = open(S_SYS_MSG_PATH,O_RDWR,0666);
		if (fd != -1)
		{
			read(fd,pSysMsg,sizeof(ST_SYS_MSG));
			close(fd);
		}
		else
		{
			memset(pSysMsg,0x00,sizeof(ST_SYS_MSG));
		}
		pSysMsg->pid = getpid();
		pSysMsg->sig = SIGUSR1;	//SIGRTMIN SIGRTMAX
	}

	signal(pSysMsg->sig,signSaveShmMsg);
//	my_signall(pSysMsg->sig,signSaveShmMsg);
	
//	int sigqueue(pid_t pid, int sig, const union sigval val)
//	sigqueue(pSysMsg->pid,pSysMsg->sig,(const union sigval)0);
	
//	umask(0);	//�ӽ���Ȩ��	
	while(1) 
	{
		if(pSysMsg->mAppMax == 0)
		{//---------�����ذ�װ����-------------
			if(0==InstallMasterAPP("Master.ksp",&pSysMsg->AppInfo[0],NULL))
			{
				pSysMsg->mAppMax++;
				//sigqueue(pSysMsg->pid,pSysMsg->sig,(sigval_t)0);
				//sigqueue(0,pSysMsg->sig,(sigval_t)0);
				raise(pSysMsg->sig);
				/*
				int fd = open(S_SYS_MSG_PATH,O_RDWR,0666);
				if (fd != -1)
				{
					write(fd,pSysMsg,sizeof(ST_SYS_MSG));
					close(fd);
				}
				*/
				pSysData->pNextAppId =0;
			}
			else
			{
				sleep(10);
				continue;
			}
		}
		//-----------------------------------------------------
		pid=fork();
		if (pid < 0)
		{
			perror("fork");
			return -2;
		}
		if (pid != 0)
		{//---�ػ�����-------
			pid_t _pid_t;
			_pid_t = wait(&pid); //---�ȴ�����̽���------
			printf("------reRunAPP-[%d,%d]---------\n",_pid_t,pid);
			pSysData->AppExitCode= (int)_pid_t;
		} 
		else break; //����̣���������ִ��
	} 

	if(pSysData->pNextAppId == 0)
	{//------����Ӧ��-------------
		pSysData->nCurrAppId=0;
		umask(0); //���ؽ���Ȩ��
		ret=execl(Tms_TMS_sApp,"master",(char*)0);
	}
	else
	{//-------����Ӧ��-------------
		pSysData->nCurrAppId=pSysData->pNextAppId;
		chdir(pSysMsg->AppInfo[pSysData->nCurrAppId].Id);	//�����ӦĿ¼
		umask(0); //Ӧ�ý���Ȩ��
		ret=execl("./app_run","app_run",(char*)0);
	}

	//----------------��������-------------------------------------
	ret=shmdt(pSysMsg);
	TRACE(" a shared pSysMsg[%d]\r\n",ret);
	ret=shmctl(shmAid,IPC_RMID,NULL);
	TRACE(" a shared memory shmctl[%d]\r\n",ret);
	
	ret=shmdt(pSysData);
	TRACE(" a shared pSysData[%d]\r\n",ret);
	ret=shmctl(shmAid,IPC_RMID,NULL);
	TRACE(" a shared memory shmctl[%d]\r\n",ret);
	return 0;
}








