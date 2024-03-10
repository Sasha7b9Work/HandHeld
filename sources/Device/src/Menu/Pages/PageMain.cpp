// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"


DEF_TIME(timeWatch, PageMain::self, "����", false);

DEF_TIME(timeAlarm, PageMain::self, "���������", true);


DEF_PAGE_4(pageMain, nullptr, "����",
    &timeWatch,
    &timeAlarm,
    PageCalls::self,
    PageHistory::self,
    nullptr
);


const Item * const PageMain::self = &pageMain;
