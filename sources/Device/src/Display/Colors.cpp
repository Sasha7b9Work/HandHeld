// 2024/03/02 09:35:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Colors.h"


Color Color::current = Color::NUMBER;


uint16 Color::colors[16] =
{
    0xFFFF,                         // WHITE
    0x0000,                         // BLACK
    MAKE_COLOR(0x1f, 0x00, 0x00),   // RED
    MAKE_COLOR(0x00, 0x3f, 0x00),   // GREEN
    MAKE_COLOR(0x00, 0x00, 0x1f),   // BLUE
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000
};


Color Color::WHITE(White);
Color Color::BLACK(Black);
Color Color::RED(Red);
Color Color::GREEN(Green);
Color Color::BLUE(Blue);
Color Color::NUMBER(Count);


void Color::SetAsCurrent() const
{
    if (value < Count)
    {
        current = *this;
    }
}
