// 2024/03/02 19:47:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Settings/Source.h"


struct SettingsSource
{
    uint8 melody;               // ������� �������
    uint8 volume;               // ��������� ������� �������
    ModeSource::E mode_source;  // ����� ���������
};


struct Settings
{
    SettingsSource sources[Source::Count];
    RTCDateTime    time_alarm;                      // ����� ����������
};


extern Settings gset;
