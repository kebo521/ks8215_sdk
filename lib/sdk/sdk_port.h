
#ifndef _SDK_PORT_
#define _SDK_PORT_

//==============ͨ��Channel ����===================
#define PORT_COM1		0		//���� 1 UART
#define PORT_COM2		1		//���� 2
#define PORT_COM3		2		//���� 3
#define PORT_PINPAD	3		//���� PinPad
#define PORT_USBDEV	11		//USB �豸ģʽ�˿�
#define PORT_USBHOST	12		//USB ����ģʽ�˿ڣ�host �˿� 0��
#define PORT_USBHID	13		//USBHID �豸�˿�
#define PORT_USBHOST1	14		//USB ����ģʽ�˿ڣ�host �˿� 1��

//==============�ӿڷ�����===================
#define USB_ERR_NOT_OPEN		-3403		//ͨ��δ��
#define USB_ERR_BUF			-3404		//���ͻ���������
#define USB_ERR_NOT_FREE		-3405		//�޿��ö˿�
#define USB_ERR_NO_CONF		-3411		//�豸δ���ö�ٺ����ù���
#define USB_ERR_DISCONN		-3412		//�豸�Ѿ��������Ͽ�
#define USB_ERR_MEM_SYSTEM	-3413		//ϵͳ�ڴ�����쳣
#define USB_ERR_BUSY			-3414		//USB ϵͳæµ
#define USB_ERR_RC_SYSTEM		-3415		//ϵͳ��Դ����ʧ��
#define USB_ERR_DEV_ABSENT	-3416		//USB �������豸����λ
#define USB_ERR_INVALID		-3417		//USB ͨѶ״̬��Ч


extern int OsPortOpen(int Channel,const char *Attr);
extern void OsPortClose(int Channel);
extern int OsPortSend(int Channel,void *SendBuf,int SendLen);
extern int OsPortRecv(int Channel,void *RecvBuf,int RecvLen,int TimeoutMs);
extern int OsPortReset(int Channel);
extern int OsPortCheckTx(int Channel);

//========================֤ͨ�ӿ�=============================================================
//==============pSendBuf ǰ��Ԥ��4���ֽڿռ�[55 02 Len[2]]===========================
//====���ա�.02 Len[2] Data[Len] crc 03���ṹ����,����Data��Len===================
extern int	API_Uart_PackSend(int Channel,u8* pSendBuf,u32 sendLen);
//==============���ա�.02 Len[2] Data[Len] crc 03���ṹ���գ�����Data����============
extern u8*	API_Uart_PackRecv(int Channel,u8* pRecvBuf,u32 *recvLen,int timeOutMs,int* pErrCode);


#endif
