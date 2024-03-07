// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"


void Item::Draw() const
{
    if (IsPage())
    {
        GetPage()->Draw();
    }
}


bool Item::IsPage() const
{
    return data->type == ItemType::Page;
}


const Page *Item::GetPage() const
{
    if (IsPage())
    {
        return (const Page *)item;
    }

    return nullptr;
}


void Page::Draw() const
{

}
