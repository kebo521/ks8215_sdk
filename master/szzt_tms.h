#ifndef _SZZT_TMS_
#define _SZZT_TMS_

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
extern int APP_rsa_decryptSign(u8 *pInData,u8* pOutData);



extern int APP_PowerOnCheckSetup(const char* pKspPath,ST_APP_INFO* pAppInfo,void (*ShowBottomProgress)(unsigned char));


#endif
