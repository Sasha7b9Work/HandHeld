// 2024/03/06 21:37:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/PCF8563/PCF8563.h"

//#define DEF_CUSTOM_BUTTON(name, keeper, title, x, y, width, height, funcPress)


//#define DEF_BUTTON

#define DEF_TIME(name, keeper, title, is_alarm)                                                                             \
static int8 opened##name = 0;                                                                                               \
static int8 field##name = 0;                                                                                                \
static const DataItem name##data = { ItemType::Time, keeper, title, &opened##name };                                        \
extern const Item name;                                                                                                     \
static RTCDateTime name##date_time;                                                                                         \
static const DataTime name##datatime = { &name, &field##name, &name##date_time, is_alarm };                                 \
static const Time name##time = { &name##datatime };                                                                         \
const Item name = {&name##data, &name##time }

#define DEF_PAGE_0(name, keeper, title, func_draw_closed, func_draw_opened, func_key)                                       \
static const Item *items##name[] = { nullptr };                                                                             \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_4(name, keeper, title, item0, item1, item2, item3, func_draw_closed, func_draw_opened, func_key)           \
static const Item *items##name[] = { item0, item1, item2, item3, nullptr };                                                 \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_5(name, keeper, title, item0, item1, item2, item3, item4, func_draw_closed, func_draw_opened,              \
    func_key)                                                                                                               \
static const Item *items##name[] = { item0, item1, item2, item3, item4, nullptr };                                          \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_6(name, keeper, title, item0, item1, item2, item3, item4, item5, func_draw_closed, func_draw_opened,       \
    func_key)                                                                                                               \
static const Item *items##name[] = { item0, item1, item2, item3, item4, item5, nullptr };                                   \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_CHOICE_2(name, keeper, title, value, name0, name1)                                                              \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Choice, keeper, title, &opened##name};                                             \
extern const Item name;                                                                                                     \
static const pchar names##name[] = {name0, name1, nullptr};                                                                 \
static const DataChoice dc##name{&name, value, &names##name[0]};                                                            \
static const Choice choice##name{&dc##name};                                                                                \
const Item name{&di##name, &choice##name}

#define DEF_CHOICE_10(name, keeper, title, value, name0, name1, name2, name3, name4, name5, name6, name7, name8, name9)     \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Choice, keeper, title, &opened##name};                                             \
extern const Item name;                                                                                                     \
static const pchar names##name[] = {name0, name1, name2, name3, name4, name5, name6, name7, name8, name9, nullptr };        \
static const DataChoice dc##name{&name, value, &names##name[0]};                                                            \
static const Choice choice##name{&dc##name};                                                                                \
const Item name{&di##name, &choice##name}
