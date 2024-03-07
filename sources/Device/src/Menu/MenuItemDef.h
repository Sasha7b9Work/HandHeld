// 2024/03/06 21:37:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


//#define DEF_CUSTOM_BUTTON(name, keeper, title, x, y, width, height, funcPress)


//#define DEF_BUTTON

#define DEF_PAGE_0(name, keeper, title)                                                     \
static const Item *items##name[] = { nullptr };                                             \
static int8 current_item##name = 0;                                                         \
static int8 opened##name = 0;                                                               \
static const DataItem di##name{ItemType::Page, nullptr, title};                             \
static const DataPage dp##name{&di##name, items##name, &current_item##name, &opened##name}; \
static const Page page##name{&dp##name};                                                    \
static const Item name{&di##name, &page##name}

#define DEF_PAGE_4(name, keeper, title, item0, item1, item2, item3)                         \
static const Item *items##name[] = { item0, item1, item2, item3, nullptr };                 \
static int8 current_item##name = 0;                                                         \
static int8 opened##name = 0;                                                               \
static const DataItem di##name{ItemType::Page, nullptr, title};                             \
static const DataPage dp##name{&di##name, items##name, &current_item##name, &opened##name}; \
static const Page page##name{&dp##name};                                                    \
static const Item name{&di##name, &page##name}
