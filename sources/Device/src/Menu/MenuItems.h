// 2024/03/02 13:56:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ItemType
{
    enum E
    {
        Page,
        Count
    };
};


struct DataItem
{
    ItemType::E type;
};


struct Item
{
    DataItem *data;
    void     *item;
};


struct DataPage
{

};


struct Page
{
    DataPage *data;
};
