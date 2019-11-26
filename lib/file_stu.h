#ifndef _FILE_DEF_
#define _FILE_DEF_

	//===============�����ļ�����=======================
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
