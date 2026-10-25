#ifdef NON_MATCHING
// sprite_fade_drift_tint_tick: particle tick (handler at 0x8008CF50, same scheme as func_1516FF34): while +0x24
// (fading in) is set, alpha +0x1F rises by 16 per frame (D_800BE9E4) up to 255; otherwise it falls by
// D_800BE9E4 << +0x2F down to 0. Returns 1 (done) once fading out reached 0. Else the size +0x14 / +0x16 grows by
// the signed rates +0x2D / +0x2E per frame; when the width reaches 0 or below both are cleared and it returns 1.
// Else the tint step +0x2C advances by D_800BE9E4 (up to 0x7F) and the colour +0x1C..+0x1E blends from
// +0x26..+0x28 towards +0x29..+0x2B by 2 * step / 256; returns 0.
s32 func_1517013C(u8 *arg0) {
    s32 v = arg0[0x1F];
    s32 t;

    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 << 4;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 << arg0[0x2F];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    *(s16 *) (arg0 + 0x14) += (s8) arg0[0x2D] * D_800BE9E4;
    *(s16 *) (arg0 + 0x16) += (s8) arg0[0x2E] * D_800BE9E4;
    if (*(s16 *) (arg0 + 0x14) <= 0) {
        *(s16 *) (arg0 + 0x16) = 0;
        *(s16 *) (arg0 + 0x14) = *(s16 *) (arg0 + 0x16);
        return 1;
    }
    v = arg0[0x2C] + D_800BE9E4;
    if (v >= 0x80) {
        v = 0x7F;
    }
    arg0[0x2C] = v;
    t = v * 2;
    arg0[0x1C] = (((arg0[0x29] - arg0[0x26]) * t) >> 8) + arg0[0x26];
    arg0[0x1D] = (((arg0[0x2A] - arg0[0x27]) * t) >> 8) + arg0[0x27];
    arg0[0x1E] = (((arg0[0x2B] - arg0[0x28]) * t) >> 8) + arg0[0x28];
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1517013C.s")
#endif
