unit BitReadStream;

interface
uses Classes;

//==============================================================================
//==============================================================================
type TBitReadStream = class

  public
    constructor Create( _data: String );
    destructor Destroy(); override;
    //higher bits first
    function Read( _numberOfBits: integer ) : integer;
    function ReadBit() : integer;
  private

    data : AnsiString;
    index: integer;
    //number of bits used in current byte
    n : integer;

end;

implementation
uses Windows;

//==============================================================================
//==============================================================================
constructor TBitReadStream.Create( _data : String );
begin
  data := _data;
  n := 0;
  index :=0 ;
end;

//==============================================================================
//==============================================================================
destructor TBitReadStream.Destroy();
begin
end;

//==============================================================================
//==============================================================================
function TBitReadStream.Read( _numberOfBits: integer ) : integer;
var
 i1,i2,i3 : integer;
 i,j : integer;
begin

  if ( _numberOfBits <= 16 ) then
    begin
    i1 := index + 1;
    i2 := index + 2;
    if ( i2 > length( data ) ) then i2 := length ( data );
    i3 := index + 3;
    if ( i3 > length( data ) ) then i3 := length ( data );

    result := ord( data[ i1 ] );

    result := result shl 8;
    result := result or ord ( data[ i2 ] );

    result := result shl 8;
    result := result or ord( data[ i3 ] );

    j := 24 - _numberOfBits - n;

    result := result shr j;

    j := n + _numberOfBits;
    inc( index, j shr 3 );
    n := j and $7;

    j := $ffff shr ( 16 - _numberOfBits );
    result := result and j;
    exit;
  end;

  result := 0;
  for i := _numberOfBits - 1 downto 0 do
    begin
      result := result shl 1;
      if ( ReadBit() <> 0  ) then
        begin
          result := result or 1;
        end;
    end;
end;

//==============================================================================
//==============================================================================
function TBitReadStream.ReadBit() : integer;
var
  b : BYTE;
begin
  b := ord( data[ index + 1 ] );

  if ( ( ( b shr ( 7 - n) ) and 1 ) <> 0 )then
    begin
      result := 1;
    end
      else
    begin
      result := 0;
    end;

  inc( n );
  if ( n = 8 ) then
  begin
    n := 0;
    inc( index );
  end;

end;

end.

