// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct PackedTime
{

};


struct Settings
{
    uint8 melody;           // Текущая мелодия
    uint8 volume;           // Громкость текущей мелодии
    uint8 enabled_led;      // Оповещение светодиодом
    uint8 enabled_melody;   // Оповещение звуком
    uint8 enabled_vibrato;  // Оповещение вибрацией
    PackedTime time_alarm;  // Время будильника
};
