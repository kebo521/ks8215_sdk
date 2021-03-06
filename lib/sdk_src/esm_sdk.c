
#include<time.h>
#include<stdlib.h>
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 





//=======================加解密=========================================================


void OsGetRandom(unsigned char *Random,int RandomLen)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<RandomLen;i++)
		Random[i]=(unsigned char)rand();
}




void OsSHA(int Mode, const void *Data, int DataLen, unsigned char*ShaOut)
{

}


void OsDES(const unsigned char *Input, unsigned char *Output, const unsigned char *DesKey, int KeyLen, int Mode)
{

}


void OsAES(const unsigned char *Input, unsigned char *Output, const unsigned char *AesKey, int KeyLen, int Mode)
{

}



int OsRSA(const unsigned char *Modulus, int ModulusLen, const unsigned char *Exp,int ExpLen, const unsigned char *DataIn, unsigned char *DataOut)
{
	return ERR_GEN_RANDOM;

}


int OsRSAKeyGen(unsigned char *Modulus, unsigned char *PriExp, int ModulusLen, const unsigned char * PubExp)
{
	return ERR_GEN_FAIL;
}


//=========================PED============================================


//功能 打开Prolin 的PED 服务。
/*返回
	RET_OK 成功
	ERR_DEV_BUSY 设备被占用 */
int OsPedOpen(void)
{
	return ERR_DEV_BUSY;
}

//功能 获取当前的PED 的版本�
/*参数: PedVer【输出】 PED 版本信息缓冲区，6 字节。
返回:	RET_OK 成功
		ERR_DEV_NOT_OPEN PED 设备未打开
		ERR_INVALID_PARAM 非法参数 */
int OsPedGetVer(unsigned char * PedVer)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 设置两次计算PIN block 之间的最小间隔时间。
/*参数 TpkIntervalMs
	= 0 使用默认值(30s)
	<1000 自动设为1000(1s)
	>600000 自动设为600000(10min)
	=0xffffffff 当前设置不被改变
返回:
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开 */
int OsPedSetInterval(unsigned long TpkIntervalMs)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 校验脱机明文PIN。
/*参数
IccSlot 卡片所在的卡座号，IccSlot=0。
ExpPinLen【输入】
	可输入的合法密码长度字符串，0~12 的枚举集合。
	应用程序把允许的密码长度全部枚举出来，并
	且用“,”号隔开每个长度，如允许输入4、6
	位密码并且允许无密码直接按确认，则该字符
	串应该设置为“0,4,6”。
	若枚举0 长度则表示可以不输任何数字而直接
	按确认键返回。
Mode【输入】
	0x00，IC 卡命令模式，现支持符合EMV2000
	的IC 卡命令。
TimeoutMs【输入】
	输入PIN 的超时时间，单位：毫秒，最大值为300000。
	0：表示没有超时时间，PED 不做超时控制。
IccRsp【输出】 
	卡片响应的状态码(2 字节：SWA+SWB)
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedVerifyPlainPin (int IccSlot,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 校验密文PIN,步骤如下：1. 获取明文PIN；2. 用应用提供的RsaPinKey 对明文PIN 按照EMV 规范进行加密；3. 用应用提供的卡片命令与卡片通道号，将密文PIN 直接发送给卡片。
/*参数
Iccslot 卡片所在的卡座
RsaPinKey【输入】 加密所需数据结构ST_ RSA_PINKEY。
ExpPinLen【输入】
	可输入的合法密码长度字符串，0~12 的枚举集合。应用程序把允许的密码长度全部枚举出来，
	并且用“,”号隔开每个长度，如允许输入4、6 位密码并且允许无密码直接按确认，则该
	字符串应该设置为“0,4,6”。若枚举0 长度则表示可以不输任何数字而直接按确认键返回.
Mode【输入】 0x00，符合EMV2000IC 卡的命令。
TimeoutMs【输入】
	输入PIN 的超时时间，单位：毫秒，最大值为300000。
	0：表示没有超时时间，PED 不做超时控制。
IccRsp【输出】 卡片响应的状态码(2 字节：SWA+SWB)
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedVerifyCipherPin (int IccSlot,const ST_RSA_PINKEY * RsaPinKey,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 擦除PED 服务保存的所有密钥信息。
/*返回
RET_OK 成功
ERR_DEV_NOT_OPEN 设备未打开 */
int OsPedEraseKeys(void)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 设定某些功能键的功能。
/*参数 KeyFlag
	0x00：在已输入的PIN 已经清空或者没有输PIN 时，按CLEAR 键，PED 退出输入密码状态， 并返回ERR_PED_INPUT_CLEAR。
	0x01：密码输入接口(OsPedGetPinBlock()，OsPedGetPinDukpt() ，OsPedVerifyPlainPin() ，OsPedVerifyCipherPin() etc)在输入PIN过程中，按下CLEAR 键，逐个清除最近输入的PIN，当所有已输入的PIN 被清除时，再按CLEAR 键无响应，并且不会退出PIN 输入函数。
	0x02：表示允许按ATM4 键来结束PIN 输入，不适用无ATM 键的机型。
	0x03：表示允许按FN 键来结束PIN 输入，不适用无FN 键的机型。
	0x04：表示允许按INFO 键来结束PIN 输入，不适用无INFO 键的机型。
	0x05：表示密码输入接口在输入PIN 过程中，按下CANCEL 键，清除所有输入的PIN位，当所有已输入的PIN 被清除时，再按CANCEL 键无响应，并且不会退出PIN 输入函数。
	0xff ：表示恢复默认的功能键设置，即按CLEAR 键清除键入的所有PIN 位，按CANCEL 键退出PIN 输入函数，按ATM4/FN/INFO 键不退出PIN 输入函数。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedSetFunctionKey(int KeyFlag)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 断开与PED 服务的连接。
void OsPedClose(void)
{
}


//功能 用于PIN 输入过程中，终止PIN 输入。
/*返回
	RET_OK 成功
	ERR_DEV_NOT_OPENPED 设备未打开 */
int OsPedCancelPinEntry(void)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 设置脱机明文/密文校验模式。
/*参数
Mode 【输入】
校验模式：
. 0-使用内置密码键盘输入PIN；
. 1-使用外置密码键盘输入PIN，通过PinBlock 参数导入PIN。
TpkIdx 【输入】
TPK 索引：
. Mode 为0 时，无意义；
. Mode 为1 时，使用该索引的TPK 对导入的PinBlock 进行解密得到PIN明文。
PinBlock 【输入】
PIN block：
. Mode 为0 时，无意义；
. Mode 为1 时，表示TPK 加密的ISO9564 Format1 格式的PIN 密文。
PinBlockLen 【输入】 PIN block 的长度
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数	*/
int OsPedSetOfflinePin(unsigned char Mode,unsigned char TpkIdx,unsigned char *PinBlock,unsigned short PinBlockLen)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 用于PIN 输入过程中，发送确认键结束PIN 输入。
/*返回
RET_OK 成功
ERR_DEV_NOT_OPEN PED 设备未打开 */
int OsPedEndPinEntry(void);

//功能监听并获取当前状态下用户输入的PIN 按键数量及当次监听与上次监听中间的历史按键序列。
/*参数
KeyCacheCnt【输出】 获取到的当前历史按键值数量。
KeyCache【输出】
. 键值按输入的时间先后顺序由低位到高位存入缓冲区中。该输出缓冲区的大小必须大于等于64 字节。
. 获取到的历史按键序列最多为64个，若此时按键序列中的按键缓存超过64 个，则输出最新的64 个按键序列。
. 获取到的键值目前只能为“PIN”、� ENTER ” 、“ CLEAR ” 、“CANCEL”、“FN”、“ATM4”这6 种，其中“PIN”数字按键以“*”代替。若此时没有按键输入，获取到的键值则为0。
返回
	>= 0 获取PIN 输入事件成功，返回值大小表示此时PIN 输入界面的“*”的个数。
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数	*/
int OsPedPinKeyNotify(int *KeyCacheCnt,unsigned char *KeyCache)
{
	return ERR_DEV_NOT_OPEN;
}


//功能写入一个密钥，包括TLK，TMK， TWK，SM4_TMK 和SM4_TWK的写入、发散，并可以选择使用KCV 验证密钥正确性。
/*参数 
KeyBlock【输入】
1 byte 格式：0x03
1 byte
	SrcKeyType：
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
1 byte
	SrcKeyIdx：
	. 当SrcKeyType = PED_TLK 时，
	SrcKeyIdx = 1；
	. 当SrcKeyType = PED_TMK 时，SrcKeyIdx = [1~100]；
	. 当ucSrcKeyType =PED_TPK/PED_TAK/PED_TDK 时， ucSrcKeyIdx = [1~100]；
	. 当ucSrcKeyType =PED_SM4_TMK 时，ucSrcKeyIdx = [1~100]；
	. 当ucSrcKeyType =PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK 时，ucSrcKeyIdx = [1~100]。
1 byte
	DstKeyIdx：
	. 当DstKeyType = PED_TLK 时，
	DstKeyIdx = 1；
	. 当DstKeyType = PED_TMK时，
	DstKeyIdx = [1~100]；
	. 当DstKeyType = PED_TPK 或PED_TAK 或PED_TDK 时，DstKeyIdx = [1~100]；
	. 当DstKeyType=PED_SM4_TMK时，DstKeyIdx=[1~100]；
	. 当DstKeyType=PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK/PED_TDFK 时，DstKeyIdx=[1~100]。
7 bytes 保留域，随机数
1 byte
	DstKeyType：
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
	. PED_TDFK
1 byte
	DstKeyLen：8/16/24当DstKeyType 为PED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK时，DstKeyLen=16。24 bytesDstKeyValue目的密钥明文/密文
1 byte
	KcvMode：
	0x00：无验证
	0x01：对8 个字节的0x00 计算DES/TDES 加密，得到密文的前3 个字节即为KCV。
	0x02：首先对密钥明文进行奇校验，再对“\x12\x34\x56\x78\x90\x12\x34\x56”进行DES/TDES 加密运算，得到密文的前3 个字节即为KCV。
	0x03：传入一串数据KcvData，使用源密钥对 [目的密钥密文+ KcvData]进行指定模式的MAC 运算，得到8 个字节的MAC 即为KCV。
	0x04：对16 字节的0x00 进行SM4加密，得到密文的前4 个字节即为KCV。
	注：模式0x01、0x02 及0x03 只用于MK/SK 密钥注入验证，模式0x04 只用于SM4 密钥注入验证。
128bytes
	KcvData：
	. KcvMode 为0x00/0x01/0x02时，填充随机数；
	. KcvMode 为0x03 时，KcvData第一个字节为参与计算的KCV数据的长度，之后为KCV 数据，KCV 数据之后一个字节表示MAC 运算模式.
8 bytes
	. 当KcvMode = 0x00 时，填充随机数；
	. 当KcvMode =0x01/0x02/0x03/0x04 时，KcvValue 指向KCV 的值。
10 bytes 填充随机数
返回
RET_OK 成功
ERR_DEV_NOT_OPEN PED 设备未打开
ERR_INVALID_PARAM 非法参数
ERR_SYS_BAD 系统错误
ERR_PED_KEY_IDX_ERR 密钥索引错误
ERR_PED_KEY_TYPE_ERR 密钥类型错误
ERR_PED_TAMPERED PED 被锁定
ERR_PED_NO_MORE_BUF 系统内存空间不足
ERR_PED_NORMAL_ERRPED 通用错误（ KeyBlockFormat 错误）
ERR_PED_DERIVE_ERR 密钥发散错误
ERR_PED_KCV_MODE_ERR PED KCV 校验模式错误
ERR_PED_KCV_CHECK_FAIL PED KCV 校验失败 */
int OsPedWriteKey(const unsigned char * KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//功 能 写入一个TIK 密钥，并可以选择使用KCV 验证密钥正确性。
/*参数 KeyBlock【输入】
1 byte 格式：0x03
1 byte
	SrcKeyType：
	. PED_TLK
1 byte
	SrcKeyIdx：
	. 当SrcKeyType = PED_TLK时，SrcKeyIdx = 1；
	. 明文写入时，SrcKeyIdx = 0。
1 byte
	DstKeyIdx。
	DstKeyIdx = [1~100]。
7 bytes 保留域，随机数
1 byte
	DstKeyType：
	. PED_TIK
1 byte DstKeyLen：8/1624 bytesDstKeyValue目的密钥明文/密文
1 byte
	KcvMode：
	0x00：无验证
	0x01：对8 个字节的0x00 计算
	Prolin 应用编程接口编程指南的前3 个字节即为KCV。
	0x02：首先对密钥明文进行奇校验，再对“ \x12\x34\x56\x78\x90\x12\x34\x56”进行DES/TDES 加密运算，得到密文的前3 个字节即为KCV。
	0x03：传入一串数据KcvData，使用源密钥对 [目的密钥密文+KcvData] 进行指定模式的MAC 运算，得到8 个字节的MAC 即为KCV。
128 bytes
KcvData：
. KcvMode 为0x00/0x01/0x02 时，填充随机数；
. KcvMode 为0x03 时，KcvData第一个字节为参与计算的KCV数据的长度，之后为KCV 数据，KCV 数据之后一个字节表示MAC 运算模式.
8 bytes
. 当KcvMode = 0x00 时，填充随机数。
. 当KcvMode = 0x01/0x02/0x03时，KcvValue 指向KCV 的值。
10bytes  初始KSN
返回
ERR_OK 成功
ERR_DEV_NOT_OPEN 设备未打开
ERR_INVALID_PARAM 非法参数 */
int OsPedWriteTIK(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//功能使用指定密钥类型的密钥索引所在的密钥明文与一串数据进行运算(异或等)，得到密钥写入到同一类型密钥区的另一指定索引位置。
/*参数
KeyType 密钥类型：
. PED_TMK
. PED_TPK
. PED_TAK
. PED_TDK
SrcKeyIdx 源密钥索引号，取值范围为[1~100]。
DstKeyIdx 目的密钥索引号，取值范围为[1~100]。
KeyVar【输入】
	24 字节，需要参与运算的字符串；为与密钥长度相同的字符串，用于和源索引的密钥异或；可扩展.
返回
RET_OK 成功
ERR_DEV_NOT_OPENPED 设备未打开
ERR_INVALID_PARAM 非法参数 */
int OsPedWriteKeyVar(int KeyType,int SrcKeyIdx,int DstKeyIdx,const unsigned char *KeyVar)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 在输入PIN 时，设置界面显示星号的布局属性。
/*参数
x 横坐标
y 纵坐标
fontSize 星号的字体大小：
	. fontSize = 16，16 个字点大小的字符；
	. fontSize = 24，24 个字点大小的字符；
	. fontSize = 32，32 个字点大小的字符；
	. fontSize = 48，48 个字点大小的字符；
	该函数中星号的显示使用PED 内部字体文件，与系统所装字库无关。
fontColor 星号的字体颜色：使用宏定义 RGB(_r, _g, _b)，根据输入的三原色生成16 位颜色值。
align 对齐方式：
	PED_ASTERISK_ALIGN_LEFT：左边起始位置固定，自左向右顺序显示星号；
	PED_ASTERISK_ALIGN_CENTER：中间位置固定，左右两边对称显示星号；
	PED_ASTERISK_ALIGN_RIGHT：右边起始位置固定，自右向左顺序显示星号。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedSetAsteriskLayout(int x,int y,int fontSize,int fontColor,unsigned char align)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 输入PIN 时，设置前景和背景图标的布局属性。
/*参数
	X【输入】 前景和背景图标的起始横坐标
	Y【输入】 前景和背景图标的起始纵坐标
	Interval【输入】 两个相邻图标之间的间距
	IconNum【输入】 背景图标的数目
	PinIcon【输入】前景图标绝对路径，支持BMP 和PNG图标
	PinIconLen 【输入】前景图标绝对路径长度，最长256 字节
	PinIconBG 【输入】背景图标绝对路径，支持BMP 和PNG图标，如不需要背景图标，可设为NULL。
	PinIconBGLen【输入】背景图标路绝对径长度，最长256 字节；如不需要背景图标，可设为0。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedSetPinIconLayout(int X,int Y,int Interval,unsigned char IconNum,char *PinIcon,int PinIconLen,char *PinIconBG,int PinIconBGLen)
{
	return ERR_DEV_NOT_OPEN;
}


//功能指定的时限内,扫描键盘上输入ExpPinLenIn 指定长度的PIN，并输出由Mode 指定算法加密生成的PIN block。
/*参数
KeyIdx TPK 的索引号，取值范围为[1-100] 。
DataIn【输入】
. 当Mode=0x00 时，DataIn 指向卡号移位后生成的16 位主帐号。
. 当Mode=0x01 时，DataIn 无意义，可为任意值。PED 将采用随机数代替DataIn 参与PinBlock 的计算。
. 当Mode=0x02 时，DataIn 指向卡号移位后生成的16 位主帐号。
. 当Mode=0x03 时，DataIn 为交易流水号ISN 【6 字节，ASCII 码】。
. 当Mode=0x10 时，DataIn 无意义，可为任意值。PED 将采用随机数代替DataIn 参与PinBlock 的计算。
ExpPinLen【输入】
	可输入的合法密码长度字符串，0~12 的枚举集合。应用程序把允许的密码长度全部枚举出来，并且用“,”号隔开每个长度，如允许输入4 位、6 位
	密码且允许无密码直接按确认，则该字符串应该设置为“0,4,6”。枚举0 表示可以不输任何数字而直接按确认键返回。
Mode
	选择PIN BLOCK 的格式
		使用DES（3DES）算法加密的PinBlock的格式：
		. 0x00 0x00 ISO9564 格式 0
		. 0x01 0x01 ISO9564 格式 1
		. 0x02 0x02 ISO9564 格式 3
		. 0x03 0x03 HK EPS 专用格式
		使用AES 算法加密的PinBlock 的格式：
		. 0x10 PinBlock 明文前八字节为ISO9564 格式 1 的明文数据，后八字节进行#PKCS7 填充，具体为8 字节的0x08。
TimeoutMs
	输入PIN 的超时时间单位：毫秒最大值为3000000：表示没有超时时间，PED 不做超时控制。
PinBlock【输出】
	8 或16 字节，指向生成的PIN block。Mode 为0x10 时，PinBlock 长度为16 字节。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedGetPinBlock(int KeyIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 重新计算PIN block，并选择是否更换TPK。
/*参数 
UpdateFlag【输入】:  0：不更换TPK； 非0：更换TPK。
KeyInfo【输入】
	参照OsPedWriteKey()下KeyBlock 的定义，长度为184 字节。当UpdateFlag 为0 时，KeyBlock 下只有DstKeyIdx 有意义，
	采用DstKeyIdx指定的TPK，重新计算PIN block。
DataIn【输入】
	. 当UpdateFlag 为0，Mode=0x03 时，为交易流水号ISN 【6 字节，ASCII 码】；
	. 当UpdateFlag 为0，Mode=0x00 时，DataIn 前16 字节为旧的PAN，后16字节为新的PAN，PAN 是指：卡号移位后生成的16 位主帐号；
	. 当UpdateFlag 为非0 时， 可为NULL。
PinBlock【输入/输出】
	8 字节，输入原PIN block 数据，输出新的PIN block
Mode
	0x00：ISO9564 格式0；
	0x03：HK EPS 专用格式【详见附录2EPS_PINBLOCK 格式】
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedUpdatePinBlock (int UpdateFlag,const unsigned char * KeyInfo,const unsigned char * DataIn,unsigned char * PinBlock,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 用KeyIdx 指定的MAC 密钥对DataIn 进行Mode 指定的运算。
/*参数
KeyIdx【输入】 TAK 的索引号，取值范围为[1~100]。
DataIn【输入】需进行MAC 运算的数据，长度小于等于8192 字节。
DataInLen【输入】MAC 运算的数据长度，当长度不能被8 字节整除，则自动补“\x00”。
Mac【输出】 8 字节，MAC 输出。
Mode【输入】将DataIn 按8 字节为单位分块，依次为BLOCK1，BLOCK2，BLOCK3 等。
0x00：将BLOCK1 用MAC 密钥做DES/TDES 加密，加密结果与BLOCK2 进行逐位异或后再用TAK 做DES/TDES 加密，依次进行得到8 字节的加密结果。
0x01：将BLOCK1 和BLOCK2 进行逐位异或，异或结果与BLOCK3 进行逐位异或，依次进行，最后得到8 字节的异或结果，将该结果用TAK 进行DES/TDES 加密运算。
0x02：依据ANSIX9.19 规范，将BLOCK1 用TAK做DES 加密(只取前8 个字节的密钥)，加密结果与BLOCK2 进行逐位异或后再用TAK 做DES 加密，依次进行得到8 字节的加密结果，最后采用DES/TDES 加密。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedGetMac(int KeyIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//功能使用TDK 对DataInLen 长度的数据进行DES/TDES 解密或加密运算，输出明文或密文；一个指定的TDK，只能用于加密或解密运算。
/*参数
KeyIdx【输入】 TDK 索引号，取值范围为[1~100]。
InitVector【输入】加解密运算的初始向量，长度为8 字节。当Mode=0x02/0x03/0x04/0x05 时,需要用到初始向量，
				为NULL 时默认为“\x00\x00\x00\x00\x00\x00\x00\x00”；当Mode=0x00/0x01 时，不需要初始向量，可以为NULL。
DataIn【输入】 指向需要进行运算的数据。
DataInLen【输入】需要运算的数据长度，以字节为单位，应小于等于1024；
	当Mode 为0x00~0x05 时，必须为8 的倍数；
	当Mode 为0x06~0x07 时，可以不是8 的倍数。
DataOut【输出】 指向运算后的数据。
Mode【输入】
. 0x00：ECB 解密
. 0x01：ECB 加密
. 0x02：CBC 解密
. 0x03：CBC 加密
. 0x04：OFB 解密
. 0x05：OFB 加密
. 0x06：CFB8 解密
. 0x07：CFB8 加密
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedDes(int KeyIdx,unsigned char * InitVector,const unsigned char *DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//功能获取密钥的KCV 值，以供对话双方进行密钥验证：密钥类型非TIK 时，用指定的密钥及算法对一段数据进行加密，并返回数据密文的前3 字节；密钥类型为TIK 时，返回与TIK 一并注入(计算得到)的8 字节KCV。
/*参数
KeyType 密钥类型：
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
. PED_TIK
. PED_SM4_TMK
. PED_SM4_TPK
. PED_SM4_TAK
. PED_SM4_TDK
KeyIdx 密钥的索引号，如：
. TLK，只能为1。
. TMK 可取值1~100。
. TWK 可取值1~100。
. TIK 可取值1~100。
KcvMode  KCV 校验模式
	0x00：使用DES 算法计算密钥的KCV；
	0x04：使用SM4 算法计算SM4 密钥的KCV，此时密钥类型只能为SM4 系列的密钥。（ KeyType 只能是PED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK）
KcvDataLen 参与计算KCV 的数据长度，不超过128 字节，且被8 整除；密钥类型为TIK 时可为0；KCV校验模式为0x04 时，该数据长度必须能被16整除。
KcvData【输入】参与计算KCV 的数据，密钥类型为TIK 时可为NULL。
Kcv【输出】
	KCV 值，3 或8 字节。密钥类型为TIK 时，
	KCV 为8 字节，其余为3 字节。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数	*/
int OsPedGetKcv(int KeyType,int KeyIdx,int KcvMode,int KcvDataLen,unsigned char *KcvData,unsigned char *Kcv)
{
	return ERR_DEV_NOT_OPEN;
}



//功能用SrcKeyIdx 指定的密钥对DstFromKeyIdx 指定的密钥进行加密或解密，发散新密钥，并将结果保存到DstToKeyIdx 指定的密钥。
/*参数
SrcKeyType 源密钥类型：
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
SrcKeyIdx 源密钥的索引号，如：
. TLK，只能为1。
. TMK 可取值1~100。
. TWK 可取值1~100。
DstKeyType 目的密钥类型：
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
DstFromKeyIdx 目的密钥源索引号
DstToKeyIdx 目的密钥目的索引号
Mode
	0x00：DES/TDES 解密
	0x01：DES/TDES 加密
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedDeriveKey(int SrcKeyType,int SrcKeyIdx,int DstKeyType,int DstFromKeyIdx,int DstToKeyIdx,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用Framebuffer 数据或者图片数据设置PIN 输入时的背景。
/*参数
Mode【输入】PIN 输入背景的设置方式：
	Mode = 0x00，清除该接口的设置；
	Mode = 0x01，使用Framebuffer 数据设置PIN 输入时的背景；
	Mode = 0x02，使用图片数据设置PIN输入时的背景。
Bg【输入】存放Framebuffer 数据或者图片数据的Buffer。
BgLen【输入】存放Framebuffer 数据或者图片数据Buffer 的长度。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedSetPinBg(unsigned char Mode,const unsigned char *Bg,int BgLen)
{
	return ERR_DEV_NOT_OPEN;
}




//功能 定制化PED 软键盘。
/*参数
IconPath 【输入】存放键盘图片的绝对路径，不支持相对路径，路径长度最长不超过256字节，可为NULL。当IconPath 为NULL 时，系统使用默认的图片。
KeypadColorBg 【输入】键盘的背景色RGBA 值，长度为4字节，可为NULL。当KeypadColorBg 为NULL 时，系统使用默认的键盘背景色。
Mode 【输入】设置模式：
	Mode = 0x00 时，使用系统默认的键盘图片以及背景颜色；
	Mode = 0x01 时，使用用户指定的键盘图片或者用户指定的键盘背景颜色。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_FILE_NOT_EXIST 图片资源文件不存在
	ERR_VERIFY_SIGN_FAIL 图片资源文件验签失败 */
int OsPedCustomKeypad(char *IconPath,unsigned char *KeypadColor,unsigned char Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//功能指定的时限内，扫描键盘上输入的PIN，并输出使用DUKPT 的PIN 密钥计算生成的PIN block。
/*参数
GroupIdx【输入】 DUKPT 组索引号，取值范围为[1~100]。
DataIn【输入】
	1. 当Mode=0x20 时，DataIn 指向卡号移位后生成的16 位主帐号。
	2. 当Mode=0x21 时，无意义。
	3. 当Mode=0x22 时，DataIn 指向卡号移位后生成的16 位主帐号。
	4. 当Mode=0x23 时，为交易流水号ISN 【6字节，ASCII 码】。
ExpPinLen【输入】
	可输入的合法密码长度字符串，0~12 的枚举集合。应用程序把允许的密码长度全部枚举出来，并且用“,”号隔开每个长度，如允许输入4、
	6 位密码并且允许无密码直接按确认，则该字符串应该设置为“0,4,6”。若枚举0 长度则表示可以不输任何数字而直接按确认键返回。
Mode【输入】选择PIN block 的格式：
. 0x20 ISO9564 格式0，KSN 不自动加1
. 0x21 ISO9564 格式1，KSN 不自动加1
. 0x22 ISO9564 格式2，KSN 不自动加1
. 0x23 HK EPS 格式，KSN 不自动加1
TimeoutMs【输入】
	输入PIN 的超时时间，单位：毫秒。最大值为300000
	0：表示没有超时时间，PED 不做超时控制。
Ksn【输出】 10 字节，指向当前的KSN。
PinBlock【输出】 8 字节，指向生成的PIN block。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedGetPinDukpt(int GroupIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *Ksn,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用DUKPT 密钥计算MAC 值。
/*参数
GroupIdx【输入】 DUKPT 组索引号，取值范围为[1~100]。
DataIn【输入】 指向需要计算MAC 的数据内容。
DataInLen【输入】数据的长度，小于等于8192 字节，当不为8字节整除时自动补“\x00”。
Mac【输出】 指向得到的MAC。
Ksn【输出】 指向当前的KSN。
Mode【输入】将DataIn 按8 字节为单位分块，依次为BLOCK1，BLOCK2，BLOCK3 等。
	0x20：将BLOCK1 用MAC 密钥做TDES 加密，加密结果与BLOCK2 进行逐位异或后再用TAK 做TDES 加密，依次进行得到8 字节的加密结果。
	0x21：将BLOCK1 和BLOCK2 进行逐位异或，异或结果与BLOCK3 进行逐位异或，依次进行，最后得到8 字节的异或结果，将该结果用TAK 进行TDES加密运算。
	0x22：依据ANSIX9.19 规范，将BLOCK1用TAK 做DES 加密(只取前8 个字节的key)，加密结果与BLOCK2 进行逐位异或后再用TAK 做DES 加密，依次进行得到8 字节的加密结果，直到最后一次采用TDES 加密。
	. 0x20/0x21/0x22/0x40/0x41/0x42KSN 不自动加1。
	. 0x40/0x41/0x42 计算MAC 方式与0x20/0x21/0x22 相同。
	. 0x40/0x41/0x42 选择应答MAC 密钥，0x20/0x21/0x22KSN 选择请求或应答MAC 密钥。
	. 其它值保留扩展MAC 算法。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedGetMacDukpt(int GroupIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 使用DUKPT 密钥，对输入数据进行加解密。
/*参数
GroupIdx【输入】 DUKPT 组索引号，取值范围为[1~100]。
KeyVarType【输入】
	0x00：使用应答或请求MAC 密钥
	0x01：使用DUKPT DES 密钥
	0x02：使用PIN variant 为data 加密，ECB和CBC 加密可用，即Mode 值可为0x01 和0x03。当DUKPT 密钥为8字节时，使用的不是标准的DES 算法，而是ANSI9.24-1998 定义的特殊DES 算法。
	0x03：使用应答MAC 密钥，仅支持加密模式，即Mode 值只能为0x01、0x03、0x05
	0x04：使用应答DES 密钥，仅支持加密模式，即Mode 值只能为0x01、0x03、0x05
InitVector【输入】加解密运算的初始向量，8 字节
	当Mode=0x02/0x03/0x04/0x05 时,需要用到初始向量，为NULL 时默认为“\x00\x00\x00\x00\x00\x00\x00\x00”；
	当Mode=0x00/0x01 时，不需要初始向量，可以为NULL。
DataInLen【输入】 需要加解密的数据长度，小于等于 8192
DataIn【输入】 指向需要进行运算的数据
DataOut【输出】 指向运算后的数据
Ksn【输出】 指向当前的KSN，10 字节
Mode【输入】加解密模式：
. 0x00：ECB 解密
. 0x01：ECB 加密
. 0x02：CBC 解密
. 0x03：CBC 加密
. 0x04：OFB 解密
. 0x05：OFB 加密
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedDesDukpt(int GroupIdx,int KeyVarType,unsigned char *InitVector,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//功能 获取当前的KSN 值。
/*参数
GroupIdx【输入】 DUKPT 组索引号，取值范围为[1~100]。
Ksn【输出】 指向当前KSN，10 字节
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedGetKsnDukpt(int GroupIdx,unsigned char *Ksn)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 增加指定DUKPT 组的KSN 值。
/*参数 
GroupIdx【输入】 DUKPT 组索引号， 取值范围为[1~100]。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedIncreaseKsnDukpt(int GroupIdx)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 读取RSA 公钥。
/*参数
RsaKeyIdx【输入】 RSA Key 的索引号，取值范围为[1~10]。
RsaKey【输出】 RSA 公钥结构体ST_RSA_KEY
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedReadRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 注入RSA 密钥到PED。
/*参数
RsaKeyIdx【输入】 RSA 密钥的索引号，取值范围为[1~10]。
RsaKey【输入】指向需要注入PED 的RSA 密钥结构体ST_RSA_KEY。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedWriteRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 用存储在PED 的RSA 密钥进行RSA 数据运算。
/*参数
RsaKeyIdx【输入】 RSA Key 的索引号，取值范围为[1~10]。
DataInLen【输入】需要进行运算的数据长度，单位为字节，与RSA 密钥的模长相同。长度值为64 到512 之间8 的倍数。
DataIn【输入】 指向需要进行运算的数据
DataOut【输出】 指向运算后的数据
KeyInfo【输出】 密钥信息
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedRsaRecover(int KeyIdx,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *KeyInfo)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 读取RSA 密钥密文。
/*参数
RsaKeyIdx【输入】 RSA Key 的索引号，取值范围为[1~10]。
CipherRsaKey【输出】 指向RSA 密钥密文
返回
	>0 表示RSA 密钥密文的长度
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedReadCipherRsaKey(int RsaKeyIdx,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 写RSA 密钥密文。
/*参数
RsaKeyIdx【输入】  RSA Key 的索引号，取值范围为[1~10]。
CipherRsaKeyLen【输入】 写入的RSA 密钥密文数据的字节长度，小于等于1024
CipherRsaKey【输入】 指向RSA 密钥密文
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedWriteCipherRsaKey(int RsaKeyIdx,int CipherRsaKeyLen,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 将一个AES 密钥的密文或者明文写入到AES 密钥区域的指定索引的位置，并可以选择使用KCV 验证密钥正确性。
/*参数 KeyBlock【输入】
1 byte 格式：0x03
1 byte SrcKeyType：
	. PED_TLK
	. PED_TMK
1 byte
	SrcKeyIdx：
	. 当SrcKeyType = PED_TLK 时，SrcKeyIdx = 1；
	. 当SrcKeyType = PED_TMK时，SrcKeyIdx = [1~100]；
	. 当SrcKeyIdx = 0，密钥将以明文形式写入PED。
1 byte DstKeyIdx：[1~100]
7 bytes 保留域，随机数
1 byte
	DstKeyType：
	. PED_TAESK
	. PED_AES_TPK
	. PED_AES_TAK
	. PED_AES_TDK
1 byte DstKeyLen：16/24/32
32 bytes DstKeyValue：目的密钥明文/密文
1 byte  KcvMode：
	0x00：无验证。
	0x01：对16 个字节的全0x00 计算AES/ECB 加密，得到密文的前3 个字节即为KCV 的值。
	0x02：首先对密钥明文进行奇校验，再对“ \x12\x34\x56\x78\x90\x12\x34\x56\x12\x34\x56\x78\x90\x12\x34\x56”进行AES/ECB加密运算，得到密文的前3个字节即为KCV 的值。
	0x03：传入一串数据KcvData，使用源密钥对[ 目的密钥密文+KCV 数据]进行指定模式的MAC 运算，得到8 个字节的MAC 即为KCV 的值。
128 bytes
	KcvData：
	. KcvMode 为0x00/0x01/0x02 时，填充随机数；
	. KcvMode 为0x03 时，KcvData第一个字节为参与计算的KCV数据的长度，之后为KCV 数据，KCV 数据之后第一个字节表示MAC 运算模式。
8 bytes
. 当KcvMode=0x00 时，填充随机数；
. 当KcvMode=0x01/0x02/0x03 时，KcvValue 指向KCV 的值。
2 bytes 填充随机数
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN PED 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedWriteAesKey(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用TAESK 或PED_AES_TDK 密钥对DataInLen 指定长度的数据进行AES 加解密运算。
/*参数
KeyIdx【输入】 TAESK 密钥索引号，取值范围为[1~100]。
InitVector 【输入/输出】加解密运算的初始向量，16 字节。
当Mode=0x02/0x03/0x04/0x05 时,需要用到初始向量，为NULL 时默认为16 字节的全0x00。
当Mode=0x00/0x01 时，不需要初始向量，可以为NULL。
当Mode=0x06/0x07 时，表示运算时所需的16 字节长度的临时计数器，运算成功后该计数器将被更新。
DataIn【输入】 需要进行运算的数据
DataInLen【输入】需要进行运算的数据长度，以字节为单位，应小于等于1024，且为16 的倍数。当运算模式为CTR 模式时，数据长度没有限制。
DataOut【输出】 指向运算后的数据。
Mode 【输入】
. 0x00：ECB 解密模式
. 0x01：ECB 加密模式
. 0x02：CBC 解密模式
. 0x03：CBC 加密模式
. 0x04：OFB 解密模式
. 0x05：OFB 加密模式
. 0x06：CTR 解密模式
. 0x07：CTR 加密模式
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 无效的参数 */
int OsPedAes(int KeyIdx,unsigned char*InitVector,const unsigned char*DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//功能 生成一组SM2 密钥对。
/*参数
PvtKey【输出】 指向SM2 私钥，32 字节
PubKey【输出】 指向SM2 公钥，64 字节
KeyLenBit【输入】 私钥位数，256 位
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误 */
int OsPedGenSM2Pair(unsigned char *PvtKey,unsigned char *PubKey,int KeyLenBit)
{
	return ERR_DEV_NOT_OPEN;
}




//功能 注入SM2 私钥或公钥到PED。
/*参数
KeyIdx 【输入】 SM2 密钥索引号，取值范围为[1~20]
KeyType【输入】密钥类型：
	PED_SM2_PVT_KEY 0x30 私钥
	PED_SM2_PUB_KEY 0x31 公钥
KeyValue 【输入】
	当KeyType=0x30 时，KeyValue 长度为32 字节
	当KeyType=0x31 时，KeyValue 长度为64 字节
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误 */
int OsPedWriteSM2Key(int KeyIdx,int KeyType,unsigned char *KeyValue)
{
	return ERR_DEV_NOT_OPEN;
}



//功能 使用 SM2 算法获得签名信息。
/*参数
PubKeyIdx【输入】 SM2 公钥索引号，取值范围为[1~20]
PvtKeyIdx【输入】 SM2 私钥索引号，取值范围为[1~20]
Uid【输入】 签名者ID无特殊约定的情况，用户身份的标识ID长度为16 字节，
			其默认值为0x31, 0x32,0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38。
UidLen【输入】 签名者ID 长度，小于等于512 字节。
Input【输入】 需要签名的数据
InputLen【输入】 数据长度，小于等于2048 字节
Signature【输入】 签名值，64 字节
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定 */
int OsPedSM2Sign(int PubKeyIdx,int PvtKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用 SM2 公钥验证签名。
/*参数
PubKeyIdx【输入】 SM2 公钥索引号，取值范围为[1~20]
Uid【输入】 签名者ID。无特殊约定的情况，用户身份的标识ID
的长度为16 字节，其默认值为0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38。
UidLen【输入】 签名者ID 长度，小于等于512 字节
Input【输入】 需要签名的数据
InputLen【输入】 数据长度，小于等于2048 字节
Signature【输入】 签名值，64 字节
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_VERIFY_SIGN_FAIL 验证签名失败
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定 */
int OsPedSM2Verify(int PubKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,const unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 使用 SM2 公钥加密数据或私钥解密数据。
/*参数
KeyIdx【输入】 SM2 密钥索引号，取值范围为[1~20]
Input【输入】 待加密或解密的数据
InputLen【输入】 数据长度，加密操作时小于等于（2048-96）字节，解密操作时小于等于2048 字节。
Output【输出】 加密或解密后的数据
OutputLen【输出】 加密或解密后的数据长度，加密后数据长度为原数据长度+96 字节，解密后数据长度为原数据长度-96 字节。
Mode【输入】 PED_DECRYPT0x00：使用SM2 私钥解密数据PED_ENCRYPT0x01：使用SM2 公钥加密数据
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定 */
int OsPedSM2Recover(int KeyIdx,unsigned char *Input,int InputLen,unsigned char *Output,int *OutputLen,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}

//功能 使用 SM3 算法计算杂凑值。
/*参数
Input【输入】 输入数据
InputLen【输入】 输入数据长度
Output【输出】 杂凑值，32 字节。
Mode【输入】 支持0x00，其它值保留。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误 */
int OsPedSM3(unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用SM4 算法加密或解密数据。
/*参数
KeyIdx【输入】 PED_SM4_TDK 的索引号，取值范围为[1～100]
InitVector【输入】 初始向量，16 字节。对于ECB 模式该参数为NULL。
Input【输入】 需要加密或解密的数据
InputLen【输入】 数据长度小于等于1024，以字节为单位，且为16 的倍数
Output【输出】 加密或解密后的数据，长度为输入长度
Mode【输入】 
PED_SM4_ECB_DECRYPT 0x00:SM4 ECB 解密
PED_SM4_ECB_ENCRYPT 0x01:SM4 ECB 加密
PED_SM4_CBC_DECRYPT 0x02:SM4 CBC 解密
PED_SM4_CBC_ENCRYPT 0x03:SM4 CBC 加密
返回 
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定
	ERR_PED_KEY_LEN_ERR 密钥长度错误 */
int OsPedSM4(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 使用SM4 算法计算MAC。
/*参数
KeyIdx【输入】 PED_SM4_TAK 的密钥索引号，取值范围为[1～100]
InitVector【输入】 初始向量，16 字节。
Input【输入】 需要进行MAC 运算的数据
InputLen【输入】 数据长度小于等于1024，以字节为单位，且为16 的倍数
MacOut【输出】 MAC 值
Mode【输入】 
	0x00：使用SM4 CBC 算法计算MAC 值，首先将初始向量与BLOCK1 进行异或，并用SM4算法使用TAK对异或的结果进行加密，
			然后获得的密文与BLOCK2 异或，用SM4 算法使用TAK 对结果加密，按顺序给出16 字节的加密结果。MacOut 为16 字节。
	0x01：使用SM4-TAK 密钥对输入数据计算SM3 Hash，计算结果作为MacOut(32 字节)。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定
	ERR_PED_KEY_LEN_ERR 密钥长度错误 */
int OsPedGetMacSM(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *MacOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 指定的时限内，扫描键盘上输入的PIN 并输出采用SM4 算法生成的PIN block 加密数据块。
/*参数
KeyIdx【输入】 PED_SM4_TPK 的密钥索引号，取值范围为[1～100]
ExpPinLenIn【输入】 可输入的合法密码长度字符串，0~12 的枚举集合。
应用程序把允许的密码长度全部枚举出来，并且用“,”号隔开每个长度，如允许输入4、6 位密码，则该字符串应该设置为“4,6”。
DataIn【输入】 当Mode=0x00 时，DataIn 指向卡号移位后生成的16 位主帐号。
PinBlockOut【输出】 生成的密文PIN block，16 字节
Mode【输入】 PIN block 的格式0x00 ISO9564 格式0
TimeoutMs【输入】 输入PIN 的超时时间，单位：毫秒。最大值为300000ms。0 表示采用默认超时时间30000ms。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数
	ERR_SYS_BAD 系统错误
	ERR_PED_KEY_IDX_ERR 密钥索引错误
	ERR_PED_KEY_TYPE_ERR 密钥类型错误
	ERR_PED_NO_KEY 密钥不存在
	ERR_PED_TAMPERED PED 被锁定
	ERR_PED_KEY_LEN_ERR 密钥长度错误
	ERR_PED_NO_PIN_INPUT 未输入任何键值
	ERR_PED_PIN_INPUT_CANCEL 取消输入
	ERR_PED_WAIT_INTERVAL 间隔时间太短 */
int OsPedGetPinBlockSM4(int KeyIdx,const char *ExpPinLenIn,unsigned char *DataIn,unsigned char *PinBlockOut,int Mode,unsigned long TimeoutMs)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 检查DESFire 卡端传来的会话密钥B 并生成会话密钥A。将A 和B合并为一个完整的会话密钥，然后对其进行加密并输出。
/*参数
SrcKeyIdx【输入】
DESFire 工作密钥索引，取值范围为1-100。
KeySetVer【输入】 密钥版本，用于检查DESFire 版本。
DivType【输入】密钥发散模式：
. 当DivType = 0x00 时，表示不发散，此时DESFire 密钥用于加密会话密钥；
. 当DivType = 0x01 时，结合Uid来发散密钥，该发散密钥用于加密会话密钥。
Mode【输入】会话密钥的加密类型：0x02：16 字节的3DES 加密运算
Uid【输入】用户数据，数据长度固定为8 字节，用于发散会话密钥。
EncRndB【输入】DESFire 卡生成的会话密钥B：
. 当会话密钥长度为8 或16 字节时， EncRndB 长度为8 字节；
. 当会话密钥长度为24 字节时，EncRndB 长度为16 字节。
EncSessionKey【输出】 加密的(RndA + RndB’).
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedDFAuthDiver(int SrcKeyIdx,int KeySetVer,int DivType,unsigned char Mode,unsigned char *Uid,unsigned char *EncRndB,unsigned char *EncSessionKey)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 检查DESFire 卡端传来的密文会话密钥A’。
/*参数
EncRndA【输入】 密文A’。
DataLen【输入】EncRndA 长度：
. 当会话密钥长度为8 或16 字节时，EncRndA 长度为8 字节；
. 当会话密钥长度为24 字节时，EncRndA 长度为16 字节。
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedDFAuthMerge(unsigned char *EncRndA,int DataLen)
{
	return ERR_DEV_NOT_OPEN;
}


//功能 注入来自RKI 服务器的密钥。
/*参数
KeyBlkLen 【输入】 RKI 密钥数据长度
KeyBlk 【输入】 RKI 密钥数据
DstKeyIdx 【输入】目的密钥索引，暂无意义，可以为任意值
返回
	RET_OK 成功
	ERR_DEV_NOT_OPEN 设备未打开
	ERR_INVALID_PARAM 非法参数 */
int OsPedRkiInjectKey(int KeyBlkLen,unsigned char *KeyBlk,unsigned char DstKeyIdx)
{
	return ERR_DEV_NOT_OPEN;
}



