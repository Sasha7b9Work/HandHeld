// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"


struct PackedTime
{

};


// �������� �������
struct Source
{
    enum E
    {
        PhoneHome,      // �������� �������
        Mobile,         // ��������� �������
        Intercom,       // �������
        Bell,           // ������� ������
        Sensor,         // ����������� ������
        Count
    };

    Source(E v) : value(v) { }

    void Draw(int x, int y, const Color &color = Color::NUMBER) const;

    static Source PHONE_HOME;

private:
    E value;
};


struct Settings
{
    uint8 melody;           // ������� �������
    uint8 volume;           // ��������� ������� �������
    uint8 enabled_led;      // ���������� �����������
    uint8 enabled_melody;   // ���������� ������
    uint8 enabled_vibrato;  // ���������� ���������
    PackedTime time_alarm;  // ����� ����������
};
