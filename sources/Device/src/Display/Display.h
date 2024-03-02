// 2024/03/01 22:45:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"


namespace Display
{
    static const int WIDTH = 160;
    static const int HEIGHT = 80;

    void Init();

    void Update();

    namespace Buffer
    {
        // Возвращает указатель на строку
        uint8 *GetLine(int x, int y);
    }
}
