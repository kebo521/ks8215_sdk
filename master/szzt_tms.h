#ifndef _SZZT_TMS_
#define _SZZT_TMS_

	typedef struct 										// APP��װ���ļ�ͷ
	{
	    u8 	        Mask[4];				// FKSP
	    u8	 		HeadLen[4];				// ͷ������
	    u8	 		DataLen[4];				// ���ݳ���
	    u8	 		Ver;					// 1
	    u8	 		Type;					// �ļ�����(KSP_TYPE)
	    u8	 		Format;					// �ļ���ʽ(tar.gz,�Զ���)
	    u8	 		Flag;					// ��� 
	    u8			filenum;                // �ļ�����
	    u8          bl[3];
	    u8			signcode[256];			//
	}KSP_FILE_HEAD;

	typedef struct 										// APP��װ���ļ�ͷ
	{
	    u8	 		DataLen[4];				// �ļ�������
	    u8			nouese;
		u8			fileName[16];
	    u8	 		fileLen[4];				// ���ݳ���
	}KSP_FILE_ITEM;

	typedef  struct 					   // APP��Ϣ
   {
	   char 	   tag[15+1];			   // Ӧ�ñ�ʶ
	   char 	   name_en[30+2];		   // Ӧ������(Ӣ��)
	   char 	   name_cn[30+2];		   // Ӧ������(����)
	   char 	   sup_dev[15+1];		   // Ӧ��֧�ֵ��豸   (��ʱ��ʹ��)
	   char 	   sdk_ver[7+1];		   // ֧�ֵ�SDK�汾    [123.567]
	   char 	   app_ver[11+1];		   // Ӧ������汾	   [123.567.901]
	   char 	   app_time[16+4];		   // Ӧ���������ʱ�� [2013-10-08]
   }KSP_SIGN_APP;							   // ��136�ֽ�
		   
   
	typedef struct					   // ǩ���������
	{	 
	   u8 signFlag[8];		   // 0x01SZZTSIG
	   u8 hashResult[32];	   // SHA256���
	   u8 signType[1];		   // ��������, 0BOOT 1ϵͳ 2KEY 3Ӧ��(����ϵͳ��Ӧ��ͳһ��KBOOT��֤�̼�,������֤ͳһ)
	   u8 signData[7];		   // ʱ������
	   u8 codeLen[4];		   // �������ݳ���,������Ȳ�������ֹ���账��
	   u8 codeAddress[4];	   // ǩ�����ݵĿ�ʼ����
	   u8 signer[16];		   // ��������	   ���Ϲ�68�ֽ� 	   
	   KSP_SIGN_APP    app; 			   // Ӧ����Ϣ	   
	}KSP_SIGN_CONTEXT;  
	
	//================================�̶�����4K�ռ�=======================================================================================
	typedef struct
	{
		u8      auth[256];       //��Դ����ǩ������(��ѹ�����:KSP_SIGN_CONTEXT)

		u8      mask[4];		    //"RESA"
		u8      ver;           
		u8      count;           //���255��RES_ITEM
		u8      itemlen;         //sizeof��RES_ITEM��
		u8      va[1+8];         //����
	}RES_Head;
	typedef struct
	{
		char	name[16];        	//��Դ�ļ���
		u8		datalen[4];      	//��Դ���ݳ���
		u8		offset[4];      	//��Դ����ƫ�Ƶ�ַ���磺��1����齫����4096
	} RES_ITEM;	
	//=======================================================================================================================
extern int APP_rsa_decryptSign(u8 *pInData,u8* pOutData);



extern int APP_PowerOnCheckSetup(const char* pKspPath,ST_APP_INFO* pAppInfo,void (*ShowBottomProgress)(unsigned char));


#endif
