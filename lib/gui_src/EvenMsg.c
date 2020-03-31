//#include "communal.h"

//#include<stdarg.h>
#include <signal.h>
#include <sys/time.h>
#include<pthread.h>
#include<semaphore.h>

#include "comm_type.h"
#include "EvenMsg.h"
#include "input_hand.h"
#include "sdk/sys_sdk.h"

typedef struct
{
	unsigned int		Id;
	unsigned int		Par;
	int 		currtimeMs;
}CMessageItem;
#define 	MESSAGE_MAX	256

typedef struct _CMessageTable
{
	int					WriteID,ReadID;
	CMessageItem		fifo[MESSAGE_MAX];
	pthread_t			threadID;
	fPushTaskMsg		pFunMessageTask;
	//------------------------------------
	struct _CMessageTable	*pPrevious;
}CMessageTable;
static CMessageTable *pMessageTable=NULL;

//==================================================================
static sem_t g_sem_event;

void FIFO_OperatInit(int pshared, unsigned int value)
{
	sem_init(&g_sem_event,pshared,value);
}

void FIFO_OperatDeInit(void)
{
	//sem_init(&g_sem_event,pshared,value);
}


void FIFO_OperatSetMsg(u32 MessageID,u32 Message,int currtimeMs)
{
	if(pMessageTable)
	{//----------FIFO------------------------
		register CMessageItem *pFiFo = &pMessageTable->fifo[(MESSAGE_MAX-1)&(pMessageTable->WriteID++)];
		pFiFo->Id= MessageID;
		pFiFo->Par= Message;
		pFiFo->currtimeMs= currtimeMs;
		sem_post(&g_sem_event);
		//-----检查消息堆已满,覆盖最第一条倒入的消息---------
		//if(!((pMessageTable->WriteID ^ pMessageTable->ReadID)&0x03))
		//	pMessageTable->ReadID++;
		//LOG(LOG_INFO,"FIFO_OperatSetMsg[%X] WriteID[%d]MessageID[%d]Message[%d]\r\n",pMessageTable->threadID,WriteID, MessageID, Message);
	}
}
//阻塞式接收消息接口
int  FIFO_OperatGetMsg(u32 *pMessageID,u32 *pMessage,int *pTimeMs)
{
	if(pMessageTable)
	{
	Adder_ReOperatGetMsgRead:
		if(pMessageTable->ReadID == pMessageTable->WriteID)
		{//-------没消息读消息----------
			sem_wait(&g_sem_event);
		}
		//--------有消息取消息--------------------
		if(pMessageTable->ReadID ^ pMessageTable->WriteID)
		{//----------FIFO------------------------
			register CMessageItem *pFiFo = &pMessageTable->fifo[(MESSAGE_MAX-1)&(pMessageTable->ReadID++)];
			//----------极限任务-----------
			if(pFiFo->Id == EVEN_ID_MSG_TASK)
			{
				if(pMessageTable->pFunMessageTask)
					(*pMessageTable->pFunMessageTask)(pFiFo->Par,pFiFo->currtimeMs);
				goto Adder_ReOperatGetMsgRead;
			}					
			if(pMessageID)
				*pMessageID=pFiFo->Id;
			if(pMessage)
				*pMessage = pFiFo->Par;
			if(pTimeMs)
				*pTimeMs = pFiFo->currtimeMs;
			//LOG(LOG_INFO,"FIFO_OperatGetMsg[%X]ReadID[%d]MessageID[%d]Message[%d]\r\n",pMessageTable->threadID,ReadID, *pMessageID, *pMessage);
			return 1;
		}
	}
	return 0;
}

//=====非阻塞式接收消息接口=========================
int  FIFO_OperatPeekGetMsg(u32 *pMessageID,u32 *pMessage,int *pTimeMs)
{
	if(pMessageTable)
	{
	Adder_ReOperatPeekGetMsg:
		if(pMessageTable->ReadID ^ pMessageTable->WriteID)
		{//----------FIFO----有消息---------------------
			register CMessageItem *pFiFo = &pMessageTable->fifo[(MESSAGE_MAX-1)&(pMessageTable->ReadID++)];
			//----------极限任务-----------
			if(pFiFo->Id == EVEN_ID_MSG_TASK)
			{
				if(pMessageTable->pFunMessageTask)
					(*pMessageTable->pFunMessageTask)(pFiFo->Par,pFiFo->currtimeMs);
				goto Adder_ReOperatPeekGetMsg;
			}					
			if(pMessageID)
				*pMessageID=pFiFo->Id;
			if(pMessage)
				*pMessage = pFiFo->Par;
			if(pTimeMs)
				*pTimeMs = pFiFo->currtimeMs;
			return 1;
		}
		/*
		else
		{//-------清空消息队列----------
			MERCURY_MESSAGE_S* msg;
			MercuryPeekMessage(&msg,GetCurrentThread());
		}	*/
	}
	return 0;
}

int	FIFO_OperatGetNum(void)
{
	return pMessageTable->WriteID - pMessageTable->ReadID;
}



void APP_PushMessageTask(fPushTaskMsg pFun,u32 par)
{
	if(pMessageTable)
	{
		pMessageTable->pFunMessageTask=pFun;
		FIFO_OperatSetMsg(EVEN_ID_MSG_TASK,par,0);
	}
}

//======================================================================================
void APP_OperationKillThread(void* threadID)
{
	CMessageTable* pMsgTable;
	if(pMessageTable)
	{
		if(threadID == NULL)
		{
			pMsgTable=pMessageTable;
			pMessageTable=pMsgTable->pPrevious;
			free(pMsgTable);
			//LOG(LOG_ERROR,"APP OperationKillThread pMessageTable[%X],threadID[%X]\r\n",pMessageTable,pMessageTable->threadID);
			return;
		}
		pMsgTable=pMessageTable;
		pMessageTable=pMsgTable->pPrevious;
		free(pMsgTable);
		//------通知上层应用继续执行-------
		FIFO_OperatSetMsg(EVEN_ID_FUNTION_OUT,0,0);
		//------结束当前线程----------
		//pthread_cancel((pthread_t)threadID);
		pthread_kill((pthread_t)threadID, SIGQUIT);
		//ExitThread(threadID);
	}
}


void APP_OperationCreateThread(void *(*pFunThread)(void*))
{
	CMessageTable* pMsgTable;
	pMsgTable = (CMessageTable*)malloc(sizeof(CMessageTable));
	API_memset(pMsgTable,0x00,sizeof(CMessageTable));
	if(pthread_create(&pMsgTable->threadID, NULL,pFunThread,NULL))
	{
		LOG(LOG_ERROR,"pthread create error!\r\n");
		return;
	}
	pMsgTable->pFunMessageTask = NULL;
	pMsgTable->pPrevious = pMessageTable;
	pMessageTable=pMsgTable;
	LOG(LOG_INFO,"APP OperationCreateThread pMessageTable[%X],threadID[%X]\r\n",pMessageTable,pMessageTable->threadID);
}

void APP_OperationLoadThread(void* threadID)
{
	CMessageTable* pMsgTable;
	pMsgTable = (CMessageTable*)malloc(sizeof(CMessageTable));
	API_memset(pMsgTable,0x00,sizeof(CMessageTable));
	pMsgTable->threadID =(pthread_t)threadID;
	pMsgTable->pFunMessageTask = NULL;
	pMsgTable->pPrevious = pMessageTable;
	pMessageTable=pMsgTable;
	LOG(LOG_INFO,"APP OperationLoadThread pMessageTable[%X],threadID[%X]\r\n",pMessageTable,pMessageTable->threadID);
}


//==================500ms定时器模块======================================================
static int tTimeOut500MsCont=0,tTimeOut500MsEnd=0;

void  TimedRefresh500Ms(int sig)
{
	tTimeOut500MsCont++;
	if(tTimeOut500MsCont&0x01)
	{
		if(tWaitEventMsg.pFunTimer1)
		{
			if(EVENT_TIMEOUT == (*tWaitEventMsg.pFunTimer1)())
				tWaitEventMsg.pFunTimer1=NULL;
		}
	}
	else
	{
		if(tWaitEventMsg.pFunTimer2)
		{
			if(EVENT_TIMEOUT == (*tWaitEventMsg.pFunTimer2)())
				tWaitEventMsg.pFunTimer2=NULL;
		}
	}
	if(tTimeOut500MsEnd != 0 && tTimeOut500MsCont >= tTimeOut500MsEnd)
	{
		if(tWaitEventMsg.EventControl&EVENT_TIMEOUT)
		{
			FIFO_OperatSetMsg(EVEN_ID_TIME_OUT,500,0);
		}
		tTimeOut500MsEnd=0;
	}
}
/*
ITIMER_REAL: 给一个指定的时间间隔，按照实际的时间来减少这个计数，当时间间隔为0的时候发出SIGALRM信号
ITIMER_VIRTUAL: 给定一个时间间隔，当进程执行的时候才减少计数，时间间隔为0的时候发出SIGVTALRM信号
ITIMER_PROF: 给定一个时间间隔，当进程执行或者是系统为进程调度的时候，减少计数，时间到了，发出SIGPROF信号，这个和ITIMER_VIRTUAL联合，常用来计算系统内核时间和用户时间。
*/

//static struct sigaction TimerRefreshHandler;// = {0};
void StartTimed500ms(void)
{
	struct itimerval valtimer,oldtimer;
	signal(SIGALRM, TimedRefresh500Ms);
	valtimer.it_value.tv_sec = 0; 
	valtimer.it_value.tv_usec = 500*1000;
	valtimer.it_interval.tv_sec = 0; 
	valtimer.it_interval.tv_usec = 500*1000;
	setitimer(ITIMER_REAL, &valtimer, &oldtimer);
}

void StopTimed500ms(void)
{
	struct itimerval valtimer;
	signal(SIGALRM, SIG_DFL);
	valtimer.it_value.tv_sec = 0; 
	valtimer.it_value.tv_usec= 0;
	valtimer.it_interval = valtimer.it_value; //定时器间隔为1s
	//setitimer(ITIMER_PROF, &valtimer, NULL);
	setitimer(ITIMER_REAL, &valtimer, NULL);
}

//=======将执行函数导入定时器中======间隔1s,fTimerS1与fTimerS2互相错开0.5S=======
void LoadTimerSFun(funtimerS fTimerS1,funtimerS fTimerS2)
{
	if(fTimerS1)
		tWaitEventMsg.pFunTimer1 = fTimerS1;
	if(fTimerS2)
		tWaitEventMsg.pFunTimer2 = fTimerS2;
}

void ClearTimerSFun(int bitInter)
{
	if(bitInter&0x01)
		tWaitEventMsg.pFunTimer1 = NULL;
	if(bitInter&0x02)
		tWaitEventMsg.pFunTimer2 = NULL;
}

/*
void handler(int sig)
{
    printf("Handle the signal %d\n", sig);
}
 
int main(int argc, char **argv)
{
    sigset_t sigset;    // 用于记录屏蔽字
    sigset_t ign;       // 用于记录被阻塞(屏蔽)的信号集
    struct sigaction act;
 
    // 清空信号集
    sigemptyset(&sigset);
    
 
    // 向信号集中添加 SIGINT
    sigaddset(&sigset, SIGINT);
 
    // 设置处理函数 和 信号集
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
 
    printf("Wait the signal SIGNAL...\n");
    pause();
 
    // 设置进程屏蔽字, 在本例中为屏蔽 SIGINT
    sigprocmask(SIG_SETMASK, &sigset, 0);
    printf("Please press Ctrl + C in 10 seconds...\n");
    sleep(10);
 
    // 测试 SIGINT 是否被屏蔽
    sigemptyset(&ign);
    sigpending(&ign);
    if (sigismember(&ign, SIGINT))
    {
        printf("The SIGINT signal has ignored\n");
    }
 
    // 从信号集中删除信号 SIGINT
    sigdelset(&sigset, SIGINT);
    printf("Wait the signal SIGINT...\n");
 
    // 将进程的屏蔽字重新设置, 即取消对 SIGINT 的屏蔽
    // 并挂起进程
    sigsuspend(&sigset);
 
    printf("The app will exit in 5 secondes!\n");
    sleep(5);
 
    return 0;
}

*/

void Set_WaitEvent(int tTimeOutMs,u32 EventControl)
{
	tWaitEventMsg.EventControl=EventControl;
	if(tTimeOutMs > 0)
	{
		tTimeOut500MsEnd = tTimeOut500MsCont + (tTimeOutMs/500);
		tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
	}
}

/*
void Get_EventMsg(int *pTimeOutMs,u32 *pEventControl)
{
	if(pEventControl)
		*pEventControl=tWaitEventMsg.EventControl;
	if(pTimeOutMs)
		*pTimeOutMs=externalLoadTimeMs;
}
*/

void Rewrite_WaitTime(int tTimeOutMs)
{
	if(tTimeOutMs > 0)
	{
		tTimeOut500MsEnd = tTimeOut500MsCont + (tTimeOutMs/500);
		tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
	}
}



//========================事件处理模块===================================================
WAIT_EVENT_MSG tWaitEventMsg={0};


//===========================================================================

u32  API_WaitEvent(int tTimeOutMs,...)
{
	int MsgTimeMs;
	u32 MessageID,Message;
	u32 Event,EventControl=0x00000000;
	va_list arg;
	va_start( arg, tTimeOutMs );
	while(EVENT_NONE != (Event=va_arg(arg, u32)))
	{
		EventControl |= Event;
	}	
	va_end( arg );

	tWaitEventMsg.EventControl=EventControl;
	if(tTimeOutMs > 0)
	{
		tTimeOut500MsEnd = tTimeOut500MsCont + (tTimeOutMs/500);
		tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
	}
	//----------------------------------------------------
	Event=EVENT_NONE;
	do
	{//---------------阻塞处理-----------------------------------
		if(FIFO_OperatGetMsg(&MessageID,&Message,&MsgTimeMs))
		{
			switch(MessageID)
			{
				case EVEN_ID_KEY_DOWN:
					if(tWaitEventMsg.EventControl&EVENT_UI)
					{
						if((Message&0xff)==K_OK)
						{
							Event=EVENT_OK;
							break;
						}
						if((Message&0xff)==K_CANCEL)
						{
							Event=EVENT_CANCEL;
							break;
						}
					}
					if(tWaitEventMsg.EventControl&EVENT_MISC)
					{
						if((Message&0xff)==K_FUNC)
						{
							Event=EVENT_QUIT;
							break;
						}
					}
					if(tWaitEventMsg.pFunEvenKey)
					{
						Event=(*tWaitEventMsg.pFunEvenKey)(Message,MsgTimeMs);
					}
					else if(tWaitEventMsg.EventControl&EVENT_KEY)
					{
						Event=EVENT_KEY|(Message&0xff);
					}
					if(Event==EVENT_NONE)
					{
						tTimeOut500MsEnd = tTimeOut500MsCont + (tTimeOutMs/500);
					}
					break;
				case EVEN_ID_ABS:
					if(tWaitEventMsg.pFunEvenKey)
					{
						Event=(*tWaitEventMsg.pFunEvenKey)(Message,MsgTimeMs);
					}
					break;
				case EVEN_ID_TIME_OUT:
					Event=EVENT_TIMEOUT;
					break;
				case EVEN_ID_SHOW_UI:
					if(tWaitEventMsg.pFunEvenUI)
					{
						fEven_Process	pOldEvenKey;
						pOldEvenKey=tWaitEventMsg.pFunEvenKey;
						Event=(*tWaitEventMsg.pFunEvenUI)(Message,MsgTimeMs);
						
						tWaitEventMsg.EventControl=EventControl;
						if(tTimeOutMs > 0)
						{
							tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
							tTimeOut500MsEnd = tTimeOut500MsCont + (tTimeOutMs/500);
						}
						tWaitEventMsg.pFunEvenKey=pOldEvenKey;
					}
					break;
				case EVEN_ID_UART_RECV:
					Event=EVENT_UART;
					break;
				case EVEN_ID_ICC_MSG:
					Event=EVENT_ICC|(Message&0xff);
					break;
			}
		}
	}while(Event == EVENT_NONE);
	tWaitEventMsg.EventControl=0x00000000;
	tWaitEventMsg.pFunEvenKey=NULL;
	return Event;
}



const API_Even_Def ApiEven={
	{'E','V','E',12},
	FIFO_OperatInit,
	FIFO_OperatDeInit,
	FIFO_OperatSetMsg,
	FIFO_OperatGetMsg,
	FIFO_OperatPeekGetMsg,
	APP_OperationKillThread,
	APP_OperationCreateThread,
	APP_OperationLoadThread,

	Set_WaitEvent,
//	Get_EventMsg,
	Rewrite_WaitTime,
	API_WaitEvent,
};




