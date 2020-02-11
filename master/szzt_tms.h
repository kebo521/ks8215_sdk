#ifndef _SZZT_TMS_
#define _SZZT_TMS_

typedef enum{
	COM_NET, /*网络通信*/
	COM_UART, /*串口通信*/
}COM_TYPE;

extern int InstallAPP(const char* pKspPath,ST_APP_INFO* pAppInfo);

#endif
