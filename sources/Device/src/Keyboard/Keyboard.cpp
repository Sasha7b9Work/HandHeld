// 2024/03/01 23:01:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Keyboard/Keyboard.h"
#include <gd32e23x.h>


namespace Keyboard
{
    Button btnMenu(GPIOB, GPIO_PIN_0);
    Button btnCancel(GPIOB, GPIO_PIN_2);
    Button btnUp(GPIOA, GPIO_PIN_7);
    Button btnDown(GPIOB, GPIO_PIN_1);
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
