// 2024/03/06 08:39:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Watch.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Display/Display.h"
#include "Display/Font/Font.h"


void Watch::Draw(int x, int y, const Color &color)
{
    RTCDateTime date_time;

    PCF8563::GetDateTime(&date_time);

    date_time.Year = 2024;

    Font::SetSize(2);

    Text<>("%02d:%02d:%02d", date_time.Hour, date_time.Minute, date_time.Second).Write(x, y, color);

    Font::SetSize(1);

    Text<>("%02d/%02d/%02d", date_time.Day, date_time.Month, date_time.Year).Write(x + 15, y + 20);
}