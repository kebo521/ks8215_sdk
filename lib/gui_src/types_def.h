
#ifndef TYPES_DEF_H
#define TYPES_DEF_H


 
#define API_strlen		strlen
#define API_strcpy		strcpy
#define API_memcpy		memcpy
#define API_memset		memset
#define API_memmove		memmove
#define API_sprintf		sprintf

extern void API_Trace(char* pMsg,...);
extern void APP_Trace_Hex(char* msg,void* pBuff,int Len);

#define TRACE							API_Trace		//MercuryTrace		//
#define TRACE_HEX(msg,pBuff,Len)		APP_Trace_Hex(msg,pBuff,Len)


//===================================================================================


#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE
#define FALSE 0
#endif /*FALSE*/

#ifndef bool_t
#define bool_t uint8_t
#endif /*bool_t*/


#endif /*TYPES_DEF_H*/
