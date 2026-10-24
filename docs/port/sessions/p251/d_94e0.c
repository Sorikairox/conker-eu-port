#ifdef NON_MATCHING
// mp3_imdct36_hybrid: P251 readable C for func_151F94E0. Long-block (36-point) IMDCT of one subband for the MP3
// hybrid synthesis, then windowing and overlap-add (the fast algorithm of maplay / JLayer's inv_mdct, 9-point DCTs
// on the even and odd inputs). `in` holds the 18 dequantised spectral lines of subband `sb` and is used as scratch
// (prefix sums). `out` gets the 18 output samples (window * IMDCT + the previous granule's overlap `prev`; the odd
// samples of odd subbands are negated: frequency inversion), `prev` gets the new overlap. `win` is one of the
// game's four sine_block[36] windows. Caller: func_151F78B4 (game_221290).
// The expressions keep the asm's evaluation order and its (signed) constants so the float results are bit-exact.
void func_151F94E0(f32 *in, s32 sb, f32 *out, f32 *prev, f32 *win) {
    f32 t[18];      /* 0x00 9-point DCT results: even part t[0..8], odd part t[9..17] */
    f32 res[18];    /* 0x48 the 18 independent IMDCT outputs */
    f32 i00, iip12, i66;
    f32 a, b;
    s32 i;

    for (i = 17; i > 0; i--) {
        in[i] += in[i - 1];
    }
    for (i = 17; i > 1; i -= 2) {
        in[i] += in[i - 2];
    }

    /* 9-point IDCT of the even inputs */
    i00 = in[0] + in[0];
    iip12 = i00 + in[12];
    t[0] = in[4] * 1.87938523f + in[8] * 1.53208888f + in[16] * 0.347296357f + iip12;
    t[2] = in[4] * -0.347296357f + in[8] * -1.87938523f + in[16] * 1.53208888f + iip12;
    t[3] = in[4] * -1.53208888f + in[8] * 0.347296357f + in[16] * -1.87938523f + iip12;
    t[1] = i00 + in[4] - in[8] - in[12] - in[12] - in[16];
    t[4] = in[0] - in[4] + in[8] - in[12] + in[16];
    i66 = in[6] * 1.73205078f;
    t[5] = in[2] * 1.96961546f + in[10] * 1.28557527f + in[14] * 0.684040308f + i66;
    i66 = -i66;
    t[6] = in[2] * 1.28557527f + in[10] * -0.684040308f + in[14] * 1.96961546f + i66;
    t[7] = in[2] * 0.684040308f + in[10] * 1.96961546f + in[14] * -1.28557527f + i66;
    t[8] = (in[2] - in[10] - in[14]) * 1.73205078f;

    /* 9-point IDCT of the odd inputs */
    i00 = in[1] + in[1];
    iip12 = i00 + in[13];
    t[9] = in[5] * 1.87938523f + in[9] * 1.53208888f + in[17] * 0.347296357f + iip12;
    t[11] = in[5] * -0.347296357f + in[9] * -1.87938523f + in[17] * 1.53208888f + iip12;
    t[12] = in[5] * -1.53208888f + in[9] * 0.347296357f + in[17] * -1.87938523f + iip12;
    t[10] = i00 + in[5] - in[9] - in[13] - in[13] - in[17];
    t[13] = in[1] - in[5] + in[9] - in[13] + in[17];
    i66 = in[7] * 1.73205078f;
    t[14] = in[3] * 1.96961546f + in[11] * 1.28557527f + in[15] * 0.684040308f + i66;
    i66 = -i66;
    t[15] = in[3] * 1.28557527f + in[11] * -0.684040308f + in[15] * 1.96961546f + i66;
    t[16] = in[3] * 0.684040308f + in[11] * 1.96961546f + in[15] * -1.28557527f + i66;
    t[17] = (in[3] - in[11] - in[15]) * 1.73205078f;

    /* butterflies: res[k] and res[17 - k] from the even (a) and scaled odd (b) parts */
    a = t[0] + t[5];
    b = (t[9] + t[14]) * 0.501909912f;
    res[0] = (a + b) * -0.25023818f;
    res[17] = (a - b) * -5.7313962f;
    a = t[1] + t[8];
    b = (t[10] + t[17]) * 0.517638087f;
    res[1] = (a + b) * -0.252157241f;
    res[16] = (a - b) * -1.91532445f;
    a = t[2] + t[6];
    b = (t[11] + t[15]) * 0.551688969f;
    res[2] = (a + b) * -0.256069869f;
    res[15] = (a - b) * -1.1550566f;
    a = t[3] + t[7];
    b = (t[12] + t[16]) * 0.610387266f;
    res[3] = (a + b) * -0.262132287f;
    res[14] = (a - b) * -0.831377387f;
    a = t[3] - t[7];
    b = (t[12] - t[16]) * 0.871723413f;
    res[5] = (a + b) * -0.28184548f;
    res[12] = (a - b) * -0.541420162f;
    a = t[2] - t[6];
    b = (t[11] - t[15]) * 1.18310082f;
    res[6] = (a + b) * -0.296422273f;
    res[11] = (a - b) * -0.465289742f;
    a = t[1] - t[8];
    b = (t[10] - t[17]) * 1.93185163f;
    res[7] = (a + b) * -0.315118104f;
    res[10] = (a - b) * -0.410669893f;
    a = t[0] - t[5];
    b = (t[9] - t[14]) * 5.73685646f;
    res[8] = (a + b) * -0.33908543f;
    res[9] = (a - b) * -0.370046794f;
    b = t[13] * 0.707106769f;
    res[4] = (t[4] + b) * -0.541196108f;
    res[13] = (t[4] - b) * -1.30656302f;

    /* window the first half and add the previous overlap (odd samples of odd subbands negated) */
    if (sb & 1) {
        for (i = 0; i < 9; i++) {
            if (i & 1) {
                out[i] = res[9 + i] * win[i] - prev[i];
            } else {
                out[i] = -res[9 + i] * win[i] + prev[i];
            }
        }
        for (i = 9; i < 18; i++) {
            if (i & 1) {
                out[i] = -res[26 - i] * win[i] - prev[i];
            } else {
                out[i] = res[26 - i] * win[i] + prev[i];
            }
        }
    } else {
        for (i = 0; i < 9; i++) {
            out[i] = -res[9 + i] * win[i] + prev[i];
        }
        for (i = 9; i < 18; i++) {
            out[i] = res[26 - i] * win[i] + prev[i];
        }
    }

    /* window the second half: the overlap for the next granule */
    for (i = 0; i < 9; i++) {
        prev[i] = res[8 - i] * win[18 + i];
    }
    for (i = 9; i < 18; i++) {
        prev[i] = res[i - 9] * win[18 + i];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_226870/func_151F94E0.s")
#endif
