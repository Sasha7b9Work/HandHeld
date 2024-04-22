// 2024/03/20 23:04:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Hardware/Power.h"
#include "Display/Display.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Modules/LED/driverLED.h"


namespace Power
{
    static const int WIDTH = 38;
    static const int HEIGHT = 14;

    static void PowerDown();
}


void Power::Init()
{
    pinPWR.Init();
    pinPWR_CTRL.Init();

    pinPWR.ToHi();

    float voltage = HAL_ADC::GetVoltage(true);

    if (voltage < 3.0f)
    {
        PCF8563::AlarmFlagEnable(false);

        PowerDown();
    }
    else if (voltage < 3.5f)
    {
        PCF8563::AlarmFlagEnable(false);

        TimeMeterMS meter;

        while (meter.ElapsedTime() < 3000)
        {
            Display::DrawLowVoltage();
        }

        PowerDown();
    }

    PCF8563::Update();

    if (PCF8563::IsAlarmed())
    {
        PCF8563::AlarmFlagEnable(false);
    }

    while (pinPWR_CTRL.IsLow())
    {
        Display::DrawPowerOn();
    }

    Timer::Delay(100);
}


void Power::Disable()
{
    TimeMeterMS meter;

    while (meter.ElapsedTime() < 1500)
    {
        Display::DrawPowerOff();
    }

    PowerDown();
}


void Power::PowerDown()
{
    pinPWR.ToLow();

    LED::Driver::On();

    while(true) { }
}


void Power::Update()
{
    if (HAL_ADC::GetVoltage(false) <= 3.5f)
    {
        Disable();
    }

    if (pinPWR_CTRL.IsLow() && !PCF8563::IsAlarmed())
    {
        Disable();
    }
}


void Power::Draw()
{
    int x = 121;
    int y = 0;

    float voltage = HAL_ADC::GetVoltage(false);

    if (voltage > 4.3f)             // Идёт заряд
    {
        Rect(HEIGHT + 4, HEIGHT + 4).Draw(x + 20, y, Color::GREEN);
        Font::SetSize(2);
        Text<>("З").Write(x + 25, y + 2);
        Font::SetSize(1);
    }
    else
    {
        Color color = Color::GREEN;

        Rect(WIDTH, HEIGHT).Draw(x, y, color);
        Rect(5, 7).Fill(x - 4, y + 3);

        if (voltage > 3.9f)        // Полный заряд
        {
            Rect(WIDTH, HEIGHT).Fill(x, y);
        }
        else if (voltage > 3.8f)        // Две трети заряда
        {
            int width = WIDTH * 2 / 3;

            Rect(width, HEIGHT).Fill(x + WIDTH - width, y);
        }
        else if (voltage > 3.7f)        // Одна треть заряда
        {
            int width = WIDTH / 3;

            Rect(width, HEIGHT).Fill(x + WIDTH - width, y, Color::YELLOW);
        }
        else if (voltage > 3.5f)        // Пустая батарея
        {
            Rect(WIDTH, HEIGHT).Draw(x, y, Color::RED);
            Rect(5, 7).Fill(x - 4, y + 3);
        }
        else
        {
            // Здесь нужно отключиться
        }
    }

    Text<>("%.2f", (double)voltage).Write(x + 2, y + 3, Color::WHITE);
}
