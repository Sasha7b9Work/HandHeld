// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace HAL
{
    void Init();
}


// ������� �������
namespace HAL_ADC
{
    void Init();

    float GetVoltage();
}


// ��� �������
namespace HAL_I2C
{
    void Init();

    bool Write(uint8 command, uint8 *data, int size);

    bool Read(uint8 reg, uint8 *buf, uint16 len);
}


// ��� ��������
namespace HAL_TIM2
{
    void Init();
}


namespace HAL_ROM
{
    // ������� �������� �� 0 �� 63
    void ErasePage(int);

    // address ������ ���� ������ 4
    void WriteBuffer(uint address, const void *buffer, int size);

    // address ������ ���� ������ 4
    void ReadBuffer(uint address, void *buffer, int size);
}
