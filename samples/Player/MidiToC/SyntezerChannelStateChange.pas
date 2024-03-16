unit SyntezerChannelStateChange;

interface
uses Windows, SequenceMember;

//==============================================================================
//==============================================================================
type TSyntezerChannelStateChange = class( ISequenceMember )
  public
    //event start time, ms
    m_start         : DWORD;

    ///channel's index to change
    m_channelIndex  : BYTE;

    ///set note index to channel
    ///0 - disable
    ///1 - white noise
    ///2..127 - note number
    m_noteNumber    : BYTE;

    constructor Create( _start : DWORD; _channelIndex : BYTE; _noteNumber : BYTE );

    function Compare( _rhs : ISequenceMember ) : integer; override;

  end;



implementation

//==============================================================================
//==============================================================================
constructor TSyntezerChannelStateChange.Create( _start : DWORD; _channelIndex : BYTE; _noteNumber : BYTE );
begin
  m_start := _start;
  m_channelIndex  := _channelIndex;
  m_noteNumber := _noteNumber;
end;

//==============================================================================
//==============================================================================
function TSyntezerChannelStateChange.Compare( _rhs : ISequenceMember ) : integer;
var
  rhs : TSyntezerChannelStateChange;
begin
  rhs := _rhs as TSyntezerChannelStateChange;

  if ( m_start > rhs.m_start ) then
    begin
      result := 1;
      exit;
    end
  else if ( m_start < rhs.m_start ) then
    begin
      result := -1;
      exit;
    end
  else if ( m_channelIndex > rhs.m_channelIndex ) then
    begin
      result := 1;
      exit;
    end
  else if ( m_channelIndex < rhs.m_channelIndex ) then
    begin
      result := -1;
      exit;
    end
  else if ( m_noteNumber > rhs.m_noteNumber ) then
    begin
      result := 1;
      exit;
    end
  else if ( m_noteNumber < rhs.m_noteNumber ) then
    begin
      result := -1;
      exit;
    end
  else
    begin
      result := 0;
      exit;
    end
end;

end.
