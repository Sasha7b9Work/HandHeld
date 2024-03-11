// 2024/03/01 22:46:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Display/Display.h"
#include <gd32e23x.h>

/*
*  ��������� - 1111110000001100111100
*  ���������� ���� ���
*  ���������� 0x3f033cfc0cf3 0xf033cfc0cf3f033c
*/


namespace CMT2210AW
{
    struct Data
    {
        int num_tick = 0;
        uint64 words[2];

        void Reset();

        void AppendBit(bool);

        // ���������� ���������� ���������� ���
        int VerifyPreambule();
    };

    static Data data;

    static bool clocks_is_run = false;          // ���� true, �� ��� ������� - ������������ ������

    // �������� ���������� �� SCK
    void EnableEXTI_SCK();

    // ���������� ���������� �� SCK
    void DisableEXTI_SCK();
}


void CMT2210AW::Init()
{
    pinDOUT.Init();
//    pinSCK.Init();          // ���� ��� ����� ������������ ��� ����������� ������ �������

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
}


void CMT2210AW::Data::AppendBit(bool bit)
{
    words[1] <<= 1;

    if (words[0] & 0x8000000000000000)
    {
        words[1] |= 1;
    }

    words[0] <<= 1;

    if (bit)
    {
        words[0] |= 1;
    }

    num_tick++;

    if (num_tick == 110)
    {
        Display::SetPreambule(VerifyPreambule());

        Reset();
    }
}


int CMT2210AW::Data::VerifyPreambule()
{
    uint64 word1 = 0x3f033cfc0cf3;
    uint64 word0 = 0xf033cfc0cf3f033c;

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

    result -= 18;           // ���������� 110 ���, ���������� ������ 18 �� 128

    return result;
}


void CMT2210AW::Data::Reset()
{
    num_tick = 0;
    words[0] = 0;
    words[0] = 0;
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
