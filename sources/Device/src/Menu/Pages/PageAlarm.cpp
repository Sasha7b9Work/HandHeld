// 2024/04/13 13:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageAlarm
{
    namespace PageTime
    {
        DEF_DATE(timeAlarm, self, "¬–≈Ãﬂ", true);

        DEF_PAGE_1(pageTime, PageAlarm::self, "¬–≈Ãﬂ",
            &timeAlarm,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageTime;
    }


    namespace PageDate
    {
        DEF_DATE(timeDate, self, "ƒ¿“¿", false);

        DEF_PAGE_1(pageDate, PageAlarm::self, "ƒ¿“¿",
            &timeDate,
            nullptr,
            nullptr,
            nullptr
        );

        const Item *const self = &pageDate;
    }


    DEF_PAGE_2(pageAlarm, PageMain::self, "¡”ƒ»À‹Õ» ",
        &PageTime::pageTime,
        &PageDate::pageDate,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageAlarm;
}
