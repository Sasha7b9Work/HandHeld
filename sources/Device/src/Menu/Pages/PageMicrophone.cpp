// 2024/04/13 13:02:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMicrophone
{
    DEF_CHOICE_7(choiceModeSource, self, "пефхл", (uint8 *const)&gset.sources[Source::Microphone].mode_source,
        "гбсй",
        "ябер",
        "бхапн",
        "гбсй+ябер",
        "гбсй+бхапн",
        "ябер+бхапн",
        "бяе"
    );

    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", (uint8 *const)&gset.sources[Source::Microphone].melody,
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

    DEF_CHOICE_3(choiceVolume, self, "цпнлйнярэ", (uint8 *const)&gset.sources[Source::Microphone].volume,
        "мхгйюъ",
        "япедмъъ",
        "бшянйюъ"
    );

    DEF_CHOICE_7(choiceColorBell, self, "жбер", (uint8 *const)&gset.sources[Source::Microphone].colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_4(pageSoundSensor, PageMain::self, "лхйпнтнм",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageSoundSensor;
}
