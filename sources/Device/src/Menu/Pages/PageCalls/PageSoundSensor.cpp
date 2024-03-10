// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    namespace PageSoundSensor
    {
        DEF_CHOICE_10(choiceMelody, self, "Мелодия", &gset.sources[Source::SoundSensor].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "Громкость", &gset.sources[Source::SoundSensor].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "Светодиод", &gset.sources[Source::SoundSensor].enabled_led,
            "Откл",
            "Вкл"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "Звук", &gset.sources[Source::SoundSensor].enabled_melody,
            "Откл",
            "Вкл"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "Вибрация", &gset.sources[Source::SoundSensor].enabled_vibrato,
            "Откл",
            "Вкл"
        );


        DEF_PAGE_5(pageSoundSensor, PageCalls::self, "Датчик звука",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro
        );

        const Item *const self = &pageSoundSensor;
    }
}
