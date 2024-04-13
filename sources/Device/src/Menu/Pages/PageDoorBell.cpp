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

    DEF_CHOICE_MELODY(Source::DoorBell);

    DEF_CHOICE_3(choiceVolume, self, "цпнлйнярэ", (uint8 *const)&gset.sources[Source::DoorBell].volume,
        "мхгйюъ",
        "япедмъъ",
        "бшянйюъ"
    );

    DEF_CHOICE_7(choiceColorBell, self, "жбер", (uint8 *const)&gset.sources[Source::DoorBell].colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_4(pageDoorBell, PageMain::self, "дбепмни гбнмнй",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageDoorBell;
}
