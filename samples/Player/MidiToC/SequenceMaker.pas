unit SequenceMaker;

interface
uses Windows, Classes, SysUtils, SequenceMember, Sequence, ClipBrd;


//==============================================================================
//==============================================================================
type TSequenceMaker = class
  private

    var

    //////////////////////////////
    //Input

    //items of original sequence
    //item should implement ISequenceMember interface
    m_items : TList;

    //////////////////////////////

    //////////////////////////////
    // Output

    // order of subsequences
    // each item is index into dictionary
    m_order : TList;

    // dictionary of sequences
    // each item is TSequence
    m_dictionary : TList;

    ///Minimum allowed length of sequence in dictionary
    m_minSequenceLength : integer;

    function GetOrderLength() : integer;
    function GetOrderItem( index : integer ) : integer;
    function GetDictionaryLength() : integer;
    function GetDictionaryItem( index : integer ) : TSequence;

  public
    constructor Create();
    destructor Destroy();

    property OrderLength : integer read GetOrderLength;
    property Order[ index : integer ] : integer read GetOrderItem;
    property DictionaryLength : integer read GetDictionaryLength;
    property DictionaryItem[ index : integer ] : TSequence read GetDictionaryItem;

    property MinSequenceLength : integer read m_minSequenceLength;

    procedure AddItem( p : ISequenceMember );

    //build sequences from original items
    procedure BuildSequences( _minSequenceLength : integer );

    //////////////////////////////

  private


    //count number of similar items in two sequences
    //i1 and i2 are starting indices
    function CountSimilarItems(
        _sequence1 : TSequence;
        _istart1 : integer;
        _sequence2 : TSequence;
        _istart2 :integer ) : integer;

    //check that created sequences are consistent with original items
    procedure CheckSequences();

end;


//==============================================================================
//==============================================================================
type TSequenceMatchItem = class
    public
      var
        sqIndex  : integer;
        index    : integer;

      constructor Create( _sqIndex : integer; _index : integer );
  end;

//==============================================================================
//==============================================================================
//this class holds a list of matches for seqence
//sq1index (index in dictionary) starting from index1
type TSequenceMatches = class

    private

      //best cost, valid after FindBest()
      m_bestConst : integer;

    public
      var

        sq1Index  : integer;
        index     : integer;

        //list of TSequenceMatchItem
        matches   : TList;

    constructor Create();

    procedure FindBest();

    function GetCost() : integer;

  end;


implementation

//==============================================================================
//==============================================================================
constructor TSequenceMatchItem.Create( _sqIndex : integer; _index : integer );
begin
  sqIndex := _sqIndex;
  index := _index;
end;

//==============================================================================
//==============================================================================
constructor TSequenceMatches.Create();
begin
  matches := TList.Create();
end;

//==============================================================================
//==============================================================================
//find best match and it's const
procedure TSequenceMatches.FindBest();
begin
end;

//==============================================================================
//==============================================================================
function TSequenceMatches.GetCost() : integer;
begin
end;

//==============================================================================
//==============================================================================
constructor TSequenceMaker.Create();
begin
  m_items := TList.Create();
  m_order := nil;
  m_dictionary := nil;

  m_minSequenceLength := 3;
end;

//==============================================================================
//==============================================================================
destructor TSequenceMaker.Destroy();
begin
  m_items.Destroy();
  if ( m_order <> nil ) then m_order.Destroy();
  if ( m_dictionary <> nil ) then m_dictionary.Destroy();
end;

//==============================================================================
//==============================================================================
function TSequenceMaker.GetOrderLength() : integer;
begin
  result := m_order.count;
end;

//==============================================================================
//==============================================================================
function TSequenceMaker.GetOrderItem( index : integer ) : integer;
begin
  result := integer( m_order.Items[ index ] );
end;

//==============================================================================
//==============================================================================
function TSequenceMaker.GetDictionaryLength() : integer;
begin
  result := m_dictionary.count;
end;

//==============================================================================
//==============================================================================
function TSequenceMaker.GetDictionaryItem( index : integer ) : TSequence;
begin
  result := TSequence( m_dictionary.Items[ index ] );
end;

//==============================================================================
//==============================================================================
procedure TSequenceMaker.AddItem( p : ISequenceMember );
begin
  m_items.Add( p );
end;

//==============================================================================
//==============================================================================
procedure TSequenceMaker.BuildSequences( _minSequenceLength : integer );
var
  len, bestLen : integer;
  sq1, sq2 : TSequence;
  index1, index2 : integer;
  s : String;
  i,j,k,l,m,n : integer;
  thisMatches : TSequenceMatches;
  bestMatches : TSequenceMatches;
begin

  //initially, we put whole melody as sequence into dictionary
  //and add id=0 into order

  m_dictionary := TList.Create();
  sq1 := TSequence.Create( 0, m_items.Count, m_items );
  m_dictionary.Add( sq1 );

  m_order := TList.Create();
  m_order.Add( pointer( 0 ) );


  CheckSequences();


  //then we divide sequences in dictionary,
  //each time selecting best division,
  //until some criteria is reached

  thisMatches := TSequenceMatches.Create();
  bestMatches := nil;

  while ( true ) do
  begin
    if ( m_order.Count = 15 ) then
      begin
        break;
      end;

    for i := 0 to DictionaryLength - 1 do
    begin
      sq1 := DictionaryItem[ i ];

      for index1 := 0 to sq1.Length - 1 do
       begin

          thisMatches.matches.Clear();
          thisMatches.sq1Index := i;
          thisMatches.index := index1;

          for j := i to DictionaryLength - 1 do
            begin

              sq2 := DictionaryItem[ j ];

              //in the same sequence, search only at the tail
              k := 0;
              if ( j = i ) then k := index1 + 1;

              for index2 := k to sq2.Length -1 do
                begin
                  l := CountSimilarItems( sq1, index1, sq2, index2 );

                  if ( l > MinSequenceLength ) then
                    begin
                      thisMatches.matches.Add( TSequenceMatchItem.Create( j, index2 ) );
                    end;
                end;
            end;

          //examine thisMatches, find best, update bestMatch

          thisMatches.FindBest();

          if  (
                ( bestMatches = nil ) or
                ( thisMatches.GetCost() > bestMatches.GetCost() )
          ) then
            begin
              bestMatches.Destroy;
              bestMatches := thisMatches;
            end;
       end;
    end;

    if ( bestMatches <> nil ) then
      begin
        //divide

        bestMatches.Destroy();
        bestMatches := nil;
      end
     else
      begin
        break;
      end;
  end;


(*
  candidates := TList.Create();

  //build a list of candidate sequences to extract to dictionary

  for i := 0 to m_items.Count-1 do
    begin
      for j := i + 1 to m_items.Count - 1 do
        begin
          l := CountSimilarItems( i, j );
          if ( l > _minSequenceLength ) then
            begin
              //add new sequence to candidates list
              sq := TSequence.Create( i, l );
              candidates.Add( sq );
            end;
        end;
    end;

  s :='';
  for i := 0 to candidates.Count-1 do
    begin
      sq := TSequence( candidates[ i ] );
      s := s+ #13 + #10 + inttostr( sq.m_start ) + ' - ' + inttostr( sq.m_length );
    end;


  clipboard.astext := s;

  candidates.Destroy();
*)

end;

//==============================================================================
//==============================================================================
function TSequenceMaker.CountSimilarItems(
        _sequence1 : TSequence;
        _istart1 : integer;
        _sequence2 : TSequence;
        _istart2 :integer ) : integer;
var
  i1, i2 : integer;
begin
  if ( _sequence1 = _sequence2 ) then
    begin
      assert( _istart1 < _istart2 );
    end;

  i1 := _istart1;
  i2 := _istart2;

  result := 0;

  while ( i1 < _sequence1.Length ) and
        ( i2 < _sequence2.Length ) and
        ( _sequence1.Items[ i1 ].Compare( _sequence2.Items[ i2 ] ) = 0 ) do
  begin
    inc( result );
    inc( i1 );
    inc( i2 );

    //do not allow overlaps
    if ( _sequence2 = _sequence1 ) then
      begin
        if ( i1 = _istart2 ) then
          begin
            break;
          end;
      end;
  end;
end;

//==============================================================================
//==============================================================================
procedure TSequenceMaker.CheckSequences();
var
  i, j, index : integer;
  sq : TSequence;
begin
  index := 0;
  for i:= 0 to m_order.Count - 1 do
    begin
      j := integer( m_order[ i ] );
      assert( j < m_dictionary.Count );
      sq := TSequence( m_dictionary[ j ] );

      for j := 0 to sq.Length - 1 do
        begin
          if ( ISequenceMember( m_items[ index ] ).Compare( sq.Items[ j ] ) <> 0 ) then
            begin
              MessageBeep( 0 );
              Assert( false );
            end;
          inc( index );
        end;
    end;
  Assert( index = m_items.Count );
end;

end.
