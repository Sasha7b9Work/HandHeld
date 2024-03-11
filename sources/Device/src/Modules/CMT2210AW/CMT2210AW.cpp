// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"
#include <gd32e23x.h>


namespace CMT2210AW
{
    struct Data
    {
        int num_tick = 0;
        uint64 bytes[2];

        void Reset();

        void AppendBit(bool);
    };

    static Data data;

    static bool clocks_is_run = false;          // Если true, то идёт частота - обрабатываем данные

    // Включить прерывание по SCK
    void EnableEXTI_SCK();

    // Выкллючить прерывание по SCK
    void DisableEXTI_SCK();
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
    if (!clocks_is_run)
    {
        return;
    }

    data.AppendBit(pinDOUT.IsHi());

    Display::SetReceiverValue((uint)data.bytes[0]);
}


void CMT2210AW::Data::AppendBit(bool bit)
{
    bytes[0] >>= 1;

    if (bytes[1] & 1)
    {
        bytes[0] |= 0x8000000000000000;
    }
    else
    {
        bytes[0] &= 0x7000000000000000;
    }

    bytes[1] >>= 1;

    if (bit)
    {
        bytes[1] |= 0x8000000000000000;
    }
    else
    {
        bytes[1] &= 0x7000000000000000;
    }
}


void CMT2210AW::Data::Reset()
{
    num_tick = 0;
    bytes[0] = 0;
    bytes[0] = 0;
}


void CMT2210AW::CallbackOnStartSCK()
{
    clocks_is_run = true;

    data.Reset();

    DisableEXTI_SCK();
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
