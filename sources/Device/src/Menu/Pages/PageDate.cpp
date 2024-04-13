// 2024/04/13 13:39:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageWatch
{
    namespace PageDate
    {
        DEF_TIME(timeDate, PageDate::self, "ÄÀÒÀ", false);

        DEF_PAGE_1(pageDate, PageMain::self, "ÄÀÒÀ",
            &timeDate,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageDate;
    }
}
