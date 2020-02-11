/**
 * History:
 * ================================================================
 * 2020-01-15 Baiwenjie <baiwenjie@szzt.com.cn> created
 *
 */
 #include "sdk_battery.h"
 //检测当前电量
 int OsCheckBattery(void)
 {

 	return BATTERY_LEVEL_CHARGE;

 }
 //检测当前供电类型
 int OsCheckPowerSupply(void)
 {
	return POWER_BATTERY;

 }

//使终端进入休眠模式。
 int OsSysSleep(void)
 {
	//将休眠状态置true
 	pthread_kill((pthread_t)threadID, SIGQUIT);//threadID为屏幕刷新线程

 }

//设置终端的电源管理模式。
int OsSysSleepEx(int level)
{
	switch(level)
		{
		case 0:
		case 1:
			if()//判断是否允许进入屏保模式
				return ERR_DEV_BUSY;
			OsSysSleep();
				return RET_OK;
		case 2:	
			if()//判断是否允许进行休眠
				return ERR_DEV_BUSY;
			OsSysSleep();
				return RET_OK;
		default:return ERR_INVALID_PARAM
	}
}


int OsSysSleepTime(int Time)
{


}
//重启机器
int OsReboot(void)
{



}

//关闭终端
int OsPowerOff (void)
{


}

//获取唤醒的唤醒源
int OsWakeupSource (void)
{


}

//检测供电状态是否异常。
int OsCheckPowerStatus(int *PowerStatus)
{




}

