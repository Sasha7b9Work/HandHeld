/**********************TS-51A单片机开发板例程************************
*		Copyright (c) 2013,52探索 单片机开发板
*		All rights reserved
*       
*		文件名称：main.c
*		功能描述：采用分页显示的方法显示一大段文字
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

/*
* 功  能：1602的检查是否忙
* 参  数：无
* 返回值：无
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
* 功  能：1602的写命令函数
* 参  数：com:命令字
* 返回值：无
*/
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

/*
* 功  能：1602的写数据函数
* 参  数：Data:要写入的数据
* 返回值：无
*/
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

/*
* 功  能：1602 清除显示内容
* 参  数：无
* 返回值：无
*/
void LCD_Clear(void) 
{ 
	LCD_Write_Com(0x01); 
	delay(5);
}

/*
* 功  能：1602 初始化
* 参  数：无
* 返回值：无
*/
void LCD_Init(void) 
{
	EN = 0;
	LCD_Write_Com(0x38);    /*显示模式设置*/ 
	delay(5); 
	LCD_Write_Com(0x0E);    /*显示关闭*/ 
	delay(5); 
	LCD_Write_Com(0x06);    /*显示清屏*/ 
	delay(5); 
	LCD_Write_Com(0x01);    /*显示光标移动设置*/ 
	delay(5); 
	LCD_Write_Com(0x80);
	delay(5);
}
   
/*------------------------------------------------
                    主函数
------------------------------------------------*/ 
void main(void) 
{
	uchar num;
	
	SMG_CLR();

	LCD_Init();
	LCD_Clear();

	for(num=0;num<16;num++)    //第一屏
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

	LCD_Write_Com(0x01); //清屏
	LCD_Write_Com(0x80);	 //设置字符显示位置指针于第一行

	for(num=0;num<16;num++)    // 第二屏
	{	
		beep=0;
		LCD_Write_Data(table2[num]);
		DelayMs(100);
		beep=1;
		DelayMs(50);
	}

	LCD_Write_Com(0x80+0x40); //设置字符显示位置指针于第二行

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

	for(num=0;num<16;num++)    //第三屏
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

	for(num=0;num<16;num++)   //第四屏
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

	for(num=0;num<16;num++)   //第五屏
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
	
	for(num=0;num<16;num++)   //第六屏
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
