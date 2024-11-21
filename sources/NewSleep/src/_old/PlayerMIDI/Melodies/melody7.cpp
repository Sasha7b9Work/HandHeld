#include "defines.h"
#include "PlayerMIDI/Melodies/melody7.h"
#include "PlayerMIDI/PlayerMIDI.h"

//Player frequency=18000
//Player minimum channels count =4
static const uint8 s_melody7_stream1[956] = {
    120,
    20,
    216,
    0,
    16,
    4,
    0,
    37,
    11,
    225,
    114,
    51,
    2,
    1,
    192,
    25,
    230,
    240,
    230,
    133,
    17,
    102,
    10,
    248,
    197,
    228,
    203,
    155,
    238,
    14,
    120,
    77,
    43,
    152,
    14,
    49,
    121,
    67,
    230,
    203,
    131,
    222,
    19,
    10,
    230,
    3,
    140,
    30,
    81,
    121,
    178,
    224,
    229,
    184,
    196,
    92,
    192,
    114,
    138,
    57,
    197,
    227,
    43,
    147,
    158,
    13,
    120,
    54,
    43,
    152,
    14,
    50,
    57,
    67,
    231,
    27,
    131,
    115,
    198,
    48,
    92,
    31,
    114,
    121,
    205,
    111,
    22,
    92,
    33,
    21,
    204,
    7,
    23,
    92,
    159,
    115,
    101,
    193,
    119,
    8,
    124,
    97,
    242,
    129,
    206,
    103,
    7,
    77,
    198,
    7,
    40,
    124,
    229,
    112,
    105,
    194,
    73,
    92,
    192,
    113,
    110,
    56,
    69,
    229,
    31,
    156,
    158,
    47,
    120,
    57,
    229,
    1,
    163,
    202,
    143,
    54,
    160,
    240,
    131,
    14,
    79,
    185,
    128,
    230,
    208,
    21,
    194,
    47,
    24,
    252,
    164,
    243,
    135,
    193,
    207,
    23,
    173,
    30,
    84,
    121,
    178,
    7,
    131,
    200,
    114,
    133,
    204,
    7,
    57,
    92,
    39,
    241,
    86,
    185,
    77,
    231,
    49,
    163,
    202,
    87,
    56,
    124,
    91,
    240,
    125,
    194,
    79,
    25,
    92,
    166,
    243,
    88,
    15,
    7,
    220,
    93,
    242,
    113,
    206,
    15,
    9,
    156,
    101,
    114,
    91,
    204,
    7,
    57,
    35,
    132,
    131,
    198,
    15,
    39,
    220,
    220,
    240,
    143,
    198,
    55,
    37,
    188,
    192,
    115,
    138,
    56,
    65,
    60,
    94,
    242,
    115,
    205,
    188,
    184,
    193,
    229,
    3,
    155,
    238,
    13,
    97,
    201,
    151,
    8,
    37,
    115,
    1,
    198,
    47,
    38,
    252,
    220,
    142,
    17,
    207,
    24,
    11,
    152,
    14,
    82,
    71,
    6,
    188,
    220,
    158,
    50,
    185,
    62,
    224,
    227,
    152,
    14,
    114,
    96,
    185,
    62,
    224,
    219,
    140,
    142,
    96,
    57,
    198,
    11,
    132,
    94,
    79,
    15,
    21,
    124,
    217,
    112,
    135,
    201,
    211,
    243,
    116,
    19,
    30,
    44,
    57,
    50,
    230,
    3,
    156,
    97,
    193,
    177,
    92,
    98,
    243,
    1,
    201,
    119,
    54,
    67,
    132,
    62,
    45,
    249,
    64,
    230,
    3,
    156,
    78,
    15,
    143,
    21,
    188,
    154,
    112,
    125,
    206,
    47,
    23,
    168,
    75,
    152,
    14,
    78,
    169,
    60,
    100,
    55,
    41,
    156,
    225,
    241,
    155,
    194,
    127,
    41,
    20,
    195,
    132,
    30,
    48,
    57,
    67,
    230,
    0,
    112,
    130,
    120,
    193,
    230,
    223,
    147,
    158,
    17,
    120,
    199,
    229,
    38,
    109,
    30,
    81,
    121,
    185,
    224,
    213,
    248,
    61,
    229,
    3,
    152,
    2,
    252,
    213,
    142,
    15,
    57,
    50,
    226,
    222,
    124,
    32,
    241,
    135,
    201,
    215,
    56,
    188,
    35,
    113,
    92,
    185,
    70,
    230,
    3,
    156,
    81,
    193,
    244,
    57,
    53,
    231,
    19,
    132,
    62,
    43,
    87,
    40,
    92,
    192,
    115,
    130,
    56,
    57,
    226,
    223,
    147,
    222,
    111,
    229,
    197,
    175,
    39,
    60,
    211,
    112,
    91,
    193,
    239,
    23,
    171,
    152,
    14,
    79,
    135,
    5,
    199,
    140,
    62,
    113,
    87,
    40,
    220,
    30,
    113,
    111,
    62,
    17,
    248,
    200,
    229,
    55,
    154,
    209,
    194,
    97,
    143,
    40,
    52,
    240,
    114,
    220,
    101,
    114,
    87,
    204,
    4,
    248,
    65,
    227,
    11,
    148,
    142,
    110,
    165,
    194,
    31,
    24,
    156,
    163,
    115,
    83,
    194,
    71,
    24,
    252,
    165,
    115,
    139,
    14,
    15,
    56,
    72,
    226,
    185,
    115,
    1,
    202,
    31,
    56,
    163,
    132,
    110,
    48,
    57,
    55,
    167,
    132,
    126,
    50,
    57,
    77,
    230,
    180,
    112,
    152,
    99,
    201,
    205,
    60,
    32,
    183,
    25,
    92,
    149,
    243,
    1,
    62,
    15,
    248,
    192,
    229,
    39,
    155,
    126,
    14,
    120,
    65,
    227,
    3,
    148,
    110,
    106,
    91,
    140,
    158,
    81,
    121,
    204,
    226,
    215,
    131,
    230,
    227,
    55,
    146,
    94,
    96,
    57,
    195,
    225,
    11,
    140,
    62,
    83,
    57,
    183,
    224,
    231,
    132,
    94,
    48,
    249,
    74,
    230,
    187,
    132,
    216,
    242,
    91,
    205,
    167,
    7,
    60,
    96,
    114,
    135,
    206,
    79,
    10,
    69,
    115,
    0,
    43,
    226,
    171,
    149,
    30,
    116,
    7,
    10,
    79,
    201,
    231,
    54,
    213,
    241,
    163,
    201,
    95,
    48,
    28,
    231,
    240,
    156,
    252,
    168,
    243,
    117,
    194,
    15,
    22,
    242,
    163,
    147,
    238,
    108,
    56,
    55,
    226,
    243,
    148,
    30,
    115,
    248,
    78,
    227,
    71,
    148,
    14,
    96,
    57,
    207,
    28,
    39,
    241,
    82,
    185,
    77,
    231,
    51,
    131,
    202,
    57,
    53,
    224,
    230,
    124,
    31,
    113,
    155,
    201,
    239,
    53,
    220,
    29,
    113,
    129,
    201,
    173,
    92,
    38,
    81,
    201,
    247,
    48,
    21,
    14,
    19,
    120,
    171,
    92,
    166,
    115,
    149,
    194,
    107,
    242,
    111,
    205,
    215,
    9,
    156,
    101,
    114,
    81,
    204,
    7,
    56,
    99,
    132,
    83,
    198,
    55,
    38,
    252,
    223,
    112,
    105,
    194,
    108,
    121,
    74,
    230,
    183,
    132,
    158,
    50,
    57,
    73,
    159,
    6,
    144,
    225,
    23,
    138,
    165,
    204,
    7,
    42,
    60,
    232,
    14,
    20,
    159,
    147,
    206,
    109,
    171,
    227,
    71,
    146,
    190,
    96,
    57,
    207,
    225,
    57,
    249,
    81,
    230,
    223,
    131,
    174,
    48,
    101,
    71,
    39,
    220,
    216,
    112,
    111,
    198,
    15,
    39,
    156,
    231,
    240,
    157,
    198,
    143,
    40,
    28,
    192,
    115,
    158,
    56,
    79,
    226,
    165,
    114,
    155,
    206,
    103,
    7,
    148,
    114,
    115,
    46,
    109,
    120,
    62,
    227,
    55,
    147,
    222,
    107,
    184,
    58,
    227,
    3,
    147,
    90,
    184,
    76,
    163,
    147,
    238,
    96,
    42,
    28,
    38,
    241,
    86,
    185,
    76,
    231,
    43,
    132,
    215,
    228,
    235,
    155,
    126,
    19,
    56,
    202,
    228,
    163,
    152,
    14,
    112,
    199,
    8,
    167,
    140,
    110,
    77,
    57,
    190,
    224,
    223,
    132,
    216,
    242,
    149,
    205,
    111,
    9,
    60,
    100,
    114,
    147,
    205,
    167,
    7,
    60,
    96,
    112,
    138,
    252,
    154,
    115,
    117,
    111,
    8,
    124,
    97,
    114,
    139,
    204,
    0,
    225,
    12,
    241,
    123,
    206,
    31,
    39,
    60,
    22,
    240,
    105,
    103,
    38,
    188,
    192,
    14,
    13,
    11,
    243,
    87,
    201,
    215,
    6,
    156,
    33,
    241,
    133,
    202,
    47,
    48,
    3,
    132,
    51,
    197,
    239,
    56,
    124,
    150,
    240,
    115,
    193,
    165,
    156,
    154,
    243,
    0,
    56,
    52,
    48,
    92,
    155,
    142,
    15,
    143,
    23,
    171,
    148,
    17,
    46,
    111,
    138,
    226,
    244,
    112,
    117,
    204,
    1,
    128,
    0
  };

static const uint8 s_melody7_stream2[629] = {
    144,
    20,
    216,
    0,
    64,
    138,
    4,
    64,
    22,
    129,
    12,
    3,
    0,
    71,
    1,
    72,
    17,
    128,
    94,
    2,
    160,
    13,
    128,
    76,
    1,
    32,
    25,
    0,
    232,
    35,
    0,
    0,
    0,
    224,
    210,
    224,
    44,
    3,
    130,
    132,
    1,
    193,
    169,
    72,
    28,
    20,
    64,
    14,
    6,
    142,
    6,
    142,
    2,
    225,
    192,
    115,
    192,
    93,
    192,
    114,
    0,
    224,
    208,
    224,
    46,
    3,
    128,
    231,
    129,
    160,
    14,
    9,
    110,
    3,
    158,
    2,
    225,
    193,
    60,
    0,
    224,
    212,
    164,
    14,
    10,
    32,
    7,
    3,
    71,
    3,
    32,
    3,
    129,
    159,
    129,
    156,
    1,
    193,
    162,
    192,
    112,
    81,
    183,
    0,
    186,
    64,
    7,
    36,
    112,
    58,
    30,
    1,
    192,
    37,
    193,
    80,
    192,
    112,
    11,
    164,
    0,
    115,
    49,
    192,
    230,
    120,
    7,
    0,
    151,
    2,
    15,
    3,
    80,
    151,
    0,
    225,
    110,
    0,
    238,
    0,
    224,
    1,
    60,
    9,
    3,
    129,
    192,
    240,
    13,
    0,
    9,
    224,
    73,
    166,
    170,
    120,
    6,
    184,
    10,
    248,
    6,
    128,
    36,
    183,
    0,
    187,
    65,
    160,
    7,
    3,
    135,
    0,
    127,
    0,
    124,
    192,
    28,
    24,
    252,
    6,
    224,
    75,
    129,
    140,
    112,
    29,
    240,
    19,
    112,
    28,
    211,
    192,
    114,
    56,
    11,
    56,
    13,
    104,
    28,
    6,
    140,
    56,
    24,
    248,
    14,
    100,
    56,
    14,
    36,
    56,
    23,
    248,
    15,
    120,
    8,
    184,
    15,
    199,
    1,
    16,
    224,
    60,
    224,
    14,
    224,
    14,
    224,
    14,
    28,
    12,
    92,
    12,
    28,
    7,
    131,
    128,
    143,
    128,
    255,
    128,
    132,
    112,
    31,
    112,
    16,
    240,
    30,
    240,
    17,
    240,
    30,
    14,
    2,
    94,
    3,
    169,
    14,
    3,
    142,
    2,
    177,
    192,
    199,
    192,
    111,
    192,
    92,
    56,
    13,
    120,
    5,
    248,
    3,
    120,
    3,
    184,
    25,
    56,
    25,
    56,
    10,
    56,
    3,
    184,
    12,
    120,
    12,
    184,
    13,
    131,
    112,
    11,
    240,
    33,
    112,
    36,
    4,
    144,
    4,
    199,
    128,
    176,
    193,
    170,
    0,
    240,
    33,
    76,
    36,
    128,
    38,
    60,
    5,
    134,
    28,
    5,
    98,
    0,
    18,
    65,
    60,
    8,
    92,
    6,
    53,
    240,
    24,
    215,
    192,
    99,
    88,
    4,
    158,
    2,
    232,
    112,
    22,
    67,
    128,
    178,
    0,
    19,
    48,
    7,
    4,
    119,
    2,
    103,
    1,
    32,
    224,
    120,
    224,
    21,
    224,
    56,
    175,
    128,
    197,
    248,
    9,
    248,
    7,
    0,
    14,
    238,
    56,
    29,
    235,
    224,
    48,
    224,
    20,
    0,
    112,
    70,
    204,
    83,
    192,
    56,
    144,
    1,
    212,
    195,
    185,
    0,
    112,
    69,
    30,
    2,
    225,
    192,
    44,
    252,
    6,
    28,
    2,
    64,
    7,
    119,
    28,
    14,
    245,
    240,
    24,
    112,
    10,
    0,
    56,
    35,
    102,
    41,
    224,
    28,
    72,
    0,
    234,
    97,
    220,
    128,
    56,
    34,
    136,
    224,
    46,
    224,
    23,
    72,
    0,
    234,
    97,
    231,
    192,
    71,
    101,
    150,
    89,
    192,
    21,
    192,
    21,
    193,
    191,
    103,
    0,
    87,
    0,
    87,
    2,
    204,
    98,
    105,
    168,
    1,
    193,
    23,
    17,
    192,
    87,
    4,
    8,
    0,
    145,
    71,
    0,
    208,
    4,
    145,
    192,
    233,
    192,
    46,
    214,
    142,
    2,
    184,
    32,
    64,
    4,
    138,
    56,
    6,
    128,
    36,
    142,
    7,
    78,
    1,
    118,
    180,
    112,
    21,
    193,
    16,
    1,
    37,
    160,
    220,
    2,
    237,
    192,
    46,
    0,
    38,
    33,
    210,
    0,
    95,
    192,
    145,
    33,
    113,
    149,
    64,
    14,
    8,
    184,
    142,
    2,
    184,
    32,
    64,
    4,
    138,
    56,
    6,
    128,
    36,
    142,
    7,
    78,
    1,
    118,
    180,
    112,
    21,
    193,
    2,
    0,
    36,
    81,
    192,
    52,
    1,
    36,
    112,
    58,
    112,
    11,
    181,
    163,
    128,
    174,
    8,
    128,
    9,
    45,
    6,
    224,
    23,
    110,
    1,
    112,
    1,
    49,
    14,
    144,
    2,
    248,
    128,
    34,
    149,
    17,
    224,
    21,
    163,
    128,
    88,
    0,
    84,
    88,
    213,
    43,
    128,
    17,
    74,
    136,
    240,
    10,
    209,
    192,
    44,
    0,
    42,
    44,
    106,
    149,
    210,
    224,
    97,
    106,
    184,
    11,
    56,
    23,
    184,
    11,
    56,
    5,
    248,
    12,
    56,
    5,
    15,
    1,
    131,
    240,
    11,
    112,
    23,
    112,
    11,
    183,
    4,
    87,
    0,
    228,
    134,
    0
  };

const MelodyMIDI melody7 =
{
    s_melody7_stream1,
    s_melody7_stream2
};

