// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageIntercom
{
    DEF_CHOICE_MODE_SOURCE(Source::Intercom);

    DEF_CHOICE_MELODY(Source::Intercom);

    DEF_CHOICE_VOLUME(Source::Intercom);

    DEF_CHOICE_COLOR(Source::Intercom);

    DEF_PAGE_4(pageIntercom, PageMain::self, "�������",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );


    const Item *const self = &pageIntercom;
}
