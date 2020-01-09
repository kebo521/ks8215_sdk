
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




//功能 打开IC 卡读卡设备.
int OsIccOpen(int Slot)
{
//RET_OK 成功
//ERR_DEV_NOT_EXIST 设备不存在
//ERR_DEV_BUSY 设备被占用
	return RET_OK;
}

//功能 检查指定的卡座是否有卡插
int OsIccDetect(int Slot)
{
/*
	ERR_SCI_HW_NOCARD -2800 没有卡片
	ERR_SCI_HW_STEP -2801
	交换数据时没有初始化，热复位
	时未上电。
	ERR_SCI_HW_PARITY -2802 奇偶校验失败
	ERR_SCI_HW_TIMEOU
	T -2803 超时
	ERR_SCI_TCK -2804 TCK 错误
	ERR_SCI_ATR_TS -2810 ATR TS 错误
	ERR_SCI_ATR_TA1 -2811 ATR TA1 错误
	ERR_SCI_ATR_TD1 -2812 ATR TD1 错误
	*/
	return RET_OK;

}

//功能 初始化 IC 卡设备。
/*
Option:	(位 0~1)卡电压选择：
				00 - 5V， 01 - 1.8V，10 - 3V
		(位 2)表示对 PPS 协议支持：
			0 - 不支持，
			1 – 支持；
		(位 3~4)表示上电复位使用速率：
			00 - 标准速率 9600
			10 - 四倍速率 38400
		(位 5)表示支持的规范类型：
			0 - EMV 规范
			1 - ISO7816 规范
			此标记如果指明规范为 EMV 模式，那么上电
			速率标记则无效，默认使用标准速率。
		(位 6 ~31)保留：
			Option 缺省设置为 0(即：5V、非 PPS、标准速
			率和遵循 EMVx)
Atr:	1. 卡片复位应答(Answer To Reset)，卡片最多返回 34 字节的响应数据。
		2. 其内容为：复位应答内容长度(1 字节)+复位应答内容
*/

int OsIccInit(int Slot,unsigned long Option,unsigned char *Atr)
{
	return RET_OK;

}

//功能 与 IC 卡进行命令交互。
/*
CtrlFlag:
	1. Bit0 表示 T=0 协议下是否自动发送
			GET RESPONSE 指令：
			1-是
			0-否
	2. Bit1~Bit31 保留
*/
int OsIccExchange(int Slot,int CtrlFlag,const ST_APDU_REQ *ApduReq,ST_APDU_RSP *ApduRsp)
{
	return RET_OK;
}

//关闭 IC 卡设备。
int OsIccClose(int Slot)
{
	return RET_OK;
}


//功能 PCD 模块上电处理，使模块进入准备工作状态。
int OsPiccOpen(void)
{
	return RET_OK;
}

//功能 PCD 模块下电处理。
int OsPiccClose(void)
{
	return RET_OK;
}

//功能 载波复位。
int OsPiccResetCarrier(void)
{
	return RET_OK;
}

//功能 寻卡，暂时只包括“A”和“B”卡两种类型的轮寻。
/*pcPiccType【输出】
		寻到卡片类型：
		“A” - A 卡 
		“B” - B 卡
pucATQx 【输出】
		寻卡时卡片应答数据：
		A 卡为 2 字节
		B 卡为 12 字节
*/
int OsPiccPoll(char *pcPiccType, unsigned char *pucATQx)
{
	return RET_OK;
}

//对卡片进行防冲突和选择。
/*
pcPiccType【输入】
		寻到卡片类型：
		. “A” - A 卡
		. “B” - B 卡
pucUID【输出】
		卡片的唯一标识：
		. A 卡可为4，7 或10 字节
		. B 卡为4 字节
ucATQ0【输入】 此参数未使用
pucSAK【输出】
	选卡时卡片应答数据，长度为1 字节。
	SAK为A卡的最后一条选择命令回应的数据，
	B 卡忽略此参数
*/
int OsPiccAntiSel(const char pcPiccType,unsigned char *pucUID, const unsigned char ucATQ0, unsigned char*pucSAK)
{
	return RET_OK;
}

//功能 对卡片进行激活处理。
/*
pcPiccType【输入】
	寻到卡片类型：
		“A” - A 卡
		“B” - B 卡
pucRATS【输出】
	激活卡片的应答数据：
		A 卡时，pucRATS 为响应ATS 命令回应的数据
		B 卡时，pucRATS 为响应ATTRIB 命令回应的数据
*/
int OsPiccActive(const char pcPiccType,unsigned char *pucRATS)
{
	return RET_OK;
}

//功能 按照ISO14443-4 中指定的半双工通信协议实现透明传输/接收功能。
/*
pucTxBuff【输入】 待传送数据缓冲区
iTxLen 【输入】 待传送数据的长度，以字节为单位
pucRxBuff【输出】 接收卡片响应数据的缓冲区
piRxLen【输出】 接收到的卡片数据字节数返回
*/

int OsPiccTransfer(const unsigned char* pucTxBuff,int iTxLen,unsigned char* pucRxBuff,int * piRxLen)
{
	return RET_OK;
}

//功能 按照EMV 模式进行移卡操作。
int OsPiccRemove(void)
{
	return RET_OK;

}
//功能 验证Mifare 卡。
/*
uid【输入】 卡片ID，长度为4 个字节。
blk no【输入】 块号
group【输入】 认证密码类型，取值为‘A’或‘B’。
psw 【输入】 认证密码，长度为6 个字节。
*/
int OsMifareAuthority(unsigned char *uid,unsigned char blk_no,unsigned char group,unsigned char *psw)
{
	return RET_OK;

}

//功能 对Mifare 卡指定的块进行读/写操作；或对Mifare 卡指定数据块进行充/减值/备份操作，操作后的值将更新到另一个指定的数据块中。
/*
ucOpCode【输入】	
	‘r’/‘R’：读操作
	‘w’/‘W’：写操作
	‘+’：充值
	‘-’：减值
	‘>’：转存/备份操作
ucSrcBlkNo【输入】 指定访问的块号
pucVal【输入/输出】
	1. 若为读操作，pucVal 输出块内容，指向的缓冲区为16 字节；
	2. 若为写操作，pucVal 输入块内容，指向的缓冲区为16 字节；
	3. 若为充值或者减值操作，pucVal 为金额数缓冲区首址，指向的缓冲区为4 字节；
	4. 若为转存操作，pucVal 无实际意义，但传入的指针不能为NULL。
ucDesBlkNo【输入】
	指定操作结果最终写入到的块号(读写块时，该值为NULL)
*/
int OsMifareOperate(unsigned charucOpCode,unsigned charucSrcBlkNo,unsigned char* pucVal,unsigned charucDesBlkNo)
{
	return RET_OK;

}

//功能 对FeliCa 卡进行初始化配置。
/*ucSpeed【输入】
	设置与卡片交互的传输速率：
		1：424Kbp
		其它值：212Kbps
ucModInvert【输入】
	设置FeliCa 调制方式：
		1：正向调制输出
		其它值：反向调制输出
*/
int OsPiccInitFelica(unsigned char ucSpeed,unsigned char ucModInvert)
{
	return RET_OK;

}

//功能 在指定的通道上，向卡片发送APDU 格式的数据，并接收响应。
/*
cid 【输入】用于指定卡片逻辑通道号。其取值范围为0~14，取值均为0。
ApduReq 【输入】发送给PICC 卡命令数据结构ST_APDU_REQ
ApduRsp 【输出】从PICC 卡返回的数据结构ST_APDU_RSP
*/
int OsPiccIsoCommand(int cid,ST_APDU_REQ*ApduReq,ST_APDU_RSP*ApduRsp)
{
	return RET_OK;

}

//功能 设置用户配置。
//参数 pcd_user_config【输入】 用户配置结构体PCD_USER_ST
int OsPiccSetUserConfig(PCD_USER_ST *pcd_user_config)
{
	return RET_OK;

}

//功能 获取用户配置。
//参数 pcd_user_config【输出】 用户配置结构体PCD_USER_ST
int OsPiccGetUserConfig(PCD_USER_ST *pcd_user_config)
{
	return RET_OK;

}

//功能 寻卡，包括“A”“B”和“V”卡三种类型的轮寻。
/*
参数
pcPiccType【输出】
寻到卡片类型：
. “A” - A 卡
. “B” - B 卡
. “V” – V 卡
pucATQx 【输出】
寻卡时卡片应答数据：
. A 卡为2 字节
. B 卡为12 字节
. V 卡为2 字节
pucSendData【输入】
输入四字节：
. "\x01\x00\x00\x00"，表示Terminal in VAS App OR Payment Mode
. "\x01\x00\x00\x01"，表示Terminal in VAS App AND Payment Mode
. "\x01\x00\x00\x02"，表示 Terminal in VAS App Only Mode
. "\x01\x00\x00\x03" ， 表示Terminal in Payment Mode Only
*/
int OsPiccApplePoll(char *pcPiccType,unsigned char *pucATQx,unsigned char *pucSendData)
{
	return RET_OK;

}

//功能 关闭载波。
int OsPiccOffCarrier(void)
{
	return RET_OK;

}

//功能 对ISO15693 卡进行初始化配置。
/*
参数 ucDataCodeMode【输入】
设置与卡片交互的传输速率：
. 0：26.48 kbits/s
. 其它值：暂不支持
*/
int OsPiccInitIso15693(unsigned char ucDataCodeMode)
{
	return RET_OK;
}


