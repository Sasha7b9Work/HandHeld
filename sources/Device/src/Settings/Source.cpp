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

    if (source.enabled_melody)
    {
        Beeper::Play((TypeSound::E)source.melody, source.volume);
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

void Source::DrawParameters(Source::E source)
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
