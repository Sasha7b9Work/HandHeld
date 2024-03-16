// 2024/03/16 09:07:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct TypeSound
{
    enum E
    {
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        Count
    };
};


namespace Player
{
    void Init();

    void Play(TypeSound::E);
}
