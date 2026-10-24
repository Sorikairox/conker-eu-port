#ifdef NON_MATCHING
/* func_15046750's hit record (game_eu_71E70 HitInfo: t, 9 s16 position words, +0x18, flags +0x1C, surface kind +0x1D) */
typedef struct {
    /* 0x00 */ f32 t;
    /* 0x04 */ s16 pos[9];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 surface;
    /* 0x1E */ u8 pad1E[2];
    /* 0x20 */ s32 unk20;
} Hit5DD0;
s32 func_15046750(f32 *, u16, f32, Hit5DD0 *);
void func_15143794(s16, s16, f32, f32 *);
s32 func_151DB5D0(u8, struct17 *, f32 *, f32, f32, f32, f32, s16, u8, s16, s16, u8, u8, s32);
u8 *func_151DA6F8(struct17 *, f32 *, f32, s16, u8, f32, s32, u8, f32, f32, u8, u8, s32, s16, s16, s32, u8, s32);
s32 func_150ADA20(void);
f32 func_150ADA68(void);

// beam_impact_effects: effects along a beam from `from` to `to` (dir = to - from); called by func_151AFA80 (game_eu_1DD290)
// with two bone points of an object and a random scale. A vertical probe (func_15046750 from (from.x, 10000, from.z)
// down to from.y) decides: on a hit whose surface kind (+0x1D) is 3, 10..20 func_151DB5D0 particles fly from `from`
// along dir * (67 r + 86) / 1000 and nothing else is spawned. Otherwise 3..7 func_151DA6F8 sprites (velocity: a random
// direction of length `scale` (func_15143794) plus dir * (618 r + 201) / 1000) and 10..20 func_151D9014 puffs (random
// direction plus dir * 200 r / 1000). kind (u8) and owner are passed through to every spawn. Returns the last
// spawn's result (the asm leaves it in v0; func_151AFA80 does not read it).
s32 func_15135DD0(struct17 *from, struct17 *to, f32 scale, u8 kind, s32 owner) {
    Hit5DD0 hit;
    f32 probe[3];
    f32 dir[3];
    f32 vel[3];
    f32 puff[3];
    s32 n;
    s32 ret;
    f32 f;
    f32 r0;
    f32 r1;
    f32 r2;
    s16 life;
    s32 a;
    s32 b;
    s32 c;

    hit.t = -10000.0f;
    hit.unk18 = 0;
    hit.flags = 0;
    hit.surface = 0;
    hit.unk20 = 0;
    dir[0] = to->unk0 - from->unk0;
    dir[1] = to->unk4 - from->unk4;
    dir[2] = to->unk8 - from->unk8;
    probe[0] = from->unk0;
    probe[1] = 10000.0f;
    probe[2] = from->unk8;
    if (func_15046750(probe, 0, from->unk4, &hit) != 0 && hit.surface == 3) {
        for (n = (u32)func_150ADA20() % 11 + 10; n > 0; n--) {
            f = (func_150ADA68() * 67.0f + 86.0f) * 0.001f;
            vel[0] = dir[0] * f;
            vel[1] = dir[1] * f;
            vel[2] = dir[2] * f;
            life = (u32)func_150ADA20() % 52 + 99;
            r0 = func_150ADA68();
            r1 = func_150ADA68();
            r2 = func_150ADA68();
            a = (u32)func_150ADA20() % 156 + 100;
            ret = func_151DB5D0(0, from, vel, r0 * 50.0f + 30.0f, r1 * 0.0f + 1.01f, 1.0f, r2 * 0.041f, life, a, life,
                                255 / life, 1, kind, owner);
        }
        return ret;
    }
    for (n = (u32)func_150ADA20() % 5 + 3; n > 0; n--) {
        f = (func_150ADA68() * 618.0f + 201.0f) * 0.001f;
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794(a & 0xFF, (b & 0x7F) - 63, scale, vel);
        vel[0] += dir[0] * f;
        vel[1] += dir[1] * f;
        vel[2] += dir[2] * f;
        r0 = func_150ADA68();
        a = func_150ADA20();
        b = func_150ADA20();
        r1 = func_150ADA68();
        c = func_150ADA20();
        func_151DA6F8(from, vel, r0 * 1.013f, (u32)a % 21 + 20, (u32)b % 101 + 100, r1 * 4.2000003f + 1.9f, (u32)c % 3 + 3,
                      0, 1.0f, 1.0f, 0, 0, 0, 16, 15, 0, kind, owner);
    }
    for (n = (u32)func_150ADA20() % 11 + 10; n > 0; n--) {
        f = func_150ADA68() * 200.0f * 0.001f;
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794(a & 0xFF, (b & 0x7F) - 63, scale, puff);
        puff[0] += dir[0] * f;
        puff[1] += dir[1] * f;
        puff[2] += dir[2] * f;
        r0 = func_150ADA68();
        a = func_150ADA20();
        b = func_150ADA20();
        r1 = func_150ADA68();
        ret = func_151D9014(from, puff, 0, r0 * 0.147f + -0.30200002f, (u32)a % 52 + 31, (u32)b % 101 + 155,
                            r1 * 50.0f + 50.0f, 0, 1.0f, 1.0f, 0, 0, 1, 0, kind, owner);
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_15135DD0.s")
#endif
