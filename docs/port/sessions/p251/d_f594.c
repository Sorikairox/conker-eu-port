#ifdef NON_MATCHING
void func_1516FDD4(u8 *arg0);
void func_1516FEBC(s32 arg0, s32 arg1);

// sprite_fade_grow_kind_tick: particle tick (handler at 0x8008CF48, sibling of func_1516FF34) with per-kind
// parameters (+0x2C = kind 0..10, tables copied from D_8008CF64 / CF70 / CF7C / CF88). While +0x24 (fading in) is
// set, alpha +0x1F rises by 16 per frame (D_800BE9E4) up to the kind's maximum; otherwise it falls by the kind's
// rate per frame down to 0. Returns 1 (done) once fading out reached 0. Else moves the particle
// (func_1516FDD4), grows the size +0x14 / +0x16 by the kind's step per frame (kind 3 also sets +0x18 = 100),
// scales its velocity by the kind's factor / 256 (func_1516FEBC) and returns 0.
s32 func_1516F594(u8 *arg0) {
    static const u8 scale[11] = { 0xFA, 0xFA, 0xEB, 0xEB, 0xFA, 0xFA, 0xDC, 0xD2, 0xD2, 0xDC, 0xD2 };
    static const u8 grow[11] = { 0x10, 0x07, 0x07, 0x07, 0x14, 0x08, 0x28, 0x28, 0x28, 0x14, 0x14 };
    static const u8 maxAlpha[11] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0xAA, 0x78, 0xC8, 0x3C, 0x78, 0xC8 };
    static const u8 fadeRate[11] = { 0x08, 0x02, 0x0A, 0x01, 0x08, 0x0A, 0xFF, 0x0A, 0x02, 0xFF, 0x0A };
    s32 kind = arg0[0x2C];
    s32 v = arg0[0x1F];
    s32 size;

    if (arg0[0x24] != 0) {
        if (v != maxAlpha[kind]) {
            v += D_800BE9E4 << 4;
            if (v > maxAlpha[kind]) {
                v = maxAlpha[kind];
            }
            arg0[0x1F] = v;
        }
    } else if (v != 0) {
        v -= D_800BE9E4 * fadeRate[kind];
        if (v < 0) {
            v = 0;
        }
        arg0[0x1F] = v;
    }
    if (arg0[0x24] == 0 && v == 0) {
        return 1;
    }
    func_1516FDD4(arg0);
    size = *(s16 *) (arg0 + 0x14) + D_800BE9E4 * grow[kind];
    *(s16 *) (arg0 + 0x16) = size;
    *(s16 *) (arg0 + 0x14) = size;
    if (kind == 3) {
        *(s16 *) (arg0 + 0x18) = 100;
    }
    func_1516FEBC((s32) arg0, scale[kind]);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F594.s")
#endif
