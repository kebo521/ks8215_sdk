
/**
 * =======================磁条阅读器=========================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include "comm_type.h"
#include "sys_sdk.h" 
#include "sdk_msr.h" 


//功能 打开磁条阅读器设备。
/*返回
	RET_OK 成功
	ERR_DEV_NOT_EXIST 设备不存在
	ERR_DEV_BUSY 设备被占用
	ERR_DEV_NOT_OPEN 设备打开失败 */
int OsMsrOpen(void)
{
	return ERR_DEV_NOT_EXIST;
}


//功能 关闭磁条读卡器设备。
void OsMsrClose(void)
{
}

//功能 软复位磁条卡阅读器，并清除已读取的磁条卡数据。
void OsMsrReset(void)
{
}	
//功能 检测是否刷卡。
/*返回
	TRUE 已刷
	FALSE 未刷
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrSwiped(void)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 读取磁条卡数据。
/*参数
	Track1【输出】 输出1 磁道数据
	Track2【输出】 输出2 磁道数据
	Track3【输出】 输出3 磁道数据
返回
	RET_OK 成功读取
	ERR_MSR_NOT_SWIPED 未刷卡
	ERR_INVALID_PARAM 非法参数
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrRead(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 读取通用的单面磁条卡或者编码方式为JIS 的双面磁条卡的数据。
/*参数
	Track1【输出】 输出1 磁道数据
	Track2【输出】 输出2 磁道数据
	Track3【输出】 输出3 磁道数据
	Track4【输出】 输出4 磁道数据
返回
	RET_OK 成功读取
	ERR_MSR_NOT_SWIPED 未刷卡
	ERR_INVALID_PARAM 非法参数
	ERR_DEV_NOT_OPEN 设备未打开 */
int OsMsrReadJIS(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3,ST_MSR_DATA *Track4)
{
	return ERR_DEV_NOT_OPEN;
}


