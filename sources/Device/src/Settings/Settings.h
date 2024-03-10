// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"


struct PackedTime
{

};


// Источинк сигнала
struct Source
{
    enum E
    {
        PhoneHome,      // Домашний телефон
        Mobile,         // Мобильный телефон
        Intercom,       // Домофон
        Bell,           // Дверной звонок
        Sensor,         // Акстический датчик
        Count
    };

    Source(E v) : value(v) { }

    void Draw(int x, int y, const Color &color = Color::NUMBER) const;

private:
    E value;
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
    PackedTime time_alarm;                      // Время будильника
};


extern Settings gset;
