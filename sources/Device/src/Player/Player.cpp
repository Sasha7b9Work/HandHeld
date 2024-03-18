#include "defines.h"
#include "Player/Player.h"
#include "Player/Beeper.h"
#include "Player/Melodies/melody1.h"
#include "Player/Melodies/melody2.h"
#include "Player/Melodies/melody3.h"
#include "Player/Melodies/melody4.h"
#include "Player/Melodies/melody5.h"
#include "Player/Melodies/melody6.h"
#include "Player/Melodies/melody7.h"
#include "Player/Melodies/melody8.h"
#include "Player/Melodies/melody9.h"
#include "Player/Melodies/melody10.h"
#include "Hardware/Timer.h"
#include <string.h>


namespace Player
{
    // ��������� ������ ������ �����������
    struct ChannelState
    {
        uint16 counter;      // ������� ���������� �������������, �������������� ��� �������� ��������
        uint16 counterAdd;   // 0 � ����., 1 � �������, >0 � �������� �������� ��������.
        uint8  envelopeCounter;
    };


    struct CompressedStreamState
    {
        const uint8 *pData;
        uint8        bitsUsed;      // ���������� �����, ������� ��� ��� ������������ � �����, m_pData ��������� ��
    };


    struct PlayerState
    {
        // noteNumber stream, 11 bits
        CompressedStreamState stream1;
        // pause stream, 13 bits
        CompressedStreamState stream2;

        const uint8 *stream1_start;
        const uint8 *stream2_start;

        // ��� �������� ����������� ��� ������ ������� �������. ������������� ������������ �� �������� m_delta StateChangeEvent.
        // ����� ��� ��������� 0, ������ ����� ������������ ������� ��������� ���������.
        uint16       eventCounter;

        // ������� 255 �� ���������� ���������� ENVELOPE_SKIP_MAX, �������� ������ ����, ����� ��������� 0, ������ ���������
        // �� ���� ������� ������ �������������
        uint8        envelopeSkipCounter;

        // ��������� ������� �����������
        ChannelState channelState[HXMIDIPLAYER_CHANNELS_COUNT];
    };

    // ������ ��������������� �������. ����� ��������������� ������� ���������������, ���������� �������� ����� Player_Finished.
    // �������� ����� Player_Started() ���������� ��� �������. _delay - �������� ������� � �������� 255 ��, �������� 65534
    void StartMelody(const Melody *, uint16 _delay);

    bool IsPlaying();

    void Stop();

    static void ProcessEvents();

    // ���������� ����� ������ �� ���������� �����
    static void Advance(CompressedStreamState *, uint16 _bitsCount);

    static uint16 ReadBits(CompressedStreamState *, uint8 _bitsCount, uint16 _mask);

    // ���������� ����� � ����������� ������
    static void StartStream(CompressedStreamState *, uint8 _numberOfBits);

    static uint16 Decompress(CompressedStreamState *, const uint8 *_streamBase, uint8 _bitsCount, uint16 _mask);

    static PlayerState playerState =
    {
        { nullptr, 0 },
        { nullptr, 0 },
        nullptr,
        nullptr,
        0,
        0,
        {
          { 0, 0, 0 },
          { 0, 0, 0 },
          { 0, 0, 0 },
          { 0, 0, 0 }
        }
    };
}


void Player::Init()
{
    Beeper::Init();
}


void Player::Play(TypeMelody::E type)
{
    static const Melody *melodies[TypeMelody::Count] =
    {
        &melody1, &melody2, &melody3, &melody4, &melody5,
        &melody6, &melody7, &melody8, &melody9, &melody10,
    };

    StartMelody(melodies[type], 3 * 255);
}


uint16 inline Player_GetNoteFreqAdd(uint8 _noteNumber)
{
    uint8 noteIndex = (uint8)(132 - 1 - _noteNumber);
    uint8 noteDiv = (uint8)(noteIndex / 12);                          //how many octaves down
    noteIndex = (uint8)(noteIndex - 12 * noteDiv);
    return (uint16)(s_noteFreqEx[noteIndex] >> noteDiv);
}


void Player::Advance(CompressedStreamState *_state, uint16 _bitsCount)
{
    uint16 s = (uint16)(_state->bitsUsed + _bitsCount);

    _state->pData += s >> 3;
    _state->bitsUsed = (uint8)(s & 0x7);
}


uint16 Player::ReadBits(CompressedStreamState *_state, uint8 _bitsCount, uint16 _mask)
{
    // ��� ��������� �������������� ��� _bitsCount 1..16 (�������� ����� ���������������� �������� �� 3 �����)

    uint r = _state->pData[0];

    r <<= 8;
    r |= _state->pData[1];

    r <<= 8;
    r |= _state->pData[2];

    int8 s = (int8)(24 - _bitsCount - _state->bitsUsed);

    r >>= s;

    Advance(_state, _bitsCount);

    return r & _mask;
}


void Player::StartStream(CompressedStreamState *_state, uint8 _numberOfBits)
{
    uint16 s = ReadBits(_state, 5, 0x1f);
    Advance(_state, (uint16)(16 + s * _numberOfBits));
}


uint16 Player::Decompress(CompressedStreamState *_state, const uint8 *_streamBase, uint8 _bitsCount, uint16 _mask)
{
    uint8 code = (uint8)ReadBits(_state, 3, 0x7);

    switch (code)
    {
    case 0:
    case 1:
    case 2:
        //use code as immedate value
        break;

    case 3:
        code = (uint8)(3 + ReadBits(_state, 1, 1));
        break;

    case 4:
        code = (uint8)(5 + ReadBits(_state, 2, 3));
        break;

    case 5:
        code = (uint8)(9 + ReadBits(_state, 3, 7));
        break;

    case 6:
        code = (uint8)(17 + ReadBits(_state, 3, 7));
        break;

    case 7:
        return ReadBits(_state, _bitsCount, _mask);
    }

    CompressedStreamState state;
    state.pData = _streamBase;
    state.bitsUsed = 0;
    Advance(&state, (uint16)(5 + 16 + ((uint16)code) * _bitsCount));
    return ReadBits(&state, _bitsCount, _mask); //review: doen't need advance
}


void Player::ProcessEvents()
{
    playerState.eventCounter = (uint16)0xffff;

    uint16 delta = Decompress(&playerState.stream1, playerState.stream1_start, 11, 0x7ff);
    uint8 noteNumber = (uint8)(delta & 0x7f);
    uint8 channelIndex = (uint8)(delta >> 7);

    delta = Decompress(&playerState.stream2, playerState.stream2_start, 13, 0x1fff);

    if (delta == 0)
    {
        playerState.stream1.pData = nullptr;
        Beeper::CallbackOnStopMelody();
        return;
    }

    uint16 cadd = 0;

    if (noteNumber == 0)
    {
        cadd = 0;
    }
    else if (noteNumber == 1)
    {
        cadd = 1;
    }
    else
    {
        cadd = Player_GetNoteFreqAdd(noteNumber);
    }

    // ������� ������ ����� 1: �� ���������� ���������� � ������� ����������� �������: ������������ ��������� ������� ���
    // ��������� ������� �������, ��� ������ ���� ���������� ����������, ��� �� ����� �������
    playerState.channelState[channelIndex].counter = 0;
    playerState.channelState[channelIndex].counterAdd = cadd;

    playerState.channelState[channelIndex].envelopeCounter = 0;

    playerState.eventCounter = delta;
}


void Player::CallbackOnTimer()
{
    if (playerState.stream1.pData == nullptr)
    {
        return;
    }

    TimeMeterUS meter;

    // advance envelopeCounter
    if (playerState.envelopeSkipCounter == 0)
    {
        playerState.envelopeSkipCounter = ENVELOPE_SKIP_MAX;

        for (uint8 i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
        {
            if (playerState.channelState[i].envelopeCounter < 255)
            {
                playerState.channelState[i].envelopeCounter++;
            }
        }

        playerState.eventCounter--;

        if (playerState.eventCounter == 0)
        {
            ProcessEvents();
        }
    }

    playerState.envelopeSkipCounter--;

    // create sample

    uint8 sample = 0x80;

    ChannelState *pState = &playerState.channelState[0];

    for (uint8 i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
    {
        pState->counter += pState->counterAdd;
        //sineVal is unsigned value, biased by 0x80 ( 0 -> 0x80 )
        uint8 sineVal = s_sineTable[(pState->counter >> (PLAYER_FREQ_SHR - 5)) & 63];
        //envelopeVal is volume value 0..255
        uint8 envelopeVal = s_envelope[pState->envelopeCounter >> 1];
        //scale sineVal as unsigned value using simple mul/shift. We divide by 256, not 255 for simplicity.
        sineVal = (uint8_t)((((uint16_t)sineVal) * envelopeVal) >> 8);
        //after scaling, 0x80 (biased zero ) became m_envelopeVal / 2
        //create unsigned value by biasing back    
        sineVal -= envelopeVal >> 1;
        sample += sineVal;
        pState++;
    }

    Beeper::CallbackOnOutputSample(sample);

    uint time = meter.ElapsedUS();

    static uint max_time = 0;

    if (time > max_time)
    {
        max_time = time;
    }
}


void Player::StartMelody(const Melody *_pMelody, uint16 _delay)
{
    Stop();

    Beeper::CallbackOnStartMelody();

    memset(playerState.channelState, 0, sizeof(ChannelState) * HXMIDIPLAYER_CHANNELS_COUNT);

    playerState.eventCounter = (uint16)(1 + _delay);
    playerState.envelopeSkipCounter = 0;

    playerState.stream1.pData = _pMelody->pStream1;
    playerState.stream2.pData = _pMelody->pStream2;
    playerState.stream1.bitsUsed = 0;
    playerState.stream2.bitsUsed = 0;

    playerState.stream1_start = _pMelody->pStream1;
    playerState.stream2_start = _pMelody->pStream2;

    StartStream(&playerState.stream1, 11);
    StartStream(&playerState.stream2, 13);
}


bool Player::IsPlaying()
{
    return playerState.stream1.pData != nullptr;
}


void Player::WaitFinish()
{
    while (IsPlaying() == true)
    {
    }
}


void Player::Stop()
{
    if (IsPlaying())
    {
        playerState.stream1.pData = nullptr;

        Beeper::CallbackOnStopMelody();
    }
}
