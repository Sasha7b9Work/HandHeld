// 2024/03/29 11:28:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


class Painter : public wxPanel
{
public:
    Painter(wxWindow *parent, int width, int height, int scale);

    ~Painter() { delete bitmap; }

    void OnPaint(wxPaintEvent &);

protected:

    // ����� ������������ ��������
    wxBitmap *bitmap = nullptr;

    // ����� ����� ��������
    wxMemoryDC memDC;

private:

    const int width;
    const int height;
    const int scale;
};
