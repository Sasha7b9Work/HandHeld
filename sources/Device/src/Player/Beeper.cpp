// 2024/03/03 17:06:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Player/Beeper.h"
#include "Hardware/HAL/HAL_PINS.h"
#include "Hardware/Timer.h"


void Beeper::Init()
{
    pinSOUND.Init();
}


void Beeper::Beep()
{
    while (true)
    {
        pinSOUND.ToHi();
        Timer::Delay(1);
        pinSOUND.ToLow();
        Timer::Delay(1);
    }
}


void Beeper::CallbackOnOutputSample(uint8)
{

}


void Beeper::CallbackOnStartMelody()
{

}


void Beeper::CallbackOnStopMelody()
{

}
