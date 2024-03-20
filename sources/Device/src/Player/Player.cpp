// 2024/03/18 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Player/Player.h"
#include "Player/Beeper.h"
#include "Hardware/Timer.h"
#include <cmath>


struct Note
{
    uint16 frequency;       // � ������
    uint8  duration;        // � 100 ��
    uint8  velocity;        // 10 �������� - �� 0 �� 9
};


struct Sound
{
    const Note *const notes;        // � ����� ������� ������� ��������
    static int num_note;
    static uint time_note_start;    // � �������������
    static const Sound *current;

    static const Sound *sounds[TypeSound::Count];

    static void Start(TypeSound::E);

    static void Update();

    // ������ ����� �������� ������������� ����
    static uint TimeNoteFull();

    // ������� ��� � �����
    static int NumberNotes();
};


#include "Player/Sounds/sound1.h"
#include "Player/Sounds/sound2.h"
#include "Player/Sounds/sound3.h"


const Sound *Sound::sounds[TypeSound::Count] =
{
    &sound1, &sound2, &sound3, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1
};


const Sound *Sound::current = nullptr;
int Sound::num_note = 0;
uint Sound::time_note_start = 0;


void Player::Init()
{
    Beeper::Init();
}


void Player::Play(TypeSound::E type, uint8 /*volume*/)
{
    Sound::Start(type);
}


void Sound::Start(TypeSound::E type)
{
    current = sounds[type];

    num_note = 0;

    time_note_start = TIME_MS;

    Beeper::StartFrequency((float)current->notes[0].frequency);
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
            Beeper::StartFrequency((float)current->notes[num_note].frequency);

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


void Player::CallbackOnTimer()
{
    Sound::Update();
}
