#ifndef __SM4_H_
#define __SM4_H_

#include <string.h>

typedef unsigned char   		u8;		//!< Define u8
typedef unsigned short   		u16;		//!< Define u8
typedef unsigned int			u32;	//!< Define u32
#define		BYTE4_TO_INT(buf)	(buf[0]*0x1000000+buf[1]*0x10000+buf[2]*0x100+buf[3])
#define 	TRACE 	printf


// 加解密接口, 允许输入缓冲与输出缓冲复用
extern int API_SM4_ENC(u8 *pInBuff,int Inlen,u8 *pOutBuff,u8 *key );
extern int API_SM4_DEC(u8 *pInBuff,int Inlen,u8 *pOutBuff,u8 *key );

#endif
