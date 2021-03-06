#include "comm_type.h"
#include "sm4.h"
//#include "communal.h"


// 单次操作的长度
#define UNIT_LEN		16

// 加密
#define SM4_ENCRYPT			0
// 解密
#define SM4_DISCRYPT		1

// 循环左移n位
#define CycleLShift(udwData, n)		((udwData << n) | (udwData >> (32 - n)))
// 轮换算法线性变换
#define RotLineTran(udwInput)		(udwInput ^ CycleLShift(udwInput, 2) ^ CycleLShift(udwInput, 10) ^ CycleLShift(udwInput, 18) ^ CycleLShift(udwInput, 24))
// 轮函数F
#define RoundF(X0)					((X0) ^ RotLineTran(udwTran))		
// 密钥扩展线性变换
#define KeySpanLineTran(udwInput)	(udwInput ^ CycleLShift(udwInput, 13) ^ CycleLShift(udwInput, 23))

// 子密钥个数
#define SUBKEY_NUM		32

// sbox
static const u8 uczSbox[] = {
	0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7, 0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05,
	0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3, 0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
	0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a, 0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62,
	0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95, 0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6,
	0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba, 0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8,
	0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b, 0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35,
	0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2, 0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87,
	0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52, 0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e,
	0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5, 0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1,
	0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55, 0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3,
	0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60, 0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f,
	0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f, 0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51,
	0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f, 0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8,
	0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd, 0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0,
	0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e, 0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84,
	0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20, 0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48
	};

// 系统参数FK
static const u32 udwSysParamsFK[] = {
	0xA3B1BAC6, 0x56AA3350, 0x677D9197, 0xB27022DC
	};

// 固定参数CK(CKij = (4 * i + j * 7) mod 256)
static const u32 udwConstParamsCK[] = {
	0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
	0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
	0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
	0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
	0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
	0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
	0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
	0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
	};

void sm4_memcpy(u32 *u1,u32 *u2,u32 len)
{
	while(len--)
		*u1++ = *u2++;
}

void sm4_memset(u32 *u1,u32 nun,u32 len)
{
	while(len--)
		*u1++ = nun;
}

// 非线性变换（S盒变换）
static u32 NonlineTran(u32 udwInput)
{
	u8* pucInput = (u8*)&udwInput;
	int i;

	for(i = 0; i < 4; i++)
	{
		pucInput[i] = uczSbox[pucInput[i]];
	}

	return udwInput;
}

// 字节序变换
static void TranByteorder(u32 udwData, u8* pucData)
{
	*pucData++ = (u8)(udwData >> 24);
	*pucData++ = (u8)((udwData >> 16) & 0xff);
	*pucData++ = (u8)((udwData >> 8) & 0xff);
	*pucData++ = (u8)(udwData & 0xff);
}

// 密钥扩展为子密钥
static void ExpaToSubKey(u32* pucKey,u32* pudwSubKey)
{
	u32 udwTemK[SUBKEY_NUM + 4];
	int i;
	u32 udwTran;

	for(i = 0; i < 4; i++)
	{
		TranByteorder(pucKey[i], (u8*)(udwTemK + i));
		udwTemK[i] ^= udwSysParamsFK[i];
	}
	for(i = 0; i < SUBKEY_NUM; i++)
	{
		udwTran = NonlineTran(udwTemK[i + 1] ^ udwTemK[i + 2] ^ udwTemK[i + 3] ^ udwConstParamsCK[i]);
		udwTemK[i + 4] = udwTemK[i] ^ KeySpanLineTran(udwTran);
	}
	sm4_memcpy(pudwSubKey, udwTemK + 4, SUBKEY_NUM);
	sm4_memset(udwTemK, 0, sizeof(udwTemK)/4);
}

// 单次操作算法
static void Sm4Unit(u32* puwInputtext, u8* pucOutputtext, u8 uOpType,u32* pudwSubKey)
{
	int i;
	u32 udwTemText[SUBKEY_NUM + 4];
	u32 udwTran;

	sm4_memcpy(udwTemText, puwInputtext,4);
	if(SM4_ENCRYPT == uOpType)
	{
		// 加密
		for(i = 0; i < SUBKEY_NUM; i++)
		{
			udwTran = NonlineTran(udwTemText[i + 1] ^ udwTemText[i + 2] ^ udwTemText[i + 3] ^ pudwSubKey[i]);
			udwTemText[i + 4] = RoundF(udwTemText[i]);
		}
	}
	else
	{
		// 解密
		for(i = 0; i < SUBKEY_NUM; i++)
		{
			udwTran = NonlineTran(udwTemText[i + 1] ^ udwTemText[i + 2] ^ udwTemText[i + 3] ^ pudwSubKey[SUBKEY_NUM - 1 - i]);
			udwTemText[i + 4] = RoundF(udwTemText[i]);
		}
	}
	// 输出
	for(i = 0; i < 4; i++)
	{
		TranByteorder(udwTemText[SUBKEY_NUM + 3 - i], pucOutputtext + (i << 2));
	}
}

// SM4处理接口
static int Sm4EncOrDes(u8 *key ,u8 *pInBuff ,int InLen,u8 *pOutBuff,u8 mOpType)
{
	int	uLoop;
	u32 pudwInput[4],udwInputText[4];
	u32 udwSubKeyRam[SUBKEY_NUM]; // 子密钥
	InLen=InLen&(~(UNIT_LEN-1)); //取整数倍以内的数
	memcpy(pudwInput, key, sizeof(pudwInput));
	ExpaToSubKey(pudwInput,udwSubKeyRam);
	for(uLoop=0;uLoop < InLen;uLoop += UNIT_LEN)
	{
	/*
		memcpy(pudwInput, pInBuff + uLoop, UNIT_LEN);
		TranByteorder(pudwInput[0], (u8*)&udwInputText[0]);
		TranByteorder(pudwInput[1], (u8*)&udwInputText[1]);
		TranByteorder(pudwInput[2], (u8*)&udwInputText[2]);
		TranByteorder(pudwInput[3], (u8*)&udwInputText[3]);
		*/
		udwInputText[0]=BYTE4_TO_INT(pInBuff); pInBuff+=4;
		udwInputText[1]=BYTE4_TO_INT(pInBuff); pInBuff+=4;
		udwInputText[2]=BYTE4_TO_INT(pInBuff); pInBuff+=4;
		udwInputText[3]=BYTE4_TO_INT(pInBuff); pInBuff+=4;
		Sm4Unit(udwInputText, pOutBuff + uLoop, mOpType,udwSubKeyRam);
	}
	return InLen;
}

//=====国密对称解密算法=====================
//----Buff 输入输出数据指针
//----Key 密钥指针
//----key_number 数据密钥倍长(16倍)
int API_SM4_ENC(u8 *pInBuff,int Inlen,u8 *pOutBuff,u8 *key )
{
	return Sm4EncOrDes(key,pInBuff,Inlen,pOutBuff,SM4_ENCRYPT);
}

int API_SM4_DEC(u8 *pInBuff,int Inlen,u8 *pOutBuff,u8 *key )
{
	return Sm4EncOrDes(key,pInBuff,Inlen,pOutBuff,SM4_DISCRYPT);
}


