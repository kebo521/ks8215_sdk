/*****************************�˵�����******************************
//����-------  ���ڴ���˵�������ִ�С���ʾ������
//����-------  �˹���
//����ʱ��--20150604
******************************************************************************/
#include "comm_type.h"

#include "EvenMsg.h"

#include "xui_ui.h"
#include "xui_fb.h"
#include "xui_font.h"
#include "xui_gui.h"

#include "ui_menu.h"

#include "language.h"
#include "sdk/sys_sdk.h"


//============�˵���ʾ�����õ��Ĳ���======================
typedef enum
{
	_GUI_MENU_SHOW,
	_GUI_MENU_PROCESS,
	_GUI_MENU_RUN,
	_GUI_MENU_RET,
	_GUI_MENU_QUT,
	_GUI_MENU_EXT,
} GUI_Menu_msg;
//============�˵�����ṹ==================================
typedef struct _CMenuUITable
{
	struct _CMenuUITable *pPrevious;	//����ָ��
	u8		ShowState;		//-�˵�����������״̬(GUI_Menu_msg)
	u8		TeamTatla;		//-�˵�������
	u8		TeamCurr;		//-��ǰ��ѡ��Ĳ˵���
	u8		ShowHead;		//-����һ����ʾ�Ĳ˵���
	//----�����ֽ���������4��������----------------
	char	*pAfterText;		//���һ����ʾ����
	fMenuFun pKeyFunc;		//���ܼ���������
	char	*pKeyFuncTitle;		//���ܼ�������
	fMenuFun pOutFunc;		//�˳�����
	char	*pOutFuncTitle;		//�˳����ܱ���
	APP_IndexH pUnifiedFunc;	//ͳһ����˵��ӿ�
	FunFillColour fBackColour;
	u8				ShowFont;	//0��ʾ�˵����֣�0xff ����ʾ�˵�����
	u8				noUse[3];	
	int				TimeOutMs;		//�˵���ʾʱ��
	char  			*pTitle;		//�˵�����
	CMenuItemStru	pItem[1];		//�˵�����,�˵�����
}CMenuUITable;
static CMenuUITable *pMenuUiTable=NULL;
static CMenuItemStru tMenuEnterTag;

//====================================================================
//����:   �����µĹ̶����ز˵�(�˹�����Ҫ�����ڴ�ռ�)
//��������:pTitle ���⣬pMenuText�˵���ʾ�tNum�˵���������pMenuFunc�˵��Ĺ���
//�������:��
//����ʱ��:  	20161128
//---------------------------------------------------------------
int APP_CreateNewMenuByStr(char *pTitle,int tNum,char* *pMenuText,const APP_IndexH pUnifiedFunc,int TimeOutMs)
{
	CMenuUITable *pNeTable;
	char *pText;
	u16 mLen,i,slen,len;
	/*
	if(pMenuUiTable!=NULL && pMenuUiTable->pMenuFunc == pMenuFunc)
	{//----ͬһ���ڷǵ�һ�δ�����ֱ����ʾ-------
		pMenuUiTable->ShowState=_GUI_MENU_SHOW;
		return;
	}*/
	mLen=sizeof(CMenuUITable) + sizeof(CMenuItemStru)*tNum;
	slen=0;
	for(i=0;i<tNum;i++)
	{
		len =	API_strlen(pMenuText[i])+1;
		slen += DfGetBeiSu(len,4);	//��Ӧ����ṹ
	}
	pNeTable=(CMenuUITable*)malloc(mLen+slen);
	if(pNeTable == NULL)
	{//�ڴ�����ʧ�ܣ��˻�֮ǰ��Ui
		LOG(LOG_INFO,"CreateNewMenuByStr malloc[%d] fail!\n",mLen+slen);
		return RET_ERR;
	}
	API_memset(pNeTable,0x00,mLen);
	//------------------------------------------------------------
	pText = (char*)&pNeTable->pItem[tNum];
	for(i=0;i<tNum;i++)
	{
		len =	API_strlen(pMenuText[i])+1;
		API_memcpy(pText,pMenuText[i],len);		
		pNeTable->pItem[i].pText=pText;
		pNeTable->pItem[i].pFunMenu=NULL;
		pText += DfGetBeiSu(len,4);	//��Ӧ����ṹ
	}
	//----------------------------------------------------------
	pNeTable->TimeOutMs=TimeOutMs;
	pNeTable->pTitle=pTitle;
	pNeTable->pUnifiedFunc=pUnifiedFunc;
	pNeTable->TeamTatla=tNum;
	pNeTable->ShowState=_GUI_MENU_SHOW;
	pNeTable->pPrevious =pMenuUiTable;
	pMenuUiTable=pNeTable;
	return RET_OK;
}

//====================================================================
//����:   �����µ��ڴ�˵�(���в˵���ʹ���ⲿ�ռ䣬�˹�����Ҫ����ϴ��ڴ�ռ�)
//��������:pTitle ���⣬tNum�˵���������pMenuAll�˵���ʾ�빦��
//�������:RET_OK�����ɹ���RET_ERR ����ʧ��
//����ʱ��:  	20151230
//---------------------------------------------------------------
int APP_CreateNewMenuByStruct(char *pTitle,int tNum,CMenuItemStru *pMenuAll,int TimeOutMs)
{
	CMenuUITable *pNeTable;
	int 		i;
	//----------------------------------------------------------
	pNeTable=(CMenuUITable*)malloc(sizeof(CMenuUITable)+sizeof(CMenuItemStru)*tNum);
	if(pNeTable == NULL)
	{	//�ڴ�����ʧ�ܣ��˻�֮ǰ��Ui
	//	 LOG(LOG_INFO,"pMenuUiTable Null!\n");
		//APP_ShowMsg(pTitle,"pMenuUiTable Null",2000);
		return RET_ERR;
	}
	API_memset(pNeTable,0x00,sizeof(CMenuUITable));
	//--------------�޸���ʱ����------------------
	for(i=0;i<tNum;i++)
	{
		pNeTable->pItem[i].pFunMenu=pMenuAll[i].pFunMenu;
		pNeTable->pItem[i].pText=pMenuAll[i].pText;
	}	
	//-------------д�������Ϣ-------
	pNeTable->TimeOutMs=TimeOutMs;
	pNeTable->pTitle = pTitle;
	pNeTable->TeamTatla=tNum;
	pNeTable->TeamCurr=0;	//Ĭ��ѡ����
	pNeTable->ShowState=_GUI_MENU_SHOW;
	pNeTable->pPrevious =pMenuUiTable;
	pMenuUiTable=pNeTable;
	return RET_OK;
}


//====================================================================
//����:   ������˵�ת�ɽṹ�˵�(�˹�����Ҫ�����ڴ�ռ䣬�˵��Ĵ�С�������ڴ����)
//����:   ��pStrlist�еĲ˵����ݿ����ṹ�˵��У����ͷ�pStrlist(��ShowFlowMenu������)����Ӧ�����ڿռ�
//��������:pTitle �˵�����,pStrlist �˵�������(��ʾ���ݣ�����ʽ)
//�������:RET_OK�����ɹ���RET_ERR ����ʧ��
//����ʱ��:  	20170207
//---------------------------------------------------------------
int APP_CreateNewMenuByList(char* pTitle,CMenuListPar* pMenulist,int TimeOutMs)
{
	u8 i,MenuCount=0;
	u8 slen,TatleLen=0;
	char *pShowMsg;
	CMenuUITable *pNeTable;
	CMenuListPar *pNewList;
	if(pMenulist==NULL) return RET_ERR;
	pNewList=pMenulist;
	while(pNewList != NULL)
	{
		MenuCount++;
		slen=pNewList->TextLen+1;
		TatleLen += DfGetBeiSu(slen,4);	//��Ӧ����ṹ
		pNewList=pNewList->pNext;
	}
	//----------------------------------------------------------
	pNeTable=(CMenuUITable*)malloc(sizeof(CMenuUITable)+sizeof(CMenuItemStru)*MenuCount +TatleLen);
	API_memset(pNeTable,0x00,sizeof(CMenuUITable));
	//--------------�޸���ʱ����------------------
	pShowMsg=(char*)&pNeTable->pItem[MenuCount];
	for(i=0;i<MenuCount;i++)
	{
		API_memcpy(pShowMsg,pMenulist->Text,pMenulist->TextLen);
		pShowMsg[pMenulist->TextLen]='\0';

		pNeTable->pItem[i].pText = pShowMsg;
		pNeTable->pItem[i].pFunMenu=pMenulist->pFunMenu;

		slen=pNewList->TextLen+1;
		pShowMsg += DfGetBeiSu(slen,4);	//��Ӧ����ṹ
		
		pNewList=pMenulist;
		pMenulist=pMenulist->pNext;
		free(pNewList);
	}
	//-------------------------------------------------------
	pNeTable->TimeOutMs=TimeOutMs;
	pNeTable->pTitle =pTitle;
	pNeTable->TeamTatla=MenuCount;
	pNeTable->ShowState= _GUI_MENU_SHOW;
	pNeTable->pPrevious =pMenuUiTable;
	pMenuUiTable=pNeTable;
	return RET_OK;
}


//====================================================================
//����:  ������һ��(����һ��)�˵�
//����:   ����CreateNewRamMenu��������ڴ�ռ�
//��������:series ���Ϸ��ؼ�����series=0ʱ���˳����в˵�,pEndMenuΪ�����Ϸ��ؼ�����pEndMenu��Ϊ�գ����ص�pEndMenu����һ�����˳���ʾ����
//�������:GUI_Menu_msg
//����ʱ��:  	20170317
//---------------------------------------------------------------
GUI_Menu_msg ReturnToPreviousMenu(u8 series,CMenuUITable *pEndMenu)  //RevocateMenuList
{
	CMenuUITable* pOldeMenu;
	while(pMenuUiTable!=NULL)
	{
		if(pMenuUiTable->pOutFunc)
			pMenuUiTable->pOutFunc(pMenuUiTable->pOutFuncTitle);
		if(pEndMenu == pMenuUiTable)
		{
			pMenuUiTable=pMenuUiTable->pPrevious;
			free(pEndMenu);
			return _GUI_MENU_EXT;
		}
		pOldeMenu=pMenuUiTable;
		pMenuUiTable=pMenuUiTable->pPrevious;
		free(pOldeMenu);
		if(series)
		{
			if((--series)==0)
			{
				if(pMenuUiTable)
					return _GUI_MENU_SHOW;
				return _GUI_MENU_EXT;
			}
		}
	}
	return _GUI_MENU_EXT;
}


//====================================================================
//����:  ��ǰ�˵�����������ܼ�ִ�й���
//����:  ���ڲ˵���Ҫ���Ӷ��⹦��
//��������:type ��������,pFunc����ִ�к�����pFunTitle ���ܱ���(��֧��ջ�ռ�)��
//�������:��
//---------------------------------------------------------------
void APP_AddCurrentMenuOtherFun(UI_MENU_ADD_TYPE type,void* pFunc,const char *pData)
{
	if(pMenuUiTable)
	{
		if(type==MENU_KEY_FUN)
		{
			pMenuUiTable->pKeyFunc	= (fMenuFun)pFunc;
			pMenuUiTable->pKeyFuncTitle = (char*)pData;
		}
		else if(type==MENU_OUT_FUN)
		{
			pMenuUiTable->pOutFunc	= (fMenuFun)pFunc;
			pMenuUiTable->pOutFuncTitle = (char*)pData;
		}
		else if(type==MENU_SHOW_AFT)
		{
			pMenuUiTable->pAfterText = (char*)pData;
		}
		else if(type==MENU_BACK_MAP)
		{
			pMenuUiTable->fBackColour	= (FunFillColour)pFunc;
			pMenuUiTable->ShowFont	= *pData;
		}
	}
}


//====================================================================
//����: ����ָ���˵���
//����: �˵����ʱ����ָ�����������������ʾ�˵�
//��������:pTagFuncָ�����ܺ�����pTagTitle ָ������,pTagFunc��pTagTitle���߿�ѡ��һ��
//�������:���� EVENT_ENTER ���߲˵�����ָ����
//---------------------------------------------------------------
int APP_DesignatMenuItem(void* pTagFunc,char *pTagTitle)
{
	if(pMenuUiTable)
		pMenuUiTable->ShowState=_GUI_MENU_RUN;
	tMenuEnterTag.pFunMenu=(fMenuFun)pTagFunc;
	tMenuEnterTag.pText = pTagTitle;
	return EVENT_ENTER;
}

//====================================================================
//����:  ����˵���ʾ��
//��������:pMenu �˵��ṹ��index�����line�к�(1~n)
//�������:pOutShow ��ʾ���
//---------------------------------------------------------------
void ShowMenuItem(void *pMenu,int index,int line,char *pOutShow)
{
	CMenuItemStru *pItem=(CMenuItemStru *)pMenu;
	API_sprintf(pOutShow,"%d.%s",line,pItem[index].pText);
}
//====================================================================
//����:  ��׼SDK��ʾ����˵���
//����:  ��ʾ������������pMenuUiTable����Ĳ˵�
//��������:��
//�������:�˵�ִ�н��
//ע:�ı��� pWindow ��Ҫ����show,û�ı䲻��
//---------------------------------------------------------------
int APP_ShowProsseMenu(void)
{
	CMenuUITable *pStartMenuAdd=pMenuUiTable;
	u32 event,ret;
	while(pMenuUiTable)
	{
		if(pMenuUiTable->ShowState == _GUI_MENU_RUN)
		{
			goto Addr_SCAD_MenuItem;
		}
		if(pMenuUiTable->ShowFont == 0xff)
		{//----����ʾ�ַ�--------
			API_GUI_CreateWindow(NULL,NULL,TCANCEL,pMenuUiTable->fBackColour);
			API_GUI_Show();
		}
		else
		{
			if(pMenuUiTable->fBackColour==NULL) pMenuUiTable->fBackColour=&API_FillMenuBack;
			API_GUI_CreateWindow(pMenuUiTable->pTitle,NULL,TCANCEL,pMenuUiTable->fBackColour);
			API_GUI_Menu(pMenuUiTable->pItem,ShowMenuItem,pMenuUiTable->TeamTatla,pMenuUiTable->TeamCurr,pMenuUiTable->ShowHead,pMenuUiTable->pAfterText,pMenuUiTable->pKeyFunc);
			API_GUI_Show();
		}
		//----------��ʾ�˵�---------------------
	//	pMenuUiTable->ShowState=_GUI_MENU_PROCESS;
		//----------����˵�----------------------
		event=API_WaitEvent(pMenuUiTable->TimeOutMs,EVENT_UI|EVENT_ABS,EVENT_NONE);	
		if(event==EVENT_INDEX)
		{
			int index,head;
			index=API_GUI_Menu_GetInxAndHear(&head);
			ret = EVENT_NONE;
			if(index<pMenuUiTable->TeamTatla)
			{
				pMenuUiTable->ShowHead=head;
			Addr_Specify_menu:
				pMenuUiTable->TeamCurr=index;
				pMenuUiTable->ShowState=_GUI_MENU_SHOW; //ִ������ʾ�˵�
				if(pMenuUiTable->pUnifiedFunc)
				{//-----ͳһ�˵�����----------
					ret=(*pMenuUiTable->pUnifiedFunc)(pMenuUiTable->pItem[index].pText,index);
				}
				else if(pMenuUiTable->pItem[index].pFunMenu)
				{//-----�����˵�����------
					ret=(*pMenuUiTable->pItem[index].pFunMenu)(pMenuUiTable->pItem[index].pText);
				}
				if(ret&EVENT_QUIT)		//ָ���˳����ٲ�
				{
					if(_GUI_MENU_EXT == ReturnToPreviousMenu(ret&0x0F,pStartMenuAdd))
						break;
				}
				if(ret&EVENT_ENTER)		//ָ������˵�
				{
					while(pMenuUiTable)
					{
					Addr_SCAD_MenuItem:
						for(index=0;index<pMenuUiTable->TeamTatla;index++)
						{
							if(tMenuEnterTag.pFunMenu)
							{
								if(tMenuEnterTag.pFunMenu == pMenuUiTable->pItem[index].pFunMenu)
									goto Addr_Specify_menu;
							}
							if(tMenuEnterTag.pText)
							{
								if(strcmp(tMenuEnterTag.pText,pMenuUiTable->pItem[index].pText) == 0)
									goto Addr_Specify_menu;
							}
						}
						if(_GUI_MENU_EXT == ReturnToPreviousMenu(1,pStartMenuAdd))
							break;
					}
					break;
				}
			}
		}
		else if(event==EVENT_CANCEL)
		{
			if(_GUI_MENU_EXT == ReturnToPreviousMenu(1,pStartMenuAdd))
				break;
	//		else
	//			pMenuUiTable->ShowState=_GUI_MENU_SHOW;
		}
		else if(event==EVENT_TIMEOUT)
		{
			if(_GUI_MENU_EXT == ReturnToPreviousMenu(1,pStartMenuAdd))
				break;
	//		else
	//			pMenuUiTable->ShowState=_GUI_MENU_SHOW;
		}
		else if(event==(EVENT_KEY|3))//K_FUNC
		{
			if(pMenuUiTable->pKeyFunc==NULL)
				continue;
			pMenuUiTable->ShowState=_GUI_MENU_SHOW; //ִ������ʾ�˵�
			ret=pMenuUiTable->pKeyFunc(pMenuUiTable->pKeyFuncTitle);
			if(EVENT_QUIT&ret)
			{//-----�˳����в˵�----------
				ReturnToPreviousMenu(ret&EVENT_INDEX,pStartMenuAdd);
				break;
			}
		}
	}
	return ret;
}
//===================�̶��˵�����=================================================
void ShowFixedMenutem(void *pMenu,int index,int line,char *pOutShow)
{
	tMenuItemStru *pItem=(tMenuItemStru *)pMenu;
	API_sprintf(pOutShow,"%d.%s",line,pItem[index].pText);
}

int APP_ShowFixedMenu(char* pTitle,const FixedMenuUITable *pFixedMenu,void* pTagFunc)
{
	int ret;
	u8 ShowHead=0,TeamCurr=0,TeamTatla;
	
	if(pFixedMenu->pInFunc)
	{
		ret=(*pFixedMenu->pInFunc)(pTitle);
		if(ret == EVENT_QUIT) return ret;
	}
	TeamTatla=pFixedMenu->TeamTatla;
	if(TeamTatla == 0)
	{
		while(pFixedMenu->pItem[TeamTatla++].pText);
	}
	if(pTagFunc)
	{
		tMenuEnterTag.pFunMenu=(fMenuFun)pTagFunc;
		goto Addr_SCAD_FixedMenuItem;
	}
	while(1)
	{
 		API_GUI_CreateWindow(pTitle,NULL,TCANCEL,API_FillMenuBack);
		API_GUI_Menu(pFixedMenu->pItem,ShowFixedMenutem,TeamTatla,TeamCurr,ShowHead,NULL,NULL);
		API_GUI_Show();
		ret=API_WaitEvent(pFixedMenu->TimeOutMs,EVENT_UI|EVENT_ABS,EVENT_NONE);	
		if(ret == EVENT_INDEX)
		{
			TeamCurr=API_GUI_Menu_GetInxAndHear(&ret);
			if(TeamCurr < TeamTatla)
			{
				ShowHead=ret;
			Addr_Specify_Fixedmenu:
				switch(pFixedMenu->pItem[TeamCurr].FunType)
				{
					case FUN_MENU_F:
						ret=(*(fMenuFun)pFixedMenu->pItem[TeamCurr].pFun)(pFixedMenu->pItem[TeamCurr].pText);
						break;
					case FUN_MENU_I:
						ret=(*(APP_IndexH)pFixedMenu->pItem[TeamCurr].pFun)(pFixedMenu->pItem[TeamCurr].pText , TeamCurr);
						break;
					case FUN_MENU_G:
						ret=APP_ShowFixedMenu(pFixedMenu->pItem[TeamCurr].pText,(FixedMenuUITable *)pFixedMenu->pItem[TeamCurr].pFun ,NULL);
						break;
				}
				if(ret&EVENT_QUIT)		//�˳����в˵�
				{
					if(ret&EVENT_INDEX)
					{
						ret--;
						break;
					}
 				}
				if(ret&EVENT_ENTER)		//ָ������˵�
				{
					if(ret&EVENT_INDEX)	//ָ������˵��ⲿ
						break;
				Addr_SCAD_FixedMenuItem:
					for(TeamCurr=0;TeamCurr<TeamTatla;TeamCurr++)
					{
						if(tMenuEnterTag.pFunMenu)
						{
							if((void*)tMenuEnterTag.pFunMenu == pFixedMenu->pItem[TeamCurr].pFun)
								goto Addr_Specify_Fixedmenu;
						}
						if(tMenuEnterTag.pText)
						{
							if(strcmp(tMenuEnterTag.pText,pFixedMenu->pItem[TeamCurr].pText) == 0)
								goto Addr_Specify_Fixedmenu;
						}
					}
					break;
				}
			}
		}
		else if(ret==EVENT_CANCEL || ret==EVENT_TIMEOUT)
		{
			break;
		}
	}
	if(pFixedMenu->pOutFunc)
	{
		(*pFixedMenu->pOutFunc)(pTitle);
	}
	return ret;
}



