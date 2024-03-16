unit MidiEventsEnumerator;

interface
uses Midifile, Windows;

//==============================================================================
// Class TMidiEventsEnumerator
//==============================================================================
//Helper class to enumerate midi events in order of appearance on all tracks
//Also handles tempo change events and is able to provide event time in ms
type TMidiEventsEnumerator = class
    public

      ///Constructor
      constructor Create( _midiFile : TMidiFile );

      ///Get current event or nil
      function GetEvent() : PMidiEvent;

      ///Get current event time in ms
      function GetEventTime() : DWORD;

      //move to next event
      procedure MoveToNext();

      //set initial state
      procedure Reset();

    private

      ///Reference to midi file
      m_midiFile : TMidiFile;

      ///current event index for each track
      m_tracksIndex : array of DWORD;

      ///current iPosition or -1 ( no events with save time )
      //m_curPosition and m_nextTrack are used to enumerate tracks with same start time
      m_curPosition : integer;

      /// next track to examine for m_curPosition
      m_nextTrack  : integer;

      //current event or null ( end of file );
      m_event : PMidiEvent;

      //current even time, ms
      m_eventtime : DWORD;

      //iPosition of last tempo change event
      m_lastTempoChangePosition : DWORD;

      //time of last tempo change event
      m_lastTempoChangeTime : DWORD;

      //current microseconds per quarter note
      m_mpqn : DWORD;

      ///Find lowest iPosition on all tracks using current indices
      function GetLowestPosition() : integer;

      ///Check if current event is change tempo event.
      ///Handle it.
      procedure HandleChangeTempoEvent();

  end;

implementation

//==============================================================================
//==============================================================================
constructor TMidiEventsEnumerator.Create( _midiFile : TMidiFile );
begin
  m_midiFile := _midiFile;

  Reset();
end;

//==============================================================================
//==============================================================================
procedure TMidiEventsEnumerator.Reset();
var
  i : integer;
begin
  //set all track indices to 0
  SetLength( m_tracksIndex, m_midiFile.trackCount );
  for i := 0 to high( m_tracksIndex ) do
    begin
      m_tracksIndex[ i ] := 0;
    end;

  m_curPosition := -1;
  m_nextTrack := -1;

  m_lastTempoChangePosition := 0;
  m_lastTempoChangeTime := 0;

  //default tempo is 120 bpm
  m_mpqn := 6000000 div  120;

  m_event := nil;
  m_eventTime := 0;

  MoveToNext();
end;

//==============================================================================
//==============================================================================
function TMidiEventsEnumerator.GetLowestPosition() : integer;
var
  i     : integer;
  index : integer;
  pos   : integer;
begin
  result := -1;

  for i := 0 to high( m_tracksIndex ) do
    begin
      index := m_tracksIndex[ i ];
      if ( index < m_midiFile.GetTrack( i ).EventCount ) then
        begin
          pos := m_midiFile.GetTrack( i ).GetEvent( index ).iPositon;
          if ( result = -1 ) or ( pos < result ) then
            begin
              result := pos;
            end;
        end;
    end;
end;

//==============================================================================
//==============================================================================
function TMidiEventsEnumerator.GetEvent() : PMidiEvent;
begin
  result := m_event;
end;

//==============================================================================
//==============================================================================
function TMidiEventsEnumerator.GetEventTime() : DWORD;
begin
  result := m_eventTime;
end;

//==============================================================================
//==============================================================================
procedure TMidiEventsEnumerator.MoveToNext();
var
  i     : integer;
  index : integer;
begin
  if ( m_curPosition = -1 ) then
    begin
      m_curPosition := GetLowestPosition();

      if ( m_curPosition = -1 ) then
        begin
          //no more events available
          m_event := nil;
          exit;
        end;

      //set next track to examine
      m_nextTrack := 0;
    end;

    for i := m_nextTrack to high( m_tracksIndex ) do
      begin
        index := m_tracksIndex[ i ];

        if ( index < m_midiFile.GetTrack( i ).EventCount )  then
          begin
            if ( m_midiFile.GetTrack( i ).GetEvent( index ).iPositon = m_curPosition ) then
                begin
                  m_event := m_midiFile.GetTrack( i ).GetEvent( index );

                  m_eventTime := m_lastTempoChangeTime +
                                  ( m_event.iPositon - m_lastTempoChangePosition ) * ( m_mpqn div 1000 ) div
                                    m_midiFile.GetMidiHead().PulsesPerQuarter;

                  inc( m_tracksIndex[ i ] );
                  inc( m_nextTrack );
                  HandleChangeTempoEvent();
                  exit;
                end;
            end;
      end;

  //no more events with m_curPosition,
  //move to next position
  m_curPosition := -1;

  MoveToNext();
end;

//==============================================================================
//==============================================================================
procedure TMidiEventsEnumerator.HandleChangeTempoEvent();
var
 i : integer;
begin
  //set tempo event
  if ( m_event.iEvent = 255 ) and ( m_event.iData1 = $51 ) then
    begin
      m_lastTempoChangeTime := m_lastTempoChangeTime +
          ( m_event.iPositon - m_lastTempoChangePosition ) * ( m_mpqn div 1000 ) div
            m_midiFile.GetMidiHead().PulsesPerQuarter;

      m_lastTempoChangePosition := m_event.iPositon;

      m_mpqn := 0;

      for i := 1 to 3 do
        begin
          m_mpqn := m_mpqn * 256;
          if ( i < length ( m_event.sLetter ) ) then
            m_mpqn := m_mpqn + ord( m_event.sLetter[ i ] );
        end;

    end;
end;



end.
