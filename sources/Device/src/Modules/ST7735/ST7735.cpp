// 2024/03/01 22:47:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Hardware/Timer.h"
#include "Display/Display.h"
#include <gd32e23x.h>


namespace ST7735
{
    static PinOut pinDC(GPIOA, GPIO_PIN_5);       // PA5  15
    static PinOut pinRES(GPIOA, GPIO_PIN_8);      // PA8  29
    static PinOut pinBKG(GPIOA, GPIO_PIN_9);      // PA9  30
    static PinOut pinSCL(GPIOA, GPIO_PIN_4);      // PA4  14
    static PinOut pinSDA(GPIOA, GPIO_PIN_6);      // PA6  16

    static void SendByte(uint8 byte)
    {
        for (int bit = 7; bit >= 0; bit--)
        {
            (byte & (1 << bit)) == 0 ? pinSDA.ToLow() : pinSDA.ToHi();

            pinSCL.ToHi();

            pinSCL.ToLow();
        }
    }

    static void SendData16(uint16 word)
    {
        pinDC.ToHi();

        SendByte((uint8)(word >> 8));
        SendByte((uint8)word);
    }

//    static void SendCommand(uint8);
//    static void SendData8(uint8);
//    static void SendData16(uint16);
    static void SetWindow(int startX, int startY, int stopX, int stopY);

    static void Write_Cmd(unsigned char CMD)
    {
        pinDC.ToLow();

        SendByte(CMD);
    }

    static void SendCommand(uint8 command)
    {
        Write_Cmd(command);
    }

    static void Write_Cmd_Data(unsigned char CMDP)
    {
        pinDC.ToHi();

        SendByte(CMDP);
    }

    static void SendData8(uint8 byte)
    {
        Write_Cmd_Data(byte);
    }

    static void LCD_SetPos_Vertical(unsigned char x0, unsigned char x1, unsigned int y0, unsigned int y1);
}


void ST7735::Init()
{
    pinDC.Init();
    pinRES.Init();
    pinBKG.Init();
    pinSCL.Init();
    pinSDA.Init();

    pinSCL.ToLow();

    pinBKG.ToHi();

    pinRES.ToLow();
    pinDC.ToLow();

    pinRES.ToLow(); //-V525
    Timer::Delay(50);
    pinRES.ToHi();
    Timer::Delay(150);

    Write_Cmd(0x11);

    Timer::Delay(120);                //ms                                                              

    Write_Cmd(0x21);

    Write_Cmd(0xB1);
    Write_Cmd_Data(0x05);
    Write_Cmd_Data(0x3A);
    Write_Cmd_Data(0x3A);

    Write_Cmd(0xB2);
    Write_Cmd_Data(0x05);
    Write_Cmd_Data(0x3A);
    Write_Cmd_Data(0x3A);

    Write_Cmd(0xB3);
    Write_Cmd_Data(0x05);
    Write_Cmd_Data(0x3A);
    Write_Cmd_Data(0x3A);
    Write_Cmd_Data(0x05);
    Write_Cmd_Data(0x3A);
    Write_Cmd_Data(0x3A);

    Write_Cmd(0xB4);     //Dot inversion
    Write_Cmd_Data(0x03);

    Write_Cmd(0xC0);
    Write_Cmd_Data(0x62);
    Write_Cmd_Data(0x02);
    Write_Cmd_Data(0x04);

    Write_Cmd(0xC1);
    Write_Cmd_Data(0xC0);

    Write_Cmd(0xC2);
    Write_Cmd_Data(0x0D);
    Write_Cmd_Data(0x00);

    Write_Cmd(0xC3);
    Write_Cmd_Data(0x8D);
    Write_Cmd_Data(0x6A);

    Write_Cmd(0xC4);
    Write_Cmd_Data(0x8D);
    Write_Cmd_Data(0xEE);

    Write_Cmd(0xC5);     //VCOM
    Write_Cmd_Data(0x0E);

    Write_Cmd(0xE0);
    Write_Cmd_Data(0x10);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x02);
    Write_Cmd_Data(0x03);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x07);
    Write_Cmd_Data(0x02);
    Write_Cmd_Data(0x07);
    Write_Cmd_Data(0x0A);
    Write_Cmd_Data(0x12);
    Write_Cmd_Data(0x27);
    Write_Cmd_Data(0x37);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x0D);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x10);


    Write_Cmd(0xE1);
    Write_Cmd_Data(0x10);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x03);
    Write_Cmd_Data(0x03);
    Write_Cmd_Data(0x0F);
    Write_Cmd_Data(0x06);
    Write_Cmd_Data(0x02);
    Write_Cmd_Data(0x08);
    Write_Cmd_Data(0x0A);
    Write_Cmd_Data(0x13);
    Write_Cmd_Data(0x26);
    Write_Cmd_Data(0x36);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x0D);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x10);

    Write_Cmd(0x3A);
    Write_Cmd_Data(0x05);

    Write_Cmd(0x36);
    Write_Cmd_Data(0xC8);

    Write_Cmd(0x29);

    Write_Cmd(0x2C);
}


void ST7735::LCD_SetPos_Vertical(unsigned char x0, unsigned char x1, unsigned int y0, unsigned int y1)
{
    unsigned char YSH, YSL, YEH, YEL;
    x0 += 26; x1 += 26; y0 += 1; y1 += 1;

    YSH = (uint8)(y0 >> 8);
    YSL = (uint8)y0;

    YEH = (uint8)(y1 >> 8);
    YEL = (uint8)y1;

    Write_Cmd(0x2A);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(x0);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(x1);
    Write_Cmd(0x2B);
    Write_Cmd_Data(YSH);
    Write_Cmd_Data(YSL);
    Write_Cmd_Data(YEH);
    Write_Cmd_Data(YEL);
    Write_Cmd(0x2C);//LCD_WriteCMD(GRAMWR);
}


void ST7735::SetWindow(int x, int y, int width, int height)
{
    SendCommand(0x2A);      // CASET
    SendData8(0x00);
    SendData8((uint8)x);
    SendData8(0x00);
    SendData8((uint8)(x + width - 1));
    SendCommand(0x2B);      // RASET
    SendData8(0x00);
    SendData8((uint8)y);
    SendData8(0x00);
    SendData8((uint8)(y + height));
}


void ST7735::Fill(uint16 color)
{
    unsigned int w, u;
    LCD_SetPos_Vertical(0, 79, 0, 159);

//    for (w = 0; w < 80; w++)
//    {
//        SendData16((uint16)(~color));
//    }

    for (w = 0; w < 160; w++)
    {
//        SendData16((uint16)(~color));

        for (u = 0; u < 80; u++)
        {
            SendData16(color);
        }

//        SendData16((uint16)(~color));
    }

//    for (w = 0; w < 80; w++)
//    {
//        SendData16((uint16)(~color));
//    }
}


void ST7735::WriteBuffer(int y0)
{
    SetWindow(0, y0, Display::WIDTH, Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT);

    SendCommand(0x2C);

    for (int y = 0; y < Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT; y++)
    {
        uint8 *points = Display::Buffer::GetLine(y);

        for (int i = 0; i < Display::WIDTH; i++)
        {
            SendData16(Color::colors[*points++]);
        }
    }
}
