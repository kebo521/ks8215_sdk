#ifndef _ESM_SDK_
#define _ESM_SDK_

//=======================¼Ó½âÃÜ=========================================================
#define ERR_DATA_TOO_BIG	-2400 //RSA ±»¼ÓÃÜÊı¾İ´óÓÚÄ£
#define ERR_GEN_RANDOM	-2401 //²úÉúËæ»úÊıÊ§°Ü
#define ERR_GEN_FAIL		-2402 //Éú³É RSA ÃÜÔ¿¶ÔÊ§°Ü


#define SHA_TYPE_1			4
#define SHA_TYPE_224		5
#define SHA_TYPE_256		6
#define SHA_TYPE_384		7
#define SHA_TYPE_512		8

extern void OsGetRandom(unsigned char *Random,int RandomLen);
extern void OsSHA(int Mode, const void *Data, int DataLen, unsigned char*ShaOut);
extern void OsDES(const unsigned char *Input, unsigned char *Output, const unsigned char *DesKey, int KeyLen, int Mode);
extern void OsAES(const unsigned char *Input, unsigned char *Output, const unsigned char *AesKey, int KeyLen, int Mode);
extern int OsRSA(const unsigned char *Modulus, int ModulusLen, const unsigned char *Exp,int ExpLen, const unsigned char *DataIn, unsigned char *DataOut);
extern int OsRSAKeyGen(unsigned char *Modulus, unsigned char *PriExp, int ModulusLen, const unsigned char * PubExp);

//=========================PED============================================
//º¯Êı·µ»ØÖµÁĞ±í
#define ERR_PED_NO_KEY -3801 //ÃÜÔ¿²»´æÔÚ
#define ERR_PED_KEY_IDX_ERR -3802 //ÃÜÔ¿Ë÷Òı´íÎó
#define ERR_PED_DERIVE_ERR -3803 //Ğ´ÃÜÔ¿Ê±,ÃÜÔ¿²ã´Î´íÎó,Ô´ÃÜÔ¿²ã´ÎµÍÓÚÄ¿µÄÃÜÔ¿µÄ²ã´Î
#define ERR_PED_CHECK_KEY_FAIL -3804 //ÃÜÔ¿ÑéÖ¤Ê§°Ü
#define ERR_PED_NO_PIN_INPUT -3805 //ÎŞPIN ÊäÈë
#define ERR_PED_PIN_INPUT_CANCEL -3806 //È¡ÏûÊäÈëPIN
#define ERR_PED_WAIT_INTERVAL -3807 //º¯Êıµ÷ÓÃµÄ¼ä¸ôÊ±¼äĞ¡ÓÚÉè¶¨µÄ×îĞ¡Ê±¼ä¼ä¸ô(¼ÆËãPIN block/MAC)
#define ERR_PED_KCV_MODE_ERR -3808 //KCV Ä£Ê½´íÎó
#define ERR_PED_KEY_TAG_ERR -3809 //ÃÜÔ¿±êÇ©´íÎó,ÎŞ·¨Ê¹ÓÃ¸ÃÃÜÔ¿
#define ERR_PED_KEY_TYPE_ERR -3810 //ÃÜÔ¿ÀàĞÍ²»Ö§³Ö»òÕßÖ¸¶¨Ë÷ÒıµÄÃÜÔ¿ÀàĞÍ²»Æ¥Åä
#define ERR_PED_PIN_LEN_ERR -3811 //ÊäÈëPIN µÄ³¤¶ÈÓëÆÚÍû³¤¶È²»·û
#define ERR_PED_DSTKEY_IDX_ERR -3812 //Ä¿µÄÃÜÔ¿Ë÷Òı´íÎó
#define ERR_PED_SRCKEY_IDX_ERR -3813 //Ô´ÃÜÔ¿Ë÷Òı´íÎó
#define ERR_PED_KEY_LEN_ERR -3814 //ÃÜÔ¿³¤¶È´íÎó
#define ERR_PED_INPUT_PIN_TIMEOUT -3815 //ÊäÈëPIN ³¬Ê±
#define ERR_PED_NO_ICC -3816 //IC ¿¨²»´æÔÚ
#define ERR_PED_ICC_INIT_ERR -3817 //IC ¿¨³õÊ¼»¯´íÎó
#define ERR_PED_GROUP_IDX_ERR -3818 //DUKPT ×éË÷Òı´íÎó
#define ERR_PED_TAMPERED -3819 //PED ÒÑËø
#define ERR_PED_NO_MORE_BUF -3820 //Ã»ÓĞ¿ÕÏĞµÄ»º³åÇø
#define ERR_PED_NORMAL_ERR -3821 //PED Í¨ÓÃ´íÎó
#define ERR_PED_NEED_ADMIN -3822 //µ±Ç°²Ù×÷ĞèÒª¸ß¼¶È¨ÏŞ
#define ERR_PED_DUKPT_KSN_OVERFLOW -3823 //µ±Ç°DUKPT Òç³ö
#define ERR_PED_KCV_CHECK_FAIL -3824 //KCV Ğ£ÑéÊ§°Ü
#define ERR_PED_SRCKEY_TYPE_ERR -3825 //Ğ´ÈëÃÜÔ¿Ê±,Ô´ÃÜÔ¿ID µÄÀàĞÍºÍÔ´ÃÜÔ¿ÀàĞÍ²»Æ¥Åä
#define ERR_PED_UNSPT_CMD -3826 //ÃüÁî²»Ö§³Ö
#define ERR_PED_ADMIN_ERR -3827 //»ñÈ¡ÏµÍ³Ãô¸Ğ·şÎñÊ§°Ü
#define ERR_PED_DOWNLOAD_INACTIVE -3828 //Î´¼¤»îPED ÏÂÔØ¹¦ÄÜ
#define ERR_PED_KCV_ODD_CHECK_FAIL -3829 //KCV ÆæĞ£ÑéÊ§°Ü
#define ERR_PED_PED_DATA_RW_FAIL -3830 //¶ÁÈ¡PED Êı¾İÊ§°Ü
#define ERR_PED_ICC_CMD_ERR -3831 //IC ¿¨²Ù×÷´íÎó(ÍÑ»úÃ÷ÎÄ.ÃÜÎÄPIN ÑéÖ¤)
#define ERR_PED_DUKPT_NEED_INC_KSN -3832 //DUKPT KSN ĞèÒªÏÈ¼Ó1
#define ERR_PED_DUKPT_NO_KCV -3833 //DUKPT ÃÜÔ¿Ã»ÓĞKCV
#define ERR_PED_NO_FREE_FLASH -3834 //PED ´æ´¢¿Õ¼ä²»×ã
#define ERR_PED_INPUT_CLEAR -3835 //ÓÃ»§°´CLEAR ¼üÍË³öPINÊäÈë
#define ERR_PED_INPUT_BYPASS_BYFUNCTION -3836 //ÓÃ»§°´FN/ATM4 ¼üÈ¡ÏûPIN ÊäÈë
#define ERR_PED_NO_PIN_MODE -3837 //Î´ÉèÖÃPIN ÊäÈëÄ£Ê½
#define ERR_PED_DATA_MAC_ERR -3838 //Êı¾İMAC Ğ£Ñé´íÎó
#define ERR_PED_DATA_CRC_ERR -3839 //Êı¾İCRC Ğ£Ñé´íÎó
#define ERR_PED_KEY_VALUE_INVALID -3840 //¹¤×÷ÃÜÔ¿Öµ²»·ûºÏÒªÇó»òÕßÒÑ¾­´æÔÚ
//---ÃÜÔ¿ÀàĞÍ-----
typedef enum {
    PED_TLK =0x01, //Loading Key
	PED_TMK =0x02, //Master Key
	PED_TPK =0x03, //PIN Key
	PED_TAK =0x04, //MAC Key
	PED_TDK =0x05, //Data Key
	PED_TIK =0x10, //DUKPT Initial Key
	PED_TRK =0x07, //MSR Key
	PED_TAESK =0x20, //AES Key
	PED_SM2_PVT_KEY =0x30, //SM2 Private Key
	PED_SM2_PUB_KEY =0x31, //SM2 Public Key
	PED_SM4_TMK =0x32, //SM4 Master Key
	PED_SM4_TPK =0x33, //SM4 PIN Key
	PED_SM4_TAK =0x34, //SM4 MAC Key
	PED_SM4_TDK =0x35, //SM4 Data Key
} ped_key_type;
/*
#define PED_TLK 0x01 //Loading Key
#define PED_TMK 0x02 //Master Key
#define PED_TPK 0x03 //PIN Key
#define PED_TAK 0x04 //MAC Key
#define PED_TDK 0x05 //Data Key
#define PED_TIK 0x10 //DUKPT Initial Key
#define PED_TRK 0x07 //MSR Key
#define PED_TAESK 0x20 //AES Key
#define PED_SM2_PVT_KEY 0x30 //SM2 Private Key
#define PED_SM2_PUB_KEY 0x31 //SM2 Public Key
#define PED_SM4_TMK 0x32 //SM4 Master Key
#define PED_SM4_TPK 0x33 //SM4 PIN Key
#define PED_SM4_TAK 0x34 //SM4 MAC Key
#define PED_SM4_TDK 0x35 //SM4 Data Key
*/
//-------------ĞÇºÅµÄÏÔÊ¾ÊôĞÔ-------------------------
#define PED_ASTERISK_ALIGN_LEFT 0 //×ó¶ÔÆë
#define PED_ASTERISK_ALIGN_CENTER 1 //¾ÓÖĞ
#define PED_ASTERISK_ALIGN_RIGHT 2 //ÓÒ¶ÔÆë
#define PED_RGB(_r, _g, _b)		((_r*0x10000)|(_g*0x100)|_b)
//-----------RSA ÃÜÔ¿½á¹¹-----------------
typedef struct {
	int ModulusLen; /* Ä£³¤(Î») */
	unsigned char Modulus[512]; /* Ä££¬²»×ã512 ×Ö½Ú×ó²¹0x00 */
	int ExponentLen; /* Ö¸Êı³¤¶È(Î») */
	unsigned char Exponent[512]; /* Ö¸Êı£¬²»×ã512 ×Ö½Ú×ó²¹0x00 */
	unsigned char KeyInfo[128]; /* RSA ÃÜÔ¿ĞÅÏ¢ */
} ST_RSA_KEY;
//----------ÑéÖ¤ÃÜÎÄIC ¿¨PIN µÄRSA ÃÜÔ¿½á¹¹-------------
typedef struct {
	int ModulusLen; /* PIN ¼ÓÃÜ¹«Ô¿Ä£³¤(Î») */
	unsigned char Modulus[256]; /* PIN ¼ÓÃÜ¹«Ô¿Ä£Êı */
	unsigned char Exponent [4]; /* PIN ¼ÓÃÜ¹«Ô¿Ö¸Êı */
	int IccRandomLen; /* ´ÓIC ¿¨È¡µÃµÄËæ»úÊıµÄ³¤¶È */
	unsigned char IccRandom[8]; /* ´ÓIC ¿¨È¡µÃµÄËæ»úÊı */
} ST_RSA_PINKEY;
//----------»ù±¾PED----------------------
//¹¦ÄÜ ´ò¿ªProlin µÄPED ·şÎñ¡£
/*·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_BUSY Éè±¸±»Õ¼ÓÃ */
extern int OsPedOpen(void);

//¹¦ÄÜ »ñÈ¡µ±Ç°µÄPED µÄ°æ±¾¡
/*²ÎÊı: PedVer¡¾Êä³ö¡¿ PED °æ±¾ĞÅÏ¢»º³åÇø£¬6 ×Ö½Ú¡£
·µ»Ø:	RET_OK ³É¹¦
		ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
		ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
extern int OsPedGetVer(unsigned char * PedVer);

//¹¦ÄÜ ÉèÖÃÁ½´Î¼ÆËãPIN block Ö®¼äµÄ×îĞ¡¼ä¸ôÊ±¼ä¡£
/*²ÎÊı TpkIntervalMs
	= 0 Ê¹ÓÃÄ¬ÈÏÖµ(30s)
	<1000 ×Ô¶¯ÉèÎª1000(1s)
	>600000 ×Ô¶¯ÉèÎª600000(10min)
	=0xffffffff µ±Ç°ÉèÖÃ²»±»¸Ä±ä
·µ»Ø:
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª */
int OsPedSetInterval(unsigned long TpkIntervalMs);

//¹¦ÄÜ Ğ£ÑéÍÑ»úÃ÷ÎÄPIN¡£
/*²ÎÊı
IccSlot ¿¨Æ¬ËùÔÚµÄ¿¨×ùºÅ£¬IccSlot=0¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£
	Ó¦ÓÃ³ÌĞò°ÑÔÊĞíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢
	ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊĞíÊäÈë4¡¢6
	Î»ÃÜÂë²¢ÇÒÔÊĞíÎŞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û
	´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£
	ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊı×Ö¶øÖ±½Ó
	°´È·ÈÏ¼ü·µ»Ø¡£
Mode¡¾ÊäÈë¡¿
	0x00£¬IC ¿¨ÃüÁîÄ£Ê½£¬ÏÖÖ§³Ö·ûºÏEMV2000
	µÄIC ¿¨ÃüÁî¡£
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë£¬×î´óÖµÎª300000¡£
	0£º±íÊ¾Ã»ÓĞ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
IccRsp¡¾Êä³ö¡¿ 
	¿¨Æ¬ÏìÓ¦µÄ×´Ì¬Âë(2 ×Ö½Ú£ºSWA+SWB)
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedVerifyPlainPin (int IccSlot,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp);

//¹¦ÄÜ Ğ£ÑéÃÜÎÄPIN,²½ÖèÈçÏÂ£º1. »ñÈ¡Ã÷ÎÄPIN£»2. ÓÃÓ¦ÓÃÌá¹©µÄRsaPinKey ¶ÔÃ÷ÎÄPIN °´ÕÕEMV ¹æ·¶½øĞĞ¼ÓÃÜ£»3. ÓÃÓ¦ÓÃÌá¹©µÄ¿¨Æ¬ÃüÁîÓë¿¨Æ¬Í¨µÀºÅ£¬½«ÃÜÎÄPIN Ö±½Ó·¢ËÍ¸ø¿¨Æ¬¡£
/*²ÎÊı
Iccslot ¿¨Æ¬ËùÔÚµÄ¿¨×ù
RsaPinKey¡¾ÊäÈë¡¿ ¼ÓÃÜËùĞèÊı¾İ½á¹¹ST_ RSA_PINKEY¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌĞò°ÑÔÊĞíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬
	²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊĞíÊäÈë4¡¢6 Î»ÃÜÂë²¢ÇÒÔÊĞíÎŞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã
	×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊı×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø.
Mode¡¾ÊäÈë¡¿ 0x00£¬·ûºÏEMV2000IC ¿¨µÄÃüÁî¡£
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë£¬×î´óÖµÎª300000¡£
	0£º±íÊ¾Ã»ÓĞ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
IccRsp¡¾Êä³ö¡¿ ¿¨Æ¬ÏìÓ¦µÄ×´Ì¬Âë(2 ×Ö½Ú£ºSWA+SWB)
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedVerifyCipherPin (int IccSlot,const ST_RSA_PINKEY * RsaPinKey,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp);

//¹¦ÄÜ ²Á³ıPED ·şÎñ±£´æµÄËùÓĞÃÜÔ¿ĞÅÏ¢¡£
/*·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª */
int OsPedEraseKeys(void);

//¹¦ÄÜ Éè¶¨Ä³Ğ©¹¦ÄÜ¼üµÄ¹¦ÄÜ¡£
/*²ÎÊı KeyFlag
	0x00£ºÔÚÒÑÊäÈëµÄPIN ÒÑ¾­Çå¿Õ»òÕßÃ»ÓĞÊäPIN Ê±£¬°´CLEAR ¼ü£¬PED ÍË³öÊäÈëÃÜÂë×´Ì¬£¬ ²¢·µ»ØERR_PED_INPUT_CLEAR¡£
	0x01£ºÃÜÂëÊäÈë½Ó¿Ú(OsPedGetPinBlock()£¬OsPedGetPinDukpt() £¬OsPedVerifyPlainPin() £¬OsPedVerifyCipherPin() etc)ÔÚÊäÈëPIN¹ı³ÌÖĞ£¬°´ÏÂCLEAR ¼ü£¬Öğ¸öÇå³ı×î½üÊäÈëµÄPIN£¬µ±ËùÓĞÒÑÊäÈëµÄPIN ±»Çå³ıÊ±£¬ÔÙ°´CLEAR ¼üÎŞÏìÓ¦£¬²¢ÇÒ²»»áÍË³öPIN ÊäÈëº¯Êı¡£
	0x02£º±íÊ¾ÔÊĞí°´ATM4 ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎŞATM ¼üµÄ»úĞÍ¡£
	0x03£º±íÊ¾ÔÊĞí°´FN ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎŞFN ¼üµÄ»úĞÍ¡£
	0x04£º±íÊ¾ÔÊĞí°´INFO ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎŞINFO ¼üµÄ»úĞÍ¡£
	0x05£º±íÊ¾ÃÜÂëÊäÈë½Ó¿ÚÔÚÊäÈëPIN ¹ı³ÌÖĞ£¬°´ÏÂCANCEL ¼ü£¬Çå³ıËùÓĞÊäÈëµÄPINÎ»£¬µ±ËùÓĞÒÑÊäÈëµÄPIN ±»Çå³ıÊ±£¬ÔÙ°´CANCEL ¼üÎŞÏìÓ¦£¬²¢ÇÒ²»»áÍË³öPIN ÊäÈëº¯Êı¡£
	0xff £º±íÊ¾»Ö¸´Ä¬ÈÏµÄ¹¦ÄÜ¼üÉèÖÃ£¬¼´°´CLEAR ¼üÇå³ı¼üÈëµÄËùÓĞPIN Î»£¬°´CANCEL ¼üÍË³öPIN ÊäÈëº¯Êı£¬°´ATM4/FN/INFO ¼ü²»ÍË³öPIN ÊäÈëº¯Êı¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedSetFunctionKey(int KeyFlag);

//¹¦ÄÜ ¶Ï¿ªÓëPED ·şÎñµÄÁ¬½Ó¡£
void OsPedClose(void);

//¹¦ÄÜ ÓÃÓÚPIN ÊäÈë¹ı³ÌÖĞ£¬ÖÕÖ¹PIN ÊäÈë¡£
/*·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPENPED Éè±¸Î´´ò¿ª */
int OsPedCancelPinEntry(void);

//¹¦ÄÜ ÉèÖÃÍÑ»úÃ÷ÎÄ/ÃÜÎÄĞ£ÑéÄ£Ê½¡£
/*²ÎÊı
Mode ¡¾ÊäÈë¡¿
Ğ£ÑéÄ£Ê½£º
. 0-Ê¹ÓÃÄÚÖÃÃÜÂë¼üÅÌÊäÈëPIN£»
. 1-Ê¹ÓÃÍâÖÃÃÜÂë¼üÅÌÊäÈëPIN£¬Í¨¹ıPinBlock ²ÎÊıµ¼ÈëPIN¡£
TpkIdx ¡¾ÊäÈë¡¿
TPK Ë÷Òı£º
. Mode Îª0 Ê±£¬ÎŞÒâÒå£»
. Mode Îª1 Ê±£¬Ê¹ÓÃ¸ÃË÷ÒıµÄTPK ¶Ôµ¼ÈëµÄPinBlock ½øĞĞ½âÃÜµÃµ½PINÃ÷ÎÄ¡£
PinBlock ¡¾ÊäÈë¡¿
PIN block£º
. Mode Îª0 Ê±£¬ÎŞÒâÒå£»
. Mode Îª1 Ê±£¬±íÊ¾TPK ¼ÓÃÜµÄISO9564 Format1 ¸ñÊ½µÄPIN ÃÜÎÄ¡£
PinBlockLen ¡¾ÊäÈë¡¿ PIN block µÄ³¤¶È
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı	*/
int OsPedSetOfflinePin(unsigned char Mode,unsigned char TpkIdx,unsigned char *PinBlock,unsigned short PinBlockLen);

//¹¦ÄÜ ÓÃÓÚPIN ÊäÈë¹ı³ÌÖĞ£¬·¢ËÍÈ·ÈÏ¼ü½áÊøPIN ÊäÈë¡£
/*·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª */
int OsPedEndPinEntry(void);

//¹¦ÄÜ¼àÌı²¢»ñÈ¡µ±Ç°×´Ì¬ÏÂÓÃ»§ÊäÈëµÄPIN °´¼üÊıÁ¿¼°µ±´Î¼àÌıÓëÉÏ´Î¼àÌıÖĞ¼äµÄÀúÊ·°´¼üĞòÁĞ¡£
/*²ÎÊı
KeyCacheCnt¡¾Êä³ö¡¿ »ñÈ¡µ½µÄµ±Ç°ÀúÊ·°´¼üÖµÊıÁ¿¡£
KeyCache¡¾Êä³ö¡¿
. ¼üÖµ°´ÊäÈëµÄÊ±¼äÏÈºóË³ĞòÓÉµÍÎ»µ½¸ßÎ»´æÈë»º³åÇøÖĞ¡£¸ÃÊä³ö»º³åÇøµÄ´óĞ¡±ØĞë´óÓÚµÈÓÚ64 ×Ö½Ú¡£
. »ñÈ¡µ½µÄÀúÊ·°´¼üĞòÁĞ×î¶àÎª64¸ö£¬Èô´ËÊ±°´¼üĞòÁĞÖĞµÄ°´¼ü»º´æ³¬¹ı64 ¸ö£¬ÔòÊä³ö×îĞÂµÄ64 ¸ö°´¼üĞòÁĞ¡£
. »ñÈ¡µ½µÄ¼üÖµÄ¿Ç°Ö»ÄÜÎª¡°PIN¡±¡¢° ENTER ¡± ¡¢¡° CLEAR ¡± ¡¢¡°CANCEL¡±¡¢¡°FN¡±¡¢¡°ATM4¡±Õâ6 ÖÖ£¬ÆäÖĞ¡°PIN¡±Êı×Ö°´¼üÒÔ¡°*¡±´úÌæ¡£Èô´ËÊ±Ã»ÓĞ°´¼üÊäÈë£¬»ñÈ¡µ½µÄ¼üÖµÔòÎª0¡£
·µ»Ø
	>= 0 »ñÈ¡PIN ÊäÈëÊÂ¼ş³É¹¦£¬·µ»ØÖµ´óĞ¡±íÊ¾´ËÊ±PIN ÊäÈë½çÃæµÄ¡°*¡±µÄ¸öÊı¡£
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı	*/
int OsPedPinKeyNotify(int *KeyCacheCnt,unsigned char *KeyCache);


//¹¦ÄÜĞ´ÈëÒ»¸öÃÜÔ¿£¬°üÀ¨TLK£¬TMK£¬ TWK£¬SM4_TMK ºÍSM4_TWKµÄĞ´Èë¡¢·¢É¢£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕıÈ·ĞÔ¡£
/*²ÎÊı 
KeyBlock¡¾ÊäÈë¡¿
1 byte ¸ñÊ½£º0x03
1 byte
	SrcKeyType£º
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
1 byte
	SrcKeyIdx£º
	. µ±SrcKeyType = PED_TLK Ê±£¬
	SrcKeyIdx = 1£»
	. µ±SrcKeyType = PED_TMK Ê±£¬SrcKeyIdx = [1~100]£»
	. µ±ucSrcKeyType =PED_TPK/PED_TAK/PED_TDK Ê±£¬ ucSrcKeyIdx = [1~100]£»
	. µ±ucSrcKeyType =PED_SM4_TMK Ê±£¬ucSrcKeyIdx = [1~100]£»
	. µ±ucSrcKeyType =PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK Ê±£¬ucSrcKeyIdx = [1~100]¡£
1 byte
	DstKeyIdx£º
	. µ±DstKeyType = PED_TLK Ê±£¬
	DstKeyIdx = 1£»
	. µ±DstKeyType = PED_TMKÊ±£¬
	DstKeyIdx = [1~100]£»
	. µ±DstKeyType = PED_TPK »òPED_TAK »òPED_TDK Ê±£¬DstKeyIdx = [1~100]£»
	. µ±DstKeyType=PED_SM4_TMKÊ±£¬DstKeyIdx=[1~100]£»
	. µ±DstKeyType=PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK/PED_TDFK Ê±£¬DstKeyIdx=[1~100]¡£
7 bytes ±£ÁôÓò£¬Ëæ»úÊı
1 byte
	DstKeyType£º
	. PED_TLK
	. PED_TMK
	. PED_TPK/PED_TAK/PED_TDK
	. PED_SM4_TMK
	. PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK
	. PED_TDFK
1 byte
	DstKeyLen£º8/16/24µ±DstKeyType ÎªPED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDKÊ±£¬DstKeyLen=16¡£24 bytesDstKeyValueÄ¿µÄÃÜÔ¿Ã÷ÎÄ/ÃÜÎÄ
1 byte
	KcvMode£º
	0x00£ºÎŞÑéÖ¤
	0x01£º¶Ô8 ¸ö×Ö½ÚµÄ0x00 ¼ÆËãDES/TDES ¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øĞĞÆæĞ£Ñé£¬ÔÙ¶Ô¡°\x12\x34\x56\x78\x90\x12\x34\x56¡±½øĞĞDES/TDES ¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x03£º´«ÈëÒ»´®Êı¾İKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô [Ä¿µÄÃÜÔ¿ÃÜÎÄ+ KcvData]½øĞĞÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV¡£
	0x04£º¶Ô16 ×Ö½ÚµÄ0x00 ½øĞĞSM4¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°4 ¸ö×Ö½Ú¼´ÎªKCV¡£
	×¢£ºÄ£Ê½0x01¡¢0x02 ¼°0x03 Ö»ÓÃÓÚMK/SK ÃÜÔ¿×¢ÈëÑéÖ¤£¬Ä£Ê½0x04 Ö»ÓÃÓÚSM4 ÃÜÔ¿×¢ÈëÑéÖ¤¡£
128bytes
	KcvData£º
	. KcvMode Îª0x00/0x01/0x02Ê±£¬Ìî³äËæ»úÊı£»
	. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊı¾İµÄ³¤¶È£¬Ö®ºóÎªKCV Êı¾İ£¬KCV Êı¾İÖ®ºóÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½.
8 bytes
	. µ±KcvMode = 0x00 Ê±£¬Ìî³äËæ»úÊı£»
	. µ±KcvMode =0x01/0x02/0x03/0x04 Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
10 bytes Ìî³äËæ»úÊı
·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊı
ERR_SYS_BAD ÏµÍ³´íÎó
ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
ERR_PED_TAMPERED PED ±»Ëø¶¨
ERR_PED_NO_MORE_BUF ÏµÍ³ÄÚ´æ¿Õ¼ä²»×ã
ERR_PED_NORMAL_ERRPED Í¨ÓÃ´íÎó£¨ KeyBlockFormat ´íÎó£©
ERR_PED_DERIVE_ERR ÃÜÔ¿·¢É¢´íÎó
ERR_PED_KCV_MODE_ERR PED KCV Ğ£ÑéÄ£Ê½´íÎó
ERR_PED_KCV_CHECK_FAIL PED KCV Ğ£ÑéÊ§°Ü */
int OsPedWriteKey(const unsigned char * KeyBlock);


//¹¦ ÄÜ Ğ´ÈëÒ»¸öTIK ÃÜÔ¿£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕıÈ·ĞÔ¡£
/*²ÎÊı KeyBlock¡¾ÊäÈë¡¿
1 byte ¸ñÊ½£º0x03
1 byte
	SrcKeyType£º
	. PED_TLK
1 byte
	SrcKeyIdx£º
	. µ±SrcKeyType = PED_TLKÊ±£¬SrcKeyIdx = 1£»
	. Ã÷ÎÄĞ´ÈëÊ±£¬SrcKeyIdx = 0¡£
1 byte
	DstKeyIdx¡£
	DstKeyIdx = [1~100]¡£
7 bytes ±£ÁôÓò£¬Ëæ»úÊı
1 byte
	DstKeyType£º
	. PED_TIK
1 byte DstKeyLen£º8/1624 bytesDstKeyValueÄ¿µÄÃÜÔ¿Ã÷ÎÄ/ÃÜÎÄ
1 byte
	KcvMode£º
	0x00£ºÎŞÑéÖ¤
	0x01£º¶Ô8 ¸ö×Ö½ÚµÄ0x00 ¼ÆËã
	Prolin Ó¦ÓÃ±à³Ì½Ó¿Ú±à³ÌÖ¸ÄÏµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øĞĞÆæĞ£Ñé£¬ÔÙ¶Ô¡° \x12\x34\x56\x78\x90\x12\x34\x56¡±½øĞĞDES/TDES ¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x03£º´«ÈëÒ»´®Êı¾İKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô [Ä¿µÄÃÜÔ¿ÃÜÎÄ+KcvData] ½øĞĞÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV¡£
128 bytes
KcvData£º
. KcvMode Îª0x00/0x01/0x02 Ê±£¬Ìî³äËæ»úÊı£»
. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊı¾İµÄ³¤¶È£¬Ö®ºóÎªKCV Êı¾İ£¬KCV Êı¾İÖ®ºóÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½.
8 bytes
. µ±KcvMode = 0x00 Ê±£¬Ìî³äËæ»úÊı¡£
. µ±KcvMode = 0x01/0x02/0x03Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
10bytes  ³õÊ¼KSN
·µ»Ø
ERR_OK ³É¹¦
ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedWriteTIK(const unsigned char *KeyBlock);


//¹¦ÄÜÊ¹ÓÃÖ¸¶¨ÃÜÔ¿ÀàĞÍµÄÃÜÔ¿Ë÷ÒıËùÔÚµÄÃÜÔ¿Ã÷ÎÄÓëÒ»´®Êı¾İ½øĞĞÔËËã(Òì»òµÈ)£¬µÃµ½ÃÜÔ¿Ğ´Èëµ½Í¬Ò»ÀàĞÍÃÜÔ¿ÇøµÄÁíÒ»Ö¸¶¨Ë÷ÒıÎ»ÖÃ¡£
/*²ÎÊı
KeyType ÃÜÔ¿ÀàĞÍ£º
. PED_TMK
. PED_TPK
. PED_TAK
. PED_TDK
SrcKeyIdx Ô´ÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DstKeyIdx Ä¿µÄÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
KeyVar¡¾ÊäÈë¡¿
	24 ×Ö½Ú£¬ĞèÒª²ÎÓëÔËËãµÄ×Ö·û´®£»ÎªÓëÃÜÔ¿³¤¶ÈÏàÍ¬µÄ×Ö·û´®£¬ÓÃÓÚºÍÔ´Ë÷ÒıµÄÃÜÔ¿Òì»ò£»¿ÉÀ©Õ¹.
·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPENPED Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedWriteKeyVar(int KeyType,int SrcKeyIdx,int DstKeyIdx,const unsigned char *KeyVar);


//¹¦ÄÜ ÔÚÊäÈëPIN Ê±£¬ÉèÖÃ½çÃæÏÔÊ¾ĞÇºÅµÄ²¼¾ÖÊôĞÔ¡£
/*²ÎÊı
x ºá×ø±ê
y ×İ×ø±ê
fontSize ĞÇºÅµÄ×ÖÌå´óĞ¡£º
	. fontSize = 16£¬16 ¸ö×Öµã´óĞ¡µÄ×Ö·û£»
	. fontSize = 24£¬24 ¸ö×Öµã´óĞ¡µÄ×Ö·û£»
	. fontSize = 32£¬32 ¸ö×Öµã´óĞ¡µÄ×Ö·û£»
	. fontSize = 48£¬48 ¸ö×Öµã´óĞ¡µÄ×Ö·û£»
	¸Ãº¯ÊıÖĞĞÇºÅµÄÏÔÊ¾Ê¹ÓÃPED ÄÚ²¿×ÖÌåÎÄ¼ş£¬ÓëÏµÍ³Ëù×°×Ö¿âÎŞ¹Ø¡£
fontColor ĞÇºÅµÄ×ÖÌåÑÕÉ«£ºÊ¹ÓÃºê¶¨Òå RGB(_r, _g, _b)£¬¸ù¾İÊäÈëµÄÈıÔ­É«Éú³É16 Î»ÑÕÉ«Öµ¡£
align ¶ÔÆë·½Ê½£º
	PED_ASTERISK_ALIGN_LEFT£º×ó±ßÆğÊ¼Î»ÖÃ¹Ì¶¨£¬×Ô×óÏòÓÒË³ĞòÏÔÊ¾ĞÇºÅ£»
	PED_ASTERISK_ALIGN_CENTER£ºÖĞ¼äÎ»ÖÃ¹Ì¶¨£¬×óÓÒÁ½±ß¶Ô³ÆÏÔÊ¾ĞÇºÅ£»
	PED_ASTERISK_ALIGN_RIGHT£ºÓÒ±ßÆğÊ¼Î»ÖÃ¹Ì¶¨£¬×ÔÓÒÏò×óË³ĞòÏÔÊ¾ĞÇºÅ¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedSetAsteriskLayout(int x,int y,int fontSize,int fontColor,unsigned char align);

//¹¦ÄÜ ÊäÈëPIN Ê±£¬ÉèÖÃÇ°¾°ºÍ±³¾°Í¼±êµÄ²¼¾ÖÊôĞÔ¡£
/*²ÎÊı
	X¡¾ÊäÈë¡¿ Ç°¾°ºÍ±³¾°Í¼±êµÄÆğÊ¼ºá×ø±ê
	Y¡¾ÊäÈë¡¿ Ç°¾°ºÍ±³¾°Í¼±êµÄÆğÊ¼×İ×ø±ê
	Interval¡¾ÊäÈë¡¿ Á½¸öÏàÁÚÍ¼±êÖ®¼äµÄ¼ä¾à
	IconNum¡¾ÊäÈë¡¿ ±³¾°Í¼±êµÄÊıÄ¿
	PinIcon¡¾ÊäÈë¡¿Ç°¾°Í¼±ê¾ø¶ÔÂ·¾¶£¬Ö§³ÖBMP ºÍPNGÍ¼±ê
	PinIconLen ¡¾ÊäÈë¡¿Ç°¾°Í¼±ê¾ø¶ÔÂ·¾¶³¤¶È£¬×î³¤256 ×Ö½Ú
	PinIconBG ¡¾ÊäÈë¡¿±³¾°Í¼±ê¾ø¶ÔÂ·¾¶£¬Ö§³ÖBMP ºÍPNGÍ¼±ê£¬Èç²»ĞèÒª±³¾°Í¼±ê£¬¿ÉÉèÎªNULL¡£
	PinIconBGLen¡¾ÊäÈë¡¿±³¾°Í¼±êÂ·¾ø¶Ô¾¶³¤¶È£¬×î³¤256 ×Ö½Ú£»Èç²»ĞèÒª±³¾°Í¼±ê£¬¿ÉÉèÎª0¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedSetPinIconLayout(int X,int Y,int Interval,unsigned char IconNum,char *PinIcon,int PinIconLen,char *PinIconBG,int PinIconBGLen);


//¹¦ÄÜÖ¸¶¨µÄÊ±ÏŞÄÚ,É¨Ãè¼üÅÌÉÏÊäÈëExpPinLenIn Ö¸¶¨³¤¶ÈµÄPIN£¬²¢Êä³öÓÉMode Ö¸¶¨Ëã·¨¼ÓÃÜÉú³ÉµÄPIN block¡£
/*²ÎÊı
KeyIdx TPK µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1-100] ¡£
DataIn¡¾ÊäÈë¡¿
. µ±Mode=0x00 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
. µ±Mode=0x01 Ê±£¬DataIn ÎŞÒâÒå£¬¿ÉÎªÈÎÒâÖµ¡£PED ½«²ÉÓÃËæ»úÊı´úÌæDataIn ²ÎÓëPinBlock µÄ¼ÆËã¡£
. µ±Mode=0x02 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
. µ±Mode=0x03 Ê±£¬DataIn Îª½»Ò×Á÷Ë®ºÅISN ¡¾6 ×Ö½Ú£¬ASCII Âë¡¿¡£
. µ±Mode=0x10 Ê±£¬DataIn ÎŞÒâÒå£¬¿ÉÎªÈÎÒâÖµ¡£PED ½«²ÉÓÃËæ»úÊı´úÌæDataIn ²ÎÓëPinBlock µÄ¼ÆËã¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌĞò°ÑÔÊĞíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊĞíÊäÈë4 Î»¡¢6 Î»
	ÃÜÂëÇÒÔÊĞíÎŞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£Ã¶¾Ù0 ±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊı×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø¡£
Mode
	Ñ¡ÔñPIN BLOCK µÄ¸ñÊ½
		Ê¹ÓÃDES£¨3DES£©Ëã·¨¼ÓÃÜµÄPinBlockµÄ¸ñÊ½£º
		. 0x00 0x00 ISO9564 ¸ñÊ½ 0
		. 0x01 0x01 ISO9564 ¸ñÊ½ 1
		. 0x02 0x02 ISO9564 ¸ñÊ½ 3
		. 0x03 0x03 HK EPS ×¨ÓÃ¸ñÊ½
		Ê¹ÓÃAES Ëã·¨¼ÓÃÜµÄPinBlock µÄ¸ñÊ½£º
		. 0x10 PinBlock Ã÷ÎÄÇ°°Ë×Ö½ÚÎªISO9564 ¸ñÊ½ 1 µÄÃ÷ÎÄÊı¾İ£¬ºó°Ë×Ö½Ú½øĞĞ#PKCS7 Ìî³ä£¬¾ßÌåÎª8 ×Ö½ÚµÄ0x08¡£
TimeoutMs
	ÊäÈëPIN µÄ³¬Ê±Ê±¼äµ¥Î»£ººÁÃë×î´óÖµÎª3000000£º±íÊ¾Ã»ÓĞ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
PinBlock¡¾Êä³ö¡¿
	8 »ò16 ×Ö½Ú£¬Ö¸ÏòÉú³ÉµÄPIN block¡£Mode Îª0x10 Ê±£¬PinBlock ³¤¶ÈÎª16 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedGetPinBlock(int KeyIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *PinBlock);


//¹¦ÄÜ ÖØĞÂ¼ÆËãPIN block£¬²¢Ñ¡ÔñÊÇ·ñ¸ü»»TPK¡£
/*²ÎÊı 
UpdateFlag¡¾ÊäÈë¡¿:  0£º²»¸ü»»TPK£» ·Ç0£º¸ü»»TPK¡£
KeyInfo¡¾ÊäÈë¡¿
	²ÎÕÕOsPedWriteKey()ÏÂKeyBlock µÄ¶¨Òå£¬³¤¶ÈÎª184 ×Ö½Ú¡£µ±UpdateFlag Îª0 Ê±£¬KeyBlock ÏÂÖ»ÓĞDstKeyIdx ÓĞÒâÒå£¬
	²ÉÓÃDstKeyIdxÖ¸¶¨µÄTPK£¬ÖØĞÂ¼ÆËãPIN block¡£
DataIn¡¾ÊäÈë¡¿
	. µ±UpdateFlag Îª0£¬Mode=0x03 Ê±£¬Îª½»Ò×Á÷Ë®ºÅISN ¡¾6 ×Ö½Ú£¬ASCII Âë¡¿£»
	. µ±UpdateFlag Îª0£¬Mode=0x00 Ê±£¬DataIn Ç°16 ×Ö½ÚÎª¾ÉµÄPAN£¬ºó16×Ö½ÚÎªĞÂµÄPAN£¬PAN ÊÇÖ¸£º¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ£»
	. µ±UpdateFlag Îª·Ç0 Ê±£¬ ¿ÉÎªNULL¡£
PinBlock¡¾ÊäÈë/Êä³ö¡¿
	8 ×Ö½Ú£¬ÊäÈëÔ­PIN block Êı¾İ£¬Êä³öĞÂµÄPIN block
Mode
	0x00£ºISO9564 ¸ñÊ½0£»
	0x03£ºHK EPS ×¨ÓÃ¸ñÊ½¡¾Ïê¼û¸½Â¼2EPS_PINBLOCK ¸ñÊ½¡¿
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedUpdatePinBlock (int UpdateFlag,const unsigned char * KeyInfo,const unsigned char * DataIn,unsigned char * PinBlock,int Mode);


//¹¦ÄÜ ÓÃKeyIdx Ö¸¶¨µÄMAC ÃÜÔ¿¶ÔDataIn ½øĞĞMode Ö¸¶¨µÄÔËËã¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ TAK µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿Ğè½øĞĞMAC ÔËËãµÄÊı¾İ£¬³¤¶ÈĞ¡ÓÚµÈÓÚ8192 ×Ö½Ú¡£
DataInLen¡¾ÊäÈë¡¿MAC ÔËËãµÄÊı¾İ³¤¶È£¬µ±³¤¶È²»ÄÜ±»8 ×Ö½ÚÕû³ı£¬Ôò×Ô¶¯²¹¡°\x00¡±¡£
Mac¡¾Êä³ö¡¿ 8 ×Ö½Ú£¬MAC Êä³ö¡£
Mode¡¾ÊäÈë¡¿½«DataIn °´8 ×Ö½ÚÎªµ¥Î»·Ö¿é£¬ÒÀ´ÎÎªBLOCK1£¬BLOCK2£¬BLOCK3 µÈ¡£
0x00£º½«BLOCK1 ÓÃMAC ÃÜÔ¿×öDES/TDES ¼ÓÃÜ£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øĞĞÖğÎ»Òì»òºóÔÙÓÃTAK ×öDES/TDES ¼ÓÃÜ£¬ÒÀ´Î½øĞĞµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£
0x01£º½«BLOCK1 ºÍBLOCK2 ½øĞĞÖğÎ»Òì»ò£¬Òì»ò½á¹ûÓëBLOCK3 ½øĞĞÖğÎ»Òì»ò£¬ÒÀ´Î½øĞĞ£¬×îºóµÃµ½8 ×Ö½ÚµÄÒì»ò½á¹û£¬½«¸Ã½á¹ûÓÃTAK ½øĞĞDES/TDES ¼ÓÃÜÔËËã¡£
0x02£ºÒÀ¾İANSIX9.19 ¹æ·¶£¬½«BLOCK1 ÓÃTAK×öDES ¼ÓÃÜ(Ö»È¡Ç°8 ¸ö×Ö½ÚµÄÃÜÔ¿)£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øĞĞÖğÎ»Òì»òºóÔÙÓÃTAK ×öDES ¼ÓÃÜ£¬ÒÀ´Î½øĞĞµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û£¬×îºó²ÉÓÃDES/TDES ¼ÓÃÜ¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedGetMac(int KeyIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,int Mode);


//¹¦ÄÜÊ¹ÓÃTDK ¶ÔDataInLen ³¤¶ÈµÄÊı¾İ½øĞĞDES/TDES ½âÃÜ»ò¼ÓÃÜÔËËã£¬Êä³öÃ÷ÎÄ»òÃÜÎÄ£»Ò»¸öÖ¸¶¨µÄTDK£¬Ö»ÄÜÓÃÓÚ¼ÓÃÜ»ò½âÃÜÔËËã¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ TDK Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
InitVector¡¾ÊäÈë¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬³¤¶ÈÎª8 ×Ö½Ú¡£µ±Mode=0x02/0x03/0x04/0x05 Ê±,ĞèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬
				ÎªNULL Ê±Ä¬ÈÏÎª¡°\x00\x00\x00\x00\x00\x00\x00\x00¡±£»µ±Mode=0x00/0x01 Ê±£¬²»ĞèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòĞèÒª½øĞĞÔËËãµÄÊı¾İ¡£
DataInLen¡¾ÊäÈë¡¿ĞèÒªÔËËãµÄÊı¾İ³¤¶È£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬Ó¦Ğ¡ÓÚµÈÓÚ1024£»
	µ±Mode Îª0x00~0x05 Ê±£¬±ØĞëÎª8 µÄ±¶Êı£»
	µ±Mode Îª0x06~0x07 Ê±£¬¿ÉÒÔ²»ÊÇ8 µÄ±¶Êı¡£
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊı¾İ¡£
Mode¡¾ÊäÈë¡¿
. 0x00£ºECB ½âÃÜ
. 0x01£ºECB ¼ÓÃÜ
. 0x02£ºCBC ½âÃÜ
. 0x03£ºCBC ¼ÓÃÜ
. 0x04£ºOFB ½âÃÜ
. 0x05£ºOFB ¼ÓÃÜ
. 0x06£ºCFB8 ½âÃÜ
. 0x07£ºCFB8 ¼ÓÃÜ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedDes(int KeyIdx,unsigned char * InitVector,const unsigned char *DataIn,int DataInLen,unsigned char *DataOut,int Mode);


//¹¦ÄÜ»ñÈ¡ÃÜÔ¿µÄKCV Öµ£¬ÒÔ¹©¶Ô»°Ë«·½½øĞĞÃÜÔ¿ÑéÖ¤£ºÃÜÔ¿ÀàĞÍ·ÇTIK Ê±£¬ÓÃÖ¸¶¨µÄÃÜÔ¿¼°Ëã·¨¶ÔÒ»¶ÎÊı¾İ½øĞĞ¼ÓÃÜ£¬²¢·µ»ØÊı¾İÃÜÎÄµÄÇ°3 ×Ö½Ú£»ÃÜÔ¿ÀàĞÍÎªTIK Ê±£¬·µ»ØÓëTIK Ò»²¢×¢Èë(¼ÆËãµÃµ½)µÄ8 ×Ö½ÚKCV¡£
/*²ÎÊı
KeyType ÃÜÔ¿ÀàĞÍ£º
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
. PED_TIK
. PED_SM4_TMK
. PED_SM4_TPK
. PED_SM4_TAK
. PED_SM4_TDK
KeyIdx ÃÜÔ¿µÄË÷ÒıºÅ£¬Èç£º
. TLK£¬Ö»ÄÜÎª1¡£
. TMK ¿ÉÈ¡Öµ1~100¡£
. TWK ¿ÉÈ¡Öµ1~100¡£
. TIK ¿ÉÈ¡Öµ1~100¡£
KcvMode  KCV Ğ£ÑéÄ£Ê½
	0x00£ºÊ¹ÓÃDES Ëã·¨¼ÆËãÃÜÔ¿µÄKCV£»
	0x04£ºÊ¹ÓÃSM4 Ëã·¨¼ÆËãSM4 ÃÜÔ¿µÄKCV£¬´ËÊ±ÃÜÔ¿ÀàĞÍÖ»ÄÜÎªSM4 ÏµÁĞµÄÃÜÔ¿¡££¨ KeyType Ö»ÄÜÊÇPED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK£©
KcvDataLen ²ÎÓë¼ÆËãKCV µÄÊı¾İ³¤¶È£¬²»³¬¹ı128 ×Ö½Ú£¬ÇÒ±»8 Õû³ı£»ÃÜÔ¿ÀàĞÍÎªTIK Ê±¿ÉÎª0£»KCVĞ£ÑéÄ£Ê½Îª0x04 Ê±£¬¸ÃÊı¾İ³¤¶È±ØĞëÄÜ±»16Õû³ı¡£
KcvData¡¾ÊäÈë¡¿²ÎÓë¼ÆËãKCV µÄÊı¾İ£¬ÃÜÔ¿ÀàĞÍÎªTIK Ê±¿ÉÎªNULL¡£
Kcv¡¾Êä³ö¡¿
	KCV Öµ£¬3 »ò8 ×Ö½Ú¡£ÃÜÔ¿ÀàĞÍÎªTIK Ê±£¬
	KCV Îª8 ×Ö½Ú£¬ÆäÓàÎª3 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı	*/
int OsPedGetKcv(int KeyType,int KeyIdx,int KcvMode,int KcvDataLen,unsigned char *KcvData,unsigned char *Kcv);


//¹¦ÄÜÓÃSrcKeyIdx Ö¸¶¨µÄÃÜÔ¿¶ÔDstFromKeyIdx Ö¸¶¨µÄÃÜÔ¿½øĞĞ¼ÓÃÜ»ò½âÃÜ£¬·¢É¢ĞÂÃÜÔ¿£¬²¢½«½á¹û±£´æµ½DstToKeyIdx Ö¸¶¨µÄÃÜÔ¿¡£
/*²ÎÊı
SrcKeyType Ô´ÃÜÔ¿ÀàĞÍ£º
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
SrcKeyIdx Ô´ÃÜÔ¿µÄË÷ÒıºÅ£¬Èç£º
. TLK£¬Ö»ÄÜÎª1¡£
. TMK ¿ÉÈ¡Öµ1~100¡£
. TWK ¿ÉÈ¡Öµ1~100¡£
DstKeyType Ä¿µÄÃÜÔ¿ÀàĞÍ£º
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
DstFromKeyIdx Ä¿µÄÃÜÔ¿Ô´Ë÷ÒıºÅ
DstToKeyIdx Ä¿µÄÃÜÔ¿Ä¿µÄË÷ÒıºÅ
Mode
	0x00£ºDES/TDES ½âÃÜ
	0x01£ºDES/TDES ¼ÓÃÜ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedDeriveKey(int SrcKeyType,int SrcKeyIdx,int DstKeyType,int DstFromKeyIdx,int DstToKeyIdx,int Mode);

//¹¦ÄÜ Ê¹ÓÃFramebuffer Êı¾İ»òÕßÍ¼Æ¬Êı¾İÉèÖÃPIN ÊäÈëÊ±µÄ±³¾°¡£
/*²ÎÊı
Mode¡¾ÊäÈë¡¿PIN ÊäÈë±³¾°µÄÉèÖÃ·½Ê½£º
	Mode = 0x00£¬Çå³ı¸Ã½Ó¿ÚµÄÉèÖÃ£»
	Mode = 0x01£¬Ê¹ÓÃFramebuffer Êı¾İÉèÖÃPIN ÊäÈëÊ±µÄ±³¾°£»
	Mode = 0x02£¬Ê¹ÓÃÍ¼Æ¬Êı¾İÉèÖÃPINÊäÈëÊ±µÄ±³¾°¡£
Bg¡¾ÊäÈë¡¿´æ·ÅFramebuffer Êı¾İ»òÕßÍ¼Æ¬Êı¾İµÄBuffer¡£
BgLen¡¾ÊäÈë¡¿´æ·ÅFramebuffer Êı¾İ»òÕßÍ¼Æ¬Êı¾İBuffer µÄ³¤¶È¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedSetPinBg(unsigned char Mode,const unsigned char *Bg,int BgLen);



//¹¦ÄÜ ¶¨ÖÆ»¯PED Èí¼üÅÌ¡£
/*²ÎÊı
IconPath ¡¾ÊäÈë¡¿´æ·Å¼üÅÌÍ¼Æ¬µÄ¾ø¶ÔÂ·¾¶£¬²»Ö§³ÖÏà¶ÔÂ·¾¶£¬Â·¾¶³¤¶È×î³¤²»³¬¹ı256×Ö½Ú£¬¿ÉÎªNULL¡£µ±IconPath ÎªNULL Ê±£¬ÏµÍ³Ê¹ÓÃÄ¬ÈÏµÄÍ¼Æ¬¡£
KeypadColorBg ¡¾ÊäÈë¡¿¼üÅÌµÄ±³¾°É«RGBA Öµ£¬³¤¶ÈÎª4×Ö½Ú£¬¿ÉÎªNULL¡£µ±KeypadColorBg ÎªNULL Ê±£¬ÏµÍ³Ê¹ÓÃÄ¬ÈÏµÄ¼üÅÌ±³¾°É«¡£
Mode ¡¾ÊäÈë¡¿ÉèÖÃÄ£Ê½£º
	Mode = 0x00 Ê±£¬Ê¹ÓÃÏµÍ³Ä¬ÈÏµÄ¼üÅÌÍ¼Æ¬ÒÔ¼°±³¾°ÑÕÉ«£»
	Mode = 0x01 Ê±£¬Ê¹ÓÃÓÃ»§Ö¸¶¨µÄ¼üÅÌÍ¼Æ¬»òÕßÓÃ»§Ö¸¶¨µÄ¼üÅÌ±³¾°ÑÕÉ«¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_FILE_NOT_EXIST Í¼Æ¬×ÊÔ´ÎÄ¼ş²»´æÔÚ
	ERR_VERIFY_SIGN_FAIL Í¼Æ¬×ÊÔ´ÎÄ¼şÑéÇ©Ê§°Ü */
int OsPedCustomKeypad(char *IconPath,unsigned char *KeypadColor,unsigned char Mode);


//¹¦ÄÜÖ¸¶¨µÄÊ±ÏŞÄÚ£¬É¨Ãè¼üÅÌÉÏÊäÈëµÄPIN£¬²¢Êä³öÊ¹ÓÃDUKPT µÄPIN ÃÜÔ¿¼ÆËãÉú³ÉµÄPIN block¡£
/*²ÎÊı
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿
	1. µ±Mode=0x20 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
	2. µ±Mode=0x21 Ê±£¬ÎŞÒâÒå¡£
	3. µ±Mode=0x22 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
	4. µ±Mode=0x23 Ê±£¬Îª½»Ò×Á÷Ë®ºÅISN ¡¾6×Ö½Ú£¬ASCII Âë¡¿¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌĞò°ÑÔÊĞíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊĞíÊäÈë4¡¢
	6 Î»ÃÜÂë²¢ÇÒÔÊĞíÎŞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊı×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø¡£
Mode¡¾ÊäÈë¡¿Ñ¡ÔñPIN block µÄ¸ñÊ½£º
. 0x20 ISO9564 ¸ñÊ½0£¬KSN ²»×Ô¶¯¼Ó1
. 0x21 ISO9564 ¸ñÊ½1£¬KSN ²»×Ô¶¯¼Ó1
. 0x22 ISO9564 ¸ñÊ½2£¬KSN ²»×Ô¶¯¼Ó1
. 0x23 HK EPS ¸ñÊ½£¬KSN ²»×Ô¶¯¼Ó1
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë¡£×î´óÖµÎª300000
	0£º±íÊ¾Ã»ÓĞ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
Ksn¡¾Êä³ö¡¿ 10 ×Ö½Ú£¬Ö¸Ïòµ±Ç°µÄKSN¡£
PinBlock¡¾Êä³ö¡¿ 8 ×Ö½Ú£¬Ö¸ÏòÉú³ÉµÄPIN block¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedGetPinDukpt(int GroupIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *Ksn,unsigned char *PinBlock);


//¹¦ÄÜ Ê¹ÓÃDUKPT ÃÜÔ¿¼ÆËãMAC Öµ¡£
/*²ÎÊı
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòĞèÒª¼ÆËãMAC µÄÊı¾İÄÚÈİ¡£
DataInLen¡¾ÊäÈë¡¿Êı¾İµÄ³¤¶È£¬Ğ¡ÓÚµÈÓÚ8192 ×Ö½Ú£¬µ±²»Îª8×Ö½ÚÕû³ıÊ±×Ô¶¯²¹¡°\x00¡±¡£
Mac¡¾Êä³ö¡¿ Ö¸ÏòµÃµ½µÄMAC¡£
Ksn¡¾Êä³ö¡¿ Ö¸Ïòµ±Ç°µÄKSN¡£
Mode¡¾ÊäÈë¡¿½«DataIn °´8 ×Ö½ÚÎªµ¥Î»·Ö¿é£¬ÒÀ´ÎÎªBLOCK1£¬BLOCK2£¬BLOCK3 µÈ¡£
	0x20£º½«BLOCK1 ÓÃMAC ÃÜÔ¿×öTDES ¼ÓÃÜ£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øĞĞÖğÎ»Òì»òºóÔÙÓÃTAK ×öTDES ¼ÓÃÜ£¬ÒÀ´Î½øĞĞµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£
	0x21£º½«BLOCK1 ºÍBLOCK2 ½øĞĞÖğÎ»Òì»ò£¬Òì»ò½á¹ûÓëBLOCK3 ½øĞĞÖğÎ»Òì»ò£¬ÒÀ´Î½øĞĞ£¬×îºóµÃµ½8 ×Ö½ÚµÄÒì»ò½á¹û£¬½«¸Ã½á¹ûÓÃTAK ½øĞĞTDES¼ÓÃÜÔËËã¡£
	0x22£ºÒÀ¾İANSIX9.19 ¹æ·¶£¬½«BLOCK1ÓÃTAK ×öDES ¼ÓÃÜ(Ö»È¡Ç°8 ¸ö×Ö½ÚµÄkey)£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øĞĞÖğÎ»Òì»òºóÔÙÓÃTAK ×öDES ¼ÓÃÜ£¬ÒÀ´Î½øĞĞµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û£¬Ö±µ½×îºóÒ»´Î²ÉÓÃTDES ¼ÓÃÜ¡£
	. 0x20/0x21/0x22/0x40/0x41/0x42KSN ²»×Ô¶¯¼Ó1¡£
	. 0x40/0x41/0x42 ¼ÆËãMAC ·½Ê½Óë0x20/0x21/0x22 ÏàÍ¬¡£
	. 0x40/0x41/0x42 Ñ¡ÔñÓ¦´ğMAC ÃÜÔ¿£¬0x20/0x21/0x22KSN Ñ¡ÔñÇëÇó»òÓ¦´ğMAC ÃÜÔ¿¡£
	. ÆäËüÖµ±£ÁôÀ©Õ¹MAC Ëã·¨¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedGetMacDukpt(int GroupIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,unsigned char *Ksn,int Mode);


//¹¦ÄÜ Ê¹ÓÃDUKPT ÃÜÔ¿£¬¶ÔÊäÈëÊı¾İ½øĞĞ¼Ó½âÃÜ¡£
/*²ÎÊı
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
KeyVarType¡¾ÊäÈë¡¿
	0x00£ºÊ¹ÓÃÓ¦´ğ»òÇëÇóMAC ÃÜÔ¿
	0x01£ºÊ¹ÓÃDUKPT DES ÃÜÔ¿
	0x02£ºÊ¹ÓÃPIN variant Îªdata ¼ÓÃÜ£¬ECBºÍCBC ¼ÓÃÜ¿ÉÓÃ£¬¼´Mode Öµ¿ÉÎª0x01 ºÍ0x03¡£µ±DUKPT ÃÜÔ¿Îª8×Ö½ÚÊ±£¬Ê¹ÓÃµÄ²»ÊÇ±ê×¼µÄDES Ëã·¨£¬¶øÊÇANSI9.24-1998 ¶¨ÒåµÄÌØÊâDES Ëã·¨¡£
	0x03£ºÊ¹ÓÃÓ¦´ğMAC ÃÜÔ¿£¬½öÖ§³Ö¼ÓÃÜÄ£Ê½£¬¼´Mode ÖµÖ»ÄÜÎª0x01¡¢0x03¡¢0x05
	0x04£ºÊ¹ÓÃÓ¦´ğDES ÃÜÔ¿£¬½öÖ§³Ö¼ÓÃÜÄ£Ê½£¬¼´Mode ÖµÖ»ÄÜÎª0x01¡¢0x03¡¢0x05
InitVector¡¾ÊäÈë¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬8 ×Ö½Ú
	µ±Mode=0x02/0x03/0x04/0x05 Ê±,ĞèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬ÎªNULL Ê±Ä¬ÈÏÎª¡°\x00\x00\x00\x00\x00\x00\x00\x00¡±£»
	µ±Mode=0x00/0x01 Ê±£¬²»ĞèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
DataInLen¡¾ÊäÈë¡¿ ĞèÒª¼Ó½âÃÜµÄÊı¾İ³¤¶È£¬Ğ¡ÓÚµÈÓÚ 8192
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòĞèÒª½øĞĞÔËËãµÄÊı¾İ
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊı¾İ
Ksn¡¾Êä³ö¡¿ Ö¸Ïòµ±Ç°µÄKSN£¬10 ×Ö½Ú
Mode¡¾ÊäÈë¡¿¼Ó½âÃÜÄ£Ê½£º
. 0x00£ºECB ½âÃÜ
. 0x01£ºECB ¼ÓÃÜ
. 0x02£ºCBC ½âÃÜ
. 0x03£ºCBC ¼ÓÃÜ
. 0x04£ºOFB ½âÃÜ
. 0x05£ºOFB ¼ÓÃÜ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedDesDukpt(int GroupIdx,int KeyVarType,unsigned char *InitVector,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *Ksn,int Mode);



//¹¦ÄÜ »ñÈ¡µ±Ç°µÄKSN Öµ¡£
/*²ÎÊı
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
Ksn¡¾Êä³ö¡¿ Ö¸Ïòµ±Ç°KSN£¬10 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedGetKsnDukpt(int GroupIdx,unsigned char *Ksn);

//¹¦ÄÜ Ôö¼ÓÖ¸¶¨DUKPT ×éµÄKSN Öµ¡£
/*²ÎÊı 
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒıºÅ£¬ È¡Öµ·¶Î§Îª[1~100]¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedIncreaseKsnDukpt(int GroupIdx);


//¹¦ÄÜ ¶ÁÈ¡RSA ¹«Ô¿¡£
/*²ÎÊı
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
RsaKey¡¾Êä³ö¡¿ RSA ¹«Ô¿½á¹¹ÌåST_RSA_KEY
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedReadRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey);

//¹¦ÄÜ ×¢ÈëRSA ÃÜÔ¿µ½PED¡£
/*²ÎÊı
RsaKeyIdx¡¾ÊäÈë¡¿ RSA ÃÜÔ¿µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
RsaKey¡¾ÊäÈë¡¿Ö¸ÏòĞèÒª×¢ÈëPED µÄRSA ÃÜÔ¿½á¹¹ÌåST_RSA_KEY¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedWriteRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey);

//¹¦ÄÜ ÓÃ´æ´¢ÔÚPED µÄRSA ÃÜÔ¿½øĞĞRSA Êı¾İÔËËã¡£
/*²ÎÊı
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
DataInLen¡¾ÊäÈë¡¿ĞèÒª½øĞĞÔËËãµÄÊı¾İ³¤¶È£¬µ¥Î»Îª×Ö½Ú£¬ÓëRSA ÃÜÔ¿µÄÄ£³¤ÏàÍ¬¡£³¤¶ÈÖµÎª64 µ½512 Ö®¼ä8 µÄ±¶Êı¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòĞèÒª½øĞĞÔËËãµÄÊı¾İ
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊı¾İ
KeyInfo¡¾Êä³ö¡¿ ÃÜÔ¿ĞÅÏ¢
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedRsaRecover(int KeyIdx,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *KeyInfo);


//¹¦ÄÜ ¶ÁÈ¡RSA ÃÜÔ¿ÃÜÎÄ¡£
/*²ÎÊı
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
CipherRsaKey¡¾Êä³ö¡¿ Ö¸ÏòRSA ÃÜÔ¿ÃÜÎÄ
·µ»Ø
	>0 ±íÊ¾RSA ÃÜÔ¿ÃÜÎÄµÄ³¤¶È
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedReadCipherRsaKey(int RsaKeyIdx,unsigned char *CipherRsaKey);


//¹¦ÄÜ Ğ´RSA ÃÜÔ¿ÃÜÎÄ¡£
/*²ÎÊı
RsaKeyIdx¡¾ÊäÈë¡¿  RSA Key µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
CipherRsaKeyLen¡¾ÊäÈë¡¿ Ğ´ÈëµÄRSA ÃÜÔ¿ÃÜÎÄÊı¾İµÄ×Ö½Ú³¤¶È£¬Ğ¡ÓÚµÈÓÚ1024
CipherRsaKey¡¾ÊäÈë¡¿ Ö¸ÏòRSA ÃÜÔ¿ÃÜÎÄ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedWriteCipherRsaKey(int RsaKeyIdx,int CipherRsaKeyLen,unsigned char *CipherRsaKey);


//¹¦ÄÜ ½«Ò»¸öAES ÃÜÔ¿µÄÃÜÎÄ»òÕßÃ÷ÎÄĞ´Èëµ½AES ÃÜÔ¿ÇøÓòµÄÖ¸¶¨Ë÷ÒıµÄÎ»ÖÃ£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕıÈ·ĞÔ¡£
/*²ÎÊı KeyBlock¡¾ÊäÈë¡¿
1 byte ¸ñÊ½£º0x03
1 byte SrcKeyType£º
	. PED_TLK
	. PED_TMK
1 byte
	SrcKeyIdx£º
	. µ±SrcKeyType = PED_TLK Ê±£¬SrcKeyIdx = 1£»
	. µ±SrcKeyType = PED_TMKÊ±£¬SrcKeyIdx = [1~100]£»
	. µ±SrcKeyIdx = 0£¬ÃÜÔ¿½«ÒÔÃ÷ÎÄĞÎÊ½Ğ´ÈëPED¡£
1 byte DstKeyIdx£º[1~100]
7 bytes ±£ÁôÓò£¬Ëæ»úÊı
1 byte
	DstKeyType£º
	. PED_TAESK
	. PED_AES_TPK
	. PED_AES_TAK
	. PED_AES_TDK
1 byte DstKeyLen£º16/24/32
32 bytes DstKeyValue£ºÄ¿µÄÃÜÔ¿Ã÷ÎÄ/ÃÜÎÄ
1 byte  KcvMode£º
	0x00£ºÎŞÑéÖ¤¡£
	0x01£º¶Ô16 ¸ö×Ö½ÚµÄÈ«0x00 ¼ÆËãAES/ECB ¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV µÄÖµ¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øĞĞÆæĞ£Ñé£¬ÔÙ¶Ô¡° \x12\x34\x56\x78\x90\x12\x34\x56\x12\x34\x56\x78\x90\x12\x34\x56¡±½øĞĞAES/ECB¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3¸ö×Ö½Ú¼´ÎªKCV µÄÖµ¡£
	0x03£º´«ÈëÒ»´®Êı¾İKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô[ Ä¿µÄÃÜÔ¿ÃÜÎÄ+KCV Êı¾İ]½øĞĞÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV µÄÖµ¡£
128 bytes
	KcvData£º
	. KcvMode Îª0x00/0x01/0x02 Ê±£¬Ìî³äËæ»úÊı£»
	. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊı¾İµÄ³¤¶È£¬Ö®ºóÎªKCV Êı¾İ£¬KCV Êı¾İÖ®ºóµÚÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½¡£
8 bytes
. µ±KcvMode=0x00 Ê±£¬Ìî³äËæ»úÊı£»
. µ±KcvMode=0x01/0x02/0x03 Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
2 bytes Ìî³äËæ»úÊı
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedWriteAesKey(const unsigned char *KeyBlock);


//¹¦ÄÜ Ê¹ÓÃTAESK »òPED_AES_TDK ÃÜÔ¿¶ÔDataInLen Ö¸¶¨³¤¶ÈµÄÊı¾İ½øĞĞAES ¼Ó½âÃÜÔËËã¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ TAESK ÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
InitVector ¡¾ÊäÈë/Êä³ö¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£
µ±Mode=0x02/0x03/0x04/0x05 Ê±,ĞèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬ÎªNULL Ê±Ä¬ÈÏÎª16 ×Ö½ÚµÄÈ«0x00¡£
µ±Mode=0x00/0x01 Ê±£¬²»ĞèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
µ±Mode=0x06/0x07 Ê±£¬±íÊ¾ÔËËãÊ±ËùĞèµÄ16 ×Ö½Ú³¤¶ÈµÄÁÙÊ±¼ÆÊıÆ÷£¬ÔËËã³É¹¦ºó¸Ã¼ÆÊıÆ÷½«±»¸üĞÂ¡£
DataIn¡¾ÊäÈë¡¿ ĞèÒª½øĞĞÔËËãµÄÊı¾İ
DataInLen¡¾ÊäÈë¡¿ĞèÒª½øĞĞÔËËãµÄÊı¾İ³¤¶È£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬Ó¦Ğ¡ÓÚµÈÓÚ1024£¬ÇÒÎª16 µÄ±¶Êı¡£µ±ÔËËãÄ£Ê½ÎªCTR Ä£Ê½Ê±£¬Êı¾İ³¤¶ÈÃ»ÓĞÏŞÖÆ¡£
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊı¾İ¡£
Mode ¡¾ÊäÈë¡¿
. 0x00£ºECB ½âÃÜÄ£Ê½
. 0x01£ºECB ¼ÓÃÜÄ£Ê½
. 0x02£ºCBC ½âÃÜÄ£Ê½
. 0x03£ºCBC ¼ÓÃÜÄ£Ê½
. 0x04£ºOFB ½âÃÜÄ£Ê½
. 0x05£ºOFB ¼ÓÃÜÄ£Ê½
. 0x06£ºCTR ½âÃÜÄ£Ê½
. 0x07£ºCTR ¼ÓÃÜÄ£Ê½
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ÎŞĞ§µÄ²ÎÊı */
int OsPedAes(int KeyIdx,unsigned char*InitVector,const unsigned char*DataIn,int DataInLen,unsigned char *DataOut,int Mode);



//¹¦ÄÜ Éú³ÉÒ»×éSM2 ÃÜÔ¿¶Ô¡£
/*²ÎÊı
PvtKey¡¾Êä³ö¡¿ Ö¸ÏòSM2 Ë½Ô¿£¬32 ×Ö½Ú
PubKey¡¾Êä³ö¡¿ Ö¸ÏòSM2 ¹«Ô¿£¬64 ×Ö½Ú
KeyLenBit¡¾ÊäÈë¡¿ Ë½Ô¿Î»Êı£¬256 Î»
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó */
int OsPedGenSM2Pair(unsigned char *PvtKey,unsigned char *PubKey,int KeyLenBit);



//¹¦ÄÜ ×¢ÈëSM2 Ë½Ô¿»ò¹«Ô¿µ½PED¡£
/*²ÎÊı
KeyIdx ¡¾ÊäÈë¡¿ SM2 ÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~20]
KeyType¡¾ÊäÈë¡¿ÃÜÔ¿ÀàĞÍ£º
	PED_SM2_PVT_KEY 0x30 Ë½Ô¿
	PED_SM2_PUB_KEY 0x31 ¹«Ô¿
KeyValue ¡¾ÊäÈë¡¿
	µ±KeyType=0x30 Ê±£¬KeyValue ³¤¶ÈÎª32 ×Ö½Ú
	µ±KeyType=0x31 Ê±£¬KeyValue ³¤¶ÈÎª64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó */
int OsPedWriteSM2Key(int KeyIdx,int KeyType,unsigned char *KeyValue);


//¹¦ÄÜ Ê¹ÓÃ SM2 Ëã·¨»ñµÃÇ©ÃûĞÅÏ¢¡£
/*²ÎÊı
PubKeyIdx¡¾ÊäÈë¡¿ SM2 ¹«Ô¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~20]
PvtKeyIdx¡¾ÊäÈë¡¿ SM2 Ë½Ô¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Uid¡¾ÊäÈë¡¿ Ç©ÃûÕßIDÎŞÌØÊâÔ¼¶¨µÄÇé¿ö£¬ÓÃ»§Éí·İµÄ±êÊ¶ID³¤¶ÈÎª16 ×Ö½Ú£¬
			ÆäÄ¬ÈÏÖµÎª0x31, 0x32,0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38¡£
UidLen¡¾ÊäÈë¡¿ Ç©ÃûÕßID ³¤¶È£¬Ğ¡ÓÚµÈÓÚ512 ×Ö½Ú¡£
Input¡¾ÊäÈë¡¿ ĞèÒªÇ©ÃûµÄÊı¾İ
InputLen¡¾ÊäÈë¡¿ Êı¾İ³¤¶È£¬Ğ¡ÓÚµÈÓÚ2048 ×Ö½Ú
Signature¡¾ÊäÈë¡¿ Ç©ÃûÖµ£¬64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Sign(int PubKeyIdx,int PvtKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,unsigned char *Signature);


//¹¦ÄÜ Ê¹ÓÃ SM2 ¹«Ô¿ÑéÖ¤Ç©Ãû¡£
/*²ÎÊı
PubKeyIdx¡¾ÊäÈë¡¿ SM2 ¹«Ô¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Uid¡¾ÊäÈë¡¿ Ç©ÃûÕßID¡£ÎŞÌØÊâÔ¼¶¨µÄÇé¿ö£¬ÓÃ»§Éí·İµÄ±êÊ¶ID
µÄ³¤¶ÈÎª16 ×Ö½Ú£¬ÆäÄ¬ÈÏÖµÎª0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38¡£
UidLen¡¾ÊäÈë¡¿ Ç©ÃûÕßID ³¤¶È£¬Ğ¡ÓÚµÈÓÚ512 ×Ö½Ú
Input¡¾ÊäÈë¡¿ ĞèÒªÇ©ÃûµÄÊı¾İ
InputLen¡¾ÊäÈë¡¿ Êı¾İ³¤¶È£¬Ğ¡ÓÚµÈÓÚ2048 ×Ö½Ú
Signature¡¾ÊäÈë¡¿ Ç©ÃûÖµ£¬64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_VERIFY_SIGN_FAIL ÑéÖ¤Ç©ÃûÊ§°Ü
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Verify(int PubKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,const unsigned char *Signature);

//¹¦ÄÜ Ê¹ÓÃ SM2 ¹«Ô¿¼ÓÃÜÊı¾İ»òË½Ô¿½âÃÜÊı¾İ¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ SM2 ÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Input¡¾ÊäÈë¡¿ ´ı¼ÓÃÜ»ò½âÃÜµÄÊı¾İ
InputLen¡¾ÊäÈë¡¿ Êı¾İ³¤¶È£¬¼ÓÃÜ²Ù×÷Ê±Ğ¡ÓÚµÈÓÚ£¨2048-96£©×Ö½Ú£¬½âÃÜ²Ù×÷Ê±Ğ¡ÓÚµÈÓÚ2048 ×Ö½Ú¡£
Output¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊı¾İ
OutputLen¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊı¾İ³¤¶È£¬¼ÓÃÜºóÊı¾İ³¤¶ÈÎªÔ­Êı¾İ³¤¶È+96 ×Ö½Ú£¬½âÃÜºóÊı¾İ³¤¶ÈÎªÔ­Êı¾İ³¤¶È-96 ×Ö½Ú¡£
Mode¡¾ÊäÈë¡¿ PED_DECRYPT0x00£ºÊ¹ÓÃSM2 Ë½Ô¿½âÃÜÊı¾İPED_ENCRYPT0x01£ºÊ¹ÓÃSM2 ¹«Ô¿¼ÓÃÜÊı¾İ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Recover(int KeyIdx,unsigned char *Input,int InputLen,unsigned char *Output,int *OutputLen,int Mode);

//¹¦ÄÜ Ê¹ÓÃ SM3 Ëã·¨¼ÆËãÔÓ´ÕÖµ¡£
/*²ÎÊı
Input¡¾ÊäÈë¡¿ ÊäÈëÊı¾İ
InputLen¡¾ÊäÈë¡¿ ÊäÈëÊı¾İ³¤¶È
Output¡¾Êä³ö¡¿ ÔÓ´ÕÖµ£¬32 ×Ö½Ú¡£
Mode¡¾ÊäÈë¡¿ Ö§³Ö0x00£¬ÆäËüÖµ±£Áô¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó */
int OsPedSM3(unsigned char *Input,int InputLen,unsigned char *Output,int Mode);


//¹¦ÄÜ Ê¹ÓÃSM4 Ëã·¨¼ÓÃÜ»ò½âÃÜÊı¾İ¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TDK µÄË÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
InitVector¡¾ÊäÈë¡¿ ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£¶ÔÓÚECB Ä£Ê½¸Ã²ÎÊıÎªNULL¡£
Input¡¾ÊäÈë¡¿ ĞèÒª¼ÓÃÜ»ò½âÃÜµÄÊı¾İ
InputLen¡¾ÊäÈë¡¿ Êı¾İ³¤¶ÈĞ¡ÓÚµÈÓÚ1024£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬ÇÒÎª16 µÄ±¶Êı
Output¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊı¾İ£¬³¤¶ÈÎªÊäÈë³¤¶È
Mode¡¾ÊäÈë¡¿ 
PED_SM4_ECB_DECRYPT 0x00:SM4 ECB ½âÃÜ
PED_SM4_ECB_ENCRYPT 0x01:SM4 ECB ¼ÓÃÜ
PED_SM4_CBC_DECRYPT 0x02:SM4 CBC ½âÃÜ
PED_SM4_CBC_ENCRYPT 0x03:SM4 CBC ¼ÓÃÜ
·µ»Ø 
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó */
int OsPedSM4(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *Output,int Mode);


//¹¦ÄÜ Ê¹ÓÃSM4 Ëã·¨¼ÆËãMAC¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TAK µÄÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
InitVector¡¾ÊäÈë¡¿ ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£
Input¡¾ÊäÈë¡¿ ĞèÒª½øĞĞMAC ÔËËãµÄÊı¾İ
InputLen¡¾ÊäÈë¡¿ Êı¾İ³¤¶ÈĞ¡ÓÚµÈÓÚ1024£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬ÇÒÎª16 µÄ±¶Êı
MacOut¡¾Êä³ö¡¿ MAC Öµ
Mode¡¾ÊäÈë¡¿ 
	0x00£ºÊ¹ÓÃSM4 CBC Ëã·¨¼ÆËãMAC Öµ£¬Ê×ÏÈ½«³õÊ¼ÏòÁ¿ÓëBLOCK1 ½øĞĞÒì»ò£¬²¢ÓÃSM4Ëã·¨Ê¹ÓÃTAK¶ÔÒì»òµÄ½á¹û½øĞĞ¼ÓÃÜ£¬
			È»ºó»ñµÃµÄÃÜÎÄÓëBLOCK2 Òì»ò£¬ÓÃSM4 Ëã·¨Ê¹ÓÃTAK ¶Ô½á¹û¼ÓÃÜ£¬°´Ë³Ğò¸ø³ö16 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£MacOut Îª16 ×Ö½Ú¡£
	0x01£ºÊ¹ÓÃSM4-TAK ÃÜÔ¿¶ÔÊäÈëÊı¾İ¼ÆËãSM3 Hash£¬¼ÆËã½á¹û×÷ÎªMacOut(32 ×Ö½Ú)¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó */
int OsPedGetMacSM(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *MacOut,int Mode);


//¹¦ÄÜ Ö¸¶¨µÄÊ±ÏŞÄÚ£¬É¨Ãè¼üÅÌÉÏÊäÈëµÄPIN ²¢Êä³ö²ÉÓÃSM4 Ëã·¨Éú³ÉµÄPIN block ¼ÓÃÜÊı¾İ¿é¡£
/*²ÎÊı
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TPK µÄÃÜÔ¿Ë÷ÒıºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
ExpPinLenIn¡¾ÊäÈë¡¿ ¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£
Ó¦ÓÃ³ÌĞò°ÑÔÊĞíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊĞíÊäÈë4¡¢6 Î»ÃÜÂë£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°4,6¡±¡£
DataIn¡¾ÊäÈë¡¿ µ±Mode=0x00 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
PinBlockOut¡¾Êä³ö¡¿ Éú³ÉµÄÃÜÎÄPIN block£¬16 ×Ö½Ú
Mode¡¾ÊäÈë¡¿ PIN block µÄ¸ñÊ½0x00 ISO9564 ¸ñÊ½0
TimeoutMs¡¾ÊäÈë¡¿ ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë¡£×î´óÖµÎª300000ms¡£0 ±íÊ¾²ÉÓÃÄ¬ÈÏ³¬Ê±Ê±¼ä30000ms¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òı´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàĞÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó
	ERR_PED_NO_PIN_INPUT Î´ÊäÈëÈÎºÎ¼üÖµ
	ERR_PED_PIN_INPUT_CANCEL È¡ÏûÊäÈë
	ERR_PED_WAIT_INTERVAL ¼ä¸ôÊ±¼äÌ«¶Ì */
int OsPedGetPinBlockSM4(int KeyIdx,const char *ExpPinLenIn,unsigned char *DataIn,unsigned char *PinBlockOut,int Mode,unsigned long TimeoutMs);


//¹¦ÄÜ ¼ì²éDESFire ¿¨¶Ë´«À´µÄ»á»°ÃÜÔ¿B ²¢Éú³É»á»°ÃÜÔ¿A¡£½«A ºÍBºÏ²¢ÎªÒ»¸öÍêÕûµÄ»á»°ÃÜÔ¿£¬È»ºó¶ÔÆä½øĞĞ¼ÓÃÜ²¢Êä³ö¡£
/*²ÎÊı
SrcKeyIdx¡¾ÊäÈë¡¿
DESFire ¹¤×÷ÃÜÔ¿Ë÷Òı£¬È¡Öµ·¶Î§Îª1-100¡£
KeySetVer¡¾ÊäÈë¡¿ ÃÜÔ¿°æ±¾£¬ÓÃÓÚ¼ì²éDESFire °æ±¾¡£
DivType¡¾ÊäÈë¡¿ÃÜÔ¿·¢É¢Ä£Ê½£º
. µ±DivType = 0x00 Ê±£¬±íÊ¾²»·¢É¢£¬´ËÊ±DESFire ÃÜÔ¿ÓÃÓÚ¼ÓÃÜ»á»°ÃÜÔ¿£»
. µ±DivType = 0x01 Ê±£¬½áºÏUidÀ´·¢É¢ÃÜÔ¿£¬¸Ã·¢É¢ÃÜÔ¿ÓÃÓÚ¼ÓÃÜ»á»°ÃÜÔ¿¡£
Mode¡¾ÊäÈë¡¿»á»°ÃÜÔ¿µÄ¼ÓÃÜÀàĞÍ£º0x02£º16 ×Ö½ÚµÄ3DES ¼ÓÃÜÔËËã
Uid¡¾ÊäÈë¡¿ÓÃ»§Êı¾İ£¬Êı¾İ³¤¶È¹Ì¶¨Îª8 ×Ö½Ú£¬ÓÃÓÚ·¢É¢»á»°ÃÜÔ¿¡£
EncRndB¡¾ÊäÈë¡¿DESFire ¿¨Éú³ÉµÄ»á»°ÃÜÔ¿B£º
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª8 »ò16 ×Ö½ÚÊ±£¬ EncRndB ³¤¶ÈÎª8 ×Ö½Ú£»
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª24 ×Ö½ÚÊ±£¬EncRndB ³¤¶ÈÎª16 ×Ö½Ú¡£
EncSessionKey¡¾Êä³ö¡¿ ¼ÓÃÜµÄ(RndA + RndB¡¯).
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedDFAuthDiver(int SrcKeyIdx,int KeySetVer,int DivType,unsigned char Mode,unsigned char *Uid,unsigned char *EncRndB,unsigned char *EncSessionKey);


//¹¦ÄÜ ¼ì²éDESFire ¿¨¶Ë´«À´µÄÃÜÎÄ»á»°ÃÜÔ¿A¡¯¡£
/*²ÎÊı
EncRndA¡¾ÊäÈë¡¿ ÃÜÎÄA¡¯¡£
DataLen¡¾ÊäÈë¡¿EncRndA ³¤¶È£º
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª8 »ò16 ×Ö½ÚÊ±£¬EncRndA ³¤¶ÈÎª8 ×Ö½Ú£»
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª24 ×Ö½ÚÊ±£¬EncRndA ³¤¶ÈÎª16 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedDFAuthMerge(unsigned char *EncRndA,int DataLen);


//¹¦ÄÜ ×¢ÈëÀ´×ÔRKI ·şÎñÆ÷µÄÃÜÔ¿¡£
/*²ÎÊı
KeyBlkLen ¡¾ÊäÈë¡¿ RKI ÃÜÔ¿Êı¾İ³¤¶È
KeyBlk ¡¾ÊäÈë¡¿ RKI ÃÜÔ¿Êı¾İ
DstKeyIdx ¡¾ÊäÈë¡¿Ä¿µÄÃÜÔ¿Ë÷Òı£¬ÔİÎŞÒâÒå£¬¿ÉÒÔÎªÈÎÒâÖµ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊı */
int OsPedRkiInjectKey(int KeyBlkLen,unsigned char *KeyBlk,unsigned char DstKeyIdx);



#endif
