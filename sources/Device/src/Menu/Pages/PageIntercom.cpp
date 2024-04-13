// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageIntercom
{
    DEF_CHOICE_7(choiceModeSource, self, "пефхл", (uint8 *const)&gset.sources[Source::Intercom].mode_source,
        "гбсй",
        "ябер",
        "бхапн",
        "гбсй+ябер",
        "гбсй+бхапн",
        "ябер+бхапн",
        "бяе"
    );

    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", &gset.sources[Source::Intercom].melody,
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10"
    );

    DEF_CHOICE_10(choiceVolume, self, "цпнлйнярэ", &gset.sources[Source::Intercom].volume,
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10"
    );

    DEF_PAGE_3(pageIntercom, PageMain::self, "днлнтнм",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );


    const Item *const self = &pageIntercom;
}
