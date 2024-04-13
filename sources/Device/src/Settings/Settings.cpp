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
    { {0, Volume::Hi, ModeSource::All},
      {1, Volume::Hi, ModeSource::All},
      {2, Volume::Hi, ModeSource::All},
      {3, Volume::Hi, ModeSource::All},
      {4, Volume::Hi, ModeSource::All} },
    { 0, 0, 0, 0, 0, 0 }
};
