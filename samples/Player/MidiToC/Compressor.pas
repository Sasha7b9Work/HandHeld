unit Compressor;

interface
uses Windows, Classes, SysUtils, ClipBrd, math;

//==============================================================================
//==============================================================================
type TCompressor = class

  public
    procedure BuildFrequencyTable( _list : TLIst; var _countValueTable : TStringList );
    procedure Debug_CheckMethods( _list : TLIst; _bitsPerValue : integer );
    function Compress( _list : TList; _bitsPerValue : integer ) : String;
    function Decompress( _data : String; _bitsPerValue : integer ) : TList;

    procedure Debug_Compare( _values1 : TList; _values2 : TList );
  private

    function CountValues( _list : TStringList; _start, _end : integer; _bitsPerValue: integer ): integer;
    procedure BuildEncodeTable( _countValueTable : TStringList; var _encode : TSTringList );

end;

implementation
uses BitWriteStream, BitReadStream;

//==============================================================================
//==============================================================================
procedure TCompressor.Debug_CheckMethods( _list : TLIst; _bitsPerValue : integer );
var
  countValueTable : TStringList;
  i,j : integer;
  s : String;
begin
  BuildFrequencyTable( _list, countValueTable );

  //j - max count
  j := strtoint( countValueTable.Names[0] ) div 100;
  if ( j = 0) then  j:=1;

  s := '';

  for i := 0 to countValueTable.Count - 1 do
    begin
      s := s +
                    countValueTable.Names[ i ] + ':' +
                    Format( '%05d', [ strToInt (countValueTable.ValueFromIndex[ i ] ) ] ) + ' ' +
                    StringOfChar('*', strtoint( countValueTable.Names[ i ] ) div j) +
                    #13 + #10;
    end;

  j := CountValues(CountValueTable, 0,-1, _bitsPerValue);
  s := s + #13 + #10 + '(uncompressed): ' + inttostr(j div 8);

  //0000..1101 - 0..13
  //1110 xxxxxx - 14..77
  //1111 - immediate
  j := CountValues( CountValueTable, 0, 13, 4 ) +
        CountValues(CountValueTable, 14,77, 10) +
        CountValues(CountValueTable, 78,-1, _bitsPerValue+4) +
        math.Min( countValueTable.Count, 78 ) * _bitsPerValue;
  s := s + #13 + #10 + '(78): ' + inttostr(j div 8);

  //000...101 - 0..5
  //110 00000 - 6-37
  //111 immediate
  j := CountValues( CountValueTable, 0, 5, 3 ) +
        CountValues(CountValueTable, 6, 37, 8 ) +
        CountValues(CountValueTable, 38,-1, _bitsPerValue+3) +
        math.Min( countValueTable.Count, 38 ) * _bitsPerValue;
  s := s + #13 + #10 + '(38): ' + inttostr(j div 8);

  //000..101 - 0..5
  //110 xxxx 6..21
  //111 immediate
  j := CountValues( CountValueTable, 0, 5, 3 ) +
        CountValues(CountValueTable, 6, 21, 7 ) +
        CountValues(CountValueTable, 22,-1, _bitsPerValue+3) +
        math.Min( countValueTable.Count, 22 ) * _bitsPerValue;
  s := s + #13 + #10 + '(22): ' + inttostr(j div 8);

  //000..101 - 0..5
  //110 xxx - 6..13
  //111 immediate
  j := CountValues( CountValueTable, 0, 5, 3 ) +
        CountValues(CountValueTable, 6, 13, 6 ) +
        CountValues(CountValueTable, 14,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 14 ) * _bitsPerValue;
  s := s + #13 + #10 + '(14): ' + inttostr(j div 8);

  //000..100 - 0..4
  //101 xx - 5..8
  //110 xxx - 9..16
  //111 immediate
  j := CountValues( CountValueTable, 0, 4, 3 ) +
        CountValues(CountValueTable, 5, 8, 5 ) +
        CountValues(CountValueTable, 9, 16, 6 ) +
        CountValues(CountValueTable, 17,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 17 ) * _bitsPerValue;
  s := s + #13 + #10 + '(17): ' + inttostr(j div 8);

  //000..011 - 0..3
  //100 x - 4..5
  //101 xx - 6..9
  //110 xxx - 10..17
  //111 immediate
  j := CountValues( CountValueTable, 0, 3, 3 ) +
        CountValues(CountValueTable, 4, 5, 4 ) +
        CountValues(CountValueTable, 6, 9, 5 ) +
        CountValues(CountValueTable, 10, 17, 6 ) +
        CountValues(CountValueTable, 18,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 18 ) * _bitsPerValue;
  s := s + #13 + #10 + '(18): ' + inttostr(j div 8);

  //000..010 - 0..2
  //011 x 3..4
  //100 xx 5..8
  //101 xxx 9..16
  //110 xxx 17..25
  //111 immediate
  j := CountValues( CountValueTable, 0, 2, 3 ) +
        CountValues(CountValueTable, 3, 4, 4 ) +
        CountValues(CountValueTable, 5, 8, 5 ) +
        CountValues(CountValueTable, 9, 16, 6 ) +
        CountValues(CountValueTable, 17, 24, 6 ) +
        CountValues(CountValueTable, 25,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 25 ) * _bitsPerValue;
  s := s + #13 + #10 + '(26): ' + inttostr(j div 8);

  //000..100- 0..4
  //101 x - 5..6
  //110 xx - 7..10
  //110 - immediate
  j := CountValues( CountValueTable, 0, 4, 3 ) +
        CountValues(CountValueTable, 5, 6, 4 ) +
        CountValues(CountValueTable, 7, 10, 5 ) +
        CountValues(CountValueTable, 11,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 11 ) * _bitsPerValue;
  s := s + #13 + #10 + '(11): ' + inttostr(j div 8);

  //00 - 0
  //01 x - 1..2
  //10 xx - 3..6
  //11 - immediate
  j := CountValues( CountValueTable, 0, 0, 2 ) +
        CountValues(CountValueTable, 1, 2, 3 ) +
        CountValues(CountValueTable, 3, 6, 4 ) +
        CountValues(CountValueTable, 7,-1, _bitsPerValue+2)+
        math.Min( countValueTable.Count, 7 ) * _bitsPerValue;
  s := s + #13 + #10 + '(7): ' + inttostr(j div 8);

  //0 - 1
  //100 - 1
  //101 - 2
  //110 - 3
  //111 - immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 3, 3 ) +
        CountValues(CountValueTable, 4,-1, _bitsPerValue+3)+
        math.Min( countValueTable.Count, 4 ) * _bitsPerValue;
  s := s + #13 + #10 + '(4): ' + inttostr(j div 8);

  //00..10 - 0..2
  //11 - immediate
  j := CountValues( CountValueTable, 0, 2, 2 ) +
        CountValues(CountValueTable, 3,-1, _bitsPerValue+2)+
        math.Min( countValueTable.Count, 3 ) * _bitsPerValue;
  s := s + #13 + #10 + '(3): ' + inttostr(j div 8);

  //0 - 0
  //10 - 1
  //110 - 2
  //1110 - 3
  //11110 - 4
  //111110 - 5
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5,-1, _bitsPerValue+6)+
        math.Min( countValueTable.Count, 5 ) * _bitsPerValue;
  s := s + #13 + #10 + '(5): ' + inttostr(j div 8);

  //000..010 - 0..2
  //011 x - 3..4
  //100 xx - 5..8
  //101 xxx - 9..16
  //110 xxx - 17..24
  //111 immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5, 5, 6)+
        CountValues(CountValueTable, 6,-1, _bitsPerValue+7)+
        math.Min( countValueTable.Count, 6 ) * _bitsPerValue;
  s := s + #13 + #10 + '(6): ' + inttostr(j div 8);

  //0 - 0
  //10 - 1
  //110 - 2
  //1110 - 3
  //11110 - 4
  //111110 - 5
  //1111110 - 6
  //11111110 - immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5, 5, 6)+
        CountValues(CountValueTable, 6, 6, 7)+
        CountValues(CountValueTable, 7,-1, _bitsPerValue+8)+
        math.Min( countValueTable.Count, 7 ) * _bitsPerValue;
  s := s + #13 + #10 + '(7): ' + inttostr(j div 8);

  //0 - 0
  //10 - 1
  //110 - 2
  //1110 - 3
  //11110 - 4
  //111110 - 5
  //1111110 - 6
  //11111110 - 7
  //111111110 - immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5, 5, 6)+
        CountValues(CountValueTable, 6, 6, 7)+
        CountValues(CountValueTable, 7, 7, 8)+
        CountValues(CountValueTable, 8,-1, _bitsPerValue+9)+
        math.Min( countValueTable.Count, 8 ) * _bitsPerValue;
  s := s + #13 + #10 + '(8): ' + inttostr(j div 8);

  //0 - 0
  //10 - 1
  //110 - 2
  //1110 - 3
  //11110 - 4
  //111110 - 5
  //1111110 - 6
  //11111110 - 7
  //111111110 - 8
  //1111111110 - immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5, 5, 6)+
        CountValues(CountValueTable, 6, 6, 7)+
        CountValues(CountValueTable, 7, 7, 8)+
        CountValues(CountValueTable, 8, 8, 9)+
        CountValues(CountValueTable, 9,-1, _bitsPerValue+10)+
        math.Min( countValueTable.Count, 9 ) * _bitsPerValue;
  s := s + #13 + #10 + '(9): ' + inttostr(j div 8);

  //0 - 0
  //10 - 1
  //110 - 2
  //1110 - 3
  //11110 - 4
  //111110 - 5
  //1111110 - 6
  //11111110 - 7
  //111111110 - 8
  //1111111110 - 9
  //11111111110 - immediate
  j := CountValues( CountValueTable, 0, 0, 1 ) +
        CountValues(CountValueTable, 1, 1, 2)+
        CountValues(CountValueTable, 2, 2, 3 )+
        CountValues(CountValueTable, 3, 3, 4 )+
        CountValues(CountValueTable, 4, 4, 5)+
        CountValues(CountValueTable, 5, 5, 6)+
        CountValues(CountValueTable, 6, 6, 7)+
        CountValues(CountValueTable, 7, 7, 8)+
        CountValues(CountValueTable, 8, 8, 9)+
        CountValues(CountValueTable, 9, 9, 10)+
        CountValues(CountValueTable, 10,-1, _bitsPerValue+11)+
        math.Min( countValueTable.Count, 10 ) * _bitsPerValue;
  s := s + #13 + #10 + '(10): ' + inttostr(j div 8);

  countValueTable.Destroy;

  Clipboard.AsText := s;
end;


//==============================================================================
//==============================================================================
procedure TCompressor.BuildFrequencyTable( _list : TLIst; var _countValueTable : TStringList );
var
  valueCountTable : TStringList;
  temp : TStringList;
  i : integer;
  value : integer;
  s : String;
begin

  //name:value, value:count of values
  //arr[value] = count
  //not sorted
  valueCountTable := TStringList.Create();

  //name: count, value: value
  //sorted by max count first
  //arr[count] = value
  _countValueTable := TStringList.Create();

  s := '';

  for i := 0 to _list.Count - 1 do
    begin
      value := integer( _list[ i ] );
      s := valueCountTable.Values[ intToStr( value ) ];
      if ( s = '' ) then
        begin
          s := '0';
        end;

      valueCountTable.Values[ intToStr( value ) ] := intToStr( StrToInt( s ) + 1 );
    end;

  for i := 0 to valueCountTable.Count - 1 do
    begin
      _countValueTable.values[ Format( '%05d', [ StrToInt( valueCountTable.ValueFromIndex[ i ] )] ) ] :=
        valueCountTable.Names[ i ];
    end;

  _countValueTable.Sort();

  temp := TStringList.Create();

  for i := 0 to _countValueTable.Count - 1 do
    begin
      temp.values[ _countValueTable.Names[ _countValueTable.Count - 1 - i ] ] := _countValueTable.valueFromIndex[ _countValueTable.Count - 1 - i ];
    end;

  _countValueTable.Destroy();
  _countValueTable := temp;
end;


//==============================================================================
//==============================================================================
function TCompressor.CountValues( _list : TStringList; _start, _end : integer;_bitsPerValue: integer ): integer;
var
  i: integer;
begin
  result := 0;

  if _end = -1 then _end := _list.Count-1;

  for i:=_start to _end do
  begin
    if ( i<_list.count ) then
      begin
        result := result + strToInt( _list.Names[i] );
      end;
  end;
  result := result * _bitsPerValue;
end;

//==============================================================================
//==============================================================================
//5 bits - values count in table - number of values
//16 bits - decompressed stream length
//5 * _bitsPerValue  - values
//stream... - encoded values
function TCompressor.Compress( _list : TList; _bitsPerValue : integer ) : String;
const
  ve1 : array [ 0.. 24 ] of integer =
    (
    //000..010 - 0..2
      0, 1, 2,
    //011 x 3..4
      6, 7,
    //100 xx 5..8
      16, 17, 18, 19,
    //101 xxx 9..16
      40,41,42,43,44,45,46,47,
    //110 xxx 17..24
      48,49,50,51,52,53,54,55
    );

  ve2 : array [ 0.. 24 ] of integer =
    (
    //000..010 - 0..2
      3, 3, 3,
    //011 x 3..4
      4, 4,
    //100 xx 5..8
      5, 5, 5, 5,
    //101 xxx 9..16
      6,6,6,6,6,6,6,6,
    //110 xxx 17..24
      6,6,6,6,6,6,6,6
    );

var
  i,j,k: integer;

  //name: count, value: value
  //sorted by max count first
  //arr[count] = value
  countValueTable : TStringList;

  //name: value
  //value : encode index
  //arr[value] = incode index
  encode: TStringList;

  bs : TBitWriteStream;

  s : String;
  list2 : TList;
begin
  //cp.Debug_CheckMethods( valuesList,11 );

  //000..010 - 0..2
  //011 x 3..4
  //100 xx 5..8
  //101 xxx 9..16
  //110 xxx 17..24
  //111 immediate

  BuildFrequencyTable( _list, countValueTable );
  BuildEncodeTable( countValueTable, encode );

  bs := TBitWriteStream.Create();

  bs.Write(  encode.Count, 5 );

  bs.Write(  _list.Count, 16 );

  for i := 0 to encode.count - 1 do
    begin
      bs.Write( strToInt( countValueTable.ValueFromIndex[ i ] ), _bitsPerValue );
    end;

  for i := 0 to _list.Count -1 do
  begin
    s := Format( '%05d', [ integer( _list[ i ] ) ] );
    s := encode.Values[ s ];

    if ( s = '' ) then
      begin
       j := $7; //111
       j := j shl _bitsPerValue;
       assert(( integer(_list[ i ]) shr _bitsPerValue) = 0);
       j := j or integer( _list[ i ] );
       bs.Write( j, 3 + _bitsPerValue );
     end
       else
     begin
       k := strToInt( s );
       bs.Write( ve1[ k ], ve2[ k ]);
     end;

  end;

  result := bs.GetContents();

  bs.Destroy();
  encode.Destroy();
  countValueTable.Destroy();

  //test
  list2 := Decompress( result, _bitsPerValue );
  Debug_Compare( _list, list2 );
  list2.Destroy;
end;

//==============================================================================
//==============================================================================
function TCompressor.Decompress( _data : String; _bitsPerValue : integer ) : TList;
const
  vd1 : array [ 0..6 ] of integer =
    (
      //000 - 0
      0,
      //001 - 1
      1,
      //010 - 2
      2,
      //011 x - 3..4
      3,
      //100 xx - 5..8
      5,
      //101 xxx - 9..16
      9,
      //110 xxx 17..24
      17
    );

  vd2 : array [ 0..6 ] of integer =
    (
      //000 - 0
      0,
      //001 - 1
      0,
      //010 - 2
      0,
      //011 x - 3..4
      1,
      //100 xx - 5..8
      2,
      //101 xxx - 9..16
      3,
      //110 xxx 17..24
      3
    );

var
  i,j,k : integer;
  len : integer;
  valCount : integer;
  st : TBitReadStream;
  values : array [ 0..24 ] of integer;
begin
  result := TList.Create();

  st := TBitReadStream.Create( _data );

  valCount := st.Read( 5 );
  len := st.Read( 16 );

  for  i := 0 to valCount-1 do
    begin
      values[ i ] := st.Read( _bitsPerValue );
    end;

  for i := 0 to len-1 do
    begin
      j := st.Read( 3 );

      if ( j = 7 ) then
      begin
        j := st.Read( _bitsPerValue );
        result.Add( pointer( j ) );
      end
        else
      begin
        k := vd2[ j ];
        j := vd1[ j ];

        k := st.Read( k );

        j := j + k;

        k := values[ j ];

        result.Add( pointer( k ) );
      end;
    end;

  st.Destroy();
end;


//==============================================================================
//==============================================================================
//build encode table from frequency table
procedure TCompressor.BuildEncodeTable( _countValueTable : TStringList; var _encode : TSTringList );
var
 i: integer;
begin
  _encode := TStringList.Create();

  for i := 0 to 24 do
    begin
      if ( i >= _countValueTable.Count ) then break;
      _encode.values[ Format( '%05d', [ strToInt( _countValueTable.ValueFromIndex[ i ] ) ] ) ] := intToStr( i );
    end;
end;

//==============================================================================
//==============================================================================
procedure TCompressor.Debug_Compare( _values1 : TList; _values2 : TList );
var
 i : integer;
begin
  assert( _values1.Count = _values2.Count );

  for i := 0 to _values1.Count - 1 do
    begin
      assert( _values1[ i ] = _values2[ i ] );
    end;
end;

end.
