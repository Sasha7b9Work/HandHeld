unit BitWriteStream;

interface
uses Classes;

//==============================================================================
//==============================================================================
type TBitWriteStream = class

  public
    constructor Create();
    destructor Destroy(); override;
    //higher bits first
    procedure Write( _value : integer; _numberOfBits: integer );
    procedure WriteBit( _value : integer );
    //can be called only once
    function GetContents() : AnsiString;
  private

    st : TMemoryStream;
    b : BYTE;
    n : integer;
end;

implementation
uses Windows;

//==============================================================================
//==============================================================================
constructor TBitWriteStream.Create();
begin
  st := TMEmoryStream.Create();
  b := 0;
  n := 0;
end;

//==============================================================================
//==============================================================================
destructor TBitWriteStream.Destroy();
begin
  if ( st <> nil ) then
    begin
      st.Destroy();
    end;
  st := nil;
end;

//==============================================================================
//==============================================================================
procedure TBitWriteStream.Write( _value : integer; _numberOfBits: integer );
var
 i: integer;
begin
  for i := _numberOfBits - 1 downto 0 do
    begin
      WriteBit( (_value shr i) and 1 );
    end;
end;

//==============================================================================
//==============================================================================
procedure TBitWriteStream.WriteBit( _value : integer );
begin
  b := b shl 1;
  if ( _value <> 0 ) then
    begin
      b := b or 1;
    end;

  inc( n );

  if ( n = 8 ) then
  begin
    st.Write( b, 1 );
    n := 0;
  end;

end;

//==============================================================================
//==============================================================================
function TBitWriteStream.GetContents() : Ansistring;
begin
  while ( n > 0 ) do
    begin
      WriteBit( 0 );
    end;

  setLength( result, st.Size );
  st.Seek( 0, soFromBeginning );
  st.ReadBuffer( result[1], st.Size );
  st.Destroy();
  st:= nil;
end;

end.
