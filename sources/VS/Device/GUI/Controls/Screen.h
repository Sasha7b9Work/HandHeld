// 2024/03/29 11:28:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


class Screen : public wxPanel
{
public:
    Screen(wxWindow *parent, int width, int height, int scale);

    ~Screen() { delete bitmap; }

    void OnPaint(wxPaintEvent &);

    wxBitmap *GetBitmap() { return bitmap; }

    wxMemoryDC &GetMemoryDC() { return memDC; }

private:

    // ����� ������������ ��������
    wxBitmap *bitmap = nullptr;

    // ����� ����� ��������
    wxMemoryDC memDC;

    const int width;
    const int height;
    const int scale;
};
