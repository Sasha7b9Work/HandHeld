// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterMelody.h"


PainterMelody *PainterMelody::self = nullptr;


void PainterMelody::Create(wxWindow *parent, const wxSize &_size)
{
    self = new PainterMelody(parent, _size);
}


void PainterMelody::SetEnabled()
{

}


void PainterMelody::SetDisabled()
{

}
