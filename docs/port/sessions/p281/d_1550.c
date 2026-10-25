/* P281: readable C for func_10001550 (compiled C, 296 insns): libc _Ldtob. */
#include "libc/stdlib.h"
void *memcpy(void *, const void *, size_t);
extern const f64 D_8002C270[];   /* powers of ten 1e1, 1e2, 1e4, 1e8, ..., 1e256 */
extern const f64 D_8002C2C8;     /* 1e8 */
extern const char D_8002C2B8[];  /* "NaN" */
extern const char D_8002C2BC[];  /* "Inf" */
s16 func_100019F0(s16 *arg0, struct05 *arg1);
void func_10001AA8(_Pft *px, u8 code, u8 *p, s16 nsig, s16 xexp);
// format_double_digits (libc _Ldtob): converts the double in px->v for printf conversion `code` (e f g E G): default
// precision 6 (1 for %g with precision 0), "NaN" / "Inf" copied as is, otherwise scales the value by powers of ten
// to 8-digit groups, generates up to 19 digits, drops leading zeros, rounds to the significant digit count and hands
// the digits to func_10001AA8 (_Genld).
void func_10001550(void *arg0, u8 code) {
    _Pft *px = arg0;
    u8 buf[0x20];
    u8 *p;
    f64 val;
    s16 err;
    s16 nsig;
    s16 xexp;
    s32 i;
    s32 n;
    f64 factor;
    s32 gen;
    s32 j;
    s32 lo;
    ldiv_t qr;
    u8 drop;
    s32 n2;

    p = buf;
    val = *(f64 *) &px->v; /* IDO long double = double */
    if (px->prec < 0) {
        px->prec = 6;
    } else if (px->prec == 0 && (code == 'g' || code == 'G')) {
        px->prec = 1;
    }
    err = func_100019F0(&xexp, (struct05 *) px);
    if (err > 0) {
        px->n1 = 3;
        memcpy(px->s, (err == 2) ? D_8002C2B8 : D_8002C2BC, 3);
        return;
    }
    if (err == 0) {
        nsig = 0;
        xexp = 0;
    } else {
        if (val < 0.0) {
            val = -val;
        }
        xexp = xexp * 30103 / 100000 - 4;
        if (xexp < 0) {
            n = (3 - xexp) & ~3;
            xexp = -n;
            for (i = 0; n > 0; n >>= 1, i++) {
                if (n & 1) {
                    val *= D_8002C270[i];
                }
            }
        } else if (xexp > 0) {
            factor = 1.0f;
            xexp &= ~3;
            for (n = xexp, i = 0; n > 0; n >>= 1, i++) {
                if (n & 1) {
                    factor *= D_8002C270[i];
                }
            }
            val /= factor;
        }
        gen = ((code == 'f') ? xexp + 10 : 6) + px->prec;
        if (gen > 19) {
            gen = 19;
        }
        *p++ = '0';
        while (gen > 0 && 0.0 < val) {
            lo = val;
            if ((gen -= 8) > 0) {
                val = (val - lo) * D_8002C2C8;
            }
            p += 8;
            for (j = 8; lo > 0 && --j >= 0;) {
                qr = ldiv(lo, 10);
                *--p = qr.rem + '0';
                lo = qr.quot;
            }
            while (--j >= 0) {
                *--p = '0';
            }
            p += 8;
        }
        gen = p - &buf[1];
        for (p = &buf[1], xexp += 7; *p == '0'; p++) {
            --gen;
            --xexp;
        }
        nsig = ((code == 'f') ? xexp + 1 : ((code == 'e' || code == 'E') ? 1 : 0)) + px->prec;
        if (gen < nsig) {
            nsig = gen;
        }
        if (nsig > 0) {
            drop = (nsig < gen && p[nsig] > '4') ? '9' : '0';
            for (n2 = nsig; p[--n2] == drop;) {
                nsig--;
            }
            if (drop == '9') {
                p[n2]++;
            }
            if (n2 < 0) {
                --p;
                ++nsig;
                ++xexp;
            }
        }
    }
    func_10001AA8(px, code, p, nsig, xexp);
}
