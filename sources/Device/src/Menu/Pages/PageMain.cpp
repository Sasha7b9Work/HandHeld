// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"


static const Item *items_main[] =
{
    PageAlarm::self,
    nullptr
};


static const DataPage dp_main{ items_main };


static const Page page_main{ &dp_main };


static const DataItem di_page_main{ ItemType::Page, nullptr, "Μενώ" };

static const Item item_page_main{ &di_page_main, &page_main };


const Item *PageMain::self = &item_page_main;
