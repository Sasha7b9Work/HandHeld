// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"


namespace CMT2210AW
{
    static uint value = 0;
}


void CMT2210AW::Init()
{
    pinDOUT.Init();
    pinSCK.Init();          // Этот пин будем использовать для определения начала посылки
}


void CMT2210AW::CallbackOn1MS()
{
    value <<= 1;

    if (pinDOUT.IsHi())
    {
        value |= 1;
    }
    else
    {
        value &= 0xFFFFFFFE;
    }

    Display::SetReceiverValue(value);
}
