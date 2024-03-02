// 2024/03/02 09:30:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/systick.h"


void Timer::Delay(uint timeMS)
{
    delay_1ms(timeMS);
}
