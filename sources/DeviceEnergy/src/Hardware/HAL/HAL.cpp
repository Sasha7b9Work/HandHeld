// 2024/03/01 22:24:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/systick.h"
#include "Hardware/HAL/HAL_PINS.h"
#include <gd32e23x.h>


void HAL::Init()
{
    rcu_deinit();
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC8M);
    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb1_clock_config(RCU_APB1_CKAHB_DIV16);
    rcu_apb2_clock_config(RCU_APB2_CKAHB_DIV16);

    systick_config();

//    rcu_periph_clock_enable(RCU_PMU);
    rcu_periph_clock_enable(RCU_GPIOA); 
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOF);
//
//    rcu_periph_clock_enable(RCU_CFGCMP);
//
//    rcu_periph_clock_enable(RCU_I2C1);
//
//    rcu_periph_clock_enable(RCU_TIMER2);
//    nvic_irq_enable(TIMER2_IRQn, 0);            // ������ �� �������
//
//    rcu_periph_clock_enable(RCU_TIMER5);        // ��� ������� ������
//    nvic_irq_enable(TIMER5_IRQn, 1);
//
    HAL_PINS::Init();
//
//    HAL_I2C::Init();
//
//    HAL_ADC::Init();
//
//    HAL_TIM2::Init();
//
//    HAL_TIM5::Init();
}
