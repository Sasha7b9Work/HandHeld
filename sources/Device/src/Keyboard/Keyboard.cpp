// 2024/03/01 23:01:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Keyboard/Keyboard.h"
#include <cstring>
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

    static bool prev_down[Key::Count] =
    {
        false,
        false,
        false,
        false
    };

    static const int MAX_ACTIONS = 10;

    static Action actions[MAX_ACTIONS];

    static int num_actions = 0;

    static void AppendAction(Action &action)
    {
        actions[num_actions++] = action;
    }
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
    for (int i = 0; i < Key::Count; i++)
    {
        bool is_down = buttons[i]->IsDown();

        if (prev_down[i] != is_down)
        {
            Action action;
            action.key = (Key::E)i;
            action.type = is_down ? ActionType::Down : ActionType::Up;

            AppendAction(action);
        }
    }
}


bool Keyboard::IsDown(Key::E key)
{
    return buttons[key]->IsDown();
}


bool Keyboard::GetNextAction(Action &action)
{
    if (num_actions == 0)
    {
        return false;
    }

    action = actions[0];

    if (num_actions == 1)
    {
        num_actions = 0;
    }
    else
    {
        std::memmove(actions, actions + 1, (uint)(sizeof(Action) * (uint)(num_actions - 1)));

        num_actions--;
    }

    return true;
}
