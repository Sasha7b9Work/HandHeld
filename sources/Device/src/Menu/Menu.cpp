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


void Menu::SetCurrentItem(const Item *item)
{
    current_item = item;
}


void Menu::Update()
{
    Action action;

    if (!Keyboard::GetNextAction(action))
    {
        return;
    }

    if (Source::GetCountReceived() != 0)
    {
        if (action.IsRelease())
        {
            Source::CancelFirst();
        }
    }
    else if (action.IsDown())
    {
        if (is_shown)
        {
            current_item->ApplyAction(action);
        }
        else
        {
            if (action.key == Key::Cancel)
            {
                Keyboard::SetBlockingMode();
                Keyboard::ms_for_disable = 0;
            }

            if (action.key == Key::Menu || action.key == Key::Up || action.key == Key::Down)
            {
                is_shown = true;
            }
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


void Menu::Close()
{
    is_shown = false;
}
