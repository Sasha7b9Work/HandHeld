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
    static int num_note;
    static uint time_note_start;    // В миллисекундах
    static const Sound *current;

    static const Sound *sounds[TypeSound::Count];

    static void Start(TypeSound::E);

    static void Update();

    // Полное время звучания проигрываемой ноты
    static uint TimeNoteFull();

    // Столько нот в звуке
    static int NumberNotes();
};


#include "Modules/Beeper/Sounds/sound1.h"
#include "Modules/Beeper/Sounds/sound2.h"
#include "Modules/Beeper/Sounds/sound3.h"


const Sound *Sound::sounds[TypeSound::Count] =
{
    &sound1, &sound2, &sound3, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1
};


const Sound *Sound::current = nullptr;
int Sound::num_note = 0;
uint Sound::time_note_start = 0;


namespace Beeper
{
    static bool is_running = false;
}


void Beeper::Init()
{
    Beeper::Driver::Init();
}


void Beeper::Play(TypeSound::E type, uint8 /*volume*/)
{
#ifdef GUI

    PainterMelody::self->EnableMelody(type);

#endif

    is_running = true;

    Sound::Start(type);
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
    Timer::Delay(500);

    current = sounds[type];

    num_note = 0;

    time_note_start = TIME_MS;

    Beeper::Driver::StartFrequency((float)current->notes[0].frequency);
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
            Beeper::Driver::StartFrequency((float)current->notes[num_note].frequency);

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


void Beeper::Update()
{
    Beeper::Driver::Update();
}
