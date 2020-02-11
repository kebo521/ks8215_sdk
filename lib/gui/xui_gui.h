

#ifndef _GUI_DISPLAY_
#define _GUI_DISPLAY_

#define FONT_SIZE    		(24)    
#define MENU_ITEM_MAX    	8    		//菜单最大项数

#define RGB565_WITHE		RGB_CURR(0xff,0xff,0xff)	//0x0000FFFF
#define RGB565_BLACK		RGB_CURR(0x00,0x00,0x00)	//0x00000000

#define RGB565_RED			RGB_CURR(0xff,0x00,0x00)
#define RGB565_GREEN		RGB_CURR(0x00,0xff,0x00)	//0x07E0
#define RGB565_BLUE		RGB_CURR(0x00,0x00,0xff)	//0x001F

//------------菜单色彩定义-----------------
//#define RGB565_TITLE_ICON		RGB_CURR(0,127,255)   //0x03ff
//#define RGB565_TITLE_FONT		RGB565_WITHE
#define RGB565_TIEM_ICON		RGB_CURR(240,244,248)
#define RGB565_TIEM_FONT		RGB_CURR(48,48,48)	//0x3186
#define RGB565_SELE_ICON		RGB_CURR(224,224,224)	//0xe71c
#define RGB565_SELE_FONT		RGB_CURR(0,127,255)	//0x03ff

#define UI_CONT_COLOUR		RGB565_TIEM_ICON
#define FONT_CONT_COLOUR		RGB565_BLACK 

#define UI_TITLE_COLOUR		RGB_CURR(24,120,200) 
#define FONT_TITLE_COLOUR		RGB565_WITHE 






typedef enum 
{
	GUI_SHOW_MSG	= 0x11	,		//普通显示内容
	GUI_EDIT_MSG	= 0x21	,		//编辑窗口
	GUI_MENU_LINE	= 0x51	,		//一维菜单 
	GUI_MENU_TWO	= 0x52	,		//二维菜单
}GUI_TYPE;			//V1.2	

/**
 * 文本输入类型定义
 */
typedef enum 
{
	IME_NONE			=0x00000000,		//!< NONE
	IME_NUM			=0x00000001,		//!< 数字
	IME_abc			=0x00000002,		//!< 小写字母
	IME_ABC			=0x00000004,		//!< 大小字母
	IME_Abc			=0x00000008,		//!< 大小写混合字母
	IME_SYM			=0x00000010,		//!< 符号
	IME_SUM			=0x00000020,		//!< 金额 1.23
	IME_PY				=0x00000040,		//!< 拼音 支持GB2312编码
	IME_PYGBK			=0x00000080,		//!< 全拼 支持GBK编码
	IME_FMT			=0x00000100,		//!< 格式化模式数字输入，如IP,账号等.
	IME_SCAN			=0x00000200,		//!< 扫码输入
	IME_MASK			=0x000003FF,		//!< 掩码
	IME_PIN_MODE		=0x10000000,		//!< 密码模式	
	IME_SYM_MODE		=0x20000000,		//!< 符号模式	
	IME_ENG			=IME_ABC|IME_abc|IME_Abc, //!< 英文输入
	IME_END	
}IME_TYPE;			//V1.2	




typedef enum
{
	MENU_ICON_NUM		=0x0001,			//图标为序号,	与MENU_LIST组合使用
	MENU_ICOM_IMG		=0x0002,			//图标为图像,	与MENU_LIST组合使用
	MENU_LIST			=0x0100,			//列表菜单
	MENU_RADIO			=0x0200,			//单项选择菜单
	MENU_CHECK			=0x0400,			//多项选择菜单
	MENU_MUILT_LINE		=0x1000,			//多行文本,		与其它类型组合使用
	MENU_MAX			=0xFFFF
}UI_MENU_TYPE;
/**
 * 文本显示类型定义
 */
typedef enum
{
	TEXT_12					=12,			//!< 12x12字体大小
	TEXT_16					=16,			//!< 16x16字体大小
	TEXT_20					=20,			//!< 20x20字体大小
	TEXT_24					=24,			//!< 24x24字体大小
	TEXT_32					=32,			//!< 32x32字体大小
	TEXT_SIZE					=0x000000FF,	//!< 字体大小掩码
	                    	
	TEXT_NONE					=0x00000000,	//!< 普通文本
	TEXT_NORMAL				=0x00000000,	//!< 普通文本
	TEXT_SHADOW				=0x00000100,	//!< 阴影字(彩色有效)
	TEXT_BORDER				=0x00000200,	//!< 空心字
	TEXT_BOLD					=0x00000400,	//!< 加粗
	TEXT_BACK					=0x00000800,	//!< 带背景色
	
	TEXT_ALIGN_LEFT			=0x10000000,	//!< 水平左对齐
	TEXT_ALIGN_CENTER			=0x20000000,	//!< 水平居中对齐
	TEXT_ALIGN_RIGHT			=0x40000000,	//!< 水平右对齐
	TEXT_ALIGN_MASK			=0x70000000,	//!< 水平对齐掩码
	                    	
	TEXT_VALIGN_TOP			=0x01000000,	//!< 垂直上对齐
	TEXT_VALIGN_CENTER		=0x02000000,	//!< 垂直居中对齐
	TEXT_VALIGN_BOTTOM		=0x04000000,	//!< 垂直下对齐
	TEXT_VALIGN_MASK			=0x07000000,	//!< 垂直对齐掩码

	TEXT_EXSTYLE_UNDERLINE	=0x00100000,	//加下划线
	TEXT_EXSTYLE_OVERLINE	=0x00200000,	//加上划线
	TEXT_EXSTYLE_BORDER		=0x00400000,	//加框
	TEXT_LINE_NUM_MASK		=0x000F0000,	//指定行号(1~15)
}TEXT_TYPE;	//V1.1



typedef void (*Fun_ShowNum)(u32,char*); 



extern void API_GUI_LoadWindow(XuiWindow *pWindow);
extern XuiWindow *API_GUI_GetCurrWindow(void);

extern void API_FillMenuBack(A_RGB* pBack,int w,int h);
extern void API_FillShowBack(A_RGB* pBack,int w,int h);
//extern int API_Set_Background(FunFillColour pFillColour);

extern int APP_WaitUiEvent(int tTimeOutMS);
extern int API_GUI_CreateShow(const char* pTitle,const char* pOk,const char* pCancel);
extern int API_GUI_CreateMenu(const char* pTitle,const char* pOk,const char* pCancel);
//=================================================================================

//extern void UI_DisplayBitMapGet(u16 x,u16 y,u16 w,u16 h);
//extern void UI_DisplayBitMapSet(void);
//extern void UI_DisplayBitMapEND(void);

//==================================================================================
extern void API_GUI_ShowColorRect(RECTL *pRect,u16 Width,A_RGB Color);

extern void API_GetALignLeftTop(u32 tTextType,RECTL *pRect);
extern void API_GUI_InputEdit(char* pStrDef,int tMaxLen,u32 Way,Fun_ShowNum pShow);


extern void API_GUI_Show(void);

//===============清除显示内容(指定区域)=================================================
extern void API_GUI_ClearScreen(RECTL* pRect);
/**
 * 创建一个窗体用于GUI界面交互
 *
 * @param pTitle 		界面标题
 * @param pOk 			按钮栏中存在OK键的提示, 为NULL不存在该按钮
 * @param pCancel 		按钮栏中存在Cancel键的提示, 为NULL不存在该按钮
 * @param tGuiType 		窗体显示类型 {@link WIN_TYPE} 例如 WIN_FULL|WIN_NOBTN 或者　WIN_POP|WIN_NOBTN
 * @return {@link RET_OK} 						成功
 * @return {@link RET_API_PARAMETER_ERROR}		函数参数错误
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */
extern int   API_GUI_CreateWindow(const char* pTitle,const char* pOk,const char* pCancel,FunFillColour fBackColour);

/**
 * GUI提示信息显示
 *
 * IMG + 提示文本
 * @param pImg 		{@link IMAGE}指针或IMAGE存储结构的路径
 * @param tTextType {@link TEXT_TYPE}组合类型
 * @param pTextBuf 	文本提示信息
 * @return {@link RET_OK} 						成功
 * @return {@link RET_API_PARAMETER_ERROR}		函数参数错误
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */
extern int  API_GUI_Info(const IMAGE* pImg,u32 tTextType,const char* pTextBuf);
extern void API_GUI_Edit_Prompt(u32 tFrontTextType,char* pFrontTextBuf,u32 tAfterTextType,char* pAfterTextBuf);
extern void API_GUI_Edit(u32 tTextType,char* pTextDef,int tMaxLen,u32 tImeType,u32 tImeLimit);


extern int API_GUI_Edit_GetText(char* pAscText,int tMaxLen);


/**
 * 构建一个GUI菜单
 *
 * 构建一个GUI菜单, {@link MENU_CHECK}多项选择菜单不支持.
 * @param pMsg 			菜单显示提示信息，默认为NULL
 * @param tNum 			菜单项数
 * @param tCurInx 		当前默认选择项, 0~tNum-1
 * @param tHead 		首项显示索引
 * @param pMenuText 	菜单文本数组
 * @return {@link RET_OK} 						成功
 * @return {@link RET_API_PARAMETER_ERROR}		函数参数错误
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */
extern int API_GUI_Menu(void* pMenu,void (*pShowItem)(void *,int,int,char*),int tNum,int tCurInx,int tHead,char* pAfterText,void* KeyFunEn);
extern int API_GUI_Menu_GetInx(void);
extern int API_GUI_Menu_GetInxAndHear(int* tHead);


extern int   APP_GUI_Menu(char* pTitle,int stratIndex,int tNum,int tCurInx,char** pMenuText);

extern void APP_ShowChangeInfo(char *pOriginal,int Originalsize,const char* format,...);


/**
 * 显示GUI界面, 开始交互
 *
 * @return {@link RET_OK} 						成功
 * @return {@link RET_FUNCTION_NOT_SUPPORT}		功能不支持
 * @return {@link RET_SYSTEM_ERROR}     		系统错误
 */

extern void APP_ShowSta(char *pTitle,char *pMsg);
//===========剧中显示内容=======
extern int APP_ShowMsg(char *pTitle,char *pMsg,int timeOutMs);
//===========左上角显示内容=======
extern int APP_ShowInfo(char *pTitle,char *pInfo,int timeOutMs);

extern int APP_ShowQrCode(char *pTitle,const char* pInfo,A_RGB Color);

extern int APP_HitMsg(const char* pMsg,int tTimeOutMS);

//=============底部显示进度条==ratio(0~100)===============================
extern void APP_ShowBottomProgress(int ratio);
//=============显示滑轨==ratio(0~100)===============================
//extern void APP_ShowParMiddleSlide(int ratio);

//===============设置倒计时相对位置=与初值时间=======================================
extern void gShowTimeS_SetInit(u32 tTextType,int len,int timeS);
//=======刷新到计时显示并返回计时结果:===时间到了返回:EVENT_TIMEOUT,没到返回:0=======
extern int gShowTimeS_GetOut(void);

//==============显示
extern void APP_ShowDrawBoard(char *pTitle);


/*
typedef struct	
{
	char Mask[4]; 	// "UI"
	
}API_GUI_Def;
extern const API_GUI_Def ApiGUI;
*/

#endif

