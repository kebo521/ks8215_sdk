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
static GRSurface* gr_draw = NULL;
static int fb_fd = -1;
static int flagRotationAngle=XUI_ROTATE_0;
static int offsetScreen=0;
static int display_off_x,display_off_y,display_width,display_height;

void SetRotationAngle(XuiTransform Angle,XuiWindow *pHardWindow)
{
	flagRotationAngle=Angle;
	if(gr_draw == NULL) return;
	//--------------------计算起点偏移量----------------------------------------------
	if(flagRotationAngle == XUI_ROTATE_0)
	{
		offsetScreen= display_off_y * gr_draw->row_bytes+ display_off_x*sizeof(A_RGB);
	}
	else if(flagRotationAngle == XUI_ROTATE_90)
	{
		offsetScreen = display_off_y * gr_draw->row_bytes + (display_off_x+display_width)*sizeof(A_RGB);
	}
	else if(flagRotationAngle == XUI_ROTATE_180)
	{
		offsetScreen = (display_off_y+display_height) *gr_draw->row_bytes + (display_off_x+display_width)*sizeof(A_RGB);
	}
	else if(flagRotationAngle == XUI_ROTATE_270)
	{
		offsetScreen = (display_off_y+display_height) *gr_draw->row_bytes + display_off_x*sizeof(A_RGB);
	}

	if(pHardWindow)
	{
		memset(pHardWindow,0x00,sizeof(XuiWindow));
		//pHardWindow->left =0;
		//pHardWindow->top =0;
		if(flagRotationAngle == XUI_ROTATE_0 || flagRotationAngle == XUI_ROTATE_180)
		{
			pHardWindow->width=display_width;
			pHardWindow->height=display_height;
		}
		else
		{
			pHardWindow->width=display_height;
			pHardWindow->height=display_width;
		}
	}
}

int tp_flag1 = 0;
static minui_backend* gr_backend = NULL;

int open_screen(const char* filename) //XuiWindow *pHardWindow
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
    display_off_x = gr_draw->width * OVERSCAN_PERCENT / 100;
    display_off_y = gr_draw->height * OVERSCAN_PERCENT / 100;
	display_width = gr_draw->width - 2*display_off_x;
	display_height=gr_draw->height - 2*display_off_y;
	//-----------------------------------------------------------------------------------
	printf("screen adf[%d,%d,%d,%d]\r\n",display_off_x,display_off_y,display_width,display_height);
	
	tp_flag1 = 0;	//0 为双画布，1为单画布
	return 1;
}

void close_screen(void)
{
    gr_backend->exit(gr_backend);
}


void gr_fb_blank(int blank)
{
    gr_backend->blank(gr_backend, blank);
}

int xui_fb_push(XuiWindow *window,RECTL* pRect,A_RGB* pInrgb) 
{
	int i,j,x,y,w,h;
	int swidth,wWidth;
	A_RGB *pMapData;
	A_RGB *destin,*source;
	if(gr_draw == NULL)
		return -1;
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
	swidth	=gr_draw->row_bytes/sizeof(A_RGB);
	pMapData = (A_RGB *)(gr_draw->data + offsetScreen);
	if(flagRotationAngle == XUI_ROTATE_0)
	{
		pMapData += window->top*swidth + window->left + x;
		for (j = y; j < h; j++) 
		{
			destin =pMapData + j*swidth;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin++ = *source++;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_90)
	{
		pMapData +=  (window->left+x)*swidth - window->top;
		for (j = y; j < h; j++) 
		{
			destin = pMapData - j;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin = *source++;
				destin += swidth;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_180)
	{
		pMapData -= window->top*swidth + window->left + x;
		for (j = y; j < h; j++) 
		{
			destin = pMapData - j*swidth;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin-- = *source++;
			}
		}
	}
	else if(flagRotationAngle == XUI_ROTATE_270)
	{
		pMapData -=  (window->left+x)*swidth - window->top;
		for (j = y; j < h; j++) 
		{
			destin = pMapData+j;
			source=pInrgb+(j*wWidth + x);
			for(i=x; i<w; i++)
			{
				*destin = *source++;
				destin -= swidth;
			}
		}
	}
	{
	    unsigned char *tmpbuf = gr_draw->data;
	    gr_draw = gr_backend->flip(gr_backend);
	    if(!tp_flag1){
	        LOG(LOG_INFO,"gr_flip gr_draw->data len: %d, %d IN", strlen(tmpbuf), __LINE__);
	        memcpy(gr_draw->data, tmpbuf, gr_draw->row_bytes*gr_draw->height);
	    }
	}
	return RET_OK;
}



