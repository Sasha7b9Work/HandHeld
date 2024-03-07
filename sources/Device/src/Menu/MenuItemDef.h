// 2024/03/06 21:37:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


//#define DEF_CUSTOM_BUTTON(name, keeper, title, x, y, width, height, funcPress)


//#define DEF_BUTTON


#define DEF_PAGE_1(name, keeper, title, item0)                  \
static const Item *items##name[] = { item0, nullptr };          \
static const DataPage dp##name{items##name};                    \
static const Page page##name{&dp##name};                        \
static const DataItem di##name{ItemType::Page, nullptr, title}; \
static const Item name{&di##name, &page##name}

#define DEF_PAGE_2(name, keeper, title, item0, item1)
