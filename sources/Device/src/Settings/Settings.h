// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct PackedTime
{

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
