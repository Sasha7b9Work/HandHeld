// 2024/03/10 14:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


DEF_CHOICE(choiceMelody, PageCalls::PageDoorBell::self, "Мелодия", &gset.sources[Source::Bell].melody, 10);

DEF_CHOICE(choiceVolume, PageCalls::PageDoorBell::self, "Громкость", &gset.sources[Source::Bell].volume, 10);

DEF_CHOICE(choiceEnableLED, PageCalls::PageDoorBell::self, "Светодиод", &gset.sources[Source::Bell].enabled_led, 1);

DEF_CHOICE(choiceEnableMelody, PageCalls::PageDoorBell::self, "Звук", &gset.sources[Source::Bell].enabled_melody, 1);

DEF_CHOICE(choiceEnabledVibro, PageCalls::PageDoorBell::self, "Вибрация", &gset.sources[Source::Bell].enabled_vibrato, 1);


DEF_PAGE_5(pageDoorBell, PageCalls::self, "Дверной звонок",
    &choiceMelody,
    &choiceVolume,
    &choiceEnableLED,
    &choiceEnableMelody,
    &choiceEnabledVibro
);


const Item *const PageCalls::PageDoorBell::self = &pageDoorBell;
