
#ifndef _SYS_SDK_
#define _SYS_SDK_

#include "sdk_port.h"
#include "sdk_msr.h"
#include "sdk_print.h"
#include "sdk_icc.h"
#include "app_net.h"
//=================通用返回码==================================
#define RET_OK						0 //成功
#define ERR_INVALID_HANDLE	-1000 //非法句柄
#define ERR_TIME_OUT			-1001 //超时
#define ERR_APP_NOT_EXIST		-1002 //应用不存在
#define ERR_INVALID_PARAM		-1003 //非法参数
#define ERR_DEV_NOT_EXIST		-1004 //设备不存在
#define ERR_DEV_BUSY			-1005 //设备被占用
#define ERR_DEV_NOT_OPEN		-1006 //设备没有打开
#define ERR_ACCESS_DENY		-1007 //无权访问
#define ERR_FONT_NOT_EXIST	-1008 //没有指定的字体
#define ERR_FILE_FORMAT		-1009 //文件格式错误
#define ERR_USER_CANCEL		-1010 //用户取消
#define ERR_NO_PORT			-1011 //无通信口可用
#define ERR_NOT_CONNECT		-1012 //未连接
#define ERR_MEM_FAULT			-1013 //内存错误
#define ERR_SYS_BAD			-1014 //系统配置有问题
#define ERR_SYS_NOT_SUPPORT	-1015 //系统没有提供该功能
#define ERR_STR_LEN			-1016 //字符串太长
#define ERR_TOO_MANY_HANDLE	-1017 //句柄过多
#define ERR_APP_MODE			-1018 //模式出错
#define ERR_FILE_NOT_EXIST	-1019 //文件不存在
#define ERR_TS_DISABLE		-1020 //触摸屏未打开
#define ERR_FONT_CODE			-1021 //字符编码错误
#define ERR_VERSION_TOO_LOW	-1022 //版本过低
#define ERR_BATTERY_ABSENT	-1023 //电池不存在
#define ERR_BATTERY_VOLTAGE_TOO_LOW		-1024 //电池电压过低

//==============函数返回值列表==================================
#define ERR_FILE_NOT_FOUND		-2201 //文件没有找到
#define ERR_VERIFY_SIGN_FAIL		-2204 //验证签名失败
#define ERR_NO_SPACE				-2205 //系统空间不够
#define ERR_NEED_ADMIN			-2207 //需要更高权限
#define ERR_PUK_NOT_EXIST			-2208 //PUK 不存在
#define ERR_OS_VERSION_TOO_LOW	-2209 //系统版本过低
//#define ERR_INVALID_PARAM			-1003 //非法参数
//#define ERR_DEV_NOT_EXIST			-1004 //设备不存在
//#define ERR_DEV_BUSY				-1005 //设备正在使用中
//#define ERR_ACCESS_DENY			-1007 //无访问权限
//#define ERR_SYS_NOT_SUPPORT		-1015 //系统不支持
//#define ERR_FILE_NOT_EXIST		-1019 //文件不存在

//=============安装文件类型定义============================
#define ILE_TYPE_APP				1 //应用包
#define FILE_TYPE_APP_PARAM		2 //应用数据文件
#define FILE_TYPE_SYS_LIB			3 //系统动态库文件
#define FILE_TYPE_PUB_KEY			4 //用户公钥文件
#define FILE_TYPE_AUP				5 //应用升级包

typedef enum{
	LOG_DEBUG, /*显示调试信息*/
	LOG_INFO, /*显示提示信息*/
	LOG_WARN, /*显示警告信息*/
	LOG_ERROR, /*显示错误信息*/
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
	int Year; /*年1970– 2037*/
	int Month; /*月1 –12*/
	int Day; /*日1 –31*/
	int Hour; /*时0 – 23*/
	int Minute; /*分0 –59*/
	int Second; /*秒0 –59*/
	int DayOfWeek; /*周1–周7（仅读取时间有效）*/
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
