/*
 * emvspi_plugin.c
 *
 * KSDK����emvporting��ʵ��
 *
 *  Created on: 2014-10-14
 *      Author: wangyun
 *
 */

#include "comm_type.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "xui_comm.h"
#include "sys_sdk.h"
#include "emv_type.h"
#include "emvapi.h"


// ���Ӧ�ø���
#define APPS_MAX_NUM                32
#if(0)

/**
 * @brief ����UI��ʾȷ����Ϣ
 * @param title ��ʾ����
 * @param msg ��ʾ��Ϣ
 * @param confirm �Ƿ���ȷ����ʾ��Ϣ
 * @param timeout ��ʱʱ��
 * 
 * @return ȷ�Ϸ���1��ȡ����ʱ����0
 */
int emvspi_ui_message(const char* title, const char* msg, int confirm, int timeout_s)
{
    int ret;
	if(confirm) 
		APP_GUI_OnlyThisHasBtn();
	APP_GUI_OnlyThisHasTitle();
	ret=APP_ShowMsg((char*)title,(char*)msg,timeout_s*1000);
	APP_ShowSta((char*)title, "���ڴ�������ο���"); // ȷ����ɼ�����ʾIC��������
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
    else if(ret==EVENT_TIMEOUT)
    	return EMV_OPER_TIMEOUT;
	return EMV_OPER_CANCEL;
}

/**
 * ��ʾ��ʾ��Ϣ����������ʾ����
 *
 * @param   id  ��ʾ��Ϣ�������ο�{@link EMV_MessageIDs}
 * @return  ����������£�����ο�{@link EMV_OperResults}��ע��
 * @return  {@link EMV_OPER_OK}
 * @return  {@link EMV_OPER_CANCEL}
 * @return  {@link EMV_OPER_TIMEOUT}
 * @return  {@link EMV_OPER_UNSUPPORTED}
 */
int emvspi_message(int id) 
{
    /*
    EMV_MSG_CONFIRM_FORCE_ONLINE,                           //!< ȷ���Ƿ�ǿ������������ֵ���ǣ����֧�֣�
    EMV_MSG_CONFIRM_PIN_BYPASS,                             //!< ȷ���Ƿ�����PIN���루����ֵ���ǣ����֧�֣�

    EMV_MSG_PROMPT_CAPK_NOT_FOUND,                          //!< ��ʾCA��Կδ�ҵ�������ֵ��ȷ�ϻ�֧�֣�
    EMV_MSG_PROMPT_CAPK_EXPIRED,                            //!< ��ʾCA��Կ�ѹ��ڣ�����ֵ��ȷ�ϻ�֧�֣�
    EMV_MSG_PROMPT_CAPK_INVALID,                            //!< ��ʾCA��Կ�����ã�����ֵ��ȷ�ϻ�֧�֣�

    //CID(9F27)��Ӧ��ԭ��/֪ͨ/��Ȩ�ο���
    EMV_MSG_PROMPT_ServiceNotAllowed,                       //!< ��ʾ��������񣨷���ֵ��ȷ�ϻ�֧�֣�
    EMV_MSG_PROMPT_PinTryLimitExceeded,                     //!< ��ʾPIN���Դ������ޣ�����ֵ��ȷ�ϻ�֧�֣�
    EMV_MSG_PROMPT_IssuerAuthenticationFailed,              //!< ��ʾ��������֤ʧ�ܣ�����ֵ��ȷ�ϻ�֧�֣�

    EMV_MSG_PROMPT_AtCardBlacklist,                         //!< ��ʾ��������������ֵ��ȷ�ϻ�֧�֣�
    EMV_MSG_PROMPT_AppExpiration,                           //!< ��ʾӦ��ʧЧ���ѹ�ʧЧ���ڣ�������ֵ��ȷ�ϻ�֧�֣�
    */
    return EMV_OPER_OK;
}




/**
* ��ʾ���ȴ��û��ƿ���QPBOC��
*
* @return  {@link EMV_OPER_OK}				   �ɹ�
* @return  {@link EMV_OPER_REPORT_APP}		   ������֮���ں˻᷵��{@link EMV_REQ_DEACTIVATE_CARD}
*/
int emvspi_deactivate_card(void)
{


	return EMV_OPER_OK;
}
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief ��ʾ�ֿ���֤��ȷ�Ͻ����Ƿ����(PBOC)
 * @param typ ֤������
 * @param cno ֤����
 * @param cnolen ֤���ų���
 * @return [0]-������ [1]-����
 */
int emvspi_ack_examine_cred(u8 type, const u8 *num, int numlen)
{
	int ret;
	char typestr[][12] = {"���֤", "����֤", "����", "�뾳֤", "��ʱ���֤", "����"};
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "���ʾ֤��:\n");
	API_sprintf(buf, "����:%s\n",typestr[type]);
	API_strcat(info, buf);
	API_memset(buf, 0, sizeof(buf));
	if(numlen<(int)sizeof(buf))
		API_memcpy(buf, num, numlen);
	API_strcat(info, buf);
	while(1)
	{
		APP_GUI_OnlyThisHasTitle();
		APP_GUI_OnlyThisHasBtn();
		APP_GUI_Win("�ֿ�����֤","ȷ�ϼ���", "����ȡ��");
		API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info);	
		API_GUI_Show();
		ret = APP_WaitUiEvent(TIMEOUT_SHOW);
		if(ret==EVENT_OK)
			return 1;
		return 0;
	}

}

/**
 * �Ӻ�ѡӦ���б���ѡ��Ӧ��.
 *
 * @param   again                                   �ٴ�ѡ��ı��
 * @param   candidates                              ��ѡӦ���б�!NULL��
 * @param   candidates_num                          ��ѡӦ�ø�����>0��
 * @return  [0 ~ candidates_num-1]                  ѡ��Ӧ�ö�Ӧ��ѡӦ���б������
 * @return  {@link EMV_OPER_CANCEL}                 ȡ��
 * @return  {@link EMV_OPER_TIMEOUT}                ��ʱ
 *
 * @note    ���Ӧ��ѡ��֧�ֳֿ���ȷ�ϣ���ô����ֱ�ӷ���0��Ĭ��ѡ���һ��Ӧ�ã�
 */
int emvspi_choice_app_form_candidates(int again, EMV_CANDIDATE* candidates, int candidates_num)
{
	int 	i, ret = 0;
	char*   title = NULL;
	char*   item[APPS_MAX_NUM] = {NULL};
	char    release_name[APPS_MAX_NUM][33];

	if (again)
		title = "������ѡ��Ӧ��:";
	else
		title = "��ѡ��Ӧ��:";

	for (i = 0; i < candidates_num; i++)
	{
		if (candidates[i].preferred_name_len == 0)
		{
			API_Conv_BcdToStr(candidates[i].aid, candidates[i].aid_len, release_name[i]);
		}
		else
		{
			API_memcpy(release_name[i], candidates[i].preferred_name, candidates[i].preferred_name_len);
			*(release_name[i] + candidates[i].preferred_name_len) = 0;
		}
		item[i] = release_name[i];
	}
	APP_GUI_OnlyThisHasTitle();	//ǿ�����ñ���
	ret = APP_RdoMenu(title,NULL,candidates_num, 0, (const char**)item);
	APP_ShowSta(title,"���ڴ�������ο���");
	if (ret < 0 || ret >= candidates_num)
	{
	    return EMV_OPER_CANCEL;
	}
	return ret;
}

/**
 * ����PIN
 * @param   type                                    ����
 *          @arg =0                                 ��������
 *          @arg =1                                 �ѻ����루��ʾ���һ�λ��ᣩ
 *          @arg >1                                 �ѻ�����
 * @param   output                                  ������棨�����������256���ѻ��������12��
 * @return  >0                                      ������ȣ���������<=256��4<=�ѻ�����<=12��
 * @return  {@link EMV_OPER_BYPASS}                 �����루����������ֱ�Ӱ�ȷ�ϼ��������룩
 * @return  {@link EMV_OPER_UNSUPPORTED}            ��֧�ֻ����쳣
 * @return  {@link EMV_OPER_TIMEOUT}                ��ʱ�˳�
 * @return  {@link EMV_OPER_CANCEL}                 ����ȡ��
 * @return  {@link EMV_OPER_QUIT}                   �����˳�
 *
 * @note    ����PIN����ʱ�����������Ӧ���Զ����ʽ���ں�ֻ���𱣴�\n
 *          �ѻ�PIN����ʱ��������ݱ�����PIN�������ַ��������磺����="123456"����ôoutput="123456"������ֵ6
 */
int emvspi_pin_entry(u8 type, u8* output, int* outlen)
{
    int ret;
    u32 Len;
	u8	Min,Max,KeyIndex;
	char magStrBuf[17];
    u8 buf[20] = {0};
    u8 key[16];
    if (type == 0) {
		Min=6; Max=6;
		KeyIndex=USAGE_WKEK_INDEX;
		APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"��������������:");
    } else if (type == 1) {
    	Min=4; Max=12;
		KeyIndex=2;
   		APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"���һ���ѻ����룺");
    } else {
    	Min=4; Max=12;
		KeyIndex=2;
    	APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"�������ѻ����룺");
    }
	if(g_MagCard_Pan.m_MagCardFlag)
		API_Conv_BcdToStr(g_MagCard_Pan.MagCardPan+2,6, magStrBuf);
	else API_memset(magStrBuf,'0',12);
	API_PCI_SetPinblock_Xor_Padding(magStrBuf,NULL);
	API_PCI_SetPrompt(g_PEVar_Data.MenuInfo,"���������п�����:","ע����߰�ȫ",gInputMoney.InputMoneyData);
	APP_PlayTradeVoice("plspass.wav");	//�����������������
	ret=API_PCI_GetPin(KeyIndex,PIN_VOICE_PWD,Min,Max,TYPE_ANSI98,0,buf,16,&Len,Term_Par.InputTimeOut[0]);
	if(ret==RET_OK) //suc
	{
		APP_ShowSta(g_PEVar_Data.MenuInfo, "���ڴ�������ο���");
		if (type == 0)
		{
			API_memcpy(output, buf, 8);
			if(outlen) *outlen=8;
			return EMV_OPER_OK;
		}
		else
		{
			CLEAR(key);
			Des_B2Dec(buf,key,1);
			API_Conv_BcdToStr(buf+1, 6, (char*)output);
			*(output + buf[0]) = 0;
			if(outlen) *outlen=buf[0];
			return EMV_OPER_OK;
		}
	}
	if(ret==RET_PCI_PWD_NULL)
	{//δ��������ֱ�Ӱ�ȷ��
		return EMV_OPER_BYPASS;		
	}
	if(ret==RET_PCI_USER_CANCEL)
	{
		return EMV_OPER_CANCEL;
	}
	if(ret==RET_PCI_USER_TIMEOUT)
	{
		APP_ShowMsg(g_PEVar_Data.MenuInfo,"���볬ʱ",3000);
		g_UIData.m_OperSta=OPER_TIMEOUT;
		return EMV_OPER_TIMEOUT;
	}
	if(ret==RET_DEVICE_MALFUNCTION)
	{
		APP_ShowMsg(g_PEVar_Data.MenuInfo,"δ��⵽�������",3000);
		return EMV_OPER_QUIT;
	}
	API_sprintf(magStrBuf,"δ֪����[%d]",ret);
	APP_ShowMsg(g_PEVar_Data.MenuInfo,magStrBuf,3000);
	g_UIData.m_OperSta=OPER_QUIT;
	return EMV_OPER_UNSUPPORTED;

}


/**
   * ȷ���Ƿ���������Уɣ�
   *
   * @return  {@link EMV_OPER_OK}				  ����
   * @return  {@link EMV_OPER_CANCEL}			  ������
   * @return  {@link EMV_OPER_UNSUPPORTED}		  ��֧��
   * @return  {@link EMV_OPER_REPORT_APP}		  ������֮���ں˻᷵��{@link EMV_REQ_CONFIRM_BYPASS_PIN}
   */
int emvspi_confirm_bypass_pin(void)
{
	int ret = 0;    
	APP_GUI_OnlyThisHasBtn();//����Ҫ�а�ť��
	APP_GUI_Win(NULL,TOK,INFO_CANCER);
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP, "ȷ���Ƿ�����PIN����?");
	API_GUI_Show();
	ret=APP_WaitUiEvent(TIMEOUT_CHK);
	APP_DispMsg("���ڴ�������ο���");
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
	return EMV_OPER_CANCEL;
}
/**
	* ȷ���Ƿ�ǿ������
	*
	* @return  {@link EMV_OPER_OK}				   ǿ������
	* @return  {@link EMV_OPER_CANCEL}			   ��ǿ������
	* @return  {@link EMV_OPER_UNSUPPORTED} 	   ��֧��
	* @return  {@link EMV_OPER_REPORT_APP}		   ������֮���ں˻᷵��{@link EMV_REQ_CONFIRM_FORCE_ONLINE}
	*/
int emvspi_confirm_force_online(void)
{
	int ret = 0;	
	APP_GUI_OnlyThisHasBtn();//����Ҫ�а�ť��
	APP_GUI_Win(NULL,TOK,INFO_CANCER);
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP, "ȷ���Ƿ�ǿ������?");
	API_GUI_Show();
	ret=APP_WaitUiEvent(TIMEOUT_CHK);
	APP_DispMsg("���ڴ�������ο���");
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
	return EMV_OPER_CANCEL;
}

/**
	* ����������Ȩ
	*
	* @param   resp 							   [OU]��Ȩ��Ӧ���ݣ��൱��55�����ݣ�TLV��ʽ��������Ȩ��Ӧ�룩
	* @param   resplen							   [OU]��Ȩ��Ӧ���ݳ���
	* @return  {@link EMV_ONLINE_NOT}			   δ������������ֹ
	* @return  {@link EMV_ONLINE_FAIL}			   ����ʧ��
	* @return  {@link EMV_ONLINE_SUCC_ACCEPT}	   �����ɹ�����������׼
	* @return  {@link EMV_ONLINE_SUCC_DENIAL}	   �����ɹ��������оܾ�
	* @return  {@link EMV_ONLINE_SUCC_ISSREF}	   �����ɹ���������ָ��
	* @return  {@link EMV_OPER_REPORT_APP}		   ������֮���ں˻᷵��{@link EMV_REQ_GO_ONLINE}
	*/
int emvspi_go_online(u8* resp, int* resplen)
{
	return EMV_OPER_REPORT_APP;
}

/**
 * �����вο���������ȷ�Ͻ����Ƿ�������ܣ�
 *
 * @param   pan                                 [IN]Ӧ�����˺�
 * @param   panlen                              [IN]Ӧ�����˺ų���
 * @return  {@link EMV_OPER_OK}                 �������
 * @return  {@link EMV_OPER_CANCEL}             ����ܾ�
 * @return  {@link EMV_OPER_UNSUPPORTED}        ��֧��
 * @return  {@link EMV_OPER_REPORT_APP}         ������֮���ں˻᷵��{@link EMV_REQ_ISSUER_REFERRAL}
 */
int emvspi_issuer_referral(u8* pan, int panlen)
{
/*
	int i, ret;
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "����ϵ�������:\n");
	API_strcat(info,"Ӧ�����ʺ�:\n");

	API_Conv_BcdToStr(pan,panlen,buf);
	for (i = 0; i < panlen*2; i++) 
	{
		if(buf[i]<'0'||buf[i]>'9') break;
	}	
	buf[i]='\0';
	API_strcat(info, buf);
	while(1)
	{
		APP_GUI_OnlyThisHasTitle();
		APP_GUI_OnlyThisHasBtn();
		APP_GUI_Win("�ֿ�����֤","��׼","�ܾ�");
		API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info);	
		API_GUI_Show();
		ret = APP_WaitUiEvent(TIMEOUT_SHOW);
		if(ret==EVENT_OK)
			return EMV_OPER_OK;
		return EMV_OPER_CANCEL;
	}*/
	return EMV_OPER_OK;
}

/**
 * ��Ƭ�ϵ�
 *
 * @param   comm                                    ��ƬͨѶ��ʽ{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          �ɹ�
 * @return  {@link EMV_FAIL}                        ʧ��
 */
int emvspi_icc_poweron(int comm)
{
	u8 Data[60];
	u32 nLen=60;
	if(comm==EMV_CARD_CONTACT)
	{
		if(API_ICC_PwrOn(ICC_CONTSCT))
		{
			APP_ShowMsg(NULL,"IC���ϵ�ʧ��",2000);
			return EMV_FAIL;
		}
		if(API_ICC_GetAtr(ICC_CONTSCT,Data,nLen,&nLen))
		{
			APP_ShowMsg(NULL,"IC����ȡATRʧ��",2000);
			return EMV_FAIL;
		}
		LOG_HEX(LOG_INFO, "emvplugin_icc_poweron::ATr", Data, nLen);
	}
    return EMV_OK;
}

/**
 * ��Ƭ�µ�
 *
 * @param   comm                                    ��ƬͨѶ��ʽ{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          �ɹ�
 * @return  {@link EMV_FAIL}                        ʧ��
 */
int emvspi_icc_poweroff(int comm)
{
	LOG(LOG_INFO, "emvplugin_icc_poweroff[%d]",comm);
	if(comm==EMV_CARD_CONTACTLESS)
	{
		CheckCard_SetNotRemove();
		API_ICC_PwrOff(ICC_NON_CONTSCT);
	}
	else if(comm==EMV_CARD_CONTACT)
		API_ICC_PwrOff(ICC_CONTSCT);
	else return EMV_FAIL;
    return EMV_OK;
}

/**
 * ��Ƭ��д
 *
 * @param   comm                                    ��ƬͨѶ��ʽ{@link EMV_CommunicationWays}
 * @param   input                                   �������ݣ�C-APDU��
 * @param   inlen                                   �������ݳ���
 * @param   output                                  ������ݻ��棨����SW1��SW2��
 * @param   outlen                                  ������ݳ��Ȼ���
 * @return  SW1SW2                                  ״̬�֣���0x9000,0x6A82,0x0000
 */
 
int emvspi_icc_rw(int type, u8* input, int inlen, u8* output, int* outlen)
{
    int sw;
    if (type == EMV_CARD_CONTACT)
    {
        if(RET_OK == API_ICC_Apdu(ICC_CONTSCT, input, (u32)inlen, output, 512, (u32*)outlen, (u32*)&sw))
            return sw;
    }
    else if (type == EMV_CARD_CONTACTLESS)
    {
        if (RET_OK == API_ICC_Apdu(ICC_NON_CONTSCT, input, (u32)inlen, output, 512, (u32*)outlen, (u32*)&sw))
            return sw;
    }
    return 0x0000;
}
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief ��ȡϵͳ���ں�ʱ��
 * @param date ���ڻ��棨��ʽ��YYYYMMDD, 4bytes��
 * @param time ʱ�仺�棨��ʽ��hhmmss, 3bytes��
 * @return                  [0]-�ɹ� [-1]-����.
 */
int emvspi_get_trans_date_time(u8 *date, u8 *time)
{
    DATE_TIME systime;
    API_TimeGet(&systime);
	//TRACE("DATE: %d,%d,%d", curDateTime.Year, (curDateTime.Year % 100) & 0xFF, FMT_NUMTOBCD((curDateTime.Year % 100) & 0xFF));
    if (date != NULL) {
       *(date) = APP_Conv_HexToBcd((systime.Year / 100) & 0xFF);
	    *(date + 1) = APP_Conv_HexToBcd((systime.Year % 100) & 0xFF);
	    *(date + 2) = APP_Conv_HexToBcd((systime.Month));
	    *(date + 3) = APP_Conv_HexToBcd((systime.Day));
    }

    if (time != NULL) {
        *(time) = APP_Conv_HexToBcd((systime.Hour));
	    *(time + 1) = APP_Conv_HexToBcd((systime.Min));
	    *(time + 2) = APP_Conv_HexToBcd((systime.Sec));
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * ��ʾ�ֿ���֤�����ͺͺ��룬����ʾ����ԱҪ��ֿ��˳�ʾ��Ӧ֤�����ȶ�һ�º�ȷ�Ͻ����Ƿ������PBOC��.
 *
 * @param type              ֤�����ͣ�@ref PBOC_DocumentTypes��
 * @param number            ֤�����루ASC��ʽ��
 * @param number_len        ֤�����볤��
 * @return                  [0]-�ȶԲ�һ�º�ȡ�������� [1]-�ȶ�һ�º�ȷ�ϼ���
 */
int emvspi_ack_examine_documents(u8 type, u8 *number, int number_len)
{
	int ret;
	char typestr[][12] = {"���֤", "����֤", "����", "�뾳֤", "��ʱ���֤", "����"};
	char info[128]={0};
	API_sprintf(info, "���ʾ֤��:\n����:%s\n",typestr[type]);
	API_memcpy(info+API_strlen(info), number, number_len);
	APP_GUI_OnlyThisHasTitle();
	APP_GUI_OnlyThisHasBtn();
	APP_GUI_Win("��֤�ֿ���","ȷ�ϼ���", "����ȡ��");
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info); 
	API_GUI_Show();
	ret = APP_WaitUiEvent(TIMEOUT_SHOW);
	if(ret==EVENT_OK)
		return 1;
	return 0;
}


/**
 * @brief ��ϵ������ȷ�Ͻ����Ƿ�����
 * @param pan Ӧ�����˺�
 * @param panlen Ӧ�����˺ŵĳ���
 * @return [0]-������ [1]-����
 */
int emvspi_ack_issuer_referral(u8* pan, int panlen)
{
/*
	int i, ret;
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "����ϵ�������:\n");
	API_strcat(info,"Ӧ�����ʺ�:\n");

	API_Conv_BcdToStr(pan,panlen,buf);
	for (i = 0; i < panlen*2; i++) 
	{
		if(buf[i]<'0'||buf[i]>'9') break;
	}	
	buf[i]='\0';
	API_strcat(info, buf);
	while(1)
	{
		APP_GUI_OnlyThisHasTitle();
		APP_GUI_OnlyThisHasBtn();
		APP_GUI_Win("�ֿ�����֤","��׼","�ܾ�");
		API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info); 
		API_GUI_Show();
		ret = APP_WaitUiEvent(TIMEOUT_SHOW);
		if(ret==EVENT_OK)
			return 1;
		return 0;
	}*/
	return 1;
}

#if(0)
const EMV_AIDPARAM k_emv_aidparam =
{
    .term.ics = "\xF4\xF0\xF0\xFC\xAF\xFE\xA0",
    .term.term_type = 0x22,
    .term.term_caps = "\xE0\xE9\xC8",
    .term.term_add_caps = "\xFF\x80\xF0\xF0\x01",
    .term.term_trans_qualifiers = "\x36\x00\x00\x80",

    .term.term_floor_limit = "\x00\x00\x03\xE8", //10.00

    .term.status_check_support_indicator = 1,
    .term.cl_trans_limit_exist = 0,
    .term.cl_trans_limit = "",
    .term.cl_floor_limit_exist = 0,
    .term.cl_floor_limit = "",
    .term.cvm_limit_exist = 0,
    .term.cvm_limit = "",

    .term.ec_support_indicator = 0,
    .term.ec_trans_limit_exist = 0,
    .term.ec_trans_limit = "",

    .term.sm_support_indicator = 0,

    .aid = "\xA0\x00\x00\x03\x33",
    .aid_len = 5,
    .app_sel_indicator = 0,
    .app_ver = "\x00\x8C",

    .target_percent = 20,
    .max_target_percent = 50,
    .threshold_value = "\x00\x00\x01\xF4", //5.00

    .default_ddol_len = 11,
    .default_ddol = "\x9F\x37\x04\x9F\x47\x01\x8F\x01\x9F\x32\x01",
    .default_tdol_len = 3,
    .default_tdol = "\x9F\x08\x02",

    .term_id = "",
    .term_ifd = "",

    .term_country_code = "\x01\x56",
    .trans_currency_code = "\x01\x56",
    .trans_currency_exponent = 2,
    .trans_ref_currency_code = "\x01\x56",
    .trans_ref_currency_exponent = 2,

    .term_action_code_default_exist = 0,
    .term_action_code_default = "",
    .term_action_code_online_exist = 0,
    .term_action_code_online = "",
    .term_action_code_denial_exist = 0,
    .term_action_code_denial = "",

    .term_risk_mana_data_len = 0,
    .term_risk_mana_data = "",

    .acquirer_id = "",

    .merchant_category_code = "\x00\x00",
    .merchant_id = "",
    .merchant_name = "",

    .online_pin_support_indicator = 1,
};

////////////////////////////////////////////////////////////////////////////////

/**
 * ��Կ����.
 * @param alg               ��Կ�㷨��ʶ��@see EMV_PubKeyAlgorithms��.
 * @param pk                ��Կ.
 * @param input             ǩ������.
 * @param output            �ָ�����.
 * @return                  �ָ����ݵĳ���.
 */
int emvspi_recover(int alg, EMV_PUBLICKEY *pk, u8 *input, u8 *output)
{
    //int ret;
    u32 outlen = 0;
    RSA_PUBKEY pubkey;

    if (alg == EMV_PUBKEY_ALG_RSA)
    {
        CLEAR(pubkey);
        pubkey.length = pk->rsa.modulus_len;
        API_memcpy(pubkey.modulus, pk->rsa.modulus, pk->rsa.modulus_len);
        API_memcpy(pubkey.exponent+1, pk->rsa.exponent, 3);

        //TRACE_HEX("####PK####", (u8*)&pubkey, sizeof(RSA_PUBKEY));
        //TRACE_HEX("INPUT", input, pk->rsa.modulus_len);
        API_Crypt(CRYPT_TYPE_RSA, (u8*)&pubkey, sizeof(pubkey), NULL, input, pk->rsa.modulus_len, output,pk->rsa.modulus_len,&outlen, CRYPT_MODE_ENCRYPT);
#if 0
        ret = API_Crypt_ImportPublicKey(0xFF, CRYPT_TYPE_RSA, (u8*)&pubkey, sizeof(RSA_PUBKEY));
        if (ret != CRYPT_OK)
        {
            TRACE("emvspi_recover:API_Crypt_ImportPublicKey Err[%d]", ret);
            return -1;
        }
        ret = API_Crypt_Calc_Use_PublicKey(0xFF, input, pk->rsa.modulus_len, output, &outlen, 0);

        if (ret != CRYPT_OK)
        {
            TRACE("emvspi_recover:API_Crypt Err[%d]", ret);
            return -1;
        }

#endif
        if (outlen != pk->rsa.modulus_len)
        {
        //    TRACE("emvspi_recover:outlen Err[%d != %d]", outlen, pk->rsa.modulus_len);
            return -1;
        }
    }
    else
    {
     //   TRACE("emvspi_recover:alg Err[%d]", alg);
        return -1;
    }

    API_TimeSleepMS(100);

    //TRACE_HEX("OUTPUT", output, outlen);
    return outlen;

}

 /**
 * ��ϣ����.
 * @param alg               ��ϣ�㷨��ʶ��@see EMV_HashAlgorithms��.
 * @param input             ��������.
 * @param inlen             �������ݳ���.
 * @param output            ��ϣ������.
 */
void emvspi_hash(int alg, u8 *input, int inlen, u8 *output)
{
	switch(alg) {
		case EMV_HASH_ALG_SHA1:
			API_Hash(HASH_TYPE_SHA1, input, inlen, output, 20,NULL,HASH_DIRECT);
		break;
		case EMV_HASH_ALG_SHA256:
			API_Hash(HASH_TYPE_SHA256, input, inlen, output,256,NULL,HASH_DIRECT);
		break;
	}
}

/**
 * ��ȡ�������м�������9F41��.
 *
 * @param buf               ������棨BCD��ʽ, 4�ֽڣ�.
 * @return                  [0]-�ɹ� [-1]-����.
 */
int emvspi_get_trans_sequence_counter(u8 *buf)
{
   API_memset(buf,0x00,4);
    return 0;
}

/**
 * ��ȡ�����.
 *
 * @param buf               �������.
 * @param len               �����ȡ����.
 * @return                  [0]-�ɹ� [-1]-����.
 */
int emvspi_get_random(u8* buf, int len)
{
    API_Rng(buf, len);
    //TRACE_HEX("�����", buf, len);
    return 0;
}


/**
 * ��ȡ�ն�������Ϣ.
 *
 * @param info              ������Ϣ.
 */
int emvspi_get_config(EMV_TERMPARAM* info)
{
  /*
    u8 core_idx;
    emv_param_t param;

    core_idx = emv_porting_para_get_kernel_index();
    
    if (emv_porting_para_load(&param, core_idx, 0)) 
    {
        TRACE("��ȡ���ò���ʧ��");
        return -1;
    }
    
    API_memcpy(info->ics, param.ics, 7);
    info->term_type = param.term_type;
    API_memcpy(info->term_caps, param.term_caps, 3);
    API_memcpy(info->term_add_caps, param.term_add_caps, 5);
    
    TRACE_HEX("ICS", info->ics, 7);
    TRACE_HEX("CAPS", info->term_caps, 3);
    TRACE_HEX("ADD_CAPS", info->term_add_caps, 5);
    TRACE("TERM_TYPE = [%02X]", info->term_type);


    info->sm_support_indicator = 0;
    API_strcpy((char*)info->merchant_name, "KS8123");

    //FIXME ʵ����ĿTTQҪ�����ն����͵Ȳ�����ȷ��
    if (emv_porting_para_get_kernel_index() == KERNEL_IND_QPBOC)
        API_memcpy(info->ttq, "\x26\x00\x00\x80", 4);
    else
        API_memcpy(info->ttq, "\x16\x00\x00\x80", 4);  //\x36\x00\x00\x80
    info->status_check_support = emv_porting_para_get_status_check_sw();

    emv_porting_para_get_floor_limit(info->floor_limit);
    //API_memcpy(info->floor_limit, "\x00\x00\x3A\x98", 4); //15000

    info->cl_trans_limit_exist = emv_porting_para_get_cl_trans_limit_exist();
    emv_porting_para_get_cl_trans_limit(info->cl_trans_limit);
    //API_memcpy(info->cl_trans_limit, "\x00\x00\x00\x02\x00\x00", 6); //200

    info->cl_floor_limit_exist = emv_porting_para_get_cl_floor_limit_exist();
    emv_porting_para_get_cl_floor_limit(info->cl_floor_limit);
    //API_memcpy(info->cl_floor_limit, "\x00\x00\x00\x00\x60\x00", 6); //60

    info->cvm_limit_exist = emv_porting_para_get_cvm_limit_exist();
    emv_porting_para_get_cvm_limit(info->cvm_limit);
    //API_memcpy(info->cvm_limit, "\x00\x00\x00\x00\x50\x00", 6); //50

    info->ec_trans_limit_exist = 0;
    
    API_memcpy(info,&k_emv_aidparam.term,sizeof(EMV_TERMPARAM));
    */
    
    return 0;
}


#define		PAR_EMV_AID			"emvaid.par"		//Ӧ��AID

void emvplugin_Init_term_apps(void)
{
	EMV_AIDPARAM* Fapps;
	u8	buffStr[sizeof(EMV_AIDPARAM)];
	u8 AppNum=0;
	Fapps =(EMV_AIDPARAM*)buffStr;
	API_memcpy(buffStr,"\xa0\x00\x00\x03\x33\x01\x01\xff\xff\xff\xff\xff\xff\xff\xff\xff\x07\x00\x00\x20\xd8\x40\x00\xa8\x00\x00\x10\x00\x00\x00\xd8\x40\x04\xf8\x00",sizeof(tapp_Flash));
	APP_SetBuf(PAR_EMV_AID, (u8*)Fapps,sizeof(EMV_AIDPARAM), 1);			
	API_memcpy(buffStr,"\xa0\x00\x00\x03\x33\x01\x01\x06\x00\xff\xff\xff\xff\xff\xff\xff\x09\x00\x00\x20\xd8\x40\x00\xa8\x00\x00\x10\x00\x00\x00\xd8\x40\x04\xf8\x00",sizeof(tapp_Flash));
	APP_SetBuf(PAR_EMV_AID, (u8*)Fapps, sizeof(EMV_AIDPARAM), 1+sizeof(EMV_AIDPARAM));
	AppNum=2;
	APP_SetBuf(PAR_EMV_AID, &AppNum, 1, 0);
}
/**
 * ��ȡ�ն�Ӧ���б�.
 *
 * @param apps              ����ն�֧�ֵ�Ӧ���б�.
 * @return                  �ն�֧�ֵ�Ӧ�ø���.
 */
int emvspi_get_term_apps(EMV_TERMAPP* apps)
{
    u8 AppNum,i;
	if(APP_GetBuf(PAR_EMV_AID, (u8*)&AppNum, 1, 0)==0)
		return 0;
	if(AppNum>APPS_MAX_NUM)
	{
		emvplugin_Init_term_apps();
		if(APP_GetBuf(PAR_EMV_AID, (u8*)&AppNum, 1, 0)==0)
			return 0;
	}
	for(i=0;i<AppNum;i++)
	{
		APP_GetBuf(PAR_EMV_AID, (u8*)(apps+i), sizeof(EMV_TERMAPP),1+(i*sizeof(EMV_TERMAPP)));
	}
	return AppNum;
}
/**
 * ��ȡ�ն�Ӧ�ò���.
 *
 * @param param             �ն˲���.
 * @param index             �ն�Ӧ���б������. �����ӣ���ʼ
 * @return                  [0]-�ɹ� [-1]-ʧ��.
 */
int emvspi_get_app_param(EMV_AIDPARAM *para, int index) 
{
	u8 AppNum;
	APP_GetBuf(PAR_EMV_AID, (u8*)&AppNum, 1, 0);
	if(index<AppNum)
		APP_GetBuf(PAR_EMV_AID, (u8*)para,sizeof(EMV_AIDPARAM), 1+(index*sizeof(EMV_TERMAPP)));
	else 
		return 1;
    return 0;
}

s16 emvplugin_Save_term_apps(EMV_AIDPARAM* Fapps)
{
	u8 AppNum,i;
	EMV_AIDPARAM Apps;
	APP_GetBuf(PAR_EMV_AID, (u8*)&AppNum, 1, 0);
	for(i=0;i<AppNum;i++)
	{
		APP_GetBuf(PAR_EMV_AID,(u8*)&Apps,sizeof(Apps),1+(i*sizeof(EMV_AIDPARAM)));
		if(Apps.aid_len==Fapps->aid_len && API_memcmp(Apps.aid,Fapps->aid,Apps.aid_len)==0)
			return AppNum;
	}
	APP_SetBuf(PAR_EMV_AID, (u8*)Fapps,sizeof(EMV_AIDPARAM), 1+(AppNum*sizeof(EMV_AIDPARAM)));
	AppNum++;
	APP_SetBuf(PAR_EMV_AID, (u8*)&AppNum,1, 0);
	//eTRACE(" Save_term_apps[%d]",AppNum);
	return AppNum;
}



#define PAR_EMV_PUBLCKEY "EmvKpub.par"
int emvplugin_int_term_capk(void)
{
	u8 AppNum=0;
	APP_SetBuf(PAR_EMV_PUBLCKEY, (u8*)&AppNum, 1, 0);	
}

/**
 * ��ȡCA��Կ֤��.
 *
 * @param cert              CA��Կ֤��.
 * @param pki               CA��Կ����.
 * @param rid               CA��Կ��Ӧ��RID��5Bytes��.
 * @return                  [0]-�ɹ� [-1]-ʧ��.
 */
int emvspi_get_capk(EMV_CAPKPARAM* cert, u8 pki, const u8 *rid)
{
	u8 AppNum,i;
	APP_GetBuf(PAR_EMV_PUBLCKEY, (u8*)&AppNum, 1, 0);	
	for(i=0;i<AppNum;i++)
	{
		if(APP_GetBuf(PAR_EMV_PUBLCKEY, (u8*)cert, sizeof(EMV_CAPKPARAM), 1+i*sizeof(EMV_CAPKPARAM)))
		if(cert->index==pki && 0==API_memcmp(cert->rid,rid,5))
			return 0;
	}
	return 1;
}

/**
 * @brief ���ҿ�Ƭ������
 * @param pan Ӧ��PAN�����10bytes��
 * @param panlen Ӧ��PAN����
 * @param sn Ӧ��PAN���к�
 * @return [0]-û�ҵ� [1]-���ҵ�
 */
int emvspi_find_card_blacklist(const u8* pan, int len, u8 seq)
{
    return 0;
}

/**
 * @brief ����֤�������
 * @param rid ע���Ӧ���ṩ�̱�ʶ��5bytes��
 * @param pki ��֤���Ĺ�Կ����
 * @param csn ��Կ֤�����кţ�3bytes��
 * @return [0]-û�ҵ� [1]-���ҵ�
 */
int emvspi_find_cert_blacklist(const u8* rid, u8 pki, const u8* csn)
{
    return 0;
  //return 0;
}

/**
 * @brief ��ȡ��־�еĽ��׽��
 * @param pan ��Ӧ�����˺�
 * @param panlen ���˺ų���
 * @param policy ��ȡ����
 *      @arg 0 ֻ�����һ�ʽ��׽�EMV��׼��
 *      @arg 1 ��ȡ������־�еĽ��׽���ܺ�
 * @return ���׽��
 */
u32 emvspi_read_amt_from_log(const u8* pan, u8 panlen, u8 policy)
{
    return 0;
}

/**
 * @brief �����������־
 * @param pan ���˺�
 * @param panlen ���˺ų���
 * @param amt ���׽��
 * @return [0]-�ɹ� [-1]-ʧ��
 */
int emvspi_save_amt_to_log(u8* pan, u8 panlen, u32 amount)
{
    return 0;
} 
// ��̬porting����
/*
const EMV_PORTING g_emv_porting = 
{
	API_Trace,
	API_TraceHex,
	emvspi_message,
	emvspi_choice_app_form_candidates,
	emvspi_choice_account_type,
	emvspi_deactivate_card,
	emvspi_ack_examine_cred,
	emvspi_pin_entry,
	emvspi_confirm_bypass_pin,
	emvspi_confirm_force_online,
	emvspi_go_online,
	emvspi_issuer_referral,
	emvspi_alloc_buffer,
	emvspi_icc_rw,
	emvspi_recover,
	emvspi_hash,
	emvspi_get_random,
	emvspi_get_trans_date_time,
	emvspi_get_trans_sequence_counter,
	emvspi_get_app_param,
	emvspi_get_config,
	emvspi_get_term_apps,
	emvspi_get_app_param,
	emvspi_get_capk,
	emvspi_read_amt_from_log,
	emvspi_save_amt_to_log,
	emvspi_find_card_blacklist,
	emvspi_find_cert_blacklist,
};
*/

#endif
#endif
/*
u8* emv_alloc_buffer(int* size)
{
	static u8 *pEmvBuff=NULL;
	*size=7*1024;	//7K 
	if(pEmvBuff==NULL)
		pEmvBuff=malloc(*size);
	return pEmvBuff;
}
*/
//=======================================================================================================================
#define _LANG_ID_		(1)											//0ΪӢ��	1Ϊ����
#define DS(en,ch)		((_LANG_ID_==0)?(en):(ch))					//�����Զ���
//=======================================================================================================================
 /**
 * ѡ���ʻ�����
 *
 * @return  {@link EMV_ACCOUNT_DEFAULT}         ѡ����Ĭ��-δָ����Default��
 * @return  {@link EMV_ACCOUNT_SAVINGS}         ѡ���˴����˻���Savings��
 * @return  {@link EMV_ACCOUNT_CHEQUE_DEBIT}    ѡ����֧Ʊ�˻�/����˻���Cheque/Debit��
 * @return  {@link EMV_ACCOUNT_CREDIT}          ѡ���������˻���Credit��
 * @return  {@link EMV_OPER_CANCEL}             ȡ��
 * @return  {@link EMV_OPER_TIMEOUT}            ��ʱ
 * @return  {@link EMV_OPER_UNSUPPORTED}        ��֧�ָù���
 * @return  {@link EMV_OPER_REPORT_APP}         ������֮���ں˻᷵��{@link EMV_REQ_SEL_ACCOUNTTYPE}
 */
int emvspi_choice_account_type(void)
{
    int ret = 0x00;
    // cn PBOC3.0 �ڣ��¡��� A.7 �˻�����
	const char* item[] = {
		DS("Default",		"Ĭ��"),
		DS("Savings",		"�����˻�"),
		DS("Cheque/Debit",	"֧Ʊ�˻�/����˻�"),
		DS("Credit",		"�����˻�"),
	};
	ret=APP_GUI_Menu("�˻�����ѡ��",NULL,4,0,item,30*1000);
	APP_ShowSta("���ڴ����","����ο���");
	if (ret == 0) {
		ret = EMV_ACCOUNT_DEFAULT;
	} else if (ret == 1) {
		ret = EMV_ACCOUNT_SAVINGS;
	} else if (ret == 2) {
		 ret = EMV_ACCOUNT_CHEQUE_DEBIT;
	} else if (ret == 3) {
		ret = EMV_ACCOUNT_CREDIT;
	} else {
		return EMV_OPER_CANCEL;
	}
	emv_set_account_type_selected(ret);
	return ret;
}

/**
 * �����¼��ص�����
 *
 * @param   data[0]     status
 * @param   data[1]     info
 */
void fEMVProcessCallback(u8* data)
{
	u8 status,info;
	status=data[0];
	info	=data[1];
	
	if(status==STATUS_CONTINUE)
	{
		switch(info)
		{
			case EMV_CANDIDATE_LIST: 			//!< notify Application show Application Candidate List
				emv_set_candidate_list_result(emvspi_choice_account_type());
				break;
			case EMV_APP_SELECTED:			   //!< Application Select Completed
				
			case EMV_GET_PROC_OPTION: 		   //!< Get Process Option Completed
			case EMV_READ_APP_DATA:			   //!< Read Application Data Completed
			case EMV_DATA_AUTH:				   //!< Data Authentication Completed
			case EMV_PROCESS_RESTRICT:		   //!< Process Restrict Completed
			case EMV_ONLINE_ENC_PIN:			   //!< notify Application prompt Caldholder enter Online PIN
			case EMV_PIN_BYPASS_CONFIRM:		   //!< notify	Application  confirm  to Accepted PIN Bypass or not
			case EMV_CARDHOLDER_VERIFY:		   //!< Cardholder Verify Completed
			case EMV_TERMINAL_RISK_MANAGEMENT:  //!< Terminal Risk Management Completed
			case EMV_PROCESS_ONLINE: 		   //!< notify Application to Process Online
			case EMV_ID_CHECK:	
			default:
                          break;
		}
	}
	else if(status==STATUS_COMPLETION)
	{

	}
	else 
	{


	}
}

/**
 * ������Ƭ�¼��ص�����
 *
 * ���п�Ƭ����������ʱ�򣬴������¼���
 * ��������OPEN_READER������п�Ƭ���������ʱ���ص��ú�����
 *
 * @param   type        ��Ƭ�¼�
 *   @arg   {@link SMART_CARD_EVENT_INSERT_CARD}
 *   @arg   {@link SMART_CARD_EVENT_REMOVE_CARD}
 */
void fCardEventOccured(int type)
{

}

EMV_INIT_PARAM tEmvInitParam=
{
	fEMVProcessCallback,
	fCardEventOccured,
};


int emvspi_Init(void)
{
//	u8 *pBuff,*pSave;
	int ret=EMV_OK;//fd,
	u8 sBuff[128];
	LOG(LOG_INFO,"->emvspi_Init1\r\n");
	ret=emv_get_version(sBuff);
	LOG(LOG_INFO,"->emv_get_version[%d][%s]\r\n",ret,sBuff);
	emv_initialize(&tEmvInitParam);
	LOG(LOG_INFO,"->emv_initialize\r\n");

	{
		DIR *dfd;
		dfd = opendir("yaffs");
		if(dfd)
		{
			closedir(dfd);
		}
		else 
		{
			mkdir("yaffs",0666);	//������ӦĿ¼
		}
	}
	/*
	fd = API_fsize("AIDFlag.flg");
	if(fd>0) return ret;
	pBuff=malloc(1024);
	pSave=pBuff;
	API_memcpy(pSave,"\x9F\x06\x08\xA0\x00\x00\x03\x33\x01\x01\x01",11); pSave+=11;
	API_memcpy(pSave,"\xDF\x01\x01\x01",4);					pSave+=4;
	API_memcpy(pSave,"\x9F\x09\x02\x00\x20",5); 			pSave+=5;
	API_memcpy(pSave,"\xDF\x11\x05\x00\x00\x00\x00\x00",8); pSave+=8;
	API_memcpy(pSave,"\xDF\x12\x05\x00\x00\x00\x00\x00",8); pSave+=8;
	API_memcpy(pSave,"\xDF\x13\x05\x00\x00\x00\x00\x00",8); pSave+=8;
	API_memcpy(pSave,"\xDF\x18\x01\x01",4); pSave+=4;
	ret=emv_add_aidparam(pBuff,pSave-pBuff);
	free(pBuff);
	//emv_set_termparam(u8* par, int len);
	//emv_add_capkparam(u8* par, int len);
	//emv_add_cardblack(void* blk);
	//emv_add_certblack(void* blk);
	fd = API_fopen("AIDFlag.flg",F_CREAT|F_RDWR);
	API_fwrite(fd,"AidSaveOK",10);
	API_fclose(fd); 
	API_fsync();	//ͬ���ļ�������,��ֹ����δ����	
	*/
	return ret;	
}

int  API_ICC_Apdu(int tCardIndex,const u8* pCmdBuf,u32 nCmdLen,u8* pOutBuf,u32 nOutSize, u32* pOutLen, u32* pSW)
{
	int ret;
	ST_APDU_REQ tApduReq;
	ST_APDU_RSP tApduRsp;
	TRACE_HEX("->ApduSendBuf",(u8*)pCmdBuf,nCmdLen);
	memcpy(tApduReq.Cmd,pCmdBuf,sizeof(tApduReq.Cmd));
	tApduReq.LC=pCmdBuf[sizeof(tApduReq.Cmd)];
	memcpy(tApduReq.DataIn,pCmdBuf+sizeof(tApduReq.Cmd)+1,tApduReq.LC);
	if(nCmdLen >(sizeof(tApduReq.Cmd)+1+tApduReq.LC))
		tApduReq.LE=pCmdBuf[(sizeof(tApduReq.Cmd)+1+tApduReq.LC)];
	else 
		tApduReq.LE=0;
		
	if(tCardIndex==EMV_CARD_CONTACT)
	{
		ret=OsIccExchange(0,0,&tApduReq,&tApduRsp);
	}
	else
	{
		ret=OsPiccIsoCommand(0,&tApduReq,&tApduRsp);
	}
	LOG(LOG_INFO,"ApduRead[%d][%X %X]",ret,tApduRsp.SWA,tApduRsp.SWB);
	if(ret == 0)
	{
		memcpy(pOutBuf,tApduRsp.DataOut,tApduRsp.LenOut);
		if(pOutLen)
			*pOutLen = tApduRsp.LenOut;
		*pSW = tApduRsp.SWA*0x100 + tApduRsp.SWB;
		
		TRACE_HEX("->ApduReadBuf",pOutBuf,*pOutLen);
		return 0;
	}
	return ret;
}


/**
 * ��Ƭ�ϵ�
 *
 * @param   comm                                    ��ƬͨѶ��ʽ{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          �ɹ�
 * @return  {@link EMV_FAIL}                        ʧ��
 */

int emvspi_Start(int comm)
{
/*
	if(comm==EMV_CARD_CONTACT)
	{
		u8 Data[60]={0};		
		if(!OsPiccPoll(NULL,Data))
		{
			APP_ShowMsg(NULL,"IC����ȡATRʧ��",2000);
			return EMV_FAIL;
		}
		LOG(LOG_INFO,"emvplugin_icc_poweron::ATr[%s]", Data);
	}*/
	emv_set_cardtype(comm);
    return EMV_OK;
}

/**
 * ��Ƭ�µ�
 *
 * @param   comm                                    ��ƬͨѶ��ʽ{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          �ɹ�
 * @return  {@link EMV_FAIL}                        ʧ��
 */
int emvspi_end(int comm)
{
	emv_process_exit();	
	LOG(LOG_INFO, "emvplugin_icc_poweroff[%d]",comm);
	if(comm==EMV_CARD_CONTACTLESS)
	{
		OsPiccRemove();
	}
	else if(comm==EMV_CARD_CONTACT)
	{
		
	}
	else return EMV_FAIL;
	return EMV_OK;
}



