
#ifndef _SDK_PRINTF_
#define _SDK_PRINTF_

#define ERR_PRN_BUSY				-3701 //´òÓ¡»úÃ¦
#define ERR_PRN_PAPEROUT			-3702 //´òÓ¡»úÈ±Ö½
#define ERR_PRN_WRONG_PACKAGE	-3703 //Êý¾Ý°ü¸ñÊ½´íÎó
#define ERR_PRN_OVERHEAT			-3704 //´òÓ¡»ú¹ýÈÈ
#define ERR_PRN_OUTOFMEMORY		-3705 //Òª´òÓ¡Êý¾Ý¹ý´ó,³¬³ö»º³åÇø³¤¶È
#define ERR_PRN_OVERVOLTAGE		-3706 //µçÑ¹¹ý¸ß


//¹¦ÄÜ ´ò¿ª´òÓ¡»úÉè±¸£¬°üÀ¨ÎïÀíºÍÐéÄâ´òÓ¡»ú¡£
/*
´ò¿ª´òÓ¡»úÉè±¸£¬°üÀ¨ÎïÀíºÍÐéÄâ´òÓ¡»ú¡£
²ÎÊý
printertype¡¾ÊäÈë¡¿
	´òÓ¡»úÉè±¸ÀàÐÍ
	. PRN_REAL£ºÎïÀí´òÓ¡Éè±¸£»
	. PRN_BMP£ºÐéÄâ´òÓ¡Éè±¸£¬´òÓ¡½á¹û
	ÒÔBMP ¸ñÊ½±£´æÔÚ±¾µØ¡£
targetname¡¾ÊäÈë¡¿
	´òÓ¡Éè±¸ÎªÎïÀí´òÓ¡»úÊ±£¬¸Ã²ÎÊý±ØÐëÎªNULL£»
	´òÓ¡Éè±¸ÎªÐéÄâ´òÓ¡»úÊ±£¬Ö¸ÏòÊä³öµ½±¾µØµÄ
	BMP ÎÄ¼þµÄÂ·¾¶¡£ÈôÖ¸¶¨ÎÄ¼þÒÑ¾­´æÔÚ£¬Ôò¸²¸Ç¡£
*/
extern int OsPrnOpen(unsigned int printertype,const char*targetname);

//¹¦ÄÜ ¹Ø±Õ´òÓ¡»ú¡£
extern void OsPrnClose(void);


//¹¦ÄÜ ÖØÖÃ´òÓ¡²ÎÊý,Çå¿Õ´òÓ¡»º´æ¡£
extern void OsPrnReset(void);

//¹¦ÄÜ ÉèÖÃÐéÄâ´òÓ¡»úÏà¹Ø²ÎÊý¡£
/*
²ÎÊý
Width¡¾ÊäÈë¡¿ ¿í¶È
Height¡¾ÊäÈë¡¿ ¸ß¶È
*/
extern int OsPrnSetSize (unsigned int Width,unsigned int Height);

//¹¦ÄÜ ÉèÖÃ´òÓ¡·½Ïò¡£
/*
²ÎÊý Mode¡¾ÊäÈë¡¿
. 0£ººáÏò´òÓ¡¡£
. 1£º×ÝÏò´òÓ¡¡£
*/
extern int OsPrnSetDirection (unsigned char Mode);

//¹¦ÄÜ ÉèÖÃ´òÓ¡»Ò¶È¡
/*£
²ÎÊý Level
. Level =0£¬±£Áô¡£
. Level =1£¬È±Ê¡ºÚ¶È£¬¼´ÆÕÍ¨´òÓ¡µ¥¡£
. Level =2£¬±£Áô¡£
. Level =3£¬Ë«²ãÈÈÃô´òÓ¡¡£
. Level =4£¬Ë«²ãÈÈÃô´òÓ¡£¬±È3 µÄºÚ¶È¸ü¸ß¡£
*/
extern void OsPrnSetGray(int Level);

//¹¦ÄÜ ÉèÖÃ´òÓ¡¼ä¾à¡£
/*
²ÎÊý
CharSpace : ×Ö¼ä¾à£¬µ¥Î»ÎªµãÊý(¶ÔÇ¿ÖÆµÄ·ÇµÈ¿í×ÖÌåÎÞÐ§£¬Èç¸÷ÖÖ°¢À­²®×ÖÌå¡¢Ì©ÎÄ×ÖÌå)
LineSpace ÐÐ¼ä¾à£¬µ¥Î»ÎªµãÊý
*/
extern void OsPrnSetSpace(int CharSpace,int LineSpace);
;
//¹¦ÄÜ ÉèÖÃ×ÖÌå·´ÏÔÊôÐÔ£¬È±Ê¡Çé¿öÏÂÕý³£´òÓ¡¡£
/* ²ÎÊý Attr: 0£ºÕý³£    1£º·´ÏÔ */
extern void OsPrnSetReversal(int Attr);

//¹¦ÄÜ ÉèÖÃ×óÓÒ±ß¾à.
/*²ÎÊý
Left¡¾ÊäÈë¡¿ ×ó±ß¾à£¬ÓÐÐ§·¶Î§ÊÇ[0£¬100]£¬Ä¬ÈÏÖµÎª0¡£
Right¡¾ÊäÈë¡¿ ÓÒ±ß¾à£¬ÓÐÐ§·¶Î§ÊÇ[0£¬100]£¬Ä¬ÈÏÖµÎª0¡£
*/
extern int OsPrnSetIndent (unsigned int Left,unsigned int Right);

//¹¦ÄÜ ²éÑ¯´òÓ¡»úµ±Ç°×´Ì¬£¬ÇÒ½öÊÊÓÃÓÚÎïÀí´òÓ¡»ú¡£
/*·µ»Ø:
RET_OK ´òÓ¡»ú¹¤×÷Õý³£
ERR_PRN_BUSY ´òÓ¡»úÃ¦
ERR_PRN_PAPEROUT ´òÓ¡»úÈ±Ö½
ERR_PRN_OVERHEAT ´òÓ¡»ú¹ýÈÈ
*/
extern int OsPrnCheck(void);

//¹¦ÄÜ »ñÈ¡µ±Ç°ÈÎÎñÒÑ´òÓ¡µÄµãÐÐÊý¡£
//·µ»Ø >=0 µ±Ç°ÒÑ´òÓ¡µãÐÐ¸öÊý
extern int OsPrnGetDotLine(void);

//¹¦ÄÜ Ñ¡Ôñ´òÓ¡×ÖÌå¡£
/*²ÎÊý: fontname¡¾ÊäÈë¡¿ ×ÖÌå(ÎÄ¼þ)Ãû³Æ
·µ»Ø:
RET_OK ³É¹¦
ERR_FONT_NOT_EXIST ×ÖÌå²»´æÔÚ
ERR_INVALID_PARAM ·Ç·¨²ÎÊý
*/
extern int OsPrnSetFont(const char* fontname);

//¹¦ÄÜ ÉèÖÃ´òÓ¡×ÖÌå´óÐ¡¡£
/*²ÎÊý
SingleCodeWidth:µ¥ÄÚÂë×ÖÌå¿í¶È¿ØÖÆ(¶Ô·ÇµÈ¿íÊä³ö×ÖÌåÀ´Ëµ£¬ÕæÕýÃ¿¸ö×Ö·ûµÄ¿í¶È²»Ò»¶¨Âú×ã´ËÉèÖÃ),Ñ¡ÖµÇø¼äÎª8~64
SingleCodeHeight:µ¥ÄÚÂë×ÖÌå¸ß¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª8~64
MultiCodeWidth:¶àÄÚÂë×ÖÌå¿í¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª12~64
MultiCodeHeight:¶àÄÚÂë×ÖÌå¸ß¶È¿ØÖÆ,Ñ¡ÖµÇø¼äÎª12~64
*/
extern void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight);

//¹¦ÄÜ ÔÚ´òÓ¡»º³åÇøÄÚ£¬Ö´ÐÐ×ßÖ½Èô¸É¸öµãÐÐ¡£
/*²ÎÊý Pixel
	Ö´ÐÐ×ßÖ½µÄµãÐÐÊý£º
	>0£º½øÖ½
	<0£ºÍËÖ½
	=0£ºÎÞ¶¯×÷
*/
extern void OsPrnFeed(int Pixel);

//¹¦ÄÜ ¸ñÊ½»¯Êä³ö×Ö·û´®µ½´òÓ¡»º³åÇøÄÚ¡£
/*²ÎÊý Str¡¾ÊäÈë¡¿ Òª´òÓ¡µÄ×Ö·û´®Ö¸Õë*/
extern void OsPrnPrintf(const char *Str, ...);

//¹¦ÄÜ Êä³öÍ¼ÐÎµ½´òÓ¡»º³åÇøÄÚ¡£
/*²ÎÊý Logo¡¾ÊäÈë¡¿Ðè´òÓ¡µÄlogo ÐÅÏ¢µÄÖ¸Õë£¬ÐÅÏ¢³¤¶È²»ÄÜ³¬¹ý20000 ¸ö×Ö½Ú*/
extern void OsPrnPutImage(const unsigned char *Logo);

//¹¦ÄÜ Æô¶¯´òÓ¡»ú£¬½«»º³åÇøÀïµÄÊý¾Ý´òÓ¡³öÀ´¡£
/*·µ»Ø
	RET_OK ´òÓ¡»ú¹¤×÷Õý³£
	ERR_PRN_BUSY ´òÓ¡»úÃ¦
	ERR_PRN_PAPEROUT ´òÓ¡»úÈ±Ö½
	ERR_PRN_WRONG_PACKAGE Êý¾Ý°ü¸ñÊ½´íÎó
	ERR_PRN_OVERHEAT ´òÓ¡»ú¹ýÈÈ
	ERR_PRN_OUTOFMEMORY ´òÓ¡Êý¾Ý¹ý´ó
*/
extern int OsPrnStart(void);

//¹¦ÄÜ Çå¿Õ´òÓ¡»º³åÇø
extern void OsPrnClrBuf(void);

//¹¦ÄÜ ÉèÖÃ´òÓ¡»úÊÇ·ñÔ¤×ßÖ½
/*²ÎÊý cmd ¡¾ÊäÈë¡¿
	1£º´òÓ¡²»Ô¤×ßÖ½
	2£º´òÓ¡ÓÐÔ¤×ßÖ½
*/
extern int OsPrnSetParam(unsigned int cmd);

#endif
