
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
#include "sdk_port.h" 
#include "usart.h" 

static int comfd[3]={0};//,pinpadfd;

//请参考通信端口宏定义列表中定义的端口号。
//Attr 当 Channel 为 UART 口时，其格式为：“波特率，数据位数，奇偶校验位，停止位”其中用半角逗号隔开。
int OsPortOpen(int Channel,const char *Attr)
{
	if(Channel < PORT_PINPAD)
	{
		int speed;
		u8 parity,databits,stopbits,flow_ctrl;
		int fd;
		if(Attr==NULL) return ERR_INVALID_PARAM;
		if(Channel == PORT_COM1)
		{
			comfd[0]=uart_open("/dev/ttyS0");
			fd = comfd[0];
		}
		else if(Channel == PORT_COM2)
		{
			comfd[1]=uart_open("/dev/ttyS1");
			fd = comfd[1];
		}
		else if(Channel == PORT_COM3)
		{
			comfd[2]=uart_open("/dev/ttyS2");
			fd = comfd[2];
		}
		if(fd  < 0) return ERR_DEV_NOT_EXIST;
		//"9600,8,n,1"
		speed=atoi(Attr);
		while(*Attr != ',') Attr++;
		Attr++;
		databits=atoi(Attr);
		while(*Attr != ',') Attr++;
		Attr++;
		parity = *Attr++;
		while(*Attr != ',') Attr++;
		Attr++;
		stopbits = atoi(Attr);
		flow_ctrl =0 ;
		LOG(LOG_INFO,"[%d]->[%d][%d][%d][%d]\r\n",fd,speed,databits,stopbits,parity);
		if(0 == uart_set(fd,speed,flow_ctrl,databits,stopbits,parity))
			return RET_OK;
		uart_close(fd);
		return ERR_INVALID_PARAM;
	}
	return ERR_DEV_NOT_EXIST;
}
void OsPortClose(int Channel)
{
	if(Channel < PORT_PINPAD)
	{
		LOG(LOG_INFO,"OsPortClose[%d]\r\n",comfd[Channel]);
		if(comfd[Channel])
			uart_close(comfd[Channel]);
		comfd[Channel]=0;
	}

}
int OsPortSend(int Channel,void *SendBuf, int SendLen)
{
	if(Channel < PORT_PINPAD)
	{
		if(comfd[Channel] == 0)
			return ERR_DEV_NOT_OPEN;
		return uart_send(comfd[Channel],SendBuf,SendLen);
	}
	return 0;
}
int OsPortRecv(int Channel,void *RecvBuf,int RecvLen,int TimeoutMs)
{
	if(Channel < PORT_PINPAD)
	{
		if(comfd[Channel] == 0)
			return ERR_DEV_NOT_OPEN;
		 return uart_recv(comfd[Channel],RecvBuf,RecvLen,TimeoutMs);
	}
	return 0;
}
int OsPortReset(int Channel)
{
	if(Channel < PORT_PINPAD)
	{
		
		//TCIFLUSH,TCOFLUSH,TCIOFLUSH
		//tcflush(comfd[Channel],TCIOFLUSH);
		//int ret;
		char buff[1024];
		uart_recv(comfd[Channel],buff,sizeof(buff),0);
		//fcntl(comfd[Channel],F_SETFL,FNDELAY);
		//while((ret=read(comfd[Channel],buff,sizeof(buff))) > 0)
		//{
		//	TRACE_HEX("OsPortReset",buff,ret);
		//}
		//fcntl(comfd[Channel],F_SETFL,0);
	}
	return 0;
}
int OsPortCheckTx(int Channel)
{
	if(Channel < PORT_PINPAD)
	{
	/*
		int fs_sel;  
		fd_set fs_write;    
		struct timeval time;  
		FD_ZERO(&fs_write);	  
		FD_SET(comfd[Channel],&fs_write);	
		time.tv_sec = 5;	
		time.tv_usec = 0;	 
		fs_sel = select(comfd[Channel]+1,NULL,&fs_write,NULL,&time);
		LOG(LOG_INFO,"CheckTx[%s]\r\n",fs_sel);
		FD_CLR(comfd[Channel],&fs_write);
		return fs_sel;
		*/
	}
	return 0;
}




//==============pSendBuf 前面预留4个字节空间[55 02 Len[2]]===========================
//====按照【.02 Len[2] Data[Len] crc 03】结构发送,传入Data与Len===================
int	API_Uart_PackSend(int Channel,u8* pSendBuf,u32 sendLen)
{
	u8 crc=0;
	u16 i;
	int ret;
	*(--pSendBuf) = sendLen&0xff;
	*(--pSendBuf) = sendLen/256;
	sendLen += 2;
	for(i=0;i<sendLen;i++)
		crc ^= pSendBuf[i];
	pSendBuf[i++]=crc;
	pSendBuf[i++]=0x03;
	*(--pSendBuf) = 0x02;
	*(--pSendBuf) = 0x55;
	sendLen += 4;
//	TRACE_HEX("->PackSendBuf",pSendBuf,sendLen);
	ret= OsPortSend(Channel,pSendBuf,sendLen);
	if(ret < 0) return ret;
	return (ret-4);
}

//==============按照【.02 Len[2] Data[Len] crc 03】结构接收，返回Data数据================
u8*	API_Uart_PackRecv(int Channel,u8* pRecvBuf,u32 *recvLen,int timeOutMs,int* pErrCode)
{
	int ret,recvSize;
	u16 ulen,offset;
	ret=OsPortRecv(Channel,pRecvBuf,6,timeOutMs);
	if(ret < 5)
	{
		LOG(LOG_ERROR,"###Uart_PackRecv recv5 ret[%d]size[%d] ##\r\n",ret,*recvLen);
		if(pErrCode) *pErrCode=ERR_TIME_OUT;
		return NULL;
	}
	offset = 0;
	while(offset < ret)
	{
		if(pRecvBuf[offset] == 0x02) break;
		offset++;
		if(offset == ret)
		{
			LOG_HEX(LOG_WARN,"***Uart_PackRecv Nouse",pRecvBuf,ret);
			ret=OsPortRecv(Channel,pRecvBuf,6,100);
			if(ret < 5) 
			{
				LOG(LOG_WARN,"###Uart_PackRecv ret[%d]\r\n",ret);
				if(pErrCode) *pErrCode=ERR_INVALID_PARAM;
				return NULL;
			}
			offset = 0;
		}
	}
	if(offset > 0)
	{
		memmove(pRecvBuf,pRecvBuf+offset,ret-offset);
		offset = ret-offset;
		if(offset < 3)
		{
			ret=OsPortRecv(Channel,pRecvBuf+offset,5-offset,100);
			if(ret < (5-offset))
			{
				LOG(LOG_WARN,"###Uart2PackRecv[%d]ret[%d]\r\n",(5-offset),ret);
				if(pErrCode) *pErrCode=ERR_INVALID_PARAM;
				return NULL;
			}
			offset += ret;
		}
	}
	ulen=pRecvBuf[1]*256 + pRecvBuf[2];
	if(ulen > 0)
	{
		if(*recvLen < (ulen+5))
		{
			LOG(LOG_ERROR,"###recvSize[%d]to small  ulen[%d]\r\n",*recvLen,ulen);
			return NULL;
		}
		recvSize = (ulen+5-offset);
		ret=OsPortRecv(Channel,pRecvBuf+offset,recvSize,(recvSize>10)?(recvSize/10):500);
		if(ret < 0)
		{
			LOG(LOG_ERROR,"##UartPackRecv1 ret[%d]\r\n",ret);
			return NULL;
		}
		offset += ret;
		if(ret < recvSize)
		{
			LOG(LOG_WARN,"**Uart2PackRecv[%d]Size[%d]\r\n",ret,recvSize);
			ret = OsPortRecv(Channel,pRecvBuf+offset,recvSize-ret,3000);
			if(ret < 0)
			{
				LOG_HEX(LOG_INFO,"to small->PackRecv2",pRecvBuf,offset);
				return NULL;
			}
			offset += ret;
		}
	}
	else if(offset < 5)
	{
		ret=OsPortRecv(Channel,pRecvBuf+offset,5-offset,200);
		if(ret < (5-offset))
		{
			LOG(LOG_WARN,"###Uart3PackRecv[%d]ret[%d]\r\n",(5-offset),ret);
			if(pErrCode) *pErrCode=ERR_INVALID_PARAM;
			return NULL;
		}
		offset += ret;
	}
	//if(offset >= (ulen+5))
	{
		u8* p;
		u16 i;
		u8 crc;
	//	LOG_HEX(LOG_INFO,"->PackRecvBuf",pRecvBuf,offset);
		p = pRecvBuf+1;
		crc = *p++;
		crc ^= *p++;
		for(i=0;i<ulen;i++)
			crc ^= *p++;
		if(crc == *p)
		{
			*recvLen = ulen;
			return pRecvBuf+3;
		}
		if(pErrCode) *pErrCode=ERR_VERIFY_SIGN_FAIL;
		//LOG_HEX(LOG_ERROR,"ERR->PackRecvBuf",pRecvBuf,ulen+5+start);
		LOG(LOG_ERROR,"###ERR recv crc[%x] != [%x],ulen[%d] ##\r\n",*p,crc,ulen);
		return NULL;
	}
	if(pErrCode) *pErrCode=ERR_INVALID_PARAM;
	LOG(LOG_ERROR,"###recvlen[%d] <[%d] to small##\r\n",ret,recvSize);
	return NULL;
}

