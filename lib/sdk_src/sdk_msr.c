
/**
 * =======================磁条阅读器=========================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include "comm_type.h"
#include "sys_sdk.h" 
#include "sdk_msr.h" 

#include "sdk_port.h" 
#ifdef EXT_INTERFACE
static ST_MSR_DATA tMsrData[3];
static int flag_msr_read=0;
#endif

//功能 打开磁条阅读器设备。
/*返回
	RET_OK 成功
	ERR_DEV_NOT_EXIST 设备不存在
	ERR_DEV_BUSY 设备被占用
	ERR_DEV_NOT_OPEN 设备打开失败 */
int OsMsrOpen(void)
{
#ifdef EXT_INTERFACE
	u8 buff[32],*p;
	u32 recvLen;
	p=buff+4;
	*p++ = 0x01;
	*p++ = 0x01;
	API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
	recvLen = sizeof(buff);
	p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
	flag_msr_read=1;
	if(p)
	{
		return p[2];
	}
	return ERR_TIME_OUT;
#else


	return ERR_DEV_NOT_EXIST;
#endif
	
}


//功能 关闭磁条读卡器设备。
void OsMsrClose(void)
{
	#ifdef EXT_INTERFACE
	u8 buff[32],*p;
	u32 recvLen;
	p=buff+4;
	*p++ = 0x01;
	*p++ = 0x02;
	flag_msr_read=0;
	API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
	recvLen = sizeof(buff);
	p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
	if(p)
	{
		//return p[2];
	}
	//return ERR_TIME_OUT;
	#else


	#endif
}

//功能 软复位磁条卡阅读器，并清除已读取的磁条卡数据。
void OsMsrReset(void)
{
	#ifdef EXT_INTERFACE
	u8 buff[32],*p;
	u32 recvLen;
	p=buff+4;
	*p++ = 0x01;
	*p++ = 0x04;
	*p++ = 0x00;
	*p++ = 0x00;
	flag_msr_read=1;
	API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
	recvLen = sizeof(buff);
	p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
	if(p)
	{
		//return p[2];
	}
	//return ERR_TIME_OUT;
	#else


	#endif
}


//功能 检测是否刷卡。
/*返回
	TRUE 已刷
	FALSE 未刷
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrSwiped(void)
{
	#ifdef EXT_INTERFACE
	u8 buff[512],*p;
	u32 recvLen;
	p=buff+4;
	*p++ = 0x01;
	*p++ = 0x03;
	API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
	recvLen = sizeof(buff);
	p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
	if(p!=NULL && p[2]==0x00 && recvLen>3)
	{
		p += 3;
		
		tMsrData[0].DataLen=*p++;
		if(tMsrData[0].DataLen)
		{
			tMsrData[0].Status = 0;
			memcpy(tMsrData[0].TrackData,p,tMsrData[0].DataLen);
			p += tMsrData[0].DataLen;
		}
		else tMsrData[0].Status = 1;

		tMsrData[1].DataLen=*p++;
		if(tMsrData[1].DataLen)
		{
			tMsrData[1].Status = 0;
			memcpy(tMsrData[1].TrackData,p,tMsrData[1].DataLen);
			p += tMsrData[1].DataLen;
		}
		else tMsrData[1].Status = 1;

		tMsrData[2].DataLen=*p++;
		if(tMsrData[2].DataLen)
		{
			tMsrData[2].Status = 0;
			memcpy(tMsrData[2].TrackData,p,tMsrData[2].DataLen);
			p += tMsrData[2].DataLen;
		}
		else tMsrData[2].Status = 1;
		flag_msr_read=2;
		return TRUE;
	}
	return FALSE;
	#else
	return ERR_DEV_NOT_OPEN;
	#endif
	
}


//功能 读取磁条卡数据。
/*参数
	Track1【输出】 输出1 磁道数据
	Track2【输出】 输出2 磁道数据
	Track3【输出】 输出3 磁道数据
返回
	RET_OK 成功读取
	ERR_MSR_NOT_SWIPED 未刷卡
	ERR_INVALID_PARAM 非法参数
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrRead(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3)
{
	#ifdef EXT_INTERFACE
	if(flag_msr_read == 2)
	{
		memcpy(Track1,&tMsrData[0],sizeof(ST_MSR_DATA));
		memcpy(Track2,&tMsrData[1],sizeof(ST_MSR_DATA));
		memcpy(Track3,&tMsrData[2],sizeof(ST_MSR_DATA));
		return RET_OK;
	}
	else if(flag_msr_read == 1)
		return ERR_MSR_NOT_SWIPED;
	return ERR_DEV_NOT_OPEN;
	#else
	return ERR_DEV_NOT_OPEN;
	#endif
}


//功能 读取通用的单面磁条卡或者编码方式为JIS 的双面磁条卡的数据。
/*参数
	Track1【输出】 输出1 磁道数据
	Track2【输出】 输出2 磁道数据
	Track3【输出】 输出3 磁道数据
	Track4【输出】 输出4 磁道数据
返回
	RET_OK 成功读取
	ERR_MSR_NOT_SWIPED 未刷卡
	ERR_INVALID_PARAM 非法参数
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrReadJIS(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3,ST_MSR_DATA *Track4)
{
	return ERR_DEV_NOT_OPEN;
}


