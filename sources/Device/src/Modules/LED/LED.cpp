// 2024/03/20 08:59:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Timer.h"
#include "Modules/LED/LED.h"
#include "Modules/LED/driverLED.h"


namespace LED
{
    static bool is_enabled = false;

    static uint time_enable = 0;

    // ����� ������� � �������������
    static const uint time_flash = 500;
}


void LED::Init()
{
    Driver::Init();

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
        Driver::On();
    }
    else
    {
        Driver::Off();
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
    return Driver::IsFired();
}