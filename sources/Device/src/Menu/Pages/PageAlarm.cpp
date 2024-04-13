// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    DEF_TIME(time, self, "�����", true);

    DEF_DATE(date, self, "����", false);

    DEF_PAGE_2(pageAlarm, PageMain::self, "���������",
        &time,
        &date,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageAlarm;
}
