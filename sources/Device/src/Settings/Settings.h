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

private:
    E value;
};


struct SettingsSource
{
    uint8 melody;           // ������� �������
    uint8 volume;           // ��������� ������� �������
    uint8 enabled_led;      // ���������� �����������
    uint8 enabled_melody;   // ���������� ������
    uint8 enabled_vibrato;  // ���������� ���������
};


struct Settings
{
    SettingsSource sources[Source::Count];
    PackedTime time_alarm;                      // ����� ����������
};


extern Settings gset;
