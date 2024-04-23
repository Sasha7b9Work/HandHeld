// 2024/04/23 08:38:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Display
{
    void Init();

    void Update();

    void DrawPowerOn();

    void DrawPowerOff();

    void DrawLowVoltage();

    void PrepareToSleep();

    uint TimeEnabled();
}

