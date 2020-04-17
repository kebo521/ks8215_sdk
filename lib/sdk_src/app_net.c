
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 

#include "app_net.h" 
#include "tls/ssl.h" 

#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#if(0)

#include<stdlib.h>
#include<errno.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>


#define PORT_NUMBER 8888
#define BACKLOG 10

/* socket->bind->listen->accept->send/recv->close*/
int main(intargc, char**argv)
{ 
	int sock_fd, new_fd; 
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret; 
	int addr_len; 
	int recv_len; 
	unsigned char recv_buf[ 1000]; 
	int client_num = -1; 

	signal(SIGCHLD,SIG_IGN); 

	/* socket */
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET:IPV4;SOCK_STREAM:TCP
	if( -1== sock_fd) 
	{ 
		fprintf( stderr, "socket error:%sna", strerror(errno)); 
		exit( 1); 
	} 

	/* set server sockaddr_in */
	memset(&server_addr, 0, sizeof(struct sockaddr_in)); //clear
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY:This machine all IP
	server_addr.sin_port = htons(PORT_NUMBER); 

	/* bind */
	ret = bind(sock_fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)); 
	if( -1== ret) 
	{ 
		fprintf( stderr, "bind error:%sna", strerror(errno)); 
		close(sock_fd); 
		exit( 1); 
	} 

	/* listen */
	ret = listen(sock_fd, BACKLOG); 
	if( -1== ret) 
	{ 
		fprintf( stderr, "listen error:%sna", strerror(errno)); 
		close(sock_fd); 
		exit( 1); 
	} 

	/* accept */
	while( 1) 
	{ 
		addr_len = sizeof(struct sockaddr); 
		new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &addr_len); 
		if( -1 == new_fd) 
		{ 
			fprintf( stderr, "accept error:%sna", strerror(errno)); 
			close(sock_fd); 
			exit( 1); 
		} 

		client_num++; 
		fprintf( stderr, "Server get connetion form client%d: %sn", client_num, inet_ntoa(client_addr.sin_addr)); 

		if(!fork()) 
		{ 
			/* Child process */
			while( 1) 
			{ 
				/* recv */
				recv_len = recv(new_fd, recv_buf, 999, 0); 
				if(recv_len <= 0) 
				{ 
					fprintf( stderr, "recv error:%sna", strerror(errno)); 
					close(new_fd); 
					exit( 1); 
				} 
				else
				{ 
					recv_buf[recv_len] = '0'; 
					printf( "Get msg from client%d: %sn", client_num, recv_buf); 
				} 
			} 
			close(new_fd); 
		} 
	} 
	/* close */
	close(sock_fd); 
	exit( 0); 
} 
/*
* tcp_client.c
# Copyright (C) 2017 hceng, <huangcheng.job@foxmail.com>
# Licensed under terms of GPLv2
#
# This program is used for TCP / UDP learning.
# https://hceng.cn/
*/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT_NUMBER 8888

/* socket->connect->send->close*/
int main(intargc, char*argv[])
{ 
	int sock_fd; 
	struct sockaddr_in server_addr;
	int ret; 
	unsigned char send_buf[ 1000]; 
	int send_len; 

	if(argc != 2) 
	{ 
		fprintf( stderr, "Usage:%s hostnamena", argv[ 0]); 
		exit( 1); 
	} 

	/* socket */
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET:IPV4;SOCK_STREAM:TCP
	if( -1== sock_fd) 
	{ 
		fprintf( stderr, "socket error:%sna", strerror(errno)); 
		exit( 1); 
	} 

	/* set sockaddr_in parameter*/
	memset(&server_addr, 0, sizeof(struct sockaddr_in)); //clear
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(PORT_NUMBER); 
	ret = inet_aton(argv[ 1], &server_addr.sin_addr); 
	if( 0== ret) 
	{ 
		fprintf( stderr, "server_ip error.n"); 
		close(sock_fd); 
		exit( 1); 
	} 

	/* connect */
	ret = connect(sock_fd, ( conststruct sockaddr *)&server_addr, sizeof(struct sockaddr)); 
	if( -1== ret) 
	{ 
		fprintf( stderr, "connect error:%sna", strerror(errno)); 
		close(sock_fd); 
		exit( 1); 
	} 

	while( 1) 
	{ 
		if(fgets(send_buf, 999, stdin)) 
		{ 
			/* send */
			send_len = send(sock_fd, send_buf, strlen(send_buf), 0); 
			if(send_len <= 0) 
			{ 
				fprintf( stderr, "send error:%sna", strerror(errno)); 
				close(sock_fd); 
				exit( 1); 
			} 
		} 
	} 

	/* close */
	close(sock_fd); 
	exit( 0); 
} 



/* C 语言服务器端代码*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
	struct sockaddr_in stSockAddr;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == SocketFD)
	{
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}
	memset(&stSockAddr, 0, sizeof(stSockAddr));
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(1100);
	stSockAddr.sin_addr.s_addr = INADDR_ANY;
	if(-1 == bind(SocketFD,(struct sockaddr *)&stSockAddr,sizeof(stSockAddr)))
	{
		perror("error bind failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	if(-1 == listen(SocketFD, 10))
	{
		perror("error listen failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	for(;;)
	{
		int ConnectFD = accept(SocketFD, NULL, NULL);
		if(0 > ConnectFD)
		{
			perror("error accept failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		/* 执行读写操作 */
		read(ConnectFD,buff,size)
		if (-1 == shutdown(ConnectFD, SHUT_RDWR))
		{
			perror("can not shutdown socket");
			close(ConnectFD);
			exit(EXIT_FAILURE);
		}
		close(ConnectFD);
	}
	return EXIT_SUCCESS;
}




/* C 语言客户端代码*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
	struct sockaddr_in stSockAddr;
	int Res;
	int KeepAlive = 1;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == SocketFD)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}
	Res = setsockopt(SocketFD, SOL_SOCKET, SO_KEEPALIVE, (void*)&KeepAlive, sizeof(KeepAlive));
	if (-1 == Res)
	{
		perror("cannot setkeepalive");
		exit(EXIT_FAILURE);
	}
	memset(&stSockAddr, 0, sizeof(stSockAddr));
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(1100);

//	ret = inet_aton(argv[ 1], &server_addr.sin_addr); 

	
	Res = inet_pton(stSockAddr.sin_family, "192.168.1.3", &stSockAddr.sin_addr);
	if (0 > Res)
	{
		perror("error: first parameter is not a valid address family");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	else if (0 == Res)
	{
		perror("char string (second parameter does not contain validipaddress)");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	if (-1 == connect(SocketFD,(struct sockaddr *)&stSockAddr,sizeof(stSockAddr)))
	{
		perror("connect failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	//send_buf = send(SocketFD, send_buf, strlen(send_buf), 0); 
	//ecv_len = recv(new_fd, recv_buf, 999, 0);

	
	/* 执行读写操作*/
	shutdown(SocketFD, SHUT_RDWR);
	close(SocketFD);
	return EXIT_SUCCESS;
}










#endif

typedef struct  
{
	char* Mask;		// "SSL"
	int (*Open)(mbedtls_ssl_send_t *,mbedtls_ssl_recv_timeout_t *,int,unsigned char *, int);
	int (*Handshake)(void);
	int (*Send)(unsigned char *, int);
	int (*Recv)(unsigned char *, int);
	int (*GetState)(int);	//mS 默认100ms
	void (*Close)(void);
}NET_SSL_API;

static NET_SSL_API *pAppNetSsl=NULL;


typedef struct
{
	int				SocketFD;
	struct sockaddr_in stSockAddr;
	char			sHost[32+2];	/* 域名或IP名 */
	u16 			port;			/* port number */
}NET_ADDR_TERM;


typedef struct
{
	u32				AcceptKey;		//受理按键标记
	NET_ADDR_TERM	*pNet;			/*当前通道 */
	NET_ADDR_TERM	net[4];
	NET_ADDR_TERM	trade;
	u8 				NetIndex;		//当前net索引
	u8  			ENssL;          //当前操作SSL标记
	u8				NetSslInit;		//Gsmssl初始化标记,交易为1,TMS为2
   	u8				sslconnet;		//SSL连接标记-
}NET_ADDR_S;

static NET_ADDR_S		tNetAddr={0};

//===================SSL========================
int Socket_net_send(void *ctx, const unsigned char *pSend, size_t sendlen)
{
	return send(tNetAddr.pNet->SocketFD, pSend, sendlen, 0); 
}


int Socket_net_recv_timeout(void *ctx, unsigned char *pRecv,size_t RecvSize, uint32_t timeoutMs)
{
	int ret;
	if(timeoutMs)
	{//设置接收超时
		struct timeval timeout; 
		timeout.tv_sec = timeoutMs/1000;
		timeout.tv_usec = (timeoutMs%1000)*1000;
		ret=setsockopt(tNetAddr.pNet->SocketFD,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout)); 
		if(ret)
		{
			LOG(LOG_INFO,"setsockopt = %d,[%d]\r\n",ret,errno);
		}
	}
	while(1)
	{
		ret = recv(tNetAddr.pNet->SocketFD, pRecv, RecvSize, 0);
		if(ret >0)
		{
			return ret;
		}
		else if(ret < 0)
		{
			LOG(LOG_INFO,"recv = %d,[%d]\r\n",ret,errno);
			if(ret == -1 && (errno == EAGAIN||errno == EWOULDBLOCK||errno == EINTR)) //这几种错误码，认为连接是正常的，继续接收
			{
				continue;//继续接收数据
			}
			break;//跳出接收循环
		}
	}
	return ret;
}


//==============================================================================================

#include <poll.h> 
int Connect_CheckEINTR(int sock) 
{  
	struct pollfd fd;
	int ret;
	socklen_t len;

	fd.fd = sock;
	fd.events = POLLOUT;

	while(poll(&fd, 1, -1) == -1 ) 
	{
		if(errno != EINTR )
		{
			LOG(LOG_ERROR,"poll errno=%d:%s\n",errno,strerror(errno));
			return -1;
		}
	}
	ret = 0;
	len = sizeof(ret);
	if(getsockopt(sock, SOL_SOCKET, SO_ERROR,&ret,&len) == -1 )
	{
		LOG(LOG_ERROR,"getsockopt errno=%d:%s\n",errno,strerror(errno));
		return -1;
	}
	if(ret != 0) {
		LOG(LOG_ERROR,"socket %d connect failed: %s\n",sock, strerror(ret));
		return -1;
	}
	return 0;
}  

int gNetConnect(NET_ADDR_TERM *pAddr,int timeOutMs)
{
	int ret,SocketFD;
	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == SocketFD)
	{
		LOG(LOG_ERROR,"NetConnect socket errno[%d]\r\n",errno);
		//perror("socket");
		return -1;
	}	
	{
		struct timeval timeout; 
		timeout.tv_sec = timeOutMs/1000;
		timeout.tv_usec = (timeOutMs%1000)*1000;
		//设置发送超时
		ret = setsockopt(SocketFD,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));
		if (-1 == ret)
		{
			LOG(LOG_ERROR,"NetConnect SNDTIMEO errno[%d]\r\n",errno);
			//perror("setsockopt5");
			close(SocketFD);
			return -1;
		}
	}
	{
		int KeepAlive = 1;
		ret = setsockopt(SocketFD, SOL_SOCKET, SO_KEEPALIVE,&KeepAlive, sizeof(KeepAlive));
		if (-1 == ret)
		{
			LOG(LOG_ERROR,"cannot setkeepalive errno[%d]\r\n",errno);
			//perror("setsockopt0");
			close(SocketFD);
			return -1;
		}
	}
	ret = connect(SocketFD,(struct sockaddr *)&pAddr->stSockAddr,sizeof(pAddr->stSockAddr));
	if((ret == 0) \
		||((ret == -1)&&(errno == EINTR) && (Connect_CheckEINTR(SocketFD) == 0)))
	{
		pAddr->SocketFD = SocketFD;
		return 0;
	}
	LOG(LOG_ERROR,"NetConnect[%X][%d] failed ret[%d]errno[%d]\r\n",pAddr->stSockAddr.sin_addr,pAddr->stSockAddr.sin_port,ret,errno);
	close(SocketFD);
	return -1;
}

void gNetDisConnect(NET_ADDR_TERM *pAddr)
{
	if(pAddr->SocketFD != -1)
	{
		shutdown(pAddr->SocketFD, SHUT_RDWR); /* 执行读写操作*/
		close(pAddr->SocketFD);
	}
	pAddr->SocketFD = -1;
}

int gNetworkGetHostPort(char* pHostIp,u16 port,struct sockaddr_in *pOutAdd)
{
	struct sockaddr_in stSockAddr={0};
	//memset(&stSockAddr, 0, sizeof(stSockAddr));
	if(pHostIp[0]<'0' || pHostIp[0] >'9')
	{
		struct hostent *hptr;
		/* 调用gethostbyname()。结果存在hptr结构中 */
		if((hptr = gethostbyname(pHostIp)) == NULL)
		{
			LOG(LOG_ERROR," gethostbyname error for host:%s,errno[%d]\n", pHostIp,errno);
			//perror("gethostbyname");
			return -103;
		}
		/* 将主机的规范名打出来 */
		//LOG(LOG_INFO,"official hostname:%s[%x],%x\n", hptr->h_name,hptr->h_addr,*(u32*)hptr->h_addr);
		stSockAddr.sin_family = hptr->h_addrtype;
		stSockAddr.sin_addr.s_addr=((struct in_addr *)hptr->h_addr)->s_addr;
	}
	else
	{
		stSockAddr.sin_family = AF_INET;
		if (0 >= inet_pton(stSockAddr.sin_family,pHostIp,&stSockAddr.sin_addr))
		{
			LOG(LOG_ERROR,"error: inet_pton errno[%d]\r\n",errno);
			return -106;
		}
	}
	stSockAddr.sin_port = htons(port);
	memcpy(pOutAdd,&stSockAddr,sizeof(stSockAddr));
	return 0;
}


int APP_Network_Init(const void *pApiSsldef)	//API_SSL_Def
{
	pAppNetSsl=(NET_SSL_API *)pApiSsldef;
	if(strcmp(pAppNetSsl->Mask,"SSL"))
		return -1;
	memset(&tNetAddr,0x00,sizeof(tNetAddr));
	return 0;
}


//============================================================================
int APP_Network_Connect(char* pHostIp,u16 port,int ENssl)
{
	int ret;
	if(tNetAddr.net==NULL || (tNetAddr.net->port != port) || (0!=strcmp(tNetAddr.net->sHost,pHostIp)))
	{//----暂存地址信息--避免重复获取信息减少处理时间------------------------------
		for(ret=0;ret < (sizeof(tNetAddr.net)/sizeof(tNetAddr.net[0])) ;ret++)
		{
			if(tNetAddr.net[ret].sHost[0] == 0)
			{
				tNetAddr.net[ret].port = port;
				strcpy(tNetAddr.net[ret].sHost,pHostIp);
				//tNetAddr.net[ret].stSockAddr.sin_port = 0;	//没有用过的组，参数肯定为0
				tNetAddr.pNet = &tNetAddr.net[ret];
				tNetAddr.NetSslInit=0;
				break;
			}
			else if((tNetAddr.net[ret].port == port) && (0==strcmp(tNetAddr.net[ret].sHost,pHostIp)))
			{
				if(tNetAddr.pNet != &tNetAddr.net[ret])
				{
					tNetAddr.pNet = &tNetAddr.net[ret];
					tNetAddr.NetSslInit=0;
				}
				break;
			}
		}
		if(ret == (sizeof(tNetAddr.net)/sizeof(tNetAddr.net[0])))
		{
			tNetAddr.trade.stSockAddr.sin_port = 0;
			tNetAddr.pNet = &tNetAddr.trade;
			tNetAddr.NetSslInit=0;
		}
	}	
	//--------------解析地址-之前连接过可以跳过这一步-----------------------
	
	if(tNetAddr.pNet->stSockAddr.sin_port == 0)
	{
		ret=gNetworkGetHostPort(pHostIp,port,&tNetAddr.pNet->stSockAddr);
		if(ret < 0) return ret;
	}
	ret=gNetConnect(tNetAddr.pNet,5000);
	if(ret < 0)
	{
		if(!gNetworkGetHostPort(pHostIp,port,&tNetAddr.pNet->stSockAddr))
		{//------检查域名对应的邋IP地址变更-------------------
			ret=gNetConnect(tNetAddr.pNet,5000);
			if(ret < 0) return ret;
		}
	}
	tNetAddr.ENssL = ENssl;
	//------------------SSL connet(Handshake)---------------------------------
	if(ENssl)
	{
		tNetAddr.sslconnet=0;
		if(pAppNetSsl==NULL) 
			return ERR_SYS_NOT_SUPPORT;
		if(tNetAddr.NetSslInit!=2)
		{
			pAppNetSsl->Close();
			LOG(LOG_INFO,"pTlsFuntion->ssl->Open\r\n");
			ret=pAppNetSsl->Open(Socket_net_send,Socket_net_recv_timeout,20*1000,NULL,0);
			tNetAddr.NetSslInit=2;
		}
		ret=pAppNetSsl->Handshake();
		if(ret)
		{
			LOG(LOG_ERROR,"ssl_net_funtion.Handshake[%s]Err ret[%d]\r\n",tNetAddr.pNet->sHost,ret);
			gNetDisConnect(tNetAddr.pNet);
			return ret;
		}
		tNetAddr.sslconnet=1;
	}
	return ret;	
}



   

//=======================网络发送=========================================================
int  APP_Network_Send(u8* pBuff,int len)
{
	if(tNetAddr.ENssL==1)
	{
		if(tNetAddr.sslconnet==0)
		{
			LOG(LOG_WARN,"**---Net_SSL_Reconnection--\r\n");
			if(gNetConnect(tNetAddr.pNet,5000))
			{
				LOG(LOG_ERROR,"---Net_SSL_SocketConnect-Err\r\n");
				return -1;
			}
			if(0 > pAppNetSsl->Handshake())
			{
				LOG(LOG_ERROR,"---Net_SSL_Handshake-Err\r\n");
				return -2;
			}
			tNetAddr.sslconnet=1;
		}
		return pAppNetSsl->Send(pBuff,len);
	}
	return send(tNetAddr.pNet->SocketFD, pBuff, len, 0); 
}

//=======================网络接收=========================================================
int  APP_Network_Recv(u8* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull)
{
	int ret,offset=0;
	if(tNetAddr.ENssL==1)
	{
		while(1)
		{
			ret=pAppNetSsl->Recv(pBuff+offset,BuffSize-offset);
			//LOG(LOG_INFO,"ssl_net_Recv ret[%d]\r\n",ret);
			if(ret > 0)
			{
				if(pCheckFull)
				{
					offset += ret;
					ret=(*pCheckFull)(pBuff,offset);
					LOG(LOG_INFO,"pCheckFullret[%d]\r\n",ret);
					if(ret==0) continue;
				}
			}
			if(MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY == pAppNetSsl->GetState(100))
			{
				LOG(LOG_ERROR,"---MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY-SocketRecv-\r\n");
				gNetDisConnect(tNetAddr.pNet);
				tNetAddr.sslconnet=0;
			}
			return ret;
		}
	}
	
	//----------------------------非ssl------------------------------------------------
	if(timeoutMs)
	{//设置接收超时
		struct timeval timeout; 
		timeout.tv_sec = timeoutMs/1000;
		timeout.tv_usec = (timeoutMs%1000)*1000;
		ret=setsockopt(tNetAddr.pNet->SocketFD,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout)); 
		if(ret)
		{
			LOG(LOG_INFO,"setsockopt = %d,[%d]\r\n",ret,errno);
		}
	}
	while(1)
	{
		ret = recv(tNetAddr.pNet->SocketFD, pBuff+offset, BuffSize-offset, 0);
		if(ret >0)
		{
			offset += ret;
			if(pCheckFull)
			{
				ret =pCheckFull(pBuff,offset);
				if(ret > 0) return ret;
				OsSleep(50);
				continue;
			}
			return offset;
		}
		else if(ret < 0)
		{
			LOG(LOG_INFO,"recv = %d,%d,[%d]\r\n",ret,offset,errno);
			if(ret == -1 && (errno == EAGAIN||errno == EWOULDBLOCK||errno == EINTR)) //这几种错误码，认为连接是正常的，继续接收
			{
				continue;//继续接收数据
			}
			break;//跳出接收循环
		}
	}
	return ret;
}

int APP_Network_Disconnect(int timeOutMs)
{
/*
	if(tNetAddr.ENssL==1)
	{
		if(tNetAddr.sslconnet==0)
			return 0;
	}
	*/
	gNetDisConnect(tNetAddr.pNet);
	return 0;
}

//=====bitflag=0,不接收按键处理，bit0=1连接时受理按键，bit1=1接收时受理按键======
void APP_Network_KeyAccept(u32 bitflag)
{
	tNetAddr.AcceptKey=bitflag;
}

//==============获得本地IP地址====================
int APP_NetAddrGet(char *pszIp)
{
	return -5;
}


int APP_GetNetMsg(int type,char *pOut,int outSize)
{
	return -5;
}





