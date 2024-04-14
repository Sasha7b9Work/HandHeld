// 2024/03/20 23:04:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Battery.h"
#include "Hardware/HAL/HAL.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"

namespace Battery
{
#define width 38
#define height 14
}


void Battery::Draw()
{
    int x = 121;
    int y = 0;

    float voltage = HAL_ADC::GetVoltage();

    if (voltage > 4.3f)             // Идёт заряд
    {
        Rect(height + 4, height + 4).Draw(x + 20, y, Color::GREEN);
        Font::SetSize(2);
        Text<>("З").Write(x + 25, y + 2);
        Font::SetSize(1);
    }
    else
    {
        Rect(width, height).Draw(x, y, Color::GREEN);
        Rect(5, 7).Fill(x - 4, y + 3);

        if (voltage > 3.9f)        // Полный заряд
        {

        }
        else if (voltage > 3.8f)        // Две трети заряда
        {

        }
        else if (voltage > 3.7f)        // Одна треть заряда
        {

        }
        else if (voltage > 3.5f)        // Пустая батарея
        {

        }
        else
        {
            // Здесь нужно отключиться
        }
    }

    Text<>("%.2f", (double)voltage).Write(x + 2, y + 3, Color::WHITE);
}
