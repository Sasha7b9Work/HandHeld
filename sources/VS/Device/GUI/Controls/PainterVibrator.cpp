// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterVibrator.h"


PainterVibrator *PainterVibrator::self = nullptr;


void PainterVibrator::Create(wxWindow *parent, int width, int height)
{
    self = new PainterVibrator(parent, width, height);
}


void PainterVibrator::SetEnabled()
{

}


void PainterVibrator::SetDisabled()
{

}
