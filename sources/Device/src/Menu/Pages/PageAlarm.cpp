// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Modules/PCF8563/PCF8563.h"


namespace PageAlarm
{
    static void FuncOnChange()
    {
        if (gset.alarm.enabled)
        {
            PCF8563::SetAlarm(&gset.alarm.time);
        }
        else
        {
            PCF8563::AlarmInterruptEnable(false);
        }
    }

    DEF_CHOICE_2(choiceEnabled, self, "��������", &gset.alarm.enabled,
        "���",
        "��",
        FuncOnChange
    );

    DEF_TIME(time, self, "�����", true);

    DEF_CHOICE_MODE_INDICATION(gset.alarm.mode_indication);

    DEF_CHOICE_MELODY(gset.alarm.melody);

    DEF_CHOICE_VOLUME(gset.alarm.volume);

    DEF_CHOICE_COLOR(gset.alarm.color);

    DEF_PAGE_6(pageAlarm, PageMain::self, "���������",
        &choiceEnabled,
        &time,
        &choiceModeIndication,
        &choiceMelody,
        &choiceVolume,
        &choiceColor,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageAlarm;
}
