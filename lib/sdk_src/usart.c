
//´®¿ÚÏà¹ØµÄÍ·ÎÄ¼ş    
#include<stdio.h>      /*±ê×¼ÊäÈëÊä³ö¶¨Òå*/    
#include<stdlib.h>     /*±ê×¼º¯Êı¿â¶¨Òå*/    
#include<unistd.h>     /*Unix ±ê×¼º¯Êı¶¨Òå*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*ÎÄ¼ş¿ØÖÆ¶¨Òå*/    
#include<termios.h>    /*PPSIX ÖÕ¶Ë¿ØÖÆ¶¨Òå*/    
#include<errno.h>      /*´íÎóºÅ¶¨Òå*/    
#include<string.h>              
#include "comm_type.h"
#include "sys_sdk.h"
#include <termios.h>

/*******************************************************************  
*Ãû³Æ£º             uart_open  
*¹¦ÄÜ£º             ´ò¿ª´®¿Ú²¢·µ»Ø´®¿ÚÉè±¸ÎÄ¼şÃèÊö  
*Èë¿Ú²ÎÊı£º         port    ´®¿ÚºÅ(ttyS0,ttyS1,ttyS2)  *³ö¿Ú²ÎÊı£ºÕıÈ··µ»ØÎª1£¬´íÎó·µ»ØÎª0  
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
    //»Ö¸´´®¿ÚÎª×èÈû×´Ì¬    
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
  //²âÊÔÊÇ·ñÎªÖÕ¶ËÉè±¸     
    if(0 == isatty(STDIN_FILENO))    
    {    
       LOG(LOG_ERROR,"standard input is not a terminal device\n");    
        return -3;    
    }    
	OsSleep(20);
	//Èç¹û·¢ÉúÊı¾İÒç³ö£¬½ÓÊÕÊı¾İ£¬µ«ÊÇ²»ÔÙ¶ÁÈ¡ Ë¢ĞÂÊÕµ½µÄÊı¾İµ«ÊÇ²»¶Á    
	tcflush(fd, TCIFLUSH);    //Çå¿ÕÊäÈë»º´æ
	tcflush(fd, TCOFLUSH);    //Çå¿ÕÊä³ö»º´æ
	tcflush(fd, TCIOFLUSH);   //Çå¿ÕÊäÈëÊä³ö»º´æ
    //printf("fd->open=%d\n",fd);    
    return fd;    
}    

/*******************************************************************  
*Ãû³Æ£º             uart_close  
*¹¦ÄÜ£º             ¹Ø±Õ´®¿Ú²¢·µ»Ø´®¿ÚÉè±¸ÎÄ¼şÃèÊö  
*Èë¿Ú²ÎÊı£º         fd          ÎÄ¼şÃèÊö·û                       
*******************************************************************/  
void uart_close(int fd)    
{    
    close(fd);    
}    

/*******************************************************************  
*Ãû³Æ£º			uart_set  
*¹¦ÄÜ£º			ÉèÖÃ´®¿ÚÊı¾İÎ»£¬Í£Ö¹Î»ºÍĞ§ÑéÎ»  
*Èë¿Ú²ÎÊı£º		fd		  ´®¿ÚÎÄ¼şÃèÊö·û*		
				speed		´®¿ÚËÙ¶È 	
				flow_ctrl   Êı¾İÁ÷¿ØÖÆ  
				databits    Êı¾İÎ»   È¡ÖµÎª 7 »òÕß8	
				stopbits	Í£Ö¹Î»	È¡ÖµÎª 1 »òÕß2	
				parity		Ğ§ÑéÀàĞÍ È¡ÖµÎªN,E,O,,S  
*³ö¿Ú²ÎÊı£ºÕıÈ··µ»ØÎª1£¬´íÎó·µ»ØÎª0  
*******************************************************************/	 
int uart_set(int fd,int speed,u8 flow_ctrl,u8 databits,u8 stopbits,u8 parity)    
{    
       
    int   i;    
    int   speed_arr[] = {B115200, B19200, B9600, B4800, B2400, B1200, B300};    
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};    
             
    struct termios options; 
   /*  tcgetattr(fd,&options)µÃµ½ÓëfdÖ¸Ïò¶ÔÏóµÄÏà¹Ø²ÎÊı£¬²¢½«ËüÃÇ±£´æÓÚoptions,¸Ãº¯Êı»¹¿ÉÒÔ²âÊÔÅäÖÃÊÇ·ñÕıÈ·£¬        
   ¸Ã´®¿ÚÊÇ·ñ¿ÉÓÃµÈ¡£Èôµ÷ÓÃ³É¹¦£¬º¯Êı·µ»ØÖµÎª0£¬Èôµ÷ÓÃÊ§°Ü£¬º¯Êı·µ»ØÖµÎª1.  */ 
    if( tcgetattr( fd,&options)  !=  0)    
    {    
       LOG(LOG_ERROR,"Err SetupSerial 1");        
        return -1;     
    }    
      
   //ÉèÖÃ´®¿ÚÊäÈë²¨ÌØÂÊºÍÊä³ö²¨ÌØÂÊ  
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)    
    {    
        if  (speed == name_arr[i])    
        {                 
            cfsetispeed(&options, speed_arr[i]);     
            cfsetospeed(&options, speed_arr[i]);   
        }    
    }         
    //options.c_cflag |= (CLOCAL | CREAD);
    //ĞŞ¸Ä¿ØÖÆÄ£Ê½£¬±£Ö¤³ÌĞò²»»áÕ¼ÓÃ´®¿Ú   
    options.c_cflag |= CLOCAL;    
    //ĞŞ¸Ä¿ØÖÆÄ£Ê½£¬Ê¹µÃÄÜ¹»´Ó´®¿ÚÖĞ¶ÁÈ¡ÊäÈëÊı¾İ    
    options.c_cflag |= CREAD;    
      
    //ÉèÖÃÊı¾İÁ÷¿ØÖÆ    
    switch(flow_ctrl)    
    {    
        case 0 ://²»Ê¹ÓÃÁ÷¿ØÖÆ    
              options.c_cflag &= ~CRTSCTS;    
              break;       
        case 1 ://Ê¹ÓÃÓ²¼şÁ÷¿ØÖÆ       
              options.c_cflag |= CRTSCTS;    
              break;    
        case 2 ://Ê¹ÓÃÈí¼şÁ÷¿ØÖÆ 
              options.c_cflag |= IXON | IXOFF | IXANY;    
              break;    
    }    
   //ÉèÖÃÊı¾İÎ»        
   //ÆÁ±ÎÆäËû±êÖ¾Î»   
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
   //ÉèÖÃĞ£ÑéÎ» 
   
    switch (parity&(~0x20))    // &(~0x20) ¹ıÂË´óĞ¡Ğ´
    {      
        case 'N': //æ— å¥‡å¶æ ¡éªŒä½ã€‚    
                 options.c_cflag &= ~PARENB;     
                 options.c_iflag &= ~INPCK;
                 break;     
        case 'O'://è®¾ç½®ä¸ºå¥‡æ ¡éªŒ        
                 options.c_cflag |= (PARODD | PARENB);     
                 options.c_iflag |= INPCK;                 
                 break;     
        case 'E'://è®¾ç½®ä¸ºå¶æ ¡éªŒ      
                 options.c_cflag |= PARENB;           
                 options.c_cflag &= ~PARODD;           
                 options.c_iflag |= INPCK;          
                 break;    
        case 'S': //è®¾ç½®ä¸ºç©ºæ ¼     
                 options.c_cflag &= ~PARENB;    
                 options.c_cflag &= ~CSTOPB;    
                 break;     
        default:      
                 LOG(LOG_ERROR,"Unsupported parity\n");        
                 return -3;     
    }     
	// ÉèÖÃÍ£Ö¹Î»     
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
       
    //ĞŞ¸ÄÊä³öÄ£Ê½£¬Ô­Ê¼Êı¾İÊä³ö  
    options.c_oflag &= ~OPOST;    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);    
    // ÆÁ±Î 0x0d   0x11  0x13 ÕâĞ©ÌØÊâ×Ö·û ½â¾öÕâĞ©ÌØÊâ×Ö·ûÊÕ²»µ½µÄÎÊÌâ
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	//ÉèÖÃµÈ´ıÊ±¼äºÍ×îĞ¡½ÓÊÕ×Ö·û  
	options.c_cc[VTIME] = 0; /* ¶ÁÈ¡Ò»¸ö×Ö·ûµÈ´ı1*(1/10)s */          
	options.c_cc[VMIN] = 0; /* ¶ÁÈ¡×Ö·ûµÄ×îÉÙ¸öÊıÎª1 */    
   //¼¤»îÅäÖÃ (½«ĞŞ¸ÄºóµÄtermiosÊı¾İÉèÖÃµ½´®¿ÚÖĞ£©    
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
* Ãû³Æ£º		uart_recv  
* ¹¦ÄÜ£º		½ÓÊÕ´®¿ÚÊı¾İ  
* Èë¿Ú²ÎÊı£º	fd         ÎÄ¼şÃèÊö·û      
				rcv_buf    ½ÓÊÕ´®¿ÚÖĞÊı¾İ´æÈërcv_buf»º³åÇøÖĞ                 
				data_len   Ò»Ö¡Êı¾İµÄ³¤¶È  
* ³ö¿Ú²ÎÊı£º    ÕıÈ··µ»ØÎª½ÓÊÕ³¤¶È£¬´íÎó·µ»ØÎª-1  
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
		//Ê¹ÓÃselectÊµÏÖ´®¿ÚµÄ¶àÂ·Í¨ĞÅ	
		time.tv_sec = timeoutMs/1000; 
		time.tv_usec = (timeoutMs%1000)*1000;  
		while(1)
		{
			fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
			if(fs_sel > 0) break;
			if(fs_sel == 0)
			{
				LOG(LOG_ERROR,"uart select timeout\r\n");
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
			tcflush(fd,TCIFLUSH); //Èç¹û½ÓÊÕÊ§°Ü Ë¢ĞÂ»º³å ¼ÌĞø½ÓÊÕ 
			return ret;
		}
		offset = ret;
		while(offset < data_len)
		{
			if(((int)OsGetTickCount()-tagTimeMs)>=0)
			{
				LOG(LOG_ERROR,"uart recvt timeOut[%d][%d]\r\n",(int)OsGetTickCount(),tagTimeMs);
				break;
			}
			usleep((data_len-offset)*100);
			ret = read(fd,rcv_buf+offset,data_len-offset);
			if(ret < 0)
			{
				LOG(LOG_ERROR,"uart offset[%d] read=%d Err\r\n",offset,ret);
				tcflush(fd,TCIFLUSH); //Èç¹û½ÓÊÕÊ§°Ü Ë¢ĞÂ»º³å ¼ÌĞø½ÓÊÕ 
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
		tcflush(fd,TCIFLUSH); //Èç¹û½ÓÊÕÊ§°Ü Ë¢ĞÂ»º³å ¼ÌĞø½ÓÊÕ 
	}
	return ret;
}    
/********************************************************************  
* Ãû³Æ£º            uart_send  
* ¹¦ÄÜ£º            ·¢ËÍÊı¾İ  
* Èë¿Ú²ÎÊı£º 		fd           ÎÄ¼şÃèÊö·û      *                   
					send_buf     ´æ·Å´®¿Ú·¢ËÍÊı¾İ  *                   
					data_len     Ò»Ö¡Êı¾İµÄ¸öÊı  * 
* ³ö¿Ú²ÎÊı£º		ÕıÈ··µ»ØÎª1£¬´íÎó·µ»ØÎª0  
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
			usleep(ret*100);	//µÈ´ıCPU´¦Àí
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
	//Ê¹ÓÃselectÊµÏÖ´®¿ÚµÄ¶àÂ·Í¨ĞÅ	
	fs_sel = select(fd+1,NULL,&fs_write,NULL,&time);
	if(fs_sel)
	{
		if(FD_ISSET(fd,&fs_write)) //²âÊÔÎÄ¼şÊÇ·ñ¿ÉĞ´  
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
