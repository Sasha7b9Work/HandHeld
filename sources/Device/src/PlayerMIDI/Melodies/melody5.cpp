#include "defines.h"
#include "PlayerMIDI/PlayerMIDI.h"
#include "PlayerMIDI/Melodies/melody5.h"


//Player frequency=18000
//Player minimum channels count =4
static const uint8 s_melody5_stream1[1145] = {
    200,
    27,
    209,
    81,
    26,
    39,
    68,
    128,
    12,
    81,
    0,
    11,
    65,
    160,
    64,
    40,
    167,
    76,
    105,
    130,
    160,
    114,
    84,
    206,
    128,
    49,
    26,
    161,
    48,
    29,
    132,
    34,
    170,
    106,
    133,
    81,
    49,
    225,
    71,
    139,
    110,
    84,
    57,
    189,
    225,
    71,
    140,
    46,
    84,
    57,
    128,
    92,
    25,
    67,
    140,
    206,
    78,
    120,
    81,
    231,
    3,
    140,
    166,
    224,
    3,
    152,
    8,
    112,
    139,
    198,
    72,
    230,
    219,
    133,
    14,
    47,
    71,
    56,
    92,
    40,
    64,
    242,
    101,
    204,
    7,
    57,
    150,
    30,
    80,
    56,
    74,
    230,
    2,
    13,
    192,
    7,
    8,
    188,
    100,
    142,
    109,
    184,
    80,
    226,
    244,
    115,
    133,
    194,
    47,
    26,
    3,
    155,
    46,
    17,
    120,
    204,
    228,
    229,
    77,
    249,
    74,
    230,
    203,
    132,
    94,
    50,
    121,
    45,
    231,
    42,
    79,
    202,
    103,
    7,
    188,
    228,
    240,
    137,
    198,
    63,
    39,
    28,
    221,
    206,
    12,
    252,
    192,
    114,
    137,
    206,
    47,
    6,
    220,
    94,
    183,
    40,
    92,
    0,
    115,
    1,
    62,
    113,
    97,
    198,
    63,
    41,
    60,
    25,
    115,
    115,
    14,
    48,
    56,
    0,
    110,
    18,
    121,
    128,
    229,
    43,
    156,
    206,
    43,
    100,
    220,
    158,
    195,
    152,
    14,
    50,
    184,
    0,
    225,
    39,
    156,
    126,
    77,
    56,
    187,
    224,
    3,
    132,
    70,
    230,
    2,
    7,
    147,
    110,
    0,
    56,
    80,
    230,
    244,
    242,
    133,
    194,
    45,
    199,
    147,
    46,
    17,
    121,
    204,
    226,
    228,
    77,
    249,
    202,
    228,
    203,
    132,
    94,
    50,
    121,
    45,
    231,
    42,
    92,
    102,
    114,
    123,
    194,
    175,
    53,
    181,
    114,
    105,
    143,
    55,
    117,
    114,
    123,
    194,
    143,
    48,
    23,
    113,
    152,
    56,
    54,
    230,
    247,
    56,
    51,
    243,
    1,
    202,
    63,
    57,
    60,
    25,
    113,
    129,
    201,
    207,
    8,
    188,
    224,
    113,
    146,
    220,
    165,
    99,
    205,
    111,
    24,
    28,
    154,
    112,
    147,
    205,
    239,
    25,
    77,
    202,
    79,
    8,
    252,
    218,
    113,
    118,
    194,
    124,
    192,
    82,
    120,
    80,
    28,
    219,
    62,
    60,
    158,
    243,
    138,
    115,
    181,
    112,
    109,
    198,
    128,
    224,
    203,
    156,
    94,
    51,
    44,
    161,
    78,
    161,
    193,
    149,
    198,
    54,
    243,
    171,
    46,
    53,
    185,
    88,
    224,
    247,
    157,
    90,
    162,
    46,
    151,
    24,
    252,
    157,
    240,
    163,
    206,
    5,
    66,
    87,
    30,
    13,
    168,
    231,
    51,
    131,
    215,
    25,
    210,
    120,
    54,
    229,
    65,
    112,
    100,
    252,
    166,
    89,
    206,
    41,
    157,
    171,
    131,
    46,
    52,
    4,
    105,
    194,
    92,
    171,
    115,
    177,
    193,
    238,
    22,
    197,
    113,
    161,
    46,
    81,
    249,
    187,
    225,
    71,
    140,
    1,
    76,
    143,
    42,
    10,
    183,
    229,
    50,
    254,
    113,
    79,
    6,
    214,
    170,
    248,
    208,
    28,
    25,
    115,
    139,
    198,
    101,
    148,
    41,
    212,
    56,
    50,
    184,
    198,
    222,
    117,
    101,
    198,
    183,
    43,
    28,
    30,
    243,
    171,
    84,
    69,
    213,
    241,
    143,
    201,
    127,
    10,
    60,
    220,
    84,
    43,
    184,
    215,
    71,
    57,
    215,
    184,
    224,
    218,
    147,
    95,
    42,
    11,
    131,
    39,
    229,
    50,
    206,
    113,
    76,
    237,
    92,
    25,
    113,
    160,
    35,
    78,
    18,
    229,
    91,
    157,
    140,
    176,
    182,
    43,
    141,
    10,
    249,
    71,
    230,
    191,
    132,
    78,
    46,
    27,
    152,
    14,
    80,
    56,
    0,
    131,
    112,
    139,
    198,
    72,
    230,
    219,
    128,
    14,
    20,
    56,
    189,
    11,
    55,
    229,
    67,
    133,
    21,
    197,
    149,
    24,
    241,
    114,
    132,
    223,
    156,
    174,
    12,
    168,
    227,
    38,
    60,
    229,
    114,
    105,
    194,
    47,
    25,
    156,
    158,
    243,
    147,
    30,
    49,
    57,
    71,
    151,
    55,
    115,
    131,
    63,
    48,
    28,
    162,
    115,
    129,
    194,
    47,
    22,
    220,
    157,
    240,
    1,
    14,
    96,
    38,
    237,
    202,
    63,
    57,
    60,
    25,
    113,
    129,
    68,
    249,
    199,
    227,
    38,
    124,
    164,
    243,
    129,
    198,
    86,
    60,
    150,
    243,
    129,
    198,
    76,
    185,
    74,
    231,
    51,
    131,
    222,
    48,
    57,
    74,
    143,
    57,
    60,
    99,
    203,
    148,
    14,
    114,
    178,
    227,
    39,
    148,
    121,
    243,
    137,
    3,
    193,
    179,
    114,
    161,
    205,
    239,
    10,
    60,
    97,
    81,
    119,
    6,
    199,
    147,
    46,
    17,
    121,
    204,
    226,
    228,
    77,
    249,
    202,
    228,
    203,
    132,
    94,
    50,
    121,
    45,
    231,
    42,
    92,
    102,
    114,
    123,
    194,
    175,
    53,
    181,
    114,
    105,
    143,
    55,
    117,
    114,
    129,
    194,
    143,
    54,
    156,
    104,
    114,
    153,
    194,
    143,
    54,
    220,
    94,
    230,
    220,
    192,
    81,
    14,
    49,
    249,
    201,
    224,
    203,
    148,
    7,
    179,
    156,
    126,
    82,
    103,
    198,
    7,
    57,
    60,
    25,
    114,
    149,
    198,
    100,
    121,
    192,
    229,
    38,
    92,
    101,
    115,
    153,
    193,
    239,
    40,
    28,
    101,
    71,
    156,
    158,
    81,
    248,
    40,
    227,
    3,
    156,
    78,
    11,
    249,
    71,
    60,
    28,
    82,
    56,
    40,
    227,
    65,
    87,
    71,
    25,
    151,
    243,
    138,
    56,
    54,
    52,
    240,
    167,
    201,
    87,
    26,
    11,
    131,
    42,
    56,
    204,
    179,
    156,
    81,
    193,
    241,
    167,
    133,
    30,
    76,
    184,
    208,
    81,
    183,
    9,
    115,
    173,
    202,
    198,
    88,
    83,
    17,
    198,
    133,
    124,
    227,
    242,
    153,
    193,
    127,
    24,
    235,
    131,
    129,
    87,
    10,
    58,
    242,
    160,
    107,
    231,
    23,
    148,
    203,
    221,
    112,
    108,
    42,
    225,
    79,
    94,
    84,
    15,
    6,
    92,
    226,
    242,
    153,
    99,
    174,
    15,
    133,
    92,
    40,
    243,
    101,
    202,
    129,
    141,
    58,
    75,
    141,
    110,
    118,
    50,
    210,
    168,
    174,
    84,
    43,
    227,
    31,
    156,
    206,
    11,
    249,
    71,
    60,
    28,
    43,
    120,
    81,
    218,
    225,
    91,
    243,
    153,
    125,
    7,
    131,
    106,
    69,
    124,
    104,
    46,
    12,
    168,
    227,
    50,
    206,
    113,
    71,
    7,
    213,
    46,
    12,
    185,
    80,
    49,
    167,
    73,
    113,
    173,
    206,
    198,
    90,
    85,
    21,
    202,
    133,
    124,
    99,
    243,
    95,
    194,
    143,
    39,
    6,
    158,
    20,
    249,
    42,
    227,
    65,
    87,
    71,
    25,
    151,
    243,
    138,
    56,
    54,
    52,
    240,
    163,
    201,
    87,
    26,
    11,
    131,
    42,
    56,
    204,
    179,
    156,
    81,
    51,
    79,
    10,
    60,
    153,
    113,
    160,
    163,
    110,
    18,
    231,
    91,
    149,
    142,
    15,
    112,
    166,
    35,
    141,
    14,
    10,
    57,
    202,
    228,
    191,
    132,
    78,
    46,
    57,
    64,
    230,
    1,
    112,
    109,
    197,
    239,
    42,
    28,
    40,
    195,
    141,
    14,
    114,
    121,
    80,
    224,
    219,
    140,
    206,
    15,
    135,
    56,
    92,
    37,
    113,
    109,
    202,
    79,
    54,
    156,
    37,
    113,
    123,
    202,
    103,
    56,
    188,
    36,
    195,
    140,
    126,
    80,
    57,
    196,
    224,
    3,
    132,
    88,
    55,
    48,
    28,
    98,
    114,
    123,
    206,
    7,
    8,
    187,
    95,
    198,
    3,
    81,
    192,
    7,
    8,
    252,
    228,
    241,
    101,
    202,
    5,
    143,
    206,
    23,
    9,
    45,
    202,
    81,
    230,
    219,
    133,
    14,
    79,
    79,
    56,
    92,
    40,
    55,
    41,
    60,
    102,
    46,
    12,
    177,
    226,
    228,
    115,
    133,
    194,
    87,
    22,
    92,
    164,
    243,
    91,
    194,
    87,
    22,
    156,
    166,
    115,
    123,
    194,
    172,
    56,
    204,
    28,
    218,
    100,
    237,
    204,
    5,
    28,
    0,
    112,
    137,
    206,
    3,
    242,
    85,
    127,
    22,
    205,
    204,
    5,
    28,
    0,
    112,
    143,
    206,
    79,
    22,
    92,
    160,
    88,
    252,
    223,
    112,
    146,
    220,
    165,
    113,
    153,
    205,
    108,
    249,
    52,
    126,
    109,
    184,
    74,
    110,
    82,
    120,
    199,
    230,
    162,
    246,
    229,
    3,
    139,
    142,
    96,
    56,
    0,
    225,
    23,
    88,
    55,
    23,
    59,
    240,
    123,
    205,
    180,
    27,
    140,
    46,
    0,
    57,
    128,
    225,
    22,
    28,
    0,
    112,
    0
  };

static const uint8 s_melody5_stream2[433] = {
    88,
    27,
    208,
    14,
    128,
    2,
    7,
    80,
    9,
    128,
    116,
    4,
    192,
    78,
    1,
    56,
    34,
    64,
    176,
    0,
    2,
    138,
    41,
    184,
    24,
    75,
    112,
    48,
    148,
    83,
    34,
    184,
    112,
    128,
    40,
    162,
    155,
    129,
    132,
    183,
    3,
    9,
    69,
    50,
    43,
    135,
    8,
    2,
    136,
    0,
    0,
    1,
    0,
    2,
    1,
    69,
    18,
    145,
    41,
    49,
    224,
    97,
    104,
    2,
    163,
    38,
    48,
    13,
    0,
    84,
    100,
    199,
    129,
    133,
    160,
    10,
    140,
    152,
    240,
    48,
    180,
    1,
    81,
    147,
    21,
    192,
    194,
    91,
    129,
    132,
    128,
    0,
    0,
    16,
    0,
    32,
    20,
    81,
    69,
    20,
    81,
    77,
    0,
    74,
    76,
    120,
    24,
    90,
    0,
    162,
    138,
    104,
    2,
    138,
    41,
    160,
    10,
    140,
    139,
    64,
    0,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    64,
    32,
    16,
    8,
    5,
    20,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    69,
    16,
    238,
    225,
    200,
    4,
    3,
    192,
    174,
    228,
    2,
    1,
    0,
    240,
    43,
    185,
    0,
    128,
    64,
    32,
    16,
    10,
    40,
    240,
    43,
    185,
    0,
    128,
    64,
    60,
    10,
    238,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    64,
    40,
    163,
    51,
    40,
    158,
    11,
    14,
    17,
    42,
    40,
    49,
    145,
    0,
    128,
    1,
    0,
    128,
    64,
    32,
    20,
    81,
    40,
    162,
    82,
    99,
    192,
    194,
    208,
    4,
    169,
    147,
    0,
    208,
    4,
    2,
    0,
    4,
    2,
    1,
    0,
    128,
    64,
    32,
    16,
    10,
    140,
    139,
    112,
    48,
    144,
    0,
    32,
    0,
    64,
    0,
    128,
    81,
    69,
    20,
    81,
    69,
    16,
    9,
    73,
    143,
    3,
    11,
    64,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    67,
    185,
    0,
    128,
    64,
    33,
    220,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    14,
    228,
    2,
    1,
    0,
    135,
    114,
    1,
    0,
    128,
    67,
    185,
    0,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    29,
    200,
    4,
    2,
    1,
    0,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1,
    0,
    128,
    81,
    68,
    59,
    144,
    8,
    4,
    2,
    29,
    200,
    4,
    2,
    1,
    14,
    228,
    2,
    1,
    0,
    128,
    64,
    40,
    162,
    155,
    129,
    132,
    148,
    155,
    129,
    133,
    18,
    138,
    40,
    162,
    138,
    41,
    184,
    24,
    73,
    159,
    3,
    11,
    19,
    192,
    194,
    137,
    41,
    55,
    3,
    11,
    64,
    20,
    81,
    77,
    0,
    81,
    69,
    55,
    3,
    9,
    37,
    20,
    81,
    69,
    20,
    83,
    112,
    48,
    146,
    147,
    30,
    6,
    22,
    128,
    37,
    38,
    60,
    12,
    45,
    0,
    81,
    69,
    52,
    1,
    69,
    20,
    208,
    5,
    70,
    69,
    151,
    3,
    9,
    99,
    192,
    194,
    81,
    153,
    148,
    79,
    3,
    12,
    120,
    44,
    13,
    32
  };

const MelodyMIDI melody5 = {
    s_melody5_stream1,
    s_melody5_stream2
  };

