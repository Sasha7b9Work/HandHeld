// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"


void Device::Init()
{
    HAL::Init();

    Timer::Init();
}


void Device::Update()
{
    ModeClock::Set(ModeClock::DeepSleep);

    ModeClock::LeaveDeepSleep();
}
