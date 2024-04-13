// 2024/04/13 13:35:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageWatch
{
    namespace PageTime
    {
        DEF_TIME(timeTime, self, "ÂĞÅÌß", false);

        DEF_PAGE_1(pageTime, PageMain::self, "ÂĞÅÌß",
            &timeTime,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageTime;
    }


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
