// 2024/03/02 09:30:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/systick.h"


uint timer_counter = 0;


void Timer::Delay(uint timeMS)
{
    delay_1ms(timeMS);
}


void TimeMeterMS::Reset()
{
    time_reset = timer_counter;
}


uint TimeMeterMS::ElapsedTime() const
{
    return timer_counter - time_reset;
}
