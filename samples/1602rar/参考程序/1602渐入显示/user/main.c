/**********************TS-51A单片机开发板例程************************
*		Copyright (c) 2013,52探索 单片机开发板
*		All rights reserved
*       
*		文件名称：main.c
*		功能描述：一串字符从右侧移入1602的显示区。
* 
*		当前版本：1.0
*		作    者：52探索
*       完成日期：2013-5-29
*
*		取代版本：无
*       改进内容：无
*
*		使用环境：TS-51A开发板 + STC89C52 + 11.0592M晶振 + Keil C51 V9.0 
*       
*		淘宝地址：http://shop104208028.taobao.com/
*		QQ      : 10903659
*		QQ群    ：336397723  336398729   336398900
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

sbit RS = P1^3;   //定义端口 
sbit RW = P1^4;
sbit EN = P1^5;
sbit wx = P2^6;
sbit dx = P2^7;

uchar table1[] = "shop104208028.";
uchar table2[] = "taobao.com";

/*
* 功  能：延时，若干毫秒
* 参  数：毫秒数
* 返回值：无
*/
void DelayMs(unsigned int i)	//一个延时函数，这个函数在11.0592M晶振下的延时时间大概为1ms
{
	unsigned int j,k;

	for(j=i; j>0; j--)
		for(k=114; k>0; k--);
}

/*
* 功  能：延时
* 参  数：延时的数量
* 返回值：无
*/
void delay(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=10;b>0;b--); 
}

/*
* 功  能：清除数码管的显示内容
* 参  数：无
* 返回值：无
*/
void SMG_CLR( void )
{
	P0 = 0x00;	 	//发送要显示的段码
	dx = 1;
	dx = 0;
	
	P0 = 0x00;		//发送要显示的位码,只显示一位数字
	wx = 1;
	wx = 0;
}

/*------------------------------------------------
              判忙函数
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
              写入命令函数
------------------------------------------------*/
void LCD_Write_Com(unsigned char com) 
{  
	while(LCD_Check_Busy()); //忙则等待
	RS_CLR; 
	RW_CLR; 
	EN_SET; 
	DataPort = com; 
	_nop_(); 
	EN_CLR;
}
/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
	while(LCD_Check_Busy()); //忙则等待
	RS_SET; 
	RW_CLR; 
	EN_SET; 
	DataPort = Data; 
	_nop_();
	EN_CLR;
}

/*------------------------------------------------
                清屏函数
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	LCD_Write_Com(0x01); 
	delay(5);
}

/*------------------------------------------------
              初始化函数
------------------------------------------------*/
void LCD_Init(void) 
{
	LCD_Write_Com(0x38);    /*显示模式设置*/ 
	delay(5); 
	LCD_Write_Com(0x0F);    /*显示关闭*/ 
	delay(5); 
	LCD_Write_Com(0x06);    /*显示清屏*/ 
	delay(5); 
	LCD_Write_Com(0x01);    /*显示光标移动设置*/ 
	delay(5);
}
   
/*------------------------------------------------
                    主函数
------------------------------------------------*/ 
void main(void) 
{ 
	uchar i;

	SMG_CLR();

	LCD_Init();
	LCD_Clear();

	LCD_Write_Com(0x80+16);	 //将第一个字符写在向右偏移17个字符处，为后面的由右向左划入做准备。
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
		LCD_Write_Com(0x18); //左移
		DelayMs(500);
	}

	while(1);
}
