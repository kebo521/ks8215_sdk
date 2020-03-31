/**
 * File:   fbshow.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  snap framebuffer to png file
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>


#include <time.h>

#include "comm_type.h"
#include "xui_comm.h"
#include "sys_sdk.h"
#include "main.h"

#include "AdminTUSN.h"

#include "szzt_tms.h"

#include "app_sdk.h"




int AppListItemFun(char* pTitle,int Index)
{
	int retnum,offset;
	ST_APP_INFO AppInfo[6];
	char sBuff[256];
	retnum=OsGetAppInfo(AppInfo,6);
	if(retnum <= Index)
	{
		APP_ShowMsg(pTitle,"����Ϣ����",3000);
		return 0;
	}
	offset = sprintf(sBuff,"ID:%s\n",AppInfo[Index].Id);
	offset += sprintf(sBuff+offset,"Bin:%s\n",AppInfo[Index].Bin);
	offset += sprintf(sBuff+offset,"Art:%s\n",AppInfo[Index].Artwork);
	offset += sprintf(sBuff+offset,"Des:%s\n",AppInfo[Index].Desc);
	offset += sprintf(sBuff+offset,"Ven:%s\n",AppInfo[Index].Vender);
	offset += sprintf(sBuff+offset,"Ver:%s\n",AppInfo[Index].Version);
	APP_ShowInfo(pTitle,sBuff,20*1000);
	return 0;
}


int APP_AppListShow(char *pTitle)
{
	int retnum,i;
	ST_APP_INFO AppInfo[6];
	char* pMenuText[6];
	retnum=OsGetAppInfo(AppInfo,6);
	if(retnum<=0)
	{
		APP_ShowMsg(pTitle,"��Ӧ����Ϣ",3000);
		return 0;
	}
	for(i=0;i<retnum;i++)
	{
		pMenuText[i]=AppInfo[i].Name;
	}
	return APP_CreateNewMenuByStr(pTitle,i,pMenuText,AppListItemFun,30*1000);
}


int APP_EDIT_SetDateTime(char* title)
{
	char str[10];
	u16	 MaxDay; 
	ST_TIME tTime;
	OsGetTime(&tTime);
	API_sprintf(str,"%04d%02d%02d",tTime.Year,tTime.Month,tTime.Day); 
    if(0 == APP_InputNum(title,"��������[������]:","[8λ]���ְ�������", str, 8,8))
	{
		tTime.Day  =API_atoi(str+6);
		str[6]='\0';
		tTime.Month=API_atoi(str+4);
		str[4]='\0';
		tTime.Year=API_atoi(str);
		//MercuryTrace("DateTime:[%s] [%02d:%02d:%02d]",str,dtime.wHour,dtime.wMinute,dtime.wSecond);
		MaxDay = 30+(((tTime.Month&1)^(tTime.Month&8)>>3)!=0)-(tTime.Month==2)*2+((tTime.Month==2) \
		&&((((tTime.Year&0x03)==0)&&((tTime.Year%100)!=0))||((tTime.Year%400)==0)));
		if( (tTime.Year<1900 || tTime.Year>2100) || (tTime.Month<1 || tTime.Month>12) || (tTime.Day<1 || tTime.Day>MaxDay))
		{
			APP_ShowMsg(title,"���ڸ�ʽ����",3000);
			return -4;
		}
		OsSetTime(&tTime);
		API_sprintf(str,"%02d%02d",tTime.Hour,tTime.Minute); 
		if(0 == APP_InputNum(title,"����ʱ��[ʱ��]:","[4λ]���ְ�������",str,4,4))
		{
			tTime.Minute=API_atoi(str+2);
			str[2]='\0';
			tTime.Hour=API_atoi(str);
			if(( tTime.Hour>23) || ( tTime.Minute>59))
			{
				APP_ShowMsg(title,"ʱ���ʽ����",3000);
				return -4;
			}
			OsSetTime(&tTime);
			APP_ShowMsg(title,"�������",3000);
		}
		return 0;
    }
    return -1;
}


int APP_WIFI_SetPar(char* title)
{

	return 0;
}

int APP_SetSleepTimeS(char* title)
{
	return 0;
}

int APP_AdminMenu(char* title)
{
	return 0;
}
int APP_TestUpSet(char* title)
{
	return 0;
}
int APP_HardVesion(char* title)
{
	return 0;
}
int APP_SysVersion(char* title)
{
	return 0;
}

extern int OsSaveAppInfo(ST_APP_INFO* pAppInfo);

int APP_UInstallAPP(char *pTitle)
{
	ST_APP_INFO tAppInfo;
	APP_ShowSta(pTitle,"������������...");
	if(!APP_TmsProcess(COM_UART))
	{
		APP_ShowMsg(pTitle,"����ʧ��",3000);
		return 1;
	}
	APP_ShowSta(pTitle,"Ӧ�ð�װ��");
	if(0==InstallAPP(&tAppInfo))
	{
		OsSaveAppInfo(&tAppInfo);
		APP_ShowMsg(pTitle,"��װ�гɹ�",3000);
	}
	return 0;
}

int APP_NInstallAPP(char *pTitle)
{
	ST_APP_INFO tAppInfo;
	APP_ShowSta(pTitle,"�������������...");
	if(!APP_TmsProcess(COM_NET))
	{
		APP_ShowMsg(pTitle,"����ʧ��",3000);
		return 1;
	}
	APP_ShowSta(pTitle,"Ӧ�ð�װ��");
	if(0==InstallAPP(&tAppInfo))
	{
		OsSaveAppInfo(&tAppInfo);
		APP_ShowMsg(pTitle,"��װ�гɹ�",3000);
	}
	return 0;
}

int AppSwitchFun(char* pTitle,int Index)
{
	int retnum;
	ST_APP_INFO AppInfo[6];
	char *ArgvPar[]={"app","test",(char*)0};
	APP_ShowMsg(pTitle,"Ӧ����Ϣ",3000);
	retnum=OsGetAppInfo(AppInfo,6);
	if(retnum <= Index)
	{
		APP_ShowMsg(pTitle,"����Ϣ����",3000);
		return 0;
	}
	APP_ShowSta(pTitle,AppInfo[Index].Id);
	LOG(LOG_INFO,"AppSwitchFun\r\n");
	OsRunApp(AppInfo[Index].Id,ArgvPar,NULL,NULL,NULL);
	return 0;
}

int APP_AppListSwitch(char *pTitle)
{
	int retnum,i;
	ST_APP_INFO AppInfo[6];
	char* pMenuText[6];
	retnum=OsGetAppInfo(AppInfo,6);
	if(retnum<=0)
	{
		APP_ShowMsg(pTitle,"��Ӧ����Ϣ",3000);
		return 0;
	}
	for(i=0;i<retnum;i++)
	{
		pMenuText[i]=AppInfo[i].Name;
	}
	return APP_CreateNewMenuByStr(pTitle,i,pMenuText,AppSwitchFun,30*1000);
}

extern tData_Set* OsSysGet_TermSet(void);
extern void OsSysMsg_sync(void);
int API_SetLanguage(unsigned int language)
{
	tData_Set* pSet;
	pSet = OsSysGet_TermSet();
	if(pSet->language == language)
		return 1;
	API_InitSysLanguage(language);
	pSet->language=language;
	OsSysMsg_sync();	//�����������
	return 0;
}

int APP_SetLanguage(char* pTitle)
{
	char* pTraceMenu[]={"English","����","�ձ��Z"};
	tData_Set* pSet;
	u32 Event;
	pSet = OsSysGet_TermSet();
	APP_GUI_Menu(pTitle,0,sizeof(pTraceMenu)/sizeof(pTraceMenu[0]),pSet->language,pTraceMenu);//tAdminTermPar.language
	Event=API_WaitEvent(30*1000,EVENT_KEY,EVENT_NONE);
	if(Event&EVENT_KEY)
	{
		if((Event&0xff)==K_1)
		{
			APP_ShowSta(pTitle,"SET English");
			API_SetLanguage(0);
		}
		else if((Event&0xff)==K_2)
		{
			APP_ShowSta(pTitle,"����Ϊ����");
			API_SetLanguage(1);
		}
		else if((Event&0xff)==K_3)
		{
			APP_ShowSta(pTitle,"����Ϊ�ձ��Z");
			API_SetLanguage(2);
		}
		else return -1;
		//----------���ض�Ӧ����---------------------
		APP_WaitUiEvent(2000);
	}
	return 0;
}


int APP_MasterMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"�ն���Ź���",		Menu_TermSnProsee},
		{"ʱ������",			APP_EDIT_SetDateTime},
		#ifdef HARD_WIFI
		{"WIFI����",			APP_WIFI_SetPar},
		#endif
		//"ʡ�����",			APP_SetSleepTimeS,
		//{"������",			APP_AdminMenu},
	//	{"������",			APP_TestUpSet},
	//	{"�̼���Ϣ",			APP_HardVesion},
		{"��������",			APP_SetLanguage},
		//{"�����Ϣ",			APP_SysVersion},
		{"���ڰ�װӦ��",		APP_UInstallAPP},
		{"���簲װӦ��",		APP_NInstallAPP},
		{"��ʾӦ���б�",		APP_AppListShow},
		{"�л�Ӧ��",			APP_AppListSwitch},
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}



