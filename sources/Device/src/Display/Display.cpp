// 2024/03/01 22:45:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"


namespace Display
{
    namespace Buffer
    {
        static uint8 buffer[WIDTH * HEIGHT];
    }
}


void Display::Init()
{
    ST7735::Init();
}


void Display::Update()
{

}


uint8 *Display::Buffer::GetLine(int, int)
{
    return buffer;
}
