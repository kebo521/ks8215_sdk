#ifndef _SZZT_TMS_
#define _SZZT_TMS_

typedef enum{
	COM_NET, /*����ͨ��*/
	COM_UART, /*����ͨ��*/
}COM_TYPE;

extern int InstallAPP(const char* pKspPath,ST_APP_INFO* pAppInfo);

#endif
