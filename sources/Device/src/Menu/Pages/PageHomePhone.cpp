// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageHomePhone
{
    DEF_CHOICE_MODE_SOURCE(Source::PhoneHome);

    DEF_CHOICE_MELODY(Source::PhoneHome);

    DEF_CHOICE_3(choiceVolume, self, "√–ŒÃ Œ—“‹", (uint8 *const)&gset.sources[Source::PhoneHome].volume,
        "Õ»« ¿ﬂ",
        "—–≈ƒÕﬂﬂ",
        "¬€—Œ ¿ﬂ"
    );

    DEF_CHOICE_7(choiceColorBell, self, "÷¬≈“", (uint8 *const)&gset.sources[Source::PhoneHome].colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_4(pageHomePhone, PageMain::self, "ƒŒÃ¿ÿÕ»… “≈À≈‘ŒÕ",
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
