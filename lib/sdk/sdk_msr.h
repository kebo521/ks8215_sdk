
#ifndef _SDK_MSR_
#define _SDK_MSR_

#define ERR_MSR_FAILED -2701 				//操作失败
#define ERR_MSR_HEADERR -2702 			//没有找到起始符
#define ERR_MSR_ENDERR -2703 				//没有找到结束符
#define ERR_MSR_LRCERR -2704 				//LRC 检验错误
#define ERR_MSR_PARERR -2705 				//磁道某位数据校验错误
#define ERR_MSR_NOT_SWIPED -2706 		//没有刷卡
#define ERR_MSR_NO_DATA -2707 			//磁条卡没有数据
#define ERR_MSR_END_ZEROERR -2708 		//磁条卡数据格式错误
#define ERR_MSR_PED_DECRYPTERR -2709 	//PED 解密失败
#define ERR_MSR_NO_TRACK_ERR -2710 		//没有检测到磁卡上对应的磁道

//================磁道信息结构体================================================
typedef struct
{
	unsigned char TrackData[256];/* 解码后的位流*/
	int DataLen;/* 磁道数据长度*/
	int Status;/* 磁道数据状态，等于0 时表示读取数据成功；其他值表示读取失败。*/
}ST_MSR_DATA;




//功能 打开磁条阅读器设备。
/*返回
	RET_OK 成功
	ERR_DEV_NOT_EXIST 设备不存在
	ERR_DEV_BUSY 设备被占用
	ERR_DEV_NOT_OPEN 设备打开失败 */
extern int OsMsrOpen(void);


//功能 关闭磁条读卡器设备。
extern void OsMsrClose(void);

//功能 软复位磁条卡阅读器，并清除已读取的磁条卡数据。
extern void OsMsrReset(void);
	
//功能 检测是否刷卡。
/*返回
	TRUE 已刷
	FALSE 未刷
	ERR_DEV_NOT_OPEN 设备未打开 */
extern int OsMsrSwiped(void);


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
extern int OsMsrRead(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3);


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
extern int OsMsrReadJIS(ST_MSR_DATA *Track1,ST_MSR_DATA *Track2,ST_MSR_DATA *Track3,ST_MSR_DATA *Track4);



#endif
