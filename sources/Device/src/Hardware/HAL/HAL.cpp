// 2024/03/01 22:24:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/systick.h"
#include <gd32e23x.h>


void HAL::Init()
{
    systick_config();

    rcu_periph_clock_enable(RCU_PMU);
    rcu_periph_clock_enable(RCU_GPIOA); 
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOF);

    rcu_periph_clock_enable(RCU_CFGCMP);

    rcu_periph_clock_enable(RCU_I2C1);

    rcu_periph_clock_enable(RCU_TIMER14);       // Для звука
    nvic_irq_enable(TIMER14_IRQn, 0);

    HAL_I2C::Init();

    HAL_ADC::Init();
}
