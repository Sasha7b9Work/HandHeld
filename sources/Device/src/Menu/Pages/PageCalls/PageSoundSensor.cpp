// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    namespace PageSoundSensor
    {
        DEF_CHOICE_10(choiceMelody, self, "ÌÅËÎÄÈß", &gset.sources[Source::SoundSensor].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "ÃĞÎÌÊÎÑÒÜ", &gset.sources[Source::SoundSensor].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "ÑÂÅÒÎÄÈÎÄ", &gset.sources[Source::SoundSensor].enabled_led,
            "Îòêë",
            "Âêë"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "ÇÂÓÊ", &gset.sources[Source::SoundSensor].enabled_melody,
            "Îòêë",
            "Âêë"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "ÂÈÁĞÀÖÈß", &gset.sources[Source::SoundSensor].enabled_vibrato,
            "Îòêë",
            "Âêë"
        );


        DEF_PAGE_5(pageSoundSensor, PageCalls::self, "ÄÀÒ×ÈÊ ÇÂÓÊÀ",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro,
            nullptr
        );

        const Item *const self = &pageSoundSensor;
    }
}
