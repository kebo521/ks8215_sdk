
//串口相关的头文件    
#include<stdio.h>      /*标准输入输出定义*/    
#include<stdlib.h>     /*标准函数库定义*/    
#include<unistd.h>     /*Unix 标准函数定义*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*文件控制定义*/    
#include<termios.h>    /*PPSIX 终端控制定义*/    
#include<errno.h>      /*错误号定义*/    
#include<string.h>              
#include "comm_type.h"
#include "sys_sdk.h"

/*******************************************************************  
*名称：             uart_open  
*功能：             打开串口并返回串口设备文件描述  
*入口参数：         port    串口号(ttyS0,ttyS1,ttyS2)  *出口参数：正确返回为1，错误返回为0  
*******************************************************************/    
int uart_open(char* port)
{
	int fd;
    fd = open( port, O_RDWR|O_NOCTTY);   //|O_NOCTTY|O_NDELAY
	LOG(LOG_INFO,"uart open[%s][%d]\n",port,fd);	
    if (fd<0)    
    {    
        return	fd;    
    }    
    //恢复串口为阻塞状态    
   // fcntl(fd,F_SETFL,FNDELAY);
	/*
    if(fcntl(fd, F_SETFL, 0) < 0)    
    {    
        printf("fcntl failed!\n");    
        return -2;    
    }         
    else    
    {    
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));    
    }
    */
  //测试是否为终端设备     
    if(0 == isatty(STDIN_FILENO))    
    {    
       LOG(LOG_ERROR,"standard input is not a terminal device\n");    
        return -3;    
    }    
	OsSleep(20);
	//如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读    
	tcflush(fd, TCIFLUSH);    //清空输入缓存
	tcflush(fd, TCOFLUSH);    //清空输出缓存
	tcflush(fd, TCIOFLUSH);   //清空输入输出缓存
    //printf("fd->open=%d\n",fd);    
    return fd;    
}    

/*******************************************************************  
*名称：             uart_close  
*功能：             关闭串口并返回串口设备文件描述  
*入口参数：         fd          文件描述符                       
*******************************************************************/  
void uart_close(int fd)    
{    
    close(fd);    
}    

/*******************************************************************  
*名称：			uart_set  
*功能：			设置串口数据位，停止位和效验位  
*入口参数：		fd		  串口文件描述符*		
				speed		串口速度 	
				flow_ctrl   数据流控制  
				databits    数据位   取值为 7 或者8	
				stopbits	停止位	取值为 1 或者2	
				parity		效验类型 取值为N,E,O,,S  
*出口参数：正确返回为1，错误返回为0  
*******************************************************************/	 
int uart_set(int fd,int speed,u8 flow_ctrl,u8 databits,u8 stopbits,u8 parity)    
{    
       
    int   i;    
    int   speed_arr[] = {B115200, B19200, B9600, B4800, B2400, B1200, B300};    
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};    
             
    struct termios options; 
   /*  tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，        
   该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.  */ 
    if( tcgetattr( fd,&options)  !=  0)    
    {    
       LOG(LOG_ERROR,"Err SetupSerial 1");        
        return -1;     
    }    
      
   //设置串口输入波特率和输出波特率  
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)    
    {    
        if  (speed == name_arr[i])    
        {                 
            cfsetispeed(&options, speed_arr[i]);     
            cfsetospeed(&options, speed_arr[i]);   
        }    
    }         
    //options.c_cflag |= (CLOCAL | CREAD);
    //修改控制模式，保证程序不会占用串口   
    options.c_cflag |= CLOCAL;    
    //修改控制模式，使得能够从串口中读取输入数据    
    options.c_cflag |= CREAD;    
      
    //设置数据流控制    
    switch(flow_ctrl)    
    {    
        case 0 ://不使用流控制    
              options.c_cflag &= ~CRTSCTS;    
              break;       
        case 1 ://使用硬件流控制       
              options.c_cflag |= CRTSCTS;    
              break;    
        case 2 ://使用软件流控制 
              options.c_cflag |= IXON | IXOFF | IXANY;    
              break;    
    }    
   //设置数据位        
   //屏蔽其他标志位   
	options.c_cflag &= ~CSIZE;    
	switch (databits)    
	{      
		case 5:    
			options.c_cflag |= CS5;    
			break;    
		case 6:    
			options.c_cflag |= CS6;    
			break;    
		case 7:        
			options.c_cflag |= CS7;    
			break;    
		case 8:        
			options.c_cflag |= CS8;    
			break;      
		default:       
			LOG(LOG_ERROR,"Unsupported data size\n");    
			return -2;     
	}    
   //设置校验位 
   
    switch (parity&(~0x20))    // &(~0x20) 过滤大小写
    {      
        case 'N': //鏃犲鍋舵牎楠屼綅銆?   
                 options.c_cflag &= ~PARENB;     
                 options.c_iflag &= ~INPCK;
                 break;     
        case 'O'://璁剧疆涓哄鏍￠獙        
                 options.c_cflag |= (PARODD | PARENB);     
                 options.c_iflag |= INPCK;                 
                 break;     
        case 'E'://璁剧疆涓哄伓鏍￠獙      
                 options.c_cflag |= PARENB;           
                 options.c_cflag &= ~PARODD;           
                 options.c_iflag |= INPCK;          
                 break;    
        case 'S': //璁剧疆涓虹┖鏍?    
                 options.c_cflag &= ~PARENB;    
                 options.c_cflag &= ~CSTOPB;    
                 break;     
        default:      
                 LOG(LOG_ERROR,"Unsupported parity\n");        
                 return -3;     
    }     
	// 设置停止位     
    switch (stopbits)    
    {      
        case 1:       
                 options.c_cflag &= ~CSTOPB; break;     
        case 2:       
                 options.c_cflag |= CSTOPB; break;    
        default:       
               LOG(LOG_ERROR,"Unsupported stop bits\n");     
               return -4;    
    }    
       
    //修改输出模式，原始数据输出  
    options.c_oflag &= ~OPOST;    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);    
    // 屏蔽 0x0d   0x11  0x13 这些特殊字符 解决这些特殊字符收不到的问题
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	//设置等待时间和最小接收字符  
	options.c_cc[VTIME] = 0; /* 读取一个字符等待1*(1/10)s */          
	options.c_cc[VMIN] = 0; /* 读取字符的最少个数为1 */    
   //激活配置 (将修改后的termios数据设置到串口中）    
    if (tcsetattr(fd,TCSANOW,&options) != 0)      
    {    
        LOG(LOG_ERROR,"com set error!\n");      
        return -5;     
    } 
	usleep(500*1000);
    return 0;     
}    

extern unsigned long OsGetTickCount(void);
//uart_set(fd,115200,0,8,1,'N')  
/*******************************************************************  
* 名称：		uart_recv  
* 功能：		接收串口数据  
* 入口参数：	fd         文件描述符      
				rcv_buf    接收串口中数据存入rcv_buf缓冲区中                 
				data_len   一帧数据的长度  
* 出口参数：    正确返回为接收长度，错误返回为-1  
*******************************************************************/  
int uart_recv(int fd, void *rcv_buf,int data_len,int timeoutMs)    
{    
	int ret;
	int offset,tagTimeMs;
	if(timeoutMs)
	{
		int fs_sel;
		fd_set fs_read;	 
		struct timeval time; 
		tagTimeMs=timeoutMs+OsGetTickCount();
		FD_ZERO(&fs_read);	  
		FD_SET(fd,&fs_read);
		//使用select实现串口的多路通信	
		time.tv_sec = timeoutMs/1000; 
		time.tv_usec = (timeoutMs%1000)*1000;  
		while(1)
		{
			fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
			if(fs_sel > 0) break;
			if(fs_sel == 0)
			{
				LOG(LOG_ERROR,"uart select timeout[%d]\r\n",timeoutMs);
				return ERR_TIME_OUT;
			}
		}
		if(!FD_ISSET(fd,&fs_read))   
		{	
			LOG(LOG_ERROR,"uart FD_ISSET NULL\r\n");
			return -2;
		}	
		ret = read(fd,rcv_buf,data_len);
		if(ret < 0)
		{
			LOG(LOG_ERROR,"#uart recvt[%d] read=%d [%d]Err\r\n",fd,ret,timeoutMs);
			tcflush(fd,TCIFLUSH); //如果接收失败 刷新缓冲 继续接收 
			return ret;
		}
		offset = ret;
		while(offset < data_len)
		{
			if(((int)OsGetTickCount()-tagTimeMs)>=0)
			{
				LOG(LOG_ERROR,"uart recvt[%d] timeOut[%d]\r\n",offset,timeoutMs);
				break;
			}
			usleep((data_len-offset)*100);
			ret = read(fd,rcv_buf+offset,data_len-offset);
			if(ret < 0)
			{
				LOG(LOG_ERROR,"uart offset[%d] read=%d Err\r\n",offset,ret);
				tcflush(fd,TCIFLUSH); //如果接收失败 刷新缓冲 继续接收 
				return ret;
			}
			offset += ret;
		}
		return offset;
	}
	ret = read(fd,rcv_buf,data_len);
	if(ret < 0)
	{
		LOG(LOG_ERROR,"#uart t0 recvt read=%d[%d] [%d]Err\r\n",ret,data_len,timeoutMs);
		tcflush(fd,TCIFLUSH); //如果接收失败 刷新缓冲 继续接收 
	}
	return ret;
}    
/********************************************************************  
* 名称：            uart_send  
* 功能：            发送数据  
* 入口参数： 		fd           文件描述符      *                   
					send_buf     存放串口发送数据  *                   
					data_len     一帧数据的个数  * 
* 出口参数：		正确返回为1，错误返回为0  
*******************************************************************/    
int uart_send(int fd, void *send_buf,int data_len)    
{    
//	LOG(LOG_INFO,"fd[%d]",fd);
//	TRACE_HEX("->SendBuf",send_buf,data_len);
	int ret,offset=0;
	while(1)
	{
		ret = write(fd,send_buf+offset,data_len-offset);	
		fsync(fd);
		if(ret <= 0)
		{	
			LOG(LOG_ERROR,"uart_send [%d]error!\n",ret);				 
			tcflush(fd,TCOFLUSH);	
			return ret;	
		}
		offset += ret;
		if(offset < data_len)
		{
			usleep(ret*100);	//等待CPU处理
			LOG(LOG_WARN,"**uart_send [%d,%d,%d]warn!\n",ret,offset,data_len);	
			continue;
		}
		break;
	}
	return offset;
/*
	int fs_sel;  
	fd_set fs_write;    
	struct timeval time;  
	FD_ZERO(&fs_write);	  
	FD_SET(fd,&fs_write);	

	time.tv_sec = 3;	
	time.tv_usec = 0;	 
	//使用select实现串口的多路通信	
	fs_sel = select(fd+1,NULL,&fs_write,NULL,&time);
	if(fs_sel)
	{
		if(FD_ISSET(fd,&fs_write)) //测试文件是否可写  
		{
			int len = write(fd,send_buf,data_len);	
			fsync(fd);
			if (len == data_len )	
			{	
				return len;	  
			}		 
			else 	  
			{	
				printf("uart_send [%d]error!\n",len);				 
				tcflush(fd,TCOFLUSH);	
				return -1;	
			}	
		}
		else
		{
			perror("FD_ISSET Write error!\n");		
			return -2;
		}
	}
	printf("select fs_sel[%d]error!\n",fs_sel);	
	return -4;
	*/
}
