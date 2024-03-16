program MidiToC;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  WavFile in 'WavFile.pas',
  Syntezer in 'Syntezer.pas',
  MidiEventsEnumerator in 'MidiEventsEnumerator.pas',
  MidiFile in 'MidiFile.pas',
  WhiteNoiseGenerator in 'WhiteNoiseGenerator.pas',
  Compressor in 'Compressor.pas',
  SequenceMaker in 'SequenceMaker.pas',
  Sequence in 'Sequence.pas',
  SequenceMember in 'SequenceMember.pas',
  SyntezerChannelStateChange in 'SyntezerChannelStateChange.pas',
  Samples in 'Samples.pas',
  BitWriteStream in 'BitWriteStream.pas',
  BitReadStream in 'BitReadStream.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
