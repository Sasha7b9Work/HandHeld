// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL_PINS.h"


namespace Device
{
    void ControlFunction(int type);
}


void Device::Init()
{
    HAL::Init();

    pinSW_LEFT.Init();

    ModeClock::Set(ModeClock::Hi);
}


void Device::Update()
{
//    ModeClock::Set(ModeClock::Hi);

    ControlFunction(1);

    ModeClock::Set(ModeClock::Sleep);

    ControlFunction(1);
//
//    ModeClock::Set(ModeClock::Low);
//
//    ControlFunction(0);
//
//    ModeClock::Set(ModeClock::Sleep);
//
//    ControlFunction(0);
}


void Device::ControlFunction(int type)
{
    if (type == 0)
    {
        for (int i = 0; i < 0xFFFF; i++)
        {
            pinSW_LEFT.ToHi();
            pinSW_LEFT.ToLow();
        }
    }
    else
    {
        for (int i = 0; i < 0xFFFFF; i++)
        {
            pinSW_LEFT.ToHi();
            pinSW_LEFT.ToLow();
        }
    }
}
