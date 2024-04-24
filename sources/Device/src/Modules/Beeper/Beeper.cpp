// 2024/03/18 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/Beeper/driverBeeper.h"
#include "Modules/Beeper/Beeper.h"
#include "Hardware/Timer.h"
#include <cmath>
#ifdef GUI
    #include "GUI/Controls/PainterMelody.h"
#endif


struct Note
{
    uint16 frequency;       // В герцах
    uint8  duration;        // В 100 мс
    uint8  velocity;        // 10 градаций - от 0 до 9
};


struct Sound
{
    const Note *const notes;        // В конце мелодии нулевые значения

    const bool native;              // Если true - ноты играются, как есть.
                                    // Если false - с преобразованием

    static void Start(TypeSound::E);

    static void Update();

private:

    static int num_note;
    static uint time_note_start;    // В миллисекундах
    static const Sound *current;

    static const Sound *sounds[TypeSound::Count];

    // Полное время звучания проигрываемой ноты
    static uint TimeNoteFull();

    // Столько нот в звуке
    static int NumberNotes();
};


#include "Modules/Beeper/Sounds/sound1.h"
#include "Modules/Beeper/Sounds/sound2.h"
#include "Modules/Beeper/Sounds/sound3.h"
#include "Modules/Beeper/Sounds/sound4.h"
#include "Modules/Beeper/Sounds/sound5.h"
#include "Modules/Beeper/Sounds/sound6.h"
#include "Modules/Beeper/Sounds/sound7.h"
#include "Modules/Beeper/Sounds/sound8.h"
#include "Modules/Beeper/Sounds/sound9.h"
#include "Modules/Beeper/Sounds/sound10.h"


const Sound *Sound::sounds[TypeSound::Count] =
{
    &sound1, &sound2, &sound3, &sound4, &sound5, &sound6, &sound7, &sound8, &sound9, &sound10
};


const Sound *Sound::current = nullptr;
int Sound::num_note = 0;
uint Sound::time_note_start = 0;


namespace Beeper
{
    static bool is_running = false;
    static bool need_running = false;
    static uint time_start = 0;       // В это время нужно запустить
    static TypeSound::E sound = TypeSound::Count;
    static uint8 volume = 0;
}


void Beeper::Init()
{
    Beeper::Driver::Init();
}


void Beeper::Play(TypeSound::E type, uint8 _volume)
{
#ifdef GUI

    PainterMelody::self->EnableMelody(type);

#endif

    is_running = true;

    need_running = true;

    time_start = TIME_MS + 100;

    sound = type;

    volume = _volume;
}


void Beeper::Update()
{
#ifdef GUI

    PainterMelody::self->Update();

#else

    if (need_running)
    {
        if (TIME_MS >= time_start)
        {
            Sound::Start(sound);

            need_running = false;
        }
    }

#endif
}


void Beeper::Stop()
{
    is_running = false;

    Beeper::Driver::Stop();
}


bool Beeper::IsRunning()
{
    return is_running;
}


void Sound::Start(TypeSound::E type)
{
    current = sounds[type];

    num_note = 0;

    time_note_start = TIME_MS;

    Beeper::Driver::StartFrequency((float)current->notes[0].frequency, Beeper::volume);
}


void Sound::Update()
{
    if (TIME_MS - time_note_start >= TimeNoteFull())
    {
        num_note++;

        if (num_note == NumberNotes())
        {
            Beeper::Stop();
        }
        else
        {
            Beeper::Driver::StartFrequency((float)current->notes[num_note].frequency, Beeper::volume);

            time_note_start = TIME_MS;
        }
    }
}


uint Sound::TimeNoteFull()
{
    return current->notes[num_note].duration * 100U;
}


int Sound::NumberNotes()
{
    for (int i = 0; ; i++)
    {
        if (current->notes[i].frequency == 0)
        {
            return i;
        }
    }
}


void Beeper::CallbackOnTimer()
{
    Sound::Update();
}
