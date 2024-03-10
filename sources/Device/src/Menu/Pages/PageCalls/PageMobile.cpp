// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    namespace PageMobile
    {
        DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::Mobile].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::Mobile].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::Mobile].enabled_led,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::Mobile].enabled_melody,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::Mobile].enabled_vibrato,
            "����",
            "���"
        );

        static void OnDraw_Mobile()
        {
            PageCalls::DrawParameters(Source::Mobile);
        }


        DEF_PAGE_5(pageMobile, PageCalls::self, "��������� �������",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro,
            OnDraw_Mobile
        );

        const Item *const self = &pageMobile;
    }
}
