// 2024/03/01 22:30:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by// 
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/Power.h"


int main()
{
    HAL::Init();

    Keyboard::Init();

    Power::DeepSleep();

    while(true)
    {
    }
}
