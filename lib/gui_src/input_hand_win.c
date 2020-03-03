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

#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <linux/input.h>
//#include "input_port_arm.h"
#include "input_hand.h"
#include "EvenMsg.h"
#include "xui_ui.h"
#include "sdk/sys_sdk.h"

static int event_keyFb=0;
DefAbsAnalytical pAbsAnalytical=NULL;

static void handleKey_quit(int signo)
{
	LOG(LOG_INFO,"in qq handle sig %d \n", signo);    
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


static pthread_t key_thread=0;


void Start_HandInput(void)
{
	int rc;
	//gUiDataAll.sInput
	event_keyFb = open("/dev/input/event2",O_RDWR);  // O_RDONLY
	if (event_keyFb == -1)  
	{  
		LOG(LOG_ERROR,"open /dev/input/event2 device error!\n");  
		return;  
	} 
	rc = pthread_create(&key_thread, NULL, get_keyMsg,NULL);
	if (rc)
	{
		LOG(LOG_ERROR,"ERROR; return code is %d\n", rc);
	}
}

void Stop_HandInput(void)
{
	//pthread_join(key_thread, NULL);
	int ret;
	ret=pthread_kill(key_thread, SIGQUIT);
	LOG(LOG_INFO,"Stop Key thread %d\n", ret);
	signal(SIGQUIT,SIG_DFL);
	close(event_keyFb);
}






