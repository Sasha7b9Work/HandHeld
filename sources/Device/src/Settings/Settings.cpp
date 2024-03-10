// 2024/03/02 19:47:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Display.h"


Settings gset =
{
    {{0, 0, 1, 1, 1},
     {0, 0, 1, 1, 1},
     {0, 0, 1, 1, 1},
     {0, 0, 1, 1, 1},
     {0, 0, 1, 1, 1}}
};


void Source::Draw(int x, int y, const Color &color) const
{
    if (value == PhoneHome)
    {
        Text<>("р.днл").Write(x, y, color);
    }
    else if (value == Mobile)
    {
        Text<>("р.лна").Write(x, y, color);
    }
    else if (value == Intercom)
    {
        Text<>("днлн").Write(x, y, color);
    }
    else if (value == DoorBell)
    {
        Text<>("гбнм").Write(x, y, color);
    }
    else if (value == SoundSensor)
    {
        Text<>("дюр").Write(x, y, color);
    }
}
