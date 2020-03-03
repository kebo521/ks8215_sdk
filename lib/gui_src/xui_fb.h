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

//===========================================================================================
typedef struct gr_surface {
    int width;
    int height;
    int row_bytes;
    int pixel_bytes;
    unsigned char* data;
} GRSurface;
typedef GRSurface* gr_surface;
//================================================================================================
//===========Ӳ�������=====����ת��=======================
extern void HSTransformCoord_0(u16 *pX,u16 *pY);
extern void HSTransformCoord_90(u16 *pX,u16 *pY);
extern void HSTransformCoord_180(u16 *pX,u16 *pY);
extern void HSTransformCoord_270(u16 *pX,u16 *pY);
//===========�����Ӳ��=====����ת��=======================
extern void SHTransformCoord_0(u16 *pX,u16 *pY);
extern void SHTransformCoord_90(u16 *pX,u16 *pY);
extern void SHTransformCoord_180(u16 *pX,u16 *pY);
extern void SHTransformCoord_270(u16 *pX,u16 *pY);

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
extern void fb_ui_get_rect(int x, int y, int w, int h,A_RGB* pArgb);
extern void fb_ui_xor_rect(int x, int y, int w, int h,A_RGB* pArgb);
extern int fb_GetScreenSize(int *pWidth,int *pHeight,RECTL* pUI) ;
extern A_RGB* xui_fb_GetScreenMsg(RECTL* pRect,int *pLineWidth);
extern void xui_fb_pull(RECTL* pRect,A_RGB* pOutRGB);
extern void xui_fb_push(RECTL* pRect,A_RGB* pInRGB);

extern void xui_fb_syn(void);
extern void xui_window_push(XuiWindow *window,RECTL* pRect,A_RGB* pInrgb);



#endif /*LINUX_FB_H*/
