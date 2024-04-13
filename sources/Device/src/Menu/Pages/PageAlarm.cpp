// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    DEF_CHOICE_2(choiceEnabled, self, "бйкчвемн", &gset.alarm.enabled,
        "мер",
        "дю"
    );

    DEF_TIME(time, self, "бпелъ", true);

    DEF_DATE(date, self, "дюрю", false);

    DEF_CHOICE_7(choiceModeIndication, self, "нонбеыемхе", (uint8 *const)&gset.alarm.mode_indication,
        "гбсй",
        "ябер",
        "бхапн",
        "гбсй+ябер",
        "гбсй+бхапн",
        "ябер+бхапн",
        "бяе"
    );

    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", (uint8 *const)&gset.alarm.melody,
        Melody::Name(Melody::_1),
        Melody::Name(Melody::_2),
        Melody::Name(Melody::_3),
        Melody::Name(Melody::_4),
        Melody::Name(Melody::_5),
        Melody::Name(Melody::_6),
        Melody::Name(Melody::_7),
        Melody::Name(Melody::_8),
        Melody::Name(Melody::_9),
        Melody::Name(Melody::_10)
    );

    DEF_CHOICE_3(choiceVolume, self, "цпнлйнярэ", (uint8 *const)&gset.alarm.volume,
        "мхгйюъ",
        "япедмъъ",
        "бшянйюъ"
    );

    DEF_CHOICE_7(choiceColorBell, self, "жбер", (uint8 *const)&gset.alarm.colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_7(pageAlarm, PageMain::self, "асдхкэмхй",
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
