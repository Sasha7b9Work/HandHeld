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
struct Page;


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
    void Draw() const;
    bool IsPage() const;
    const Page *GetPage() const;    // Возвращает указатель на объект типа Page, если возможно. Иначе возвращает nullptr
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page
struct DataPage
{
    const DataItem *data_item;
    const Item **items;
    const int8 *current_item;   // Текущий элемент страницы
    const int8 *opened;         // Если не равно нулю, то страница открыта
};


struct Page
{
    const DataPage *data;
    void Draw() const;
    bool IsOpened() const;
    const Item *CurrentItem() const;
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
