unit Samples;

interface

var
  sample_length : integer = 0;
  sample_data: array of byte;

function loadSample( _filename : String ) : Boolean;

function GetSampleCode( _channelsCount : integer ) : String;

implementation
uses SysUtils;


const DUMP___SIZE = 6724;

const sampleData : Array [ 0..DUMP___SIZE - 1 ] of byte = (
$52, $49, $46, $46, $3c, $1a, $00, $00, $57, $41, $56, $45, $66, $6d, $74, $20,
$10, $00, $00, $00, $01, $00, $01, $00, $9a, $20, $00, $00, $9a, $20, $00, $00,
$01, $00, $08, $00, $64, $61, $74, $61, $18, $1a, $00, $00, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $7f, $80, $80, $80, $80, $80, $80, $7f, $7f, $7f, $7e, $7e,
$80, $80, $80, $7f, $7e, $7d, $7e, $7e, $80, $7f, $80, $7e, $7c, $80, $85, $86,
$7f, $7a, $7f, $7e, $7d, $84, $89, $85, $85, $84, $86, $7b, $78, $77, $87, $8f,
$8e, $86, $81, $7b, $7e, $83, $7a, $71, $61, $a3, $a7, $91, $80, $57, $60, $81,
$51, $6c, $6f, $f5, $b7, $4c, $1a, $37, $83, $8e, $b1, $d8, $c4, $8a, $58, $46,
$1c, $33, $75, $b2, $e9, $e5, $9f, $48, $2a, $3d, $5d, $97, $ac, $bb, $a4, $7c,
$69, $60, $5d, $78, $aa, $b1, $7c, $67, $57, $6c, $88, $9e, $c0, $a4, $62, $4b,
$52, $66, $83, $b1, $ce, $b2, $61, $32, $43, $5d, $87, $be, $d8, $b5, $6d, $3a,
$34, $4e, $77, $b1, $e1, $bc, $78, $4b, $3e, $50, $6e, $a3, $cb, $b2, $75, $55,
$55, $5c, $75, $a3, $be, $a7, $73, $51, $4f, $5d, $81, $b0, $c7, $a7, $6c, $4a,
$48, $5b, $84, $b6, $ca, $ae, $70, $48, $48, $55, $7d, $b3, $ce, $b3, $74, $4b,
$47, $56, $7a, $ae, $c7, $aa, $75, $54, $4e, $59, $7b, $ae, $c3, $a6, $6f, $4c,
$4d, $5c, $83, $b1, $c3, $a7, $6c, $4a, $4b, $5b, $83, $b2, $c3, $a5, $6d, $4a,
$4b, $5d, $84, $b5, $c5, $a4, $69, $46, $48, $5d, $88, $b9, $cb, $a9, $67, $45,
$48, $59, $85, $b9, $ca, $a9, $6e, $4d, $4e, $56, $7a, $af, $c6, $aa, $71, $56,
$54, $5d, $82, $ab, $ba, $9c, $6a, $58, $5b, $69, $89, $af, $b8, $91, $60, $50,
$57, $6a, $91, $ba, $c1, $94, $59, $45, $4d, $65, $92, $c0, $c6, $98, $5e, $49,
$4d, $5f, $89, $b7, $c3, $99, $64, $51, $54, $64, $8c, $b1, $b7, $93, $62, $51,
$58, $6b, $90, $b4, $b7, $8d, $61, $51, $56, $69, $8f, $b7, $bb, $93, $63, $52,
$53, $64, $8c, $b3, $bb, $94, $67, $58, $58, $65, $88, $ab, $b6, $94, $68, $5a,
$5c, $6a, $8a, $ad, $b1, $8c, $66, $5a, $5f, $6e, $8d, $b0, $b2, $8c, $62, $56,
$5c, $6d, $94, $b4, $b3, $8b, $5e, $54, $5a, $6c, $92, $b6, $b8, $8d, $60, $52,
$56, $69, $94, $b8, $b7, $8b, $60, $53, $56, $69, $93, $b9, $b8, $8d, $60, $53,
$55, $68, $93, $b7, $b7, $8d, $62, $55, $57, $69, $93, $b6, $b4, $8a, $5f, $53,
$57, $6b, $98, $ba, $b4, $89, $5f, $52, $54, $6a, $97, $b7, $b3, $8a, $63, $56,
$58, $6c, $93, $b2, $ae, $86, $60, $58, $5e, $73, $9a, $b3, $aa, $7f, $5a, $54,
$5e, $78, $a0, $b9, $aa, $7e, $59, $52, $59, $74, $9f, $bb, $af, $81, $5b, $52,
$59, $73, $9c, $b6, $ac, $81, $5d, $57, $5b, $75, $9c, $b4, $a9, $7d, $5c, $57,
$60, $79, $9e, $b6, $a5, $79, $5b, $56, $5f, $78, $a1, $ba, $aa, $7a, $59, $54,
$5b, $76, $9f, $b8, $ab, $7e, $60, $59, $5b, $74, $9a, $b3, $a6, $7c, $61, $5b,
$61, $7a, $9c, $b1, $a1, $79, $5d, $59, $63, $7c, $a1, $b3, $a1, $77, $5b, $58,
$62, $7e, $a3, $b3, $a3, $77, $5a, $57, $61, $7f, $a5, $b7, $a2, $74, $59, $56,
$61, $7f, $a5, $b8, $a3, $77, $5a, $56, $60, $7d, $a4, $b7, $a3, $76, $59, $57,
$62, $7f, $a5, $b5, $9f, $73, $59, $56, $61, $81, $a8, $b6, $9e, $73, $57, $55,
$60, $80, $a8, $b5, $9f, $74, $59, $55, $5e, $7f, $a6, $b3, $9d, $72, $59, $59,
$64, $83, $a5, $b1, $98, $70, $5a, $5b, $67, $87, $a9, $b2, $96, $6b, $55, $59,
$6a, $8d, $af, $b6, $97, $69, $51, $54, $65, $8a, $b3, $bb, $9d, $6d, $53, $52,
$60, $85, $ad, $b6, $9d, $73, $59, $56, $63, $86, $ab, $b4, $97, $6d, $58, $59,
$67, $89, $ac, $b3, $96, $6c, $57, $57, $66, $88, $ac, $b3, $96, $6d, $58, $58,
$65, $86, $a9, $b0, $93, $6c, $5a, $5b, $69, $89, $a9, $ac, $8e, $69, $5b, $5f,
$6e, $8d, $ab, $ab, $8b, $66, $57, $5d, $71, $92, $b1, $af, $8a, $64, $55, $59,
$6f, $95, $b4, $b3, $8e, $65, $55, $58, $6b, $91, $b1, $b3, $90, $68, $58, $5b,
$6d, $8f, $ad, $ae, $8d, $66, $58, $5c, $6f, $92, $af, $ae, $8a, $64, $56, $5c,
$6f, $91, $ae, $ad, $8a, $64, $58, $5c, $6f, $92, $ad, $ae, $8a, $61, $55, $5b,
$73, $96, $ad, $ab, $89, $68, $5a, $5c, $6f, $8f, $ab, $a7, $88, $6a, $60, $63,
$72, $91, $a8, $a3, $83, $66, $5f, $65, $79, $98, $ac, $a2, $7f, $61, $5a, $63,
$79, $9c, $b0, $a6, $83, $60, $55, $5d, $76, $9b, $b0, $a8, $85, $64, $58, $5c,
$74, $97, $ae, $a6, $83, $65, $5c, $61, $74, $94, $aa, $a1, $80, $65, $5e, $64,
$78, $98, $aa, $9e, $7c, $60, $5d, $65, $7c, $9c, $ac, $a1, $7c, $61, $5c, $64,
$7b, $9a, $ab, $9f, $7f, $66, $60, $67, $7d, $9a, $a7, $99, $7a, $64, $61, $6b,
$83, $9f, $a9, $98, $75, $5f, $5d, $68, $83, $a1, $ad, $9a, $77, $5e, $5b, $65,
$7f, $9f, $ad, $9c, $79, $61, $5d, $64, $7d, $9d, $aa, $9b, $7b, $64, $60, $66,
$7e, $9b, $a6, $99, $7a, $64, $61, $68, $80, $9a, $a6, $98, $77, $63, $61, $6a,
$81, $9d, $a7, $96, $76, $61, $61, $6a, $81, $9e, $a8, $97, $76, $63, $61, $6a,
$82, $9e, $a6, $95, $75, $64, $63, $6b, $84, $a0, $a7, $93, $73, $62, $61, $6c,
$86, $a2, $a8, $93, $73, $60, $5e, $6b, $87, $a4, $aa, $92, $70, $5d, $5c, $6b,
$89, $a7, $ac, $94, $70, $5a, $59, $68, $87, $a7, $ac, $95, $73, $5d, $5b, $68,
$85, $a3, $a8, $92, $73, $60, $5f, $6e, $88, $a3, $a5, $8d, $6e, $5e, $60, $72,
$8e, $a7, $a8, $8c, $6c, $5b, $5e, $70, $8f, $aa, $aa, $8e, $6d, $5a, $5d, $6f,
$8e, $a9, $a8, $8e, $6e, $5c, $5e, $71, $8f, $a8, $a6, $8b, $6b, $5b, $5f, $73,
$92, $a9, $a6, $89, $67, $57, $5c, $73, $95, $ad, $a9, $8a, $65, $54, $59, $70,
$94, $ad, $ac, $8e, $6a, $57, $58, $6d, $90, $a9, $a9, $8d, $6c, $5b, $5e, $72,
$92, $a8, $a5, $89, $69, $5a, $5f, $75, $97, $ac, $a6, $87, $66, $58, $5e, $75,
$98, $ad, $a7, $87, $66, $57, $5d, $76, $98, $ad, $a6, $85, $64, $57, $5e, $77,
$9a, $ad, $a5, $84, $63, $56, $5e, $78, $9b, $ae, $a4, $82, $62, $56, $5e, $7a,
$9c, $ae, $a4, $81, $60, $55, $5e, $7a, $9e, $af, $a4, $80, $5f, $54, $5e, $7a,
$9d, $af, $a4, $82, $61, $56, $5e, $7a, $9c, $ad, $a2, $81, $63, $59, $62, $7c,
$9c, $ab, $9f, $7f, $62, $5b, $64, $7f, $9e, $aa, $9d, $7c, $60, $5b, $67, $82,
$a1, $ac, $9c, $78, $5d, $57, $65, $83, $a4, $af, $9e, $79, $5c, $56, $63, $80,
$a1, $ad, $9d, $7a, $5e, $59, $65, $82, $a1, $aa, $9a, $76, $5c, $59, $68, $86,
$a5, $ad, $99, $74, $59, $56, $65, $86, $a7, $b0, $9c, $76, $59, $55, $64, $84,
$a5, $af, $9d, $78, $5d, $58, $66, $84, $a3, $ab, $99, $76, $5d, $5c, $6a, $87,
$a4, $a9, $95, $72, $5b, $5c, $6d, $8c, $a8, $aa, $93, $6e, $58, $5a, $6c, $8e,
$aa, $ac, $94, $6e, $57, $58, $6b, $8d, $a9, $ab, $94, $6e, $58, $5a, $6c, $8d,
$a7, $a8, $90, $6c, $58, $5c, $6f, $91, $aa, $a9, $8f, $6a, $57, $5b, $6f, $91,
$aa, $aa, $91, $6c, $58, $5b, $6e, $90, $a9, $a9, $90, $6c, $5a, $5d, $70, $91,
$a8, $a8, $8f, $6c, $5b, $5e, $70, $90, $a7, $a6, $8d, $6c, $5c, $60, $72, $90,
$a5, $a3, $8a, $6a, $5c, $61, $75, $93, $a7, $a3, $87, $66, $5a, $61, $76, $96,
$a9, $a5, $88, $65, $58, $5e, $75, $96, $aa, $a6, $89, $66, $58, $5e, $74, $95,
$a9, $a5, $88, $67, $59, $60, $76, $96, $a8, $a3, $86, $66, $5a, $61, $78, $98,
$aa, $a3, $85, $64, $59, $61, $79, $9a, $ac, $a4, $85, $63, $58, $60, $77, $98,
$aa, $a4, $86, $67, $5c, $62, $78, $96, $a6, $9e, $82, $65, $5e, $67, $7e, $99,
$a5, $9b, $7c, $61, $5c, $67, $80, $9d, $a9, $9d, $7c, $5f, $59, $64, $7f, $9d,
$a9, $9f, $7e, $61, $5a, $64, $7e, $9c, $a8, $9d, $7d, $62, $5c, $66, $80, $9c,
$a7, $9c, $7c, $62, $5d, $67, $81, $9d, $a8, $9b, $7b, $61, $5c, $67, $82, $9d,
$a8, $9c, $7b, $61, $5c, $67, $81, $9d, $a7, $9c, $7c, $62, $5d, $67, $80, $9b,
$a5, $99, $7b, $63, $5f, $6a, $83, $9c, $a4, $97, $77, $60, $5e, $6b, $85, $9e,
$a5, $96, $76, $60, $5e, $6b, $86, $9f, $a6, $96, $75, $5e, $5e, $6c, $88, $a1,
$a7, $96, $74, $5d, $5c, $6b, $88, $a2, $a8, $97, $75, $5e, $5d, $6a, $87, $a0,
$a6, $96, $75, $60, $5f, $6c, $88, $a0, $a4, $93, $72, $5f, $60, $6f, $8b, $a1,
$a4, $92, $71, $5e, $5f, $6e, $8b, $a2, $a5, $93, $72, $5f, $5f, $6d, $8a, $a0,
$a3, $91, $72, $61, $62, $70, $8b, $9f, $a1, $8d, $6f, $60, $63, $73, $8e, $a1,
$a0, $8b, $6d, $5e, $62, $74, $91, $a4, $a3, $8c, $6c, $5b, $5f, $72, $91, $a6,
$a6, $8f, $6f, $5d, $5e, $70, $8d, $a3, $a5, $8f, $70, $5f, $61, $72, $8e, $a2,
$a2, $8b, $6e, $5e, $62, $74, $91, $a4, $a2, $8a, $6c, $5c, $60, $73, $90, $a4,
$a3, $8c, $6d, $5d, $60, $72, $8f, $a3, $a2, $8b, $6d, $5e, $62, $75, $91, $a3,
$a0, $88, $6b, $5e, $63, $77, $93, $a4, $a0, $86, $69, $5d, $64, $79, $95, $a5,
$9f, $85, $68, $5c, $63, $7a, $97, $a7, $a0, $85, $67, $5b, $62, $7a, $97, $a7,
$a1, $86, $68, $5c, $62, $79, $96, $a6, $a0, $85, $68, $5d, $64, $7a, $96, $a5,
$9e, $84, $68, $5e, $64, $7a, $96, $a3, $9c, $82, $68, $5f, $66, $7c, $96, $a3,
$9b, $80, $66, $5e, $66, $7e, $98, $a4, $9b, $80, $66, $5e, $66, $7d, $97, $a3,
$9b, $81, $68, $60, $68, $7e, $97, $a2, $98, $7e, $67, $60, $6b, $82, $9b, $a4,
$98, $7b, $63, $5d, $69, $83, $9d, $a7, $9a, $7d, $63, $5b, $66, $80, $9b, $a7,
$9b, $7f, $65, $5d, $66, $7f, $99, $a4, $99, $7e, $65, $5f, $69, $80, $9a, $a3,
$97, $7c, $65, $5f, $6a, $83, $9b, $a3, $96, $79, $62, $5f, $6b, $84, $9d, $a4,
$96, $7a, $63, $5e, $6a, $84, $9d, $a3, $96, $7a, $64, $61, $6c, $85, $9c, $a1,
$93, $78, $63, $62, $6f, $89, $9f, $a2, $91, $74, $60, $60, $6f, $8a, $a0, $a3,
$92, $75, $60, $5f, $6e, $89, $a0, $a3, $92, $75, $61, $60, $6e, $88, $9f, $a2,
$91, $75, $62, $60, $6e, $88, $9e, $a1, $91, $76, $62, $61, $6f, $88, $9d, $a0,
$8f, $75, $64, $63, $71, $8a, $9d, $9f, $8d, $73, $63, $64, $73, $8c, $9f, $9f,
$8d, $73, $62, $63, $72, $8c, $9f, $a0, $8d, $72, $62, $63, $73, $8c, $9f, $9e,
$8c, $71, $62, $63, $74, $8d, $9f, $9e, $8a, $70, $61, $64, $75, $8f, $a0, $9e,
$89, $6e, $5f, $63, $75, $90, $a2, $9f, $8a, $6d, $5e, $61, $73, $8f, $a2, $a0,
$8c, $70, $60, $62, $73, $8d, $9f, $9d, $8a, $71, $63, $66, $77, $8f, $9f, $9b,
$86, $6e, $62, $67, $7a, $93, $a1, $9b, $85, $6c, $61, $66, $7a, $93, $a1, $9c,
$86, $6d, $61, $67, $7a, $92, $a0, $9a, $85, $6d, $63, $68, $7c, $93, $9f, $98,
$82, $6b, $62, $69, $7d, $95, $a0, $99, $81, $69, $60, $68, $7d, $95, $a1, $99,
$81, $69, $60, $67, $7c, $95, $a1, $9a, $83, $6a, $61, $67, $7b, $93, $9f, $99,
$83, $6c, $63, $69, $7d, $94, $9e, $97, $81, $6b, $63, $6a, $7e, $95, $9f, $97,
$80, $6a, $63, $6b, $7f, $96, $9f, $96, $7f, $6a, $63, $6c, $81, $97, $9f, $95,
$7d, $68, $62, $6c, $82, $98, $a0, $95, $7c, $67, $61, $6b, $81, $98, $a0, $95,
$7c, $67, $62, $6c, $82, $98, $9f, $93, $7a, $66, $62, $6d, $84, $9a, $a0, $93,
$7a, $65, $61, $6c, $84, $9b, $a1, $94, $7b, $66, $61, $6c, $83, $99, $9f, $94,
$7c, $68, $64, $6e, $84, $98, $9d, $91, $7a, $68, $66, $71, $86, $99, $9c, $8f,
$78, $67, $66, $73, $89, $9b, $9d, $8e, $76, $65, $64, $72, $89, $9c, $9e, $8f,
$76, $65, $63, $70, $87, $9a, $9d, $8e, $77, $66, $65, $72, $88, $99, $9b, $8c,
$74, $65, $65, $73, $8a, $9c, $9d, $8c, $73, $63, $63, $73, $8b, $9d, $9f, $8e,
$75, $64, $63, $71, $89, $9c, $9e, $8e, $76, $66, $65, $73, $8a, $9b, $9c, $8c,
$75, $66, $67, $75, $8b, $9b, $9b, $8a, $73, $65, $67, $76, $8d, $9c, $9b, $89,
$72, $64, $67, $77, $8e, $9d, $9b, $88, $70, $63, $67, $78, $8f, $9e, $9b, $87,
$6f, $63, $66, $78, $8f, $9d, $9a, $86, $6f, $63, $67, $79, $90, $9d, $9a, $86,
$6e, $63, $67, $79, $90, $9e, $9a, $86, $6f, $64, $68, $7a, $90, $9d, $99, $85,
$6e, $64, $69, $7b, $91, $9e, $99, $85, $6e, $64, $69, $7b, $90, $9c, $98, $85,
$70, $66, $6a, $7b, $90, $9b, $96, $83, $6f, $67, $6d, $7e, $92, $9b, $94, $80,
$6c, $65, $6c, $7f, $94, $9d, $95, $7f, $6a, $63, $6a, $7e, $93, $9e, $96, $81,
$6b, $63, $6a, $7d, $93, $9c, $95, $80, $6c, $65, $6c, $7f, $93, $9c, $95, $7f,
$6b, $65, $6c, $80, $95, $9e, $95, $7f, $6a, $64, $6c, $81, $96, $9e, $95, $7f,
$6a, $64, $6c, $80, $95, $9e, $95, $80, $6c, $65, $6d, $80, $93, $9b, $92, $7d,
$6b, $67, $70, $83, $95, $9a, $90, $7a, $69, $66, $71, $85, $97, $9c, $90, $7a,
$68, $65, $6f, $85, $98, $9c, $90, $7a, $68, $65, $70, $85, $97, $9c, $8f, $79,
$68, $65, $71, $86, $98, $9c, $8f, $79, $68, $66, $71, $86, $98, $9c, $8f, $79,
$69, $66, $72, $86, $97, $9b, $8e, $78, $68, $67, $72, $87, $98, $9b, $8e, $78,
$68, $67, $72, $87, $97, $9a, $8e, $78, $69, $68, $73, $87, $96, $99, $8c, $77,
$69, $69, $74, $88, $97, $98, $8a, $76, $68, $69, $76, $89, $98, $98, $89, $74,
$67, $68, $76, $8b, $9a, $9a, $89, $73, $65, $67, $76, $8b, $9b, $9b, $8b, $75,
$66, $67, $75, $8a, $9a, $9a, $8b, $75, $68, $69, $77, $8b, $99, $98, $88, $73,
$67, $6a, $79, $8d, $9a, $98, $88, $72, $66, $68, $78, $8d, $9a, $99, $88, $72,
$66, $69, $77, $8b, $98, $97, $87, $73, $68, $6b, $7a, $8c, $97, $94, $84, $71,
$68, $6c, $7c, $8e, $99, $94, $83, $6f, $67, $6c, $7d, $90, $9a, $95, $83, $6f,
$66, $6c, $7d, $91, $9b, $96, $84, $6f, $66, $6b, $7c, $8f, $9a, $96, $84, $71,
$68, $6c, $7c, $90, $99, $94, $83, $70, $68, $6d, $7e, $90, $9a, $94, $82, $6f,
$67, $6d, $7d, $90, $99, $94, $82, $70, $68, $6d, $7d, $8f, $98, $93, $81, $6f,
$68, $6e, $7e, $90, $98, $92, $80, $6e, $68, $6e, $7f, $91, $99, $92, $7f, $6e,
$68, $6f, $80, $92, $98, $91, $7e, $6d, $68, $71, $82, $94, $9a, $91, $7d, $6b,
$67, $70, $83, $95, $9b, $92, $7d, $6b, $66, $6f, $82, $94, $9b, $92, $7e, $6c,
$67, $70, $82, $93, $99, $90, $7d, $6c, $69, $71, $83, $93, $98, $8f, $7c, $6c,
$69, $72, $84, $94, $97, $8d, $7a, $6b, $69, $73, $85, $94, $98, $8e, $7b, $6b,
$69, $72, $84, $94, $97, $8d, $7b, $6d, $6b, $74, $85, $93, $96, $8b, $79, $6c,
$6b, $76, $88, $95, $96, $8a, $77, $6a, $6a, $76, $88, $97, $98, $8c, $78, $69,
$68, $74, $86, $96, $98, $8d, $79, $6b, $69, $74, $86, $95, $97, $8b, $79, $6b,
$6a, $75, $87, $95, $97, $8a, $78, $6b, $6b, $76, $88, $95, $96, $8a, $77, $6b,
$6b, $77, $88, $96, $96, $89, $76, $6a, $6b, $77, $89, $96, $96, $89, $76, $6a,
$6c, $78, $8a, $96, $95, $87, $75, $6a, $6d, $7a, $8b, $97, $95, $86, $73, $69,
$6c, $7a, $8c, $97, $95, $86, $73, $69, $6c, $7a, $8c, $97, $94, $85, $73, $69,
$6c, $7b, $8d, $97, $95, $85, $72, $69, $6c, $7a, $8c, $97, $94, $86, $73, $6a,
$6d, $7a, $8b, $95, $93, $85, $74, $6c, $6f, $7c, $8c, $94, $91, $83, $73, $6b,
$70, $7e, $8e, $96, $92, $83, $72, $6a, $6f, $7d, $8e, $96, $92, $83, $72, $6b,
$6f, $7d, $8d, $95, $91, $82, $72, $6b, $71, $7f, $8e, $95, $90, $81, $70, $6a,
$70, $7f, $8f, $96, $90, $80, $6f, $69, $70, $7f, $90, $97, $91, $80, $6f, $68,
$6e, $7e, $8f, $97, $92, $81, $70, $6a, $6f, $7e, $8e, $95, $90, $81, $71, $6c,
$72, $80, $8f, $95, $8e, $7f, $6f, $6c, $73, $82, $91, $96, $8f, $7e, $6f, $6b,
$73, $82, $91, $96, $8f, $7e, $6f, $6c, $73, $82, $91, $95, $8d, $7d, $6f, $6c,
$74, $84, $92, $95, $8c, $7b, $6d, $6c, $74, $84, $92, $95, $8c, $7b, $6d, $6b,
$74, $84, $92, $95, $8b, $7a, $6d, $6b, $74, $84, $92, $95, $8c, $7b, $6d, $6b,
$74, $84, $92, $95, $8c, $7b, $6e, $6c, $74, $84, $91, $94, $8b, $7b, $6f, $6d,
$76, $85, $91, $93, $8a, $7b, $6f, $6e, $77, $86, $92, $93, $89, $7a, $6f, $6e,
$78, $87, $93, $93, $89, $78, $6d, $6d, $78, $87, $93, $94, $89, $78, $6d, $6c,
$77, $87, $93, $94, $89, $78, $6d, $6d, $78, $87, $92, $92, $87, $77, $6c, $6d,
$79, $89, $94, $93, $87, $75, $6b, $6c, $78, $89, $95, $94, $88, $77, $6c, $6c,
$78, $88, $93, $94, $88, $78, $6e, $6f, $79, $88, $92, $92, $86, $77, $6e, $70,
$7b, $8a, $93, $91, $85, $76, $6e, $70, $7c, $8b, $94, $91, $84, $75, $6d, $70,
$7d, $8b, $94, $91, $84, $74, $6d, $70, $7c, $8b, $93, $90, $83, $74, $6d, $70,
$7c, $8b, $93, $8f, $82, $73, $6c, $70, $7d, $8c, $93, $90, $82, $73, $6c, $70,
$7d, $8c, $94, $91, $83, $74, $6c, $70, $7d, $8b, $93, $90, $83, $75, $6e, $71,
$7e, $8c, $93, $8f, $82, $74, $6e, $72, $7e, $8c, $93, $8f, $82, $74, $6e, $72,
$7f, $8c, $93, $8e, $81, $73, $6e, $73, $80, $8d, $93, $8d, $7f, $71, $6d, $73,
$81, $8f, $94, $8e, $7f, $71, $6c, $72, $80, $8e, $94, $8d, $7f, $71, $6d, $73,
$81, $8e, $93, $8d, $7e, $71, $6d, $73, $81, $8f, $93, $8c, $7e, $70, $6d, $74,
$82, $8f, $93, $8c, $7d, $70, $6d, $75, $83, $90, $94, $8c, $7e, $71, $6e, $74,
$82, $8f, $93, $8c, $7e, $72, $6f, $76, $82, $8e, $91, $8a, $7d, $72, $70, $77,
$84, $8f, $90, $88, $7a, $70, $6f, $78, $85, $90, $92, $89, $7a, $6f, $6e, $76,
$84, $90, $92, $8a, $7b, $70, $6f, $77, $84, $8f, $91, $89, $7b, $70, $6f, $78,
$85, $90, $92, $89, $7a, $6f, $6f, $77, $86, $91, $92, $89, $7a, $70, $6f, $78,
$86, $91, $92, $89, $7a, $70, $6f, $78, $86, $90, $92, $88, $7a, $70, $70, $78,
$86, $90, $90, $87, $7a, $70, $71, $7a, $87, $90, $90, $86, $78, $6f, $70, $7a,
$88, $91, $90, $85, $77, $6f, $70, $7b, $88, $91, $90, $85, $77, $6e, $71, $7b,
$89, $91, $90, $84, $76, $6e, $71, $7c, $8a, $92, $90, $85, $77, $6f, $71, $7b,
$89, $92, $90, $85, $77, $70, $72, $7c, $89, $91, $8f, $84, $77, $70, $72, $7d,
$8a, $91, $8e, $83, $76, $6f, $72, $7c, $89, $90, $8e, $83, $76, $70, $72, $7c,
$88, $8f, $8d, $82, $76, $70, $73, $7d, $89, $8f, $8c, $81, $75, $70, $74, $7e,
$8a, $90, $8c, $80, $74, $6f, $74, $7f, $8c, $91, $8d, $81, $74, $6e, $73, $7f,
$8c, $92, $8e, $82, $75, $6f, $73, $7e, $8b, $91, $8e, $82, $75, $70, $74, $80,
$8c, $91, $8c, $80, $74, $70, $75, $81, $8d, $92, $8d, $80, $73, $6f, $74, $80,
$8c, $91, $8c, $80, $74, $70, $74, $80, $8b, $90, $8b, $7f, $74, $71, $76, $81,
$8c, $8f, $89, $7d, $72, $70, $76, $82, $8d, $90, $89, $7d, $72, $70, $77, $83,
$8d, $90, $89, $7c, $72, $70, $77, $83, $8e, $90, $89, $7c, $72, $70, $77, $84,
$8e, $91, $8a, $7d, $72, $70, $77, $83, $8e, $90, $89, $7d, $73, $71, $78, $83,
$8e, $90, $89, $7d, $73, $71, $78, $83, $8d, $8f, $89, $7c, $73, $72, $78, $84,
$8d, $8f, $87, $7b, $72, $72, $79, $84, $8d, $8f, $87, $7b, $72, $71, $78, $84,
$8d, $8e, $87, $7b, $72, $72, $79, $85, $8d, $8e, $86, $7a, $72, $73, $7b, $87,
$8f, $8e, $85, $79, $70, $71, $7b, $87, $90, $90, $87, $79, $70, $71, $79, $86,
$8f, $90, $87, $7a, $72, $72, $7a, $86, $8e, $8e, $85, $79, $72, $73, $7b, $87,
$8f, $8e, $85, $79, $72, $73, $7c, $87, $8f, $8d, $84, $78, $72, $73, $7c, $88,
$8f, $8d, $84, $78, $72, $73, $7c, $87, $8e, $8c, $83, $78, $72, $74, $7d, $88,
$8d, $8b, $82, $77, $72, $75, $7e, $89, $8f, $8b, $81, $76, $71, $74, $7e, $8a,
$8f, $8d, $82, $77, $71, $74, $7e, $89, $8f, $8c, $82, $77, $72, $74, $7e, $89,
$8e, $8c, $82, $77, $71, $74, $7e, $89, $8e, $8c, $82, $77, $72, $74, $7e, $89,
$8e, $8b, $82, $77, $72, $75, $7f, $89, $8e, $8b, $81, $76, $72, $76, $80, $8a,
$8e, $8b, $80, $76, $72, $76, $80, $8a, $8f, $8b, $80, $76, $72, $77, $81, $8b,
$8e, $8a, $7f, $75, $72, $77, $81, $8b, $8f, $89, $7f, $74, $72, $77, $82, $8c,
$8f, $89, $7e, $74, $71, $77, $82, $8c, $8f, $8a, $7e, $74, $71, $76, $81, $8b,
$8f, $8a, $7f, $75, $72, $77, $81, $8a, $8d, $88, $7e, $75, $73, $78, $82, $8a,
$8c, $87, $7d, $75, $73, $79, $83, $8c, $8d, $87, $7d, $74, $73, $79, $83, $8c,
$8e, $88, $7d, $75, $74, $79, $83, $8b, $8d, $87, $7d, $75, $74, $7a, $84, $8c,
$8d, $86, $7b, $74, $73, $7a, $85, $8d, $8d, $86, $7b, $73, $73, $79, $84, $8c,
$8d, $87, $7b, $73, $72, $79, $84, $8c, $8e, $87, $7c, $74, $73, $79, $84, $8c,
$8d, $86, $7c, $74, $74, $7a, $84, $8c, $8c, $85, $7b, $74, $74, $7b, $85, $8c,
$8c, $85, $7b, $74, $74, $7b, $86, $8d, $8c, $85, $7a, $74, $75, $7c, $86, $8d,
$8c, $84, $79, $73, $75, $7d, $87, $8d, $8c, $83, $79, $73, $74, $7d, $87, $8d,
$8c, $83, $79, $73, $75, $7d, $87, $8d, $8b, $83, $78, $73, $75, $7d, $87, $8d,
$8b, $82, $78, $72, $74, $7d, $87, $8d, $8b, $83, $78, $73, $75, $7c, $86, $8c,
$8b, $83, $79, $74, $76, $7e, $87, $8c, $8a, $82, $79, $75, $77, $7f, $88, $8c,
$8a, $81, $78, $74, $77, $7f, $88, $8c, $8a, $81, $78, $74, $77, $7f, $88, $8d,
$8a, $81, $77, $73, $76, $7f, $88, $8c, $8a, $81, $78, $74, $77, $7f, $88, $8c,
$89, $7f, $76, $73, $77, $80, $89, $8d, $89, $7f, $76, $72, $76, $80, $89, $8d,
$8a, $80, $77, $73, $76, $7f, $88, $8c, $89, $80, $77, $74, $78, $80, $89, $8c,
$88, $7f, $77, $74, $79, $81, $8a, $8c, $88, $7f, $77, $74, $79, $82, $8a, $8c,
$87, $7e, $76, $75, $7a, $82, $8a, $8c, $87, $7e, $76, $74, $79, $82, $8a, $8c,
$87, $7d, $75, $74, $79, $82, $8a, $8c, $86, $7d, $75, $74, $79, $82, $8a, $8c,
$86, $7c, $75, $74, $79, $82, $8a, $8c, $86, $7d, $76, $74, $7a, $82, $8a, $8b,
$86, $7d, $76, $75, $7a, $83, $8a, $8c, $86, $7d, $76, $75, $7a, $83, $8a, $8c,
$86, $7d, $77, $76, $7b, $83, $8a, $8b, $85, $7d, $77, $76, $7c, $84, $8a, $8a,
$84, $7b, $75, $76, $7c, $85, $8b, $8b, $84, $7b, $74, $75, $7b, $84, $8b, $8b,
$85, $7b, $75, $75, $7b, $84, $8b, $8a, $84, $7b, $75, $75, $7c, $85, $8b, $8b,
$84, $7a, $74, $75, $7c, $86, $8c, $8b, $84, $7a, $75, $76, $7d, $86, $8b, $8b,
$84, $7b, $75, $76, $7d, $85, $8b, $8a, $84, $7b, $76, $77, $7d, $85, $8a, $89,
$82, $7a, $76, $78, $7e, $86, $8a, $88, $81, $79, $75, $77, $7e, $87, $8b, $89,
$81, $79, $75, $77, $7e, $86, $8b, $89, $81, $79, $75, $77, $7e, $86, $8a, $88,
$81, $79, $75, $77, $7f, $87, $8b, $89, $81, $79, $75, $77, $7e, $87, $8c, $8a,
$82, $7a, $76, $78, $7f, $87, $8b, $89, $82, $7a, $76, $78, $7f, $87, $8b, $89,
$81, $79, $76, $78, $7f, $87, $8b, $88, $81, $79, $76, $78, $7f, $87, $8a, $87,
$80, $79, $76, $79, $80, $87, $8a, $87, $7f, $78, $75, $79, $80, $88, $8a, $86,
$7e, $77, $75, $79, $81, $88, $8b, $87, $7e, $77, $75, $79, $81, $89, $8b, $87,
$7f, $77, $75, $79, $81, $88, $8b, $87, $7f, $78, $76, $7a, $82, $89, $8b, $87,
$7f, $78, $76, $7b, $82, $89, $8b, $87, $7e, $78, $76, $7a, $82, $89, $8b, $87,
$7f, $78, $76, $7a, $81, $87, $89, $85, $7e, $78, $77, $7b, $82, $88, $89, $84,
$7d, $77, $77, $7b, $83, $88, $89, $84, $7c, $77, $76, $7b, $83, $89, $8a, $85,
$7d, $77, $76, $7b, $83, $89, $8a, $85, $7d, $77, $76, $7b, $83, $89, $8a, $85,
$7d, $77, $77, $7c, $84, $89, $8a, $85, $7d, $77, $77, $7c, $84, $8a, $8a, $85,
$7d, $77, $77, $7c, $84, $89, $8a, $85, $7d, $77, $77, $7c, $83, $89, $89, $83,
$7c, $77, $77, $7d, $84, $89, $88, $82, $7b, $76, $77, $7d, $84, $89, $88, $82,
$7b, $76, $77, $7d, $84, $89, $88, $82, $7b, $77, $78, $7e, $85, $8a, $88, $82,
$7a, $76, $78, $7e, $86, $8a, $89, $82, $7b, $76, $78, $7e, $85, $8a, $89, $83,
$7b, $77, $78, $7e, $85, $89, $88, $82, $7b, $77, $79, $7e, $85, $89, $88, $82,
$7b, $77, $79, $7f, $85, $89, $87, $81, $7a, $77, $79, $7e, $85, $89, $87, $81,
$7a, $77, $79, $7e, $85, $88, $86, $81, $7a, $77, $79, $7f, $85, $88, $86, $80,
$7a, $77, $7a, $80, $87, $89, $87, $80, $79, $77, $79, $80, $87, $8b, $88, $81,
$79, $76, $79, $80, $87, $8a, $88, $81, $7a, $77, $7a, $80, $86, $89, $87, $80,
$79, $77, $7a, $80, $87, $89, $86, $80, $79, $77, $7a, $80, $86, $89, $86, $7f,
$79, $77, $7a, $80, $86, $88, $85, $7f, $79, $77, $7b, $81, $87, $88, $85, $7e,
$79, $78, $7b, $81, $87, $88, $84, $7e, $79, $78, $7b, $82, $87, $88, $85, $7e,
$78, $78, $7c, $82, $88, $89, $85, $7e, $79, $78, $7c, $82, $88, $89, $85, $7e,
$79, $78, $7c, $83, $88, $89, $85, $7e, $79, $78, $7b, $82, $87, $89, $85, $7e,
$79, $78, $7b, $81, $87, $88, $84, $7e, $79, $78, $7c, $82, $86, $87, $83, $7d,
$79, $78, $7c, $83, $87, $88, $84, $7d, $78, $78, $7c, $83, $87, $88, $84, $7d,
$79, $78, $7d, $83, $87, $87, $83, $7d, $79, $79, $7d, $84, $88, $88, $83, $7c,
$78, $78, $7d, $84, $89, $88, $83, $7c, $78, $78, $7d, $84, $89, $89, $83, $7c,
$78, $78, $7d, $84, $88, $88, $83, $7c, $78, $78, $7d, $83, $87, $87, $82, $7c,
$78, $79, $7e, $84, $87, $86, $81, $7b, $78, $79, $7e, $84, $88, $87, $81, $7b,
$78, $79, $7e, $84, $88, $87, $82, $7c, $79, $7a, $7f, $84, $87, $86, $81, $7b,
$79, $7b, $80, $85, $88, $86, $81, $7b, $78, $7a, $7f, $85, $88, $87, $81, $7b,
$78, $7a, $7f, $85, $88, $86, $81, $7b, $78, $7a, $7f, $85, $88, $86, $81, $7b,
$78, $79, $7f, $85, $88, $86, $81, $7b, $78, $7a, $7f, $85, $87, $86, $80, $7b,
$78, $7a, $7f, $85, $87, $86, $80, $7b, $79, $7b, $80, $85, $88, $85, $80, $7b,
$79, $7b, $81, $86, $88, $85, $80, $7a, $79, $7b, $81, $87, $88, $86, $7f, $7a,
$78, $7b, $81, $86, $88, $85, $7f, $7a, $78, $7b, $81, $86, $87, $84, $7e, $79,
$78, $7b, $81, $86, $88, $84, $7e, $79, $77, $7b, $81, $86, $88, $85, $7f, $7a,
$78, $7b, $81, $86, $87, $84, $7f, $7a, $79, $7c, $81, $86, $87, $84, $7e, $7a,
$7a, $7d, $82, $86, $87, $84, $7e, $7a, $7a, $7d, $82, $87, $87, $84, $7e, $7a,
$79, $7d, $82, $87, $87, $84, $7e, $7a, $79, $7d, $82, $87, $87, $83, $7e, $7a,
$79, $7d, $82, $87, $87, $83, $7d, $79, $79, $7d, $82, $87, $87, $83, $7d, $79,
$78, $7c, $82, $87, $87, $83, $7d, $79, $78, $7c, $82, $86, $87, $83, $7d, $7a,
$79, $7d, $83, $87, $87, $83, $7d, $7a, $7a, $7e, $83, $87, $87, $83, $7d, $7a,
$7a, $7e, $84, $87, $87, $82, $7d, $7a, $7b, $7f, $84, $87, $86, $81, $7c, $79,
$7a, $7f, $84, $87, $86, $81, $7b, $78, $79, $7e, $84, $87, $86, $81, $7b, $79,
$7a, $7e, $84, $87, $86, $81, $7c, $79, $7a, $7f, $84, $87, $86, $81, $7c, $79,
$7a, $7f, $84, $87, $86, $81, $7c, $79, $7a, $7f, $84, $87, $86, $81, $7c, $7a,
$7b, $7f, $84, $87, $86, $81, $7d, $7a, $7b, $80, $84, $87, $85, $81, $7c, $7a,
$7c, $80, $85, $87, $85, $80, $7b, $79, $7b, $80, $85, $87, $85, $80, $7b, $79,
$7b, $80, $85, $87, $85, $80, $7b, $79, $7b, $80, $84, $86, $84, $7f, $7a, $79,
$7b, $80, $85, $87, $85, $7f, $7a, $78, $7b, $80, $85, $87, $85, $80, $7b, $79,
$7b, $80, $85, $87, $85, $80, $7b, $7a, $7c, $81, $85, $87, $85, $80, $7b, $7a,
$7c, $81, $85, $87, $84, $7f, $7b, $7a, $7d, $81, $85, $86, $83, $7e, $7a, $7a,
$7d, $82, $85, $86, $83, $7e, $7a, $7a, $7c, $81, $85, $86, $83, $7e, $7a, $79,
$7d, $82, $85, $86, $83, $7e, $7a, $79, $7d, $82, $86, $86, $83, $7e, $7a, $79,
$7d, $82, $86, $87, $84, $7f, $7b, $7a, $7d, $82, $86, $86, $83, $7e, $7b, $7a,
$7d, $82, $86, $86, $83, $7e, $7b, $7a, $7d, $82, $86, $86, $83, $7e, $7b, $7a,
$7d, $82, $85, $86, $83, $7e, $7b, $7b, $7e, $82, $85, $85, $82, $7d, $7a, $7a,
$7e, $83, $86, $85, $82, $7c, $79, $7a, $7e, $83, $86, $86, $82, $7c, $79, $7a,
$7e, $83, $86, $86, $82, $7d, $7a, $7a, $7e, $83, $86, $86, $82, $7d, $7a, $7b,
$7f, $83, $86, $86, $82, $7d, $7a, $7b, $7f, $84, $87, $86, $82, $7d, $7a, $7b,
$7f, $83, $86, $86, $82, $7d, $7b, $7b, $7f, $83, $85, $84, $81, $7d, $7b, $7c,
$7f, $83, $85, $84, $80, $7c, $7a, $7b, $7f, $84, $86, $84, $80, $7c, $7a, $7b,
$7f, $84, $86, $84, $80, $7c, $7a, $7b, $80, $84, $86, $84, $80, $7c, $7a, $7b,
$80, $84, $86, $85, $81, $7c, $7a, $7b, $80, $84, $86, $85, $81, $7c, $7a, $7c,
$80, $84, $86, $85, $81, $7d, $7a, $7c, $80, $84, $86, $85, $80, $7c, $7a, $7c,
$80, $84, $86, $84, $80, $7c, $7a, $7c, $80, $84, $86, $84, $7f, $7b, $7a, $7c,
$80, $84, $85, $83, $7f, $7b, $7a, $7c, $80, $84, $85, $83, $7e, $7b, $7a, $7d,
$81, $85, $86, $83, $7e, $7b, $7a, $7d, $81, $86, $87, $84, $7f, $7b, $7a, $7d,
$81, $85, $86, $84, $7f, $7c, $7b, $7d, $81, $85, $86, $83, $7f, $7c, $7b, $7d,
$82, $85, $86, $83, $7f, $7b, $7b, $7d, $81, $85, $85, $83, $7f, $7b, $7b, $7d,
$81, $84, $85, $82, $7e, $7b, $7b, $7d, $81, $84, $85, $82, $7e, $7b, $7b, $7e,
$82, $85, $85, $82, $7e, $7b, $7b, $7e, $82, $85, $85, $82, $7e, $7b, $7b, $7e,
$82, $85, $86, $83, $7e, $7b, $7b, $7e, $82, $85, $86, $83, $7e, $7b, $7b, $7e,
$82, $85, $85, $82, $7e, $7b, $7b, $7e, $82, $86, $86, $82, $7e, $7b, $7b, $7e,
$82, $85, $85, $82, $7e, $7b, $7b, $7e, $82, $85, $84, $81, $7d, $7b, $7b, $7e,
$82, $85, $84, $81, $7d, $7b, $7b, $7e, $82, $85, $84, $81, $7d, $7b, $7c, $7f,
$83, $85, $84, $81, $7d, $7b, $7c, $7f, $83, $85, $84, $81, $7d, $7b, $7c, $7f,
$84, $85, $84, $81, $7d, $7b, $7c, $7f, $83, $85, $85, $81, $7d, $7b, $7c, $7f,
$83, $85, $84, $81, $7d, $7b, $7c, $7f, $83, $84, $84, $81, $7d, $7b, $7c, $7f,
$83, $84, $83, $80, $7d, $7b, $7c, $80, $83, $85, $84, $80, $7d, $7b, $7c, $7f,
$83, $85, $84, $81, $7d, $7c, $7d, $80, $83, $84, $83, $80, $7d, $7c, $7d, $80,
$84, $85, $83, $80, $7c, $7b, $7d, $80, $84, $85, $84, $80, $7c, $7b, $7c, $80,
$84, $85, $84, $80, $7c, $7b, $7c, $80, $84, $85, $84, $80, $7c, $7b, $7d, $80,
$83, $85, $83, $80, $7c, $7b, $7d, $80, $83, $84, $83, $7f, $7c, $7b, $7d, $80,
$84, $84, $83, $7f, $7c, $7c, $7d, $81, $84, $84, $82, $7f, $7c, $7c, $7e, $81,
$84, $84, $82, $7f, $7c, $7c, $7e, $82, $84, $85, $82, $7f, $7c, $7c, $7e, $81,
$84, $85, $83, $7f, $7c, $7c, $7e, $81, $84, $84, $82, $7f, $7c, $7c, $7e, $81,
$84, $84, $82, $7f, $7c, $7b, $7d, $81, $84, $84, $82, $7f, $7c, $7b, $7d, $81,
$83, $84, $82, $7f, $7c, $7c, $7e, $81, $83, $84, $82, $7f, $7c, $7c, $7e, $81,
$84, $84, $82, $7e, $7c, $7c, $7e, $82, $84, $84, $82, $7e, $7c, $7c, $7f, $82,
$84, $84, $82, $7e, $7c, $7c, $7f, $82, $84, $84, $82, $7e, $7c, $7c, $7f, $82,
$85, $84, $81, $7e, $7c, $7c, $7f, $82, $85, $84, $81, $7d, $7b, $7b, $7e, $82,
$84, $84, $81, $7e, $7b, $7c, $7e, $81, $83, $83, $81, $7e, $7c, $7c, $7f, $82,
$84, $83, $81, $7e, $7c, $7d, $7f, $82, $84, $83, $81, $7e, $7c, $7d, $7f, $82,
$84, $83, $81, $7e, $7d, $7d, $80, $83, $84, $83, $81, $7e, $7c, $7d, $80, $83,
$84, $83, $80, $7d, $7c, $7d, $80, $83, $84, $83, $80, $7d, $7c, $7d, $80, $83,
$84, $83, $80, $7d, $7c, $7c, $7f, $82, $84, $83, $80, $7d, $7b, $7c, $7f, $82,
$84, $83, $80, $7d, $7c, $7d, $7f, $82, $84, $83, $80, $7d, $7c, $7d, $80, $83,
$84, $83, $80, $7d, $7c, $7d, $80, $83, $84, $83, $80, $7d, $7d, $7e, $81, $83,
$84, $82, $7f, $7d, $7c, $7e, $81, $84, $85, $83, $80, $7d, $7c, $7d, $81, $84,
$84, $83, $80, $7d, $7c, $7e, $81, $83, $84, $82, $7f, $7c, $7c, $7e, $81, $83,
$84, $82, $7f, $7c, $7c, $7d, $81, $83, $84, $82, $7f, $7d, $7c, $7e, $81, $83,
$84, $82, $7f, $7d, $7c, $7e, $81, $83, $84, $82, $7f, $7d, $7d, $7e, $81, $83,
$84, $82, $7f, $7d, $7d, $7f, $81, $83, $83, $82, $7f, $7d, $7d, $7e, $81, $83,
$84, $82, $7f, $7c, $7c, $7e, $81, $83, $83, $81, $7f, $7c, $7c, $7e, $81, $83,
$83, $81, $7e, $7c, $7c, $7e, $81, $84, $84, $82, $7e, $7c, $7c, $7e, $81, $84,
$84, $82, $7f, $7d, $7c, $7e, $81, $84, $84, $82, $7f, $7d, $7d, $7f, $82, $84,
$84, $81, $7f, $7d, $7d, $7f, $82, $84, $84, $81, $7e, $7d, $7d, $7f, $82, $83,
$83, $81, $7e, $7d, $7d, $7f, $82, $84, $83, $80, $7e, $7c, $7d, $7f, $82, $84,
$83, $80, $7d, $7c, $7d, $7f, $82, $84, $83, $80, $7d, $7c, $7d, $7f, $82, $84,
$83, $80, $7d, $7c, $7d, $7f, $82, $83, $83, $80, $7e, $7d, $7d, $80, $82, $83,
$83, $80, $7e, $7d, $7e, $80, $83, $84, $83, $81, $7e, $7d, $7e, $80, $82, $84,
$83, $81, $7e, $7d, $7e, $80, $82, $83, $82, $80, $7e, $7d, $7e, $80, $82, $83,
$82, $7f, $7d, $7c, $7e, $80, $82, $83, $82, $7f, $7d, $7c, $7d, $80, $82, $83,
$82, $7f, $7d, $7c, $7d, $80, $82, $83, $82, $7f, $7d, $7c, $7e, $80, $83, $84,
$82, $80, $7d, $7d, $7e, $81, $83, $84, $82, $80, $7d, $7d, $7e, $81, $83, $84,
$82, $80, $7e, $7d, $7e, $81, $83, $84, $82, $80, $7e, $7d, $7f, $81, $83, $83,
$82, $7f, $7e, $7d, $7f, $81, $83, $83, $81, $7f, $7d, $7d, $7f, $81, $83, $83,
$81, $7f, $7d, $7d, $7e, $81, $82, $82, $81, $7f, $7d, $7d, $7f, $81, $83, $83,
$81, $7f, $7d, $7d, $7f, $81, $83, $83, $81, $7f, $7d, $7d, $7f, $81, $83, $83,
$82, $7f, $7e, $7d, $7f, $81, $83, $83, $81, $7f, $7e, $7e, $7f, $81, $83, $83,
$81, $7f, $7e, $7e, $7f, $81, $83, $83, $81, $7f, $7d, $7e, $7f, $81, $82, $82,
$81, $7f, $7d, $7d, $7f, $81, $82, $82, $80, $7e, $7d, $7d, $7f, $81, $82, $82,
$80, $7e, $7d, $7e, $7f, $82, $83, $82, $80, $7e, $7d, $7d, $7f, $82, $83, $83,
$81, $7f, $7d, $7e, $7f, $82, $83, $83, $81, $7f, $7e, $7e, $80, $82, $83, $82,
$81, $7f, $7e, $7e, $80, $82, $83, $82, $80, $7e, $7d, $7e, $80, $82, $83, $82,
$80, $7f, $7e, $7e, $80, $81, $82, $82, $80, $7e, $7e, $7e, $80, $81, $82, $81,
$80, $7e, $7e, $7e, $80, $81, $82, $81, $80, $7e, $7d, $7e, $80, $82, $82, $81,
$80, $7e, $7d, $7e, $80, $82, $82, $82, $80, $7e, $7e, $7e, $80, $82, $83, $82,
$80, $7e, $7e, $7f, $80, $82, $83, $82, $80, $7e, $7e, $7f, $80, $82, $83, $82,
$80, $7e, $7e, $7e, $80, $82, $82, $81, $80, $7e, $7e, $7f, $80, $82, $82, $81,
$7f, $7e, $7e, $7f, $80, $82, $82, $81, $7f, $7e, $7e, $7f, $80, $82, $82, $81,
$7f, $7e, $7e, $7f, $80, $82, $82, $81, $7f, $7e, $7e, $7f, $81, $82, $82, $81,
$7f, $7e, $7e, $7f, $81, $82, $82, $81, $7f, $7e, $7e, $7f, $81, $82, $82, $81,
$80, $7e, $7e, $7f, $81, $82, $82, $81, $7f, $7e, $7e, $7f, $81, $82, $82, $81,
$7f, $7e, $7e, $7f, $81, $82, $81, $80, $7f, $7e, $7e, $7f, $81, $82, $81, $80,
$7f, $7e, $7e, $7f, $81, $82, $82, $81, $7f, $7e, $7f, $80, $81, $82, $81, $80,
$7f, $7e, $7f, $80, $81, $82, $82, $81, $7f, $7e, $7f, $80, $81, $82, $82, $81,
$7f, $7e, $7f, $80, $81, $82, $82, $81, $7f, $7e, $7f, $80, $81, $82, $82, $81,
$7f, $7e, $7f, $80, $81, $82, $81, $80, $7f, $7e, $7e, $7f, $81, $81, $81, $80,
$7f, $7e, $7f, $80, $81, $81, $81, $80, $7f, $7e, $7f, $80, $81, $81, $81, $80,
$7f, $7e, $7f, $80, $81, $82, $81, $80, $7f, $7e, $7f, $80, $81, $82, $81, $80,
$7f, $7f, $7f, $80, $81, $82, $81, $80, $7f, $7f, $7f, $80, $81, $82, $81, $80,
$7f, $7f, $7f, $80, $81, $82, $81, $80, $7f, $7e, $7f, $80, $81, $81, $81, $80,
$7f, $7f, $7f, $80, $81, $81, $81, $80, $7f, $7f, $7f, $80, $81, $81, $81, $80,
$7f, $7f, $7f, $80, $81, $81, $81, $80, $7f, $7f, $7f, $80, $81, $81, $81, $80,
$7f, $7f, $7f, $80, $81, $81, $81, $80, $7f, $7f, $7f, $80, $81, $81, $81, $80,
$7f, $7f, $7f, $80, $81, $81, $81, $80, $7f, $7f, $7f, $80, $81, $81, $81, $80,
$7f, $7f, $7f, $80, $81, $81, $81, $80, $7f, $7f, $7f, $80, $81, $81, $80, $80,
$7f, $7f, $7f, $80, $81, $81, $80, $80, $7f, $7f, $7f, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $81, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $80, $80, $80, $81, $80, $80, $80,
$7f, $7f, $80, $80, $81, $81, $80, $80, $7f, $7f, $80, $80, $81, $81, $80, $80,
$7f, $7f, $80, $80, $81, $80, $80, $80, $7f, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80, $80,
$80, $80, $80, $80 );

//==============================================================================
//==============================================================================
//REVIEW: can generate shorter samples, because all values at the end
//of the sample vanish to zero after scaling.
function GetSample(
                    _name : String;
                    _comment : String;
                    _channelsCount : integer;
                    const _a: array of BYTE;
                    _length : integer
                  ): String;
const
  CR : String = #13 + #10;
var
  maxChannelAmplitude : integer;
  i, j: integer;

begin
  maxChannelAmplitude := 127 div _channelsCount;

  result := result + '//' + _comment + CR;
  result := result + '//Scaled for channels count: ' + intToStr( _channelsCount ) + CR ;
  result := result + 'static const flash int8_t ' + _name + '[ ' + intToStr(_length) + ' ] = { ';

  for i := 0 to _length - 1 do
    begin
      if ( ( i mod 16 ) = 0 ) then
        begin
          result := result + CR + '    ';
        end;

      j := integer( _a[ i ] ) - 128;
      j := j * maxChannelAmplitude div 128;

      if ( j >= 0 ) then
        begin
          result := result + '0x' + intToHex( j, 2 );
        end
          else
        begin
          result := result + '0x' + intToHex( 255 + j, 2 );
        end;

      if ( i < _length - 1 ) then
        begin
          result := result + ', ';
        end;
    end;

  result := result + ' };' + CR;
end;

//==============================================================================
//==============================================================================
function GetSampleCode( _channelsCount : integer ) : String;
begin
  result := GetSample('s_sample', 'Sample: piano 1.5k', _channelsCount, sample_data, sample_length)
end;

//==============================================================================
//==============================================================================
function loadSample( _filename : String ) : Boolean;
var
  f : File;
begin
  assignFile( f, _filename );
  reset( f, 1 );

  sample_length := filesize( f ) - 44;

  setLength( sample_data, sample_length );

  seek( f, 44 );
  blockread( f, sample_data[0], sample_length );

  closeFile( f );

  result := true;
end;

//==============================================================================
//==============================================================================
procedure readEmbeddedSample();
var
  i : integer;
begin
  setLength( sample_data, DUMP___SIZE - 44 );
  for i := 0 to ( DUMP___SIZE - 44 - 1 )  do
  begin
    sample_data[ i ] := sampleData[ i + 44 ];
  end;

  sample_length := DUMP___SIZE - 44;
end;


begin
 readEmbeddedSample();
end.
