// 2024/03/02 13:56:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Keyboard/Keyboard.h"
#include "Display/Display.h"
#include "Modules/PCF8563/PCF8563.h"


struct ItemType
{
    enum E
    {
        Page,
        Button,
        CustomButton,
        Time,
        Choice,
        Count
    };
};


struct Item;
struct Page;
struct Time;
struct Choice;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Item
struct DataItem
{
    ItemType::E type;
    const Item *keeper;     // Предок итема
    pchar       title;
    int8 *const opened;     // Если не равно нулю, то итем раскрыт

};


struct Item
{
    const DataItem *data;
    const void     *item;     // Указатель на структуру типа ItemType
    void Draw() const;
    bool IsPage() const { return data->type == ItemType::Page; }
    bool IsTime() const { return data->type == ItemType::Time; }
    bool IsChoice() const { return data->type == ItemType::Choice; }
    const Page *GetPage() const { if (IsPage()) { return (const Page *)item; } return nullptr; }
    const Time *GetTime() const { if (IsTime()) { return (const Time *)item; } return nullptr; }
    const Choice *GetChoice() const { if (IsChoice()) { return (const Choice *)item; } return nullptr; }
    void ApplyAction(const Action &) const;
    bool IsOpened() const;
    Text<> Title() const;
    void Open() const;
    void Close() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page
struct DataPage
{
    const Item     *item;           // В этом итеме хранится данная структура
    const Item   **items;
    int8 * const   current_item;    // Текущий элемент страницы
    void (*func_draw_closed)();
    void (*func_draw_opened)();
};


struct Page
{
    const DataPage *data;
    void Draw() const;
    const Item *CurrentItem() const;
    const DataItem *GetDataItem() const;
    void ApplyAction(const Action &) const;
    // Сделать текущим следующий элемент
    void NextCurrentItem() const;
    // Сделать текущим предыдущий элемент
    void PrevCurrentItem() const;
    int NumItems() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Time
struct DataTime
{
    const Item *item;
    int8 *const field;          // Активное поле 0 - часы, 1 - минуты, 2 - секунды, 3 - день, 4 - месяц, 5 - год, 6 - отмена, 7 - сохранить
    RTCDateTime * const date_time;
    static int8 in_edit_mode;
    const bool is_alarm;        // Если true - то настройка будильника
};


struct Time
{
    const DataTime *data;
    void Draw() const;
    void ApplyAction(const Action &) const;
    void ChangeCurrentField(int delta) const;
    void DrawField(int x, int y, int width, int height, const Text<> &, bool selected) const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice
struct DataChoice
{
    const Item *item;
    uint8 *const value;
    const pchar * const names;
};


struct Choice
{
    const DataChoice *data;
    void Draw() const;
    void ApplyAction(const Action &) const;
    int NumChoices() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Button
struct DataButton
{

};


struct Button
{
    DataButton *data;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// CustomButton
struct DataCustomButton
{
    int x;
    int y;
    int width;
    int height;
    void (*funcPress)();
    void (*funcDraw)();
};


struct CustomButton
{
    DataButton *data;
};
