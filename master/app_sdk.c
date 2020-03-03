
//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include "comm_type.h"
#include "sys_sdk.h"
#include "xui_comm.h"

#include "app_sdk.h"


DISPLAY_SCREEN_STATUS OldScreen={0};



//========从src1中查找src2字段=返回匹配src1中的末端地址=======
char *API_eStrstr(char* src1, const char* src2)
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



//===================================================================
int APP_Edit(EDIT_DATA *pEdit,char* pOutStr)
{
	u32 Event;
	while(1)
	{
		API_GUI_CreateShow(pEdit->pTitle,TOK,TCANCEL);
		API_GUI_Edit_Prompt(SIZE_NORMAL,pEdit->pFrontText,SIZE_NORMAL,pEdit->pAfterText);
		API_GUI_Edit(SIZE_NORMAL,pOutStr,pEdit->Max,pEdit->Way,pEdit->Limit);
		API_GUI_Show();
		Event=API_WaitEvent(pEdit->timeOutMs,EVENT_UI,EVENT_NONE);
		if(Event==EVENT_OK) //获取输入卡号数据
		{
			int ret;
			ret=API_GUI_Edit_GetText(pOutStr,33);
			if(ret >= pEdit->Min)
				return ret;
			APP_ShowMsg(pEdit->pTitle,STR_LACK_INPUT,2000);
		}
		if(Event==EVENT_TIMEOUT)
			return OPER_TIMEOUT;
		else if(Event==EVENT_CANCEL)
			return OPER_RET;
	}
}

int APP_InputNum(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen)
{
	int 		ret;
	EDIT_DATA	EditData;	
	CLEAR(EditData);
	EditData.pTitle	      =pTitle;
	EditData.pFrontText	=pFrontTextBuf;
	EditData.pAfterText      =pAfterTextBuf;

	EditData.Min		=InputMinLen;
	EditData.Max		=InputMaxlen;
	EditData.Way		=IME_NUM;
	EditData.Limit		=IME_NUM;
	EditData.timeOutMs=30*1000;

	ret =APP_Edit(&EditData,pInputDef);
	if(ret>=0)
		return 0;
	else
		return 1;
}
//输入数字+字母
int APP_InputAbc(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinlen,int InputMaxlen)
{
	int 	ret;
	EDIT_DATA	EditData;		
	CLEAR(EditData);
	EditData.pTitle	     =pTitle;
	EditData.pFrontText    =pFrontTextBuf;
	EditData.pAfterText     =pAfterTextBuf;

	EditData.Min		=InputMinlen;
	EditData.Max		=InputMaxlen;
	EditData.Way		=IME_NUM;
	EditData.Limit		=IME_NUM|IME_ABC|IME_abc;
       EditData.timeOutMs=30*1000;

	ret =APP_Edit(&EditData,pInputDef);
	if(ret>=0)
		return 0;
	else
		return 1;
}

int APP_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey)
{
	char pOutMsg[40]={0};
	EDIT_DATA tEdit;
	int ret;

	tEdit.pTitle		=pTitle;
	tEdit.pFrontText	=pFrontTextBuf;
	tEdit.pAfterText	=pAfterTextBuf;
	tEdit.Way			=IME_NUM|IME_PIN_MODE;
	tEdit.Limit			=IME_NUM|IME_PIN_MODE;
	tEdit.Min			=1;
	tEdit.Max			=32;
	tEdit.timeOutMs=20*1000;
	ret=APP_Edit(&tEdit,pOutMsg);
	if(ret>=  tEdit.Min)
	{
		if(API_strcmp(pOutMsg,pkey)==0) return 0;

		APP_ShowMsg(pTitle, "\r\n密码错误!",3000);	
	}
	return -1;
}


/*
//=====================================================================
int API_fopen(const char * filename, int flags)
{
	u16	 i=0,pU16File[64];
	DWORD dwDesiredAccess;
	while(*filename)
		pU16File[i++]=*filename++;
	pU16File[i]=0;
	
	if((flags&0x0f)==F_RDONLY)
		dwDesiredAccess=MCFILE_OPERATE_MODE_READ;
	else if((flags&0x0f)==F_WRONLY)
		dwDesiredAccess=MCFILE_OPERATE_MODE_WRITE;
	else if((flags&0x0f)==F_RDWR)
		dwDesiredAccess=MCFILE_OPERATE_MODE_READ|MCFILE_OPERATE_MODE_WRITE;
	
	if(flags&F_CRNEW)
		dwDesiredAccess|=MCFILE_ACCESS_MODE_CREATE_ALWAYS;
	else if(flags&F_CREAT)
		dwDesiredAccess|=MCFILE_ACCESS_MODE_OPEN_ALWAYS;
	else 
		dwDesiredAccess|=MCFILE_ACCESS_MODE_OPEN_EXISTING;
		
	return CreateFile(pU16File,MCFILE_OPERATE_MODE_WRITE|MCFILE_OPERATE_MODE_READ|MCFILE_ACCESS_MODE_OPEN_ALWAYS,0,NULL,0,0,0);
}

int API_fclose(int fd)
{
	return CloseHandle(fd);
}

int API_fseek(int fd,int offset ,int whence)
{
	DWORD dwMoveMethod;
	if(whence==F_SEEK_SET)
		dwMoveMethod=MCFILE_SEEK_BEGIN;
	else if(whence==F_SEEK_CUR)
		dwMoveMethod=MCFILE_SEEK_CUR;
	else //if(whence==F_SEEK_END)
		dwMoveMethod=MCFILE_SEEK_END;
	return SetFilePointer(fd,offset,NULL,dwMoveMethod);
}

int API_fread(int fd,void * buf, u32 count)
{
	DWORD ReadLen=0;
	if(ERROR_SUCCESS != ReadFile(fd,buf,count,&ReadLen,NULL))
	{
		TRACE("API fread Err count[%d]\r\n",count);
		return -1;
	}
	return ReadLen;
}

int API_fwrite(int fd,void * buf,u32 count)
{
	DWORD nWriteLen = 0;
	if(ERROR_SUCCESS != WriteFile(fd, buf, count, &nWriteLen, NULL))
	{
		TRACE("API fwrite Err count[%d]\r\n",count);
		return -1;
	}
	return nWriteLen;
}

int API_fSetSize(int fd,u32 size)
{
	return SetFileSize(fd,size);
}

int API_fGetSize(int fd)
{
	return GetFileSize(fd,NULL); 
}
*/

int API_fremove(const char *filename)
{
	return remove(filename);
}

//=============================================================

//====================================================================
//功能:    保存参数到文件系统
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),Inlen(文件长度)
//输出数据:写入结果 0 为成功
//作者: 	邓国祖	--- 
//创作时间:  20150916
//---------------------------------------------------------------
int APP_FileSaveBuff(const char* pfilePath,u32 offset,void* pBuff,u32 Inlen)
{
	int 	fb;
	int 	ret;
	fb = open(pfilePath,O_WRONLY|O_CREAT,0666);
	if(fb == -1)
	{
		LOG(LOG_ERROR,"APP FileSaveBuff Open[%s] fail\r\n",pfilePath);
		return -1;
	}
	if(offset)
	{
		lseek(fb,offset,SEEK_SET);
	}
	ret=write(fb,pBuff,Inlen);
	close(fb);
	if(Inlen != ret)
	{
		LOG(LOG_ERROR,"APP FileSaveBuff WriteFile[%s] Err ret[%d != %d]\r\n",pfilePath,Inlen,ret);
		return -2;
	}
	return ret;
}
//====================================================================
//功能:    从文件系统读参数
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),pOutlen(输入文件长度)
//输出数据:读取结果 0 为成功
//作者: 	邓国祖	--- 
//创作时间:  20150916
//---------------------------------------------------------------
int APP_FileReadBuff(const char* pfilePath,u32 offset,void* pBuff,u32 buffSize)
{
	int 	fd;
	int 	ret=0;
	fd = open(pfilePath,O_RDONLY);
	if(fd == -1)
	{
		LOG(LOG_ERROR,"APP FileReadBuff Open[%s]fail, \r\n",pfilePath);
		return -1;
	}
	if(pBuff)
	{
		if(offset)
		{
			lseek(fd,offset,SEEK_SET);
		}
		ret=read(fd, pBuff, buffSize);
		if(buffSize != ret)
		{
			LOG(LOG_ERROR,"APP FileReadBuff Read[%s] Err nReadSize[%d,%d]\r\n",pfilePath,ret,buffSize);
		}
	}
	else 
	{
		struct stat tFile;
		fstat(fd, &tFile);
		ret = tFile.st_size;
	}
	close(fd);
	return ret;
}



//---输入格式 2018 03 08 17 03 43---每个元素间隔不限----------------
void SetSysDateTime(char *pInDateTime)
{
	ST_TIME dtime,inTime;
	char sBuff[8];
	//2018 03 08 17 03 43
	API_memcpy(sBuff,pInDateTime,4); sBuff[4]='\0';
	inTime.Year =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+5,2); sBuff[2]='\0';
	inTime.Month=API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+8,2); //sBuff[2]='\0';
	inTime.Day =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+11,2); //sBuff[2]='\0';
	inTime.Hour =API_atoi(sBuff);

	API_memcpy(sBuff,pInDateTime+14,2); //sBuff[2]='\0';
	inTime.Minute=API_atoi(sBuff);
	
	OsGetTime(&dtime);
	if(dtime.Year!=inTime.Year || dtime.Month!=inTime.Month || dtime.Day!=inTime.Day \
		|| dtime.Hour!=inTime.Hour || dtime.Minute!=inTime.Minute)
	{
		API_memcpy(sBuff,pInDateTime+17,2); //sBuff[19]='\0';
		inTime.Second=API_atoi(sBuff); 
		OsSetTime(&inTime); 
	}
}





