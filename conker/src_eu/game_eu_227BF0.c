#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P281: readable C for mp3_imdct12_short (Rare hand asm, MP3 short-block IMDCT). */
extern f32 g_mp3_imdct12_cos3_a, g_mp3_imdct12_cos3_b;              /* 3-point stage cosines; was D_800B116C; was D_800B1170 */
extern f32 g_mp3_imdct12_twiddle_0, g_mp3_imdct12_twiddle_1, g_mp3_imdct12_twiddle_2;  /* odd-part twiddles; was D_800B1174; was D_800B1178; was D_800B117C */
extern f32 g_mp3_imdct12_scale_0, g_mp3_imdct12_scale_1, g_mp3_imdct12_scale_2, g_mp3_imdct12_scale_3, g_mp3_imdct12_scale_4, g_mp3_imdct12_scale_5; /* 6-point scale; was D_800B1180; was D_800B1184; was D_800B1188; was D_800B118C; was D_800B1190; was D_800B1194 */
extern f32 g_mp3_imdct12_win_0, g_mp3_imdct12_win_1, g_mp3_imdct12_win_2, g_mp3_imdct12_win_3, g_mp3_imdct12_win_4, g_mp3_imdct12_win_5; /* window (first half); was D_800B1198; was D_800B119C; was D_800B11A0; was D_800B11A4; was D_800B11A8; was D_800B11AC */
extern f32 g_mp3_imdct12_win_6, g_mp3_imdct12_win_7, g_mp3_imdct12_win_8, g_mp3_imdct12_win_9, g_mp3_imdct12_win_10, g_mp3_imdct12_win_11; /* window (second half); was D_800B11B0; was D_800B11B4; was D_800B11B8; was D_800B11BC; was D_800B11C0; was D_800B11C4 */
// mp3_imdct_short: inverse MDCT of the three 6-line short windows of one subband `in` (18 floats, modified in place
// by the input butterflies), overlapped into a 36-float buffer (window w at offset 6 + 6 w). The first 18 floats
// plus the previous granule's tail `prev` give `out` (odd subbands: every odd line negated, the frequency
// inversion); the last 18 replace `prev`.
/* was func_151FA3E0 */
void mp3_imdct12_short(f32 *in, s32 subband, f32 *out, f32 *prev) {
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
        t[0] = even + x[2] * g_mp3_imdct12_cos3_a;
        t[2] = even - x[2] * g_mp3_imdct12_cos3_a;
        odd = x[1] + x[5] * 0.5f;
        t[4] = x[1] - x[5];
        t[5] = odd + x[3] * g_mp3_imdct12_cos3_b;
        t[3] = odd - x[3] * g_mp3_imdct12_cos3_b;
        t[3] *= g_mp3_imdct12_twiddle_0;
        t[4] *= g_mp3_imdct12_twiddle_1;
        t[5] *= g_mp3_imdct12_twiddle_2;
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
        t[0] *= g_mp3_imdct12_scale_0;
        t[1] *= g_mp3_imdct12_scale_1;
        t[2] *= g_mp3_imdct12_scale_2;
        t[3] *= g_mp3_imdct12_scale_3;
        t[4] *= g_mp3_imdct12_scale_4;
        t[5] *= g_mp3_imdct12_scale_5;
        /* window */
        t[8] = t[0] * g_mp3_imdct12_win_0;
        t[9] = t[0] * g_mp3_imdct12_win_1;
        t[7] = t[1] * g_mp3_imdct12_win_2;
        t[10] = t[1] * g_mp3_imdct12_win_3;
        t[6] = t[2] * g_mp3_imdct12_win_4;
        t[11] = t[2] * g_mp3_imdct12_win_5;
        t[0] = t[3] * 1.0f;
        t[1] = t[4] * g_mp3_imdct12_win_6;
        t[2] = t[5] * g_mp3_imdct12_win_7;
        t[3] = t[5] * g_mp3_imdct12_win_8;
        t[5] = t[0] * g_mp3_imdct12_win_10;
        t[4] = t[4] * g_mp3_imdct12_win_9;
        t[0] = t[0] * g_mp3_imdct12_win_11;
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
