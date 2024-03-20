// 2024/03/20 09:00:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Vibrato.h"
#include <gd32e23x.h>


void Vibrato::Init()
{
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    Disable();
}


void Vibrato::Enable()
{
    gpio_bit_set(GPIOA, GPIO_PIN_10);
}


void Vibrato::Disable()
{
    gpio_bit_reset(GPIOA, GPIO_PIN_10);
}


bool Vibrato::IsRunning()
{
    return gpio_input_bit_get(GPIOA, GPIO_PIN_10) != RESET;
}
