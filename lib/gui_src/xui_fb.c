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
#include "comm_type.h"

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

#include "xui_ui.h"
#include "xui_fb.h"
#include "sdk/sys_sdk.h"



/*
XuiWindow* xui_fb_open(const char* filename) {
  uint32_t size = 0;
  XuiWindow* fb = NULL;
  struct fb_fix_screeninfo fix;
  struct fb_var_screeninfo var;
  return_value_if_fail(filename != NULL, NULL);

  fb = (XuiWindow*)calloc(1, sizeof(XuiWindow));
  return_value_if_fail(fb != NULL, NULL);

  fb->fd = open(filename, O_RDWR);
  if (fb->fd < 0) {
    log_debug("open %s failed(%d)\n", filename, errno);
    free(fb);
    return NULL;
  }

  if (ioctl(fb->fd, FBIOGET_FSCREENINFO, &fix) < 0) goto fail;
  if (ioctl(fb->fd, FBIOGET_VSCREENINFO, &var) < 0) goto fail;

  var.xoffset = 0;
  var.yoffset = 0;
  ioctl(fb->fd, FBIOPAN_DISPLAY, &(var));

  log_debug("fb_info_t: %s\n", filename);
  log_debug("fb_info_t: xres=%d yres=%d bits_per_pixel=%d mem_size=%d\n", var.xres, var.yres,
            var.bits_per_pixel, fb_size(fb));
  log_debug("fb_info_t: red(%d %d) green(%d %d) blue(%d %d)\n", var.red.offset, var.red.length,
            var.green.offset, var.green.length, var.blue.offset, var.blue.length);

  fb->w = var.xres;
  fb->h = var.yres;
  fb->bpp = var.bits_per_pixel / 8;
  fb->line_length = fix.line_length;

  size = fb->height * fb->line_length;
  fb->data = (uint8_t*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fb->fd, 0);

  if (fb->data == MAP_FAILED) {
    log_debug("map framebuffer failed.\n");
    goto fail;
  }

  log_debug("line_length=%d mem_size=%d\n", fix.line_length,fb->height * fb->line_length);
  log_debug("xres_virtual =%d yres_virtual=%d xpanstep=%d ywrapstep=%d\n", var.xres_virtual,
            var.yres_virtual, fix.xpanstep, fix.ywrapstep);

  return fb;
fail:
  log_debug("%s is not a framebuffer.\n", filename);
  close(fb->fd);
  free(fb);

  return NULL;
}


ret_t xui_fb_close(XuiWindow* fb) {
  return_value_if_fail(fb != NULL, RET_BAD_PARAMS);

  munmap(fb->data, fb_size(fb));
  close(fb->fd);
  memset(fb, 0x00, sizeof(XuiWindow));
  free(fb);

  return RET_OK;
}

*/
#if(1)

typedef struct {
	int off_X,off_Y;
    int width,height;
    int sWidth,sHeight,rWidth;
	int RotationAngle;
	A_RGB*	pARGB;	//原始地址
    A_RGB* 	pStartPoint;
} DefSurface;
static DefSurface tSurface={0};

static int flagRotationAngle=XUI_ROTATE_0;
static int fb_fd = -1;

void close_screen(void)
{
	if(tSurface.pARGB)
	{
		/* Unmap the framebuffer*/
		munmap(tSurface.pARGB,tSurface.sHeight * tSurface.rWidth * sizeof(A_RGB));
	}
	
	if(fb_fd != -1)
	{
		/* Close framebuffer device */
		close(fb_fd);
		fb_fd = -1;
	}
	memset(&tSurface,0x00,sizeof(tSurface));
	
}

int open_screen(const char* filename,int tpFlag) //XuiWindow *pHardWindow
{
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;
	int pixel_bytes;
	unsigned char* pMapdata;
	//printf("open screen open[%s]\r\n",filename);
	if ((fb_fd = open(filename, O_RDWR)) == -1) {
		printf("open screen open[%s] Err\r\n",filename);
		return -1;
	}
	if((ioctl(fb_fd, FBIOGET_VSCREENINFO, &var) < 0) || (ioctl(fb_fd, FBIOGET_FSCREENINFO, &fix) < 0)) 
	{
		printf("open screen in %s line %d\r\n",__FUNCTION__,__LINE__);
		close(fb_fd); fb_fd= -1;
		return -2;
	}
	pMapdata =  mmap(NULL, var.yres *fix.line_length, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fb_fd, 0);
	if (pMapdata == MAP_FAILED)
	{
		printf("rw_sd_inand.c: Can't mmap frame pARGB ++\r\n");
		close(fb_fd); fb_fd= -1;
		return -4;
	}
	printf("open screen[%d,%d][%d][%d]\r\n",var.xres,var.yres,var.bits_per_pixel,fix.line_length);
	pixel_bytes = var.bits_per_pixel / 8;
	if(pixel_bytes == 3)
		pixel_bytes = 4;
	tSurface.sWidth = var.xres;
	tSurface.sHeight= var.yres;
	//--------------全屏参数----------------------
	tSurface.width =	320;
	tSurface.height=	240;
	tSurface.off_X=tSurface.sWidth - tSurface.width-10;
	tSurface.off_Y=10;
	tSurface.rWidth=fix.line_length/sizeof(A_RGB);
	tSurface.pARGB=(A_RGB*)pMapdata;
	//-----------------------------------------------------------------------------------
	return 1;
}

//=============================画点====================================
void fb_ui_point(int x,int y,A_RGB Inrgb) 
{
	tSurface.pARGB[y*tSurface.rWidth + x]=Inrgb;
}

void fb_ui_vline(int x, int y, int h, A_RGB argb) 
{
	register A_RGB *pbgra;
	register int rWidth;
	if(x >= tSurface.sWidth) return;
	if(y >= tSurface.sHeight) return;
	if((y+h) > tSurface.sHeight) 
		h = tSurface.sHeight-y;
	rWidth = tSurface.rWidth;
	pbgra=tSurface.pARGB+(y*rWidth+ x);
	while(h--)
	{
		*pbgra = argb;
		pbgra += rWidth;
		//fb_ui_point(x, y + i, argb);
	}
}

void fb_ui_hline(int x, int y, int w, A_RGB argb) 
{
	register A_RGB *pbgra;
	if(y >= tSurface.sHeight) return; 
	if(x >= tSurface.sWidth) return;
	if((x+w) > tSurface.sWidth)
		w = tSurface.sWidth - x;
	pbgra=tSurface.pARGB+(y*tSurface.rWidth+ x);
	while(w--)
	{
		*pbgra++ =argb;
	//	fb_ui_point(x + i, y, rgba);
	}
}

//=============================画线，起到到终点，支持斜线====================================
void fb_ui_line(int xs, int ys, int xe, int ye,A_RGB argb) 
{
	int w,h,max;
	float xm,ym,wm,hm;
	if(xe >= xs)
	{
		if(xs >= tSurface.sWidth) return;
		if(xe > tSurface.sWidth) xe = tSurface.sWidth;
		w = xe-xs;
		wm = w;
	}
	else
	{
		if(xe >= tSurface.sWidth) return;
		if(xs > tSurface.sWidth) xs = tSurface.sWidth;
		w = xe-xs;
		wm = -w;
	}
	if(ye >= ys)
	{
		if(ys >= tSurface.sHeight) return;
		if(ye > tSurface.sHeight) ye=tSurface.sHeight;
		h = ye-ys;
		hm = h;
	}
	else
	{
		if(ye >= tSurface.sHeight) return;
		if(ys > tSurface.sHeight) ys=tSurface.sHeight;
		h = ye-ys;
		hm = -h;
	}
	if(wm>hm) max=wm;
	else max=hm;
	tSurface.pARGB[ys*tSurface.rWidth+xs]=argb;
	if(!max) return;
	wm = (float)w/max;
	hm = (float)h/max;
	xm	=	xs;
	ym	=	ys;
	max--;	//终点不画
	while(max--) 
	{
		xm += wm;
		ym += hm;
		xs = xm;
		ys = ym;
		tSurface.pARGB[ys*tSurface.rWidth+xs]=argb;
	}
}




typedef struct{
	signed short x,y;
}area_pixel;


typedef union {
	unsigned long uXY;
	area_pixel pix;
}pixel_Data;



void fb_ui_circle(signed short x, signed short y, signed short r,A_RGB argb) 
{
	double sci,scs;
	int jdm;
	pixel_Data curr,old;
	signed short xr,yr,xMax,yMax;

	xMax=tSurface.sWidth;
	yMax=tSurface.sHeight;
	
	jdm = r*M_PI;
	scs = M_PI/jdm;
	sci =0;
	//----4段90度弧线组成一个画圆，减少三角函数使用量，提升效率--------------
	jdm += 3;
	jdm >>= 2;
	
	old.uXY=0;	
	while(jdm--)
	{
		curr.pix.x=sin(sci)*r;
		curr.pix.y=cos(sci)*r;
		sci += scs;
		if(old.uXY == curr.uXY) continue; //避免重复写点
		
	#if(0)
		xr=x - curr.pix.x;
		yr=y - curr.pix.y;
		if(xr < xMax && yr < yMax)
			fb_ui_point(fb,xr,yr,rgba);

		xr= x + curr.pix.y;
		yr= y - curr.pix.x;
		if(xr < xMax && yr < yMax)
			fb_ui_point(fb,xr,yr,rgba);

		xr= x + curr.pix.x;
		yr= y + curr.pix.y;
		if(xr < xMax && yr < yMax)
			fb_ui_point(fb,xr,yr,rgba);
		
		xr=x - curr.pix.y;
		yr=y + curr.pix.x;
		if(xr < xMax && yr < yMax)
			fb_ui_point(fb,xr,yr,rgba);
	#else
		yr=y - curr.pix.y;
		if(yr < yMax)
		{
			xr=x - curr.pix.x;
			if( x < xMax)
				fb_ui_point(xr,yr,argb);
			if(curr.pix.x)
			{
				xr= x + curr.pix.x;
				if( x < xMax)
					fb_ui_point(xr,yr,argb);
			}
		}
		yr= y + curr.pix.y;
		if(yr < yMax)
		{
		//	xr= x + curr.pix.x;
			if( x < xMax)
				fb_ui_point(xr,yr,argb);
			if(curr.pix.x)
			{
				xr=x - curr.pix.x;
				if( x < xMax)
					fb_ui_point(xr,yr,argb);
			}
		}
		xr= x + curr.pix.y;
		if(xr < xMax)
		{
			yr= y - curr.pix.x;
			if( yr < yMax)
				fb_ui_point(xr,yr,argb);
			if(curr.pix.x)
			{
				yr= y + curr.pix.x;
				if( yr < yMax)
					fb_ui_point(xr,yr,argb);
			}
		}
		xr=x - curr.pix.y;
		if(xr < xMax)
		{
		//	yr=y + curr.pix.x;
			if( yr < yMax)
				fb_ui_point(xr,yr,argb);
			if(curr.pix.x)
			{
				yr=y - curr.pix.x;
				if( yr < yMax)
					fb_ui_point(xr,yr,argb);
			}
		}	
	#endif
		old.uXY = curr.uXY;
	}		
}


void fb_ui_fill_circle(signed short x, signed short y, signed short r,signed short ar, A_RGB argb) 
{
	double sci,scs;
	int jdm;
	pixel_Data curr,old;
	signed short xr,yr,xtwo,yMax;

	yMax=tSurface.sHeight;
	
	jdm = r*M_PI;
	scs = M_PI/jdm;
	sci =M_PI/2;
	//----4段90度弧线组成一个画圆，减少三角函数使用量，提升效率--------------
	jdm ++;
	jdm >>= 1;
	
	old.pix.y=0xffff;	
	while(jdm--)
	{
		curr.pix.x=sin(sci)*r;
		curr.pix.y=cos(sci)*r;
		sci -= scs;
		if(old.pix.y == curr.pix.y) continue; //避免重复写点

		xr=x - curr.pix.x;
		if(ar <= curr.pix.y)
		{
			yr=y - curr.pix.y;
			if(yr>=0 && yr < yMax)
			{
				if(curr.pix.x)
				{
					fb_ui_hline(xr,yr,curr.pix.x*2,argb);
				}
				else
				{
					fb_ui_point(xr,yr,argb);
				}
			}
			yr= y + curr.pix.y;
			if(yr < yMax)
			{
				if(curr.pix.x)
				{
					fb_ui_hline(xr,yr,curr.pix.x*2,argb);
				}
				else
				{
					fb_ui_point(xr,yr,argb);
				}
			}
		}
		else
		{
			xtwo=sin( acos(((double)curr.pix.y)/ar) )*ar;
			yr=y - curr.pix.y;
			if(yr>=0 && yr < yMax)
			{
				fb_ui_hline(xr,yr,curr.pix.x-xtwo,argb);
				fb_ui_hline(x+xtwo+1,yr,curr.pix.x-xtwo,argb);
			}
			yr= y + curr.pix.y;
			if(yr < yMax)
			{
				fb_ui_hline(xr,yr,curr.pix.x-xtwo,argb);
				fb_ui_hline(x+xtwo+1,yr,curr.pix.x-xtwo,argb);
			}
		}
		old.uXY = curr.uXY;
	}		
}



void fb_ui_fill_rect(int x, int y, int w, int h,A_RGB argb) 
{
	register A_RGB *pbgra;
	register int i;
	w += x;
	h += y;

	if(w > tSurface.sWidth) w=tSurface.sWidth;
	if(h > tSurface.sHeight) h=tSurface.sHeight;
	for (;y < h; y++) 
	{
		//fb_ui_hline(fb, x, y + i, w, rgba);
		pbgra=tSurface.pARGB+(y*tSurface.rWidth + x);
		for(i=x; i<w; i++)
		{
			*pbgra++ = argb;
		}
	}
}

void fb_ui_set_rect(int x, int y, int w, int h,A_RGB* pArgb) 
{
	register GuiColor *destin,*source;
	int		i;
	w += x;
	h += y;

	if(w > tSurface.sWidth) w=tSurface.sWidth;
	if(h > tSurface.sHeight) h=tSurface.sHeight;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	source =(GuiColor *)pArgb;
	for (;y < h; y++) 
	{
		destin=(GuiColor *)(tSurface.pARGB+(y*tSurface.rWidth + x));
		for(i=x; i<w; i++)
		{
			if(source->color.a == 0xFF)
			{//-----------不透蜜---------
				destin->argb = source->argb;
			}
			else if(source->color.a > 0)
			{//-----------部分透明---------
				register int as,ad;
				as = source->color.a;
				ad = 0xFF - as;
				destin->color.r = (ad*destin->color.r + as*source->color.r)/0xFF;
				destin->color.g = (ad*destin->color.g + as*source->color.g)/0xFF;
				destin->color.b = (ad*destin->color.b + as*source->color.b)/0xFF;
			}
			destin++; source++;
		}
	}
}

void fb_ui_get_rect(int x, int y, int w, int h,A_RGB* pArgb) 
{
	register A_RGB *pbgra;
	register int i;
	w += x;
	h += y;
	if(w > tSurface.sWidth) w=tSurface.sWidth;
	if(h > tSurface.sHeight) h=tSurface.sHeight;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	for (;y < h; y++) 
	{
		pbgra=tSurface.pARGB+(y*tSurface.rWidth + x);
		for(i=x; i<w; i++)
		{
			*pArgb++ = *pbgra++;
		}
	}
}

void fb_ui_xor_rect(int x, int y, int w, int h,A_RGB* pArgb) 
{
	register A_RGB *pbgra;
	register int i;
	w += x;
	h += y;

	if(w > tSurface.sWidth) w=tSurface.sWidth;
	if(h > tSurface.sHeight) h=tSurface.sHeight;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	for (;y < h; y++) 
	{
		pbgra=tSurface.pARGB+(y*tSurface.rWidth + x);
		for(i=x; i<w; i++)
		{
			*pbgra++ ^= *pArgb++;
		}
	}
}

int fb_GetScreenSize(int *pWidth,int *pHeight,RECTL* pUI) 
{
	if(tSurface.pARGB== NULL)
		return -1;
	if(pWidth)
		*pWidth = tSurface.sWidth;
	if(pHeight)
		*pHeight = tSurface.sHeight;

	if(pUI)
	{
		pUI->left = tSurface.off_X;
		pUI->top = tSurface.off_Y;
		pUI->width =tSurface.width;
		pUI->height =tSurface.height;
	}
	return 0;
}


A_RGB* xui_fb_GetScreenMsg(RECTL* pRect,int *pLineWidth) 
{
	pRect->left = tSurface.off_X;
	pRect->top = tSurface.off_Y;
	pRect->width = tSurface.width;
	pRect->height = tSurface.height;
	if(pLineWidth)
		*pLineWidth=tSurface.rWidth;
	return tSurface.pARGB;
}

void xui_fb_push(RECTL* pRect,A_RGB* pInRGB) 
{
	register int w,h,i;
	register A_RGB *pStartPoint,*source;
	w = pRect->width;
	h = pRect->height;
	if(flagRotationAngle == XUI_ROTATE_0)
	{
		pStartPoint = tSurface.pStartPoint + tSurface.rWidth*pRect->top + pRect->left;
		while(h--)
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*source++ = *pInRGB++;
			}
			pStartPoint += tSurface.rWidth;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_90)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint+ pRect->left*tSurface.rWidth - pRect->top;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*source = *pInRGB++;
				source += rWidth;
			}
			pStartPoint--;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_180)
	{
		pStartPoint = tSurface.pStartPoint - pRect->top*tSurface.rWidth - pRect->left;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*source-- = *pInRGB++;
			}
			pStartPoint -= tSurface.rWidth;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_270)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint - tSurface.rWidth*pRect->left + pRect->top;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*source = *pInRGB++;
				source -= rWidth;
			}
			pStartPoint++;
		}
	}
}


void xui_fb_pull(RECTL* pRect,A_RGB* pOutRGB) 
{
	register int w,h,i;
	register A_RGB *pStartPoint,*source;
	w = pRect->width;
	h = pRect->height;
	if(flagRotationAngle == XUI_ROTATE_0)
	{
		pStartPoint = tSurface.pStartPoint + tSurface.rWidth*pRect->top + pRect->left;
		while(h--)
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*pOutRGB++ = *source++;
			}
			pStartPoint += tSurface.rWidth;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_90)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint+ pRect->left*tSurface.rWidth - pRect->top;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*pOutRGB++ = *source;
				source += rWidth;
			}
			pStartPoint--;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_180)
	{
		pStartPoint = tSurface.pStartPoint - pRect->top*tSurface.rWidth - pRect->left;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*pOutRGB++ = *source--;
			}
			pStartPoint -= tSurface.rWidth;
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_270)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint - tSurface.rWidth*pRect->left + pRect->top;
		while(h--) 
		{
			source =pStartPoint;
			for(i=0; i<w; i++)
			{
				*pOutRGB++ = *source;
				source -= rWidth;
			}
			pStartPoint++;
		}
	}
}

//===========硬件到软件=====坐标转换=======================
void HSTransformCoord_0(u16 *pX,u16 *pY)
{
	*pX -= tSurface.off_X;
	*pY -= tSurface.off_Y;
}
void HSTransformCoord_90(u16 *pX,u16 *pY)
{
	u16 buff;
	*pX -= tSurface.off_X;
	*pY -= tSurface.off_Y;
	buff = *pY;
	*pY = (gUiDataAll.tHardWindow.height - *pX);
	*pX = buff;
}
void HSTransformCoord_180(u16 *pX,u16 *pY)
{
	*pX -= tSurface.off_X;
	*pY -= tSurface.off_Y;
	*pX = (gUiDataAll.tHardWindow.width - *pX);
	*pY = (gUiDataAll.tHardWindow.height - *pY);
}

void HSTransformCoord_270(u16 *pX,u16 *pY)
{
	u16 buff;
	*pX -= tSurface.off_X;
	*pY -= tSurface.off_Y;
	buff = (gUiDataAll.tHardWindow.width - *pY);
	*pY = *pX;
	*pX = buff;
}
//===========软件到硬件=====坐标转换=======================
void SHTransformCoord_0(u16 *pX,u16 *pY)
{
	*pX += tSurface.off_X;
	*pY += tSurface.off_Y;
}
void SHTransformCoord_90(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = (tSurface.height - *pY);
	*pY = tSurface.off_Y + *pX;
	*pX = tSurface.off_X + buff;
}
void SHTransformCoord_180(u16 *pX,u16 *pY)
{
	*pX = tSurface.off_X + (tSurface.width - *pX);
	*pY = tSurface.off_Y + (tSurface.height - *pY);
}

void SHTransformCoord_270(u16 *pX,u16 *pY)
{
	u16 buff;
	buff = *pY;
	*pY = tSurface.off_Y + (tSurface.width - *pX);
	*pX = tSurface.off_X + buff;
}

//=========================================================================================================
int SetRotationAngle(XuiTransform Angle,XuiWindow *pHardWindow)
{
	int offsetData=0;
	if(tSurface.pARGB == NULL) return -1;
	//--------------------计算起点偏移量----------------------------------------------
	if(Angle == XUI_ROTATE_0)
	{
		offsetData = tSurface.off_Y * tSurface.rWidth + tSurface.off_X;
	}
	else if(Angle == XUI_ROTATE_90)
	{
		offsetData = tSurface.off_Y * tSurface.rWidth + (tSurface.off_X+tSurface.width-1);
	}
	else if(Angle == XUI_ROTATE_180)
	{
		offsetData = (tSurface.off_Y+tSurface.height-1) *tSurface.rWidth + (tSurface.off_X+tSurface.width-1);
	}
	else if(Angle == XUI_ROTATE_270)
	{
		offsetData = (tSurface.off_Y+tSurface.height-1) *tSurface.rWidth + tSurface.off_X;
	}
	tSurface.pStartPoint = tSurface.pARGB + offsetData;

	if(pHardWindow)
	{
		memset(pHardWindow,0x00,sizeof(XuiWindow));
		//pHardWindow->left =0;
		//pHardWindow->top =0;
		if(Angle == XUI_ROTATE_0 || Angle == XUI_ROTATE_180)
		{
			pHardWindow->width=tSurface.width;
			pHardWindow->height=tSurface.height;
		}
		else
		{
			pHardWindow->width=tSurface.height;
			pHardWindow->height=tSurface.width;
		}
	}
	flagRotationAngle=Angle;
	return 0;
}

void xui_fb_syn(void)
{
	
}

void xui_window_push(XuiWindow *window,RECTL* pRect,A_RGB* pInrgb) 
{
	int i,j,x,y,w,h;
	int wWidth;
	A_RGB *pStartPoint;
	register A_RGB *destin,*source;
	if(pRect)
	{
		x = pRect->left;
		y = pRect->top;
		w =x+ pRect->width;
		h =y+ pRect->height;
	}
	else
	{
		x = 0;
		y = 0;
		w = window->width;
		h = window->height;
	}
	wWidth = window->width;
	if(flagRotationAngle == XUI_ROTATE_0)
	{
		pStartPoint = tSurface.pStartPoint+ window->top*tSurface.rWidth + window->left + x;
		for (j = y; j < h; j++) 
		{
			destin =pStartPoint + j*tSurface.rWidth;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin++ = *source++;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_90)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint+ (window->left+x)*tSurface.rWidth - window->top;
		for (j = y; j < h; j++) 
		{
			destin = pStartPoint - j;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin = *source++;
				destin += rWidth;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_180)
	{
		pStartPoint = tSurface.pStartPoint - window->top*tSurface.rWidth - (window->left + x);
		for (j = y; j < h; j++) 
		{
			destin = pStartPoint - j*tSurface.rWidth;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin-- = *source++;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_270)
	{
		register int rWidth = tSurface.rWidth;
		pStartPoint = tSurface.pStartPoint - (window->left+x)*tSurface.rWidth + window->top;
		for (j = y; j < h; j++) 
		{
			destin = pStartPoint+j;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin = *source++;
				destin -= rWidth;
			}
		}
	}
}



#endif



