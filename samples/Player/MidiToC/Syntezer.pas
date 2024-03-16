unit Syntezer;

interface
uses Classes, Windows, MidiFile, WhiteNoiseGenerator, SysUtils, SequenceMember,
 SyntezerChannelStateChange,  Math, Samples;

//==============================================================================
//==============================================================================
type EWAVEFORMKIND = (
  EWK_SQUARE,
  EWK_SINE,
  EWK_SINE_ENVELOPE,
  EWK_WAVEFORM1,
  EWK_WAVEFORM1_ENVELOPE,
  EWK_WAVEFORM2,
  EWK_WAVEFORM2_ENVELOPE,
  EWK_WAVEFORM3,
  EWK_WAVEFORM3_ENVELOPE,
  EWK_SAMPLE
  );

//==============================================================================
//==============================================================================
type TSyntezerChannelState = record

    ///note assigned to channel
    m_note        : PMidiEvent;

    ///instument of assigned note
    m_instrument  : BYTE;

    ///midi channel
    m_midichannel : BYTE;

    ///note start time
    m_start       : DWORD;

    //used in merge "stereo notes" mode
    m_refCount    : BYTE;
  end;

//==============================================================================
//==============================================================================
type TSyntezerChannelStateSmall = record

    // 0 - off
    m_noteNumber: BYTE;

    ///start time of note
    m_start : DWORD;
  end;

//==============================================================================
//==============================================================================
type TSyntezerChannelStateRt = record

    m_counter : WORD;
    m_counter2 : DWORD; //3-byte counter
    m_envelopeCounter: BYTE;

    m_counterAdd : WORD;
  end;



//==============================================================================
//==============================================================================
type EINSTRUMENTKIND = ( EIK_DISABLED, EIK_SYNTHWAVE, EIK_WHITENOISE );

//==============================================================================
//==============================================================================
type TSyntezerInstrumentPreset = record

    ///instrument kind
    m_eInstrumentKind : EINSTRUMENTKIND;

    ///max note duration
    m_noteDuration : integer;

  end;


//==============================================================================
//==============================================================================
type TSyntezer = class
    public

      constructor Create(
                          _midiFile : TMidiFile;
                          _channelsCount : integer;
                          _eWaveformKind : EWAVEFORMKIND;
                          _iPitch : integer; //-20..20
                          _bAllowSingleNotPerChannel : Boolean;
                          _bSuppresStereoNotes : Boolean;
                          _bForceSingleDrumChannel : Boolean;
                          _midiChannelEnabled : WORD;
                          _bEnableDrums : Boolean;
                          _instrumentPresets : array of TSyntezerInstrumentPreset;
                          _drumPresets : array of TSyntezerInstrumentPreset
                        );

      destructor Destroy();

      ///Melody length in ms
      function GetMelodyLength() : DWORD;

      ///Return Max number of active syntezer channels seeen while playing
      function GetMaxActiveChannels(): DWORD;

      ///Return Max number of active syntezer drum channels seeen while playing
      function GetMaxActiveDrumChannels(): DWORD;

      ///Return Max number of active syntezer drum channels seeen while playing
      function GetMaxActiveStereoNotes(): DWORD;

      ///Not enought channels to play melody ?
      function GetNotEnoughtChannels() : boolean;

      ///bit 1 - channel present in file
      function GetMidiChannelPresent() : WORD;

      ///
      function GetInstrumentUsed( _instrumentNumber: BYTE ) : Boolean;

      function GetDrumUsed( _drumNumber : BYTE ) : Boolean;

      ///Create sound sample
      procedure CreateSample(
                                  _startTime_ms: DWORD;
                                  _length_sec : DWORD;
                                  _freq : DWORD;
                                  _soundBuffer: PBYTE
                            );

      ///Create sound sample
      procedure CreateSampleRt(
                                  _startTime_ms: DWORD;
                                  _length_sec : DWORD;
                                  _freq : DWORD;
                                  _soundBuffer: PBYTE
                              );

      procedure CreateMelodyCode(
                                startPosition, endPosition : integer ;
                                _freq: DWORD;
                                _bUseCompression : Boolean;
                                _bCalculateCodeSizeOnly : boolean;
                                var code: String;
                                var codeSize : integer
                                );

      procedure CreatePlayerConfig(
                                _freq : DWORD;
                                _bUseCompression : Boolean
                                );

      procedure CreateRTFreqTable(
            _freq : DWORD;
            var nf : array of WORD;
            var _iFreqShr : DWORD;
            var _maxCounter2Val : DWORD
        );

    private

      ///reference to midi file
      m_midiFile : TMidifile;

      ///number of syntezer channels
      m_channelsCount : integer;

      ///Max number of active syntezer channels seeen while playing
      m_maxActiveChannelsCount : DWORD;

      ///Waveform kind
      m_eWaveformKind : EWAVEFORMKIND;

      ///Max number of active drum syntezer channels seeen while playing
      m_maxActiveDrumChannelsCount : DWORD;

      ///Max number of active stereo notes
      m_maxActiveStereoNotesCount : DWORD;

      ///melody length in ms
      m_melodyLength : DWORD;

      m_bSuppressStereoNotes : boolean;
      m_bForceSingleDrumChannel : boolean;

      //syntezer event to play melody
      m_syntezerEvents : TList;

      m_bNotEnoughtChannels : boolean;

      ///instance of white noise generator
      m_wng : TWhiteNoiseGenerator;

      ///bit is 1 - midi channel is present in file
      m_midiChannelPresent: WORD;

      ///bit is 1 - enable midi channel
      m_midiChannelEnabled: WORD;

      //enable drums syntezer
      m_bEnableDrums : Boolean;

      ///allow only one active note per midi channel\
      m_bAllowSingleNotPerChannel : Boolean;

      //instrument used ?
      m_bInstrumentUsed : array[0..127] of boolean;

      //drum used (midi channel 10 )
      m_bDrumUsed : array[0..127] of boolean;

      m_instrumentPresets : array [0..127] of TSyntezerInstrumentPreset;
      m_drumPresets : array [0..127] of TSyntezerInstrumentPreset;

      ///sample envelope table
      m_envelopeTable : array [0..127] of integer;

      m_iPitch : integer;

      function GetNoteFreq( _noteNumber: integer ): single;
      function GetNoteFreqAdd( _noteNumber: integer; _noteFreqEx : array of WORD ): WORD;

      procedure ProcessMelody();

      procedure AddSyntezerStateChange(
                                _start : DWORD;
                                _channelIndex : BYTE;
                                _noteNumber : BYTE;
                                _bSort: Boolean
                                );

      procedure StopNote(
                                _event : PMidiEvent;
                                _noteStartTime : DWORD;  //can e MAXDWORD if not available
                                _eventTime : DWORD;
                                var _channelState : array of TSyntezerChannelState;
                                _bSort: Boolean
                              );

      procedure StartNote(
                                _event : PMidiEvent;
                                _eventTime : DWORD;
                                var _channelState : array of TSyntezerChannelState;
                                var _midiChannelInstruments : array of byte
                              );

      procedure UpdateMaxActiveChannelsCount(
              var _channelState : array of TSyntezerChannelState;
              var _midiChannelInstruments : array of byte
            );

      function IsDrum( _ev : PMidiEvent; var _midiChannelInstruments : array of byte ) : Boolean;

      function IsMidiChannelEnabled( _index : integer ) : Boolean;

      procedure FilterZeroLengthNotes( _syntezerEvents : TList );

      procedure CreateSineTable( amplitude: integer; var sineTable : array of integer );

      procedure InitEnvelopeTable();

      function GetEnvelopeCCode( _freq : integer ) : String;

      function Get255HzCounterCode( _freq : integer ) : String;

      function GetSineTableCCode( _bSigned : Boolean ) : String;

      function GetNoteFreqExTableCCode( _freq : DWORD ) : String;
  end;

implementation
uses WavFile, MidiEventsEnumerator, FileCtrl, Clipbrd, Compressor, SequenceMaker,
 TypInfo;

 //suppress note if same note is started less then 100 ms later
 const STEREO_NOTE_SUPPRESS_PERIOD : DWORD = 100;

//==============================================================================
//==============================================================================
//http://www.indiana.edu/~emusic/hertz.htm
//We intentionally use one octave up frequency. This way  syntezer sounds better.
function TSyntezer.GetNoteFreq( _noteNumber: integer ): single;
const
  noteFreq : array [ 0.. 11 ] of integer =
      ( 31609, 29835, 28160, 26580, 25088, 23680, 22351, 21096, 19912, 18795, 17740, 16744 );

var
  noteIndex : integer;
  noteDiv : integer;
begin
  noteIndex := 132 - 1 - _noteNumber;
  noteDiv :=   noteIndex div 12;  //how many octaves down
  noteIndex := noteIndex - 12 * noteDiv;
  noteDiv := 1 shl noteDiv;

  result := noteFreq[noteIndex] / noteDiv;
end;

//==============================================================================
//==============================================================================
//Simplified divide by 12 routine
//_value = 0..96+48+24+12
function DivideBy12( _value : BYTE ) : BYTE;
var
  d : Byte;
  label l1;
begin
  result := 0;
  d := 96;

  l1:

  result := result shl 1;
  if ( _value >= d ) then
    begin
      _value := _value - d;
      result := result or 1;
    end;
  d := d shr 1;
  if ( d>=12) then goto l1;

end;

//==============================================================================
//==============================================================================
function TSyntezer.GetNoteFreqAdd( _noteNumber: integer; _noteFreqEx : array of WORD ) : WORD;
var
  noteIndex : integer;
  noteDiv : integer;
begin
  noteIndex := 132 - 1 - _noteNumber;
  noteDiv :=   DivideBy12( noteIndex );  //how many octaves down
  noteIndex := noteIndex - ( noteDiv * 8 + noteDiv * 4 );

  result := _noteFreqEx[noteIndex];
  result := result shr noteDiv;
end;

//==============================================================================
//==============================================================================
constructor TSyntezer.Create(
                                _midiFile : TMidiFile;
                                _channelsCount : integer;
                                _eWaveformKind : EWAVEFORMKIND;
                                _iPitch : integer;
                                _bAllowSingleNotPerChannel : Boolean;
                                _bSuppresStereoNotes : Boolean;
                                _bForceSingleDrumChannel : Boolean;
                                _midiChannelEnabled : WORD;
                                _bEnableDrums : Boolean;
                                _instrumentPresets : array of TSyntezerInstrumentPreset;
                                _drumPresets : array of TSyntezerInstrumentPreset
                              );
var
  i : integer;
begin
  m_midiFile := _midiFile;
  m_channelsCount := _channelsCount;
  m_eWaveformKind := _eWaveformKind;
  m_bAllowSingleNotPerChannel := _bAllowSingleNotPerChannel;
  m_bSuppressStereoNotes := _bSuppresStereoNotes;
  m_bForceSingleDrumChannel := _bForceSingleDrumChannel;
  m_midiChannelEnabled := _midiChannelEnabled;
  m_bEnableDrums := _bEnableDrums;
  m_iPitch := _iPitch;

  m_wng := TWhiteNoiseGenerator.Create();

  for i := 0 to 127 do
    begin
      m_instrumentPresets[ i ] := _instrumentPresets[ i ];
      m_drumPresets[ i ] := _drumPresets[ i ];
    end;

  ProcessMelody();
  InitEnvelopeTable();
end;

//==============================================================================
//==============================================================================
destructor TSyntezer.Destroy();
var
  i : integer;
begin
  m_wng.Destroy();

  for i:=0 to m_syntezerEvents.Count-1 do
    begin
      Dispose( m_syntezerEvents[ i ] );
    end;
end;

//==============================================================================
//==============================================================================
procedure TSyntezer.CreateSample(
                                  _startTime_ms: DWORD;
                                  _length_sec : DWORD;
                                  _freq : DWORD;
                                  _soundBuffer: PBYTE
                              );
var
  channelState : array of TSyntezerChannelStateSmall;

  i : integer;

  ev : TSyntezerChannelStateChange;

  curSample : DWORD;
  curTime : single;
  samplesCount : DWORD;

  eventIndex : DWORD;

  f: single;
  noteFreq : single;
  amplitude : single;

  timePassed: single;

  procedure ProcessEvents( _time : DWORD );
  begin
    while (
            ( eventIndex < m_syntezerEvents.Count ) and
            ( TSyntezerChannelStateChange( m_syntezerEvents[ eventIndex  ] ).m_start <= _time )
          ) do
      begin
        ev := TSyntezerChannelStateChange( m_syntezerEvents[ eventIndex  ] );
        channelState[ ev.m_channelIndex ].m_start := ev.m_start;
        channelState[ ev.m_channelIndex ].m_noteNumber := ev.m_noteNumber;
        inc( eventIndex );
      end;
  end;

begin

  SetLength( channelState, m_channelsCount );
  for i := 0 to m_channelsCount-1 do
    begin
      channelState[0].m_noteNumber := 0;
    end;

  //process all events untill startTime

  eventIndex := 0;

  ProcessEvents( _startTime_ms );

  samplesCount := _length_sec * _freq;

  curSample := 0;

  while ( samplesCount > 0 ) do
    begin
      curTime := _startTime_ms + curSample * 1000/_freq;

      ProcessEvents( Round( curTime ) );

      //create sample

      f := 0;

      for i := 0 to m_channelsCount - 1 do
        if channelState[ i ].m_noteNumber <> 0 then
          begin

            timePassed := curTime - channelState[i].m_start;

            if ( channelState[ i ].m_noteNumber > 1 ) then
              begin
                noteFreq := GetnoteFreq( channelState[i].m_noteNumber );

                amplitude :=
                    (
                      sin(
                            timePassed / 1000 * 3.1415 * noteFreq
                          )
                      + 1)*0.5;

                if amplitude > 0.5 then amplitude := 1 else amplitude := 0;
              end
            else
              begin
                amplitude := ( m_wng.GetValue() and 1 );
              end;

            f := f + amplitude;
          end;

      if ( m_maxActiveChannelsCount > 0 ) then
        begin
          f := f / m_maxActiveChannelsCount;
        end;

      _soundBuffer^ := round(f * 255);

      inc( curSample );
      inc( DWORD( _soundBuffer ) );
      dec( samplesCount );
    end;
end;


//==============================================================================
//==============================================================================
procedure TSyntezer.CreateSampleRt(
                                  _startTime_ms: DWORD;
                                  _length_sec : DWORD;
                                  _freq : DWORD;
                                  _soundBuffer: PBYTE
                              );
var
  channelState : array of TSyntezerChannelStateRt;

  i,j : integer;

  ev : TSyntezerChannelStateChange;

  curSample : DWORD;
  curTime : single;
  samplesCount : DWORD;

  eventIndex : DWORD;

  v : BYTE;
  noteFreq : single;
  amplitude : single;
  maxChannelAmplitude: integer;

  timePassed: single;

  iFreqShr : DWORD;
  noteFreqEx : array [ 0..11 ] of WORD;

  sineTable : array [ 0..63 ] of integer;

  envelopeSkipCounter : BYTE;
  envelopeSkipMax : BYTE;

  //max value of counter2. Should count up to [piano] sample length
  maxCounter2Val : DWORD;



  procedure ProcessEvents( _time : DWORD );
  begin
    while (
            ( eventIndex < m_syntezerEvents.Count ) and
            ( TSyntezerChannelStateChange( m_syntezerEvents[ eventIndex  ] ).m_start <= _time )
          ) do
      begin
        ev := TSyntezerChannelStateChange( m_syntezerEvents[ eventIndex  ] );
        channelState[ ev.m_channelIndex ].m_counter := 0;
        channelState[ ev.m_channelIndex ].m_counter2 := 0;
        channelState[ ev.m_channelIndex ].m_envelopeCounter := 0;
        if ( ev.m_noteNumber = 0 ) then
          begin
            channelState[ ev.m_channelIndex ].m_counterAdd := 0;
          end
        else if ( ev.m_noteNumber = 1 ) then
          begin
            channelState[ ev.m_channelIndex ].m_counterAdd := 1;
          end
        else
          begin
            channelState[ ev.m_channelIndex ].m_counterAdd := GetNoteFreqAdd( ev.m_noteNumber, noteFreqEx );
          end;

        inc( eventIndex );
      end;
  end;

begin

//loadSample();


  CreateRTFreqTable( _freq, noteFreqEx, iFreqShr, maxCounter2Val );

  if ( m_maxActiveChannelsCount > 0 ) then
    begin
      maxChannelAmplitude := 127 div m_maxActiveChannelsCount;
    end
      else
    begin
      maxChannelAmplitude := 0;
    end;

  CreateSineTable( maxChannelAmplitude, sineTable );

  SetLength( channelState, m_channelsCount );
  for i := 0 to m_channelsCount-1 do
    begin
      channelState[0].m_counter := 0;
      channelState[0].m_counter2 := 0;
      channelState[0].m_counterAdd := 0;
      channelState[0].m_envelopeCounter := 0;
    end;

  //process all events untill startTime

  eventIndex := 0;

  ProcessEvents( _startTime_ms );

  samplesCount := _length_sec * _freq;

  //enveloperCounter should encrease 0..255 during 1 second
  envelopeSkipMax := _freq  div  255;
  envelopeskipCounter := 0;

  curSample := 0;

  while ( samplesCount > 0 ) do
    begin
      curTime := _startTime_ms + curSample * 1000.0/_freq;

      ProcessEvents( Round( curTime ) );

      if ( envelopeSkipcounter = 0 ) then
      begin
        for i := 0 to m_channelsCount - 1 do
          begin
            //Note: note will be disabled before envelopecounter overflow
            //on active channels. Can ignore overflow in player.
            if ( channelState[ i ].m_envelopeCounter < 255 ) then
              begin
                inc( channelState[ i ].m_envelopeCounter );
              end
          end;

        envelopeSkipcounter := envelopeSkipMax;
      end;

      dec( envelopeSkipcounter );

      //create sample

      if ( m_eWaveformKind = EWK_SQUARE ) then
        begin
          v := 0;
        end
          else
        begin
          v := 128;
        end;

      for i := 0 to m_channelsCount - 1 do
        begin
          if ( channelState[i].m_counterAdd = 1 ) then
          begin
            //white noise
            if ( m_eWaveformKind = EWK_SQUARE ) then
              begin
                v := v + ( m_wng.GetValue() and 1 ) * maxChannelAmplitude * 2;
              end
                else
              begin
                v := v + (( m_wng.GetValue() and 1 ) * maxChannelAmplitude shr 2 );
              end;
          end
            else
          begin

            channelState[i].m_counter := channelState[i].m_counter + channelState[i].m_counterAdd;

            channelState[i].m_counter2 := channelState[i].m_counter2 + channelState[i].m_counterAdd;
            if ( channelState[i].m_counter2 > maxCounter2Val ) then
            begin
              channelState[i].m_counter2 := maxCounter2Val;
            end;

            case  m_eWaveformKind of
              EWK_SQUARE:
                begin
                  v := v + (( channelState[i].m_counter shr iFreqShr ) and 1) * maxChannelAmplitude * 2;
                end;

              EWK_SINE,
              EWK_WAVEFORM1,
              EWK_WAVEFORM2,
              EWK_WAVEFORM3:
                begin
                  v := v + sineTable[ (( channelState[i].m_counter shr ( iFreqShr - 5 ) ) and 63) ];
                end;

              EWK_SINE_ENVELOPE,
              EWK_WAVEFORM1_ENVELOPE,
              EWK_WAVEFORM2_ENVELOPE,
              EWK_WAVEFORM3_ENVELOPE:
                begin
                  //sine+envelope
                  j:= channelState[ i ].m_envelopeCounter shr 1;
                  j := m_envelopeTable[ j ];
                  v := v + sineTable[ (( channelState[i].m_counter shr ( iFreqShr - 5 ) ) and 63) ] * j div 255;
                end;

              EWK_SAMPLE:
                begin
                  j := (channelState[i].m_counter2 shr ( iFreqShr - 3 ) );
                  //if ( j > piano1_wav_size ) then j := piano1_wav_size;
                  v := v + ( (integer(sample_data[ j ]) - 128) * maxChannelAmplitude div  127  );
                end;
            end;

          end;

        end;

      if ( m_maxActiveChannelsCount > 0 ) then
        begin
          _soundBuffer^ := v;
        end
      else
        begin
          _soundBuffer^ := 0;
        end;


      inc( curSample );
      inc( DWORD( _soundBuffer ) );
      dec( samplesCount );
    end;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetMelodyLength() : DWORD;
begin
  result := m_melodyLength;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetMaxActiveChannels(): DWORD;
begin
  result := m_maxActiveChannelsCount;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetMaxActiveDrumChannels(): DWORD;
begin
  result := m_maxActiveDrumChannelsCount;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetMaxActiveStereoNotes(): DWORD;
begin
  result := m_maxActiveStereoNotesCount;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetNotEnoughtChannels() : boolean;
begin
  result := m_bNotEnoughtChannels;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetMidiChannelPresent() : WORD;
begin
  result := m_midiChannelPresent;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetInstrumentUsed( _instrumentNumber: BYTE ) : Boolean;
begin
  result := m_bInstrumentUsed[ _instrumentNumber ];
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetDrumUsed( _drumNumber : BYTE ) : Boolean;
begin
  result := m_bDrumUsed[ _drumNumber ];
end;


//==============================================================================
//==============================================================================
procedure TSyntezer.ProcessMelody();
var
  enumerator : TMidiEventsEnumerator;

  i : integer;

  maxDuration : integer;

  ///Syntezer channel state
  channelState     : array of TSyntezerChannelState;

  ///current instrument of each midi channel
  midiChannelInstruments : array [0..15] of BYTE;

  ev: PMidiEvent;
  evtime : DWORD;

begin
  SetLength( channelState, m_channelsCount );
  for i := 0 to m_channelsCount - 1 do
    begin
      channelState[ i ].m_note := nil;
    end;

  for i := 0 to 15 do
    begin
      midiChannelInstruments[ i ]:=0;
    end;

  m_bNotEnoughtChannels := false;

  m_maxActiveChannelsCount := 0;
  m_maxActiveDrumChannelsCount := 0;
  m_maxActiveStereoNotesCount := 0;
  m_midiChannelPresent := 0;

  m_melodyLength := 0;

  for i := 0 to 127 do
    begin
      m_bInstrumentUsed[ i ] := false;
      m_bDrumUsed[ i ] := false;
    end;

  m_syntezerEvents := TList.Create();

  enumerator := TMidiEventsEnumerator.Create( m_midiFile );

  //------ test enumerator ------------

  ev := nil;
  evTime := 0;

  while ( true ) do
    begin

      if ( enumerator.GetEvent() = nil ) then
      begin
        break;
      end;

      if ( ev <> nil ) then
        begin
          if ( ev.iPositon > enumerator.GetEvent().iPositon ) then
          begin
            MessageBeep(0);
          end;

        if ( evTime > enumerator.GetEventTime() ) then
          begin
            MessageBeep(0);
          end;

        end;

      ev := enumerator.GetEvent();
      evTime := enumerator.GetEventTime();

      enumerator.MoveToNext();
    end;

  enumerator.Destroy();
  enumerator := TMidiEventsEnumerator.Create( m_midiFile );

  //-------------------------------

  while ( true ) do
  begin

    if ( enumerator.GetEvent() = nil ) then
    begin
      break;
    end;

    //stop active notes on channels according to instrument max note length

    for i := 0 to m_channelsCount - 1 do
      if  ( channelState[ i ].m_note <> nil ) then
        begin
          if ( channelState[ i ].m_midichannel = 9 ) then
            begin
              maxDuration := m_drumPresets[ channelState[ i ].m_note.iData1 and $7f ].m_noteDuration;
            end
          else
            begin
              if ( m_eWaveformKind = EWK_SINE_ENVELOPE ) or
                  ( m_eWaveformKind = EWK_WAVEFORM1_ENVELOPE ) or
                  ( m_eWaveformKind = EWK_WAVEFORM2_ENVELOPE ) or
                  ( m_eWaveformKind = EWK_WAVEFORM3_ENVELOPE ) then
                begin
                  //envelope fades out sound in 1 second
                    maxDuration := 1000;
                end
              else if ( m_eWaveformKind = EWK_SAMPLE ) then
                begin
                  //note duration of sample depends on sample size and note frequency
                  //we play sample with note frequency * 16 speed
                  //length in seconds = sample_length / ( frequency * 16 )

                  maxDuration := ( 1000 * sample_length ) div ( Round( GetNoteFreq( channelState[ i ].m_note.iData1 and $7f ) * power( 1.05946188, m_iPitch ) * 16 ) );

                end
              else
                begin
                  maxduration := m_instrumentPresets[ channelState[ i ].m_instrument ].m_noteDuration;
                end;

            end;

          if ( channelState[ i ].m_start + maxduration < enumerator.GetEventtime() ) then
            begin
              //due to different max durations and different start times,
              //StopNote events generated here can come in unsorted order.
              //Tell StopNote() and AddSyntezerEvent() to instert event using sorting
              StopNote( channelState[ i ].m_note, channelState[ i ].m_start, channelState[ i ].m_start + maxDuration, channelState, true );
            end;
        end;

    //update melody length
    m_melodyLength := enumerator.GetEventTime();

    // note off event,
    // or set note volume 0 event
    if  ( ( enumerator.GetEvent().iEvent and $f0 )= $80 ) or    //note Off
        (
          ( ( enumerator.GetEvent().iEvent and $f0 )= $90) and  //Note On, volume = 0
            ( enumerator.GetEvent().iData2 = 0 )
        ) or
        (
          ( ( enumerator.GetEvent().iEvent and $f0 )= $A0) and  //Note AfterTouch, volume = 0
            ( enumerator.GetEvent().iData2 = 0 )
        )
    then
      begin
        //do not process stopnote event with SINEWAVE_ENVELOPE and
        //SAMPLE modes
        //jikebox and samples do not have an option to stop note
        if ( m_eWaveformKind <> EWK_SINE_ENVELOPE ) and
            ( m_eWaveformKind <> EWK_WAVEFORM1_ENVELOPE ) and
            ( m_eWaveformKind <> EWK_WAVEFORM2_ENVELOPE ) and
            ( m_eWaveformKind <> EWK_WAVEFORM3_ENVELOPE ) and
            ( m_eWaveformKind <> EWK_SAMPLE ) then
        begin
          StopNote( enumerator.GetEvent(), MAXDWORD, enumerator.GetEventTime(), channelState, false );
        end;
      end;

    // note On event ( with volume > 0 )
    if ( ( enumerator.GetEvent().iEvent and $f0 )= $90) and ( enumerator.GetEvent().iData2 > 0 ) then
      begin
        StartNote( enumerator.GetEvent(), enumerator.GetEventTime(), channelState, midiChannelInstruments );
      end;

    // set instrument
    if ( ( enumerator.GetEvent().iEvent and $f0 )= $c0) then
      begin
        midiChannelInstruments[ enumerator.GetEvent().iEvent and $f ] := enumerator.GetEvent().iData1 and $7f;
      end;

    enumerator.MoveToNext();
  end;

  enumerator.Destroy();

  //------------- test events ------------

  for i := 0 to m_syntezerEvents.Count - 1 do
    begin
      ev := m_syntezerEvents[ i ];
      if ( i <> m_syntezerEvents.Count-1 ) then
        begin
          if  TSyntezerChannelStateChange( m_syntezerEvents[ i + 1 ] ).m_start <
                TSyntezerChannelStateChange( m_syntezerEvents[ i ] ).m_start then
          begin
            MessageBeep( 0 );
          end;
        end;
    end;

  //--------------------------------------

  FilterZeroLengthNotes( m_syntezerEvents );
end;

//==============================================================================
//==============================================================================
procedure TSyntezer.StartNote(
                                _event : PMidiEvent;
                                _eventTime : DWORD;
                                var _channelState : array of TSyntezerChannelState;
                                var _midiChannelInstruments : array of byte
                              );
var
 i  : integer;
 midichannel : integer;
 freeChannel : integer;
begin
  freeChannel := -1;

  midiChannel := _event.iEvent and $f;

  //Update  "Midi channel present" array
  m_midiChannelPresent := m_midiChannelPresent or ( 1 shl midichannel );


  //Update "Drum used" and "Instrument used" array
  if ( midiChannel = 9 ) then
    begin
      m_bDrumUsed[ _event.iData1 and $7f ] := true;
    end
   else
    begin
      m_bInstrumentUsed[ _midiChannelInstruments[ midiChannel ] and $7f ] := true;
    end;


  //Ignore notes from disabled midi channels
  if ( IsMidiChannelEnabled( midiChannel ) = false ) then
    begin
      exit;
    end;

  //ignore drums is drum syntezer is disabled
  if ( ( m_bEnableDrums = false ) and IsDrum( _event, _midichannelInstruments ) ) then
    begin
      exit;
    end;

  //ignore notes from disabled instumenrs/drums
  if ( midiChannel = 9 ) then
    begin
      if ( m_drumPresets[ _event.iData1 and $7f ].m_eInstrumentKind = EIK_DISABLED ) then
        begin
          exit;
        end
    end
  else
    begin
      if  ( m_instrumentPresets[ _midiChannelInstruments[ midiChannel ] ].m_eInstrumentKind = EIK_DISABLED ) then
        begin
          exit;
        end;
    end;

  //If single note per midi channel allowed, use syntezer track from previous note
  if ( m_bAllowSingleNotPerChannel ) then
  begin
      for i := 0 to high( _channelState ) do
        if  ( _channelState[ i ].m_note <> nil ) and
            ( (_channelState[ i ].m_note.iEvent and $f ) = midichannel ) then
          begin
            freeChannel := i;
          end;
  end;

  //if "Merge stereo notes" option is on, use refcounter
  if ( m_bSuppressStereoNotes ) then
    begin
      for i := 0 to high( _channelState ) do
        if  ( _channelState[ i ].m_note <> nil ) and
            ( _channelState[ i ].m_note.iData1 = _event.iData1 ) and
            ( ( _eventTime - _channelState[ i ].m_start ) < STEREO_NOTE_SUPPRESS_PERIOD ) then  //iData1 - note number
          begin
            //just add refcount
            inc( _channelState[ i ].m_refCount );
            exit;
          end;
    end;

  // if single drum channel allowed - overwrite note
  if ( m_bForceSingleDrumChannel ) then
    if ( IsDrum( _event, _midichannelInstruments ) ) then
      begin
        for i := 0 to high( _channelState ) do
          if  ( _channelState[ i ].m_note <> nil ) and
              IsDrum( _channelState[ i ].m_note, _midiChannelInstruments ) then
                begin
                  freechannel := i;
                  break
                end;
      end;

   if ( freeChannel = -1 ) then
    begin
      freeChannel := midichannel mod ( high( _channelState ) + 1 );
      if ( _channelState[ freechannel ].m_note <> nil ) then
        begin
          freeChannel := -1;
        end;
    end;

  //find free syntezer channel to play on ( if not already chosen by previous logic )
  if ( freeChannel = -1 ) then
    begin
      for i := 0 to high( _channelState ) do
        if  ( _channelState[ i ].m_note = nil ) then
          begin
            freeChannel := i;
            break;
          end;
    end;

  //if all syntezer channels are used - select channels with most old note
  //and set "Not enought channels" flag
  if ( freeChannel = -1 ) then
    begin
      m_bNotEnoughtChannels := true;

      //use most old channel
      freeChannel := 0;
      for i := 0 to high( _channelState ) do
        if  ( _channelState[ i ].m_start < _channelState[ freeChannel ].m_start ) then
          begin
            freeChannel := i;
          end;
    end;

  _channelState[ freeChannel ].m_start := _eventTime;
  _channelState[ freeChannel ].m_note := _event;
  _channelState[ freeChannel ].m_midiChannel := midiChannel;
  _channelState[ freeChannel ].m_instrument := _midiChannelInstruments[ midiChannel ];
  _channelState[ freeChannel ].m_refCount := 1;

  //create syntezer state change event

  if ( IsDrum( _channelState[ freeChannel ].m_note, _midiChannelInstruments ) ) then
    begin
      //drums!
      AddSyntezerStateChange( _eventTime, freeChannel, 1, false );
    end
      else
    begin
      AddSyntezerStateChange( _eventTime, freeChannel, _event.iData1, false );
    end;

  //update max number of active syntezer channels
  UpdateMaxActiveChannelsCount( _channelState, _midiChannelInstruments );

end;

//==============================================================================
//==============================================================================
procedure TSyntezer.StopNote(
                                _event : PMidiEvent;
                                _noteStartTime : DWORD;
                                _eventTime : DWORD;
                                var _channelState : array of TSyntezerChannelState;
                                _bSort: Boolean
                              );
var
  i : integer;
  midiChannel : integer;
begin

  midiChannel := _event.iEvent and $f;

  for i := 0 to high( _channelState ) do
    if  ( _channelState[ i ].m_note <> nil ) and
        (
          ( _channelState[ i ].m_midiChannel = midiChannel ) or m_bSuppressStereoNotes
        )  and
        ( _channelState[ i ].m_note.iData1 = _event.iData1 ) then
      begin
        if ( _noteStartTime <> MAXDWORD ) then
        begin
          //it is important to match starttime also if we are disabling note with maxDuration.
          //otherwise can stop new repeated note on the same channel.

          if ( m_bSuppressStereoNotes = false ) then
            begin
              if ( _channelState[ i ].m_start <> _noteStartTime ) then
                begin
                  exit;
                end;
            end
            else
            begin
              if ( _channelState[ i ].m_start > _noteStartTime ) or
                  ( _channelState[ i ].m_start + STEREO_NOTE_SUPPRESS_PERIOD < _noteStartTime ) then
                begin
                  exit;
                end;
            end;
        end;

        Assert( _channelState[ i ].m_refCount > 0 );
        dec( _channelState[ i ].m_refCount );

        if ( _channelState[ i ].m_refCount > 0 ) then
          begin
            exit;
          end;

        _channelState[ i ].m_note := nil;

        //create syntezer state change event
        AddSyntezerStateChange( _eventTime, i, 0, _bSort );

        exit;
      end;

end;

//==============================================================================
//==============================================================================
procedure TSyntezer.AddSyntezerStateChange(
                                            _start : DWORD;
                                            _channelIndex : BYTE;
                                            _noteNumber : BYTE;
                                            _bSort: Boolean
                                        );
var
  ev : TSyntezerChannelStateChange;
  i : integer;
begin

  //------- validate start time -----------
  if ( _bSort = false ) then
  begin
    if ( m_syntezerEvents.Count > 0 ) then
      begin
        if ( TSyntezerChannelStateChange(  m_syntezerEvents[  m_syntezerEvents.Count - 1 ] ).m_start > _start ) then
          begin
            MessageBeep( 0 );
          end;
      end;
  end;
  //-----------------------------------------

  ev := TSyntezerChannelStateChange.Create( _start, _channelIndex, _noteNumber);
  m_syntezerEvents.Add( ev );

  if ( _bSort ) then
  begin

    i := m_syntezerEvents.Count - 1;

    while ( i > 0 ) and ( TSyntezerChannelStateChange(  m_syntezerEvents[ i - 1 ] ).m_start > _start ) do
      begin
        ev := m_syntezerEvents[ i - 1 ];
        m_syntezerEvents[ i - 1 ] := m_syntezerEvents[ i ];
        m_syntezerEvents[ i ] := ev;
        dec( i );
      end;

  end;
end;

//==============================================================================
//==============================================================================
procedure TSyntezer.UpdateMaxActiveChannelsCount(
          var _channelState : array of TSyntezerChannelState;
          var _midiChannelInstruments : array of byte
        );
var
  count : DWORD;
  count1 : DWORD;
  i,j : integer;
begin
  count := 0;
  count1 := 0;

  for i := 0 to high( _channelState ) do
    if  ( _channelState[ i ].m_note <> nil ) then
      begin
        inc( count );
        if ( IsDrum( _channelState[ i ].m_note, _midiChannelInstruments ) ) then
          begin
            inc ( count1 );
          end;
      end;

  if ( count > m_maxActiveChannelsCount ) then
    begin
      m_maxActiveChannelsCount := count;
    end;

  if ( count1 > m_maxActiveDrumChannelsCount ) then
    begin
      m_maxActiveDrumChannelsCount := count1;
    end;

  for i := 0 to high( _channelState ) do
    if  ( _channelState[ i ].m_note <> nil ) then
      begin
        count := 0;

        for j := 0 to high( _channelState ) do
          if  ( j<> i ) and
              ( _channelState[ j].m_note <> nil ) and
              ( _channelState[ i ].m_note.iData1 = _channelState[ j ].m_note.iData1 ) then
            begin
              inc( count );
            end;

        if ( count > m_maxActiveStereoNotesCount ) then
          begin
            m_maxActiveStereoNotesCount := count;
          end;

      end;

end;

//==============================================================================
//==============================================================================
function TSyntezer.IsDrum( _ev : PMidiEvent; var _midiChannelInstruments : array of byte ) : Boolean;
var
 midiChannel : BYTE;
begin
  //todo: use instrument definitions
  midiChannel := _ev.iEvent and $f;
  if ( midiChannel = 9 ) then
    begin
      result := m_drumPresets[ _ev.iData1 and $7f ].m_eInstrumentKind = EIK_WHITENOISE;
    end
  else
    begin
      result := m_instrumentPresets[ _midiChannelInstruments[ midiChannel ] ].m_eInstrumentKind = EIK_WHITENOISE;
    end;
end;

//==============================================================================
//==============================================================================
//index is zero-based
function TSyntezer.IsMidiChannelEnabled( _index : integer ) : Boolean;
begin
  result := ( (1 shl _index ) and m_midiChannelEnabled ) > 0;
end;

//==============================================================================
//==============================================================================
//Remove note on event when note off event follows immediatelly ( zero-length notes )
//Remove note off event when note on event follows immediatelly ( just overwrite note )
procedure TSyntezer.FilterZeroLengthNotes( _syntezerEvents : TList );
var
  i : integer;
  channelLastEvent: array of TSyntezerChannelStateChange;
  channelLastEventIndex: array of integer;
  ev : TSyntezerChannelStateChange;
  count : integer;
begin
  SetLength( channelLastEvent, m_channelsCount );
  SetLength( channelLastEventIndex, m_channelsCount );

  for i := 0 to m_channelsCount - 1 do
    begin
      channelLastEvent[ i ] := nil;
    end;

  count := 0;

  for i := 0 to _syntezerEvents.Count - 1 do
    begin
      ev := _syntezerEvents[ i ];

      if ( channelLastEvent [ ev.m_channelIndex ] <> nil ) then
        begin
          if ( ev.m_start = channelLastEvent [ ev.m_channelIndex ].m_start ) then
            begin
              //remove redundant event
              channelLastEvent [ ev.m_channelIndex ].Destroy();
              _syntezerEvents[ channelLastEventIndex [ ev.m_channelIndex ] ] := nil;
              channelLastEvent [ ev.m_channelIndex ] := nil;
              inc( count );
            end;
        end;

      channelLastEvent [ ev.m_channelIndex ] := ev;
      channelLastEventIndex [ ev.m_channelIndex ] := i;
    end;

  OutputDebugString( PChar( intToStr( count ) + ' redundant events removed.' ) );

  i := 0;
  while ( i < _syntezerEvents.Count ) do
    begin
      if ( _syntezerEvents[ i ] = nil ) then
        begin
          _syntezerEvents.Delete( i );
        end
      else
        begin
          inc ( i );
        end;
    end;

end;


//==============================================================================
//==============================================================================
procedure TSyntezer.CreateMelodyCode(
        startPosition, endPosition : integer;
        _freq: DWORD;
        _bUseCompression : Boolean;
        _bCalculateCodeSizeOnly : boolean;
        var code: String;
        var codeSize : integer
        );
const
  CR : String = #13 + #10;
var
  i,j : integer;
  s : Ansistring;
  stream1, stream2: AnsiString;
  ev,ev1 : TSyntezerChannelStateChange;
  f: file;

  m_noteNumber : integer;

  m_delta : WORD;
  channelIndex : integer;

  valuesList : TList;
  valuesList2 : TList;

  cp : TCompressor;

  sm : TSequenceMaker;

  ratio : single;

begin
  valuesList := TList.Create();
  valuesList2 := TList.Create();

  s := '#include "melody.h"' + CR + CR;

  s := s + '//Player frequency=' + inttostr( _freq )  + CR;
  s := s + '//Player minimum channels count =' + inttostr( m_channelsCount )  + CR;

  for i := 0 to m_syntezerEvents.Count - 1 do
    begin
      ev := m_syntezerEvents[ i ];

      if ( ev.m_start < startPosition) then continue;
      if ( ev.m_start >= endPosition) then break;

      m_noteNumber := ev.m_noteNumber;
      if ( m_noteNumber > 127 ) then m_noteNumber := 127;

      m_noteNumber := m_noteNumber + ( ev.m_channelIndex shl 7 );

      if ( i = m_syntezerEvents.Count - 1 ) then
      begin
        j := 0;
      end
        else
      begin
        j := TSyntezerChannelStateChange( m_syntezerEvents[ i + 1 ] ).m_start;
        if ( j >= endPosition) then
          begin
            j := 0;
          end
            else
          begin
            j := j - ev.m_start;
          end;
      end;

      //round to 4ms
      //j := ( j div 4 ) * 4;

      //j - ms to wait for next event execution
//      j := j * _freq div 1000;
      j := j * 255 div 1000;

      //j - 255Hz ticks to wait for next event execution

      //REVIEW: just repeat previous event with max wait time
      if ( j > $1fff ) then
        begin
          j := $1fff;
        end;

      //min delta time is 1 => process event on text 255Hz tick
      //it wan't be noticable
      if ( j < 1 ) then
        begin
          j := 1;
        end;

      valuesList.Add( pointer( m_notenumber ) );
      valuesList2.Add( pointer( j ) );
    end;

  //wait time = 0 is special 'end' mark
  valuesList.Add( pointer ( 0 ) );
  valuesList2.Add( pointer ( 0 ));

  if ( _bUseCompression = true ) then
    begin
      cp := TCompressor.Create();
      stream1 := cp.Compress( valuesList, 11 );
      cp.Destroy();

      cp := TCompressor.Create();
      stream2 := cp.Compress( valuesList2, 13 );
      cp.Destroy();

      ratio := ( length( stream1 ) + length( stream2 ) ) /
      ((valuesList.Count * 11 / 8) + (valuesList2.Count * 13 / 8));

      OutputDebugStringW( pwchar( 'Compression ratio: ' + FloatToStr( ratio ) ));

      codeSize := length( stream1 ) + length( stream2 ) + 4; //+TMelodyStreams
    end
      else
    begin
      codeSize := valuesList.Count * 3;
    end;

  if ( _bCalculateCodeSizeOnly = false ) then
    begin
      if ( _bUseCompression = false ) then
        begin
          s := s + 'const flash TPlayerStateChange s_melody_events[' + intToStr( valuesList.Count ) + '] = {' + CR;

          for i := 0 to valuesList.Count - 1 do
            begin
              m_delta := integer( valuesList2[ i ] );
              m_noteNumber := integer( valuesList[ i ] ) and $7f;
              channelIndex := (integer( valuesList[ i ] )shr 7) and $f;

              m_delta := m_delta shl 3;
              m_delta := m_delta or ( channelIndex and $7 );

              if ( channelIndex >= 8) then
                begin
                  m_noteNumber := m_noteNumber or $80;
                end;

              s := s + '     { ' + inttostr( m_noteNumber ) + ', ' + inttostr( m_delta ) + ' }';

              if ( i = valuesList.Count - 1 ) then
                begin
                  s := s + CR;
                end
                  else
                begin
                  s := s + ',' + CR;
                end;

              inc( codeSize, 3 );
            end; //for

          s := s + '  };' + CR;
          s := s + CR;

          s := s + 'const flash TMelody s_melody = {' + CR;
          s := s + '    s_melody_events' + CR;
          s := s + '  };' + CR;
          s := s + CR;

          code := s;
        end //usecompression=false
          else
        begin
          s := s + 'const flash uint8_t s_melody_stream1[' + intToStr( length( stream1 ) ) + '] = {' + CR;

          for i := 0 to length( stream1 ) - 1 do
            begin
              s := s + '    ' + inttostr( ord ( stream1[ i + 1 ] ) );

              if ( i = length( stream1 ) - 1 ) then
                begin
                  s := s + CR;
                end
                  else
                begin
                  s := s + ',' + CR;
                end;
            end;

          s := s + '  };' + CR;

          s := s + CR;
          s := s + 'const flash uint8_t s_melody_stream2[' + intToStr( length( stream2 ) ) + '] = {' + CR;

          for i := 0 to length( stream2 ) - 1 do
            begin
              s := s + '    ' + inttostr( ord ( stream2[ i + 1 ] ) );

              if ( i = length( stream2 ) - 1 ) then
                begin
                  s := s + CR;
                end
                  else
                begin
                  s := s + ',' + CR;
                end;
            end;

          s := s + '  };' + CR;
          s := s + CR;

          s := s + 'const flash TMelody s_melody = {' + CR;
          s := s + '    s_melody_stream1,' + CR;
          s := s + '    s_melody_stream2' + CR;
          s := s + '  };' + CR;
          s := s + CR;

          code := s;
        end; //else
    end; //calculateCodeSizeOnly=false

  valuesList2.Destroy;
  valuesList.Destroy;
(*
  sm := TSequenceMaker.Create();

    for i := 0 to m_syntezerEvents.Count - 1 do
      begin

        ev := m_syntezerEvents[ i ];
        if ( i < m_syntezerEvents.Count - 1 ) then
          begin
            ev1 := m_syntezerEvents[ i + 1 ];
            j := ev1.m_start - ev.m_start;
            //j := ( j div 10 ) * 10;
            sm.AddItem( TSyntezerChannelStateChange.Create( j, ev.m_channelIndex, ev.m_noteNumber ) );
          end
          else
          begin
            sm.AddItem( TSyntezerChannelStateChange.Create( $1fff, ev.m_channelIndex, ev.m_noteNumber ) );
          end;

      end;

    //sm.BuildSequences(10);

    sm.Destroy();
  end;
*)
end;

//==============================================================================
//==============================================================================
procedure TSyntezer.CreatePlayerConfig( _freq : DWORD; _bUseCompression : Boolean );
const
  CR : String = #13 + #10;
var
  s : String;
begin

  s := '#ifndef HXMIDIPLAYER_CONFIG_INCLUDED' + CR;
  s := s + '#define HXMIDIPLAYER_CONFIG_INCLUDED' + CR + CR;

  s := s + '#include <stdint.h>' + CR + CR;

  s := s + '//=====================================================' + CR;
  s := s + '//=====================================================' + CR;
  s := s + '//Player settings:' + CR;
  s := s + '//Channels count: ' + intTostr( m_channelsCount ) + CR;
  s := s + '//Frequency: ' + intTostr( _freq ) + CR;
  s := s + '//Pitch: ' + intTostr( m_iPitch ) + CR;
  s := s + '//Waveform: ' + GetEnumName( TypeInfo(EWAVEFORMKIND), integer(  m_eWaveformKind)) + CR;

  s := s + CR;

  s := s + '//uncomment to place note frequency table in eeprom' + CR;
  s := s + '//#define NOTES_TO_EEPROM' + CR;
  s := s + CR;

  if ( ( m_eWaveformKind <> EWK_SQUARE ) and ( m_eWaveformKind <> EWK_SAMPLE ) ) then
  begin
    s := s + '//uncomment to place sine table in eeprom' + CR;
    s := s + '//#define SINETABLE_TO_EEPROM' + CR;
    s := s + CR;
  end;

  if ( m_eWaveformKind in [ EWK_SINE_ENVELOPE, EWK_WAVEFORM1_ENVELOPE,
                            EWK_WAVEFORM2_ENVELOPE, EWK_WAVEFORM3_ENVELOPE]
    ) then
  begin
    s := s + '//uncomment to place envelope table in eeprom' + CR;
    s := s + '//#define ENVELOPE_TO_EEPROM' + CR;
    s := s + CR;
  end;

  s := s + '//=====================================================' + CR;
  s := s + '//=====================================================' + CR;
  s := s + '#define HXMIDIPLAYER_SAMPLING_RATE          ' + intToStr( _freq ) + CR;
  s := s + '#define HXMIDIPLAYER_CHANNELS_COUNT         ' + intToStr( m_channelsCount ) + CR;

  case ( m_eWaveformKind ) of
    EWK_SQUARE:
      s := s + '#define HXMIDIPLAYER_WAVEFORM_SQUARE' + CR;

    EWK_SINE,
    EWK_WAVEFORM1,
    EWK_WAVEFORM2,
    EWK_WAVEFORM3:
      s := s + '#define HXMIDIPLAYER_WAVEFORM_SINE' + CR;

    EWK_SINE_ENVELOPE,
    EWK_WAVEFORM1_ENVELOPE,
    EWK_WAVEFORM2_ENVELOPE,
    EWK_WAVEFORM3_ENVELOPE:
      s := s + '#define HXMIDIPLAYER_WAVEFORM_SINE_ENVELOPE' + CR;

    EWK_SAMPLE:
      begin
        s := s + '#define HXMIDIPLAYER_WAVEFORM_SAMPLE' + CR;
      end;
  end;

  if ( m_bEnableDrums ) then
    begin
      s := s + '#define HXMIDIPLAYER_ENABLE_DRUMS_SYNTEZER' + CR;
    end;

  if ( _bUseCompression ) then
    begin
      s := s + '#define HXMIDIPLAYER_USE_COMPRESSION' + CR;
    end;

  s := s + Get255HzCounterCode( _freq ) + CR;

  s := s + CR;

  s := s + GetNoteFreqExTableCCode( _freq );
  s := s + CR;

  case ( m_eWaveformKind ) of
    EWK_SINE,
    EWK_WAVEFORM1,
    EWK_WAVEFORM2,
    EWK_WAVEFORM3:
      begin
        s := s + GetSineTableCCode( true ) + CR;
      end;

    EWK_SINE_ENVELOPE,
    EWK_WAVEFORM1_ENVELOPE,
    EWK_WAVEFORM2_ENVELOPE,
    EWK_WAVEFORM3_ENVELOPE:
      begin
        s := s + GetSineTableCCode( false ) + CR;
        s := s + GetEnvelopeCCode( _freq ) + CR;
      end;

    EWK_SAMPLE:
      begin
        s := s + GetSampleCode( m_channelsCount );
      end;
  end;

  s := s + CR;
  s := s + '#endif HXMIDIPLAYER_CONFIG_INCLUDED' + CR;

  Clipboard.AsText := s;
end;

(*
function GetOnlyFileName( const _fname : String ) :String;
begin
  result := ExtractfilePath( _fname ) + ExtractfileName( _fname );
end;
*)

//==============================================================================
//==============================================================================
//Create helper table for GetNoteFreqAdd
procedure TSyntezer.CreateRTFreqTable(
        _freq : DWORD;
        var nf : array of WORD;
        var _iFreqShr : DWORD;
        var _maxCounter2Val : DWORD
        );
var
  i : integer;
  d : DWORD;
  maxMul : DWORD;
  b : boolean;
begin

  //here we have to calculate counterAdd values for the top 12 notes ( 120..131 )
  //considering pitch

  //counter has 16 bit precision.
  //The goal is to oscillate higher bit of counter with a frequency of note.

  //Let note frequency is 1046Hz
  //Timer frequency is 16000Hz
  //counterAdd = 1046 * $8000 / 16000 = 2142

  //but with high pitch counter can exceed 16 bit precision
  //f.e.
  //Let note frequency is 25086Hz
  //Timer frequency is 8000Hz
  //counterAdd = 25086 * $8000 / 8000 = 102572

  //102572  > 65535

  //in this case we are aiming to oscillate 14th bit, this
  //way we can set counterAdd to 102572 / 2

  //the algoruthm below is to choose what bit to oscillate

  maxmul := $8000;
  _iFreqShr := 15;

  while ( true ) do
    begin
        b := true;
        for i := 0 to 11 do
        begin
          d := Round( GetNoteFreq( 120 + i ) * power( 1.05946188, m_iPitch ) );
          d := d * maxmul div _freq;
          if d > $ffff then
            begin
              b := false;
            end;
          nf[ 11 - i ] := d;
      end;

      if ( b = true ) then break;

      dec( _iFreqShr );
      maxMul := maxMul shr 1;
    end;


  //we use ( counter shr 3 ) to index samples
  //so maximum value for counter is sample_size << ( _iFreqShr - 3 )
  case  m_eWaveformKind of
    EWK_SAMPLE:
      begin
        _maxCounter2Val := sample_length shl ( _iFreqShr - 3 );
      end;

    else
      begin
        _maxCounter2Val := 0;
      end;
  end;

  //what is sampling rate for sample?
  //we use counter >> ( _iFreqShr - 3 ) to index sample
  //Middle C is 261Hz
  //Considering 15th bit will oscillate with 261Hz frequency == increase with 261*2 Hz
  //14th bit will oscillate with 261*2 * 2 frequency,
  //13th bit will oscillate with 261*2 * 2 * 2 frequency,
  //12th bit will oscillate with 261*2 * 2 * 2 * 2 frequency =
  //   4176Hz sampling rate for middle C (C4) sound
  //OR   8362Hz sampling rate for C5 sound

  //

end;

//==============================================================================
//==============================================================================
procedure TSyntezer.CreateSineTable( amplitude: integer; var sineTable : array of integer );
var
 i: integer;

const ss1: Array [0..63] of integer =
    (
       0,   55,  100,  118,  127,  127,  127,  127,  127,  127,  127,  127,  127,  127,  127,  100,
      63,   27,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   -8,  -27,  -19,
       0,   18,   27,    9,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  -26,
     -63, -100, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -119, -101,  -57
    );

const ss2: Array [0..63] of integer =
    (
      63,   64,   57,   42,   24,    5,  -10,  -21,  -21,  -10,    7,   31,   58,   84,  107,  121,
     127,  121,  107,   85,   58,   31,    8,  -10,  -21,  -21,  -10,    5,   24,   42,   57,   64,
      63,   52,   32,    6,  -27,  -62,  -93, -116, -128, -126, -114,  -94,  -69,  -42,  -20,   -4,
       0,   -4,  -18,  -41,  -68,  -93, -114, -126, -128, -117,  -94,  -65,  -29,    4,   31,   51
    );

const ss3: Array [0..63] of integer =
    (
       0,   38,   73,  101,  120,  127,  125,  114,  100,   82,   66,   54,   46,   44,   44,   45,
      46,   46,   41,   32,   18,    4,  -16,  -37,  -52,  -56,  -54,  -40,  -23,   -7,    1,    2,
       0,  -14,  -40,  -68,  -97, -116, -128, -123, -101,  -71,  -28,    6,   29,   48,   57,   57,
      48,   30,    8,  -23,  -64,  -94, -113, -118, -111,  -94,  -73,  -49,  -28,  -11,   -2,    0
    );

begin

  case m_eWaveformKind of
    EWK_WAVEFORM1,
    EWK_WAVEFORM1_ENVELOPE:
      begin
        for i:=0 to 63 do sineTable[ i ] := round( ss1[ i ] / 128.0  * amplitude );
      end;

    EWK_WAVEFORM2,
    EWK_WAVEFORM2_ENVELOPE:
      begin
        for i:=0 to 63 do sineTable[ i ] := round( ss2[ i ] / 128.0  * amplitude );
      end;

    EWK_WAVEFORM3,
    EWK_WAVEFORM3_ENVELOPE:
      begin
        for i:=0 to 63 do sineTable[ i ] := round( ss3[ i ] / 128.0  * amplitude );
      end;

    else
      begin
        for i:=0 to 63 do sineTable[ i ] := round( sin( i / 64 * 2 * PI) * amplitude );
      end;
  end;
end;

//==============================================================================
//==============================================================================
procedure TSyntezer.InitEnvelopeTable();
const
 env : array [0..255] of byte =
    (
    	  255,252,250,247,245,243,240,238,235,233,231,228,226,224,222,219,
	      217,215,213,211,209,207,205,203,201,199,197,195,193,191,189,187,
	      185,183,182,180,178,176,174,173,171,169,168,166,164,163,161,159,
	      158,156,155,153,152,150,149,147,146,144,143,141,140,139,137,136,
	      134,133,132,130,129,128,127,125,124,123,122,120,119,118,117,116,
	      115,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,
	      98,97,96,95,94,93,92,91,90,89,88,87,87,86,85,84,
	      83,82,82,81,80,79,78,78,77,76,75,75,74,73,72,72,
	      71,70,69,69,68,67,67,66,65,65,64,64,63,62,62,61,
	      60,60,59,59,58,57,57,56,56,55,55,54,54,53,53,52,
	      51,51,50,50,49,49,48,48,48,47,47,46,46,45,45,44,
	      44,43,43,43,42,42,41,40,40,39,39,38,38,37,37,36,
	      35,35,34,34,33,33,32,31,31,30,30,29,29,28,28,27,
	      26,26,25,25,24,24,23,22,22,21,21,20,20,19,19,18,
	      17,17,16,16,15,15,14,13,13,12,12,11,11,10,10,9,
	      8,8,7,7,6,6,5,4,4,3,3,2,2,1,1,0 );

var
 i: integer;
begin
  for i := 0 to 127 do m_envelopeTable[i] := env[i*2];
  m_envelopeTable[ 127 ] := 0;
end;

//==============================================================================
//==============================================================================
function TSyntezer.Get255HzCounterCode( _freq : integer ) : String;
const
  CR : String = #13 + #10;
var
  i, j: integer;
  envelopeSkipMax : integer;
begin
  envelopeSkipMax := ( _freq + 128 ) div 255;
  result := '#define ENVELOPE_SKIP_MAX      ' + inttostr( envelopeSkipMax ) + CR;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetEnvelopeCCode( _freq : integer ) : String;
const
  CR : String = #13 + #10;
var
  i, j: integer;
begin
  result := result + 'static const' + CR;
  result := result + '#ifdef ENVELOPE_TO_EEPROM' + CR;
  result := result + 'eeprom' + CR;
  result := result + '#else' + CR;
  result := result + 'flash' + CR;
  result := result + '#endif' + CR;

  result := result + 'uint8_t s_envelope[ 128 ] = { ';

  for i := 0 to 127 do
    begin
      if ( ( i mod 16 ) = 0 ) then
        begin
          result := result + CR + '    ';
        end;

      j := m_envelopeTable[ i ];
      result := result + '0x' + intToHex( j, 2 );

      if ( i < 127 ) then
        begin
          result := result + ', ';
        end;
    end;

  result := result + ' };' + CR;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetSineTableCCode( _bSigned : Boolean ) : String;
const
  CR : String = #13 + #10;
var
  maxChannelAmplitude : integer;
  i, j: integer;
  sineTable : array [ 0..63 ] of integer;
begin
  maxChannelAmplitude := 127 div m_channelsCount;
  CreateSineTable( maxChannelAmplitude, sineTable );

  result :='//Rescaled for channels count = ' + intToStr( m_channelsCount ) + CR;

  result := result + 'static const' + CR;
  result := result + '#ifdef SINETABLE_TO_EEPROM' + CR;
  result := result + 'eeprom' + CR;
  result := result + '#else' + CR;
  result := result + 'flash' + CR;
  result := result + '#endif' + CR;

  if ( _bSigned ) then
    begin
      result := result + 'int8_t s_sineTable[ 64 ] = { ';
    end
      else
    begin
      result := result + 'uint8_t s_sineTable[ 64 ] = { ';
    end;

  for i := 0 to 63 do
    begin

      if ( ( i mod 16 ) = 0 ) then
        begin
          result := result + CR + '    ';
        end;

      j := sineTable[ i ];

      if ( _bSigned = false ) then
        begin
          j := j + 128;
        end;

      if ( j >= 0 ) then
        begin
          result := result + '0x' + intToHex( j, 2 );
        end
          else
        begin
          result := result + '0x' + intToHex( 255 + j, 2 );
        end;

      if ( i < 63 ) then
        begin
          result := result + ', ';
        end;
    end;

  result := result + ' };' + CR;
end;

//==============================================================================
//==============================================================================
function TSyntezer.GetNoteFreqExTableCCode( _freq : DWORD ) : String;
const
  CR : String = #13 + #10;
var
  i, j: integer;
  noteFreqEx : array [ 0..11 ] of WORD;
  maxCounter2Val : DWORD;
  iFreqShr : DWORD;
begin
  CreateRTFreqTable( _freq, noteFreqEx, iFreqShr,  maxCounter2Val );

  result := '//Player frequency = ' + intToStr( _freq ) + CR;
  result := result + '//Pitch = ' + intToStr( m_iPitch ) + CR;
  result := result + '#define PLAYER_FREQ_SHR               ' + intToStr( iFreqShr  ) + CR;
  result := result + '#define PLAYER_COUNTER_MAX_VAL        ' + intToStr( maxCounter2Val ) + CR;
  result := result + 'static const' + CR;
  result := result + '#ifdef NOTES_TO_EEPROM' + CR;
  result := result + 'eeprom' + CR;
  result := result + '#else' + CR;
  result := result + 'flash' + CR;
  result := result + '#endif' + CR;
  result := result + 'uint16_t s_noteFreqEx[ 12 ] = { ';

  for i := 0 to 11 do
    begin
      j := noteFreqEx[ i ];
      result := result + '0x' + intToHex( j, 4 );

      if ( i < 11 ) then
        begin
          result := result + ', ';
        end;
    end;

  result := result + ' };' + CR;
end;

begin

end.


