// 2024/03/01 22:30:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by// 
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/Power.h"
#include "systick.h"


int main()
{
    HAL::Init();

    Keyboard::Init();

    delay_1ms(3000);

    Power::DeepSleep();

    while(true)
    {
    }
}
