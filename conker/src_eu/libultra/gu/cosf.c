#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/cosf/cosf.s")
// NON-MATCHING: only dn/dx swap registers (f12/f2). To use it, split .data 0x22B4C0-0x22B4D0
// and .rodata 0x23E3A0-0x23E3C0 out of the game_data blobs (tools/eu_port/rodata_split.py).
// typedef union {
//     unsigned int i;
//     float f;
// } fu;
//
// extern float __libm_qnan_f;
//
// /* float cosf (game copy): P is .rodata (EU rom 0x23E3A0), the scalars are .data (0x22B4C0) */
// static const fu P[] = {
//     { 0x3F800000 }, { 0xBE2AAAA6 }, { 0x3C088769 }, { 0xB94FB7FD }, { 0x362EDEFA },
// };
// static fu rpi = { 0x3EA2F984 };
// static fu pihi = { 0x40490FDC };
// static fu pilo = { 0x330885A3 };
// static fu zero = { 0x00000000 };
//
// #define ROUND(d) (int)(((d) >= 0.0f) ? ((d) + 0.5f) : ((d) - 0.5f))
// #define ABS(d) ((d) > 0 ? (d) : -(d))
//
// float cosf(float x) {
//     float absx;
//     float dx;
//     float xsq;
//     float poly;
//     float dn;
//     int n;
//     float result;
//     int ix;
//     int xpt;
//
//     ix = *(int *)&x;
//     xpt = (ix >> 22);
//     xpt &= 0x1FF;
//
//     if (xpt < 0x136) {
//         absx = ABS(x);
//         dn = absx * rpi.f + 0.5f;
//         n = ROUND(dn);
//         dn = n;
//         dn = dn - 0.5f;
//         dx = absx - dn * pihi.f;
//         dx = dx - dn * pilo.f;
//         xsq = dx * dx;
//         poly = ((P[4].f * xsq + P[3].f) * xsq + P[2].f) * xsq + P[1].f;
//         result = dx + (dx * xsq) * poly;
//         if ((n & 1) == 0) {
//             return result;
//         }
//         return -result;
//     }
//
//     if (x != x) {
//         return __libm_qnan_f;
//     }
//     return zero.f;
// }
