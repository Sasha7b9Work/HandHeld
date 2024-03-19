// 2024/03/02 19:47:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Player/Player.h"
#include <cstdlib>


Settings gset =
{
    { {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1} },
    { 0, 0, 0, 0, 0, 0, 0 }
};


uint Source::time_recv[Source::Count] = { 0, 0, 0, 0, 0 };


void Source::Draw(int x, int y, const Color &color) const
{
    if (value == PhoneHome)
    {
        Text<>("�.���").Write(x, y, color);
    }
    else if (value == Mobile)
    {
        Text<>("�.���").Write(x, y, color);
    }
    else if (value == Intercom)
    {
        Text<>("����").Write(x, y, color);
    }
    else if (value == DoorBell)
    {
        Text<>("����").Write(x, y, color);
    }
    else if (value == SoundSensor)
    {
        Text<>("���").Write(x, y, color);
    }
}


void Source::Receive(E type)
{
    time_recv[type] = TIME_MS;

    Player::Play(TypeSound::_1);
}


bool Source::IsReceived(E type)
{
    return time_recv[type] + 1000 > TIME_MS;
}
