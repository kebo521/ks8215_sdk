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

#ifndef SDK_FONT_H
#define SDK_FONT_H




//========================��ʾ��Դ(�ֿ�)==================================================
typedef struct
{
	u32		ParLen;      			//��Դ���ݳ���
	u32		Offset;      		//��Դ����ƫ�Ƶ�ַ
}tFont_OFS;	

typedef struct
{
	u16 reqLen_en;
	u16 reqLen_ch;
}tFont_Len;	

typedef struct
{
	tFont_Len	resFd;
	tFont_OFS	fn[6];	//en+hz1+hz2+hz3+hz4+hz5
	tFont_OFS	gbk;
	tFont_OFS	ucode;
	u8			pbFont[0];
}RES_table;

typedef struct{
	u8 Direction;	//������ʾ����,XuiTransform
	u8 h,w;	
	u8 lineLen;	//pFontBit����=lineLen*h
	u8 *pFontBit;
}FontbitMsg;

typedef struct{
	u8 Direction;	//������ʾ����
	u8 h;		//�����
	u8 Cw,Ew;	//���Ŀ�Ӣ�Ŀ�
	int (*GetEnAddr)(RES_table *,u8);	//(u8 En)
	int (*GetGbkChnAddr)(RES_table *,u8,u8);	//(u8 hv,u8 lv)
	RES_table res;	//�ɱ䳤�����������
}tSdkFont;



extern tSdkFont *Font_Create(char *fontfile);
extern void Font_Destroy(tSdkFont *font);


extern int Font_GetBitMap(tSdkFont *pFont,u8* pInChar,FontbitMsg *pOutMsg);




#endif /*LINUX_FB_H*/
