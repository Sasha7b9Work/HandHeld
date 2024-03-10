// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_0(pageMobile, PageCalls::self, "Мобильный телефон");


const Item *const PageCalls::PageMobile::self = &pageMobile;
