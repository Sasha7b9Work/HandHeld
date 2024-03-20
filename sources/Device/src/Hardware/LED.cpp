// 2024/03/20 08:59:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LED.h"
#include <gd32e23x.h>


void LED::Init()
{
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    Disable();
}


void LED::Enable()
{
    gpio_bit_set(GPIOA, GPIO_PIN_2);
}


void LED::Disable()
{
    gpio_bit_reset(GPIOA, GPIO_PIN_2);
}
