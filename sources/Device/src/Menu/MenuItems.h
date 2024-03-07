// 2024/03/02 13:56:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Keyboard/Keyboard.h"
#include "Display/Display.h"


struct ItemType
{
    enum E
    {
        Page,
        Button,
        CustomButton,
        Time,
        Count
    };
};


struct Item;
struct Page;
struct Time;


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
    const Page *GetPage() const { if (IsPage()) { return (const Page *)item; } return nullptr; }
    const Time *GetTime() const { if (IsTime()) { return (const Time *)item; } return nullptr; }
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
};


struct Time
{
    const DataTime *data;
    void Draw() const;
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
