// 2024/03/02 09:35:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Colors.h"


uint16 Color::colors[16] =
{
    0xFFFF,                         // WHITE
    0x0000,                         // BLACK
    MAKE_COLOR(0x1f, 0x00, 0x00),   // RED
    MAKE_COLOR(0x00, 0x3f, 0x00),   // GREEN
    MAKE_COLOR(0x00, 0x00, 0x1f),   // BLUE
    MAKE_COLOR(0x10, 0x20, 0x10),   // GRAY
    MAKE_COLOR(0x1f, 0x3f, 0x00),   // YELLOW
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


Color Color::WHITE(Color::White);
Color Color::BLACK(Black);
Color Color::RED(Red);
Color Color::GREEN(Green);
Color Color::BLUE(Blue);
Color Color::GRAY(Gray);
Color Color::YELLOW(Yellow);
Color Color::NUMBER(Count);


Color Color::current = Color::NUMBER;


void Color::SetAsCurrent() const
{
    if (value < Count)
    {
        current = *this;
    }
}
