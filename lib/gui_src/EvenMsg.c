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
}CMessageItem;
#define 	MESSAGE_MAX	128

typedef struct _CMessageTable
{
	unsigned int		ReadID;
	unsigned int		WriteID;
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


void FIFO_OperatSetMsg(u32 MessageID,u32 Message)
{
	if(pMessageTable)
	{//----------FIFO------------------------
		register unsigned int WriteID;
		WriteID=(MESSAGE_MAX-1)&(pMessageTable->WriteID++);	
		pMessageTable->fifo[WriteID].Id= MessageID;
		pMessageTable->fifo[WriteID].Par= Message;
		sem_post(&g_sem_event);
		//-----�����Ϣ������,�������һ���������Ϣ---------
		//if(!((pMessageTable->WriteID ^ pMessageTable->ReadID)&0x03))
		//	pMessageTable->ReadID++;
		//LOG(LOG_INFO,"FIFO_OperatSetMsg[%X] WriteID[%d]MessageID[%d]Message[%d]\r\n",pMessageTable->threadID,WriteID, MessageID, Message);
	}
}
//����ʽ������Ϣ�ӿ�
int  FIFO_OperatGetMsg(u32 *pMessageID,u32 *pMessage)
{
	if(pMessageTable)
	{
		register unsigned int ReadID;
	Adder_ReOperatGetMsgRead:
		ReadID=pMessageTable->ReadID;
		if(ReadID == pMessageTable->WriteID)
		{//-------û��Ϣ����Ϣ----------
			sem_wait(&g_sem_event);
		}
		//--------����Ϣȡ��Ϣ--------------------
		if(ReadID ^ pMessageTable->WriteID)
		{//----------FIFO------------------------
			pMessageTable->ReadID++;
			ReadID &= (MESSAGE_MAX-1);
			//----------��������-----------
			if(pMessageTable->fifo[ReadID].Id== EVEN_ID_MSG_TASK)
			{
				if(pMessageTable->pFunMessageTask)
					(*pMessageTable->pFunMessageTask)(pMessageTable->fifo[ReadID].Par);
				goto Adder_ReOperatGetMsgRead;
			}					
			if(pMessageID)
				*pMessageID=pMessageTable->fifo[ReadID].Id;
			if(pMessage)
				*pMessage=pMessageTable->fifo[ReadID].Par;
			//LOG(LOG_INFO,"FIFO_OperatGetMsg[%X]ReadID[%d]MessageID[%d]Message[%d]\r\n",pMessageTable->threadID,ReadID, *pMessageID, *pMessage);
			return 1;
		}
	}
	return 0;
}

//=====������ʽ������Ϣ�ӿ�=========================
int  FIFO_OperatPeekGetMsg(u32 *pMessageID,u32 *pMessage)
{
	if(pMessageTable)
	{
		register unsigned int ReadID;
	Adder_ReOperatPeekGetMsg:
		ReadID=pMessageTable->ReadID;
		if(ReadID ^ pMessageTable->WriteID)
		{//----------FIFO----����Ϣ---------------------
			pMessageTable->ReadID++;
			//----------��������-----------
			ReadID &= (MESSAGE_MAX-1);
			if(pMessageTable->fifo[ReadID].Id== EVEN_ID_MSG_TASK)
			{
				if(pMessageTable->pFunMessageTask)
					(*pMessageTable->pFunMessageTask)(pMessageTable->fifo[ReadID].Par);
				goto Adder_ReOperatPeekGetMsg;
			}					
			if(pMessageID)
				*pMessageID=pMessageTable->fifo[ReadID].Id;
			if(pMessage)
				*pMessage=pMessageTable->fifo[ReadID].Par;
			return 1;
		}
		/*
		else
		{//-------�����Ϣ����----------
			MERCURY_MESSAGE_S* msg;
			MercuryPeekMessage(&msg,GetCurrentThread());
		}	*/
	}
	return 0;
}




void APP_PushMessageTask(fPushTaskMsg pFun,u32 par)
{
	if(pMessageTable)
	{
		pMessageTable->pFunMessageTask=pFun;
		FIFO_OperatSetMsg(EVEN_ID_MSG_TASK,par);
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
		//------֪ͨ�ϲ�Ӧ�ü���ִ��-------
		FIFO_OperatSetMsg(EVEN_ID_FUNTION_OUT,0);
		//------������ǰ�߳�----------
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

//=======================================================================================
//==================500ms��ʱ��ģ��======================================================
static int tTimeOutMsEvent=0,externalLoadTimeMs=0;
//static sigaction TimedRefresh500MsID = {NULL,NULL,0,0,0};

void  TimedRefresh500Ms()
{
	if(tWaitEventMsg.EventControl&EVENT_TIMEOUT)
	{
		if(externalLoadTimeMs)
		{
			tTimeOutMsEvent=externalLoadTimeMs;
			externalLoadTimeMs=0;
		}
		tTimeOutMsEvent -= 500;
		if(tTimeOutMsEvent <= 0)
		{
			FIFO_OperatSetMsg(EVEN_ID_TIME_OUT,500);
		}
	}
}

/*
void handler(int sig)
{
    printf("Handle the signal %d\n", sig);
}
 
int main(int argc, char **argv)
{
    sigset_t sigset;    // ���ڼ�¼������
    sigset_t ign;       // ���ڼ�¼������(����)���źż�
    struct sigaction act;
 
    // ����źż�
    sigemptyset(&sigset);
    
 
    // ���źż������ SIGINT
    sigaddset(&sigset, SIGINT);
 
    // ���ô����� �� �źż�
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
 
    printf("Wait the signal SIGNAL...\n");
    pause();
 
    // ���ý���������, �ڱ�����Ϊ���� SIGINT
    sigprocmask(SIG_SETMASK, &sigset, 0);
    printf("Please press Ctrl + C in 10 seconds...\n");
    sleep(10);
 
    // ���� SIGINT �Ƿ�����
    sigemptyset(&ign);
    sigpending(&ign);
    if (sigismember(&ign, SIGINT))
    {
        printf("The SIGINT signal has ignored\n");
    }
 
    // ���źż���ɾ���ź� SIGINT
    sigdelset(&sigset, SIGINT);
    printf("Wait the signal SIGINT...\n");
 
    // �����̵���������������, ��ȡ���� SIGINT ������
    // ���������
    sigsuspend(&sigset);
 
    printf("The app will exit in 5 secondes!\n");
    sleep(5);
 
    return 0;
}



void StartTimed500ms(void)
{
	if(0)//if(TimedRefresh500MsID.sa_handler)
	{
		struct itimerval val;
		val.it_value.tv_sec = 0; //1������ö�ʱ��
		val.it_value.tv_usec = 500*1000;
		val.it_interval = val.it_value; //��ʱ�����Ϊ1s
		setitimer(ITIMER_PROF, &val, NULL);
	}
	else
	{
		struct itimerval val;
		struct sigaction act;
		act.sa_handler = TimedRefresh500Ms; //���ô����źŵĺ���
		act.sa_flags  = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGPROF,&act, NULL);//ʱ�䵽����SIGROF�ź�
	         
	    val.it_value.tv_sec = 0; //1������ö�ʱ��
	    val.it_value.tv_usec = 500*1000;
	    val.it_interval = val.it_value; //��ʱ�����Ϊ1s
	    setitimer(ITIMER_PROF, &val, NULL);
		TimedRefresh500MsID = 0xff;
	}
}

void StopTimed500ms(void)
{
	if(TimedRefresh500MsID)
	{
		struct itimerval val;
		val.it_value.tv_sec = 0; //1������ö�ʱ��
		val.it_value.tv_usec = 0;
		val.it_interval = val.it_value; //��ʱ�����Ϊ1s
		setitimer(ITIMER_PROF, &val, NULL);
	}
}
*/

void Set_WaitEvent(int tTimeOutMs,u32 EventControl)
{
	tWaitEventMsg.EventControl=EventControl;
	if(tTimeOutMs > 0)
	{
		externalLoadTimeMs = tTimeOutMs;
		tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
	}
}

void Get_EventMsg(int *pTimeOutMs,u32 *pEventControl)
{
	if(pEventControl)
		*pEventControl=tWaitEventMsg.EventControl;
	if(pTimeOutMs)
		*pTimeOutMs=externalLoadTimeMs;
}


void Rewrite_WaitTime(int tTimeOutMs)
{
	if(externalLoadTimeMs^tTimeOutMs)
		externalLoadTimeMs = tTimeOutMs;
}



//========================�¼�����ģ��===================================================
WAIT_EVENT_MSG tWaitEventMsg={0};


//===========================================================================

u32  API_WaitEvent(int tTimeOutMs,...)
{
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
	if(tTimeOutMs >= 0)
	{
		tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
		externalLoadTimeMs = tTimeOutMs;
	}
	//----------------------------------------------------
	Event=EVENT_NONE;
	do
	{//---------------��������-----------------------------------
		if(FIFO_OperatGetMsg(&MessageID,&Message))
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
						Event=(*tWaitEventMsg.pFunEvenKey)(Message);
					}
					else if(tWaitEventMsg.EventControl&EVENT_KEY)
					{
						Event=EVENT_KEY|(Message&0xff);
					}
					if(Event==EVENT_NONE)
					{
						externalLoadTimeMs = tTimeOutMs;
					}
					break;
				case EVEN_ID_ABS:
					if(tWaitEventMsg.pFunEvenKey)
					{
						Event=(*tWaitEventMsg.pFunEvenKey)(Message);
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
						Event=(*tWaitEventMsg.pFunEvenUI)(Message);
						
						tWaitEventMsg.EventControl=EventControl;
						if(tTimeOutMs>0)
						{
							tWaitEventMsg.EventControl |= EVENT_TIMEOUT;
							externalLoadTimeMs = tTimeOutMs;
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
	Get_EventMsg,
	Rewrite_WaitTime,
	API_WaitEvent,
};




