
#ifndef _SDK_ICC_
#define _SDK_ICC_

//==================IC卡参数==============================
//IC 卡通道号：
#define ICC_USER_SLOT	0	//	 用户卡
#define ICC_SAM1_SLOT 1	//SAM 卡卡座 1
#define ICC_SAM2_SLOT 2	//SAM 卡卡座 2
#define ICC_SAM3_SLOT 3	//SAM 卡卡座 3
#define ICC_SAM4_SLOT 4	//SAM 卡卡座 4

//	IC 卡返回列表
#define	ERR_SCI_HW_NOCARD		-2800 	//没有卡片
#define	ERR_SCI_HW_STEP		-2801	//交换数据时没有初始化，热复位时未上电。
#define	ERR_SCI_HW_PARITY		-2802	//奇偶校验失败
#define	ERR_SCI_HW_TIMEOUT	-2803	//超时
#define	ERR_SCI_TCK			-2804	//TCK 错误
#define	ERR_SCI_ATR_TS		-2810	//ATR TS 错误
#define	ERR_SCI_ATR_TA1		-2811	//ATR TA1 错误
#define	ERR_SCI_ATR_TD1		-2812	//ATR TD1 错误
#define	ERR_SCI_ATR_TA2 -2813 //ATR TA2 错误
#define	ERR_SCI_ATR_TB1 -2814 //ATR TB1 错误
#define	ERR_SCI_ATR_TB2 -2815 //ATR TB2 错误
#define	ERR_SCI_ATR_TC2 -2816 //ATR TC2 错误
#define	ERR_SCI_ATR_TD2 -2817 //ATR TD2 错误
#define	ERR_SCI_ATR_TA3 -2818 //ATR TA3 错误
#define	ERR_SCI_ATR_TB3 -2819 //ATR TB3 错误
#define	ERR_SCI_ATR_TC3 -2820 //ATR TC3 错误
#define	ERR_SCI_T_ORDER -2821 //协议不是 T0 或 T1
#define	ERR_SCI_PPS_PPSS -2830 //PPS 上的 PPSS 错误
#define	ERR_SCI_PPS_PPS0 -2831 //PPS 上的 PPS0 错误
#define	ERR_SCI_PPS_PCK -2832 //PPS 上的 ATR PCK 错误
#define	ERR_SCI_T0_PARAM -2840 //磁道 0 上的传输的数据太长。
#define	ERR_SCI_T0_REPEAT -2841 //磁道0上字符重复超过最大限制
#define	ERR_SCI_T0_PROB -2842 //T0 发生程序字节错误
#define	ERR_SCI_T1_PARAM -2850 //在 T1 中传输的数据太长
#define	ERR_SCI_T1_BWT -2851 //T1 BWT 过大
#define	ERR_SCI_T1_CWT -2852 //T1 CWT 过大
#define	ERR_SCI_T1_BREP -2853 //T1 太多块重复
#define	ERR_SCI_T1_LRC -2854 //T1LRC 错误
#define	ERR_SCI_T1_NAD -2855 //T1NAD 错误
#define	ERR_SCI_T1_LEN -2856 //T1 LEN 错误
#define	ERR_SCI_T1_PCB -2857 //T1 PCB 错误
#define	ERR_SCI_T1_SRC -2858 //T1SRC 错误
#define	ERR_SCI_T1_SRL -2859 //T1SRL 错误
#define	ERR_SCI_T1_SRA -2860 //T1SRA 错误
#define	ERR_SCI_PARAM -2880 //非法参数

/*
2. LE 和 LC 的组合使用情况如下： ? 
LC=0，LE=0，既无发送数据也无期望数据返回； ? 
LC=0，LE>0，无发送数据但有期望数据返回。如果在实际应用中终端期望返回的数据个数未知，应置 LE=256；否则为确定的数值； ? 
LC>0，LE=0，有发送数据但无期望数据返回； ? 
LC>0，LE>0，有发送数据且有期望数据返回。如果在实际应用中终端期望返回的数据个数未知，应置 LE=256；否则为确定的数值。
*/
typedef struct
{
	unsigned char Cmd[4]; /*CLA, INS, P1, P2*/
	int LC; /*发送到 IC 卡的 DataIn 有效数据长度 */
	unsigned char DataIn[512]; /*发送到 IC 卡的数据*/
	int LE; /*期望返回数据的长度*/
}ST_APDU_REQ;

typedef struct
{
	unsigned char SWA; /*IC 卡状态字 1*/
	unsigned char SWB; /*IC 卡状态字 2*/
	unsigned short LenOut; /* 实际从 IC 卡返回的数据长度*/
	unsigned char DataOut[512]; /*从 IC 卡返回的数据指针*/
}ST_APDU_RSP;


//功能 打开IC 卡读卡设备.
extern int OsIccOpen(int Slot);

//功能 检查指定的卡座是否有卡插
extern int OsIccDetect(int Slot);

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
extern int OsIccInit(int Slot,unsigned long Option,unsigned char *Atr);

//功能 与 IC 卡进行命令交互。
/*
CtrlFlag:
	1. Bit0 表示 T=0 协议下是否自动发送
			GET RESPONSE 指令：
			1-是
			0-否
	2. Bit1~Bit31 保留
*/
extern int OsIccExchange(int Slot,int CtrlFlag,const ST_APDU_REQ *ApduReq,ST_APDU_RSP *ApduRsp);

//关闭 IC 卡设备。
extern int OsIccClose(int Slot);



//================================================射频读卡器=================================
//射频读卡器返回
#define	PCD_ERR_PAR_FLAG 				-2901 //校验错误
#define	PCD_ERR_CRC_FLAG 				-2902 //CRC 错误
#define	PCD_ERR_WTO_FLAG 				-2903 //超时或无卡
#define	PCD_ERR_COLL_FLAG 			-2904 //多卡冲突
#define	PCD_ERR_ECD_FLAG 				-2905 //帧格式错误
#define	PCD_ERR_EMD_FLAG 				-2906 //干扰
#define	PCD_ERR_COM_FLAG 				-2907 //芯片故障,无法正确通信
#define	PCD_ERR_AUT_FLAG 				-2908 //M1 认证错误
#define	PCD_ERR_TRANSMIT_FLAG		-2909 //传输错误
#define	PCD_ERR_PROTOCOL_FLAG		-2910 //协议错误
#define	PCD_ERR_PARAMFILE_FLAG		-2911 //配置文件不存在
#define	PCD_ERR_USER_CANCEL			-2912 //用户取消交易
#define	PCD_ERR_CARRIER_OBTAIN_FLAG	-2913 //载波未获得
#define	PCD_ERR_CONFIG_FLAG			-2914 //配置寄存器不成功
#define	PCD_ERR_RXLEN_EXCEED_FLAG	-2915 //卡片返回数据长度超过设定接收长度
#define	PCD_ERR_NOT_ALLOWED_FLAG	-2951 //参数错误或取值不允许
#define	PCD_CHIP_ABNORMAL 			-2952 //芯片不存在或异常
#define	PCD_CHIP_NOT_OPENED			-2953 //模块未打开
#define	PCD_CHIP_CARDEXIST 			-2954 //卡片未移开
#define	PCD_ERR_NOT_IDLE_FLAG		-2955 //卡片没有在 idle 态
#define	PCD_ERR_NOT_POLLING_FLAG	-2956 //卡片没有进行 POLLING
#define	PCD_ERR_NOT_WAKEUP_FLAG		-2957 //卡片没有唤醒
#define	PCD_ERR_NOT_ACTIVE_FLAG		-2958 //卡片未激活
#define	PCD_ERR_NOT_SUPPORT			-2959 //芯片不支持
//ERR_BATTERY_VOLTAGE_TOO_LOW-1024 电池电压过低
typedef struct pcd_user_t{
	unsigned char wait_retry_limit_w; /* S(WTX)响应发送次数写入允许*/
	unsigned int wait_retry_limit_val; /* S(WTX)响应最大重试次数*/
	unsigned char check_cancel_key_w; /*响应取消键写入允许*/
	unsigned char check_cancel_key_val;  /* 0表示不响应取消键，1表示响应取消键*/
	int (*check_cancel_key_function)(void); /*检测是否按下取消键函数。如果设置check_cancel_key_w=1及check_cancel_key_val=1。则在射频卡交易过程中会调用check_cancel_key_function()。如果check_cancel_key_function()返回0，表示没有按下取消键，如果返回非0，表示已按下取消键，会强行退出交易*/
	unsigned char os_picc_transfer_set_w; /*1表示os_picc_transfer_set_val值有效，0表示os_picc_transfer_set_val值无效*/
	unsigned char os_picc_transfer_set_val; /*OsPiccTransfer收发设置,
													Bit0=0，表示发送禁用CRC,
													Bit0=1，表示发送使能CRC,
													Bit1=0，表示接收禁用CRC,
													Bit1=1，表示接收使能CRC*/
	unsigned char anti_interference_flag; /*寻卡抗干扰功能设置; 1-启用寻卡抗干扰功能，0-不启用寻卡抗干扰功能*/
	unsigned char protocol_layer_fwt_set_w; /*1表示protocol_layer_fwt_set_val值有效，0表示protocol_layer_fwt_set_val值无效*/
	unsigned int protocol_layer_fwt_set_val;  /*设置协议层的帧等待时间FWT值*/
	unsigned char os_picc_transfer_rxlen_set_w;   /*1表示os_picc_transfer_rxlen_set_val值有效，0表示os_picc_transfer_rxlen_set_val值无效*/
	unsigned int os_picc_transfer_rxlen_set_val;	/*OsPiccTransfer半双工块传输中设置最大可接收数据长度值*/
	unsigned char reserved[44];  /*保留字节，用于将来扩展*/
}PCD_USER_ST;


//功能 PCD 模块上电处理，使模块进入准备工作状态。
extern int OsPiccOpen(void);

//功能 PCD 模块下电处理。
extern int OsPiccClose(void);

//功能 载波复位。
extern int OsPiccResetCarrier(void);

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
extern int OsPiccPoll(char *pcPiccType, unsigned char *pucATQx);

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
extern int OsPiccAntiSel(const char pcPiccType,unsigned char *pucUID, const unsigned char ucATQ0, unsigned char*pucSAK);

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
extern int OsPiccActive(const char pcPiccType,unsigned char *pucRATS);

//功能 按照ISO14443-4 中指定的半双工通信协议实现透明传输/接收功能。
/*
pucTxBuff【输入】 待传送数据缓冲区
iTxLen 【输入】 待传送数据的长度，以字节为单位
pucRxBuff【输出】 接收卡片响应数据的缓冲区
piRxLen【输出】 接收到的卡片数据字节数返回
*/
extern int OsPiccTransfer(const unsigned char* pucTxBuff,int iTxLen,unsigned char* pucRxBuff,int * piRxLen);

//功能 按照EMV 模式进行移卡操作。
extern int OsPiccRemove(void);

//功能 验证Mifare 卡。
/*
uid【输入】 卡片ID，长度为4 个字节。
blk no【输入】 块号
group【输入】 认证密码类型，取值为‘A’或‘B’。
psw 【输入】 认证密码，长度为6 个字节。
*/
extern int OsMifareAuthority(unsigned char *uid,unsigned char blk_no,unsigned char group,unsigned char *psw);

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
extern int OsMifareOperate(unsigned charucOpCode,unsigned charucSrcBlkNo,unsigned char* pucVal,unsigned charucDesBlkNo);

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
extern int OsPiccInitFelica(unsigned char ucSpeed,unsigned char ucModInvert);

//功能 在指定的通道上，向卡片发送APDU 格式的数据，并接收响应。
/*
cid 【输入】用于指定卡片逻辑通道号。其取值范围为0~14，取值均为0。
ApduReq 【输入】发送给PICC 卡命令数据结构ST_APDU_REQ
ApduRsp 【输出】从PICC 卡返回的数据结构ST_APDU_RSP
*/
extern int OsPiccIsoCommand(int cid,ST_APDU_REQ*ApduReq,ST_APDU_RSP*ApduRsp);

//功能 设置用户配置。
//参数 pcd_user_config【输入】 用户配置结构体PCD_USER_ST
extern int OsPiccSetUserConfig(PCD_USER_ST *pcd_user_config);

//功能 获取用户配置。
//参数 pcd_user_config【输出】 用户配置结构体PCD_USER_ST
extern int OsPiccGetUserConfig(PCD_USER_ST *pcd_user_config);

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
extern int OsPiccApplePoll(char *pcPiccType,unsigned char *pucATQx,unsigned char *pucSendData);

//功能 关闭载波。
extern int OsPiccOffCarrier(void);

//功能 对ISO15693 卡进行初始化配置。
/*
参数 ucDataCodeMode【输入】
设置与卡片交互的传输速率：
. 0：26.48 kbits/s
. 其它值：暂不支持
*/
extern int OsPiccInitIso15693(unsigned char ucDataCodeMode);


#endif
