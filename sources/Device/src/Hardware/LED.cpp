// 2024/03/20 08:59:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LED.h"
#include "Hardware/Timer.h"
#include <gd32e23x.h>


namespace LED
{
    static bool is_enabled = false;

    static uint time_enable = 0;

    // Время мигания в микросекундах
    static const uint time_flash = 500;
}


void LED::Init()
{
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    Disable();
}


void LED::Update()
{
    if (!is_enabled)
    {
        return;
    }

    uint time_passed = (TIME_MS - time_enable) / time_flash;

    if ((time_passed % 2) == 0)
    {
        gpio_bit_set(GPIOA, GPIO_PIN_2);
    }
    else
    {
        gpio_bit_reset(GPIOA, GPIO_PIN_2);
    }
}


void LED::Enable()
{
    is_enabled = true;

    time_enable = TIME_MS;
}


void LED::Disable()
{
    is_enabled = false;
}


bool LED::IsFired()
{
    return gpio_input_bit_get(GPIOA, GPIO_PIN_2) != RESET;
}
