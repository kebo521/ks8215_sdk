
#ifndef _APP_MIAI_
#define _APP_MIAI_


typedef struct	
{
	char Mask[4]; 	// "Even"
	void (*Init)(int,unsigned int);	//int pshared, unsigned int value
	void (*DeInit)(void);
	void (*SetMsg)(u16,u16);
	int (*GetMsg)(u16*,u16*);
	int (*GetMsgPeek)(u16*,u16*);
	void (*KillThread)(void*);
	void (*CreateThread)(void *(*pFunThread)(void*));
	void (*LoadThread)(void*); 
	void (*SetEvent)(int,u32);
	void (*GetEvent)(int *,u32 *);
	void (*SetEventTime)(int );
	u32  (*WaitEvent)(int,...);
}API_Even_Def;

typedef struct	
{
	char Mask[4]; 	// "Fnt"
	void (*DisplaySysString)(int,int,int,char*);	//(x,y,TEXT_TYPE,pMsg) TEXT_TYPE=TEXT_12/TEXT_16/TEXT_24
	
	int (*InitFontLib)(char*);		//(char *pfile)
	void (*DeInitFontLib)(void);	//
	void (*SetFontColor)(u32,u32);	//(u32 fgColor,u32 bgColor) RGB_CURR
	int (*DisplayFont)(POINT*,u8*);	//(POINT* prclTrg, u8* hzData)
	int (*DrawLineString)(POINT*,const char*);//Display single line of text, no automatic line breaks
	int (*DrawRectString)(RECTL*,const char*);//The specified area displays text and wraps automatically
}API_FONT_Def;



typedef struct{
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
}gUIrgba;
#define	RGB_CURR(r,g,b)		((r*0x10000)|(g*0x100)|b)	//(u32)(gUIrgba)(b,g,r,0xff))

typedef struct _API_UI	
{
	char Mask[4]; 	// "UI"
	int (*open)(int,char **);	//(int argc,char **argv)
	void (*close)(void);

	int (*RootCanvas)(void);
	int(*StatusbarCanvas)(void);

	void (*Push)(RECTL*);	//Cache area is pushed to video memory,(RECTL==NULL,Show full area)
	void (*FillRectSingLe)(RECTL*,u32);	//(xywh,RGB_CURR(r,g,b))
	void (*SetRectBuff)(RECTL*,gUIrgba*);	//(xywh,gUIrgba...)
	void (*GetRectBuff)(RECTL*,gUIrgba*); //(xywh,gUIrgba...)

	void (*ShowQrCode)(RECTL* ,const char*,u32);	//(xywh,"Text",RGB_CURR(r,g,b))
	int (*ShowPictureFile)(RECTL *,const char *);
	void (*ShowBottomProgress)(int);	//ratio (0~100)
	void (*ShowParMiddleSlide)(int); //ratio (0~100)
}API_UI_Def;


typedef struct	
{
	char Mask[4]; 	// "API"
	int (*test)(char*);	//²âÊÔº¯Êý
	const API_UI_Def *ui;
	const API_FONT_Def *font;
	const API_Even_Def *event;
}APP_SDK;



#endif
