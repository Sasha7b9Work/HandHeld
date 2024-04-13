// 2024/04/13 13:02:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMicrophone
{
    DEF_CHOICE_MODE_SOURCE(Source::Microphone);

    DEF_CHOICE_MELODY(Source::Microphone);

    DEF_CHOICE_VOLUME(Source::Microphone);

    DEF_CHOICE_COLOR(Source::Microphone);

    DEF_PAGE_4(pageSoundSensor, PageMain::self, "Ã» –Œ‘ŒÕ",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        &choiceColorBell,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageSoundSensor;
}
