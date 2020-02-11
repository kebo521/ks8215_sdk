
#ifndef _SDK_ICC_
#define _SDK_ICC_

//==================IC������==============================
//IC ��ͨ���ţ�
#define ICC_USER_SLOT	0	//	 �û���
#define ICC_SAM1_SLOT 1	//SAM ������ 1
#define ICC_SAM2_SLOT 2	//SAM ������ 2
#define ICC_SAM3_SLOT 3	//SAM ������ 3
#define ICC_SAM4_SLOT 4	//SAM ������ 4

//	IC �������б�
#define	ERR_SCI_HW_NOCARD		-2800 	//û�п�Ƭ
#define	ERR_SCI_HW_STEP		-2801	//��������ʱû�г�ʼ�����ȸ�λʱδ�ϵ硣
#define	ERR_SCI_HW_PARITY		-2802	//��żУ��ʧ��
#define	ERR_SCI_HW_TIMEOUT	-2803	//��ʱ
#define	ERR_SCI_TCK			-2804	//TCK ����
#define	ERR_SCI_ATR_TS		-2810	//ATR TS ����
#define	ERR_SCI_ATR_TA1		-2811	//ATR TA1 ����
#define	ERR_SCI_ATR_TD1		-2812	//ATR TD1 ����
#define	ERR_SCI_ATR_TA2 -2813 //ATR TA2 ����
#define	ERR_SCI_ATR_TB1 -2814 //ATR TB1 ����
#define	ERR_SCI_ATR_TB2 -2815 //ATR TB2 ����
#define	ERR_SCI_ATR_TC2 -2816 //ATR TC2 ����
#define	ERR_SCI_ATR_TD2 -2817 //ATR TD2 ����
#define	ERR_SCI_ATR_TA3 -2818 //ATR TA3 ����
#define	ERR_SCI_ATR_TB3 -2819 //ATR TB3 ����
#define	ERR_SCI_ATR_TC3 -2820 //ATR TC3 ����
#define	ERR_SCI_T_ORDER -2821 //Э�鲻�� T0 �� T1
#define	ERR_SCI_PPS_PPSS -2830 //PPS �ϵ� PPSS ����
#define	ERR_SCI_PPS_PPS0 -2831 //PPS �ϵ� PPS0 ����
#define	ERR_SCI_PPS_PCK -2832 //PPS �ϵ� ATR PCK ����
#define	ERR_SCI_T0_PARAM -2840 //�ŵ� 0 �ϵĴ��������̫����
#define	ERR_SCI_T0_REPEAT -2841 //�ŵ�0���ַ��ظ������������
#define	ERR_SCI_T0_PROB -2842 //T0 ���������ֽڴ���
#define	ERR_SCI_T1_PARAM -2850 //�� T1 �д��������̫��
#define	ERR_SCI_T1_BWT -2851 //T1 BWT ����
#define	ERR_SCI_T1_CWT -2852 //T1 CWT ����
#define	ERR_SCI_T1_BREP -2853 //T1 ̫����ظ�
#define	ERR_SCI_T1_LRC -2854 //T1LRC ����
#define	ERR_SCI_T1_NAD -2855 //T1NAD ����
#define	ERR_SCI_T1_LEN -2856 //T1 LEN ����
#define	ERR_SCI_T1_PCB -2857 //T1 PCB ����
#define	ERR_SCI_T1_SRC -2858 //T1SRC ����
#define	ERR_SCI_T1_SRL -2859 //T1SRL ����
#define	ERR_SCI_T1_SRA -2860 //T1SRA ����
#define	ERR_SCI_PARAM -2880 //�Ƿ�����

/*
2. LE �� LC �����ʹ��������£� ? 
LC=0��LE=0�����޷�������Ҳ���������ݷ��أ� ? 
LC=0��LE>0���޷������ݵ����������ݷ��ء������ʵ��Ӧ�����ն��������ص����ݸ���δ֪��Ӧ�� LE=256������Ϊȷ������ֵ�� ? 
LC>0��LE=0���з������ݵ����������ݷ��أ� ? 
LC>0��LE>0���з������������������ݷ��ء������ʵ��Ӧ�����ն��������ص����ݸ���δ֪��Ӧ�� LE=256������Ϊȷ������ֵ��
*/
typedef struct
{
	unsigned char Cmd[4]; /*CLA, INS, P1, P2*/
	int LC; /*���͵� IC ���� DataIn ��Ч���ݳ��� */
	unsigned char DataIn[512]; /*���͵� IC ��������*/
	int LE; /*�����������ݵĳ���*/
}ST_APDU_REQ;

typedef struct
{
	unsigned char SWA; /*IC ��״̬�� 1*/
	unsigned char SWB; /*IC ��״̬�� 2*/
	unsigned short LenOut; /* ʵ�ʴ� IC �����ص����ݳ���*/
	unsigned char DataOut[512]; /*�� IC �����ص�����ָ��*/
}ST_APDU_RSP;


//���� ��IC �������豸.
extern int OsIccOpen(int Slot);

//���� ���ָ���Ŀ����Ƿ��п���
extern int OsIccDetect(int Slot);

//���� ��ʼ�� IC ���豸��
/*
Option:	(λ 0~1)����ѹѡ��
				00 - 5V�� 01 - 1.8V��10 - 3V
		(λ 2)��ʾ�� PPS Э��֧�֣�
			0 - ��֧�֣�
			1 �C ֧�֣�
		(λ 3~4)��ʾ�ϵ縴λʹ�����ʣ�
			00 - ��׼���� 9600
			10 - �ı����� 38400
		(λ 5)��ʾ֧�ֵĹ淶���ͣ�
			0 - EMV �淶
			1 - ISO7816 �淶
			�˱�����ָ���淶Ϊ EMV ģʽ����ô�ϵ�
			���ʱ������Ч��Ĭ��ʹ�ñ�׼���ʡ�
		(λ 6 ~31)������
			Option ȱʡ����Ϊ 0(����5V���� PPS����׼��
			�ʺ���ѭ EMVx)
Atr:	1. ��Ƭ��λӦ��(Answer To Reset)����Ƭ��෵�� 34 �ֽڵ���Ӧ���ݡ�
		2. ������Ϊ����λӦ�����ݳ���(1 �ֽ�)+��λӦ������
*/
extern int OsIccInit(int Slot,unsigned long Option,unsigned char *Atr);

//���� �� IC �������������
/*
CtrlFlag:
	1. Bit0 ��ʾ T=0 Э�����Ƿ��Զ�����
			GET RESPONSE ָ�
			1-��
			0-��
	2. Bit1~Bit31 ����
*/
extern int OsIccExchange(int Slot,int CtrlFlag,const ST_APDU_REQ *ApduReq,ST_APDU_RSP *ApduRsp);

//�ر� IC ���豸��
extern int OsIccClose(int Slot);



//================================================��Ƶ������=================================
//��Ƶ����������
#define	PCD_ERR_PAR_FLAG 				-2901 //У�����
#define	PCD_ERR_CRC_FLAG 				-2902 //CRC ����
#define	PCD_ERR_WTO_FLAG 				-2903 //��ʱ���޿�
#define	PCD_ERR_COLL_FLAG 			-2904 //�࿨��ͻ
#define	PCD_ERR_ECD_FLAG 				-2905 //֡��ʽ����
#define	PCD_ERR_EMD_FLAG 				-2906 //����
#define	PCD_ERR_COM_FLAG 				-2907 //оƬ����,�޷���ȷͨ��
#define	PCD_ERR_AUT_FLAG 				-2908 //M1 ��֤����
#define	PCD_ERR_TRANSMIT_FLAG		-2909 //�������
#define	PCD_ERR_PROTOCOL_FLAG		-2910 //Э�����
#define	PCD_ERR_PARAMFILE_FLAG		-2911 //�����ļ�������
#define	PCD_ERR_USER_CANCEL			-2912 //�û�ȡ������
#define	PCD_ERR_CARRIER_OBTAIN_FLAG	-2913 //�ز�δ���
#define	PCD_ERR_CONFIG_FLAG			-2914 //���üĴ������ɹ�
#define	PCD_ERR_RXLEN_EXCEED_FLAG	-2915 //��Ƭ�������ݳ��ȳ����趨���ճ���
#define	PCD_ERR_NOT_ALLOWED_FLAG	-2951 //���������ȡֵ������
#define	PCD_CHIP_ABNORMAL 			-2952 //оƬ�����ڻ��쳣
#define	PCD_CHIP_NOT_OPENED			-2953 //ģ��δ��
#define	PCD_CHIP_CARDEXIST 			-2954 //��Ƭδ�ƿ�
#define	PCD_ERR_NOT_IDLE_FLAG		-2955 //��Ƭû���� idle ̬
#define	PCD_ERR_NOT_POLLING_FLAG	-2956 //��Ƭû�н��� POLLING
#define	PCD_ERR_NOT_WAKEUP_FLAG		-2957 //��Ƭû�л���
#define	PCD_ERR_NOT_ACTIVE_FLAG		-2958 //��Ƭδ����
#define	PCD_ERR_NOT_SUPPORT			-2959 //оƬ��֧��
//ERR_BATTERY_VOLTAGE_TOO_LOW-1024 ��ص�ѹ����
typedef struct pcd_user_t{
	unsigned char wait_retry_limit_w; /* S(WTX)��Ӧ���ʹ���д������*/
	unsigned int wait_retry_limit_val; /* S(WTX)��Ӧ������Դ���*/
	unsigned char check_cancel_key_w; /*��Ӧȡ����д������*/
	unsigned char check_cancel_key_val;  /* 0��ʾ����Ӧȡ������1��ʾ��Ӧȡ����*/
	int (*check_cancel_key_function)(void); /*����Ƿ���ȡ�����������������check_cancel_key_w=1��check_cancel_key_val=1��������Ƶ�����׹����л����check_cancel_key_function()�����check_cancel_key_function()����0����ʾû�а���ȡ������������ط�0����ʾ�Ѱ���ȡ��������ǿ���˳�����*/
	unsigned char os_picc_transfer_set_w; /*1��ʾos_picc_transfer_set_valֵ��Ч��0��ʾos_picc_transfer_set_valֵ��Ч*/
	unsigned char os_picc_transfer_set_val; /*OsPiccTransfer�շ�����,
													Bit0=0����ʾ���ͽ���CRC,
													Bit0=1����ʾ����ʹ��CRC,
													Bit1=0����ʾ���ս���CRC,
													Bit1=1����ʾ����ʹ��CRC*/
	unsigned char anti_interference_flag; /*Ѱ�������Ź�������; 1-����Ѱ�������Ź��ܣ�0-������Ѱ�������Ź���*/
	unsigned char protocol_layer_fwt_set_w; /*1��ʾprotocol_layer_fwt_set_valֵ��Ч��0��ʾprotocol_layer_fwt_set_valֵ��Ч*/
	unsigned int protocol_layer_fwt_set_val;  /*����Э����֡�ȴ�ʱ��FWTֵ*/
	unsigned char os_picc_transfer_rxlen_set_w;   /*1��ʾos_picc_transfer_rxlen_set_valֵ��Ч��0��ʾos_picc_transfer_rxlen_set_valֵ��Ч*/
	unsigned int os_picc_transfer_rxlen_set_val;	/*OsPiccTransfer��˫���鴫�����������ɽ������ݳ���ֵ*/
	unsigned char reserved[44];  /*�����ֽڣ����ڽ�����չ*/
}PCD_USER_ST;


//���� PCD ģ���ϵ紦��ʹģ�����׼������״̬��
extern int OsPiccOpen(void);

//���� PCD ģ���µ紦��
extern int OsPiccClose(void);

//���� �ز���λ��
extern int OsPiccResetCarrier(void);

//���� Ѱ������ʱֻ������A���͡�B�����������͵���Ѱ��
/*pcPiccType�������
		Ѱ����Ƭ���ͣ�
		��A�� - A �� 
		��B�� - B ��
pucATQx �������
		Ѱ��ʱ��ƬӦ�����ݣ�
		A ��Ϊ 2 �ֽ�
		B ��Ϊ 12 �ֽ�
*/
extern int OsPiccPoll(char *pcPiccType, unsigned char *pucATQx);

//�Կ�Ƭ���з���ͻ��ѡ��
/*
pcPiccType�����롿
		Ѱ����Ƭ���ͣ�
		. ��A�� - A ��
		. ��B�� - B ��
pucUID�������
		��Ƭ��Ψһ��ʶ��
		. A ����Ϊ4��7 ��10 �ֽ�
		. B ��Ϊ4 �ֽ�
ucATQ0�����롿 �˲���δʹ��
pucSAK�������
	ѡ��ʱ��ƬӦ�����ݣ�����Ϊ1 �ֽڡ�
	SAKΪA�������һ��ѡ�������Ӧ�����ݣ�
	B �����Դ˲���
*/
extern int OsPiccAntiSel(const char pcPiccType,unsigned char *pucUID, const unsigned char ucATQ0, unsigned char*pucSAK);

//���� �Կ�Ƭ���м����
/*
pcPiccType�����롿
	Ѱ����Ƭ���ͣ�
		��A�� - A ��
		��B�� - B ��
pucRATS�������
	���Ƭ��Ӧ�����ݣ�
		A ��ʱ��pucRATS Ϊ��ӦATS �����Ӧ������
		B ��ʱ��pucRATS Ϊ��ӦATTRIB �����Ӧ������
*/
extern int OsPiccActive(const char pcPiccType,unsigned char *pucRATS);

//���� ����ISO14443-4 ��ָ���İ�˫��ͨ��Э��ʵ��͸������/���չ��ܡ�
/*
pucTxBuff�����롿 ���������ݻ�����
iTxLen �����롿 ���������ݵĳ��ȣ����ֽ�Ϊ��λ
pucRxBuff������� ���տ�Ƭ��Ӧ���ݵĻ�����
piRxLen������� ���յ��Ŀ�Ƭ�����ֽ�������
*/
extern int OsPiccTransfer(const unsigned char* pucTxBuff,int iTxLen,unsigned char* pucRxBuff,int * piRxLen);

//���� ����EMV ģʽ�����ƿ�������
extern int OsPiccRemove(void);

//���� ��֤Mifare ����
/*
uid�����롿 ��ƬID������Ϊ4 ���ֽڡ�
blk no�����롿 ���
group�����롿 ��֤�������ͣ�ȡֵΪ��A����B����
psw �����롿 ��֤���룬����Ϊ6 ���ֽڡ�
*/
extern int OsMifareAuthority(unsigned char *uid,unsigned char blk_no,unsigned char group,unsigned char *psw);

//���� ��Mifare ��ָ���Ŀ���ж�/д���������Mifare ��ָ�����ݿ���г�/��ֵ/���ݲ������������ֵ�����µ���һ��ָ�������ݿ��С�
/*
ucOpCode�����롿	
	��r��/��R����������
	��w��/��W����д����
	��+������ֵ
	��-������ֵ
	��>����ת��/���ݲ���
ucSrcBlkNo�����롿 ָ�����ʵĿ��
pucVal������/�����
	1. ��Ϊ��������pucVal ��������ݣ�ָ��Ļ�����Ϊ16 �ֽڣ�
	2. ��Ϊд������pucVal ��������ݣ�ָ��Ļ�����Ϊ16 �ֽڣ�
	3. ��Ϊ��ֵ���߼�ֵ������pucVal Ϊ�������������ַ��ָ��Ļ�����Ϊ4 �ֽڣ�
	4. ��Ϊת�������pucVal ��ʵ�����壬�������ָ�벻��ΪNULL��
ucDesBlkNo�����롿
	ָ�������������д�뵽�Ŀ��(��д��ʱ����ֵΪNULL)
*/
extern int OsMifareOperate(unsigned charucOpCode,unsigned charucSrcBlkNo,unsigned char* pucVal,unsigned charucDesBlkNo);

//���� ��FeliCa �����г�ʼ�����á�
/*ucSpeed�����롿
	�����뿨Ƭ�����Ĵ������ʣ�
		1��424Kbp
		����ֵ��212Kbps
ucModInvert�����롿
	����FeliCa ���Ʒ�ʽ��
		1������������
		����ֵ������������
*/
extern int OsPiccInitFelica(unsigned char ucSpeed,unsigned char ucModInvert);

//���� ��ָ����ͨ���ϣ���Ƭ����APDU ��ʽ�����ݣ���������Ӧ��
/*
cid �����롿����ָ����Ƭ�߼�ͨ���š���ȡֵ��ΧΪ0~14��ȡֵ��Ϊ0��
ApduReq �����롿���͸�PICC ���������ݽṹST_APDU_REQ
ApduRsp ���������PICC �����ص����ݽṹST_APDU_RSP
*/
extern int OsPiccIsoCommand(int cid,ST_APDU_REQ*ApduReq,ST_APDU_RSP*ApduRsp);

//���� �����û����á�
//���� pcd_user_config�����롿 �û����ýṹ��PCD_USER_ST
extern int OsPiccSetUserConfig(PCD_USER_ST *pcd_user_config);

//���� ��ȡ�û����á�
//���� pcd_user_config������� �û����ýṹ��PCD_USER_ST
extern int OsPiccGetUserConfig(PCD_USER_ST *pcd_user_config);

//���� Ѱ����������A����B���͡�V�����������͵���Ѱ��
/*
����
pcPiccType�������
Ѱ����Ƭ���ͣ�
. ��A�� - A ��
. ��B�� - B ��
. ��V�� �C V ��
pucATQx �������
Ѱ��ʱ��ƬӦ�����ݣ�
. A ��Ϊ2 �ֽ�
. B ��Ϊ12 �ֽ�
. V ��Ϊ2 �ֽ�
pucSendData�����롿
�������ֽڣ�
. "\x01\x00\x00\x00"����ʾTerminal in VAS App OR Payment Mode
. "\x01\x00\x00\x01"����ʾTerminal in VAS App AND Payment Mode
. "\x01\x00\x00\x02"����ʾ Terminal in VAS App Only Mode
. "\x01\x00\x00\x03" �� ��ʾTerminal in Payment Mode Only
*/
extern int OsPiccApplePoll(char *pcPiccType,unsigned char *pucATQx,unsigned char *pucSendData);

//���� �ر��ز���
extern int OsPiccOffCarrier(void);

//���� ��ISO15693 �����г�ʼ�����á�
/*
���� ucDataCodeMode�����롿
�����뿨Ƭ�����Ĵ������ʣ�
. 0��26.48 kbits/s
. ����ֵ���ݲ�֧��
*/
extern int OsPiccInitIso15693(unsigned char ucDataCodeMode);


#endif
