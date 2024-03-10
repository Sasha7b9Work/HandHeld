// 2024/03/02 09:33:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#ifdef GUI
    #define WIN32_LEAN_AND_MEAN
    #include "wx/wx.h"

enum
{
    ID_BUTTON_MENU = wxID_HIGHEST + 1,
    ID_BUTTON_CANCEL,
    ID_BUTTON_UP,
    ID_BUTTON_DOWN
};
#endif


typedef signed char    int8;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint;
typedef const char    *pchar;
typedef unsigned char  uchar;


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic ignored "-Wold-style-cast"
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
    #pragma clang diagnostic ignored "-Wglobal-constructors"
    #pragma clang diagnostic ignored "-Wpadded"
    #pragma clang diagnostic ignored "-Winvalid-source-encoding"
    #pragma clang diagnostic ignored "-Wc++98-compat"
    #pragma clang diagnostic ignored "-Wformat-nonliteral"
#else
#endif


#define _bitset(bits)                               \
  ((uint8)(                                         \
  (((uint8)((uint)bits / 01)        % 010) << 0) |  \
  (((uint8)((uint)bits / 010)       % 010) << 1) |  \
  (((uint8)((uint)bits / 0100)      % 010) << 2) |  \
  (((uint8)((uint)bits / 01000)     % 010) << 3) |  \
  (((uint8)((uint)bits / 010000)    % 010) << 4) |  \
  (((uint8)((uint)bits / 0100000)   % 010) << 5) |  \
  (((uint8)((uint)bits / 01000000)  % 010) << 6) |  \
  (((uint8)((uint)bits / 010000000) % 010) << 7)))

#define BINARY_U8( bits ) _bitset(0##bits)

#define ENABLED_RU "Вкл"
#define DISABLED_RU "Откл"
