#include "comm_type.h"
#include "EvenMsg.h"
#include "input_hand.h"
#include "xui_ui.h"
#include "xui_font.h"
#include "xui_gui.h"
#include "language.h"


const KS_LANGUAGE tLanguageEn={
	"ksE",
		
	"OK",									
	"Cancel",							
	"SUCCESS",							
	"FAILED",							
	"Pls charge the power",
	"Powering off", 			
	"The input is full",		
	"Lack input",					
								
	"Software update",				
	"Check version updates",
	"Pls do not shut down", 
	"Press[OK]to continue",
	"Download completed",
	"Verification failed",
	"Download failed",
	"Create file Failed",

	"Firmware upgrade",
	"Check the package",
	"Verify sign error",
	"Calc sign error",
	"Installing",
	"APP Installing",
	"TMS Installing",
							
	"[number mode]",					
	"[lowercase  ]",				
	"[uppercase  ]",				
	"key[0] Page down", 	
	"key[8] Page up",			
	"key[8]up,key[0]down",
	
	"Failed to initialize camera",
};

const KS_LANGUAGE tLanguageChn={
	"ksC",
		
	"ȷ��",        
	"ȡ��",	       
	"�ɹ�",        
	"ʧ��",        
	"����",      
	"���ڹػ�",    
	"��������",    
	"����λ������",
	                       
	"�������",            
	"�а汾��Ҫ����",      
	"������,�벻Ҫ�ػ�",   
	"��[ȷ��]������",
	"�������,�������",
	"У��ʧ��",
	"����ʧ��",
	"�����ļ�ʧ��",

	"�̼�����",
	"���������",
	"��֤ǩ����",
	"����ǩ����",
	"���ڰ�װ",
	"Ӧ�ð�װ",
	"���ذ�װ",
	                       
	"    [����]����������",
	"[����]������Сд��ĸ",
	"[����]�������д��ĸ",
	"��[0]���·�ҳ",       
	"��[8]���Ϸ�ҳ",       
	"[8]�Ϸ�ҳ,[0]�·�ҳ", 
	"����ͷ��ʼ��ʧ��",
};

const KS_LANGUAGE tLanguageJP={
	"ksJ",
		
	"�_�J",        
	"ȡ������",	       
	"�ɹ�",        
	"ʧ��",        
	"��늤��Ƥ�������",      
	"����åȥ�����",    
	"�����g��",    
	"�����줬���ʤ�",
	                       
	"���եȥ������Υ��åץ���`��",            
	"�Щ`����󥢥åפ����Ҫ������ޤ�",      
	"�����Ф˥���åȥ����󤷤ʤ��Ǥ�������",   
	"[�_�J]�ܥ����Ѻ���A����",
	"�������`������",
	"���^��ʧ�����ޤ���",
	"�������`��ʧ��",
	"�ե���������ʧ��",
	
	"���åץ���`��",
	"�ѥå��`��������å�",
	"��������`��_�J",
	"��������`��Ӌ�㤹��",
	"���󥹥ȩ`����",
	"APP ���󥹥ȩ`��",
	"TMS ���󥹥ȩ`��",
	                       
	"    [����]����������",
	"[����]С���֤�������",
	"[����]�����֤�������",
	"[0]�ک`������",       
	"[8]�ک`�����å�",       
	"[8]����,[0]����", 
	"�������ڻ�ʧ��",
};

KS_LANGUAGE sLanguageIndex;


//=APP_LoadCustomizeLanguage
int API_LoadSysLanguage(const KS_LANGUAGE *pL)
{
	if(pL->Flaglang[0]=='k' && pL->Flaglang[1]=='s')
	{
		memcpy(&sLanguageIndex,pL,sizeof(sLanguageIndex));	
		return 0;
	}
	return -1;
}

void API_InitSysLanguage(u8 index)
{
	switch( index )
    {
        case 0: API_LoadSysLanguage(&tLanguageEn); break;
        case 1: API_LoadSysLanguage(&tLanguageChn); break;
        case 2: API_LoadSysLanguage(&tLanguageJP); break;
        default : API_ShowLineEn(5,"Language Index Err",5*1000);
    }
}

int API_SetLanguage(unsigned int language)
{
/*
	if(tAdminTermPar.language == language)
		return 1;
	if(language>300)
	{//-----����ָ�봦��---֧�ֵ�����ʾģ��------
		return API_LoadSysLanguage((const KS_LANGUAGE *)language);
	}
	API_InitSysLanguage(language);
	tAdminTermPar.language=language;
	APP_SetTermPar(&tAdminTermPar);
	*/
	return 0;
}

int APP_SetLanguage(char* pTitle)
{
	char* pTraceMenu[]={"English","����","�ձ��Z"};
	u32 Event;
	APP_GUI_Menu(pTitle,0,sizeof(pTraceMenu)/sizeof(pTraceMenu[0]),0,pTraceMenu);//tAdminTermPar.language
	Event=API_WaitEvent(30*1000,EVENT_KEY,EVENT_NONE);
	if(Event&EVENT_KEY)
	{
		if((Event&0xff)==K_1)
		{
			APP_ShowSta(pTitle,"SET English");
			API_SetLanguage(0);
		}
		else if((Event&0xff)==K_2)
		{
			APP_ShowSta(pTitle,"����Ϊ����");
			API_SetLanguage(1);
		}
		else if((Event&0xff)==K_3)
		{
			APP_ShowSta(pTitle,"����Ϊ�ձ��Z");
			API_SetLanguage(2);
		}
		else return -1;
		//----------���ض�Ӧ����---------------------
		APP_WaitUiEvent(2000);
	}
	return 0;
}








