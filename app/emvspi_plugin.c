/*
 * emvspi_plugin.c
 *
 * KSDK方案emvporting层实现
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


// 最大应用个数
#define APPS_MAX_NUM                32
#if(0)

/**
 * @brief 调用UI显示确认信息
 * @param title 显示标题
 * @param msg 提示信息
 * @param confirm 是否有确认提示信息
 * @param timeout 超时时间
 * 
 * @return 确认返回1，取消超时返回0
 */
int emvspi_ui_message(const char* title, const char* msg, int confirm, int timeout_s)
{
    int ret;
	if(confirm) 
		APP_GUI_OnlyThisHasBtn();
	APP_GUI_OnlyThisHasTitle();
	ret=APP_ShowMsg((char*)title,(char*)msg,timeout_s*1000);
	APP_ShowSta((char*)title, "正在处理，请勿拔卡！"); // 确认完成继续显示IC卡操作中
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
    else if(ret==EVENT_TIMEOUT)
    	return EMV_OPER_TIMEOUT;
	return EMV_OPER_CANCEL;
}

/**
 * 显示提示信息，并根据提示操作
 *
 * @param   id  提示信息索引，参考{@link EMV_MessageIDs}
 * @return  操作结果如下，定义参考{@link EMV_OperResults}的注释
 * @return  {@link EMV_OPER_OK}
 * @return  {@link EMV_OPER_CANCEL}
 * @return  {@link EMV_OPER_TIMEOUT}
 * @return  {@link EMV_OPER_UNSUPPORTED}
 */
int emvspi_message(int id) 
{
    /*
    EMV_MSG_CONFIRM_FORCE_ONLINE,                           //!< 确认是否强迫联机（返回值：是，否或不支持）
    EMV_MSG_CONFIRM_PIN_BYPASS,                             //!< 确认是否跳过PIN输入（返回值：是，否或不支持）

    EMV_MSG_PROMPT_CAPK_NOT_FOUND,                          //!< 提示CA公钥未找到（返回值：确认或不支持）
    EMV_MSG_PROMPT_CAPK_EXPIRED,                            //!< 提示CA公钥已过期（返回值：确认或不支持）
    EMV_MSG_PROMPT_CAPK_INVALID,                            //!< 提示CA公钥不可用（返回值：确认或不支持）

    //CID(9F27)对应的原因/通知/授权参考码
    EMV_MSG_PROMPT_ServiceNotAllowed,                       //!< 提示不允许服务（返回值：确认或不支持）
    EMV_MSG_PROMPT_PinTryLimitExceeded,                     //!< 提示PIN尝试次数超限（返回值：确认或不支持）
    EMV_MSG_PROMPT_IssuerAuthenticationFailed,              //!< 提示发卡行认证失败（返回值：确认或不支持）

    EMV_MSG_PROMPT_AtCardBlacklist,                         //!< 提示黑名单卡（返回值：确认或不支持）
    EMV_MSG_PROMPT_AppExpiration,                           //!< 提示应用失效（已过失效日期）（返回值：确认或不支持）
    */
    return EMV_OPER_OK;
}




/**
* 提示并等待用户移卡（QPBOC）
*
* @return  {@link EMV_OPER_OK}				   成功
* @return  {@link EMV_OPER_REPORT_APP}		   不处理，之后内核会返回{@link EMV_REQ_DEACTIVATE_CARD}
*/
int emvspi_deactivate_card(void)
{


	return EMV_OPER_OK;
}
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 出示持卡人证件确认交易是否继续(PBOC)
 * @param typ 证件类型
 * @param cno 证件号
 * @param cnolen 证件号长度
 * @return [0]-不继续 [1]-继续
 */
int emvspi_ack_examine_cred(u8 type, const u8 *num, int numlen)
{
	int ret;
	char typestr[][12] = {"身份证", "军官证", "护照", "入境证", "临时身份证", "其他"};
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "请出示证件:\n");
	API_sprintf(buf, "类型:%s\n",typestr[type]);
	API_strcat(info, buf);
	API_memset(buf, 0, sizeof(buf));
	if(numlen<(int)sizeof(buf))
		API_memcpy(buf, num, numlen);
	API_strcat(info, buf);
	while(1)
	{
		APP_GUI_OnlyThisHasTitle();
		APP_GUI_OnlyThisHasBtn();
		APP_GUI_Win("持卡人验证","确认继续", "返回取消");
		API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info);	
		API_GUI_Show();
		ret = APP_WaitUiEvent(TIMEOUT_SHOW);
		if(ret==EVENT_OK)
			return 1;
		return 0;
	}

}

/**
 * 从候选应用列表中选择应用.
 *
 * @param   again                                   再次选择的标记
 * @param   candidates                              候选应用列表（!NULL）
 * @param   candidates_num                          候选应用个数（>0）
 * @return  [0 ~ candidates_num-1]                  选中应用对应候选应用列表的索引
 * @return  {@link EMV_OPER_CANCEL}                 取消
 * @return  {@link EMV_OPER_TIMEOUT}                超时
 *
 * @note    如果应用选择不支持持卡人确认，那么可以直接返回0（默认选择第一个应用）
 */
int emvspi_choice_app_form_candidates(int again, EMV_CANDIDATE* candidates, int candidates_num)
{
	int 	i, ret = 0;
	char*   title = NULL;
	char*   item[APPS_MAX_NUM] = {NULL};
	char    release_name[APPS_MAX_NUM][33];

	if (again)
		title = "请重新选择应用:";
	else
		title = "请选择应用:";

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
	APP_GUI_OnlyThisHasTitle();	//强制设置标题
	ret = APP_RdoMenu(title,NULL,candidates_num, 0, (const char**)item);
	APP_ShowSta(title,"正在处理，请勿拔卡！");
	if (ret < 0 || ret >= candidates_num)
	{
	    return EMV_OPER_CANCEL;
	}
	return ret;
}

/**
 * 输入PIN
 * @param   type                                    类型
 *          @arg =0                                 联机密码
 *          @arg =1                                 脱机密码（提示最后一次机会）
 *          @arg >1                                 脱机密码
 * @param   output                                  输出缓存（联机密码最大256，脱机密码最大12）
 * @return  >0                                      输出长度（联机密码<=256，4<=脱机密码<=12）
 * @return  {@link EMV_OPER_BYPASS}                 无密码（不输入密码直接按确认键跳过输入）
 * @return  {@link EMV_OPER_UNSUPPORTED}            不支持或工作异常
 * @return  {@link EMV_OPER_TIMEOUT}                超时退出
 * @return  {@link EMV_OPER_CANCEL}                 按键取消
 * @return  {@link EMV_OPER_QUIT}                   按键退出
 *
 * @note    联机PIN输入时，输出内容由应用自定义格式，内核只负责保存\n
 *          脱机PIN输入时，输出内容必须是PIN的明文字符串，例如：密码="123456"，那么output="123456"，返回值6
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
		APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"请输入联机密码:");
    } else if (type == 1) {
    	Min=4; Max=12;
		KeyIndex=2;
   		APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"最后一次脱机密码：");
    } else {
    	Min=4; Max=12;
		KeyIndex=2;
    	APP_ShowOperat(g_PEVar_Data.MenuInfo,INFO_OK,INFO_RET,"请输入脱机密码：");
    }
	if(g_MagCard_Pan.m_MagCardFlag)
		API_Conv_BcdToStr(g_MagCard_Pan.MagCardPan+2,6, magStrBuf);
	else API_memset(magStrBuf,'0',12);
	API_PCI_SetPinblock_Xor_Padding(magStrBuf,NULL);
	API_PCI_SetPrompt(g_PEVar_Data.MenuInfo,"请输入银行卡密码:","注意身边安全",gInputMoney.InputMoneyData);
	APP_PlayTradeVoice("plspass.wav");	//增加输入密码的语音
	ret=API_PCI_GetPin(KeyIndex,PIN_VOICE_PWD,Min,Max,TYPE_ANSI98,0,buf,16,&Len,Term_Par.InputTimeOut[0]);
	if(ret==RET_OK) //suc
	{
		APP_ShowSta(g_PEVar_Data.MenuInfo, "正在处理，请勿拔卡！");
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
	{//未输入密码直接按确认
		return EMV_OPER_BYPASS;		
	}
	if(ret==RET_PCI_USER_CANCEL)
	{
		return EMV_OPER_CANCEL;
	}
	if(ret==RET_PCI_USER_TIMEOUT)
	{
		APP_ShowMsg(g_PEVar_Data.MenuInfo,"输入超时",3000);
		g_UIData.m_OperSta=OPER_TIMEOUT;
		return EMV_OPER_TIMEOUT;
	}
	if(ret==RET_DEVICE_MALFUNCTION)
	{
		APP_ShowMsg(g_PEVar_Data.MenuInfo,"未检测到密码键盘",3000);
		return EMV_OPER_QUIT;
	}
	API_sprintf(magStrBuf,"未知错误[%d]",ret);
	APP_ShowMsg(g_PEVar_Data.MenuInfo,magStrBuf,3000);
	g_UIData.m_OperSta=OPER_QUIT;
	return EMV_OPER_UNSUPPORTED;

}


/**
   * 确认是否跳过输入ＰＩＮ
   *
   * @return  {@link EMV_OPER_OK}				  跳过
   * @return  {@link EMV_OPER_CANCEL}			  不跳过
   * @return  {@link EMV_OPER_UNSUPPORTED}		  不支持
   * @return  {@link EMV_OPER_REPORT_APP}		  不处理，之后内核会返回{@link EMV_REQ_CONFIRM_BYPASS_PIN}
   */
int emvspi_confirm_bypass_pin(void)
{
	int ret = 0;    
	APP_GUI_OnlyThisHasBtn();//设置要有按钮栏
	APP_GUI_Win(NULL,TOK,INFO_CANCER);
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP, "确认是否跳过PIN输入?");
	API_GUI_Show();
	ret=APP_WaitUiEvent(TIMEOUT_CHK);
	APP_DispMsg("正在处理，请勿拔卡！");
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
	return EMV_OPER_CANCEL;
}
/**
	* 确认是否强制联机
	*
	* @return  {@link EMV_OPER_OK}				   强制联机
	* @return  {@link EMV_OPER_CANCEL}			   不强制联机
	* @return  {@link EMV_OPER_UNSUPPORTED} 	   不支持
	* @return  {@link EMV_OPER_REPORT_APP}		   不处理，之后内核会返回{@link EMV_REQ_CONFIRM_FORCE_ONLINE}
	*/
int emvspi_confirm_force_online(void)
{
	int ret = 0;	
	APP_GUI_OnlyThisHasBtn();//设置要有按钮栏
	APP_GUI_Win(NULL,TOK,INFO_CANCER);
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP, "确认是否强迫联机?");
	API_GUI_Show();
	ret=APP_WaitUiEvent(TIMEOUT_CHK);
	APP_DispMsg("正在处理，请勿拔卡！");
	if(ret==EVENT_OK)
		return EMV_OPER_OK;
	return EMV_OPER_CANCEL;
}

/**
	* 请求联机授权
	*
	* @param   resp 							   [OU]授权响应数据（相当于55域数据，TLV格式，包含授权响应码）
	* @param   resplen							   [OU]授权响应数据长度
	* @return  {@link EMV_ONLINE_NOT}			   未联机，交易终止
	* @return  {@link EMV_ONLINE_FAIL}			   联机失败
	* @return  {@link EMV_ONLINE_SUCC_ACCEPT}	   联机成功，发卡行批准
	* @return  {@link EMV_ONLINE_SUCC_DENIAL}	   联机成功，发卡行拒绝
	* @return  {@link EMV_ONLINE_SUCC_ISSREF}	   联机成功，发卡行指引
	* @return  {@link EMV_OPER_REPORT_APP}		   不处理，之后内核会返回{@link EMV_REQ_GO_ONLINE}
	*/
int emvspi_go_online(u8* resp, int* resplen)
{
	return EMV_OPER_REPORT_APP;
}

/**
 * 发卡行参考（发卡行确认交易是否请求接受）
 *
 * @param   pan                                 [IN]应用主账号
 * @param   panlen                              [IN]应用主账号长度
 * @return  {@link EMV_OPER_OK}                 请求接受
 * @return  {@link EMV_OPER_CANCEL}             请求拒绝
 * @return  {@link EMV_OPER_UNSUPPORTED}        不支持
 * @return  {@link EMV_OPER_REPORT_APP}         不处理，之后内核会返回{@link EMV_REQ_ISSUER_REFERRAL}
 */
int emvspi_issuer_referral(u8* pan, int panlen)
{
/*
	int i, ret;
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "请联系你的银行:\n");
	API_strcat(info,"应用主帐号:\n");

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
		APP_GUI_Win("持卡人验证","批准","拒绝");
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
 * 卡片上电
 *
 * @param   comm                                    卡片通讯方式{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          成功
 * @return  {@link EMV_FAIL}                        失败
 */
int emvspi_icc_poweron(int comm)
{
	u8 Data[60];
	u32 nLen=60;
	if(comm==EMV_CARD_CONTACT)
	{
		if(API_ICC_PwrOn(ICC_CONTSCT))
		{
			APP_ShowMsg(NULL,"IC卡上电失败",2000);
			return EMV_FAIL;
		}
		if(API_ICC_GetAtr(ICC_CONTSCT,Data,nLen,&nLen))
		{
			APP_ShowMsg(NULL,"IC卡获取ATR失败",2000);
			return EMV_FAIL;
		}
		LOG_HEX(LOG_INFO, "emvplugin_icc_poweron::ATr", Data, nLen);
	}
    return EMV_OK;
}

/**
 * 卡片下电
 *
 * @param   comm                                    卡片通讯方式{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          成功
 * @return  {@link EMV_FAIL}                        失败
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
 * 卡片读写
 *
 * @param   comm                                    卡片通讯方式{@link EMV_CommunicationWays}
 * @param   input                                   输入数据（C-APDU）
 * @param   inlen                                   输入数据长度
 * @param   output                                  输出数据缓存（不含SW1和SW2）
 * @param   outlen                                  输出数据长度缓存
 * @return  SW1SW2                                  状态字，如0x9000,0x6A82,0x0000
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
 * @brief 获取系统日期和时间
 * @param date 日期缓存（格式：YYYYMMDD, 4bytes）
 * @param time 时间缓存（格式：hhmmss, 3bytes）
 * @return                  [0]-成功 [-1]-错误.
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
 * 显示持卡人证件类型和号码，并提示服务员要求持卡人出示相应证件，比对一致后确认交易是否继续（PBOC）.
 *
 * @param type              证件类型（@ref PBOC_DocumentTypes）
 * @param number            证件号码（ASC格式）
 * @param number_len        证件号码长度
 * @return                  [0]-比对不一致后取消不继续 [1]-比对一致后确认继续
 */
int emvspi_ack_examine_documents(u8 type, u8 *number, int number_len)
{
	int ret;
	char typestr[][12] = {"身份证", "军官证", "护照", "入境证", "临时身份证", "其他"};
	char info[128]={0};
	API_sprintf(info, "请出示证件:\n类型:%s\n",typestr[type]);
	API_memcpy(info+API_strlen(info), number, number_len);
	APP_GUI_OnlyThisHasTitle();
	APP_GUI_OnlyThisHasBtn();
	APP_GUI_Win("验证持卡人","确认继续", "返回取消");
	API_GUI_Info(NULL, SIZE_FONT|TEXT_VALIGN_TOP,info); 
	API_GUI_Show();
	ret = APP_WaitUiEvent(TIMEOUT_SHOW);
	if(ret==EVENT_OK)
		return 1;
	return 0;
}


/**
 * @brief 联系发卡行确认交易是否允许
 * @param pan 应用主账号
 * @param panlen 应用主账号的长度
 * @return [0]-不继续 [1]-继续
 */
int emvspi_ack_issuer_referral(u8* pan, int panlen)
{
/*
	int i, ret;
	char buf[32];
	char info[100]={0};
	API_strcpy(info, "请联系你的银行:\n");
	API_strcat(info,"应用主帐号:\n");

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
		APP_GUI_Win("持卡人验证","批准","拒绝");
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
 * 公钥运算.
 * @param alg               公钥算法标识（@see EMV_PubKeyAlgorithms）.
 * @param pk                公钥.
 * @param input             签名数据.
 * @param output            恢复数据.
 * @return                  恢复数据的长度.
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
 * 哈希运算.
 * @param alg               哈希算法标识（@see EMV_HashAlgorithms）.
 * @param input             输入数据.
 * @param inlen             输入数据长度.
 * @param output            哈希运算结果.
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
 * 获取交易序列计数器（9F41）.
 *
 * @param buf               输出缓存（BCD格式, 4字节）.
 * @return                  [0]-成功 [-1]-错误.
 */
int emvspi_get_trans_sequence_counter(u8 *buf)
{
   API_memset(buf,0x00,4);
    return 0;
}

/**
 * 获取随机数.
 *
 * @param buf               输出缓存.
 * @param len               请求获取长度.
 * @return                  [0]-成功 [-1]-错误.
 */
int emvspi_get_random(u8* buf, int len)
{
    API_Rng(buf, len);
    //TRACE_HEX("随机数", buf, len);
    return 0;
}


/**
 * 获取终端配置信息.
 *
 * @param info              配置信息.
 */
int emvspi_get_config(EMV_TERMPARAM* info)
{
  /*
    u8 core_idx;
    emv_param_t param;

    core_idx = emv_porting_para_get_kernel_index();
    
    if (emv_porting_para_load(&param, core_idx, 0)) 
    {
        TRACE("读取配置参数失败");
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

    //FIXME 实际项目TTQ要根据终端类型等参数来确定
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


#define		PAR_EMV_AID			"emvaid.par"		//应用AID

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
 * 获取终端应用列表.
 *
 * @param apps              存放终端支持的应用列表.
 * @return                  终端支持的应用个数.
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
 * 获取终端应用参数.
 *
 * @param param             终端参数.
 * @param index             终端应用列表的索引. 索引从０开始
 * @return                  [0]-成功 [-1]-失败.
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
 * 读取CA公钥证书.
 *
 * @param cert              CA公钥证书.
 * @param pki               CA公钥索引.
 * @param rid               CA公钥对应的RID（5Bytes）.
 * @return                  [0]-成功 [-1]-失败.
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
 * @brief 查找卡片黑名单
 * @param pan 应用PAN（最大10bytes）
 * @param panlen 应用PAN长度
 * @param sn 应用PAN序列号
 * @return [0]-没找到 [1]-有找到
 */
int emvspi_find_card_blacklist(const u8* pan, int len, u8 seq)
{
    return 0;
}

/**
 * @brief 查找证书黑名单
 * @param rid 注册的应用提供商标识（5bytes）
 * @param pki 认证中心公钥索引
 * @param csn 公钥证书序列号（3bytes）
 * @return [0]-没找到 [1]-有找到
 */
int emvspi_find_cert_blacklist(const u8* rid, u8 pki, const u8* csn)
{
    return 0;
  //return 0;
}

/**
 * @brief 读取日志中的交易金额
 * @param pan 对应的主账号
 * @param panlen 主账号长度
 * @param policy 读取策略
 *      @arg 0 只读最后一笔交易金额（EMV标准）
 *      @arg 1 读取所有日志中的交易金额总和
 * @return 交易金额
 */
u32 emvspi_read_amt_from_log(const u8* pan, u8 panlen, u8 policy)
{
    return 0;
}

/**
 * @brief 保存金额到交易日志
 * @param pan 主账号
 * @param panlen 主账号长度
 * @param amt 交易金额
 * @return [0]-成功 [-1]-失败
 */
int emvspi_save_amt_to_log(u8* pan, u8 panlen, u32 amount)
{
    return 0;
} 
// 静态porting配置
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
#define _LANG_ID_		(1)											//0为英文	1为中文
#define DS(en,ch)		((_LANG_ID_==0)?(en):(ch))					//多语言定义
//=======================================================================================================================
 /**
 * 选择帐户类型
 *
 * @return  {@link EMV_ACCOUNT_DEFAULT}         选择了默认-未指定（Default）
 * @return  {@link EMV_ACCOUNT_SAVINGS}         选择了储蓄账户（Savings）
 * @return  {@link EMV_ACCOUNT_CHEQUE_DEBIT}    选择了支票账户/借记账户（Cheque/Debit）
 * @return  {@link EMV_ACCOUNT_CREDIT}          选择了信用账户（Credit）
 * @return  {@link EMV_OPER_CANCEL}             取消
 * @return  {@link EMV_OPER_TIMEOUT}            超时
 * @return  {@link EMV_OPER_UNSUPPORTED}        不支持该功能
 * @return  {@link EMV_OPER_REPORT_APP}         不处理，之后内核会返回{@link EMV_REQ_SEL_ACCOUNTTYPE}
 */
int emvspi_choice_account_type(void)
{
    int ret = 0x00;
    // cn PBOC3.0 第６章　表 A.7 账户类型
	const char* item[] = {
		DS("Default",		"默认"),
		DS("Savings",		"储蓄账户"),
		DS("Cheque/Debit",	"支票账户/借记账户"),
		DS("Credit",		"信用账户"),
	};
	ret=APP_GUI_Menu("账户类型选择",NULL,4,0,item,30*1000);
	APP_ShowSta("正在处理濉","请勿拔卡！");
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
 * 流程事件回调函数
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
 * 侦听卡片事件回调函数
 *
 * 当有卡片靠近或插入的时候，触发该事件，
 * 即当调用OPEN_READER后，如果有卡片靠近或插入时，回调该函数。
 *
 * @param   type        卡片事件
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
			mkdir("yaffs",0666);	//创建对应目录
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
	API_fsync();	//同步文件到磁盘,防止掉电未保存	
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
 * 卡片上电
 *
 * @param   comm                                    卡片通讯方式{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          成功
 * @return  {@link EMV_FAIL}                        失败
 */

int emvspi_Start(int comm)
{
/*
	if(comm==EMV_CARD_CONTACT)
	{
		u8 Data[60]={0};		
		if(!OsPiccPoll(NULL,Data))
		{
			APP_ShowMsg(NULL,"IC卡获取ATR失败",2000);
			return EMV_FAIL;
		}
		LOG(LOG_INFO,"emvplugin_icc_poweron::ATr[%s]", Data);
	}*/
	emv_set_cardtype(comm);
    return EMV_OK;
}

/**
 * 卡片下电
 *
 * @param   comm                                    卡片通讯方式{@link EMV_CommunicationWays}
 * @return  {@link EMV_OK}                          成功
 * @return  {@link EMV_FAIL}                        失败
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



