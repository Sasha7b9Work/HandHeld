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
    { {0, 9, ModeSource::All},
      {1, 9, ModeSource::All},
      {2, 9, ModeSource::All},
      {3, 9, ModeSource::All},
      {4, 9, ModeSource::All} },
    { 0, 0, 0, 0, 0, 0 }
};
