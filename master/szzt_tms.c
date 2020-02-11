
/*****************************tms功能******************************
//功能-------  
//作者-------  邓国祖
//创作时间--20180511
******************************************************************************/
#include "comm_type.h"
#include "file_stu.h"

#include "tls_sdk.h"

#include "sys_sdk.h"

#include "xui_comm.h"

#include "dataconv.h"
#include "app_sdk.h"

#include "AdminTUSN.h"
#include "szzt_tms.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <unistd.h>
//#include <fcntl.h>
//#include <signal.h>
//#include <time.h>

//#include <sys/types.h>    
//#include <sys/stat.h>    
//#include <sys/time.h>
//#include <sys/shm.h> 



//--------------程序升级使用---------------------------
#define Tms_Term_UpFlag		"appup.ini"  	// 应用参数标记
#define Tms_TMS_sAppUp		"tms_run"  		// 终端参数版本
#define Tms_Term_fAppUp		"appup.ksp"  	// 终端参数版本
#define Tms_APP_sAppUp		"app_run"  		// 应用程序
#define Tms_APP_sLogo			"logo.bmp"  		// 应用程序

#define TMS_CONNET_ADDER		tAdminTermPar.TmsAddre
#define TMS_CONNET_POST		tAdminTermPar.TmsPost
#define TMS_CONNET_SSLEN		tAdminTermPar.TmsSSL
#define TMS_RECV_MAX			tAdminTermPar.TmsPackMax


typedef struct
{
	u16 	uID;
	u16 	len;
	u8		*pData;
}tData_TMS;

typedef struct
{
	int			Total;
	tData_TMS	Item[40];
}tData_TMS_struct;


//===================应用签名RSA密钥====================================
#ifdef CUSTOMER_DVI
//--------------给客户的密钥(公开)--------------------------------
const char Develop_Channel_Cert_ZT[] =
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEpAIBAAKCAQEAyHTEzLn5tXnpRdkUYLB9u5Pyax6fM60Nj4o8VmXl3ETZzGaF\r\n"
"B9X4J7BKNdBjngpuG7fa8H6r7gwQk4ZJGDTzqCrSV/Uu1C93KYRhTYJQj6eVSHD1\r\n"
"bk2y1RPD0hrt5kPqQhTrdOrA7R/UV06p86jt0uDBMHEwMjDV0/YI0FZPRo7yX/k9\r\n"
"Z5GIMC5Cst99++UMd//sMcB4j7/Cf8qtbCHWjdmLao5v4Jv4EFbMs44TFeY0BGbH\r\n"
"7vk2DmqV9gmaBmf0ZXH4yqSxJeD+PIs1BGe64E92hfx//DZrtenNLQNiTrM9AM+v\r\n"
"dqBpVoNq0qjU51Bx5rU2BXcFbXvI5MT9TNUhXwIDAQABAoIBAGdNtfYDiap6bzst\r\n"
"yhCiI8m9TtrhZw4MisaEaN/ll3XSjaOG2dvV6xMZCMV+5TeXDHOAZnY18Yi18vzz\r\n"
"4Ut2TnNFzizCECYNaA2fST3WgInnxUkV3YXAyP6CNxJaCmv2aA0yFr2kFVSeaKGt\r\n"
"ymvljNp2NVkvm7Th8fBQBO7I7AXhz43k0mR7XmPgewe8ApZOG3hstkOaMvbWAvWA\r\n"
"zCZupdDjZYjOJqlA4eEA4H8/w7F83r5CugeBE8LgEREjLPiyejrU5H1fubEY+h0d\r\n"
"l5HZBJ68ybTXfQ5U9o/QKA3dd0toBEhhdRUDGzWtjvwkEQfqF1reGWj/tod/gCpf\r\n"
"DFi6X0ECgYEA4wOv/pjSC3ty6TuOvKX2rOUiBrLXXv2JSxZnMoMiWI5ipLQt+RYT\r\n"
"VPafL/m7Dn6MbwjayOkcZhBwk5CNz5A6Q4lJ64Mq/lqHznRCQQ2Mc1G8eyDF/fYL\r\n"
"Ze2pLvwP9VD5jTc2miDfw+MnvJhywRRLcemDFP8k4hQVtm8PMp3ZmNECgYEA4gz7\r\n"
"wzObR4gn8ibe617uQPZjWzUj9dUHYd+in1gwBCIrtNnaRn9I9U/Q6tegRYpii4ys\r\n"
"c176NmU+umy6XmuSKV5qD9bSpZWG2nLFnslrN15Lm3fhZxoeMNhBaEDTnLT26yoi\r\n"
"33gp0mSSWy94ZEqipms+ULF6sY1ZtFW6tpGFoy8CgYAQHhnnvJflIs2ky4q10B60\r\n"
"ZcxFp3rtDpkp0JxhFLhiizFrujMtZSjYNm5U7KkgPVHhLELEUvCmOnKTt4ap/vZ0\r\n"
"BxJNe1GZH3pW6SAvGDQpl9sG7uu/vTFP+lCxukmzxB0DrrDcvorEkKMom7ZCCRvW\r\n"
"KZsZ6YeH2Z81BauRj218kQKBgQCUV/DgKP2985xDTT79N08jUo3hTP5MVYCCuj/+\r\n"
"UeEw1TvZcx3LJby7P6Xad6a1/BqveaGyFKIfEFIaBUBItk801sDDpDaYc4gL00Xc\r\n"
"7lFuBHOZkxJYlss5QrGpuOEl9ZwUt5IrFLBdYaKqNHzNVC1pCPfb/JyH6Dr2HUxq\r\n"
"gxUwAQKBgQCcU6G2L8AG9d9c0UpOyL1tMvFe5Ttw0KjlQVdsh1MP6yigYo9DYuwu\r\n"
"bHFVW2r0dBTqegP2/KTOxKzaHfC1qf0RGDsUoJCNJrd1cwoCLG8P2EF4w3OBrKqv\r\n"
"8u4ytY0F+Vlanj5lm3TaoHSVF1+NWPyOTiwevIECGKwSxvlki4fDAA==\r\n"
"-----END RSA PRIVATE KEY-----\r\n";
#else	
//--------------公司内部用的密钥(不公开)---------------------------------
const char Develop_Channel_Cert_ZT[] =
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEowIBAAKCAQEAyrPz81zvCTKDi3vj+6FvhmQFzrFWQYBMZPsVbhrnOocqYcu/\r\n"
"WykQYQyJabcHtzSpXbc4FGDFEvjaly0B+8hGm3doc8hmVO+Ks4Jry4O0KCg7Bjui\r\n"
"4Q5/WwEq6BHN2L7A0y9pJe8AkjpR2hFTsZOIF+PnbfTtsLGP/Ecuf7jPcHcxXlwZ\r\n"
"yPb5RmsAw+tC3JAIxovQAvreaGc/0FLhRMx0ic5jFgTl+81cYAgc3HhgPd0iHUJO\r\n"
"TaXRifPyeqHAZro8BT9yyzqmA4G8/ogBd5RUHpGX9P1tmucNotfDYu3F1/W4qIRF\r\n"
"XPjfj12RBc1hhQstMATEixx54tlFpKuMQkENlQIDAQABAoIBAH/UJgaV18R0D5K5\r\n"
"6Vb5Qmx8zVDAcsXR09tmn+gUnTdCoA6WP7GMXuDk2A9Ltljpo9kOvxXSxNUnDCqD\r\n"
"3plafnRyQ/OoMChl+5EisTnhb45XeImAuEG3M8c/IEDDYY3LFazYXDXo1/JfRtj/\r\n"
"TklQ4WU3eu3TpMVl5IhSl1dCQ8cGsz7G6OaBjG/UntLX/wcnseuwIYELl0M5y7Vk\r\n"
"gsxnB/nHoeOikIkdN3rCoxTGSX8iyEvOolgga/T73K9ywvzb0Q0TwdkpDX2bDDrM\r\n"
"s1arClTxqYKke8kShr/AX9Uj1tk9aE3WQHsM4MUfFVG0VZmZvQMpyh5gPYa7Ms8G\r\n"
"qqeIHi0CgYEA+GOufhHxVfdc8M88qBuup162WSitpB0O/Nn/4rbMHaa0XvfnuZuR\r\n"
"hYOzr4cQ2yzxooAHxOnD3pE1ORNS/yxj3150KNd0yUKobrSWYmb1gdIs1R/97FUJ\r\n"
"r1HoEvSLw9nvutR5Pnk1y5MNTw+Xq1kMRXM2iM5wjaBPSJ41zBRYVbsCgYEA0Onq\r\n"
"ay/fzdq6QDMTyzDtz9CW/QfFzumvysy/VGaOx2GQlmRXSUewC4Lwy118Sx95fEQC\r\n"
"A4EKR21SKRuX2yP70/1XMptYW3Uu8qPzwFTouXWz5smWoNwguakHhuuxiQAiUHBU\r\n"
"5Z5o2SpeR1IwiZ4Nt8uHyosPXXpGr2EryarozO8CgYEA8tVJNzlFbpz5wPdpvpPp\r\n"
"qPlAXmQVdlduWqapsrSxUt+ygRHt+phrqVL7rUPnp88FoK94aPt9IS9nEBijUJLO\r\n"
"RQbrmy4gn85KKojkaOltZXDbobS4I39zi3IQ588qgNukskudCQWpIQ/vt/ZvefYB\r\n"
"uDgN/auNf/hU6pK5132gapcCgYBZcOwVu8dbgJtgxP1ibq5B3JHn/p3nehDzCDmZ\r\n"
"ztat8c1PNeJQ00pBg2vIBVwjZXRDiXI7QdG+xsT4KIIZJgy4s6vTVMK9VSwmYZ8H\r\n"
"5tJEJGpDEmdUsymnkwBP+TRm7RHD0nPmYq2M3CDE9CEnqe1BlPer9WE8qg79IuL2\r\n"
"Uh+dLQKBgEtgOzeGV5KAwl/TqIo9Li77L6uToIUkqMtvPKVEQvPKyEleW2NDeXw+\r\n"
"5pcEdydGstikUxPUItbnHi0lKn9zjef0BKsvNSUClCT3dFe/KwHAeicCycaC2+Cp\r\n"
"NfMupSeWXUMjSjJuZPAldNVs2yf+XS87UHIhm6JmxDlwP2WESXsy\r\n"
"-----END RSA PRIVATE KEY-----\r\n";
#endif




#if(1)






u8* TMS_FindRecvData(tData_TMS_struct* pTms,u16 uInID,u32 *pOutLen)
{
	int i;
	for(i=0; i< pTms->Total;i++)
	{
		if(pTms->Item[i].uID == uInID)
		{
			if(pOutLen)
				*pOutLen = pTms->Item[i].len;
			return pTms->Item[i].pData;
		}
	}
	LOG(LOG_INFO,"Tms FindRecvData Nofind[%X] \r\n",uInID);
	return NULL;
}


int TMS_CheckFullData(char *pIndata,int InLen)
{
	u16 Len=0;
	//TRACE_HEX("TMS_CheckFullData",pIndata,InLen);
	if(InLen > 2)
	{
		Len = (u8)*pIndata++;
		Len *= 256;
		Len |= (u8)*pIndata++;
		Len += 2;
		//if(Len > 4096) return -1;
		if(InLen >= Len) return Len;
	}
	return 0;
}



u8* TMS_AddSendData(u8 *pSendData,u16 hID,char *format,...)
{
	int ret;
	va_list arg;
	*pSendData++ = hID/256;
	*pSendData++ = hID&0xff;
	va_start( arg, format);
	ret=vsprintf((char*)pSendData+2,format,arg);
	va_end( arg );
	*pSendData++ = ret/256;
	*pSendData++ = ret&0xff;
	pSendData += ret;
	return pSendData;
}

void TMS_LoadStructData(tData_TMS_struct* pTmsRecv,u8* pRecv,u16 reLen)
{
	u16 Len,Tag;
	int cont = 0;
	u8 *pEnd = pRecv+reLen;
	while(pRecv < pEnd)
	{	
		Tag = *pRecv++;
		Tag *= 256;
		Tag |= *pRecv++;
		
		Len =* pRecv++;
		Len *= 256;
		Len |= *pRecv++;
		pTmsRecv->Item[cont].uID=Tag;
		pTmsRecv->Item[cont].len=Len;
		pTmsRecv->Item[cont].pData=pRecv;
		cont++;
		//TRACE("TMS LoadStructData cont[%d] Tag[%X],Len[%d]\r\n",cont,Tag,Len);
		if(cont>= (sizeof(pTmsRecv->Item)/sizeof(pTmsRecv->Item[0])))
		{
			LOG(LOG_ERROR,"tTmsRecv.Item[%d] is full \r\n",cont);
			break;
		}
		pRecv += Len;
	}
	pTmsRecv->Total = cont;
}



int TMS_GetParVersion(char* pParVer,int sizeVer)
{
/*
	int cont;
	if(0 < APP_FileReadBuff(TermParVersion,0,pParVer,sizeVer))
	{
		for(cont=0 ;cont<sizeVer ;cont++){
			if((u8)pParVer[cont] < (u8)' ') {
				pParVer[cont]='\0';
				break;
			}
		}
		if(cont ==	sizeVer)
			pParVer[cont-1]='\0';
		return cont;
	}
	else
	{
		API_strcpy(pParVer,"000000");
		return -1;
	}
	*/
	API_strcpy(pParVer,"000000");
	return -1;
}


//===================================文件下载========================================
int TMS_UpApp_Init(char* pfilePath,u32 fSize)
{
	return open(pfilePath,O_WRONLY|O_CREAT,0666);
}

int APP_UpAPP_Load(int fb,u32 offset,u8* pBuff,u16 Inlen)
{
	lseek(fb,offset,SEEK_SET);
	return write(fb,pBuff,Inlen);
}

void TMS_UpApp_End(int fd)
{
	close(fd);
}

//============================外部通信==========================================
int tms_external_open(COM_TYPE type)
{
	int ret;
	if(type == COM_NET)
	{
		APP_Network_KeyAccept(3);
		ret=APP_Network_Connect(TMS_CONNET_ADDER,TMS_CONNET_POST,TMS_CONNET_SSLEN);
		APP_Network_KeyAccept(0);
	}
	else
	{
		u8 buff[64],*p;
		u32 OutLen;
		ret=OsPortOpen(PORT_COM1,"115200,8,n,1");
		if(ret != RET_OK) return ret;
		
		memcpy(buff+4,"ks8215->hello",14);
		APP_Uart_PackSend(PORT_COM1,buff+4,14);
		OutLen = sizeof(buff);
		CLEAR(buff);
		p=APP_Uart_PackRecv(PORT_COM1,buff,&OutLen);
		if(p)
		{
			LOG(LOG_INFO,"tms__open ret[%s]\r\n",p);
			return OPER_OK;
		}
		return OPER_TIMEOUT;
	}
	return ret;
}

int tms_external_send(COM_TYPE type,u8 *pSendBuf, funTmsPack pFunPack,tData_TMS_Const *pInBack)
{
	int dataLen;
	if(type == COM_NET)
	{
		dataLen=pFunPack(pInBack,pSendBuf+2);
		pSendBuf[0]=dataLen/256;
		pSendBuf[1]=dataLen&0xff;
		return APP_Network_Send((char*)pSendBuf,dataLen+2);
	}
	else
	{
		dataLen=pFunPack(pInBack,pSendBuf+4);
		return APP_Uart_PackSend(PORT_COM1,pSendBuf+4,dataLen);
	}
}

void* tms_external_read(COM_TYPE type,u8* pRecvBuf,u32 *pLen,funTmsParse pFunParse)
{
	int ret;
	if(type == COM_NET)
	{
		ret=APP_Network_Recv((char*)pRecvBuf,*pLen,5000,TMS_CheckFullData);
		if(ret > 2)
		{
			*pLen = pRecvBuf[0]*256 + pRecvBuf[1];
			return pFunParse(pRecvBuf+2,pLen);
		}
	}
	else
	{
		u8* pRecvData;
		pRecvData =	APP_Uart_PackRecv(PORT_COM1,pRecvBuf,pLen);
		if(pRecvData)
		{
			return pFunParse(pRecvData,pLen);
		}
	}
	return NULL;
}

void tms_external_close(COM_TYPE type,int timeOutMs)
{
	if(type == COM_NET)
	{
		APP_Network_Disconnect(timeOutMs);
	}
	else
	{
		OsPortClose(PORT_COM1);
		OsSleep(timeOutMs);
	}
}

//======================================================================
int APP_TmsPackS001(tData_TMS_Const *pFixed,u8* pOutBuff)
{
	u8 *pSend;
	pSend=pOutBuff;
	pSend=TMS_AddSendData(pSend,0x3101,"S0001");
	pSend=TMS_AddSendData(pSend,0x3103,pFixed->sTuSN);
	pSend=TMS_AddSendData(pSend,0x3140,pFixed->sType);
	pSend=TMS_AddSendData(pSend,0x3141,pFixed->sModel);
	pSend=TMS_AddSendData(pSend,0x3001,"4.4");
	pSend=TMS_AddSendData(pSend,0x3126,"{\"net\":\"%s\",\"app_v\":\"%s\",\"source_v\":\"%s\",\"life\":\"%d\",\"bat\":\"%d\"}", \
		pFixed->sComType,tAdminTermPar.AppVer,pFixed->sParVer,APP_GetLifeCycle(),OldScreen.batteryLevel);
	LOG_HEX(LOG_INFO,"TmsSendS001",pOutBuff,(pSend-pOutBuff));
	return (pSend-pOutBuff);
}


void* APP_TmsParseS001(u8* pInData,u32* pinLen)
{
	u32 Len;
	u8 *pRecv,*pIdData;
	tData_TMS_struct tTmsRecv;
	OldScreen.TmsUpDataFlag = 1;
	//Len[2]+Data[Len]
	LOG_HEX(LOG_INFO,"TmsRecvS001",pInData,*pinLen);
	OldScreen.TmsUpDataFlag = 2;
	TMS_LoadStructData(&tTmsRecv,pInData,*pinLen);
/*
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3101,&Len);
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3103,&Len);
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3140,&Len);
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3141,&Len);
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3001,&Len);
	*/
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3126,&Len);
	if(pIdData)
	{//date: '2018-05-01 10:00:00'
		pRecv=(u8*)API_eStrstr((char*)pIdData,"\"date\"");
		if(pRecv)
		{
			while(*pRecv++ != '\"');
			LOG_HEX(LOG_INFO,"Set SysDateTime Buff",pRecv,19);
			SetSysDateTime((char*)pRecv);
			OldScreen.TmsUpDataFlag = 3;
		}
	}
	pIdData=TMS_FindRecvData(&tTmsRecv,0x3106,&Len);
	if(pIdData == NULL  && *pIdData != '1') 
	{
		LOG(LOG_ERROR,"pIdData 3106 No 1 Err\r\n");
		return NULL;
	}
	pIdData=TMS_FindRecvData(&tTmsRecv,0x4005,&Len);
	if(pIdData)
	{
		return Conv_JSON_GetMsg((char*)pIdData,(char*)pIdData+Len);
	}
	return NULL;
}

/*
3101 必填 交易代码(固定): S0001 , 详情可以查看交易代码字典 
3103 必填 终端编号 
3140 必填 终端类型(固定小写s -> 扫码终端): s 
3141 必填 终端型号: 例如 KS8223 
3111 必填 文件唯一号, fileNo 
4007 必填 以k为单位, 默认1k 
3114 必填 下载偏移量, 从0开始 
3154 必填 文件md5散列 
*/
int APP_TmsPackF011(tData_TMS_Const *pFixed,u8* pOutBuff)
{
	u8 *pSend;
	pSend=pOutBuff;
	pSend=TMS_AddSendData(pSend,0x3101,"F011");
	pSend=TMS_AddSendData(pSend,0x3103,pFixed->sTuSN);
	pSend=TMS_AddSendData(pSend,0x3140,pFixed->sType);
	pSend=TMS_AddSendData(pSend,0x3141,pFixed->sModel);
	pSend=TMS_AddSendData(pSend,0x3111,pFixed->pFileNo);
	pSend=TMS_AddSendData(pSend,0x3114,"%d",*pFixed->pOffset);
	pSend=TMS_AddSendData(pSend,0x4007,"%d",*pFixed->pReadMax);
	//LOG_HEX(LOG_INFO,"TmsSendF011",pOutBuff,(pSend-pOutBuff));
	return (pSend-pOutBuff);
	
}


/*
3101 必填 交易代码(固定): S0001 , 详情可以查看交易代码字典 
3103 必填 终端编号 
3140 必填 终端类型(固定小写s -> 扫码终端): s 
3111 必填 文件唯一号, fileNo 
4007 必填 以k为单位, 默认1k 
3115 必填 文件流片段 
3154 必填 文件md5散列 
*/
void* APP_TmsParseF011(u8* pInData,u32* pLen)
{
	tData_TMS_struct tTmsRecv;
	//Len[2]+Data[Len]
	//LOG_HEX(LOG_INFO,"TmsRecvF011",pUseBuff,ret);
	TMS_LoadStructData(&tTmsRecv,pInData,*pLen);
	return TMS_FindRecvData(&tTmsRecv,0x3115,pLen);
}

/*
3101 必填 交易代码(固定): F012 , 详情可以查看交易代码字典 
3103 必填 终端编号 
3140 必填 终端类型(固定小写s -> 扫码终端): s 
3111 必填 文件唯一号, fileNo 
3116 必填 文件类型, type 
3117 必填 上报状态
3:下载完成
4:正在覆盖
9:覆盖完成(覆盖完成) 
*/
int APP_TmsPackF012(tData_TMS_Const *pFixed,u8* pOutBuff)
{
	u8 *pSend;
	pSend=pOutBuff;
	pSend=TMS_AddSendData(pSend,0x3101,"F012");
	pSend=TMS_AddSendData(pSend,0x3103,pFixed->sTuSN);
	pSend=TMS_AddSendData(pSend,0x3140,pFixed->sType);
	pSend=TMS_AddSendData(pSend,0x3141,pFixed->sModel);
	pSend=TMS_AddSendData(pSend,0x3111,pFixed->pFileNo);
	pSend=TMS_AddSendData(pSend,0x3116,"img");
	pSend=TMS_AddSendData(pSend,0x3117,pFixed->pRetCode);
	//LOG_HEX(LOG_INFO,"TmsSendF012",pOutBuff,(pSend-pOutBuff));
	return (pSend-pOutBuff);
	
}


void* APP_TmsParseF012(u8* pIndata,u32 *Inlen)
{
	//u8 *pIdData;
	//tData_TMS_struct tTmsRecv;
	//ret=APP_Network_Recv((char*)pUseBuff,BuffSize,5000,TMS_CheckFullData);
	//Len[2]+Data[Len]
	LOG_HEX(LOG_INFO,"APP_TmsRecvF012",pIndata,*Inlen);
	return NULL;
}


extern tData_UpIni* OsSysGet_UpIni(void);
extern tHardSN_Key* OsSysGet_SnKey(void);
extern void OsSysGet_Sn(char *pSn,int size);

extern 	void OsSysMsg_sync(void);






int APP_TmsProcess(COM_TYPE type)
{
	int ret;
	u16 UseSize,UpOk;
	u32 outLen;
	u8 SaveSleepEn;
	u8* pUseBuff;
	tData_TMS_Const tTermPar;
	tData_UpIni *pTermIni;
	ret=tms_external_open(type);
	if(OPER_OK != ret) return -1;
	//----------------------------------------------------
	//if(OldScreen.mSignalType == SIGNAL_WIFI)
		API_strcpy(tTermPar.sComType,"WIFI");
	//else
	//	API_strcpy(tTermPar.sComType,"2G");
	//------------------------------------------------------------------------------------
	TMS_GetParVersion(tTermPar.sParVer,sizeof(tTermPar.sParVer));
	//--------------------------------------------------------------
	if(0 >= APP_GetHardMsg(TYPE_TERM_HARD_SN,tTermPar.sTuSN,sizeof(tTermPar.sTuSN)))
	{
		tTermPar.sTuSN[0]='K';
		tTermPar.sTuSN[1]='0';
		tTermPar.sTuSN[2]='\0';
	}
	API_strcpy(tTermPar.sModel,"KS8312");
	API_strcpy(tTermPar.sType,"s");
	//-----------------------------------------------------------
	UseSize = 256+ TMS_RECV_MAX;
	pUseBuff =	(u8*)malloc(UseSize+256);	//多256用于Wifi多余消耗。
	UpOk = 0;
	//--------------------------------------------------------
	pTermIni=OsSysGet_UpIni();
	tTermPar.pFileNo = pTermIni->sFileNo;
	tTermPar.pOffset = &pTermIni->uOffset;
	//--------------------------------------------------------
	if(pTermIni->upFlag == 2)
	{
		tTermPar.pRetCode = "3";
		if(0 <= tms_external_send(type,pUseBuff,APP_TmsPackF012,&tTermPar))
		{
			outLen= UseSize;
			tms_external_read(type,pUseBuff,&outLen,APP_TmsParseF012);
		}
		/*
		if(API_strcmp(tTermIni.sAppVer,tAdminTermPar.AppVer))
		{//------更新成功-------
			if(0 <= APP_TmsSendF012(&tTermPar,pUseBuff,tTermIni.sFileNo,"3"))
				APP_TmsRecvF012(pUseBuff,UseSize);
		}
		else
		{//------更新失败-------
			if(0 <= APP_TmsSendF012(&tTermPar,pUseBuff,tTermIni.sFileNo,"-5"))
				APP_TmsRecvF012(pUseBuff,UseSize);
		}
		*/
		tms_external_close(type,5000);
		
		API_fremove(Tms_Term_fAppUp);
		API_memset(pTermIni,0x00,sizeof(tData_UpIni));
		ret=tms_external_open(type);
	}
	
	while(OPER_OK == ret)
	{
		if(0 > tms_external_send(type,pUseBuff,APP_TmsPackS001,&tTermPar))
		{
			LOG(LOG_ERROR,"APP TmsSendS001 fail\r\n");
		}
		else
		{
			char *pIdData;
			dfJsonTable* pTable;
			u8 Md5buff[20];
			outLen= UseSize;
			pTable=(dfJsonTable*)tms_external_read(type,pUseBuff,&outLen,APP_TmsParseS001);
			if(pTable==NULL) break;
			pIdData=Conv_GetJsonValue(pTable,"fileNo",NULL);
			if(pIdData==NULL) break;
			LOG(LOG_INFO,"fileNo[%s]\r\n",pIdData);
			API_strcpy(pTermIni->sFileNo,pIdData);
			
			pIdData=Conv_GetJsonValue(pTable,"size",NULL);
			if(pIdData==NULL) break;
			pTermIni->uFileSize=API_atoi(pIdData);
			LOG(LOG_INFO,"Filesize[%d]\r\n",pTermIni->uFileSize);
			
			pIdData=Conv_GetJsonValue(pTable,"md5",NULL);
			if(pIdData==NULL) break;
			LOG(LOG_INFO,"md5[%s]\r\n",pIdData);
			Conv_StrToBcd_Left(pIdData,32,Md5buff);

			if(memcmp(pTermIni->sFileMd5,Md5buff,16))
			{//--文件内容不一样，重新下载所有
				LOG_HEX(LOG_ERROR,"md5file",pTermIni->sFileMd5,16);
				LOG_HEX(LOG_ERROR,"md5Load",Md5buff,16);
				pTermIni->upFlag=0;	//重新下载所有
				API_memcpy(pTermIni->sFileMd5,Md5buff,16);
			}
			//pIdData=Conv_GetParFindID(pTable,"v");
			//pIdData=Conv_GetParFindID(pTable,"type");
			Conv_JSON_free(pTable);
			UpOk = 1;
		}
		break;
	}
	SaveSleepEn=OldScreen.SleepEn;
	OldScreen.SleepEn=FALSE;
	while(UpOk == 1)
	{	
		u32 	RecvMax;
		u16		ErrTime;
		u8		OutMd5[20];
		u8*		pRecvApp;
		//mbedtls_md5_context ctx;
		int	fb_In;
		//-----------------休眠亮屏--------------------------------------------
//		if(OldScreen.SleepState==TRUE) DisplayScreenOn();
		//-------------------------------------------------------------	
		if(pTermIni->upFlag==0)
		{
			if(type == COM_NET)
			{
				API_GUI_CreateWindow(STR_SOFTWARE_UPDATA,TOK,TCANCEL,0);
				API_GUI_Info(NULL,TEXT_ALIGN_CENTER|TEXT_VALIGN_CENTER,STR_CHECK_UPDATA);
				API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,STR_PRESS_OK_CONNET);
				API_GUI_Show();
				if(EVENT_CANCEL == APP_WaitUiEvent(5*1000))
				{
					APP_ShowSta(STR_SOFTWARE_UPDATA,"EXIT");
					UpOk = 0x434C;
					break;
				}
			}
			fb_In = open(Tms_Term_fAppUp,O_WRONLY|O_CREAT,0666);
			//flieHandle=TMS_UpApp_Init(Tms_Term_fAppUp,tTermIni.uFileSize);
		}
		else 
		{//----------------断点续传----------------
			//flieHandle=TMS_UpApp_Init(Tms_Term_fAppUp,0);
			fb_In = open(Tms_Term_fAppUp,O_WRONLY|O_APPEND,0666);
		}
		if(fb_In <= 0)
		{
			APP_ShowSta(STR_SOFTWARE_UPDATA,STR_CREATE_FILE_FAILED);
			UpOk = 0x4641;
			break;
		}
		//--------------------------------------------------------------
		APP_ShowSta(STR_SOFTWARE_UPDATA,STR_PRESS_OK_UPDATE);
		//--------------------------------------------------------------
		//mbedtls_md5_starts_ret(&ctx);
		//----------断点续传-----------------------
		if(pTermIni->upFlag==1 && pTermIni->uOffset>0)
		{
			LOG(LOG_WARN," ->断点续传 fileLen[%d]uOffset[%d]\r\n",pTermIni->uOffset);
		}
		else pTermIni->uOffset=0;	//首次更新
		//-------------------------------------------------------------------
		APP_ShowBottomProgress(pTermIni->uOffset*100/pTermIni->uFileSize);
		RecvMax = TMS_RECV_MAX;
		ErrTime = 0;
		tTermPar.pReadMax = &RecvMax;
		while(pTermIni->uOffset < pTermIni->uFileSize)
		{
			if(0 > tms_external_send(type,pUseBuff,APP_TmsPackF011,&tTermPar))
				break;
			outLen= UseSize;
			pRecvApp=(u8*)tms_external_read(type,pUseBuff,&outLen,APP_TmsParseF011);
			if(pRecvApp)
			{
				ret=APP_UpAPP_Load(fb_In,pTermIni->uOffset,pRecvApp,outLen);
				if(ret <= 0) {
					UpOk =0x5345;
					break;
				}
			//	mbedtls_md5_update_ret(&ctx, pRecvApp, ret);
				RecvMax = ret;
			}
			else
			{
				if(++ErrTime > 3)
				{
					UpOk = 0x4146;
					LOG(LOG_ERROR," 失败次数超限ErrTime=%dr\n",ErrTime);
					break;
				}
				LOG(LOG_WARN," uOffset=%d,->断点续传[%d]....\r\n",pTermIni->uOffset,ErrTime);
				tms_external_close(type,15000);
				ret=tms_external_open(type);
				if(OPER_OK != ret)
				{
					UpOk = 0x4146;
					LOG(LOG_ERROR," 再次连接中心失败=%dr\n",ret);
					break;
				}
				continue;
			}
			pTermIni->uOffset += RecvMax;
			//----------显示进度条--------------------------------
			APP_ShowBottomProgress(pTermIni->uOffset*100/pTermIni->uFileSize);
		}
		TMS_UpApp_End(fb_In);
		if(pTermIni->uOffset >= pTermIni->uFileSize)
		{
			mbedtls_md_context_t ctx;
			u32 offset,fMaxlen;
			APP_ShowSta(STR_SOFTWARE_UPDATA,STR_DOWNLOAD_COMPLETED);
			
			offset=0;
			RecvMax = UseSize;
			fMaxlen= pTermIni->uFileSize;
			api_md_starts(&ctx,MBEDTLS_MD_MD5);
			fb_In = open(Tms_Term_fAppUp,O_RDONLY|O_CREAT,0666);
			while(offset < fMaxlen)
			{
				if(RecvMax > fMaxlen) RecvMax = fMaxlen;
				ret= read(fb_In,pUseBuff,RecvMax);
				if(ret < (int)RecvMax) break;
				api_md_update(&ctx,pUseBuff,ret);
				offset += RecvMax;
			}
			close(fb_In);
			api_md_finish(&ctx,OutMd5,NULL);
			
			if((offset >= fMaxlen) && (memcmp(pTermIni->sFileMd5,OutMd5,16)==0))
			{
				UpOk = 0x4B4F;
				APP_ShowSta(STR_SOFTWARE_UPDATA,STR_INSTALLING); 
				pTermIni->upFlag=2;
				API_strcpy(pTermIni->sAppVer,tAdminTermPar.AppVer);
				tTermPar.pRetCode = "2";
				if(0 > tms_external_send(type,pUseBuff,APP_TmsPackF012,&tTermPar))
					break;
				outLen= UseSize;
				tms_external_read(type,pUseBuff,&outLen,APP_TmsParseF012);
			}
			else
			{
				APP_ShowSta(STR_SOFTWARE_UPDATA,STR_VERIFY_FAILED);
				API_fremove(Tms_Term_fAppUp);
				memset(pTermIni,0x00,sizeof(tData_UpIni));
				UpOk = 0x5243;
				LOG(LOG_ERROR,"uFileSize=%d,Check MD5 Err....\r\n",pTermIni->uFileSize);
				LOG_HEX(LOG_ERROR,"sFileMd5",pTermIni->sFileMd5,16);
				LOG_HEX(LOG_ERROR,"OutMd5",OutMd5,16);
				pTermIni->upFlag=0;
				tTermPar.pRetCode = "-2";
				if(0 > tms_external_send(type,pUseBuff,APP_TmsPackF012,&tTermPar))
					break;
				outLen= UseSize;
				tms_external_read(type,pUseBuff,&outLen,APP_TmsParseF012);
			}
		}
		else
		{
			APP_ShowSta(STR_SOFTWARE_UPDATA,STR_DOWNLOAD_FAILED);
			pTermIni->upFlag=1;
			
			LOG(LOG_ERROR," uOffset=%d,uFileSize=%d,Err[%x]....\r\n",pTermIni->uOffset,pTermIni->uFileSize,UpOk);
			LOG_HEX(LOG_ERROR,"sFileMd5",pTermIni->sFileMd5,16);
			LOG_HEX(LOG_ERROR,"OutMd5",OutMd5,16);
			/*
			if(0 > APP_TmsSendF012(&tTermPar,pUseBuff,tTermIni.sFileNo,"-1"))
				break;
			APP_TmsRecvF012(pUseBuff,UseSize);
			*/
		}
		break;
	}
	free(pUseBuff);
	OsSysMsg_sync();
	tms_external_close(type,5000);
	APP_WaitUiEvent(2000);
	OldScreen.SleepEn=SaveSleepEn;
	//---------------------------升级应用---------------------------------
	if(UpOk == 0x4B4F)
	{
	//	memcpy(&ret,"up",sizeof(ret));
	//	OsExit(ret); //PowerReboot();
	}
	if(UpOk > 0)
		return 1;
	return 0;
}



int APP_TmsSetIp(char *pTitle)
{
	#ifdef HARD_WIFI
	char sBuff[32];
	int ret;
	EDIT_DATA tEdit;
	tEdit.pTitle=pTitle;
	tEdit.pFrontText="设置IP地址";
	tEdit.pAfterText=STR_EDIT_SWITCH_ALPHA;
	tEdit.Way=IME_NUM;
	tEdit.Limit=IME_NUM|IME_ABC;
	tEdit.Max=32;
	tEdit.Min=8;
	tEdit.timeOutMs=30*1000;
	sBuff[0]='\0';
	ret=APP_Edit(&tEdit,sBuff);
	if(ret <  tEdit.Min)
		return 0;
	APP_ShowSta("正在导入",sBuff);
	WIFI_LoadDestIp(SOCKETA_TCP_C,sBuff,TMS_CONNET_POST);
	#endif
	return 0;
}

u32 APP_TMS_UpAPP(u16 Msg)
{
	int cTimeMS;
	static int OldTimeMS=0;
	cTimeMS=OsGetTickCount();

	LOG(LOG_INFO,"APP TMS UpAPP GetCurrentTime[%d]\r\n",cTimeMS);
	if(OldTimeMS)
	{//------------6个小时发一次心跳-------------------
		if(((int)cTimeMS - OldTimeMS) < (6*60*60*1000))
			return EVENT_NONE;
	}
	OldTimeMS=cTimeMS;
	
	if(0 < APP_TmsProcess(COM_NET))
		return EVENT_CANCEL;	//刷新外层界面
	return EVENT_NONE;
}

//#include <direct.h>
int InstallAPP(ST_APP_INFO* pAppInfo)
{ // 从文件系统中读取应用
	u8  i,tmsSetup,appSetup,resLogoSetup; //ret bit0,logo bit1
	int ks_fd,ret,kspoffset,totalLen,compLen;
	KSP_FILE_HEAD head;
	int		MaxSet,CruSet;
	u8		*pBuffData;
	u32 	fileLen;
	u32 	offset;
	u8					signout[256];
	KSP_SIGN_CONTEXT 	*tKspSignContext;
	const char* pKspPath=Tms_Term_fAppUp;
	LOG(LOG_INFO,"InstallMasterAPP[%s] Init\r\n",pKspPath);
	//----------------读取KSP文件头----------------------------------
	ks_fd=open(pKspPath,O_RDONLY);
	if(ks_fd == -1)
	{
		LOG(LOG_ERROR,"fs read err.\r\n");
		return -1;
	}
	ret = read(ks_fd,&head, sizeof(KSP_FILE_HEAD));
	if(sizeof(KSP_FILE_HEAD) != ret) 
	{
		LOG(LOG_ERROR,"fs read len[%d] err.\r\n",ret);
		close(ks_fd);
		remove(pKspPath);
		return -1;
	}
	LOG_HEX(LOG_INFO,"head",&head,20);
	if (0 != memcmp(head.Mask, "FKSP", 4)) 
	{
		LOG(LOG_ERROR,"fs read mask err.\r\n");
		close(ks_fd);
		remove(pKspPath);
		return -2;
	}
	kspoffset = sizeof(KSP_FILE_HEAD);
	totalLen= BYTE4_TO_INT(head.DataLen);
	if(totalLen < 16) 
	{
		LOG(LOG_ERROR,"kspoffset[%d],totalLen:%d Err\r\n",kspoffset,totalLen);
		close(ks_fd);
		remove(pKspPath);
		return 1;
	}
	APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CHECK_PACKAGE);
#if(1)
	offset = 0;
	tKspSignContext =(KSP_SIGN_CONTEXT *)signout;
	if(APP_rsa_PrivatekeyPublic((char*)Develop_Channel_Cert_ZT,sizeof(Develop_Channel_Cert_ZT),head.signcode, signout) == 0) // 签名块验证
	{
		int ret;
		u8 shaResult[32];
		mbedtls_md_context_t ctx;
//		LOG_HEX(LOG_INFO,"signout",signout,sizeof(KSP_SIGN_CONTEXT));
		//-------------------SHA256验证--------------------------
		MaxSet = 32*1024;
		pBuffData=(u8*)malloc(MaxSet);
		api_tls_InterFace.hash->md_starts(&ctx,MBEDTLS_MD_SHA256);

		lseek(ks_fd,kspoffset,SEEK_SET);
		while(offset < totalLen) 
		{
			CruSet = totalLen - offset;
			if(CruSet>MaxSet) CruSet=MaxSet;

			ret=read(ks_fd,pBuffData,CruSet);
			//ret=APP_FileReadBuff(pKspPath,kspoffset+offset,pBuffData,CruSet);
			if(ret < CruSet)
			{
				LOG(LOG_ERROR,"APP FileReadBuff CruSet:%d ret:%d\r\n",CruSet,ret);
				break;
			}
			api_tls_InterFace.hash->md_update(&ctx,pBuffData,ret);
			offset += ret;
		}
		api_tls_InterFace.hash->md_finish(&ctx,shaResult,NULL);
		free(pBuffData);
		if(offset == totalLen)
		{
			if (memcmp(shaResult, tKspSignContext->hashResult, 32) != 0) 
			{
				LOG_HEX(LOG_ERROR,"sha256-1", tKspSignContext->hashResult, 32);
				LOG_HEX(LOG_ERROR,"sha256-2", shaResult, 32);
				APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_VERIFY_SIGN_ERR);
				close(ks_fd);
				remove(pKspPath);
				OsSleep(3000);
				return -4;
			}
		}
	}

	if(offset < totalLen)
	{
		LOG(LOG_ERROR,"ks signinfo check err.\r\n");
		APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CALC_SIGN_ERR);
		close(ks_fd);
		remove(pKspPath);
		OsSleep(3000);
		return -3;
	}	
	mkdir(tKspSignContext->app.tag,0666);	//创建对应目录
//	chdir(tKspSignContext->app.tag);		//进入对应目录
#endif
	APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_INSTALLING);
	// 写入应用信息到块
	compLen = 0;	
	tmsSetup=0;
	appSetup=0;
	resLogoSetup=0;
  	MaxSet = 32*1024;
	pBuffData=(u8*)malloc(MaxSet);
  	LOG(LOG_INFO,"write app[%d]\r\n",head.filenum);
	APP_ShowBottomProgress(0);	//初始进度条
	//-----不休眠--------------
	//先关字库文件，有利于更新字库。
	//------------------------------
	{
		int 	Tfd;
		char	fileName[16+1];
		char	dir_name[32+3];
		KSP_FILE_ITEM tFileItem;
		//-----打开安装文件------------
		// 重新读取文件，并按文件写入相关系统
		for (i = 0; i < head.filenum; i++) 
		{
			// 读一个块
			lseek(ks_fd,kspoffset,SEEK_SET);
			read(ks_fd,&tFileItem,sizeof(tFileItem));
			//APP_FileReadBuff(pKspPath,kspoffset,&tFileItem, sizeof(tFileItem));
			memcpy(fileName,tFileItem.fileName,16);
			fileName[16]='\0';
			fileLen = BYTE4_TO_INT(tFileItem.fileLen);		
			kspoffset += sizeof(tFileItem); 	
			LOG(LOG_INFO,"filename[%d]:%s,fileLen=%d\r\n",i,fileName,fileLen);		
			Tfd = -1;
			if(0 == strcmp("/hd/tms", fileName)) //TMS自身更新
			{ 
				
			}
			else if(0 == strcmp("/hd/app", fileName)) //应用更新
			{ 
				sprintf(dir_name,"%s/%s",tKspSignContext->app.tag,Tms_APP_sAppUp);
				//remove(dir_name);
				appSetup=1;
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0777);
			}
			else	//资源更新
			{ 
				sprintf(dir_name,"%s/%s",tKspSignContext->app.tag,fileName);
				if(!(resLogoSetup&0x01))
				{
					if(strcmp("ks.res", fileName) == 0) //字库资源
					{ 
						resLogoSetup |= 0x01;
					}
				}
				if(!(resLogoSetup&0x02))
				{
					if(strstr(fileName,"Logo."))//logo 资源
					{
						resLogoSetup |= 0x02;
					}
				}
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0666);
			}
			compLen += sizeof(KSP_FILE_ITEM);
			if(Tfd == -1)
			{
				LOG(LOG_ERROR,"API fopen CRNEW[%s]\r\n",dir_name);
				continue;
			}
			//------------刷新进度条----------------------
			APP_ShowBottomProgress(compLen*100/totalLen);
			//-------------SetData-----------------------------
			{
				offset = 0;
				while(offset < fileLen) 
				{
					CruSet = fileLen - offset;
					if(CruSet>MaxSet) CruSet=MaxSet;
					// 读目标文件
					lseek(ks_fd,kspoffset+offset,SEEK_SET);
					ret=read(ks_fd,pBuffData,CruSet);
					if(ret != CruSet)
					{
						LOG(LOG_ERROR,"ERR->FileReadBuff->%s,CruSet=%d,ret=%d\r\n",pKspPath,CruSet,ret);
						break;
					}
					// 写入文件系统
					//lseek(Tfd,offset,SEEK_SET);
					ret=write(Tfd,pBuffData,CruSet);
					if (ret != CruSet) 
					{
						LOG(LOG_ERROR,"ERR->FileSaveBuff->%s,CruSet=%d,ret=%d\r\n",dir_name,CruSet,ret);
						break;
					}
					offset += CruSet;
					//------------刷新进度调----------------------
					compLen += CruSet;
					APP_ShowBottomProgress(compLen*100/totalLen);
				}
				close(Tfd);
				if(offset < fileLen)
				{
					LOG(LOG_ERROR,"ERR->FileSave->%s ERR[%d<%d]\r\n",dir_name,offset,fileLen);
					remove(dir_name);
				}
			}
			// 该文件结束
			kspoffset += fileLen;
		}
	}
	close(ks_fd);
	free(pBuffData);
	LOG(LOG_INFO,"CheckSetup:resLogo=%x,app=%d,tms=%d\r\n",resLogoSetup,appSetup,tmsSetup);	
	ret = 1;
	//---------------更新LOGO-----------------------------------
	if(resLogoSetup&0x02)
	{

	}
	//----------------安装参数-----------------------------------
	if(resLogoSetup&0x01)
	{
		
	}
	//----------------安装应用-----------------------------------
	if(appSetup)
	{
		strcpy(pAppInfo->Id,tKspSignContext->app.tag);
		strcpy(pAppInfo->Name,tKspSignContext->app.name_cn);
		strcpy(pAppInfo->Desc,tKspSignContext->app.name_en);
		strcpy(pAppInfo->Artwork,tKspSignContext->app.sdk_ver);
		strcpy(pAppInfo->Vender,tKspSignContext->app.app_time);
		strcpy(pAppInfo->Version,tKspSignContext->app.app_ver);
		ret = 0;
	}
	//--------------安装主控-----------------------------------
	if(tmsSetup)	//安装主控
	{
		
	}
	remove(pKspPath);
	LOG(LOG_INFO,"API fremove[%s]\r\n",pKspPath);
	return ret;
}


#endif
