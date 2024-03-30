// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterVibrator.h"


PainterVibrator *PainterVibrator::self = nullptr;


void PainterVibrator::Create(wxWindow *parent, const wxSize &_size)
{
    self = new PainterVibrator(parent, _size);
}


void PainterVibrator::SetEnabled()
{

}


void PainterVibrator::SetDisabled()
{

}
