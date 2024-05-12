// 2024/04/23 08:38:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display1602.h"
#include "Modules/WH1602B/WH1602B.h"


void Display::Init()
{
    WH1602B::Init();
}


void Display::Update()
{
    pchar buffer = "12345678ABCDEFGH";

    WH1602B::Write((uint8*)buffer);
}


void Display::DrawPowerOn()
{

}


void Display::DrawPowerOff()
{

}


void Display::DrawLowVoltage()
{

}


void Display::PrepareToSleep()
{

}


uint Display::TimeEnabled()
{
    return 0;
}
