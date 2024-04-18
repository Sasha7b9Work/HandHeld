// 2024/04/18 15:19:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/ST7735/ST7735.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
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
    ST7735::Disable();

    CMT2210AW::PrepareToSleep();

    rcu_periph_clock_enable(RCU_PMU);
    pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
}


void HAL_CLOCK::SetLow()
{
    SystemCoreClock = 3250000;

    rcu_hxtal_prediv_config(RCU_PLL_PREDV16);
    RCU_CFG0 |= RCU_CFG0_PLLDV;         // Должно быть то же, что и в PREDV2[0]

    while (0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)) {
    }

    while (RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    HAL::Init();
}


void HAL_CLOCK::SetHi()
{
    SystemCoreClock = 52000000;

    rcu_hxtal_prediv_config(RCU_PLL_PREDV1);
    RCU_CFG0 &= ~(RCU_CFG0_PLLDV);         // Должно быть то же, что и в PREDV2[0]

    while (0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)) {
    }

    while (RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    HAL::Init();
}
