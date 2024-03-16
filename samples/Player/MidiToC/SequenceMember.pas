unit SequenceMember;

interface

//==============================================================================
//==============================================================================
type ISequenceMember = class

  //compare to other item
  // -1 - less then other item
  //0 - equals oter item
  // 1 - greater then other item
  function Compare( _rhs : ISequenceMember ) : integer; virtual; abstract;

end;


implementation

end.
