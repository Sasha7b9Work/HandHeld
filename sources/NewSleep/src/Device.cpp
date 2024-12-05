// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL_PINS.h"


static void ControlFunction(int type);


void Device::Init()
{
    HAL::Init();

    Timer::Init();

    pinSW_LEFT.Init();
}


void Device::Update()
{
    ModeClock::Set(ModeClock::Low);

    ControlFunction(0);

    ModeClock::Set(ModeClock::Sleep);

    ModeClock::LeaveSleep();

    ModeClock::Set(ModeClock::Hi);

    ControlFunction(1);
}


static void ControlFunction(int type)
{
    if (type == 0)
    {
        for (int i = 0; i < 0xFFF; i++)
        {
            pinSW_LEFT.ToHi();
            pinSW_LEFT.ToLow();
        }
    }
    else
    {
        for (int i = 0; i < 0xFFF; i++)
        {
            pinSW_LEFT.ToHi();
            pinSW_LEFT.ToLow();
        }
    }
}
