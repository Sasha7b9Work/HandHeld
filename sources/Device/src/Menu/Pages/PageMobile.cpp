// 2024/04/13 12:47:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMobile
{
    DEF_CHOICE_MODE_SOURCE(Source::Mobile);

    DEF_CHOICE_MELODY(Source::Mobile);

    DEF_CHOICE_VOLUME(Source::Mobile);

    DEF_CHOICE_COLOR(Source::Mobile);

    DEF_PAGE_4(pageMobile, PageMain::self, "лнахкэмши рекетнм",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageMobile;
}
