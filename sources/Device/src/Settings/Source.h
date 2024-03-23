// 2024/03/23 17:28:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


// Источинк сигнала
struct Source
{
    enum E
    {
        DoorBell,       // Дверной звонок
        Mobile,         // Мобильный телефон
        PhoneHome,      // Домашний телефон
        Intercom,       // Домофон
        SoundSensor,    // Акстический датчик
        Count
    };

    Source(E v) : value(v) { }

    // Нарисовать иконку для оповещения
    void DrawIcon(int x, int y, const Color &color = Color::NUMBER) const;

    // Вызывается при получении сигнала
    static void Receive(E);

    // Возвращает true, если приём идёт
    static bool IsReceived(E);

    static void Update();

    static pchar Name(E);

private:
    Source::E value;

    // Который первый входит, тот первый и выходит
    struct Queue
    {
        // Добавить в хвост
        static void Push(Source::E);

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

        static Source::E buffer[Source::Count];         // Здесь принятые события в том порядке, как принимались
        static uint time_recv[Source::Count];           // Время начала аларма
        static int size;

        // Удалить те, срок действия которых истёк
        static void DeleteOld();
    };
};
