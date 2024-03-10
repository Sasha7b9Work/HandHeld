// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    namespace PageDoorBell
    {
        DEF_CHOICE_10(choiceMelody, PageCalls::PageDoorBell::self, "�������", &gset.sources[Source::Bell].melody,
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

        DEF_CHOICE_10(choiceVolume, PageCalls::PageDoorBell::self, "���������", &gset.sources[Source::Bell].volume,
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

        DEF_CHOICE_2(choiceEnableLED, PageCalls::PageDoorBell::self, "���������", &gset.sources[Source::Bell].enabled_led,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnableMelody, PageCalls::PageDoorBell::self, "����", &gset.sources[Source::Bell].enabled_melody,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnabledVibro, PageCalls::PageDoorBell::self, "��������", &gset.sources[Source::Bell].enabled_vibrato,
            "����",
            "���"
        );


        DEF_PAGE_5(pageDoorBell, PageCalls::self, "������� ������",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro
        );
    }
}


const Item *const PageCalls::PageDoorBell::self = &PageCalls::PageDoorBell::pageDoorBell;
