// 2024/03/20 09:00:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Vibrato.h"
#include "Hardware/Timer.h"
#include "Settings/Source.h"
#include "Modules/PCF8563/PCF8563.h"
#include <gd32e23x.h>


namespace Vibrato
{
    namespace Driver
    {
        static void On()
        {
            gpio_bit_set(GPIOA, GPIO_PIN_10);
        }

        static void Off()
        {
            gpio_bit_reset(GPIOA, GPIO_PIN_10);
        }
    }

    static uint time_start = 0;
    static bool is_enabled = false;
}


void Vibrato::Init()
{
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    Driver::Off();
}


void Vibrato::Enable()
{
    is_enabled = true;
    time_start = TIME_MS;
}


void Vibrato::Disable()
{
    is_enabled = false;
    Driver::Off();
}


bool Vibrato::IsRunning()
{
    return gpio_input_bit_get(GPIOA, GPIO_PIN_10) != RESET;
}


void Vibrato::Update()
{
    if (!is_enabled)
    {
        return;
    }

    Source::E source = PCF8563::IsAlarmed() ? Source::Test : Source::Current();

    if (SourceScript::GetForVibro(source, TIME_MS - time_start))
    {
        Driver::On();
    }
    else
    {
        Driver::Off();
    }
}
