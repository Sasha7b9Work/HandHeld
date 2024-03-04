// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL
{
    void Init();
}


namespace HAL_I2C
{
    void Init();

    bool Write(uint8 command, uint8 *data, int size);

    bool Read(uint8 reg, uint8 *buf, uint16 len);
}
