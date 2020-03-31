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

#include "xui_ui.h"
#include "xui_fb.h"
#include "xui_font.h"
#include "xui_gui.h"
#include "sdk/sys_sdk.h"

#include "sdk/sdk_font.h"

//==========字义系统字库=======================
#define SYS_FUNT_12EN
#define SYS_FUNT_16EN
//#define SYS_FUNT_24EN

#include "fontBitEn.h"

static A_RGB uiEnForeColor=0x00FFFFFF,uiEnBackColor=0xFF000000;

void UI_SetSysEnColor(A_RGB ForeColor,A_RGB BackColor)
{
	uiEnForeColor= ForeColor;
	uiEnBackColor= BackColor;
}

void UI_DisplaySysEn(XuiWindow *pWindow,int x,int y,int type,char*pMsgEn) 
{
	A_RGB *pbgra;
	u8*	pbit;
	u8	i,j,jn,backflag;	//readLen,
	u8	cH,cW,cZ;
	#ifdef SYS_FUNT_24EN
	u16 jb;
	#else
	u8 jb;
	#endif
	u16 width,height;
	A_RGB* pWidget;

	#ifdef SYS_FUNT_12EN
	if(type == TEXT_12)
	{
		cH = 12; cW = 6; cZ = 12;
		pbit = funt6x12EnBuff;
	}
	else 
	#endif
	#ifdef SYS_FUNT_16EN
	if(type == TEXT_16)
	{
		cH = 16; cW = 8; cZ = 16;
		pbit = funt6x16EnBuff;
	}
	else 
	#endif
	#ifdef SYS_FUNT_24EN
	if(type == TEXT_24)
	{
		cH = 24; cW = 12; cZ = 48;
		pbit = funt12x24EnBuff;
	}
	else 
	#endif
			return;
	//---------------------------------------------------------------
	pWidget	= pWindow->widget;
	width	= pWindow->width;
	height	= pWindow->height;
	if(uiEnBackColor&0xFF000000)
		backflag = 1;
	else
		backflag = 0;
	while((jn=(u8)*pMsgEn++) != '\0')
	{
		if(jn & 0x80)
		{//-----中文-------

		}
		else if(jn >= 0x20)
		{
			if((x+cW) > width) 
			{//--Automatic line feed display---
				x = 0;
				y += cH;
			}
			if(y >= height) return ;
			if(cH > (height-y)) cH=(height-y);
			
			#ifdef SYS_FUNT_24EN
			if(cW > 8) {
				for(i = 0; i < cH; i++) {	 
					pbgra = &pWidget[(y+i)*width + x];
					jb = pbit[(jn-0x20)*cZ + i*2]*256 + pbit[(jn-0x20)*cZ + i*2+1];
					for(j = 0; j < cW; j++) {
						if(jb & (0x8000>>j))
							*pbgra = uiEnForeColor;
						else if(backflag)
							*pbgra = uiEnBackColor;
						pbgra++;
					}
				}
			}
			else
			#endif
			for(i = 0; i < cH; i++) {
				pbgra = &pWidget[(y+i)*width + x];
				jb = pbit[(jn-0x20)*cZ + i];
				for(j = 0; j < cW; j++) {
					if(jb & (0x80>>j))
						*pbgra = uiEnForeColor;
					else if(backflag)
						*pbgra = uiEnBackColor;
					pbgra++;
				}
			}
		}
		x += cW;
	}
}

//==================显示英文，不需要字库支持===================================
void API_ShowLineEn(u8 Line,char *pMsgEn,int timeoutms) 
{
	if(gUiDataAll.tHardWindow.widget == NULL) return;
	UI_DisplaySysEn(&gUiDataAll.tHardWindow,0,Line*TEXT_12,TEXT_12,pMsgEn);
	if(timeoutms) OsSleep(timeoutms);
}


DisRES_table resDisTable={0};

int InitExtResLib(char *pfile)
{
	u8  	i,uVer,itemCount,itemLen; 
	u8		HerdBuff[2048];
	int 	fd;
	u32 	fileLen,baseOffset;
	RES_Head* phead;
	RES_ITEM* pItem;
//	KSP_SIGN_CONTEXT *tKspSignContext;
	
	// 读取KSP文件头
	fd=open(pfile, O_RDONLY);
	if(fd <= 0)
	{
		LOG(LOG_ERROR,"open read %s err[%d].\r\n",pfile,fd);
	//	UnInitFileSystem();
		API_ShowLineEn(1,"open ks.res err Necessary download of ks.res",10*1000);
		return -1;
	}
	if(sizeof(HerdBuff) != read(fd,&HerdBuff,sizeof(HerdBuff)))
	{
		LOG(LOG_ERROR,"fs read %s Head res err.\r\n",pfile);
		API_ShowLineEn(1,"read ks.res err Necessary download of ks.res",10*1000);
		close(fd);
		return -2;
	}
	phead=(RES_Head*)HerdBuff;
	if(memcmp(phead->mask, "RESA", 4)) 
	{
		//TRACE_HEX("Err res mask head",&phead,sizeof(RES_Head));
		API_ShowLineEn(1,"ks.res mask err Necessary download of ks.res",10*1000);
		close(fd);
		return -3;
	}
	uVer=phead->ver;
	itemCount=phead->count;
	itemLen=phead->itemlen;
	LOG(LOG_INFO,"res:Ver[%d],itemCount[%d],itemLen[%d]\r\n",uVer,itemCount,itemLen);
	//计算文件长度
	fileLen=0;
	for(i=0; i<itemCount; i++) 
	{
		int itemHerdLen;
		pItem = (RES_ITEM *)&HerdBuff[sizeof(RES_Head) + i*itemLen];
		itemHerdLen= BYTE4_TO_INT(pItem->datalen);
		fileLen += DfGetBeiSu(itemHerdLen,16);
	}
	/*
	LOG(LOG_INFO,"ks.res:data fileLen[%u]\r\n",fileLen);
	// 签名块验证
	{
		u8		signout[256];
		u32 	offset;
		offset = 4096;
		fileLen += offset;
		lseek(fd,offset,SEEK_SET);
		tKspSignContext =(KSP_SIGN_CONTEXT *)signout;
		if(APP_rsa_decryptSign(phead->auth, signout) == 0) 
		{
			int ret;
			int MaxSet,CruSet;
			u8 shaResult[32];
			u8	*pBuffData;
			mbedtls_md_context_t ctx;
			TRACE_HEX("signout",signout,sizeof(signout));
			//-------------------SHA256验证--------------------------
			MaxSet = 32*1024;
			pBuffData=(u8*)malloc(MaxSet);
			//app_InterFace->pTls->hash->md_starts(&ctx,MBEDTLS_MD_SHA256);
			api_tls_InterFace.hash->md_starts(&ctx,MBEDTLS_MD_SHA256);
			while(offset < fileLen) 
			{
				CruSet = fileLen - offset;
				if(CruSet>MaxSet) CruSet=MaxSet;
				ret=read(fd,pBuffData,CruSet);//offset
				if(ret < CruSet)
				{
					LOG(LOG_ERROR,"API fread Res CruSet:%d ret:%d\r\n",CruSet,ret);
					break;
				}
				api_tls_InterFace.hash->md_update(&ctx,pBuffData,ret);
				offset += ret;
			}
			api_tls_InterFace.hash->md_finish(&ctx,shaResult,NULL);
			free(pBuffData);
			if(offset == fileLen)
			{
				if (API_memcmp(shaResult, tKspSignContext->hashResult, 32) != 0) 
				{
					TRACE_HEX("sha256-O", tKspSignContext->hashResult, 32);
					TRACE_HEX("sha256-C", shaResult, 32);
					//API_fclose(fd);
					API_ShowLineEn(2,"error check ks.res sign",10*1000);
					//return -5;
				}
			}
		}
	
		if(offset < fileLen)
		{
			LOG(LOG_ERROR,"res signinfo check err.\r\n");
			//API_fclose(fd);
			API_ShowLineEn(2,"error check ks.res signlen",10*1000);
			//return -4;
		}	
	}
	//*/
	baseOffset = 4096;
	//--------------------生成资源参数表-------------------------------------------
	for(i=0; i<itemCount; i++) 
	{
		pItem = (RES_ITEM *)&HerdBuff[sizeof(RES_Head) + i*itemLen];
		if(strstr(pItem->name,"gbk"))
		{
			resDisTable.gbk.ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.gbk.Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"gbk-> Offset[%d]ParLen[%d]\r\n",resDisTable.gbk.Offset,resDisTable.gbk.ParLen);
		}
		else if(strstr(pItem->name,"ucode"))
		{
			resDisTable.ucode.ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.ucode.Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"ucode-> Offset[%d]ParLen[%d]\r\n",resDisTable.ucode.Offset,resDisTable.ucode.ParLen);
		}
		else if(strstr(pItem->name,"f24_enn"))
		{
			resDisTable.fn[0].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[0].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[0]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[0].Offset,resDisTable.fn[0].ParLen);
		}
		else if(strstr(pItem->name,"f24_hz1n"))
		{
			resDisTable.fn[1].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[1].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[1]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[1].Offset,resDisTable.fn[1].ParLen);
		}
		else if(strstr(pItem->name,"f24_hz2n"))
		{
			resDisTable.fn[2].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[2].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[2]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[2].Offset,resDisTable.fn[2].ParLen);
		}
		else if(strstr(pItem->name,"f24_hz3n"))
		{
			resDisTable.fn[3].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[3].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[3]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[3].Offset,resDisTable.fn[3].ParLen);
		}
		else if(strstr(pItem->name,"f24_hz4n"))
		{
			resDisTable.fn[4].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[4].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[4]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[4].Offset,resDisTable.fn[4].ParLen);
		}
		else if(strstr(pItem->name,"f24_hz5n"))
		{
			resDisTable.fn[5].ParLen= BYTE4_TO_INT(pItem->datalen);
			resDisTable.fn[5].Offset= baseOffset+BYTE4_TO_INT(pItem->offset);
//			LOG(LOG_INFO,"fn[5]-> Offset[%d]ParLen[%d]\r\n",resDisTable.fn[5].Offset,resDisTable.fn[5].ParLen);
		}
	}

	//----------24点阵字库配置-----------------------
	if(resDisTable.fn[0].ParLen==0)
	{
		LOG(LOG_INFO,"res no f24_enn err.\r\n");
		close(fd);
		API_ShowLineEn(2,"error\nread f24_enn not",10*1000);
		return -6;
	}
	resDisTable.resFd.reqLen_en   = 48;
	resDisTable.resFd.reqLen_ch   = 72;              //删除了一些多余
	resDisTable.resFd.outLen_en   = 48;
	resDisTable.resFd.outLen_ch   = 72;
//	resDisTable.fd=fd;
	lseek(fd,0,SEEK_SET);
	resDisTable.lenFont=baseOffset+fileLen;
	resDisTable.pbFont=(u8*)malloc(resDisTable.lenFont);
	read(fd,resDisTable.pbFont,resDisTable.lenFont);
	close(fd);
	return 0;
}




void DeInitExtResLib(void)
{
	free(resDisTable.pbFont);
	memset(&resDisTable,0x00,sizeof(resDisTable));
}





#define FONT_MAX_ONE_GBK	96     //目前使用的最大字体,一个汉字占用的存储空间
#define FONT_CL_CALC		94    //  (0xFE - 0xA1 + 1)=94;

int Font_Gbk_chn_addr(u8 hv,u8 lv)
{  
	// 0xXX7F delete from gbk
	if (lv == 0x7F) return -1;
	
	// GBK2 - 1
	if (hv >= 0xB0 && hv <= 0xD7 && lv >= 0xA1 && lv <= 0xFE)
	{
		int index = (hv - 0xB0) * FONT_CL_CALC;
		index += lv - 0xA1;
		
		if (hv == 0xD7 && lv > 0xF9) return -1;
		return  resDisTable.fn[2].Offset + index*(resDisTable.resFd.reqLen_ch);
	}
	// GBK2 - 2
	if (hv >= 0xD8 && hv <= 0xF7 && lv >= 0xA1 && lv <= 0xFE)
	{
		int index = (3755) + (hv - 0xD8) * FONT_CL_CALC;
		index += lv - 0xA1;
		return  resDisTable.fn[2].Offset + index*(resDisTable.resFd.reqLen_ch);
	}
	
	// GBK3
	if (hv >= 0x81 && hv <= 0xA0 && lv >= 0x40 && lv <= 0xFE)
	{
		int index = (hv - 0x81) * (0xFE - 0x40);
		index += lv > 0x7F ? (lv - 0x40 - 1) : (lv - 0x40);
		return  resDisTable.fn[3].Offset + index*(resDisTable.resFd.reqLen_ch);
	}
	
	// GBK4
	if (hv >= 0xAA && hv <= 0xFE && lv >= 0x40 && lv <= 0xA0)
	{
		int index = (hv - 0xAA) * (0xA0 - 0x40);
		index += lv > 0x7F ? (lv - 0x40 - 1) : (lv - 0x40);
		return  resDisTable.fn[4].Offset + index*(resDisTable.resFd.reqLen_ch);
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
		
		return  resDisTable.fn[1].Offset + index*(resDisTable.resFd.reqLen_ch);
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

		return  resDisTable.fn[5].Offset + index*(resDisTable.resFd.reqLen_ch);
	}
	return -2;
}

int Font_Get_en_addr(u8 a)
{	
	if(a < 0x20)
		return -1;      //非英文字母
	return resDisTable.fn[0].Offset + ((a-0x20) * resDisTable.resFd.reqLen_en);
}

static A_RGB uilibForeColor=0x00FFFFFF,uilibBackColor=0xFF000000;
void UI_SetFontColor(A_RGB ForeColor,A_RGB BackColor)
{
	uilibForeColor= ForeColor;
	uilibBackColor= BackColor;
}

int UI_DisplayFont(XuiWindow *pWindow,POINT* prclTrg, u8* hzData)
{
	A_RGB *pbgra;
	A_RGB* pWidget;
	u8 *s_dots;
    RECTL rect;
	int  offset;
	u8  i,j,backflag;	//readLen,
	u8  wMax,wi,db;	//readLen,
	u16 width,height;
	
    if(resDisTable.pbFont == NULL)
        return 0;
	//----------------------------------------------------------------
	pWidget = pWindow->widget;
	width	= pWindow->width;
	height	= pWindow->height;
	
	if(prclTrg->left >= width || prclTrg->top>=height) 
		return 0;
    rect.left = prclTrg->left;
    rect.top = prclTrg->top;    
    rect.height = FONT_SIZE;
	
    if(hzData[0]&0x80)
    {
		offset=Font_Gbk_chn_addr(hzData[0],hzData[1]);
		if(offset < 0) return 0;
		rect.width = FONT_SIZE;
	//	readLen=resDisTable.resFd.reqLen_ch;
	//	hzData++; hzData++;
	}
	else
	{
		offset=Font_Get_en_addr(hzData[0]);
		if(offset < 0) return 0;
		rect.width = FONT_SIZE/2;
	//	readLen = resDisTable.resFd.reqLen_en;
	//	hzData++;
	}
	s_dots=resDisTable.pbFont + offset;
	if(uilibBackColor&0xFF000000)
		backflag = 1;
	else
		backflag = 0;
	//--------------------------------------------------
    for (i = 0; i < FONT_SIZE; i++)
    {    
    	if((u16)(rect.top+i) >= height) break;
    	pbgra=&pWidget[(rect.top+i)*width+rect.left];
        for (j = 0; j < rect.width; j+=8)
        {
        	db=*s_dots++;
        	wMax=rect.width-j;
			if(wMax>8) wMax=8;
        	for(wi=0;wi<wMax;wi++)
        	{
        		if((rect.left+j+wi) >= width) break;
				if(db&0x80) 	//if((db<<(wi&0x07)) & 0x80)	//
				{
					*pbgra = uilibForeColor;
				}
				else if(backflag)
				{
					*pbgra = uilibBackColor;
				}
				pbgra++; db<<=1;
			}
        }
    }
	return rect.width;
}


int UI_DrawLineString(XuiWindow *pWindow,POINT* prclTrg,const char *src)
{
	int ret,offset=0;
	POINT rclTrg;
	rclTrg.left=prclTrg->left;
	rclTrg.top=prclTrg->top;
	while(src[offset])
	{
		if(src[offset] & 0x80)
		{
			ret=UI_DisplayFont(pWindow,&rclTrg,(u8*)src+offset);
			if(ret <= 0) break;
			rclTrg.left += ret;	
			offset++;
		}
		else if(src[offset]=='\n')
		{
			rclTrg.top += FONT_SIZE;
			rclTrg.left = prclTrg->left;
		}
		else if(src[offset] >= ' ')
		{
			ret=UI_DisplayFont(pWindow,&rclTrg,(u8*)src+offset);
			if(ret <= 0) break;
			rclTrg.left += ret;
		}
		offset++;
	}
	return offset;
}

int UI_DrawRectString(XuiWindow *pWindow,RECTL* pRect,const char *src)
{
	int offset=0;
	POINT rclTrg;
	rclTrg.left=pRect->left;
	rclTrg.top=pRect->top;
	while(src[offset])
	{
		if(src[offset] & 0x80)
		{
			if(rclTrg.left > ((pRect->left+pRect->width)- FONT_SIZE))
			{
				rclTrg.top += FONT_SIZE;
				//---------严格控制显示区域---------------------
				if((rclTrg.top+FONT_SIZE)>(pRect->top+pRect->height))
					return offset;
				rclTrg.left = pRect->left;
			}
			rclTrg.left += UI_DisplayFont(pWindow,&rclTrg,(u8*)src+offset);
			offset++;
		}
		else if(src[offset] == '\n')
		{
			rclTrg.top += FONT_SIZE;
			//---------严格控制显示区域---------------------
			if((rclTrg.top+FONT_SIZE)>(pRect->top+pRect->height))
				return offset;
			rclTrg.left = pRect->left;
		}
		else if((u8)src[offset] >= ' ')
		{
			if(rclTrg.left > ((pRect->left+pRect->width)- FONT_SIZE/2))
			{
				rclTrg.top += FONT_SIZE;
				//---------严格控制显示区域---------------------
				if((rclTrg.top+FONT_SIZE)>(pRect->top+pRect->height))
					return offset;
				rclTrg.left = pRect->left;
			}
			/*
			if(uiBgColor&0xff000000)
				DisplayTransparentString(&rclTrg,(LPBYTE)sBuff);
			else
				DisplayString(&rclTrg, (LPBYTE)sBuff);
				*/
			rclTrg.left += UI_DisplayFont(pWindow,&rclTrg,(u8*)src+offset);
		}
		offset++;
	}
	return offset;
}


void UI_DrawCenterString(XuiWindow *pWindow,char *src)
{
	int sLenWidth;
	POINT rclTrg;
	sLenWidth=strlen(src)*FONT_SIZE/2;
	if(sLenWidth < pWindow->width)
		rclTrg.left=(pWindow->width - sLenWidth)/2;
	else
		rclTrg.left=0;
	if(FONT_SIZE < pWindow->height)
		rclTrg.top= (pWindow->height- FONT_SIZE)/2;
	else
		rclTrg.top = 0;
	
	while(*src)
	{
		if(*src & 0x80)
		{
			rclTrg.left += UI_DisplayFont(pWindow,&rclTrg,(u8*)src);
			src++;
		}
		else
		{
			rclTrg.left += UI_DisplayFont(pWindow,&rclTrg,(u8*)src);
		}
		src++;
	}
}


const API_FONT_Def ApiFont={
	{'F','N','T',8},
	UI_SetSysEnColor,
	UI_DisplaySysEn,
	
	InitExtResLib,
	DeInitExtResLib,
	UI_SetFontColor,
	UI_DisplayFont,
	UI_DrawLineString,
	UI_DrawRectString,
	UI_DrawCenterString,
};


//=====================================================================================
XuiFont *XuiCreateFont(char *fontfile,int index, XuiFontSet fontset)
{
	XuiFont *pXfont;
	pXfont=(XuiFont *)malloc(sizeof(XuiFont));
	memset(pXfont,0x00,sizeof(XuiFont));
	pXfont->pFont=Font_Create(fontfile);
	pXfont->fontset=fontset;
	pXfont->index = index;
	return pXfont;
}

void XuiDestroyFont(XuiFont *font)
{
	if(font)
	{
		Font_Destroy(font->pFont);
		free(font);
	}
}

int XuiDisplayFont(XuiWindow *pWindow,XuiFont *pFont,POINT* prclTrg,XuiTextStyle textstyle,u8* *ppChar,A_RGB ForeColor)
{
	A_RGB *pbgra;
	A_RGB* pWidget;
	u8  i,j;	//readLen,
	u8  wMax,wi,db;	//readLen,
	u16 width,height,left,top;
	FontbitMsg tFontMsg;
	
    if(pFont->pFont == NULL)
        return 0;
	//----------------------------------------------------------------
	width	= pWindow->width;
	height	= pWindow->height;
	
	if(prclTrg->left >= width || prclTrg->top>=height) 
		return 0;
   
	*ppChar += Font_GetBitMap(pFont->pFont,*ppChar,&tFontMsg);
	if(tFontMsg.pFontBit==NULL)
		return tFontMsg.w;
	//--------------------------------------------------
    left = prclTrg->left;
    top = prclTrg->top;    
	pWidget = pWindow->widget;
    for (i = 0; i < tFontMsg.h; i++)
    {    
    	if((u16)(top+i) >= height) break;
    	pbgra=&pWidget[(top+i)*width+left];
        for (j = 0; j < tFontMsg.w; j+=8)
        {
        	db = *tFontMsg.pFontBit++;
        	wMax=tFontMsg.w - j;
			if(wMax>8) wMax=8;
        	for(wi=0;wi<wMax;wi++)
        	{
        		if((left+j+wi) >= width) break;
				if(db&0x80) 	//if((db<<(wi&0x07)) & 0x80)	//
				{
					*pbgra = ForeColor;
					if(textstyle == XUI_BOLD)
					{
						pbgra[1] = ForeColor;
						pbgra[width] = ForeColor;
						pbgra[width+1] = ForeColor;
					}
				}
				pbgra++; db<<=1;
			}
        }
    }
	return tFontMsg.w;
}

int XuiCanvasDrawText(XuiWindow *window,unsigned int x,unsigned int y,unsigned int height,XuiFont *font,XuiTextStyle textstyle,XuiColor fg,char *text)
{
	u8 *pChar;
	int ret;
	POINT rclTrg;
	rclTrg.left=x;
	rclTrg.top=y;
	pChar = (u8*)text;
	while(*pChar)
	{
		if(*pChar > ' ')
		{
			ret=XuiDisplayFont(window,font,&rclTrg,textstyle,&pChar,*(A_RGB*)&fg);//(A_RGB)fg
			if(ret <= 0) break;
			rclTrg.left += ret;
		}
		else
		{
			if(*pChar == '\n')
			{
				rclTrg.top += height;
				rclTrg.left = x;
			}
			pChar++;
		}
	}
	return 0;
}




