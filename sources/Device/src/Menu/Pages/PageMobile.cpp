// 2024/04/13 12:47:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMobile
{
    DEF_CHOICE_7(choiceModeSource, self, "�����", (uint8 *const)&gset.sources[Source::Mobile].mode_source,
        "����",
        "����",
        "�����",
        "����+����",
        "����+�����",
        "����+�����",
        "���"
    );

    DEF_CHOICE_10(choiceMelody, self, "�������", (uint8 *const)&gset.sources[Source::Mobile].melody,
        Melody::Name(Melody::_1),
        Melody::Name(Melody::_2),
        Melody::Name(Melody::_3),
        Melody::Name(Melody::_4),
        Melody::Name(Melody::_5),
        Melody::Name(Melody::_6),
        Melody::Name(Melody::_7),
        Melody::Name(Melody::_8),
        Melody::Name(Melody::_9),
        Melody::Name(Melody::_10)
    );

    DEF_CHOICE_3(choiceVolume, self, "���������", (uint8 *const)&gset.sources[Source::Mobile].volume,
        "������",
        "�������",
        "�������"
    );

    DEF_CHOICE_7(choiceColorBell, self, "����", (uint8 *const)&gset.sources[Source::Mobile].colorBell,
        ColorBell::Name(ColorBell::White),
        ColorBell::Name(ColorBell::Red),
        ColorBell::Name(ColorBell::Orange),
        ColorBell::Name(ColorBell::Yellow),
        ColorBell::Name(ColorBell::Green),
        ColorBell::Name(ColorBell::Blue),
        ColorBell::Name(ColorBell::Fiolet)
    );

    DEF_PAGE_4(pageMobile, PageMain::self, "��������� �������",
        &choiceColorBell,
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageMobile;
}
