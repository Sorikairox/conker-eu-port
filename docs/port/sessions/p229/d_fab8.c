#ifdef NON_MATCHING

// spray_pair_spawn: spawns two particle sprays at (x, y, z) through func_1516DF0C (same parameters except the second
// one's +0x13 byte (rate11 instead of rate10) and +0x27 = 6), then plays sound 7 there with `span` as the sound's user
// value. Speeds speedA / speedB go through a 20.12 fixed-point round trip ((v << 12) / 4096) as in the asm.
void func_1516FAB8(s32 x, s32 y, s32 z, s32 span, s32 dx, s32 spread, s32 dz, s32 speedA, s32 speedB, s32 size,
                   s32 rate10, s32 rate11, s32 unused12, s32 unused13, s32 unused14, s32 flag, s32 owner) {
    s16 a = (s16)((speedA << 12) / 4096);
    s16 b = (s16)((speedB << 12) / 4096);

    func_1516DF0C(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate10, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 0, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    func_1516DF0C(x, y, z, 0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2, dx, 0, dz, 0, 0, 0, rate11, 0, 0, 0, 0, 0, 0, 0,
                  a, a, b, b, span, size, 0x14, 0xFF, 0x10, spread, 0xC8, 1, 6, 0, 1, 0, 0, 0, 0, 0, flag, owner);
    func_1000FA64(7, x, y, z, 0x36B0, 0x3E8, 0x64, (s32)&func_1000EBC4, (void *)span, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FAB8.s")
#endif
