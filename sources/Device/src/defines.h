// 2024/03/02 09:33:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic ignored "-Wold-style-cast"
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#else
#endif
