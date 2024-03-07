// 2024/03/01 23:02:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"


namespace Menu
{
    static bool is_shown = false;
    static const Item *item = PageMain::self;
}


void Menu::Init()
{

}


void Menu::Update()
{

}


void Menu::Draw()
{

}


bool Menu::IsShown()
{
    return is_shown;
}
