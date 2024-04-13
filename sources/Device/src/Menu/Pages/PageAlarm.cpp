// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    DEF_CHOICE_2(choiceEnabled, self, "��������", &gset.alarm.enabled,
        "���",
        "��"
    );

    DEF_TIME(time, self, "�����", true);

    DEF_DATE(date, self, "����", false);

    DEF_CHOICE_7(choiceModeIndication, self, "����������", (uint8 *const)&gset.alarm.mode_indication,
        "����",
        "����",
        "�����",
        "����+����",
        "����+�����",
        "����+�����",
        "���"
    );

    DEF_CHOICE_MELODY_PAGE(gset.alarm.melody)

    DEF_CHOICE_3(choiceVolume, self, "���������", (uint8 *const)&gset.alarm.volume,
        "������",
        "�������",
        "�������"
    );

    DEF_CHOICE_7(choiceColorBell, self, "����", (uint8 *const)&gset.alarm.colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_7(pageAlarm, PageMain::self, "���������",
        &choiceEnabled,
        &time,
        &date,
        &choiceModeIndication,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageAlarm;
}
