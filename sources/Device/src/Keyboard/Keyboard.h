// 2024/03/01 22:58:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
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

    void Init();

    void Update();

    extern Button btnMenu;
    extern Button btnCancel;
    extern Button btnUp;
    extern Button btnDown;
}
