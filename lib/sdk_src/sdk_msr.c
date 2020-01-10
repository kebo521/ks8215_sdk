
/**
 * =======================�����Ķ���=========================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include "comm_type.h"
#include "sys_sdk.h" 
#include "sdk_msr.h" 


//���� �򿪴����Ķ����豸��
/*����
	RET_OK �ɹ�
	ERR_DEV_NOT_EXIST �豸������
	ERR_DEV_BUSY �豸��ռ��
	ERR_DEV_NOT_OPEN �豸��ʧ�� */
int OsMsrOpen(void)
{
	return ERR_DEV_NOT_EXIST;
}


//���� �رմ����������豸��
void OsMsrClose(void)
{
}

//���� ��λ�������Ķ�����������Ѷ�ȡ�Ĵ��������ݡ�
void OsMsrReset(void)
{
}	
//���� ����Ƿ�ˢ����
/*����
	TRUE ��ˢ
	FALSE δˢ
	ERR_DEV_NOT_OPEN �豸δ�� */
int OsMsrSwiped(void)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ��ȡ���������ݡ�
/*����
	Track1������� ���1 �ŵ�����
	Track2������� ���2 �ŵ�����
	Track3������� ���3 �ŵ�����
����
	RET_OK �ɹ���ȡ
	ERR_MSR_NOT_SWIPED δˢ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_DEV_NOT_OPEN �豸δ�� */
int OsMsrRead(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3)
{
	return ERR_DEV_NOT_OPEN;
}


//���� ��ȡͨ�õĵ�����������߱��뷽ʽΪJIS ��˫������������ݡ�
/*����
	Track1������� ���1 �ŵ�����
	Track2������� ���2 �ŵ�����
	Track3������� ���3 �ŵ�����
	Track4������� ���4 �ŵ�����
����
	RET_OK �ɹ���ȡ
	ERR_MSR_NOT_SWIPED δˢ��
	ERR_INVALID_PARAM �Ƿ�����
	ERR_DEV_NOT_OPEN �豸δ�� */
int OsMsrReadJIS(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3,ST_MSR_DATA *Track4)
{
	return ERR_DEV_NOT_OPEN;
}


