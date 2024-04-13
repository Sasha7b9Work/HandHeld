// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageIntercom
{
    DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::Intercom].melody,
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

    DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::Intercom].volume,
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

    DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::Intercom].enabled_led,
        "����",
        "���"
    );

    DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::Intercom].enabled_melody,
        "����",
        "���"
    );

    DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::Intercom].enabled_vibrato,
        "����",
        "���"
    );

    static void OnDraw_Intercom()
    {
        Source::DrawParameters(Source::Intercom);
    }

    DEF_PAGE_5(pageIntercom, PageMain::self, "�������",
        &choiceMelody,
        &choiceVolume,
        &choiceEnableLED,
        &choiceEnableMelody,
        &choiceEnabledVibro,
        OnDraw_Intercom,
        nullptr,
        nullptr
    );


    const Item *const self = &pageIntercom;
}
