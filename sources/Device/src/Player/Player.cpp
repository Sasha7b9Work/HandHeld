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
    static int time_note;           // � �������������
    static const Sound *current;

    static const Sound *sounds[TypeSound::Count];

    static void Start(TypeSound::E);
};


#include "Player/Sounds/sound1.h"


const Sound *Sound::sounds[TypeSound::Count] =
{
    &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1, &sound1
};


const Sound *Sound::current = nullptr;


void Player::Init()
{
    Beeper::Init();
}


void Player::Play(TypeSound::E type)
{
    Sound::Start(type);
}


void Sound::Start(TypeSound::E type)
{
    current = sounds[type];
}


void Player::CallbackOnTimer()
{
}
