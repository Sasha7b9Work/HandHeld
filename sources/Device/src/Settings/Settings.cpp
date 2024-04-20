// 2024/03/02 19:47:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Hardware/Vibrato.h"
#include "Display/Icons.h"
#include <cstdlib>


Settings gset =
{
    { {Melody::_1, Volume::Hi, Color::Red,    ModeIndication::All},
      {Melody::_2, Volume::Hi, Color::Orange, ModeIndication::All},
      {Melody::_3, Volume::Hi, Color::Yellow, ModeIndication::All},
      {Melody::_4, Volume::Hi, Color::Green,  ModeIndication::All},
      {Melody::_5, Volume::Hi, Color::Blue,   ModeIndication::All},
      {Melody::_6, Volume::Hi, Color::Purple, ModeIndication::All}
    },
    {
        0,
        Melody::_1,
        Volume::Hi,
        Color::White,
        ModeIndication::All,
        { 0, 0, 0, 0, 0, 0 }
    }
};


pchar Melody::Name(E v)
{
    static const pchar names[Count] =
    {
        "������� 1",
        "������� 2",
        "������� 3",
        "������� 4",
        "������� 5",
        "������� 6",
        "������� 7",
        "������� 8",
        "������� 9",
        "������� 10"
    };

    return names[v];
}
