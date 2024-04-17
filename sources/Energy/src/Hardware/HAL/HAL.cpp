// 2024/03/01 22:24:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/systick.h"
#include <gd32e23x.h>


void HAL::Init()
{
    rcu_deinit();
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC8M);
    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV512);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV16);
    rcu_apb2_clock_config(RCU_APB2_CKAHB_DIV16);
}
