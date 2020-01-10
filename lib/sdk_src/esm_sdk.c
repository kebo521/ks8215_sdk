
#include<time.h>
#include<stdlib.h>
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 





//=======================�ӽ���=========================================================


void OsGetRandom(unsigned char *Random,int RandomLen)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<RandomLen;i++)
		Random[i]=(unsigned char)rand();
}




void OsSHA(int Mode, const void *Data, int DataLen, unsigned char*ShaOut)
{

}


void OsDES(const unsigned char *Input, unsigned char *Output, const unsigned char *DesKey, int KeyLen, int Mode)
{

}


void OsAES(const unsigned char *Input, unsigned char *Output, const unsigned char *AesKey, int KeyLen, int Mode)
{

}



int OsRSA(const unsigned char *Modulus, int ModulusLen, const unsigned char *Exp,int ExpLen, const unsigned char *DataIn, unsigned char *DataOut)
{
	return ERR_GEN_RANDOM;

}


int OsRSAKeyGen(unsigned char *Modulus, unsigned char *PriExp, int ModulusLen, const unsigned char * PubExp)
{
	return ERR_GEN_FAIL;
}


//=========================PED============================================


//���� ��Prolin ��PED ����
/*����
	RET_OK �ɹ�
	ERR_DEV_BUSY �豸��ռ�� */
int OsPedOpen(void)
{
	return ERR_DEV_BUSY;
}

//���� ��ȡ��ǰ��PED �İ汾�
/*����: PedVer������� PED �汾��Ϣ��������6 �ֽڡ�
����:	RET_OK �ɹ�
		ERR_DEV_NOT_OPEN PED �豸δ��
		ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetVer(unsigned char * PedVer)
{
	return ERR_DEV_NOT_OPEN;
}


//���� �������μ���PIN block ֮�����С���ʱ�䡣
/*���� TpkIntervalMs
	= 0 ʹ��Ĭ��ֵ(30s)
	<1000 �Զ���Ϊ1000(1s)
	>600000 �Զ���Ϊ600000(10min)
	=0xffffffff ��ǰ���ò����ı�
����:
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ�� */
int OsPedSetInterval(unsigned long TpkIntervalMs)
{
	return ERR_DEV_NOT_OPEN;
}

//���� У���ѻ�����PIN��
/*����
IccSlot ��Ƭ���ڵĿ����ţ�IccSlot=0��
ExpPinLen�����롿
	������ĺϷ����볤���ַ�����0~12 ��ö�ټ��ϡ�
	Ӧ�ó������������볤��ȫ��ö�ٳ�������
	���á�,���Ÿ���ÿ�����ȣ�����������4��6
	λ���벢������������ֱ�Ӱ�ȷ�ϣ�����ַ�
	��Ӧ������Ϊ��0,4,6����
	��ö��0 �������ʾ���Բ����κ����ֶ�ֱ��
	��ȷ�ϼ����ء�
Mode�����롿
	0x00��IC ������ģʽ����֧�ַ���EMV2000
	��IC �����
TimeoutMs�����롿
	����PIN �ĳ�ʱʱ�䣬��λ�����룬���ֵΪ300000��
	0����ʾû�г�ʱʱ�䣬PED ������ʱ���ơ�
IccRsp������� 
	��Ƭ��Ӧ��״̬��(2 �ֽڣ�SWA+SWB)
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedVerifyPlainPin (int IccSlot,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//���� У������PIN,�������£�1. ��ȡ����PIN��2. ��Ӧ���ṩ��RsaPinKey ������PIN ����EMV �淶���м��ܣ�3. ��Ӧ���ṩ�Ŀ�Ƭ�����뿨Ƭͨ���ţ�������PIN ֱ�ӷ��͸���Ƭ��
/*����
Iccslot ��Ƭ���ڵĿ���
RsaPinKey�����롿 �����������ݽṹST_ RSA_PINKEY��
ExpPinLen�����롿
	������ĺϷ����볤���ַ�����0~12 ��ö�ټ��ϡ�Ӧ�ó������������볤��ȫ��ö�ٳ�����
	�����á�,���Ÿ���ÿ�����ȣ�����������4��6 λ���벢������������ֱ�Ӱ�ȷ�ϣ����
	�ַ���Ӧ������Ϊ��0,4,6������ö��0 �������ʾ���Բ����κ����ֶ�ֱ�Ӱ�ȷ�ϼ�����.
Mode�����롿 0x00������EMV2000IC �������
TimeoutMs�����롿
	����PIN �ĳ�ʱʱ�䣬��λ�����룬���ֵΪ300000��
	0����ʾû�г�ʱʱ�䣬PED ������ʱ���ơ�
IccRsp������� ��Ƭ��Ӧ��״̬��(2 �ֽڣ�SWA+SWB)
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedVerifyCipherPin (int IccSlot,const ST_RSA_PINKEY * RsaPinKey,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//���� ����PED ���񱣴��������Կ��Ϣ��
/*����
RET_OK �ɹ�
ERR_DEV_NOT_OPEN �豸δ�� */
int OsPedEraseKeys(void)
{
	return ERR_DEV_NOT_OPEN;
}

//���� �趨ĳЩ���ܼ��Ĺ��ܡ�
/*���� KeyFlag
	0x00�����������PIN �Ѿ���ջ���û����PIN ʱ����CLEAR ����PED �˳���������״̬�� ������ERR_PED_INPUT_CLEAR��
	0x01����������ӿ�(OsPedGetPinBlock()��OsPedGetPinDukpt() ��OsPedVerifyPlainPin() ��OsPedVerifyCipherPin() etc)������PIN�����У�����CLEAR ������������������PIN���������������PIN �����ʱ���ٰ�CLEAR ������Ӧ�����Ҳ����˳�PIN ���뺯����
	0x02����ʾ����ATM4 ��������PIN ���룬��������ATM ���Ļ��͡�
	0x03����ʾ����FN ��������PIN ���룬��������FN ���Ļ��͡�
	0x04����ʾ����INFO ��������PIN ���룬��������INFO ���Ļ��͡�
	0x05����ʾ��������ӿ�������PIN �����У�����CANCEL ����������������PINλ���������������PIN �����ʱ���ٰ�CANCEL ������Ӧ�����Ҳ����˳�PIN ���뺯����
	0xff ����ʾ�ָ�Ĭ�ϵĹ��ܼ����ã�����CLEAR ��������������PIN λ����CANCEL ���˳�PIN ���뺯������ATM4/FN/INFO �����˳�PIN ���뺯����
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedSetFunctionKey(int KeyFlag)
{
	return ERR_DEV_NOT_OPEN;
}

//���� �Ͽ���PED ��������ӡ�
void OsPedClose(void)
{
}


//���� ����PIN ��������У���ֹPIN ���롣
/*����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPENPED �豸δ�� */
int OsPedCancelPinEntry(void)
{
	return ERR_DEV_NOT_OPEN;
}


//���� �����ѻ�����/����У��ģʽ��
/*����
Mode �����롿
У��ģʽ��
. 0-ʹ�����������������PIN��
. 1-ʹ�����������������PIN��ͨ��PinBlock ��������PIN��
TpkIdx �����롿
TPK ������
. Mode Ϊ0 ʱ�������壻
. Mode Ϊ1 ʱ��ʹ�ø�������TPK �Ե����PinBlock ���н��ܵõ�PIN���ġ�
PinBlock �����롿
PIN block��
. Mode Ϊ0 ʱ�������壻
. Mode Ϊ1 ʱ����ʾTPK ���ܵ�ISO9564 Format1 ��ʽ��PIN ���ġ�
PinBlockLen �����롿 PIN block �ĳ���
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ�����	*/
int OsPedSetOfflinePin(unsigned char Mode,unsigned char TpkIdx,unsigned char *PinBlock,unsigned short PinBlockLen)
{
	return ERR_DEV_NOT_OPEN;
}

//���� ����PIN ��������У�����ȷ�ϼ�����PIN ���롣
/*����
RET_OK �ɹ�
ERR_DEV_NOT_OPEN PED �豸δ�� */
int OsPedEndPinEntry(void);

//���ܼ�������ȡ��ǰ״̬���û������PIN �������������μ������ϴμ����м����ʷ�������С�
/*����
KeyCacheCnt������� ��ȡ���ĵ�ǰ��ʷ����ֵ������
KeyCache�������
. ��ֵ�������ʱ���Ⱥ�˳���ɵ�λ����λ���뻺�����С�������������Ĵ�С������ڵ���64 �ֽڡ�
. ��ȡ������ʷ�����������Ϊ64��������ʱ���������еİ������泬��64 ������������µ�64 ���������С�
. ��ȡ���ļ�ֵĿǰֻ��Ϊ��PIN����� ENTER �� ���� CLEAR �� ����CANCEL������FN������ATM4����6 �֣����С�PIN�����ְ����ԡ�*�����档����ʱû�а������룬��ȡ���ļ�ֵ��Ϊ0��
����
	>= 0 ��ȡPIN �����¼��ɹ�������ֵ��С��ʾ��ʱPIN �������ġ�*���ĸ�����
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ�����	*/
int OsPedPinKeyNotify(int *KeyCacheCnt,unsigned char *KeyCache)
{
	return ERR_DEV_NOT_OPEN;
}


//����д��һ����Կ������TLK��TMK�� TWK��SM4_TMK ��SM4_TWK��д�롢��ɢ��������ѡ��ʹ��KCV ��֤��Կ��ȷ�ԡ�
/*���� 
KeyBlock�����롿
1 byte ��ʽ��0x03
1 byte
	SrcKeyType��
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
1 byte
	SrcKeyIdx��
	. ��SrcKeyType = PED_TLK ʱ��
	SrcKeyIdx = 1��
	. ��SrcKeyType = PED_TMK ʱ��SrcKeyIdx = [1~100]��
	. ��ucSrcKeyType =PED_TPK/PED_TAK/PED_TDK ʱ�� ucSrcKeyIdx = [1~100]��
	. ��ucSrcKeyType =PED_SM4_TMK ʱ��ucSrcKeyIdx = [1~100]��
	. ��ucSrcKeyType =PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK ʱ��ucSrcKeyIdx = [1~100]��
1 byte
	DstKeyIdx��
	. ��DstKeyType = PED_TLK ʱ��
	DstKeyIdx = 1��
	. ��DstKeyType = PED_TMKʱ��
	DstKeyIdx = [1~100]��
	. ��DstKeyType = PED_TPK ��PED_TAK ��PED_TDK ʱ��DstKeyIdx = [1~100]��
	. ��DstKeyType=PED_SM4_TMKʱ��DstKeyIdx=[1~100]��
	. ��DstKeyType=PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK/PED_TDFK ʱ��DstKeyIdx=[1~100]��
7 bytes �����������
1 byte
	DstKeyType��
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
	. PED_TDFK
1 byte
	DstKeyLen��8/16/24��DstKeyType ΪPED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDKʱ��DstKeyLen=16��24 bytesDstKeyValueĿ����Կ����/����
1 byte
	KcvMode��
	0x00������֤
	0x01����8 ���ֽڵ�0x00 ����DES/TDES ���ܣ��õ����ĵ�ǰ3 ���ֽڼ�ΪKCV��
	0x02�����ȶ���Կ���Ľ�����У�飬�ٶԡ�\x12\x34\x56\x78\x90\x12\x34\x56������DES/TDES �������㣬�õ����ĵ�ǰ3 ���ֽڼ�ΪKCV��
	0x03������һ������KcvData��ʹ��Դ��Կ�� [Ŀ����Կ����+ KcvData]����ָ��ģʽ��MAC ���㣬�õ�8 ���ֽڵ�MAC ��ΪKCV��
	0x04����16 �ֽڵ�0x00 ����SM4���ܣ��õ����ĵ�ǰ4 ���ֽڼ�ΪKCV��
	ע��ģʽ0x01��0x02 ��0x03 ֻ����MK/SK ��Կע����֤��ģʽ0x04 ֻ����SM4 ��Կע����֤��
128bytes
	KcvData��
	. KcvMode Ϊ0x00/0x01/0x02ʱ������������
	. KcvMode Ϊ0x03 ʱ��KcvData��һ���ֽ�Ϊ��������KCV���ݵĳ��ȣ�֮��ΪKCV ���ݣ�KCV ����֮��һ���ֽڱ�ʾMAC ����ģʽ.
8 bytes
	. ��KcvMode = 0x00 ʱ������������
	. ��KcvMode =0x01/0x02/0x03/0x04 ʱ��KcvValue ָ��KCV ��ֵ��
10 bytes ��������
����
RET_OK �ɹ�
ERR_DEV_NOT_OPEN PED �豸δ��
ERR_INVALID_PARAM �Ƿ�����
ERR_SYS_BAD ϵͳ����
ERR_PED_KEY_IDX_ERR ��Կ��������
ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
ERR_PED_TAMPERED PED ������
ERR_PED_NO_MORE_BUF ϵͳ�ڴ�ռ䲻��
ERR_PED_NORMAL_ERRPED ͨ�ô��� KeyBlockFormat ����
ERR_PED_DERIVE_ERR ��Կ��ɢ����
ERR_PED_KCV_MODE_ERR PED KCV У��ģʽ����
ERR_PED_KCV_CHECK_FAIL PED KCV У��ʧ�� */
int OsPedWriteKey(const unsigned char * KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//�� �� д��һ��TIK ��Կ��������ѡ��ʹ��KCV ��֤��Կ��ȷ�ԡ�
/*���� KeyBlock�����롿
1 byte ��ʽ��0x03
1 byte
	SrcKeyType��
	. PED_TLK
1 byte
	SrcKeyIdx��
	. ��SrcKeyType = PED_TLKʱ��SrcKeyIdx = 1��
	. ����д��ʱ��SrcKeyIdx = 0��
1 byte
	DstKeyIdx��
	DstKeyIdx = [1~100]��
7 bytes �����������
1 byte
	DstKeyType��
	. PED_TIK
1 byte DstKeyLen��8/1624 bytesDstKeyValueĿ����Կ����/����
1 byte
	KcvMode��
	0x00������֤
	0x01����8 ���ֽڵ�0x00 ����
	Prolin Ӧ�ñ�̽ӿڱ��ָ�ϵ�ǰ3 ���ֽڼ�ΪKCV��
	0x02�����ȶ���Կ���Ľ�����У�飬�ٶԡ� \x12\x34\x56\x78\x90\x12\x34\x56������DES/TDES �������㣬�õ����ĵ�ǰ3 ���ֽڼ�ΪKCV��
	0x03������һ������KcvData��ʹ��Դ��Կ�� [Ŀ����Կ����+KcvData] ����ָ��ģʽ��MAC ���㣬�õ�8 ���ֽڵ�MAC ��ΪKCV��
128 bytes
KcvData��
. KcvMode Ϊ0x00/0x01/0x02 ʱ������������
. KcvMode Ϊ0x03 ʱ��KcvData��һ���ֽ�Ϊ��������KCV���ݵĳ��ȣ�֮��ΪKCV ���ݣ�KCV ����֮��һ���ֽڱ�ʾMAC ����ģʽ.
8 bytes
. ��KcvMode = 0x00 ʱ������������
. ��KcvMode = 0x01/0x02/0x03ʱ��KcvValue ָ��KCV ��ֵ��
10bytes  ��ʼKSN
����
ERR_OK �ɹ�
ERR_DEV_NOT_OPEN �豸δ��
ERR_INVALID_PARAM �Ƿ����� */
int OsPedWriteTIK(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//����ʹ��ָ����Կ���͵���Կ�������ڵ���Կ������һ�����ݽ�������(����)���õ���Կд�뵽ͬһ������Կ������һָ������λ�á�
/*����
KeyType ��Կ���ͣ�
. PED_TMK
. PED_TPK
. PED_TAK
. PED_TDK
SrcKeyIdx Դ��Կ�����ţ�ȡֵ��ΧΪ[1~100]��
DstKeyIdx Ŀ����Կ�����ţ�ȡֵ��ΧΪ[1~100]��
KeyVar�����롿
	24 �ֽڣ���Ҫ����������ַ�����Ϊ����Կ������ͬ���ַ��������ں�Դ��������Կ��򣻿���չ.
����
RET_OK �ɹ�
ERR_DEV_NOT_OPENPED �豸δ��
ERR_INVALID_PARAM �Ƿ����� */
int OsPedWriteKeyVar(int KeyType,int SrcKeyIdx,int DstKeyIdx,const unsigned char *KeyVar)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ������PIN ʱ�����ý�����ʾ�ǺŵĲ������ԡ�
/*����
x ������
y ������
fontSize �Ǻŵ������С��
	. fontSize = 16��16 ���ֵ��С���ַ���
	. fontSize = 24��24 ���ֵ��С���ַ���
	. fontSize = 32��32 ���ֵ��С���ַ���
	. fontSize = 48��48 ���ֵ��С���ַ���
	�ú������Ǻŵ���ʾʹ��PED �ڲ������ļ�����ϵͳ��װ�ֿ��޹ء�
fontColor �Ǻŵ�������ɫ��ʹ�ú궨�� RGB(_r, _g, _b)�������������ԭɫ����16 λ��ɫֵ��
align ���뷽ʽ��
	PED_ASTERISK_ALIGN_LEFT�������ʼλ�ù̶�����������˳����ʾ�Ǻţ�
	PED_ASTERISK_ALIGN_CENTER���м�λ�ù̶����������߶Գ���ʾ�Ǻţ�
	PED_ASTERISK_ALIGN_RIGHT���ұ���ʼλ�ù̶�����������˳����ʾ�Ǻš�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedSetAsteriskLayout(int x,int y,int fontSize,int fontColor,unsigned char align)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ����PIN ʱ������ǰ���ͱ���ͼ��Ĳ������ԡ�
/*����
	X�����롿 ǰ���ͱ���ͼ�����ʼ������
	Y�����롿 ǰ���ͱ���ͼ�����ʼ������
	Interval�����롿 ��������ͼ��֮��ļ��
	IconNum�����롿 ����ͼ�����Ŀ
	PinIcon�����롿ǰ��ͼ�����·����֧��BMP ��PNGͼ��
	PinIconLen �����롿ǰ��ͼ�����·�����ȣ��256 �ֽ�
	PinIconBG �����롿����ͼ�����·����֧��BMP ��PNGͼ�꣬�粻��Ҫ����ͼ�꣬����ΪNULL��
	PinIconBGLen�����롿����ͼ��·���Ծ����ȣ��256 �ֽڣ��粻��Ҫ����ͼ�꣬����Ϊ0��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedSetPinIconLayout(int X,int Y,int Interval,unsigned char IconNum,char *PinIcon,int PinIconLen,char *PinIconBG,int PinIconBGLen)
{
	return ERR_DEV_NOT_OPEN;
}


//����ָ����ʱ����,ɨ�����������ExpPinLenIn ָ�����ȵ�PIN���������Mode ָ���㷨�������ɵ�PIN block��
/*����
KeyIdx TPK �������ţ�ȡֵ��ΧΪ[1-100] ��
DataIn�����롿
. ��Mode=0x00 ʱ��DataIn ָ�򿨺���λ�����ɵ�16 λ���ʺš�
. ��Mode=0x01 ʱ��DataIn �����壬��Ϊ����ֵ��PED ���������������DataIn ����PinBlock �ļ��㡣
. ��Mode=0x02 ʱ��DataIn ָ�򿨺���λ�����ɵ�16 λ���ʺš�
. ��Mode=0x03 ʱ��DataIn Ϊ������ˮ��ISN ��6 �ֽڣ�ASCII �롿��
. ��Mode=0x10 ʱ��DataIn �����壬��Ϊ����ֵ��PED ���������������DataIn ����PinBlock �ļ��㡣
ExpPinLen�����롿
	������ĺϷ����볤���ַ�����0~12 ��ö�ټ��ϡ�Ӧ�ó������������볤��ȫ��ö�ٳ����������á�,���Ÿ���ÿ�����ȣ�����������4 λ��6 λ
	����������������ֱ�Ӱ�ȷ�ϣ�����ַ���Ӧ������Ϊ��0,4,6����ö��0 ��ʾ���Բ����κ����ֶ�ֱ�Ӱ�ȷ�ϼ����ء�
Mode
	ѡ��PIN BLOCK �ĸ�ʽ
		ʹ��DES��3DES���㷨���ܵ�PinBlock�ĸ�ʽ��
		. 0x00 0x00 ISO9564 ��ʽ 0
		. 0x01 0x01 ISO9564 ��ʽ 1
		. 0x02 0x02 ISO9564 ��ʽ 3
		. 0x03 0x03 HK EPS ר�ø�ʽ
		ʹ��AES �㷨���ܵ�PinBlock �ĸ�ʽ��
		. 0x10 PinBlock ����ǰ���ֽ�ΪISO9564 ��ʽ 1 ���������ݣ�����ֽڽ���#PKCS7 ��䣬����Ϊ8 �ֽڵ�0x08��
TimeoutMs
	����PIN �ĳ�ʱʱ�䵥λ���������ֵΪ3000000����ʾû�г�ʱʱ�䣬PED ������ʱ���ơ�
PinBlock�������
	8 ��16 �ֽڣ�ָ�����ɵ�PIN block��Mode Ϊ0x10 ʱ��PinBlock ����Ϊ16 �ֽڡ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetPinBlock(int KeyIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ���¼���PIN block����ѡ���Ƿ����TPK��
/*���� 
UpdateFlag�����롿:  0��������TPK�� ��0������TPK��
KeyInfo�����롿
	����OsPedWriteKey()��KeyBlock �Ķ��壬����Ϊ184 �ֽڡ���UpdateFlag Ϊ0 ʱ��KeyBlock ��ֻ��DstKeyIdx �����壬
	����DstKeyIdxָ����TPK�����¼���PIN block��
DataIn�����롿
	. ��UpdateFlag Ϊ0��Mode=0x03 ʱ��Ϊ������ˮ��ISN ��6 �ֽڣ�ASCII �롿��
	. ��UpdateFlag Ϊ0��Mode=0x00 ʱ��DataIn ǰ16 �ֽ�Ϊ�ɵ�PAN����16�ֽ�Ϊ�µ�PAN��PAN ��ָ��������λ�����ɵ�16 λ���ʺţ�
	. ��UpdateFlag Ϊ��0 ʱ�� ��ΪNULL��
PinBlock������/�����
	8 �ֽڣ�����ԭPIN block ���ݣ�����µ�PIN block
Mode
	0x00��ISO9564 ��ʽ0��
	0x03��HK EPS ר�ø�ʽ�������¼2EPS_PINBLOCK ��ʽ��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedUpdatePinBlock (int UpdateFlag,const unsigned char * KeyInfo,const unsigned char * DataIn,unsigned char * PinBlock,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ��KeyIdx ָ����MAC ��Կ��DataIn ����Mode ָ�������㡣
/*����
KeyIdx�����롿 TAK �������ţ�ȡֵ��ΧΪ[1~100]��
DataIn�����롿�����MAC ��������ݣ�����С�ڵ���8192 �ֽڡ�
DataInLen�����롿MAC ��������ݳ��ȣ������Ȳ��ܱ�8 �ֽ����������Զ�����\x00����
Mac������� 8 �ֽڣ�MAC �����
Mode�����롿��DataIn ��8 �ֽ�Ϊ��λ�ֿ飬����ΪBLOCK1��BLOCK2��BLOCK3 �ȡ�
0x00����BLOCK1 ��MAC ��Կ��DES/TDES ���ܣ����ܽ����BLOCK2 ������λ��������TAK ��DES/TDES ���ܣ����ν��еõ�8 �ֽڵļ��ܽ����
0x01����BLOCK1 ��BLOCK2 ������λ����������BLOCK3 ������λ������ν��У����õ�8 �ֽڵ�����������ý����TAK ����DES/TDES �������㡣
0x02������ANSIX9.19 �淶����BLOCK1 ��TAK��DES ����(ֻȡǰ8 ���ֽڵ���Կ)�����ܽ����BLOCK2 ������λ��������TAK ��DES ���ܣ����ν��еõ�8 �ֽڵļ��ܽ����������DES/TDES ���ܡ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetMac(int KeyIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//����ʹ��TDK ��DataInLen ���ȵ����ݽ���DES/TDES ���ܻ�������㣬������Ļ����ģ�һ��ָ����TDK��ֻ�����ڼ��ܻ�������㡣
/*����
KeyIdx�����롿 TDK �����ţ�ȡֵ��ΧΪ[1~100]��
InitVector�����롿�ӽ�������ĳ�ʼ����������Ϊ8 �ֽڡ���Mode=0x02/0x03/0x04/0x05 ʱ,��Ҫ�õ���ʼ������
				ΪNULL ʱĬ��Ϊ��\x00\x00\x00\x00\x00\x00\x00\x00������Mode=0x00/0x01 ʱ������Ҫ��ʼ����������ΪNULL��
DataIn�����롿 ָ����Ҫ������������ݡ�
DataInLen�����롿��Ҫ��������ݳ��ȣ����ֽ�Ϊ��λ��ӦС�ڵ���1024��
	��Mode Ϊ0x00~0x05 ʱ������Ϊ8 �ı�����
	��Mode Ϊ0x06~0x07 ʱ�����Բ���8 �ı�����
DataOut������� ָ�����������ݡ�
Mode�����롿
. 0x00��ECB ����
. 0x01��ECB ����
. 0x02��CBC ����
. 0x03��CBC ����
. 0x04��OFB ����
. 0x05��OFB ����
. 0x06��CFB8 ����
. 0x07��CFB8 ����
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedDes(int KeyIdx,unsigned char * InitVector,const unsigned char *DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//���ܻ�ȡ��Կ��KCV ֵ���Թ��Ի�˫��������Կ��֤����Կ���ͷ�TIK ʱ����ָ������Կ���㷨��һ�����ݽ��м��ܣ��������������ĵ�ǰ3 �ֽڣ���Կ����ΪTIK ʱ��������TIK һ��ע��(����õ�)��8 �ֽ�KCV��
/*����
KeyType ��Կ���ͣ�
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
. PED_TIK
. PED_SM4_TMK
. PED_SM4_TPK
. PED_SM4_TAK
. PED_SM4_TDK
KeyIdx ��Կ�������ţ��磺
. TLK��ֻ��Ϊ1��
. TMK ��ȡֵ1~100��
. TWK ��ȡֵ1~100��
. TIK ��ȡֵ1~100��
KcvMode  KCV У��ģʽ
	0x00��ʹ��DES �㷨������Կ��KCV��
	0x04��ʹ��SM4 �㷨����SM4 ��Կ��KCV����ʱ��Կ����ֻ��ΪSM4 ϵ�е���Կ���� KeyType ֻ����PED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK��
KcvDataLen �������KCV �����ݳ��ȣ�������128 �ֽڣ��ұ�8 ��������Կ����ΪTIK ʱ��Ϊ0��KCVУ��ģʽΪ0x04 ʱ�������ݳ��ȱ����ܱ�16������
KcvData�����롿�������KCV �����ݣ���Կ����ΪTIK ʱ��ΪNULL��
Kcv�������
	KCV ֵ��3 ��8 �ֽڡ���Կ����ΪTIK ʱ��
	KCV Ϊ8 �ֽڣ�����Ϊ3 �ֽڡ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ�����	*/
int OsPedGetKcv(int KeyType,int KeyIdx,int KcvMode,int KcvDataLen,unsigned char *KcvData,unsigned char *Kcv)
{
	return ERR_DEV_NOT_OPEN;
}



//������SrcKeyIdx ָ������Կ��DstFromKeyIdx ָ������Կ���м��ܻ���ܣ���ɢ����Կ������������浽DstToKeyIdx ָ������Կ��
/*����
SrcKeyType Դ��Կ���ͣ�
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
SrcKeyIdx Դ��Կ�������ţ��磺
. TLK��ֻ��Ϊ1��
. TMK ��ȡֵ1~100��
. TWK ��ȡֵ1~100��
DstKeyType Ŀ����Կ���ͣ�
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
DstFromKeyIdx Ŀ����ԿԴ������
DstToKeyIdx Ŀ����ԿĿ��������
Mode
	0x00��DES/TDES ����
	0x01��DES/TDES ����
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedDeriveKey(int SrcKeyType,int SrcKeyIdx,int DstKeyType,int DstFromKeyIdx,int DstToKeyIdx,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ��Framebuffer ���ݻ���ͼƬ��������PIN ����ʱ�ı�����
/*����
Mode�����롿PIN ���뱳�������÷�ʽ��
	Mode = 0x00������ýӿڵ����ã�
	Mode = 0x01��ʹ��Framebuffer ��������PIN ����ʱ�ı�����
	Mode = 0x02��ʹ��ͼƬ��������PIN����ʱ�ı�����
Bg�����롿���Framebuffer ���ݻ���ͼƬ���ݵ�Buffer��
BgLen�����롿���Framebuffer ���ݻ���ͼƬ����Buffer �ĳ��ȡ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedSetPinBg(unsigned char Mode,const unsigned char *Bg,int BgLen)
{
	return ERR_DEV_NOT_OPEN;
}




//���� ���ƻ�PED ����̡�
/*����
IconPath �����롿��ż���ͼƬ�ľ���·������֧�����·����·�������������256�ֽڣ���ΪNULL����IconPath ΪNULL ʱ��ϵͳʹ��Ĭ�ϵ�ͼƬ��
KeypadColorBg �����롿���̵ı���ɫRGBA ֵ������Ϊ4�ֽڣ���ΪNULL����KeypadColorBg ΪNULL ʱ��ϵͳʹ��Ĭ�ϵļ��̱���ɫ��
Mode �����롿����ģʽ��
	Mode = 0x00 ʱ��ʹ��ϵͳĬ�ϵļ���ͼƬ�Լ�������ɫ��
	Mode = 0x01 ʱ��ʹ���û�ָ���ļ���ͼƬ�����û�ָ���ļ��̱�����ɫ��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_FILE_NOT_EXIST ͼƬ��Դ�ļ�������
	ERR_VERIFY_SIGN_FAIL ͼƬ��Դ�ļ���ǩʧ�� */
int OsPedCustomKeypad(char *IconPath,unsigned char *KeypadColor,unsigned char Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//����ָ����ʱ���ڣ�ɨ������������PIN�������ʹ��DUKPT ��PIN ��Կ�������ɵ�PIN block��
/*����
GroupIdx�����롿 DUKPT �������ţ�ȡֵ��ΧΪ[1~100]��
DataIn�����롿
	1. ��Mode=0x20 ʱ��DataIn ָ�򿨺���λ�����ɵ�16 λ���ʺš�
	2. ��Mode=0x21 ʱ�������塣
	3. ��Mode=0x22 ʱ��DataIn ָ�򿨺���λ�����ɵ�16 λ���ʺš�
	4. ��Mode=0x23 ʱ��Ϊ������ˮ��ISN ��6�ֽڣ�ASCII �롿��
ExpPinLen�����롿
	������ĺϷ����볤���ַ�����0~12 ��ö�ټ��ϡ�Ӧ�ó������������볤��ȫ��ö�ٳ����������á�,���Ÿ���ÿ�����ȣ�����������4��
	6 λ���벢������������ֱ�Ӱ�ȷ�ϣ�����ַ���Ӧ������Ϊ��0,4,6������ö��0 �������ʾ���Բ����κ����ֶ�ֱ�Ӱ�ȷ�ϼ����ء�
Mode�����롿ѡ��PIN block �ĸ�ʽ��
. 0x20 ISO9564 ��ʽ0��KSN ���Զ���1
. 0x21 ISO9564 ��ʽ1��KSN ���Զ���1
. 0x22 ISO9564 ��ʽ2��KSN ���Զ���1
. 0x23 HK EPS ��ʽ��KSN ���Զ���1
TimeoutMs�����롿
	����PIN �ĳ�ʱʱ�䣬��λ�����롣���ֵΪ300000
	0����ʾû�г�ʱʱ�䣬PED ������ʱ���ơ�
Ksn������� 10 �ֽڣ�ָ��ǰ��KSN��
PinBlock������� 8 �ֽڣ�ָ�����ɵ�PIN block��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetPinDukpt(int GroupIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *Ksn,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ��DUKPT ��Կ����MAC ֵ��
/*����
GroupIdx�����롿 DUKPT �������ţ�ȡֵ��ΧΪ[1~100]��
DataIn�����롿 ָ����Ҫ����MAC ���������ݡ�
DataInLen�����롿���ݵĳ��ȣ�С�ڵ���8192 �ֽڣ�����Ϊ8�ֽ�����ʱ�Զ�����\x00����
Mac������� ָ��õ���MAC��
Ksn������� ָ��ǰ��KSN��
Mode�����롿��DataIn ��8 �ֽ�Ϊ��λ�ֿ飬����ΪBLOCK1��BLOCK2��BLOCK3 �ȡ�
	0x20����BLOCK1 ��MAC ��Կ��TDES ���ܣ����ܽ����BLOCK2 ������λ��������TAK ��TDES ���ܣ����ν��еõ�8 �ֽڵļ��ܽ����
	0x21����BLOCK1 ��BLOCK2 ������λ����������BLOCK3 ������λ������ν��У����õ�8 �ֽڵ�����������ý����TAK ����TDES�������㡣
	0x22������ANSIX9.19 �淶����BLOCK1��TAK ��DES ����(ֻȡǰ8 ���ֽڵ�key)�����ܽ����BLOCK2 ������λ��������TAK ��DES ���ܣ����ν��еõ�8 �ֽڵļ��ܽ����ֱ�����һ�β���TDES ���ܡ�
	. 0x20/0x21/0x22/0x40/0x41/0x42KSN ���Զ���1��
	. 0x40/0x41/0x42 ����MAC ��ʽ��0x20/0x21/0x22 ��ͬ��
	. 0x40/0x41/0x42 ѡ��Ӧ��MAC ��Կ��0x20/0x21/0x22KSN ѡ�������Ӧ��MAC ��Կ��
	. ����ֵ������չMAC �㷨��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetMacDukpt(int GroupIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ʹ��DUKPT ��Կ�����������ݽ��мӽ��ܡ�
/*����
GroupIdx�����롿 DUKPT �������ţ�ȡֵ��ΧΪ[1~100]��
KeyVarType�����롿
	0x00��ʹ��Ӧ�������MAC ��Կ
	0x01��ʹ��DUKPT DES ��Կ
	0x02��ʹ��PIN variant Ϊdata ���ܣ�ECB��CBC ���ܿ��ã���Mode ֵ��Ϊ0x01 ��0x03����DUKPT ��ԿΪ8�ֽ�ʱ��ʹ�õĲ��Ǳ�׼��DES �㷨������ANSI9.24-1998 ���������DES �㷨��
	0x03��ʹ��Ӧ��MAC ��Կ����֧�ּ���ģʽ����Mode ֵֻ��Ϊ0x01��0x03��0x05
	0x04��ʹ��Ӧ��DES ��Կ����֧�ּ���ģʽ����Mode ֵֻ��Ϊ0x01��0x03��0x05
InitVector�����롿�ӽ�������ĳ�ʼ������8 �ֽ�
	��Mode=0x02/0x03/0x04/0x05 ʱ,��Ҫ�õ���ʼ������ΪNULL ʱĬ��Ϊ��\x00\x00\x00\x00\x00\x00\x00\x00����
	��Mode=0x00/0x01 ʱ������Ҫ��ʼ����������ΪNULL��
DataInLen�����롿 ��Ҫ�ӽ��ܵ����ݳ��ȣ�С�ڵ��� 8192
DataIn�����롿 ָ����Ҫ�������������
DataOut������� ָ������������
Ksn������� ָ��ǰ��KSN��10 �ֽ�
Mode�����롿�ӽ���ģʽ��
. 0x00��ECB ����
. 0x01��ECB ����
. 0x02��CBC ����
. 0x03��CBC ����
. 0x04��OFB ����
. 0x05��OFB ����
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedDesDukpt(int GroupIdx,int KeyVarType,unsigned char *InitVector,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//���� ��ȡ��ǰ��KSN ֵ��
/*����
GroupIdx�����롿 DUKPT �������ţ�ȡֵ��ΧΪ[1~100]��
Ksn������� ָ��ǰKSN��10 �ֽ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedGetKsnDukpt(int GroupIdx,unsigned char *Ksn)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ����ָ��DUKPT ���KSN ֵ��
/*���� 
GroupIdx�����롿 DUKPT �������ţ� ȡֵ��ΧΪ[1~100]��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedIncreaseKsnDukpt(int GroupIdx)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ��ȡRSA ��Կ��
/*����
RsaKeyIdx�����롿 RSA Key �������ţ�ȡֵ��ΧΪ[1~10]��
RsaKey������� RSA ��Կ�ṹ��ST_RSA_KEY
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedReadRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ע��RSA ��Կ��PED��
/*����
RsaKeyIdx�����롿 RSA ��Կ�������ţ�ȡֵ��ΧΪ[1~10]��
RsaKey�����롿ָ����Ҫע��PED ��RSA ��Կ�ṹ��ST_RSA_KEY��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedWriteRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//���� �ô洢��PED ��RSA ��Կ����RSA �������㡣
/*����
RsaKeyIdx�����롿 RSA Key �������ţ�ȡֵ��ΧΪ[1~10]��
DataInLen�����롿��Ҫ������������ݳ��ȣ���λΪ�ֽڣ���RSA ��Կ��ģ����ͬ������ֵΪ64 ��512 ֮��8 �ı�����
DataIn�����롿 ָ����Ҫ�������������
DataOut������� ָ������������
KeyInfo������� ��Կ��Ϣ
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedRsaRecover(int KeyIdx,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *KeyInfo)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ��ȡRSA ��Կ���ġ�
/*����
RsaKeyIdx�����롿 RSA Key �������ţ�ȡֵ��ΧΪ[1~10]��
CipherRsaKey������� ָ��RSA ��Կ����
����
	>0 ��ʾRSA ��Կ���ĵĳ���
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedReadCipherRsaKey(int RsaKeyIdx,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}



//���� дRSA ��Կ���ġ�
/*����
RsaKeyIdx�����롿  RSA Key �������ţ�ȡֵ��ΧΪ[1~10]��
CipherRsaKeyLen�����롿 д���RSA ��Կ�������ݵ��ֽڳ��ȣ�С�ڵ���1024
CipherRsaKey�����롿 ָ��RSA ��Կ����
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedWriteCipherRsaKey(int RsaKeyIdx,int CipherRsaKeyLen,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ��һ��AES ��Կ�����Ļ�������д�뵽AES ��Կ�����ָ��������λ�ã�������ѡ��ʹ��KCV ��֤��Կ��ȷ�ԡ�
/*���� KeyBlock�����롿
1 byte ��ʽ��0x03
1 byte SrcKeyType��
	. PED_TLK
	. PED_TMK
1 byte
	SrcKeyIdx��
	. ��SrcKeyType = PED_TLK ʱ��SrcKeyIdx = 1��
	. ��SrcKeyType = PED_TMKʱ��SrcKeyIdx = [1~100]��
	. ��SrcKeyIdx = 0����Կ����������ʽд��PED��
1 byte DstKeyIdx��[1~100]
7 bytes �����������
1 byte
	DstKeyType��
	. PED_TAESK
	. PED_AES_TPK
	. PED_AES_TAK
	. PED_AES_TDK
1 byte DstKeyLen��16/24/32
32 bytes DstKeyValue��Ŀ����Կ����/����
1 byte  KcvMode��
	0x00������֤��
	0x01����16 ���ֽڵ�ȫ0x00 ����AES/ECB ���ܣ��õ����ĵ�ǰ3 ���ֽڼ�ΪKCV ��ֵ��
	0x02�����ȶ���Կ���Ľ�����У�飬�ٶԡ� \x12\x34\x56\x78\x90\x12\x34\x56\x12\x34\x56\x78\x90\x12\x34\x56������AES/ECB�������㣬�õ����ĵ�ǰ3���ֽڼ�ΪKCV ��ֵ��
	0x03������һ������KcvData��ʹ��Դ��Կ��[ Ŀ����Կ����+KCV ����]����ָ��ģʽ��MAC ���㣬�õ�8 ���ֽڵ�MAC ��ΪKCV ��ֵ��
128 bytes
	KcvData��
	. KcvMode Ϊ0x00/0x01/0x02 ʱ������������
	. KcvMode Ϊ0x03 ʱ��KcvData��һ���ֽ�Ϊ��������KCV���ݵĳ��ȣ�֮��ΪKCV ���ݣ�KCV ����֮���һ���ֽڱ�ʾMAC ����ģʽ��
8 bytes
. ��KcvMode=0x00 ʱ������������
. ��KcvMode=0x01/0x02/0x03 ʱ��KcvValue ָ��KCV ��ֵ��
2 bytes ��������
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN PED �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedWriteAesKey(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ��TAESK ��PED_AES_TDK ��Կ��DataInLen ָ�����ȵ����ݽ���AES �ӽ������㡣
/*����
KeyIdx�����롿 TAESK ��Կ�����ţ�ȡֵ��ΧΪ[1~100]��
InitVector ������/������ӽ�������ĳ�ʼ������16 �ֽڡ�
��Mode=0x02/0x03/0x04/0x05 ʱ,��Ҫ�õ���ʼ������ΪNULL ʱĬ��Ϊ16 �ֽڵ�ȫ0x00��
��Mode=0x00/0x01 ʱ������Ҫ��ʼ����������ΪNULL��
��Mode=0x06/0x07 ʱ����ʾ����ʱ�����16 �ֽڳ��ȵ���ʱ������������ɹ���ü������������¡�
DataIn�����롿 ��Ҫ�������������
DataInLen�����롿��Ҫ������������ݳ��ȣ����ֽ�Ϊ��λ��ӦС�ڵ���1024����Ϊ16 �ı�����������ģʽΪCTR ģʽʱ�����ݳ���û�����ơ�
DataOut������� ָ�����������ݡ�
Mode �����롿
. 0x00��ECB ����ģʽ
. 0x01��ECB ����ģʽ
. 0x02��CBC ����ģʽ
. 0x03��CBC ����ģʽ
. 0x04��OFB ����ģʽ
. 0x05��OFB ����ģʽ
. 0x06��CTR ����ģʽ
. 0x07��CTR ����ģʽ
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM ��Ч�Ĳ��� */
int OsPedAes(int KeyIdx,unsigned char*InitVector,const unsigned char*DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//���� ����һ��SM2 ��Կ�ԡ�
/*����
PvtKey������� ָ��SM2 ˽Կ��32 �ֽ�
PubKey������� ָ��SM2 ��Կ��64 �ֽ�
KeyLenBit�����롿 ˽Կλ����256 λ
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ���� */
int OsPedGenSM2Pair(unsigned char *PvtKey,unsigned char *PubKey,int KeyLenBit)
{
	return ERR_DEV_NOT_OPEN;
}




//���� ע��SM2 ˽Կ��Կ��PED��
/*����
KeyIdx �����롿 SM2 ��Կ�����ţ�ȡֵ��ΧΪ[1~20]
KeyType�����롿��Կ���ͣ�
	PED_SM2_PVT_KEY 0x30 ˽Կ
	PED_SM2_PUB_KEY 0x31 ��Կ
KeyValue �����롿
	��KeyType=0x30 ʱ��KeyValue ����Ϊ32 �ֽ�
	��KeyType=0x31 ʱ��KeyValue ����Ϊ64 �ֽ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ��� */
int OsPedWriteSM2Key(int KeyIdx,int KeyType,unsigned char *KeyValue)
{
	return ERR_DEV_NOT_OPEN;
}



//���� ʹ�� SM2 �㷨���ǩ����Ϣ��
/*����
PubKeyIdx�����롿 SM2 ��Կ�����ţ�ȡֵ��ΧΪ[1~20]
PvtKeyIdx�����롿 SM2 ˽Կ�����ţ�ȡֵ��ΧΪ[1~20]
Uid�����롿 ǩ����ID������Լ����������û���ݵı�ʶID����Ϊ16 �ֽڣ�
			��Ĭ��ֵΪ0x31, 0x32,0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38��
UidLen�����롿 ǩ����ID ���ȣ�С�ڵ���512 �ֽڡ�
Input�����롿 ��Ҫǩ��������
InputLen�����롿 ���ݳ��ȣ�С�ڵ���2048 �ֽ�
Signature�����롿 ǩ��ֵ��64 �ֽ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������ */
int OsPedSM2Sign(int PubKeyIdx,int PvtKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ�� SM2 ��Կ��֤ǩ����
/*����
PubKeyIdx�����롿 SM2 ��Կ�����ţ�ȡֵ��ΧΪ[1~20]
Uid�����롿 ǩ����ID��������Լ����������û���ݵı�ʶID
�ĳ���Ϊ16 �ֽڣ���Ĭ��ֵΪ0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38��
UidLen�����롿 ǩ����ID ���ȣ�С�ڵ���512 �ֽ�
Input�����롿 ��Ҫǩ��������
InputLen�����롿 ���ݳ��ȣ�С�ڵ���2048 �ֽ�
Signature�����롿 ǩ��ֵ��64 �ֽ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_VERIFY_SIGN_FAIL ��֤ǩ��ʧ��
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������ */
int OsPedSM2Verify(int PubKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,const unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}

//���� ʹ�� SM2 ��Կ�������ݻ�˽Կ�������ݡ�
/*����
KeyIdx�����롿 SM2 ��Կ�����ţ�ȡֵ��ΧΪ[1~20]
Input�����롿 �����ܻ���ܵ�����
InputLen�����롿 ���ݳ��ȣ����ܲ���ʱС�ڵ��ڣ�2048-96���ֽڣ����ܲ���ʱС�ڵ���2048 �ֽڡ�
Output������� ���ܻ���ܺ������
OutputLen������� ���ܻ���ܺ�����ݳ��ȣ����ܺ����ݳ���Ϊԭ���ݳ���+96 �ֽڣ����ܺ����ݳ���Ϊԭ���ݳ���-96 �ֽڡ�
Mode�����롿 PED_DECRYPT0x00��ʹ��SM2 ˽Կ��������PED_ENCRYPT0x01��ʹ��SM2 ��Կ��������
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������ */
int OsPedSM2Recover(int KeyIdx,unsigned char *Input,int InputLen,unsigned char *Output,int *OutputLen,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}

//���� ʹ�� SM3 �㷨�����Ӵ�ֵ��
/*����
Input�����롿 ��������
InputLen�����롿 �������ݳ���
Output������� �Ӵ�ֵ��32 �ֽڡ�
Mode�����롿 ֧��0x00������ֵ������
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ���� */
int OsPedSM3(unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ��SM4 �㷨���ܻ�������ݡ�
/*����
KeyIdx�����롿 PED_SM4_TDK �������ţ�ȡֵ��ΧΪ[1��100]
InitVector�����롿 ��ʼ������16 �ֽڡ�����ECB ģʽ�ò���ΪNULL��
Input�����롿 ��Ҫ���ܻ���ܵ�����
InputLen�����롿 ���ݳ���С�ڵ���1024�����ֽ�Ϊ��λ����Ϊ16 �ı���
Output������� ���ܻ���ܺ�����ݣ�����Ϊ���볤��
Mode�����롿 
PED_SM4_ECB_DECRYPT 0x00:SM4 ECB ����
PED_SM4_ECB_ENCRYPT 0x01:SM4 ECB ����
PED_SM4_CBC_DECRYPT 0x02:SM4 CBC ����
PED_SM4_CBC_ENCRYPT 0x03:SM4 CBC ����
���� 
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������
	ERR_PED_KEY_LEN_ERR ��Կ���ȴ��� */
int OsPedSM4(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ʹ��SM4 �㷨����MAC��
/*����
KeyIdx�����롿 PED_SM4_TAK ����Կ�����ţ�ȡֵ��ΧΪ[1��100]
InitVector�����롿 ��ʼ������16 �ֽڡ�
Input�����롿 ��Ҫ����MAC ���������
InputLen�����롿 ���ݳ���С�ڵ���1024�����ֽ�Ϊ��λ����Ϊ16 �ı���
MacOut������� MAC ֵ
Mode�����롿 
	0x00��ʹ��SM4 CBC �㷨����MAC ֵ�����Ƚ���ʼ������BLOCK1 ������򣬲���SM4�㷨ʹ��TAK�����Ľ�����м��ܣ�
			Ȼ���õ�������BLOCK2 �����SM4 �㷨ʹ��TAK �Խ�����ܣ���˳�����16 �ֽڵļ��ܽ����MacOut Ϊ16 �ֽڡ�
	0x01��ʹ��SM4-TAK ��Կ���������ݼ���SM3 Hash����������ΪMacOut(32 �ֽ�)��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������
	ERR_PED_KEY_LEN_ERR ��Կ���ȴ��� */
int OsPedGetMacSM(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *MacOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ָ����ʱ���ڣ�ɨ������������PIN ���������SM4 �㷨���ɵ�PIN block �������ݿ顣
/*����
KeyIdx�����롿 PED_SM4_TPK ����Կ�����ţ�ȡֵ��ΧΪ[1��100]
ExpPinLenIn�����롿 ������ĺϷ����볤���ַ�����0~12 ��ö�ټ��ϡ�
Ӧ�ó������������볤��ȫ��ö�ٳ����������á�,���Ÿ���ÿ�����ȣ�����������4��6 λ���룬����ַ���Ӧ������Ϊ��4,6����
DataIn�����롿 ��Mode=0x00 ʱ��DataIn ָ�򿨺���λ�����ɵ�16 λ���ʺš�
PinBlockOut������� ���ɵ�����PIN block��16 �ֽ�
Mode�����롿 PIN block �ĸ�ʽ0x00 ISO9564 ��ʽ0
TimeoutMs�����롿 ����PIN �ĳ�ʱʱ�䣬��λ�����롣���ֵΪ300000ms��0 ��ʾ����Ĭ�ϳ�ʱʱ��30000ms��
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_SYS_BAD ϵͳ����
	ERR_PED_KEY_IDX_ERR ��Կ��������
	ERR_PED_KEY_TYPE_ERR ��Կ���ʹ���
	ERR_PED_NO_KEY ��Կ������
	ERR_PED_TAMPERED PED ������
	ERR_PED_KEY_LEN_ERR ��Կ���ȴ���
	ERR_PED_NO_PIN_INPUT δ�����κμ�ֵ
	ERR_PED_PIN_INPUT_CANCEL ȡ������
	ERR_PED_WAIT_INTERVAL ���ʱ��̫�� */
int OsPedGetPinBlockSM4(int KeyIdx,const char *ExpPinLenIn,unsigned char *DataIn,unsigned char *PinBlockOut,int Mode,unsigned long TimeoutMs)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ���DESFire ���˴����ĻỰ��ԿB �����ɻỰ��ԿA����A ��B�ϲ�Ϊһ�������ĻỰ��Կ��Ȼ�������м��ܲ������
/*����
SrcKeyIdx�����롿
DESFire ������Կ������ȡֵ��ΧΪ1-100��
KeySetVer�����롿 ��Կ�汾�����ڼ��DESFire �汾��
DivType�����롿��Կ��ɢģʽ��
. ��DivType = 0x00 ʱ����ʾ����ɢ����ʱDESFire ��Կ���ڼ��ܻỰ��Կ��
. ��DivType = 0x01 ʱ�����Uid����ɢ��Կ���÷�ɢ��Կ���ڼ��ܻỰ��Կ��
Mode�����롿�Ự��Կ�ļ������ͣ�0x02��16 �ֽڵ�3DES ��������
Uid�����롿�û����ݣ����ݳ��ȹ̶�Ϊ8 �ֽڣ����ڷ�ɢ�Ự��Կ��
EncRndB�����롿DESFire �����ɵĻỰ��ԿB��
. ���Ự��Կ����Ϊ8 ��16 �ֽ�ʱ�� EncRndB ����Ϊ8 �ֽڣ�
. ���Ự��Կ����Ϊ24 �ֽ�ʱ��EncRndB ����Ϊ16 �ֽڡ�
EncSessionKey������� ���ܵ�(RndA + RndB��).
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedDFAuthDiver(int SrcKeyIdx,int KeySetVer,int DivType,unsigned char Mode,unsigned char *Uid,unsigned char *EncRndB,unsigned char *EncSessionKey)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ���DESFire ���˴��������ĻỰ��ԿA����
/*����
EncRndA�����롿 ����A����
DataLen�����롿EncRndA ���ȣ�
. ���Ự��Կ����Ϊ8 ��16 �ֽ�ʱ��EncRndA ����Ϊ8 �ֽڣ�
. ���Ự��Կ����Ϊ24 �ֽ�ʱ��EncRndA ����Ϊ16 �ֽڡ�
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedDFAuthMerge(unsigned char *EncRndA,int DataLen)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ע������RKI ����������Կ��
/*����
KeyBlkLen �����롿 RKI ��Կ���ݳ���
KeyBlk �����롿 RKI ��Կ����
DstKeyIdx �����롿Ŀ����Կ�������������壬����Ϊ����ֵ
����
	RET_OK �ɹ�
	ERR_DEV_NOT_OPEN �豸δ��
	ERR_INVALID_PARAM �Ƿ����� */
int OsPedRkiInjectKey(int KeyBlkLen,unsigned char *KeyBlk,unsigned char DstKeyIdx)
{
	return ERR_DEV_NOT_OPEN;
}



