// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    DEF_TIME(timeAlarm, PageAlarm::self, "¡”ƒ»À‹Õ» ", true);

    DEF_PAGE_1(pageAlarm, PageMain::self, "¡”ƒ»À‹Õ» ",
        &timeAlarm,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageAlarm;
}
