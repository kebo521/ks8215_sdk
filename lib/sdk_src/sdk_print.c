
/**
 * History:
 * ================================================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>    
#include <sys/stat.h>    
#include <sys/time.h>
#include <sys/ipc.h>
//#include <sys/shm.h> 
//#include <linux/shm.h> 
#include<sys/mman.h>

#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 
#include "sdk_print.h" 

//驱动文件:打印机的POSIX 接口





//功能 打开打印机设备，包括物理和虚拟打印机。
/*
打开打印机设备，包括物理和虚拟打印机。
参数
printertype【输入】
	打印机设备类型
	. PRN_REAL：物理打印设备；
	. PRN_BMP：虚拟打印设备，打印结果
	以BMP 格式保存在本地。
targetname【输入】
	打印设备为物理打印机时，该参数必须为NULL；
	打印设备为虚拟打印机时，指向输出到本地的
	BMP 文件的路径。若指定文件已经存在，则覆盖。
*/
int OsPrnOpen(unsigned int printertype,const char*targetname)
{
	//int print_handle = open(“/dev/printer”, O_RDWR);
/*
	RET_OK 成功
	ERR_DEV_NOT_EXIST 设备不存在
	ERR_INVALID_PARAM 非法参数
	ERR_DEV_BUSY 设备被占用
	ERR_BATTERY_ABSENT 电池不存在
	ERR_BATTERY_VOLTAGE_TOO_LOW
	//电池电压过低用法
	*/
	return ERR_DEV_NOT_EXIST;

}

//功能 关闭打印机。
void OsPrnClose(void)
{
	//open(print_handle);

}


//功能 重置打印参数,清空打印缓存。
void OsPrnReset(void)
{

}

//功能 设置虚拟打印机相关参数。
/*
参数
Width【输入】 宽度
Height【输入】 高度
*/
int OsPrnSetSize (unsigned int Width,unsigned int Height)
{
	//RET_OK 成功
	//ERR_INVALID_PARAM 非法参数
	return ERR_INVALID_PARAM;

}

//功能 设置打印方向。
/*
参数 Mode【输入】
. 0：横向打印。
. 1：纵向打印。
*/
int OsPrnSetDirection (unsigned char Mode)
{
	//RET_OK 成功
	//ERR_INVALID_PARAM 非法参数
	return ERR_INVALID_PARAM;

}

//功能 设置打印灰度�
/*�
参数 Level
. Level =0，保留。
. Level =1，缺省黑度，即普通打印单。
. Level =2，保留。
. Level =3，双层热敏打印。
. Level =4，双层热敏打印，比3 的黑度更高。
*/
void OsPrnSetGray(int Level)
{

}

//功能 设置打印间距。
/*
参数
CharSpace : 字间距，单位为点数(对强制的非等宽字体无效，如各种阿拉伯字体、泰文字体)
LineSpace 行间距，单位为点数
*/
void OsPrnSetSpace(int CharSpace,int LineSpace)
{

}

//功能 设置字体反显属性，缺省情况下正常打印。
/* 参数 Attr: 0：正常    1：反显 */
void OsPrnSetReversal(int Attr)
{

}

//功能 设置左右边距.
/*参数
Left【输入】 左边距，有效范围是[0，100]，默认值为0。
Right【输入】 右边距，有效范围是[0，100]，默认值为0。
*/
int OsPrnSetIndent (unsigned int Left,unsigned int Right)
{
	//RET_OK 成功
	//ERR_INVALID_PARAM 非法参数
	return ERR_INVALID_PARAM;
}

//功能 查询打印机当前状态，且仅适用于物理打印机。
/*返回:
RET_OK 打印机工作正常
ERR_PRN_BUSY 打印机忙
ERR_PRN_PAPEROUT 打印机缺纸
ERR_PRN_OVERHEAT 打印机过热
*/
int OsPrnCheck(void)
{
	return ERR_PRN_BUSY;
}

//功能 获取当前任务已打印的点行数。
//返回 >=0 当前已打印点行个数
int OsPrnGetDotLine(void)
{
	return 0;
}

//功能 选择打印字体。
/*参数: fontname【输入】 字体(文件)名称
返回:
RET_OK 成功
ERR_FONT_NOT_EXIST 字体不存在
ERR_INVALID_PARAM 非法参数
*/
int OsPrnSetFont(const char* fontname)
{
	return ERR_FONT_NOT_EXIST;
}

//功能 设置打印字体大小。
/*参数
SingleCodeWidth:单内码字体宽度控制(对非等宽输出字体来说，真正每个字符的宽度不一定满足此设置),选值区间为8~64
SingleCodeHeight:单内码字体高度控制,选值区间为8~64
MultiCodeWidth:多内码字体宽度控制,选值区间为12~64
MultiCodeHeight:多内码字体高度控制,选值区间为12~64
*/
void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight)
{

}

//功能 在打印缓冲区内，执行走纸若干个点行。
/*参数 Pixel
	执行走纸的点行数：
	>0：进纸
	<0：退纸
	=0：无动作
*/
void OsPrnFeed(int Pixel)
{

}

//功能 格式化输出字符串到打印缓冲区内。
/*参数 Str【输入】 要打印的字符串指针*/
void OsPrnPrintf(const char *Str, ...)
{

}

//功能 输出图形到打印缓冲区内。
/*参数 Logo【输入】需打印的logo 信息的指针，信息长度不能超过20000 个字节*/
void OsPrnPutImage(const unsigned char *Logo)
{

}
//功能 启动打印机，将缓冲区里的数据打印出来。
/*返回
	RET_OK 打印机工作正常
	ERR_PRN_BUSY 打印机忙
	ERR_PRN_PAPEROUT 打印机缺纸
	ERR_PRN_WRONG_PACKAGE 数据包格式错误
	ERR_PRN_OVERHEAT 打印机过热
	ERR_PRN_OUTOFMEMORY 打印数据过大
*/
int OsPrnStart(void)
{
	return RET_OK;
}

//功能 清空打印缓冲区
void OsPrnClrBuf(void)
{

}

//功能 设置打印机是否预走纸
/*参数 cmd 【输入】
	1：打印不预走纸
	2：打印有预走纸
*/
int OsPrnSetParam(unsigned int cmd)
{
	return RET_OK;
}



