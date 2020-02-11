/*****************************21�����ն�Ӳ�����кŲ���******************************
//����-------  ����Ӳ�����кš����ض�Ӧ��Կ���ն˼���鿴���к���Macֵ
//����-------  �˹���
//����ʱ��--20170613
******************************************************************************/
#include "comm_type.h"
#include "sys_sdk.h"
#include "xui_comm.h"

#include "tls_sdk.h"
#include "dataconv.h"

#include "app_sdk.h"
#include "AdminTUSN.h"

//==========����ӿ�=========================================================

#define USAGE_MKEK_HARD_INDEX			0X06		//Ӳ�����кż�������Կ
#define USAGE_WKEK_HARD_INDEX			0X03		//Ӳ�����кż��ܹ�����Կ

//==============================
#define UART_PC		6			//��������PCʹ�õĴ���,RJ11С��
#define BAUD_PC		9600		//PC���ò�����


#define UART_TIME_OUT			(15*1000)  //��λms
//=============�������ڹ���==============================
#define HARD_SN_STATUS_WR		"UpSn" // ��ʾ������дSN
#define HARD_SN_STATUS_UP		"Aply" // ��ʾ���ϱ�SN
#define HARD_SN_STATUS_DOWN		"Work" // ��ʾ���������к���Կ
#define HARD_SN_STATUS_OVER		"Over" // ��ʾ������

#define MFRS_ID					"000009" 	   //����ID ����:000009,����:000026   
#define DEVICE_TYPE				"02" 		   //�豸���ͣ� 05�� II �͹̶��绰 
//======================�ն��ͺ�======================================
#define TERM_TYPE				"KS8312" 		//����G��
//=================================================================

const u8 g_root_key[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};

DfTermPar tAdminTermPar;

extern tHardSN_Key* OsSysGet_SnKey(void);
extern void OsSysMsg_sync(void);


//====================ARM������==========================
int APP_GetHardMsg(u8 type,void *pOut,int OutSize)
{
	u8 i,check,*p;
	tHardSN_Key* pSn;
	pSn = OsSysGet_SnKey();
	p=(u8*)pSn;
	for(check=0,i=0;i<sizeof(tHardSN_Key);i++)
	{
		check += p[i];
	}
	if(check)
	{
		LOG_HEX(LOG_INFO,"GetHardMsg CheckErr->Buf",p,sizeof(tHardSN_Key));
		return -1;
	}
	if(pSn->LifeEnd)
	{
		return -2;
	}
	if(type==TYPE_TERM_HARD_LIFE)
	{
		API_memcpy(pOut,pSn->Life,OutSize);
		return OutSize;
	}
	else if(type==TYPE_TERM_HARD_SN)
	{
		API_memcpy(pOut,pSn->HardSN,OutSize);
		return OutSize;
	}
	else if(type==TYPE_TERM_HARD_TMK)
	{
		if(strcmp(pSn->Life,HARD_SN_STATUS_WR) == 0)
		{//----ûд21����֮ǰ����ԭ������---
			API_memcpy(pOut,pSn->TMK,OutSize);
			return OutSize;
		}
		else if(strcmp(pSn->Life,HARD_SN_STATUS_DOWN) == 0)
		{
			u8 ptk_key[16];
			char TUSN[32]={0};
			int ln=0;
			if(OutSize < sizeof(pSn->TMK)) 
				return -12;
			API_strcpy(TUSN,TERM_TYPE);
			API_memcpy(TUSN+API_strlen(TUSN),pSn->HardSN,pSn->SnLen);
			API_memcpy(ptk_key,TUSN+API_strlen(TUSN)-16, 16);
			// ���ܵõ�������Կ
			API_Crypt(CRYPT_TYPE_DES,g_root_key,16,NULL,ptk_key,16,ptk_key,&ln,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
			memcpy(pOut,pSn->TMK,sizeof(pSn->TMK));
			// ����
			API_Crypt(CRYPT_TYPE_DES,ptk_key,16,NULL,pOut,16,pOut,&ln,CRYPT_MODE_DECRYPT|CRYPT_MODE_ECB);
			return sizeof(pSn->TMK);
		}
		return -3;
	}
	else if(type==TYPE_TERM_HARD_ALL)
	{
		API_memcpy(pOut,pSn,OutSize);
		return OutSize;
	}
	return -5;
}


int APP_SetHardMsg(u8 type,void *pIn,int InSize)
{
	u8 i,check,*p;
	tHardSN_Key* pSnKey;
	pSnKey = OsSysGet_SnKey();
	if(type==TYPE_TERM_HARD_LIFE)
	{
		API_memcpy(pSnKey->Life,pIn,4);
		pSnKey->LifeEnd='\0';
	}
	else if(type==TYPE_TERM_HARD_SN)
	{
		if(InSize > sizeof(pSnKey->HardSN))
			InSize = sizeof(pSnKey->HardSN);
		API_memcpy(pSnKey->HardSN,pIn,InSize);
		if(InSize < sizeof(pSnKey->HardSN))
		{
			pSnKey->HardSN[InSize]='\0';
		}
		pSnKey->SnLen=API_strlen(pSnKey->HardSN);
	}
	else if(type==TYPE_TERM_HARD_TMK)
	{
		API_memcpy(pSnKey->TMK,pIn,sizeof(pSnKey->TMK));
	}
	else if(type==TYPE_TERM_HARD_ALL)
	{
		API_memcpy(pSnKey,pIn,InSize);
	}
	else return -1;
	
	p=(u8*)pSnKey;
	for(check=0,i=0;i<(sizeof(tHardSN_Key)-1);i++)
	{
		check += p[i];
	}
	pSnKey->Addcheck = ~check+1;
	OsSysMsg_sync();
	//LOG_HEX(LOG_INFO,"SetHardMsg->Buf",Buf,NV_APPINFO_LEN);
	return 0;
}





int APP_GetLifeCycle(void)
{
	char HardLife[6];
	int		Ret;
	Ret=APP_GetHardMsg(TYPE_TERM_HARD_LIFE,HardLife,sizeof(HardLife));
	if(Ret < 1)
	{
		return 1;	//����������ʧ�ܻ�֧��21����
	}
	if(0 == API_memcmp(HardLife,"UpSn",4))
		return 2;
	if(0 == API_memcmp(HardLife,"Aply",4))
		return 3;
	if(0 == API_memcmp(HardLife,"Work",4))
		return 4;
	//if(0 == API_memcmp(HardLife,"Over",4))
	return 5;
}

int ShowHardSn(char *title)
{
	tHardSN_Key ReadHardSnSta;
	char ShowBuff[128];
	if(APP_GetHardMsg(TYPE_TERM_HARD_ALL,&ReadHardSnSta,sizeof(ReadHardSnSta)) < 0)
	{
		APP_ShowMsg(title,"������Ӳ�����к�",3000);
		return 1;
	}
	API_sprintf(ShowBuff,"SN:%s\n���к�״̬:%s",ReadHardSnSta.HardSN,ReadHardSnSta.Life);
	APP_ShowMsg(title,ShowBuff,10*1000);
	return 0;
}


int ScanGetHardSn(char *title,char* HardSn)
{
	API_GUI_CreateWindow(title,NULL,NULL,0);
	API_GUI_Info(NULL,TEXT_ALIGN_LEFT|TEXT_VALIGN_TOP|TEXT_EXSTYLE_UNDERLINE,"���׼���к���Ϣ��");
	API_GUI_Info(NULL,TEXT_ALIGN_RIGHT|TEXT_VALIGN_BOTTOM|TEXT_EXSTYLE_OVERLINE,"��[ȷ��]������");
	API_GUI_Show();
	/*
	int IndexId;
	IndexId=APP_OnlyCamScan(0x02,12,12,HardSn,20*1000);
	if(IndexId<0) return 1;
	if(IndexId==OPER_HARD)
	*/
	{
	   HardSn[0]='K';
	   HardSn[1]='\0';
       if(APP_InputAbc(title,"�ն����к�����:",  "�밴���ּ�����", HardSn,12,12)) return 1;//��ȡ��������
	}
	if(HardSn[0] !='K')
	{
	    APP_ShowMsg(title,"���к���������ȷ!",5000);
		return 1;
	}
	return  0;
}

// д�����к�SN
int APP_SetHardSn(char *pHardSn)
{
	tHardSN_Key ReadHardSnSta;
	CLEAR(ReadHardSnSta);
	APP_GetHardMsg(TYPE_TERM_HARD_ALL,&ReadHardSnSta,sizeof(ReadHardSnSta));
	API_strcpy(ReadHardSnSta.HardSN,pHardSn);
	API_strcpy(ReadHardSnSta.Life,HARD_SN_STATUS_WR);
	if(APP_SetHardMsg(TYPE_TERM_HARD_ALL,&ReadHardSnSta,sizeof(ReadHardSnSta)) >= 0)
	{
		CLEAR(ReadHardSnSta.HardSN);
		if(APP_GetHardMsg(TYPE_TERM_HARD_SN,ReadHardSnSta.HardSN,sizeof(ReadHardSnSta.HardSN)) > 0)
		{
			if(API_strcmp(pHardSn,ReadHardSnSta.HardSN) == 0)
			{
				return 0;
			}
		}
	}
	return -1;
}

int WriteHardSn(char *title)
{
    char HardSn[36]={0};
	if(0 < APP_GetHardMsg(TYPE_TERM_HARD_LIFE,HardSn,4))
	{
		if(API_memcmp(HardSn,HARD_SN_STATUS_WR,4)==0)
		{
			APP_ShowMsg(title,"״̬������\n�ն����������к�",3000);
			return 1;
		}
	}
	if(ScanGetHardSn(title,HardSn)) return 1;
	APP_ShowSta(title,"����д��");// ������ʾ д�������ʱ�ȽϾ�
	if(APP_SetHardSn(HardSn)==0)
	{
		char Msg[128];
		API_sprintf(Msg,"SN:%s\n�ն����к�д��ɹ�",HardSn);
		APP_ShowMsg(title,Msg,10*1000);
		return 0;
	}
	APP_ShowMsg(title,"�ն����к�д��ʧ��!",10*1000);
	return -1;
}

int ChangHardSn(char *title)
{	
    char HardSn[36]={0};
    if(APP_InputPin(title,"��������֤����","�����ݼ�����", "002197")) return 1;
	if(ScanGetHardSn(title,HardSn)) return 1;
	APP_ShowSta(title,"���ڸ���...");// ������ʾ д�������ʱ�ȽϾ�
	if(APP_SetHardSn(HardSn)==0)
	{
		char Msg[128];
		API_sprintf(Msg,"SN:%s\n�ն����кŸ��³ɹ�",HardSn);
		APP_ShowMsg(title,Msg,10*1000);
		return 0;
	}
    APP_ShowMsg(title,"�ն����кŸ���ʧ��!",10*1000);
	return -1;
}
int ClearHardSn(char *title)
{	
	tHardSN_Key ReadHardSnSta; 
	char Msg[128];
	int ret;
	API_memset(&ReadHardSnSta,0xff,sizeof(ReadHardSnSta));
	ret=APP_SetHardMsg(TYPE_TERM_HARD_ALL,&ReadHardSnSta,sizeof(ReadHardSnSta));
	API_sprintf(Msg,"����ɹ�[%d]",ret);
	APP_ShowMsg(title,Msg,10*1000);
	return 0;
}


//-------------�˵�------------------------------------
extern int APP_Menu_TermSnProsee(char* title);

int Menu_TermSnProsee(char* title)
{
	    CMenuItemStru MenuStruPar[]=
		{
			{"д���ն����к�",			WriteHardSn},//ProduceWriteHardSn,
		    {"�鿴�ն����к�",			ShowHardSn},	
		    {"�޸��ն����к�",          ChangHardSn},
		    {"21�����ϱ�����",			APP_Menu_TermSnProsee},
		};
		return APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
}
//=================21 ���Ŀͻ���=======================
typedef enum  
{
	CMD_USER_lOGIN			=0xC0,		//2.3.�û�����
	CMD_HAND_SHAKE			=0xC1,		//2.4.����
	CMD_GET_MFR_SN			=0xD1,		//2.5.��ȡ���̱�š��豸����
	CMD_TERM_USN_REPORT		=0xD2,		//2.6.�ն�Ψһ���к��ϱ� �������ɵ� TUSN��ʽ�ϱ�  ����D4�ĵ�����ʽ����
	CMD_TERM_USN_APPLY		=0xD4,		//2.7.�ն�Ψһ���к�����
	CMD_TERM_UKEY_GNRT		=0xD6,		//2.8.�ն�Ψһ���к���Կ����
	CMD_DOWN_UKEY_FB		=0xDA,		//2.9.���ؽ��֪ͨ
	CMD_ONLINE_ACT			=0xD8,		//2.10.��������
	CMD_AUTHORIZE_DOWN_KEY	=0xC8,		//2.11.��Ȩ��Կ����
}UART_PACKET_CMD;


typedef enum
{
	CMD_ERR_NONE			='0',	//�ɹ�
	CMD_ERR_FAIL			='F',	//ʧ��
	CMD_ERR_ACCOUNT		='1',	//�Ƿ��˻�
	CMD_ERR_PWD			='2',	//�Ϸ��˻���������֤ʧ��
	CMD_ERR_TERM_NOT		='3',	//�ն˲�����
	CMD_ERR_TERM_ALREAD	='4',	//�ն��Ѵ���
	CMD_ERR_KEY_NOT		='5',	//��Կ������
	CMD_ERR_KEY_ALREAD	='6',	//��Կ�Ѵ���
	CMD_ERR_INDEX_NOT		='7',	//��Ȩ��Կ��Ų�����
	CMD_ERR_MAC			='8',	//MAC����
	CMD_ERR_DATE_OUT		='9',	//��Ȩ��Կ����
}UART_PACKET_RESULT;

typedef struct
{
	u8	stx; 		//ͷ
	u8	cmd; 		//����
	u8	Len[2];		//����
	u8	data[256]; 	//����
	//u8	crc32;	//CRC32
	//u8	etx;	//����
}PE_UART_PACKET;


#define 	DfGetStr2HexLen(nL,sL) 			{nL=sL[0]*256+sL[1];}
#define 	DfSetStr2HexLen(sL,nL) 			{sL[0]=nL/256; sL[1]=nL&0xff;}

int APP_Uart_Init()
{
	//APP_ShowSta(NULL,"�����л���...");
	return OsPortOpen(PORT_COM1,"115200,8,n,1");
}
int APP_Uart_End(char* title)
{
	OsPortClose(PORT_COM1);
	return 0;
}


int	API_Uart_Send(u8* pSendBuf,u32 tSendLen)
{
	return OsPortSend(PORT_COM1,pSendBuf,tSendLen);
}
int	API_Uart_Recv(u8* pRecvBuf, u32 nRecvSize, u32* pRecvLen)
{
	int ReadLen=0,ret=0;
	u32 MessageID,Message;
	Set_WaitEvent(TIME_INFINE,EVENT_KEY);
	while(1)
	{
		ReadLen=OsPortRecv(PORT_COM1,pRecvBuf,nRecvSize,150);
		if(ReadLen > 0)
		{
			LOG(LOG_INFO,"MercuryUsbRead\r\n");
			LOG_HEX(LOG_INFO,"API_Uart_Recv:",pRecvBuf,ReadLen);
			*pRecvLen=ReadLen;
			break;
		}
		if(FIFO_OperatPeekGetMsg(&MessageID,&Message,NULL))
		{
			if(MessageID == EVEN_ID_KEY_DOWN)
			{
				if(Message==K_CANCEL)
				{
					ret=1;
					LOG(LOG_INFO,"MercuryUsbRead  K_CANCEL\r\n");
					break;
				}
			}
		}
	}
	Set_WaitEvent(TIME_INFINE,EVENT_NONE);
	return ret;
}
//=========SDK�汾���ⲿ�ṩ==========================
u16 APP_String_CutHead(u8 *str,u16 len,u16 hdLen)
{
	u16 	i,Max;
	if(hdLen==0 || hdLen>=len) 
		return len;
	Max=len-hdLen;
	for(i=0;i<Max;i++)
		str[i] = str[i+hdLen];
	return Max;
}

int CheckRecvPack(u8* pRecvData,u16 *pRecvLen)
{
	u16	Max,i;
	u8 crc32;
	PE_UART_PACKET *pPacket;
	Max=*pRecvLen;
	for(i=0;i<Max;i++)
	{
		if(pRecvData[i]==0x02)
			break;
	}
	if(i) 
		*pRecvLen = APP_String_CutHead(pRecvData,Max, i);//�޳�����ͷǰ�ַ�
	if(i==Max) 
		return OPER_NoHEAD;
	
	pPacket=(PE_UART_PACKET *)pRecvData;
	DfGetStr2HexLen(Max,pPacket->Len);
	if(*pRecvLen < (Max+(sizeof(PE_UART_PACKET)-sizeof(pPacket->data))))
		return OPER_NoEND;
	Max+=2;	////(stx+cmd)-(crc32+etx)+Len[2]
	crc32=Crc32Cal((u8*)pPacket, Max);
	if(((u8*)pPacket)[Max]== crc32)
	{
		Max += 2;
		*pRecvLen = Max;
		LOG_HEX(LOG_INFO,"PC_RecvPack:",pRecvData,Max);
		return OPER_OK;	
	}
	return OPER_CRCERR;
}
//====================================================================
//����:  CRC32У��
//��������: crc ��Ҫ��ʼ��CRC����
//�������: ��ʼ��CRC����
//���ز���: pTable��
//---------------------------------------------------------------
u32 Crc32Cal(u8 *buff, int len)
{
	int i,j;
	u32 crc;
	u32 Table[256];
    for(i = 0 ; i < 256 ; i++)
    {
        for (j = 0, Table[i] = i ; j < 8 ; j++)
        {
            Table[i] = (Table[i]>>1)^((Table[i]&1)?0xEDB88320:0);
        }
    }
    crc = 0xFFFFFFFF;
    for(i = 0; i < len; i++)
    {
        crc = (crc >> 8) ^ Table[(crc ^ buff[i]) & 0xff];
    }
    return ~crc;
}

typedef int (*CHECK_DATA)(u8*,u16 *);
s16 APP_UART_Comm(u32 UartIndex,u8* pInBuf,u16 InLen,u8* pOutBuf,u16 *pOutLen,int msTimeOut,CHECK_DATA pFCheck)
{
	u8 RecvOk;
	u16 reclen=0;
	u32	ret;
	int checkflag;
	if(pInBuf)
	{
		API_Uart_Send(pInBuf,InLen); // ��������
	}
	if(pOutBuf==NULL)
		return OPER_RET;	
	RecvOk=1;
	API_memset(pOutBuf,0,*pOutLen);
	for(;;)
	{
		if(RecvOk)
		{
			if(API_Uart_Recv(pOutBuf+reclen,*pOutLen-reclen,&ret))return OPER_QUIT;
			reclen	+= ret;
			if(pFCheck)
			{
				checkflag=(*pFCheck)(pOutBuf,&reclen);
				if(checkflag<0) return checkflag;
				if(checkflag==OPER_OK)
				{
					*pOutLen=reclen;
					return OPER_OK; 
				}
			}
			else
			{
				*pOutLen=reclen;
				return OPER_OK; 
			}
			RecvOk=0;
		}
	}
}
void ShowErrorInfo(char *title,u8 ErrCode)
{	
	char display[128]={0};
	API_sprintf(display,"������[%c]\n", ErrCode);
	switch(ErrCode)
	{
		case CMD_ERR_TERM_NOT:
			API_strcat(display,"�ն˲�����");
			break;
		case CMD_ERR_TERM_ALREAD:
			API_strcat(display,"�ն��Ѵ���");
			break;
		case CMD_ERR_KEY_NOT:
			API_strcat(display,"��Կ������");
			break;
		case CMD_ERR_KEY_ALREAD:
			API_strcat(display,"��Կ�Ѵ���");
			break;
		case CMD_ERR_INDEX_NOT:
			API_strcat(display,"��Ȩ��Կ��Ų�����");
			break;
		case CMD_ERR_MAC:
			API_strcat(display,"MACУ�����");
			break;
		case CMD_ERR_DATE_OUT:
			API_strcat(display,"��Ȩ��Կ����");
			break;
        case CMD_ERR_FAIL:
            API_strcat(display,"ָ��ִ��ʧ��");
            break;
		default:
			API_strcat(display,"δ֪����");
            break;
	}
	APP_ShowMsg(title,display,3000);
}


u16 GetSendPack(u8 cmd,u8* pInData,u16 InLen,PE_UART_PACKET* pPacket)
{
	u8 crc32;
	//--------------Send Data-------------------------------------
	pPacket->stx=0x02;
	pPacket->cmd=cmd;
	if(pInData!=NULL && InLen!=0)
	API_memcpy(pPacket->data, pInData, InLen);
	InLen+=2;	////crc32+etx
	DfSetStr2HexLen(pPacket->Len,InLen);// ʮ�����Ƴ���
	InLen+=2;	////(stx+cmd)-(crc32+etx)+Len[2]
	crc32=Crc32Cal((u8*)pPacket,InLen);
	((u8*)pPacket)[InLen++]=crc32;
	((u8*)pPacket)[InLen++]=0x03;
	LOG_HEX(LOG_INFO,"PC_SendPack:",(u8*)pPacket,InLen);
	return InLen;
}
int LoadHardkey(char* pTermSnKey,u8 *pInKey,u8 Len)
{
	return APP_SetHardMsg(TYPE_TERM_HARD_TMK,pInKey,Len);
}

int SendCmdPack(char *title,u32 CommIndex, u8* pCmd,u8 CmdNum)
{
	u8 cmd,i,RetCode='0';
	char inData[80]={0};
	PE_UART_PACKET tSendData,tRecvData;
	u16 InLen,SendLen,RecvLen;
	char *pShowRet="�������";
	APP_ShowSta(title,"����������...");
	for(i=0;i<CmdNum;i++)
	{
		cmd=pCmd[i];
		InLen=0;
		CLEAR(inData);
		switch(cmd)
		{
			case CMD_HAND_SHAKE:
			case CMD_GET_MFR_SN:
				break;
			case CMD_TERM_USN_APPLY:
				API_sprintf(inData+40,"%s%s%s",MFRS_ID,DEVICE_TYPE,TERM_TYPE);
				InLen=40+24;
				inData[InLen++]='1';//���ɷ�ʽ
				break;
			case CMD_TERM_USN_REPORT:
			case CMD_TERM_UKEY_GNRT:
			case CMD_ONLINE_ACT:
				// 8312 ����֮ǰ��SN  ��ȫ����ͷ
				API_strcpy(inData,MFRS_ID);
				API_strcat(inData,DEVICE_TYPE);
				API_strcat(inData,TERM_TYPE);
				APP_GetHardMsg(TYPE_TERM_HARD_SN,inData+API_strlen(inData),sizeof(inData)-API_strlen(inData));
				API_strcpy(inData+60,TERM_TYPE);
				InLen=60+16;
				break;
			case CMD_DOWN_UKEY_FB:
				// 8312 ����֮ǰ��SN  ��ȫ����ͷ
				API_strcpy(inData,MFRS_ID);
				API_strcat(inData,DEVICE_TYPE);
				API_strcat(inData,TERM_TYPE);
				APP_GetHardMsg(TYPE_TERM_HARD_SN,inData+API_strlen(inData),sizeof(inData)-API_strlen(inData));
				inData[60]=RetCode;
				InLen=61;
				break;
			default:
				return RET_ERR;
		}
		SendLen=GetSendPack(cmd,(u8*)inData,InLen,&tSendData);
		RecvLen=sizeof(tRecvData);
		if(OPER_OK != APP_UART_Comm(CommIndex,(u8*)&tSendData,SendLen,(u8*)&tRecvData,&RecvLen,15*1000,&CheckRecvPack))
		{
			APP_ShowMsg(title,"����ʧ��",3000);
			return OPER_TIMEOUT;
		}
		if(cmd != tRecvData.cmd)
		{
			char ShowMsg[64];
			API_sprintf(ShowMsg,"%X���ݰ�����%X����",tRecvData.cmd,tRecvData.stx);
			APP_ShowMsg(title,ShowMsg,5000);//"�������ݰ��������"
			return RET_ERR;
		}
		RetCode=tRecvData.data[0];
		if(RetCode == '0')
		{
			if(cmd == CMD_TERM_USN_REPORT)// cyb KS8312 �����ϱ��ķ�ʽ  D2�ϱ��ɹ��� ����Ҳ��D2ָ��
			{		
				pShowRet="TUSN���ϱ��ɹ�";
				APP_SetHardMsg(TYPE_TERM_HARD_LIFE,HARD_SN_STATUS_UP,4);	
			}
			else if(cmd==CMD_TERM_UKEY_GNRT || cmd==CMD_ONLINE_ACT)
			{
				if(0x16 != tRecvData.data[1])		//BCD ����
				{
					pShowRet="��Կ���Ȳ�Ϊ16�ֽ�";
					RetCode='1';
					continue;
				}
				if(RET_OK!=LoadHardkey(inData+8,&tRecvData.data[2],16))
				{
					pShowRet="������Կʧ��";
					RetCode='1';
					continue;
				}
				if(cmd==CMD_TERM_UKEY_GNRT)
				{
					APP_SetHardMsg(TYPE_TERM_HARD_LIFE,HARD_SN_STATUS_DOWN,4);
					pShowRet="��Կ���سɹ�";
				}
				else if(cmd==CMD_ONLINE_ACT)
				{
					APP_SetHardMsg(TYPE_TERM_HARD_LIFE,HARD_SN_STATUS_DOWN,4);
					pShowRet="�ն˼���ɹ�";
				}
			}
			else if(cmd == CMD_TERM_USN_APPLY)// D4����ƽ̨������ʽ�����·�
			{
				if(RecvLen<64)
				{
					pShowRet="���ݳ��ȴ���";
				}
				else
				{
					RecvLen=API_strlen((char*)&tRecvData.data[1]);
					if(RecvLen < 12)
					{
						pShowRet="TUSN�ų��ȴ���";
					}
					else
					{
						if(APP_SetHardMsg(TYPE_TERM_HARD_SN,&tRecvData.data[1],RecvLen))
						{
							pShowRet="TUSN�Ÿ���ʧ��";
						}
						else
						{
							pShowRet="TUSN�Ÿ��³ɹ�";
							APP_SetHardMsg(TYPE_TERM_HARD_LIFE,HARD_SN_STATUS_WR,4);
						}
					}
				}
			}
		}
		else
		{
			ShowErrorInfo(title,RetCode);
			return OPER_SYSTEM_ERROR;
		}
	}
	APP_ShowMsg(title,pShowRet,3000);
	return OPER_OK;
}

int APP_GetHardSm4Mac(u8* pInData,u16 InLen,u8 *pOutMac)
{
	u8 Sm4Key[16]={0},Sm4Data[16]={0},AscData[34]={0};
	u16 i;
	int ouLen;
	if(sizeof(Sm4Key) > APP_GetHardMsg(TYPE_TERM_HARD_TMK,Sm4Key,sizeof(Sm4Key)))
	{
		return -1;
	}
	CLEAR(Sm4Data);
	for(i=0;i<InLen;i++)
	{
		Sm4Data[i%16] ^= pInData[i];
	}
	Conv_BcdToStr(Sm4Data,sizeof(Sm4Data),(char*)AscData);
	CLEAR(Sm4Data);
	API_Crypt(CRYPT_TYPE_SM4,Sm4Key,16,NULL,AscData,16,Sm4Data,&ouLen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
	API_memcpy(AscData,Sm4Data,16);
	for(i=0;i<16;i++)
	{
		AscData[i] ^= AscData[i+16];
	}
	API_Crypt(CRYPT_TYPE_SM4,Sm4Key,16,NULL,AscData,16,Sm4Data,&ouLen,CRYPT_MODE_ENCRYPT|CRYPT_MODE_ECB);
	API_memcpy(AscData,Sm4Data,16);
	//----����Sm4Data�ռ俽�����ݣ�����pOutMacԽ��---
	CLEAR(Sm4Data);
	Conv_BcdToStr(AscData,4,(char*)Sm4Data);
	if(pOutMac)
	{
		memcpy(pOutMac,Sm4Data,8);
	}
	return 0;
}
//��ȡӲ�����к������ӦMACֵ
int APP_GetHardSnAndMac(u8* pInRandPar,u8 InRandLen,char *pOutHardSn,u8 *pOutMac)
{
	char HardSnSta[60];
	u8 MacData[60+8];
	s16		Ret;
	Ret=APP_GetHardMsg(TYPE_TERM_HARD_SN,HardSnSta,sizeof(HardSnSta));
	if(Ret < 5)
	{
		return -1;	//����������ʧ�ܻ�֧��21����
	}
	if(pOutHardSn)
	{
		API_memcpy(pOutHardSn,HardSnSta,Ret);
		pOutHardSn[Ret]='\0';
	}
	if(pOutMac)
	{
		API_memcpy(MacData, HardSnSta, Ret);
		API_memcpy(MacData+Ret,pInRandPar,InRandLen);
		Ret += InRandLen;
		return APP_GetHardSm4Mac(MacData,Ret,pOutMac);
	}
	return 0;
}

int ProduceWriteHardSn(char *title)
{
	u8 cmds[]={CMD_HAND_SHAKE, CMD_TERM_USN_REPORT};
	char lifeBuff[6]={0};
	if(0 < APP_GetHardMsg(TYPE_TERM_HARD_LIFE,lifeBuff,4))
	{
		if(API_memcmp(lifeBuff,HARD_SN_STATUS_OVER,4)==0)
		{
			APP_ShowMsg("״̬������","����д��SN��",3000);
			return 1;
		}
		if((API_memcmp(lifeBuff,HARD_SN_STATUS_UP,4)==0)	\
			||(API_memcmp(lifeBuff,HARD_SN_STATUS_DOWN,4)==0))
		{
			APP_ShowMsg("״̬������","�ն����ϱ����к�",3000);
			return 1;
		}
	}
	APP_ShowSta(title,"���ڴ���...");
	return SendCmdPack(title,UART_2,cmds,sizeof(cmds)/sizeof(cmds[0]));
}


int PC_LoadHardKey(char *title)
{
	u8 cmds[]={CMD_HAND_SHAKE,CMD_TERM_UKEY_GNRT, CMD_DOWN_UKEY_FB};
    char lifeBuff[6]={0};
	APP_ShowSta(title,"���ڴ���...");
	if(0 > APP_GetHardMsg(TYPE_TERM_HARD_LIFE,lifeBuff,sizeof(lifeBuff)))
	{
		APP_ShowMsg(title,"����Ψһ���к�����",3000);
		return 1;
	}
	if(API_memcmp(lifeBuff,HARD_SN_STATUS_DOWN,4)==0)  
	{
		APP_ShowMsg(title,"�ն���������Կ",3000);
		return 1;
	}
	return SendCmdPack(title,UART_2,cmds,sizeof(cmds)/sizeof(cmds[0]));
}

int PC_OnlineActivate(char *title)
{
	u8 cmds[]={CMD_ONLINE_ACT};
	char lifeBuff[6]={0};
	
	APP_ShowSta(title,"���ڴ���...");
	
	if(0 > APP_GetHardMsg(TYPE_TERM_HARD_LIFE,lifeBuff,sizeof(lifeBuff)))
	{
		APP_ShowMsg(title,"����Ψһ���к�����",3000);
		return 1;
	}
	if((0==API_memcmp(lifeBuff,HARD_SN_STATUS_DOWN,sizeof(lifeBuff)))\
      ||(0==API_memcmp(lifeBuff,HARD_SN_STATUS_OVER,sizeof(lifeBuff)))\
      ||(0==API_memcmp(lifeBuff,HARD_SN_STATUS_WR,sizeof(lifeBuff))))
	{
		return SendCmdPack(title,UART_2,cmds,sizeof(cmds)/sizeof(cmds[0]));
	}
    APP_ShowMsg(title,"�������ڲ���������",3000);
	return 1;
}

int HardKeyCheck(char *title)
{
	u8 Mac[8+1];
	char lifeBuff[6]={0};
	APP_ShowSta(title,"���ڴ���...");
	if(0 > APP_GetHardMsg(TYPE_TERM_HARD_LIFE,lifeBuff,sizeof(lifeBuff)))
	{
		APP_ShowMsg(title,"����Ψһ���к�����",3000);
		return 1;
	}
	if(API_memcmp(lifeBuff,HARD_SN_STATUS_DOWN,sizeof(lifeBuff)))
	{
		APP_ShowMsg(title,"�������к���Կ����",3000);
		return 2;
	}
	if(APP_GetHardSnAndMac(NULL,0,NULL,Mac))
	{
		APP_ShowMsg(title,"����MACʧ��",3000);
		return 3;
	}
	Mac[8]=0x00;
	APP_ShowMsg(title,(char*)Mac,10*1000);
	return 0;
}

int PC_ShowHardSn(char *title)
{
	char HardSnSta[68];
	char ShowBuff[128];
	s16 sLen;
	tHardSN_Key *pSnData;
	sLen=APP_GetHardMsg(TYPE_TERM_HARD_ALL,HardSnSta,sizeof(HardSnSta));
	if(sLen<0)
	{
		APP_ShowMsg(title,"����Ψһ���к�����",3000);
		return 1;
	}
	pSnData=(tHardSN_Key *)HardSnSta;
	API_strcpy(ShowBuff,"TUSN:");
	API_strcat(ShowBuff,MFRS_ID);
	API_strcat(ShowBuff,DEVICE_TYPE);
	API_strcat(ShowBuff,TERM_TYPE);
	sLen=API_strlen(ShowBuff);
	API_strcpy(ShowBuff+sLen,pSnData->HardSN);
	sLen=API_strlen(ShowBuff);
	ShowBuff[sLen++]='\n';
	API_sprintf(ShowBuff+sLen,"���к�״̬:%s",pSnData->Life);
	APP_ShowMsg(title,ShowBuff,10*1000);
	return 0;
}

int APP_Menu_TermSnProsee(char* title)
{
    CMenuItemStru MenuStruPar[]=
	{
		{"���к��ϱ�",       ProduceWriteHardSn},
		{"�������к���Կ",	PC_LoadHardKey},
		{"��������",			PC_OnlineActivate},
		{"�鿴MACֵ",		HardKeyCheck},
		{"�鿴���к�",		PC_ShowHardSn},
	};
	APP_Uart_Init();
	APP_CreateNewMenuByStruct(title,sizeof(MenuStruPar)/sizeof(CMenuItemStru),MenuStruPar,30*1000);
	APP_AddCurrentMenuOtherFun(MENU_OUT_FUN,APP_Uart_End,title);
	return 0;
}





