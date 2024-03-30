// 2024/03/29 12:07:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/PainterMelody.h"


PainterMelody *PainterMelody::self = nullptr;


void PainterMelody::Create(wxWindow *parent, const wxSize &_size)
{
    self = new PainterMelody(parent, _size);

    self->EnableMelody(5);
}


void PainterMelody::EnableMelody(int number)
{
    memDC.SelectObject(*bitmap);

    wxPen pen = *wxWHITE_PEN;

    wxBrush brush = *wxWHITE_BRUSH;

    wxFont font = wxFont(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN));

    memDC.SetPen(pen);
    memDC.SetBrush(brush);
    memDC.SetFont(font);

    memDC.DrawText("T", 1, 20);

    for (int i = 0; i < number; i++)
    {
        memDC.DrawRectangle(3 + i * 5, 5, 4, 20);
    }

    memDC.SelectObject(wxNullBitmap);

    Refresh();
}


void PainterMelody::Disable()
{

}
