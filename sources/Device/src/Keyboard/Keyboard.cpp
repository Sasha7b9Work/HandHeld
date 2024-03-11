// 2024/03/01 23:01:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/Timer.h"
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

    struct ButtonStruct
    {
        Button *button;
        bool prev_down;
        uint prev_time;     // Будем обрабатывать кнопку только если прошло более определённого времени - антидребезг
    };

    static ButtonStruct buttons[Key::Count] =
    {
        {&btnMenu, false, 0},
        {&btnCancel, false, 0},
        {&btnUp, false, 0},
        {&btnDown, false, 0}
    };

    static const int MAX_ACTIONS = 10;

    static Action actions[MAX_ACTIONS];

    static int num_actions = 0;

    static void AppendAction(const Action &action)
    {
        actions[num_actions] = action;
        num_actions++;
    }

    static bool is_busy = false;
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
    static uint counter = 0;

    if (counter++ < 10)     // Так как прерывание вызывается каждую миллисекунду, будем пропускать
    {
        return;
    }

    counter = 0;

    if (is_busy)
    {
        return;
    }

    uint time = TIME_MS;

    for (int i = 0; i < Key::Count; i++)
    {
        if (time - buttons[i].prev_time < 100)
        {
            continue;
        }

        bool is_down = buttons[i].button->IsDown();

        if (buttons[i].prev_down != is_down)
        {
            AppendAction({ (Key::E)i , is_down ? ActionType::Down : ActionType::Up });

            buttons[i].prev_time = time;
            buttons[i].prev_down = is_down;
        }
    }
}


bool Keyboard::IsDown(Key::E key)
{
    return buttons[key].button->IsDown();
}


bool Keyboard::GetNextAction(Action &action)
{
    if (num_actions == 0)
    {
        return false;
    }

    is_busy = true;

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

    is_busy = false;

    return true;
}
