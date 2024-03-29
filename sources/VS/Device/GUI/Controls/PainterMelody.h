// 2024/03/29 12:06:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Painter.h"


class PainterMelody : public Painter
{
public:

    static void Create(wxWindow *parent, int width, int height);

    static PainterMelody *self;

    void SetEnabled();

    void SetDisabled();

private:

    PainterMelody(wxWindow *parent, int width, int height) :
        Painter(parent, width, height, 1) { };
};
