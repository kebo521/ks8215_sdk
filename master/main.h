
#ifndef _MIAI_
#define _MIAI_

typedef struct
{
	u8 DormancyState;//����״̬
	u8 Screensaver;//����״̬
	pthread_t threadID;//ˢ��״̬��ui�߳�

}Status_Messages;


extern void API_Trace(char* pMsg,...);
extern void APP_Trace_Hex(char* msg,void* pBuff,int Len);

#define TRACE							API_Trace		//MercuryTrace		//
//#define TRACE_HEX(msg,pBuff,Len)		APP_Trace_Hex(msg,pBuff,Len)



#endif
