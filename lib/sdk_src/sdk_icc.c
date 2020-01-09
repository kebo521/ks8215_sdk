
/**
 * History:
 * ================================================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

//#include <sys/shm.h> 
//#include <linux/shm.h> 
//#include<sys/mman.h>

#include "comm_type.h"
#include "sys_sdk.h" 
#include "sdk_icc.h" 




//���� ��IC �������豸.
int OsIccOpen(int Slot)
{
//RET_OK �ɹ�
//ERR_DEV_NOT_EXIST �豸������
//ERR_DEV_BUSY �豸��ռ��
	return RET_OK;
}

//���� ���ָ���Ŀ����Ƿ��п���
int OsIccDetect(int Slot)
{
/*
	ERR_SCI_HW_NOCARD -2800 û�п�Ƭ
	ERR_SCI_HW_STEP -2801
	��������ʱû�г�ʼ�����ȸ�λ
	ʱδ�ϵ硣
	ERR_SCI_HW_PARITY -2802 ��żУ��ʧ��
	ERR_SCI_HW_TIMEOU
	T -2803 ��ʱ
	ERR_SCI_TCK -2804 TCK ����
	ERR_SCI_ATR_TS -2810 ATR TS ����
	ERR_SCI_ATR_TA1 -2811 ATR TA1 ����
	ERR_SCI_ATR_TD1 -2812 ATR TD1 ����
	*/
	return RET_OK;

}

//���� ��ʼ�� IC ���豸��
/*
Option:	(λ 0~1)����ѹѡ��
				00 - 5V�� 01 - 1.8V��10 - 3V
		(λ 2)��ʾ�� PPS Э��֧�֣�
			0 - ��֧�֣�
			1 �C ֧�֣�
		(λ 3~4)��ʾ�ϵ縴λʹ�����ʣ�
			00 - ��׼���� 9600
			10 - �ı����� 38400
		(λ 5)��ʾ֧�ֵĹ淶���ͣ�
			0 - EMV �淶
			1 - ISO7816 �淶
			�˱�����ָ���淶Ϊ EMV ģʽ����ô�ϵ�
			���ʱ������Ч��Ĭ��ʹ�ñ�׼���ʡ�
		(λ 6 ~31)������
			Option ȱʡ����Ϊ 0(����5V���� PPS����׼��
			�ʺ���ѭ EMVx)
Atr:	1. ��Ƭ��λӦ��(Answer To Reset)����Ƭ��෵�� 34 �ֽڵ���Ӧ���ݡ�
		2. ������Ϊ����λӦ�����ݳ���(1 �ֽ�)+��λӦ������
*/

int OsIccInit(int Slot,unsigned long Option,unsigned char *Atr)
{
	return RET_OK;

}

//���� �� IC �������������
/*
CtrlFlag:
	1. Bit0 ��ʾ T=0 Э�����Ƿ��Զ�����
			GET RESPONSE ָ�
			1-��
			0-��
	2. Bit1~Bit31 ����
*/
int OsIccExchange(int Slot,int CtrlFlag,const ST_APDU_REQ *ApduReq,ST_APDU_RSP *ApduRsp)
{
	return RET_OK;
}

//�ر� IC ���豸��
int OsIccClose(int Slot)
{
	return RET_OK;
}


//���� PCD ģ���ϵ紦��ʹģ�����׼������״̬��
int OsPiccOpen(void)
{
	return RET_OK;
}

//���� PCD ģ���µ紦��
int OsPiccClose(void)
{
	return RET_OK;
}

//���� �ز���λ��
int OsPiccResetCarrier(void)
{
	return RET_OK;
}

//���� Ѱ������ʱֻ������A���͡�B�����������͵���Ѱ��
/*pcPiccType�������
		Ѱ����Ƭ���ͣ�
		��A�� - A �� 
		��B�� - B ��
pucATQx �������
		Ѱ��ʱ��ƬӦ�����ݣ�
		A ��Ϊ 2 �ֽ�
		B ��Ϊ 12 �ֽ�
*/
int OsPiccPoll(char *pcPiccType, unsigned char *pucATQx)
{
	return RET_OK;
}

//�Կ�Ƭ���з���ͻ��ѡ��
/*
pcPiccType�����롿
		Ѱ����Ƭ���ͣ�
		. ��A�� - A ��
		. ��B�� - B ��
pucUID�������
		��Ƭ��Ψһ��ʶ��
		. A ����Ϊ4��7 ��10 �ֽ�
		. B ��Ϊ4 �ֽ�
ucATQ0�����롿 �˲���δʹ��
pucSAK�������
	ѡ��ʱ��ƬӦ�����ݣ�����Ϊ1 �ֽڡ�
	SAKΪA�������һ��ѡ�������Ӧ�����ݣ�
	B �����Դ˲���
*/
int OsPiccAntiSel(const char pcPiccType,unsigned char *pucUID, const unsigned char ucATQ0, unsigned char*pucSAK)
{
	return RET_OK;
}

//���� �Կ�Ƭ���м����
/*
pcPiccType�����롿
	Ѱ����Ƭ���ͣ�
		��A�� - A ��
		��B�� - B ��
pucRATS�������
	���Ƭ��Ӧ�����ݣ�
		A ��ʱ��pucRATS Ϊ��ӦATS �����Ӧ������
		B ��ʱ��pucRATS Ϊ��ӦATTRIB �����Ӧ������
*/
int OsPiccActive(const char pcPiccType,unsigned char *pucRATS)
{
	return RET_OK;
}

//���� ����ISO14443-4 ��ָ���İ�˫��ͨ��Э��ʵ��͸������/���չ��ܡ�
/*
pucTxBuff�����롿 ���������ݻ�����
iTxLen �����롿 ���������ݵĳ��ȣ����ֽ�Ϊ��λ
pucRxBuff������� ���տ�Ƭ��Ӧ���ݵĻ�����
piRxLen������� ���յ��Ŀ�Ƭ�����ֽ�������
*/

int OsPiccTransfer(const unsigned char* pucTxBuff,int iTxLen,unsigned char* pucRxBuff,int * piRxLen)
{
	return RET_OK;
}

//���� ����EMV ģʽ�����ƿ�������
int OsPiccRemove(void)
{
	return RET_OK;

}
//���� ��֤Mifare ����
/*
uid�����롿 ��ƬID������Ϊ4 ���ֽڡ�
blk no�����롿 ���
group�����롿 ��֤�������ͣ�ȡֵΪ��A����B����
psw �����롿 ��֤���룬����Ϊ6 ���ֽڡ�
*/
int OsMifareAuthority(unsigned char *uid,unsigned char blk_no,unsigned char group,unsigned char *psw)
{
	return RET_OK;

}

//���� ��Mifare ��ָ���Ŀ���ж�/д���������Mifare ��ָ�����ݿ���г�/��ֵ/���ݲ������������ֵ�����µ���һ��ָ�������ݿ��С�
/*
ucOpCode�����롿	
	��r��/��R����������
	��w��/��W����д����
	��+������ֵ
	��-������ֵ
	��>����ת��/���ݲ���
ucSrcBlkNo�����롿 ָ�����ʵĿ��
pucVal������/�����
	1. ��Ϊ��������pucVal ��������ݣ�ָ��Ļ�����Ϊ16 �ֽڣ�
	2. ��Ϊд������pucVal ��������ݣ�ָ��Ļ�����Ϊ16 �ֽڣ�
	3. ��Ϊ��ֵ���߼�ֵ������pucVal Ϊ�������������ַ��ָ��Ļ�����Ϊ4 �ֽڣ�
	4. ��Ϊת�������pucVal ��ʵ�����壬�������ָ�벻��ΪNULL��
ucDesBlkNo�����롿
	ָ�������������д�뵽�Ŀ��(��д��ʱ����ֵΪNULL)
*/
int OsMifareOperate(unsigned charucOpCode,unsigned charucSrcBlkNo,unsigned char* pucVal,unsigned charucDesBlkNo)
{
	return RET_OK;

}

//���� ��FeliCa �����г�ʼ�����á�
/*ucSpeed�����롿
	�����뿨Ƭ�����Ĵ������ʣ�
		1��424Kbp
		����ֵ��212Kbps
ucModInvert�����롿
	����FeliCa ���Ʒ�ʽ��
		1������������
		����ֵ������������
*/
int OsPiccInitFelica(unsigned char ucSpeed,unsigned char ucModInvert)
{
	return RET_OK;

}

//���� ��ָ����ͨ���ϣ���Ƭ����APDU ��ʽ�����ݣ���������Ӧ��
/*
cid �����롿����ָ����Ƭ�߼�ͨ���š���ȡֵ��ΧΪ0~14��ȡֵ��Ϊ0��
ApduReq �����롿���͸�PICC ���������ݽṹST_APDU_REQ
ApduRsp ���������PICC �����ص����ݽṹST_APDU_RSP
*/
int OsPiccIsoCommand(int cid,ST_APDU_REQ*ApduReq,ST_APDU_RSP*ApduRsp)
{
	return RET_OK;

}

//���� �����û����á�
//���� pcd_user_config�����롿 �û����ýṹ��PCD_USER_ST
int OsPiccSetUserConfig(PCD_USER_ST *pcd_user_config)
{
	return RET_OK;

}

//���� ��ȡ�û����á�
//���� pcd_user_config������� �û����ýṹ��PCD_USER_ST
int OsPiccGetUserConfig(PCD_USER_ST *pcd_user_config)
{
	return RET_OK;

}

//���� Ѱ����������A����B���͡�V�����������͵���Ѱ��
/*
����
pcPiccType�������
Ѱ����Ƭ���ͣ�
. ��A�� - A ��
. ��B�� - B ��
. ��V�� �C V ��
pucATQx �������
Ѱ��ʱ��ƬӦ�����ݣ�
. A ��Ϊ2 �ֽ�
. B ��Ϊ12 �ֽ�
. V ��Ϊ2 �ֽ�
pucSendData�����롿
�������ֽڣ�
. "\x01\x00\x00\x00"����ʾTerminal in VAS App OR Payment Mode
. "\x01\x00\x00\x01"����ʾTerminal in VAS App AND Payment Mode
. "\x01\x00\x00\x02"����ʾ Terminal in VAS App Only Mode
. "\x01\x00\x00\x03" �� ��ʾTerminal in Payment Mode Only
*/
int OsPiccApplePoll(char *pcPiccType,unsigned char *pucATQx,unsigned char *pucSendData)
{
	return RET_OK;

}

//���� �ر��ز���
int OsPiccOffCarrier(void)
{
	return RET_OK;

}

//���� ��ISO15693 �����г�ʼ�����á�
/*
���� ucDataCodeMode�����롿
�����뿨Ƭ�����Ĵ������ʣ�
. 0��26.48 kbits/s
. ����ֵ���ݲ�֧��
*/
int OsPiccInitIso15693(unsigned char ucDataCodeMode)
{
	return RET_OK;
}


