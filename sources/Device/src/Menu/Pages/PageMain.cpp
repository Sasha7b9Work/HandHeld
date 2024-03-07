// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"


DEF_TIME(timeWatch, PageMain::self, "Часы");


DEF_PAGE_4(pageMain, nullptr, "Меню",
    &timeWatch,
    PageAlarm::self,
    PageCalls::self,
    PageHistory::self
);


const Item * const PageMain::self = &pageMain;
