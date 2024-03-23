// 2024/03/23 17:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Source.h"
#include "Display/Icons.h"
#include "Hardware/Timer.h"
#include "Player/Player.h"
#include "Hardware/Vibrato.h"
#include "Hardware/LED.h"
#include <cstring>


Source::E Source::Queue::buffer[Source::Count] = { Source::Count, Source::Count, Source::Count, Source::Count, Source::Count };
int Source::Queue::size = 0;

uint Source::Queue::time_recv[Source::Count] = { 0, 0, 0, 0, 0 };

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
    // Âðåìÿ ïðåäûäóùåãî ïðè¸ìà ñèãíàëà
    static uint time_prev_signal[Source::Count] = { 0, 0, 0, 0, 0 };

    // Âðåìÿ, â òå÷åíèå êîòîðîãî íå íóæíî ïîâòîðíî ïðèíèìàòü ñîáûòèå
    static const uint time_pause[Source::Count] =
    {
        1000,
        10000,
        10000,
        10000,
        15000
    };

    if (time_prev_signal[type] == 0 ||
        (TIME_MS > time_prev_signal[type] + time_pause[type]))
    {
        Queue::Push(type);
    }
}


bool Source::IsReceived(E type)
{
    return Queue::IsConsist(type);
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


void Source::Queue::Push(Source::E type)
{
    if (IsConsist(type))
    {
        for (int i = 0; i < size; i++)
        {
            if (buffer[i] == type)
            {
                time_recv[type] = TIME_MS;
                break;
            }
        }
    }
    else
    {
        buffer[size++] = type;
        time_recv[type] = TIME_MS;
    }

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


Source::E Source::Queue::At(int i)
{
    return buffer[i];
}


bool Source::Queue::IsConsist(Source::E source)
{
    DeleteOld();

    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == source)
        {
            return true;
        }
    }

    return false;
}


void Source::Queue::DeleteOld()
{
    if (size)
    {
        for (int i = 0; i < size; i++)
        {
            Source::E source = buffer[i];

            if (TIME_MS > time_recv[source] + TIME_ALARM)
            {
                size--;

                if (size)
                {
                    std::memmove(buffer, buffer + 1, size * sizeof(Source::E));
                }
            }
        }
    }
}
