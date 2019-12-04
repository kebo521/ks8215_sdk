//============================================================
//---显示功能---
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "comm_type.h"

#include "EvenMsg.h"
#include "xui_ui.h"
#include "xui_fb.h"
#include "xui_font.h"
#include "xui_gui.h"

#include "key_hard.h"
#include "language.h"
#include "sdk/sys_sdk.h"


//=========================按键定义==========================
static const char* KeyMsgABC[10]={"*#:/?%@-+=","&$!,;'`^~\"_|","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};

//#include "QR_Encode.h"

typedef struct {
	XuiWindow *pWindow;
	u16		hfont,hn,hmc;			//字体高度，内容数，菜单项高度
	u16		width,htitle,hcont;		//菜单宽度，标题高度，内容高度
	A_RGB	titleFclr,contFclr;	//标题背景色，标题字体色
	FunFillColour pFillColour;
	XuiWindow *pOldWindow;
}GUI_THEME_MSG;

static GUI_THEME_MSG tGuiThemeMsg={0};

void API_GUI_LoadWindow(XuiWindow *pWindow)
{
	tGuiThemeMsg.hfont = FONT_SIZE;
	tGuiThemeMsg.hn = 8+1;
	do
	{//------自动计算每行高度-------
		tGuiThemeMsg.hn--;
		tGuiThemeMsg.hmc = pWindow->height/(1 + tGuiThemeMsg.hn);
	}
	while(tGuiThemeMsg.hmc < tGuiThemeMsg.hfont);
	
	tGuiThemeMsg.hcont = tGuiThemeMsg.hmc*tGuiThemeMsg.hn;
	tGuiThemeMsg.htitle = pWindow->height - tGuiThemeMsg.hcont;
	tGuiThemeMsg.width = pWindow->width;
	tGuiThemeMsg.titleFclr = FONT_TITLE_COLOUR;
	tGuiThemeMsg.contFclr = RGB565_TIEM_FONT;
	tGuiThemeMsg.pWindow = pWindow;
//	LOG(LOG_INFO,"Theme[%d][%d][%d][%d][%d]\r\n",tGuiThemeMsg.hfont,tGuiThemeMsg.hn,tGuiThemeMsg.hmc,tGuiThemeMsg.htitle,tGuiThemeMsg.hcont);
}


XuiWindow *API_GUI_GetCurrWindow(void)
{
	return tGuiThemeMsg.pWindow;
}


void API_FillMenuBack(A_RGB* pBack,int w,int h)
{
	A_RGB colour;
	A_RGB *pEnd;
	int item;
	colour=UI_TITLE_COLOUR;
	//--------------标题空间-------------------------
	pEnd = pBack+ (w*tGuiThemeMsg.htitle);
	while(pBack < pEnd)
	{
		*pBack++ = colour;
	}
	//--------------内容空间------------------------
	for(item=0 ; item<tGuiThemeMsg.hn ; item++)
	{
		if(item&0x01)
			colour = RGB_CURR(232,232,232);
		else
			colour = RGB_CURR(240,240,240);
		pEnd = pBack+ (w*tGuiThemeMsg.hmc);
		while(pBack < pEnd)
		{
			*pBack++ = colour;
		}
	}
}

void API_FillShowBack(A_RGB* pBack,int w,int h)
{
	A_RGB colour;
	A_RGB *pEnd;
	colour=UI_TITLE_COLOUR;
	//--------------标题空间-------------------------
	pEnd = pBack+ (w*tGuiThemeMsg.htitle);
	while(pBack < pEnd)
	{
		*pBack++ = colour;
	}
	//--------------内容空间------------------------
	colour = RGB565_TIEM_ICON;
	pEnd = pBack+ (w*tGuiThemeMsg.hcont);
	while(pBack < pEnd)
	{
		*pBack++ = colour;
	}
}
//=================================================================================
int API_Set_Background(FunFillColour pFillColour)	// 'M' = menu , 'C'=cont
{
	if(pFillColour)
	{
		if(tGuiThemeMsg.pOldWindow!=tGuiThemeMsg.pWindow || pFillColour != tGuiThemeMsg.pFillColour)
		{
			UI_SetBackground(tGuiThemeMsg.pWindow,pFillColour);
			tGuiThemeMsg.pFillColour = pFillColour;
			tGuiThemeMsg.pOldWindow = tGuiThemeMsg.pWindow;
		}
	}
	UI_ShowBackground(tGuiThemeMsg.pWindow);
	return 0;
}

//===============清除显示内容(指定区域)=================================================
void API_GUI_ClearScreen(RECTL* pRect)
{
	XuiClearArea(tGuiThemeMsg.pWindow,pRect->left,pRect->top,pRect->width,pRect->height);
}


//------------------显示金额 转 交易金额-------------------------------
void ChinaDmoneyToTmoney(char* pOutStr,char* pInsMoney)
{
	u8 i,j,k;
	u8 Inlen=API_strlen(pInsMoney);
	for(i=0;i<Inlen;i++)
		if(pInsMoney[i]=='.') break;
	//----整数部分------
	for(j=0;j<i;j++)
		pOutStr[j]=pInsMoney[j];
	//---小数部分精确两位----
	if(i<Inlen)	//有小数点
	{
		for(i=0; i<2; i++)
		{
			if((j+1) < Inlen)
				pOutStr[j]=pInsMoney[j+1];
			else
				pOutStr[j]='0';
			j++;
		}
	}
	else	//无小数点,两位0
	{
		pOutStr[j++]='0';
		pOutStr[j++]='0';
	}
	//---过滤无效位------
	for(i=0; i<j; i++)
		if(pOutStr[i]!='0')
			break;
	if(i)
	{
		k=j-i;
		for(j=0;j<k;j++)
			pOutStr[j]=pOutStr[j+i];
	}
	pOutStr[j]='\0';
}

//------------------交易金额 转 显示金额-------------------------------
void ChinaTmoneyToDmoney(char* pOutdMoney,char* pIntMoney)
{
	u16 i=0,Inlen=API_strlen(pIntMoney);
	if(Inlen == 0)
	{
		pOutdMoney[0]='\0';
		return;
	}
	if(Inlen <= 2)
	{
		pOutdMoney[i++]='0';
		pOutdMoney[i++]='.';
		if(Inlen < 2)
			pOutdMoney[i++]='0';
		else
			pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}
	else
	{
		Inlen -= 2;
		while(i<Inlen)
		{
			pOutdMoney[i++]=*pIntMoney++;
		}
		pOutdMoney[i++]='.';
		pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}

	while(i--)	//去掉无效参数
	{
		if(pOutdMoney[i] == '.')
		{
			i--;
			break;
		}
		else if(pOutdMoney[i] != '0') 
			break;
	}
	pOutdMoney[++i]='\0';
}

int ChinaMoneyToCentInt(char* pInstr)
{
	int Integers;
	u8 i,IntNum,j,Inlen;
	//------金额数据有效性检查----------
	Inlen=strlen(pInstr);
	if(Inlen>1)
	{//------两位以上判断----------
		if(pInstr[0]=='0' && pInstr[1]!='.')
			return -1;
	}
	for(IntNum=0;IntNum<Inlen;IntNum++)
		if(pInstr[IntNum]=='.') break;
	//-------小数点后不能超过两位--------
	if((Inlen-IntNum) > 3)
		return -2;
	//------小数点后不能再有小数点------
	for(j=IntNum+1;j<Inlen;j++)
	{
		if(pInstr[j]=='.') 
			return -3;
	}
	Integers=0;
	for(j=0;j<IntNum;j++)
		Integers=Integers*10 + (pInstr[j]&0x0f);
	IntNum++;
	for(i=0;i<2;i++)
	{
		Integers *= 10;
		if((i+IntNum) < Inlen)
			Integers += pInstr[IntNum+i]&0x0f;
	}
	return Integers;
}


//================================画框=======================================================
void API_GUI_ShowColorRect(RECTL *pRect,u16 Width,A_RGB Color)
{
	RECTL fTrg;
	fTrg.left = pRect->left; fTrg.top = pRect->top;
	fTrg.width = pRect->width;
	fTrg.height= Width;
	UI_FillRectSingLe(tGuiThemeMsg.pWindow,&fTrg,Color);
//	UI_vline(tGuiThemeMsg.pWindow,(POINT *)&fTrg,pRect->width,Color);
	fTrg.top = pRect->top+pRect->height-Width;
	UI_FillRectSingLe(tGuiThemeMsg.pWindow,&fTrg,Color);
//	UI_vline(tGuiThemeMsg.pWindow,(POINT *)&fTrg,pRect->width,Color);
	fTrg.top = pRect->top+Width;
	fTrg.width = Width;
	fTrg.height= pRect->height-2*Width;
	UI_FillRectSingLe(tGuiThemeMsg.pWindow,&fTrg,Color);
//	UI_hline(tGuiThemeMsg.pWindow,(POINT *)&fTrg,fTrg.height,Color);
	fTrg.left = pRect->left+pRect->width-Width;
	UI_FillRectSingLe(tGuiThemeMsg.pWindow,&fTrg,Color);
//	UI_hline(tGuiThemeMsg.pWindow,(POINT *)&fTrg,fTrg.height,Color);
}




//==========width -> left ======height -> top======================
void API_GetALignLeftTop(u32 tTextType,RECTL *pRect)
{
	switch(tTextType&TEXT_ALIGN_MASK)
	{
		case TEXT_ALIGN_RIGHT:	//右对齐tIdle.rThis
			pRect->left=tGuiThemeMsg.width-pRect->width;
			break;
		case TEXT_ALIGN_CENTER: 	//左右居中
			pRect->left=(tGuiThemeMsg.width-pRect->width)/2;
			break;
		default ://case 0:	//左对齐
			pRect->left=0;
		//	break;
	}
	if(tTextType&TEXT_LINE_NUM_MASK)
	{//-----------指定行号(1~15)----------
		u16 max,line=(tTextType&TEXT_LINE_NUM_MASK)/0x10000 - 1;
		max = tGuiThemeMsg.hcont/(tTextType&TEXT_SIZE);
		if(line < max)
			pRect->top=tGuiThemeMsg.htitle + line*(tTextType&TEXT_SIZE);
		else
			pRect->top=tGuiThemeMsg.htitle + (max-1)*(tTextType&TEXT_SIZE);
		/*
		if(line < tGuiThemeMsg.hn)
			pRect->top=tGuiThemeMsg.htitle + line*tGuiThemeMsg.hmc;// + (tGuiThemeMsg.hmc-(tTextType&TEXT_SIZE))/2;
		else
			pRect->top=tGuiThemeMsg.hn-1;
		*/
	}
	else switch(tTextType&TEXT_VALIGN_MASK)
	{
		case TEXT_VALIGN_BOTTOM:	//下对齐
			pRect->top=tGuiThemeMsg.htitle + tGuiThemeMsg.hcont-pRect->height;
			break;
		case TEXT_VALIGN_CENTER:	//上下居中
			pRect->top=tGuiThemeMsg.htitle +(tGuiThemeMsg.hcont-pRect->height)/2;
			break;
		default:		//上对齐
			pRect->top=tGuiThemeMsg.htitle;
		//	break;
	}
}

//================================================================

void API_GUI_Show(void)
{
	UI_Push(tGuiThemeMsg.pWindow,NULL);
}

int  API_GUI_CreateWindow(const char* pTitle,const char* pOk,const char* pCancel,FunFillColour fBackColour)
{
	int ret;
	ret=API_Set_Background(fBackColour);
	if(ret < 0)
	{
		LOG(LOG_INFO,"Set_Background [%d] ERR\r\n",ret);
		return ret;
	}
	if(pTitle!=NULL)
	{
		//-------------------显示标题--------------------------------
		POINT	tFontXY;
		int 	sWidth;
		sWidth=API_strlen(pTitle)*tGuiThemeMsg.hfont/2;
		if(sWidth > tGuiThemeMsg.width)
			tFontXY.left=0;
		else
			tFontXY.left=(tGuiThemeMsg.width-sWidth)/2;
		tFontXY.top =(tGuiThemeMsg.htitle - tGuiThemeMsg.hfont)/2;
		UI_SetFontColor(tGuiThemeMsg.titleFclr,RGB565_CLEAR);
		UI_DrawLineString(tGuiThemeMsg.pWindow,&tFontXY,pTitle);
	}
	return 0;
}


int  API_GUI_Info(const IMAGE* pImg,u32 tTextType,const char* pTextBuf)
{
	RECTL tCoordinate={0};
	u16 sLen,offset,i,line,fontN,fontSize;
	fontSize=tTextType&TEXT_SIZE;
	if(fontSize==0)
	{//------没有字体加入默认字体-----------
		fontSize=tGuiThemeMsg.hfont;
		tTextType |= fontSize;
	}
	
	if(pImg)
	{
		tCoordinate.width=pImg->w;
		tCoordinate.height=pImg->h;
	}
	
	if(pTextBuf)
	{
		if(tCoordinate.width)
			fontN=tCoordinate.width*2/fontSize;
		else
			fontN=(tGuiThemeMsg.width*2/fontSize);
		sLen=API_strlen(pTextBuf);
		for(offset=0,line=0;line<10;line++)
		{
			if(offset >= sLen) break;
			for(i=0;i<fontN;i++)
			{
				if(pTextBuf[offset+i]=='\n')
				{
					i++;
					break;
				}
				if(pTextBuf[offset+i]&0x80)
				{
					if((i+1) >= fontN) break;
					i++;
				}
			}
			offset += i;
		}
		if(sLen > fontN)
			tCoordinate.width=tGuiThemeMsg.width;
		else
			tCoordinate.width=sLen*fontSize/2;
		tCoordinate.height=line*fontSize;
	}
	API_GetALignLeftTop(tTextType,&tCoordinate);
	
	if(tTextType&TEXT_EXSTYLE_BORDER)//加框
	{
		RECTL rect;
		if(tCoordinate.left>0&& tCoordinate.top>0)
		{
			rect.left=tCoordinate.left-1;
			rect.top=tCoordinate.top-1;
			rect.width=tCoordinate.width+2;
			rect.height=tCoordinate.height+2;
			API_GUI_ShowColorRect(&rect,1,RGB_CURR(30,30,30));
		}
	}
	else
	{
		POINT rclTrg;
		rclTrg.left=tCoordinate.left;
		if(tTextType&TEXT_EXSTYLE_UNDERLINE) //加下划线
		{
			rclTrg.top =tCoordinate.top+tCoordinate.height+1;
			UI_vline(tGuiThemeMsg.pWindow,&rclTrg,tCoordinate.width,RGB_CURR(30,30,30));
		}
		if(tTextType&TEXT_EXSTYLE_OVERLINE)//加上划线
		{
			rclTrg.top =tCoordinate.top-1;
			UI_vline(tGuiThemeMsg.pWindow,&rclTrg,tCoordinate.width,RGB_CURR(30,30,30));
		}
	}
	
	if(pImg)
	{
	//	DisplayBitMap(&tCoordinate,(LPBYTE)pImg->idata);
	}
	if(pTextBuf)
	{
		if(fontSize == FONT_SIZE)
		{
			ApiFont.SetFontColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
			ApiFont.DrawRectString(tGuiThemeMsg.pWindow,&tCoordinate,pTextBuf);
		}
		else
		{
			UI_SetSysEnColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
			UI_DisplaySysEn(tGuiThemeMsg.pWindow,tCoordinate.left,tCoordinate.top,fontSize,(char*)pTextBuf);
		}
	}
	return 0;
}

void API_GUI_Edit_Prompt(u32 tFrontTextType,char* pFrontTextBuf,u32 tAfterTextType,char* pAfterTextBuf)
{
	if(pFrontTextBuf)
		API_GUI_Info(NULL,tFrontTextType|TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE,pFrontTextBuf);
	if(pAfterTextBuf)
		API_GUI_Info(NULL,tFrontTextType|TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,pAfterTextBuf);
}

typedef struct {
	u32		Limit,Way;		//控制不要输入法切换,IME_TYPE(多选),输入法,IME_TYPE(其中之一)
	Fun_ShowNum ShowNum;	//显示内容 (u32 flagPs,char* pStrNum)	bit31=1,init,bit0~bit7 showCode
	int		oldTimeMs;
	RECTL	Rect;
	u8		Min,Max;	//最小最大输入范围
	u8		KeyTimes,oldKey;
	u8		MaxS,MaskCode;
	u8		indexEdit,indexShow;	//当前输入长度与显示长度
	char	sEditBuff[64];

	char	*pShowInfo;
	char	*pAfterText;				//最后一行提示信息
	//int		InfoMax,InfoIndex,InfoOffset;
}UI_EDIT_MSG;

UI_EDIT_MSG tGuiEditMsg;


u32 API_UI_EditShow(u16 keyNum)
{
	int 	newTimeMs;
	u8		WayChange,i,KeyValABC;

	if(keyNum)
	{
		if(keyNum==K_IME)
		{//----切换输入法-----
			WayChange=0;
			for(i=1;i<8;i++)
			{
				if((tGuiEditMsg.Way<<i) & (tGuiEditMsg.Limit&0xff))
				{
					tGuiEditMsg.Way <<= i;
					WayChange=1;
					break;
				}
			}
			if(i == 8)
			{
				while(--i)
				{
					if((tGuiEditMsg.Way>>i) & (tGuiEditMsg.Limit&0xff))
					{
						tGuiEditMsg.Way >>= i;
						WayChange=1;
						break;
					}
				}
			}
			if(WayChange)
			{
				if(tGuiEditMsg.Way==IME_NUM)
				{
					API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,STR_KEY_INPUT_NUMBER);
				}
				else if(tGuiEditMsg.Way==IME_abc)
				{
					API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,KEY_INPUT_LOWERCASE_LETTERS);
				}
				else if(tGuiEditMsg.Way==IME_ABC)
				{
					API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM,KEY_INPUT_UPPERCASE_LETTERS);
				}
				API_GUI_Show();
			}
		}
		else if(keyNum==K_DEL)
		{
			if(tGuiEditMsg.Way == IME_SUM)
				tGuiEditMsg.indexEdit=0;
			else if(tGuiEditMsg.indexEdit>0)
				tGuiEditMsg.indexEdit--;
		}
		else if((keyNum>=K_0 && keyNum<=K_9)||keyNum == K_D)
		{
			if(keyNum!=K_D && (tGuiEditMsg.Way&(IME_ABC|IME_abc)))
			{//---0~9 的数字转化------
				if(tGuiEditMsg.oldKey != keyNum)
				{
					tGuiEditMsg.oldKey=keyNum;
					newTimeMs=0;
					tGuiEditMsg.KeyTimes=0;
				}
				else 
				{
					newTimeMs = (int)OsGetTickCount();
					newTimeMs -= tGuiEditMsg.oldTimeMs;
					//LOG(LOG_INFO,"IME_ABC key[%d]oldTimeMs[%d]time[%d]\r\n",Message,oldTimeMs,newTimeMs);
					if(newTimeMs>700)
					{
						newTimeMs=0;
						tGuiEditMsg.KeyTimes=0;
					}
					else	//连续快按
					{
						newTimeMs=1;
						if(++tGuiEditMsg.KeyTimes >= API_strlen(KeyMsgABC[keyNum-K_0]))
							tGuiEditMsg.KeyTimes=0;
					}
				}
				tGuiEditMsg.oldTimeMs = (int)OsGetTickCount();
				KeyValABC=KeyMsgABC[keyNum-K_0][tGuiEditMsg.KeyTimes];
				if(tGuiEditMsg.Way == IME_abc)
				{//-------大写转小写----------
					if(KeyValABC>='A' && KeyValABC<='Z')
						KeyValABC |= 0x20;
				}
				if(newTimeMs)
				{//------短按改变原来值--------
					keyNum=KeyValABC;
					tGuiEditMsg.indexEdit--;
					tGuiEditMsg.indexShow--;//驱动显示
				}
				else
				{
					keyNum=KeyValABC;
				}
			}
			//---------------------------------------
			if(tGuiEditMsg.indexEdit < tGuiEditMsg.Max)
			{
				tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit++]=keyNum;
				if(tGuiEditMsg.Way == IME_SUM)
				{
					tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit]='\0';
					if(ChinaMoneyToCentInt(tGuiEditMsg.sEditBuff) < 0)
					{
						tGuiEditMsg.sEditBuff[--tGuiEditMsg.indexEdit]='\0';
						return EVENT_NONE;
					}
				}
				else if(tGuiEditMsg.Way == (IME_SUM|IME_NUM))
				{
					if(tGuiEditMsg.indexEdit==1 && tGuiEditMsg.sEditBuff[0]=='0')
					{
						tGuiEditMsg.sEditBuff[--tGuiEditMsg.indexEdit]='\0';
						return EVENT_NONE;
					}
					if(tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit-1]=='.')
					{
						tGuiEditMsg.sEditBuff[--tGuiEditMsg.indexEdit]='\0';
						return EVENT_NONE;
					}
				}
			}
			else
			{
				APP_HitMsg(STR_EDIT_FULL,1500);
			}
		}
	}
	//---------ShowSN--------------
	if(tGuiEditMsg.indexShow != tGuiEditMsg.indexEdit)
	{
		POINT	rclTrg;
		u8		sbuff[4]={0};
		//LOG(LOG_INFO,"API_UI_EditShow indexShow[%d],indexEdit[%d],keyNum[%d]\r\n",tGuiEditMsg.indexShow,tGuiEditMsg.indexEdit,keyNum);
		//---清除之前的内容------
		sbuff[0]=' ';//sbuff[0]='\0';
		while(tGuiEditMsg.indexShow > tGuiEditMsg.indexEdit)
		{
			tGuiEditMsg.indexShow--;
			if(tGuiEditMsg.indexShow >= tGuiEditMsg.MaxS)
			{
				rclTrg.top = tGuiEditMsg.Rect.top+FONT_SIZE;
				rclTrg.left = tGuiEditMsg.Rect.left+(tGuiEditMsg.indexShow-tGuiEditMsg.MaxS)*FONT_SIZE/2;
			}
			else
			{
				rclTrg.top = tGuiEditMsg.Rect.top;
				rclTrg.left = tGuiEditMsg.Rect.left+(tGuiEditMsg.indexShow)*FONT_SIZE/2;
			}
			ApiFont.SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
			//LOG(LOG_INFO,"API_UI_EditShow top[%d],left[%d],sbuff[%S]\r\n",rclTrg.top,rclTrg.left,sbuff);
			ApiFont.DisplayFont(tGuiThemeMsg.pWindow,&rclTrg,sbuff);
		}
		while(tGuiEditMsg.indexShow < tGuiEditMsg.indexEdit)
		{
			if(tGuiEditMsg.indexShow >= tGuiEditMsg.MaxS)
			{
				rclTrg.top = tGuiEditMsg.Rect.top+FONT_SIZE;
				rclTrg.left = tGuiEditMsg.Rect.left+(tGuiEditMsg.indexShow-tGuiEditMsg.MaxS)*FONT_SIZE/2;
			}
			else
			{
				rclTrg.top = tGuiEditMsg.Rect.top;
				rclTrg.left = tGuiEditMsg.Rect.left+(tGuiEditMsg.indexShow)*FONT_SIZE/2;
			}
			ApiFont.SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
			if(tGuiEditMsg.MaskCode)
				sbuff[0]=tGuiEditMsg.MaskCode;
			else
				sbuff[0]=tGuiEditMsg.sEditBuff[tGuiEditMsg.indexShow];
			//LOG(LOG_INFO,"API_UI_EditShow top[%d],left[%d],sbuff[%S]\r\n",rclTrg.top,rclTrg.left,sbuff);
			ApiFont.DisplayFont(tGuiThemeMsg.pWindow,&rclTrg,sbuff);
			tGuiEditMsg.indexShow++;
		}
		if(keyNum) API_GUI_Show();
		tGuiEditMsg.sEditBuff[tGuiEditMsg.indexShow]='\0';	//增加结束符号
	}
	return EVENT_NONE;
}



void API_GUI_Edit(u32 tTextType,char* pTextDef,int tMaxLen,u32 tImeType,u32 tImeLimit)
{
	tGuiEditMsg.Rect.width= tGuiThemeMsg.width -tGuiThemeMsg.hfont*2+8;
	tGuiEditMsg.Rect.height= tGuiThemeMsg.hfont*2+8;
	tGuiEditMsg.Rect.left	= tGuiThemeMsg.hfont-4;
	tGuiEditMsg.Rect.top	= tGuiThemeMsg.htitle+(tGuiThemeMsg.hcont-tGuiEditMsg.Rect.height)/2;
	API_GUI_ShowColorRect(&tGuiEditMsg.Rect,1,RGB_CURR(192,192,192));
	tGuiEditMsg.Rect.width	= tGuiThemeMsg.width-tGuiThemeMsg.hfont*2;
	tGuiEditMsg.Rect.height = tGuiThemeMsg.hfont*2;
	tGuiEditMsg.Rect.left	= tGuiThemeMsg.hfont;
	tGuiEditMsg.Rect.top	= tGuiThemeMsg.htitle+(tGuiThemeMsg.hcont-tGuiEditMsg.Rect.height)/2;;
	tGuiEditMsg.MaxS=(tGuiEditMsg.Rect.width*2/tGuiThemeMsg.hfont);
	if(tMaxLen > 32) tMaxLen = 32;
	tGuiEditMsg.Max=tMaxLen;
	tGuiEditMsg.Way=tImeType&IME_MASK;
	tGuiEditMsg.Limit=tImeLimit&IME_MASK;
	if(tGuiEditMsg.Way == IME_SUM)
		ChinaTmoneyToDmoney(tGuiEditMsg.sEditBuff,pTextDef);
	else 
		API_strcpy(tGuiEditMsg.sEditBuff,pTextDef);
		
	tGuiEditMsg.indexEdit= API_strlen(tGuiEditMsg.sEditBuff);//初始长度
	tGuiEditMsg.indexShow=0;
	//---------------------------------------------------
	if(tImeType&IME_PIN_MODE)
		tGuiEditMsg.MaskCode='*';
	else
		tGuiEditMsg.MaskCode=0x00;
	tGuiEditMsg.KeyTimes=0;
	//---------------------------------------------------
	tWaitEventMsg.pFunEvenKey=&API_UI_EditShow;
	API_UI_EditShow(0);
}

u32 API_UI_OprInfo(u16 keyNum)
{
	if(keyNum)
	{
		if(keyNum==K_UP || keyNum==K_8)
		{
			if(tGuiEditMsg.Way)
			{
				tGuiEditMsg.Way=0;
				API_GUI_ClearScreen(&tGuiEditMsg.Rect);
				ApiFont.SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
				tGuiEditMsg.oldTimeMs=ApiFont.DrawRectString(tGuiThemeMsg.pWindow,&tGuiEditMsg.Rect,tGuiEditMsg.pShowInfo + tGuiEditMsg.Way);
			}
		}
		else if(keyNum==K_DOWN || keyNum==K_0)
		{
			if((tGuiEditMsg.Way+tGuiEditMsg.oldTimeMs) < tGuiEditMsg.Limit)
			{
				tGuiEditMsg.Way += tGuiEditMsg.oldTimeMs;
				API_GUI_ClearScreen(&tGuiEditMsg.Rect);
				ApiFont.SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
				tGuiEditMsg.oldTimeMs=ApiFont.DrawRectString(tGuiThemeMsg.pWindow,&tGuiEditMsg.Rect,tGuiEditMsg.pShowInfo + tGuiEditMsg.Way);
			}
		}
	}
	else
	{
		tGuiEditMsg.Way = 0;
		tGuiEditMsg.Limit = API_strlen(tGuiEditMsg.pShowInfo); //初始长度
		ApiFont.SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
		tGuiEditMsg.oldTimeMs=ApiFont.DrawRectString(tGuiThemeMsg.pWindow,&tGuiEditMsg.Rect,tGuiEditMsg.pShowInfo);
		if((tGuiEditMsg.pAfterText!=NULL)&&(tGuiEditMsg.oldTimeMs<tGuiEditMsg.Limit))
		{
			POINT rclTrg;
			u16 width;
			width=API_strlen(tGuiEditMsg.pAfterText)*FONT_SIZE/2;
			if(width<tGuiEditMsg.Rect.width)
				rclTrg.left =tGuiEditMsg.Rect.width-width;
			else 
				rclTrg.left =tGuiEditMsg.Rect.left;
			rclTrg.top =tGuiEditMsg.Rect.top+tGuiEditMsg.Rect.height;
			UI_vline(tGuiThemeMsg.pWindow,&rclTrg,width,RGB_CURR(30,30,30));
			UI_SetFontColor(FONT_CONT_COLOUR,UI_CONT_COLOUR);
			UI_DrawLineString(tGuiThemeMsg.pWindow,&rclTrg,tGuiEditMsg.pAfterText);
		}
	}
	API_GUI_Show();
	return EVENT_NONE;
}

void API_GUI_OprInfo(char* pShowInfo,char *pAfterText)
{
	tGuiEditMsg.Rect.left	= 0;
	tGuiEditMsg.Rect.top	= tGuiThemeMsg.htitle;
	tGuiEditMsg.Rect.width= tGuiThemeMsg.width;
	if(pAfterText)
		tGuiEditMsg.Rect.height=tGuiThemeMsg.hcont-tGuiThemeMsg.hfont;
	else
		tGuiEditMsg.Rect.height=tGuiThemeMsg.hcont;
	
	tGuiEditMsg.pShowInfo	= pShowInfo;
	tGuiEditMsg.pAfterText	= pAfterText;
	//---------------------------------------------------
	tWaitEventMsg.pFunEvenKey=&API_UI_OprInfo;
	API_UI_OprInfo(0);
}

int API_GUI_Edit_GetText(char* pAscText,int tMaxLen)
{
	tMaxLen--;
	if(tMaxLen < tGuiEditMsg.indexShow)
		return -1;
	if(tGuiEditMsg.Way==IME_SUM)
	{
		ChinaDmoneyToTmoney(pAscText,tGuiEditMsg.sEditBuff);
	}
	else
	{
		API_strcpy(pAscText,tGuiEditMsg.sEditBuff);
	}
	return API_strlen(pAscText);
}
//=========================================================================================
typedef struct {
	//u32 	tMenuType;
	//XuiWindow *pWindow;
	void 	(*ShowItem)(void *,int,int,char*);
	void*	pMenu;	//菜单内容
	char*	pAfterText;	//最后一行显示
	u8		tCurInx,showInx;
	u8		tCurHead,showHead;
	u8		tNum;
	u8		ShowState,KeyFunEn;
//	u16		width,ht,hc,hn;//菜单宽度，标题高度，内容高度，行数
}UI_MENU_MSG;





static UI_MENU_MSG tGuiMenuMsg={0};

u32 API_UI_MenuShow(u16 keyNum)
{
	u16 i,MaxLine;
	MaxLine=tGuiThemeMsg.hn;
	if(tGuiMenuMsg.pAfterText) MaxLine--;
		
	if(keyNum)
	{
		if(keyNum>=K_1 && keyNum<(K_1+MaxLine))
		{
			keyNum -= K_1;
			if((tGuiMenuMsg.tCurHead+keyNum) >= tGuiMenuMsg.tNum)
				return EVENT_NONE;
			tGuiMenuMsg.tCurInx=(tGuiMenuMsg.tCurHead+keyNum);
			return EVENT_INDEX;
		}
		else if(keyNum==K_UP || keyNum==(K_1+MaxLine))
		{
			if(tGuiMenuMsg.tCurHead >= MaxLine)
				tGuiMenuMsg.tCurHead -= MaxLine;
			else if(tGuiMenuMsg.tCurHead > 0)
				tGuiMenuMsg.tCurHead=0;
			else
				return EVENT_NONE;
		}
		else if(keyNum==K_DOWN || keyNum==K_0)
		{
			if((tGuiMenuMsg.tCurHead+MaxLine) < tGuiMenuMsg.tNum)
				tGuiMenuMsg.tCurHead += MaxLine;
			else
				return EVENT_NONE;
		}
		else if(keyNum == K_FUNC)
		{
			if(tGuiMenuMsg.KeyFunEn)
				return (EVENT_KEY|K_FUNC);
		}
	}
	//----------------------------------------------------------
	//if(tGuiMenuMsg.ShowState)
	{//----------显示菜单--------
		POINT tFontXY;
		tFontXY.left = 4;
		tFontXY.top =tGuiThemeMsg.htitle + (tGuiThemeMsg.hmc -tGuiThemeMsg.hfont)/2;
		for(i=0;i<tGuiThemeMsg.hn;i++)
		{
			if(i >= MaxLine) break;
			//-------------------显示菜单项--------------------------------
			if((tGuiMenuMsg.tCurHead+i) < tGuiMenuMsg.tNum)
			{
				char sBuff[32];
				tGuiMenuMsg.ShowItem(tGuiMenuMsg.pMenu,tGuiMenuMsg.tCurHead+i,i+1,sBuff);
				ApiFont.SetFontColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
				ApiFont.DrawLineString(tGuiThemeMsg.pWindow,&tFontXY,sBuff);
			}
			tFontXY.top  += tGuiThemeMsg.hmc;
		}
		if(tGuiMenuMsg.pAfterText)
		{
			int tLenW=API_strlen(tGuiMenuMsg.pAfterText)*tGuiThemeMsg.hfont/2;
			if(tLenW < tGuiThemeMsg.width)
				tFontXY.left=tGuiThemeMsg.width-tLenW;
			else
			{
				tFontXY.left=0;
				tLenW = tGuiThemeMsg.width;
			}
			tFontXY.top= tGuiThemeMsg.hcont - tGuiThemeMsg.hmc + (tGuiThemeMsg.hmc-tGuiThemeMsg.hfont)/2;;
			UI_vline(tGuiThemeMsg.pWindow,&tFontXY,tLenW,RGB_CURR(30,30,30));
			tFontXY.top++;tFontXY.top++;
			ApiFont.SetFontColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
			ApiFont.DrawLineString(tGuiThemeMsg.pWindow,&tFontXY,tGuiMenuMsg.pAfterText);
		}
		UI_Push(tGuiThemeMsg.pWindow,NULL);
	}
	return EVENT_NONE;
}

int API_GUI_Menu_GetInx(void)
{
	return tGuiMenuMsg.tCurInx;
}


int API_GUI_Menu_GetInxAndHear(int* tHead)
{
	if(tHead)
		*tHead=tGuiMenuMsg.tCurHead;
	return tGuiMenuMsg.tCurInx;
}

int API_GUI_Menu(void* pMenu,void (*pShowItem)(void *,int,int,char*),int tNum,int tCurInx,int tHead,char* pAfterText,void* KeyFunEn)
{
	tGuiMenuMsg.tNum=tNum;
	tGuiMenuMsg.tCurInx=tCurInx;
	tGuiMenuMsg.showInx=0xff;
	tGuiMenuMsg.tCurHead=tHead;
	tGuiMenuMsg.showHead=0xff;
	tGuiMenuMsg.pAfterText=pAfterText;
	if(KeyFunEn)
		tGuiMenuMsg.KeyFunEn=TRUE;
	else 
		tGuiMenuMsg.KeyFunEn=FALSE;
	tGuiMenuMsg.pMenu=pMenu;
	tGuiMenuMsg.ShowItem=pShowItem;

	//-----------------------------------------------------
	API_UI_MenuShow(0);
	tWaitEventMsg.pFunEvenKey=&API_UI_MenuShow;
	return 0;
}



//========================输入==============================================
u32 API_UI_InputEdit(u16 keyNum)
{
	if(keyNum)
	{
		if(keyNum==K_IME)
		{
			if(tGuiEditMsg.Way < tGuiEditMsg.Limit)
			{//----切换输入法-----
				u32 i,WayChange=tGuiEditMsg.Way;
				for(i=1;i<8;i++)
				{
					if((WayChange<<i) & (tGuiEditMsg.Limit&0xff))
					{
						WayChange <<= i;
						break;
					}
				}
				if(i == 8)
				{
					while(--i)
					{
						if((tGuiEditMsg.Way>>i) & (tGuiEditMsg.Limit&0xff))
						{
							WayChange >>= i;
							break;
						}
					}
				}
				if(WayChange != tGuiEditMsg.Way)
				{
					tGuiEditMsg.Way=WayChange;
					tGuiEditMsg.ShowNum(WayChange,NULL);
					API_GUI_Show();
				}
			}
		}
		else if(keyNum==K_DEL)
		{
			if(tGuiEditMsg.indexEdit)
			{
				if(tGuiEditMsg.Way & IME_SUM)
					tGuiEditMsg.indexEdit=0;
				else
					tGuiEditMsg.indexEdit--;
			}
			tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit]='\0';
			tGuiEditMsg.ShowNum(tGuiEditMsg.MaskCode,tGuiEditMsg.sEditBuff);
			API_GUI_Show();
			tGuiEditMsg.indexShow=tGuiEditMsg.indexEdit;
		}
		else if((keyNum>=K_0 && keyNum<=K_9) || keyNum==K_D)
		{	
			if(keyNum==K_D && tGuiEditMsg.Way == (IME_SUM|IME_NUM))	// 金客加数字 屏蔽小数点
				return EVENT_NONE;
			if(keyNum!=K_D && (tGuiEditMsg.Way&(IME_ABC|IME_abc)))
			{//---0~9 的数字转化--多输入法输入----
				unsigned long	newTimeMs;
				u8				KeyValABC;
				if(tGuiEditMsg.oldKey != keyNum)
				{
					tGuiEditMsg.oldKey=keyNum;
					newTimeMs=0;
					tGuiEditMsg.KeyTimes=0;
				}
				else 
				{
					newTimeMs= (int)OsGetTickCount();
					newTimeMs -= tGuiEditMsg.oldTimeMs;
					if(newTimeMs>700)
					{
						newTimeMs=0;
						tGuiEditMsg.KeyTimes=0;
					}
					else	//连续快按
					{
						newTimeMs=1;
						if(++tGuiEditMsg.KeyTimes >= API_strlen(KeyMsgABC[keyNum-K_0]))
							tGuiEditMsg.KeyTimes=0;
					}
				}
				tGuiEditMsg.oldTimeMs=(int)OsGetTickCount();
				KeyValABC=KeyMsgABC[keyNum-K_0][tGuiEditMsg.KeyTimes];
				if(tGuiEditMsg.Way == IME_abc)
				{//-------大写转小写----------
					if(KeyValABC>='A' && KeyValABC<='Z')
						KeyValABC |= 0x20;
				}
				if(newTimeMs)
				{//------短按改变原来值--------
					tGuiEditMsg.indexEdit--;
					tGuiEditMsg.indexShow--;//驱动显示
				}
				keyNum=KeyValABC;
			}
			
			if(tGuiEditMsg.indexEdit < tGuiEditMsg.Max)
			{
				tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit++]=keyNum;
				tGuiEditMsg.sEditBuff[tGuiEditMsg.indexEdit]='\0';
				if(tGuiEditMsg.Way == IME_SUM)
				{
					if(ChinaMoneyToCentInt(tGuiEditMsg.sEditBuff) < 0)
					{
						tGuiEditMsg.sEditBuff[--tGuiEditMsg.indexEdit]='\0';
						return EVENT_NONE;
					}
				}
				else if(tGuiEditMsg.Way == (IME_SUM|IME_NUM))
				{
					if(tGuiEditMsg.indexEdit==1 \
						&&tGuiEditMsg.sEditBuff[0]=='0')
					{
						tGuiEditMsg.sEditBuff[--tGuiEditMsg.indexEdit]='\0';
						return EVENT_NONE;
					}
				}
				tGuiEditMsg.ShowNum(tGuiEditMsg.MaskCode,tGuiEditMsg.sEditBuff);
				API_GUI_Show();
				tGuiEditMsg.indexShow=tGuiEditMsg.indexEdit;
			}
			else
			{
				APP_HitMsg(STR_EDIT_FULL,1500);
			}
		}
	}
	else
	{
		tGuiEditMsg.ShowNum(0x80000000|tGuiEditMsg.MaskCode,tGuiEditMsg.sEditBuff);
		API_GUI_Show();
	}
	return EVENT_NONE;
}

void API_GUI_InputEdit(char* pStrDef,int tMaxLen,u32 Way,Fun_ShowNum pShow)
{
	if(Way)
	{
		tGuiEditMsg.Max=tMaxLen;
		if(Way==IME_SUM)
			ChinaTmoneyToDmoney(tGuiEditMsg.sEditBuff,pStrDef);
		else
			API_strcpy(tGuiEditMsg.sEditBuff,pStrDef);

		tGuiEditMsg.indexShow=API_strlen(tGuiEditMsg.sEditBuff);
		if(Way|IME_SUM)
			tGuiEditMsg.indexEdit=0;	//需要重新输入
		else
			tGuiEditMsg.indexEdit=tGuiEditMsg.indexShow;
		//----------------兼容多种输入法-----------------------------------
		tGuiEditMsg.Limit=Way;
		{//--检查多输入法----
			u32 i,j,cWay=IME_NUM;
			for(j=0,i=0;i<4;i++)
			{
				if(cWay&Way)
					j++;
				cWay <<= 1;
			}
			if(j>1)
			{
				for(cWay=IME_NUM,i=0;i<4;i++)
				{
					if(cWay&Way)
						break;
					cWay <<= 1;
				}
				Way &= (~(IME_NUM|IME_abc|IME_ABC|IME_Abc))|cWay;
			}
		}
		//---------------------------------------------------
		tGuiEditMsg.Way=Way;
		if(Way&IME_PIN_MODE)
			tGuiEditMsg.MaskCode='*';
		else tGuiEditMsg.MaskCode=0x00;
		tGuiEditMsg.ShowNum=pShow;
		//---------------------------------------------------
		tWaitEventMsg.pFunEvenKey=&API_UI_InputEdit;
		API_UI_InputEdit(0);
	}
	else
	{
		tWaitEventMsg.pFunEvenKey=&API_UI_InputEdit;
	}
}
//=======================================================================================


//----由于滚显示更新信息---pOriginal 原信息空间 Originalsize原信息空间大小--pAddMsg 新加信息------
void APP_ShowChangeInfo(char *pOriginal,int Originalsize,const char* format,...)
{
	u16 OriginalLen,AddMsgLen,i,offset=0;
	//u16 lineStart,LineMax,contMax;
	RECTL tRect;
	char pAddMsg[128];
	va_list arg;	
	va_start( arg, format);
	vsnprintf(pAddMsg,sizeof(pAddMsg),format,arg);
	va_end( arg );
	//-------------------------------------------------
	OriginalLen=API_strlen(pOriginal);
	AddMsgLen=API_strlen(pAddMsg);
	Originalsize--;
	while((OriginalLen+AddMsgLen) > Originalsize)
	{//-----信息内容已经满，需要清除前面行信息-------
		for(offset=0;offset<OriginalLen;offset++)
		{
			if(pOriginal[offset] == '\n')
			{
				offset++;//跳过'\n'
				break;
			}
		}
		if((offset == OriginalLen)&&(OriginalLen > (tGuiThemeMsg.width*2/tGuiThemeMsg.hfont)))
		{//---跳过(UI_CONT_W*2/FONT_SIZE)字节，避开半汉字------
			int flagHz=0;
			for(i=0;i<(tGuiThemeMsg.width*2/tGuiThemeMsg.hfont);i++)
			{
				if(pOriginal[i]&0x80)
				{
					if(flagHz==0)
						flagHz=1;
					else
						flagHz=0;
				}
			}
			offset=i-flagHz;
		}
		OriginalLen -= offset;
		for(i=0;i<OriginalLen;i++)
			pOriginal[i]=pOriginal[offset++];
		offset++;//作为标记屏刷新自加
	}
	for(i=0;i<=AddMsgLen;i++)
	{
		if((OriginalLen+i) > Originalsize) break;
		pOriginal[OriginalLen+i]=pAddMsg[i];
	}
	pOriginal[OriginalLen+i]='\0';	
	//----clear-----
	tRect.left=0; tRect.top=tGuiThemeMsg.htitle;
	tRect.width=tGuiThemeMsg.width; 
	tRect.height=tGuiThemeMsg.hcont;
	
	if(offset) API_GUI_ClearScreen(&tRect);	//清空区域
	ApiFont.SetFontColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
	ApiFont.DrawRectString(tGuiThemeMsg.pWindow,&tRect,pOriginal);
	API_GUI_Show();	
}

//====================================================
/*--------------
make a QR code and display it to lcd
---------------*/


//=============================================================================


int APP_WaitUiEvent(int tTimeOutMS)
{
	return API_WaitEvent(tTimeOutMS,EVENT_UI,EVENT_NONE);
}


void APP_ShowSta(char *pTitle,char *pMsg)
{
	API_GUI_CreateWindow(pTitle,NULL,NULL,API_FillShowBack);
	API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER,pMsg);
	API_GUI_Show();
}

int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs)
{
	APP_ShowSta(pTitle,pMsg);
	return APP_WaitUiEvent(timeOutMs);
}

int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs)
{
	API_GUI_CreateWindow(pTitle,TOK,TCANCEL,API_FillShowBack);
	API_GUI_OprInfo(pInfo,NULL);
	API_GUI_Show();
	return APP_WaitUiEvent(timeOutMs);
}


int APP_ShowQrCode(char *pTitle,const char* pInfo,A_RGB Color)
{
	RECTL tRect;
	API_GUI_CreateWindow(pTitle,NULL,NULL,API_FillShowBack);
	tRect.left=0;
	tRect.top= tGuiThemeMsg.htitle;
	tRect.width = tGuiThemeMsg.width;
	tRect.height= tGuiThemeMsg.hcont;
	UI_ShowQrCode(tGuiThemeMsg.pWindow,&tRect,pInfo,Color);
	API_GUI_Show();
	return 0;
}



int APP_HitMsg(const char* pMsg,int tTimeOutMS)
{
	int ret,minW;
	XuiWindow *babyWindow,*pCurrWindow;
	minW =FONT_SIZE + strlen(pMsg)*FONT_SIZE/2;
		
	pCurrWindow = API_GUI_GetCurrWindow();
	if(minW > pCurrWindow->width) 
		return -1;
	
	babyWindow = XuiCreateCanvas(pCurrWindow,(pCurrWindow->width-minW)/2,(pCurrWindow->height-60)/2,minW,60);
	//------------babyWindow---------------------------
	UI_SetBackground(babyWindow,UI_FillHitBack);
	UI_ShowBackground(babyWindow);
	UI_SetFontColor(RGB565_BLACK,RGB565_CLEAR);	//(RGB565_RED|RGB565_GREEN,RGB565_PARENT)
	UI_DrawCenterString(babyWindow,(char*)pMsg);
	UI_Push(babyWindow,NULL);
	ret= APP_WaitUiEvent(tTimeOutMS);
	//-------------------------------------------	
	XuiDestroyWindow(babyWindow);
	return ret;
}


int APP_GUI_Menu(char* pTitle,int stratIndex,int tNum,int tCurInx,char** pMenuText)
{
	POINT tFontXY;
	char sBuff[32+2];
	u16 i;
	//-------------------显示标题--------------------------------
	API_GUI_CreateWindow(pTitle,NULL,NULL,API_FillMenuBack);
	//-------------------显示菜单项--------------------------------
	//tGuiThemeMsg.hmc;
	tFontXY.top =tGuiThemeMsg.htitle + (tGuiThemeMsg.hmc-tGuiThemeMsg.hfont)/2;
	tFontXY.left = 4;
	for(i=0; i<tGuiThemeMsg.hn; i++)
	{
		if((stratIndex+i) >= tNum)
			break;
		API_sprintf(sBuff,"%d.%s",1+stratIndex+i,pMenuText[stratIndex+i]);
		if((stratIndex+i)==tCurInx)
			ApiFont.SetFontColor(RGB565_SELE_FONT,RGB565_CLEAR);
		else
			ApiFont.SetFontColor(tGuiThemeMsg.contFclr,RGB565_CLEAR);
		ApiFont.DrawLineString(tGuiThemeMsg.pWindow,&tFontXY,sBuff);

		tFontXY.top += tGuiThemeMsg.hmc;
	}
	API_GUI_Show();
	return 0;
}

//=============底部显示进度条==ratio(0~100)===============================
void APP_ShowBottomProgress(int ratio)
{
	RECTL tRect;
	tRect.width=tGuiThemeMsg.pWindow->width;
	tRect.left = 0; 
	tRect.height=16;
	tRect.top = tGuiThemeMsg.pWindow->height-tRect.height;
	UI_ShowBottomProgress(tGuiThemeMsg.pWindow,&tRect,3,ratio);
	UI_Push(tGuiThemeMsg.pWindow,&tRect);
}
	
//=============显示滑轨==ratio(0~100)===============================
/*
void APP_ShowParMiddleSlide(int ratio)
{
	UI_ShowParMiddleSlide(tGuiThemeMsg.pWindow,ratio);
	ret=API_sprintf(sbuff,"%d",par);
	tRect.left = SCREEN_APP_X+(SCREEN_APP_W-ret*FONT_SIZE/2)/2;
	tRect.top = SCREEN_APP_Y+ (SCREEN_APP_H-32)/2  +32;
	ApiFont.SetFontColor(RGB_CURR(56,56,56),RGB_CURR(255,255,255));
	ApiFont.DisplayFont(tGuiThemeMsg.pWindow,&tRect,(u8*)sbuff);
	DisplayPaintEnd();	
}
*/


//=============数字显示函数===========服务倒计时==================
void APP_ShowNumberL(RECTL *pRect,int num)
{
	char showbuff[12];
	int slen=sizeof(showbuff);
	int wlen=pRect->width/(pRect->height/2);
	showbuff[--slen]='\0';
	while(wlen--)
	{
		showbuff[--slen]=num%10+'0';
		num /=10;
	}
	if(pRect->height == FONT_SIZE)
		UI_DrawRectString(tGuiThemeMsg.pWindow,pRect,showbuff+slen);
	else
		UI_DisplaySysEn(tGuiThemeMsg.pWindow,pRect->left,pRect->top,pRect->height,showbuff+slen);
	UI_Push(tGuiThemeMsg.pWindow,pRect);
}
//================倒计时显示=================
static RECTL rgTimeRect;
static int ShowTimeS,SeedTimeS;
//===============设置倒计时相对位置=与初值时间=======================================
void gShowTimeS_SetInit(u32 tTextType,int len,int timeS)
{
	u16 fontSize;
	SeedTimeS=(int)time(NULL);
	ShowTimeS =SeedTimeS+ timeS;
	if(len > 11) len=11;
	fontSize=tTextType&TEXT_SIZE;
	if(fontSize==0)
	{//------没有字体加入默认字体-----------
		fontSize=tGuiThemeMsg.hfont;
		tTextType |= fontSize;
	}
	rgTimeRect.width=len*fontSize/2;
	rgTimeRect.height=fontSize;
	API_GetALignLeftTop(tTextType,&rgTimeRect);
	APP_ShowNumberL(&rgTimeRect,timeS);
}


int gShowTimeS_GetOut(void)
{
	int CurrSec;
	CurrSec=(int)time(NULL);
	if(SeedTimeS!= CurrSec)
	{
		if(((int)CurrSec- (int)ShowTimeS) >= 0)
			return EVENT_TIMEOUT;//EVENT_TIMEOUT;
		SeedTimeS=CurrSec;
		API_GUI_ClearScreen(&rgTimeRect);
		APP_ShowNumberL(&rgTimeRect,ShowTimeS-SeedTimeS);
	}
	return 0;//EVENT_NONE;
}



/*
const API_GUI_Def ApiGUI={
	{'G','U','I',26},
	
};
*/
