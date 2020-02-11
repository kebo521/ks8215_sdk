/**
 * History:
 * ================================================================
 * 2020-01-15 Baiwenjie <baiwenjie@szzt.com.cn> created
 *
 */
#define BATTERY_LEVEL_0 0 //��ص���0 ��
#define BATTERY_LEVEL_1 1 //��ص���1 ��
#define BATTERY_LEVEL_2 2 //��ص���2 ��
#define BATTERY_LEVEL_3 3 //��ص���3 ��
#define BATTERY_LEVEL_4 4 //��ص���4 ��
#define BATTERY_LEVEL_CHARGE 5 //������ڳ��
#define BATTERY_LEVEL_COMPLETE 6 //��س���ѳ���
#define BATTERY_LEVEL_ABSENT 7 //��ز�����
//��������
typedef enum {
	POWER_ADAPTER = 1,/*����������*/
	POWER_USB,/*USB ���蹩��*/
	POWER_BATTERY,/*��ع���*/
	POWER_WPC/*���ߵ�������*/
} POWER_TYPE;
//���߻��ѵĻ���Դ
typedef enum {
	WAKEUP_SRC_NONE = 0, /* û�н��й����߻��ѣ��޻���Դ */
	WAKEUP_SRC_KP,/* �������� */
	WAKEUP_SRC_RTC,/* ��ʱ������ */
	WAKEUP_SRC_BT,/* �������� */
	WAKEUP_SRC_CHC, /* ��Դ���� */
	WAKEUP_SRC_WIFI, /* WIFI ���� */
	WAKEUP_SRC_MSR, /* ���������� */
	WAKEUP_SRC_SMARTCARD0 = 8, /* IC ������ */
} WAKEUP_SOURCE;

//�ͻ�������
typedef enum {
PM_FORBID_SLEEP, /*��ֹ������������*/
PM_ALLOW_SLEEP, /*���������������*/
PM_FORBID_SCREENSAVER, /*��ֹ������������*/
PM_ALLOW_SCREENSAVER, /*���������������*/
PM_FORBID_POWEROFF, /*��ֹ�����ػ�*/
PM_ALLOW_POWEROFF, /*��������ػ�*/
} PM_REQ_T;
 
/*���� ����ص�����
���� ��
����
BATTERY_LEVEL_0
����0~5%����Դ�����ͣ�����
����硣���鲻Ҫ���н��ס���
ӡ������ͨѶ�Ȳ���������ص�
�����ͣ�ϵͳ���Զ��ػ�
BATTERY_LEVEL_1 ����5%~15%
BATTERY_LEVEL_2 ����15%~40%
BATTERY_LEVEL_3 ����40%~70%
BATTERY_LEVEL_4 ����70%~100%
BATTERY_LEVEL_CHARGE ������ڳ��
BATTERY_LEVEL_COMPLETE ��س�������繩��
BATTERY_LEVEL_ABSENT ��ز����ڣ���繩��
ERR_SYS_NOT_SUPPORT
ϵͳ��֧�ּ�������
S800/S300/Px7/Px5 ���ظ�ֵ��
*/
int OsCheckBattery(void);

/*
���� ��⹩�����͡�
���� ��
����
POWER_BATTERY ���õ�ع���
POWER_ADAPTER ��Դ����������
POWER_USB USB ���蹩�磬����PC ����
POWER_WPC ���ߵ�������
*/
int OsCheckPowerSupply(void);

/*
���� ʹ�ն˽�������ģʽ��
���� ��
����
RET_OK �ɹ�
ERR_SYS_NOT_SUPPORT �豸��֧��
ERR_DEV_BUSY �豸��ռ��
�÷�
1. ����������������ܽ������ߣ�
1�����ù�OsPmRequest()��ֹ���ߣ�
2�������USB��������ΪUSB device��
���������������������ֵΪERR_DEV_BUSY��
2. ��������ģʽ��CPU ֹͣ���У���Ļ�رա�ͨ���������Ѻ�
��Ļ��ʾ��������øú���֮ǰһ�£�ϵͳ������ǰ��ֹͣ��
�жϵ㴦�������С�
3. Modem ���ųɹ��� �������ߺ���OsSysSleep() ��
OsSysSleepEx(2)������ERR_DEV_BUSY��ϵͳ�������ߣ�
modem �һ��󣬵������ߺ���ϵͳ�����ߣ�
4. ���ߺ󣬰�����ͨ��ģ�鲻�µ磻
*/
int OsSysSleep(void);

/*
���� �����ն˵ĵ�Դ����ģʽ��
���� Level�����롿
���ߵȼ���
	0 ��ϵͳ�������У�
	1 ������ģʽ��CPU ���������������ڹر�LCD���������⡢���������ʹ�����������
ͨ���ܽ��������ѣ�Ҳ����Ӧ�ó����������ѡ�
	2��ϵͳ���ߣ�CPU ֹͣ��������ģ��رգ�����ͨ���ܽ��������ѣ����ֻ���Ҳ��ͨ��
��Դ��WIFI �ȷ�ʽ���ѡ�
����
	ET_OK �ɹ�
	RR_INVALID_PARAM ��������
	RR_SYS_NOT_SUPPORT �豸��֧��
	RR_DEV_BUSY �豸��ռ��
*/
int OsSysSleepEx(int Level);

/*
���� Time�����롿
���߳���ʱ�䣬����λ���롿��
ȡֵ��ΧΪ60~43200����12 Сʱ����
����Prolin-2.4��С��128���Զ�����Ϊ128��
����Prolin-cygnus-2.6��С��60���Զ�����Ϊ60��
����43200���Զ�����Ϊ43200��
����
RET_OK �ɹ�
ERR_SYS_NOT_SUPPORT �豸��֧��
*/

int OsSysSleepTime(int Time);

/*
���� ����������
���� ��
���� ERR_SYS_BAD ϵͳ����
�÷� �ú���Ϊ����ģʽ�����ִ�гɹ�����ֱ������û�з��ء�
*/
int OsReboot(void);

/*
���� �ر��ն�
���� ��
���� ERR_SYS_BAD ϵͳ����
�÷� �ú���Ϊ����ģʽ�����ִ�гɹ�����ֱ�ӹػ�û�з��ء�
*/
int OsPowerOff (void);

/*
���� ��ȡPM ģ�鷢�͵���Ϣ
���� TimeoutMs�����롿
��ʱʱ�䣬����λ��ms��
ȡֵ��ΧΪ��0 �Լ�100~ 3600000����
TimeoutMs=0����������ʽ��ȡ��Ϣ��
����
ERR_INVALID_PARAM ��������
>=0 �����PM_MSG_T

*/
//_MSG_T OsPmGetEvent (int TimeoutMs);

/*
���� �ͻ��������������ָ����ģʽ��
���� ReqType�����롿
�¼���Ӧ�ĺ��������PM_REQ_T �ṹ��
���磺PM_FORBID_SLEEP����ֹ��������
sleep ģʽ��
PM_ALLOW_SLEEP�������������sleep
ģʽ��
����
ERR_INVALID_PARAM ��������
RET_OK �ɹ�
*/
//t OsPmRequest (PM_REQ_T ReqType);

/*
���� ��ȡʹ�����������л��ѵĻ���Դ��
���� ��
����
>=0
����Դ��ö��ֵ����ֵ��Ӧ�Ļ���Դ
��ο�WAKEUP_SOURCE ö�ٽṹ
ERR_SYS_NOT_SUPPORT ϵͳ��֧��

*/
int OsWakeupSource (void);

/*
���� ��⹩��״̬�Ƿ��쳣��
���� PowerStatus�������
����״̬����
Bit0����ص�ѹ״̬��0-������1-�쳣��
Bit1����س��״̬��0-������1-�쳣��
Bit2�����IC ״̬��0-������1-�쳣��
Bit3������Ƿ��𻵣�0-��1-�ǣ�
Bit4����������Ƿ񳬹����ƣ�0-��1-�ǣ�
Bit5����ؽ���״̬SOH��0-������1-�ϻ���
�أ�
Bit6~Bit31 ������
*/
int OsCheckPowerStatus(int *PowerStatus);

