// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL
{
    void Init();
}


// Уровень батареи
namespace HAL_ADC
{
    void Init();

    float GetVoltage();
}


// Для дисплея
namespace HAL_I2C
{
    void Init();

    bool Write(uint8 command, uint8 *data, int size);

    bool Read(uint8 reg, uint8 *buf, uint16 len);
}


// Для приёмника
namespace HAL_TIM2
{
    void Init();
}


namespace HAL_ROM
{
    // Стиреть страницу от 0 до 63
    void ErasePage(int);

    // address должен быть кратен 4
    void WriteBuffer(uint address, const void *buffer, int size);

    // address должен быть кратен 4
    void ReadBuffer(uint address, void *buffer, int size);
}
