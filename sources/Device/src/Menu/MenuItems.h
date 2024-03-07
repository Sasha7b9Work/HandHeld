// 2024/03/02 13:56:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ItemType
{
    enum E
    {
        Page,
        Button,
        CustomButton,
        Count
    };
};


struct Item;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Item
struct DataItem
{
    ItemType::E type;
    Item       *keeper;     // Предок итема
    pchar       title;
};


struct Item
{
    const DataItem *data;
    const void     *item;     // Указатель на структуру типа ItemType
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page
struct DataPage
{
    const Item **items;
    const int8 *current_item;    // Текущий элемент страницы
};


struct Page
{
    const DataPage *data;

    const Item *CastToItem() { return (const Item *)((uint)this - 4); }
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
