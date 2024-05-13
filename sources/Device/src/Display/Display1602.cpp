// 2024/04/23 08:38:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display1602.h"
#include "Modules/WH1602B/WH1602B.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Settings/Source.h"
#include "Menu/Menu.h"
#include "Hardware/Power.h"
#include "Utils/StringUtils.h"
#include "Settings/Settings.h"
#include <cstring>


template int Text<64>::Write(int x, int y, const Color &color) const;


namespace Display
{
    static char buffer[2][16];

    static void BeginScene();
    static void EndScene();
    static void Convert();
    static void WriteSymbol(int x, int y, char);
}


void Display::Init()
{
    WH1602B::Init();
}


void Display::Update()
{
    BeginScene();

    if (PCF8563::IsAlarmed())
    {
        Text<>("¡”ƒ»À‹Õ» ").WriteInCenter(0, 0, Display::WIDTH, Color(Color::Contrast(gset.alarm.color)));
    }
    else if (Source::GetCountReceived())
    {
        pchar name = Source::Name(Source::Current());

        int num_words = SU::NumWordsInString(name);

        if (num_words == 1)
        {
            Text<>(name).WriteInCenter(0, 0, Display::WIDTH);
        }
        else if (num_words == 2)
        {
            char buff[32];

            Text<>(SU::GetWordFromString(name, 1, buff)).WriteInCenter(0, 0, Display::WIDTH);

            Text<>(SU::GetWordFromString(name, 2, buff)).WriteInCenter(0, 1, Display::WIDTH);
        }
    }
    else
    {
        if (Menu::IsShown())
        {
            Menu::Draw();
        }
        else
        {
            PCF8563::GetDateTime().DrawTime(0, 0);

            PCF8563::GetDateTime().DrawDate(0, 0);

            Power::Draw();
        }
    }

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


void RTCDateTime::DrawTime(int, int, const Color &) const
{
    Text<>("%02d:%02d", Day, Month, Year).Write(0, 0);
}


void RTCDateTime::DrawDate(int, int, const Color &) const
{
    Text<>("%02d/%02d/%02d", Day, Month, Year).Write(0, 1);
}


template<int capacity>
int Text<capacity>::Write(int x, int y, const Color &) const
{
    if (x == -1)
    {
        WriteInCenter(0, y, 0);
    }
    else
    {
        const char *pointer = &text[0];

        while (*pointer)
        {
            Display::WriteSymbol(x++, y, *pointer);
            pointer++;
        }
    }

    return 0;
}


void Display::WriteSymbol(int x, int y, char symbol)
{
    if (y == 0 || y == 1)
    {
        if (x >= 0 && x <= 15)
        {
            buffer[y][x] = symbol;
        }
    }
}
