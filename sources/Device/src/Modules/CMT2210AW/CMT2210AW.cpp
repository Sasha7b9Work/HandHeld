// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"
#include <gd32e23x.h>


namespace CMT2210AW
{
    static uint value = 0;
}


void CMT2210AW::Init()
{
    pinDOUT.Init();
//    pinSCK.Init();          // Этот пин будем использовать для определения начала посылки

    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_13);

    EnableEXTI_SCK();
}


void CMT2210AW::CallbackOn1MS()
{
    value <<= 1;

    if (pinDOUT.IsHi())
    {
        value |= 1;
    }
    else
    {
        value &= 0xFFFFFFFE;
    }

    Display::SetReceiverValue(value);
}


void CMT2210AW::EnableEXTI_SCK()
{
    /* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(EXTI4_15_IRQn, 2U);

    /* connect key EXTI line to key GPIO pin */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN13);

    /* configure key EXTI line */
    exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_flag_clear(EXTI_13);
}


void CMT2210AW::DisableEXTI_SCK()
{
    nvic_irq_disable(EXTI4_15_IRQn);
}
