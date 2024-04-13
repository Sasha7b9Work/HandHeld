// 2024/04/13 13:35:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageWatch
{
    namespace PageTime
    {
        DEF_DATE(timeTime, self, "ÂÐÅÌß", false);

        DEF_PAGE_1(pageTime, PageWatch::self, "ÂÐÅÌß",
            &timeTime,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageTime;
    }


    namespace PageDate
    {
        DEF_DATE(timeDate, self, "ÄÀÒÀ", false);

        DEF_PAGE_1(pageDate, PageWatch::self, "ÄÀÒÀ",
            &timeDate,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageDate;
    }


    DEF_PAGE_2(pageWatch, PageMain::self, "×ÀÑÛ",
        &PageTime::pageTime,
        &PageDate::pageDate,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageWatch;
}
