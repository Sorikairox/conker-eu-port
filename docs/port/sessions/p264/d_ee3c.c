#ifdef NON_MATCHING
extern u8 D_800A71E0[]; /* glow level thresholds (descending) */
extern u8 D_800A71EC[]; /* rgb per threshold */
// glow_colour_update: handler 0 of D_8008CF40 (`s32 (u8 *)`). While +0x24 (the glow level) is set the fade +0x1F
// rises by D_800BE9E4 * 32 up to 0xFF, else it falls by D_800BE9E4 * 16 down to 0; returns 1 (done) when both are 0.
// The phase +0x14 advances by D_800BE9E4 * 10 (copied to +0x16). The level (+0x24 + 8, or fade >> 5 while fading
// out) picks, from index +0x26 for 8 entries, the first threshold of D_800A71E0 at or below it, and the colour
// +0x1C..+0x1E is that entry's rgb (D_800A71EC) blended with the previous entry's by the level's position between
// the two thresholds. Returns 0.
s32 func_1516EE3C(u8 *arg0) {
    u8 on = arg0[0x24];
    s32 fade = arg0[0x1F];
    s32 level;
    s32 i;
    u8 *rgb;
    f32 t;
    f32 u;

    if (on != 0) {
        if (fade != 0xFF) {
            fade += D_800BE9E4 << 5;
            if (fade >= 0x100) {
                fade = 0xFF;
            }
            arg0[0x1F] = fade;
            on = arg0[0x24];
        }
    } else if (fade != 0) {
        fade -= D_800BE9E4 << 4;
        if (fade < 0) {
            fade = 0;
        }
        arg0[0x1F] = fade;
        on = arg0[0x24];
    }
    if (on == 0 && fade == 0) {
        return 1;
    }
    *(s16 *) (arg0 + 0x14) += D_800BE9E4 * 10;
    *(s16 *) (arg0 + 0x16) = *(s16 *) (arg0 + 0x14);
    if (on == 0) {
        level = arg0[0x1F] >> 5;
    } else {
        level = on + 8;
    }
    for (i = arg0[0x26]; i < arg0[0x26] + 8; i++) {
        if (level >= D_800A71E0[i]) {
            t = (f32) (level - D_800A71E0[i]) / (f32) (D_800A71E0[i - 1] - D_800A71E0[i]);
            u = 1.0f - t;
            rgb = &D_800A71EC[i * 3];
            arg0[0x1C] = (u32) (rgb[-3] * t + rgb[0] * u);
            arg0[0x1D] = (u32) (rgb[-2] * t + rgb[1] * u);
            arg0[0x1E] = (u32) (rgb[-1] * t + rgb[2] * u);
            break;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EE3C.s")
#endif
