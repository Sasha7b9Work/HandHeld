// 2024/04/14 16:45:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <gd32e23x.h>


void HAL_TIM5::Init()
{
    timer_parameter_struct timer_initpara;

    /* deinit a TIMER */
    timer_deinit(TIMER5);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */

    // prescaler = 400e-6 / (1 / 78000000) / 2
    // prescaler = 400e-6 * 78000000 / 2
    // prescaler = 400 * 78 / 2

    timer_initpara.prescaler = (uint16)(SystemCoreClock / 1000000 * 50 / 2);   // 50 мс
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 2000;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_init(TIMER5, &timer_initpara);
}


void HAL_TIM5::Start(uint timeMS)
{
    TIMER_PSC(TIMER5) = (uint16)(SystemCoreClock / 1000000 * timeMS / 2);

    timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);

    timer_interrupt_enable(TIMER5, TIMER_INT_UP);

    timer_enable(TIMER5);
}


void HAL_TIM5::Stop()
{
    timer_disable(TIMER5);

    timer_interrupt_disable(TIMER5, TIMER_INT_UP);
}
