unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, MMSystem, CheckLst, ComCtrls, ExtCtrls, Grids, XPMan, Clipbrd,
  shellapi;

// Midi format: http://www.sonicspot.com/guide/midifiles.html

//==============================================================================
//==============================================================================
type TForm1 = class(TForm)
    Timer1: TTimer;
    OpenDialog1: TOpenDialog;
    Timer2: TTimer;
    Timer3: TTimer;
    Panel1: TPanel;
    btnLoadMidi: TButton;
    btnCreatePlayerCode: TButton;
    btnCreateMelodyCode: TButton;
    Label8: TLabel;
    CategoryPanelGroup1: TCategoryPanelGroup;
    CategoryPanel1: TCategoryPanel;
    rgOutputPins: TRadioGroup;
    StaticText1: TStaticText;
    edSamplingRate: TEdit;
    Label10: TLabel;
    CategoryPanel2: TCategoryPanel;
    cbForceSingleDrumChannel: TCheckBox;
    cbSuppressStereoNotes: TCheckBox;
    cbSingleNotePerChannel: TCheckBox;
    CategoryPanel3: TCategoryPanel;
    CheckListBox1: TCheckListBox;
    CategoryPanel4: TCategoryPanel;
    sgInstrumentPresets: TStringGrid;
    cboxInstrumentPresets: TComboBox;
    Label11: TLabel;
    sgDrumPresets: TStringGrid;
    cboxDrumPresets: TComboBox;
    Label12: TLabel;
    Bevel4: TBevel;
    Label2: TLabel;
    lbLength: TLabel;
    Label3: TLabel;
    lbMaxActiveSyntezerChannels: TLabel;
    Label4: TLabel;
    lbMaxActiveDrumchannels: TLabel;
    Label5: TLabel;
    lbMxActiveStereoNotes: TLabel;
    ProgressBar1: TProgressBar;
    edStart: TEdit;
    edEnd: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    Bevel1: TBevel;
    Bevel3: TBevel;
    Label9: TLabel;
    shNotEnoughtChannels: TShape;
    lbProcessing: TLabel;
    lbPosition: TLabel;
    Label1: TLabel;
    lbEstimatedSize: TLabel;
    SaveDialog1: TSaveDialog;
    cbWaveForm: TComboBox;
    Label14: TLabel;
    Label15: TLabel;
    lbRequirement: TLabel;
    cbPitch: TComboBox;
    Label13: TLabel;
    cbUseCompression: TCheckBox;
    cbEnableDrumsSyntezer: TCheckBox;
    btLoadSample: TButton;
    Image1: TImage;
    Label16: TLabel;
    procedure btnLoadMidiClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
    procedure OnSyntezerOptionChanged(Sender: TObject);
    procedure TrackBar1KeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure sgInstrumentPresetsSelectCell(Sender: TObject; ACol,
      ARow: Integer; var CanSelect: Boolean);
    procedure cboxInstrumentPresetsChange(Sender: TObject);
    procedure cboxDrumPresetsChange(Sender: TObject);
    procedure sgDrumPresetsSelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure edSamplingRateKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Timer2Timer(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
    procedure ProgressBar1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure edStartKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edEndKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure edStartExit(Sender: TObject);
    procedure edEndExit(Sender: TObject);
    procedure edSamplingRateExit(Sender: TObject);
    procedure btnCreatePlayerCodeClick(Sender: TObject);
    procedure btnCreateMelodyCodeClick(Sender: TObject);
    procedure cbWaveFormChange(Sender: TObject);
    procedure cbPitchChange(Sender: TObject);
    procedure cbUseCompressionClick(Sender: TObject);
    procedure cbEnableDrumsSyntezerClick(Sender: TObject);
    procedure btLoadSampleClick(Sender: TObject);
    procedure Panel1DblClick(Sender: TObject);
    procedure Label16MouseEnter(Sender: TObject);
    procedure Label16MouseLeave(Sender: TObject);
    procedure Label16Click(Sender: TObject);
  private
    { Private declarations }

    procedure PlayNextSample();
    function GetMidiChannelEnabled() : WORD;
    procedure SetMidiChannelPresent( _value : WORD );
    procedure InitControlsForNewMidi();
    procedure CreateSyntezer( _bRestartPosition : Boolean );
    procedure LoadInstrumentPresets();
    procedure CopyUsedInstrumentsToGrid();
    function GetChannelsCount() : integer;
    procedure ScheduleRecreateSyntezer();
    procedure ScheduleRecreateSoundSample();
    function GetStartPosition() : integer;
    function GetEndPosition() : integer;
    procedure ParseStartPosition( _bForce : boolean );
    procedure ParseEndPosition();
    function GetPlayerFrequency() : DWORD;
    procedure UpdateMelodySize();
    procedure UpdateOutputPinsBox();
    procedure SaveWAV();

    var
      m_bIgnoreChangeMessages : Boolean;
  end;

var
  Form1: TForm1;

implementation
uses Wavfile, MidiFile, Syntezer, Samples;

{$R *.dfm}

const
  SPAN_LENGTH = 40;

const
  PredefinedInstrument : array [ 0 .. 15 ] of TSyntezerInstrumentPreset =
    (
      ( m_eInstrumentKind: EIK_DISABLED; m_noteDuration: 0 ),

      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 1000 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 700 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 500 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 200 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 100 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 70 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 40 ),
      ( m_eInstrumentKind: EIK_SYNTHWAVE; m_noteDuration: 20 ),

      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 200 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 100 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 70 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 40 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 20 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 15 ),
      ( m_eInstrumentKind: EIK_WHITENOISE; m_noteDuration: 10 )

    );

var
  mf : TMidiFile;
  sn : TSyntezer;
  soundBuffer : array of byte;
  timerCounter : integer;
  startPosition, endPosition : integer;

  instrumentPresets : array [0..127] of TSyntezerInstrumentPreset;
  drumPresets : array [0..127] of TSyntezerInstrumentPreset;

//==============================================================================
//==============================================================================
function InstrumentPresetToString( _preset : TSyntezerInstrumentPreset ) : String;
begin
  case _preset.m_eInstrumentKind of
    EIK_DISABLED : result := 'Disabled';
    EIK_SYNTHWAVE : result := 'Synth wave';
    EIK_WHITENOISE : result := 'White noise';
  end;

  if ( _preset.m_eInstrumentKind <> EIK_DISABLED ) then
    begin
      if _preset.m_noteDuration = 1000 then
        begin
          result := result + ', 1 sec';
        end
          else
        begin
          result := result + ', ' + intToStr( _preset.m_noteDuration ) + ' ms';
        end;
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.FormCreate(Sender: TObject);
var
  i : integer;
begin
  sn := nil;
  mf := nil;
  m_bIgnoreChangeMessages := false;

  LoadInstrumentPresets();

  sgInstrumentPresets.ColWidths[ 0 ] := 60;
  sgInstrumentPresets.ColWidths[ 1 ] := sgInstrumentPresets.Width - 60 - 4;
  sgInstrumentPresets.Cells[ 0, 0 ] := 'Number';
  sgInstrumentPresets.Cells[ 1, 0 ] := 'Preset';

  sgDrumPresets.ColWidths[ 0 ] := 60;
  sgDrumPresets.ColWidths[ 1 ] := sgDrumPresets.Width - 60 - 4;
  sgDrumPresets.Cells[ 0, 0 ] := 'Number';
  sgDrumPresets.Cells[ 1, 0 ] := 'Preset';

  for i := 0 to high ( PredefinedInstrument ) do
    begin
      cboxInstrumentPresets.Items.Add( InstrumentPresetToString( PredefinedInstrument[ i ] ) );
      cboxDrumPresets.Items.Add( InstrumentPresetToString( PredefinedInstrument[ i ] ) );
    end;

  UpdateOutputPinsBox();
end;

//==============================================================================
//==============================================================================
//User clicked "Load midi" button
procedure TForm1.btnLoadMidiClick(Sender: TObject);
begin
  timer1.Enabled := false;

  if ( mf <> nil)then
  begin
    sn.Destroy;
    mf.Destroy;
    mf := nil;
    sn:= nil;
    btnCreatePlayerCode.Enabled := false;
    btnCreateMelodyCode.Enabled := false;
  end;

  InitControlsForNewMidi();

  OpenDialog1.Title := 'Select MIDI file';
  OpenDialog1.FileName := '';
  OpenDialog1.Filter := 'Midi Files|*.mid;*.midi';
  OpenDialog1.FilterIndex := 0;

  if ( OpenDialog1.Execute() = false) then exit;
 // OpenDialog1.FileName := 'joinme.mid';

  Caption := 'hxMidiPlayer - ' + OpenDialog1.FileName;

  mf := TMidifile.Create();
  mf.filename := OpenDialog1.FileName;

  mf.ReadFile();

  CreateSyntezer( true );

  btnCreatePlayerCode.Enabled := true;
  btnCreateMelodyCode.Enabled := true;
end;

//==============================================================================
//==============================================================================
//User clicked on one of the syntezer options control
procedure TForm1.OnSyntezerOptionChanged(Sender: TObject);
begin
  if ( m_bIgnoreChangeMessages ) then exit;
  UpdateOutputPinsBox();
  ScheduleRecreateSyntezer();
end;

//==============================================================================
//==============================================================================
procedure TForm1.CreateSyntezer( _bRestartPosition : Boolean );
begin
  if ( mf = nil ) then exit;

  if ( sn <> nil ) then
    begin
      sn.Destroy();
    end;

  sn := TSyntezer.Create(
                          mf,
                          GetChannelsCount(),
                          EWAVEFORMKIND( cbWaveForm.ItemIndex ),
                          24 - cbPitch.ItemIndex,
                          cbSingleNotePerChannel.Checked,
                          cbSuppressStereoNotes.Checked,
                          cbForceSingleDrumChannel.Checked,
                          GetMidiChannelEnabled(),
                          cbEnableDrumsSyntezer.Checked,
                          instrumentPresets,
                          drumPresets
                        );

  lbLength.Caption :=inttostr( sn.GetMelodyLength() ) + ' ms';
  lbMaxActiveSyntezerChannels.Caption := inttostr( sn.GetMaxActiveChannels() );
  lbMaxActiveDrumchannels.Caption := inttostr( sn.GetMaxActiveDrumChannels() );
  lbMxActiveStereoNotes.Caption := inttostr( sn.GetMaxActiveStereoNotes() );

  if sn.GetNotEnoughtChannels() then shNotEnoughtChannels.Brush.Color := clRed
                                else shNotEnoughtChannels.Brush.Color := clGreen;

  if ( _bRestartPosition ) then
    begin
      m_bIgnoreChangeMessages := true;

      startPosition := 0;
      endPosition := sn.GetMelodyLength();

      edStart.Text := '0';
      edEnd.Text := intToStr( sn.GetMelodyLength() );

      ProgressBar1.Position := 0;
      ProgressBar1.Max := sn.GetMelodyLength;

      m_bIgnoreChangeMessages := false;

      CopyUsedInstrumentsToGrid();
    end;

  m_bIgnoreChangeMessages := true;
  SetMidiChannelPresent( sn.GetMidiChannelPresent() );
  m_bIgnoreChangeMessages := false;

  PlayNextSample();
end;

//==============================================================================
//==============================================================================
procedure TForm1.edEndExit(Sender: TObject);
begin
  ParseEndPosition();
end;

//==============================================================================
//==============================================================================
procedure TForm1.edEndKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if ( key = 13 ) then
    begin
      ParseEndPosition();
      key := 0;
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.edSamplingRateExit(Sender: TObject);
begin
  PlayNextSample();
end;

procedure TForm1.edSamplingRateKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if ( key = 13 ) then
    begin
      key := 0;
      PlayNextSample();
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.edStartExit(Sender: TObject);
begin
  ParseStartPosition( false );
end;

//==============================================================================
//==============================================================================
procedure TForm1.edStartKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if ( key = 13 ) then
    begin
      ParseStartPosition( true );
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.PlayNextSample();
var
  startTime : DWORD;
  freq : DWORD;
begin
  if ( mf = nil ) then exit;

  lbProcessing.Visible := true;
  Update();

  m_bIgnoreChangeMessages := true;

  if ( ProgressBar1.Position >= endPosition ) then
    begin
      ProgressBar1.Position := startPosition;
    end;

  timer1.Enabled := false;
  sndPlaySound(nil, 0); // Stops the sound

  startTime := ProgressBar1.Position;

  freq := GetPlayerFrequency();

  SetLength( soundBuffer, 44 + SPAN_LENGTH * freq );

  CreateWavHeader8BitMono( @soundBuffer[0], SPAN_LENGTH * freq, freq );

  sn.CreateSampleRT( startTime, SPAN_LENGTH, freq, @soundBuffer[44] );

  sndPlaySound( @(soundBuffer[0]), SND_MEMORY Or SND_NODEFAULT Or SND_ASYNC );

  timer1.Interval := SPAN_LENGTH * 10;
  timer1.Enabled := true;
  timerCounter := 0;

  lbProcessing.Visible := false;

  m_bIgnoreChangeMessages := false;
  UpdateMelodySize();
end;


//==============================================================================
//==============================================================================
//Use clicked on progressbar
procedure TForm1.ProgressBar1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  position : single;
begin
  position := X / ( ProgressBar1.Width - 4 );
  if position < 0 then position := 0;
  if position > 1 then position := 1;
  position := ProgressBar1.Min + position * ( ProgressBar1.Max - ProgressBar1.Min );
  ProgressBar1.Position := Round( Position );
  ScheduleRecreateSoundSample();
end;

//==============================================================================
//==============================================================================
procedure TForm1.Timer1Timer(Sender: TObject);
begin
  m_bIgnoreChangeMessages := true;

  ProgressBar1.Position := ProgressBar1.Position + SPAN_LENGTH * 10;

  if ( ProgressBar1.Position >= endPosition ) then
    begin
      PlayNextSample();
    end;

  lbPosition.Caption := FormatFloat( '0.000', ProgressBar1.Position / 1000 );

  m_bIgnoreChangeMessages := false;

  inc( timercounter );
  if ( timerCounter = 100 ) then
    begin
      PlayNextSample();
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.TrackBar1Change(Sender: TObject);
begin
  if ( m_bIgnoreChangeMessages ) then exit;

  ScheduleRecreateSoundSample();
end;

//==============================================================================
//==============================================================================
procedure TForm1.TrackBar1KeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
end;

//==============================================================================
//==============================================================================
function TForm1.GetMidiChannelEnabled() : WORD;
var
  i : integer;
begin
  result := 0;

  for i := 0 to 15 do
    if ( CheckListBox1.Checked[ i ] ) then
      begin
        result := result or ( 1 shl i );
      end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.SetMidiChannelPresent( _value : WORD );
var
 i: integer;
begin
  for i:=0 to 15 do
    begin
      if ( ( 1 shl i ) and _value ) = 0 then
        begin
          CheckListBox1.State[ i ] := cbGrayed;
        end
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.sgDrumPresetsSelectCell(Sender: TObject; ACol, ARow: Integer;
  var CanSelect: Boolean);
var
  R: TRect;
  i : integer;
begin
  if ((ACol = 1) and (ARow > 0)) then
  begin
    {Ширина и положение ComboBox должно соответствовать ячейке StringGrid}
    R := sgDrumPresets.CellRect(ACol, ARow);
    R.Left := R.Left + sgDrumPresets.Left;
    R.Right := R.Right + sgDrumPresets.Left;
    R.Top := R.Top + sgDrumPresets.Top;
    R.Bottom := R.Bottom + sgDrumPresets.Top;
    cboxDrumPresets.Left := R.Left + 1;
    cboxDrumPresets.Top := R.Top + 1;
    cboxDrumPresets.Width := (R.Right + 1) - R.Left;
    cboxDrumPresets.Height := (R.Bottom + 1) - R.Top; {Покажем combobox}
    cboxDrumPresets.Visible := True;

    m_bIgnoreChangeMessages := true;
    for i := 0 to high( PredefinedInstrument ) do
      if ( sgDrumPresets.Cells[ 1 , ARow ] = InstrumentPresetToString( PredefinedInstrument [ i ] ) ) then
        begin
          cboxDrumPresets.ItemIndex := i;
          break;
        end;
    m_bIgnoreChangeMessages := false;

    cboxDrumPresets.SetFocus;
  end;
  CanSelect := True;
end;

//==============================================================================
//==============================================================================
procedure TForm1.sgInstrumentPresetsSelectCell(Sender: TObject; ACol,
  ARow: Integer; var CanSelect: Boolean);
var
  R: TRect;
  i: integer;
begin
  if ((ACol = 1) and (ARow > 0)) then
  begin
    {Ширина и положение ComboBox должно соответствовать ячейке StringGrid}
    R := sgInstrumentPresets.CellRect(ACol, ARow);
    R.Left := R.Left + sgInstrumentPresets.Left;
    R.Right := R.Right + sgInstrumentPresets.Left;
    R.Top := R.Top + sgInstrumentPresets.Top;
    R.Bottom := R.Bottom + sgInstrumentPresets.Top;
    cboxInstrumentPresets.Left := R.Left + 1;
    cboxInstrumentPresets.Top := R.Top + 1;
    cboxInstrumentPresets.Width := (R.Right + 1) - R.Left;
    cboxInstrumentPresets.Height := (R.Bottom + 1) - R.Top; {Покажем combobox}
    cboxInstrumentPresets.Visible := True;

    m_bIgnoreChangeMessages := true;
    for i := 0 to high( PredefinedInstrument ) do
      if ( sgInstrumentPresets.Cells[ 1 , ARow ] = InstrumentPresetToString( PredefinedInstrument [ i ] ) ) then
        begin
          cboxInstrumentPresets.ItemIndex := i;
          break;
        end;

    m_bIgnoreChangeMessages := false;

    cboxInstrumentPresets.SetFocus;
  end;
  CanSelect := True;
end;

//==============================================================================
//==============================================================================
procedure TForm1.InitControlsForNewMidi();
var
 i: integer;
begin
  for i:=0 to 15 do
    begin
      CheckListBox1.State[ i ] := cbChecked;
    end;
end;

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
procedure TForm1.Label16Click(Sender: TObject);
begin
  ShellExecute( 0, 'Open', 'http://www.deep-shadows.com/hax/', '', nil, SW_SHOWNORMAL);
end;

//==============================================================================
//==============================================================================
procedure TForm1.Label16MouseEnter(Sender: TObject);
begin
 label1.Font.Style := [];
end;

//==============================================================================
//==============================================================================
procedure TForm1.Label16MouseLeave(Sender: TObject);
begin
 label1.Font.Style := [];
end;

//==============================================================================
//==============================================================================
procedure TForm1.LoadInstrumentPresets();
var
  i : integer;
begin
  for i := 0 to 127 do
    begin
      instrumentPresets[ i ].m_eInstrumentKind := EIK_SYNTHWAVE;
      instrumentPresets[ i ].m_noteDuration := 1000;

      drumPresets[ i ].m_eInstrumentKind := EIK_WHITENOISE;
      drumPresets[ i ].m_noteDuration := 15;
    end;

  drumPresets[ 35 ].m_noteDuration := 70;
  drumPresets[ 36 ].m_noteDuration := 70;
  drumPresets[ 38 ].m_noteDuration := 70;
  drumPresets[ 40 ].m_noteDuration := 100;
  drumPresets[ 46 ].m_noteDuration := 70;
  drumPresets[ 49 ].m_noteDuration := 70;
  drumPresets[ 52 ].m_noteDuration := 70;
end;

//==============================================================================
//==============================================================================
procedure TForm1.cboxInstrumentPresetsChange(Sender: TObject);
var
  instrumentNumber : integer;
  preset : TSyntezerInstrumentPreset;
begin
  if ( m_bIgnoreChangeMessages ) then exit;

  {Перебросим выбранное в значение из ComboBox в grid}

  instrumentNumber := strtoInt( sgInstrumentPresets.Cells[ 0 , sgInstrumentPresets.Row ] );

  preset := PredefinedInstrument[ cboxInstrumentPresets.ItemIndex ];

  instrumentPresets[ instrumentNumber ] := preset;

  sgInstrumentPresets.Cells[sgInstrumentPresets.Col, sgInstrumentPresets.Row] := InstrumentPresetToString( preset );
  cboxInstrumentPresets.Visible := False;
  sgInstrumentPresets.SetFocus();
  PostMessage(sgInstrumentPresets.Handle, CB_SHOWDROPDOWN, Integer(True), 0);

  CreateSyntezer( false );
end;

procedure TForm1.cbPitchChange(Sender: TObject);
begin
  ScheduleRecreateSyntezer();
end;

//==============================================================================
//==============================================================================
procedure TForm1.cbUseCompressionClick(Sender: TObject);
begin
  if ( m_bIgnoreChangeMessages ) then exit;

  UpdateMelodySize();
end;

//==============================================================================
//==============================================================================
procedure TForm1.UpdateOutputPinsBox();
begin
  if ( cbWaveForm.ItemIndex = 0 ) then
    begin
      case rgOutputPins.ItemIndex of
        0:  lbRequirement.Caption := 'Required: 1 pin or PWM';
        1:  lbRequirement.Caption := 'Required: 2 pins or PWM';
        2:  lbRequirement.Caption := 'Required: 2 pins or PWM';
        3:  lbRequirement.Caption := 'Required: 3 pins or PWM';
        4:  lbRequirement.Caption := 'Required: 3 pins or PWM';
        5:  lbRequirement.Caption := 'Required: 3 pins or PWM';
        6:  lbRequirement.Caption := 'Required: 3 pins or PWM';
        7:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        8:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        9:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        10:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        11:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        12:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        13:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        14:  lbRequirement.Caption := 'Required: 4 pins or PWM';
        15:  lbRequirement.Caption := 'Required: 4 pins or PWM';
      end;
    end
      else
    begin
      lbRequirement.Caption := 'Required: 5+ pins or PWM';
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.cbWaveFormChange(Sender: TObject);
begin
  if ( m_bIgnoreChangeMessages ) then exit;
  ScheduleRecreateSyntezer();

  UpdateOutputPinsBox();

  btLoadSample.Enabled := cbWaveForm.ItemIndex = cbWaveForm.items.Count - 1;
end;

//==============================================================================
//==============================================================================
procedure TForm1.btnCreatePlayerCodeClick(Sender: TObject);
begin
  sn.CreatePlayerConfig(  GetPlayerFrequency(), cbUseCompression.checked );
  ShowMessage( 'Player config copied to clipboard' );
end;

//==============================================================================
//==============================================================================
procedure TForm1.btLoadSampleClick(Sender: TObject);
begin
  OpenDialog1.Title := 'Select WAV file';
  OpenDialog1.FileName := '';
  OpenDialog1.Filter := 'WAVE Files|*.wav';
  OpenDialog1.FilterIndex := 0;

  if ( OpenDialog1.Execute() = false) then exit;

  loadsample( OpenDialog1.FileName );

  ScheduleRecreateSyntezer();
end;

procedure TForm1.btnCreateMelodyCodeClick(Sender: TObject);
var
  code : String;
  codesize : integer;
begin
  if mf = nil then exit;
  sn.CreateMelodyCode( startPosition, endPosition, GetPlayerFrequency(), cbUseCompression.Checked, false, code, codesize );
  Clipboard.AsText := code;
  ShowMessage( 'Melody code copied to Clipboard' );
end;

//==============================================================================
//==============================================================================
procedure TForm1.cbEnableDrumsSyntezerClick(Sender: TObject);
begin
  ScheduleRecreateSyntezer();
end;

//==============================================================================
//==============================================================================
procedure TForm1.cboxDrumPresetsChange(Sender: TObject);
var
  instrumentNumber : integer;
  preset : TSyntezerInstrumentPreset;
begin
  if ( m_bIgnoreChangeMessages ) then exit;

  {Перебросим выбранное в значение из ComboBox в grid}

  instrumentNumber := strtoInt( sgDrumPresets.Cells[ 0 , sgDrumPresets.Row ] );

  preset := PredefinedInstrument[ cboxDrumPresets.ItemIndex ];

  drumPresets[ instrumentNumber ] := preset;

  sgDrumPresets.Cells[sgDrumPresets.Col, sgDrumPresets.Row] := InstrumentPresetToString( preset );
  cboxDrumPresets.Visible := False;
  sgDrumPresets.SetFocus();
  PostMessage(sgDrumPresets.Handle, CB_SHOWDROPDOWN, Integer(True), 0);

  CreateSyntezer( false );
end;

//==============================================================================
//==============================================================================
//Copy instuments and drums used in current melody to string grids
procedure TForm1.CopyUsedInstrumentsToGrid();
var
  i : integer;
  count : integer;
begin
  count := 0;
  for i := 0 to 127 do
    if ( sn.GetInstrumentUsed( i ) ) then
      inc( count );

  sgInstrumentPresets.RowCount := count + 1;

  count := 0;
  for i := 0 to 127 do
    if ( sn.GetInstrumentUsed( i ) ) then
      begin
        sgInstrumentPresets.Cells[ 0, count + 1 ] := inttostr( i );
        sgInstrumentPresets.Cells[ 1, count + 1 ] := InstrumentPresetToString( instrumentPresets[ i ]);

        inc( count );
      end;

  count := 0;
  for i := 0 to 127 do
    if ( sn.GetDrumUsed( i ) ) then
      inc( count );

  sgDrumPresets.RowCount := count + 1;

  count := 0;
  for i := 0 to 127 do
    if ( sn.GetDrumUsed( i ) ) then
      begin
        sgDrumPresets.Cells[ 0, count + 1 ] := inttostr( i );
        sgDrumPresets.Cells[ 1, count + 1 ] := InstrumentPresetToString( drumPresets[ i ]);

        inc( count );
      end;

end;

//==============================================================================
//==============================================================================
//get number of channels for player
function TForm1.GetChannelsCount(): integer;
begin
  result := rgOutputPins.itemIndex + 1;
end;

//==============================================================================
//==============================================================================
//Schedule recreate syntezer in 50 ms
//Used to gather multiple optins changes
procedure TForm1.ScheduleRecreateSyntezer();
begin
  Timer2.Interval:=50;
  Timer2.Enabled := true;
end;

//==============================================================================
//==============================================================================
//Delayed procedure call. Recretae syntezer with new options.
procedure TForm1.Timer2Timer(Sender: TObject);
begin
  Timer2.Enabled := false;
  CreateSyntezer( false );
end;

//==============================================================================
//==============================================================================
//Schedule recreate syntezer in 50 ms
//Used to gather multiple optins changes
procedure TForm1.ScheduleRecreateSoundSample();
begin
  Timer3.Interval:=50;
  Timer3.Enabled := true;
end;

//==============================================================================
//==============================================================================
//Delayed procedure call. Recretae sound sample with current options
procedure TForm1.Timer3Timer(Sender: TObject);
begin
  Timer3.Enabled := false;
 PlayNextSample();
end;

//==============================================================================
//==============================================================================
function TForm1.GetStartPosition() : integer;
var
  i : integer;
begin
  val( edStart.Text, result, i );
  if result < 0 then result := 0;
end;

//==============================================================================
//==============================================================================
function TForm1.GetEndPosition() : integer;
var
  i : integer;
begin
  val( edEnd.Text, result, i );
  if result < GetStartPosition() + 1000 then result := GetStartPosition() + 1000;
end;

//==============================================================================
//==============================================================================
procedure TForm1.ParseStartPosition( _bForce : boolean );
var
  oldValue : integer;
begin
  oldValue := startPosition;
  startPosition := GetStartPosition();

  if (inttostr(startPosition) <> edStart.Text) then
    begin
      edStart.Text := inttostr( startPosition );
    end;

  if ( oldvalue <> startPosition ) or _bForce then
    begin
      ProgressBar1.Position := startPosition;
      PlayNextSample();
    end;
end;

//==============================================================================
//==============================================================================
procedure TForm1.SaveWAV();
var
  startTime : DWORD;
  freq : DWORD;
  f: file;
  soundBuffer1 : array of byte;
  len : DWORD;
begin
  if ( sn = nil ) then
  begin
    exit;
  end;

  SaveDialog1.FileName := OpenDialog1.FileName + '_W' +
    IntToStr( cbWaveForm.ItemIndex ) + '.wav';

  if ( SaveDialog1.Execute() = false ) then
  begin
    exit;
  end;

  freq := GetPlayerFrequency();

  len := ( ProgressBar1.Max + 999 ) div 1000;

  SetLength( soundBuffer1, 44 + len * freq );

  CreateWavHeader8BitMono( @soundBuffer1[0], len * freq, freq );

  sn.CreateSampleRT( 0, len, freq, @soundBuffer1[44] );

  assignFile( f, SaveDialog1.FileName );
  rewrite( f, 1 );

  blockWrite( f, soundBuffer1[0], length( soundBuffer1 ) );

  closeFile( f );

end;

//==============================================================================
//==============================================================================
procedure TForm1.Panel1DblClick(Sender: TObject);
begin
  if GetKeyState(VK_SHIFT) <> 0 then
  begin
    saveWav();
  end;

end;

procedure TForm1.ParseEndPosition();
begin
  endPosition := GetEndPosition();

  if (inttostr(endPosition) <> edEnd.Text) then
    begin
      edEnd.Text := inttostr( endPosition );
    end;

 UpdateMelodySize();
end;

//==============================================================================
//==============================================================================
function TForm1.GetPlayerFrequency() : DWORD;
var
  i : integer;
begin
  val( edSamplingRate.Text, result, i );

  if ( result < 5000) or ( result > 65535 ) then
    begin
      result := 44100;
      edSamplingRate.Text := '44100';
    end;
end;

procedure TForm1.UpdateMelodySize;
var
  codeSize: Integer;
  code: string;
begin
  if ( sn = nil ) then
  begin
    exit;
  end;

  sn.CreateMelodyCode(startPosition, endPosition, GetPlayerFrequency, cbUseCompression.Checked, true, code, codesize);
  if ( cbWaveForm.ItemIndex = integer( EWK_SAMPLE ) ) then
  begin
    lbEstimatedSize.Caption := IntToStr(codeSize) + '+' + IntToStr( sample_length );
  end
  else
  begin
    lbEstimatedSize.Caption := IntToStr(codeSize);
  end;
end;

end.

