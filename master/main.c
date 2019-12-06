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

#include "comm_type.h"

#include "xui_comm.h"
#include "app_show.h"


//#include "mbedtls_sdk.h"


#include "main.h"

#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>
//#include <sys/shm.h>  
//#include <sys/ipc.h>
#include "language.h"
#include "sys_sdk.h"



void API_Trace(char* pMsg,...)
{
	va_list arg;
	va_start(arg, pMsg);
	vprintf(pMsg,arg);	//ret=
	va_end(arg);
}

void APP_Trace_Hex(char* msg,void* pBuff,int Len)
{
	int i;
	printf("%s[%d]:",msg,Len);
	for(i=0;i<Len;i++)
	{
		printf("%02X ",((u8*)pBuff)[i]);
	}
	printf("\r\n");
}


//================================================================================================



/*
#include <pthread.h>
static pthread_t ntid;
static void *thread_fn(void *arg)
{
	printf("This is child thread\n");
	return ((void *)0);
}
int main()
{
	printf("This is main thread\n");
	if(pthread_create(&ntid,NULL,thread_fn,NULL) != 0)
		printf("can't create thread\n");
	sleep(5);
	return 0;
}
*/


//#include <unistd.h>
 
/* 
void *PrintHello(void *args)
{
    return NULL;
}
int InitProcessPool(int noclose)
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return -1;
	}
	LOG(LOG_INFO,"1->InitProcessPool getpid[%d]fork[%d]\r\n",getpid(),pid);
	if(pid != 0)
		return 1;
	pid=setsid();
	LOG(LOG_INFO,"2->InitProcessPool getpid[%d]setsid[%d]\r\n",getpid(),pid);
	if(pid < 0)
	{
		printf("setsid failed\n");
		return 2;
	}
	//chdir("/");
	if (!noclose)
	{
		int fd;
		fd = open ("/dev/null", O_RDWR, 0);
		if (fd != -1)
		{
			dup2 (fd, STDIN_FILENO);
			dup2 (fd, STDOUT_FILENO);
			dup2 (fd, STDERR_FILENO);
			if (fd > 2)
				close(fd);
		}
	}
	umask(0);	//子进程权限

	while(1) 
	{//---守护进程-------
		pid=fork();
		if (pid < 0)
		{
			perror("fork");
			return -2;
		}
		if (pid != 0)
		{ 
			pid_t _pid_t = wait(&pid); //---等待孙进程结束------
			printf("------reRunAPP-[%d,%d]---------\n",_pid_t,pid);
		} 
		else break; //孙进程，跳出外面执行
	} 
	umask(0); //孙进程权限
	return 0;
}


*/


int test_Printf(char *pTitle)
{
	printf("->test_Printf[%s]\r\n",pTitle);
	return 0;
}




typedef struct	
{
	char Mask[4]; 	// "API"
	int (*test)(char*);	//测试函数
	const API_UI_Def *ui;
	const API_FONT_Def *font;
	const API_Even_Def *event;
}API_SDK;


const API_SDK SdkApi={
	{'A','P','I',3},
	test_Printf,
	&ApiUI,
	&ApiFont,
	&ApiEven,
};

/*
char **environ; 
int execl (const char *path, const char *arg0, ..., (char*)0);
int execlp(const char *file, const char *arg0, ..., (char*)0);
int execle(const char *path, const char *arg0, ..., (char*)0, char *const envp[]); 
int execv (const char *path, char *const argv[]);
int execvp(cosnt char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
*/

int APP_main(int argc, char* argv[]) {
//	int ret;
	
	char *pHardMsg[]={
	"FB=/dev/fb0",
	"INPUT=/dev/input/event2",
	"ROTATE=270",
//	"TSDEV=",
	"STATUSBAR=24",
	};

	XuiWindow* pWindow,*pStaWindow;
//	OsLogSetTag("logo.txt");	
	XuiOpen(sizeof(pHardMsg)/sizeof(pHardMsg[0]) ,pHardMsg);
	if((pWindow=XuiRootCanvas()) != NULL)
	{
		pStaWindow=XuiStatusbarCanvas();
		UI_DisplaySysEn(pStaWindow,0,0,TEXT_12,"0 yz131234&&*()");
		UI_DisplaySysEn(pStaWindow,15*6,8,TEXT_16,"_+~!@#$%^&*");
		//UI_DisplaySysEn(pStaWindow,0,TEXT_12+TEXT_16,TEXT_24,"0 yz131234&&*()_+~!@#$%^&*");
		UI_Push(pStaWindow,NULL);
		
		ApiEven.Init(0,0);
		
		ApiEven.LoadThread(NULL);
		ApiFont.InitFontLib("ks.res");
		
		API_InitSysLanguage(1);
		API_GUI_LoadWindow(pWindow);

		APP_FactoryMeun("测试应用");
		//APP_MasterMeun("终端管理");//
		APP_ShowProsseMenu();

		ApiFont.DeInitFontLib();
		ApiEven.KillThread(NULL);
		ApiUI.DestroyWindow(pWindow);
		ApiEven.DeInit();
	}
	XuiClose();

	LOG(LOG_INFO,"->Main End\r\n");
	OsExit(0);
	//------------------------------------------------------------
	return 0;
}








