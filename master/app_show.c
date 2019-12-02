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
	APP_ShowMsg(pTitle,"测试项1234",2000);
	return 0;
}


int APP_NineDirecTest(char *pTitle)
{
	API_GUI_CreateWindow(pTitle,NULL,NULL,API_FillShowBack);
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE,"左上");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_TOP,"中上");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_TOP,"右上");

	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_CENTER,"左中");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER|TEXT_EXSTYLE_BORDER,"中中");	//
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_CENTER,"右中");

	
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_BOTTOM,"左下");
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_BOTTOM,"中下");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,"右下");
	
	API_GUI_Show();
	APP_WaitUiEvent(5000);
	return 0;
}


int APP_QianMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"九方位显示 ",			APP_NineDirecTest},
		{"二维码测试",			APP_QrCodeTest}
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
		{"显示屏测试",		APP_AutoTest},
		{"按键测试",		APP_AutoTest},
		{"SIM卡测试",		APP_AutoTest},
		{"扫码头测试",		APP_AutoTest},
		{"播放语音测试",	APP_AutoTest},
		{"网络测试",		APP_AutoTest},
		{"电池测试",		APP_AutoTest},
		{"NFC卡测试",		APP_AutoTest},
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
		APP_ShowMsg(pTitle,"读信息错误",3000);
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
		APP_ShowMsg(pTitle,"无应用信息",3000);
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
	APP_HitMsg("弹窗3S,暂停2s",3000);
	APP_ShowSta(pTitle,"开始计时...");
	
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
		{"单项测试",			APP_HardTestMenu},
		//{"自动测试",			APP_AutoTest},
		//{"测试结果",			APP_AutoTest},
		//{"老化测试",			APP_AutoTest},
		{"显示应用列表",		APP_AppListShow},
		{"九方位显示 ",			APP_NineDirecTest},
		{"嵌套菜单",			APP_QianTest},
		{"弹窗测试",			APP_AppHitShow},
		{"二维码测试",			APP_QrCodeTest},
		{"设置语言",			APP_SetLanguage},
		
	//	"单项测试",				NULL,
	//	"自动测试",				NULL,
	//	"测试结果",				NULL,
	//	"老化测试",				NULL,
	//	"拨打电话测试",			NULL,
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
	APP_ShowSta(pTitle,"应用安装中");
	sleep(1);
	APP_ShowSta(pTitle,"应用安装中...");
	if(0==InstallAPP("app.ksp",&tAppInfo))
	{
		OsSaveAppInfo(&tAppInfo);
		APP_ShowMsg(pTitle,"安装中成功",3000);
	}
	return 0;
}


int AppSwitchFun(char* pTitle,int Index)
{
	int retnum;
	ST_APP_INFO AppInfo[6];
	char *ArgvPar[]={"app","test",(char*)0};
	APP_ShowMsg(pTitle,"应用信息",3000);
	retnum=OsGetAppInfo(AppInfo,6);
	if(retnum <= Index)
	{
		APP_ShowMsg(pTitle,"读信息错误",3000);
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
		APP_ShowMsg(pTitle,"无应用信息",3000);
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
		{"时间设置",			APP_EDIT_SetDateTime},
		#ifdef HARD_WIFI
		{"WIFI设置",			APP_WIFI_SetPar},
		#endif
		{"终端序号",			Menu_TermSnProsee},
		//"省电管理",			APP_SetSleepTimeS,
		//{"管理功能",			APP_AdminMenu},
	//	{"检查更新",			APP_TestUpSet},
	//	{"固件信息",			APP_HardVesion},
		{"语言设置",			APP_SetLanguage},
		//{"软件信息",			APP_SysVersion},
		{"应用安装",			APP_InstallAPP},
		{"显示应用列表",		APP_AppListShow},
		{"切换应用",			APP_AppListSwitch},
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}



