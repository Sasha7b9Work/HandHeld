// 2024/03/01 23:01:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Keyboard/Keyboard.h"
#include <gd32e23x.h>


namespace Keyboard
{
    struct Button
    {
        Button(uint _port, uint16 _pin) : port(_port), pin(_pin) { }

        void Init()
        {
            gpio_mode_set(port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, pin);
        }

        bool IsDown()
        {
            return (gpio_input_bit_get(port, pin) == RESET);
        }
        bool IsUp()
        {
            return !IsDown();
        }

    private:
        uint port;
        uint16 pin;
    };

    static Button btnMenu(GPIOB, GPIO_PIN_0);
    static Button btnCancel(GPIOB, GPIO_PIN_2);
    static Button btnUp(GPIOA, GPIO_PIN_7);
    static Button btnDown(GPIOB, GPIO_PIN_1);

    static Button *buttons[Key::Count] =
    {
        &btnMenu,
        &btnCancel,
        &btnUp,
        &btnDown
    };
}


void Keyboard::Init()
{
    btnMenu.Init();
    btnCancel.Init();
    btnUp.Init();
    btnDown.Init();
}


void Keyboard::Update()
{

}


bool Keyboard::IsDown(Key::E key)
{
    return buttons[key]->IsDown();
}
