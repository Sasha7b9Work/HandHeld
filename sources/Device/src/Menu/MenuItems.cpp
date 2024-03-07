// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Display/Display.h"


void Item::Draw() const
{
    if (IsPage())
    {
        const Page *page = GetPage();

        page->Draw();
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
    if (IsOpened())
    {
        CurrentItem()->Draw();
    }
    else
    {
        Text<>(data->data_item->title).Write(10, 10, Color::WHITE);
    }
}


bool Page::IsOpened() const
{
    if (data->data_item->keeper == nullptr)
    {
        return true;
    }

    return *data->opened != 0;
}


const Item *Page::CurrentItem() const
{
    return data->items[*data->current_item];
}
