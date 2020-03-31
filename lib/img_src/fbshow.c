/**
 * File:   fbshow.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  snap framebuffer to png file
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

#include "linux_fb.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

void u32coy(void *u1,void *u2)
{
	*(unsigned long *)u1 = *(unsigned long *)u2;
}


int main(int argc, char* argv[]) {
  fb_info_t* fb = NULL;
  const char* filename = NULL;
  const char* fbfilename = NULL;

  if (argc != 3) {
    printf("\nUsage: %s outputfilename [framebuffer dev]\n", argv[0]);
    printf("Example: %s data/rgba.png /dev/fb0\n", argv[0]);
    printf("-----------------------------------------\n");

    return 0;
  }

  filename = argv[1];
  fbfilename = argv[2];

  fb = linux_fb_open(fbfilename);
  if (fb != NULL) {
    bitmap_t* pbin = bitmap_load(filename);
    if (pbin != NULL) {
		bitmap_t* p12 = bitmap_load("./data/2412.png");
		printf("frombitmap w[%d],h[%d]\n",pbin->w,pbin->h);
		if(p12)
		{
			printf("frombitmap p12 w[%d],h[%d]\n",p12->w,p12->h);
		}
		linux_fb_from_bitmap(fb, pbin);
		sleep(2);
		{
			int index;
			signed short xi,xmax,yi,ymax;
			signed short rr1,gg1,bb1,rr2,gg2,bb2;
			uint8_t xc,yc;
			rgba_t b2,b3,b4,bshow;
			bitmap_t mb;
			
			xmax = pbin->w-1;
			ymax = pbin->h-1;
			mb.data=(rgba_t*)malloc(xmax*ymax*sizeof(rgba_t));
			
			for(yi=0;yi<ymax;yi++)
			{
				for(xi=0;xi<xmax;xi++)
				{
					u32coy(&b2,&pbin->data[yi*pbin->w+xi+1]);
					u32coy(&b3,&pbin->data[(yi+1)*pbin->w+xi]);
					u32coy(&b4,&pbin->data[(yi+1)*pbin->w+xi+1]);
				
					rr1 = b4.r-b2.r;
					gg1 = b4.g-b2.g;
					bb1 = b4.b-b2.b;

					rr2 = b4.r-b3.r;
					gg2 = b4.g-b3.g;
					bb2 = b4.b-b3.b;

					bshow.r = (rr1 + bb2)+0x7f;
					bshow.g = (gg1 + rr2)+0x7f;
					bshow.b = (bb1 + gg2)+0x7f;
					bshow.a = 0xff;

					
					//mb.data[yi*xmax+xi]=b4;
					u32coy(&mb.data[yi*xmax+xi],&bshow);
					
				}
			}

			mb.w = xi;
			mb.h = yi;
			linux_fb_from_bitmap(fb,&mb);
			sleep(3);
			bitmap_save(&mb, "./data/guo.png");
			//xc=0x3f;
			for(yi=0;yi<ymax;yi++)
			{
				for(xi=0;xi<xmax;xi++)
				{
					mb.data[yi*xmax+xi].r=0;
					mb.data[yi*xmax+xi].g=0;
					if(mb.data[yi*xmax+xi].b > (0x7f+0x30)) 
						mb.data[yi*xmax+xi].r = 0xff;
					else if(mb.data[yi*xmax+xi].b > (0x7f+0x20)) 
						mb.data[yi*xmax+xi].r = 0x7f;
					else if(mb.data[yi*xmax+xi].b > (0x7f+0x10)) 
						mb.data[yi*xmax+xi].r = 0x3f;
					
					if(mb.data[yi*xmax+xi].b < (0x7f-0x30)) 
						mb.data[yi*xmax+xi].g = 0xff;
					else if(mb.data[yi*xmax+xi].b < (0x7f-0x20)) 
						mb.data[yi*xmax+xi].g = 0x7f;
					else if(mb.data[yi*xmax+xi].b < (0x7f-0x10)) 
						mb.data[yi*xmax+xi].g = 0x3f;

					u32coy(&b4,&p12->data[(yi%12)*24+(xi%24)]);	
					if(b4.r > 0x7f) mb.data[yi*xmax+xi].b=0;
				}
			}
			/*
			yc=0x3f;
			for(xi=0;xi<xmax;xi++)
			{
				for(yi=0;yi<ymax;yi++)
				{
					if(mb.data[yi*xmax+xi].b > (0x7f+0x20)) yc = 0xff;
					else if(mb.data[yi*xmax+xi].b < (0x7f-0x20)) yc = 0x00;
					else yc = 0x7f;
					mb.data[yi*xmax+xi].b=0;
					if(mb.data[yi*xmax+xi].g != yc)
						mb.data[yi*xmax+xi].g = yc;
				}
			}
			*/
			linux_fb_from_bitmap(fb,&mb);
			sleep(3);
			bitmap_save(&mb, "./data/guo1.png");


			memset(mb.data,0xff,xmax*ymax*sizeof(rgba_t));
			{
				double sci,scMax,reX,reY;
				unsigned short jdi,jdm;
				int scxy;
				for(jdi=0;jdi<360;jdi++)
				{
					sci = M_PI*jdi/180;
					reX=sin(sci);
					reY=cos(sci);
					xi=110+ reX*100;
					yi=110+ reY*100;

					scxy=yi*xmax+xi;
					//printf("sin reX[%d,%d]\n",xi,yi);
					mb.data[scxy].r=0;
					mb.data[scxy].g=0;
					mb.data[scxy].b=0;


				}
				/*
				scMax=M_PI*2;
				for(sci=0;sci<scMax;sci+=0.01)
				{
					int scxy;
					reX=sin(sci);
					reY=cos(sci);
					xi=110+ reX*100;
					yi=110+ reY*100;

					scxy=yi*xmax+xi;
					//printf("sin reX[%d,%d]\n",xi,yi);
					mb.data[scxy].r=0;
					mb.data[scxy].g=0;
					mb.data[scxy].b=0;
				}*/
				//printf("frombitmap sin reX[%f],reY[%f]M_PI[%f]\n",sin((double)30/180*M_PI),sin(M_PI),M_PI);
			 //double sin(double x);
			//double cos(double x);

			}
			linux_fb_from_bitmap(fb,&mb);
			sleep(3);
			
		/*
			for(yi=0;yi<ymax;yi++)
			{
				for(xi=0;xi<xmax;xi++)
				{
					index=(yi+1) * pbin->w + xi+1;
					if(mb.data[yi*xmax+xi].r == 0xff)
						pbin->data[index].r=0xff;
					if(mb.data[yi*xmax+xi].g == 0xff)
						pbin->data[index].g=0xff;
				}
			}
			printf("frombitmap---rr1[%d]\n",rr1);
			linux_fb_from_bitmap(fb,pbin);
			*/
			free(mb.data);
		}
		bitmap_destroy(pbin);
    }
//	sleep(10);
    linux_fb_close(fb);
  }

  return 0;
}
