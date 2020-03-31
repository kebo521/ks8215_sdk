
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

#include "sdk_font.h" 


#include "sdk_port.h" 
#ifdef EXT_INTERFACE
#endif
#define PRINT_WIDTH		384


typedef struct
{
	char sName[32];
	u8 RotationAngle;	//打印方向
	u8 GreyScale;		//打印灰度
	u8 Reversal;	//正反显: 0：正常    1：反显
	u8 CharSpace;	//字间距
	u8 LineSpace;	//行间距
	u8 PreFeed;;		//预走纸:1：打印不预走纸   2：打印有预走纸
	u8 Left,Right;	//左边距，右边距
	int PixelFeed;		//打印机走纸

	DEF_PRINT_DATA dGram;
}DEF_PRINT_MSG;


static DEF_PRINT_MSG *pPrintMsg=NULL;

static tSdkFont *pPrintFont=NULL;


//static DEF_PRINT_PAR *pPrintPar=NULL;

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
int OsPrnOpen(unsigned int printertype,const char* targetname)
{
	//int print_handle = open(“/dev/printer”, O_RDWR);
	if(printertype == PRN_BMP)
	{
		if(pPrintMsg)
		{
			if(pPrintMsg->dGram.pBufBit)
				free(pPrintMsg->dGram.pBufBit);
			free(pPrintMsg);
		}
		pPrintMsg=(DEF_PRINT_MSG *)malloc(sizeof(DEF_PRINT_MSG));
		memset(pPrintMsg,0x00,sizeof(DEF_PRINT_MSG));
		strcpy(pPrintMsg->sName,targetname);
	}
	#ifdef EXT_INTERFACE
	{
		u8 buff[32],*p;
		u32 recvLen;
		p=buff+4;
		*p++ = 0x08;
		*p++ = 0x01;
		API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
		recvLen = sizeof(buff);
		p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
		if(p!=NULL && p[2]==0)
		{
			return RET_OK;
		}
		return ERR_TIME_OUT;
	}
	#else
	/*
		RET_OK 成功
		ERR_DEV_NOT_EXIST 设备不存在
		ERR_INVALID_PARAM 非法参数
		ERR_DEV_BUSY 设备被占用
		ERR_BATTERY_ABSENT 电池不存在
		ERR_BATTERY_VOLTAGE_TOO_LOW
		//电池电压过低用法
		*/
	return RET_OK;
	#endif

}

//功能 关闭打印机。
void OsPrnClose(void)
{
	//open(print_handle);
	if(pPrintMsg)
	{
		if(pPrintMsg->dGram.pBufBit)
			free(pPrintMsg->dGram.pBufBit);
		free(pPrintMsg);
		pPrintMsg=NULL;
	}
	#ifdef EXT_INTERFACE
	{
		u8 buff[32],*p;
		u32 recvLen;
		p=buff+4;
		*p++ = 0x08;
		*p++ = 0x02;
		API_Uart_PackSend(EXT_INTERFACE,buff+4,p-(buff+4));
		recvLen = sizeof(buff);
		p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
		if(p)
		{
			//return p[2];
		}
	}
	#else
		
	
	#endif

}


//功能 重置打印参数,清空打印缓存。
void OsPrnReset(void)
{
	free(pPrintMsg->dGram.pBufBit);
	memset(pPrintMsg,0x00,sizeof(DEF_PRINT_MSG));
	//pPrintMsg->dGram.height=0;
}

//功能 设置虚拟打印机相关参数。
/*
参数
Width【输入】 宽度
Height【输入】 高度
*/
int OsPrnSetSize(unsigned int Width,unsigned int Height)
{
	//RET_OK 成功
	//ERR_INVALID_PARAM 非法参数
	if(pPrintMsg)
	{
		pPrintMsg->dGram.width=Width;
		pPrintMsg->dGram.height=Height;
		pPrintMsg->dGram.lineW = (Width+7)/8;
		if(pPrintMsg->dGram.pBufBit) free(pPrintMsg->dGram.pBufBit );
		pPrintMsg->dGram.pBufBit = (u8*)malloc(Height*pPrintMsg->dGram.lineW);
		memset(pPrintMsg->dGram.pBufBit,0x00,Height*pPrintMsg->dGram.lineW);
		pPrintMsg->dGram.save_X = pPrintMsg->Left;
		return RET_OK;
	}
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
	if(pPrintMsg)
	{
		if(Mode == 0)
			pPrintMsg->RotationAngle=0;
		else
			pPrintMsg->RotationAngle=90;
		return RET_OK;
	}
	return ERR_INVALID_PARAM;

}

//功能 设置打印灰度?/*?参数 Level
/*
. Level =0，保留。
. Level =1，缺省黑度，即普通打印单。
. Level =2，保留。
. Level =3，双层热敏打印。
. Level =4，双层热敏打印，比3 的黑度更高。
*/
void OsPrnSetGray(int Level)
{
	if(pPrintMsg)
	{
		pPrintMsg->GreyScale=Level;
	}
}

//功能 设置打印间距。
/*
参数
CharSpace : 字间距，单位为点数(对强制的非等宽字体无效，如各种阿拉伯字体、泰文字体)
LineSpace 行间距，单位为点数
*/
void OsPrnSetSpace(int CharSpace,int LineSpace)
{
	if(pPrintMsg)
	{
		pPrintMsg->CharSpace=CharSpace;
		pPrintMsg->LineSpace=LineSpace;
	}
}

//功能 设置字体反显属性，缺省情况下正常打印。
/* 参数 Attr: 0：正常    1：反显 */
void OsPrnSetReversal(int Attr)
{
	if(pPrintMsg)
	{
		pPrintMsg->Reversal=Attr;
	}
}

//功能 设置左右边距.
/*参数
Left【输入】 左边距，有效范围是[0，100]，默认值为0。
Right【输入】 右边距，有效范围是[0，100]，默认值为0。
*/
int OsPrnSetIndent(unsigned int Left,unsigned int Right)
{
	//RET_OK 成功
	//ERR_INVALID_PARAM 非法参数
	if(pPrintMsg)
	{
		pPrintMsg->Left=Left;
		pPrintMsg->Right=Right;
		if(pPrintMsg->dGram.save_X == 0)
			pPrintMsg->dGram.save_X = pPrintMsg->Left;
		return RET_OK;
	}
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
	if(pPrintMsg)
	{
		return pPrintMsg->dGram.save_Y;
	}
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
	if(pPrintFont)
	{
		Font_Destroy(pPrintFont);
	}
	pPrintFont=Font_Create((char*)fontname);
	if(pPrintFont == NULL)
		return ERR_FONT_NOT_EXIST;
	return RET_OK;
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
	if(pPrintMsg)
	{
		pPrintMsg->PixelFeed=Pixel;
	}
}

//功能 格式化输出字符串到打印缓冲区内。
/*参数 Str【输入】 要打印的字符串指针*/
void OsPrnPrintf(const char *Str, ...)
{
	int ret;
	char sPrintBuff[2048];
	if(pPrintFont == NULL || pPrintMsg == NULL) return;
	{
		va_list arg;
		va_start(arg, Str);
		ret=vsprintf(sPrintBuff,Str,arg);
		va_end(arg);
	}
	{
		u8 		eBit[8]={0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE};
		u8 		zBit[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
		u8 		fBit[8]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
		u8		*pBit,*pS,*pEnd;
		int 	off_y;
		FontbitMsg tFontMsg;
		u8		maxW,maxY,byteW,bitW;
	
		pS = (u8*)sPrintBuff;
		pEnd = pS+ret;
		while(pS < pEnd)
		{
			if(*pS < 0x20)
			{
				if(*pS == '\n')
				{
					pPrintMsg->dGram.save_Y += pPrintFont->h + pPrintMsg->LineSpace;	//字休高 + 行间距
					pPrintMsg->dGram.save_X = pPrintMsg->Left;	//左边距
				}
				else
				{
					pPrintMsg->dGram.save_X +=	 pPrintMsg->CharSpace+ pPrintFont->h/2; 
				}
				pS++;
			}
			else
			{
				ret=Font_GetBitMap(pPrintFont,pS,&tFontMsg);
				pS += ret;
				if(tFontMsg.pFontBit)
				{
					maxW = tFontMsg.w;
					maxY = tFontMsg.h;
					
					if(maxW > (pPrintMsg->dGram.width-pPrintMsg->dGram.save_X-pPrintMsg->Right))
						maxW = (pPrintMsg->dGram.width-pPrintMsg->dGram.save_X-pPrintMsg->Right);
					
					if(maxY > (pPrintMsg->dGram.height-pPrintMsg->dGram.save_Y))
						maxY = (pPrintMsg->dGram.height-pPrintMsg->dGram.save_Y);
		
					if(maxW > 0 && maxY > 0)
					{
						u8	byteS,bitS,b,ib;
						u8 i,maxi,is,iw;
						
						byteW = maxW >> 3;
						bitW = eBit[maxW&0x07];//(0x01<<(maxW&0x0f))-1;
						
						byteS = pPrintMsg->dGram.save_X>>3;
						bitS = pPrintMsg->dGram.save_X&0x07;
							
						off_y = pPrintMsg->dGram.save_Y;
						while(maxY--)
						{
							pBit = pPrintMsg->dGram.pBufBit +(off_y * pPrintMsg->dGram.lineW + byteS);
							//----------------------绘制线行-----------------------------
							if(bitS)
							{//-------字节不对称---------
								ib = 0;
								is = bitS;
								maxi = 8 ;
								iw = maxW;
								while(iw)
								{
									if(maxi > iw)
										maxi = iw;	
									b = tFontMsg.pFontBit[ib++];
									for(i=0;i<maxi;i++)
									{
										if((b<<i)&0x80)
											*pBit |= zBit[is];//(0x80>>is); //zBit[bitS];
										else
											*pBit &= fBit[is];//~(0x80>>is);//fBit[bitS];
										if(++is > 7) {
											pBit++;
											is=0;
										}
									}
									iw -= maxi;
								}
							}
							else //-------字节对称---------
							{
								memcpy(pBit,tFontMsg.pFontBit,byteW);
								if(bitW)
								{
									pBit[byteW] &= ~bitW;
									pBit[byteW] |= (bitW & tFontMsg.pFontBit[byteW]);
								}
							}
							//-------------下一线行-----------------
							off_y++;
							tFontMsg.pFontBit += tFontMsg.lineLen;
						}
					}
				}
				pPrintMsg->dGram.save_X +=	 pPrintMsg->CharSpace+ tFontMsg.w; //字间距+字宽
			}
		}
		if(pPrintMsg->dGram.offsetLine < (pPrintMsg->dGram.save_Y+pPrintFont->h))
			pPrintMsg->dGram.offsetLine = (pPrintMsg->dGram.save_Y+pPrintFont->h);
	}
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
	#ifdef EXT_INTERFACE
	u8 buff[32],*p,*pSend;
	u32 recvLen;
	if(pPrintMsg==NULL)
		return ERR_DEV_NOT_OPEN;
	recvLen = pPrintMsg->dGram.offsetLine * pPrintMsg->dGram.lineW;
	pSend= (u8*)malloc(recvLen+32);
	p=pSend+4;
	*p++ = 0x08;	//操作设备	0x08	
	*p++ = 0x03;	//操作命令 0x03(打印)	
	*p++ = 0x01;	//打印份数
	*p++ = 0x00;	//打印后走纸行数
	*p++ = 24;	//等待时间	HEX1	0~255秒	
	*p++ = 'b';	//‘b’表示位图文件
	*p++ = pPrintMsg->dGram.offsetLine/0x100;
	*p++ = pPrintMsg->dGram.offsetLine&0xff;
	*p++ = pPrintMsg->dGram.width/0x100;
	*p++ = pPrintMsg->dGram.width&0xff;
	memcpy(p,pPrintMsg->dGram.pBufBit,recvLen);
	p += recvLen;
	API_Uart_PackSend(EXT_INTERFACE,pSend+4,p-(pSend+4));
	free(pSend);
	
	recvLen = sizeof(buff);
	p= API_Uart_PackRecv(EXT_INTERFACE,buff,&recvLen,3000,NULL);
	if(p)
	{
		return p[2];
	}
	return ERR_TIME_OUT;
	#else
	
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
	
	#endif
	return RET_OK;
}

//功能 清空打印缓冲区
void OsPrnClrBuf(void)
{
	if(pPrintMsg->dGram.pBufBit)
		free(pPrintMsg->dGram.pBufBit);
	memset(&pPrintMsg->dGram,0x00,sizeof(pPrintMsg->dGram));

}

//功能 设置打印机是否预走纸
/*参数 cmd 【输入】
	1：打印不预走纸
	2：打印有预走纸
*/
int OsPrnSetParam(unsigned int cmd)
{
	if(pPrintMsg)
	{
		pPrintMsg->PreFeed=cmd;
	}
	return RET_OK;
}


//============额外添加用于GUI显示打印信息=============================
DEF_PRINT_DATA *OsGerPrintData(void)
{
	return &pPrintMsg->dGram;
}






