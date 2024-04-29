#ifndef H_RU_FONT
#define H_RU_FONT
/*
 * HD44780 2 line symbol display driver.
 *
 * Copyright 2023 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/* Для классического шрифта закомментируйте все макросы, иначе раскомментируйте те случаи
   экономии знакомест, которые считаете незаметными. */
// латинская r как русская г
//#define ECONOMY_gr
// латинская g как русская д
//#define ECONOMY_dg
// экономия на замене ё на е
//#define ECONOMY_joe
// латинская u как русская и
//#define ECONOMY_iu
// экономия на замене й на и
//#define ECONOMY_ji
// латинская k и русская k одно и то же
//#define ECONOMY_kk
// латинская m и русская м одно и то же
//#define ECONOMY_mm
// латинская m как русская т
//#define ECONOMY_tm
// латинская n как русская п
//#define ECONOMY_pn
// 4 как русская ч
//#define ECONOMY_сh4
// 4 как русская Ч
//#define ECONOMY_CH4
// экономия на мягком знаке вместо твердого
//#define ECONOMY_tzmz
// латинская R как русская Я
//#define ECONOMY_YAR
// латинская N как русская И
//#define ECONOMY_IN
// латинский Y как русский У
//#define ECONOMY_UY

const uint8_t ru_b[8]  = {0x00, 0x03, 0x0C, 0x10, 0x1E, 0x11, 0x11, 0x0E};
const uint8_t ru_v[8]  = {0x00, 0x00, 0x00, 0x1C, 0x12, 0x1C, 0x12, 0x1C};
const uint8_t ru_g[8]  = {0x00, 0x00, 0x00, 0x1F, 0x11, 0x10, 0x10, 0x10};
const uint8_t ru_d[8]  = {0x00, 0x00, 0x0F, 0x05, 0x09, 0x11, 0x1F, 0x11};
const uint8_t ru_jo[8] = {0x00, 0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E};
const uint8_t ru_zh[8] = {0x00, 0x00, 0x00, 0x15, 0x15, 0x0E, 0x15, 0x15};
const uint8_t ru_z[8]  = {0x00, 0x00, 0x00, 0x1E, 0x01, 0x06, 0x01, 0x1E};
const uint8_t ru_i[8]  = {0x00, 0x00, 0x00, 0x11, 0x13, 0x15, 0x19, 0x11};
const uint8_t ru_j[8]  = {0x00, 0x00, 0x0A, 0x04, 0x11, 0x13, 0x15, 0x19};
const uint8_t ru_k[8]  = {0x00, 0x00, 0x00, 0x12, 0x14, 0x18, 0x14, 0x12};
const uint8_t ru_l[8]  = {0x00, 0x00, 0x00, 0x0F, 0x05, 0x05, 0x15, 0x09};
const uint8_t ru_m[8]  = {0x00, 0x00, 0x00, 0x11, 0x1B, 0x15, 0x11, 0x11};
const uint8_t ru_n[8]  = {0x00, 0x00, 0x00, 0x11, 0x11, 0x1F, 0x11, 0x11};
const uint8_t ru_p[8]  = {0x00, 0x00, 0x00, 0x1F, 0x11, 0x11, 0x11, 0x11};
const uint8_t ru_t[8]  = {0x00, 0x00, 0x00, 0x1F, 0x04, 0x04, 0x04, 0x04};
const uint8_t ru_f[8]  = {0x00, 0x04, 0x04, 0x0E, 0x15, 0x15, 0x0E, 0x04};
const uint8_t ru_c[8]  = {0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x1F, 0x01};
const uint8_t ru_ch[8] = {0x00, 0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x01};
const uint8_t ru_sh[8] = {0x00, 0x00, 0x00, 0x15, 0x15, 0x15, 0x15, 0x1F};
const uint8_t ru_shh[8]= {0x00, 0x00, 0x00, 0x15, 0x15, 0x15, 0x1F, 0x01};
const uint8_t ru_tz[8] = {0x00, 0x00, 0x00, 0x18, 0x08, 0x0E, 0x09, 0x0E};
const uint8_t ru_y[8]  = {0x00, 0x00, 0x00, 0x11, 0x11, 0x1D, 0x13, 0x1D};
const uint8_t ru_mz[8] = {0x00, 0x00, 0x00, 0x10, 0x10, 0x1C, 0x12, 0x1C};
const uint8_t ru_e[8]  = {0x00, 0x00, 0x00, 0x0E, 0x11, 0x07, 0x11, 0x0E};
const uint8_t ru_ju[8] = {0x00, 0x00, 0x00, 0x12, 0x15, 0x1D, 0x15, 0x12};
const uint8_t ru_ja[8] = {0x00, 0x00, 0x00, 0x0F, 0x11, 0x0F, 0x05, 0x09};
const uint8_t ru_B[8]  = {0x00, 0x1F, 0x11, 0x10, 0x1E, 0x11, 0x11, 0x1E};
const uint8_t ru_G[8]  = {0x00, 0x1F, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10};
const uint8_t ru_D[8]  = {0x00, 0x0F, 0x05, 0x05, 0x09, 0x11, 0x1F, 0x11};
const uint8_t ru_JO[8] = {0x00, 0x0A, 0x00, 0x1E, 0x10, 0x1C, 0x10, 0x1E};
const uint8_t ru_ZH[8] = {0x00, 0x15, 0x15, 0x15, 0x0E, 0x15, 0x15, 0x15};
const uint8_t ru_Z[8]  = {0x00, 0x1E, 0x01, 0x01, 0x06, 0x01, 0x01, 0x1E};
const uint8_t ru_I[8]  = {0x00, 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11};
const uint8_t ru_J[8]  = {0x0A, 0x04, 0x11, 0x11, 0x13, 0x15, 0x19, 0x11};
const uint8_t ru_L[8]  = {0x00, 0x0F, 0x05, 0x05, 0x05, 0x05, 0x15, 0x09};
const uint8_t ru_P[8]  = {0x00, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
const uint8_t ru_U[8]  = {0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x08, 0x10};
const uint8_t ru_F[8]  = {0x00, 0x04, 0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04};
const uint8_t ru_C[8]  = {0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x01};
const uint8_t ru_CH[8] = {0x00, 0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01};
const uint8_t ru_SH[8] = {0x00, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F};
const uint8_t ru_SHH[8]= {0x00, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x01};
const uint8_t ru_TZ[8] = {0x00, 0x18, 0x08, 0x08, 0x0E, 0x09, 0x09, 0x0E};
const uint8_t ru_Y[8]  = {0x00, 0x11, 0x11, 0x11, 0x19, 0x15, 0x15, 0x19};
const uint8_t ru_MZ[8] = {0x00, 0x10, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E};
const uint8_t ru_E[8]  = {0x00, 0x0E, 0x11, 0x05, 0x0B, 0x01, 0x11, 0x0E};
const uint8_t ru_JU[8] = {0x00, 0x12, 0x15, 0x15, 0x1D, 0x15, 0x15, 0x12};
const uint8_t ru_JA[8] = {0x00, 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11};

#define RU_U8_a     0xb0
#define RU_U8_b     0xb1
#define RU_U8_v     0xb2
#define RU_U8_g     0xb3
#define RU_U8_d     0xb4
#define RU_U8_e     0xb5
#define RU_U8_jo    0x70
#define RU_U8_zh    0xb6
#define RU_U8_z     0xb7
#define RU_U8_i     0xb8
#define RU_U8_j     0xb9
#define RU_U8_k     0xba
#define RU_U8_l     0xbb
#define RU_U8_m     0xbc
#define RU_U8_n     0xbd
#define RU_U8_o     0xbe
#define RU_U8_p     0xbf
#define RU_U8_r     0x80
#define RU_U8_s     0x81
#define RU_U8_t     0x82
#define RU_U8_u     0x83
#define RU_U8_f     0x84
#define RU_U8_h     0x85
#define RU_U8_c     0x86
#define RU_U8_ch    0x87
#define RU_U8_sh    0x88
#define RU_U8_shh   0x89
#define RU_U8_tz    0x8a
#define RU_U8_y     0x8b
#define RU_U8_mz    0x8c
#define RU_U8_ee    0x8d
#define RU_U8_ju    0x8e
#define RU_U8_ja    0x8f
#define RU_U8_A     0x90
#define RU_U8_B     0x91
#define RU_U8_V     0x92
#define RU_U8_G     0x93
#define RU_U8_D     0x94
#define RU_U8_E     0x95
#define RU_U8_JO    0x71
#define RU_U8_ZH    0x96
#define RU_U8_Z     0x97
#define RU_U8_I     0x98
#define RU_U8_J     0x99
#define RU_U8_K     0x9a
#define RU_U8_L     0x9b
#define RU_U8_M     0x9c
#define RU_U8_N     0x9d
#define RU_U8_O     0x9e
#define RU_U8_P     0x9f
#define RU_U8_R     0xa0
#define RU_U8_S     0xa1
#define RU_U8_T     0xa2
#define RU_U8_U     0xa3
#define RU_U8_F     0xa4
#define RU_U8_H     0xa5
#define RU_U8_C     0xa6
#define RU_U8_CH    0xa7
#define RU_U8_SH    0xa8
#define RU_U8_SHH   0xa9
#define RU_U8_TZ    0xaa
#define RU_U8_Y     0xab
#define RU_U8_MZ    0xac
#define RU_U8_EE    0xad
#define RU_U8_JU    0xae
#define RU_U8_JA    0xaf

#endif
