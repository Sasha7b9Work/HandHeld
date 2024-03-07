// 2024/03/01 23:02:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Keyboard/Keyboard.h"


namespace Menu
{
    static bool is_shown = false;
    static const Item *current_item = PageMain::self;
}


void Menu::Init()
{

}


void Menu::Update()
{
    Action action;

    if (!Keyboard::GetNextAction(action))
    {
        return;
    }

    if (!action.IsRelease())
    {
        if (action.key == Key::Menu)
        {
            is_shown = true;
        }
        else if (action.key == Key::Cancel)
        {
            is_shown = false;
        }
    }
}


void Menu::Draw()
{
    current_item->Draw();
}


bool Menu::IsShown()
{
    return is_shown;
}
