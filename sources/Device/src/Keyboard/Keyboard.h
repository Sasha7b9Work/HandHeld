// 2024/03/01 22:58:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <gd32e23x.h>


struct Key
{
    enum E
    {
        Menu,
        Cancel,
        Up,
        Down,
        Count
    };
};


namespace Keyboard
{
    void Init();

    void Update();

    bool IsDown(Key::E);
}
