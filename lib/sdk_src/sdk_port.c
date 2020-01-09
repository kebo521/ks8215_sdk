
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



