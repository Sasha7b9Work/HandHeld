// 2024/03/20 23:04:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Power
{
    void Enable();

    void Disable();

    // Заснуть на time ms
    void Sleep(uint time = (uint)-1);

    void Draw();

    void CallbackOnTimer();
}
