// 2024/03/20 23:04:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Battery.h"
#include "Hardware/HAL/HAL.h"
#include "Display/Display.h"


namespace Battery
{
    static float ConvertToCharge(float voltage);
}


void Battery::Draw(int x, int y)
{
    const int width = 38;

    Rect(width, 13).Draw(x, y, Color::GREEN);
    Rect(5, 7).Fill(x - 4, y + 3);

    float voltage = HAL_ADC::GetVoltage();

    int width_rect = (int)(width * ConvertToCharge(voltage) / 100.0f + 0.5f);

    Rect rect(width_rect, 13);
    rect.Fill(x + width - width_rect, y);

    Text<>("%.2f", (double)voltage).Write(x + 2, y + 2, Color::WHITE);
}


float Battery::ConvertToCharge(float /*voltage*/)
{
    return 50.0f;
}
