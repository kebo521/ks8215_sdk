/**
 * History:
 * ================================================================
 * 2020-01-15 Baiwenjie <baiwenjie@szzt.com.cn> created
 *
 */
 #include "sdk_battery.h"
 //��⵱ǰ����
 int OsCheckBattery(void)
 {

 	return BATTERY_LEVEL_CHARGE;

 }
 //��⵱ǰ��������
 int OsCheckPowerSupply(void)
 {
	return POWER_BATTERY;

 }

//ʹ�ն˽�������ģʽ��
 int OsSysSleep(void)
 {
	//������״̬��true
 	pthread_kill((pthread_t)threadID, SIGQUIT);//threadIDΪ��Ļˢ���߳�

 }

//�����ն˵ĵ�Դ����ģʽ��
int OsSysSleepEx(int level)
{
	switch(level)
		{
		case 0:
		case 1:
			if()//�ж��Ƿ������������ģʽ
				return ERR_DEV_BUSY;
			OsSysSleep();
				return RET_OK;
		case 2:	
			if()//�ж��Ƿ������������
				return ERR_DEV_BUSY;
			OsSysSleep();
				return RET_OK;
		default:return ERR_INVALID_PARAM
	}
}


int OsSysSleepTime(int Time)
{


}
//��������
int OsReboot(void)
{



}

//�ر��ն�
int OsPowerOff (void)
{


}

//��ȡ���ѵĻ���Դ
int OsWakeupSource (void)
{


}

//��⹩��״̬�Ƿ��쳣��
int OsCheckPowerStatus(int *PowerStatus)
{




}

