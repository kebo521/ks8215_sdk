/**
 * File:   linux_fb.h
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  linux_framebuffer
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <unistd.h>
#include <math.h>

#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "comm_type.h"
#include "file_stu.h"
#include "sdk_font.h"

#include "sys_sdk.h"











#define FONT_CL_CALC		94    //  (0xFE - 0xA1 + 1)=94;

int Font_GbkChnAddr(RES_table *pRes,u8 hv,u8 lv)
{  
	// 0xXX7F delete from gbk
	if (lv == 0x7F) return -1;
	
	// GBK2 - 1
	if (hv >= 0xB0 && hv <= 0xD7 && lv >= 0xA1 && lv <= 0xFE)
	{
		int index = (hv - 0xB0) * FONT_CL_CALC;
		index += lv - 0xA1;
		
		if (hv == 0xD7 && lv > 0xF9) return -1;
		return  pRes->fn[2].Offset + index*(pRes->resFd.reqLen_ch);
	}
	// GBK2 - 2
	if (hv >= 0xD8 && hv <= 0xF7 && lv >= 0xA1 && lv <= 0xFE)
	{
		int index = (3755) + (hv - 0xD8) * FONT_CL_CALC;
		index += lv - 0xA1;
		return  pRes->fn[2].Offset + index*(pRes->resFd.reqLen_ch);
	}
	
	// GBK3
	if (hv >= 0x81 && hv <= 0xA0 && lv >= 0x40 && lv <= 0xFE)
	{
		int index = (hv - 0x81) * (0xFE - 0x40);
		index += lv > 0x7F ? (lv - 0x40 - 1) : (lv - 0x40);
		return  pRes->fn[3].Offset + index*(pRes->resFd.reqLen_ch);
	}
	
	// GBK4
	if (hv >= 0xAA && hv <= 0xFE && lv >= 0x40 && lv <= 0xA0)
	{
		int index = (hv - 0xAA) * (0xA0 - 0x40);
		index += lv > 0x7F ? (lv - 0x40 - 1) : (lv - 0x40);
		return  pRes->fn[4].Offset + index*(pRes->resFd.reqLen_ch);
	}
	
	// GBK1
	if (hv >= 0xA1 && hv <= 0xA9 && lv >= 0xA1 && lv <= 0xFE)
	{
		int index = (hv - 0xA1) * FONT_CL_CALC;
		index += lv - 0xA1;
		
		// not \xA1A1
		if (hv == 0xA1 && lv == 0xA1) return -1;
		else index -= 1;
		
		// not \xA2B1 - \xA2AA)
		if (hv == 0xA2 && lv > 0xAA && lv < 0xB1) return -1;
		if((hv == 0xA2 && lv >= 0xB1) || hv > 0xA2)
		{
			index -= 6;
		}
		
		// not \xA2E4
		if (hv == 0xA2 && lv == 0xE4) return -1;
		if((hv == 0xA2 && lv >= 0xE5) || hv > 0xA2)
		{
			index -= 1;
		}
		
		// not \xA2EF \xA2F0
		if (hv == 0xA2 && (lv == 0xEF || lv == 0xF0)) return -1;
		if((hv == 0xA2 &&  lv >= 0xF1)|| hv > 0xA2)
		{
			index -= 2;
		}
		
		// not \xA2FD-\xA2FE
		if (hv == 0xA2 && (lv >= 0xFD && lv <= 0xFE)) return -1;
		if (hv > 0xA2)
		{
			index -= 2;
		}
		
		// not \xA4F4-\xA4FE
		if (hv == 0xA4 && (lv >= 0xF4 && lv <= 0xFE)) return -1;
		if (hv > 0xA4)
		{
			index -= 11;
		}
		
		// not \xA5F7-\xA5FE
		if (hv == 0xA5 && (lv >= 0xF7 && lv <= 0xFE)) return -1;
		if (hv > 0xA5)
		{
			index -= 8;
		}
		
		// not \xA6B9-\xA6C0
		if (hv == 0xA6 && (lv >= 0xB9 && lv <= 0xC0)) return -1;
		if((hv == 0xA6 &&  lv >= 0xC1)|| hv > 0xA6)
		{
			index -= 8;
		}
		
		// not \xA6F6-\xA6FE
		if (hv == 0xA6 && (lv >= 0xF6 && lv <= 0xFE)) return -1;
		if (hv > 0xA6)
		{
			index -= 9;
		}
		
		// not \xA7C2-\xA7D0
		if (hv == 0xA7 && (lv >= 0xC2 && lv <= 0xD0)) return -1;
		if((hv == 0xA7 &&  lv >= 0xD1)|| hv > 0xA7)
		{
			index -= 15;
		}
		
		// not \xA7F2-\xA7FE
		if (hv == 0xA7 && (lv >= 0xF2 && lv <= 0xFE)) return -1;
		if (hv > 0xA7)
		{
			index -= 13;
		}
		
		// not \xA8C1-\xA8C4
		if (hv == 0xA8 && (lv >= 0xC1 && lv <= 0xC4)) return -1;
		if((hv == 0xA8 &&  lv >= 0xC5)|| hv > 0xA8)
		{
			index -= 4;
		}
		
		// not \xA8EA-\xA8FE
		if (hv == 0xA8 && (lv >= 0xEA && lv <= 0xFE)) return -1;
		if (hv > 0xA8)
		{
			index -= 21;
		}
		
		// not \xA9A1-\xA9A3
		if (hv == 0xA9 && (lv >= 0xA1 && lv <= 0xA3)) return -1;
		if((hv == 0xA9 &&  lv >= 0xA4)|| hv > 0xA9)
		{
			index -= 3;
		}
		// not \xA9F0-\xA9FE
		if (hv == 0xA9 && (lv >= 0xF0 && lv <= 0xFE)) return -1;
		
		return  pRes->fn[1].Offset + index*(pRes->resFd.reqLen_ch);
	}
	
	// GBK5
	if (hv >= 0xA8 && hv <= 0xA9 && lv >= 0x40 && lv <= 0xA0)
	{
		int index = (hv - 0xA8) * (0xA0 - 0x40);
		index += lv > 0x7F ? (lv - 0x40 - 1) : (lv - 0x40);
					
		// not \xA896-\xA8A0
		if (hv == 0xA8 && (lv >= 0x96 && lv <= 0xA0)) return -1;
		if (hv > 0xA8)
		{
			index -= (0xA0 - 0x96 + 1);
		}
					
		// not \xA958
		if (hv == 0xA9 && lv == 0x58) return -1;
		if((hv == 0xA9 && lv >= 0x59)|| hv > 0xA9)
		{
			index -= 1;
		}
					
		// \xA95B
		if (hv == 0xA9 && lv == 0x5B) return -1;
		if((hv == 0xA9 && lv >= 0x5C)|| hv > 0xA9)
		{
			index -= 1;
		}
					
		// not \xA95D-\xA95F
		if (hv == 0xA9 && (lv >= 0x5D && lv <= 0x5F)) return -1;
		if((hv == 0xA9 &&  lv >= 0x60)|| hv > 0xA9)
		{
			index -= 3;
		}
					
		// not \xA997-\xA9A0
		if (hv == 0xA9 && (lv >= 0x97 && lv <= 0xA0)) return -1;

		return  pRes->fn[5].Offset + index*(pRes->resFd.reqLen_ch);
	}
	return -2;
}

int Font_GetEnAddr(RES_table *pRes,u8 a)
{	
	if(a < 0x20)
		return -1;      //非英文字母
	return pRes->fn[0].Offset + ((a-0x20) * pRes->resFd.reqLen_en);
}


tSdkFont *Font_Create(char *fontfile)
{
	u8		i,uVer,itemCount,itemLen; 
	u8		HerdBuff[2048];
	int 	fd;
	u32 	fileLen;
	RES_Head* phead;
	RES_ITEM* pItem;
	tSdkFont *pFont;
//	KSP_SIGN_CONTEXT *tKspSignContext;
	
	// 读取KSP文件头
	fd=open(fontfile, O_RDONLY);
	if(fd <= 0)
	{
		LOG(LOG_ERROR,"open read %s err[%d].\r\n",fontfile,fd);
		return NULL;
	}
	if(sizeof(HerdBuff) != read(fd,&HerdBuff,sizeof(HerdBuff)))
	{
		LOG(LOG_ERROR,"fs read %s Head res err.\r\n",fontfile);
		close(fd);
		return NULL;
	}
	phead=(RES_Head*)HerdBuff;
	if(memcmp(phead->mask, "RESA", 4)) 
	{
		LOG_HEX(LOG_ERROR,"Err res mask head",&phead,sizeof(RES_Head));
		close(fd);
		return NULL;
	}
	uVer=phead->ver;
	itemCount=phead->count;
	itemLen=phead->itemlen;
	LOG(LOG_INFO,"Fontres:Ver[%d],Count[%d],Len[%d]\r\n",uVer,itemCount,itemLen);
	//计算文件长度
	fileLen=0;
	for(i=0; i<itemCount; i++) 
	{
		int itemHerdLen;
		pItem = (RES_ITEM *)&HerdBuff[sizeof(RES_Head) + i*itemLen];
		itemHerdLen= BYTE4_TO_INT(pItem->datalen);
		fileLen += DfGetBeiSu(itemHerdLen,16);
	}
	pFont=(tSdkFont*)malloc(sizeof(tSdkFont) + fileLen);
	//--------------------生成资源参数表-------------------------------------------
	for(i=0; i<itemCount; i++) 
	{
		pItem = (RES_ITEM *)&HerdBuff[sizeof(RES_Head) + i*itemLen];
		if(strstr(pItem->name,"f24_enn"))
		{
			pFont->res.fn[0].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[0].Offset= BYTE4_TO_INT(pItem->offset);
		}
		else if(strstr(pItem->name,"f24_hz1n"))
		{
			pFont->res.fn[1].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[1].Offset= BYTE4_TO_INT(pItem->offset);
		}
		else if(strstr(pItem->name,"f24_hz2n"))
		{
			pFont->res.fn[2].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[2].Offset= BYTE4_TO_INT(pItem->offset);
		}
		else if(strstr(pItem->name,"f24_hz3n"))
		{
			pFont->res.fn[3].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[3].Offset= BYTE4_TO_INT(pItem->offset);
		}
		else if(strstr(pItem->name,"f24_hz4n"))
		{
			pFont->res.fn[4].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[4].Offset= BYTE4_TO_INT(pItem->offset);
		}
		else if(strstr(pItem->name,"f24_hz5n"))
		{
			pFont->res.fn[5].ParLen= BYTE4_TO_INT(pItem->datalen);
			pFont->res.fn[5].Offset= BYTE4_TO_INT(pItem->offset);
		}
	}
	//----------24点阵字库配置-----------------------
	if(pFont->res.fn[0].ParLen==0)
	{
		LOG(LOG_INFO,"res no f24_enn ParLen err.\r\n");
		close(fd);
		return NULL;
	}
	lseek(fd,4096,SEEK_SET);	//baseOffset
	read(fd,pFont->res.pbFont,fileLen);
	close(fd);

	pFont->res.resFd.reqLen_en   = 48;
	pFont->res.resFd.reqLen_ch   = 72; 			 //删除了一些多余

	pFont->h = 24;
	pFont->Cw = 24;
	pFont->Ew = 12;
	pFont->Direction = 0;
	pFont->GetEnAddr= &Font_GetEnAddr;
	pFont->GetGbkChnAddr=&Font_GbkChnAddr;
	return pFont;
}


void Font_Destroy(tSdkFont *font)
{
	if(font)
	{
		free(font);
	}
}

//==================================================================
int Font_GetBitMap(tSdkFont *pFont,u8* pInChar,FontbitMsg *pOutMsg)
{
	int  offset;
	//pOutMsg->Direction = pFont->Direction;
	pOutMsg->h = pFont->h;
    if(*pInChar&0x80)
    {
		pOutMsg->w = pFont->Cw;
		offset=pFont->GetGbkChnAddr(&pFont->res,pInChar[0],pInChar[1]);
		if(offset > 0)
		{
			pOutMsg->lineLen = (pOutMsg->w+7)/8;
			pOutMsg->pFontBit = pFont->res.pbFont + offset;
		}
		else
		{
			pOutMsg->pFontBit = NULL;
		}
		return 2;
	}
	else
	{
		pOutMsg->w = pFont->Ew;
		offset=pFont->GetEnAddr(&pFont->res,pInChar[0]);
		if(offset > 0) 
		{
			pOutMsg->lineLen = (pOutMsg->w+7)/8;
			pOutMsg->pFontBit = pFont->res.pbFont + offset;
		}
		else
		{
			pOutMsg->pFontBit = NULL;
		}
		return 1;
	}
}



