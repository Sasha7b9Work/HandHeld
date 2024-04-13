// 2024/03/07 09:52:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuItemDef.h"

/*
  ���������, �����, ����, ������� ������, M�������� �������, �������� �������, �������, ��������, ������
*/


DEF_PAGE_9(pageMain, nullptr, "����",
    PageAlarm::self,
    PageTime::self,
    PageDate::self,
    PageDoorBell::self,
    PageMobile::self,
    PageHomePhone::self,
    PageIntercom::self,
    PageMicrophone::self,
    PageJournal::self,
    nullptr,
    nullptr,
    nullptr
);


const Item * const PageMain::self = &pageMain;
