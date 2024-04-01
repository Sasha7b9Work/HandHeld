// 2024/03/20 19:26:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "GUI/Controls/PainterLED.h"
#include "GUI/Frame.h"
#include "Modules/LED/LED.h"


void LED::Init()
{
    PainterLED::Create(Frame::self, Painter::size_indicator);

    PainterLED::self->SetPosition({ 550, 68 });
}


void LED::Update()
{
    PainterLED::self->Update();
}


void LED::Enable()
{
    PainterLED::self->SetEnabled();
}


void LED::Disable()
{
    PainterLED::self->SetDisabled();
}
