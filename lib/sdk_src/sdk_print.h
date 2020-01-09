
#ifndef _SDK_PRINTF_
#define _SDK_PRINTF_

#define ERR_PRN_BUSY				-3701 //��ӡ��æ
#define ERR_PRN_PAPEROUT			-3702 //��ӡ��ȱֽ
#define ERR_PRN_WRONG_PACKAGE	-3703 //���ݰ���ʽ����
#define ERR_PRN_OVERHEAT			-3704 //��ӡ������
#define ERR_PRN_OUTOFMEMORY		-3705 //Ҫ��ӡ���ݹ���,��������������
#define ERR_PRN_OVERVOLTAGE		-3706 //��ѹ����


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
extern int OsPrnOpen(unsigned int printertype,const char*targetname);

//���� �رմ�ӡ����
extern void OsPrnClose(void);


//���� ���ô�ӡ����,��մ�ӡ���档
extern void OsPrnReset(void);

//���� ���������ӡ����ز�����
/*
����
Width�����롿 ���
Height�����롿 �߶�
*/
extern int OsPrnSetSize (unsigned int Width,unsigned int Height);

//���� ���ô�ӡ����
/*
���� Mode�����롿
. 0�������ӡ��
. 1�������ӡ��
*/
extern int OsPrnSetDirection (unsigned char Mode);

//���� ���ô�ӡ�Ҷȡ
/*�
���� Level
. Level =0��������
. Level =1��ȱʡ�ڶȣ�����ͨ��ӡ����
. Level =2��������
. Level =3��˫��������ӡ��
. Level =4��˫��������ӡ����3 �ĺڶȸ��ߡ�
*/
extern void OsPrnSetGray(int Level);

//���� ���ô�ӡ��ࡣ
/*
����
CharSpace : �ּ�࣬��λΪ����(��ǿ�Ƶķǵȿ�������Ч������ְ��������塢̩������)
LineSpace �м�࣬��λΪ����
*/
extern void OsPrnSetSpace(int CharSpace,int LineSpace);
;
//���� �������巴�����ԣ�ȱʡ�����������ӡ��
/* ���� Attr: 0������    1������ */
extern void OsPrnSetReversal(int Attr);

//���� �������ұ߾�.
/*����
Left�����롿 ��߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
Right�����롿 �ұ߾࣬��Ч��Χ��[0��100]��Ĭ��ֵΪ0��
*/
extern int OsPrnSetIndent (unsigned int Left,unsigned int Right);

//���� ��ѯ��ӡ����ǰ״̬���ҽ������������ӡ����
/*����:
RET_OK ��ӡ����������
ERR_PRN_BUSY ��ӡ��æ
ERR_PRN_PAPEROUT ��ӡ��ȱֽ
ERR_PRN_OVERHEAT ��ӡ������
*/
extern int OsPrnCheck(void);

//���� ��ȡ��ǰ�����Ѵ�ӡ�ĵ�������
//���� >=0 ��ǰ�Ѵ�ӡ���и���
extern int OsPrnGetDotLine(void);

//���� ѡ���ӡ���塣
/*����: fontname�����롿 ����(�ļ�)����
����:
RET_OK �ɹ�
ERR_FONT_NOT_EXIST ���岻����
ERR_INVALID_PARAM �Ƿ�����
*/
extern int OsPrnSetFont(const char* fontname);

//���� ���ô�ӡ�����С��
/*����
SingleCodeWidth:�����������ȿ���(�Էǵȿ����������˵������ÿ���ַ��Ŀ�Ȳ�һ�����������),ѡֵ����Ϊ8~64
SingleCodeHeight:����������߶ȿ���,ѡֵ����Ϊ8~64
MultiCodeWidth:�����������ȿ���,ѡֵ����Ϊ12~64
MultiCodeHeight:����������߶ȿ���,ѡֵ����Ϊ12~64
*/
extern void OsPrnSelectFontSize(int SingleCodeWidth,int SingleCodeHeight,int MultiCodeWidth,int MultiCodeHeight);

//���� �ڴ�ӡ�������ڣ�ִ����ֽ���ɸ����С�
/*���� Pixel
	ִ����ֽ�ĵ�������
	>0����ֽ
	<0����ֽ
	=0���޶���
*/
extern void OsPrnFeed(int Pixel);

//���� ��ʽ������ַ�������ӡ�������ڡ�
/*���� Str�����롿 Ҫ��ӡ���ַ���ָ��*/
extern void OsPrnPrintf(const char *Str, ...);

//���� ���ͼ�ε���ӡ�������ڡ�
/*���� Logo�����롿���ӡ��logo ��Ϣ��ָ�룬��Ϣ���Ȳ��ܳ���20000 ���ֽ�*/
extern void OsPrnPutImage(const unsigned char *Logo);

//���� ������ӡ������������������ݴ�ӡ������
/*����
	RET_OK ��ӡ����������
	ERR_PRN_BUSY ��ӡ��æ
	ERR_PRN_PAPEROUT ��ӡ��ȱֽ
	ERR_PRN_WRONG_PACKAGE ���ݰ���ʽ����
	ERR_PRN_OVERHEAT ��ӡ������
	ERR_PRN_OUTOFMEMORY ��ӡ���ݹ���
*/
extern int OsPrnStart(void);

//���� ��մ�ӡ������
extern void OsPrnClrBuf(void);

//���� ���ô�ӡ���Ƿ�Ԥ��ֽ
/*���� cmd �����롿
	1����ӡ��Ԥ��ֽ
	2����ӡ��Ԥ��ֽ
*/
extern int OsPrnSetParam(unsigned int cmd);

#endif
