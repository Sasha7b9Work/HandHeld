// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Display/Display.h"
#include "Menu/Menu.h"
#include "Hardware/Watch.h"
#include "Display/Font/Font.h"


void Item::Draw() const
{
    if (IsPage())
    {
        GetPage()->Draw();
    }
    else if (IsTime())
    {
        GetTime()->Draw();
    }
}


void Page::Draw() const
{
    if (data->item->IsOpened())
    {
        const Item *current_item = CurrentItem();

        if (current_item)
        {
            current_item->Draw();
        }
    }
    else
    {
        data->item->Title().Write(10, 10, Color::WHITE);
    }
}


void Time::Draw() const
{
    if (data->item->IsOpened())
    {
        int values[6] = {
            data->date_time->Hour,
            data->date_time->Minute,
            data->date_time->Second,
            data->date_time->Day,
            data->date_time->Month,
            data->date_time->Year - 2000
        };

        int x0 = 10;
        int x1 = 40;
        int x2 = 70;

        int y0 = 10;
        int y1 = 35;

        int x[6] = { x0, x1, x2, x0, x1, x2 };
        int y[6] = { y0, y0, y0, y1, y1, y1 };

        for (int i = 0; i < 6; i++)
        {
            Rect(23, 20).Draw(x[i], y[i], Color::WHITE);

            Font::SetSize(2);

            Text<>("%02d", values[i]).Write(x[i] + 3, y[i] + 3);

            Font::SetSize(1);
        }
    }
    else
    {
        data->item->Title().Write(10, 10, Color::WHITE);

        Watch::Draw(30, 30, Color::GREEN);
    }
}


Text<> Item::Title() const
{
    const Page *page_keeper = data->keeper->GetPage();

    for (int i = 0; ; i++)
    {
        if (page_keeper->data->items[i] == this)
        {
            return Text<>("%d/%d %s", i + 1, page_keeper->NumItems(), data->title);
        }
    }
}


const DataItem *Page::GetDataItem() const
{
    return data->item->data;
}


bool Item::IsOpened() const
{
    if (data->keeper == nullptr)
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
    else if (IsTime())
    {
        GetTime()->ApplyAction(action);
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
            CurrentItem()->Open();
        }
    }
    else if (action.key == Key::Cancel)
    {
        data->item->Close();
    }
}


void Time::ApplyAction(const Action &action) const
{
    if (action.key == Key::Cancel)
    {
        data->item->Close();
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


void Item::Open() const
{
    *data->opened = 1;

    if (IsTime())
    {
        PCF8563::GetDateTime(GetTime()->data->date_time);
    }

    Menu::SetCurrentItem(this);
}

void Item::Close() const
{
    *data->opened = 0;

    if (data->keeper == nullptr)
    {
        Menu::Close();
    }
    else
    {
        Menu::SetCurrentItem(data->keeper);
    }
}
