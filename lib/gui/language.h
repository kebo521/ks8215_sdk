#ifndef _KS_LANGUAGE_
#define _KS_LANGUAGE_

typedef struct
{
	char Flaglang[4];
	char *pOK;
	char *pCancel;
	char *pSuccess;
	char *pFailed;
	char *pPlsChg;
	char *pShuDown;
	char *pEditFull;
	char *pLackInput;

	char *pSoftwareUpdate;
	char *pCheckUpdate;
	char *pUpdating;
	char *pPressContinue;
	char *pDowloadCompleted;
	char *pVerifyFailed;
	char *pDownloadFailed;
	char *pCreateFileFailed;
		
	char *pFirmUp;
	char *pCheckPackage;
	char *pVerifySignErr;
	char *pCalcSignErr;
	char *pInstalling;
	char *pAppInstalling;
	char *pTmsInstalling;

	char *pInputNumber;
	char *pInputLletters;
	char *pInputUletters;
	char *pKeyDownMsg;
	char *pKeyUpMsg;
	char *pKeyUpDownMsg;
	char *pKeyScanInitErr;
}KS_LANGUAGE;

extern KS_LANGUAGE sLanguageIndex;


#define TOK							sLanguageIndex.pOK
#define TCANCEL						sLanguageIndex.pCancel
#define STR_SUCCESS					sLanguageIndex.pSuccess
#define STR_FAILED					sLanguageIndex.pFailed
#define STR_UI_PLS_CHG				sLanguageIndex.pPlsChg
#define STR_UI_SHU_DOWN				sLanguageIndex.pShuDown
#define STR_EDIT_FULL				sLanguageIndex.pEditFull
#define STR_LACK_INPUT				sLanguageIndex.pLackInput

#define STR_SOFTWARE_UPDATA			sLanguageIndex.pSoftwareUpdate
#define STR_CHECK_UPDATA			sLanguageIndex.pCheckUpdate
#define STR_PRESS_OK_UPDATE			sLanguageIndex.pUpdating
#define STR_PRESS_OK_CONNET			sLanguageIndex.pPressContinue
#define STR_DOWNLOAD_COMPLETED		sLanguageIndex.pDowloadCompleted
#define STR_VERIFY_FAILED			sLanguageIndex.pVerifyFailed
#define STR_DOWNLOAD_FAILED			sLanguageIndex.pDownloadFailed
#define STR_CREATE_FILE_FAILED		sLanguageIndex.pCreateFileFailed

#define STR_FIRMWARE_UPGRADE		sLanguageIndex.pFirmUp
#define STR_CHECK_PACKAGE			sLanguageIndex.pCheckPackage
#define STR_VERIFY_SIGN_ERR			sLanguageIndex.pVerifySignErr
#define STR_CALC_SIGN_ERR			sLanguageIndex.pCalcSignErr
#define STR_INSTALLING				sLanguageIndex.pInstalling
#define STR_APP_INSTALLING			sLanguageIndex.pAppInstalling
#define STR_TMS_INSTALLING			sLanguageIndex.pTmsInstalling

#define STR_KEY_INPUT_NUMBER		sLanguageIndex.pInputNumber
#define KEY_INPUT_LOWERCASE_LETTERS	sLanguageIndex.pInputLletters
#define KEY_INPUT_UPPERCASE_LETTERS	sLanguageIndex.pInputUletters
#define STR_KEY_DOWT				sLanguageIndex.pKeyDownMsg
#define STR_KEY_UP					sLanguageIndex.pKeyUpMsg
#define STR_KEY_UPDOWT				sLanguageIndex.pKeyUpDownMsg

#define STR_SCAN_ERR_INIT			sLanguageIndex.pKeyScanInitErr


extern void API_InitSysLanguage(u8 index);
extern int API_SetLanguage(unsigned int language);

extern int APP_SetLanguage(char* pTitle);




#endif

