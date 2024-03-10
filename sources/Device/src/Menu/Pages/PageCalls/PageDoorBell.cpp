// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


DEF_CHOICE(choiceMelody, PageCalls::PageDoorBell::self, "Мелодия", &gset.sources[Source::Bell].melody, 10);


DEF_PAGE_5(pageDoorBell, PageCalls::self, "Дверной звонок",
    &choiceMelody,
    &choiceMelody,
    &choiceMelody,
    &choiceMelody,
    &choiceMelody
);


const Item *const PageCalls::PageDoorBell::self = &pageDoorBell;
