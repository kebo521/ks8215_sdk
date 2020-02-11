#ifndef _APP_SDK_
#define _APP_SDK_

#define		OPER_OK				0
	
#define	 	OPER_RET			-1
#define	 	OPER_QUIT			-2
#define	 	OPER_TIMEOUT		-3
#define    	OPER_RDMagERR     -4 		//������
#define    	OPER_CRCERR     	-5 		//У��ʧ��
#define		OPER_ERR			-6		//����ʧ��
#define 	OPER_SYSTEM_ERROR	-7		//����ʧ��
#define 	OPER_TRANS_OVER	-8	    //����������ȷ����ʾʧ��msg
#define		OPER_OFFLINE		-11		//�¼�
#define		OPER_LOW_VOLTAGE	-15		//��ѹ����
#define		OPER_HARD_Err		-16		//Ӳ������
#define		OPER_SEND_ERR		-1000	//��������ʧ��
#define		OPER_RECV_ERR		-2000	//��������ʧ��


#define		OPER_NO_CHECK		15		//��ǩ������
#define		OPER_NoEND 			6		//�ɹ�����δ����	
#define		OPER_NoHEAD  		5		//δ�ҵ�ͷ��
#define		OPER_HARD			4		//�ֹ�����
#define		OPER_NEW			3		//����������
#define		OPER_PAY			1		//ȷ��֧��

#define		SOCKET_UN_APN			-101		//δ��APN
#define		SOCKET_UN_IP			-102		//δ����IP
#define		SOCKET_UN				-200		//δ����IP

#define	SIZE_NORMAL		24


typedef struct
{
	u16		ReDisplayScreen;
	u16		StatusMcc,StatusMnc;
	u16		Hour,Minute;
	u16		PDPStatus;
	u16		SleepTimeS;
	u8		SleepEn,SaveSleepEn;		//���߿���
	u8		SleepState;
	u8		SleepDeep;		//�������
	u8		screenRefState;
	u8		batteryLevel,screenACLine,ACLineInit;
	u8		ChargeStatus,chargeShow;
	u8		Rssi,flagIP_OK;			//�ź���,������Ϣ
	u8		mSignalType;
	u8		TmsUpDataFlag;
	u8		bH360Exist;		//360Ӳ�����ڱ��
	#ifdef HARD_WIFI
	s8		WifiStatus,wifiShow;
	s8		WifiRssi,wifiOldShow;
	u8		wificom,wificomShow;
	#endif
}DISPLAY_SCREEN_STATUS;
extern DISPLAY_SCREEN_STATUS OldScreen;

//==============�⺯���Ľ�����============================
extern char *API_eStrstr(char* src1, const char* src2);


typedef struct 
{
	u32		Way;		//���뷨,IME_TYPE(����֮һ)
	u32		Limit;		//���Ʋ�Ҫ���뷨�л�,IME_TYPE(��ѡ)
	u16		Min,Max;	//��С������뷶Χ
	char*	pTitle;		//��ʾ����
	char*	pFrontText;	//��ʾ��Ϣ��ָ��
	char*	pAfterText;	//���һ����ʾ��Ϣ
	//char*	pVoice;		//��������
	int		timeOutMs;	//��ʱ����
	//u8 FcChar;	//�ʺ�����ʱ�ķָ��ַ�	2006/09/25 zhou  added
	//u8 SanMag;	//ɨ��ſ�����2006/11/08 zhou added
	//u8 ScanInput;	//ˢ������20080629 added
}EDIT_DATA;

extern int APP_Edit(EDIT_DATA *pEdit,char* pOutStr);
extern int APP_InputNum(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen);
extern int APP_InputAbc(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinlen,int InputMaxlen);
extern int APP_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey);

//========================================================================================
enum UART_INDEX
{                           //�豸      KN-MODEM        KS8210-B        KS3660-B        KS3660-E
    UART_UNKNOW     	= 0,    //δ֪      ��              ��              ��              ��
    UART_1 			= 1,	//����1     ����̨(RJ45),	����̨(Usb)		����̨(Usb)		����̨(MiniUsb)
    UART_2 			= 2,	//����2     ��չ��(RJ11),	ɨ��ͷ(�ڲ�)	��				��
    UART_3 			= 3,	//����3     ��(Phone)		��				��				��
    UART_4 			= 4,	//����4     ��(Modem)	  	��				��				��
	UART_MAX		= 4
};
//====================================================================================
enum FILE_FLAG
{
	F_RDONLY	=00000000,		//!< ֻ��
	F_WRONLY	=00000001,		//!< ֻд
	F_RDWR		=00000002,		//!< ��д
	F_CREAT	=00000100,		//!< �Զ�����
	F_APPEND	=00002000,		//!< ׷�ӵ�β��
	F_CRNEW	=00000200,		//!< ɾ����ǰ�������µ�
};
/**
 * �ļ�seekģʽ
 */
enum FILE_SEEK
{
	F_SEEK_SET	=00000001,		//!< �ļ���ͷ
	F_SEEK_CUR	=00000002,		//!< ��ǰλ��
	F_SEEK_END	=00000004		//!< �ļ���β
};

/**
 * ���ļ��������ļ����������0�ɹ�
 *
 * @param filename 	�ļ�����·��Ϊ��ǰӦ��·��
 * @param flags 	�򿪷�ʽ,�ο�{@link FILE_FLAG}
 * @return 			[>0]�ļ������[<=0]����
 */
extern int 	API_fopen(const char * filename, int flags);
/**
 * �ر��ļ�
 *
 * @param fd 	{@link API_fopen}����Ч�ļ����
 * @return 		[>=0]�ļ�������ǰλ�� [<0]����
 */
extern int 	API_fclose(int fd);
/**
 * �ƶ���дλ��
 *
 * @param fd 		{@link API_fopen}����Ч�ļ����
 * @param offset 	ƫ��λ��
 * @param whence 	��ʼλ�ã��ο�{@link FILE_SEEK}����
 * @return 			�ɹ�������0��ʧ�ܷ���-1
 */
extern int 	API_fseek(int fd,int offset ,int whence);

/**
 * ���ļ�
 *
 * @param fd 		�ļ����
 * @param buf [out]	��ȡ������
 * @param count 	��ȡ��С
 * @return 			[>=0]����ʵ�ʶ��������ݴ�С [<0]����
 */
extern int 	API_fread(int fd,void * buf, u32 count);

/**
 * д���ļ�
 *
 * @param fd 	�ļ����
 * @param buf 	д�뻺����
 * @param count д���С
 * @return 		[>=0]����ʵ��д������ݴ�С [<0]����
 */
extern int 	API_fwrite(int fd,void * buf,u32 count);

//-------�����ļ���С-------------------------
extern int API_fSetSize(int fd,u32 size);
//-------��ȡ�ļ���С-------------------------
extern int API_fGetSize(int fd);

/**
 * ɾ���ļ�
 *
 * @param filename �ļ�����·��Ϊ��ǰӦ��·��
 * @return 			[0]�ɹ� [��0]ʧ��	
 */	
extern int	API_fremove(const char *filename);

extern int APP_FileSaveBuff(const char* pfilePath,u32 offset,void* pBuff,u32 Inlen);
extern int APP_FileReadBuff(const char* pfilePath,u32 offset,void* pBuff,u32 buffSize);


extern void SetSysDateTime(char *pInDateTime);

extern int	APP_Uart_PackSend(int Channel,u8* pSendBuf,u32 sendLen);
extern u8*	APP_Uart_PackRecv(int Channel,u8* pRecvBuf,u32 *recvLen);


#endif
