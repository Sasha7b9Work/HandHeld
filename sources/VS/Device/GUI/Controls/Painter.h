// 2024/03/29 11:28:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Display.h"


class Painter : public wxPanel
{
public:
    Painter(wxWindow *parent, const wxSize &, int scale);

    ~Painter() { delete bitmap; }

    void OnPaint(wxPaintEvent &);

    virtual void Update() { };

protected:

    // ����� ������������ ��������
    wxBitmap *bitmap = nullptr;

    // ����� ����� ��������
    wxMemoryDC memDC;

    void BeginScene();

    void EndScene();

private:

    const wxSize size;
    const int scale;
};
