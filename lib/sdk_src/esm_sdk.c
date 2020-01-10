
#include<time.h>
#include<stdlib.h>
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 





//=======================¼Ó½âÃÜ=========================================================


void OsGetRandom(unsigned char *Random,int RandomLen)
{
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<RandomLen;i++)
		Random[i]=(unsigned char)rand();
}




void OsSHA(int Mode, const void *Data, int DataLen, unsigned char*ShaOut)
{

}


void OsDES(const unsigned char *Input, unsigned char *Output, const unsigned char *DesKey, int KeyLen, int Mode)
{

}


void OsAES(const unsigned char *Input, unsigned char *Output, const unsigned char *AesKey, int KeyLen, int Mode)
{

}



int OsRSA(const unsigned char *Modulus, int ModulusLen, const unsigned char *Exp,int ExpLen, const unsigned char *DataIn, unsigned char *DataOut)
{
	return ERR_GEN_RANDOM;

}


int OsRSAKeyGen(unsigned char *Modulus, unsigned char *PriExp, int ModulusLen, const unsigned char * PubExp)
{
	return ERR_GEN_FAIL;
}


//=========================PED============================================


//¹¦ÄÜ ´ò¿ªProlin µÄPED ·þÎñ¡£
/*·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_BUSY Éè±¸±»Õ¼ÓÃ */
int OsPedOpen(void)
{
	return ERR_DEV_BUSY;
}

//¹¦ÄÜ »ñÈ¡µ±Ç°µÄPED µÄ°æ±¾¡
/*²ÎÊý: PedVer¡¾Êä³ö¡¿ PED °æ±¾ÐÅÏ¢»º³åÇø£¬6 ×Ö½Ú¡£
·µ»Ø:	RET_OK ³É¹¦
		ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
		ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetVer(unsigned char * PedVer)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ÉèÖÃÁ½´Î¼ÆËãPIN block Ö®¼äµÄ×îÐ¡¼ä¸ôÊ±¼ä¡£
/*²ÎÊý TpkIntervalMs
	= 0 Ê¹ÓÃÄ¬ÈÏÖµ(30s)
	<1000 ×Ô¶¯ÉèÎª1000(1s)
	>600000 ×Ô¶¯ÉèÎª600000(10min)
	=0xffffffff µ±Ç°ÉèÖÃ²»±»¸Ä±ä
·µ»Ø:
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª */
int OsPedSetInterval(unsigned long TpkIntervalMs)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ Ð£ÑéÍÑ»úÃ÷ÎÄPIN¡£
/*²ÎÊý
IccSlot ¿¨Æ¬ËùÔÚµÄ¿¨×ùºÅ£¬IccSlot=0¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£
	Ó¦ÓÃ³ÌÐò°ÑÔÊÐíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢
	ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊÐíÊäÈë4¡¢6
	Î»ÃÜÂë²¢ÇÒÔÊÐíÎÞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û
	´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£
	ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊý×Ö¶øÖ±½Ó
	°´È·ÈÏ¼ü·µ»Ø¡£
Mode¡¾ÊäÈë¡¿
	0x00£¬IC ¿¨ÃüÁîÄ£Ê½£¬ÏÖÖ§³Ö·ûºÏEMV2000
	µÄIC ¿¨ÃüÁî¡£
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë£¬×î´óÖµÎª300000¡£
	0£º±íÊ¾Ã»ÓÐ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
IccRsp¡¾Êä³ö¡¿ 
	¿¨Æ¬ÏìÓ¦µÄ×´Ì¬Âë(2 ×Ö½Ú£ºSWA+SWB)
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedVerifyPlainPin (int IccSlot,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ Ð£ÑéÃÜÎÄPIN,²½ÖèÈçÏÂ£º1. »ñÈ¡Ã÷ÎÄPIN£»2. ÓÃÓ¦ÓÃÌá¹©µÄRsaPinKey ¶ÔÃ÷ÎÄPIN °´ÕÕEMV ¹æ·¶½øÐÐ¼ÓÃÜ£»3. ÓÃÓ¦ÓÃÌá¹©µÄ¿¨Æ¬ÃüÁîÓë¿¨Æ¬Í¨µÀºÅ£¬½«ÃÜÎÄPIN Ö±½Ó·¢ËÍ¸ø¿¨Æ¬¡£
/*²ÎÊý
Iccslot ¿¨Æ¬ËùÔÚµÄ¿¨×ù
RsaPinKey¡¾ÊäÈë¡¿ ¼ÓÃÜËùÐèÊý¾Ý½á¹¹ST_ RSA_PINKEY¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌÐò°ÑÔÊÐíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬
	²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊÐíÊäÈë4¡¢6 Î»ÃÜÂë²¢ÇÒÔÊÐíÎÞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã
	×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊý×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø.
Mode¡¾ÊäÈë¡¿ 0x00£¬·ûºÏEMV2000IC ¿¨µÄÃüÁî¡£
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë£¬×î´óÖµÎª300000¡£
	0£º±íÊ¾Ã»ÓÐ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
IccRsp¡¾Êä³ö¡¿ ¿¨Æ¬ÏìÓ¦µÄ×´Ì¬Âë(2 ×Ö½Ú£ºSWA+SWB)
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedVerifyCipherPin (int IccSlot,const ST_RSA_PINKEY * RsaPinKey,const char * ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char * IccRsp)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ ²Á³ýPED ·þÎñ±£´æµÄËùÓÐÃÜÔ¿ÐÅÏ¢¡£
/*·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª */
int OsPedEraseKeys(void)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ Éè¶¨Ä³Ð©¹¦ÄÜ¼üµÄ¹¦ÄÜ¡£
/*²ÎÊý KeyFlag
	0x00£ºÔÚÒÑÊäÈëµÄPIN ÒÑ¾­Çå¿Õ»òÕßÃ»ÓÐÊäPIN Ê±£¬°´CLEAR ¼ü£¬PED ÍË³öÊäÈëÃÜÂë×´Ì¬£¬ ²¢·µ»ØERR_PED_INPUT_CLEAR¡£
	0x01£ºÃÜÂëÊäÈë½Ó¿Ú(OsPedGetPinBlock()£¬OsPedGetPinDukpt() £¬OsPedVerifyPlainPin() £¬OsPedVerifyCipherPin() etc)ÔÚÊäÈëPIN¹ý³ÌÖÐ£¬°´ÏÂCLEAR ¼ü£¬Öð¸öÇå³ý×î½üÊäÈëµÄPIN£¬µ±ËùÓÐÒÑÊäÈëµÄPIN ±»Çå³ýÊ±£¬ÔÙ°´CLEAR ¼üÎÞÏìÓ¦£¬²¢ÇÒ²»»áÍË³öPIN ÊäÈëº¯Êý¡£
	0x02£º±íÊ¾ÔÊÐí°´ATM4 ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎÞATM ¼üµÄ»úÐÍ¡£
	0x03£º±íÊ¾ÔÊÐí°´FN ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎÞFN ¼üµÄ»úÐÍ¡£
	0x04£º±íÊ¾ÔÊÐí°´INFO ¼üÀ´½áÊøPIN ÊäÈë£¬²»ÊÊÓÃÎÞINFO ¼üµÄ»úÐÍ¡£
	0x05£º±íÊ¾ÃÜÂëÊäÈë½Ó¿ÚÔÚÊäÈëPIN ¹ý³ÌÖÐ£¬°´ÏÂCANCEL ¼ü£¬Çå³ýËùÓÐÊäÈëµÄPINÎ»£¬µ±ËùÓÐÒÑÊäÈëµÄPIN ±»Çå³ýÊ±£¬ÔÙ°´CANCEL ¼üÎÞÏìÓ¦£¬²¢ÇÒ²»»áÍË³öPIN ÊäÈëº¯Êý¡£
	0xff £º±íÊ¾»Ö¸´Ä¬ÈÏµÄ¹¦ÄÜ¼üÉèÖÃ£¬¼´°´CLEAR ¼üÇå³ý¼üÈëµÄËùÓÐPIN Î»£¬°´CANCEL ¼üÍË³öPIN ÊäÈëº¯Êý£¬°´ATM4/FN/INFO ¼ü²»ÍË³öPIN ÊäÈëº¯Êý¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedSetFunctionKey(int KeyFlag)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ ¶Ï¿ªÓëPED ·þÎñµÄÁ¬½Ó¡£
void OsPedClose(void)
{
}


//¹¦ÄÜ ÓÃÓÚPIN ÊäÈë¹ý³ÌÖÐ£¬ÖÕÖ¹PIN ÊäÈë¡£
/*·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPENPED Éè±¸Î´´ò¿ª */
int OsPedCancelPinEntry(void)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ÉèÖÃÍÑ»úÃ÷ÎÄ/ÃÜÎÄÐ£ÑéÄ£Ê½¡£
/*²ÎÊý
Mode ¡¾ÊäÈë¡¿
Ð£ÑéÄ£Ê½£º
. 0-Ê¹ÓÃÄÚÖÃÃÜÂë¼üÅÌÊäÈëPIN£»
. 1-Ê¹ÓÃÍâÖÃÃÜÂë¼üÅÌÊäÈëPIN£¬Í¨¹ýPinBlock ²ÎÊýµ¼ÈëPIN¡£
TpkIdx ¡¾ÊäÈë¡¿
TPK Ë÷Òý£º
. Mode Îª0 Ê±£¬ÎÞÒâÒå£»
. Mode Îª1 Ê±£¬Ê¹ÓÃ¸ÃË÷ÒýµÄTPK ¶Ôµ¼ÈëµÄPinBlock ½øÐÐ½âÃÜµÃµ½PINÃ÷ÎÄ¡£
PinBlock ¡¾ÊäÈë¡¿
PIN block£º
. Mode Îª0 Ê±£¬ÎÞÒâÒå£»
. Mode Îª1 Ê±£¬±íÊ¾TPK ¼ÓÃÜµÄISO9564 Format1 ¸ñÊ½µÄPIN ÃÜÎÄ¡£
PinBlockLen ¡¾ÊäÈë¡¿ PIN block µÄ³¤¶È
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý	*/
int OsPedSetOfflinePin(unsigned char Mode,unsigned char TpkIdx,unsigned char *PinBlock,unsigned short PinBlockLen)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ ÓÃÓÚPIN ÊäÈë¹ý³ÌÖÐ£¬·¢ËÍÈ·ÈÏ¼ü½áÊøPIN ÊäÈë¡£
/*·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª */
int OsPedEndPinEntry(void);

//¹¦ÄÜ¼àÌý²¢»ñÈ¡µ±Ç°×´Ì¬ÏÂÓÃ»§ÊäÈëµÄPIN °´¼üÊýÁ¿¼°µ±´Î¼àÌýÓëÉÏ´Î¼àÌýÖÐ¼äµÄÀúÊ·°´¼üÐòÁÐ¡£
/*²ÎÊý
KeyCacheCnt¡¾Êä³ö¡¿ »ñÈ¡µ½µÄµ±Ç°ÀúÊ·°´¼üÖµÊýÁ¿¡£
KeyCache¡¾Êä³ö¡¿
. ¼üÖµ°´ÊäÈëµÄÊ±¼äÏÈºóË³ÐòÓÉµÍÎ»µ½¸ßÎ»´æÈë»º³åÇøÖÐ¡£¸ÃÊä³ö»º³åÇøµÄ´óÐ¡±ØÐë´óÓÚµÈÓÚ64 ×Ö½Ú¡£
. »ñÈ¡µ½µÄÀúÊ·°´¼üÐòÁÐ×î¶àÎª64¸ö£¬Èô´ËÊ±°´¼üÐòÁÐÖÐµÄ°´¼ü»º´æ³¬¹ý64 ¸ö£¬ÔòÊä³ö×îÐÂµÄ64 ¸ö°´¼üÐòÁÐ¡£
. »ñÈ¡µ½µÄ¼üÖµÄ¿Ç°Ö»ÄÜÎª¡°PIN¡±¡¢° ENTER ¡± ¡¢¡° CLEAR ¡± ¡¢¡°CANCEL¡±¡¢¡°FN¡±¡¢¡°ATM4¡±Õâ6 ÖÖ£¬ÆäÖÐ¡°PIN¡±Êý×Ö°´¼üÒÔ¡°*¡±´úÌæ¡£Èô´ËÊ±Ã»ÓÐ°´¼üÊäÈë£¬»ñÈ¡µ½µÄ¼üÖµÔòÎª0¡£
·µ»Ø
	>= 0 »ñÈ¡PIN ÊäÈëÊÂ¼þ³É¹¦£¬·µ»ØÖµ´óÐ¡±íÊ¾´ËÊ±PIN ÊäÈë½çÃæµÄ¡°*¡±µÄ¸öÊý¡£
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý	*/
int OsPedPinKeyNotify(int *KeyCacheCnt,unsigned char *KeyCache)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜÐ´ÈëÒ»¸öÃÜÔ¿£¬°üÀ¨TLK£¬TMK£¬ TWK£¬SM4_TMK ºÍSM4_TWKµÄÐ´Èë¡¢·¢É¢£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕýÈ·ÐÔ¡£
/*²ÎÊý 
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
7 bytes ±£ÁôÓò£¬Ëæ»úÊý
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
	0x00£ºÎÞÑéÖ¤
	0x01£º¶Ô8 ¸ö×Ö½ÚµÄ0x00 ¼ÆËãDES/TDES ¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øÐÐÆæÐ£Ñé£¬ÔÙ¶Ô¡°\x12\x34\x56\x78\x90\x12\x34\x56¡±½øÐÐDES/TDES ¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x03£º´«ÈëÒ»´®Êý¾ÝKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô [Ä¿µÄÃÜÔ¿ÃÜÎÄ+ KcvData]½øÐÐÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV¡£
	0x04£º¶Ô16 ×Ö½ÚµÄ0x00 ½øÐÐSM4¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°4 ¸ö×Ö½Ú¼´ÎªKCV¡£
	×¢£ºÄ£Ê½0x01¡¢0x02 ¼°0x03 Ö»ÓÃÓÚMK/SK ÃÜÔ¿×¢ÈëÑéÖ¤£¬Ä£Ê½0x04 Ö»ÓÃÓÚSM4 ÃÜÔ¿×¢ÈëÑéÖ¤¡£
128bytes
	KcvData£º
	. KcvMode Îª0x00/0x01/0x02Ê±£¬Ìî³äËæ»úÊý£»
	. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊý¾ÝµÄ³¤¶È£¬Ö®ºóÎªKCV Êý¾Ý£¬KCV Êý¾ÝÖ®ºóÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½.
8 bytes
	. µ±KcvMode = 0x00 Ê±£¬Ìî³äËæ»úÊý£»
	. µ±KcvMode =0x01/0x02/0x03/0x04 Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
10 bytes Ìî³äËæ»úÊý
·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊý
ERR_SYS_BAD ÏµÍ³´íÎó
ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
ERR_PED_TAMPERED PED ±»Ëø¶¨
ERR_PED_NO_MORE_BUF ÏµÍ³ÄÚ´æ¿Õ¼ä²»×ã
ERR_PED_NORMAL_ERRPED Í¨ÓÃ´íÎó£¨ KeyBlockFormat ´íÎó£©
ERR_PED_DERIVE_ERR ÃÜÔ¿·¢É¢´íÎó
ERR_PED_KCV_MODE_ERR PED KCV Ð£ÑéÄ£Ê½´íÎó
ERR_PED_KCV_CHECK_FAIL PED KCV Ð£ÑéÊ§°Ü */
int OsPedWriteKey(const unsigned char * KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ ÄÜ Ð´ÈëÒ»¸öTIK ÃÜÔ¿£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕýÈ·ÐÔ¡£
/*²ÎÊý KeyBlock¡¾ÊäÈë¡¿
1 byte ¸ñÊ½£º0x03
1 byte
	SrcKeyType£º
	. PED_TLK
1 byte
	SrcKeyIdx£º
	. µ±SrcKeyType = PED_TLKÊ±£¬SrcKeyIdx = 1£»
	. Ã÷ÎÄÐ´ÈëÊ±£¬SrcKeyIdx = 0¡£
1 byte
	DstKeyIdx¡£
	DstKeyIdx = [1~100]¡£
7 bytes ±£ÁôÓò£¬Ëæ»úÊý
1 byte
	DstKeyType£º
	. PED_TIK
1 byte DstKeyLen£º8/1624 bytesDstKeyValueÄ¿µÄÃÜÔ¿Ã÷ÎÄ/ÃÜÎÄ
1 byte
	KcvMode£º
	0x00£ºÎÞÑéÖ¤
	0x01£º¶Ô8 ¸ö×Ö½ÚµÄ0x00 ¼ÆËã
	Prolin Ó¦ÓÃ±à³Ì½Ó¿Ú±à³ÌÖ¸ÄÏµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øÐÐÆæÐ£Ñé£¬ÔÙ¶Ô¡° \x12\x34\x56\x78\x90\x12\x34\x56¡±½øÐÐDES/TDES ¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV¡£
	0x03£º´«ÈëÒ»´®Êý¾ÝKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô [Ä¿µÄÃÜÔ¿ÃÜÎÄ+KcvData] ½øÐÐÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV¡£
128 bytes
KcvData£º
. KcvMode Îª0x00/0x01/0x02 Ê±£¬Ìî³äËæ»úÊý£»
. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊý¾ÝµÄ³¤¶È£¬Ö®ºóÎªKCV Êý¾Ý£¬KCV Êý¾ÝÖ®ºóÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½.
8 bytes
. µ±KcvMode = 0x00 Ê±£¬Ìî³äËæ»úÊý¡£
. µ±KcvMode = 0x01/0x02/0x03Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
10bytes  ³õÊ¼KSN
·µ»Ø
ERR_OK ³É¹¦
ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedWriteTIK(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜÊ¹ÓÃÖ¸¶¨ÃÜÔ¿ÀàÐÍµÄÃÜÔ¿Ë÷ÒýËùÔÚµÄÃÜÔ¿Ã÷ÎÄÓëÒ»´®Êý¾Ý½øÐÐÔËËã(Òì»òµÈ)£¬µÃµ½ÃÜÔ¿Ð´Èëµ½Í¬Ò»ÀàÐÍÃÜÔ¿ÇøµÄÁíÒ»Ö¸¶¨Ë÷ÒýÎ»ÖÃ¡£
/*²ÎÊý
KeyType ÃÜÔ¿ÀàÐÍ£º
. PED_TMK
. PED_TPK
. PED_TAK
. PED_TDK
SrcKeyIdx Ô´ÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DstKeyIdx Ä¿µÄÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
KeyVar¡¾ÊäÈë¡¿
	24 ×Ö½Ú£¬ÐèÒª²ÎÓëÔËËãµÄ×Ö·û´®£»ÎªÓëÃÜÔ¿³¤¶ÈÏàÍ¬µÄ×Ö·û´®£¬ÓÃÓÚºÍÔ´Ë÷ÒýµÄÃÜÔ¿Òì»ò£»¿ÉÀ©Õ¹.
·µ»Ø
RET_OK ³É¹¦
ERR_DEV_NOT_OPENPED Éè±¸Î´´ò¿ª
ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedWriteKeyVar(int KeyType,int SrcKeyIdx,int DstKeyIdx,const unsigned char *KeyVar)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ÔÚÊäÈëPIN Ê±£¬ÉèÖÃ½çÃæÏÔÊ¾ÐÇºÅµÄ²¼¾ÖÊôÐÔ¡£
/*²ÎÊý
x ºá×ø±ê
y ×Ý×ø±ê
fontSize ÐÇºÅµÄ×ÖÌå´óÐ¡£º
	. fontSize = 16£¬16 ¸ö×Öµã´óÐ¡µÄ×Ö·û£»
	. fontSize = 24£¬24 ¸ö×Öµã´óÐ¡µÄ×Ö·û£»
	. fontSize = 32£¬32 ¸ö×Öµã´óÐ¡µÄ×Ö·û£»
	. fontSize = 48£¬48 ¸ö×Öµã´óÐ¡µÄ×Ö·û£»
	¸Ãº¯ÊýÖÐÐÇºÅµÄÏÔÊ¾Ê¹ÓÃPED ÄÚ²¿×ÖÌåÎÄ¼þ£¬ÓëÏµÍ³Ëù×°×Ö¿âÎÞ¹Ø¡£
fontColor ÐÇºÅµÄ×ÖÌåÑÕÉ«£ºÊ¹ÓÃºê¶¨Òå RGB(_r, _g, _b)£¬¸ù¾ÝÊäÈëµÄÈýÔ­É«Éú³É16 Î»ÑÕÉ«Öµ¡£
align ¶ÔÆë·½Ê½£º
	PED_ASTERISK_ALIGN_LEFT£º×ó±ßÆðÊ¼Î»ÖÃ¹Ì¶¨£¬×Ô×óÏòÓÒË³ÐòÏÔÊ¾ÐÇºÅ£»
	PED_ASTERISK_ALIGN_CENTER£ºÖÐ¼äÎ»ÖÃ¹Ì¶¨£¬×óÓÒÁ½±ß¶Ô³ÆÏÔÊ¾ÐÇºÅ£»
	PED_ASTERISK_ALIGN_RIGHT£ºÓÒ±ßÆðÊ¼Î»ÖÃ¹Ì¶¨£¬×ÔÓÒÏò×óË³ÐòÏÔÊ¾ÐÇºÅ¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedSetAsteriskLayout(int x,int y,int fontSize,int fontColor,unsigned char align)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ÊäÈëPIN Ê±£¬ÉèÖÃÇ°¾°ºÍ±³¾°Í¼±êµÄ²¼¾ÖÊôÐÔ¡£
/*²ÎÊý
	X¡¾ÊäÈë¡¿ Ç°¾°ºÍ±³¾°Í¼±êµÄÆðÊ¼ºá×ø±ê
	Y¡¾ÊäÈë¡¿ Ç°¾°ºÍ±³¾°Í¼±êµÄÆðÊ¼×Ý×ø±ê
	Interval¡¾ÊäÈë¡¿ Á½¸öÏàÁÚÍ¼±êÖ®¼äµÄ¼ä¾à
	IconNum¡¾ÊäÈë¡¿ ±³¾°Í¼±êµÄÊýÄ¿
	PinIcon¡¾ÊäÈë¡¿Ç°¾°Í¼±ê¾ø¶ÔÂ·¾¶£¬Ö§³ÖBMP ºÍPNGÍ¼±ê
	PinIconLen ¡¾ÊäÈë¡¿Ç°¾°Í¼±ê¾ø¶ÔÂ·¾¶³¤¶È£¬×î³¤256 ×Ö½Ú
	PinIconBG ¡¾ÊäÈë¡¿±³¾°Í¼±ê¾ø¶ÔÂ·¾¶£¬Ö§³ÖBMP ºÍPNGÍ¼±ê£¬Èç²»ÐèÒª±³¾°Í¼±ê£¬¿ÉÉèÎªNULL¡£
	PinIconBGLen¡¾ÊäÈë¡¿±³¾°Í¼±êÂ·¾ø¶Ô¾¶³¤¶È£¬×î³¤256 ×Ö½Ú£»Èç²»ÐèÒª±³¾°Í¼±ê£¬¿ÉÉèÎª0¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedSetPinIconLayout(int X,int Y,int Interval,unsigned char IconNum,char *PinIcon,int PinIconLen,char *PinIconBG,int PinIconBGLen)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜÖ¸¶¨µÄÊ±ÏÞÄÚ,É¨Ãè¼üÅÌÉÏÊäÈëExpPinLenIn Ö¸¶¨³¤¶ÈµÄPIN£¬²¢Êä³öÓÉMode Ö¸¶¨Ëã·¨¼ÓÃÜÉú³ÉµÄPIN block¡£
/*²ÎÊý
KeyIdx TPK µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1-100] ¡£
DataIn¡¾ÊäÈë¡¿
. µ±Mode=0x00 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
. µ±Mode=0x01 Ê±£¬DataIn ÎÞÒâÒå£¬¿ÉÎªÈÎÒâÖµ¡£PED ½«²ÉÓÃËæ»úÊý´úÌæDataIn ²ÎÓëPinBlock µÄ¼ÆËã¡£
. µ±Mode=0x02 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
. µ±Mode=0x03 Ê±£¬DataIn Îª½»Ò×Á÷Ë®ºÅISN ¡¾6 ×Ö½Ú£¬ASCII Âë¡¿¡£
. µ±Mode=0x10 Ê±£¬DataIn ÎÞÒâÒå£¬¿ÉÎªÈÎÒâÖµ¡£PED ½«²ÉÓÃËæ»úÊý´úÌæDataIn ²ÎÓëPinBlock µÄ¼ÆËã¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌÐò°ÑÔÊÐíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊÐíÊäÈë4 Î»¡¢6 Î»
	ÃÜÂëÇÒÔÊÐíÎÞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£Ã¶¾Ù0 ±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊý×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø¡£
Mode
	Ñ¡ÔñPIN BLOCK µÄ¸ñÊ½
		Ê¹ÓÃDES£¨3DES£©Ëã·¨¼ÓÃÜµÄPinBlockµÄ¸ñÊ½£º
		. 0x00 0x00 ISO9564 ¸ñÊ½ 0
		. 0x01 0x01 ISO9564 ¸ñÊ½ 1
		. 0x02 0x02 ISO9564 ¸ñÊ½ 3
		. 0x03 0x03 HK EPS ×¨ÓÃ¸ñÊ½
		Ê¹ÓÃAES Ëã·¨¼ÓÃÜµÄPinBlock µÄ¸ñÊ½£º
		. 0x10 PinBlock Ã÷ÎÄÇ°°Ë×Ö½ÚÎªISO9564 ¸ñÊ½ 1 µÄÃ÷ÎÄÊý¾Ý£¬ºó°Ë×Ö½Ú½øÐÐ#PKCS7 Ìî³ä£¬¾ßÌåÎª8 ×Ö½ÚµÄ0x08¡£
TimeoutMs
	ÊäÈëPIN µÄ³¬Ê±Ê±¼äµ¥Î»£ººÁÃë×î´óÖµÎª3000000£º±íÊ¾Ã»ÓÐ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
PinBlock¡¾Êä³ö¡¿
	8 »ò16 ×Ö½Ú£¬Ö¸ÏòÉú³ÉµÄPIN block¡£Mode Îª0x10 Ê±£¬PinBlock ³¤¶ÈÎª16 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetPinBlock(int KeyIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ ÖØÐÂ¼ÆËãPIN block£¬²¢Ñ¡ÔñÊÇ·ñ¸ü»»TPK¡£
/*²ÎÊý 
UpdateFlag¡¾ÊäÈë¡¿:  0£º²»¸ü»»TPK£» ·Ç0£º¸ü»»TPK¡£
KeyInfo¡¾ÊäÈë¡¿
	²ÎÕÕOsPedWriteKey()ÏÂKeyBlock µÄ¶¨Òå£¬³¤¶ÈÎª184 ×Ö½Ú¡£µ±UpdateFlag Îª0 Ê±£¬KeyBlock ÏÂÖ»ÓÐDstKeyIdx ÓÐÒâÒå£¬
	²ÉÓÃDstKeyIdxÖ¸¶¨µÄTPK£¬ÖØÐÂ¼ÆËãPIN block¡£
DataIn¡¾ÊäÈë¡¿
	. µ±UpdateFlag Îª0£¬Mode=0x03 Ê±£¬Îª½»Ò×Á÷Ë®ºÅISN ¡¾6 ×Ö½Ú£¬ASCII Âë¡¿£»
	. µ±UpdateFlag Îª0£¬Mode=0x00 Ê±£¬DataIn Ç°16 ×Ö½ÚÎª¾ÉµÄPAN£¬ºó16×Ö½ÚÎªÐÂµÄPAN£¬PAN ÊÇÖ¸£º¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ£»
	. µ±UpdateFlag Îª·Ç0 Ê±£¬ ¿ÉÎªNULL¡£
PinBlock¡¾ÊäÈë/Êä³ö¡¿
	8 ×Ö½Ú£¬ÊäÈëÔ­PIN block Êý¾Ý£¬Êä³öÐÂµÄPIN block
Mode
	0x00£ºISO9564 ¸ñÊ½0£»
	0x03£ºHK EPS ×¨ÓÃ¸ñÊ½¡¾Ïê¼û¸½Â¼2EPS_PINBLOCK ¸ñÊ½¡¿
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedUpdatePinBlock (int UpdateFlag,const unsigned char * KeyInfo,const unsigned char * DataIn,unsigned char * PinBlock,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ ÓÃKeyIdx Ö¸¶¨µÄMAC ÃÜÔ¿¶ÔDataIn ½øÐÐMode Ö¸¶¨µÄÔËËã¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ TAK µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿Ðè½øÐÐMAC ÔËËãµÄÊý¾Ý£¬³¤¶ÈÐ¡ÓÚµÈÓÚ8192 ×Ö½Ú¡£
DataInLen¡¾ÊäÈë¡¿MAC ÔËËãµÄÊý¾Ý³¤¶È£¬µ±³¤¶È²»ÄÜ±»8 ×Ö½ÚÕû³ý£¬Ôò×Ô¶¯²¹¡°\x00¡±¡£
Mac¡¾Êä³ö¡¿ 8 ×Ö½Ú£¬MAC Êä³ö¡£
Mode¡¾ÊäÈë¡¿½«DataIn °´8 ×Ö½ÚÎªµ¥Î»·Ö¿é£¬ÒÀ´ÎÎªBLOCK1£¬BLOCK2£¬BLOCK3 µÈ¡£
0x00£º½«BLOCK1 ÓÃMAC ÃÜÔ¿×öDES/TDES ¼ÓÃÜ£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øÐÐÖðÎ»Òì»òºóÔÙÓÃTAK ×öDES/TDES ¼ÓÃÜ£¬ÒÀ´Î½øÐÐµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£
0x01£º½«BLOCK1 ºÍBLOCK2 ½øÐÐÖðÎ»Òì»ò£¬Òì»ò½á¹ûÓëBLOCK3 ½øÐÐÖðÎ»Òì»ò£¬ÒÀ´Î½øÐÐ£¬×îºóµÃµ½8 ×Ö½ÚµÄÒì»ò½á¹û£¬½«¸Ã½á¹ûÓÃTAK ½øÐÐDES/TDES ¼ÓÃÜÔËËã¡£
0x02£ºÒÀ¾ÝANSIX9.19 ¹æ·¶£¬½«BLOCK1 ÓÃTAK×öDES ¼ÓÃÜ(Ö»È¡Ç°8 ¸ö×Ö½ÚµÄÃÜÔ¿)£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øÐÐÖðÎ»Òì»òºóÔÙÓÃTAK ×öDES ¼ÓÃÜ£¬ÒÀ´Î½øÐÐµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û£¬×îºó²ÉÓÃDES/TDES ¼ÓÃÜ¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetMac(int KeyIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜÊ¹ÓÃTDK ¶ÔDataInLen ³¤¶ÈµÄÊý¾Ý½øÐÐDES/TDES ½âÃÜ»ò¼ÓÃÜÔËËã£¬Êä³öÃ÷ÎÄ»òÃÜÎÄ£»Ò»¸öÖ¸¶¨µÄTDK£¬Ö»ÄÜÓÃÓÚ¼ÓÃÜ»ò½âÃÜÔËËã¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ TDK Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
InitVector¡¾ÊäÈë¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬³¤¶ÈÎª8 ×Ö½Ú¡£µ±Mode=0x02/0x03/0x04/0x05 Ê±,ÐèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬
				ÎªNULL Ê±Ä¬ÈÏÎª¡°\x00\x00\x00\x00\x00\x00\x00\x00¡±£»µ±Mode=0x00/0x01 Ê±£¬²»ÐèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòÐèÒª½øÐÐÔËËãµÄÊý¾Ý¡£
DataInLen¡¾ÊäÈë¡¿ÐèÒªÔËËãµÄÊý¾Ý³¤¶È£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬Ó¦Ð¡ÓÚµÈÓÚ1024£»
	µ±Mode Îª0x00~0x05 Ê±£¬±ØÐëÎª8 µÄ±¶Êý£»
	µ±Mode Îª0x06~0x07 Ê±£¬¿ÉÒÔ²»ÊÇ8 µÄ±¶Êý¡£
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊý¾Ý¡£
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
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedDes(int KeyIdx,unsigned char * InitVector,const unsigned char *DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ»ñÈ¡ÃÜÔ¿µÄKCV Öµ£¬ÒÔ¹©¶Ô»°Ë«·½½øÐÐÃÜÔ¿ÑéÖ¤£ºÃÜÔ¿ÀàÐÍ·ÇTIK Ê±£¬ÓÃÖ¸¶¨µÄÃÜÔ¿¼°Ëã·¨¶ÔÒ»¶ÎÊý¾Ý½øÐÐ¼ÓÃÜ£¬²¢·µ»ØÊý¾ÝÃÜÎÄµÄÇ°3 ×Ö½Ú£»ÃÜÔ¿ÀàÐÍÎªTIK Ê±£¬·µ»ØÓëTIK Ò»²¢×¢Èë(¼ÆËãµÃµ½)µÄ8 ×Ö½ÚKCV¡£
/*²ÎÊý
KeyType ÃÜÔ¿ÀàÐÍ£º
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
KeyIdx ÃÜÔ¿µÄË÷ÒýºÅ£¬Èç£º
. TLK£¬Ö»ÄÜÎª1¡£
. TMK ¿ÉÈ¡Öµ1~100¡£
. TWK ¿ÉÈ¡Öµ1~100¡£
. TIK ¿ÉÈ¡Öµ1~100¡£
KcvMode  KCV Ð£ÑéÄ£Ê½
	0x00£ºÊ¹ÓÃDES Ëã·¨¼ÆËãÃÜÔ¿µÄKCV£»
	0x04£ºÊ¹ÓÃSM4 Ëã·¨¼ÆËãSM4 ÃÜÔ¿µÄKCV£¬´ËÊ±ÃÜÔ¿ÀàÐÍÖ»ÄÜÎªSM4 ÏµÁÐµÄÃÜÔ¿¡££¨ KeyType Ö»ÄÜÊÇPED_SM4_TMK/PED_SM4_TPK/PED_SM4_TAK/PED_SM4_TDK£©
KcvDataLen ²ÎÓë¼ÆËãKCV µÄÊý¾Ý³¤¶È£¬²»³¬¹ý128 ×Ö½Ú£¬ÇÒ±»8 Õû³ý£»ÃÜÔ¿ÀàÐÍÎªTIK Ê±¿ÉÎª0£»KCVÐ£ÑéÄ£Ê½Îª0x04 Ê±£¬¸ÃÊý¾Ý³¤¶È±ØÐëÄÜ±»16Õû³ý¡£
KcvData¡¾ÊäÈë¡¿²ÎÓë¼ÆËãKCV µÄÊý¾Ý£¬ÃÜÔ¿ÀàÐÍÎªTIK Ê±¿ÉÎªNULL¡£
Kcv¡¾Êä³ö¡¿
	KCV Öµ£¬3 »ò8 ×Ö½Ú¡£ÃÜÔ¿ÀàÐÍÎªTIK Ê±£¬
	KCV Îª8 ×Ö½Ú£¬ÆäÓàÎª3 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý	*/
int OsPedGetKcv(int KeyType,int KeyIdx,int KcvMode,int KcvDataLen,unsigned char *KcvData,unsigned char *Kcv)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜÓÃSrcKeyIdx Ö¸¶¨µÄÃÜÔ¿¶ÔDstFromKeyIdx Ö¸¶¨µÄÃÜÔ¿½øÐÐ¼ÓÃÜ»ò½âÃÜ£¬·¢É¢ÐÂÃÜÔ¿£¬²¢½«½á¹û±£´æµ½DstToKeyIdx Ö¸¶¨µÄÃÜÔ¿¡£
/*²ÎÊý
SrcKeyType Ô´ÃÜÔ¿ÀàÐÍ£º
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
SrcKeyIdx Ô´ÃÜÔ¿µÄË÷ÒýºÅ£¬Èç£º
. TLK£¬Ö»ÄÜÎª1¡£
. TMK ¿ÉÈ¡Öµ1~100¡£
. TWK ¿ÉÈ¡Öµ1~100¡£
DstKeyType Ä¿µÄÃÜÔ¿ÀàÐÍ£º
. PED_TLK
. PED_TMK
. PED_TAK
. PED_TPK
. PED_TDK
DstFromKeyIdx Ä¿µÄÃÜÔ¿Ô´Ë÷ÒýºÅ
DstToKeyIdx Ä¿µÄÃÜÔ¿Ä¿µÄË÷ÒýºÅ
Mode
	0x00£ºDES/TDES ½âÃÜ
	0x01£ºDES/TDES ¼ÓÃÜ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedDeriveKey(int SrcKeyType,int SrcKeyIdx,int DstKeyType,int DstFromKeyIdx,int DstToKeyIdx,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃFramebuffer Êý¾Ý»òÕßÍ¼Æ¬Êý¾ÝÉèÖÃPIN ÊäÈëÊ±µÄ±³¾°¡£
/*²ÎÊý
Mode¡¾ÊäÈë¡¿PIN ÊäÈë±³¾°µÄÉèÖÃ·½Ê½£º
	Mode = 0x00£¬Çå³ý¸Ã½Ó¿ÚµÄÉèÖÃ£»
	Mode = 0x01£¬Ê¹ÓÃFramebuffer Êý¾ÝÉèÖÃPIN ÊäÈëÊ±µÄ±³¾°£»
	Mode = 0x02£¬Ê¹ÓÃÍ¼Æ¬Êý¾ÝÉèÖÃPINÊäÈëÊ±µÄ±³¾°¡£
Bg¡¾ÊäÈë¡¿´æ·ÅFramebuffer Êý¾Ý»òÕßÍ¼Æ¬Êý¾ÝµÄBuffer¡£
BgLen¡¾ÊäÈë¡¿´æ·ÅFramebuffer Êý¾Ý»òÕßÍ¼Æ¬Êý¾ÝBuffer µÄ³¤¶È¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedSetPinBg(unsigned char Mode,const unsigned char *Bg,int BgLen)
{
	return ERR_DEV_NOT_OPEN;
}




//¹¦ÄÜ ¶¨ÖÆ»¯PED Èí¼üÅÌ¡£
/*²ÎÊý
IconPath ¡¾ÊäÈë¡¿´æ·Å¼üÅÌÍ¼Æ¬µÄ¾ø¶ÔÂ·¾¶£¬²»Ö§³ÖÏà¶ÔÂ·¾¶£¬Â·¾¶³¤¶È×î³¤²»³¬¹ý256×Ö½Ú£¬¿ÉÎªNULL¡£µ±IconPath ÎªNULL Ê±£¬ÏµÍ³Ê¹ÓÃÄ¬ÈÏµÄÍ¼Æ¬¡£
KeypadColorBg ¡¾ÊäÈë¡¿¼üÅÌµÄ±³¾°É«RGBA Öµ£¬³¤¶ÈÎª4×Ö½Ú£¬¿ÉÎªNULL¡£µ±KeypadColorBg ÎªNULL Ê±£¬ÏµÍ³Ê¹ÓÃÄ¬ÈÏµÄ¼üÅÌ±³¾°É«¡£
Mode ¡¾ÊäÈë¡¿ÉèÖÃÄ£Ê½£º
	Mode = 0x00 Ê±£¬Ê¹ÓÃÏµÍ³Ä¬ÈÏµÄ¼üÅÌÍ¼Æ¬ÒÔ¼°±³¾°ÑÕÉ«£»
	Mode = 0x01 Ê±£¬Ê¹ÓÃÓÃ»§Ö¸¶¨µÄ¼üÅÌÍ¼Æ¬»òÕßÓÃ»§Ö¸¶¨µÄ¼üÅÌ±³¾°ÑÕÉ«¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_FILE_NOT_EXIST Í¼Æ¬×ÊÔ´ÎÄ¼þ²»´æÔÚ
	ERR_VERIFY_SIGN_FAIL Í¼Æ¬×ÊÔ´ÎÄ¼þÑéÇ©Ê§°Ü */
int OsPedCustomKeypad(char *IconPath,unsigned char *KeypadColor,unsigned char Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜÖ¸¶¨µÄÊ±ÏÞÄÚ£¬É¨Ãè¼üÅÌÉÏÊäÈëµÄPIN£¬²¢Êä³öÊ¹ÓÃDUKPT µÄPIN ÃÜÔ¿¼ÆËãÉú³ÉµÄPIN block¡£
/*²ÎÊý
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿
	1. µ±Mode=0x20 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
	2. µ±Mode=0x21 Ê±£¬ÎÞÒâÒå¡£
	3. µ±Mode=0x22 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
	4. µ±Mode=0x23 Ê±£¬Îª½»Ò×Á÷Ë®ºÅISN ¡¾6×Ö½Ú£¬ASCII Âë¡¿¡£
ExpPinLen¡¾ÊäÈë¡¿
	¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£Ó¦ÓÃ³ÌÐò°ÑÔÊÐíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊÐíÊäÈë4¡¢
	6 Î»ÃÜÂë²¢ÇÒÔÊÐíÎÞÃÜÂëÖ±½Ó°´È·ÈÏ£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°0,4,6¡±¡£ÈôÃ¶¾Ù0 ³¤¶ÈÔò±íÊ¾¿ÉÒÔ²»ÊäÈÎºÎÊý×Ö¶øÖ±½Ó°´È·ÈÏ¼ü·µ»Ø¡£
Mode¡¾ÊäÈë¡¿Ñ¡ÔñPIN block µÄ¸ñÊ½£º
. 0x20 ISO9564 ¸ñÊ½0£¬KSN ²»×Ô¶¯¼Ó1
. 0x21 ISO9564 ¸ñÊ½1£¬KSN ²»×Ô¶¯¼Ó1
. 0x22 ISO9564 ¸ñÊ½2£¬KSN ²»×Ô¶¯¼Ó1
. 0x23 HK EPS ¸ñÊ½£¬KSN ²»×Ô¶¯¼Ó1
TimeoutMs¡¾ÊäÈë¡¿
	ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë¡£×î´óÖµÎª300000
	0£º±íÊ¾Ã»ÓÐ³¬Ê±Ê±¼ä£¬PED ²»×ö³¬Ê±¿ØÖÆ¡£
Ksn¡¾Êä³ö¡¿ 10 ×Ö½Ú£¬Ö¸Ïòµ±Ç°µÄKSN¡£
PinBlock¡¾Êä³ö¡¿ 8 ×Ö½Ú£¬Ö¸ÏòÉú³ÉµÄPIN block¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetPinDukpt(int GroupIdx,const unsigned char *DataIn,const char *ExpPinLen,int Mode,unsigned long TimeoutMs,unsigned char *Ksn,unsigned char *PinBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃDUKPT ÃÜÔ¿¼ÆËãMAC Öµ¡£
/*²ÎÊý
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòÐèÒª¼ÆËãMAC µÄÊý¾ÝÄÚÈÝ¡£
DataInLen¡¾ÊäÈë¡¿Êý¾ÝµÄ³¤¶È£¬Ð¡ÓÚµÈÓÚ8192 ×Ö½Ú£¬µ±²»Îª8×Ö½ÚÕû³ýÊ±×Ô¶¯²¹¡°\x00¡±¡£
Mac¡¾Êä³ö¡¿ Ö¸ÏòµÃµ½µÄMAC¡£
Ksn¡¾Êä³ö¡¿ Ö¸Ïòµ±Ç°µÄKSN¡£
Mode¡¾ÊäÈë¡¿½«DataIn °´8 ×Ö½ÚÎªµ¥Î»·Ö¿é£¬ÒÀ´ÎÎªBLOCK1£¬BLOCK2£¬BLOCK3 µÈ¡£
	0x20£º½«BLOCK1 ÓÃMAC ÃÜÔ¿×öTDES ¼ÓÃÜ£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øÐÐÖðÎ»Òì»òºóÔÙÓÃTAK ×öTDES ¼ÓÃÜ£¬ÒÀ´Î½øÐÐµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£
	0x21£º½«BLOCK1 ºÍBLOCK2 ½øÐÐÖðÎ»Òì»ò£¬Òì»ò½á¹ûÓëBLOCK3 ½øÐÐÖðÎ»Òì»ò£¬ÒÀ´Î½øÐÐ£¬×îºóµÃµ½8 ×Ö½ÚµÄÒì»ò½á¹û£¬½«¸Ã½á¹ûÓÃTAK ½øÐÐTDES¼ÓÃÜÔËËã¡£
	0x22£ºÒÀ¾ÝANSIX9.19 ¹æ·¶£¬½«BLOCK1ÓÃTAK ×öDES ¼ÓÃÜ(Ö»È¡Ç°8 ¸ö×Ö½ÚµÄkey)£¬¼ÓÃÜ½á¹ûÓëBLOCK2 ½øÐÐÖðÎ»Òì»òºóÔÙÓÃTAK ×öDES ¼ÓÃÜ£¬ÒÀ´Î½øÐÐµÃµ½8 ×Ö½ÚµÄ¼ÓÃÜ½á¹û£¬Ö±µ½×îºóÒ»´Î²ÉÓÃTDES ¼ÓÃÜ¡£
	. 0x20/0x21/0x22/0x40/0x41/0x42KSN ²»×Ô¶¯¼Ó1¡£
	. 0x40/0x41/0x42 ¼ÆËãMAC ·½Ê½Óë0x20/0x21/0x22 ÏàÍ¬¡£
	. 0x40/0x41/0x42 Ñ¡ÔñÓ¦´ðMAC ÃÜÔ¿£¬0x20/0x21/0x22KSN Ñ¡ÔñÇëÇó»òÓ¦´ðMAC ÃÜÔ¿¡£
	. ÆäËüÖµ±£ÁôÀ©Õ¹MAC Ëã·¨¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetMacDukpt(int GroupIdx,const unsigned char *DataIn,int DataInLen,unsigned char *Mac,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ Ê¹ÓÃDUKPT ÃÜÔ¿£¬¶ÔÊäÈëÊý¾Ý½øÐÐ¼Ó½âÃÜ¡£
/*²ÎÊý
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
KeyVarType¡¾ÊäÈë¡¿
	0x00£ºÊ¹ÓÃÓ¦´ð»òÇëÇóMAC ÃÜÔ¿
	0x01£ºÊ¹ÓÃDUKPT DES ÃÜÔ¿
	0x02£ºÊ¹ÓÃPIN variant Îªdata ¼ÓÃÜ£¬ECBºÍCBC ¼ÓÃÜ¿ÉÓÃ£¬¼´Mode Öµ¿ÉÎª0x01 ºÍ0x03¡£µ±DUKPT ÃÜÔ¿Îª8×Ö½ÚÊ±£¬Ê¹ÓÃµÄ²»ÊÇ±ê×¼µÄDES Ëã·¨£¬¶øÊÇANSI9.24-1998 ¶¨ÒåµÄÌØÊâDES Ëã·¨¡£
	0x03£ºÊ¹ÓÃÓ¦´ðMAC ÃÜÔ¿£¬½öÖ§³Ö¼ÓÃÜÄ£Ê½£¬¼´Mode ÖµÖ»ÄÜÎª0x01¡¢0x03¡¢0x05
	0x04£ºÊ¹ÓÃÓ¦´ðDES ÃÜÔ¿£¬½öÖ§³Ö¼ÓÃÜÄ£Ê½£¬¼´Mode ÖµÖ»ÄÜÎª0x01¡¢0x03¡¢0x05
InitVector¡¾ÊäÈë¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬8 ×Ö½Ú
	µ±Mode=0x02/0x03/0x04/0x05 Ê±,ÐèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬ÎªNULL Ê±Ä¬ÈÏÎª¡°\x00\x00\x00\x00\x00\x00\x00\x00¡±£»
	µ±Mode=0x00/0x01 Ê±£¬²»ÐèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
DataInLen¡¾ÊäÈë¡¿ ÐèÒª¼Ó½âÃÜµÄÊý¾Ý³¤¶È£¬Ð¡ÓÚµÈÓÚ 8192
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòÐèÒª½øÐÐÔËËãµÄÊý¾Ý
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊý¾Ý
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
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedDesDukpt(int GroupIdx,int KeyVarType,unsigned char *InitVector,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *Ksn,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//¹¦ÄÜ »ñÈ¡µ±Ç°µÄKSN Öµ¡£
/*²ÎÊý
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
Ksn¡¾Êä³ö¡¿ Ö¸Ïòµ±Ç°KSN£¬10 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedGetKsnDukpt(int GroupIdx,unsigned char *Ksn)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ôö¼ÓÖ¸¶¨DUKPT ×éµÄKSN Öµ¡£
/*²ÎÊý 
GroupIdx¡¾ÊäÈë¡¿ DUKPT ×éË÷ÒýºÅ£¬ È¡Öµ·¶Î§Îª[1~100]¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedIncreaseKsnDukpt(int GroupIdx)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ ¶ÁÈ¡RSA ¹«Ô¿¡£
/*²ÎÊý
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
RsaKey¡¾Êä³ö¡¿ RSA ¹«Ô¿½á¹¹ÌåST_RSA_KEY
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedReadRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ×¢ÈëRSA ÃÜÔ¿µ½PED¡£
/*²ÎÊý
RsaKeyIdx¡¾ÊäÈë¡¿ RSA ÃÜÔ¿µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
RsaKey¡¾ÊäÈë¡¿Ö¸ÏòÐèÒª×¢ÈëPED µÄRSA ÃÜÔ¿½á¹¹ÌåST_RSA_KEY¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedWriteRsaKey(int RsaKeyIdx,ST_RSA_KEY *RsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ÓÃ´æ´¢ÔÚPED µÄRSA ÃÜÔ¿½øÐÐRSA Êý¾ÝÔËËã¡£
/*²ÎÊý
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
DataInLen¡¾ÊäÈë¡¿ÐèÒª½øÐÐÔËËãµÄÊý¾Ý³¤¶È£¬µ¥Î»Îª×Ö½Ú£¬ÓëRSA ÃÜÔ¿µÄÄ£³¤ÏàÍ¬¡£³¤¶ÈÖµÎª64 µ½512 Ö®¼ä8 µÄ±¶Êý¡£
DataIn¡¾ÊäÈë¡¿ Ö¸ÏòÐèÒª½øÐÐÔËËãµÄÊý¾Ý
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊý¾Ý
KeyInfo¡¾Êä³ö¡¿ ÃÜÔ¿ÐÅÏ¢
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedRsaRecover(int KeyIdx,int DataInLen,unsigned char *DataIn,unsigned char *DataOut,unsigned char *KeyInfo)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ ¶ÁÈ¡RSA ÃÜÔ¿ÃÜÎÄ¡£
/*²ÎÊý
RsaKeyIdx¡¾ÊäÈë¡¿ RSA Key µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
CipherRsaKey¡¾Êä³ö¡¿ Ö¸ÏòRSA ÃÜÔ¿ÃÜÎÄ
·µ»Ø
	>0 ±íÊ¾RSA ÃÜÔ¿ÃÜÎÄµÄ³¤¶È
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedReadCipherRsaKey(int RsaKeyIdx,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ Ð´RSA ÃÜÔ¿ÃÜÎÄ¡£
/*²ÎÊý
RsaKeyIdx¡¾ÊäÈë¡¿  RSA Key µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~10]¡£
CipherRsaKeyLen¡¾ÊäÈë¡¿ Ð´ÈëµÄRSA ÃÜÔ¿ÃÜÎÄÊý¾ÝµÄ×Ö½Ú³¤¶È£¬Ð¡ÓÚµÈÓÚ1024
CipherRsaKey¡¾ÊäÈë¡¿ Ö¸ÏòRSA ÃÜÔ¿ÃÜÎÄ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedWriteCipherRsaKey(int RsaKeyIdx,int CipherRsaKeyLen,unsigned char *CipherRsaKey)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ½«Ò»¸öAES ÃÜÔ¿µÄÃÜÎÄ»òÕßÃ÷ÎÄÐ´Èëµ½AES ÃÜÔ¿ÇøÓòµÄÖ¸¶¨Ë÷ÒýµÄÎ»ÖÃ£¬²¢¿ÉÒÔÑ¡ÔñÊ¹ÓÃKCV ÑéÖ¤ÃÜÔ¿ÕýÈ·ÐÔ¡£
/*²ÎÊý KeyBlock¡¾ÊäÈë¡¿
1 byte ¸ñÊ½£º0x03
1 byte SrcKeyType£º
	. PED_TLK
	. PED_TMK
1 byte
	SrcKeyIdx£º
	. µ±SrcKeyType = PED_TLK Ê±£¬SrcKeyIdx = 1£»
	. µ±SrcKeyType = PED_TMKÊ±£¬SrcKeyIdx = [1~100]£»
	. µ±SrcKeyIdx = 0£¬ÃÜÔ¿½«ÒÔÃ÷ÎÄÐÎÊ½Ð´ÈëPED¡£
1 byte DstKeyIdx£º[1~100]
7 bytes ±£ÁôÓò£¬Ëæ»úÊý
1 byte
	DstKeyType£º
	. PED_TAESK
	. PED_AES_TPK
	. PED_AES_TAK
	. PED_AES_TDK
1 byte DstKeyLen£º16/24/32
32 bytes DstKeyValue£ºÄ¿µÄÃÜÔ¿Ã÷ÎÄ/ÃÜÎÄ
1 byte  KcvMode£º
	0x00£ºÎÞÑéÖ¤¡£
	0x01£º¶Ô16 ¸ö×Ö½ÚµÄÈ«0x00 ¼ÆËãAES/ECB ¼ÓÃÜ£¬µÃµ½ÃÜÎÄµÄÇ°3 ¸ö×Ö½Ú¼´ÎªKCV µÄÖµ¡£
	0x02£ºÊ×ÏÈ¶ÔÃÜÔ¿Ã÷ÎÄ½øÐÐÆæÐ£Ñé£¬ÔÙ¶Ô¡° \x12\x34\x56\x78\x90\x12\x34\x56\x12\x34\x56\x78\x90\x12\x34\x56¡±½øÐÐAES/ECB¼ÓÃÜÔËËã£¬µÃµ½ÃÜÎÄµÄÇ°3¸ö×Ö½Ú¼´ÎªKCV µÄÖµ¡£
	0x03£º´«ÈëÒ»´®Êý¾ÝKcvData£¬Ê¹ÓÃÔ´ÃÜÔ¿¶Ô[ Ä¿µÄÃÜÔ¿ÃÜÎÄ+KCV Êý¾Ý]½øÐÐÖ¸¶¨Ä£Ê½µÄMAC ÔËËã£¬µÃµ½8 ¸ö×Ö½ÚµÄMAC ¼´ÎªKCV µÄÖµ¡£
128 bytes
	KcvData£º
	. KcvMode Îª0x00/0x01/0x02 Ê±£¬Ìî³äËæ»úÊý£»
	. KcvMode Îª0x03 Ê±£¬KcvDataµÚÒ»¸ö×Ö½ÚÎª²ÎÓë¼ÆËãµÄKCVÊý¾ÝµÄ³¤¶È£¬Ö®ºóÎªKCV Êý¾Ý£¬KCV Êý¾ÝÖ®ºóµÚÒ»¸ö×Ö½Ú±íÊ¾MAC ÔËËãÄ£Ê½¡£
8 bytes
. µ±KcvMode=0x00 Ê±£¬Ìî³äËæ»úÊý£»
. µ±KcvMode=0x01/0x02/0x03 Ê±£¬KcvValue Ö¸ÏòKCV µÄÖµ¡£
2 bytes Ìî³äËæ»úÊý
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN PED Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedWriteAesKey(const unsigned char *KeyBlock)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃTAESK »òPED_AES_TDK ÃÜÔ¿¶ÔDataInLen Ö¸¶¨³¤¶ÈµÄÊý¾Ý½øÐÐAES ¼Ó½âÃÜÔËËã¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ TAESK ÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~100]¡£
InitVector ¡¾ÊäÈë/Êä³ö¡¿¼Ó½âÃÜÔËËãµÄ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£
µ±Mode=0x02/0x03/0x04/0x05 Ê±,ÐèÒªÓÃµ½³õÊ¼ÏòÁ¿£¬ÎªNULL Ê±Ä¬ÈÏÎª16 ×Ö½ÚµÄÈ«0x00¡£
µ±Mode=0x00/0x01 Ê±£¬²»ÐèÒª³õÊ¼ÏòÁ¿£¬¿ÉÒÔÎªNULL¡£
µ±Mode=0x06/0x07 Ê±£¬±íÊ¾ÔËËãÊ±ËùÐèµÄ16 ×Ö½Ú³¤¶ÈµÄÁÙÊ±¼ÆÊýÆ÷£¬ÔËËã³É¹¦ºó¸Ã¼ÆÊýÆ÷½«±»¸üÐÂ¡£
DataIn¡¾ÊäÈë¡¿ ÐèÒª½øÐÐÔËËãµÄÊý¾Ý
DataInLen¡¾ÊäÈë¡¿ÐèÒª½øÐÐÔËËãµÄÊý¾Ý³¤¶È£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬Ó¦Ð¡ÓÚµÈÓÚ1024£¬ÇÒÎª16 µÄ±¶Êý¡£µ±ÔËËãÄ£Ê½ÎªCTR Ä£Ê½Ê±£¬Êý¾Ý³¤¶ÈÃ»ÓÐÏÞÖÆ¡£
DataOut¡¾Êä³ö¡¿ Ö¸ÏòÔËËãºóµÄÊý¾Ý¡£
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
	ERR_INVALID_PARAM ÎÞÐ§µÄ²ÎÊý */
int OsPedAes(int KeyIdx,unsigned char*InitVector,const unsigned char*DataIn,int DataInLen,unsigned char *DataOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}




//¹¦ÄÜ Éú³ÉÒ»×éSM2 ÃÜÔ¿¶Ô¡£
/*²ÎÊý
PvtKey¡¾Êä³ö¡¿ Ö¸ÏòSM2 Ë½Ô¿£¬32 ×Ö½Ú
PubKey¡¾Êä³ö¡¿ Ö¸ÏòSM2 ¹«Ô¿£¬64 ×Ö½Ú
KeyLenBit¡¾ÊäÈë¡¿ Ë½Ô¿Î»Êý£¬256 Î»
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó */
int OsPedGenSM2Pair(unsigned char *PvtKey,unsigned char *PubKey,int KeyLenBit)
{
	return ERR_DEV_NOT_OPEN;
}




//¹¦ÄÜ ×¢ÈëSM2 Ë½Ô¿»ò¹«Ô¿µ½PED¡£
/*²ÎÊý
KeyIdx ¡¾ÊäÈë¡¿ SM2 ÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~20]
KeyType¡¾ÊäÈë¡¿ÃÜÔ¿ÀàÐÍ£º
	PED_SM2_PVT_KEY 0x30 Ë½Ô¿
	PED_SM2_PUB_KEY 0x31 ¹«Ô¿
KeyValue ¡¾ÊäÈë¡¿
	µ±KeyType=0x30 Ê±£¬KeyValue ³¤¶ÈÎª32 ×Ö½Ú
	µ±KeyType=0x31 Ê±£¬KeyValue ³¤¶ÈÎª64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó */
int OsPedWriteSM2Key(int KeyIdx,int KeyType,unsigned char *KeyValue)
{
	return ERR_DEV_NOT_OPEN;
}



//¹¦ÄÜ Ê¹ÓÃ SM2 Ëã·¨»ñµÃÇ©ÃûÐÅÏ¢¡£
/*²ÎÊý
PubKeyIdx¡¾ÊäÈë¡¿ SM2 ¹«Ô¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~20]
PvtKeyIdx¡¾ÊäÈë¡¿ SM2 Ë½Ô¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Uid¡¾ÊäÈë¡¿ Ç©ÃûÕßIDÎÞÌØÊâÔ¼¶¨µÄÇé¿ö£¬ÓÃ»§Éí·ÝµÄ±êÊ¶ID³¤¶ÈÎª16 ×Ö½Ú£¬
			ÆäÄ¬ÈÏÖµÎª0x31, 0x32,0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38¡£
UidLen¡¾ÊäÈë¡¿ Ç©ÃûÕßID ³¤¶È£¬Ð¡ÓÚµÈÓÚ512 ×Ö½Ú¡£
Input¡¾ÊäÈë¡¿ ÐèÒªÇ©ÃûµÄÊý¾Ý
InputLen¡¾ÊäÈë¡¿ Êý¾Ý³¤¶È£¬Ð¡ÓÚµÈÓÚ2048 ×Ö½Ú
Signature¡¾ÊäÈë¡¿ Ç©ÃûÖµ£¬64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Sign(int PubKeyIdx,int PvtKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃ SM2 ¹«Ô¿ÑéÖ¤Ç©Ãû¡£
/*²ÎÊý
PubKeyIdx¡¾ÊäÈë¡¿ SM2 ¹«Ô¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Uid¡¾ÊäÈë¡¿ Ç©ÃûÕßID¡£ÎÞÌØÊâÔ¼¶¨µÄÇé¿ö£¬ÓÃ»§Éí·ÝµÄ±êÊ¶ID
µÄ³¤¶ÈÎª16 ×Ö½Ú£¬ÆäÄ¬ÈÏÖµÎª0x31,0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,0x38¡£
UidLen¡¾ÊäÈë¡¿ Ç©ÃûÕßID ³¤¶È£¬Ð¡ÓÚµÈÓÚ512 ×Ö½Ú
Input¡¾ÊäÈë¡¿ ÐèÒªÇ©ÃûµÄÊý¾Ý
InputLen¡¾ÊäÈë¡¿ Êý¾Ý³¤¶È£¬Ð¡ÓÚµÈÓÚ2048 ×Ö½Ú
Signature¡¾ÊäÈë¡¿ Ç©ÃûÖµ£¬64 ×Ö½Ú
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_VERIFY_SIGN_FAIL ÑéÖ¤Ç©ÃûÊ§°Ü
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Verify(int PubKeyIdx,unsigned char *Uid,int UidLen,unsigned char *Input,int InputLen,const unsigned char *Signature)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ Ê¹ÓÃ SM2 ¹«Ô¿¼ÓÃÜÊý¾Ý»òË½Ô¿½âÃÜÊý¾Ý¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ SM2 ÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1~20]
Input¡¾ÊäÈë¡¿ ´ý¼ÓÃÜ»ò½âÃÜµÄÊý¾Ý
InputLen¡¾ÊäÈë¡¿ Êý¾Ý³¤¶È£¬¼ÓÃÜ²Ù×÷Ê±Ð¡ÓÚµÈÓÚ£¨2048-96£©×Ö½Ú£¬½âÃÜ²Ù×÷Ê±Ð¡ÓÚµÈÓÚ2048 ×Ö½Ú¡£
Output¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊý¾Ý
OutputLen¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊý¾Ý³¤¶È£¬¼ÓÃÜºóÊý¾Ý³¤¶ÈÎªÔ­Êý¾Ý³¤¶È+96 ×Ö½Ú£¬½âÃÜºóÊý¾Ý³¤¶ÈÎªÔ­Êý¾Ý³¤¶È-96 ×Ö½Ú¡£
Mode¡¾ÊäÈë¡¿ PED_DECRYPT0x00£ºÊ¹ÓÃSM2 Ë½Ô¿½âÃÜÊý¾ÝPED_ENCRYPT0x01£ºÊ¹ÓÃSM2 ¹«Ô¿¼ÓÃÜÊý¾Ý
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨ */
int OsPedSM2Recover(int KeyIdx,unsigned char *Input,int InputLen,unsigned char *Output,int *OutputLen,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}

//¹¦ÄÜ Ê¹ÓÃ SM3 Ëã·¨¼ÆËãÔÓ´ÕÖµ¡£
/*²ÎÊý
Input¡¾ÊäÈë¡¿ ÊäÈëÊý¾Ý
InputLen¡¾ÊäÈë¡¿ ÊäÈëÊý¾Ý³¤¶È
Output¡¾Êä³ö¡¿ ÔÓ´ÕÖµ£¬32 ×Ö½Ú¡£
Mode¡¾ÊäÈë¡¿ Ö§³Ö0x00£¬ÆäËüÖµ±£Áô¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó */
int OsPedSM3(unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃSM4 Ëã·¨¼ÓÃÜ»ò½âÃÜÊý¾Ý¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TDK µÄË÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
InitVector¡¾ÊäÈë¡¿ ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£¶ÔÓÚECB Ä£Ê½¸Ã²ÎÊýÎªNULL¡£
Input¡¾ÊäÈë¡¿ ÐèÒª¼ÓÃÜ»ò½âÃÜµÄÊý¾Ý
InputLen¡¾ÊäÈë¡¿ Êý¾Ý³¤¶ÈÐ¡ÓÚµÈÓÚ1024£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬ÇÒÎª16 µÄ±¶Êý
Output¡¾Êä³ö¡¿ ¼ÓÃÜ»ò½âÃÜºóµÄÊý¾Ý£¬³¤¶ÈÎªÊäÈë³¤¶È
Mode¡¾ÊäÈë¡¿ 
PED_SM4_ECB_DECRYPT 0x00:SM4 ECB ½âÃÜ
PED_SM4_ECB_ENCRYPT 0x01:SM4 ECB ¼ÓÃÜ
PED_SM4_CBC_DECRYPT 0x02:SM4 CBC ½âÃÜ
PED_SM4_CBC_ENCRYPT 0x03:SM4 CBC ¼ÓÃÜ
·µ»Ø 
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó */
int OsPedSM4(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *Output,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ê¹ÓÃSM4 Ëã·¨¼ÆËãMAC¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TAK µÄÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
InitVector¡¾ÊäÈë¡¿ ³õÊ¼ÏòÁ¿£¬16 ×Ö½Ú¡£
Input¡¾ÊäÈë¡¿ ÐèÒª½øÐÐMAC ÔËËãµÄÊý¾Ý
InputLen¡¾ÊäÈë¡¿ Êý¾Ý³¤¶ÈÐ¡ÓÚµÈÓÚ1024£¬ÒÔ×Ö½ÚÎªµ¥Î»£¬ÇÒÎª16 µÄ±¶Êý
MacOut¡¾Êä³ö¡¿ MAC Öµ
Mode¡¾ÊäÈë¡¿ 
	0x00£ºÊ¹ÓÃSM4 CBC Ëã·¨¼ÆËãMAC Öµ£¬Ê×ÏÈ½«³õÊ¼ÏòÁ¿ÓëBLOCK1 ½øÐÐÒì»ò£¬²¢ÓÃSM4Ëã·¨Ê¹ÓÃTAK¶ÔÒì»òµÄ½á¹û½øÐÐ¼ÓÃÜ£¬
			È»ºó»ñµÃµÄÃÜÎÄÓëBLOCK2 Òì»ò£¬ÓÃSM4 Ëã·¨Ê¹ÓÃTAK ¶Ô½á¹û¼ÓÃÜ£¬°´Ë³Ðò¸ø³ö16 ×Ö½ÚµÄ¼ÓÃÜ½á¹û¡£MacOut Îª16 ×Ö½Ú¡£
	0x01£ºÊ¹ÓÃSM4-TAK ÃÜÔ¿¶ÔÊäÈëÊý¾Ý¼ÆËãSM3 Hash£¬¼ÆËã½á¹û×÷ÎªMacOut(32 ×Ö½Ú)¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó */
int OsPedGetMacSM(int KeyIdx,unsigned char *InitVector,unsigned char *Input,int InputLen,unsigned char *MacOut,int Mode)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ Ö¸¶¨µÄÊ±ÏÞÄÚ£¬É¨Ãè¼üÅÌÉÏÊäÈëµÄPIN ²¢Êä³ö²ÉÓÃSM4 Ëã·¨Éú³ÉµÄPIN block ¼ÓÃÜÊý¾Ý¿é¡£
/*²ÎÊý
KeyIdx¡¾ÊäÈë¡¿ PED_SM4_TPK µÄÃÜÔ¿Ë÷ÒýºÅ£¬È¡Öµ·¶Î§Îª[1¡«100]
ExpPinLenIn¡¾ÊäÈë¡¿ ¿ÉÊäÈëµÄºÏ·¨ÃÜÂë³¤¶È×Ö·û´®£¬0~12 µÄÃ¶¾Ù¼¯ºÏ¡£
Ó¦ÓÃ³ÌÐò°ÑÔÊÐíµÄÃÜÂë³¤¶ÈÈ«²¿Ã¶¾Ù³öÀ´£¬²¢ÇÒÓÃ¡°,¡±ºÅ¸ô¿ªÃ¿¸ö³¤¶È£¬ÈçÔÊÐíÊäÈë4¡¢6 Î»ÃÜÂë£¬Ôò¸Ã×Ö·û´®Ó¦¸ÃÉèÖÃÎª¡°4,6¡±¡£
DataIn¡¾ÊäÈë¡¿ µ±Mode=0x00 Ê±£¬DataIn Ö¸Ïò¿¨ºÅÒÆÎ»ºóÉú³ÉµÄ16 Î»Ö÷ÕÊºÅ¡£
PinBlockOut¡¾Êä³ö¡¿ Éú³ÉµÄÃÜÎÄPIN block£¬16 ×Ö½Ú
Mode¡¾ÊäÈë¡¿ PIN block µÄ¸ñÊ½0x00 ISO9564 ¸ñÊ½0
TimeoutMs¡¾ÊäÈë¡¿ ÊäÈëPIN µÄ³¬Ê±Ê±¼ä£¬µ¥Î»£ººÁÃë¡£×î´óÖµÎª300000ms¡£0 ±íÊ¾²ÉÓÃÄ¬ÈÏ³¬Ê±Ê±¼ä30000ms¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý
	ERR_SYS_BAD ÏµÍ³´íÎó
	ERR_PED_KEY_IDX_ERR ÃÜÔ¿Ë÷Òý´íÎó
	ERR_PED_KEY_TYPE_ERR ÃÜÔ¿ÀàÐÍ´íÎó
	ERR_PED_NO_KEY ÃÜÔ¿²»´æÔÚ
	ERR_PED_TAMPERED PED ±»Ëø¶¨
	ERR_PED_KEY_LEN_ERR ÃÜÔ¿³¤¶È´íÎó
	ERR_PED_NO_PIN_INPUT Î´ÊäÈëÈÎºÎ¼üÖµ
	ERR_PED_PIN_INPUT_CANCEL È¡ÏûÊäÈë
	ERR_PED_WAIT_INTERVAL ¼ä¸ôÊ±¼äÌ«¶Ì */
int OsPedGetPinBlockSM4(int KeyIdx,const char *ExpPinLenIn,unsigned char *DataIn,unsigned char *PinBlockOut,int Mode,unsigned long TimeoutMs)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ¼ì²éDESFire ¿¨¶Ë´«À´µÄ»á»°ÃÜÔ¿B ²¢Éú³É»á»°ÃÜÔ¿A¡£½«A ºÍBºÏ²¢ÎªÒ»¸öÍêÕûµÄ»á»°ÃÜÔ¿£¬È»ºó¶ÔÆä½øÐÐ¼ÓÃÜ²¢Êä³ö¡£
/*²ÎÊý
SrcKeyIdx¡¾ÊäÈë¡¿
DESFire ¹¤×÷ÃÜÔ¿Ë÷Òý£¬È¡Öµ·¶Î§Îª1-100¡£
KeySetVer¡¾ÊäÈë¡¿ ÃÜÔ¿°æ±¾£¬ÓÃÓÚ¼ì²éDESFire °æ±¾¡£
DivType¡¾ÊäÈë¡¿ÃÜÔ¿·¢É¢Ä£Ê½£º
. µ±DivType = 0x00 Ê±£¬±íÊ¾²»·¢É¢£¬´ËÊ±DESFire ÃÜÔ¿ÓÃÓÚ¼ÓÃÜ»á»°ÃÜÔ¿£»
. µ±DivType = 0x01 Ê±£¬½áºÏUidÀ´·¢É¢ÃÜÔ¿£¬¸Ã·¢É¢ÃÜÔ¿ÓÃÓÚ¼ÓÃÜ»á»°ÃÜÔ¿¡£
Mode¡¾ÊäÈë¡¿»á»°ÃÜÔ¿µÄ¼ÓÃÜÀàÐÍ£º0x02£º16 ×Ö½ÚµÄ3DES ¼ÓÃÜÔËËã
Uid¡¾ÊäÈë¡¿ÓÃ»§Êý¾Ý£¬Êý¾Ý³¤¶È¹Ì¶¨Îª8 ×Ö½Ú£¬ÓÃÓÚ·¢É¢»á»°ÃÜÔ¿¡£
EncRndB¡¾ÊäÈë¡¿DESFire ¿¨Éú³ÉµÄ»á»°ÃÜÔ¿B£º
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª8 »ò16 ×Ö½ÚÊ±£¬ EncRndB ³¤¶ÈÎª8 ×Ö½Ú£»
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª24 ×Ö½ÚÊ±£¬EncRndB ³¤¶ÈÎª16 ×Ö½Ú¡£
EncSessionKey¡¾Êä³ö¡¿ ¼ÓÃÜµÄ(RndA + RndB¡¯).
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedDFAuthDiver(int SrcKeyIdx,int KeySetVer,int DivType,unsigned char Mode,unsigned char *Uid,unsigned char *EncRndB,unsigned char *EncSessionKey)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ¼ì²éDESFire ¿¨¶Ë´«À´µÄÃÜÎÄ»á»°ÃÜÔ¿A¡¯¡£
/*²ÎÊý
EncRndA¡¾ÊäÈë¡¿ ÃÜÎÄA¡¯¡£
DataLen¡¾ÊäÈë¡¿EncRndA ³¤¶È£º
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª8 »ò16 ×Ö½ÚÊ±£¬EncRndA ³¤¶ÈÎª8 ×Ö½Ú£»
. µ±»á»°ÃÜÔ¿³¤¶ÈÎª24 ×Ö½ÚÊ±£¬EncRndA ³¤¶ÈÎª16 ×Ö½Ú¡£
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedDFAuthMerge(unsigned char *EncRndA,int DataLen)
{
	return ERR_DEV_NOT_OPEN;
}


//¹¦ÄÜ ×¢ÈëÀ´×ÔRKI ·þÎñÆ÷µÄÃÜÔ¿¡£
/*²ÎÊý
KeyBlkLen ¡¾ÊäÈë¡¿ RKI ÃÜÔ¿Êý¾Ý³¤¶È
KeyBlk ¡¾ÊäÈë¡¿ RKI ÃÜÔ¿Êý¾Ý
DstKeyIdx ¡¾ÊäÈë¡¿Ä¿µÄÃÜÔ¿Ë÷Òý£¬ÔÝÎÞÒâÒå£¬¿ÉÒÔÎªÈÎÒâÖµ
·µ»Ø
	RET_OK ³É¹¦
	ERR_DEV_NOT_OPEN Éè±¸Î´´ò¿ª
	ERR_INVALID_PARAM ·Ç·¨²ÎÊý */
int OsPedRkiInjectKey(int KeyBlkLen,unsigned char *KeyBlk,unsigned char DstKeyIdx)
{
	return ERR_DEV_NOT_OPEN;
}



