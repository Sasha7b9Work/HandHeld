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
#include <string.h>


namespace Player
{
    // Single syntezer channel state  
    struct ChannelState
    {
        uint16 counter;      //square wave, sine or waveform generator counter

        uint16 counterAdd;   //0 - off, 1 - drum, >0 - add value for counter

        uint8  envelopeCounter;
    };


    struct CompressedStreamState
    {
        const uint8 *pData;

        // number of bits still used in byte m_pData points to
        uint8        bitsUsed;
    };


    struct PlayerState
    {
        //noteNumber stream, 11 bits
        CompressedStreamState stream1;
        //pause stream, 13 bits
        CompressedStreamState stream2;

        const uint8 *m_stream1_start;
        const uint8 *m_stream2_start;

        // This value is decreased on every timer event.
        // Initially is writeln from m_delta value of StateChangeEvent.
        // When it reaches 0, it's time to process state change events.
        uint16          m_eventCounter;

        // 255Hz counter    
        // initally writeln ENVELOPE_SKIP_MAX
        // decreased every tick
        // when reaches 0, envelope index on all channels should increase
        uint8           m_envelopeSkipCounter;

        // Syntezer channels states
        ChannelState   m_channelState[HXMIDIPLAYER_CHANNELS_COUNT];
    };

    // Called by player to output data to DAC/pwm
    static void Output(uint8 /*sample*/);

    // Timer event function, should be called by user with fixed frequency HXMIDIPLAYER_SAMPLING_RATE
    void TimerFunc();

    // Start playing melody
    // Previously played melody is stoped, Player_Finished callback is called.
    // Player_Started() callback is called on start.
    // _delay - start delay in 255Hz ticks, max is 65534
    void StartMelody(const TMelody *_pMelody, uint16 _delay);

    bool IsPlaying();

    // Wait untill player finishes playing
    void WaitFinish();

    void Stop();

    // Called by player when player starts to play 
    // ( from Player_StartMelody() )
    // Can be used to configure timer/pwm
    static void Started();

    // Called by player when melody is finished 
    // ( from Player_TimerFunc(), interrupts disabled )
    // Can be used to configure timer/pwm
    static void Finished();

    static void ProcessEvents();

    //advance stream by number of bits
    static void Advance(CompressedStreamState *_state, uint16 _bitsCount);

    static uint16 ReadBits(CompressedStreamState *_state, uint8 _bitsCount, uint16 _mask);

    // advance stream to actual data
    static void StartStream(CompressedStreamState *_state, uint8 _numberOfBits);

    static uint16 Decompress(CompressedStreamState *_state, const uint8 *_streamBase, uint8 _bitsCount, uint16 _mask);

    // Player state
    static PlayerState s_playerState =
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
    static const TMelody *melodies[TypeMelody::Count] =
    {
        &s_melody1, &s_melody2, &s_melody3, &s_melody4, &s_melody5,
        &s_melody6, &s_melody7, &s_melody8, &s_melody9, &s_melody10,
    };

    StartMelody(melodies[type], 3 * 255);
}


void Player::Output(uint8 /*sample*/)
{
}


void Player::Started()
{

}


void Player::Finished()
{

}


uint16 inline Player_GetNoteFreqAdd(uint8 _noteNumber)
{
    uint8 noteIndex;
    uint8 noteDiv;

    noteIndex = (uint8)(132 - 1 - _noteNumber);
    noteDiv = (uint8)(noteIndex / 12);                          //how many octaves down
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
    //this procedure is optimized for _bitsCount 1..16
    //(value can be spread at most by 3 bytes)

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
    uint16 s;

    s = ReadBits(_state, 5, 0x1f);
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
    uint8 channelIndex;
    uint8 noteNumber;
    uint16 delta;
    uint16 cadd;

    s_playerState.m_eventCounter = (uint16)0xffff;
    //    #asm("sei")

    delta = Decompress(&s_playerState.stream1, s_playerState.m_stream1_start, 11, 0x7ff);
    noteNumber = (uint8)(delta & 0x7f);
    channelIndex = (uint8)(delta >> 7);

    delta = Decompress(&s_playerState.stream2, s_playerState.m_stream2_start, 13, 0x1fff);

    if (delta == 0)
    {
        //        #asm("cli")
        s_playerState.stream1.pData = nullptr;
        Finished();
        return;
    }

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

    //mid delta is 1:
    //do not hold interrupt for a long time:
    //process next event on next tick event it should be processed immediatelly       
    //it wan't be noticable

//    #asm("cli")

    s_playerState.m_channelState[channelIndex].counter = 0;
    s_playerState.m_channelState[channelIndex].counterAdd = cadd;

    s_playerState.m_channelState[channelIndex].envelopeCounter = 0;

    s_playerState.m_eventCounter = delta;
}


void Player::TimerFunc()
{
    uint8 sample;
    uint8 i;
    ChannelState *pState;

    if (s_playerState.stream1.pData == nullptr)
    {
        return;
    }

    //advance envelopeCounter    
    if (s_playerState.m_envelopeSkipCounter == 0)
    {
        s_playerState.m_envelopeSkipCounter = ENVELOPE_SKIP_MAX;

        for (i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
        {
            if (s_playerState.m_channelState[i].envelopeCounter < 255)
            {
                s_playerState.m_channelState[i].envelopeCounter++;
            }
        }

        s_playerState.m_eventCounter--;
        if (s_playerState.m_eventCounter == 0)
        {
            ProcessEvents();
        }
    }
    s_playerState.m_envelopeSkipCounter--;

    //create sample

    sample = 0x80;

    pState = &s_playerState.m_channelState[0];

    for (i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
    {
        {
            uint8 sineVal;
            uint8 envelopeVal;
            pState->counter += pState->counterAdd;
            //sineVal is unsigned value, biased by 0x80 ( 0 -> 0x80 )
            sineVal = s_sineTable[(pState->counter >> (PLAYER_FREQ_SHR - 5)) & 63];
            //envelopeVal is volume value 0..255
            envelopeVal = s_envelope[pState->envelopeCounter >> 1];
            //scale sineVal as unsigned value using simple mul/shift. We divide by 256, not 255 for simplicity.
            sineVal = (uint8_t)((((uint16_t)sineVal) * envelopeVal) >> 8);
            //after scaling, 0x80 (biased zero ) became m_envelopeVal / 2
            //create unsigned value by biasing back    
            sineVal -= envelopeVal >> 1;
            sample += sineVal;
        }
        pState++;
    }

    Output(sample);
}


void Player::StartMelody(const TMelody *_pMelody, uint16 _delay)
{
    Stop();

    Started();

    memset(s_playerState.m_channelState, 0, sizeof(ChannelState) * HXMIDIPLAYER_CHANNELS_COUNT);

    s_playerState.m_eventCounter = (uint16)(1 + _delay);
    s_playerState.m_envelopeSkipCounter = 0;

    //    #asm("cli")

    s_playerState.stream1.pData = _pMelody->m_pStream1;
    s_playerState.stream2.pData = _pMelody->m_pStream2;
    s_playerState.stream1.bitsUsed = 0;
    s_playerState.stream2.bitsUsed = 0;

    s_playerState.m_stream1_start = _pMelody->m_pStream1;
    s_playerState.m_stream2_start = _pMelody->m_pStream2;

    StartStream(&s_playerState.stream1, 11);
    StartStream(&s_playerState.stream2, 13);

    //    #asm("sei")

    ///Set initial values for white noise generator
    //s_playerState.m_wngState.m_nze = 0;
    //s_playerState.m_wngState.m_t1 = 45;
    //s_playerState.m_wngState.m_t2 = 34;
    //s_playerState.m_wngState.m_t3 = 53;
}


bool Player::IsPlaying()
{
    return s_playerState.stream1.pData != nullptr;
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
//        #asm("cli")

        s_playerState.stream1.pData = nullptr;

//        #asm("sei")

        Finished();
    }
}
