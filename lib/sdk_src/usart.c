
//������ص�ͷ�ļ�    
#include<stdio.h>      /*��׼�����������*/    
#include<stdlib.h>     /*��׼�����ⶨ��*/    
#include<unistd.h>     /*Unix ��׼��������*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*�ļ����ƶ���*/    
#include<termios.h>    /*PPSIX �ն˿��ƶ���*/    
#include<errno.h>      /*����Ŷ���*/    
#include<string.h>              
#include "comm_type.h"
#include "sys_sdk.h"

/*******************************************************************  
*���ƣ�             uart_open  
*���ܣ�             �򿪴��ڲ����ش����豸�ļ�����  
*��ڲ�����         port    ���ں�(ttyS0,ttyS1,ttyS2)  *���ڲ�������ȷ����Ϊ1�����󷵻�Ϊ0  
*******************************************************************/    
int uart_open(char* port)
{
	int fd;
	printf("%s\n",port);
    fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);    
    if (fd<0)    
    {    
        perror("Can't Open Serial Port");    
        return	-1;    
    }    
    //�ָ�����Ϊ����״̬    
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
  //�����Ƿ�Ϊ�ն��豸     
    if(0 == isatty(STDIN_FILENO))    
    {    
        printf("standard input is not a terminal device\n");    
        return -3;    
    }    
	OsSleep(20);
	//�����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���    
	tcflush(fd, TCIFLUSH);    //������뻺��
	tcflush(fd, TCOFLUSH);    //����������
	tcflush(fd, TCIOFLUSH);   //��������������
    //printf("fd->open=%d\n",fd);    
    return fd;    
}    

/*******************************************************************  
*���ƣ�             uart_close  
*���ܣ�             �رմ��ڲ����ش����豸�ļ�����  
*��ڲ�����         fd          �ļ�������                       
*******************************************************************/  
void uart_close(int fd)    
{    
    close(fd);    
}    

/*******************************************************************  
*���ƣ�			uart_set  
*���ܣ�			���ô�������λ��ֹͣλ��Ч��λ  
*��ڲ�����		fd		  �����ļ�������*		
				speed		�����ٶ� 	
				flow_ctrl   ����������  
				databits    ����λ   ȡֵΪ 7 ����8	
				stopbits	ֹͣλ	ȡֵΪ 1 ����2	
				parity		Ч������ ȡֵΪN,E,O,,S  
*���ڲ�������ȷ����Ϊ1�����󷵻�Ϊ0  
*******************************************************************/	 
int uart_set(int fd,int speed,u8 flow_ctrl,u8 databits,u8 stopbits,u8 parity)    
{    
       
    int   i;    
    int   speed_arr[] = {B115200, B19200, B9600, B4800, B2400, B1200, B300};    
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};    
             
    struct termios options; 
   /*  tcgetattr(fd,&options)�õ���fdָ��������ز������������Ǳ�����options,�ú��������Բ��������Ƿ���ȷ��        
   �ô����Ƿ���õȡ������óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1.  */ 
    if( tcgetattr( fd,&options)  !=  0)    
    {    
        perror("SetupSerial 1");        
        return -1;     
    }    
      
   //���ô������벨���ʺ����������  
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)    
    {    
        if  (speed == name_arr[i])    
        {                 
            cfsetispeed(&options, speed_arr[i]);     
            cfsetospeed(&options, speed_arr[i]);   
        }    
    }         
    //options.c_cflag |= (CLOCAL | CREAD);
    //�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���   
    options.c_cflag |= CLOCAL;    
    //�޸Ŀ���ģʽ��ʹ���ܹ��Ӵ����ж�ȡ��������    
    options.c_cflag |= CREAD;    
      
    //��������������    
    switch(flow_ctrl)    
    {    
        case 0 ://��ʹ��������    
              options.c_cflag &= ~CRTSCTS;    
              break;       
        case 1 ://ʹ��Ӳ��������       
              options.c_cflag |= CRTSCTS;    
              break;    
        case 2 ://ʹ������������ 
              options.c_cflag |= IXON | IXOFF | IXANY;    
              break;    
    }    
   //��������λ        
   //����������־λ   
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
			fprintf(stderr,"Unsupported data size\n");    
			return -2;     
	}    
   //����У��λ 
   
    switch (parity&(~0x20))    // &(~0x20) ���˴�Сд
    {      
        case 'N': //无奇偶校验位。    
                 options.c_cflag &= ~PARENB;     
                 options.c_iflag &= ~INPCK;
                 break;     
        case 'O'://设置为奇校验        
                 options.c_cflag |= (PARODD | PARENB);     
                 options.c_iflag |= INPCK;                 
                 break;     
        case 'E'://设置为偶校验      
                 options.c_cflag |= PARENB;           
                 options.c_cflag &= ~PARODD;           
                 options.c_iflag |= INPCK;          
                 break;    
        case 'S': //设置为空格     
                 options.c_cflag &= ~PARENB;    
                 options.c_cflag &= ~CSTOPB;    
                 break;     
        default:      
                 fprintf(stderr,"Unsupported parity\n");        
                 return -3;     
    }     
	// ����ֹͣλ     
    switch (stopbits)    
    {      
        case 1:       
                 options.c_cflag &= ~CSTOPB; break;     
        case 2:       
                 options.c_cflag |= CSTOPB; break;    
        default:       
               fprintf(stderr,"Unsupported stop bits\n");     
               return -4;    
    }    
       
    //�޸����ģʽ��ԭʼ�������  
    options.c_oflag &= ~OPOST;    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);    
    // ���� 0x0d   0x11  0x13 ��Щ�����ַ� �����Щ�����ַ��ղ���������
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	//���õȴ�ʱ�����С�����ַ�  
	options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */          
	options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */    
   //�������� (���޸ĺ��termios�������õ������У�    
    if (tcsetattr(fd,TCSANOW,&options) != 0)      
    {    
        perror("com set error!\n");      
        return -5;     
    }    
    return 0;     
}    

//uart_set(fd,115200,0,8,1,'N')  
  
/*******************************************************************  
* ���ƣ�		uart_recv  
* ���ܣ�		���մ�������  
* ��ڲ�����	fd         �ļ�������      
				rcv_buf    ���մ��������ݴ���rcv_buf��������                 
				data_len   һ֡���ݵĳ���  
* ���ڲ�����    ��ȷ����Ϊ���ճ��ȣ����󷵻�Ϊ-1  
*******************************************************************/  
int uart_recv(int fd, void *rcv_buf,int data_len,int timeoutMs)    
{    
	int ret;
	if(timeoutMs)
	{
		int fs_sel;  
		fd_set fs_read;    
		struct timeval time;  
		FD_ZERO(&fs_read);	  
		FD_SET(fd,&fs_read);	
	
		time.tv_sec = timeoutMs/1000;	
		time.tv_usec = timeoutMs*1000;	 
		//ʹ��selectʵ�ִ��ڵĶ�·ͨ��	
		fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
		//FD_CLR(fd,&fs_read);
		printf("fs_sel=%d ",fs_sel);
		if(fs_sel==0) return -1;
	}
	ret = read(fd,rcv_buf,data_len);
	if(ret < 0)
	{
		tcflush(fd,TCIFLUSH); //�������ʧ�� ˢ�»��� �������� 
	}
	return ret;
}    
/********************************************************************  
* ���ƣ�            uart_send  
* ���ܣ�            ��������  
* ��ڲ����� 		fd           �ļ�������      *                   
					send_buf     ��Ŵ��ڷ�������  *                   
					data_len     һ֡���ݵĸ���  * 
* ���ڲ�����		��ȷ����Ϊ1�����󷵻�Ϊ0  
*******************************************************************/    
int uart_send(int fd, void *send_buf,int data_len)    
{    
	LOG(LOG_INFO,"fd[%d]",fd);
	TRACE_HEX("->SendBuf",send_buf,data_len);
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
/*
	int fs_sel;  
	fd_set fs_write;    
	struct timeval time;  
	FD_ZERO(&fs_write);	  
	FD_SET(fd,&fs_write);	

	time.tv_sec = 3;	
	time.tv_usec = 0;	 
	//ʹ��selectʵ�ִ��ڵĶ�·ͨ��	
	fs_sel = select(fd+1,NULL,&fs_write,NULL,&time);
	if(fs_sel)
	{
		if(FD_ISSET(fd,&fs_write)) //�����ļ��Ƿ��д  
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