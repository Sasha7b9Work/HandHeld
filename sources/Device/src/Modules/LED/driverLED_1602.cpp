// 2024/05/15 19:51:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/LED/driverLED.h"
#include <gd32e23x.h>


namespace LED
{
    namespace Driver
    {
        static bool is_fired = false;
    }
}


void LED::Driver::Init()
{

}


void LED::Driver::On()
{
    is_fired = true;
}


void LED::Driver::Off()
{
    is_fired = false;
}


bool LED::Driver::IsFired()
{
    return is_fired;
}
