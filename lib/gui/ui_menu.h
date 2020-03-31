#ifndef _UI_MENU_
#define _UI_MENU_
//=======单项菜单结构==========

typedef int (*fMenuFun)(char*); 
typedef int (*APP_IndexH)(char*,int); 

typedef struct 
{//显示+功能
	char			*pText;		//显示内容
	fMenuFun		pFunMenu;	//功能项
}CMenuItemStru;


typedef struct _CMenuListPar
{//用于组织菜单的
	struct _CMenuListPar *pNext;
	fMenuFun		pFunMenu;	//功能项
	int				TextLen;	//显示内容长度
	char			Text[0];	//显示内容,编译器支持的话 Text[0]
}CMenuListPar;

extern int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs);
extern int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs);
extern int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs);
typedef enum 
{
	MENU_KEY_FUN,		//功能键执行功能
	MENU_OUT_FUN,		//退出时键执行功能
	MENU_SHOW_AFT,	//最后一行显示
	MENU_BACK_MAP,	//背景图片功能
}UI_MENU_ADD_TYPE;
extern void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,void* pFunc,const char *pData);
extern int APP_DesignatMenuItem(void* pTagFunc,char *pTagTitle);
extern int APP_ShowProsseMenu();

//===================固定菜单处理=================================================
enum FIXED_MENU_TYPE
{
	FUN_MENU_N,	//空菜功能，用于末端标记
	FUN_MENU_F,	//单功能菜单项	(char* pTitle)
	FUN_MENU_I,	//带索引功能菜单项 (char* pTitle,int index)
	FUN_MENU_G,	//菜单组		FixedMenuUITable
};	

typedef struct 
{//显示+功能
	char		*pText;		//显示内容
	void		*pFun;		//功能项,由 FunType 指定(fMenuFun,APP_IndexH,FixedMenuUITable)
	int			FunType;	//FIXED_MENU_TYPE
}tMenuItemStru;

typedef struct
{
	fMenuFun 	pInFunc;		//进入功能
	fMenuFun 	pOutFunc;		//退出功能
	int			TimeOutMs;		//菜单显示时间
	int			TeamTatla;		//-菜单总条数
	tMenuItemStru pItem[];		//菜单内容,菜单功能
}FixedMenuUITable;

extern int APP_ShowFixedMenu(char* pTitle,FixedMenuUITable *pFixedMenu,void* pTagFunc);



#endif
