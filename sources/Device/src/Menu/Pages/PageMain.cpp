// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"

/*
  асдхкэмхй, бпелъ, дюрю, дбепмни гбнмнй, Mнахкэмши рекетнм,
  днлюьмхи рекетнм,
  днлнтнм,
  лхйпнтнм, фспмюк
*/

DEF_TIME(timeAlarm, PageMain::self, "асдхкэмхй", true);

DEF_TIME(timeTime, PageMain::self, "бпелъ", false);

DEF_TIME(timeDate, PageMain::self, "дюрю", false);

DEF_PAGE_9(pageMain, nullptr, "лемч",
    &timeAlarm,
    &timeTime,
    &timeDate,
    PageDoorBell::self,
    PageMobile::self,
    PageHomePhone::self,
    PageIntercom::self,

    PageCalls::self,
    PageHistory::self,
    nullptr,
    nullptr,
    nullptr
);


const Item * const PageMain::self = &pageMain;
