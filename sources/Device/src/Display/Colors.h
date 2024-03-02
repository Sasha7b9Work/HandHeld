// 2024/03/02 09:35:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct Color
{
    enum E
    {
        Count
    };

    static uint16 colors[16];
};



#define MAKE_COLOR(r, g, b)  (uint16)((b) + ((g) << 5) + ((r) << 11))

#define BLUE_FROM_COLOR(color)  ((color) & 0x1f)
#define GREEN_FROM_COLOR(color) (((color) >> 5) & 0x3f)
#define RED_FROM_COLOR(color)   (((color) >> 11) & 0x1f)
