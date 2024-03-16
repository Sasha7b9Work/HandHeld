unit Sequence;

interface
uses Classes, SequenceMember;

//==============================================================================
//==============================================================================
//A sequence
//items of sequence are kept in external TList
type TSequence = class
  private

    var

    //reference to list holding items
    m_sequenceItems : TList;

    //index of first item of sequence
    m_start : integer;

    //length of sequence
    m_length : integer;


  public

    ///Constructor
    constructor Create( _start, _length : integer; _sequenceItems : TList );

    ///Get item of sequence by index
    function GetItem( index : integer ) : ISequenceMember;

    ///Items access member
    property Items[ index : Integer ] : ISequenceMember read GetItem;

    ///Number of items in sequence
    property Length : integer read m_length;


end;


implementation

//==============================================================================
//==============================================================================
constructor TSequence.Create( _start, _length : integer; _sequenceItems : TList  );
begin
  m_start := _start;
  m_length := _length;
  m_sequenceItems := _sequenceItems;
end;

//==============================================================================
//==============================================================================
function TSequence.GetItem( index : integer ): ISequenceMember;
begin
  Assert( index < m_length );
  result := m_sequenceItems[ m_start + index ];
end;


end.
