// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ModeClock
{
    enum E
    {
        DeepSleep,  // ������ �����
        Low,        // �������� ������� 3MHz
        Hi,         // ������� 52��� ��� ��������� ������
        Count
    };

    static void Set(E);

    static void LeaveDeepSleep();

    static bool IsDeepSleep() { return current == DeepSleep; }
    static bool IsLow()       { return current == Low; }
    static bool IsHi()        { return current == Hi; }

private:

    static E current;
};


namespace HAL
{
    void Init();

    void DeInit();
}


// ������� �������
namespace HAL_ADC
{
    void Init();

    float GetVoltage(bool force);
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

    void Start();
}


namespace HAL_ROM
{
    static const uint ADDRESS_BEGIN = 0x8000000;
    static const uint SIZE_PAGE = 1024;
    static const int PAGE_FIRST_JOURNAL = 61;       // ������ ������ �������
    static const int PAGE_LAST_JOURNAL = 64;        // ��������� ������ ������� (� �� �������� ��� ���)

    // ������� �������� �� 0 �� 63
    void ErasePage(int);

    // address ������ ���� ������ 4
    void WriteBuffer(uint address, const void *buffer, int size);

    // address ������ ���� ������ 4
    void ReadBuffer(uint address, void *buffer, int size);
}
