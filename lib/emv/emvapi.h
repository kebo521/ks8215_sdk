/**
************************************************************************************************************************
*                                     COPYRIGHT (C) 2015 Kingsee Tech. Co., Ltd.
*
* @file     emvapi.h
* @brief    EMVӦ�ýӿ�
* @author   Kingsee Development Team - chenjinhai@szzt.com.cn
* @version  V0.4.9
*
************************************************************************************************************************
*/
#ifndef EMVAPI_H_
#define EMVAPI_H_


/*
************************************************************************************************************************
* INCLUDE FILES
************************************************************************************************************************
*/

#include "emv_type.h"


/*
************************************************************************************************************************
* EXTERNS
************************************************************************************************************************
*/

#if defined(__cplusplus)
extern "C" {
#endif


/*
************************************************************************************************************************
* DEFINES
************************************************************************************************************************
*/

/**
 * EMV����ִ��״̬
 */
enum emv_process_status
{
    STATUS_COMPLETION = 2,              //!< ִ����ɣ���Ϣ������{@link emv_completion_info}
    STATUS_CONTINUE = 1,                //!< ִ��δ�꣬��Ϣ������{@link emv_continue_info}
    STATUS_ERROR = 0,                   //!< ִ�б�����Ϣ������{@link emv_error_info}
};

/**
 * EMV����ִ����ɷ�����Ϣ����
 */
enum emv_completion_info
{
    APPROVE_OFFLINE = 1,                //!< �ѻ�����
    APPROVE_ONLINE = 2,                 //!< ��������
    DECLINE_OFFLINE = 3,                //!< �ѻ��ܾ�
    DECLINE_ONLINE = 4,                 //!< �����ܾ�
    FALLBACK = 5,                       //!< ��������
};

/**
 * EMV����ִ��δ��ɷ�����Ϣ����
 */
enum emv_continue_info
{
    EMV_CANDIDATE_LIST = 1,             //!< notify Application show Application Candidate List
    EMV_APP_SELECTED = 2,               //!< Application Select Completed
    EMV_GET_PROC_OPTION = 3,            //!< Get Process Option Completed
    EMV_READ_APP_DATA = 4,              //!< Read Application Data Completed
    EMV_DATA_AUTH = 5,                  //!< Data Authentication Completed
    EMV_PROCESS_RESTRICT = 6,           //!< Process Restrict Completed
    EMV_ONLINE_ENC_PIN = 7,             //!< notify Application prompt Caldholder enter Online PIN
    EMV_PIN_BYPASS_CONFIRM = 8,         //!< notify  Application  confirm  to Accepted PIN Bypass or not
    EMV_CARDHOLDER_VERIFY = 9,          //!< Cardholder Verify Completed
    EMV_TERMINAL_RISK_MANAGEMENT = 10,  //!< Terminal Risk Management Completed
    EMV_PROCESS_ONLINE = 11,            //!< notify Application to Process Online
    EMV_ID_CHECK = 12,                  //!< notify  Application  Check  Cardholder's Identification

    /*
    STA_IDLE = 0,                       //!< ����״̬������ִ�н�������
    STA_CANDIDATES_BUILT,               //!< ��ѡ�б������
    REQ_SEL_CANDIDATES,                 //!< ����ѡ���ѡӦ���б�
    REQ_SEL_CANDIDATES_AGAIN,           //!< �����ٴ�ѡ���ѡӦ���б�
    STA_APP_SELECTED,                   //!< Ӧ��ѡ�����
    REQ_SEL_ACCOUNTTYPE,                //!< ����ѡ���ʻ�����
    STA_APP_INITIALIZED,                //!< Ӧ�ó�ʼ�����
    REQ_DEACTIVATE_CARD,                //!< �������߷ǽӴ�ʽ��Ƭ��QPBOCר�ã�
    STA_CARD_DEACTIVATED,               //!< �ǽӴ�ʽ��Ƭ���Ƴ���QPBOCר�ã�
    STA_READ_APP_DATA_COMPLETED,        //!< ��Ӧ���������
    STA_DATA_AUTH_COMPLETED,            //!< �ѻ�������֤���
    STA_PROCESS_RESTRICT_COMPLETED,     //!< �����������
    REQ_CHECK_ID,                       //!< ����ֿ��˳�ʾ֤��
    REQ_ONLINE_PIN,                     //!< ����ֿ�����������PIN
    REQ_OFFLINE_PIN,                    //!< ����ֿ��������ѻ�PIN
    REQ_OFFLINE_PIN_LAST,               //!< ����ֿ��������ѻ�PIN�����һ�Σ�
    REQ_CONFIRM_BYPASS_PIN,             //!< ����ȷ���Ƿ�����PIN����
    STA_CARDHOLDER_VERIFY_COMPLETED,    //!< �ֿ�����֤���
    REQ_CONFIRM_FORCE_ONLINE,           //!< ����ȷ���Ƿ�ǿ������
    STA_RISK_MANAGEMENT_COMPLETED,      //!< �ն˷��չ������
    STA_ACTION_ANALYSE_COMPLETED,       //!< �ն���Ϊ�������
    REQ_GO_ONLINE,                      //!< ��������
    REQ_ISSUER_REFERRAL,                //!< ���󷢿��вο�
*/
};

/**
 * EMV����ִ�д��󷵻���Ϣ����
 */
enum emv_error_info
{
    SUCCESS = 0,                        //!< no more information
    ERROR_APP_NO_INFO = 1,              //!< Selected Application do not in the Candidate List when Application Select
    ERROR_APP_ANALYSIS = 3,             //!< Parse Card Returned Data Error when Application Select
    ERROR_APP_BLOCKED = 4,              //!< card  return  6A81  when Application Select
    ERROR_APP_SELECT = 5,               //!< Error when Application Select
    ERROR_NO_AIPAFL = 6,                //!< Application Interchange Profile(AIP) and Application  File  Locator(AFL)  not  exist  when  Initialize Application
    ERROR_INIT_APP = 7,                 //!< Error when ApplicationInit
    ERROR_OTHER_CARD = 8,               //!< Error when other card insert used
    ERROR_EXPIRED_CARD = 9,             //!< Error when Initialize Application Data
    ERROR_APP_DATA = 10,                //!< Error when Read Application Data
    ERROR_AUTH_METHOD_BLOCKED = 11,     //!< card return 6983, command not allowed, authentication method blocked
    ERROR_REFDATA_INVALIDATED = 12,     //!< card return 6984, command not allowed, referenced data invalidated
    ERROR_COND_NOT_SATISFIED = 13,      //!< card return 6985, command not allowed, conditions of use not satisfied
    ERROR_FUNC_NOT_SUPPORTED = 14,      //!< card return 6A81, wrong parameter p1 p2, function not supported
    ERROR_FILE_NOT_FOUND = 15,          //!< card return 6A82, wrong parameter p1 p2, file not found
    ERROR_RECORD_NOT_FOUND = 16,        //!< card return 6A83, wrong parameter p1 p2, record not found
    ERROR_REFDATA_NOT_FOUND = 17,       //!< card return 6A88, referenced data (data objects) not found
    ERROR_SELFILE_INVALIDATED = 18,     //!< card return 6283, state  of non-volatile memory unchanged, selected file invalidated
    ERROR_AUTH_FAILED = 19,             //!< card return 6300, state of non-volatile memory changed, authentication failed
    ERROR_COUNTER_X = 20,               //!< card return 63Cx, state of non-volatile memory changed, counter provided by 'x'(from 0-15)
    ERROR_BLOCKED_NOSEL = 21,           //!< card blocked or select command not supported
    ERROR_ANALYSIS = 22,                //!< Parse Card Returned Data Error
    ERROR_READ_DATA = 23,               //!< Error when Processing Restrict
    ERROR_GEN_RANDOM = 24,              //!< Card Returned Data for SDA Overflow when Read Application Data
    ERROR_GEN_DOLBLOCK = 25,            //!< Generate DOL Block error when Data Authentication
    ERROR_GEN_AC = 26,                  //!< Generate AC error when Transaction Process
    ERROR_NO_CDOL1 = 27,                //!< CDOL1 not exist when Transaction Process
    ERROR_NO_CDOL2 = 28,                //!< CDOL2 not exist when Transaction Process
    ERROR_LOGIC = 29,                   //!< Logic Error when Transaction Process
    ERROR_CHIP_CANNOT_BE_READ = 30,     //!< Card Returned Unknown Response Code
    ERROR_PROCESS_CMD = 31,             //!< Process Command ERROR
    ERROR_AAR_ABORTED = 32,             //!< Card decision is AAR when Transaction Process
    ERROR_LOG_FILE = 33,                //!< Log File Error
    ERROR_SERVICE_NOT_ALLOWED = 34,     //!< Service not Allowed
    ERROR_PINENTERY_TIMEOUT = 35,       //!< PIN Entry timeout
    ERROR_OFFLINE_VERIFY = 36,          //!< Check Offline PIN Error when Cardholder Verify
    ERROR_NEED_ADVICE = 37,             //!< Trans need Advice
    ERROR_USER_CANCELLED = 38,          //!< Communication Error with Host, but the card need advice, halted the transaction
};


/*
************************************************************************************************************************
* ERROR CODES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
* DATA TYPES
************************************************************************************************************************
*/

typedef struct
{
    /**
     * �����¼��ص�����
     *
     * @param   data[0]     status
     * @param   data[1]     info
     */
    void (*pEMVProcessCallback)(u8* data);

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
    void (*pCardEventOccured)(int type);

} EMV_INIT_PARAM;


/*
************************************************************************************************************************
* GLOBAL VARIABLES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
* MACRO'S
************************************************************************************************************************
*/


/*
************************************************************************************************************************
* FUNCTION PROTOTYPES
************************************************************************************************************************
*/


/**
 * ����ȫ�ֻ��棬���ڴ��Ӧ�����ݣ����鿪7168�ֽ����ϣ�
 *
 * @param   size                                [OU]�����ȫ�ֻ����С
 * @return  ȫ�ֻ���ĵ�ַ
 *
 * @warning ȫ�ֻ����ڽ��������в�������\n
 *          ȫ�ֻ�������������ط����ã��ٴ�ʹ��EMVǰ�������³�ʼ��
 * 
 * @note    �����濪��ȫ�ֻ���ռ���9216�ֽڣ�Ӧ�ÿ�������ʵ�ָú����������ռ�
 */
u8* emv_alloc_buffer(int* size);


#define C_O_M_M__F_U_N_C__H


/**
 * ��ȡָ����ǩ�����ݺͳ���
 *
 * @param   tag                             [IN]��ǩֵ������: 0x9F02
 * @param   value                           [OU]��ǩ��Ӧ�����ݻ���
 * @param   length                          [OU]��ǩ��Ӧ�����ݳ���
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_get_tag_data(u32 tag, u8* value, int* length);

int emv_set_tag_data(u32 tag, u8* value, int length);

/**
 * ��ȡEMV�ں˰汾��Ϣ
 *
 * @param   ver                             [OU]�汾��Ϣ�ַ�������
 * @return  {@link EMV_OK}                  �ɹ�
 */
int emv_get_version(u8* ver);

/**
 * ��ȡ��ѡӦ���б�
 *
 * @param   list                            [OU]��ѡӦ���б���ʽΪ{@link EMV_CANDIDATE}
 * @return  ��ѡӦ�ø���
 */
int emv_get_candidate_list(void* list);


#define P_R_O_C__F_U_N_C__H


/**
 * ����ģ���ʼ��
 *
 * @param   par                             [IN]��ʼ�����������{@link EMV_INIT_PARAM}
 */
void emv_initialize(EMV_INIT_PARAM* par);

/**
 * ���ý�������
 *
 * @param   type                            [IN]�������ͣ����{@link EMV_TransTypes}
 */
void emv_set_trans_type(u8 type);

/**
 * ���ý��׽��
 *
 * @param   amount                          [IN]���׽���λ���֣�
 */
void emv_set_trans_amount(u32 amount);

/**
 * �����������
 *
 * @param   amount                          [IN]��������λ���֣�
 */
void emv_set_other_amount(u32 amount);

/**
 * ����Ԥ�����ǽ�ר�ã�
 *
 * @param   online                          [IN]����Ƿ���������
 * @return  {@link EMV_OK}                  �ɹ�������ǽӴ�����·��
 * @return  {@link EMV_FAIL}                ʧ�ܣ�������ǽӴ�����·��
 */
int emv_preprocess(u8 online);

/**
 * ���ÿ�Ƭ����
 *
 * @param   type                            [IN]��Ƭ���ͣ�1-�Ӵ�ʽ��2-�ǽӴ�ʽ��
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_set_cardtype(u8 type);

/**
 * ��������
 *
 * @return  [-1000 ~ -9999]                 ����״̬����ֵ������ο�{@link EMV_Status}
 * @return  [    1 ~    99]                 �м�״̬����ֵ������ο�{@link EMV_Status}
 * @return  [  100 ~   199]                 ����״̬����ֵ������ο�{@link EMV_Status}
 */
int emv_process(void);

/**
 * ����ѡ���ѡӦ���б�Ľ��
 *
 * @param   eResult                         [IN]ѡ��Ӧ�ö�Ӧ��ѡӦ���б��������0��ʼ��
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_SELCANDIDATENOTREQ}  �ں�δ����ѡ���ѡӦ���б�
 */
int emv_set_candidate_list_result(int index);

/**
 * ����ѡ���ʻ����͵Ľ��
 *
 * @param   result                          [IN]ѡ�е��ʻ����ͣ��ο�{@link EMV_AccountTypes}
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_SELACCOUNTNOTREQ}    �ں�δ����ѡ���ʻ�����
 */
int emv_set_account_type_selected(int result);

/**
 * ���ò���ֿ���֤���Ľ��
 *
 * ����IDType��9F62����IDNumber��9F61�������óֿ���֤�������
 *
 * @param   result                          [IN]��������0-��ͨ����1-ͨ����
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_CHECKIDNOTREQ}       �ں�δ�������ֿ���֤��
 */
int emv_set_check_id_result(int result);

/**
 * ��������PIN������
 *
 * @param   result                          [IN]���������ο�{@link EMV_OperResults}
 *   @arg   {@link EMV_OPER_OK}             ������������
 *   @arg   {@link EMV_OPER_BYPASS}         �����루����������ֱ�Ӱ�ȷ�ϼ��������룩
 *   @arg   {@link EMV_OPER_UNSUPPORTED}    ��֧�ֻ����쳣
 *   @arg   {@link EMV_OPER_TIMEOUT}        ��ʱ�˳�
 *   @arg   {@link EMV_OPER_CANCEL}         ����ȡ��
 *   @arg   {@link EMV_OPER_QUIT}           �����˳�
 * @param   pinbuf                          [IN]����PIN�������ݣ�ΪNULL��ʾ����Ҫ�ں˱��棩
 * @param   pinlen                          [IN]����PIN�������ݳ��ȣ����֧��256�ֽڣ�
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_ONLINEPINNOTREQ}     �ں�δ������������PIN
 *
 * @note    pData��nDatalenֻ����������eResultΪEMV_OPER_OKʱ��Ч��
 *          ��ʽ��Ӧ���Զ��壬�ں�ֻ���𱣴棬����ı�ǩΪ{@link TAG_ONLINE_PIN}��
 */
int emv_set_online_pin_entered(int result, u8* pinbuf, int pinlen);

/**
 * �����ѻ�PIN������
 *
 * @param   result                          [IN]���������ο�{@link EMV_OperResults}
 *   @arg   {@link EMV_OPER_OK}             ������������
 *   @arg   {@link EMV_OPER_BYPASS}         �����루����������ֱ�Ӱ�ȷ�ϼ��������룩
 *   @arg   {@link EMV_OPER_UNSUPPORTED}    ��֧�ֻ����쳣
 *   @arg   {@link EMV_OPER_TIMEOUT}        ��ʱ�˳�
 *   @arg   {@link EMV_OPER_CANCEL}         ����ȡ��
 *   @arg   {@link EMV_OPER_QUIT}           �����˳�
 * @param   pinbuf                          [IN]�ѻ�PINԭʼ���ݣ���֧��NULL����ʽΪASC��
 * @param   pinlen                          [IN]�ѻ�PINԭʼ���ݵĳ��ȣ�֧��4 ~ 12���ַ���
 * @return  {@link EMV_OK}                  ���óɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_OFFLINEPINNOTREQ}    �ں�δ���������ѻ�PIN
 *
 * @note    pData��nDatalenֻ����������eResultΪEMV_OPER_OKʱ��Ч��
 *          ��ʽ������PIN�������ַ��������磺����="123456"����ôpData="123456"��nDataLen=6��
 */
int emv_set_offline_pin_entered(int result, u8* pinbuf, int pinlen);

/**
 * ���óֿ���ȷ���Ƿ�����PIN����Ľ��
 *
 * @param   result                          [IN]������־��0-��������1-������
 * @return  {@link EMV_OK}                  ���óɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_BYPASSPINNOTREQ}     �ں�δ����ȷ���Ƿ�����PIN����
 */
int emv_set_pin_bypass_confirmed(int result);

/**
 * �����̻�ȷ���Ƿ�ǿ�������Ľ��
 *
 * @param   result                          [IN]ǿ��������־��0-��ǿ��������1-ǿ��������
 * @return  {@link EMV_OK}                  ���óɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_FORCEONLINENOTREQ}   �ں�δ����ȷ���Ƿ�ǿ������
 */
int emv_set_force_online(int result);

/**
 * ����������Ȩ���
 *
 * @param   result                          [IN]������Ȩ������ο�{@link EMV_OnlineResults}
 *   @arg   {@link EMV_ONLINE_NOT}          δ����
 *   @arg   {@link EMV_ONLINE_FAIL}         ����ʧ��
 *   @arg   {@link EMV_ONLINE_SUCC_ACCEPT}  �����ɹ�����������׼ "00"
 *   @arg   {@link EMV_ONLINE_SUCC_DENIAL}  �����ɹ��������оܾ� "05"
 *   @arg   {@link EMV_ONLINE_SUCC_ISSREF}  �����ɹ���������ָ�� "01"
 * @param   resp                            [IN]��Ȩ��Ӧ���ݣ��൱��55�����ݣ�TLV��ʽ���������Ȩ��Ӧ�룩
 * @param   resplen                         [IN]��Ȩ��Ӧ���ݳ���
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_GOONLINENOTREQ}      �ں�δ����������Ȩ
 */
int emv_set_online_result(int result, u8* resp, int resplen);

/**
 * ���÷����вο����
 *
 * @param   result                          [IN]�����вο������0-�ܾ���1-��׼��
 * @return  {@link EMV_OK}                  ���óɹ�
 * @return  {@link EMV_UNINITIALIZED}       �ں�δ��ʼ��
 * @return  {@link EMV_ISSREFERRALNOTREQ}   �ں�δ���󷢿��вο�
 */
int emv_set_issref_result(int result);

/**
 * ��ȡ�����Ƿ���Ҫ����֪ͨ
 *
 * @return  0                               ����Ҫ����
 * @return  1                               ��Ҫ����
 */
int emv_is_need_advice(void);

/**
 * ��ȡ�����Ƿ���Ҫǩ��
 *
 * @return  0                               ����Ҫǩ��
 * @return  1                               ��Ҫǩ��
 */
int emv_is_need_signature(void);

/**
 * ������������
 *
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_process_exit(void);


#define P_A_R_A__F_U_N_C__H

/**
 * �����ն˲���
 *
 * @param   par                             [IN]�ն˲���(TLV��ʽ)
 * @param   len                             [IN]�ն˲������ȣ����֧��1020��
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_set_termparam(u8* par, int len);

/**
 * ���AID����
 *
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_clr_aidparam(void);

/**
 * ����AID����
 *
 * @param   par                             [IN]AID����(TLV��ʽ)
 * @param   len                             [IN]AID�������ȣ����֧��1020��
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_add_aidparam(u8* par, int len);

/**
 * ���CAPK����
 *
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_clr_capkparam(void);

/**
 * ����CAPK����
 *
 * @param   par                             [IN]CAPK����(TLV��ʽ)
 * @param   len                             [IN]CAPK�������ȣ����֧��1020��
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_add_capkparam(u8* par, int len);

/**
 * �����Ƭ������
 *
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_clr_cardblack(void);

/**
 * ���ӿ�Ƭ������
 *
 * @param   blk                             [IN]��Ƭ����������ʽΪ{@link EMV_CARDBLACK}
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_add_cardblack(void* blk);

/**
 * ���֤�������
 *
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_clr_certblack(void);

/**
 * ����֤�������
 *
 * @param   blk                             [IN]֤�����������ʽΪ{@link EMV_CERTBLACK}
 * @return  {@link EMV_OK}                  �ɹ�
 * @return  {@link EMV_FAIL}                ʧ��
 */
int emv_add_certblack(void* blk);


#if defined(__cplusplus)
}
#endif


#endif /* EMVAPI_H_ */
/*
************************************************************************************************************************
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF FILE ~~~
************************************************************************************************************************
*/
