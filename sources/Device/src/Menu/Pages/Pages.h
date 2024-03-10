// 2024/03/02 13:56:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Menu/MenuItems.h"


namespace PageMain
{
    extern const Item *const self;
}


namespace PageCalls
{
    extern const Item *const self;

    void DrawParameters(Source::E);

    namespace PageDoorBell
    {
        extern const Item *const self;
    }

    namespace PageMobile
    {
        extern const Item *const self;
    }

    namespace PageHomePhone
    {
        extern const Item *const self;
    }

    namespace PageIntercom
    {
        extern const Item *const self;
    }

    namespace PageSoundSensor
    {
        extern const Item *const self;
    }
}


namespace PageHistory
{
    extern const Item *const self;
}
