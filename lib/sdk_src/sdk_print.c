
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
	u8 RotationAngle;	//��ӡ����
	u8 GreyScale;		//��ӡ�Ҷ�
	u8 Reversal;	//������: 0������    1������
	u8 CharSpace;	//�ּ��
	u8 LineSpace;	//�м��
	u8 PreFeed;;		//Ԥ��ֽ:1����ӡ��Ԥ��ֽ   2����ӡ��Ԥ��ֽ
	u8 Left,Right;	//��߾࣬�ұ߾�
	int PixelFeed;		//��ӡ����ֽ

	DEF_PRINT_DATA dGram;
}DEF_PRINT_MSG;


static DEF_PRINT_MSG *pPrintMsg=NULL;

static tSdkFont *pPrintFont=NULL;


//static DEF_PRINT_PAR *pPrintPar=NULL;

//�����ļ�:��ӡ����POSIX �ӿ�





//���� �򿪴�ӡ���豸����������������ӡ����
/*
�򿪴�ӡ���豸����������������ӡ����
����
printertype�����롿
	��ӡ���豸����
	. PRN_REAL�������ӡ�豸��
	. PRN_BMP�������ӡ�豸����ӡ���
	��BMP ��ʽ�����ڱ��ء�
targetname�����롿
	��ӡ�豸Ϊ�����ӡ��ʱ���ò�������ΪNULL��
	��ӡ�豸Ϊ�����ӡ��ʱ��ָ����������ص�
	BMP �ļ���·������ָ���ļ��Ѿ����ڣ��򸲸ǡ�
*/
int OsPrnOpen(unsigned int printertype,const char* targetname)
{
	//int print_handle = open(��/dev/printer��, O_RDWR);
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
		RET_OK �ɹ�
		ERR_DEV_NOT_EXIST �豸������
		ERR_INVALID_PARAM �Ƿ�����
		ERR_DEV_BUSY �豸��ռ��
		ERR_BATTERY_ABSENT ��ز�����
		ERR_BATTERY_VOLTAGE_TOO_LOW
		//��ص�ѹ�����÷�
		*/
	return RET_OK;
	#endif

}

//���� �رմ�ӡ����
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


//���� ���ô�ӡ����,��մ�ӡ���档
void OsPrnReset(void)
{
	free(pPrintMsg->dGram.pBufBit);
	memset(pPrintMsg,0x00,sizeof(DEF_PRINT_MSG));
	//pPrintMsg->dGram.height=0;
}

//���� ���������ӡ����ز�����
/*
����
Width�����롿 ���
Height�����롿 �߶�
*/
int OsPrnSetSize(unsigned int Width,unsigned int Height)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
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

//���� ���ô�ӡ����
/*
���� Mode�����롿
. 0�������ӡ��
. 1�������ӡ��
*/
int OsPrnSetDirection (unsigned char Mode)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
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

//���� ���ô�ӡ�Ҷ�?/*?���� Level
/*
. Level =0��������
. Level =1��ȱʡ�ڶȣ�����ͨ��ӡ����
. Level =2��������
. Level =3��˫��������ӡ��
. Level =4��˫��������ӡ����3 �ĺڶȸ��ߡ�
*/
void OsPrnSetGray(int Level)
{
	if(pPrintMsg)
	{
		pPrintMsg->GreyScale=Level;
	}
}

//���� ���ô�ӡ��ࡣ
/*
����
CharSpace : �ּ�࣬��λΪ����(��ǿ�Ƶķǵȿ�������Ч������ְ��������塢̩������)
LineSpace �м�࣬��λΪ����
*/
void OsPrnSetSpace(int CharSpace,int LineSpace)
{
	if(pPrintMsg)
	{
		pPrintMsg->CharSpace=CharSpace;
		pPrintMsg->LineSpace=LineSpace;
	}
}

//���� �������巴�����ԣ�ȱʡ�����������ӡ��
/* ���� Attr: 0������    1������ */
void OsPrnSetReversal(int Attr)
{
	if(pPrintMsg)
	{
		pPrintMsg->Reversal=Attr;
	}
}

//���� �������ұ߾�.
/*����
Left�����롿 ��߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
Right�����롿 �ұ߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
*/
int OsPrnSetIndent(unsigned int Left,unsigned int Right)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
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

//���� ��ѯ��ӡ����ǰ״̬���ҽ������������ӡ����
/*����:
RET_OK ��ӡ����������
ERR_PRN_BUSY ��ӡ��æ
ERR_PRN_PAPEROUT ��ӡ��ȱֽ
ERR_PRN_OVERHEAT ��ӡ������
*/
int OsPrnCheck(void)
{
	
	return ERR_PRN_BUSY;
}

//���� ��ȡ��ǰ�����Ѵ�ӡ�ĵ�������
//���� >=0 ��ǰ�Ѵ�ӡ���и���
int OsPrnGetDotLine(void)
{
	if(pPrintMsg)
	{
		return pPrintMsg->dGram.save_Y;
	}
	return 0;
}

//���� ѡ���ӡ���塣
/*����: fontname�����롿 ����(�ļ�)����
����:
RET_OK �ɹ�
ERR_FONT_NOT_EXIST ���岻����
ERR_INVALID_PARAM �Ƿ�����
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

//���� ���ô�ӡ�����С��
/*����
SingleCodeWidth:�����������ȿ���(�Էǵȿ����������˵������ÿ���ַ��Ŀ�Ȳ�һ�����������),ѡֵ����Ϊ8~64
SingleCodeHeight:����������߶ȿ���,ѡֵ����Ϊ8~64
MultiCodeWidth:�����������ȿ���,ѡֵ����Ϊ12~64
MultiCodeHeight:����������߶ȿ���,ѡֵ����Ϊ12~64
*/
void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight)
{

}

//���� �ڴ�ӡ�������ڣ�ִ����ֽ���ɸ����С�
/*���� Pixel
	ִ����ֽ�ĵ�������
	>0����ֽ
	<0����ֽ
	=0���޶���
*/
void OsPrnFeed(int Pixel)
{
	if(pPrintMsg)
	{
		pPrintMsg->PixelFeed=Pixel;
	}
}

//���� ��ʽ������ַ�������ӡ�������ڡ�
/*���� Str�����롿 Ҫ��ӡ���ַ���ָ��*/
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
					pPrintMsg->dGram.save_Y += pPrintFont->h + pPrintMsg->LineSpace;	//���ݸ� + �м��
					pPrintMsg->dGram.save_X = pPrintMsg->Left;	//��߾�
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
							//----------------------��������-----------------------------
							if(bitS)
							{//-------�ֽڲ��Գ�---------
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
							else //-------�ֽڶԳ�---------
							{
								memcpy(pBit,tFontMsg.pFontBit,byteW);
								if(bitW)
								{
									pBit[byteW] &= ~bitW;
									pBit[byteW] |= (bitW & tFontMsg.pFontBit[byteW]);
								}
							}
							//-------------��һ����-----------------
							off_y++;
							tFontMsg.pFontBit += tFontMsg.lineLen;
						}
					}
				}
				pPrintMsg->dGram.save_X +=	 pPrintMsg->CharSpace+ tFontMsg.w; //�ּ��+�ֿ�
			}
		}
		if(pPrintMsg->dGram.offsetLine < (pPrintMsg->dGram.save_Y+pPrintFont->h))
			pPrintMsg->dGram.offsetLine = (pPrintMsg->dGram.save_Y+pPrintFont->h);
	}
}

//���� ���ͼ�ε���ӡ�������ڡ�
/*���� Logo�����롿���ӡ��logo ��Ϣ��ָ�룬��Ϣ���Ȳ��ܳ���20000 ���ֽ�*/
void OsPrnPutImage(const unsigned char *Logo)
{

}


//���� ������ӡ������������������ݴ�ӡ������
/*����
	RET_OK ��ӡ����������
	ERR_PRN_BUSY ��ӡ��æ
	ERR_PRN_PAPEROUT ��ӡ��ȱֽ
	ERR_PRN_WRONG_PACKAGE ���ݰ���ʽ����
	ERR_PRN_OVERHEAT ��ӡ������
	ERR_PRN_OUTOFMEMORY ��ӡ���ݹ���
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
	*p++ = 0x08;	//�����豸	0x08	
	*p++ = 0x03;	//�������� 0x03(��ӡ)	
	*p++ = 0x01;	//��ӡ����
	*p++ = 0x00;	//��ӡ����ֽ����
	*p++ = 24;	//�ȴ�ʱ��	HEX1	0~255��	
	*p++ = 'b';	//��b����ʾλͼ�ļ�
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
		RET_OK �ɹ�
		ERR_DEV_NOT_EXIST �豸������
		ERR_INVALID_PARAM �Ƿ�����
		ERR_DEV_BUSY �豸��ռ��
		ERR_BATTERY_ABSENT ��ز�����
		ERR_BATTERY_VOLTAGE_TOO_LOW
		//��ص�ѹ�����÷�
		*/
		return ERR_DEV_NOT_EXIST;
	
	#endif
	return RET_OK;
}

//���� ��մ�ӡ������
void OsPrnClrBuf(void)
{
	if(pPrintMsg->dGram.pBufBit)
		free(pPrintMsg->dGram.pBufBit);
	memset(&pPrintMsg->dGram,0x00,sizeof(pPrintMsg->dGram));

}

//���� ���ô�ӡ���Ƿ�Ԥ��ֽ
/*���� cmd �����롿
	1����ӡ��Ԥ��ֽ
	2����ӡ��Ԥ��ֽ
*/
int OsPrnSetParam(unsigned int cmd)
{
	if(pPrintMsg)
	{
		pPrintMsg->PreFeed=cmd;
	}
	return RET_OK;
}


//============�����������GUI��ʾ��ӡ��Ϣ=============================
DEF_PRINT_DATA *OsGerPrintData(void)
{
	return &pPrintMsg->dGram;
}






