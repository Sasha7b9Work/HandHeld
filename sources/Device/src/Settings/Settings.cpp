// 2024/03/02 19:47:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Display.h"

Source Source::PHONE_HOME(PhoneHome);


void Source::Draw(int x, int y, const Color &color) const
{
    if (value == PhoneHome)
    {
        Text("Ò.ÄÎÌ").Write(x, y, color);
    }
    else if (value == Mobile)
    {

    }
    else if (value == Intercom)
    {

    }
    else if (value == Bell)
    {

    }
    else if (value == Sensor)
    {

    }
}
