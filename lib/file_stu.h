#ifndef _FILE_DEF_
#define _FILE_DEF_

	//===============下载文件字义=======================
	typedef struct 										// APP安装包文件头
	{
	    u8 	        Mask[4];				// FKSP
	    u8	 		HeadLen[4];				// 头部长度
	    u8	 		DataLen[4];				// 数据长度
	    u8	 		Ver;					// 1
	    u8	 		Type;					// 文件类型(KSP_TYPE)
	    u8	 		Format;					// 文件格式(tar.gz,自定义)
	    u8	 		Flag;					// 标记 
	    u8			filenum;                // 文件数量
	    u8          bl[3];
	    u8			signcode[256];			//
	}KSP_FILE_HEAD;

	typedef struct 										// APP安装包文件头
	{
	    u8	 		DataLen[4];				// 文件名长度
	    u8			nouese;
		u8			fileName[16];
	    u8	 		fileLen[4];				// 数据长度
	}KSP_FILE_ITEM;

	typedef  struct 					   // APP信息
   {
	   char 	   tag[15+1];			   // 应用标识
	   char 	   name_en[30+2];		   // 应用名称(英文)
	   char 	   name_cn[30+2];		   // 应用名称(中文)
	   char 	   sup_dev[15+1];		   // 应用支持的设备   (暂时不使用)
	   char 	   sdk_ver[7+1];		   // 支持的SDK版本    [123.567]
	   char 	   app_ver[11+1];		   // 应用软件版本	   [123.567.901]
	   char 	   app_time[16+4];		   // 应用软件日期时间 [2013-10-08]
   }KSP_SIGN_APP;							   // 共136字节
		   
   
	typedef struct					   // 签名结果定义
	{	 
	   u8 signFlag[8];		   // 0x01SZZTSIG
	   u8 hashResult[32];	   // SHA256结果
	   u8 signType[1];		   // 数据内容, 0BOOT 1系统 2KEY 3应用(对于系统和应用统一由KBOOT验证固件,下载验证统一)
	   u8 signData[7];		   // 时间日期
	   u8 codeLen[4];		   // 数据内容长度,如果长度不符合终止后需处理
	   u8 codeAddress[4];	   // 签名数据的开始长度
	   u8 signer[16];		   // 渠道名称	   以上共68字节 	   
	   KSP_SIGN_APP    app; 			   // 应用信息	   
	}KSP_SIGN_CONTEXT;  
	
	//================================固定定义4K空间=======================================================================================
	typedef struct
	{
		u8      auth[256];       //资源区的签名数据(解压后就是:KSP_SIGN_CONTEXT)

		u8      mask[4];		    //"RESA"
		u8      ver;           
		u8      count;           //最大255个RES_ITEM
		u8      itemlen;         //sizeof（RES_ITEM）
		u8      va[1+8];         //保留
	}RES_Head;
	typedef struct
	{
		char	name[16];        	//资源文件名
		u8		datalen[4];      	//资源数据长度
		u8		offset[4];      	//资源数据偏移地址，如：第1项按建议将等于4096
	} RES_ITEM;	
	//=======================================================================================================================

const char sMaster_Cert_ZT[] =
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
