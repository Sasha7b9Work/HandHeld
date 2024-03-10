// 2024/03/07 09:44:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_5(pageCalls, PageMain::self, "ÍÀÑÒĞÎÉÊÈ ÂÛÇÎÂÎÂ",
    PageCalls::PageDoorBell::self,
    PageCalls::PageMobile::self,
    PageCalls::PageHomePhone::self,
    PageCalls::PageIntercom::self,
    PageCalls::PageSoundSensor::self
);

const Item *const PageCalls::self = &pageCalls;
