unit WhiteNoiseGenerator;

interface
uses Windows;

///=============================================================================
///=============================================================================
type TWhiteNoiseGenerator = class
    public

      constructor Create();

      function GetValue() : BYTE;

    private

      m_nze : BYTE;
      m_t1  : BYTE;
      m_t2  : BYTE;
      m_t3  : BYTE;


  end;
implementation


///=============================================================================
///=============================================================================
constructor TWhiteNoiseGenerator.Create();
begin
  m_nze := 0;
  m_t1 := 45;
  m_t2 := 34;
  m_t3 := 53;
end;

///=============================================================================
///=============================================================================

//mov t1,nze
//andi t1,66
//breq nsj1
//cpi t1,66
//rjmp nsj2
//nsj1:
//clc
//nsj2:
//rol t2
//rol t3
//rol nze

//http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=697747

function TWhiteNoiseGenerator.GetValue() : BYTE;
var
  b: boolean;
  b1: boolean;
begin
  m_t1 := m_nze;
  m_t1 := m_t1 and 66;

  if ( m_t1 = 0 ) then b:= false else b := m_t1 < 66;

  b1:= ( m_t2 and $80 ) > 0;
  m_t2:=m_t2 shl 1;
  if (b) then m_t2:=m_t2 or 1;

  b:= (m_t3 and $80) > 0;

  m_t3:=m_t3 shl 1;
  if ( b1) then m_t3:=m_t3 or 1;

  m_nze:=m_nze shl 1;
  if b then m_nze:=m_nze or 1;

  result := m_nze;
end;

end.
