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

#include "minui.h"



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

typedef struct {
	int off_X,off_Y;
    int width,height;
    int sWidth,sHeight,rWidth;
//	int RotationAngle;
	A_RGB*	pARGB;	//原始地址
    A_RGB* 	pStartPoint;
} DefSurface;
static DefSurface tSurface={0};



static GRSurface* gr_draw = NULL;
static int flagRotationAngle=XUI_ROTATE_0;
static int offsetScreen=0;



int tp_flag1 = 0;
static minui_backend* gr_backend = NULL;

int open_screen(const char* filename,int tpFlag) //XuiWindow *pHardWindow
{
	printf("open screen adf open[%s]\r\n",filename);
	gr_backend = open_adf();
    if (gr_backend) {
        gr_draw = gr_backend->init(gr_backend);
        if (!gr_draw) {
            gr_backend->exit(gr_backend);
        }
    }

    if (!gr_draw) {
        gr_backend = open_fbdev();
        gr_draw = gr_backend->init(gr_backend);
        if (gr_draw == NULL) {
            return -1;
        }
    }
	printf("screen adf[%d,%d][%d,,%d,%d]\r\n",gr_draw->pixel_bytes,gr_draw->row_bytes, \
		OVERSCAN_PERCENT,gr_draw->width,gr_draw->height);
	tSurface.sWidth = gr_draw->width;
	tSurface.sHeight = gr_draw->height;
	tSurface.rWidth = gr_draw->row_bytes/sizeof(A_RGB);

	tSurface.off_X = tSurface.sWidth * OVERSCAN_PERCENT / 100;
	tSurface.off_Y = tSurface.height * OVERSCAN_PERCENT / 100;
	tSurface.width = tSurface.sWidth - 2*tSurface.off_X;
	tSurface.height= tSurface.sHeight - 2*tSurface.off_Y;

	tSurface.pARGB = (A_RGB*)gr_draw->data;
	//-----------------------------------------------------------------------------------
	printf("screen adf[%d,%d,%d,%d]\r\n",tSurface.off_X,tSurface.off_Y,tSurface.width,tSurface.height);
	
	tp_flag1 = tpFlag;	//0 为双画布，1为单画布

	return 1;
}

void close_screen(void)
{
    gr_backend->exit(gr_backend);
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
	int w,h,min;
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
	if(wm<hm) min=wm;
	else min=hm;
	wm = (float)w/min;
	hm = (float)h/min;
	xm	=	xs;
	ym	=	ys;
	//LOG(LOG_INFO,"xui fb line [%f,%f]-[%d,%d],%d,[%f,%f]\r\n",xm,ym,xe,ye,max,wm,hm);
	while(min--) 
	{
		tSurface.pARGB[ys*tSurface.rWidth+xs]=argb;
		xm += wm;
		ym += hm;
		xs = xm;
		ys = ym;
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
	register A_RGB *pbgra;
	register int i;
	w += x;
	h += y;

	if(w > tSurface.sWidth) w=tSurface.sWidth;
	if(h > tSurface.sHeight) h=tSurface.sHeight;
	for (;y < h; y++) 
	{
		pbgra=tSurface.pARGB+(y*tSurface.rWidth + x);
		for(i=x; i<w; i++)
		{
			*pbgra++ = *pArgb++;
		}
	}
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

//=========================================================================================================
int SetRotationAngle(XuiTransform Angle,XuiWindow *pHardWindow)
{
	if(tSurface.pARGB == NULL) return -1;
	//--------------------计算起点偏移量----------------------------------------------
	if(Angle == XUI_ROTATE_0)
	{
		offsetScreen = tSurface.off_Y * tSurface.rWidth + tSurface.off_X;
	}
	else if(Angle == XUI_ROTATE_90)
	{
		offsetScreen = tSurface.off_Y * tSurface.rWidth + (tSurface.off_X+tSurface.width-1);
	}
	else if(Angle == XUI_ROTATE_180)
	{
		offsetScreen = (tSurface.off_Y+tSurface.height-1) *tSurface.rWidth + (tSurface.off_X+tSurface.width-1);
	}
	else if(Angle == XUI_ROTATE_270)
	{
		offsetScreen = (tSurface.off_Y+tSurface.height-1) *tSurface.rWidth + tSurface.off_X;
	}
	tSurface.pStartPoint = tSurface.pARGB + offsetScreen;

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
	unsigned char *tmpbuf = gr_draw->data;
	gr_draw= gr_backend->flip(gr_backend);
	if(!tp_flag1){
		memcpy(gr_draw->data, tmpbuf, gr_draw->row_bytes*gr_draw->height);
		tSurface.pARGB = (A_RGB*)gr_draw->data;
		tSurface.pStartPoint = tSurface.pARGB + offsetScreen;
	}
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







