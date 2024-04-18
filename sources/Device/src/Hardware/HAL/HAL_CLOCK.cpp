// 2024/04/18 15:19:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <gd32e23x.h>


ModeClock::E ModeClock::current = ModeClock::Low;


namespace HAL_CLOCK
{
    static void SetDeepSleep();
    static void SetLow();
    static void SetHi();
}


void ModeClock::Set(E v)
{
    current = v;

    if (v == ModeClock::DeepSleep)
    {
        HAL_CLOCK::SetDeepSleep();
    }
    else if (v == ModeClock::Low)
    {
        HAL_CLOCK::SetLow();
    }
    else if (v == ModeClock::Hi)
    {
        HAL_CLOCK::SetHi();
    }
}


void HAL_CLOCK::SetDeepSleep()
{

    rcu_periph_clock_enable(RCU_PMU);
    pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
}


void HAL_CLOCK::SetLow()
{

}


void HAL_CLOCK::SetHi()
{

}
