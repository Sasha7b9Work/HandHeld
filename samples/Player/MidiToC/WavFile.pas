unit WavFile;
//https://ccrma.stanford.edu/courses/422/projects/WaveFormat/

interface
uses windows;

procedure CreateWavHeader8BitMono(
                                  p : pointer;  //to buffer 44 bytes
                                  samplesCount: integer;
                                  samplingRate: integer
                                );


procedure CreateWavFile8BitMono(
                                  const fileName : String;
                                  p : pointer;
                                  samplesCount: integer;
                                  samplingRate: integer
                                );

implementation


//==============================================================================
//==============================================================================
procedure CreateWavHeader8BitMono(
                                  p : pointer;
                                  samplesCount: integer;
                                  samplingRate: integer
                                );
const
 headerData: array [0..43] of byte =
  ( $52, $49, $46, $46,   //0: RIFF
    0,0,0,0,              //4: chunk size = file size - 8
    $57, $41, $56, $45,   //8: WAVE
    $66, $6d, $74, $20,   //12: fmt_
    $10, $00, $00, $00,   //16: subchunk size = 10
    $01, $00, $01, $00,   //20: PCM 1 channels
    $22, $56, $00, $00,   //24: sample rate,
    $88, $58, $01, $00,   //28: byterate,
    $01, $00,             //32: block allign
    $08, $00,             //34: bits per sample
    $64, $61, $74, $61,   //36: data
    $00, $08, $00, $00    //40: subchunk size,
    );

var
  header: array [0..43] of byte;
  i : integer;
  d: DWORD;
begin
  for i := 0 to 44 - 1 do
  begin
    header[i] := headerData[i];
  end;

  d := samplesCount + 36;
  header[4] :=  d and 255;
  header[5] := (d shr 8) and 255;
  header[6] := (d shr 16) and 255;
  header[7] := (d shr 24) and 255;

  header[24] := samplingRate and 255;
  header[25] := (samplingRate shr 8) and 255;
  header[26] := (samplingRate shr 16) and 255;
  header[27] := (samplingRate shr 24) and 255;

  header[28] := samplingRate and 255;
  header[29] := (samplingRate shr 8) and 255;
  header[30] := (samplingRate shr 16) and 255;
  header[31] := (samplingRate shr 24) and 255;

  header[40] := samplesCount and 255;
  header[41] := (samplesCount shr 8) and 255;
  header[42] := (samplesCount shr 16) and 255;
  header[43] := (samplesCount shr 24) and 255;

  move( header, p^, 44 );
end;


//==============================================================================
//==============================================================================
procedure CreateWavFile8BitMono(
                                  const fileName : String;
                                  p : pointer;
                                  samplesCount: integer;
                                  samplingRate: integer
                                );
var
  header: array [0..43] of byte;
  f: file;
begin
  CreateWavHeader8BitMono( @header[0], samplesCount, samplingRate );

  assignfile( f, fileName );
  rewrite( f, 1 );
  blockwrite(f, header, 44 );
  blockwrite(f, p^, samplescount );
  closeFile(f);
end;

end.
