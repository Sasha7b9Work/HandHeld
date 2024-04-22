// 2024/03/20 23:04:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Hardware/Power.h"
#include "Display/Display.h"
#include "Hardware/HAL/HAL_PINS.h"


namespace Power
{
    static const int WIDTH = 38;
    static const int HEIGHT = 14;
}


void Power::Init()
{
    pinPWR.Init();
    pinPWR_CTRL.Init();

    pinPWR.ToHi();
}


void Power::Disable()
{
    TimeMeterMS meter;

    while (meter.ElapsedTime() < 1500)
    {
        Display::DrawPowerOff();
    }

    pinPWR.ToLow();
}


void Power::Draw()
{
    int x = 121;
    int y = 0;

    float voltage = HAL_ADC::GetVoltage();

    if (voltage > 4.3f)             // ��� �����
    {
        Rect(HEIGHT + 4, HEIGHT + 4).Draw(x + 20, y, Color::GREEN);
        Font::SetSize(2);
        Text<>("�").Write(x + 25, y + 2);
        Font::SetSize(1);
    }
    else
    {
        Color color = Color::GREEN;

        Rect(WIDTH, HEIGHT).Draw(x, y, color);
        Rect(5, 7).Fill(x - 4, y + 3);

        if (voltage > 3.9f)        // ������ �����
        {
            Rect(WIDTH, HEIGHT).Fill(x, y);
        }
        else if (voltage > 3.8f)        // ��� ����� ������
        {
            int width = WIDTH * 2 / 3;

            Rect(width, HEIGHT).Fill(x + WIDTH - width, y);
        }
        else if (voltage > 3.7f)        // ���� ����� ������
        {
            int width = WIDTH / 3;

            Rect(width, HEIGHT).Fill(x + WIDTH - width, y, Color::YELLOW);
        }
        else if (voltage > 3.5f)        // ������ �������
        {
            Rect(WIDTH, HEIGHT).Draw(x, y, Color::RED);
            Rect(5, 7).Fill(x - 4, y + 3);
        }
        else
        {
            // ����� ����� �����������
        }
    }

    Text<>("%.2f", (double)voltage).Write(x + 2, y + 3, Color::WHITE);
}


void Power::Update()
{
    if (HAL_ADC::GetVoltage() <= 3.5f)
    {
        Disable();
    }
}
