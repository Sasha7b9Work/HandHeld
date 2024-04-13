// 2024/04/13 12:47:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMobile
{
    DEF_CHOICE_7(choiceModeSource, self, "пефхл", (uint8 *const)&gset.sources[Source::Mobile].mode_source,
        "гбсй",
        "ябер",
        "бхапн",
        "гбсй+ябер",
        "гбсй+бхапн",
        "ябер+бхапн",
        "бяе"
    );

    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", &gset.sources[Source::Mobile].melody,
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

    DEF_CHOICE_3(choiceVolume, self, "цпнлйнярэ", (uint8 *const)&gset.sources[Source::Mobile].volume,
        "мхгйюъ",
        "япедмъъ",
        "бшянйюъ"
    );

    DEF_PAGE_3(pageMobile, PageMain::self, "лнахкэмши рекетнм",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageMobile;
}
