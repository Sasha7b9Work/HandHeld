// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterLED.h"


PainterLED *PainterLED::self = nullptr;


void PainterLED::Create(wxWindow *parent, const wxSize &_size)
{
    self = new PainterLED(parent, _size);
}


void PainterLED::SetEnabled()
{

}


void PainterLED::SetDisabled()
{

}
