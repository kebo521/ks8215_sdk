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

//===========================================================================================

extern int SetRotationAngle(XuiTransform Angle,XuiWindow *pHardWindow);

extern int open_screen(const char* filename,int tpFlag);
extern void close_screen(void);

extern void fb_ui_point(int x,int y,A_RGB Inrgb);
extern void fb_ui_vline(int x, int y, int h, A_RGB argb);
extern void fb_ui_hline(int x, int y, int w, A_RGB argb);
extern void fb_ui_line(int xs, int ys, int xe, int ye, A_RGB argb);
extern void fb_ui_circle(signed short x, signed short y, signed short r, A_RGB argb);
extern void fb_ui_fill_circle(signed short x, signed short y, signed short r,signed short ar,A_RGB argb);
extern void fb_ui_fill_rect(int x, int y, int w, int h,A_RGB argb); 
extern void fb_ui_set_rect(int x, int y, int w, int h,A_RGB* pArgb);
extern A_RGB* xui_fb_GetScreenMsg(RECTL* pRect,int *pLineWidth);
extern void xui_fb_pull(RECTL* pRect,A_RGB* pOutRGB);
extern void xui_fb_push(RECTL* pRect,A_RGB* pInRGB);

extern void xui_fb_syn(void);
extern void xui_window_push(XuiWindow *window,RECTL* pRect,A_RGB* pInrgb);


#endif /*LINUX_FB_H*/
