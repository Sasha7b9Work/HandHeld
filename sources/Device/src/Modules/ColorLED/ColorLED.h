// 2024/04/23 08:39:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace LED
{
    void Init();

    void Update();

    void Enable();

    void Disable();

    bool IsFired();

    namespace Driver
    {
        void On();
    }
}
