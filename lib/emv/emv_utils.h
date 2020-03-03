/**
************************************************************************************************************************
*                         			  COPYRIGHT (C) 2015 Kingsee Tech. Co., Ltd.
*
* @file     emv_utils.h
* @brief    EMV�ں˽ӿ� - ʵ�ù���
* @author   Kingsee Development Team - chenjinhai@szzt.com.cn
* @version  V43E1.0.2
*
************************************************************************************************************************
*/
#ifndef EMV_UTILS_H_
#define EMV_UTILS_H_


/*
************************************************************************************************************************
* INCLUDE FILES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
* EXTERNS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
* DEFINES
************************************************************************************************************************
*/

/**
 * TLV�������
 */
enum EMV_TLVDecodeFlags
{
    SINGLE_TLVOBJ = 0x01,                           //!< ����������TLV����
    STRING_TLVOBJ = 0x02,                           //!< ���������TLV����
    DECODE_LEVEL1 = 0x10,                           //!< ������һ��
};

/**
 * TLV���Ҽ���
 */
enum EMV_TLVFindLevels
{
    SEARCH_ALL_DESC = 0x01,                         //!< ����ָ�������¹ҵ�����TLV
    SEARCH_ONLY_SON = 0x02,                         //!< ����ָ�������¹ҵ���TLV
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

/**
 * TLV�������ݸ�ʽ
 */
typedef struct {
    u32 tagname;                                    //!< ��ǩ��
    int parent;                                     //!< ��Ԫ�ؼ��𣨴�0��ʼ��
    int childnum;                                   //!< ��Ԫ�ظ���
    int valuelen;                                   //!< Ԫ�����ݳ���
    u8* pvalue;                                     //!< Ԫ������
} EMV_TLVOBJ;


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
 * TLV���ݽ���
 *
 * @param   pData                                   [IN]TLV���ݻ���
 * @param   nDataLen                                [IN]TLV���ݻ���ĳ���
 * @param   pTLVs                                   [OU]TLV���������������
 * @param   nTLVs                                   [IN]TLV���������������ĸ��������֧�ֵ�TLV������
 * @param   bFlags                                  [IN]������ǣ��ο�{@link EMV_TLVDecodeFlags}
 * @return  {@link EMV_OK}                          �����ɹ�
 * @return  {@link EMV_FAIL}                        ����ʧ��
 */
int EMV_TLV_Decode(u8 *pData, int nDataLen, EMV_TLVOBJ *pTLVs, int nTLVs, int bFlags);

/**
 * ����ָ��TAG��ӦTLV�������ݣ�ͨ��{@link EMV_TLV_Decode}�������е�����
 *
 * @param   nParent                                 [IN]����λ����������ӦpTLVs������±�
 * @param   nTag                                    [IN]���ұ�ǩ
 * @param   pTLVs                                   [IN]TLV�������ݻ���
 * @param   nLevel                                  [IN]���Ҽ��𣬲ο�{@link EMV_TLVFindLevels}
 * @return  =0                                      û�ҵ�
 * @return  >0                                      nTag��pTLVs�����ж�Ӧ���±�
 */
int EMV_TLV_Find(int nParent, u32 nTag, EMV_TLVOBJ *pTLVs, int nLevel);

/**
 * ʹ��DOL�Ͷ�Ӧ���ݴ����TLV����
 *
 * @param   pDOL                                    [IN]���ݶ����б���TAG��LEN��
 * @param   nDOLLen                                 [IN]���ݶ����б�ĳ���
 * @param   pVal                                    [IN]DOL��Ӧ���ݣ�VAL��
 * @param   nValLen                                 [IN]DOL��Ӧ���ݵĳ���
 * @param   pOut                                    [OU]TLV�����������
 * @param   pOutLen                                 [OU]TLV����������Ȼ���
 * @param   nOutMaxLen                              [IN]TLV��������������󳤶�
 * @return  {@link EMV_OK}                          ����ɹ�
 * @return  {@link EMV_FAIL}                        ���ʧ��
 */
int EMV_TLV_PacketByDOL(u8 *pDOL, int nDOLLen, u8 *pVal, int nValLen, u8 *pOut, int *pOutLen, int nOutMaxLen);

/**
 * ʹ��TAG����ȥ��ȡӦ�����ݴ����TLV����
 *
 * @param   pTags                                   [IN]TAG�б�
 * @param   nTagNum                                 [IN]TAG����
 * @param   pOut                                    [OU]TLV���ݻ���
 * @param   pOutLen                                 [OU]TLV���ݳ��Ȼ���
 * @param   nOutMaxLen                              [IN]TLV���ݻ�����󳤶�
 * @return  {@link EMV_OK}                          ����ɹ�
 * @return  {@link EMV_FAIL}                        ���ʧ��
 */
int EMV_TLV_PacketByTAG(u32 *pTags, int nTagNum, u8 *pOut, int *pOutLen, int nOutMaxLen);


/**
 * �ɣÿ�����ӿ�
 *
 * @param   pInput                                  [IN]�������ݣ�C-APDU��
 * @param   nInlen                                  [IN]�������ݳ���
 * @param   pOutput                                 [OU]������ݻ���
 * @param   pOutlen                                 [OU]������ݳ��Ȼ��棨����SW1��SW2��
 * @return  ״̬��(SW)����0x9000,0x6A82,0x0000
 */
int EMV_ICC_Apdu(u8 *pInput, int nInlen, u8 *pOutput, int *pOutlen);

/**
 * �ɣÿ�ȡ�������GET DATA��
 * @param   nTag                                    [IN]��ǩ���ο�PBOC��5���ֱ�B.10
 * @param   pOut                                    [OU]��ǩ����
 * @param   pOutLen                                 [OU]��ǩ���ݳ���
 * @return  [>=0]                                   ״̬��(SW)����0x9000,0x6A88,0x0000
 * @return  {@link EMV_UNINITIALIZED}               �ں�δ��ʼ��
 * @return  {@link EMV_APPSELUNDONE}                �ں�δ���Ӧ��ѡ��
 */
int EMV_ICC_GetData(u32 nTag, u8 *pOut, int *pOutLen);

/**
 * �ɣÿ�����¼���READ RECORD��
 * @param   nSFI                                    [IN]SFI�����ļ���ʶ��
 * @param   nRecNo                                  [IN]��¼��
 * @param   pOut                                    [OU]��¼����
 * @param   pOutLen                                 [OU]��¼���ݳ���
 * @return  [>=0]                                   ״̬��(SW)����0x9000,0x6A83,0x0000
 * @return  {@link EMV_UNINITIALIZED}               �ں�δ��ʼ��
 * @return  {@link EMV_APPSELUNDONE}                �ں�δ���Ӧ��ѡ��
 */
int EMV_ICC_ReadRecord(u8 nSFI, u8 nRecNo, u8 *pOut, int *pOutLen);


/**
 * ��ȡ��Ƭ���׼�¼��PBOC��
 *
 * @param   nRecNo                                  [IN]��¼��
 *   @arg   [0x00~0xff]                             ������־��¼��
 *   @arg   {@link PBOC_TRANSREC_SFI}               ������־���
 *   @arg   {@link PBOC_TRANSREC_NUM}               ������־����
 *   @arg   {@link PBOC_TRANSREC_FMT}               ������־��ʽ
 * @param   pOut                                    [OU]��¼����
 * @param   pOutLen                                 [OU]��¼���ݳ���
 * @return  {@link EMV_OK}                          �ɹ�
 * @return  {@link EMV_UNINITIALIZED}               �ں�δ��ʼ��
 * @return  {@link EMV_APPSELUNDONE}                �ں�δ���Ӧ��ѡ��
 * @return  {@link EMV_PBOCLOGSFINOTFOUND}          ������־���û�ҵ�
 * @return  {@link EMV_PBOCLOGFMTNOTFOUND}          ������־��ʽû�ҵ�
 * @return  {@link EMV_PBOCLOGRDRECFAILED}          ������־��¼��ȡʧ��
 * @return  {@link EMV_PBOCLOGRECNOINV}             ������־��¼����Ч
 */
int EMV_GetTransLog(int nRecNo, u8 *pOut, int *pOutLen);



#endif /* EMV_UTILS_H_ */
/*
************************************************************************************************************************
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF FILE ~~~
************************************************************************************************************************
*/
