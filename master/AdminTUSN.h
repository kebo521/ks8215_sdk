#ifndef PC_UART_LOAD_HARD_KEY
#define PC_UART_LOAD_HARD_KEY


enum TYPE_TERM_HARD_INFO
{
	TYPE_TERM_HARD_LIFE			=0x01,
	TYPE_TERM_HARD_SN				=0x02,
	TYPE_TERM_HARD_TMK			=0x04,
	TYPE_TERM_HARD_ALL			=0x07,
};


typedef struct
{
	char 	Head[4];//KSPT 头标记
	u8		WifiOpen; 		//Wifi开关
	u8		volume;			//音量大小
	u8		language;		//语言
	u8		DebugMode;		//调试开关
	char 	NoUes[36-8-4];
	//-------------------------------
	char	MastVer[12];	//主控版本，SDK 版本 --
	//---------------------------------
	char 	AppExist[4];	//"OK" 存在
	u32 	AppAdder;
	char	AppTag[16];
	char 	AppVer[16];
	char 	AppName[20];
	char 	AppDateTime[20];

	char 	ParExist[4];	//"OK" 存在
	u32 	ParAdder;
	char 	ParVer[16];
	//---------------------
	
	u16		LightSleepTimeS;	//浅休眠时间
	u16		DeepSleepTimeS;		//深度休眠时间
	//-------------------------------
	u16		TmsPost;		//Tms访问端口
	char 	TmsAddre[35];	//Tms访问地址
	u8		TmsSSL;			//Tms访问方式
	u16		TmsPackMax;		//Tms下载接收数据最大量
	//---------------------
	char	sEnd[4];//END 尾标记
}DfTermPar;

//===============================================================================
typedef struct
{
	DfTermPar		tTerm;
}DfAdminTermPar;

extern DfTermPar tAdminTermPar;


extern int APP_GetHardMsg(u8 type,void *pOut,int OutSize);
extern int APP_SetHardMsg(u8 type,void *pIn,int InSize);
extern int APP_GetHardSm4Mac(u8* pInData,u16 InLen,u8 *pOutMac);

u32 Crc32Cal(u8 *buff, int len);

extern int APP_GetLifeCycle(void);
extern int Menu_TermSnProsee(char* title);


#endif /* PC_UART_LOAD_HARD_KEY */

