// 2024/04/13 12:53:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


namespace PageHomePhone
{
    DEF_CHOICE_10(choiceMelody, self, "лекндхъ", &gset.sources[Source::PhoneHome].melody,
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

    DEF_CHOICE_10(choiceVolume, self, "цпнлйнярэ", &gset.sources[Source::PhoneHome].volume,
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

    DEF_CHOICE_2(choiceEnableLED, self, "яберндхнд", &gset.sources[Source::PhoneHome].enabled_led,
        "нРЙК",
        "бЙК"
    );

    DEF_CHOICE_2(choiceEnableMelody, self, "гбсй", &gset.sources[Source::PhoneHome].enabled_melody,
        "нРЙК",
        "бЙК"
    );

    DEF_CHOICE_2(choiceEnabledVibro, self, "бхапюжхъ", &gset.sources[Source::PhoneHome].enabled_vibrato,
        "нРЙК",
        "бЙК"
    );

    static void OnDraw_HomePhone()
    {
        PageCalls::DrawParameters(Source::PhoneHome);
    }


    DEF_PAGE_5(pageHomePhone, PageMain::self, "днлюьмхи рекетнм",
        &choiceMelody,
        &choiceVolume,
        &choiceEnableLED,
        &choiceEnableMelody,
        &choiceEnabledVibro,
        OnDraw_HomePhone,
        nullptr,
        nullptr
    );

    const Item *const self = &pageHomePhone;
}
