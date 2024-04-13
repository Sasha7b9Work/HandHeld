// 2024/04/13 12:39:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageDoorBell
{
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

    DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::DoorBell].volume,
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

    DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::DoorBell].enabled_led,
        DISABLED_RU,
        ENABLED_RU
    );

    DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::DoorBell].enabled_melody,
        "����",
        "���"
    );

    DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::DoorBell].enabled_vibrato,
        "����",
        "���"
    );

    DEF_PAGE_5(pageDoorBell, PageMain::self, "������� ������",
        &choiceMelody,
        &choiceVolume,
        &choiceEnableLED,
        &choiceEnableMelody,
        &choiceEnabledVibro,
        nullptr,
        nullptr,
        nullptr
    );

    const Item *const self = &pageDoorBell;
}
