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
	char 	Head[4];//KSPT ͷ���
	u8		WifiOpen; 		//Wifi����
	u8		volume;			//������С
	u8		language;		//����
	u8		DebugMode;		//���Կ���
	char 	NoUes[36-8-4];
	//-------------------------------
	char	MastVer[12];	//���ذ汾��SDK �汾 --
	//---------------------------------
	char 	AppExist[4];	//"OK" ����
	u32 	AppAdder;
	char	AppTag[16];
	char 	AppVer[16];
	char 	AppName[20];
	char 	AppDateTime[20];

	char 	ParExist[4];	//"OK" ����
	u32 	ParAdder;
	char 	ParVer[16];
	//---------------------
	
	u16		LightSleepTimeS;	//ǳ����ʱ��
	u16		DeepSleepTimeS;		//�������ʱ��
	//-------------------------------
	u16		TmsPost;		//Tms���ʶ˿�
	char 	TmsAddre[35];	//Tms���ʵ�ַ
	u8		TmsSSL;			//Tms���ʷ�ʽ
	u16		TmsPackMax;		//Tms���ؽ������������
	//---------------------
	char	sEnd[4];//END β���
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

