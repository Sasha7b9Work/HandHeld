#include "defines.h"
#include "Player/Player.h"
#include "Player/Beeper.h"
#include "Player/Melodies/melody1.h"
#include "Player/Melodies/melody2.h"
#include "Player/Melodies/melody3.h"
#include <string.h>


namespace Player
{
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
}


void Player::Init()
{
    Beeper::Init();
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


// Single syntezer channel state  
typedef struct
{
    uint16    m_counter;      //square wave, sine or waveform generator counter

    uint16    m_counterAdd;   //0 - off, 1 - drum, >0 - add value for counter

    uint8     m_envelopeCounter;

} TChannelState;


// TCompressedStreamState
typedef struct
{
    const uint8 *m_pData;

    // number of bits still used in byte m_pData points to
    uint8                 m_bitsUsed;
} TCompressedStreamState;


// TPlayerState
typedef struct
{
    //noteNumber stream, 11 bits
    TCompressedStreamState              m_stream1;
    //pause stream, 13 bits
    TCompressedStreamState              m_stream2;

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
    TChannelState   m_channelState[HXMIDIPLAYER_CHANNELS_COUNT];
} TPlayerState;


// Player state
static TPlayerState s_playerState =
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


uint16 inline Player_GetNoteFreqAdd(uint8 _noteNumber)
{
    uint8 noteIndex;
    uint8 noteDiv;

    noteIndex = (uint8)(132 - 1 - _noteNumber);
    noteDiv = (uint8)(noteIndex / 12);                          //how many octaves down
    noteIndex = (uint8)(noteIndex - 12 * noteDiv);
    return (uint16)(s_noteFreqEx[noteIndex] >> noteDiv);
}


//advance stream by number of bits
static void Player_Advance(TCompressedStreamState *_state, uint16 _bitsCount)
{
    uint16 s = (uint16)(_state->m_bitsUsed + _bitsCount);

    _state->m_pData += s >> 3;
    _state->m_bitsUsed = (uint8)(s & 0x7);
}


static uint16 Player_ReadBits(TCompressedStreamState *_state, uint8 _bitsCount, uint16 _mask)
{
    //this procedure is optimized for _bitsCount 1..16
    //(value can be spread at most by 3 bytes)

    uint r = _state->m_pData[0];

    r <<= 8;
    r |= _state->m_pData[1];

    r <<= 8;
    r |= _state->m_pData[2];

    int8 s = (int8)(24 - _bitsCount - _state->m_bitsUsed);

    r >>= s;

    Player_Advance(_state, _bitsCount);

    return r & _mask;
}


// advance stream to actual data
static void Player_StartStream(TCompressedStreamState *_state, uint8 _numberOfBits)
{
    uint16 s;

    s = Player_ReadBits(_state, 5, 0x1f);
    Player_Advance(_state, (uint16)(16 + s * _numberOfBits));
}


static uint16 Player_Decompress(TCompressedStreamState *_state, const uint8 *_streamBase, uint8 _bitsCount, uint16 _mask)
{
    uint8 code = (uint8)Player_ReadBits(_state, 3, 0x7);

    switch (code)
    {
    case 0:
    case 1:
    case 2:
        //use code as immedate value
        break;

    case 3:
        code = (uint8)(3 + Player_ReadBits(_state, 1, 1));
        break;

    case 4:
        code = (uint8)(5 + Player_ReadBits(_state, 2, 3));
        break;

    case 5:
        code = (uint8)(9 + Player_ReadBits(_state, 3, 7));
        break;

    case 6:
        code = (uint8)(17 + Player_ReadBits(_state, 3, 7));
        break;

    case 7:
        return Player_ReadBits(_state, _bitsCount, _mask);
    }

    TCompressedStreamState state;
    state.m_pData = _streamBase;
    state.m_bitsUsed = 0;
    Player_Advance(&state, (uint16)(5 + 16 + ((uint16)code) * _bitsCount));
    return Player_ReadBits(&state, _bitsCount, _mask); //review: doen't need advance
}


void Player::ProcessEvents()
{
    uint8 channelIndex;
    uint8 noteNumber;
    uint16 delta;
    uint16 cadd;

    s_playerState.m_eventCounter = (uint16)0xffff;
    //    #asm("sei")

    delta = Player_Decompress(&s_playerState.m_stream1, s_playerState.m_stream1_start, 11, 0x7ff);
    noteNumber = (uint8)(delta & 0x7f);
    channelIndex = (uint8)(delta >> 7);

    delta = Player_Decompress(&s_playerState.m_stream2, s_playerState.m_stream2_start, 13, 0x1fff);

    if (delta == 0)
    {
        //        #asm("cli")
        s_playerState.m_stream1.m_pData = nullptr;
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

    s_playerState.m_channelState[channelIndex].m_counter = 0;
    s_playerState.m_channelState[channelIndex].m_counterAdd = cadd;

    s_playerState.m_channelState[channelIndex].m_envelopeCounter = 0;

    s_playerState.m_eventCounter = delta;
}


void Player::TimerFunc()
{
    uint8 sample;
    uint8 i;
    TChannelState *pState;

    if (s_playerState.m_stream1.m_pData == nullptr)
    {
        return;
    }

    //advance envelopeCounter    
    if (s_playerState.m_envelopeSkipCounter == 0)
    {
        s_playerState.m_envelopeSkipCounter = ENVELOPE_SKIP_MAX;

        for (i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
        {
            if (s_playerState.m_channelState[i].m_envelopeCounter < 255)
            {
                s_playerState.m_channelState[i].m_envelopeCounter++;
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
            pState->m_counter += pState->m_counterAdd;
            //sineVal is unsigned value, biased by 0x80 ( 0 -> 0x80 )
            sineVal = s_sineTable[(pState->m_counter >> (PLAYER_FREQ_SHR - 5)) & 63];
            //envelopeVal is volume value 0..255
            envelopeVal = s_envelope[pState->m_envelopeCounter >> 1];
            //scale sineVal as unsigned value using simple mul/shift. We divide by 256, not 255 for simplicity.
            sineVal = (uint8_t)((((uint16_t)sineVal) * envelopeVal) >> 8);
            //after scaling, 0x80 (biased zero ) became m_envelopeVal / 2
            //create unsigned value by biasing back    
            sineVal -= envelopeVal >> 1;
            sample += sineVal;
        }
        pState++;
    }

    Player::Output(sample);
}


void Player::StartMelody(const TMelody *_pMelody, uint16 _delay)
{
    Player::Stop();

    Started();

    memset(s_playerState.m_channelState, 0, sizeof(TChannelState) * HXMIDIPLAYER_CHANNELS_COUNT);

    s_playerState.m_eventCounter = (uint16)(1 + _delay);
    s_playerState.m_envelopeSkipCounter = 0;

    //    #asm("cli")

    s_playerState.m_stream1.m_pData = _pMelody->m_pStream1;
    s_playerState.m_stream2.m_pData = _pMelody->m_pStream2;
    s_playerState.m_stream1.m_bitsUsed = 0;
    s_playerState.m_stream2.m_bitsUsed = 0;

    s_playerState.m_stream1_start = _pMelody->m_pStream1;
    s_playerState.m_stream2_start = _pMelody->m_pStream2;

    Player_StartStream(&s_playerState.m_stream1, 11);
    Player_StartStream(&s_playerState.m_stream2, 13);

    //    #asm("sei")

    ///Set initial values for white noise generator
    //s_playerState.m_wngState.m_nze = 0;
    //s_playerState.m_wngState.m_t1 = 45;
    //s_playerState.m_wngState.m_t2 = 34;
    //s_playerState.m_wngState.m_t3 = 53;
}


bool Player::IsPlaying()
{
    return s_playerState.m_stream1.m_pData != nullptr;
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

        s_playerState.m_stream1.m_pData = nullptr;

//        #asm("sei")

        Finished();
    }
}
