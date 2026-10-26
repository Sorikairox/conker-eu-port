#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P279: the libultra cosf below (the commented copy) with the ROM's own constants: rpi / pihi / pilo / zero are
 * g_cosf_inv_pi..4C (.data), the polynomial P[0..4] is g_cosf_poly (.rodata), __libm_qnan_f is g_libm_qnan_f. */
// cosf: cos(x) by range reduction to [-pi/2, pi/2] around the nearest (n + 1/2) pi and an odd degree-9 polynomial
// (sign from n's parity); |x| >= 2^28 (exponent field >= 0x136 after >> 22) gives 0, NaN gives the quiet NaN.
extern f32 g_cosf_inv_pi; /* 1/pi; was D_80086240 */
extern f32 g_cosf_pi_hi; /* pi, high part; was D_80086244 */
extern f32 g_cosf_pi_lo; /* pi, low part; was D_80086248 */
extern f32 g_cosf_zero; /* 0.0f; was D_8008624C */
extern f32 g_cosf_poly[5]; /* was D_80099120 */
extern f32 g_libm_qnan_f; /* __libm_qnan_f; was D_8002CC80 */

f32 cosf(f32 x) {
    f32 absx, dn, dx, xsq, poly;
    s32 n;
    s32 xpt = (*(s32 *) &x >> 22) & 0x1FF;

    if (xpt < 0x136) {
        absx = (x > 0.0f) ? x : -x;
        dn = absx * g_cosf_inv_pi + 0.5f;
        n = (dn >= 0.0f) ? (s32) (dn + 0.5f) : (s32) (dn - 0.5f);
        dn = n;
        dn = dn - 0.5f;
        dx = absx - dn * g_cosf_pi_hi;
        dx = dx - dn * g_cosf_pi_lo;
        xsq = dx * dx;
        poly = ((g_cosf_poly[4] * xsq + g_cosf_poly[3]) * xsq + g_cosf_poly[2]) * xsq + g_cosf_poly[1];
        dx = dx + (dx * xsq) * poly;
        return (n & 1) ? -dx : dx;
    }
    if (x != x) {
        return g_libm_qnan_f;
    }
    return g_cosf_zero;
}
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
