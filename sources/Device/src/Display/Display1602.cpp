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
        uint8 rows[7];          // В каждом байте хранятся 5 точек строки символа
    };

    static const Symbol symbols[21] =
    {
        {
            BINARY_U8(00000000),    // Б - 0x00
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Г - 0x01
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Д - 0x02
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ж - 0x03
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // З - 0x04
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // И - 0x05
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Й - 0x06
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Л - 0x07
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // П - 0x08
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // У - 0x09
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ф - 0x0A
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ц - 0x0B
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ч - 0x0C
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ш - 0x0D
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Щ - 0x0E
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ъ - 0x0F
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ы - 0x10
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ь - 0x11
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Э - 0x12
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Ю - 0x13
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000),
            BINARY_U8(00000000)
        },
        {
            BINARY_U8(00000000),    // Я - 0x14
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
        uint8 code;             // Код символа от 0x00 до 0x14 - столько символов нет в стандартном знакогенераторе
        uint time;              // Время загузки символа. Нужно, чтобы определить символ, который загружался раньше всех,
                                // чтобы на его место записать другой, более нужный
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
    // Конвертировать выводимые символы в символы, приходные для загрузки в дисплй
    static void Convert();
    // Загрузить в дисплей символы, которых нет в стандартном знакогенераторе и заменить на них
    // нужные символы в буфере
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
        Text<>("БУДИЛЬНИК").WriteInCenter(0, 0, Display::WIDTH, Color(Color::Contrast(gset.alarm.color)));
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
    //  Б - 0x00
    //  Г - 0x01
    //  Д - 0x02
    //  Ж - 0x03
    //  З - 0x04
    //  И - 0x05
    //  Й - 0x06
    //  Л - 0x07
    //  П - 0x08
    //  У - 0x09
    //  Ф - 0x0A
    //  Ц - 0x0B
    //  Ч - 0x0C
    //  Ш - 0x0D
    //  Щ - 0x0E
    //  Ъ - 0x0F
    //  Ы - 0x10
    //  Ь - 0x11
    //  Э - 0x12
    //  Ю - 0x13
    //  Я - 0x14

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

    // На выходе сиволы кириллицы будут замены на символы латинского алфавита (если есть),
    // либо на коды символов, загружаемых в дисплей
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
