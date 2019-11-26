/*****************************tms功能******************************
//功能-------  
//作者-------  邓国祖
//创作时间--20180511
******************************************************************************/

#include "tls_sdk.h"

//--------------程序升级使用---------------------------
#define Tms_Term_UpFlag		"appup.ini"  	// 应用参数标记
#define Tms_Term_fAppUp		"appup.ksp"  	// 终端参数版本
#define Tms_TMS_sAppUp		"tms_run"  		// 终端参数版本
#define Tms_APP_sAppUp		"app_run"  		// 应用程序
#define Tms_APP_sLogo			"logo.bmp"  		// 应用程序


//#define TMS_CONNET_ADDER	"172.16.36.11"
//#define TMS_CONNET_ADDER	"192.168.1.10"


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

typedef struct
{
	char		sTuSN[32];
	char		sModel[8];
	char		sType[2];
	char		sComType[6];
	char		sParVer[12];
}tData_TMS_Const;

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

//=============================================================
//====================================================================
//功能:    保存参数到文件系统
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),Inlen(文件长度)
//输出数据:写入结果 0 为成功
//作者:     邓国祖	---	
//创作时间:  20150916
//---------------------------------------------------------------
int APP_FileSaveBuff(const char* pfilePath,u32 offset,void* pBuff,u32 Inlen)
{
	int		fb;
	int		ret;
    fb = open(pfilePath,O_WRONLY|,O_CREAT,0666);
	if(fb == -1)
	{
		Log(LOG_ERROR,"APP FileSaveBuff Open[%s] fail\r\n",pfilePath);
		return -1;
	}
	if(offset)
	{
		seek(fb,offset,SEEK_SET);
	}
	ret=write(fb,pBuff,Inlen);
	close(fb);
	if(Inlen != ret)
	{
		Log(LOG_ERROR,"APP FileSaveBuff WriteFile[%s] Err ret[%d != %d]\r\n",pfilePath,Inlen,ret);
		return -2;
	}
	return ret;
}
//====================================================================
//功能:    从文件系统读参数
//输入数据:pfilePath(文件名),pBuff(参数缓冲区),pOutlen(输入文件长度)
//输出数据:读取结果 0 为成功
//作者:     邓国祖	---	
//创作时间:  20150916
//---------------------------------------------------------------
int APP_FileReadBuff(const char* pfilePath,u32 offset,void* pBuff,u32 buffSize)
{
	int		fd;
	int 	ret=0;
	fd = open(pfilePath,O_RDONLY);
	if(fd == -1)
	{
		Log(LOG_ERROR,"APP FileReadBuff Open[%s]fail, \r\n",pfilePath);
		return -1;
	}
	if(pBuff)
	{
		if(offset)
		{
			seek(fb,offset,SEEK_SET);
		}
		ret=read(fd, pBuff, buffSize);
		if(buffSize != ret)
		{
			Log(LOG_ERROR,"APP FileReadBuff Read[%s] Err nReadSize[%d,%d]\r\n",pfilePath,ret,buffSize);
		}
	}
	else 
	{
		struct stat tFile;
		fstat(fd, &tFile);
		ret = tFile.st_size;
	}
	close(fd);
	return ret;
}

//#include <direct.h>
#include <sys/stat.h> 


int APP_PowerOnCheckSetup(const char* pKspPath,ST_APP_INFO* pAppInfo,void (*ShowBottomProgress)(unsigned char))
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
	
	//----------------读取KSP文件头----------------------------------
	ks_fd=open(pKspPath,O_RDONLY);
	if(ks_fd == -1)
	{
		Log(LOG_ERROR,"fs read err.\r\n");
		return -1;
	}
	ret = read(ks_fd,&head, sizeof(KSP_FILE_HEAD));
	if(sizeof(KSP_FILE_HEAD) != ret) 
	{
		Log(LOG_ERROR,"fs read len[%d] err.\r\n",ret);
		close(ks_fd);
		remove(pKspPath);
		return -1;
	}
	TRACE_HEX("head",&head,20);
	if (0 != memcmp(head.Mask, "FKSP", 4)) 
	{
		Log(LOG_ERROR,"fs read mask err.\r\n");
		close(ks_fd);
		remove(pKspPath);
		return -2;
	}
	kspoffset = sizeof(KSP_FILE_HEAD);
	totalLen= BYTE4_TO_INT(head.DataLen);
	if(totalLen < 16) 
	{
		Log(LOG_ERROR,"kspoffset[%d],totalLen:%d Err\r\n",kspoffset,totalLen);
		close(ks_fd);
		remove(pKspPath);
		return 1;
	}
	//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CHECK_PACKAGE);
#if(1)
	offset = 0;
	tKspSignContext =(KSP_SIGN_CONTEXT *)signout;
	if(APP_rsa_PrivatekeyPublic(Develop_Channel_Cert_ZT,sizeof(Develop_Channel_Cert_ZT),head.signcode, signout) == 0) // 签名块验证
	{
		int ret;
		u8 shaResult[32];
		mbedtls_md_context_t ctx;
//		TRACE_HEX("signout",signout,sizeof(KSP_SIGN_CONTEXT));
		//-------------------SHA256验证--------------------------
		MaxSet = 32*1024;
		pBuffData=(u8*)malloc(MaxSet);
		api_tls_InterFace.hash->md_starts(&ctx,MBEDTLS_MD_SHA256);

		seek(ks_fd,kspoffset,SEEK_SET);
		while(offset < totalLen) 
		{
			CruSet = totalLen - offset;
			if(CruSet>MaxSet) CruSet=MaxSet;

			ret=read(ks_fd,pBuffData,CruSet);
			//ret=APP_FileReadBuff(pKspPath,kspoffset+offset,pBuffData,CruSet);
			if(ret < CruSet)
			{
				Log(LOG_ERROR,"APP FileReadBuff CruSet:%d ret:%d\r\n",CruSet,ret);
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
				TRACE_HEX("sha256-1", tKspSignContext->hashResult, 32);
				TRACE_HEX("sha256-2", shaResult, 32);
				//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_VERIFY_SIGN_ERR);
				close(ks_fd);
				remove(pKspPath);
				//Sleep(3000);
				return -4;
			}
		}
	}

	if(offset < totalLen)
	{
		Log(LOG_ERROR,"ks signinfo check err.\r\n");
		//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_CALC_SIGN_ERR);
		close(ks_fd);
		remove(pKspPath);
		//Sleep(3000);
		return -3;
	}	
	mkdir(tKspSignContext->app.tag,0666);	//创建对应目录
	chdir(tKspSignContext->app.tag);	//进入对应目录
#endif
	//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_INSTALLING);
	// 写入应用信息到块
	compLen = 0;	
	tmsSetup=0;
	appSetup=0;
	resLogoSetup=0;
  	MaxSet = 32*1024;
	pBuffData=(u8*)malloc(MaxSet);
  	Log(LOG_INFO,"write app[%d]\r\n",head.filenum);
	if(ShowBottomProgress) ShowBottomProgress(0);	//初始进度条
	//-----不休眠--------------
	//先关字库文件，有利于更新字库。
	//------------------------------
	{
		int 	Tfd;
		char	fileName[16+1];
		char	dir_name[20+3];
		KSP_FILE_ITEM tFileItem;
		//-----打开安装文件------------
		// 重新读取文件，并按文件写入相关系统
		for (i = 0; i < head.filenum; i++) 
		{
			// 读一个块
			seek(ks_fd,kspoffset,SEEK_SET);
			read(ks_fd,&tFileItem,sizeof(tFileItem));
			//APP_FileReadBuff(pKspPath,kspoffset,&tFileItem, sizeof(tFileItem));
			memcpy(fileName,tFileItem.fileName,16);
			fileName[16]='\0';
			fileLen = BYTE4_TO_INT(tFileItem.fileLen);		
			kspoffset += sizeof(tFileItem); 	
			Log(LOG_INFO,"filename[%d]:%s,fileLen=%d\r\n",i,fileName,fileLen);		
			
			if(0 == strcmp("/hd/tms", fileName)) //TMS自身更新
			{ 
				strcpy(dir_name,Tms_TMS_sAppUp);
				//remove(dir_name);
				tmsSetup=1;
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0777);
			}
			else if(0 == strcmp("/hd/app", fileName)) //应用更新
			{ 
				strcpy(dir_name,Tms_APP_sAppUp);
				//remove(dir_name);
				appSetup=1;
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0777);
			}
			else	//资源更新
			{ 
				strcpy(dir_name, fileName);
				if(!(resLogoSetup&0x01))
				{
					if(strcmp("ks.res", fileName) == 0) //字库资源
					{ 
						resLogoSetup |= 0x01;
					}
				}
				if(!(resLogoSetup&0x02))
				{
					if(strsts("Logo.", fileName))//logo 资源
					{
						resLogoSetup |= 0x02;
					}
				}
				Tfd=open(dir_name,O_WRONLY|O_CREAT,0666);
			}
			//------------刷新进度条----------------------
			if(Tfd==0)
			{
				Log(LOG_ERROR,"API fopen CRNEW[%s]\r\n",dir_name);
				continue;
			}
			compLen += sizeof(KSP_FILE_ITEM);
			if(ShowBottomProgress) ShowBottomProgress(compLen*100/totalLen);
			//-------------SetData-----------------------------
			{
				offset = 0;
				while(offset < fileLen) 
				{
					CruSet = fileLen - offset;
					if(CruSet>MaxSet) CruSet=MaxSet;
					// 读目标文件
					seek(ks_fd,kspoffset+offset,SEEK_SET);
					ret=read(ks_fd,pBuffData,CruSet);
					if(ret != CruSet)
					{
						Log(LOG_ERROR,"ERR->FileReadBuff->%s,CruSet=%d,ret=%d\r\n",pKspPath,CruSet,ret);
						break;
					}
					// 写入文件系统
					//seek(Tfd,offset,SEEK_SET);
					ret=write(Tfd,pBuffData,CruSet);
					if (ret != CruSet) 
					{
						Log(LOG_ERROR,"ERR->FileSaveBuff->%s,CruSet=%d,ret=%d\r\n",dir_name,CruSet,ret);
						break;
					}
					offset += CruSet;
					//------------刷新进度调----------------------
					compLen += CruSet;
					if(ShowBottomProgress) ShowBottomProgress(compLen*100/totalLen);
				}
				close(Tfd);
				if(offset < fileLen)
				{
					Log(LOG_ERROR,"ERR->FileSave->%s ERR[%d<%d]\r\n",dir_name,offset,fileLen);
					remove(dir_name);
				}
			}
			// 该文件结束
			kspoffset += fileLen;
		}
	}
	close(ks_fd);
	free(pBuffData);
	Log(LOG_INFO,"CheckSetup:resLogo=%x,app=%d,tms=%d\r\n",resLogoSetup,appSetup,tmsSetup);
	remove(pKspPath);
	Log(LOG_INFO,"API fremove[%s]\r\n",pKspPath);
	//---------------更新LOGO-----------------------------------
	if(resLogoSetup&0x02)
	{

	}
	//----------------安装参数-----------------------------------
	if(resLogoSetup&0x01)
	{
	
	}
	//----------------安装应用-----------------------------------
	if(appSetup)	//安装应用
	{
		//APP_ShowSta(STR_FIRMWARE_UPGRADE,STR_SUCCESS);
		strcpy(pAppInfo->Id,tKspSignContext->app.tag);
		strcpy(pAppInfo->Name,tKspSignContext->app.name_cn);
		strcpy(pAppInfo->Desc,tKspSignContext->app.name_en);
		strcpy(pAppInfo->Artwork,tKspSignContext->app.sdk_ver);
		strcpy(pAppInfo->Vender,tKspSignContext->app.app_time);
		strcpy(pAppInfo->Version,tKspSignContext->app.app_ver);
	}
	//--------------安装主控-----------------------------------
	if(tmsSetup)	//安装主控
	{
		strcpy(pAppInfo->Id,tKspSignContext->app.tag);
		strcpy(pAppInfo->Name,tKspSignContext->app.name_cn);
		strcpy(pAppInfo->Desc,tKspSignContext->app.name_en);
		strcpy(pAppInfo->Artwork,tKspSignContext->app.sdk_ver);
		strcpy(pAppInfo->Vender,tKspSignContext->app.app_time);
		strcpy(pAppInfo->Version,tKspSignContext->app.app_ver);
	}
	return 0;
}

#endif
