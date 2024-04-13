// 2024/04/13 12:39:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageDoorBell
{
    DEF_CHOICE_7(choiceModeSource, self, "пефхл", (uint8 *const)&gset.sources[Source::DoorBell].mode_source,
        "гбсй",
        "ябер",
        "бхапн",
        "гбсй+ябер",
        "гбсй+бхапн",
        "ябер+бхапн",
        "бяе"
    );

    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", (uint8 *const)&gset.sources[Source::DoorBell].melody,
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

    DEF_CHOICE_3(choiceVolume, self, "цпнлйнярэ", (uint8 *const)&gset.sources[Source::DoorBell].volume,
        "мхгйюъ",
        "япедмъъ",
        "бшянйюъ"
    );

    DEF_PAGE_3(pageDoorBell, PageMain::self, "дбепмни гбнмнй",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageDoorBell;
}
