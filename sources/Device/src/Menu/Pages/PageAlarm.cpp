// 2024/03/07 09:44:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_0(pageAlarm, nullptr, "Будильник");

const Item * const PageAlarm::self = &pageAlarm;
