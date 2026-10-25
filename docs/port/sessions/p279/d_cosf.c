#include <ultra64.h>
#include "functions.h"
#include "variables.h"
/* P279: the libultra cosf below (the commented copy) with the ROM's own constants: rpi / pihi / pilo / zero are
 * D_80086240..4C (.data), the polynomial P[0..4] is D_80099120 (.rodata), __libm_qnan_f is D_8002CC80. */
// cosf: cos(x) by range reduction to [-pi/2, pi/2] around the nearest (n + 1/2) pi and an odd degree-9 polynomial
// (sign from n's parity); |x| >= 2^28 (exponent field >= 0x136 after >> 22) gives 0, NaN gives the quiet NaN.
extern f32 D_80086240; /* 1/pi */
extern f32 D_80086244; /* pi, high part */
extern f32 D_80086248; /* pi, low part */
extern f32 D_8008624C; /* 0.0f */
extern f32 D_80099120[5];
extern f32 D_8002CC80; /* __libm_qnan_f */

f32 cosf(f32 x) {
    f32 absx, dn, dx, xsq, poly;
    s32 n;
    s32 xpt = (*(s32 *) &x >> 22) & 0x1FF;

    if (xpt < 0x136) {
        absx = (x > 0.0f) ? x : -x;
        dn = absx * D_80086240 + 0.5f;
        n = (dn >= 0.0f) ? (s32) (dn + 0.5f) : (s32) (dn - 0.5f);
        dn = n;
        dn = dn - 0.5f;
        dx = absx - dn * D_80086244;
        dx = dx - dn * D_80086248;
        xsq = dx * dx;
        poly = ((D_80099120[4] * xsq + D_80099120[3]) * xsq + D_80099120[2]) * xsq + D_80099120[1];
        dx = dx + (dx * xsq) * poly;
        return (n & 1) ? -dx : dx;
    }
    if (x != x) {
        return D_8002CC80;
    }
    return D_8008624C;
}
