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


/*
    1) заливка экрана цветом, выбранным в настройках при вызове
    2) новый источник сигнала ТЕСТ.
     Я решил, что не надо ему отдельных настроек, пусть его цвет всегда будет белый,
     громкость максимальная, свет + звук + вибрация будут всегда
    3) коды передатчиков :
    Дверной звонок 0x7E9E
    Мобильный 0x7EA6
    Телефон 0x7ED5
    Домофон 0x7EB9
    Микрофон 0x7ECA
    Тест 0x7EED
    4) будильник надо проверить
    5) реализовать механизм выключения : если PWR_CTRL(PA0) перешёл в 0, то это одно
       из двух : либо сработал INT от мсх часов(будильник), либо нажали кнопку выключения.
       Надо проверить регистры часов и если там будильник, включить его индикацию(на часах
       его тоже сбросить, конечно), а если нет, то написать на экране ВЫКЛЮЧЕНИЕ, сделать
       задержку 1, 5с и снять единицу с ноги PWR(PA12).
    6) Таймаут свечения экрана 20с.Хорошо бы, кнопка 'left' имела функцию принудительного
       досрочного гашения экрана из основного меню(сейчас она все равно ничего не делает)
    7) при разряде батареи ниже допустимого предела тоже выключение
*/


void Device::Init()
{
    HAL::Init();

    Timer::Init();

    Keyboard::Init();

    Menu::Init();

    Display::Init();

    LED::Init();

    Vibrato::Init();

    CMT2210AW::Init();

    PCF8563::Init();

    Beeper::Init();
}


void Device::Update()
{
    if (!CMT2210AW::IsEnabled() && Keyboard::ToMoreTime() && Source::GetCountReceived() == 0)
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
}
