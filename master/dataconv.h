#ifndef	__DATACONV_H__
#define	__DATACONV_H__

	//=======���Json��������===========
	typedef enum
	{	
		ITEM_FALSE,
		ITEM_TRUE,
		ITEM_NULL,
		ITEM_INT,
		ITEM_STRING,
		ITEM_STRUCT,
		ITEM_ARRAY,
	}JSON_ITEM_TYPE;

	typedef struct
	{
		char	*pkey;
		void	*pValue;
		u16		dType,vaNum;
	}dfJsonItem;

	typedef struct _dfJsonTable
	{
		struct _dfJsonTable *pNext;
		u16			sLen,Total;
		dfJsonItem	Item[1];
	}dfJsonTable;

	//=======����Json��������===========
	//#include  "type.h"
	//#include  "string.h"
	//	write your header here
	//	Hex����ת����Ӧ�ַ�
						
	//	�ַ�ת����ӦHex����
	//	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
	extern u8 Conv_CharToNum(char c);
			
	//  �ַ���ת��BCD�룬BCD�������
	//	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
	//	Conv_StrToBcd("12345",5,bcd);	
	//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	extern void Conv_StrToBcd_Left(char* str,s16 API_strlen,u8* bcd);
	
	//  �ַ���ת��BCD�룬BCD���Ҷ���
	//	bcd	="\x00\x00\x00\x00\x00\x00\x00";
	//	Conv_StrToBcd_Right("12345",5,bcd,7);	
	//	bcd	="\x00\x00\x00\x00\x01\x23\x45F";
	extern void Conv_StrToBcd_Right(char* str,s16 slen,u8 *bcd,s16 blen);
	
	//  BCD��ת���ַ���
	//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
	//	Conv_BcdToStr(bcd,4,str);	
	//	str	="12345FFF";
	extern void Conv_BcdToStr(u8* bcd,s16 blen,char* str);
	//HEXת���ַ���
	//���ֻ��ת5λ
	
	extern int Conv_IsHexChar(char b);
	extern u8 Conv_HexToBcd(u8 Hex);
	extern u8 Conv_BcdToHex(u8 Bcd);
	extern int Conv_StrToLong(char* number);
//	extern void Conv_FomartByteStr(u8 *s,u8 len);
	extern u32 Conv_StrToNum(u8* strbuf,u8 Inlen);
	extern void Conv_NumToStrRight(u32 InNum,u8 Outlen,u8* OutBuf);
	extern void Conv_NumToStrLeft(u32 InNum,u8* OutBuf);
	extern int Conv_MoneyToCentInt(char* pInstr);
	extern int Conv_DmoneyToTmoney(char* pOutStr,char* pInsMoney);
	extern int Conv_TmoneyToDmoney(char* pOutdMoney,char* pIntMoney);
	extern void Conv_UpperToLowercase(char* pBuff,int Len);
	extern void ArrayStringGroup(const char* pStringGroup[],u16 MaxNum,u16 *pArrayIndexTable);
	extern char *Conv_SetPackageHttpPOST(char* pPostStr,char* pPostID,char *pInData);
	extern char *Conv_SetPackageHttpGET(char* pGetStr,char* pPostID,char *pInData);
	extern char *Conv_Strcpy(char* pOut,const char* pIn);
	extern void Conv_U32memcpy(u32* pOut,u32* pIn,int len);

	//extern char* tRChar(const char* pfPath, const char cDim);
	extern u8 Conv_HttpGetName(char* pOutName,const char* pInAddre);
	extern char* Conv_HttpPost_SetHead(char * url,char *pBuffOut);
	extern char* Conv_HttpPost_SetData(char *param, char *pBuffOut);	
	//====================���JSON����======================================
	extern dfJsonTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd);
	extern char* Conv_GetJsonValue(dfJsonTable *pStart,char* pKey,u8 *pType); //===����pKey ֧�ֶ༶����ʣ���'/'�������� "abc/efg/hij"==========
	extern void Conv_JSON_free(dfJsonTable *pTable);
	//===========================================================================

#endif
