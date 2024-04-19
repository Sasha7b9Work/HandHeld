// 2024/03/01 22:45:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"
#include "Settings/Settings.h"
#include "Display/Font/Font.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Utils/FPS.h"
#include "Utils/StringUtils.h"
#include "Hardware/Power.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Utils/Math.h"
#include <string>


namespace Display
{
    namespace Buffer
    {
        static uint8 buffer[SIZE];

        static uint crc[NUMBER_PARTS_HEIGHT] = { 0, 0, 0, 0, 0, 0, 0, 0 };

        static int current_part = 0;                            // Эту часть сейчас отрисовываем

        static bool MatchesCRC(uint _crc)
        {
            return _crc == crc[current_part];
        }

        static uint CalcualteCRC()
        {
            return Math::CalculateCRC(buffer, SIZE);
        }

        static void Fill(const Color &color)
        {
            std::memset(buffer, color.value, SIZE);
        }

        uint8 *GetLine(int y)
        {
            return buffer + y * Display::WIDTH;
        }
    }

    void BeginScene(int num_part);
    void DrawScene(int num_part);
    void EndScene(int num_parts);
}


void Display::Init()
{
    ST7735::Init();

    Font::SetType(TypeFont::_7);
}


void Display::PrepareToSleep()
{
    ST7735::Disable();

    for (int i = 0; i < NUMBER_PARTS_HEIGHT; i++)
    {
        Buffer::crc[i] = 0;
    }
}


void Display::Update()
{
    static TimeMeterMS meter;

    if (meter.ElapsedTime() < 20 || Keyboard::ToMoreTime())
    {
        return;
    }

    meter.Reset();

    FPS::BeginFrame();

    for (int i = 0; i < NUMBER_PARTS_HEIGHT; i++)
    {
        BeginScene(i);      // 0 ms
        DrawScene(i);       // 20 ms
        EndScene(i);        // 68 ms
    }

    FPS::EndFrame();
}


void Display::BeginScene(int num_part)
{
    Buffer::current_part = num_part;

    Buffer::Fill(Color::BLACK);
}


void Display::EndScene(int num_parts)
{
    uint crc = Buffer::CalcualteCRC();

    if (!Buffer::MatchesCRC(crc))
    {
        ST7735::Enable();

        Buffer::crc[Buffer::current_part] = crc;

        ST7735::WriteBuffer(HEIGHT / NUMBER_PARTS_HEIGHT * num_parts);
    }
}


void Display::DrawScene(int num_part)
{
    (void)num_part;

    if (Source::GetCountReceived())
    {
        int y = 40;

        if (Source::GetCountReceived() == 1)
        {
            y = 30;
        }
        else
        {
            for (int i = 0; i < Source::Count; i++)
            {
                if (Source::IsReceived((Source::E)i))
                {
                    Source((Source::E)i).DrawIcon(11 + i * 30, 8);
                }
            }
        }

        Font::SetSize(2);

        pchar name = Source::Name(Source::GetFirstReceived());

        int num_words = SU::NumWordsInString(name);

        if (num_words == 1)
        {
            Text<>(name).WriteInCenter(0, y, Display::WIDTH, Color::GREEN);
        }
        else if (num_words == 2)
        {
            char buffer[32];

            Text<>(SU::GetWordFromString(name, 1, buffer)).WriteInCenter(0, y - 10, Display::WIDTH, Color::GREEN);

            Text<>(SU::GetWordFromString(name, 2, buffer)).WriteInCenter(0, y + 15, Display::WIDTH, Color::GREEN);
        }

        Font::SetSize(1);

        FPS::DrawTimeFrame(0, 75);
    }
    else
    {
        if (Menu::IsShown())
        {
            Menu::Draw();
        }
        else
        {
            Font::SetSize(5);

            PCF8563::GetDateTime().DrawTime(30, 23, Color::WHITE);

            Font::SetSize(2);

            PCF8563::GetDateTime().DrawDate(46, 66);

            Font::SetSize(1);

            Power::Draw();

            FPS::DrawTimeFrame(0, 75);
        }
    }
}


void Rect::Fill(int x0, int y0, const Color &color) const
{
    color.SetAsCurrent();

    for (int y = y0; y < y0 + height; y++)
    {
        HLine(width).Draw(x0, y);
    }
}


void Rect::Draw(int x, int y, const Color &color) const
{
    color.SetAsCurrent();

    HLine(width).Draw(x, y);
    HLine(width).Draw(x, y + height - 1);
    VLine(height).Draw(x, y);
    VLine(height).Draw(x + width - 1, y);
}


void HLine::Draw(int x, int y, const Color &color) const
{
    color.SetAsCurrent();

    for (int i = 0; i < width; i++)
    {
        Pixel().Set(x++, y);
    }
}


void VLine::Draw(int x, int y, const Color &color) const
{
    color.SetAsCurrent();

    for (int i = 0; i < height; i++)
    {
        Pixel().Set(x, y++);
    }
}


void Pixel::Set(int x, int y, const Color &color) const
{
    color.SetAsCurrent();

    if (x < 0)
    {
        return;
    }

    if (x >= Display::WIDTH)
    {
        return;
    }

    y -= Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT * Display::Buffer::current_part;

    if (y < 0)
    {
        return;
    }

    if (y >= Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT)
    {
        return;
    }

    Display::Buffer::buffer[y * Display::WIDTH + x] = (uint8)Color::current.value;
}


void RTCDateTime::DrawTime(int x, int y, const Color &color) const
{
    Text<>("%02d:%02d", Hour, Minute).Write(x, y, color);
}


void RTCDateTime::DrawDate(int x, int y, const Color &color) const
{
    Text<>("%02d/%02d/%02d", Day, Month, Year).Write(x, y, color);
}
