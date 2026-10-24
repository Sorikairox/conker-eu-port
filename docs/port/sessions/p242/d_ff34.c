#ifdef NON_MATCHING
// sprite_fade_scale_tick: particle tick (same scheme as func_151702C0): while +0x24 (fading in) is set, alpha +0x1F
// rises by 16 per frame (D_800BE9E4) up to 255; otherwise it falls by 8 per frame down to 0 and the size
// (+0x14 / +0x16) follows it (2 * alpha). Returns 1 (done) once fading out reached 0; else moves the particle
// (func_1516FDD4), scales its velocity by 0xF0 / 256 (func_1516FEF4) and returns 0.
s32 func_1516FF34(u8 *arg0) {
    s32 v;
    s32 t;

    v = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (v != 0xFF) {
            v += D_800BE9E4 * 0x10;
            if (v >= 0x100) {
                v = 0xFF;
            }
            arg0[0x1F] = v;
        }
    } else {
        if (v != 0) {
            v -= D_800BE9E4 * 8;
            if (v < 0) {
                v = 0;
            }
            arg0[0x1F] = v;
        }
        t = (v << 9) >> 8;
        *(s16 *)(arg0 + 0x16) = t;
        *(s16 *)(arg0 + 0x14) = t;
    }
    if ((arg0[0x24] == 0) && (v == 0)) {
        return 1;
    }
    func_1516FDD4(arg0);
    func_1516FEF4((s32) arg0, 0xF0);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FF34.s")
#endif
