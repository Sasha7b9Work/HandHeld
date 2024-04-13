// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageIntercom
{
    DEF_CHOICE_7(choiceModeSource, self, "�����", (uint8 *const)&gset.sources[Source::Intercom].mode_source,
        "����",
        "����",
        "�����",
        "����+����",
        "����+�����",
        "����+�����",
        "���"
    );

    DEF_CHOICE_10(choiceMelody, self, "�������", (uint8 *const)&gset.sources[Source::Intercom].melody,
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

    DEF_CHOICE_3(choiceVolume, self, "���������", (uint8 *const)&gset.sources[Source::Intercom].volume,
        "������",
        "�������",
        "�������"
    );

    DEF_PAGE_3(pageIntercom, PageMain::self, "�������",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );


    const Item *const self = &pageIntercom;
}