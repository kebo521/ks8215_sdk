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
		
	"确认",        
	"取消",	       
	"成功",        
	"失败",        
	"请充电",      
	"正在关机",    
	"输入已满",    
	"输入位数不足",
	                       
	"软件升级",            
	"有版本需要更新",      
	"更新中,请不要关机",   
	"按[确认]键继续",
	"下载完成,检查数据",
	"校验失败",
	"下载失败",
	"创建文件失败",

	"固件升级",
	"检查升级包",
	"验证签名错",
	"计算签名错",
	"正在安装",
	"应用安装",
	"主控安装",
	                       
	"    [数字]键输入数字",
	"[数字]键输入小写字母",
	"[数字]键输入大写字母",
	"按[0]键下翻页",       
	"按[8]键上翻页",       
	"[8]上翻页,[0]下翻页", 
	"摄像头初始化失败",
};

const KS_LANGUAGE tLanguageJP={
	"ksJ",
		
	"確認",        
	"取り消す",	       
	"成功",        
	"失敗",        
	"充電してください",      
	"シャットダウン",    
	"入力済み",    
	"入力桁が足りない",
	                       
	"ソフトウェアのアップグレード",            
	"バージョンアップする必要があります",      
	"更新中にシャットダウンしないでください",   
	"[確認]ボタンを押し続ける",
	"ダウンロード完了",
	"検証に失敗しました",
	"ダウンロード失敗",
	"ファイル作成失敗",
	
	"アップグレード",
	"パッケージをチェック",
	"署名エラーを確認",
	"署名エラーを計算する",
	"インストール中",
	"APP インストール",
	"TMS インストール",
	                       
	"    [数字]を入力する",
	"[数字]小文字を入力す",
	"[数字]大文字を入力す",
	"[0]ページを打つ",       
	"[8]ページアップ",       
	"[8]上向き,[0]下向き", 
	"カメラ初期化失敗",
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
	{//-----当作指针处理---支持导入显示模块------
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
	char* pTraceMenu[]={"English","中文","日本語"};
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
			APP_ShowSta(pTitle,"设置为中文");
			API_SetLanguage(1);
		}
		else if((Event&0xff)==K_3)
		{
			APP_ShowSta(pTitle,"设置为日本語");
			API_SetLanguage(2);
		}
		else return -1;
		//----------加载对应语言---------------------
		APP_WaitUiEvent(2000);
	}
	return 0;
}








