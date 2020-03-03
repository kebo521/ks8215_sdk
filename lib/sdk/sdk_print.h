#ifndef _SDK_PRINTF_
#define _SDK_PRINTF_

#define ERR_PRN_BUSY				-3701 //打印机忙
#define ERR_PRN_PAPEROUT			-3702 //打印机缺纸
#define ERR_PRN_WRONG_PACKAGE	-3703 //数据包格式错误
#define ERR_PRN_OVERHEAT			-3704 //打印机过热
#define ERR_PRN_OUTOFMEMORY		-3705 //要打印数据过大,超出缓冲区长度
#define ERR_PRN_OVERVOLTAGE		-3706 //电压过高

enum PRINT_TYPE
{
	PRN_REAL,	//物理打印设备；
	PRN_BMP,	//虚拟打印设备，打印结果
};

//===================虚拟打印机数据===========================
typedef struct
{
	u16 save_X,save_Y;	//存入位置
	u16 height,width;
	u16 lineW,offsetLine;
	u8* pBufBit;		//[n][48]
}DEF_PRINT_DATA;


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
extern int OsPrnOpen(unsigned int printertype,const char* targetname);

//功能 关闭打印机。
extern void OsPrnClose(void);


//功能 重置打印参数,清空打印缓存。
extern void OsPrnReset(void);

//功能 设置虚拟打印机相关参数。
/*
参数
Width【输入】 宽度
Height【输入】 高度
*/
extern int OsPrnSetSize(unsigned int Width,unsigned int Height);

//功能 设置打印方向。
/*
参数 Mode【输入】
. 0：横向打印。
. 1：纵向打印。
*/
extern int OsPrnSetDirection (unsigned char Mode);

//功能 设置打印灰度?
/*?
参数 Level
. Level =0，保留。
. Level =1，缺省黑度，即普通打印单。
. Level =2，保留。
. Level =3，双层热敏打印。
. Level =4，双层热敏打印，比3 的黑度更高。
*/
extern void OsPrnSetGray(int Level);

//功能 设置打印间距。
/*
参数
CharSpace : 字间距，单位为点数(对强制的非等宽字体无效，如各种阿拉伯字体、泰文字体)
LineSpace 行间距，单位为点数
*/
extern void OsPrnSetSpace(int CharSpace,int LineSpace);
;
//功能 设置字体反显属性，缺省情况下正常打印。
/* 参数 Attr: 0：正常    1：反显 */
extern void OsPrnSetReversal(int Attr);

//功能 设置左右边距.
/*参数
Left【输入】 左边距，有效范围是[0，100]，默认值为0。
Right【输入】 右边距，有效范围是[0，100]，默认值为0。
*/
extern int OsPrnSetIndent (unsigned int Left,unsigned int Right);

//功能 查询打印机当前状态，且仅适用于物理打印机。
/*返回:
RET_OK 打印机工作正常
ERR_PRN_BUSY 打印机忙
ERR_PRN_PAPEROUT 打印机缺纸
ERR_PRN_OVERHEAT 打印机过热
*/
extern int OsPrnCheck(void);

//功能 获取当前任务已打印的点行数。
//返回 >=0 当前已打印点行个数
extern int OsPrnGetDotLine(void);

//功能 选择打印字体。
/*参数: fontname【输入】 字体(文件)名称
返回:
RET_OK 成功
ERR_FONT_NOT_EXIST 字体不存在
ERR_INVALID_PARAM 非法参数
*/
extern int OsPrnSetFont(const char* fontname);

//功能 设置打印字体大小。
/*参数
SingleCodeWidth:单内码字体宽度控制(对非等宽输出字体来说，真正每个字符的宽度不一定满足此设置),选值区间为8~64
SingleCodeHeight:单内码字体高度控制,选值区间为8~64
MultiCodeWidth:多内码字体宽度控制,选值区间为12~64
MultiCodeHeight:多内码字体高度控制,选值区间为12~64
*/
extern void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight);

//功能 在打印缓冲区内，执行走纸若干个点行。
/*参数 Pixel
	执行走纸的点行数：
	>0：进纸
	<0：退纸
	=0：无动作
*/
extern void OsPrnFeed(int Pixel);

//功能 格式化输出字符串到打印缓冲区内。
/*参数 Str【输入】 要打印的字符串指针*/
extern void OsPrnPrintf(const char *Str, ...);

//功能 输出图形到打印缓冲区内。
/*参数 Logo【输入】需打印的logo 信息的指针，信息长度不能超过20000 个字节*/
extern void OsPrnPutImage(const unsigned char *Logo);

//功能 启动打印机，将缓冲区里的数据打印出来。
/*返回
	RET_OK 打印机工作正常
	ERR_PRN_BUSY 打印机忙
	ERR_PRN_PAPEROUT 打印机缺纸
	ERR_PRN_WRONG_PACKAGE 数据包格式错误
	ERR_PRN_OVERHEAT 打印机过热
	ERR_PRN_OUTOFMEMORY 打印数据过大
*/
extern int OsPrnStart(void);

//功能 清空打印缓冲区
extern void OsPrnClrBuf(void);

//功能 设置打印机是否预走纸
/*参数 cmd 【输入】
	1：打印不预走纸
	2：打印有预走纸
*/
extern int OsPrnSetParam(unsigned int cmd);




//============额外添加用于GUI显示打印信息=============================
extern DEF_PRINT_DATA *OsGerPrintData(void);


#endif
