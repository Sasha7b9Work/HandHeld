// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL_PINS.h"


static void ControlFunction();


void Device::Init()
{
    HAL::Init();

    Timer::Init();

    pinSW_LEFT.Init();
}


void Device::Update()
{
    ModeClock::Set(ModeClock::Low);

    ControlFunction();

    ModeClock::Set(ModeClock::Sleep);

    ModeClock::LeaveSleep();

    ModeClock::Set(ModeClock::Hi);

    ControlFunction();
}


static void ControlFunction()
{
    for (int i = 0; i < 100; i++)
    {
        pinSW_LEFT.ToHi();
        pinSW_LEFT.ToLow();
    }
}
