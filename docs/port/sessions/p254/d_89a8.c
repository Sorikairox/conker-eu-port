#ifdef NON_MATCHING
// bone_bounce_splash_b: handler 8 of D_80089CD4 (`s32 (u8 *, f32, f32, f32, f32, u8 *)`), twin of func_15139578:
// bounces the object on the ground (y velocity +0x48 flipped, velocities +0x44..+0x58 scaled by +0x14, y +0x3C =
// +0x10 + ground; under a bounce speed of 4 velocities +0x44..+0x5C cleared and flags 0x69 of +0x60 dropped). Unless
// +0x30 is 2.0 it spawns a splash (func_151D9B8C) at (+0x38, ground, +0x40): kind 1 when +0x30 != 0, size (39.8 +
// 25.4 * random) * mean of +0x18 / +0x1C, alpha 100..200, life 80..180, then clears +0x2C. Returns 1.
s32 func_151389A8(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 ground, u8 *bone) {
    f32 fac = *(f32 *) (arg0 + 0x14);
    struct17 pos;
    s32 kind;
    f32 r;
    u32 alpha;
    u32 life;

    *(f32 *) (arg0 + 0x48) = *(f32 *) (arg0 + 0x48) * -fac;
    *(f32 *) (arg0 + 0x3C) = *(f32 *) (arg0 + 0x10) + ground;
    *(f32 *) (arg0 + 0x44) *= fac;
    *(f32 *) (arg0 + 0x4C) *= fac;
    *(f32 *) (arg0 + 0x50) *= fac;
    *(f32 *) (arg0 + 0x54) *= fac;
    *(f32 *) (arg0 + 0x58) *= fac;
    if (fabsf(*(f32 *) (arg0 + 0x48)) < 4.0f) {
        *(f32 *) (arg0 + 0x44) = 0.0f;
        *(s32 *) (arg0 + 0x60) &= ~0x69;
        *(f32 *) (arg0 + 0x48) = 0.0f;
        *(f32 *) (arg0 + 0x4C) = 0.0f;
        *(f32 *) (arg0 + 0x50) = 0.0f;
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    if (*(f32 *) (arg0 + 0x30) == 2.0f) {
        return 1;
    }
    pos.unk0 = *(f32 *) (arg0 + 0x38);
    pos.unk4 = ground;
    pos.unk8 = *(f32 *) (arg0 + 0x40);
    kind = (*(f32 *) (arg0 + 0x30) == 0.0f) ? 0 : 1;
    r = func_150ADA68();
    alpha = func_150ADA20();
    life = func_150ADA20();
    func_151D9B8C(kind, (r * 25.4f + 39.8f) * ((*(f32 *) (arg0 + 0x18) + *(f32 *) (arg0 + 0x1C)) * 0.5f),
                  alpha % 101 + 100, (s32) bone, &pos, life % 101 + 80, 1, 1, 0, arg0[0xC], arg0[1]);
    *(f32 *) (arg0 + 0x2C) = 0.0f;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_151389A8.s")
#endif
