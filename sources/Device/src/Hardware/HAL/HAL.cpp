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

    nvic_irq_enable(TIMER14_IRQn, 1);           // Таймер на ШИМ звука

    HAL_I2C::Init();

    timer_parameter_struct timer_initpara;

    /* enable the peripherals clock */
    rcu_periph_clock_enable(RCU_TIMER2);

    /* deinit a TIMER */
    timer_deinit(TIMER2);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */
//    timer_initpara.prescaler = 36864;                    // F = 72e6 / 36864 = 1953.125Гц; T = 1 / F = 1 / 1953.125 * 2 = 0.001024 сек
    timer_initpara.prescaler = 14400;                   // 409.6 мкс
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 1;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER2, &timer_initpara);

    /* clear channel 0 interrupt bit */
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
    /* enable the TIMER interrupt */
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    /* enable a TIMER */
    timer_enable(TIMER2);
}
