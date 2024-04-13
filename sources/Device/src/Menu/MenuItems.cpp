// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Display/Display.h"
#include "Menu/Menu.h"
#include "Hardware/Watch.h"
#include "Display/Font/Font.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"


int8 DataDate::in_edit_mode = 0;


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
    else if (IsChoice())
    {
        GetChoice()->Draw();
    }
}


void Page::Draw() const
{
    if (data->item->IsOpened())
    {
        if (data->func_draw_opened)
        {
            data->func_draw_opened();
        }
        else
        {
            const Item *current_item = CurrentItem();

            if (current_item)
            {
                current_item->Draw();
            }
        }
    }
    else
    {
        Font::SetSize(2);

        data->item->Title().WriteInCenter(0, 30, Display::WIDTH, Color::BLUE);

        Font::SetSize(1);

        if (data->func_draw_closed)
        {
            data->func_draw_closed();
        }
    }
}


void Choice::Draw() const
{
    if (data->item->IsOpened())
    {

    }
    else
    {
        data->item->Title().Write(10, 10, Color::WHITE);

        int index = (int)(*data->value);

        pchar text = data->names[index];

        Text<>(text).Write(10, 40, Color::WHITE);
    }
}


void Date::DrawField(int x, int y, int width, int height, const Text<> &text, bool selected) const
{
    Rect(width, height).Draw(x, y, selected ? Color::BLACK : Color::WHITE);
    Rect(width - 2, height - 2).Fill(x + 1, y + 1, selected ? Color::WHITE : Color::BLACK);
    if (selected)
    {
        Rect(width + 2, height + 2).Draw(x - 1, y - 1, Color::WHITE);
    }
    Font::SetSize(2);
    text.Write(x + 3, y + 3, selected ? Color::BLACK : Color::WHITE);
    Font::SetSize(1);
}


void Date::Draw() const
{
    if (data->item->IsOpened())
    {
        int values[6] = {
            data->date_time->Hour,
            data->date_time->Minute,
            data->date_time->Second,
            data->date_time->Day,
            data->date_time->Month,
            data->date_time->Year
        };

        int x0 = 20;
        int x1 = 50;
        int x2 = 80;

        int y0 = 15;
        int y1 = 45;

        int x[6] = { x0, x1, x2, x0, x1, x2 };
        int y[6] = { y0, y0, y0, y1, y1, y1 };

        for (int i = 0; i < 6; i++)
        {
            DrawField(x[i], y[i], 23, 20, Text<>("%02d", values[i]), i == *data->field);

            if (i == *data->field && data->in_edit_mode != 0)
            {
                Color backbround = Color::WHITE;

                Font::SetSize(2);
                Text<>("+").Write(x[i] + 9, y[i] - 13, backbround);
                Text<>("+").Write(x[i] + 9, y[i] + 18, backbround);
                Font::SetSize(1);
            }
        }

        DrawField(110, 15, 40, 20, Text<>("0тм"), 6 == *data->field);

        DrawField(110, 45, 40, 20, Text<>("Сох"), 7 == *data->field);
    }
    else
    {
        data->item->Title().Write(10, 10, Color::BLUE);

        if (data->is_alarm)
        {
            gset.time_alarm.Draw(30, 30, Color::GREEN);
        }
        else
        {
            Watch::Draw(30, 30, Color::GREEN);
        }
    }
}


Text<> Item::Title() const
{
    const Page *page_keeper = data->keeper->GetPage();

    for (int i = 0; ; i++)
    {
        if (page_keeper->data->items[i] == this)
        {
            return Text<>(data->title);
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
    else if (IsChoice())
    {
        GetChoice()->ApplyAction(action);
    }
}


void Page::ApplyAction(const Action &action) const
{
    bool need_apply = true;

    if (data->func_action_key)
    {
        if (data->func_action_key(action))
        {
            need_apply = false;
        }
    }

    if (need_apply)
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
                if (CurrentItem()->IsChoice())
                {
                    CurrentItem()->ApplyAction(action);
                }
                else
                {
                    CurrentItem()->Open();
                }
            }
        }
        else if (action.key == Key::Cancel)
        {
            data->item->Close();
        }
    }
}


void Choice::ApplyAction(const Action &action) const
{
    if (action.key == Key::Menu)
    {
        int value = (int)(*data->value) + 1;

        if (value == NumChoices())
        {
            value = 0;
        }

        *data->value = (uint8)value;
    }
}


int Choice::NumChoices() const
{
    for (int i = 0; ; i++)
    {
        if (data->names[i] == nullptr)
        {
            return i;
        }
    }
}


void Date::ApplyAction(const Action &action) const
{
    if (action.key == Key::Menu)
    {
        if (*data->field < 6)
        {
            if (data->in_edit_mode == 0)
            {
                data->in_edit_mode = 1;
            }
            else
            {
                data->in_edit_mode = 0;
            }
        }
        else
        {
            if (*data->field == 7)
            {
                if (data->is_alarm)
                {
                    gset.time_alarm = *data->date_time;

                    PCF8563::SetAlarm(&gset.time_alarm);
                }
                else
                {
                    PCF8563::SetDateTime(data->date_time);
                }
            }

            data->item->Close();
        }
    }
    else if (action.key == Key::Cancel)
    {
        if (data->in_edit_mode != 0)
        {
            data->in_edit_mode = 0;
        }
        else
        {
            data->item->Close();
        }
    }
    else if (action.key == Key::Up)
    {
        if (data->in_edit_mode)
        {
            ChangeCurrentField(+1);
        }
        else
        {
            *data->field = *data->field + 1;

            if (*data->field == 8)
            {
                *data->field = 0;
            }
        }
    }
    else if (action.key == Key::Down)
    {
        if (data->in_edit_mode)
        {
            ChangeCurrentField(-1);
        }
        else
        {
            *data->field = *data->field - 1;

            if (*data->field < 0)
            {
                *data->field = 7;
            }
        }
    }
}


void Date::ChangeCurrentField(int delta) const
{
    int field = *data->field;

    if (field > 5)
    {
        return;
    }

    uint8 *refs[6] =
    {
        &data->date_time->Hour,
        &data->date_time->Minute,
        &data->date_time->Second,
        &data->date_time->Day,
        &data->date_time->Month,
        &data->date_time->Year
    };

    int min[6] = { 0, 0, 0, 1, 1, 0 };
    int max[6] = { 23, 59, 59, 31, 12, 99 };

    int value = *refs[field];

    Math::CircleChange(&value, min[field], max[field], (delta < 0) ? -1 : 1);

    *refs[field] = (uint8)value;
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
        if (GetTime()->data->is_alarm)
        {
            *GetTime()->data->date_time = gset.time_alarm;
        }
        else
        {
            *GetTime()->data->date_time = PCF8563::GetDateTime();
        }
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
