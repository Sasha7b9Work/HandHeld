// 2024/04/13 12:39:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageDoorBell
{
    DEF_CHOICE_7(choiceModeSource, self, "�����", (uint8 *const)&gset.sources[Source::DoorBell].mode_source,
        "����",
        "����",
        "�����",
        "����+����",
        "����+�����",
        "����+�����",
        "���"
    );

    DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::DoorBell].melody,
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10"
    );

    DEF_CHOICE_3(choiceVolume, self, "���������", (uint8 *const)&gset.sources[Source::DoorBell].volume,
        "������",
        "�������",
        "�������"
    );

    DEF_PAGE_3(pageDoorBell, PageMain::self, "������� ������",
        &choiceModeSource,
        &choiceMelody,
        &choiceVolume,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageDoorBell;
}
