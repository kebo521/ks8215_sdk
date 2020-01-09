
/**
 * History:
 * ================================================================
 * 2019-11-03 Deng Guozu <dengguozu@szzt.com.cn> created
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>    
#include <sys/stat.h>    
#include <sys/time.h>
#include <sys/ipc.h>
//#include <sys/shm.h> 
//#include <linux/shm.h> 
#include<sys/mman.h>

#include "comm_type.h"
#include "sys_sdk.h" 
#include "esm_sdk.h" 
#include "sdk_print.h" 

//�����ļ�:��ӡ����POSIX �ӿ�





//���� �򿪴�ӡ���豸����������������ӡ����
/*
�򿪴�ӡ���豸����������������ӡ����
����
printertype�����롿
	��ӡ���豸����
	. PRN_REAL�������ӡ�豸��
	. PRN_BMP�������ӡ�豸����ӡ���
	��BMP ��ʽ�����ڱ��ء�
targetname�����롿
	��ӡ�豸Ϊ�����ӡ��ʱ���ò�������ΪNULL��
	��ӡ�豸Ϊ�����ӡ��ʱ��ָ����������ص�
	BMP �ļ���·������ָ���ļ��Ѿ����ڣ��򸲸ǡ�
*/
int OsPrnOpen(unsigned int printertype,const char*targetname)
{
	//int print_handle = open(��/dev/printer��, O_RDWR);
/*
	RET_OK �ɹ�
	ERR_DEV_NOT_EXIST �豸������
	ERR_INVALID_PARAM �Ƿ�����
	ERR_DEV_BUSY �豸��ռ��
	ERR_BATTERY_ABSENT ��ز�����
	ERR_BATTERY_VOLTAGE_TOO_LOW
	//��ص�ѹ�����÷�
	*/
	return ERR_DEV_NOT_EXIST;

}

//���� �رմ�ӡ����
void OsPrnClose(void)
{
	//open(print_handle);

}


//���� ���ô�ӡ����,��մ�ӡ���档
void OsPrnReset(void)
{

}

//���� ���������ӡ����ز�����
/*
����
Width�����롿 ���
Height�����롿 �߶�
*/
int OsPrnSetSize (unsigned int Width,unsigned int Height)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
	return ERR_INVALID_PARAM;

}

//���� ���ô�ӡ����
/*
���� Mode�����롿
. 0�������ӡ��
. 1�������ӡ��
*/
int OsPrnSetDirection (unsigned char Mode)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
	return ERR_INVALID_PARAM;

}

//���� ���ô�ӡ�Ҷȡ
/*�
���� Level
. Level =0��������
. Level =1��ȱʡ�ڶȣ�����ͨ��ӡ����
. Level =2��������
. Level =3��˫��������ӡ��
. Level =4��˫��������ӡ����3 �ĺڶȸ��ߡ�
*/
void OsPrnSetGray(int Level)
{

}

//���� ���ô�ӡ��ࡣ
/*
����
CharSpace : �ּ�࣬��λΪ����(��ǿ�Ƶķǵȿ�������Ч������ְ��������塢̩������)
LineSpace �м�࣬��λΪ����
*/
void OsPrnSetSpace(int CharSpace,int LineSpace)
{

}

//���� �������巴�����ԣ�ȱʡ�����������ӡ��
/* ���� Attr: 0������    1������ */
void OsPrnSetReversal(int Attr)
{

}

//���� �������ұ߾�.
/*����
Left�����롿 ��߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
Right�����롿 �ұ߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
*/
int OsPrnSetIndent (unsigned int Left,unsigned int Right)
{
	//RET_OK �ɹ�
	//ERR_INVALID_PARAM �Ƿ�����
	return ERR_INVALID_PARAM;
}

//���� ��ѯ��ӡ����ǰ״̬���ҽ������������ӡ����
/*����:
RET_OK ��ӡ����������
ERR_PRN_BUSY ��ӡ��æ
ERR_PRN_PAPEROUT ��ӡ��ȱֽ
ERR_PRN_OVERHEAT ��ӡ������
*/
int OsPrnCheck(void)
{
	return ERR_PRN_BUSY;
}

//���� ��ȡ��ǰ�����Ѵ�ӡ�ĵ�������
//���� >=0 ��ǰ�Ѵ�ӡ���и���
int OsPrnGetDotLine(void)
{
	return 0;
}

//���� ѡ���ӡ���塣
/*����: fontname�����롿 ����(�ļ�)����
����:
RET_OK �ɹ�
ERR_FONT_NOT_EXIST ���岻����
ERR_INVALID_PARAM �Ƿ�����
*/
int OsPrnSetFont(const char* fontname)
{
	return ERR_FONT_NOT_EXIST;
}

//���� ���ô�ӡ�����С��
/*����
SingleCodeWidth:�����������ȿ���(�Էǵȿ����������˵������ÿ���ַ��Ŀ�Ȳ�һ�����������),ѡֵ����Ϊ8~64
SingleCodeHeight:����������߶ȿ���,ѡֵ����Ϊ8~64
MultiCodeWidth:�����������ȿ���,ѡֵ����Ϊ12~64
MultiCodeHeight:����������߶ȿ���,ѡֵ����Ϊ12~64
*/
void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight)
{

}

//���� �ڴ�ӡ�������ڣ�ִ����ֽ���ɸ����С�
/*���� Pixel
	ִ����ֽ�ĵ�������
	>0����ֽ
	<0����ֽ
	=0���޶���
*/
void OsPrnFeed(int Pixel)
{

}

//���� ��ʽ������ַ�������ӡ�������ڡ�
/*���� Str�����롿 Ҫ��ӡ���ַ���ָ��*/
void OsPrnPrintf(const char *Str, ...)
{

}

//���� ���ͼ�ε���ӡ�������ڡ�
/*���� Logo�����롿���ӡ��logo ��Ϣ��ָ�룬��Ϣ���Ȳ��ܳ���20000 ���ֽ�*/
void OsPrnPutImage(const unsigned char *Logo)
{

}
//���� ������ӡ������������������ݴ�ӡ������
/*����
	RET_OK ��ӡ����������
	ERR_PRN_BUSY ��ӡ��æ
	ERR_PRN_PAPEROUT ��ӡ��ȱֽ
	ERR_PRN_WRONG_PACKAGE ���ݰ���ʽ����
	ERR_PRN_OVERHEAT ��ӡ������
	ERR_PRN_OUTOFMEMORY ��ӡ���ݹ���
*/
int OsPrnStart(void)
{
	return RET_OK;
}

//���� ��մ�ӡ������
void OsPrnClrBuf(void)
{

}

//���� ���ô�ӡ���Ƿ�Ԥ��ֽ
/*���� cmd �����롿
	1����ӡ��Ԥ��ֽ
	2����ӡ��Ԥ��ֽ
*/
int OsPrnSetParam(unsigned int cmd)
{
	return RET_OK;
}



