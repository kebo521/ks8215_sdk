/**
 * File:   linux_fb.h
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  linux_framebuffer
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

#ifndef XUI_FONT_H
#define XUI_FONT_H


#include "file_stu.h"

extern void UI_SetSysEnColor(A_RGB ForeColor,A_RGB BackColor);
extern void UI_DisplaySysEn(XuiWindow *pWindow,int x,int y,int type,char*pMsgEn);
extern void API_ShowLineEn(u8 Line,char *pMsgEn,int timeoutms);

//========================��ʾ��Դ(�ֿ�)==================================================
typedef struct
{
	u32		ParLen;      			//��Դ���ݳ���
	u32		Offset;      		//��Դ����ƫ�Ƶ�ַ
}DisRES_ITEM;	

typedef struct
{
	u8 reqLen_en;
	u8 reqLen_ch;
	u8 outLen_en;
	u8 outLen_ch;
}DisFont_Len;	

typedef struct
{
//	int		fd;		//�ļ����
	u32			lenFont;
	u8			*pbFont;
	DisRES_ITEM gbk;
	DisRES_ITEM ucode;
	DisFont_Len resFd;
	DisRES_ITEM fn[6];	//en+hz1+hz2+hz3+hz4+hz5
}DisRES_table;
extern DisRES_table resDisTable;

extern int InitExtResLib(char *pfile);
extern void DeInitExtResLib(void);
//==================��ʾ���ģ���Ҫ�ֿ�ks.res֧��===================================
extern void UI_SetFontColor(A_RGB ForeColor,A_RGB BackColor);
extern int UI_DisplayFont(XuiWindow *pWindow,POINT* prclTrg, u8* hzData);
extern int UI_DrawLineString(XuiWindow *pWindow,POINT* prclTrg,const char *src);
extern int UI_DrawRectString(XuiWindow *pWindow,RECTL* pRect,const char *src);
extern void UI_DrawCenterString(XuiWindow *pWindow,char *src);


typedef struct	
{
	char Mask[4]; 	// "Fnt"
	void (*SetSysEnColor)(A_RGB,A_RGB);	//(A_RGB ForeColor,A_RGB BackColor)
	void (*DisplaySysString)(XuiWindow*,int,int,int,char*);	//(Window��x,y,TEXT_TYPE,pMsg) TEXT_TYPE=TEXT_12/TEXT_16/TEXT_24
	
	int (*InitFontLib)(char*);		//(char *pfile)
	void (*DeInitFontLib)(void);	//
	void (*SetFontColor)(A_RGB,A_RGB);	//(u32 fgColor,u32 bgColor) RGB_CURR
	int (*DisplayFont)(XuiWindow*,POINT*,u8*);	//(pWindow,POINT* prclTrg, u8* hzData)
	int (*DrawLineString)(XuiWindow*,POINT*,const char*);//Display single line of text, no automatic line breaks
	int (*DrawRectString)(XuiWindow*,RECTL*,const char*);//The specified area displays text and wraps automatically
	void (*DrawCenterString)(XuiWindow*,char*);	//(XuiWindow *pWindow,char *src)
}API_FONT_Def;


extern const API_FONT_Def ApiFont;


//============================���嶨��=============================
typedef enum
{
	XUI_FONT_MONO,	// �ڰ�����(˫ɫ)
	XUI_FONT_GREY,	// �Ҷ�����
}XuiFontSet;

//==============================������ʽ===============================
typedef enum
{
	XUI_TEXT_NORMAL,		// ����
	XUI_BOLD,				// ����
	XUI_ITALIC,			// б��
	XUI_TEXT_BOLD_ITALIC,// �����б��
}XuiTextStyle;

typedef struct{
	XuiFontSet fontset;
	int index;
	void *pFont;	//tSdkFont
}XuiFont;

extern XuiFont *XuiCreateFont(char *fontfile,int index, XuiFontSet fontset);
extern void XuiDestroyFont(XuiFont *font);
extern int XuiCanvasDrawText(XuiWindow *window,unsigned int x,unsigned int y,unsigned int height,XuiFont *font,XuiTextStyle textstyle,XuiColor fg,char *text);


#endif /*LINUX_FB_H*/
