// 2024/03/01 22:47:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/ST7735/ST7735.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Hardware/Timer.h"
#include "Display/Display.h"
#include <gd32e23x.h>


namespace ST7735
{
#define SET_DC   pinTFT_DC.ToHi()
#define RESET_DC pinTFT_DC.ToLow()

    static void SendCommand(uint8);
    static void SendData8(uint8);
    static void SendData16(uint16);
    static void SetWindow(int startX, int startY, int stopX, int stopY);
}


void ST7735::Init()
{
    pinTFT_DC.Init();
    pinTFT_RES.Init();
    pinTFT_BKG.Init();
    pinTFT_SCL.Init();
    pinTFT_SDA.Init();

    pinTFT_RES.ToLow();
    pinTFT_DC.ToLow();

    pinTFT_RES.ToHi(); //-V525
    Timer::Delay(20);
    pinTFT_RES.ToLow();
    Timer::Delay(20);
    pinTFT_RES.ToHi();
    Timer::Delay(20);

    SendCommand(0x01);      // SWRESET Software reset
    Timer::Delay(12);

    SendCommand(0x11);      // SLPOUT Sleep out
    Timer::Delay(12);

    SendCommand(0x3A);      // COLMOD Interface pixel format
    Timer::Delay(0x05);        // 16 bit / pixel

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


void ST7735::SendCommand(uint8)
{
}



void ST7735::SendData8(uint8)
{
}


void ST7735::SendData16(uint16)
{
}
