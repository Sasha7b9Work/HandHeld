// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Display/Display.h"
#include "Keyboard/Keyboard.h"
#include "Menu/Menu.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Hardware/Beeper.h"


void Device::Init()
{
    HAL::Init();

    Keyboard::Init();

    Menu::Init();

    Display::Init();

    CMT2210AW::Init();

    PCF8563::Init();

    PCF8563::SetTimer(1);       // Переводим INT в 0, чтобы питание не выключалось

    Beeper::Init();
}


void Device::Update()
{
    Keyboard::Update();

    Menu::Update();

    PCF8563::Update();

    Display::Update();
}
