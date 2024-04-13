// 2024/04/13 12:39:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageDoorBell
{
    DEF_SOURCE_CHOICES(Source::DoorBell);

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
