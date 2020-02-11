#ifndef _SZZT_TMS_
#define _SZZT_TMS_

typedef enum{
	COM_NET, /*网络通信*/
	COM_UART, /*串口通信*/
}COM_TYPE;

typedef struct
{
	char 		*pFileNo;
	u32 		*pOffset;
	u32 		*pReadMax;
	char 		*pRetCode;

	char		sTuSN[32];
	char		sModel[8];
	char		sType[2];
	char		sComType[6];
	char		sParVer[12];
}tData_TMS_Const;


typedef int (*funTmsPack)(tData_TMS_Const*,u8*); 
typedef void* (*funTmsParse)(u8* ,u32*); 


extern int APP_TmsProcess(COM_TYPE type);
extern u32 APP_TMS_UpAPP(u16 Msg);

extern int InstallAPP(ST_APP_INFO* pAppInfo);

#endif
