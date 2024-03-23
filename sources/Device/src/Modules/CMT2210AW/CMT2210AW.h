// 2024/03/01 22:46:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Settings/Settings.h"


namespace CMT2210AW
{
    void Init();

    // Вызывается на приёме очередного бита
    void CallbackOnBit();

    uint GetCode(Source::E);
}
