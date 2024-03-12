// 2024/03/01 22:24:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/systick.h"
#include <gd32e23x.h>


void HAL::Init()
{
    systick_config();

    rcu_periph_clock_enable(RCU_GPIOA); 
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOF);

    rcu_periph_clock_enable(RCU_CFGCMP);

    rcu_periph_clock_enable(RCU_I2C1);

    nvic_irq_enable(TIMER2_IRQn, 0);            // Таймер на приёмник

    HAL_I2C::Init();

    // ----------------------------------------------------------------------------
    // TIMER2 Configuration:
    // TIMER2CLK = SystemCoreClock/7200 = 10KHz,the period is 1s(10000/10000 = 1s).
    // ----------------------------------------------------------------------------

    timer_parameter_struct timer_initpara;

    /* enable the peripherals clock */
    rcu_periph_clock_enable(RCU_TIMER2);

    /* deinit a TIMER */
    timer_deinit(TIMER2);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */
    timer_initpara.prescaler = 719;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 99;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER2, &timer_initpara);

    /* clear channel 0 interrupt bit */
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
    /* enable the TIMER interrupt */
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    /* enable a TIMER */
    timer_enable(TIMER2);
}
