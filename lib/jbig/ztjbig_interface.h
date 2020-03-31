#ifndef __ztjbig_interface_h_2014_11_24___fq___
#define __ztjbig_interface_h_2014_11_24___fq___


#define IOC_PRINTER_MAGIC  'B'
#define LP_GET_PAPER_STATE        	_IO(IOC_PRINTER_MAGIC, 10)
#define LP_GET_STATUS       	_IO(IOC_PRINTER_MAGIC, 11)
#define LP_SET_MOTO  				_IO(IOC_PRINTER_MAGIC, 12)
#define LP_SET_SPEED  					_IO(IOC_PRINTER_MAGIC, 14)
#define LP_SET_GRAY  					_IO(IOC_PRINTER_MAGIC, 15)
#define LP_SET_HEATTYPE	    		_IO(IOC_PRINTER_MAGIC, 16)
#define LP_SET_START_STEP				_IO(IOC_PRINTER_MAGIC, 17)
#define LP_SET_STOP_STEP				_IO(IOC_PRINTER_MAGIC, 18)

#define LP_SPEED_LOW	0x0
#define LP_SPEED_MIDDLE 0x1
#define LP_SPEED_HIGH	0x2

#define LCDDEV 					"/dev/fb0"
#define ZTLCD_OPENERROR 		-1
#define ZTLCD_FVINFOERROR 		-2
#define ZTLCD_OPEN_BINFAILED 	-3
#define ENBUFF_SIZE 153600

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;

#pragma pack (1)


typedef struct tagBITMAPFILEHEADER
{

	U16 bfType;
	U32 bfSize;
	U16 bfReserved1;
	U16 bfReserved2;
	U32 bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	U32 biSize;
	U32 biWidth;
	U32 biHeight;
	U16 biPlanes;
	U16 biBitCount;
	U32 biCompression;
	U32 biSizeImage;
	U32 biXPelsPerMeter;
	U32 biYPelsPerMeter;
	U32 biClrUsed;
	U32 biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagOLD
{
	U32 abc;
	U32 bcd;
} OLD;

typedef struct tagRGBQUAD
{
	U8 rgbBlue;
	U8 rgbGreen;
	U8 rgbRed;
	U8 rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER bmiHeader;
	OLD bmiold;
	RGBQUAD bmiColors[1];
} BITMAPINFO;


typedef struct tagBITMAP
{
	BITMAPFILEHEADER bfHeader;
	BITMAPINFO biInfo;
}BITMAPFILE;




extern int ztjbig_enc(unsigned char **orig_image, int width, int height, 
	unsigned char *jbigbuf, int *jbigln);

extern int ztjbig_dec(char *fjbig, unsigned char *bmpbuf, int *width, int *height);

extern int ztjbig_bmptojbg(char *pbmp, int w, int h, char *jbgbuf, int *jbgln);

extern int ztjbig_jbgtopbm(char *pi_fjbg, char *po_pbm, int * width,int * height);

extern int ztjbig_sprint(int w, int h, char *buf, int imd);

extern int ztjbig_fbshot(int isx, int isy, int iex, int iey, char *buf);

extern int ztjbig_prtojbig(char *pi_fjbig);

extern int ztjbig_genbmp(char* pi_buf, int w, int h, char *pi_fname);

extern int ztjbig_getbmpData(char *pi_buf, int iw, int ih, char *po_bmp, int *oh);
extern void ztjbig_compose(int imgw, int imgh, char *img, char *buf, char *comimg);
extern int ztjbig_getPrintdata(int w, int h, char *buf, int imd, char*obuf, int *oln);



#endif

