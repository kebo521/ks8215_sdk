
#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 

#include "app_net.h" 


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


NET_ADDR_S		tNetAddr={0};









//============================================================================
int APP_Network_Connect(char* pHostIp,u16 port,int ENssl)
{
	struct sockaddr_in stSockAddr;
	int ret;
	int SocketFD;
	SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == SocketFD)
	{
		LOG(LOG_ERROR,"cannot create socket\r\n");
		return -1;
	}
	{
		struct timeval timeout; 
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		//设置发送超时
		ret = setsockopt(SocketFD,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));
		if (-1 == ret)
		{
			LOG(LOG_ERROR,"cannot set SNDTIMEO\r\n");
			return -1;
		}
	}
	{
		int KeepAlive = 1;
		ret = setsockopt(SocketFD, SOL_SOCKET, SO_KEEPALIVE,&KeepAlive, sizeof(KeepAlive));
		if (-1 == ret)
		{
			LOG(LOG_ERROR,"cannot setkeepalive\r\n");
			return -1;
		}
	}
	
	memset(&stSockAddr, 0, sizeof(stSockAddr));
	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(port);

	if(pHostIp[0]<'0' && pHostIp[0] >'9')
	{
		struct hostent *hptr;
		/* 调用gethostbyname()。结果存在hptr结构中 */
		if((hptr = gethostbyname(pHostIp)) == NULL)
		{
			LOG(LOG_ERROR," gethostbyname error for host:%s\n", pHostIp);
			return -103;
		}

		/* 将主机的规范名打出来 */
    	LOG(LOG_INFO,"official hostname:%s\n", hptr->h_name);


		ret = inet_pton(hptr->h_addrtype,hptr->h_addr, &stSockAddr.sin_addr);
		if (0 > ret)
		{
			LOG(LOG_ERROR,"error: first parameter is not a valid address family\r\n");
			close(SocketFD);
			return -104;
		}
		else if (0 == ret)
		{
			LOG(LOG_ERROR,"char string (second parameter does not contain validipaddress)\r\n");
			close(SocketFD);
			return -105;
		}

		/* 主机可能有多个别名，将所有别名分别打出来 
		    for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		        printf(" alias:%s\n", *pptr);*/
		/* 根据地址类型，将地址打出来 
	    switch(hptr->h_addrtype)
	    {
			case AF_INET:
			case AF_INET6:
				pptr = hptr->h_addr_list;
				// 将刚才得到的所有地址都打出来。其中调用了inet_ntop()函数
				for(; *pptr!=NULL; pptr++)
				printf(" address:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				printf(" first address: %s\n", inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
			       break;
			default:
				printf("unknown address type\n");
		        break;
	    }
   		*/
	}
	else
	{
		ret = inet_pton(stSockAddr.sin_family,pHostIp, &stSockAddr.sin_addr);
		if (0 > ret)
		{
			LOG(LOG_ERROR,"error: first parameter is not a valid address family\r\n");
			close(SocketFD);
			return -106;
		}
		else if (0 == ret)
		{
			LOG(LOG_ERROR,"char string (second parameter does not contain validipaddress)\r\n");
			close(SocketFD);
			return -107;
		}
	}

	if (-1 == connect(SocketFD,(struct sockaddr *)&stSockAddr,sizeof(stSockAddr)))
	{
		LOG(LOG_ERROR,"connect[%X][%d] failed\r\n",stSockAddr.sin_addr,stSockAddr.sin_port);
		close(SocketFD);
		return -1;
	}
	
	tNetAddr.net[tNetAddr.NetIndex].SocketFD = SocketFD;
	tNetAddr.net[tNetAddr.NetIndex].port = port;
	strcpy(tNetAddr.net[tNetAddr.NetIndex].sHost,pHostIp);
	tNetAddr.pNet = &tNetAddr.net[tNetAddr.NetIndex];
	
	return 0;
}

//=======================网络发送=========================================================
int  APP_Network_Send(char* pBuff,int len)
{
	return send(tNetAddr.pNet->SocketFD, pBuff, len, 0); 
}

//=======================网络接收=========================================================
int  APP_Network_Recv(char* pBuff,int BuffSize,int timeoutMs,CHECK_DATA_FULL pCheckFull)
{
	if(timeoutMs)
	{//设置接收超时
		struct timeval timeout; 
		timeout.tv_sec = timeoutMs/1000;
		timeout.tv_usec = (timeoutMs%1000)*1000;
		setsockopt(tNetAddr.pNet->SocketFD,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout)); 
	}

	{
		int ret,offset=0;
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
				LOG(LOG_INFO,"recv = %d,[%d,%d,%d]\r\n",ret,EAGAIN,EWOULDBLOCK,EINTR);
				if(ret == EAGAIN||ret == EWOULDBLOCK||ret == EINTR) //这几种错误码，认为连接是正常的，继续接收
				{
					continue;//继续接收数据
				}
				break;//跳出接收循环
			}
		}
	}
	return -3;
}

int APP_Network_Disconnect(int timeOutMs)
{
	/* 执行读写操作*/
	shutdown(tNetAddr.pNet->SocketFD, SHUT_RDWR);
	close(tNetAddr.pNet->SocketFD);
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





