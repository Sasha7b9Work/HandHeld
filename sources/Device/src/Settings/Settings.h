// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Modules/PCF8563/PCF8563.h"

// �������� �������
struct Source
{
    enum E
    {
        DoorBell,       // ������� ������
        Mobile,         // ��������� �������
        PhoneHome,      // �������� �������
        Intercom,       // �������
        SoundSensor,    // ����������� ������
        Count
    };

    Source(E v) : value(v) { }

    // ���������� ������ ��� ����������
    void DrawIcon(int x, int y, const Color &color = Color::NUMBER) const;

    // ���������� ��� ��������� �������
    static void Receive(E);

    // ���������� true, ���� ���� ���
    static bool IsReceived(E);

    static void Update();

    static pchar Name(E);

private:
    E value;
    static uint time_recv[Count];

    // ������� ������ ������, ��� ������ � �������
    struct Queue
    {
        // �������� � �����
        static void Push(Source::E);

        // ������� �� ������
        static void Pop();

        static bool IsConsist(Source::E);

        static int Size()
        {
            return size;
        }

        static bool IsEmpty()
        {
            return Size() == 0;
        }

    private:

        static Source::E buffer[Source::Count];
        static int size;
    };
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
    RTCDateTime    time_alarm;                      // ����� ����������
};


extern Settings gset;
