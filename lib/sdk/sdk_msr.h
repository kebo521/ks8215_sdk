
#ifndef _SDK_MSR_
#define _SDK_MSR_

#define ERR_MSR_FAILED -2701 				//����ʧ��
#define ERR_MSR_HEADERR -2702 			//û���ҵ���ʼ��
#define ERR_MSR_ENDERR -2703 				//û���ҵ�������
#define ERR_MSR_LRCERR -2704 				//LRC �������
#define ERR_MSR_PARERR -2705 				//�ŵ�ĳλ����У�����
#define ERR_MSR_NOT_SWIPED -2706 		//û��ˢ��
#define ERR_MSR_NO_DATA -2707 			//������û������
#define ERR_MSR_END_ZEROERR -2708 		//���������ݸ�ʽ����
#define ERR_MSR_PED_DECRYPTERR -2709 	//PED ����ʧ��
#define ERR_MSR_NO_TRACK_ERR -2710 		//û�м�⵽�ſ��϶�Ӧ�Ĵŵ�

//================�ŵ���Ϣ�ṹ��================================================
typedef struct
{
	unsigned char TrackData[256];/* ������λ��*/
	int DataLen;/* �ŵ����ݳ���*/
	int Status;/* �ŵ�����״̬������0 ʱ��ʾ��ȡ���ݳɹ�������ֵ��ʾ��ȡʧ�ܡ�*/
}ST_MSR_DATA;




//���� �򿪴����Ķ����豸��
/*����
	RET_OK �ɹ�
	ERR_DEV_NOT_EXIST �豸������
	ERR_DEV_BUSY �豸��ռ��
	ERR_DEV_NOT_OPEN �豸��ʧ�� */
extern int OsMsrOpen(void);


//���� �رմ����������豸��
extern void OsMsrClose(void);

//���� ��λ�������Ķ�����������Ѷ�ȡ�Ĵ��������ݡ�
extern void OsMsrReset(void);
	
//���� ����Ƿ�ˢ����
/*����
	TRUE ��ˢ
	FALSE δˢ
	ERR_DEV_NOT_OPEN �豸δ�� */
extern int OsMsrSwiped(void);


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
extern int OsMsrRead(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3);


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
extern int OsMsrReadJIS(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3,ST_MSR_DATA *Track4);



#endif
