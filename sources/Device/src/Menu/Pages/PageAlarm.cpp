// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    DEF_CHOICE_2(choiceEnabled, self, "¬ Àﬁ◊≈ÕŒ", &gset.alarm.enabled,
        "Õ≈“",
        "ƒ¿"
    );

    DEF_TIME(time, self, "¬–≈Ãﬂ", true);

    DEF_DATE(date, self, "ƒ¿“¿", false);

    DEF_CHOICE_MODE_INDICATION(gset.alarm.mode_indication);

    DEF_CHOICE_MELODY(gset.alarm.melody);

    DEF_CHOICE_VOLUME(gset.alarm.volume);

    DEF_CHOICE_COLOR(gset.alarm.color);

    DEF_PAGE_7(pageAlarm, PageMain::self, "¡”ƒ»À‹Õ» ",
        &choiceEnabled,
        &time,
        &date,
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
