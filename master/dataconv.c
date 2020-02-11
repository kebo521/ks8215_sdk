//===================================================================
//-------------------数据转换,打包服务------------------------------
//===================================================================
#include "comm_type.h"
#include "sys_sdk.h"
#include "tls_sdk.h"

#include "dataconv.h"
#include "app_sdk.h"



//	Hex数字转成相应字符
//	0x0-0x9='0'-'9'   0xA-0xF='A'-'F'  其它=' '
const char BcdToAsicCode[16]={"0123456789ABCDEF"};
//	字符转成相应Hex数字
//	'0'-'9'=0x0-0x9  'a'-'f'=0xA-0xF	'A'-'F'=0xA-0xF
u8 Conv_CharToNum(char c)		
{
	if (c>='0' && c<='9')
	{
		return (c-'0');
	}
	else if(c>='a' && c<='f')
	{
		return (c-'a'+10);
	}
	else if(c>='A' && c<='F')
	{
		return (c-'A'+10);
	}
	else return 0;
}

//  字符串转成BCD码，BCD码左对齐
//	bcd	="\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
//	Conv_StrToBcd("12345",5,bcd);	
//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";

void Conv_StrToBcd_Left(char* str,s16 slen,u8* bcd)
{
	u8	c;
	u8	b;
	s16		i=0;
	s16		j=0;
	//TRACE_HEX("Conv_StrToBcd_Left:str",str,API_strlen);
	for(i=0;i<slen;i++)
	{
		c=Conv_CharToNum((char)str[i]);
		b=bcd[j];
		if (i%2) //Right
		{
			b&=0xF0;
			b|=c;
			bcd[j++]=b;
		}else
		{
			b&=0x0F;
			b|=(c<<4);
			bcd[j]=b;
		}
	}
}

//  字符串转成BCD码，BCD码右对齐
//	bcd	="\x00\x00\x00\x00\x00\x00\x00";
//	Conv_StrToBcd_Right("12345",5,bcd,7);	
//	bcd	="\x00\x00\x00\x00\x01\x23\x45F";


void Conv_StrToBcd_Right(char* str,s16 slen,u8 *bcd,s16 blen)
{
	u8 a,b;
	while (slen>0) 
	{
		b=Conv_CharToNum(str[--slen]);
		if(slen<1)
			a=bcd[blen-1]/16;	
		else
			a=Conv_CharToNum(str[--slen]);
		bcd[--blen]=a*16+b;
	}
}

//  BCD码转成字符串
//	bcd	="\x12\x34\x5F\xFF\xFF\xFF\xFF";
//	Conv_BcdToStr(bcd,4,str);	
//	str	="12345FFF";
void Conv_BcdToStr(u8* bcd,s16 blen,char* str)
{
	s16		i=0;
	s16		j=0;

	for(i=0;i<blen;i++)
	{
		str[j++]=BcdToAsicCode[bcd[i]/16];	//取高4位
		str[j++]=BcdToAsicCode[bcd[i]&0x0f]; //取低4位
	}
	str[j++]=0;
}


int Conv_IsHexChar(char b)
{
	return ((b>='0'&&b<='9')||(b>='a'&&b<='f')||(b>='A'&&b<='F'))?TRUE:FALSE;
}

int Conv_StrToLong(char* number)
{
   u8 		neg = 0;
   int   	n = 0;

   while (*number <= ' ' && *number > 0)
      ++number;
   if (*number == '-')
   {
      neg = 1;
      ++number;
   }
   else if (*number == '+')
      ++number;
   while (*number>='0' && *number<='9')
      n = (n * 10) + ((*number++) - '0');
   return (neg ? -n : n);
}
//单字节Hex转成BCD形式
u8 Conv_HexToBcd(u8 Hex)
{
	u8 a,b;
	u8 Bcd;
	if(Hex>99)
	{
		return 0;
	}
	else
	{
		a=(Hex/10)&0x0f;
		b=(Hex%10)&0x0f;
		Bcd=a<<4|b;
		return Bcd;
	}

}
u8 Conv_BcdToHex(u8 Bcd)
{
	u8 a,b;
	a=(Bcd>>4)&0x0f;
	b=Bcd&0x0f;
	return (a*10+b)&0xff;
}

//-------------Guozu add---20110523---------------------
u32 Conv_StrToNum(u8* strbuf,u8 Inlen)
{
	u8 i;
	u32 buffhex=0;
	for(i=0;i<Inlen;i++)
	{
		buffhex *=10;
		buffhex +=(strbuf[i]-'0');
	}
	return buffhex;
}
void Conv_NumToStrRight(u32 InNum,u8 Outlen,u8* OutBuf)
{
	while(Outlen--)
	{
		OutBuf[Outlen]=InNum%10+'0';
		InNum /=10;
	}
}

void Conv_NumToStrLeft(u32 InNum,u8* OutBuf)
{
	u8 buff[12],Len=0;
	while(InNum)
	{
		buff[11-Len]=InNum%10+'0';
		InNum /=10;
		Len++;
	}
	API_memcpy(OutBuf,&buff[12-Len],Len);
	OutBuf[Len]=0x00;
}

//================检查并获得金额以分为单位的数值=====================
int Conv_MoneyToCentInt(char* pInstr)
{
	int Integers;
	u8 i,IntNum,j,Inlen;
	//------金额数据有效性检查----------
	Inlen=API_strlen(pInstr);
	if(Inlen>1)
	{//------两位以上判断----------
		if(pInstr[0]=='0' && pInstr[1]!='.')
			return -1;
	}
	for(IntNum=0;IntNum<Inlen;IntNum++)
		if(pInstr[IntNum]=='.') break;
	//-------小数点后不能超过两位--------
	if((Inlen-IntNum) > 3)
		return -2;
	//------小数点后不能再有小数点------
	for(j=IntNum+1;j<Inlen;j++)
	{
		if(pInstr[j]=='.') 
			return -3;
	}
	Integers=0;
	for(j=0;j<IntNum;j++)
		Integers=Integers*10 + (pInstr[j]&0x0f);
	IntNum++;
	for(i=0;i<2;i++)
	{
		Integers *= 10;
		if((i+IntNum) < Inlen)
			Integers += pInstr[IntNum+i]&0x0f;
	}
	return Integers;
}

//------------------显示金额 转 交易金额-------------------------------
int Conv_DmoneyToTmoney(char* pOutStr,char* pInsMoney)
{
	u8 i,j,k;
	u8 Inlen=API_strlen(pInsMoney);
	for(i=0;i<Inlen;i++)
		if(pInsMoney[i]=='.') break;
	//----整数部分------
	for(j=0;j<i;j++)
		pOutStr[j]=pInsMoney[j];
	//---小数部分精确两位----
	if(i<Inlen)	//有小数点
	{
		for(i=0; i<2; i++)
		{
			if((j+1) < Inlen)
				pOutStr[j]=pInsMoney[j+1];
			else
				pOutStr[j]='0';
			j++;
		}
	}
	else	//无小数点,两位0
	{
		pOutStr[j++]='0';
		pOutStr[j++]='0';
	}
	//---过滤无效位------
	for(i=0; i<j; i++)
		if(pOutStr[i]!='0')
			break;
	if(i)
	{
		k=j-i;
		for(j=0;j<k;j++)
			pOutStr[j]=pOutStr[j+i];
	}
	pOutStr[j]='\0';
	return j;
}

//------------------交易金额 转 显示金额-------------------------------
int Conv_TmoneyToDmoney(char* pOutdMoney,char* pIntMoney)
{
	u16 i=0,Inlen=API_strlen(pIntMoney);
	if(Inlen == 0)
	{
		pOutdMoney[0]='\0';
		return 0;
	}
	if(Inlen <= 2)
	{
		pOutdMoney[i++]='0';
		pOutdMoney[i++]='.';
		if(Inlen < 2)
			pOutdMoney[i++]='0';
		else
			pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}
	else
	{
		Inlen -= 2;
		while(i<Inlen)
		{
			pOutdMoney[i++]=*pIntMoney++;
		}
		pOutdMoney[i++]='.';
		pOutdMoney[i++]=*pIntMoney++;
		pOutdMoney[i++]=*pIntMoney++;
	}

	while(i--)	//去掉无效参数
	{
		if(pOutdMoney[i] == '.')
		{
			i--;
			break;
		}
		else if(pOutdMoney[i] != '0') 
			break;
	}
	pOutdMoney[++i]='\0';
	return i;
}


//===========统一转小写字符串Buff============================
void Conv_UpperToLowercase(char* pBuff,int Len)
{
	int i;
	for(i=0;i<Len;i++)
	{
		pBuff[i] |= 0x20;
	}
}


//===========用于POST打包方式数据============================
char *Conv_SetPackageHttpPOST(char* pPostStr,char* pPostID,char *pInData)
{
	int sIDlen,DataLen;
	*pPostStr++ ='<';
	sIDlen=API_strlen(pPostID);
	API_memcpy(pPostStr,pPostID,sIDlen);
	pPostStr += sIDlen;
	*pPostStr++ ='>';
	DataLen=API_strlen(pInData);
	API_memcpy(pPostStr,pInData,DataLen);
	pPostStr += DataLen;
	*pPostStr++ ='<';
	*pPostStr++ ='/';
	API_memcpy(pPostStr,pPostID,sIDlen);
	pPostStr += sIDlen;
	*pPostStr++ ='>';
	return pPostStr;
}


//========拷贝pPostID=pInData到pGetStr并返回pGetStr的末地址========
char *Conv_SetPackageHttpGET(char* pGetStr,char* pPostID,char *pInData)
{
	int sIDlen,DataLen;
	sIDlen=API_strlen(pPostID);
	API_memcpy(pGetStr,pPostID,sIDlen);
	pGetStr += sIDlen;
	*pGetStr++ ='=';
	DataLen=API_strlen(pInData);
	API_memcpy(pGetStr,pInData,DataLen);
	pGetStr += DataLen;
	return pGetStr;
}

//========拷贝pIn到pOut并返回pOut的末地址,以'\0'做结束========
char *Conv_Strcpy(char* pOut,const char* pIn)
{
	while(*pIn)
	{
		*pOut++ = *pIn++;
	}
	*pOut='\0';
	return pOut;
}

void Conv_U32memcpy(u32* pOut,u32* pIn,int len)
{
	while(len--)
	{
		*pOut++ = *pIn++;
	}
}



char* tRChar(char* pfPath, const char cDim)
{
    int len = API_strlen(pfPath);
    int loop = 0;

    for (loop = len; loop > 0; loop--)
    {
        if (pfPath[loop] == cDim)
        {
            return &(pfPath[loop+1]);
        }
    }
    return pfPath;
}

u8 Conv_HttpGetName(char* pOutName,const char* pInAddre)
{
	u8 sslEn=0;
	char *pStr;
	pStr=API_eStrstr((char*)pInAddre,"//");
	if(pStr)
	{
		while(*pStr)
		{
			*pOutName = *pStr;
			if(*pOutName == '/')
				break;
			pOutName++;pStr++;
		}
		*pOutName='\0';

		if(API_strstr(pInAddre,"https"))	//https
			sslEn= 1;
	}
	else	//IP 地址
	{
		API_strcpy(pOutName,pInAddre);
	}
	return sslEn;
}


void twebGetHostGET(const char *url, char *server, char *GET, char *file)
{
	char myurl[256] = {0};
	char *pHost = NULL;
	char *temp = NULL;

	API_strcpy(myurl, url);
	
	if(file) API_strcpy(file, tRChar((char *)url, '/'));   //分离文件名
	temp = API_eStrstr(myurl, "http://");
	if(temp==NULL)
	{
		temp = API_eStrstr(myurl, "https://");
		if(temp==NULL) temp = myurl;
	}
	for (pHost = temp; *pHost != '/' && *pHost != '\0'; ++pHost);
	if ((int)(pHost - myurl) == API_strlen(myurl))
		API_strcpy(GET, "/");
	else
		API_strcpy(GET, pHost);
	*pHost = '\0';
	API_strcpy(server, temp);
}

char* Conv_HttpPost_SetHead(char * url,char *pBuffOut)
{
	char serverAdd[64] = {0};
	char fileName[32] = {0};
	char PostAdd[64] = {0};
	twebGetHostGET(url, serverAdd, PostAdd, fileName);
	//TRACE("serverAdd:%s\r\nPostAdd:%s\r\nfileName:%s\r\n", serverAdd,PostAdd,fileName);
	API_sprintf(pBuffOut, "POST %s HTTP/1.1\r\n",PostAdd);
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut,"User-Agent: Apache-HttpClient/4.4.1 \r\n");
	API_sprintf(pBuffOut,"Host: %s\r\n",serverAdd);
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut,"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n");
	pBuffOut=Conv_Strcpy(pBuffOut,"Connection: Keep-Alive\r\n");
	pBuffOut=Conv_Strcpy(pBuffOut,"Content-Length:");
	return pBuffOut;
}

char* Conv_HttpPost_SetData(char *param, char *pBuffOut)
{
	API_sprintf(pBuffOut, "%d\r\n\r\n",API_strlen(param));//内容和请求头要用回车换行分开
	pBuffOut += API_strlen(pBuffOut);
	pBuffOut=Conv_Strcpy(pBuffOut, param);
	return pBuffOut;
}


//===多层JSON处理功能{"abb":"cdd","struct":{"abb":"cdd"}.....}===============
//--注: pIndata不能是ROM空间，处理后会修改pIndata中的参数,
//--    用完后需要Conv_JSON_free释放空间
dfJsonTable* Conv_JSON_GetMsg(char *pIndata,char* pEnd)
{
	dfJsonTable *pIdData;
	dfJsonItem *pItem=NULL;
	u16 		colonCount,parenCount;
	u16			ItemIndex,cycle;
	//------------找到起点-----------------------
	parenCount=0;
	while(pIndata < pEnd)
	{
		if(*pIndata++ == '{') 
		{
			parenCount++;
			break;
		}
	}
	if(parenCount!=1) return NULL;
	//------------找到终点-----------------------
	colonCount=0;
	{
		char *pE=pEnd;
		pEnd=pIndata;
		while(pEnd < pE)
		{
			if(*pEnd == '{')
				parenCount++;
			else if(*pEnd == '}')
			{
				if(--parenCount == 0) break;
			}
			else if(*pEnd == ':')
			{
				if(parenCount == 1)	//-计算第一层参数总数-
					colonCount++;
			}
			pEnd++;
		}
	}
	if(parenCount)
	{
		LOG(LOG_ERROR,"JSON_GetMsg ERR The {} number does not match[%d]\r\n",parenCount);
		return NULL;
	}
	if(colonCount<1)
	{
		LOG(LOG_ERROR,"GetMsg  The : number Err[%d]\r\n",colonCount);
		return NULL;
	}
	*pEnd = '\0';
	//-----------申请对应空间----------------------
	pIdData=(dfJsonTable*)malloc(sizeof(dfJsonTable)+(sizeof(dfJsonItem)*colonCount)); //+1 = +'\0';
	pIdData->pNext= NULL;
	pIdData->sLen = pEnd-pIndata;
	cycle=0;
	ItemIndex=0;
	while(pIndata < pEnd)
	{
		if(*pIndata == '\"')
		{
			if(cycle==0)	//0 strar
			{
				pItem=&pIdData->Item[ItemIndex++];
				cycle++;	// 1-> IDStar
			}
			else if(cycle==2) // 2-> End ID
			{
				*pIndata='\0';	//增加结束符号
				cycle++; // 3-> :
			}
			else if(cycle==4)	// 4->Data Strat
			{
				cycle++;		//5 Strat Data
			}
			else if(cycle==5 || cycle==6) // 6-> End IDEnd
			{//为5时空数据
				*pIndata='\0';	//增加结束符号
				cycle=7;	// 7-> Next
			}
		}
		else if(*pIndata == '[')
		{
			char *pKuoEnd;
			u16 dkjs,dkNum;
			pKuoEnd = ++pIndata;
			parenCount=1;
			dkjs=0;dkNum=0;
			while(pKuoEnd < pEnd)
			{
				if(*pKuoEnd == '[')
					parenCount++;
				else if(*pKuoEnd == ']')
				{
					parenCount--;
					if(parenCount == 0) break;
				}
				else if(*pKuoEnd == '{')
					dkjs++;
				else if(*pKuoEnd == '}')
				{
					dkjs--;
					if(dkjs == 0)
						dkNum++;
				}				
				pKuoEnd++;
			}
			if(parenCount==0 && dkNum > 0)
			{
				dfJsonTable *pNext=NULL;
				char *pS,*pE;
				for(dkjs=0;dkjs<dkNum;dkjs++)
				{
					pS = NULL;
					parenCount=0;
					while(pIndata < pKuoEnd)
					{
						if(*pIndata == '{')
						{
							if(++parenCount == 1)
								pS = pIndata;
						}
						else if(*pIndata == '}')
						{
							if(--parenCount == 0) break;
						}
						pIndata++;
					}
					pE = ++pIndata;
					if(pS)
					{
						if(pNext==NULL)
						{
							pNext=Conv_JSON_GetMsg(pS,pE);
							pItem->pValue=pNext;
						}
						else 
						{
							pNext->pNext=Conv_JSON_GetMsg(pS,pE);
							pNext=pNext->pNext;
						}
					}
				}
				pItem->vaNum= dkNum;
				pItem->dType= ITEM_STRUCT;
			}
			else
			{
				pItem->dType= ITEM_STRING;
				pItem->pValue=pIndata;
				*pKuoEnd = '\0';
			}
			pIndata=pKuoEnd;
			pIndata++;
			cycle=0;  //0 strar
		}
		else if(*pIndata == ':')
		{
			if(cycle==3) 
				cycle++; // 4-> Data:
		}
		else if(*pIndata == ',')
		{
			if(cycle==7)
			{
				*pIndata='\0';	
				cycle=0;  //0 strar
			}
		}
		else if(*pIndata == '{')
		{
			if(cycle==4 || cycle==5)	//cycle==4 为:{} 模式   , cycle==5 为:"{}" 模式
			{
				char *p;
				p=pIndata;
				p++; 
				parenCount=1;
				colonCount=0;
				while(p < pEnd)
				{
					if(*p == '{')
						parenCount++;
					else if(*p == '}')
					{
						if(--parenCount == 0) break;
					}
					else if(*p == ':')
						colonCount++;
					p++;
				}
				p++;
				pItem->vaNum= 1;
				if(parenCount==0)
				{
					if(colonCount>0)
					{
						pItem->dType= ITEM_STRUCT;
						pItem->pValue=Conv_JSON_GetMsg(pIndata,p);
					}
					else
					{
						pItem->dType= ITEM_NULL;
						pItem->pValue=pIndata;
						*p = '\0';
					}
				}
				else
				{
					LOG(LOG_ERROR,"JSON_GetMsg Key[%s],Get Value ERR \r\n",pItem->pkey);
					free(pIdData);
					return NULL;
				}
				pIndata=p;
				if(cycle==5)
					pIndata++;
				cycle=0;  //0 strar
			}
		}
		else
		{
			if(cycle==1)	// 1-> IDStar
			{
				pItem->pkey=pIndata;
				cycle++;	// 2-> End IDStar
			}
			else if(cycle==4 && (*pIndata > ' '))	// 3-> Data Int ,空格或换行符无效
			{
				pItem->dType= ITEM_INT;
				pItem->pValue=pIndata;
				cycle=7;		//5 End ,
			}
			else if(cycle==15)	// 3-> Data Int ,空格或换行符无效
			{
				pItem->dType= ITEM_INT;
				pItem->pValue=pIndata;
				cycle++;		//5 End ,
			}
			else if(cycle==5) // 3-> Data Str
			{
				pItem->dType= ITEM_STRING;
				pItem->pValue=pIndata;
				cycle++;	// 6-> End Data
			}
		}
		pIndata++;
	}
	pIdData->Total = ItemIndex;
	return pIdData;
}

/*
===参数pKey 支持多级别访问，用'/'隔开,支持组访问用"[i]",i表示下标，如 "abc/list[2]/hij"==========
注: ITEM_STRUCT,类型:pType为空时不会返回指针.
如返回指针为ITEM_STRUCT类型可当(dfJsonTable*)参数继续用Conv_GetJsonValue来解下一层
*/
char* Conv_GetJsonValue(dfJsonTable *pStart,char* pKey,u8 *pType)
{
	char *src1,*src2;
	u16 i,Max;
	if(pStart == NULL)
	{
		LOG(LOG_ERROR,"Conv GetJsonStr[%s] pStart Err\r\n",pKey);
		return NULL;
	}
	Max=pStart->Total;
	for(i=0;i<Max;i++)
	{
		src1=pKey;
		src2=pStart->Item[i].pkey;
		while(*src2)
		{
			if(*src1 != *src2)
				break;
			src1++; src2++;
		}
		
		if(*src2 == '\0')
		{
			if(*src1 == '\0')
			{
				if(pType) 
				{
					*pType= pStart->Item[i].dType;
				}
				else if(pStart->Item[i].dType == ITEM_STRUCT)
				{
					LOG(LOG_ERROR,"GetJsonStr[%s] dtype is[%d],pType is NULL,not return\r\n",pKey,pStart->Item[i].dType);
					return NULL;
				}
				return pStart->Item[i].pValue;
			}
			else if(*src1 == '/')	//处理第二级
			{
				if(pStart->Item[i].dType == ITEM_STRUCT)
				{
					return Conv_GetJsonValue((dfJsonTable *)pStart->Item[i].pValue,++src1,pType);
				}
				LOG(LOG_ERROR,"GetJsonStr pKey[%s] '/' warning\r\n",pKey);
				return pStart->Item[i].pValue;
			}
			else if(*src1 == '[')	//处理分级，
			{//"abc/efg/hij[3]"
				u16 index=0;
				src1 ++;
				while((*src1 >= '0') && (*src1 <= '9'))
				{
					index =index*10 + ((*src1)&0x0f);
					src1++;
				}
				if(*src1++ != ']')
				{
					LOG(LOG_ERROR,"GetJsonStr[%s] Format error,not return\r\n",pKey);
					return NULL;
				}
				else
				{
					dfJsonTable *pArray=(dfJsonTable *)pStart->Item[i].pValue;
					while(index--) pArray = pArray->pNext;
					
					if(pArray)
					{
						if(*src1 == '/')
							return Conv_GetJsonValue(pArray,++src1,pType);
						else if(pType) 
						{
							*pType= pStart->Item[i].dType;
							return (char*)pArray;
						}
						return NULL;
					}
					return (char*)pArray;
				}
			}
		}
	}
	LOG(LOG_ERROR,"GetJsonStr[%s] Nofind\r\n",pKey);
	return NULL;
}


void Conv_JSON_free(dfJsonTable *pTable)
{
	u16 i,max;
	if(pTable==NULL) return ;
	max=pTable->Total;
	for(i=0;i<max;i++)
	{
		if(pTable->Item[i].dType == ITEM_STRUCT)
		{
			dfJsonTable *pCurr,*pNext;
			pCurr=(dfJsonTable*)pTable->Item[i].pValue;
			while(pCurr)
			{
				pNext = pCurr->pNext;
				Conv_JSON_free(pCurr);
				pCurr=pNext;
			}
		}
		
	}
	free(pTable);
}

//=====================================================================================================


