#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_

//===============色彩参数定义========================================
#if(1)
//-----------------M1901定义----------------------------
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} rgba_t;

typedef unsigned int  			A_RGB;		// <= RGB_CURR
#define	RGB_CURR(r,g,b)		(r|(g*0x100)|(b*0x10000))	//(u32)(rgba_t)(b,g,r,0xff))
#define RGB565_CLEAR			0xFF000000		// Transparent color
#else
//-----------------ubuntu定义----------------------------
typedef struct {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
} rgba_t;

typedef unsigned int  			A_RGB;		// <= RGB_CURR
#define	RGB_CURR(r,g,b)		((r*0x10000)|(g*0x100)|b)	//(u32)(rgba_t)(b,g,r,0xff))
#define RGB565_CLEAR			0xFF000000		// Transparent color
#endif

typedef void (*FunFillColour)(A_RGB*,int,int);		//色彩填充函数定义(data,w,h)
//=====================================================================================================
typedef struct{
  u16 left;
  u16 top;
} POINT, *PPOINT;

typedef struct{
  u16 left;
  u16 top;
  u16 width;
  u16 height;
}RECTL,*LPRECTL;

/**
 * GUI支持的图像格式定义
 */
typedef struct
{
	u16					w;				//!< 图像宽
	u16					h;				//!< 高
	u16					mline,len;				//!< 高
	u8*					pByte;			
}IMAGE;									



typedef struct _XuiWindow{
	struct _XuiWindow *pChild;	//父一个窗口
	struct _XuiWindow *pParent;	//子窗口
	struct _XuiWindow *pNext;		//子窗口....
	
	int left,top,width,height;
	
//	unsigned short key;		//鍏宠仈鎸夐敭鍊?
//	unsigned short type;	//Window 绐楀彛绫诲瀷锛岃瑙乆uiWindowType
	
	A_RGB* 		wBack;	//Window 背景色，无 可借用复窗口还原
	A_RGB* 		widget;	//用结构体后面的空间不需要释放，Window 鍏宠仈鐢诲竷鎸囬拡
} XuiWindow;
//extern XuiWindow UI_screen;

//extern int UI_RootCanvas(screen_buffer* fb);
typedef struct {
	int SetFlag;	//是否初始化标记
	int iRotate;	//旋转方向 0，90 ，180 ，270 
	int iStatusbar;	///*状态栏高度（0-64，默认值0，设置不支持的值时均使用默认值）*/
	int keys_fd;
	int TsDev_fd;
	int Screen_fd;
	XuiWindow tHardWindow;
//	u16 left,top;
}gUi_def;
extern gUi_def gUiDataAll;

extern int XuiOpen(int argc,char **argv);
extern void XuiClose(void);

extern XuiWindow *XuiRootCanvas(void);
extern XuiWindow *XuiStatusbarCanvas(void);
extern XuiWindow *XuiCreateCanvas(XuiWindow *parent, unsigned int x, unsigned int y,unsigned int width, unsigned int height);
extern void UI_Push(XuiWindow *pWindow,RECTL *pRect);
extern void XuiCanvasSetBackground(XuiWindow *pWindow,int bgstyle,void *img,A_RGB bg);
extern void XuiDestroyWindow(XuiWindow *window);
extern int XuiClearArea(XuiWindow *window, unsigned int x,unsigned int y, unsigned int width, unsigned int height);
extern void XuiShowWindow(XuiWindow *window,int show, int flag);

extern void UI_FillHitBack(A_RGB* pBack,int w,int h);
extern void UI_SetBackground(XuiWindow *pWindow,FunFillColour pFillColour);	//(u32* pOut,int width,int height)
extern void UI_ShowBackground(XuiWindow *pWindow);
extern void UI_vline(XuiWindow *pWindow,POINT *pRect,int width,A_RGB Color);
extern void UI_hline(XuiWindow *pWindow,POINT *pRect,int height,A_RGB Color);
extern void UI_FillRectSingLe(XuiWindow *pWindow,RECTL *pRect,A_RGB Color);
extern void UI_ShowQrCode(XuiWindow *pWindow,RECTL* pRect,const char* pInfo,A_RGB Color);

extern void UI_ShowBottomProgress(XuiWindow *pWindow,RECTL *pRect,int thick,int ratio);

typedef struct _API_UI	
{
	char Mask[4]; 	// "UI"
	int (*open)(int,char **);	//(int argc,char **argv)
	void (*close)(void);

	XuiWindow* (*RootCanvas)(void);
	XuiWindow* (*StatusbarCanvas)(void);
	void (*ShowWindow)(XuiWindow *,int,int);	//XuiWindow *,int show, int flag
	void (*DestroyWindow)(XuiWindow *);

	void (*Push)(XuiWindow *,RECTL*);	//Cache area is pushed to video memory,(RECTL==NULL,Show full area)

	void (*FillRectSingLe)(XuiWindow *,RECTL*,A_RGB);	//(xywh,RGB_CURR(r,g,b))

	void (*ShowQrCode)(XuiWindow *,RECTL* ,const char*,A_RGB);	//(xywh,"Text",RGB_CURR(r,g,b))
	int (*ShowPictureFile)(XuiWindow *,RECTL *,const char *);
	void (*ShowBottomProgress)(XuiWindow *,RECTL *,int,int);	//(XuiWindow *pWindow,RECTL *pRect,int thick,int ratio) ratio (0~100)
	void (*ShowParMiddleSlide)(XuiWindow *,int); //ratio (0~100)
}API_UI_Def;


extern const API_UI_Def ApiUI;

#endif

