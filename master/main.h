
#ifndef _MIAI_
#define _MIAI_

typedef struct
{
	u8 DormancyState;//ÐÝÃß×´Ì¬
	u8 Screensaver;//ÆÁ±£×´Ì¬
	pthread_t threadID;//Ë¢ÐÂ×´Ì¬À¸uiÏß³Ì

}Status_Messages;


extern void API_Trace(char* pMsg,...);
extern void APP_Trace_Hex(char* msg,void* pBuff,int Len);

#define TRACE							API_Trace		//MercuryTrace		//
//#define TRACE_HEX(msg,pBuff,Len)		APP_Trace_Hex(msg,pBuff,Len)



#endif
