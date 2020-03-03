
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
	u8 RotationAngle;	//´òÓ¡·½Ïò
	u8 GreyScale;		//´òÓ¡»Ò¶È
	u8 Reversal;	//Õý·´ÏÔ: 0£ºÕý³£    1£º·´ÏÔ
	u8 CharSpace;	//×Ö¼ä¾à
	u8 LineSpace;	//ÐÐ¼ä¾à
	u8 PreFeed;;		//Ô¤×ßÖ½:1£º´òÓ¡²»Ô¤×ßÖ½   2£º´òÓ¡ÓÐÔ¤×ßÖ½
	u8 Left,Right;	//×ó±ß¾à£¬ÓÒ±ß¾à
	int PixelFeed;		//´òÓ¡»ú×ßÖ½

	DEF_PRINT_DATA dGram;
}DEF_PRINT_MSG;


static DEF_PRINT_MSG *pPrintMsg=NULL;

static tSdkFont *pPrintFont=NULL;


//static DEF_PRINT_PAR *pPrintPar=NULL;

//Çý¶¯ÎÄ¼þ:´òÓ¡»úµÄPOSIX ½Ó¿Ú





//¹¦ÄÜ ´ò¿ª´òÓ¡»úÉè±¸£¬°üÀ¨ÎïÀíºÍÐéÄâ´òÓ¡»ú¡£
/*
´ò¿ª´òÓ¡»úÉè±¸£¬°üÀ¨ÎïÀíºÍÐéÄâ´òÓ¡»ú¡£
²ÎÊý
printertype¡¾ÊäÈë¡¿
	´òÓ¡»úÉè±¸ÀàÐÍ
	. PRN_REAL£ºÎïÀí´òÓ¡Éè±¸£»
	. PRN_BMP£ºÐéÄâ´òÓ¡Éè±¸£¬´òÓ¡½á¹û
	ÒÔBMP ¸ñÊ½±£´æÔÚ±¾µØ¡£
targetname¡¾ÊäÈë¡¿
	´òÓ¡Éè±¸ÎªÎïÀí´òÓ¡»úÊ±£¬¸Ã²ÎÊý±ØÐëÎªNULL£»
	´òÓ¡Éè±¸ÎªÐéÄâ´òÓ¡»úÊ±£¬Ö¸ÏòÊä³öµ½±¾µØµÄ
	BMP ÎÄ¼þµÄÂ·¾¶¡£ÈôÖ¸¶¨ÎÄ¼þÒÑ¾­´æÔÚ£¬Ôò¸²¸Ç¡£
*/
int OsPrnOpen(unsigned int printertype,const char* targetname)
{
	//int print_handle = open(¡°/dev/printer¡±, O_RDWR);
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
		RET_OK ³É¹¦
		ERR_DEV_NOT_EXIST Éè±¸²»´æÔÚ
		ERR_INVALID_PARAM ·Ç·¨²ÎÊý
		ERR_DEV_BUSY Éè±¸±»Õ¼ÓÃ
		ERR_BATTERY_ABSENT µç³Ø²»´æÔÚ
		ERR_BATTERY_VOLTAGE_TOO_LOW
		//µç³ØµçÑ¹¹ýµÍÓÃ·¨
		*/
	return RET_OK;
	#endif

}

//¹¦ÄÜ ¹Ø±Õ´òÓ¡»ú¡£
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


//¹¦ÄÜ ÖØÖÃ´òÓ¡²ÎÊý,Çå¿Õ´òÓ¡»º´æ¡£
void OsPrnReset(void)
{
	free(pPrintMsg->dGram.pBufBit);
	memset(pPrintMsg,0x00,sizeof(DEF_PRINT_MSG));
	//pPrintMsg->dGram.height=0;
}

//¹¦ÄÜ ÉèÖÃÐéÄâ´òÓ¡»úÏà¹Ø²ÎÊý¡£
/*
²ÎÊý
Width¡¾ÊäÈë¡¿ ¿í¶È
Height¡¾ÊäÈë¡¿ ¸ß¶È
*/
int OsPrnSetSize(unsigned int Width,unsigned int Height)
{
	//RET_OK ³É¹¦
	//ERR_INVALID_PARAM ·Ç·¨²ÎÊý
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

//¹¦ÄÜ ÉèÖÃ´òÓ¡·½Ïò¡£
/*
²ÎÊý Mode¡¾ÊäÈë¡¿
. 0£ººáÏò´òÓ¡¡£
. 1£º×ÝÏò´òÓ¡¡£
*/
int OsPrnSetDirection (unsigned char Mode)
{
	//RET_OK ³É¹¦
	//ERR_INVALID_PARAM ·Ç·¨²ÎÊý
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

//¹¦ÄÜ ÉèÖÃ´òÓ¡»Ò¶È¡
/*£
²ÎÊý Level
. Level =0£¬±£Áô¡£
. Level =1£¬È±Ê¡ºÚ¶È£¬¼´ÆÕÍ¨´òÓ¡µ¥¡£
. Level =2£¬±£Áô¡£
. Level =3£¬Ë«²ãÈÈÃô´òÓ¡¡£
. Level =4£¬Ë«²ãÈÈÃô´òÓ¡£¬±È3 µÄºÚ¶È¸ü¸ß¡£
*/
void OsPrnSetGray(int Level)
{
	if(pPrintMsg)
	{
		pPrintMsg->GreyScale=Level;
	}
}

//¹¦ÄÜ ÉèÖÃ´òÓ¡¼ä¾à¡£
/*
²ÎÊý
CharSpace : ×Ö¼ä¾à£¬µ¥Î»ÎªµãÊý(¶ÔÇ¿ÖÆµÄ·ÇµÈ¿í×ÖÌåÎÞÐ§£¬Èç¸÷ÖÖ°¢À­²®×ÖÌå¡¢Ì©ÎÄ×ÖÌå)
LineSpace ÐÐ¼ä¾à£¬µ¥Î»ÎªµãÊý
*/
void OsPrnSetSpace(int CharSpace,int LineSpace)
{
	if(pPrintMsg)
	{
		pPrintMsg->CharSpace=CharSpace;
		pPrintMsg->LineSpace=LineSpace;
	}
}

//¹¦ÄÜ ÉèÖÃ×ÖÌå·´ÏÔÊôÐÔ£¬È±Ê¡Çé¿öÏÂÕý³£´òÓ¡¡£
/* ²ÎÊý Attr: 0£ºÕý³£    1£º·´ÏÔ */
void OsPrnSetReversal(int Attr)
{
	if(pPrintMsg)
	{
		pPrintMsg->Reversal=Attr;
	}
}

//¹¦ÄÜ ÉèÖÃ×óÓÒ±ß¾à.
/*²ÎÊý
Left¡¾ÊäÈë¡¿ ×ó±ß¾à£¬ÓÐÐ§·¶Î§ÊÇ[0£¬100]£¬Ä¬ÈÏÖµÎª0¡£
Right¡¾ÊäÈë¡¿ ÓÒ±ß¾à£¬ÓÐÐ§·¶Î§ÊÇ[0£¬100]£¬Ä¬ÈÏÖµÎª0¡£
*/
int OsPrnSetIndent(unsigned int Left,unsigned int Right)
{
	//RET_OK ³É¹¦
	//ERR_INVALID_PARAM ·Ç·¨²ÎÊý
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

//¹¦ÄÜ ²éÑ¯´òÓ¡»úµ±Ç°×´Ì¬£¬ÇÒ½öÊÊÓÃÓÚÎïÀí´òÓ¡»ú¡£
/*·µ»Ø:
RET_OK ´òÓ¡»ú¹¤×÷Õý³£
ERR_PRN_BUSY ´òÓ¡»úÃ¦
ERR_PRN_PAPEROUT ´òÓ¡»úÈ±Ö½
ERR_PRN_OVERHEAT ´òÓ¡»ú¹ýÈÈ
*/
int OsPrnCheck(void)
{
	
	return ERR_PRN_BUSY;
}

//¹¦ÄÜ »ñÈ¡µ±Ç°ÈÎÎñÒÑ´òÓ¡µÄµãÐÐÊý¡£
//·µ»Ø >=0 µ±Ç°ÒÑ´òÓ¡µãÐÐ¸öÊý
int OsPrnGetDotLine(void)
{
	if(pPrintMsg)
	{
		return pPrintMsg->dGram.save_Y;
	}
	return 0;
}

//¹¦ÄÜ Ñ¡Ôñ´òÓ¡×ÖÌå¡£
/*²ÎÊý: fontname¡¾ÊäÈë¡¿ ×ÖÌå(ÎÄ¼þ)Ãû³Æ
·µ»Ø:
RET_OK ³É¹¦
ERR_FONT_NOT_EXIST ×ÖÌå²»´æÔÚ
ERR_INVALID_PARAM ·Ç·¨²ÎÊý
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

//¹¦ÄÜ ÉèÖÃ´òÓ¡×ÖÌå´óÐ¡¡£
/*²ÎÊý
SingleCodeWidth:µ¥ÄÚÂë×ÖÌå¿í¶È¿ØÖÆ(¶Ô·ÇµÈ¿íÊä³ö×ÖÌåÀ´Ëµ£¬ÕæÕýÃ¿¸ö×Ö·ûµÄ¿í¶È²»Ò»¶¨Âú×ã´ËÉèÖÃ),Ñ¡ÖµÇø¼äÎª8~64
SingleCodeHeight:µ¥ÄÚÂë×ÖÌå¸ß¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª8~64
MultiCodeWidth:¶àÄÚÂë×ÖÌå¿í¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª12~64
MultiCodeHeight:¶àÄÚÂë×ÖÌå¸ß¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª12~64
*/
void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight)
{

}

//¹¦ÄÜ ÔÚ´òÓ¡»º³åÇøÄÚ£¬Ö´ÐÐ×ßÖ½Èô¸É¸öµãÐÐ¡£
/*²ÎÊý Pixel
	Ö´ÐÐ×ßÖ½µÄµãÐÐÊý£º
	>0£º½øÖ½
	<0£ºÍËÖ½
	=0£ºÎÞ¶¯×÷
*/
void OsPrnFeed(int Pixel)
{
	if(pPrintMsg)
	{
		pPrintMsg->PixelFeed=Pixel;
	}
}

//¹¦ÄÜ ¸ñÊ½»¯Êä³ö×Ö·û´®µ½´òÓ¡»º³åÇøÄÚ¡£
/*²ÎÊý Str¡¾ÊäÈë¡¿ Òª´òÓ¡µÄ×Ö·û´®Ö¸Õë*/
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
					pPrintMsg->dGram.save_Y += pPrintFont->h + pPrintMsg->LineSpace;	//×ÖÐÝ¸ß + ÐÐ¼ä¾à
					pPrintMsg->dGram.save_X = pPrintMsg->Left;	//×ó±ß¾à
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
							//----------------------»æÖÆÏßÐÐ-----------------------------
							if(bitS)
							{//-------×Ö½Ú²»¶Ô³Æ---------
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
							else //-------×Ö½Ú¶Ô³Æ---------
							{
								memcpy(pBit,tFontMsg.pFontBit,byteW);
								if(bitW)
								{
									pBit[byteW] &= ~bitW;
									pBit[byteW] |= (bitW & tFontMsg.pFontBit[byteW]);
								}
							}
							//-------------ÏÂÒ»ÏßÐÐ-----------------
							off_y++;
							tFontMsg.pFontBit += tFontMsg.lineLen;
						}
					}
				}
				pPrintMsg->dGram.save_X +=	 pPrintMsg->CharSpace+ tFontMsg.w; //×Ö¼ä¾à+×Ö¿í
			}
		}
		if(pPrintMsg->dGram.offsetLine < (pPrintMsg->dGram.save_Y+pPrintFont->h))
			pPrintMsg->dGram.offsetLine = (pPrintMsg->dGram.save_Y+pPrintFont->h);
	}
}

//¹¦ÄÜ Êä³öÍ¼ÐÎµ½´òÓ¡»º³åÇøÄÚ¡£
/*²ÎÊý Logo¡¾ÊäÈë¡¿Ðè´òÓ¡µÄlogo ÐÅÏ¢µÄÖ¸Õë£¬ÐÅÏ¢³¤¶È²»ÄÜ³¬¹ý20000 ¸ö×Ö½Ú*/
void OsPrnPutImage(const unsigned char *Logo)
{

}


//¹¦ÄÜ Æô¶¯´òÓ¡»ú£¬½«»º³åÇøÀïµÄÊý¾Ý´òÓ¡³öÀ´¡£
/*·µ»Ø
	RET_OK ´òÓ¡»ú¹¤×÷Õý³£
	ERR_PRN_BUSY ´òÓ¡»úÃ¦
	ERR_PRN_PAPEROUT ´òÓ¡»úÈ±Ö½
	ERR_PRN_WRONG_PACKAGE Êý¾Ý°ü¸ñÊ½´íÎó
	ERR_PRN_OVERHEAT ´òÓ¡»ú¹ýÈÈ
	ERR_PRN_OUTOFMEMORY ´òÓ¡Êý¾Ý¹ý´ó
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
	*p++ = 0x08;	//²Ù×÷Éè±¸	0x08	
	*p++ = 0x03;	//²Ù×÷ÃüÁî 0x03(´òÓ¡)	
	*p++ = 0x01;	//´òÓ¡·ÝÊý
	*p++ = 0x00;	//´òÓ¡ºó×ßÖ½ÐÐÊý
	*p++ = 24;	//µÈ´ýÊ±¼ä	HEX1	0~255Ãë	
	*p++ = 'b';	//¡®b¡¯±íÊ¾Î»Í¼ÎÄ¼þ
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
		RET_OK ³É¹¦
		ERR_DEV_NOT_EXIST Éè±¸²»´æÔÚ
		ERR_INVALID_PARAM ·Ç·¨²ÎÊý
		ERR_DEV_BUSY Éè±¸±»Õ¼ÓÃ
		ERR_BATTERY_ABSENT µç³Ø²»´æÔÚ
		ERR_BATTERY_VOLTAGE_TOO_LOW
		//µç³ØµçÑ¹¹ýµÍÓÃ·¨
		*/
		return ERR_DEV_NOT_EXIST;
	
	#endif
	return RET_OK;
}

//¹¦ÄÜ Çå¿Õ´òÓ¡»º³åÇø
void OsPrnClrBuf(void)
{
	if(pPrintMsg->dGram.pBufBit)
		free(pPrintMsg->dGram.pBufBit);
	memset(&pPrintMsg->dGram,0x00,sizeof(pPrintMsg->dGram));

}

//¹¦ÄÜ ÉèÖÃ´òÓ¡»úÊÇ·ñÔ¤×ßÖ½
/*²ÎÊý cmd ¡¾ÊäÈë¡¿
	1£º´òÓ¡²»Ô¤×ßÖ½
	2£º´òÓ¡ÓÐÔ¤×ßÖ½
*/
int OsPrnSetParam(unsigned int cmd)
{
	if(pPrintMsg)
	{
		pPrintMsg->PreFeed=cmd;
	}
	return RET_OK;
}


//============¶îÍâÌí¼ÓÓÃÓÚGUIÏÔÊ¾´òÓ¡ÐÅÏ¢=============================
DEF_PRINT_DATA *OsGerPrintData(void)
{
	return &pPrintMsg->dGram;
}






