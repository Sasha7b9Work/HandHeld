// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"
#include <gd32e23x.h>

/*
*  Преамбула - 1111110000001100111100
*  Повторённая пять раз
*  Получается 0x3f033cfc0cf3 0xf033cfc0cf3f033c
*/


namespace CMT2210AW
{
    struct Data
    {
        uint64 words[2] = { 0, 0 };

        void Reset();

        void AppendBit(bool);

        // Возвращает количество правильных бит
        int VerifyPreambule();
    };

    static Data data;

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
    data.AppendBit(pinDOUT.IsHi());
}


void CMT2210AW::Data::AppendBit(bool bit)
{
    words[0] <<= 1;

    if (words[1] & 0x8000000000000000)
    {
        words[0] |= 1;
    }

    words[1] <<= 1;

    if (bit)
    {
        words[1] |= 1;
    }

    Display::SetPreambule(VerifyPreambule());
}


int CMT2210AW::Data::VerifyPreambule()
{
    uint64 word0 =     0x3f033cfc0cf3;
    uint64 word1 = 0xf033cfc0cf3f033c;

    words[0] &= 0x00003ff33fffffff;

    uint64 xor0 = words[0] ^ word0;
    uint64 xor1 = words[1] ^ word1;

    int result = 0;

    for (int i = 0; i < 64; i++)
    {
        if ((xor0 & (((uint64)1) << i)) != 0)
        {
            result++;
        }

        if ((xor1 & (((uint64)1) << i)) != 0)
        {
            result++;
        }
    }

    result -= 18;           // Сравниваем 110 бит, откидываем лишние 18 из 128

    return result;
}


void CMT2210AW::Data::Reset()
{
    words[0] = 0;
    words[0] = 0;
}


void CMT2210AW::CallbackOnStartSCK()
{
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
