
#ifndef _INPUT_HAND_
#define _INPUT_HAND_

typedef int (*DefAbsAnalytical)(u16*,u16*); 

extern DefAbsAnalytical pAbsAnalytical;


typedef enum 
{
	K_D 			='.',			//!< С����
	K_0 			='0',			//!< ����0
	K_1 			='1',			//!< ����1
	K_2 			='2',			//!< ����2
	K_3 			='3',			//!< ����3
	K_4 			='4',			//!< ����4
	K_5 			='5',			//!< ����5
	K_6 			='6',			//!< ����6
	K_7 			='7',			//!< ����7
	K_8 			='8',			//!< ����8
	K_9 			='9',			//!< ����9
	K_STAR			='*',			//!< �Ǻż�
	K_POUND 		='#',			//!< ���ż�
			
	K_UP			=0x01,			//!< �Ϸ����
	K_DOWN			=0x02,			//!< �·����
	K_LEFT			=0x03,			//!< �����
	K_RIGHT 		=0x04,			//!< �ҷ����
									
	K_MENU			=0x05,			//!< �˵�	
	K_IME			=0x06,			//!< ���뷨 
	K_SYM			=0x07,			//!< ����	
	K_BACK			=0x08,			//!< ����	
																			
	K_CANCEL		=0x0C,			//!< ȡ��
	K_OK			=0x0D,			//!< ȷ��
	K_DEL			=0x0E,			//!< ɾ��
	K_QUIT			=0x0F,			//!< �˳�
									
	K_FUNC			=0x10,			//!< ����
	K_F1			=0x11,			//!< ����1
	K_F2			=0x12,			//!< ����2
	K_F3			=0x13,			//!< ����3
	K_F4			=0x14,			//!< ����4
									
	K_PWR			=0x91,			//!< ��Դ
									
	K_INVALID		=0x00			//!< ��Ч����
}KEY_VAL;							//V3��������

extern void Start_HandInput(void);
extern void Stop_HandInput(void);





#endif
