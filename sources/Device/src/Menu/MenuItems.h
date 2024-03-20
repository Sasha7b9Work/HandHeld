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
    const Item *keeper;     // ������ �����
    pchar       title;
    int8 *const opened;     // ���� �� ����� ����, �� ���� �������

};


struct Item
{
    const DataItem *data;
    const void     *item;     // ��������� �� ��������� ���� ItemType
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
    const Item     *item;           // � ���� ����� �������� ������ ���������
    const Item   **items;
    int8 * const   current_item;    // ������� ������� ��������
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
    // ������� ������� ��������� �������
    void NextCurrentItem() const;
    // ������� ������� ���������� �������
    void PrevCurrentItem() const;
    int NumItems() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Time
struct DataTime
{
    const Item *item;
    int8 *const field;          // �������� ���� 0 - ����, 1 - ������, 2 - �������, 3 - ����, 4 - �����, 5 - ���, 6 - ������, 7 - ���������
    RTCDateTime * const date_time;
    static int8 in_edit_mode;
    const bool is_alarm;        // ���� true - �� ��������� ����������
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
