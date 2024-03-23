// 2024/03/02 19:47:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"
#include "Player/Player.h"
#include "Hardware/LED.h"
#include "Hardware/Vibrato.h"
#include "Display/Icons.h"
#include <cstdlib>


Settings gset =
{
    { {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1},
      {0, 9, 1, 1, 1} },
    { 0, 0, 0, 0, 0, 0 }
};


uint Source::time_recv[Source::Count] = { 0, 0, 0, 0, 0 };


void Source::DrawIcon(int x, int y, const Color &color) const
{
    sourceIcons[value]->Draw(x, y, color);
}


pchar Source::Name(E v)
{
    static const pchar names[Count] =
    {
        "ÄÂÅÐÜ",
        "ÌÎÁ. ÒÅËÅÔÎÍ",
        "ÄÎÌ. ÒÅËÅÔÎÍ",
        "ÄÎÌÎÔÎÍ",
        "ÄÀÒ×ÈK"
    };

    return names[v];
}


void Source::Receive(E type)
{
    time_recv[type] = TIME_MS;

    const SettingsSource &source = gset.sources[type];

    if (source.enabled_melody)
    {
        Player::Play((TypeSound::E)source.melody, source.volume);
    }

    if (source.enabled_vibrato)
    {
        Vibrato::Enable();
    }

    if (source.enabled_led)
    {
        LED::Enable();
    }
}


bool Source::IsReceived(E type)
{
    return time_recv[type] + 1000 > TIME_MS;
}


void Source::Update()
{
    bool enabled = false;

    for (int i = 0; i < Source::Count; i++)
    {
        if (IsReceived((Source::E)i))
        {
            enabled = true;
        }
    }

    if (!enabled)
    {
        Vibrato::Disable();
        LED::Disable();
    }
}
