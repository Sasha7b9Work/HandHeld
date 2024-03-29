// 2024/03/29 11:28:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines_win.h"
#include "GUI/Controls/Screen.h"


Screen::Screen(wxWindow *parent) : wxPanel(parent)
{
    bitmap = new wxBitmap(Display::WIDTH, Display::HEIGHT);

    SetMinSize({ Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE });
    SetDoubleBuffered(true);
    Bind(wxEVT_PAINT, &Screen::OnPaint, this);
}


void Screen::OnPaint(wxPaintEvent &)
{
    wxPaintDC dc(this);

    wxImage image = bitmap->ConvertToImage().Rescale(Display::WIDTH * IMAGE_SCALE, Display::HEIGHT * IMAGE_SCALE);

    dc.DrawBitmap(wxBitmap(image), 0, 0);
}
