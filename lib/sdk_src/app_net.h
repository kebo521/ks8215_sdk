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


typedef struct
{
	int				SocketFD;
	u16  			port;           /* port number */
	char 			sHost[32+1];	/* 域名或IP名 */
	u8				ENssL;			/* SSL标记 */
}NET_ADDR_TERM;


typedef struct
{
	NET_ADDR_TERM	*pNet;			/*当前通道 */
	NET_ADDR_TERM	net[5];
	//NET_ADDR_TERM	trade;
	u32				AcceptKey;		//受理按键标记
	u8 				NetIndex;		//当前net索引
	u8  			ENssL;          //当前操作SSL标记
	u8				GsmSslInit;		//Gsmssl初始化标记,交易为1,TMS为2
   	u8				sslconnet;		//SSL连接标记-
   	u8				SaveSleepEn;
}NET_ADDR_S;
extern NET_ADDR_S		tNetAddr;

typedef int (*CHECK_DATA_FULL)(char *,int); 

extern int APP_Network_Connect(char* pHostIp,u16 port,int ENssl);
extern int APP_Network_Send(char* pBuff,int len);
extern int APP_Network_Recv(char* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull);
extern int APP_Network_Disconnect(int timeOutMs);
extern void APP_Network_KeyAccept(u32 bitflag);




#endif
