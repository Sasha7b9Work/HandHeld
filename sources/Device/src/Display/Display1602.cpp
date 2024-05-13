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
    struct Symbol
    {
        uint8 rows[7];          // � ������ ����� �������� 5 ����� ������ �������
    };

    static const Symbol symbols[21] =
    {
        {
            BINARY_U8(00000000),    // � - 0x00
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x01
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x02
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x03
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x04
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x05
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x06
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x07
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x08
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x09
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0A
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0B
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0C
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0D
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0E
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x0F
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x10
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x11
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x12
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x13
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // � - 0x14
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        }
    };

    struct SymbolCGRAM
    {
        uint8 code;             // ��� ������� �� 0x00 �� 0x14 - ������� �������� ��� � ����������� ���������������
        uint time;              // ����� ������� �������. �����, ����� ���������� ������, ������� ���������� ������ ����,
                                // ����� �� ��� ����� �������� ������, ����� ������
    };

    struct ROM
    {
        SymbolCGRAM symbols[8] =
        {
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 }
        };
    };

    static char buffer[2][16];

    static void BeginScene();
    static void EndScene();
    // �������������� ��������� ������� � �������, ��������� ��� �������� � ������
    static void Convert();
    // ��������� � ������� �������, ������� ��� � ����������� ��������������� � �������� �� ���
    // ������ ������� � ������
    static void LoadSymbolsToCGRAM();
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
        Text<>("���������").WriteInCenter(0, 0, Display::WIDTH, Color(Color::Contrast(gset.alarm.color)));
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

    LoadSymbolsToCGRAM();

    WH1602B::Write((uint8 *)buffer);
}


void Display::Convert()
{
    //  � - 0x00
    //  � - 0x01
    //  � - 0x02
    //  � - 0x03
    //  � - 0x04
    //  � - 0x05
    //  � - 0x06
    //  � - 0x07
    //  � - 0x08
    //  � - 0x09
    //  � - 0x0A
    //  � - 0x0B
    //  � - 0x0C
    //  � - 0x0D
    //  � - 0x0E
    //  � - 0x0F
    //  � - 0x10
    //  � - 0x11
    //  � - 0x12
    //  � - 0x13
    //  � - 0x14

    static const pchar symbs =
        "                "
        "                "
        "                "
        "                "
        "A\x00""B\x01\x02E\x03\x04\x05\x06K\x07MHO\x08"
        "PCT\x09\x0AX\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14"
        "                "
        "                ";

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            uint8 symbol = (uint8)buffer[i][j];

            if (symbol > 127)
            {
                buffer[i][j] = symbs[symbol - 128];
            }
        }
    }

    // �� ������ ������ ��������� ����� ������ �� ������� ���������� �������� (���� ����),
    // ���� �� ���� ��������, ����������� � �������
}


void Display::LoadSymbolsToCGRAM()
{

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
