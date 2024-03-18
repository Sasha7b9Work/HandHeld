// 2024/03/02 09:30:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/systick.h"
#include <gd32e23x.h>


uint timer_counter = 0;


void Timer::Init()
{
    rcu_periph_clock_enable(RCU_TIMER13);
    timer_deinit(TIMER13);

    timer_parameter_struct timer_initpara =
    {
        0,
        TIMER_COUNTER_EDGE,
        TIMER_COUNTER_UP,
        TIMER_CKDIV_DIV1,
        65535,
        0
    };

    timer_init(TIMER13, &timer_initpara);
}


void Timer::Delay(uint timeMS)
{
    delay_1ms(timeMS);
}


void TimeMeterMS::Reset()
{
    time_reset = timer_counter;
}


uint TimeMeterMS::ElapsedTime() const
{
    return timer_counter - time_reset;
}


void TimeMeterUS::Reset()
{
    timer_enable(TIMER13);
    timer_counter_value_config(TIMER13, 0);
}

uint TimeMeterUS::ElapsedUS() const
{
    return timer_counter_read(TIMER13) / 72;
}
