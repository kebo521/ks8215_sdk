
#ifndef _INPUT_HAND_
#define _INPUT_HAND_

typedef int (*DefAbsAnalytical)(u16*,u16*); 

extern DefAbsAnalytical pAbsAnalytical;


typedef enum 
{
	K_D 			='.',			//!< 小数点
	K_0 			='0',			//!< 数字0
	K_1 			='1',			//!< 数字1
	K_2 			='2',			//!< 数字2
	K_3 			='3',			//!< 数字3
	K_4 			='4',			//!< 数字4
	K_5 			='5',			//!< 数字5
	K_6 			='6',			//!< 数字6
	K_7 			='7',			//!< 数字7
	K_8 			='8',			//!< 数字8
	K_9 			='9',			//!< 数字9
	K_STAR			='*',			//!< 星号键
	K_POUND 		='#',			//!< 井号键
			
	K_UP			=0x01,			//!< 上方向键
	K_DOWN			=0x02,			//!< 下方向键
	K_LEFT			=0x03,			//!< 左方向键
	K_RIGHT 		=0x04,			//!< 右方向键
									
	K_MENU			=0x05,			//!< 菜单	
	K_IME			=0x06,			//!< 输入法 
	K_SYM			=0x07,			//!< 符号	
	K_BACK			=0x08,			//!< 返回	
																			
	K_CANCEL		=0x0C,			//!< 取消
	K_OK			=0x0D,			//!< 确认
	K_DEL			=0x0E,			//!< 删除
	K_QUIT			=0x0F,			//!< 退出
									
	K_FUNC			=0x10,			//!< 功能
	K_F1			=0x11,			//!< 功能1
	K_F2			=0x12,			//!< 功能2
	K_F3			=0x13,			//!< 功能3
	K_F4			=0x14,			//!< 功能4
									
	K_PWR			=0x91,			//!< 电源
									
	K_INVALID		=0x00			//!< 无效按键
}KEY_VAL;							//V3按键定义

extern void Start_HandInput(void);
extern void Stop_HandInput(void);





#endif
