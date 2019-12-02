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


#include "szzt_tms.h"



int APP_QrCodeTest(char *pTitle)
{
	APP_ShowQrCode(pTitle,"12345678abcduehsfiufwfowei3482y348239342",RGB_CURR(0,0,0xff));
	return APP_WaitUiEvent(5000);
}



int APP_AutoTest(char *pTitle)
{
	APP_ShowMsg(pTitle,"������1234",2000);
	return 0;
}


int APP_NineDirecTest(char *pTitle)
{
	API_GUI_CreateWindow(pTitle,NULL,NULL,API_FillShowBack);
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE,"����");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_TOP,"����");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_TOP,"����");

	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_CENTER,"����");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER|TEXT_EXSTYLE_BORDER,"����");	//
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_CENTER,"����");

	
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_BOTTOM,"����");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_BOTTOM,"����");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,"����");
	
	API_GUI_Show();
	APP_WaitUiEvent(5000);
	return 0;
}


int APP_QianMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"�ŷ�λ��ʾ ",			APP_NineDirecTest},
		{"��ά�����",			APP_QrCodeTest}
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}



int APP_QianTest(char *pTitle)
{
	XuiWindow *babyWindow,*pCurrWindow;
	pCurrWindow = API_GUI_GetCurrWindow();
	babyWindow = XuiCreateCanvas(pCurrWindow,24,60,192,296-130);
	API_GUI_LoadWindow(babyWindow);

	APP_QianMeun(pTitle);
	APP_ShowProsseMenu();

	XuiShowWindow(babyWindow,0,1);
	sleep(2);
	XuiShowWindow(babyWindow,1,1);
	sleep(2);
	
	XuiDestroyWindow(babyWindow);
	sleep(2);
	API_GUI_LoadWindow(pCurrWindow);
	return 0;
}



int APP_HardTestMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"��ʾ������",		APP_AutoTest},
		{"��������",		APP_AutoTest},
		{"SIM������",		APP_AutoTest},
		{"ɨ��ͷ����",		APP_AutoTest},
		{"������������",	APP_AutoTest},
		{"�������",		APP_AutoTest},
		{"��ز���",		APP_AutoTest},
		{"NFC������",		APP_AutoTest},
	};
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	//APP_AddCurrentMenuOtherFun(MENU_OUT_FUN,APP_SaveTestResult,NULL);
	return 0;
}

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

int APP_AppHitShow(char *pTitle)
{
	APP_HitMsg("����3S,��ͣ2s",3000);
	APP_ShowSta(pTitle,"��ʼ��ʱ...");
	
	gShowTimeS_SetInit(TEXT_24|TEXT_ALIGN_LEFT|TEXT_VALIGN_BOTTOM,2,10);
	while(1)
	{
		OsSleep(1000);
		if(gShowTimeS_GetOut())
			break;
	}
	UI_SetSysEnColor(RGB_CURR(0xff,0,0),RGB_CURR(0,0xff,0));
	gShowTimeS_SetInit(TEXT_12|TEXT_ALIGN_CENTER|TEXT_VALIGN_BOTTOM,2,10);
	while(1)
	{
		OsSleep(1000);
		if(gShowTimeS_GetOut())
			break;
	}

	UI_SetSysEnColor(RGB_CURR(0,0,0xff),RGB_CURR(0xff,0xff,0));
	gShowTimeS_SetInit(TEXT_16|TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,2,10);
	while(1)
	{
		OsSleep(1000);
		if(gShowTimeS_GetOut())
			break;
	}

	gShowTimeS_SetInit(TEXT_24|TEXT_ALIGN_LEFT|TEXT_VALIGN_CENTER,2,10);
	while(1)
	{
		OsSleep(1000);
		if(gShowTimeS_GetOut())
			break;
	}
	return 0;
}


int APP_FactoryMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"�������",			APP_HardTestMenu},
		//{"�Զ�����",			APP_AutoTest},
		//{"���Խ��",			APP_AutoTest},
		//{"�ϻ�����",			APP_AutoTest},
		{"��ʾӦ���б�",		APP_AppListShow},
		{"�ŷ�λ��ʾ ",			APP_NineDirecTest},
		{"Ƕ�ײ˵�",			APP_QianTest},
		{"��������",			APP_AppHitShow},
		{"��ά�����",			APP_QrCodeTest},
		{"��������",			APP_SetLanguage},
		
	//	"�������",				NULL,
	//	"�Զ�����",				NULL,
	//	"���Խ��",				NULL,
	//	"�ϻ�����",				NULL,
	//	"����绰����",			NULL,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}



int APP_EDIT_SetDateTime(char* title)
{
	ST_TIME tTime;
	OsGetTime(&tTime);
	return 0;
}

int APP_WIFI_SetPar(char* title)
{

	return 0;
}

int Menu_TermSnProsee(char* title)
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

int APP_InstallAPP(char *pTitle)
{
	ST_APP_INFO tAppInfo;
	APP_ShowSta(pTitle,"Ӧ�ð�װ��");
	sleep(1);
	APP_ShowSta(pTitle,"Ӧ�ð�װ��...");
	if(0==InstallAPP("app.ksp",&tAppInfo))
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


int APP_MasterMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"ʱ������",			APP_EDIT_SetDateTime},
		#ifdef HARD_WIFI
		{"WIFI����",			APP_WIFI_SetPar},
		#endif
		{"�ն����",			Menu_TermSnProsee},
		//"ʡ�����",			APP_SetSleepTimeS,
		//{"������",			APP_AdminMenu},
	//	{"������",			APP_TestUpSet},
	//	{"�̼���Ϣ",			APP_HardVesion},
		{"��������",			APP_SetLanguage},
		//{"�����Ϣ",			APP_SysVersion},
		{"Ӧ�ð�װ",			APP_InstallAPP},
		{"��ʾӦ���б�",		APP_AppListShow},
		{"�л�Ӧ��",			APP_AppListSwitch},
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}



