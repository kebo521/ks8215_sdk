//============================================================
//---显示功能---
#include <unistd.h>
//#include <stdarg.h>
#include <fcntl.h>
#include <sys/time.h>
#include <linux/input.h>

#include "comm_type.h"

#include "xui_ui.h"
#include "xui_fb.h"
//#include "xui_font.h"
#include "xui_gui.h"
//#include "EvenMsg.h"
#include "QR_Encode.h"
#include "input_hand.h"
#include "sdk/sys_sdk.h"




//XuiWindow UI_screen = {0};
gUi_def gUiDataAll={0};


void argbset(A_RGB *u1,A_RGB nun,int len)
{
	while(len--)
		*u1++ = nun;
}
//================sys_sdk 提供=========================
//extern char *eStrstr(char* src1, const char* src2);

/*
//========从src1中查找src2字段=返回匹配src1中的末端地址=======
char *API_eStrstr(char* src1, const char* src2)
{
	unsigned char *pS1,*pS2;
	//if(src1==NULL || src2==NULL) return NULL;
	pS1=(unsigned char*)src1;
	pS2=(unsigned char*)src2;
	while(*pS1)
	{
		if(*pS1 != *pS2)
		{
			if(pS2 != (unsigned char*)src2)
			{
				pS2=(unsigned char*)src2;
				pS1=(unsigned char*)src1;
			}
			else pS1++;
		}
		else
		{
			pS1++; 
			if(pS2 == (unsigned char*)src2) //记录串1起点(src1+1)
				src1=(char*)pS1;
			pS2++;
			if(*pS2 == '\0')
				return (char*)pS1;
		}
	}
	return NULL;
}
*/

//===========硬件到软件=====坐标转换=======================
void HSTransformCoord_0(u16 *pX,u16 *pY)
{
}
void HSTransformCoord_90(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = *pY;
	*pY = (gUiDataAll.tHardWindow.height - *pX);
	*pX = buff;
}
void HSTransformCoord_180(u16 *pX,u16 *pY)
{
	*pX = (gUiDataAll.tHardWindow.width - *pX);
	*pY = (gUiDataAll.tHardWindow.height - *pY);
}

void HSTransformCoord_270(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = (gUiDataAll.tHardWindow.width - *pY);
	*pY = *pX;
	*pX = buff;
}
//===========软件到硬件=====坐标转换=======================
void SHTransformCoord_0(u16 *pX,u16 *pY)
{
}
void SHTransformCoord_90(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = (gUiDataAll.tHardWindow.height - *pY);
	*pY = *pX;
	*pX = buff;
}
void SHTransformCoord_180(u16 *pX,u16 *pY)
{
	*pX = (gUiDataAll.tHardWindow.width - *pX);
	*pY = (gUiDataAll.tHardWindow.height - *pY);
}

void SHTransformCoord_270(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = *pY;
	*pY = (gUiDataAll.tHardWindow.width - *pX);
	*pX = buff;
}

	
//argv 支持的格式为
//FB=xxxxx /*framebuffer 设备节点（默认值"/dev/graphics/fb0"）*/
//INPUT=xxxx /*input 设备节点，可以多个（默认值/dev/keypad 和/dev/tp）。只有在应用不设置该参数时，按照默认值加载输入设备，当应用设置了该参数时，则只加载所设置的设备节点，比如如果仅设置这个参数为INPUT=/dev/tp，那么XUI 初始化时则只加载默认触摸屏输入，而不加载物理键盘，这就等于是屏蔽了物理按键输入*/
//ROTATE=xxx /*屏幕旋转(取值可为0，90，180，默认值0，设置不支持的值时均使用默认值）*/
//TSDEV=xxxx/*触摸屏设备节点，（默认值/dev/input/event2）*/
//STATUSBAR=xxx /*状态栏高度（0-64，默认值0，设置不支持的值时均使用默认值）*/
//示例：char *xui_argv[] = {"ROTATE=90","STATUSBAR=18"};
//XuiOpen(sizeof(xui_argv)/sizeof(xui_argv[0]), xui_argv);


int XuiOpen(int argc,char **argv)
{
	int i;
	char *pTag;
	for(i=0;i<argc;i++)
	{
		pTag=eStrstr(argv[i],"FB=");
		if(pTag)
		{
			gUiDataAll.Screen_fd=open_screen(pTag,1);
			if(gUiDataAll.Screen_fd < 0) 
			{
				LOG(LOG_INFO,"->main open screen ret NULL \r\n");
				return 2;
			}
			continue;
		}
		pTag=eStrstr(argv[i],"INPUT=");
		if(pTag)
		{
			//LOG(LOG_INFO,"Open Input[%d]\r\n",pTag);
			strcpy(gUiDataAll.sInput,pTag);
			if(gUiDataAll.sInput[0])
			{
				Start_HandInput();
			}
			continue;
		}
		pTag=eStrstr(argv[i],"ROTATE=");
		if(pTag)
		{
			gUiDataAll.iRotate=atoi(pTag);
			if(gUiDataAll.iRotate>270 ||(gUiDataAll.iRotate % 90))
			{
				gUiDataAll.iRotate=0;
			}
			//LOG(LOG_INFO,"gUiDataAll iRotate[%d]\r\n",gUiDataAll.iRotate);
			continue;
		}
		pTag=eStrstr(argv[i],"TSDEV=");
		if(pTag)
		{
			//LOG(LOG_INFO,"Open TSDEV[%d]\r\n",pTag);
			gUiDataAll.TsDev_fd = open(pTag,O_RDWR);  // O_RDONLY
			continue;
		}
		pTag=eStrstr(argv[i],"STATUSBAR=");
		if(pTag)
		{
			gUiDataAll.iStatusbar=atoi(pTag);
			if(gUiDataAll.iStatusbar > 64)
			{
				gUiDataAll.iStatusbar = 0;
			}
			//LOG(LOG_INFO,"Open iStatusbar[%d]\r\n",gUiDataAll.iStatusbar);
			continue;
		}
	}
	if(gUiDataAll.iRotate==0)
	{
		SetRotationAngle(XUI_ROTATE_0,&gUiDataAll.tHardWindow);
		gUiDataAll.fTransformCoord_HS=&HSTransformCoord_0;
		gUiDataAll.fTransformCoord_SH=&SHTransformCoord_0;
	}
	else if(gUiDataAll.iRotate==90)
	{
		SetRotationAngle(XUI_ROTATE_90,&gUiDataAll.tHardWindow);
		gUiDataAll.fTransformCoord_HS=&HSTransformCoord_90;
		gUiDataAll.fTransformCoord_SH=&SHTransformCoord_90;
	}
	else if(gUiDataAll.iRotate==180)
	{
		SetRotationAngle(XUI_ROTATE_180,&gUiDataAll.tHardWindow);
		gUiDataAll.fTransformCoord_HS=&HSTransformCoord_180;
		gUiDataAll.fTransformCoord_SH=&SHTransformCoord_180;
	}
	else if(gUiDataAll.iRotate==270)
	{
		SetRotationAngle(XUI_ROTATE_270,&gUiDataAll.tHardWindow);
		gUiDataAll.fTransformCoord_HS=&HSTransformCoord_270;
		gUiDataAll.fTransformCoord_SH=&SHTransformCoord_270;
	}
	return 0;
}

//关闭XUI
void XuiClose(void)
{
	if(gUiDataAll.sInput[0])
	{
		Stop_HandInput();
		gUiDataAll.sInput[0]=0;
	}
	if(gUiDataAll.TsDev_fd)
	{
		close(gUiDataAll.TsDev_fd);
	}
	if(gUiDataAll.Screen_fd < 0)
	{
		close_screen();
		free(gUiDataAll.tHardWindow.wBack);
	}
	memset(&gUiDataAll,0x00,sizeof(gUiDataAll));
}


//判断XUI 是否正在运行。
int XuiIsRunning(void)
{

	return 0;
}


//暂停XUI 运行。
int XuiSuspend(void)
{

	return 0;
}

//恢复XUI 运行
int XuiResume(void)
{

	return 0;
}

//XuiWindow *XuiRootCanvas(void);
#define FB_WIDTH	260
#define FB_HEIGHT	340

//获取根画布
XuiWindow *XuiRootCanvas(void)
{
	XuiWindow *Window;
	int width,height;
	if(gUiDataAll.Screen_fd < 0)
	{
		LOG(LOG_ERROR,"Xui Root Canvas Screen_fd=%d\r\n",gUiDataAll.Screen_fd);
		return NULL;
	}
	//-------------------------------------------
	width=gUiDataAll.tHardWindow.width;
	height= gUiDataAll.tHardWindow.height -gUiDataAll.iStatusbar;
	Window = (XuiWindow *)malloc(sizeof(XuiWindow) +  (height*width)*sizeof(A_RGB));
	if(Window==NULL)
	{
		LOG(LOG_ERROR,"InitRootCanvas malloc(%d) is NULL\r\n",sizeof(XuiWindow) +  (height*width)*sizeof(A_RGB));
		return NULL;
	}
	memset(Window,0x00,sizeof(XuiWindow));
	Window->left=gUiDataAll.tHardWindow.left;
	Window->top=gUiDataAll.tHardWindow.top + gUiDataAll.iStatusbar;
	Window->width = width;
	Window->height = height;
	Window->widget = (A_RGB*)((u8*)Window + sizeof(XuiWindow));	
	argbset(Window->widget,RGB565_CLEAR,height*width);
	//LOG(LOG_INFO,"InitRootCanvas [%X][%X]\r\n",(u32)Window,(u32)Window->widget);
	return Window;
}

//获取状态栏画布
XuiWindow *XuiStatusbarCanvas(void)
{
	XuiWindow *Window;
	u16 width,height;
	if(gUiDataAll.Screen_fd < 0)
	{
		LOG(LOG_ERROR,"Xui Status barCanvas .Screen_fd=%d\r\n",gUiDataAll.Screen_fd);
		return NULL;
	}
	width=gUiDataAll.tHardWindow.width;
	height= gUiDataAll.iStatusbar;
	Window = (XuiWindow *)malloc(sizeof(XuiWindow) +  (height*width)*sizeof(A_RGB));
	memset(Window,0x00,sizeof(XuiWindow));
	Window->left=gUiDataAll.tHardWindow.left;
	Window->top=gUiDataAll.tHardWindow.top;
	Window->width = width;
	Window->height = height;
	Window->widget = (A_RGB*)((u8*)Window + sizeof(XuiWindow));	
	argbset(Window->widget,RGB565_CLEAR,height*width);
	return Window;
}


XuiWindow *XuiCreateCanvas(XuiWindow *parent, unsigned int x, unsigned int y,unsigned int width, unsigned int height)
{
	XuiWindow *Window;
	if((x+width)> parent->width || (y+height)> parent->height)
		return NULL;
	Window = (XuiWindow *)malloc(sizeof(XuiWindow) + (height*width)*sizeof(A_RGB));
	memset(Window,0x00,sizeof(XuiWindow));
	Window->left=parent->left+ x;
	Window->top =parent->top + y;
	Window->width = width;
	Window->height = height;
	Window->pChild = parent;
	Window->widget = (A_RGB*)((u8*)Window + sizeof(XuiWindow)); 
	argbset(Window->widget,RGB565_CLEAR,height*width);

	if(parent->pParent==NULL)
	{
		parent->pParent = Window;
	}
	else
	{
		XuiWindow *pParentNext;
		pParentNext = parent->pParent;
		while(pParentNext->pNext)
		{
			pParentNext=pParentNext->pNext;
		}
		pParentNext->pNext = Window;
	}
	return Window;
}







/*
//创建字体
XuiFont *XuiCreateFont(char *fontfile,int index,XuiFontSet fontset);
{
	return NULL;
}

int XuiCanvasDrawText(XuiWindow *window,unsigned int x,unsigned int y,unsigned int height,XuiFont *font,XuiTextStyle textstyle,XuiColor fg,char *text)
{
	return 0;
}

*/
void UI_Push(XuiWindow *pWindow,RECTL *pRect)
{
	if(pRect == NULL)
		xui_fb_push((RECTL*)pWindow,pWindow->widget);
	else
		xui_window_push(pWindow,pRect,pWindow->widget);
	xui_fb_syn();
}


void XuiCanvasSetBackground(XuiWindow *pWindow,int bgstyle,void *img,A_RGB bg)
{
	u16 y,x;
	u16 width,height;
	A_RGB* pWidget;
	width	= pWindow->width;
	height = pWindow->height;
	free(pWindow->wBack);
	pWidget = (A_RGB*)malloc((height * width)*sizeof(A_RGB));
	if(img)
	{


	}
	else for (y = 0; y < height; y++) 
	{
		for(x=0; x<width; x++)
		{
			*pWidget++ = bg;
		}
	}
	xui_fb_push((RECTL*)pWindow,pWidget);
	//xui_window_push(pWindow,NULL,pWidget);
	xui_fb_syn();
	pWindow->wBack = pWidget;
}

//================================================================================================================
void FreeParentWindow(XuiWindow *window)
{
	XuiWindow *pNext;
	if(window->pParent)
	{
		FreeParentWindow(window->pParent);
		window->pParent = NULL;
	}
	while(window)
	{	
		pNext = window->pNext;
		free(window->wBack);
		free(window);
		window= pNext;
	}
}

void XuiDestroyWindow(XuiWindow *window)
{
	XuiWindow *pParent;
	pParent= window->pParent;
	if(window->pParent)
	{	
		FreeParentWindow(window->pParent);
	}
	if(window->pChild)
	{//-----拆链表------
		pParent=window->pChild;
		if(pParent->pParent != window)
		{
			pParent = pParent->pParent;
			while(pParent->pNext != window)
				pParent= pParent->pNext;
		}
		pParent->pNext=window->pNext;
	}
	
	if(window->pChild)
	{
		RECTL tRect;
		pParent=window->pChild;
		tRect.left = window->left - pParent->left;
		tRect.top= 	window->top - pParent->top;
		tRect.width= window->width;
		tRect.height= window->height;
		xui_window_push(pParent,&tRect,pParent->widget);
	}
	else if(window->wBack)
	{//-----根画布------
		xui_fb_push((RECTL*)window,window->wBack);
		//xui_window_push(window,NULL,window->wBack);
	}
	xui_fb_syn();
	free(window->wBack);
	free(window);
}

int XuiClearArea(XuiWindow *window, unsigned int x,unsigned int y, unsigned int width, unsigned int height)
{
	int i,j,w,h;
	int mWidth,mChildw;
	A_RGB *pBack,*pWidget;
	A_RGB *destin,*source;
	
	w = x + width;
	h = y + height;
	mWidth = window->width;
	pWidget = window->widget;
	if(window->wBack)
	{
		pBack = window->wBack;
		for (j = y; j < h; j++) 
		{
			mChildw = j*mWidth + x;
			source= pBack+mChildw;
			destin= pWidget+mChildw;
			for(i=x; i<w; i++)
			{
				*destin++ = *source++;
			}
		}
	}
	else if(window->pChild)
	{
		u16 xOff,yOff;
		xOff = window->left - window->pChild->left;
		yOff = window->top  - window->pChild->top;;
		pBack = window->pChild->widget;
		mChildw = window->pChild->width;
		for (j = y; j < h; j++) 
		{
			source=&pBack[(yOff+j)*mChildw + xOff+x];
			destin=&pWidget[j*mWidth + x];
			for(i=x; i<w; i++)
			{
				*destin++ = *source++;
			}
		}
	}
	else return -1;
/*
	{
		RECTL tRect;
		tRect.left = x;
		tRect.top=	y;
		tRect.width= width;
		tRect.height= height;
		xui_window_push(window,&tRect,window->widget);
	}*/
	return 0;
}


void XuiShowWindow(XuiWindow *window,int show, int flag)
{
	if(show == 1)
	{
		xui_fb_push((RECTL*)window,window->widget);
		//xui_window_push(window,NULL,window->widget);
	}
	else
	{
		if(window->pChild)
		{
			RECTL tRect;
			tRect.left = window->left;
			tRect.top=	window->top;
			tRect.width= window->width;
			tRect.height= window->height;
			window = window->pChild;
			tRect.left -= window->left;	//取相对位置
			tRect.top -= window->top;		//取相对位置
			xui_window_push(window,&tRect,window->widget);
		}
		else if(window->wBack)
		{
			xui_fb_push((RECTL*)window,window->wBack);
			//xui_window_push(window,NULL,window->wBack);
		}
	}
	xui_fb_syn();
}

void UI_FillHitBack(A_RGB* pBack,int w,int h)
{
	u16 sx,mx,sy,my;
	int i=5;
	sy=i;
	sx=i;
	my=h- sy*2;	
	mx=w- sx*2;
	//------------------------------------------------------
	i = sy*w;
	while(i--)
		*pBack++ = RGB_CURR(0xD8,0xE0,0xE0);

	while(my--)
	{
		i=sx;
		while(i--)
			*pBack++ = RGB_CURR(0xD8,0xE0,0xE0);

		i=mx;
		while(i--)
			*pBack++ = RGB_CURR(0xff,0xff,0x7f);

		i=sx;
		while(i--)
			*pBack++ = RGB_CURR(0xD8,0xE0,0xE0);
	}

	i = sy*w;
	while(i--)
		*pBack++ = RGB_CURR(0xD8,0xE0,0xE0);
}

void UI_SetBackground(XuiWindow *pWindow,FunFillColour pFillColour)	//(u32* pOut,int width,int height)
{
	if(pWindow->wBack == NULL)
		pWindow->wBack = (A_RGB*)malloc((pWindow->height * pWindow->width)*sizeof(A_RGB));
	pFillColour(pWindow->wBack,pWindow->width,pWindow->height);
}

void UI_ShowBackground(XuiWindow *pWindow)	
{
	int max;
	A_RGB *destin,*source;
	source = pWindow->wBack;
	if(source == NULL) return ;
	destin = pWindow->widget;
	max= pWindow->height * pWindow->width;
	while(max--)
		*destin++ = *source++;
}


void UI_vline(XuiWindow *pWindow,POINT *pRect,int width,A_RGB Color)
{
	u16 sX,eX;
	A_RGB *destinE,*destinS;
	sX = pRect->left;
	if(pRect->top>=pWindow->height || sX >= pWindow->width)
		return;

	eX = sX+width;
	if(eX > pWindow->width) eX=pWindow->width;
	
	destinS=&pWindow->widget[pRect->top*pWindow->width + sX];
	destinE=destinS+(eX-sX);
	while(destinS < destinE)
	{
		*destinS++ = Color;
	}
}

void UI_hline(XuiWindow *pWindow,POINT *pRect,int height,A_RGB Color)
{
	u16 sH,eH,width;
	A_RGB *destinE,*destinS;
	sH = pRect->top;
	width = pWindow->width;
	if(pRect->left >= width || sH>=pWindow->height)
		return;
	eH = sH + height;
	if(eH > pWindow->height) eH=pWindow->height;
	
	destinS=&pWindow->widget[sH*width + pRect->left];
	destinE=destinS + (eH-sH)*width;
	while(destinS < destinE)
	{
		*destinS = Color;
		destinS += width;
	}
}

void UI_FillRectSingLe(XuiWindow *pWindow,RECTL *pRect,A_RGB Color)
{
	A_RGB *destin;
	if(pRect)
	{
		A_RGB* pWidget;
		u16 sX,sY,eX,eY,i,mWidth;
		sX = pRect->left;
		sY = pRect->top;
		if(sY >= pWindow->height || sX >= pWindow->width)
			return;
		mWidth	= pWindow->width;
		eX = sX+pRect->width;
		if(eX > mWidth) eX=mWidth;
	
		eY = sY+pRect->height;
		if(eY > pWindow->height) 
			eY=pWindow->height;
		pWidget = pWindow->widget;
		while(sY < eY)
		{
			destin=pWidget+(sY*mWidth + sX);
			for(i=sX; i<eX; i++)
			{
				*destin++ = Color;
			}
			sY++;
		}
	}
	else	//全屏显示
	{
		int max=pWindow->width*pWindow->height;
		destin = pWindow->widget;
		while(max--)
		{
			*destin++ = Color;
		}
	}
}

/*
void UI_SetRectBuff(XuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB)
{
	u16 i,j,sx,sy,w,h;
	int mWidth;
	A_RGB *destin;
	sx = pRect->left;
	sy = pRect->top;
	
	mWidth = pWindow->width;
	w = sx+mWidth;
	if(w > mWidth) w=mWidth;
	h = sy+pRect->height;
	if(h > pWindow->height) h=pWindow->height;
	
	for (j = sy; j < h; j++) 
	{
		destin=&pWindow->widget[j*mWidth + sx];
		for(i=sx; i<w; i++)
		{
			*destin++ = *pRGB++;
		}
	}
}

void UI_GetRectBuff(XuiWindow *pWindow,RECTL *pRect,A_RGB *pRGB)
{
	u16 i,j,sx,sy,w,h;
	int mWidth;
	A_RGB *destin;
	sx = pRect->left;
	sy = pRect->top;
	mWidth = pWindow->width;
	w = sx+mWidth;
	if(w > mWidth) w=mWidth;
	h = sy+pRect->height;
	if(h > pWindow->height) h=pWindow->height;
	for (j = sy; j < h; j++) 
	{
		destin=&pWindow->widget[j*mWidth + sx];
		for(i=sx; i<w; i++)
		{
			*pRGB++ = *destin++;
		}
	}
}
*/

//static u8 SPF_runLock=FALSE;
int UI_ShowPictureFile(XuiWindow *pWindow,RECTL *prclTrg,const char *pfilePath)
{
	
	return 0;
}


//=============底部显示进度条==ratio(0~100)===============================
void UI_ShowBottomProgress(XuiWindow *pWindow,RECTL *pRect,int thick,int ratio)
{
	UI_FillRectSingLe(pWindow,pRect,RGB_CURR(199,200,244));
	if(ratio)
	{
		RECTL tRect;
		tRect.top	=	pRect->top+thick;
		tRect.left	=	pRect->left+thick;
		tRect.width =	pRect->width-(thick<<1);	//thick*2;
		tRect.height =	pRect->height-(thick<<1);	//thick*2;
		if(ratio < 100)
			tRect.width = tRect.width*ratio/100;
		UI_FillRectSingLe(pWindow,&tRect,RGB_CURR(0,255,255));
	}
}

//=============显示滑轨==ratio(0~100)===============================
void UI_ShowParMiddleSlide(XuiWindow *pWindow,int ratio)
{
	u16 Width1,Width2;
	RECTL tRect;
	tRect.left = 4;
	tRect.height = 32;
	tRect.width = pWindow->width - tRect.left*2;
	tRect.top = (pWindow->height - tRect.height)/2;
	Width1 = (tRect.width-tRect.height)*ratio/100;
	Width2 = (tRect.width-tRect.height)-Width1;
	UI_FillRectSingLe(pWindow,&tRect,RGB_CURR(255,255,255));

	tRect.height = 16;
	tRect.left = 4;
	if(Width1)
	{
		tRect.width = Width1;
		tRect.top = (pWindow->height - tRect.height)/2;
		UI_FillRectSingLe(pWindow,&tRect,RGB_CURR(210,99,25));
	}
	if(Width2)
	{
		tRect.left += pWindow->width+Width1+tRect.height;
		tRect.width = Width2;
		UI_FillRectSingLe(pWindow,&tRect,RGB_CURR(56,56,56));
	}
	tRect.height = 32;
	tRect.top = (pWindow->height - tRect.height)/2;
	tRect.left = pWindow->width+4+Width1;
	UI_FillRectSingLe(pWindow,&tRect,RGB_CURR(199,206,218));
}


void UI_ShowQrCode(XuiWindow *pWindow,RECTL* pRect,const char* pInfo,A_RGB Color)
{
	IMAGE image;
	if(0==Lib_QrCodeImg(&image,pInfo,FALSE))
	{
		RECTL oImage;
		u8 *pByte;
		A_RGB *pbgra;
		u16 x,y,ix,mx,iy,my;
		u16 width;//height,width,
		A_RGB *pWidget;
		//RECTL tRect;
		//----保持长宽比，按最小宽度放大--------------
		mx = MIN(pRect->width,pRect->height)/image.w;
		my = mx;
		//------不保持长宽比，按指定区域放大---------
		//mx =pRect->width/image.w;
		//my = pRect->height/image.h;
		oImage.width = image.w * mx;
		oImage.height = image.h * my;
		oImage.left = pRect->left;
		oImage.top = pRect->top;
		if(pRect->width > oImage.width)
			oImage.left +=(pRect->width - oImage.width)/2;
		if(pRect->height > oImage.height)
			oImage.top +=(pRect->height - oImage.height)/2;		

	//	width	= pWindow->width;
	//	height	= pWindow->height;
		width = pWindow->width;
		pWidget = pWindow->widget;
		for(x=0 ;x<image.w ; x++)
		{
			pByte = &image.pByte[x*image.mline];
			for(y = 0; y < image.h; y++) 
			{
				if(pByte[y])
				{
					for(iy=0;iy<my;iy++)	
					{
						pbgra=&pWidget[(oImage.top + y*my+iy)*width + oImage.left + x*mx];
						for(ix=0;ix<mx;ix++)
						{
							*pbgra++ = Color;
						}
					}
					//tRect.left = oImage.left++ x*mx;
					//tRect.top = oImage.top+y*my;
					//UI_FillRectSingLe(&tRect,Color);
				}
			}
		}
	}
}


const API_UI_Def ApiUI={
	{'U','I','\0',26},
	XuiOpen,
	XuiClose,

	XuiRootCanvas,
	XuiStatusbarCanvas,
	XuiShowWindow,
	XuiDestroyWindow,

	UI_Push,
	UI_FillRectSingLe,
	
	UI_ShowQrCode,
	UI_ShowPictureFile,
	UI_ShowBottomProgress,
	UI_ShowParMiddleSlide,
};

