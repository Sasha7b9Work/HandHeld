// 2024/04/13 13:02:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMicrophone
{
    DEF_CHOICE_MODE_SOURCE(Source::Microphone);

    DEF_CHOICE_MELODY(Source::Microphone);

    DEF_CHOICE_VOLUME(Source::Microphone);

    DEF_CHOICE_7(choiceColorBell, self, "÷¬≈“", (uint8 *const)&gset.sources[Source::Microphone].colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

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
