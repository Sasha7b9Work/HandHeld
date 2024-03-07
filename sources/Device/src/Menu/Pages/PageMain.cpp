// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_1(pageMain, nullptr, "Μενώ", PageAlarm::self);


const Item *PageMain::self = &pageMain;
