// 2024/03/01 22:45:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"
#include "Settings/Settings.h"
#include "Display/Font/Font.h"
#include "Hardware/Watch.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Hardware/Battery.h"
#include "Utils/FPS.h"
#include <string>


namespace Display
{
    namespace Buffer
    {
        static uint8 buffer[SIZE];

        static void Fill(const Color &color)
        {
            std::memset(buffer, color.value, SIZE);
        }

        uint8 *GetLine(int y)
        {
            return buffer + y * Display::WIDTH;
        }
    }

    static int current_part = 0;                            // ��� ����� ������ ������������

    void BeginScene(int num_part);
    void DrawScene(int num_part);
    void EndScene(int num_parts);
}


void Display::Init()
{
    ST7735::Init();

    Font::SetType(TypeFont::_7);
}


void Display::Update()
{
    FPS::BeginFrame();

    volatile uint start_time = TIME_MS;

    for (int i = 0; i < NUMBER_PARTS_HEIGHT; i++)
    {
        BeginScene(i);      // 0 ms
        DrawScene(i);       // 20 ms
        EndScene(i);        // 68 ms
    }

    volatile uint time = TIME_MS - start_time;

    time = time;

    FPS::EndFrame();
}


void Display::BeginScene(int num_part)
{
    current_part = num_part;

    Buffer::Fill(Color::BLACK);
}


void Display::EndScene(int num_parts)
{
    ST7735::WriteBuffer(HEIGHT / NUMBER_PARTS_HEIGHT * num_parts);
}


void Display::DrawScene(int num_part)
{
    (void)num_part;

    if (Menu::IsShown())
    {
        Menu::Draw();
    }
    else
    {
        Watch::Draw(45, 30, Color::WHITE);

        for (int i = 0; i < Source::Count; i++)
        {
            if (Source::IsReceived((Source::E)i))
            {
                Source((Source::E)i).DrawIcon(11 + i * 30, 8);
            }
        }

        Battery::Draw(121, 67);

        FPS::DrawTimeFrame(0, 75);
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

    y -= Display::HEIGHT / Display::NUMBER_PARTS_HEIGHT * Display::current_part;

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


void RTCDateTime::Draw(int x, int y, const Color &color) const
{
    Font::SetSize(2);

    Text<>("%02d:%02d:%02d", Hour, Minute, Second).Write(x, y, color);

    Font::SetSize(1);

    Text<>("%02d/%02d/%02d", Day, Month, Year).Write(x + 15, y + 20);
}
