// 2024/04/17 22:12:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/DeepSleep.h"
#include <gd32e23x.h>


void DeepSleep::Enter()
{
    rcu_periph_clock_enable(RCU_PMU);
    pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
}
