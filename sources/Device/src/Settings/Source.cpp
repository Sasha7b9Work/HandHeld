// 2024/03/23 17:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Source.h"
#include "Display/Icons.h"
#include "Hardware/Timer.h"
#include "Player/Player.h"
#include "Hardware/Vibrato.h"
#include "Hardware/LED.h"
#include "Storage/Storage.h"
#include <cstring>


Source::E Source::Queue::buffer[Source::Count] = { Source::Count, Source::Count, Source::Count, Source::Count, Source::Count };
int Source::Queue::size = 0;

Source::Queue::Time Source::Queue::time_recv[Source::Count];

void Source::DrawIcon(int x, int y, const Color &color) const
{
    sourceIcons[value]->Draw(x, y, color);
}


Text<> Source::Name(E v)
{
    static const pchar names[Count] =
    {
        "ДВЕРЬ",
        "МОБ. ТЕЛЕФОН",
        "ДОМ. ТЕЛЕФОН",
        "ДОМОФОН",
        "ДАТЧИK"
    };

    return Text<>(names[v]);
}


void Source::Receive(E type)
{
    // Время предыдущего приёма сигнала
    static uint time_prev_signal[Source::Count] = { 0, 0, 0, 0, 0 };

    // Время, в течение которого не нужно повторно принимать событие
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
        time_prev_signal[type] = TIME_MS;

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
        Player::Stop();
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
                time_recv[type].Set(TIME_MS, PCF8563::GetDateTime());
                break;
            }
        }
    }
    else
    {
        buffer[size++] = type;
        time_recv[type].Set(TIME_MS, PCF8563::GetDateTime());
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

            if (TIME_MS > time_recv[source].GetMS() + TIME_ALARM)
            {
                Storage::Append(time_recv[source].GetRTC(), source, false);

                size--;

                if (size)
                {
                    std::memmove(buffer + i, buffer + i + 1, (uint)size * sizeof(Source::E));
                }
            }
        }
    }
}


void Source::CancelFirst()
{
    Queue::PopFirst();
}


void Source::Queue::PopFirst()
{
    if (Size() == 0)
    {
        return;
    }

    Source::E source = buffer[0];

    Storage::Append(time_recv[source].GetRTC(), source, true);

    size--;

    if (size)
    {
        std::memmove(buffer, buffer + 1, (uint)size * sizeof(Source::E));
    }
}


int Source::GetCountReceived()
{
    return Queue::Size();
}


Source::E Source::GetFirstReceived()
{
    return Queue::At(0);
}
