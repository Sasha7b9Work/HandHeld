// 2024/03/23 17:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Source.h"
#include "Display/Icons.h"
#include "Hardware/Timer.h"
#include "Hardware/Vibrato.h"
#include "Storage/Storage.h"
#include "Modules/LED/LED.h"
#include "Modules/Beeper/Beeper.h"
#include <cstring>


Source::E Source::Queue::buffer[Source::Count] = { Source::Count, Source::Count, Source::Count, Source::Count, Source::Count };
int Source::Queue::size = 0;

Source::Queue::Time Source::Queue::time_recv[Source::Count];

void Source::DrawIcon(int x, int y, const Color &color) const
{
    sourceIcons[value]->Draw(x, y, color);
}


static bool need_received[Source::Count] = { false, false, false, false, false };


pchar Source::Name(E v)
{
    static const pchar names[Count] =
    {
        "ДВЕРНОЙ ЗВОНОК",
        "МОБИЛЬНЫЙ ТЕЛЕФОН",
        "ДОМАШНИЙ ТЕЛЕФОН",
        "ДОМОФОН",
        "МИКРОФОН"
    };

    return names[v];
}


void Source::Receive(E type)
{
    need_received[type] = true;
}


bool Source::IsReceived(E type)
{
    return Queue::IsConsist(type);
}


void Source::Update()
{
    for (int i = 0; i < Source::Count; i++)
    {
        if (need_received[i])
        {
            need_received[i] = false;

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

            if (time_prev_signal[i] == 0 ||
                (TIME_MS > time_prev_signal[i] + time_pause[i]))
            {
                time_prev_signal[i] = TIME_MS;

                Queue::Push((Source::E)i);
            }
        }
    }

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
        Beeper::Stop();
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

    if (source.mode_indication == ModeIndication::All || source.mode_indication == ModeIndication::Sound || source.mode_indication == ModeIndication::Sound_LED || source.mode_indication == ModeIndication::Sound_Vibro)
    {
        Beeper::Play((TypeSound::E)source.melody, (uint8)source.volume);
    }

    if (source.mode_indication == ModeIndication::All || source.mode_indication == ModeIndication::Vibro || source.mode_indication == ModeIndication::Sound_Vibro || source.mode_indication == ModeIndication::LED_Vibro)
    {
        Vibrato::Enable();
    }

    if (source.mode_indication == ModeIndication::All || source.mode_indication == ModeIndication::LED || source.mode_indication == ModeIndication::Sound_LED || source.mode_indication == ModeIndication::LED_Vibro)
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
            if (TIME_MS > time_recv[buffer[i]].GetMS() + TIME_ALARM)
            {
                Remove(i, false);
            }
        }
    }
}


void Source::CancelFirst()
{
    Queue::Remove(0, true);
}


void Source::Queue::Remove(int index, bool received)
{
    if (index < Size())
    {
        Source::E source = buffer[index];

        Storage::Append(time_recv[source].GetRTC(), source, received);

        size--;

        if (size)
        {
            std::memmove(buffer + index, buffer + index + 1, (uint)size * sizeof(Source::E));
        }
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
