// 2024/03/01 22:46:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace CMT2210AW
{
    void Init();

    // Включить прерывание по SCK
    void EnableEXTI_SCK();

    // Выкллючить прерывание по SCK
    void DisableEXTI_SCK();

    void CallbackOn1MS();
}
