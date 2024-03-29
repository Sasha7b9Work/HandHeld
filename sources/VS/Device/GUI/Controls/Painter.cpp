// 2024/03/29 11:28:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/Painter.h"


Painter::Painter(wxWindow *parent, int _width, int _height, int _scale) :
    wxPanel(parent), width(_width), height(_height), scale(_scale)
{
    bitmap = new wxBitmap(width, height);

    SetMinSize({ width * scale, height * scale });
    SetSize({ width * scale, height * scale });
    SetDoubleBuffered(true);
    Bind(wxEVT_PAINT, &Painter::OnPaint, this);
}


void Painter::OnPaint(wxPaintEvent &)
{
    wxPaintDC dc(this);

    wxImage image = bitmap->ConvertToImage().Rescale(width * scale, height * scale);

//    wxImage image = bitmap->ConvertToImage();

    dc.DrawBitmap(wxBitmap(image), 0, 0);
}
