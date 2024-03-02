// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL
{
    void Init();
}


struct I2C
{
    void Init();
};


extern I2C i2cCOMMON;       // Для часов и приёмника
