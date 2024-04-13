// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageHomePhone
{
    DEF_CHOICE_MODE_SOURCE(Source::PhoneHome);

    DEF_CHOICE_MELODY(Source::PhoneHome);

    DEF_CHOICE_VOLUME(Source::PhoneHome);

    DEF_CHOICE_COLOR(Source::PhoneHome);

    DEF_PAGE_4(pageHomePhone, PageMain::self, "днлюьмхи рекетнм",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageHomePhone;
}
