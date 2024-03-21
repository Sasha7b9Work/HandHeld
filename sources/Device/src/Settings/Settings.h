// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Modules/PCF8563/PCF8563.h"


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

    void DrawSmall(int x, int y, const Color &color = Color::NUMBER) const;

    // Вызывается при получении сигнала
    static void Receive(E);

    // Возвращает true, если приём идёт
    static bool IsReceived(E);

    static void Update();

    static pchar Name(E);

private:
    E value;
    static uint time_recv[Count];
};


struct SettingsSource
{
    uint8 melody;           // Текущая мелодия
    uint8 volume;           // Громкость текущей мелодии
    uint8 enabled_led;      // Оповещение светодиодом
    uint8 enabled_melody;   // Оповещение звуком
    uint8 enabled_vibrato;  // Оповещение вибрацией
};


struct Settings
{
    SettingsSource sources[Source::Count];
    RTCDateTime    time_alarm;                      // Время будильника
};


extern Settings gset;
