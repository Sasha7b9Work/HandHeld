// 2024/03/07 09:45:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_0(pageHistory, nullptr, "Журнал вызовов");

const Item *const PageHistory::self = &pageHistory;
