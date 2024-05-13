// 2024/04/23 08:38:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display1602.h"
#include "Modules/WH1602B/WH1602B.h"
#include <cstring>


namespace Display
{
    static char buffer[2][16];

    static void BeginScene();
    static void EndScene();
    static void Convert();
}


void Display::Init()
{
    WH1602B::Init();
}


void Display::Update()
{
    BeginScene();

    EndScene();
}


void Display::DrawPowerOn()
{

}


void Display::DrawPowerOff()
{

}


void Display::DrawLowVoltage()
{

}


void Display::PrepareToSleep()
{

}


uint Display::TimeEnabled()
{
    return 0;
}


void Display::BeginScene()
{
    std::memset(buffer, ' ', 32);
}


void Display::EndScene()
{
    Convert();

    WH1602B::Write((uint8 *)buffer);
}


void Display::Convert()
{
    static const pchar symbols =
        "                "
        "                "
        "                "
        "                "
        "ABBGDEJZIIKLMNOP"
        "PCTYFXC4JJQYIIII"
        "                "
        "                ";

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            uint8 symbol = (uint8)buffer[i][j];

            if (symbol > 127)
            {
                buffer[i][j] = symbols[symbol - 128];
            }
        }
    }
}
