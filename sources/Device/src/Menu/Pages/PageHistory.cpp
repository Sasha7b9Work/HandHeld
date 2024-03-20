// 2024/03/07 09:45:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Display/Display.h"


namespace PageHistory
{
    static void FuncDraw_History()
    {
        HLine(160).Draw(0, 26, Color::WHITE);
        HLine(160).Draw(0, 53);
    }

    static bool Func_ActionKey(const Action &action)
    {
        if (action.key == Key::Up || action.key == Key::Down)
        {
            return true;
        }

        return false;
    }

    DEF_PAGE_0(pageHistory, PageMain::self, "ÆÓÐÍÀË ÂÛÇÎÂÎÂ",
        nullptr,
        FuncDraw_History,
        Func_ActionKey
    );

    const Item *const self = &pageHistory;
}
