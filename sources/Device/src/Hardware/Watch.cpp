// 2024/03/06 08:39:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Watch.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Display/Display.h"
#include "Display/Font/Font.h"


void Watch::Draw(int x, int y, const Color &color)
{
    PCF8563::GetDateTime().Draw(x, y, color);
}
