#ifndef _APP_SDK_
#define _APP_SDK_

#define		OPER_OK				0
	
#define	 	OPER_RET			-1
#define	 	OPER_QUIT			-2
#define	 	OPER_TIMEOUT		-3
#define    	OPER_RDMagERR     -4 		//读卡错
#define    	OPER_CRCERR     	-5 		//校验失败
#define		OPER_ERR			-6		//操作失败
#define 	OPER_SYSTEM_ERROR	-7		//操作失败
#define 	OPER_TRANS_OVER	-8	    //返回数据正确，显示失败msg
#define		OPER_OFFLINE		-11		//下级
#define		OPER_LOW_VOLTAGE	-15		//电压过低
#define		OPER_HARD_Err		-16		//硬件错误
#define		OPER_SEND_ERR		-1000	//发送数据失败
#define		OPER_RECV_ERR		-2000	//发送数据失败


#define		OPER_NO_CHECK		15		//无签名数据
#define		OPER_NoEND 			6		//成功，但未结束	
#define		OPER_NoHEAD  		5		//未找到头部
#define		OPER_HARD			4		//手工输入
#define		OPER_NEW			3		//进入新流程
#define		OPER_PAY			1		//确认支付

#define		SOCKET_UN_APN			-101		//未打开APN
#define		SOCKET_UN_IP			-102		//未连接IP
#define		SOCKET_UN				-200		//未连接IP

#define	SIZE_NORMAL		24


typedef struct
{
	u16		ReDisplayScreen;
	u16		StatusMcc,StatusMnc;
	u16		Hour,Minute;
	u16		PDPStatus;
	u16		SleepTimeS;
	u8		SleepEn,SaveSleepEn;		//休眠控制
	u8		SleepState;
	u8		SleepDeep;		//深度休眠
	u8		screenRefState;
	u8		batteryLevel,screenACLine,ACLineInit;
	u8		ChargeStatus,chargeShow;
	u8		Rssi,flagIP_OK;			//信号量,连接信息
	u8		mSignalType;
	u8		TmsUpDataFlag;
	u8		bH360Exist;		//360硬件存在标记
	#ifdef HARD_WIFI
	s8		WifiStatus,wifiShow;
	s8		WifiRssi,wifiOldShow;
	u8		wificom,wificomShow;
	#endif
}DISPLAY_SCREEN_STATUS;
extern DISPLAY_SCREEN_STATUS OldScreen;

//==============库函数改进函数============================
extern char *API_eStrstr(char* src1, const char* src2);


typedef struct 
{
	u32		Way;		//输入法,IME_TYPE(其中之一)
	u32		Limit;		//控制不要输入法切换,IME_TYPE(多选)
	u16		Min,Max;	//最小最大输入范围
	char*	pTitle;		//显示标题
	char*	pFrontText;	//提示信息的指针
	char*	pAfterText;	//最后一行提示信息
	//char*	pVoice;		//播放语音
	int		timeOutMs;	//超时控制
	//u8 FcChar;	//帐号输入时的分隔字符	2006/09/25 zhou  added
	//u8 SanMag;	//扫描磁卡控制2006/11/08 zhou added
	//u8 ScanInput;	//刷卡输入20080629 added
}EDIT_DATA;

extern int APP_Edit(EDIT_DATA *pEdit,char* pOutStr);
extern int APP_InputNum(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinLen,int InputMaxlen);
extern int APP_InputAbc(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pInputDef,int InputMinlen,int InputMaxlen);
extern int APP_InputPin(char* pTitle,char* pFrontTextBuf,char* pAfterTextBuf,char* pkey);

//========================================================================================
enum UART_INDEX
{                           //设备      KN-MODEM        KS8210-B        KS3660-B        KS3660-E
    UART_UNKNOW     	= 0,    //未知      无              无              无              无
    UART_1 			= 1,	//串口1     控制台(RJ45),	控制台(Usb)		控制台(Usb)		控制台(MiniUsb)
    UART_2 			= 2,	//串口2     扩展口(RJ11),	扫描头(内部)	无				无
    UART_3 			= 3,	//串口3     无(Phone)		无				无				无
    UART_4 			= 4,	//串口4     无(Modem)	  	无				无				无
	UART_MAX		= 4
};
//====================================================================================
enum FILE_FLAG
{
	F_RDONLY	=00000000,		//!< 只读
	F_WRONLY	=00000001,		//!< 只写
	F_RDWR		=00000002,		//!< 读写
	F_CREAT	=00000100,		//!< 自动创建
	F_APPEND	=00002000,		//!< 追加到尾部
	F_CRNEW	=00000200,		//!< 删除当前，创建新的
};
/**
 * 文件seek模式
 */
enum FILE_SEEK
{
	F_SEEK_SET	=00000001,		//!< 文件开头
	F_SEEK_CUR	=00000002,		//!< 当前位置
	F_SEEK_END	=00000004		//!< 文件结尾
};

/**
 * 打开文件，返回文件句柄，大于0成功
 *
 * @param filename 	文件名，路径为当前应用路径
 * @param flags 	打开方式,参考{@link FILE_FLAG}
 * @return 			[>0]文件句柄　[<=0]错误
 */
extern int 	API_fopen(const char * filename, int flags);
/**
 * 关闭文件
 *
 * @param fd 	{@link API_fopen}打开有效文件句柄
 * @return 		[>=0]文件操作当前位置 [<0]错误
 */
extern int 	API_fclose(int fd);
/**
 * 移动读写位置
 *
 * @param fd 		{@link API_fopen}打开有效文件句柄
 * @param offset 	偏移位置
 * @param whence 	起始位置，参考{@link FILE_SEEK}定义
 * @return 			成功，返回0，失败返回-1
 */
extern int 	API_fseek(int fd,int offset ,int whence);

/**
 * 读文件
 *
 * @param fd 		文件句柄
 * @param buf [out]	读取缓冲区
 * @param count 	读取大小
 * @return 			[>=0]返回实际读出的数据大小 [<0]错误
 */
extern int 	API_fread(int fd,void * buf, u32 count);

/**
 * 写文文件
 *
 * @param fd 	文件句柄
 * @param buf 	写入缓冲区
 * @param count 写入大小
 * @return 		[>=0]返回实际写入的数据大小 [<0]错误
 */
extern int 	API_fwrite(int fd,void * buf,u32 count);

//-------设置文件大小-------------------------
extern int API_fSetSize(int fd,u32 size);
//-------获取文件大小-------------------------
extern int API_fGetSize(int fd);

/**
 * 删除文件
 *
 * @param filename 文件名，路径为当前应用路径
 * @return 			[0]成功 [非0]失败	
 */	
extern int	API_fremove(const char *filename);

extern int APP_FileSaveBuff(const char* pfilePath,u32 offset,void* pBuff,u32 Inlen);
extern int APP_FileReadBuff(const char* pfilePath,u32 offset,void* pBuff,u32 buffSize);


extern void SetSysDateTime(char *pInDateTime);

extern int	APP_Uart_PackSend(int Channel,u8* pSendBuf,u32 sendLen);
extern u8*	APP_Uart_PackRecv(int Channel,u8* pRecvBuf,u32 *recvLen);


#endif
