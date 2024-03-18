#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "Player/PlayerConfig.h"


struct TypeMelody
{
    enum E
    {
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        Count
    };
};

struct Melody
{
    const uint8 *pStream1;
    const uint8 *pStream2;
};


namespace Player
{
    void Play(TypeMelody::E);

    void Init();

    // Is player currently playing ?
    bool IsPlaying();

    // Wait untill player finish playing
    // If not playing currently, returns immediatelly.
    void WaitFinish();

    // ���������� ��������������� � ������ ������ �������. �������� ����� Player_Finished() ����������, ���� ����
    // ����������������. ���� ������� �� ������ - ������ ��������� ������������.
    void Stop();

    // ������� ������� ������� ������ ���������� ������������� � ������������� �������� HXMIDIPLAYER_SAMPLING_RATE
    void CallbackOnTimer();
}
