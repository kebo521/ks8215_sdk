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

#include "emv_type.h"
#include "emv_tag.h"
#include "emvapi.h"
#include "emvspi_plugin.h"
#include "dataconv.h"


//1连续扫码，2SIM卡测试，3按键测试，4充电测试，5显示屏测试，6摄像头测试

typedef struct
{
	u32		RunFlag; 
	u32		KeyBitFail;
	u16		ScandFail;
	u8		ScreenBitFail;		//屏显示
	u8		SimFail;
	u8		voiceFail;
	u8		communication;
	u8		BatteryFail; 
	u8		NfcFail;
}FACTORY_TEST_RESULT;
FACTORY_TEST_RESULT tFacTestResult={0};


int APP_QrCodeTest(char *pTitle)
{
	APP_ShowQrCode(pTitle,"12345678abcduehsfiufwfowei3482y348239342",RGB_CURR(0,0,0xff));
	return APP_WaitUiEvent(5000);
}

int APP_BatteryTest(char *pTitle)
{
	return APP_ShowMsg(pTitle,"测试充电与放电",2000);
}


int APP_DeleteKeyAndShow(char *str, char *substr)
{
	int substr_len;
	char *pos;

	pos = API_strstr(str, substr);
	substr_len = API_strlen(substr);
	if(pos)
	{	
		API_memset(pos, 0x20, substr_len);
	}
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_RECT_CLEAR,str);
	API_GUI_Show();
	return 0;
}

int APP_KeyDeleteTest(char *pTitle)
{
	u32 even,KeyBitFlag=0x3ffff;
	char showBuff[256]="[ 取消 ]  [ 清除 ]\n[ 功能 ]  [ 确认 ]\n[ 1 ] [ 2 ] [ 3 ]\n[ 4 ] [ 5 ] [ 6 ]\n[ 7 ] [ 8 ] [ 9 ]\n[ 字母 ] [ 0 ] [ . ]\n[上] [下]";
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP, showBuff);
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE, "除电源键,按完所有键");
	API_GUI_Show();
	while(1)
	{
		even=API_WaitEvent(30*1000,EVENT_KEY,EVENT_NONE);
		if(even&EVENT_KEY)
		{
			switch(even&EVENT_INDEX)
			{
				case K_CANCEL:
					KeyBitFlag &= ~(0x01<<11);
					APP_DeleteKeyAndShow(showBuff,"[ 取消 ]");
					break;
				case K_OK:
					KeyBitFlag &= ~(0x01<<12);
					APP_DeleteKeyAndShow(showBuff,"[ 确认 ]");
					break;
				case K_DEL:
					KeyBitFlag &= ~(0x01<<13);
					APP_DeleteKeyAndShow(showBuff,"[ 清除 ]");
					break;
				case K_FUNC:
					KeyBitFlag &= ~(0x01<<14);
					APP_DeleteKeyAndShow(showBuff,"[ 功能 ]");
					break;
				case K_IME:
					KeyBitFlag &= ~(0x01<<15);
					APP_DeleteKeyAndShow(showBuff,"[ 字母 ]");
					break;
				case K_UP:
					KeyBitFlag &= ~(0x01<<16);
					APP_DeleteKeyAndShow(showBuff,"[上]");
					break;
				case K_DOWN:
					KeyBitFlag &= ~(0x01<<17);
					APP_DeleteKeyAndShow(showBuff,"[下]");
					break;
				default:
				{
					char keystr[7],keyVar;
					keyVar = even&EVENT_INDEX;
					if((keyVar<K_0 || keyVar>K_9)&&(keyVar != K_D))
						break;
					API_memset(keystr, 0, sizeof(keystr));
					API_sprintf(keystr, "[ %c ]", keyVar);
					APP_DeleteKeyAndShow(showBuff,keystr);
					if(keyVar>=K_0 && keyVar<=K_9)
					{
						KeyBitFlag &= ~(0x01<<(keyVar-K_0));
					}
					else
					{
						KeyBitFlag &= ~(0x01<<10);
					}
				}
			}
			if(KeyBitFlag==0) break;
		}
		else if(even&EVENT_TIMEOUT)
		{
			break;
		}
	}
	LOG(LOG_INFO,"APP_KeyDeleteTest[%03X]\r\n",KeyBitFlag);
	tFacTestResult.KeyBitFail=KeyBitFlag;
	tFacTestResult.RunFlag |= 0x01;
	return RET_OK;
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
	APP_ShowSta(pTitle,"UI底层全屏显示");
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
	APP_ShowSta(title,"内存覆盖");
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
		OsSleep(500);
	}
	return 0;
}


int APP_TestMsr(char* title)
{
	int ret,timeoutMs=30*1000;
	LOG(LOG_INFO,"->TestMsr In\r\n");
	ret=OsMsrOpen();
	APP_ShowSta(title,"请刷卡");
	while(timeoutMs>0)
	{
		ret=OsMsrSwiped();
		if(ret == TRUE) break;
		OsSleep(500);
		timeoutMs -= 500;
	}
	ret=OsMsrSwiped();
	if(ret == TRUE)
	{
		ST_MSR_DATA tTrack[3];
		char showBuff[512],*pShow;
		OsMsrRead(&tTrack[0],&tTrack[1],&tTrack[2]);
		pShow=showBuff;

		if(tTrack[0].DataLen)
		{
			tTrack[0].TrackData[tTrack[0].DataLen]=0x00;
			pShow += sprintf(pShow,"Track1:%s\n",tTrack[0].TrackData);
		}
		if(tTrack[1].DataLen)
		{
			tTrack[1].TrackData[tTrack[1].DataLen]=0x00;
			pShow += sprintf(pShow,"Track2:%s\n",tTrack[1].TrackData);
		}
		if(tTrack[2].DataLen)
		{
			tTrack[2].TrackData[tTrack[2].DataLen]=0x00;
			pShow += sprintf(pShow,"Track3:%s\n",tTrack[2].TrackData);
		}
		APP_ShowInfo(title,showBuff,30*1000);
	}
	APP_ShowSta(title,"关闭读卡器");
	OsMsrClose();
	return ret;
}

/**
 * @brief 卡片读写
 * @param ibuf 输入数据
 * @param ilen 输入数据长度
 * @param obuf 输出数据
 * @param osize 输出数据长度限制
 * @return [>=2]-输出数据长度 [-1]-失败
 
int emvplugin_icc_rw(u8* ibuf, int ilen, u8* obuf, int osize)
{
	int RetLen;
	ST_APDU_REQ tApduReq;
	ST_APDU_RSP tApduRsp;
	//LOG_HEX(LOG_INFO,"Eicc_rw:In:",ibuf,ilen);
	memcpy(tApduReq.Cmd,ibuf,sizeof(tApduReq.Cmd));
	tApduReq.LC = ibuf[4];
	memcpy(tApduReq.DataIn,ibuf+5,ibuf[4]);
	
	if(OsIccExchange(0,&tApduReq,&tApduRsp))
		return -1;
	memcpy(obuf,tApduRsp.DataOut,tApduRsp.LenOut);
	RetLen = tApduRsp.LenOut;
	if(tApduRsp.SWB == 0x00 && (tApduRsp.SWA==0x61 || tApduRsp.SWA==0x6C))
	{
		if(tApduRsp.SWA==0x61)		//正常结束,还有有效数据可取
		{
			memcpy(tApduReq.Cmd,"\x00\xC0\x00\x00",sizeof(tApduReq.Cmd));
		}
		tApduReq.LC = 0x00;
		tApduReq.LE	=tApduRsp.SWB; 	// ((iSW&0xff00)==0x6C00) 长度错误,P3不正确
		//----------------------------------------------
		if(OsIccExchange(0,&tApduReq,&tApduRsp))
			return -1;
		memcpy(obuf+RetLen,tApduRsp.DataOut,tApduRsp.LenOut);
		RetLen += tApduRsp.LenOut;
	}
	obuf[RetLen++] =tApduRsp.SWA;
	obuf[RetLen++] =tApduRsp.SWB;
	//LOG_HEX(LOG_INFO,"Eicc_rw:Out:",obuf,RetLen);
	return RetLen;
}
*/

int APP_TestICC(char* title)
{
	int ret,timeoutMs=30*1000;
	LOG(LOG_INFO,"->TestMsr In\r\n");
	ret=OsIccOpen(0);
	APP_ShowSta(title,"请刷卡");

	while(timeoutMs>0)
	{
		ret=OsIccDetect(0);
		if(ret == RET_OK) break;
		OsSleep(500);
		timeoutMs -= 500;
	}
	//OsIccExchange();
	APP_ShowSta(title,"关闭读卡器");
	OsMsrClose();
	return ret;
}

int APP_TestQIC(char* title)
{
	int ret,timeoutMs=30*1000;
	u8 sArc[64]={0};
	LOG(LOG_INFO,"->TestMsr In\r\n");
	ret=OsPiccOpen();
	APP_ShowSta(title,"请挥卡");

	while(timeoutMs>0)
	{
		ret=OsPiccPoll(NULL,sArc);
		if(ret == RET_OK) break;
		OsSleep(500);
		timeoutMs -= 500;
	}
	//OsIccExchange();
	LOG(LOG_INFO,"sArc[%s]\r\n",sArc);
	APP_ShowSta(title,"关闭读卡器");
	OsPiccClose();
	return ret;
}


int IC_SelectAid(u8 type,char* pAid,u8 AidLen)	//选目录
{
	ST_APDU_REQ tApduReq;
	ST_APDU_RSP tApduRsp;
	tApduReq.Cmd[0] = 0x00;
	tApduReq.Cmd[1] = 0xa4;
	tApduReq.Cmd[2]	= 0x04;
	tApduReq.Cmd[3]	= 0x00;
	tApduReq.LC = AidLen;
	API_memcpy(tApduReq.DataIn, pAid, AidLen);
	tApduReq.LE = 0;
	if(type == EMV_CARD_CONTACTLESS)
	{
		if(OsPiccIsoCommand(0,&tApduReq,&tApduRsp))
			return -1;
		if(tApduRsp.SWA != 0x90)
			return 1;
	}
	else if(type == EMV_CARD_CONTACT)
	{
		if(OsIccExchange(0,0,&tApduReq,&tApduRsp))
			return -1;
		if(tApduRsp.SWA != 0x90)
			return 1;
	}
	return 0;
}

int APP_ICC_Test(char* title)
{
	u8 		buffStr[127],Openflag;
	int		ret;
	ST_TIMER tTimer;
	ret=OsIccOpen(0);
	ret=OsPiccOpen();
	APP_ShowSta(title,"请插IC卡或挥IC卡");
	Openflag=0;
	OsTimerSet(&tTimer,30*1000);
	while(OsTimerCheck(&tTimer))
	{
		ret=OsPiccPoll(NULL,buffStr);
		if(ret == RET_OK) 
		{
			Openflag=EMV_CARD_CONTACTLESS;
			break;
		}
		ret=OsIccDetect(0);
		if(ret == RET_OK) 
		{
			Openflag=EMV_CARD_CONTACT;
			break;
		}
		if(EVENT_CANCEL == APP_WaitUiEvent(2000))
			break;
	}
	if(Openflag)
	{
		if(IC_SelectAid(Openflag,"2PAY.SYS.DDF01",14))
		{
			LOG(LOG_ERROR,"PSam_SelectFile Err!!!");
		}
		if(IC_SelectAid(Openflag,"\xA0\x00\x00\x03\x33\x01\x01\x02",8))
		{
			LOG(LOG_ERROR,"PESam_SelectAid Err!!!");
		}
		APP_ShowMsg(title,"测试完成",3000);
	}
	OsPiccClose();	//关闭剩下的IC 卡；
	OsIccClose(0);
	return 0;
}

//====================================================================
//功能:  电子现金查余额并显示余额
//作用:  可直接显示当前余额和余额上限
//输入数据:title显示标题
//输出数据:NULL
//---------------------------------------------------------------
int ElectronicCashBalance(char* title)
{
	u8 buffBCD[32],Openflag;
	char buffStr[128];
	char CashStr[16];
	int slen,resplen;
	int		ret,timeoutMs=30*1000;
	//addmsg_emv();
	
	API_strcpy(buffStr,"仅限IC卡交易\n");
	ret=OsIccOpen(0);
	if(ret==RET_OK)
		API_strcat(buffStr,"请插IC卡");

	ret=OsPiccOpen();
	if(ret==RET_OK)
		API_strcat(buffStr,"请挥IC卡");
	APP_ShowSta(title,buffStr);
	Openflag=0;
	while(timeoutMs>0)
	{
		ret=OsPiccPoll(NULL,(u8*)buffStr);
		if(ret == RET_OK) 
		{
			Openflag=EMV_CARD_CONTACTLESS;
			break;
		}
		ret=OsIccDetect(0);
		if(ret == RET_OK) 
		{
			Openflag=EMV_CARD_CONTACT;
			break;
		}
		OsSleep(500);
		timeoutMs -= 500;
	}
	if(Openflag)
	{
		do{
			if(emvspi_Start(Openflag)) break;
			//-------------------------------------------
			//APP_ShowSta(title,"处理中..请勿拔/移卡");
			emv_set_trans_type(_EMV_TRANSTYPE_EC_INQUIRY);
			do
			{
				resplen=emv_process();
			}
			while((resplen>0)&&(resplen!=EMV_COMPLETED));
			if(resplen != EMV_COMPLETED)
			{
				API_sprintf(buffStr,"初始化失败[%d]",resplen);
				APP_ShowMsg(title,buffStr,3000);
				break; //操作失败
			}
			//----------------------------TAG_9F5D_AVAILABLE_OFFLINE_SPENDING_AMOUNT----------------
			slen=0;
			if (emv_get_tag_data(TAG_9F79_EC_BALANCE, buffBCD, &resplen) == EMV_OK)
			{
				API_strcpy(buffStr+slen,"电子现金余额:");
				slen +=API_strlen(buffStr+slen);
				Conv_BcdToStr(buffBCD,resplen,CashStr);
				slen += Conv_TmoneyToDmoney(buffStr+slen,CashStr);
				buffStr[slen++]='\n';
			}
			if (emv_get_tag_data(TAG_9F77_EC_BALANCE_LIMIT, buffBCD, &resplen) == EMV_OK)
			{
				API_strcpy(buffStr+slen,"余额上限:");
				slen +=API_strlen(buffStr+slen);
				Conv_BcdToStr(buffBCD,resplen,CashStr);
				slen += Conv_TmoneyToDmoney(buffStr+slen,CashStr);
				buffStr[slen++]='\n';
			}
			if(slen>5)
			{
				buffStr[slen++]=0;
				APP_ShowInfo(title,buffStr,10*1000);
			}
			else 
			{
				APP_ShowMsg(title,"查询失败",3000);
			}
		}while(0);
		emvspi_end(Openflag);
	}
	OsPiccClose();	//关闭剩下的IC 卡；
	OsIccClose(0);
	return 0;
}



int APP_TestPrint(char* title)
{
	DEF_PRINT_DATA *pPrint;
	RECTL tRect;
	A_RGB* pBufRGB,*pRgb;
	u8* pBit;
	int i,j;
	LOG(LOG_INFO,"->TestMsr In\r\n");
	APP_ShowSta(title,"打开打印机");
	OsPrnOpen(PRN_BMP,"print01.bmp");
	APP_ShowSta(title,"设置参数");
	OsPrnSetSize(384,384);
	OsPrnSetSpace(0,0);
	OsPrnSetIndent(0,0);

	if(OsPrnSetFont("ks.res"))
	{
		APP_ShowSta(title,"字体不存在");
		return 1;
	}
	APP_ShowSta(title,"打印内容");
	OsPrnPrintf("88901234223\n");
	OsPrnSetSpace(3,3);
	OsPrnPrintf("12345678\n");
	OsPrnSetSpace(7,7);
	OsPrnPrintf("12345678\n");
	OsPrnSetSpace(13,13);
	OsPrnPrintf("12345678\n");
	OsPrnSetSpace(9,9);
	OsPrnPrintf("1打3印5测6试haha*#!@#$%^&*()\n");
	//OsPrnPrintf("打印\n");
//	OsPrnPrintf("2我1在哪 l%d\n",123);
//	OsPrnPrintf("有2什么3人 n%d\n",456);
//	OsPrnPrintf("什么时候做什么 w%s\n","hahaha");
	APP_ShowSta(title,"输出打印内容");
	OsPortOpen(PORT_COM1,"115200,8,n,1");
	OsPrnStart();
	OsMsrClose();


	pPrint=OsGerPrintData();
	tRect.left=0;
	tRect.top=0;
	tRect.width = pPrint->width;
	tRect.height= pPrint->height;
	LOG(LOG_INFO,"->tRect width[%d]height[%d]lineW[%d]\r\n",tRect.width,tRect.height,pPrint->lineW);
	pBufRGB =(A_RGB*)malloc(tRect.height*tRect.width*sizeof(A_RGB));
	pRgb = pBufRGB;
	for(j=0;j<tRect.height;j++)
	{
		pBit = pPrint->pBufBit+(j * pPrint->lineW);
		for(i=0;i<tRect.width;i++)
		{
			if(*pBit & (0x80>>(i&7)))
			{
				*pRgb = RGB_CURR(0xff,0xff,0x00);
			}
			else
			{
				*pRgb = RGB_CURR(0x00,0x00,0xff);	
			}
			pRgb++;
			if((i&7)==7) pBit++;
		}
	}
	fb_ui_set_rect(tRect.left,tRect.top,tRect.width,tRect.height,pBufRGB);
	free(pBufRGB);
	OsPrnClose();
	APP_ShowSta(title,"结束打印");
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
	tFacTestResult.ScreenBitFail=ScreenBitFail;
	tFacTestResult.RunFlag |= 0x04;
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
	ret=OsPortSend(port,"com start..\n",13);
	do
	{
		int offset=0;
		char buff[1024];
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收数据1",ret);
		ret=OsPortRecv(port,buff,1,10*1000);
		if(ret == ERR_TIME_OUT)
		{
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"->超时");
			break;
		}
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
		APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收数据2",ret);
		ret=OsPortRecv(port,buff,1,5*1000);
		if(ret == ERR_TIME_OUT)
		{
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"->超时");
			break;
		}
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
	while(0);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n关闭串口",ret);
	OsPortClose(port);
	return APP_WaitUiEvent(15000);
}

int TMS_CheckFullData(u8 *pIndata,int InLen)
{
	if(InLen > 2)
	{
		int Len;
		Len = pIndata[0]*256 + pIndata[1] + 2;
		if(InLen >= Len) return Len;
	}
	return 0;
}

int APP_TestNet(char* pTitle)
{
	int ret;
	char showBuff[2048];
	u8  buff[1024];
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	showBuff[0]='\0';
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"连接网络->kbai.club:8888");
	ret=APP_Network_Connect("106.52.246.42",8888,0);	//kbai.club	//106.52.246.42
	//ret=APP_Network_Connect("218.17.164.125",20011,0);
	if(ret)
	{
		LOG(LOG_ERROR,"Network_Connect Err[%d]\r\n",ret);
		return 1;
	}
	ret=sprintf((char*)buff+2,"%s","123+456*2+84/2");
	buff[0]=ret/256;
	buff[1]=ret&0xff;
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n发送:%s",buff+2);
	//memcpy(buff,"\x00\x3C\x60\x05\x01\x00\x00\x61\x32\x00\x32\x01\x14\x08\x00\x00\x20\x00\x00\x00\xC0\x00\x12\x00\x00\x01\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x38\x00\x11\x00\x00\x00\x01\x00\x40\x00\x03\x30\x31\x20",0x3e);
	//APP_Network_Send(buff,0x3e);
	APP_Network_Send(buff,ret + 2);
	memset(buff,0,1024);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收:");
	ret=APP_Network_Recv(buff,sizeof(buff),10*1000,TMS_CheckFullData);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n断开网络");
	APP_Network_Disconnect(1000);
	return APP_WaitUiEvent(30*1000);
}

/*
int APP_TestNet(char* pTitle)
{
	int ret,offset=0,sLen;
	char showBuff[2048];
	char  buff[1024];
	API_GUI_CreateShow(pTitle,NULL,TCANCEL);
	showBuff[0]='\0';
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"连接网络->kbai.club:8888");
	ret=APP_Network_Connect("kbai.club",8888,0);	//kbai.club	//106.52.246.42
	if(ret)
	{
		LOG(LOG_ERROR,"Network_Connect Err[%d]\r\n",ret);
		return 1;
	}
	ret=sprintf(buff+2,"%s","123+456*2+84/2");
	buff[0]=ret/256;
	buff[1]=ret&0xff;
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n发送:%s",buff+2);
	APP_Network_Send(buff,ret+2);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n接收:",ret);
	ret=APP_Network_Recv(buff,2,10*1000,NULL);
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
	if(ret > 1)
	{
		sLen=buff[0]*256 + buff[1];
		offset = 0;
		while(offset < sLen)
		{
			ret=APP_Network_Recv(buff+offset,sLen-offset,3000,NULL);
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"[%d]",ret);
			if(ret <= 0) break;
			offset += sLen;
		}
		if(offset)
		{
			buff[offset] = '\0';
			APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n%s",buff);
		}
	}
	APP_ShowChangeInfo(showBuff,sizeof(showBuff),"\n断开网络",ret);
	APP_Network_Disconnect(1000);
	return APP_WaitUiEvent(30*1000);
}
*/
int APP_UartClose(char* title)
{
	OsPortClose(PORT_COM1);
	return 0;
}

int APP_TestReadCard(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"刷卡测试",			APP_TestMsr},
		{"IC卡测试",			APP_TestICC},
		{"非接IC测试",			APP_TestQIC},
		{"命令测试",			APP_ICC_Test},
		{"电子现金查余额",		ElectronicCashBalance},
		{"打印测试",			APP_TestPrint},
	};
	if(OsPortOpen(PORT_COM1,"115200,8,n,1") != RET_OK) return -1;
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
	APP_AddCurrentMenuOtherFun(MENU_OUT_FUN,&APP_UartClose,NULL);
	return 0;
}

int APP_TestPicture(char* title)
{
	APP_ShowSta(title,"TradeOK.bmp");
	if(APP_ShowPictureFile(NULL,"TradeOK.bmp"))
	{
		APP_ShowSta(title,"失败");
	}
	APP_WaitUiEvent(5*1000);
	APP_ShowPictureFile(NULL,"tree.png");
	APP_WaitUiEvent(5*1000);
	return 0;
}


int APP_HardTestMenu(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"按键测试",		APP_KeyDeleteTest},
		{"显示屏测试",		APP_ScreenTest},
		{"读卡卡测试",		APP_TestReadCard},
		{"串口测试",		APP_TestUart},
		{"网络测试",		APP_TestNet},
		{"电池测试",		APP_BatteryTest},
		{"显示图片",		APP_TestPicture},
		
		{"UI基础测试",		APP_UiBaseTest},
		//{"SIM卡测试",		APP_AutoTest},
		//{"扫码头测试",		APP_AutoTest},
		//{"播放语音测试",	APP_AutoTest},
		{"测试界面暂存",	APP_UiPullPush},
		{"进度调测试",		APP_TestShowBottom},
		//{"速度测试",		APP_TestRun},
	};
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	//APP_AddCurrentMenuOtherFun(MENU_OUT_FUN,APP_SaveTestResult,NULL);
	return 0;
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
	API_WaitEvent(60*1000,EVENT_UI,EVENT_ABS,EVENT_NONE);
	APP_ShowMsg(pTitle,"测试完成",3000);
	return 0;
}

int APP_AutoTest(char *pTitle)
{
	APP_ShowMsg(pTitle,"自动执行每一项测试\n按提示操作",2000);
	APP_KeyDeleteTest("按键测试");
	APP_ScreenTest("显示屏测试");
	APP_TestReadCard("读卡卡测试");
	APP_TestUart("串口测试");
	APP_TestNet("网络测试");
	APP_BatteryTest("电池测试");
	APP_TestPicture("显示图片");
	return 0;
}


int APP_FactoryMeun(char* title)
{
	CMenuItemStru MenuStruPar[]=
	{
		{"单项测试",			APP_HardTestMenu},
		{"自动测试",			APP_AutoTest},
		//{"测试结果",			APP_AutoTest},
		//{"老化测试",			APP_AutoTest},
		{"九方位显示 ",			APP_NineDirecTest},
		{"嵌套菜单",			APP_QianTest},
		{"弹窗测试",			APP_AppHitShow},
		{"二维码测试",			APP_QrCodeTest},
		{"签名板测试",			APP_TestDrawBoard},
	};
	return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,-1);
}





int APP_UartOpen(char* title)
{
	if(OsPortOpen(PORT_COM1,"115200,8,n,1") != RET_OK) 
		return EVENT_QUIT+1;
	return 0;
}


FixedMenuUITable tTestReadCard={
	APP_UartOpen,		//InFunc;		//进入功能
	APP_UartClose,	//OutFunc;		//退出功能
	30*1000,			//timoutMs
	6,
	{
		{"刷卡测试",			APP_TestMsr},
		{"IC卡测试",			APP_TestICC},
		{"非接IC测试",			APP_TestQIC},
		{"命令测试",			APP_ICC_Test},
		{"电子现金查余额",		ElectronicCashBalance},
		{"打印测试",			APP_TestPrint},
	}
};


FixedMenuUITable tHardTestMenu={
	NULL,	//InFunc;		//进入功能
	NULL,	//OutFunc;		//退出功能
	30*1000,	//timoutMs
	10,
	{
		{"按键测试",		APP_KeyDeleteTest,FUN_MENU_F},
		{"显示屏测试",		APP_ScreenTest,FUN_MENU_F},
		{"读卡卡测试",		&tTestReadCard,FUN_MENU_G},
		{"串口测试",		APP_TestUart,FUN_MENU_F},
		{"网络测试",		APP_TestNet,FUN_MENU_F},
		{"电池测试",		APP_BatteryTest,FUN_MENU_F},
		{"显示图片",		APP_TestPicture,FUN_MENU_F},
		
		{"UI基础测试",		APP_UiBaseTest,FUN_MENU_F},
		//{"SIM卡测试",		APP_AutoTest,FUN_MENU_F},
		//{"扫码头测试",		APP_AutoTest,FUN_MENU_F},
		//{"播放语音测试",	APP_AutoTest,FUN_MENU_F},
		{"测试界面暂存",	APP_UiPullPush,FUN_MENU_F},
		{"进度调测试",		APP_TestShowBottom,FUN_MENU_F},
		//{"速度测试",		APP_TestRun,FUN_MENU_F},
	}
};


FixedMenuUITable tFactoryMeun={
	NULL,	//InFunc;		//进入功能
	NULL,	//OutFunc;		//退出功能
	-1,		//timoutMs
	7,
	{
		{"单项测试",		&tHardTestMenu,FUN_MENU_G},
		{"自动测试",		APP_AutoTest,FUN_MENU_F},
		//{"测试结果",		APP_AutoTest,FUN_MENU_F},
		//{"老化测试",		APP_AutoTest,FUN_MENU_F},
		{"九方位显示 ",		APP_NineDirecTest,FUN_MENU_F},
		{"嵌套菜单",		APP_QianTest,FUN_MENU_F},
		{"弹窗测试",		APP_AppHitShow,FUN_MENU_F},
		{"二维码测试",		APP_QrCodeTest,FUN_MENU_F},
		{"签名板测试",		APP_TestDrawBoard,FUN_MENU_F},
	}
};




