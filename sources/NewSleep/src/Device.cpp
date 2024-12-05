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

//    Timer::Init();

//    pinSW_LEFT.Init();

    ModeClock::Set(ModeClock::Hi);

    ModeClock::Set(ModeClock::Sleep);
}


void Device::Update()
{
    while (true)
    {
        ModeClock::Set(Mode)
    }
//    ModeClock::Set(ModeClock::Low);
//
//    ControlFunction(0);
//
//    ModeClock::Set(ModeClock::Sleep);
//
//    ModeClock::LeaveSleep();
//
//    ModeClock::Set(ModeClock::Hi);
//
//    ControlFunction(1);
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
