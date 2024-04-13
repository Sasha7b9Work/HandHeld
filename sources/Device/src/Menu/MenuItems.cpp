// 2024/03/02 13:56:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Display/Display.h"
#include "Menu/Menu.h"
#include "Hardware/Watch.h"
#include "Display/Font/Font.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"


void Item::Draw() const
{
    if (IsPage())
    {
        GetPage()->Draw();
    }
    else if (IsDate())
    {
        GetDate()->Draw();
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


void Date::DrawField(int x, int y, const Text<> &text, bool selected) const
{
    const int width = 42;
    const int height = 35;

    Rect(width, height).Draw(x, y, selected ? Color::BLACK : Color::WHITE);
    Rect(width - 2, height - 2).Fill(x + 1, y + 1, selected ? Color::WHITE : Color::BLACK);
    if (selected)
    {
        Rect(width + 2, height + 2).Draw(x - 1, y - 1, Color::WHITE);
    }
    Font::SetSize(4);
    text.Write(x + 3, y + 3, selected ? Color::BLACK : Color::WHITE);
    Font::SetSize(1);
}


void Date::Draw() const
{
    if (data->item->IsOpened())
    {
        Font::SetSize(2);

        Text<>("ÓÑÒÀÍÎÂÊÀ").Write(10, 5, Color::WHITE);

        Font::SetSize(1);

        int values[3] = {
            data->date_time->Day,
            data->date_time->Month,
            data->date_time->Year
        };

        const int y = 32;

        const int x[3] = { 5, 58, 111 };

        for (int i = 0; i < 3; i++)
        {
            DrawField(x[i], y, Text<>("%02d", values[i]), i == *data->field);
        }
    }
    else
    {
        Font::SetSize(2);

        data->item->Title().WriteInCenter(0, 30, Display::WIDTH, Color::BLUE);

        Font::SetSize(1);
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
    else if (IsDate())
    {
        GetDate()->ApplyAction(action);
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
        *data->field = *data->field + 1;

        if (*data->field == 3)
        {
            if (data->is_alarm)
            {
                gset.time_alarm.Day = data->date_time->Day;
                gset.time_alarm.Month = data->date_time->Month;
                gset.time_alarm.Year = data->date_time->Year;

                PCF8563::SetAlarm(&gset.time_alarm);
            }
            else
            {
                RTCDateTime current_time = PCF8563::GetDateTime();

                current_time.Day = data->date_time->Day;
                current_time.Month = data->date_time->Month;
                current_time.Year = data->date_time->Year;

                PCF8563::SetDateTime(&current_time);
            }

            data->item->Close();
        }
    }
    else if (action.key == Key::Cancel)
    {
        data->item->Close();
    }
    else if (action.key == Key::Up)
    {
        ChangeValueInCurrentField(+1);
    }
    else if (action.key == Key::Down)
    {
        ChangeValueInCurrentField(-1);
    }
}


void Date::ChangeValueInCurrentField(int delta) const
{
    int field = *data->field;

    if (field > 2)
    {
        return;
    }

    uint8 *refs[3] =
    {
        &data->date_time->Day,
        &data->date_time->Month,
        &data->date_time->Year
    };

    int min[6] = { 1, 1, 0 };
    int max[6] = { 31, 12, 99 };

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

    if (IsDate())
    {
        *GetDate()->data->field = 0;

        if (GetDate()->data->is_alarm)
        {
            *GetDate()->data->date_time = gset.time_alarm;
        }
        else
        {
            *GetDate()->data->date_time = PCF8563::GetDateTime();
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
