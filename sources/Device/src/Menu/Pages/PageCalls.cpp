// 2024/03/07 09:44:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    static void DrawParameters(Source::E source)
    {
        const int x0 = 10;
        const int x1 = 80;
        const int dy = 10;
        int y = 25;

        Text<>("�������").Write(x0, y, Color::WHITE);
        Text<>("%d", gset.sources[source].melody).Write(x1, y);

        y += dy;

        Text<>("���������").Write(x0, y);
        Text<>("%d", gset.sources[source].volume).Write(x1, y);

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


        static void OnDraw_DoorBell()
        {
            PageCalls::DrawParameters(Source::DoorBell);
        }


        DEF_PAGE_5(pageDoorBell, PageCalls::self, "������� ������",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro,
            OnDraw_DoorBell
        );

        const Item *const self = &pageDoorBell;
    }


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


    namespace PageHomePhone
    {
        DEF_CHOICE_10(choiceMelody, self, "�������", &gset.sources[Source::PhoneHome].melody,
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

        DEF_CHOICE_10(choiceVolume, self, "���������", &gset.sources[Source::PhoneHome].volume,
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

        DEF_CHOICE_2(choiceEnableLED, self, "���������", &gset.sources[Source::PhoneHome].enabled_led,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnableMelody, self, "����", &gset.sources[Source::PhoneHome].enabled_melody,
            "����",
            "���"
        );

        DEF_CHOICE_2(choiceEnabledVibro, self, "��������", &gset.sources[Source::PhoneHome].enabled_vibrato,
            "����",
            "���"
        );

        static void OnDraw_HomePhone()
        {
            PageCalls::DrawParameters(Source::PhoneHome);
        }


        DEF_PAGE_5(pageHomePhone, PageCalls::self, "�������� �������",
            &choiceMelody,
            &choiceVolume,
            &choiceEnableLED,
            &choiceEnableMelody,
            &choiceEnabledVibro,
            OnDraw_HomePhone
        );

        const Item *const self = &pageHomePhone;
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
            OnDraw_Intercom
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
            OnDraw_SoundSensor
        );

        const Item *const self = &pageSoundSensor;
    }
}


DEF_PAGE_5(pageCalls, PageMain::self, "��������� �������",
    PageCalls::PageDoorBell::self,
    PageCalls::PageMobile::self,
    PageCalls::PageHomePhone::self,
    PageCalls::PageIntercom::self,
    PageCalls::PageSoundSensor::self,
    nullptr
);

const Item *const PageCalls::self = &pageCalls;
