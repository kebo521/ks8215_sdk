/**
 * File:   bitmap.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  bitmap
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

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "comm_type.h"
#include "xui_ui.h"
#include "bitmap.h"
#include "stb_image.h"
#include "stb_image_write.h"

bitmap_t* bitmap_create(uint32_t w, uint32_t h) {
  uint32_t size = 0;
  bitmap_t* b = (bitmap_t*)calloc(1, sizeof(bitmap_t));

  b->w = w;
  b->h = h;
  size = w * h * sizeof(XuiColor);

  b->data = (XuiColor*)malloc(size);
  memset(b->data, 0xff, size);

  return b;
}

ret_t bitmap_save(bitmap_t* b, const char* filename) {
	char *p;
	if(b == NULL || b->data == NULL || filename == NULL)
		return RET_BAD_PARAMS;
	p=(char*)filename;
	while(*p) p++;
	while((*p != '.') && (p> filename)) p--;
	if(*p == '.') 
	{
		p++;
		if(strstr(p,"bmp"))
		   stbi_write_bmp(filename, b->w, b->h, 4, b->data);
		else if(strstr(p,"png"))
		   stbi_write_png(filename, b->w, b->h, 4, b->data, 0);
		else if(strstr(p,"jpg")!=NULL || strstr(p,"jpeg")!=NULL)
		   stbi_write_jpg(filename, b->w, b->h, 4, b->data, 0);
		else if(strstr(p,"tga"))
		   stbi_write_tga(filename, b->w, b->h, 4, b->data);
		else return RET_BAD_PARAMS;
		return RET_OK;
	}
	return RET_BAD_PARAMS;
}

ret_t bitmap_init_from_data(bitmap_t* b, uint32_t w, uint32_t h, const uint8_t* data,uint32_t comp) 
{
    uint32_t n = w * h;
    register uint8_t* s = (uint8_t *)data;
    register XuiColor* d = b->data;
	if (comp == 4)
	{
		while(n--) 
		{
			d->r = *s++;
			d->g = *s++;
			d->b = *s++;
			d->a = *s++;
			d++;
		}
	}
	else
	{
		while(n--) 
		{
			d->r = *s++;
			d->g = *s++;
			d->b = *s++;
			d->a = 0xFF;
			d++;
		}
	}
	return RET_OK;
}

bitmap_t* bitmap_load(const char* filename) {
	  int w = 0;  
	  int h = 0;  
	  int n = 0;  
	  bitmap_t* b = NULL;  
	  uint8_t* data = NULL;  
	  data = stbi_load(filename, &w, &h, &n, 0);
	  if(data == NULL) return NULL;
	  b = bitmap_create(w, h);  
	  if (b != NULL) {    bitmap_init_from_data(b, w, h, data, n);  }  
	  stbi_image_free((uint8_t*)(data));  
	  return b;
}

ret_t bitmap_get(bitmap_t* b, uint32_t x, uint32_t y, XuiColor* rgba) {
	if(x < b->w && y < b->h)
	{
		*rgba = b->data[b->w * y + x];
		return RET_OK;
	}
  	return RET_BAD_PARAMS;
}

ret_t bitmap_set(bitmap_t* b, uint32_t x, uint32_t y, const XuiColor* rgba) {
	if(x < b->w && y < b->h)
	{
		b->data[b->w * y + x] = *rgba;
		return RET_OK;
	}
	return RET_BAD_PARAMS;
}

ret_t bitmap_destroy(bitmap_t* b) {
	if(b)
	{
		if(b->data)
		{
			free(b->data);
			b->data=NULL;
		}
		free(b);
	}
  	return RET_OK;
}
