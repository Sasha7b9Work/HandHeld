// 2024/03/29 12:06:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Painter.h"


class PainterLED : public Painter
{
public:

    static void Create(wxWindow *parent, int width, int height);

    static PainterLED *self;

    void SetEnabled();

    void SetDisabled();

private:

    PainterLED(wxWindow *parent, int width, int height) :
        Painter(parent, width, height, 1) { };
};
