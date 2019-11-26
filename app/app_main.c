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
//#include <fcntl.h>
#include <sys/wait.h>
#include<sys/stat.h>

#include "types_def.h"
#include "app_main.h"

#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>
#include <sys/shm.h>  





int main(int argc, char* argv[]) {
	int ret;
	int shmid;
	APP_SDK *pSDK;
	
//	for(i=0;i<argc;i++)
//		printf("app main argv[%s] \r\n",argv[i]);

	printf("main22222 argv[0]= [%s]\r\n",argv[0]);
	sleep(2);
	
	shmid=shmget(0xA019,sizeof(APP_SDK),0666);  
	if(shmid == -1)
	{
		printf("shmget Err\r\n");
		return -1;
	}
	pSDK=(APP_SDK *)shmat(shmid,NULL,0); 
	printf("shared shmat[%c%c,%u]\r\n",pSDK->Mask[0],pSDK->Mask[1],pSDK->Mask[3]);
	pSDK->Mask[3]++ ;
	/*
	char *pHardMsg[]={
	"FB=/dev/fb0",
	"INPUT=/dev/input/event2",
	"ROTATE=0",
//	"TSDEV=",
	"STATUSBAR=24",
	};
	pSDK->ui->open(sizeof(pHardMsg)/sizeof(pHardMsg[0]) ,pHardMsg);
	if(pSDK->ui->RootCanvas() == 0)
	{
		pSDK->font->DisplaySysString(0,0,12,"0 yz131234&&*()_+~!@#$%^&*");
		pSDK->font->DisplaySysString(0,12,16,"0 yz131234&&*()_+~!@#$%^&*");
		pSDK->font->DisplaySysString(0,12+16,24,"0 yz131234&&*()_+~!@#$%^&*");
		sleep(10);
	}
	pSDK->ui->close();

	*/
	ret=shmdt(pSDK);
	printf("shared shmdt[%d]/r/n",ret);
	//------------------------------------------------------------
	return 0;
}








