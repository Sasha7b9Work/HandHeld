// 2024/03/29 11:28:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


class Screen : public wxPanel
{
public:
    Screen(wxWindow *parent);

    void OnPaint(wxPaintEvent &);

    wxBitmap *GetBitmap() { return bitmap; }

private:

    // Здесь нарисованная картинка
    wxBitmap *bitmap = nullptr;
};
