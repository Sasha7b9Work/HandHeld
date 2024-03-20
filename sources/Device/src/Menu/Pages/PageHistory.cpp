// 2024/03/07 09:45:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Display/Display.h"


namespace PageHistory
{
    static void FuncDraw_History()
    {
        HLine(180).Draw(0, 26, Color::WHITE);
        HLine(180).Draw(0, 53);
    }

    DEF_PAGE_0(pageHistory, PageMain::self, "ÆÓĞÍÀË ÂÛÇÎÂÎÂ",
        nullptr,
        FuncDraw_History
    );

    const Item *const self = &pageHistory;
}
