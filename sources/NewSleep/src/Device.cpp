// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL_PINS.h"


namespace Device
{
    void ControlFunction(bool pins, int type);
}


void Device::Init()
{
    HAL::Init();

    pinSW_LEFT.Init();
}


void Device::Update()
{
    ModeClock::Set(ModeClock::Hi);

    ControlFunction(true, 1);
    ControlFunction(false, 1);

    ModeClock::Set(ModeClock::Sleep);

    ModeClock::Set(ModeClock::Low);

    ControlFunction(true, 0);
    ControlFunction(false, 0);
}


void Device::ControlFunction(bool pins, int type)
{
    if (type == 0)
    {
        if (pins)
        {
            for (int i = 0; i < 0xFFFF; i++)
            {
                pinSW_LEFT.ToHi();
                pinSW_LEFT.ToLow();
            }
        }
        else
        {
            volatile int i = 0xFFFFFF;

            while (i--)
            {
            }
        }
    }
    else
    {
        if (pins)
        {
            for (int i = 0; i < 0xFFFFF; i++)
            {
                pinSW_LEFT.ToHi();
                pinSW_LEFT.ToLow();
            }
        }
        else
        {
            volatile int i = 0xFFFFFFF;

            while (i--)
            {
            }
        }
    }
}
