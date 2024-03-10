// 2024/03/06 21:37:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Modules/PCF8563/PCF8563.h"

//#define DEF_CUSTOM_BUTTON(name, keeper, title, x, y, width, height, funcPress)


//#define DEF_BUTTON

#define DEF_TIME(name, keeper, title)                                                               \
static int8 opened##name = 0;                                                                       \
static int8 field##name = 0;                                                                        \
static const DataItem name##data = { ItemType::Time, keeper, title, &opened##name };                \
extern const Item name;                                                                             \
static RTCDateTime name##date_time;                                                                 \
static const DataTime name##datatime = { &name, &field##name, &name##date_time };                   \
static const Time name##time = { &name##datatime };                                                 \
const Item name = {&name##data, &name##time }

#define DEF_PAGE_0(name, keeper, title)                                                             \
static const Item *items##name[] = { nullptr };                                                     \
static int8 current_item##name = 0;                                                                 \
static int8 opened##name = 0;                                                                       \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                       \
extern const Item name;                                                                             \
static const DataPage dp##name{&name, items##name, &current_item##name};                            \
static const Page page##name{&dp##name};                                                            \
const Item name{&di##name, &page##name}

#define DEF_PAGE_4(name, keeper, title, item0, item1, item2, item3)                                 \
static const Item *items##name[] = { item0, item1, item2, item3, nullptr };                         \
static int8 current_item##name = 0;                                                                 \
static int8 opened##name = 0;                                                                       \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                       \
extern const Item name;                                                                             \
static const DataPage dp##name{&name, items##name, &current_item##name};                            \
static const Page page##name{&dp##name};                                                            \
const Item name{&di##name, &page##name}

#define DEF_PAGE_5(name, keeper, title, item0, item1, item2, item3, item4)                          \
static const Item *items##name[] = { item0, item1, item2, item3, item4, nullptr };                  \
static int8 current_item##name = 0;                                                                 \
static int8 opened##name = 0;                                                                       \
static const DataItem di##name{ItemType::Page, keeper, title, &opened##name};                       \
extern const Item name;                                                                             \
static const DataPage dp##name{&name, items##name, &current_item##name};                            \
static const Page page##name{&dp##name};                                                            \
const Item name{&di##name, &page##name}
