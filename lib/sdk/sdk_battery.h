/**
 * History:
 * ================================================================
 * 2020-01-15 Baiwenjie <baiwenjie@szzt.com.cn> created
 *
 */
#define BATTERY_LEVEL_0 0 //电池电量0 格
#define BATTERY_LEVEL_1 1 //电池电量1 格
#define BATTERY_LEVEL_2 2 //电池电量2 格
#define BATTERY_LEVEL_3 3 //电池电量3 格
#define BATTERY_LEVEL_4 4 //电池电量4 格
#define BATTERY_LEVEL_CHARGE 5 //电池正在充电
#define BATTERY_LEVEL_COMPLETE 6 //电池充电已充满
#define BATTERY_LEVEL_ABSENT 7 //电池不存在
//供电类型
typedef enum {
	POWER_ADAPTER = 1,/*适配器供电*/
	POWER_USB,/*USB 外设供电*/
	POWER_BATTERY,/*电池供电*/
	POWER_WPC/*无线底座供电*/
} POWER_TYPE;
//休眠唤醒的唤醒源
typedef enum {
	WAKEUP_SRC_NONE = 0, /* 没有进行过休眠唤醒，无唤醒源 */
	WAKEUP_SRC_KP,/* 按键唤醒 */
	WAKEUP_SRC_RTC,/* 定时器唤醒 */
	WAKEUP_SRC_BT,/* 蓝牙唤醒 */
	WAKEUP_SRC_CHC, /* 电源唤醒 */
	WAKEUP_SRC_WIFI, /* WIFI 唤醒 */
	WAKEUP_SRC_MSR, /* 磁条卡唤醒 */
	WAKEUP_SRC_SMARTCARD0 = 8, /* IC 卡唤醒 */
} WAKEUP_SOURCE;

//客户端请求
typedef enum {
PM_FORBID_SLEEP, /*阻止机器进入休眠*/
PM_ALLOW_SLEEP, /*允许机器进入休眠*/
PM_FORBID_SCREENSAVER, /*阻止机器进入屏保*/
PM_ALLOW_SCREENSAVER, /*允许机器进入屏保*/
PM_FORBID_POWEROFF, /*阻止机器关机*/
PM_ALLOW_POWEROFF, /*允许机器关机*/
} PM_REQ_T;
 
/*功能 检测电池电量。
参数 无
返回
BATTERY_LEVEL_0
电量0~5%，电源电量低，需立
即充电。建议不要进行交易、打
印、无线通讯等操作。当电池电
量过低，系统会自动关机
BATTERY_LEVEL_1 电量5%~15%
BATTERY_LEVEL_2 电量15%~40%
BATTERY_LEVEL_3 电量40%~70%
BATTERY_LEVEL_4 电量70%~100%
BATTERY_LEVEL_CHARGE 电池正在充电
BATTERY_LEVEL_COMPLETE 电池充满，外电供电
BATTERY_LEVEL_ABSENT 电池不存在，外电供电
ERR_SYS_NOT_SUPPORT
系统不支持检测电量，
S800/S300/Px7/Px5 返回该值。
*/
int OsCheckBattery(void);

/*
功能 检测供电类型。
参数 无
返回
POWER_BATTERY 内置电池供电
POWER_ADAPTER 电源适配器供电
POWER_USB USB 外设供电，例如PC 机。
POWER_WPC 无线底座供电
*/
int OsCheckPowerSupply(void);

/*
功能 使终端进入休眠模式。
参数 无
返回
RET_OK 成功
ERR_SYS_NOT_SUPPORT 设备不支持
ERR_DEV_BUSY 设备被占用
用法
1. 当有下列情况，不能进入休眠：
1）调用过OsPmRequest()禁止休眠；
2）有外接USB，并且作为USB device。
出现上述情况，函数返回值为ERR_DEV_BUSY。
2. 进入休眠模式后，CPU 停止运行，屏幕关闭。通过按键唤醒后，
屏幕显示内容与调用该函数之前一致，系统从休眠前的停止运
行断点处继续运行。
3. Modem 拨号成功后， 调用休眠函数OsSysSleep() 或
OsSysSleepEx(2)将返回ERR_DEV_BUSY，系统不能休眠；
modem 挂机后，调用休眠函数系统能休眠；
4. 休眠后，按键和通信模块不下电；
*/
int OsSysSleep(void);

/*
功能 设置终端的电源管理模式。
参数 Level【输入】
休眠等级：
	0 ：系统正常运行；
	1 ：屏保模式，CPU 正常工作，表现在关闭LCD、按键背光、触摸按键和触摸屏，可以
通过塑胶按键唤醒；也可由应用程序主动唤醒。
	2：系统休眠，CPU 停止工作，各模块关闭，可以通过塑胶按键唤醒；部分机型也可通过
电源、WIFI 等方式唤醒。
返回
	ET_OK 成功
	RR_INVALID_PARAM 参数错误
	RR_SYS_NOT_SUPPORT 设备不支持
	RR_DEV_BUSY 设备被占用
*/
int OsSysSleepEx(int Level);

/*
参数 Time【输入】
休眠持续时间，【单位：秒】；
取值范围为60~43200（即12 小时）。
对于Prolin-2.4：小于128，自动设置为128；
对于Prolin-cygnus-2.6：小于60，自动设置为60；
大于43200，自动设置为43200。
返回
RET_OK 成功
ERR_SYS_NOT_SUPPORT 设备不支持
*/

int OsSysSleepTime(int Time);

/*
功能 重启机器。
参数 无
返回 ERR_SYS_BAD 系统错误
用法 该函数为阻塞模式，如果执行成功，将直接重启没有返回。
*/
int OsReboot(void);

/*
功能 关闭终端
参数 无
返回 ERR_SYS_BAD 系统错误
用法 该函数为阻塞模式，如果执行成功，将直接关机没有返回。
*/
int OsPowerOff (void);

/*
功能 获取PM 模块发送的消息
参数 TimeoutMs【输入】
超时时间，【单位：ms】
取值范围为：0 以及100~ 3600000，当
TimeoutMs=0，非阻塞方式获取消息。
返回
ERR_INVALID_PARAM 参数错误
>=0 请参照PM_MSG_T

*/
//_MSG_T OsPmGetEvent (int TimeoutMs);

/*
功能 客户端请求机器进入指定的模式。
参数 ReqType【输入】
事件对应的含义请参照PM_REQ_T 结构体
例如：PM_FORBID_SLEEP：阻止机器进入
sleep 模式；
PM_ALLOW_SLEEP：允许机器进入sleep
模式。
返回
ERR_INVALID_PARAM 参数错误
RET_OK 成功
*/
//t OsPmRequest (PM_REQ_T ReqType);

/*
功能 获取使机器从休眠中唤醒的唤醒源。
参数 无
返回
>=0
唤醒源的枚举值，数值对应的唤醒源
请参考WAKEUP_SOURCE 枚举结构
ERR_SYS_NOT_SUPPORT 系统不支持

*/
int OsWakeupSource (void);

/*
功能 检测供电状态是否异常。
参数 PowerStatus【输出】
供电状态参数
Bit0：电池电压状态，0-正常，1-异常；
Bit1：电池充电状态，0-正常，1-异常；
Bit2：充电IC 状态，0-正常，1-异常；
Bit3：电池是否损坏，0-否，1-是；
Bit4：充电周期是否超过限制，0-否，1-是；
Bit5：电池健康状态SOH，0-健康，1-老化严
重；
Bit6~Bit31 保留。
*/
int OsCheckPowerStatus(int *PowerStatus);

