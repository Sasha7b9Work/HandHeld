// 2024/03/06 21:37:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/PCF8563/PCF8563.h"


#define DEF_DATE(name, keeper, title, is_alarm)                                                                             \
static int8 opened##name = 0;                                                                                               \
static int8 field##name = 0;                                                                                                \
static const DataItem name##data = { ItemType::Time, keeper, title, &opened##name };                                        \
extern const Item name;                                                                                                     \
static RTCDateTime name##date_time;                                                                                         \
static const DataDate name##datatime = { &name, &field##name, &name##date_time, is_alarm };                                 \
static const StructTime name##time = { &name##datatime };                                                                   \
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

#define DEF_PAGE_1(name, keeper, title, item0, func_draw_closed, func_draw_opened, func_key)                                \
static const Item *items##name[] = { item0, nullptr };                                                                      \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_2(name, keeper, title, item0, item1, func_draw_closed, func_draw_opened, func_key)                         \
static const Item *items##name[] = { item0, item1, nullptr };                                                               \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_3(name, keeper, title, item0, item1, item2, func_draw_closed, func_draw_opened, func_key)                  \
static const Item *items##name[] = { item0, item1, item2, nullptr };                                                        \
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

#define DEF_PAGE_7(name, keeper, title, item0, item1, item2, item3, item4, item5, item6,                                    \
    func_draw_closed, func_draw_opened, func_key)                                                                           \
static const Item *items##name[] = { item0, item1, item2, item3, item4, item5, item6, nullptr };                            \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_8(name, keeper, title, item0, item1, item2, item3, item4, item5, item6, item7,                             \
    func_draw_closed, func_draw_opened, func_key)                                                                           \
static const Item *items##name[] = { item0, item1, item2, item3, item4, item5, item6, item7, nullptr };                     \
static int8 current_item##name = 0;                                                                                         \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                                               \
extern const Item name;                                                                                                     \
static const DataPage dp##name{&name, items##name, &current_item##name, func_draw_closed, func_draw_opened, func_key};      \
static const Page page##name{&dp##name};                                                                                    \
const Item name{&di##name, &page##name}

#define DEF_PAGE_9(name, keeper, title, item0, item1, item2, item3, item4, item5, item6, item7, item8,                      \
    func_draw_closed, func_draw_opened, func_key)                                                                           \
static const Item *items##name[] = { item0, item1, item2, item3, item4, item5, item6, item7, item8, nullptr };              \
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

#define DEF_CHOICE_3(name, keeper, title, value, name0, name1, name2)                                                       \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Choice, keeper, title, &opened##name};                                             \
extern const Item name;                                                                                                     \
static const pchar names##name[] = {name0, name1, name2, nullptr };                                                         \
static const DataChoice dc##name{&name, value, &names##name[0]};                                                            \
static const Choice choice##name{&dc##name};                                                                                \
const Item name{&di##name, &choice##name}

#define DEF_CHOICE_7(name, keeper, title, value, name0, name1, name2, name3, name4, name5, name6)                           \
static int8 opened##name = 0;                                                                                               \
static const DataItem di##name{ItemType::Choice, keeper, title, &opened##name};                                             \
extern const Item name;                                                                                                     \
static const pchar names##name[] = {name0, name1, name2, name3, name4, name5, name6, nullptr };                             \
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
