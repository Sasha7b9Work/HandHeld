#include "defines.h"
#include <string.h>
#include "hxMidiPlayer.h"


// Called by player to output data to DAC/pwm
static void Player_Output(uint8_t /*sample*/)
{
}


// Called by player when player starts to play 
// ( from Player_StartMelody() )
// Can be used to configure timer/pwm
static void Player_Started()
{

}


// Called by player when melody is finished 
// ( from Player_TimerFunc(), interrupts disabled )
// Can be used to configure timer/pwm
static void Player_Finished()
{

}


// Single syntezer channel state  
typedef struct
{
#ifdef HXMIDIPLAYER_WAVEFORM_SAMPLE
    //can be 24 bit uint
    uint    m_counter;      //sample index counter
#else
    uint16    m_counter;      //square wave, sine or waveform generator counter
#endif
    uint16    m_counterAdd;   //0 - off, 1 - drum, >0 - add value for counter

#ifdef HXMIDIPLAYER_WAVEFORM_SINE_ENVELOPE
    uint8     m_envelopeCounter;
#endif    

} TChannelState;


#ifdef HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER
// WhiteNoiseGeneratorState
typedef struct
{
    uint8     m_nze;
    uint8     m_t1;
    uint8     m_t2;
    uint8     m_t3;
} WhiteNoiseGeneratorState;
#endif 


#ifdef HXMIDIPLAYER_USE_COMPRESSION
// TCompressedStreamState
typedef struct
{
    const uint8 *m_pData;

    // number of bits still used in byte m_pData points to
    uint8                 m_bitsUsed;
} TCompressedStreamState;
#endif


// TPlayerState
typedef struct
{
#ifdef HXMIDIPLAYER_USE_COMPRESSION
    //noteNumber stream, 11 bits
    TCompressedStreamState              m_stream1;
    //pause stream, 13 bits
    TCompressedStreamState              m_stream2;

    const uint8 *m_stream1_start;
    const uint8 *m_stream2_start;
#else
    // pointer to next event in melody        
    const flash TPlayerStateChange *m_pMelody;
#endif

#ifdef HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER
    WhiteNoiseGeneratorState            m_wngState;
#endif

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
#ifdef HXMIDIPLAYER_USE_COMPRESSION
        { nullptr, 0 },
        { nullptr, 0 },
        nullptr,
        nullptr,
#else
        nullptr,
#endif    
#ifdef HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER
        { 0, 45, 34, 53 }
#endif
        0,
        0,
        { { 0, 0, 0 },
          { 0, 0, 0 },
          { 0, 0, 0 },
          { 0, 0, 0 } }
};


#ifdef HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER
uint8 inline Player_GetWhiteNoise()
{
    uint8 b;
    uint8 b1;

    s_playerState.m_wngState.m_t1 = s_playerState.m_wngState.m_nze;
    s_playerState.m_wngState.m_t1 &= 66;

    if ((s_playerState.m_wngState.m_t1 != 0) && (s_playerState.m_wngState.m_t1 < 66))
    {
        b = 1;
    }
    else
    {
        b = 0;
    }

    b1 = s_playerState.m_wngState.m_t2 >> 7;
    s_playerState.m_wngState.m_t2 <<= 1;
    s_playerState.m_wngState.m_t2 |= b;
    b = s_playerState.m_wngState.m_t3 >> 7;
    s_playerState.m_wngState.m_t3 <<= 1;
    s_playerState.m_wngState.m_t3 |= b1;
    s_playerState.m_wngState.m_nze <<= 1;
    s_playerState.m_wngState.m_nze |= b;

    return s_playerState.m_wngState.m_nze;
}
#endif


uint16 inline Player_GetNoteFreqAdd(uint8 _noteNumber)
{
    uint8 noteIndex;
    uint8 noteDiv;

    noteIndex = (uint8)(132 - 1 - _noteNumber);
    noteDiv = (uint8)(noteIndex / 12);                          //how many octaves down
    noteIndex = (uint8)(noteIndex - 12 * noteDiv);
    return (uint16)(s_noteFreqEx[noteIndex] >> noteDiv);
}

#ifdef HXMIDIPLAYER_USE_COMPRESSION

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
#endif


void inline Player_ProcessEvents()
{
    uint8 channelIndex;
    uint8 noteNumber;
    uint16 delta;
    uint16 cadd;

    s_playerState.m_eventCounter = (uint16)0xffffffff;
//    #asm("sei")

#ifdef HXMIDIPLAYER_USE_COMPRESSION
        delta = Player_Decompress(&s_playerState.m_stream1, s_playerState.m_stream1_start, 11, 0x7ff);
    noteNumber = (uint8)(delta & 0x7f);
    channelIndex = (uint8)(delta >> 7);

    delta = Player_Decompress(&s_playerState.m_stream2, s_playerState.m_stream2_start, 13, 0x1fff);

    if (delta == 0)
    {
//        #asm("cli")
            s_playerState.m_stream1.m_pData = nullptr;
        Player_Finished();
        return;
    }

#else    
        delta = s_playerState.m_pMelody->m_delta;
    noteNumber = s_playerState.m_pMelody->m_noteNumber;

    channelIndex = delta & 0x7;
    delta >>= 3;

    if (delta == 0)
    {
        #asm("cli")
            s_playerState.m_pMelody = NULL;
        Player_Finished();
        return;
    }

    channelIndex |= (noteNumber >> (7 - 3)) & 8;

    noteNumber &= 0x7f;
#endif

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

#ifndef HXMIDIPLAYER_USE_COMPRESSION            
    s_playerState.m_pMelody++;
#endif    

    //mid delta is 1:
    //do not hold interrupt for a long time:
    //process next event on next tick event it should be processed immediatelly       
    //it wan't be noticable

//    #asm("cli")

        s_playerState.m_channelState[channelIndex].m_counter = 0;
    s_playerState.m_channelState[channelIndex].m_counterAdd = cadd;

#ifdef HXMIDIPLAYER_WAVEFORM_SINE_ENVELOPE
    s_playerState.m_channelState[channelIndex].m_envelopeCounter = 0;
#endif    

    s_playerState.m_eventCounter = delta;
}


void Player_TimerFunc()
{
    uint8 sample;
    uint8 i;
    TChannelState *pState;

#ifdef HXMIDIPLAYER_USE_COMPRESSION
    if (s_playerState.m_stream1.m_pData == nullptr)
    {
        return;
    }
#else
    if (s_playerState.m_pMelody == NULL)
    {
        return;
    }
#endif    

    //advance envelopeCounter    
    if (s_playerState.m_envelopeSkipCounter == 0)
    {
        s_playerState.m_envelopeSkipCounter = ENVELOPE_SKIP_MAX;

#ifdef HXMIDIPLAYER_WAVEFORM_SINE_ENVELOPE
        for (i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
        {
            if (s_playerState.m_channelState[i].m_envelopeCounter < 255)
            {
                s_playerState.m_channelState[i].m_envelopeCounter++;
            }
        }
#endif    
        s_playerState.m_eventCounter--;
        if (s_playerState.m_eventCounter == 0)
        {
            Player_ProcessEvents();
        }
    }
    s_playerState.m_envelopeSkipCounter--;

    //create sample

#ifdef HXMIDIPLAYER_WAVEFORM_SQUARE    
    sample = 0;
#else
    sample = 0x80;
#endif     

    pState = &s_playerState.m_channelState[0];

    for (i = 0; i < HXMIDIPLAYER_CHANNELS_COUNT; i++)
    {
#ifdef HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER    
        if (pState->m_counterAdd == 1)
        {

#ifdef HXMIDIPLAYER_WAVEFORM_SQUARE    
            sample += Player_GetWhiteNoise() & 1;
#else
            if ((Player_GetWhiteNoise() & 1) != 0)
            {
                sample += 127 / HXMIDIPLAYER_CHANNELS_COUNT / 4;
            }
#endif     

        }
        else
#endif //drums syntezer        
        {

#ifdef HXMIDIPLAYER_WAVEFORM_SQUARE    
            pState->m_counter += pState->m_counterAdd;
            sample += (pState->m_counter >> PLAYER_FREQ_SHR) & 1;
#endif

#ifdef HXMIDIPLAYER_WAVEFORM_SINE    
            pState->m_counter += pState->m_counterAdd;
            sample += s_sineTable[(pState->m_counter >> (PLAYER_FREQ_SHR - 5)) & 63];
#endif

#ifdef HXMIDIPLAYER_WAVEFORM_SINE_ENVELOPE    
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
#endif

#ifdef HXMIDIPLAYER_WAVEFORM_SAMPLE
            if (pState->m_counter < PLAYER_COUNTER_MAX_VAL)
            {
                pState->m_counter += pState->m_counterAdd;
            }
            sample += s_sample[pState->m_counter >> (PLAYER_FREQ_SHR - 3)];
#endif

        }
        pState++;
    }

    Player_Output(sample);
}


void Player_StartMelody(const TMelody *_pMelody, uint16 _delay)
{
    Player_Stop();

    Player_Started();

    memset(s_playerState.m_channelState, 0, sizeof(TChannelState) * HXMIDIPLAYER_CHANNELS_COUNT);

    s_playerState.m_eventCounter = (uint16)(1 + _delay);
    s_playerState.m_envelopeSkipCounter = 0;

//    #asm("cli")

#ifdef HXMIDIPLAYER_USE_COMPRESSION
        s_playerState.m_stream1.m_pData = _pMelody->m_pStream1;
    s_playerState.m_stream2.m_pData = _pMelody->m_pStream2;
    s_playerState.m_stream1.m_bitsUsed = 0;
    s_playerState.m_stream2.m_bitsUsed = 0;

    s_playerState.m_stream1_start = _pMelody->m_pStream1;
    s_playerState.m_stream2_start = _pMelody->m_pStream2;

    Player_StartStream(&s_playerState.m_stream1, 11);
    Player_StartStream(&s_playerState.m_stream2, 13);
#else
        s_playerState.m_pMelody = _pMelody->m_pEvents;
#endif 

//    #asm("sei")

        ///Set initial values for white noise generator
        //s_playerState.m_wngState.m_nze = 0;
        //s_playerState.m_wngState.m_t1 = 45;
        //s_playerState.m_wngState.m_t2 = 34;
        //s_playerState.m_wngState.m_t3 = 53;
}


bool Player_IsPlaying()
{
#ifdef HXMIDIPLAYER_USE_COMPRESSION
    return s_playerState.m_stream1.m_pData != nullptr;
#else
    return s_playerState.m_pMelody != NULL;
#endif    
}

// Wait untill player finishes playing
void Player_WaitFinish()
{
    while (Player_IsPlaying() == true)
        ;
}


void Player_Stop()
{
    if (Player_IsPlaying())
    {
//        #asm("cli")

#ifdef HXMIDIPLAYER_USE_COMPRESSION
            s_playerState.m_stream1.m_pData = nullptr;
#else          
            s_playerState.m_pMelody = NULL;
#endif        

//        #asm("sei")

            Player_Finished();
    }
}
