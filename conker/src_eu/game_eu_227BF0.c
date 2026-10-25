#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P281: readable C for func_151FA3E0 (Rare hand asm, MP3 short-block IMDCT). */
extern f32 D_800B116C, D_800B1170;              /* 3-point stage cosines */
extern f32 D_800B1174, D_800B1178, D_800B117C;  /* odd-part twiddles */
extern f32 D_800B1180, D_800B1184, D_800B1188, D_800B118C, D_800B1190, D_800B1194; /* 6-point scale */
extern f32 D_800B1198, D_800B119C, D_800B11A0, D_800B11A4, D_800B11A8, D_800B11AC; /* window (first half) */
extern f32 D_800B11B0, D_800B11B4, D_800B11B8, D_800B11BC, D_800B11C0, D_800B11C4; /* window (second half) */
// mp3_imdct_short: inverse MDCT of the three 6-line short windows of one subband `in` (18 floats, modified in place
// by the input butterflies), overlapped into a 36-float buffer (window w at offset 6 + 6 w). The first 18 floats
// plus the previous granule's tail `prev` give `out` (odd subbands: every odd line negated, the frequency
// inversion); the last 18 replace `prev`.
void func_151FA3E0(f32 *in, s32 subband, f32 *out, f32 *prev) {
    f32 t[16];
    f32 acc[36];
    f32 *x;
    f32 *a;
    f32 even, odd;
    s32 w;
    s32 i;

    for (i = 0; i < 16; i++) {
        t[i] = 0.0f;
    }
    for (i = 0; i < 36; i++) {
        acc[i] = 0.0f;
    }
    x = in;
    a = acc;
    for (w = 0; w < 3; w++) {
        /* input butterflies */
        x[5] += x[4];
        x[4] += x[3];
        x[3] += x[2];
        x[2] += x[1];
        x[1] += x[0];
        x[5] += x[3];
        x[3] += x[1];
        /* 3-point IDCTs of the even and odd lines */
        even = x[0] + x[4] * 0.5f;
        t[1] = x[0] - x[4];
        t[0] = even + x[2] * D_800B116C;
        t[2] = even - x[2] * D_800B116C;
        odd = x[1] + x[5] * 0.5f;
        t[4] = x[1] - x[5];
        t[5] = odd + x[3] * D_800B1170;
        t[3] = odd - x[3] * D_800B1170;
        t[3] *= D_800B1174;
        t[4] *= D_800B1178;
        t[5] *= D_800B117C;
        /* combine */
        even = t[0];
        t[0] = even + t[5];
        t[5] = even - t[5];
        even = t[1];
        t[1] = even + t[4];
        t[4] = even - t[4];
        even = t[2];
        t[2] = even + t[3];
        t[3] = even - t[3];
        t[0] *= D_800B1180;
        t[1] *= D_800B1184;
        t[2] *= D_800B1188;
        t[3] *= D_800B118C;
        t[4] *= D_800B1190;
        t[5] *= D_800B1194;
        /* window */
        t[8] = t[0] * D_800B1198;
        t[9] = t[0] * D_800B119C;
        t[7] = t[1] * D_800B11A0;
        t[10] = t[1] * D_800B11A4;
        t[6] = t[2] * D_800B11A8;
        t[11] = t[2] * D_800B11AC;
        t[0] = t[3] * 1.0f;
        t[1] = t[4] * D_800B11B0;
        t[2] = t[5] * D_800B11B4;
        t[3] = t[5] * D_800B11B8;
        t[5] = t[0] * D_800B11C0;
        t[4] = t[4] * D_800B11BC;
        t[0] = t[0] * D_800B11C4;
        /* overlap-add into the window's place */
        for (i = 0; i < 12; i++) {
            a[6 + i] += t[i];
        }
        x += 6;
        a += 6;
    }
    if (subband & 1) {
        for (i = 0; i < 18; i += 2) {
            out[i] = acc[i] + prev[i];
            out[i + 1] = -acc[i + 1] - prev[i + 1];
        }
    } else {
        for (i = 0; i < 18; i++) {
            out[i] = acc[i] + prev[i];
        }
    }
    for (i = 0; i < 18; i++) {
        prev[i] = acc[18 + i];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_227BF0/func_151FA3E0.s")
#endif
