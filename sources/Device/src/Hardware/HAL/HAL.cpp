// 2024/03/01 22:24:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"


void HAL::Init()
{
    i2cCOMMON.Init();
    i2cTFT.Init();
}
