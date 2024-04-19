// 2024/03/23 17:28:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/Source.h"
#include "Display/Icons.h"
#include "Hardware/Timer.h"
#include "Hardware/Vibrato.h"
#include "Storage/Storage.h"
#include "Modules/LED/LED.h"
#include "Modules/Beeper/Beeper.h"
#include "Modules/CMT2210AW/CMT2210AW.h"
#include <cstring>


//const led_vibro_const_t LED_VIBRO_TIMINGS[] = {
//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 200 / 5, .pulse_period = 320 / 5, .pulses_in_packet = 2, .pause_between_packet = 4000 / 5, .total_duration = 38000 / 5},  //���������� �������� ������
//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 240 / 5, .pulse_period = 380 / 5, .pulses_in_packet = 4, .pause_between_packet = 5500 / 5, .total_duration = 31000 / 5},  //���������� �������� (������ ����.5500)
//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 240 / 5, .pulse_period = 450 / 5, .pulses_in_packet = 3, .pause_between_packet = 3500 / 5, .total_duration = 31000 / 5},  //���������� �������� (������ ����.6500)
//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 180 / 5, .pulse_period = 600 / 5, .pulses_in_packet = 5, .pause_between_packet = 1500 / 5, .total_duration = 31000 / 5},  //���������� ����� �������

//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 40 / 5, .pulse_period = 110 / 5, .pulses_in_packet = 255, .pause_between_packet = 55 / 5,   .total_duration = 60000 / 5},  //���������� �������� ������������
//{.led_pulse_duration = 100 / 5, .vibro_pulse_duration = 40 / 5, .pulse_period = 400 / 5, .pulses_in_packet = 6, .pause_between_packet = 600 / 5,  .total_duration = 30000 / 5},  //���������� ��������
//{.led_pulse_duration = 15 / 5, .vibro_pulse_duration = 160 / 5, .pulse_period = 1000 / 5, .pulses_in_packet = 1, .pause_between_packet = 0,      .total_duration = 1000 / 5},  //�������.��������� ��� ���������
//{.led_pulse_duration = 150 / 5, .vibro_pulse_duration = 300 / 5, .pulse_period = 100 / 5, .pulses_in_packet = 2, .pause_between_packet = 0,      .total_duration = 600 / 5},  //�������.��������� ��� ����������


const SourceScript SourceScript::scripts[Source::Count] =
{
    { 100, 200, 320, 2, 4000 },
    { 100, 100, 400, 3, 4000 },
    { 100, 240, 380, 4, 5500 },
    { 100, 240, 450, 5, 3500 },
    { 100, 180, 600, 6, 1500 },
    { 0,   0,   0,   0, 0 }
};


bool SourceScript::GetForLED(Source::E source, uint _time)
{
    const SourceScript &script = scripts[source];

    int time = (int)(_time % script.PeriodPacket());            // ������� ��� �����

    for (int i = 0; i < script.num_pulses; i++)
    {
        if (time <= script.led_duration + 100 && time >= 100)
        {
            return true;
        }

        time -= script.period;
    }

    return false;
}


bool SourceScript::GetForVibro(Source::E source, uint _time)
{
    const SourceScript &script = scripts[source];

    int time = (int)(_time % script.PeriodPacket());            // ������� ��� �����

    for (int i = 0; i < script.num_pulses; i++)
    {
        if (time < script.vibro_duration + 100 && time >= 100)
        {
            return true;
        }

        time -= script.period;
    }

    return false;
}


uint SourceScript::PeriodPacket() const
{
    return (uint)period * (uint)num_pulses + (uint)pause_packet;
}


Source::E Source::Queue::buffer[Source::Count] = { Source::Count, Source::Count, Source::Count, Source::Count, Source::Count, Source::Count };
int Source::Queue::size = 0;

Source::Queue::Time Source::Queue::time_recv[Source::Count];

void Source::DrawIcon(int x, int y, const Color &color) const
{
    sourceIcons[value]->Draw(x, y, color);
}


static bool need_received[Source::Count] = { false, false, false, false, false, false };


pchar Source::Name(E v)
{
    static const pchar names[Count] =
    {
        "������� ������",
        "��������� �������",
        "�������� �������",
        "�������",
        "��������",
        "TECT"
    };

    return names[v];
}


void Source::Receive(E type)
{
    need_received[type] = true;
}


bool Source::ExistReceived()
{
    for (int i = 0; i < Count; i++)
    {
        if (need_received[i])
        {
            return true;
        }
    }

    return GetCountReceived() != 0;
}


bool Source::IsReceived(E type)
{
    return Queue::IsConsist(type);
}


void Source::Update()
{
    if (CMT2210AW::IsEnabled())
    {
        return;
    }

    for (int i = 0; i < Source::Count; i++)
    {
        if (need_received[i])
        {
            need_received[i] = false;

            // ����� ����������� ����� �������
            static uint time_prev_signal[Source::Count] = { 0, 0, 0, 0, 0, 0 };

            // �����, � ������� �������� �� ����� �������� ��������� �������
            static const uint time_pause[Source::Count] =
            {
                1000,
                10000,
                10000,
                10000,
                15000,
                10000
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


Source::E Source::Current()
{
    return Queue::At(0);
}
