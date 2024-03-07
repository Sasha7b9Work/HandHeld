// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Display/Display.h"
#include "Menu/Menu.h"


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
        const Item *current_item = CurrentItem();

        if (current_item)
        {
            current_item->Draw();
        }
    }
    else
    {
        Title().Write(10, 10, Color::WHITE);
    }
}


Text<> Page::Title() const
{
    const Page *page_keeper = GetDataItem()->keeper->GetPage();

    for (int i = 0; ; i++)
    {
        if (page_keeper->data->items[i]->item == this)
        {
            return Text<>("%d/%d %s", i + 1, page_keeper->NumItems(), GetDataItem()->title);
        }
    }
}


const Item *Page::GetSelfItem() const
{
    return data->item;
}


const DataItem *Page::GetDataItem() const
{
    return GetSelfItem()->data;
}


bool Page::IsOpened() const
{
    if (GetDataItem()->keeper == nullptr)
    {
        return true;
    }

    return *data->opened != 0;
}


const Item *Page::CurrentItem() const
{
    return data->items[*data->current_item];
}


void Item::ApplyAction(const Action &action) const
{
    if (IsPage())
    {
        GetPage()->ApplyAction(action);
    }
}


void Page::ApplyAction(const Action &action) const
{
    if (action.key == Key::Up)
    {
        PrevCurrentItem();
    }
    else if (action.key == Key::Down)
    {
        NextCurrentItem();
    }
    else if (action.key == Key::Menu)
    {
        if (NumItems())
        {
            if (CurrentItem()->IsPage())
            {
                CurrentItem()->GetPage()->Open();
            }
        }
    }
    else if (action.key == Key::Cancel)
    {
        Close();
    }
}


void Page::NextCurrentItem() const
{
    int8 current = *data->current_item + 1;

    if (current == NumItems())
    {
        current = 0;
    }

    *data->current_item = current;
}


void Page::PrevCurrentItem() const
{
    int8 current = *data->current_item - 1;

    if (current < 0)
    {
        current = (int8)(NumItems() - 1);
    }

    *data->current_item = current;
}


int Page::NumItems() const
{
    for(int i = 0; ; i++)
    {
        if (data->items[i] == nullptr)
        {
            return i;
        }
    }
}


void Page::Open() const
{
    *data->opened = 1;

    Menu::SetCurrentItem(GetSelfItem());
}

void Page::Close() const
{
    *data->opened = 0;

    if (GetDataItem()->keeper == nullptr)
    {
        Menu::Close();
    }
    else
    {
        Menu::SetCurrentItem(GetDataItem()->keeper);
    }
}
