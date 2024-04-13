// 2024/03/07 09:44:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Menu/MenuItemDef.h"
#include "Settings/Settings.h"


namespace PageCalls
{
    void DrawParameters(Source::E source)
    {
        const int x0 = 10;
        const int x1 = 80;
        const int dy = 10;
        int y = 25;

        Text<>("Мелодия").Write(x0, y, Color::WHITE);
        Text<>("%d", gset.sources[source].melody + 1).Write(x1, y);

        y += dy;

        Text<>("Громкость").Write(x0, y);
        Text<>("%d", gset.sources[source].volume + 1).Write(x1, y);

        y += dy;

        Text<>("Свет").Write(x0, y);
        Text<>(gset.sources[source].enabled_led == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("Звук").Write(x0, y);
        Text<>(gset.sources[source].enabled_melody == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);

        y += dy;

        Text<>("Вибрация").Write(x0, y);
        Text<>(gset.sources[source].enabled_vibrato == 0 ? DISABLED_RU : ENABLED_RU).Write(x1, y);
    }
}
