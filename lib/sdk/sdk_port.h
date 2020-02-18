
#ifndef _SDK_PORT_
#define _SDK_PORT_

//==============通道Channel 定义===================
#define PORT_COM1		0		//串口 1 UART
#define PORT_COM2		1		//串口 2
#define PORT_COM3		2		//串口 3
#define PORT_PINPAD	3		//外置 PinPad
#define PORT_USBDEV	11		//USB 设备模式端口
#define PORT_USBHOST	12		//USB 主机模式端口（host 端口 0）
#define PORT_USBHID	13		//USBHID 设备端口
#define PORT_USBHOST1	14		//USB 主机模式端口（host 端口 1）

//==============接口返回码===================
#define USB_ERR_NOT_OPEN		-3403		//通道未打开
#define USB_ERR_BUF			-3404		//发送缓冲区错误
#define USB_ERR_NOT_FREE		-3405		//无可用端口
#define USB_ERR_NO_CONF		-3411		//设备未完成枚举和配置过程
#define USB_ERR_DISCONN		-3412		//设备已经与主机断开
#define USB_ERR_MEM_SYSTEM	-3413		//系统内存出现异常
#define USB_ERR_BUSY			-3414		//USB 系统忙碌
#define USB_ERR_RC_SYSTEM		-3415		//系统资源申请失败
#define USB_ERR_DEV_ABSENT	-3416		//USB 主机上设备不在位
#define USB_ERR_INVALID		-3417		//USB 通讯状态无效


extern int OsPortOpen(int Channel,const char *Attr);
extern void OsPortClose(int Channel);
extern int OsPortSend(int Channel,void *SendBuf,int SendLen);
extern int OsPortRecv(int Channel,void *RecvBuf,int RecvLen,int TimeoutMs);
extern int OsPortReset(int Channel);
extern int OsPortCheckTx(int Channel);

//========================证通接口=============================================================
//==============pSendBuf 前面预留4个字节空间[55 02 Len[2]]===========================
//====按照【.02 Len[2] Data[Len] crc 03】结构发送,传入Data与Len===================
extern int	API_Uart_PackSend(int Channel,u8* pSendBuf,u32 sendLen);
//==============按照【.02 Len[2] Data[Len] crc 03】结构接收，返回Data数据============
extern u8*	API_Uart_PackRecv(int Channel,u8* pRecvBuf,u32 *recvLen,int timeOutMs,int* pErrCode);


#endif
