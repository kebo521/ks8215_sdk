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
	babyWindow = XuiCreateCanvas(pCurrWindow,40,40,160,160);
	if(babyWindow==NULL)
	{
		LOG(LOG_ERROR,"XuiCreateCanvas Err\r\n");
		return -1;
	}
	API_GUI_LoadWindow(babyWindow);

	APP_QianMeun(pTitle);
	APP_ShowProsseMenu();

	XuiShowWindow(babyWindow,0,1);
	OsSleep(2000);
	XuiShowWindow(babyWindow,1,1);
	OsSleep(2000);
	
	XuiDestroyWindow(babyWindow);
	OsSleep(2000);
	API_GUI_LoadWindow(pCurrWindow);
	return 0;
}

int APP_UiBaseTest(char *pTitle)
{
	RECTL tRect;
	u16 x,y,w,h;
	xui_fb_GetScreenMsg(&tRect,NULL);
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB_CURR(127,127,127));

	x=30;
	y=30;
	fb_ui_point(tRect.left+x,tRect.top+y,RGB_CURR(255,0,0));
	x=40;
	fb_ui_point(tRect.left+x,tRect.top+y,RGB_CURR(0,255,0));
	x=50;
	fb_ui_point(tRect.left+x,tRect.top+y,RGB_CURR(0,0,255));
	
	x=0;
	w=tRect.width;
	
	y=60;
	fb_ui_hline(tRect.left+x,tRect.top+y,w,RGB_CURR(255,0,0));
	y=70;
	fb_ui_hline(tRect.left+x,tRect.top+y,w,RGB_CURR(0,255,0));
	y=80;
	fb_ui_hline(tRect.left+x,tRect.top+y,w,RGB_CURR(0,0,255));

	y=0;
	h=tRect.height;
	
	x=60;
	fb_ui_vline(tRect.left+x,tRect.top+y,h,RGB_CURR(255,0,0));
	x=70;
	fb_ui_vline(tRect.left+x,tRect.top+y,h,RGB_CURR(0,255,0));
	x=80;
	fb_ui_vline(tRect.left+x,tRect.top+y,h,RGB_CURR(0,0,255));


	w=tRect.width-1;
	h=tRect.height-1;
	fb_ui_point(tRect.left+w,tRect.top+h,RGB_CURR(255,0,0));
	x=0;
	y=0;
	fb_ui_line(tRect.left+x,tRect.top+y,tRect.left+w,tRect.top+h,RGB_CURR(255,255,0));

	w=0;
	h=tRect.height-1;
	fb_ui_point(tRect.left+w,tRect.top+h,RGB_CURR(255,0,0));
	x=tRect.width-1;
	y=0;
	fb_ui_line(tRect.left+x,tRect.top+y,tRect.left+w,tRect.top+h,RGB_CURR(0,255,255));


	w=150;
	h=tRect.height-1;
	fb_ui_point(tRect.left+w,tRect.top+h,RGB_CURR(255,0,0));
	x=150;
	y=0;
	fb_ui_line(tRect.left+x,tRect.top+y,tRect.left+w,tRect.top+h,RGB_CURR(0,127,127));

	w=tRect.width-1;
	h=150;
	fb_ui_point(tRect.left+w,tRect.top+h,RGB_CURR(255,0,0));
	x=0;
	y=150;
	fb_ui_line(tRect.left+x,tRect.top+y,tRect.left+w,tRect.top+h,RGB_CURR(0,0,127));

	x=tRect.width/2;
	y=tRect.height/2;
	fb_ui_circle(tRect.left+x,tRect.top+y,100,RGB_CURR(255,0,255));

	x=tRect.width/2-20;
	y=tRect.height-40;
	fb_ui_fill_rect(tRect.left+x,tRect.top+y,40,40,RGB_CURR(0,255,0));
	xui_fb_syn();
	return APP_WaitUiEvent(20*1000);

}

int APP_UiPullPush(char* title)
{
	RECTL tRect;
	A_RGB *pRGB;
	XuiWindow *pCurrWindow;
	pCurrWindow = API_GUI_GetCurrWindow();
	
	tRect.left = pCurrWindow->left+50;
	tRect.top= pCurrWindow->top+20;
	tRect.width= 180;
	tRect.height= 180;
	pRGB=(A_RGB *)malloc(tRect.height * tRect.width * sizeof(A_RGB));
	xui_fb_pull(&tRect,pRGB);
	APP_ShowSta("测试标题濉","内存覆盖");
	OsSleep(3000);
	xui_fb_push(&tRect,pRGB);
	free(pRGB);
	OsSleep(3000);
	return 0;
	//return APP_WaitUiEvent(3*1000);
}

int APP_TestShowBottom(char* title)
{
	int i;
	APP_ShowSta(title,"显示进度");
	for(i=0;i<=100;i++)
	{
		APP_ShowBottomProgress(i);
		OsSleep(1000);
	}
	return 0;
}




/*
int APP_TestRun(char* title)
{
	float fa,fb;
	u32 ua,ub,i,ta,sd;
	struct timeval time_1,time_2;
	APP_ShowSta(title,"测试开始");
	ta=31415;
	ua=ta<<8;
	ub=ta;
	gettimeofday(&time_1, NULL);
	i=100000;
	while(i--)
	{
		ua+=ub;
		sd = ua>>8;
	}
	gettimeofday(&time_2, NULL);
	printf("---ua1->s=%d,us=%d,,%d\r\n",time_2.tv_sec-time_1.tv_sec,time_2.tv_usec-time_1.tv_usec,time_1.tv_usec);


	ua=ta<<8;
	ub=ta;
	gettimeofday(&time_1, NULL);
	i=100000;
	while(i--)
	{
		ua+=ub;
		sd = ua/0x100;
	}
	gettimeofday(&time_2, NULL);
	printf("---ua2->s=%d,us=%d,,%d\r\n",time_2.tv_sec-time_1.tv_sec,time_2.tv_usec-time_1.tv_usec,time_1.tv_usec);

	fa=ta/10;
	fb=ta/1000;
	gettimeofday(&time_1, NULL);
	i=100000;
	while(i--)
	{
		fa += fb;
		sd = fa;
	}
	gettimeofday(&time_2, NULL);
	printf("---fa->s=%d,us=%d,,%d\r\n",time_2.tv_sec-time_1.tv_sec,time_2.tv_usec-time_1.tv_usec,time_1.tv_usec);


	APP_ShowSta(title,"测试完成");
	
	return 0;
	//return APP_WaitUiEvent(3*1000);
}
*/
int APP_ScreenTest(char *pTitle)
{
	RECTL tRect;
	u8	ScreenBitFail=0x3f;
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER,"红绿蓝白黑灰渐");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,"按[确认]键表示正常");
	API_GUI_Show();
	APP_WaitUiEvent(3000);
	//--------全屏显示不刷新状态栏-----------------
	xui_fb_GetScreenMsg(&tRect,NULL);
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB565_RED);
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x01;
	}
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB565_GREEN);
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x02;
	}
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB565_BLUE);
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x04;
	}
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB565_WITHE);
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x08;
	}
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB_CURR(127,127,127));
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x20;
	}
	fb_ui_fill_rect(tRect.left,tRect.top,tRect.width,tRect.height,RGB565_BLACK);
	xui_fb_syn();
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x10;
	}
	
	{
		u8 rgb,w;
		u16 i,max;
		i=tRect.top;
		max=tRect.top+tRect.height;
		w = tRect.width/3;
		for(rgb=0;i<max;i++)
		{
			fb_ui_hline(tRect.left,i,w,RGB_CURR(rgb,0,0));
			fb_ui_hline(tRect.left+w,i,w,RGB_CURR(0,rgb,0));
			fb_ui_hline(tRect.left+w+w,i,w,RGB_CURR(0,0,rgb));
			rgb++;
			if(rgb==0) break;
		}
		for(i++;i<max;i++,rgb++)
		{
			fb_ui_hline(tRect.left,i,w,RGB_CURR(0,rgb,rgb));
			fb_ui_hline(tRect.left+w,i,w,RGB_CURR(rgb,0,rgb));
			fb_ui_hline(tRect.left+w+w,i,w,RGB_CURR(rgb,rgb,0));
		}
		xui_fb_syn();
	}
	if(EVENT_OK==APP_WaitUiEvent(10*1000))
	{
		ScreenBitFail &= ~0x40;
	}
//	tFacTestResult.ScreenBitFail=ScreenBitFail;
//	tFacTestResult.RunFlag |= 0x04;
	//--------恢复刷新状态栏-----------------
//	OldScreen.screenRefState=TRUE;
//	OldScreen.ReDisplayScreen=0xff;//重新显示所有
	return 0;
}

int APP_TestUart(char* pTitle)
{
	int ret,port;
	char showBuff[256];
	port = PORT_COM1;
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	showBuff[0]='\0';
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"打开串口");
	ret=OsPortOpen(port,"115200,8,n,1");
	if(ret)
	{
		LOG(LOG_ERROR,"OsPortOpen Err[%d]\r\n",ret);
		return 1;
	}
	OsPortReset(port);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n发送起动数据");
	OsPortSend(port,"com start..\n",13);
	{
		int offset=0;
		char buff[1024];
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收数据",ret);
		ret=OsPortRecv(port,buff,1,10*1000);
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d,%02X]",ret,buff[0]);
		if(ret > 0)
		{
			while(ret>0)
			{
				offset += ret;
				OsSleep(10);
				ret=OsPortRecv(port,buff+offset,sizeof(buff)-offset,0);
				APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
			}
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n返回[%d]数据",offset);
			OsPortSend(port,buff,offset);
		}
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收数据",ret);
		ret=OsPortRecv(port,buff,1,5*1000);
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d,%02X]",ret,buff[0]);
		if(ret > 0)
		{
			while(ret>0)
			{
				offset += ret;
				OsSleep(10);
				ret=OsPortRecv(port,buff+offset,sizeof(buff)-offset,0);
				APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
			}
		}
	}
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n关闭串口",ret);
	OsPortClose(port);
	OsSleep(5000);
	return 0;
}


int APP_TestNet(char* pTitle)
{
	int ret;
	char showBuff[2048];
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	showBuff[0]='\0';
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"连接网络");
	
	ret=APP_Network_Connect("192.168.56.1",60000,0);
	if(ret)
	{
		LOG(LOG_ERROR,"Network_Connect Err[%d]\r\n",ret);
		return 1;
	}
	APP_Network_Send("guozu test00001",16);
	{
		int offset=0;
		char buff[1024];
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收数据",ret);
		ret=APP_Network_Recv(buff,1,10*1000,NULL);
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d,%02X]",ret,buff[0]);
		if(ret > 0)
		{
			while(ret>0)
			{
				offset += ret;
				OsSleep(10);
				ret=APP_Network_Recv(buff+offset,sizeof(buff)-offset,0,NULL);
				APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
			}
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n返回[%d]数据",offset);
			APP_Network_Send(buff,offset);
		}
	}
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n关闭网络",ret);
	APP_Network_Disconnect(1000);
	return 0;
}



int APP_HardTestMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"UI基础测试",		APP_UiBaseTest},
		{"UI_pull_push",	APP_UiPullPush},
		{"串口测试",		APP_TestUart},
		{"网络测试",		APP_TestNet},
		{"进度调测试",		APP_TestShowBottom},
		//{"速度测试",		APP_TestRun},
		{"显示屏测试",		APP_ScreenTest},
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

int APP_TestDrawBoard(char *pTitle)
{
	APP_ShowDrawBoard(pTitle);
	return API_WaitEvent(20*1000,EVENT_UI,EVENT_ABS,EVENT_NONE);
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
		{"签名板测试",			APP_TestDrawBoard},
	//	"单项测试",				NULL,
	//	"自动测试",				NULL,
	//	"测试结果",				NULL,
	//	"老化测试",				NULL,
	//	"拨打电话测试",			NULL,
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}



int APP_EDIT_SetDateTime(char* title)
{
	ST_TIME tTime;
	char sDateTime[24];
	OsGetTime(&tTime);
	sprintf(sDateTime,"%04d-%02d-%02d %02d:%02d-%02d",tTime.Year,tTime.Month,tTime.Day,tTime.Hour,tTime.Minute,tTime.Second);
	APP_ShowMsg(title,sDateTime,3000);
	return 0;
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

int APP_InstallAPP(char *pTitle)
{
	ST_APP_INFO tAppInfo;
	APP_ShowSta(pTitle,"向主机请求中...");
	if(!APP_TmsProcess(COM_UART))
	{
		APP_ShowMsg(pTitle,"下载失败",3000);
		return 1;
	}
	APP_ShowSta(pTitle,"应用安装中");
	if(0==InstallAPP(&tAppInfo))
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



