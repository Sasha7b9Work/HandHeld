// 2024/03/23 17:28:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


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

    // �������� ������ �������� �����
    static void CancelFirst();

    // ���������� true, ���� ���� ���
    static bool IsReceived(E);

    static void Update();

    static pchar Name(E);

private:
    Source::E value;

    // ������� ������ ������, ��� ������ � �������
    struct Queue
    {
        // �������� � �����
        static void Push(Source::E);

        // ������� ������ �� �������
        static void PopFirst();

        static Source::E At(int);

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

        static Source::E buffer[Source::Count];         // ����� �������� ������� � ��� �������, ��� �����������
        static uint time_recv[Source::Count];           // ����� ������ ������
        static int size;

        // ������� ��, ���� �������� ������� ����
        static void DeleteOld();
    };
};
