// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterMelody.h"


PainterMelody *PainterMelody::self = nullptr;


void PainterMelody::Create(wxWindow *parent, const wxSize &_size)
{
    self = new PainterMelody(parent, _size);

    self->EnableMelody(2);
}


void PainterMelody::EnableMelody(int number)
{
    memDC.SelectObject(*bitmap);

    wxPen pen = *wxWHITE_PEN;

    wxBrush brush = *wxBLUE_BRUSH;

    wxFont font = wxFont(wxFontInfo(8).Family(wxFONTFAMILY_ROMAN));

    memDC.SetPen(pen);
    memDC.SetBrush(brush);
    memDC.SetFont(font);

    memDC.DrawText("T", 1, 1);

    memDC.DrawRectangle(20, 20, 10, 10);

    memDC.SelectObject(wxNullBitmap);

    Refresh();
}


void PainterMelody::Disable()
{

}
