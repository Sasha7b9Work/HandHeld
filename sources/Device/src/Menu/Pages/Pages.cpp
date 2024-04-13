// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"


namespace PageDoorBell
{
    DEF_PAGE_SOURCE(pageDoorBell, Source::DoorBell, "дбепмни гбнмнй");
}


namespace PageMobile
{
    DEF_PAGE_SOURCE(pageMobile, Source::Mobile, "лнахкэмши рекетнм");
}


namespace PageHomePhone
{
    DEF_PAGE_SOURCE(pageHomePhone, Source::PhoneHome, "днлюьмхи рекетнм");
}


namespace PageIntercom
{
    DEF_PAGE_SOURCE(pageIntercom, Source::Intercom, "днлнтнм");
}


namespace PageMicrophone
{
    DEF_PAGE_SOURCE(pageSoundSensor, Source::Microphone, "лхйпнтнм");
}


DEF_PAGE_8(pageMain, nullptr, "лемч",
    PageAlarm::self,
    PageWatch::self,
    PageDoorBell::self,
    PageMobile::self,
    PageHomePhone::self,
    PageIntercom::self,
    PageMicrophone::self,
    PageJournal::self,
    nullptr,
    nullptr,
    nullptr
);


const Item * const PageMain::self = &pageMain;
