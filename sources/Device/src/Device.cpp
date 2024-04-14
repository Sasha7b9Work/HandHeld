// 2024/03/01 22:29:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Display/Display.h"
#include "Keyboard/Keyboard.h"
#include "Menu/Menu.h"
#include "Hardware/HAL/HAL.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include "Modules/PCF8563/PCF8563.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Hardware/Vibrato.h"
#include "Storage/Storage.h"
#include "Modules/LED/LED.h"
#include "Modules/Beeper/Beeper.h"
#include "Hardware/Power.h"


void Device::Init()
{
    HAL::Init();

    Timer::Init();

    Timer::Delay(1000);

    Keyboard::Init();

    Menu::Init();

    Display::Init();

    LED::Init();

    Vibrato::Init();

    CMT2210AW::Init();

    PCF8563::Init();

    PCF8563::SetTimer(1);       // Переводим INT в 0, чтобы питание не выключалось

    Beeper::Init();

    Beeper::Play(TypeSound::_2, 9);
}


void Device::Update()
{
    Menu::Update();

    PCF8563::Update();

    Display::Update();

    Source::Update();

    Beeper::Update();

    LED::Update();

    Beeper::Update();

    Power::Sleep(50);
}
