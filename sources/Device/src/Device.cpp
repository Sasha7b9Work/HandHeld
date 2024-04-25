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
#include "Modules/ST7735/ST7735.h"
#include "Hardware/Power.h"


/*
    * ��� ������� ������� ���� ����������� ������� ���� ����������
    * ��������� ���� ���������
    * ���������.  ���� ��������, ��� ��������� ����������, ��� �� ��� ���������, ���� ���,
      �� ������ �� �����, ������ ���������� � ��. �� � ��� PWR (PA12) ���� �������
    * ���������� : ���� PWR_CTRL(PA0) ������� � 0, �� ��� ����
      �� ���� : ���� �������� INT �� ��� �����(���������), ���� ������ ������ ����������.
      ���� ��������� �������� ����� � ���� ��� ���������, �������� ��� ���������(�� �����
      ��� ���� ��������, �������), � ���� ���, �� �������� �� ������ ����������, �������
      �������� 1, 5� � ����� ������� � ���� PWR(PA12).
*/


void Device::Init()
{
    HAL::Init();

    PCF8563::Init();

    Display::Init();

    Power::Init();

    Timer::Init();

    Keyboard::Init();

    Menu::Init();

    LED::Init();

    Vibrato::Init();

    CMT2210AW::Init();

    Beeper::Init();
}


void Device::Update()
{
    if (!CMT2210AW::IsEnabled() && Keyboard::ToMoreTime() && Source::GetCountReceived() == 0 && !PCF8563::IsAlarmed())
    {
        ModeClock::Set(ModeClock::DeepSleep);
    }

    ModeClock::LeaveDeepSleep();

    PCF8563::Update();

    Menu::Update();

    CMT2210AW::Update();

    Display::Update();

    LED::Update();

    Vibrato::Update();

    Beeper::Update();

    Source::Update();

    Power::Update();
}
