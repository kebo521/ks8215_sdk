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


#ifndef LINUX_FB_H
#define LINUX_FB_H

//================屏显示方向==========================================
typedef enum
{
	XUI_ROTATE_0,		// 不旋转
	XUI_ROTATE_90,	// 顺时针旋转 90 度
	XUI_ROTATE_180,	// 顺时针旋转 180 度
	XUI_ROTATE_270,	// 顺时针旋转 270 度
	XUI_FLIP_VERT,	// 垂直翻转
	XUI_FLIP_HORIZ,	// 横向翻转
}XuiTransform;
//--------------全屏参数----------------------
#define SCREEN_WIDTH		(240) 
#define SCREEN_HEIGT		(320) 

//===========================================================================================
extern void SetRotationAngle(XuiTransform Angle);

extern int open_screen(const char* filename,XuiWindow *pHardWindow);
extern void close_screen(void);

extern int xui_fb_line(int xs, int ys, int xe, int ye, A_RGB argb);
extern int xui_fb_circle(signed short x, signed short y, signed short r, A_RGB argb);
extern int xui_fb_fill_circle(signed short x, signed short y, signed short r,signed short ar,A_RGB argb);
extern int xui_fb_vline(int x, int y, int h, A_RGB argb);
extern int xui_fb_hline(int x, int y, int w, A_RGB argb);
//extern int xui_fb_fill_rect(int x, int y, int w, int h,A_RGB argb);
extern int xui_fb_stroke_rect(int x, int y, int w, int h,A_RGB argb);
//extern int xui_fb_close(screen_buffer* fb);
extern int xui_fb_show_rect(int x, int y, int w, int h,A_RGB* argb);
extern int xui_fb_rect_push(int x, int y, int w, int h,A_RGB* pInrgb);
extern int xui_fb_push(XuiWindow *window,RECTL* pRect,A_RGB* pInrgb);


#endif /*LINUX_FB_H*/
