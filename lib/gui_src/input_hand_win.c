/**
 * File:   fbshow.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  snap framebuffer to png file
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <unistd.h>
//#include <stdarg.h>

#include "comm_type.h"
#include <termios.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <linux/input.h>
//#include "input_port_arm.h"
#include "input_hand.h"
#include "EvenMsg.h"
#include "xui_ui.h"
#include "xui_fb.h"
#include "sdk/sys_sdk.h"

static pthread_t key_thread=0,mice_thread=0;
static int event_keyFb=0,event_mice=0;
DefAbsAnalytical pAbsAnalytical=NULL;

static void handleKey_quit(int signo)
{
	LOG(LOG_INFO,"Key quit sig %d \n", signo);    
	pthread_exit(NULL);
}

static void *get_keyMsg(void *args)  
{  
	unsigned short type,code,varX,varY;
	unsigned short oldCode=0xFFFF,oldX=0xFFFF,oldY=0xFFFF;
	int timeMs,oldTimsMs;
	int i,max;
    int res;
	struct input_event event[8];  
//	keys_fd = open("/dev/input/event2",O_RDWR);  // O_RDONLY
	signal(SIGQUIT,handleKey_quit);
	while(1)  
	{
        res = read(event_keyFb, event, sizeof(event));
		//printf("read[%d]-[%ld]\r\n",res,sizeof(event));
        if(res < (int)sizeof(event[0])) {
            printf("##could not get event[%d]\r\n",res);
            break;
        }
		if(!(tWaitEventMsg.EventControl & (EVENT_ABS|EVENT_KEY|EVENT_UI)))
			continue;
		
		type=0xFFFF;
		timeMs=0;
		max = res/sizeof(event[0]);
		for(i=0;i < max ;i++)
		{
			switch(event[i].type)
			{
				case EV_SYN:
					if(event[i].code == 0)
						timeMs = event[i].time.tv_sec*1000 + event[i].time.tv_usec/1000;
					break;
				case EV_KEY:
					if(i == 1)
					{
						if(event[i].value == 1)
						{
							type = EV_KEY;
							code = event[i].code;
						}
					}
					break;
				case EV_ABS:
					type = EV_ABS;
					switch(event[i].code)
					{
						case ABS_MT_TOUCH_MAJOR: code = event[i].value; break;
						case ABS_MT_POSITION_X: varX = event[i].value; break;
						case ABS_MT_POSITION_Y: varY = event[i].value; break;
					}
					break;
				case EV_MSC:
					break;
			}
		}

		if((type == EV_KEY) && (tWaitEventMsg.EventControl & (EVENT_KEY|EVENT_UI)))
		{
			switch(code)
			{
				case KEY_0: varX=K_0; break;
				case KEY_1: varX=K_1; break;
				case KEY_2: varX=K_2; break;
				case KEY_3: varX=K_3; break;
				case KEY_4: varX=K_4; break;
				case KEY_5: varX=K_5; break;
				case KEY_6: varX=K_6; break;
				case KEY_7: varX=K_7; break;
				case KEY_8: varX=K_8; break;
				case KEY_9: varX=K_9; break;
				case KEY_UP: varX=K_UP; break;
				case KEY_DOWN: varX=K_DOWN; break;
				case KEY_LEFT: varX=K_LEFT; break;
				case KEY_RIGHT: varX=K_RIGHT; break;
				case KEY_BACKSPACE: varX=K_DEL; break;
				case KEY_ESC:
				case KEY_CANCEL: varX=K_CANCEL; break;
				case KEY_ENTER: varX=K_OK; break;
				case KEY_LEFTSHIFT: varX=K_IME; break;
				case KEY_DOT:
				case KEY_NUMERIC_POUND: varX=K_D; break;
				case KEY_F2: varX=K_FUNC; break;
				case KEY_POWER: varX=K_PWR; break;
				default: varX=0xFFFF;
			}
			if(varX != 0xFFFF)
			{
				if(oldCode != code)
				{
					oldTimsMs = timeMs;
					oldCode = code;
					timeMs=0xFFFF;
				}
				else
				{
					timeMs -= oldTimsMs;
					if(timeMs > 0xFFFF) timeMs=0xFFFF;
				}
				FIFO_OperatSetMsg(EVEN_ID_KEY_DOWN,varX,timeMs);
			}
			//printf("----KEY[%x] down[%02X],timeMs[%d]-----\r\n",code,varX,timeMs);
		}
		if((type == EV_ABS) && (tWaitEventMsg.EventControl & EVENT_ABS))
		{
			if(oldX != varX || oldY != varY)
			{
				oldX=varX; oldY=varY;
				printf("---ABS[%d,%d]%d,timeMs[%d]-----\r\n",varX,varY,code,timeMs);
				if(pAbsAnalytical)
				{
					int ret;
					ret= (*pAbsAnalytical)(&varX,&varY);
					if(ret == EVEN_ID_KEY_DOWN)
						FIFO_OperatSetMsg(EVEN_ID_KEY_DOWN,varX,timeMs);
					else if(ret == EVEN_ID_ABS)
						FIFO_OperatSetMsg(EVEN_ID_ABS,varY*0x10000+varX,timeMs);
				}
			}
		}
	}
//	close (keys_fd); 
	LOG(LOG_INFO," -key_end-pthread_exit\n");	
	pthread_exit(NULL);
	return 0;  
}  

#define 	MICE_POINT_NUM 		5
static A_RGB micePushRgb[MICE_POINT_NUM*MICE_POINT_NUM];
static A_RGB micePinRgb[3*3];

void mice_Set_point(int x,int y) 
{
	fb_ui_xor_rect(x-(MICE_POINT_NUM/2),y-(MICE_POINT_NUM/2),MICE_POINT_NUM ,MICE_POINT_NUM ,micePushRgb);
}

void mice_Set_pin(int x,int y) 
{
	fb_ui_xor_rect(x,y+1,3 ,3 ,micePinRgb); 
}



static int mice_x,mice_y,mice_w,mice_h;
static int oldMiceX,oldMiceY;
static int oldPmiceX,oldPmiceY;
static void handleMice_quit(int signo)
{
	LOG(LOG_INFO,"Mice quit sig %d \n", signo);
	if(oldMiceX>0)
	{
		mice_Set_point(oldMiceX,oldMiceY);
		oldMiceX = -1;
	}
	if(oldPmiceX > 0)
	{
		mice_Set_pin(oldPmiceX,oldPmiceY);
		oldPmiceX = -1;
	}
	pthread_exit(NULL);
}

static void *get_miceMsg(void *args)    
{       
	int ret;
	struct timeval time_tv;
	RECTL tMice_UI;
	signed char buf[3];       
	signal(SIGQUIT,handleMice_quit);

	argbset(micePushRgb,RGB_CURR(255,255,255),MICE_POINT_NUM*MICE_POINT_NUM);
	micePushRgb[0]=0;
	micePushRgb[MICE_POINT_NUM-1]=0;
	micePushRgb[MICE_POINT_NUM*(MICE_POINT_NUM-1)]=0;
	micePushRgb[MICE_POINT_NUM*MICE_POINT_NUM -1]=0;

	argbset(micePinRgb,0,3*3);
	micePinRgb[0]=RGB_CURR(0,0xF8,0xF8);
	micePinRgb[3]=RGB_CURR(0,0xF8,0xF8);
	micePinRgb[4]=RGB_CURR(0,0xF8,0xF8);
	micePinRgb[6]=RGB_CURR(0,0xF8,0xF8);
	micePinRgb[7]=RGB_CURR(0,0xF8,0xF8);
	micePinRgb[8]=RGB_CURR(0,0xF8,0xF8);
	oldPmiceX = -1;
	ret = read(event_mice, buf, sizeof(buf));
	//LOG_HEX(LOG_INFO,"mice1",buf,ret);
	ret = read(event_mice, buf, sizeof(buf));
	//LOG_HEX(LOG_INFO,"mice2",buf,ret);

	fb_GetScreenSize(&mice_w,&mice_h,&tMice_UI);
	mice_x = mice_w/2;
	mice_y = mice_h/2;
	ret = read(event_mice, buf, sizeof(buf));
	if(ret >= 3)
	{
		mice_x = buf[1];
		mice_y = buf[2];

		mice_x += 127;
		mice_y += 127; mice_y = 254-mice_y;

		mice_x = (mice_x*mice_w)/255;
		mice_y = (mice_y*mice_h)/255;
		//LOG(LOG_INFO,"mice3[%d,%d]-[%d,%d]\r\n",buf[1],buf[2],mice_x,mice_y);
 	}
	oldMiceX = mice_x;
	oldMiceY = mice_y;
	mice_Set_point(oldMiceX,oldMiceY);
	tMice_UI.width += tMice_UI.left;
	tMice_UI.height += tMice_UI.top;
	ret = read(event_mice, buf, sizeof(buf));
	//LOG_HEX(LOG_INFO,"mice4",buf,ret);

	mice_w -= 1+(MICE_POINT_NUM/2);
	mice_h -= 1+(MICE_POINT_NUM/2);
	while(1) 
	{           
		// 读取鼠标设备中的数据
		ret = read(event_mice, buf,sizeof(buf));
		if(ret < 3) 
		{       
			LOG(LOG_INFO,"mice read ret[%x]!\n" ,ret);
			continue;               
		}   
		mice_x += buf[1];
		mice_y -= buf[2];
		//--------------------纠正越界坐标---------------------------
		if(mice_x < (MICE_POINT_NUM/2))
			mice_x = (MICE_POINT_NUM/2);
		if(mice_x > mice_w)
			mice_x = mice_w;
		if(mice_y < (MICE_POINT_NUM/2))
			mice_y = (MICE_POINT_NUM/2);
		if(mice_y >mice_h)
			mice_y =mice_h;
		//-------------------------------------------------------------
		if(oldMiceX>0)
		{
			mice_Set_point(oldMiceX,oldMiceY);
			oldMiceX = -1;
		}
		if(oldPmiceX > 0)
		{
			mice_Set_pin(oldPmiceX,oldPmiceY);
			oldPmiceX = -1;
		}
		//-------------------------------------------------------------------
		if(mice_x < tMice_UI.left || mice_x >= tMice_UI.width || \
			mice_y < tMice_UI.top || mice_y >= tMice_UI.height)
		{
			if(oldMiceX != mice_x || oldMiceY != mice_y)
			{
				mice_Set_point(mice_x,mice_y);			
				oldMiceX = mice_x;
				oldMiceY = mice_y;
			}
			continue;
		}
		
		if(buf[0]&0x01)	//else if(buf[0]&0x02) //---右击----
		{//---左击----
			if(pAbsAnalytical)
			{
				int ret;
				u16 varX,varY;
				gettimeofday(&time_tv, NULL);
				varX = mice_x;
				varY = mice_y;
				ret= (*pAbsAnalytical)(&varX,&varY);
				if(ret == EVEN_ID_KEY_DOWN)
				{
					FIFO_OperatSetMsg(EVEN_ID_KEY_DOWN,varX,(time_tv.tv_sec*1000 + time_tv.tv_usec/1000));
					oldPmiceX = -1;	//页面会刷新，不需要再恢复被改点。
				}
				else if(ret == EVEN_ID_ABS)
					FIFO_OperatSetMsg(EVEN_ID_ABS,varY*0x10000+varX,(time_tv.tv_sec*1000 + time_tv.tv_usec/1000));					
			}
		}
		else if(oldPmiceX != mice_x || oldPmiceY != mice_y)
		{
			mice_Set_pin(mice_x,mice_y);
			oldPmiceX = mice_x;
			oldPmiceY = mice_y;
		}
		//LOG(LOG_INFO,"Button type = %d, X = %d, Y = %d, Z = %d\n", (buf[0] & 0x07), buf[1], buf[2],   buf[3]);           
	}       
	return 0;   
}




void Start_HandInput(void)
{
	int rc;
	//gUiDataAll.sInput
	event_keyFb = open("/dev/input/event2",O_RDWR);  // O_RDONLY
	if (event_keyFb != -1)  
	{  
		rc = pthread_create(&key_thread, NULL, get_keyMsg,NULL);
		if (rc)
		{
			LOG(LOG_ERROR,"ERROR; return code is %d\n", rc);
		}
	}
	else
	{
		LOG(LOG_ERROR,"open /dev/input/event2 device error!\n");  
	}
	
	// 打开鼠标设备  
	event_mice = open( "/dev/input/mice",O_RDONLY);
	if (event_mice != -1)	
	{  
		//为阻塞状态    
/*
		struct termios tio;
		tio.c_cc[VTIME] = FRAME_MAXSIZE;// timeout in deciseconds for noncanonical read
		tio.c_cc[VMIN] = 3; // minimum number of characters for noncanonical read
		tcsetattr(event_mice, TCSANOW, &tio);
*/
		//fcntl(event_mice,F_SETFL,0);//FNDELAY
		rc = pthread_create(&mice_thread, NULL, get_miceMsg,NULL);
		if (rc)
		{
			LOG(LOG_ERROR,"ERROR; mice return code is %d\n", rc);
		}
	}
	else
	{
		LOG(LOG_ERROR,"open /dev/input/mice device error!\n");	
	}
}

void Stop_HandInput(void)
{
	//pthread_join(key_thread, NULL);
	int ret;
	ret=pthread_kill(key_thread, SIGQUIT);
	LOG(LOG_INFO,"Stop Key thread %d\n", ret);
	close(event_keyFb);

	ret=pthread_kill(mice_thread, SIGQUIT);
	LOG(LOG_INFO,"Stop mice thread %d\n", ret);
	close(event_mice);

	signal(SIGQUIT,SIG_DFL);
}




