// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"


DEF_PAGE_0(pageHomePhone, PageCalls::self, "Домашний телефон");


const Item *const PageCalls::PageHomePhone::self = &pageHomePhone;
