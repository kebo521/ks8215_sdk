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

//================����ʾ����==========================================
typedef enum
{
	XUI_ROTATE_0,		// ����ת
	XUI_ROTATE_90,	// ˳ʱ����ת 90 ��
	XUI_ROTATE_180,	// ˳ʱ����ת 180 ��
	XUI_ROTATE_270,	// ˳ʱ����ת 270 ��
	XUI_FLIP_VERT,	// ��ֱ��ת
	XUI_FLIP_HORIZ,	// ����ת
}XuiTransform;
//--------------ȫ������----------------------
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
