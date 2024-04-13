// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Settings/Source.h"


struct SettingsSource
{
    uint8 melody;               // Текущая мелодия
    uint8 volume;               // Громкость текущей мелодии
    ModeSource::E mode_source;  // Режим индикации
};


struct Settings
{
    SettingsSource sources[Source::Count];
    RTCDateTime    time_alarm;                      // Время будильника
};


extern Settings gset;
