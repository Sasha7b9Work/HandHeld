// 2024/04/13 13:35:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageTime
{
    DEF_TIME(timeTime, PageMain::self, "ÂÐÅÌß", false);

    DEF_PAGE_1(pageTime, PageMain::self, "ÂÐÅÌß",
        &timeTime,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageTime;
}
