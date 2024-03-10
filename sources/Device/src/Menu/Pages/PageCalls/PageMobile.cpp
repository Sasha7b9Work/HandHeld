// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    namespace PageMobile
    {
        DEF_CHOICE_10(choiceMelody, self, "лекндхъ", &gset.sources[Source::Mobile].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "цпнлйнярэ", &gset.sources[Source::Mobile].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "яберндхнд", &gset.sources[Source::Mobile].enabled_led,
            "нРЙК",
            "бЙК"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "гбсй", &gset.sources[Source::Mobile].enabled_melody,
            "нРЙК",
            "бЙК"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "бхапюжхъ", &gset.sources[Source::Mobile].enabled_vibrato,
            "нРЙК",
            "бЙК"
        );


        DEF_PAGE_5(pageMobile, PageCalls::self, "лнахкэмши рекетнм",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro
        );

        const Item *const self = &pageMobile;
    }
}
