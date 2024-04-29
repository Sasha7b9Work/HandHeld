/**********************TS-51A��Ƭ������������************************
*		Copyright (c) 2013,52̽�� ��Ƭ��������
*		All rights reserved
*       
*		�ļ����ƣ�main.c
*		�������������÷�ҳ��ʾ�ķ�����ʾһ�������
* 
*		��ǰ�汾��1.0
*		��    �ߣ�52̽��
*       ������ڣ�2013-5-29
*
*		ȡ���汾����
*       �Ľ����ݣ���
*
*		ʹ�û�����TS-51A������ + STC89C52 + 11.0592M���� + Keil C51 V9.0 
*       
*		�Ա���ַ��http://shop104208028.taobao.com/
*		QQ      : 10903659
*		QQȺ    ��336397723  336398729   336398900
******************************************************************/

#include <REGX52.H>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define RS_CLR RS = 0 
#define RS_SET RS = 1

#define RW_CLR RW = 0 
#define RW_SET RW = 1 

#define EN_CLR EN = 0
#define EN_SET EN = 1

#define DataPort P0

sbit RS = P1^3;   //����˿� 
sbit RW = P1^4;
sbit EN = P1^5;

sbit dx = P2^7;
sbit wx = P2^6;
sbit beep=P2^2;

uchar code table []="I want to bring ";
uchar code table1[]="out the secret  ";
uchar code table2[]="of nature and   ";
uchar code table3[]="apply them for  ";
uchar code table4[]="the happiness of";
uchar code table5[]="man.I don't know";
uchar code table6[]="of any better s-";
uchar code table7[]="-ervice to offer";
uchar code table8[]="for the short t-";
uchar code table9[]="-ime we are in  ";
uchar code table10[]="the world.      ";
uchar code table11[]="---Thomas Edison";

/*
* ��  �ܣ���ʱ�����ɺ���
* ��  ����������
* ����ֵ����
*/
void DelayMs(unsigned int i)	//һ����ʱ���������������11.0592M�����µ���ʱʱ����Ϊ1ms
{
	unsigned int j,k;

	for(j=i; j>0; j--)
		for(k=114; k>0; k--);
}

/*
* ��  �ܣ���ʱ
* ��  ������ʱ������
* ����ֵ����
*/
void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}

/*
* ��  �ܣ��������ܵ���ʾ����
* ��  ������
* ����ֵ����
*/
void SMG_CLR( void )
{
	P0 = 0x00;	 	//����Ҫ��ʾ�Ķ���
	dx = 1;
	dx = 0;
	
	P0 = 0x00;		//����Ҫ��ʾ��λ��,ֻ��ʾһλ����
	wx = 1;
	wx = 0;
}

/*
* ��  �ܣ�1602�ļ���Ƿ�æ
* ��  ������
* ����ֵ����
*/
bit LCD_Check_Busy(void) 
{ 
	DataPort = 0xFF; 
	RS_CLR; 
	RW_SET; 
	EN_CLR; 
	_nop_(); 
	EN_SET;
	
	return (bit)(DataPort & 0x80);
}

/*
* ��  �ܣ�1602��д�����
* ��  ����com:������
* ����ֵ����
*/
void LCD_Write_Com(unsigned char com) 
{  
	while(LCD_Check_Busy()); //æ��ȴ�
	RS_CLR; 
	RW_CLR; 
	EN_SET; 
	DataPort = com; 
	_nop_(); 
	EN_CLR;
}

/*
* ��  �ܣ�1602��д���ݺ���
* ��  ����Data:Ҫд�������
* ����ֵ����
*/
void LCD_Write_Data(unsigned char Data) 
{ 
	while(LCD_Check_Busy()); //æ��ȴ�
	RS_SET; 
	RW_CLR; 
	EN_SET; 
	DataPort = Data; 
	_nop_();
	EN_CLR;
}

/*
* ��  �ܣ�1602 �����ʾ����
* ��  ������
* ����ֵ����
*/
void LCD_Clear(void) 
{ 
	LCD_Write_Com(0x01); 
	delay(5);
}

/*
* ��  �ܣ�1602 ��ʼ��
* ��  ������
* ����ֵ����
*/
void LCD_Init(void) 
{
	EN = 0;
	LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
	delay(5); 
	LCD_Write_Com(0x0E);    /*��ʾ�ر�*/ 
	delay(5); 
	LCD_Write_Com(0x06);    /*��ʾ����*/ 
	delay(5); 
	LCD_Write_Com(0x01);    /*��ʾ����ƶ�����*/ 
	delay(5); 
	LCD_Write_Com(0x80);
	delay(5);
}
   
/*------------------------------------------------
                    ������
------------------------------------------------*/ 
void main(void) 
{
	uchar num;
	
	SMG_CLR();

	LCD_Init();
	LCD_Clear();

	for(num=0;num<16;num++)    //��һ��
	{
		beep=0;
		LCD_Write_Data(table[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40);

	for(num=0;num<16;num++)
	{
		beep=0;
		LCD_Write_Data(table1[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x01); //����
	LCD_Write_Com(0x80);	 //�����ַ���ʾλ��ָ���ڵ�һ��

	for(num=0;num<16;num++)    // �ڶ���
	{	
		beep=0;
		LCD_Write_Data(table2[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40); //�����ַ���ʾλ��ָ���ڵڶ���

	for(num=0;num<16;num++)
	{	
		beep=0;
		LCD_Write_Data(table3[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80);
	LCD_Write_Com(0x01);

	for(num=0;num<16;num++)    //������
	{
		beep=0;
		LCD_Write_Data(table4[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40);

	for(num=0;num<16;num++)
	{
		beep=0;
		LCD_Write_Data(table5[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x01);
	LCD_Write_Com(0x80);

	for(num=0;num<16;num++)   //������
	{
		beep=0;
		LCD_Write_Data(table6[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40);

	for(num=0;num<16;num++)
	{
		beep=0;
		LCD_Write_Data(table7[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x01);
	LCD_Write_Com(0x80);

	for(num=0;num<16;num++)   //������
	{
		beep=0;
		LCD_Write_Data(table8[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40);

	for(num=0;num<16;num++)
	{
		beep=0;
		LCD_Write_Data(table9[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x01);
	LCD_Write_Com(0x80);
	
	for(num=0;num<16;num++)   //������
	{
		beep=0;
		LCD_Write_Data(table10[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40);

	for(num=0;num<16;num++)
	{
		beep=0;
		LCD_Write_Data(table11[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	while(1);
}
