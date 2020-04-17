#ifndef _PE_NET_
#define _PE_NET_

enum NET_STATE
{
	NET_NULL			=0x0000,
		
	NET_WLAN_CLOSE		=0x0000,
	NET_WLAN_DisHost	=0x0010,	//DIS Connect
	NET_WLAN_CntHost	=0x0011,
	NET_WLAN_cetCenter	=0x0012,

	STATE_NET_2G		=0x2000,
	STATE_NET_3G		=0x3000,
	STATE_NET_4G		=0x4000,
	STATE_NET_5G		=0x5000,

	STATE_NET_CLOSE		=0x0000,
	STATE_NET_DisPDP	=0x0800,
	STATE_NET_CntPDP	=0x0900,
	STATE_NET_CntCenter	=0x0B00,
};	
//extern int APP_GetNetState(void);
//=======================================================================================

typedef enum
{
	SR_STAIP=1,	//<Station	IP	address>
	SR_STAMAC=2,	//<Station	MAC	address>
}APP_MSG_TYPE;

extern int APP_Network_Init(const void *pApiSsldef);	//(API_SSL_Def *pApiSsldef)

typedef int (*CHECK_DATA_FULL)(u8 *,int); 

extern int APP_Network_Connect(char* pHostIp,u16 port,int ENssl);
extern int APP_Network_Send(u8* pBuff,int len);
extern int APP_Network_Recv(u8* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull);
extern int APP_Network_Disconnect(int timeOutMs);
extern void APP_Network_KeyAccept(u32 bitflag);




#endif
