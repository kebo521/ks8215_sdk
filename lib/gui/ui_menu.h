#ifndef _UI_MENU_
#define _UI_MENU_
//=======����˵��ṹ==========

typedef int (*fMenuFun)(char*); 
typedef int (*APP_IndexH)(char*,int); 

typedef struct 
{//��ʾ+����
	char			*pText;		//��ʾ����
	fMenuFun		pFunMenu;	//������
}CMenuItemStru;


typedef struct _CMenuListPar
{//������֯�˵���
	struct _CMenuListPar *pNext;
	fMenuFun		pFunMenu;	//������
	int				TextLen;	//��ʾ���ݳ���
	char			Text[0];	//��ʾ����,������֧�ֵĻ� Text[0]
}CMenuListPar;

extern int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs);
extern int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs);
extern int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs);
typedef enum 
{
	MENU_KEY_FUN,		//���ܼ�ִ�й���
	MENU_OUT_FUN,		//�˳�ʱ��ִ�й���
	MENU_SHOW_AFT,	//���һ����ʾ
	MENU_BACK_MAP,	//����ͼƬ����
}UI_MENU_ADD_TYPE;
extern void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,void* pFunc,const char *pData);
extern int APP_DesignatMenuItem(void* pTagFunc,char *pTagTitle);
extern int APP_ShowProsseMenu();

//===================�̶��˵�����=================================================
enum FIXED_MENU_TYPE
{
	FUN_MENU_N,	//�ղ˹��ܣ�����ĩ�˱��
	FUN_MENU_F,	//�����ܲ˵���	(char* pTitle)
	FUN_MENU_I,	//���������ܲ˵��� (char* pTitle,int index)
	FUN_MENU_G,	//�˵���		FixedMenuUITable
};	

typedef struct 
{//��ʾ+����
	char		*pText;		//��ʾ����
	void		*pFun;		//������,�� FunType ָ��(fMenuFun,APP_IndexH,FixedMenuUITable)
	int			FunType;	//FIXED_MENU_TYPE
}tMenuItemStru;

typedef struct
{
	fMenuFun 	pInFunc;		//���빦��
	fMenuFun 	pOutFunc;		//�˳�����
	int			TimeOutMs;		//�˵���ʾʱ��
	int			TeamTatla;		//-�˵�������
	tMenuItemStru pItem[];		//�˵�����,�˵�����
}FixedMenuUITable;

extern int APP_ShowFixedMenu(char* pTitle,FixedMenuUITable *pFixedMenu,void* pTagFunc);



#endif
