
#ifndef _SYS_SDK_
#define _SYS_SDK_

#include "sdk_port.h"
#include "sdk_msr.h"
#include "sdk_print.h"
#include "sdk_icc.h"
#include "app_net.h"
//=================ͨ�÷�����==================================
#define RET_OK						0 //�ɹ�
#define ERR_INVALID_HANDLE	-1000 //�Ƿ����
#define ERR_TIME_OUT			-1001 //��ʱ
#define ERR_APP_NOT_EXIST		-1002 //Ӧ�ò�����
#define ERR_INVALID_PARAM		-1003 //�Ƿ�����
#define ERR_DEV_NOT_EXIST		-1004 //�豸������
#define ERR_DEV_BUSY			-1005 //�豸��ռ��
#define ERR_DEV_NOT_OPEN		-1006 //�豸û�д�
#define ERR_ACCESS_DENY		-1007 //��Ȩ����
#define ERR_FONT_NOT_EXIST	-1008 //û��ָ��������
#define ERR_FILE_FORMAT		-1009 //�ļ���ʽ����
#define ERR_USER_CANCEL		-1010 //�û�ȡ��
#define ERR_NO_PORT			-1011 //��ͨ�ſڿ���
#define ERR_NOT_CONNECT		-1012 //δ����
#define ERR_MEM_FAULT			-1013 //�ڴ����
#define ERR_SYS_BAD			-1014 //ϵͳ����������
#define ERR_SYS_NOT_SUPPORT	-1015 //ϵͳû���ṩ�ù���
#define ERR_STR_LEN			-1016 //�ַ���̫��
#define ERR_TOO_MANY_HANDLE	-1017 //�������
#define ERR_APP_MODE			-1018 //ģʽ����
#define ERR_FILE_NOT_EXIST	-1019 //�ļ�������
#define ERR_TS_DISABLE		-1020 //������δ��
#define ERR_FONT_CODE			-1021 //�ַ��������
#define ERR_VERSION_TOO_LOW	-1022 //�汾����
#define ERR_BATTERY_ABSENT	-1023 //��ز�����
#define ERR_BATTERY_VOLTAGE_TOO_LOW		-1024 //��ص�ѹ����

//==============��������ֵ�б�==================================
#define ERR_FILE_NOT_FOUND		-2201 //�ļ�û���ҵ�
#define ERR_VERIFY_SIGN_FAIL		-2204 //��֤ǩ��ʧ��
#define ERR_NO_SPACE				-2205 //ϵͳ�ռ䲻��
#define ERR_NEED_ADMIN			-2207 //��Ҫ����Ȩ��
#define ERR_PUK_NOT_EXIST			-2208 //PUK ������
#define ERR_OS_VERSION_TOO_LOW	-2209 //ϵͳ�汾����
//#define ERR_INVALID_PARAM			-1003 //�Ƿ�����
//#define ERR_DEV_NOT_EXIST			-1004 //�豸������
//#define ERR_DEV_BUSY				-1005 //�豸����ʹ����
//#define ERR_ACCESS_DENY			-1007 //�޷���Ȩ��
//#define ERR_SYS_NOT_SUPPORT		-1015 //ϵͳ��֧��
//#define ERR_FILE_NOT_EXIST		-1019 //�ļ�������

//=============��װ�ļ����Ͷ���============================
#define ILE_TYPE_APP				1 //Ӧ�ð�
#define FILE_TYPE_APP_PARAM		2 //Ӧ�������ļ�
#define FILE_TYPE_SYS_LIB			3 //ϵͳ��̬���ļ�
#define FILE_TYPE_PUB_KEY			4 //�û���Կ�ļ�
#define FILE_TYPE_AUP				5 //Ӧ��������

typedef enum{
	LOG_DEBUG, /*��ʾ������Ϣ*/
	LOG_INFO, /*��ʾ��ʾ��Ϣ*/
	LOG_WARN, /*��ʾ������Ϣ*/
	LOG_ERROR, /*��ʾ������Ϣ*/
} LOG_T;

#define CURR_LOG_T						LOG_INFO			
extern void OsLogSetTag(const char *Tag);
extern int OsLog(LOG_T Prio,const char *fmt,...);
#define LogSetTag						OsLogSetTag		
#define LOG								OsLog
//#define TRACE(...)						OsLog(LOG_INFO,__VA_ARGS__)	
extern void OsLogHex(char* msg,void* pBuff,int Len);
#define LOG_HEX(logT,msg,pBuff,Len)		OsLogHex(msg,pBuff,Len)


typedef struct{
	int Year; /*��1970�C 2037*/
	int Month; /*��1 �C12*/
	int Day; /*��1 �C31*/
	int Hour; /*ʱ0 �C 23*/
	int Minute; /*��0 �C59*/
	int Second; /*��0 �C59*/
	int DayOfWeek; /*��1�C��7������ȡʱ����Ч��*/
} ST_TIME;

typedef struct{
	unsigned long Start;
	unsigned long Stop;
	unsigned long TimeLeft;
} ST_TIMER;

extern char *eStrstr(char* src1, const char* src2);

extern unsigned long OsGetTickCount(void);

extern int OsSetTime(const ST_TIME *Time);
extern void OsGetTime(ST_TIME *Time);
extern int OsTimerSet(ST_TIMER *Timer,unsigned long Ms);
extern unsigned long OsTimerCheck(ST_TIMER *Timer);
extern void OsSleep(unsigned int Ms);





typedef void (*RUNAPP_CB)(char *appid, char *str, void *data);	//(char *appid, char *str, void *data)


extern int OsExit(int recode);

extern int OsGetAppInfo(ST_APP_INFO AppInfo[],int InfoCnt);
extern int OsGetOptInfo(ST_OPT_INFO OptInfo[],int InfoCnt);
extern int OsRunApp(char *AppId, char **Argv, void *Data, RUNAPP_CB CbOut,RUNAPP_CB CbErr);
extern int OsGetAppExitCode(void);


#endif
