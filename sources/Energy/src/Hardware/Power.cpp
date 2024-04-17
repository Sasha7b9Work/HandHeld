// 2024/04/17 08:46:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Power.h"
#include <gd32e23x.h>


void Power::DeepSleep()
{
    pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
}
