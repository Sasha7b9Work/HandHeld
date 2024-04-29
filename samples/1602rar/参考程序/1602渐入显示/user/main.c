/**********************TS-51A��Ƭ������������************************
*		Copyright (c) 2013,52̽�� ��Ƭ��������
*		All rights reserved
*       
*		�ļ����ƣ�main.c
*		����������һ���ַ����Ҳ�����1602����ʾ����
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
sbit wx = P2^6;
sbit dx = P2^7;

uchar table1[] = "shop104208028.";
uchar table2[] = "taobao.com";

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

/*------------------------------------------------
              ��æ����
------------------------------------------------*/
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
/*------------------------------------------------
              д�������
------------------------------------------------*/
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
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
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

/*------------------------------------------------
                ��������
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	LCD_Write_Com(0x01); 
	delay(5);
}

/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
{
	LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
	delay(5); 
	LCD_Write_Com(0x0F);    /*��ʾ�ر�*/ 
	delay(5); 
	LCD_Write_Com(0x06);    /*��ʾ����*/ 
	delay(5); 
	LCD_Write_Com(0x01);    /*��ʾ����ƶ�����*/ 
	delay(5);
}
   
/*------------------------------------------------
                    ������
------------------------------------------------*/ 
void main(void) 
{ 
	uchar i;

	SMG_CLR();

	LCD_Init();
	LCD_Clear();

	LCD_Write_Com(0x80+16);	 //����һ���ַ�д������ƫ��17���ַ�����Ϊ�����������������׼����
	delay(10);

	for(i=0; i<14; i++)
	{
		LCD_Write_Data(table1[i]);
		delay(10);		
	}
	
	LCD_Write_Com(0xc0+16);
	delay(10);

	for(i=0; i<10; i++)
	{
		LCD_Write_Data(table2[i]);
		delay(10);		
	}
	
	for(i=0; i<16; i++)
	{
		LCD_Write_Com(0x18); //����
		DelayMs(500);
	}

	while(1);
}
