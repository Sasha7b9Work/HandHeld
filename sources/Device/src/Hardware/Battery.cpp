// 2024/03/20 23:04:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/Battery.h"
#include "Hardware/HAL/HAL.h"


double Battery::GetVoltage()
{
    return (double)HAL_ADC::GetVoltage();
}
