// 2024/03/03 17:06:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Player/Beeper.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Hardware/Timer.h"
#include <gd32e23x.h>


namespace Beeper
{
    // PA3 - Alternate TIMER14_CH1 AF0
}


void Beeper::Init()
{
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_3);

    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER14);

    timer_struct_para_init(&timer_initpara);

    // TIMER14CLK = SystemCoreClock / 36 = 1MHz, the PWM frequency is 4000 Hz
    timer_initpara.prescaler = 35;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 249;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER14, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* configure TIMER channel output function */
    timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER14, TIMER_CH_1, &timer_ocinitpara);

    /* CH1 configuration in PWM mode0, duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER14, TIMER_CH_1, 125);
    timer_channel_output_mode_config(TIMER14, TIMER_CH_1, TIMER_OC_MODE_PWM1);
    timer_channel_output_shadow_config(TIMER14, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(TIMER14, ENABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER14);

    timer_interrupt_flag_clear(TIMER14, TIMER_INT_FLAG_CH1);
    timer_interrupt_enable(TIMER14, TIMER_INT_CH1);

    /* TIMER2 counter enable */
    timer_enable(TIMER14);
}


void Beeper::Beep()
{
    while (true)
    {
        Timer::Delay(1);
        Timer::Delay(1);
    }
}


void Beeper::CallbackOnOutputSample(uint8)
{

}


void Beeper::CallbackOnStartMelody()
{

}


void Beeper::CallbackOnStopMelody()
{

}
