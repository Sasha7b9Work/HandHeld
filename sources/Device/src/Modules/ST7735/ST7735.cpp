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

    static void SendByte(uint8);
    static void SendCommand(uint8);
    static void SendData8(uint8);
    static void SendData16(uint16);
    static void SetWindow(int startX, int startY, int stopX, int stopY);
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

    pinRES.ToHi(); //-V525
    Timer::Delay(20);
    pinRES.ToLow();
    Timer::Delay(20);
    pinRES.ToHi();
    Timer::Delay(20);

    SendCommand(0x01);      // SWRESET Software reset
    Timer::Delay(12);

    SendCommand(0x11);      // SLPOUT Sleep out
    Timer::Delay(12);

    SendCommand(0x3A);      // COLMOD Interface pixel format
    Timer::Delay(0x05);     // 16 bit / pixel

    SendCommand(0x36);      // MADCTL Memory Data Access Control
    SendData8(BINARY_U8(01100000));

    SendCommand(0x29);      // DISPON Display on
}


void ST7735::WriteBuffer(int y0)
{
    SetWindow(0, y0, Display::WIDTH, Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT);

    SendCommand(0x2C);

    for (int y = y0; y < y0 + Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT; y++)
    {
        uint8 *points = Display::Buffer::GetLine(y);

        for (int i = 0; i < Display::WIDTH; i++)
        {
            SendData16(Color::colors[*points++]);
        }
    }
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


void ST7735::SendByte(uint8 byte)
{
    for (int bit = 7; bit >= 0; bit--)
    {
        (byte & (1 << bit)) == 0 ? pinSDA.ToLow() : pinSDA.ToHi();

        pinSCL.ToHi();

        pinSCL.ToLow();
    }
}


void ST7735::SendCommand(uint8 command)
{
    pinDC.ToLow();

    SendByte(command);
}


void ST7735::SendData8(uint8 data)
{
    pinDC.ToHi();

    SendByte(data);
}


void ST7735::SendData16(uint16 data)
{
    pinDC.ToHi();

    SendByte((uint8)(data >> 8));

    SendByte((uint8)data);
}
