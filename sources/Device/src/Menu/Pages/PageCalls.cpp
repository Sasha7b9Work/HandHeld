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

        Text<>("�������").Write(x0, y, Color::WHITE);
        Text<>("%d", gset.sources[source].melody + 1).Write(x1, y);

        y += dy;

        Text<>("���������").Write(x0, y);
        Text<>("%d", gset.sources[source].volume + 1).Write(x1, y);

        y += dy;

        Text<>("����").Write(x0, y);
        Text<>(gset.sources[source].enabled_led == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("����").Write(x0, y);
        Text<>(gset.sources[source].enabled_melody == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("��������").Write(x0, y);
        Text<>(gset.sources[source].enabled_vibrato == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);
    }


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
            PageCalls::DrawParameters(Source::Intercom);
        }

        DEF_PAGE_5(pageIntercom, PageCalls::self, "�������",
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


    namespace PageSoundSensor
    {
        DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::SoundSensor].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::SoundSensor].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::SoundSensor].enabled_led,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::SoundSensor].enabled_melody,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::SoundSensor].enabled_vibrato,
            "����",
            "���"
        );


        static void OnDraw_SoundSensor()
        {
            PageCalls::DrawParameters(Source::SoundSensor);
        }


        DEF_PAGE_5(pageSoundSensor, PageCalls::self, "������ �����",
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


DEF_PAGE_2(pageCalls, PageMain::self, "��������� �������",
    PageCalls::PageIntercom::self,
    PageCalls::PageSoundSensor::self,
    nullptr,
    nullptr,
    nullptr
);

const Item *const PageCalls::self = &pageCalls;
