// 2024/04/13 13:02:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageMicrophone
{
    DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::Microphone].melody,
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

    DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::Microphone].volume,
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

    DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::Microphone].enabled_led,
        "����",
        "���"
    );

    DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::Microphone].enabled_melody,
        "����",
        "���"
    );

    DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::Microphone].enabled_vibrato,
        "����",
        "���"
    );


    static void OnDraw_SoundSensor()
    {
        Source::DrawParameters(Source::Microphone);
    }


    DEF_PAGE_5(pageSoundSensor, PageMain::self, "��������",
        &choiceMelody,
        &choiceVolume,
        &choiceEnableLED,
        &choiceEnableMelody,
        &choiceEnabledVibro,
        OnDraw_SoundSensor,
        nullptr,
        nullptr
    );

    const Item *const self = &pageSoundSensor;
}
