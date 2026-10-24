#ifdef NON_MATCHING
s32 func_151EFDD0(void);
// sprite_flicker_drift_tick: particle tick (handler at 0x8008CF58 of D_8008CF40, same scheme as func_1516FF34).
// While +0x24 (life) is set, the alpha +0x1F rises by 64 per frame (D_800BE9E4) up to 254; a particle whose alpha is
// still 0 first gets a life of 200..224 (func_150ADA20). Otherwise the alpha falls by 16 per frame down to 0, and
// the particle is done (returns 1) once it reached 0. Else it moves (func_1516FDD4) and its velocity +0x26 / +0x28
// is scaled by a random (230 + -31..31) / 256 when +0x2F is set, or by (220 + -31..31) / 256 when the 8.8
// velocity +0x26 is above sqrt(1000); +0x18 is cleared and it returns 0.
s32 func_15170D50(u8 *arg0) {
    s32 alpha = arg0[0x1F];
    s32 vel;

    if (arg0[0x24] != 0) {
        if (alpha == 0) {
            arg0[0x24] = (u32) func_150ADA20() % 25 + 200;
        }
        if (alpha != 0xFE) {
            alpha += D_800BE9E4 << 6;
            if (alpha >= 0xFF) {
                alpha = 0xFE;
            }
            arg0[0x1F] = alpha;
        }
    } else if (alpha != 0) {
        alpha -= D_800BE9E4 << 4;
        if (alpha < 0) {
            alpha = 0;
        }
        arg0[0x1F] = alpha;
    }
    if (arg0[0x24] == 0 && alpha == 0) {
        return 1;
    }
    func_1516FDD4(arg0);
    if (arg0[0x2F] != 0) {
        func_1516FE5C((s32) arg0, func_151EFDD0() % 32 + 0xE6);
        func_1516FE8C((s32) arg0, func_151EFDD0() % 32 + 0xE6);
    } else {
        vel = (*(s8 *) (arg0 + 0x26) << 8) + arg0[0x27];
        // the asm squares the +0x26 velocity twice (not +0x28); u32 keeps its wrap-around at vel = -0x8000
        if ((s32) ((u32) vel * vel + (u32) vel * vel) > 2000) {
            func_1516FE5C((s32) arg0, func_151EFDD0() % 32 + 0xDC);
            func_1516FE8C((s32) arg0, func_151EFDD0() % 32 + 0xDC);
        }
    }
    *(s16 *) (arg0 + 0x18) = 0;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170D50.s")
#endif
