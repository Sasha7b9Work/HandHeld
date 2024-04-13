// 2024/03/07 09:44:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    void DrawParameters(Source::E source)
    {
        const int x0 = 10;
        const int x1 = 80;
        const int dy = 10;
        int y = 25;

        Text<>("Ìåëîäèÿ").Write(x0, y, Color::WHITE);
        Text<>("%d", gset.sources[source].melody + 1).Write(x1, y);

        y += dy;

        Text<>("Ãğîìêîñòü").Write(x0, y);
        Text<>("%d", gset.sources[source].volume + 1).Write(x1, y);

        y += dy;

        Text<>("Ñâåò").Write(x0, y);
        Text<>(gset.sources[source].enabled_led == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("Çâóê").Write(x0, y);
        Text<>(gset.sources[source].enabled_melody == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("Âèáğàöèÿ").Write(x0, y);
        Text<>(gset.sources[source].enabled_vibrato == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);
    }


    namespace PageSoundSensor
    {
        DEF_CHOICE_10(choiceMelody, self, "ÌÅËÎÄÈß", &gset.sources[Source::Ìicrophone].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "ÃĞÎÌÊÎÑÒÜ", &gset.sources[Source::Ìicrophone].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "ÑÂÅÒÎÄÈÎÄ", &gset.sources[Source::Ìicrophone].enabled_led,
            "Îòêë",
            "Âêë"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "ÇÂÓÊ", &gset.sources[Source::Ìicrophone].enabled_melody,
            "Îòêë",
            "Âêë"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "ÂÈÁĞÀÖÈß", &gset.sources[Source::Ìicrophone].enabled_vibrato,
            "Îòêë",
            "Âêë"
        );


        static void OnDraw_SoundSensor()
        {
            PageCalls::DrawParameters(Source::Ìicrophone);
        }


        DEF_PAGE_5(pageSoundSensor, PageCalls::self, "ÄÀÒ×ÈÊ ÇÂÓÊÀ",
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
}


DEF_PAGE_1(pageCalls, PageMain::self, "ÍÀÑÒĞÎÉÊÈ ÂÛÇÎÂÎÂ",
    PageCalls::PageSoundSensor::self,
    nullptr,
    nullptr,
    nullptr
);

const Item *const PageCalls::self = &pageCalls;
