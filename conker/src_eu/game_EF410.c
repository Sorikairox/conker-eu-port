#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* func_151506E8's spec (S06E8 in game_2062D0) */
typedef struct {
    s16 u0[4];
    f32 u8;
    f32 uC;
    f32 u10;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S2700;
s32 func_151506E8(S2700 *, f32 *, s32, u8, s32);

#ifdef NON_MATCHING
void func_15151FA8(u8 *arg0, s32 arg1, s32 arg2);

/* func_15151FA8's smoke spec (layout as smoke_column_spawn_far's) */
typedef struct {
    /* 0x00 */ struct17 pos;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s16 u24[10];
    /* 0x38 */ u8 u38;
    /* 0x39 */ u8 u39;
    /* 0x3A */ u8 u3A;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ s32 u40;
    /* 0x44 */ s32 u44[4];
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x56 */ u8 u56;
    /* 0x58 */ s32 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ s32 u60;
    /* 0x64 */ s32 u64;
    /* 0x68 */ s32 u68;
    /* 0x6C */ s32 u6C;
    /* 0x70 */ s32 u70;
    /* 0x74 */ s32 u74;
    /* 0x78 */ s32 u78;
    /* 0x7C */ u8 u7C;
    /* 0x7D */ u8 u7D;
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ s16 u80;
    /* 0x82 */ s16 u82;
} SmokeSpec150C1F60;


// smoke_columns_spawn: queues two smoke columns (func_15151FA8, owner byte `flag`) at (8152, 40, -309): a wide one
// (size 9 x 21.9, ...) and a thin one (55.6 x 39, ...), then a func_151506E8 effect at the same place.
/* was func_150C1F60 */
void smoke_columns_spawn(u8 flag) {
    SmokeSpec150C1F60 spec;
    S2700 t;

    spec.pos.unk0 = 8152.0f;
    spec.pos.unk4 = 40.0f;
    spec.u24[0] = 12;
    spec.u24[2] = -160;
    spec.u24[4] = -60;
    spec.u24[3] = 0x45;
    spec.u24[5] = 0x43;
    spec.u24[6] = 3;
    spec.u24[7] = 5;
    spec.u24[9] = 0x1F;
    spec.u38 = 0xB;
    spec.pos.unk8 = -309.0f;
    spec.u24[1] = 13;
    spec.u24[8] = 0x32;
    spec.u3A = 0x28;
    spec.u3C = 1;
    spec.u40 = 4;
    spec.u54 = 0xFF;
    spec.u55 = 0xFF;
    spec.u58 = 3;
    spec.u39 = 1;
    spec.u44[0] = 0;
    spec.u44[1] = 0;
    spec.u44[2] = 0;
    spec.u44[3] = 0;
    spec.u56 = 0;
    spec.u5C = 0xFF;
    spec.u60 = 0;
    spec.u64 = 0x220005;
    spec.u68 = 0x1D0600;
    spec.u6C = 1;
    spec.u70 = 0x3B;
    spec.u74 = 0x80;
    spec.u78 = 0x20;
    spec.u7C = 0;
    spec.u7D = 7;
    spec.u80 = 0xC;
    spec.u82 = 0x15;
    spec.u1C = 40.92f;
    spec.u20 = 20.45f;
    spec.u0C = 9.0f;
    spec.u10 = 21.9f;
    spec.u14 = 1.46f;
    spec.u18 = 0.5f;
    func_15151FA8((u8 *) &spec, flag, 1);

    spec.u24[0] = 2;
    spec.u24[1] = 3;
    spec.u24[2] = -108;
    spec.u24[4] = -22;
    spec.u24[3] = 0x15;
    spec.u24[5] = 0x16;
    spec.u24[6] = 7;
    spec.u24[7] = 0;
    spec.u24[8] = 0x30;
    spec.u24[9] = 0x15;
    spec.u1C = 100.0f;
    spec.u20 = 57.5f;
    spec.u0C = 55.6f;
    spec.u10 = 39.0f;
    spec.u14 = 0.46f;
    spec.u18 = 1.0f;
    func_15151FA8((u8 *) &spec, flag, 1);

    t.u8 = spec.pos.unk0;
    t.uC = spec.pos.unk4;
    t.u10 = spec.pos.unk8;
    t.u14 = 0x19;
    t.u16 = 0x12;
    t.u0[0] = -0x9F;
    t.u0[1] = 0x44;
    t.u0[2] = -0x34;
    t.u0[3] = 0x26;
    t.u20 = 0x19;
    t.u22 = 0x19;
    t.u2C = 0x9B;
    t.u2D = 0x64;
    t.u38 = 1;
    t.u39 = 6;
    t.u3C = 0.0f;
    t.u40 = 1;
    t.u44 = 0.0f;
    t.u18 = 40.0f;
    t.u1C = 35.0f;
    t.u24 = -2.0210001f;
    t.u28 = 0.89400005f;
    t.u30 = 1152.0f;
    t.u34 = 848.0f;
    func_151506E8(&t, &t.u8, 0, flag, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/smoke_columns_spawn.s")
#endif
#ifdef NON_MATCHING

/* was func_150C2290 */
void smoke_column_spawn_far(s32 arg0) {
    struct {
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        s16 u3C;
        s16 u3E;
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s8 u50;
        s8 u51;
        s8 u52;
        u8 pad53[0x1];
        s32 u54;
        s32 u58;
        s32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        u8 pad6F[0x1];
        s32 u70;
        s32 u74;
        s32 u78;
        s32 u7C;
        s32 u80;
        s32 u84;
        s32 u88;
        s32 u8C;
        s32 u90;
        s8 u94;
        s8 u95;
        u8 pad96[0x2];
        s16 u98;
        s16 u9A;
    } sp;

    sp.u18 = 8152.0f;
    sp.u1C = 40.0f;
    sp.u3E = 3;
    sp.u40 = -0x29;
    sp.u44 = -0x16;
    sp.u42 = 0x15;
    sp.u46 = 0x16;
    sp.u48 = 7;
    sp.u4E = 0x15;
    sp.u50 = 0xB;
    sp.u20 = 309.0f;
    sp.u3C = 2;
    sp.u4C = 0x30;
    sp.u52 = 0x28;
    sp.u54 = 1;
    sp.u58 = 4;
    sp.u6C = 0xFF;
    sp.u6D = 0xFF;
    sp.u70 = 3;
    sp.u4A = 0;
    sp.u51 = 1;
    sp.u5C = 0;
    sp.u60 = 0;
    sp.u64 = 0;
    sp.u68 = 0;
    sp.u6E = 0;
    sp.u74 = 0xFF;
    sp.u78 = 0;
    sp.u7C = 0x220005;
    sp.u80 = 0x1D0600;
    sp.u84 = 1;
    sp.u88 = 0x3B;
    sp.u8C = 0x80;
    sp.u90 = 0x20;
    sp.u94 = 0;
    sp.u95 = 7;
    sp.u98 = 0xC;
    sp.u9A = 0x15;
    sp.u34 = 100.0f;
    sp.u38 = 57.5f;
    sp.u24 = 55.6f;
    sp.u28 = 39.0f;
    sp.u2C = 0.46f;
    sp.u30 = 1.0f;
    func_15151FA8(&sp.u18, arg0 & 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/smoke_column_spawn_far.s")
#endif
// TODO: figure out this struct!
// void smoke_column_spawn_far(s32 arg0) {
//     s16 sp9A;
//     s16 sp98;
//     s8 sp95;
//     s8 sp94;
//     ?32 sp90;
//     ?32 sp8C;
//     ?32 sp88;
//     ?32 sp84;
//     ?32 sp80;
//     ?32 sp7C;
//     ?32 sp78;
//     ?32 sp74;
//     ?32 sp70;
//     s8 sp6E;
//     s8 sp6D;
//     s8 sp6C;
//     ?32 sp68;
//     ?32 sp64;
//     ?32 sp60;
//     ?32 sp5C;
//     ?32 sp58;
//     ?32 sp54;
//     s8 sp52;
//     s8 sp51;
//     s8 sp50;
//     s16 sp4E;
//     s16 sp4C;
//     s16 sp4A;
//     s16 sp48;
//     s16 sp46;
//     s16 sp44;
//     s16 sp42;
//     s16 sp40;
//     s16 sp3E;
//     s16 sp3C;
//     f32 sp38;
//     f32 sp34;
//     f32 sp30;
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//     f32 sp20;
//     f32 sp1C;
//     f32 sp18;
//
//     sp18 = *(void *)0x800A0258;
//     sp1C = 40.0f;
//     sp3E = 3;
//     sp40 = -0x29;
//     sp44 = -0x16;
//     sp42 = 0x15;
//     sp46 = 0x16;
//     sp48 = 7;
//     sp4E = 0x15;
//     sp50 = 0xB;
//     sp20 = *(void *)0x800A025C;
//     sp3C = 2;
//     sp4C = 0x30;
//     sp52 = 0x28;
//     sp54 = 1;
//     sp58 = 4;
//     sp6C = 0xFF;
//     sp6D = 0xFF;
//     sp70 = 3;
//     sp4A = 0;
//     sp51 = 1;
//     sp5C = 0;
//     sp60 = 0;
//     sp64 = 0;
//     sp68 = 0;
//     sp6E = 0;
//     sp74 = 0xFF;
//     sp78 = 0;
//     sp7C = 0x220005;
//     sp80 = 0x1D0600;
//     sp84 = (?32) (u8)1;
//     sp88 = 0x3B;
//     sp8C = 0x80;
//     sp90 = 0x20;
//     sp94 = 0;
//     sp95 = 7;
//     sp98 = 0xC;
//     sp9A = 0x15;
//     sp34 = 100.0f;
//     sp38 = 57.5f;
//     sp24 = *(void *)0x800A0260;
//     sp28 = 39.0f;
//     sp2C = *(void *)0x800A0264;
//     sp30 = 1.0f;
//     func_15151A38(&sp18, arg0 & 0xFF, 1);
// }

/* was func_150C2424 */
void fx_twin_beams_spawn(u8 arg0) {
    f32 r;

    r = random_float() * 8.0f + 8.0f;
    func_1514C9E0(8500.0f, -490.0f, -328.0f, 8500.0f, -490.0f, 328.0f, r, 1, 0, 0.0f, 0, arg0);
    r = random_float() * 3.0f + 4.0f;
    func_1514C9E0(8843.0f, -560.0f, -580.0f, 8117.0f, -560.0f, -580.0f, r, 3, 0, 0.0f, 0, arg0);
}
/* was func_150C251C */
s32 sprite_fade_in_alpha_b(struct_eu_sprite *arg0) {
    struct_eu_sprite_sub *sub = arg0->unk98;
    s32 v = arg0->unk1C * 8;

    if (v >= 0x100) {
        v = 0xFF;
    }
    sub->unk1B = v;
    if (sub->unk1B < 0) {
        return 0;
    }
    return 1;
}
#ifdef NON_MATCHING
/* P243: readable C for emit_point_smoke (game_EF410, 106 insns). */
// emit_point_smoke: D_8008ADA0 spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a,
// s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`): queues one func_15151FA8 smoke puff (owner byte argB,
// arg 1) at (x, y, z + 15 - rand * 30), sizes 22 / 44, 200 / 150, the byte angle (s32) (pz * 0.07012195f) - 0x40 and
// the fixed puff constants of the asm (the 0x84-byte request of func_150B8020; the last word stays unwritten, as in
// the asm). Always returns 1 (go on).
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 sizeA;
    /* 0x10 */ f32 sizeB;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s16 u24[10];
    /* 0x38 */ u8 u38[3];
    /* 0x3C */ s32 u3C[6];
    /* 0x54 */ u8 u54[3];
    /* 0x58 */ s32 u58[9];
    /* 0x7C */ u8 u7C[2];
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ s16 u80;
    /* 0x82 */ s16 u82;
    /* 0x84 */ s32 u84;
} Smoke2558;
f32 random_float(void);

/* was func_150C2558 */
s32 emit_point_smoke(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    Smoke2558 sm;
    f32 pz;

    sm.pos[0] = x;
    sm.pos[1] = y;
    pz = (z + 15.0f) - random_float() * 30.0f;
    sm.pos[2] = pz;
    sm.sizeA = 22.0f;
    sm.sizeB = 44.0f;
    sm.u14 = 0.0f;
    sm.u18 = 0.0f;
    sm.u1C = 200.0f;
    sm.u20 = 150.0f;
    sm.u24[0] = 1;
    sm.u24[1] = 0;
    sm.u24[2] = (s32) (pz * 0.07012195f) - 0x40;
    sm.u24[3] = 9;
    sm.u24[4] = 0;
    sm.u24[5] = 0;
    sm.u24[6] = 3;
    sm.u24[7] = 3;
    sm.u24[8] = 0x28;
    sm.u24[9] = 0x15;
    sm.u38[0] = 0xB;
    sm.u38[1] = 1;
    sm.u38[2] = 0x28;
    sm.u3C[0] = 1;
    sm.u3C[1] = 4;
    sm.u3C[2] = 0;
    sm.u3C[3] = 0;
    sm.u3C[4] = 0;
    sm.u3C[5] = 0;
    sm.u54[0] = 0xFF;
    sm.u54[1] = 0xFF;
    sm.u54[2] = 0;
    sm.u58[0] = 3;
    sm.u58[1] = 0xFF;
    sm.u58[2] = 0;
    sm.u58[3] = 0x220005;
    sm.u58[4] = 0x1D0600;
    sm.u58[5] = 1;
    sm.u58[6] = 0x3B;
    sm.u58[7] = 0x80;
    sm.u58[8] = 0x20;
    sm.u7C[0] = 0;
    sm.u7C[1] = 7;
    sm.u80 = 0xC;
    sm.u82 = 0x15;
    func_15151FA8((u8 *) &sm, argB & 0xFF, 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/emit_point_smoke.s")
#endif

/* was func_150C2700 */
s32 fx_blast_spawn_preset(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    extern f32 D_800A064C;
    S2700 s;

    s.u10 = arg4;
    s.u8 = arg2;
    s.uC = arg3;
    s.u14 = 6;
    s.u16 = 5;
    s.u0[0] = 0x6B;
    s.u0[1] = 0x46;
    s.u0[2] = -0x1F;
    s.u0[3] = 0x2E;
    s.u20 = 0x64;
    s.u22 = 0;
    s.u2C = 0x9B;
    s.u2D = 0x64;
    s.u34 = 0.0f;
    s.u38 = 1;
    s.u39 = 6;
    s.u3C = 0.0f;
    s.u40 = 1;
    s.u44 = 0.0f;
    s.u18 = 30.0f;
    s.u1C = 35.0f;
    s.u24 = -2.328f;
    s.u28 = 1.6630001f;
    s.u30 = D_800A064C;
    func_151506E8(&s, &s.u8, 0, argE, 1);
    return 1;
}
extern f32 D_800A0650, D_800A0654; // s105: 0x64C-0x664 stay externs (1655.0f is loaded from .rodata, not lui)
/* was func_150C2804 */
void fx_point_emitter_spawn(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    struct_eu_EF410 sp1C;

    sp1C.unkC = D_800A0650;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg1;
    sp1C.unk8 = arg2;
    sp1C.unk10 = D_800A0654;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 6;
    sp1C.unk18 = 3;
    sp1C.unk19 = -1;
    point_emitter_spawn(&sp1C, 0, arg4, arg5);
}
extern f32 D_800A0658, D_800A065C, D_800A0660; // C2898 keeps these as externs: literals add 8 frame bytes (s105)
/* was func_150C2898 */
void fx_debris_spray(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, struct_eu_2062D0_c *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 temp_f2;
    s32 pad;
    u32 sp54;
    u32 sp50;
    f32 sp4C;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_f2 = ((random_float() * 112.0f) + 247.0f) * D_800A0658;
    sp60[0] = -arg3 * temp_f2;
    sp60[1] = -arg4 * temp_f2;
    sp60[2] = -arg5 * temp_f2;
    sp4C = random_float();
    sp50 = random_int();
    sp54 = random_int();
    impact_dust_cloud_spawn(sp6C, sp60, 6, (sp4C * D_800A065C) + D_800A0660, (sp50 & 0xF) + 0x19, (sp54 % 101) + 0x9B, (random_float() * 119.0f) + 129.0f, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg6->unkC, arg6->unk1);
}
extern f32 D_800A0670, D_800A0674, D_800A0678, D_800A067C, D_800A0680, D_800A0684, D_800A0688, D_800A068C;
s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
/* was func_150C29F0 */
void fx_ring_particle_spawn(u8 *arg0)
{
  f32 t;
  struct 
  {
    f32 u3C;
    f32 u40;
    f32 u44;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
    f32 u58;
    s16 u5C;
    s16 u5E;
    s16 u60;
    u8 u62;
    u8 u63;
    u8 u64;
    u8 u65;
    s16 u66;
    u8 u68;
    u8 u69;
    u8 u6A;
    u8 u6B;
    s32 u6C;
    u8 u70;
    u8 pad71[3];
    f32 u74;
    f32 u78;
    f32 u7C;
    f32 u80;
  } sp;
  f32 scale;
  f32 *p;
  u8 r;
  f32 c;
  f32 s;
  f32 m;
  r = random_int() & 0xFF;
  c = angle_byte_cos(r - 0x40);
 do { s = angle_byte_cos(r); p = (f32 *) (arg0 + 0x28); m = p[2] * random_float(); sp.u5C = 0x6231; sp.u5E = 0x1A4D; } while (0); // fakematch: same-line do-while (permuter) orders the two sh stores
  sp.u62 = 0;
  sp.u63 = 0;
  sp.u64 = 0;
  sp.u65 = 0xFF;
  sp.u68 = 0xFF;
  sp.u69 = 0xFF;
  sp.u6C = 0;
  sp.u66 = 1;
  sp.u6A = 0;
  sp.u6B = 1;
  sp.u60 = (random_int() % 201U) + 100;
  sp.u70 = 0xF;
  sp.u74 = 0.0f;
  sp.u7C = D_800A0670;
  sp.u80 = D_800A0674;
  sp.u3C = p[0] + (m * c);
  sp.u40 = p[3];
  sp.u44 = p[1] + (m * s);
  sp.u78 = D_800A0678;
  scale = (random_float() * 0.5f) + 1.0f;
  t = (random_float() * 0.5f) + 1.0f;
  sp.u48 = D_800A067C * scale;
  sp.u50 = D_800A0680 * scale;
  sp.u4C = D_800A0684 * t;
  sp.u54 = D_800A0688 * t;
  sp.u58 = D_800A068C * t;
  func_15149AC0(&sp.u3C, 0xA, 1, 0, arg0[0xC], arg0[1]);
  *((s16 *) (arg0 + 0xE)) = (random_int() % 51U) + 0x19;
}
#ifdef NON_MATCHING
void func_1514373C(f32, f32, f32 *, f32 *);
s32 memcpy(s32, f32 *, s32);

/* was func_150C2C00 */
void fx_distant_burst_update(u8 *arg0) {
    struct {
        f32 u8C;
        u8 pad90[0x4];
        f32 u94;
        f32 u98;
        s32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        s8 uBD;
        s16 uBE;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s32 uC4;
        s8 uC8;
        u8 padC9[0x3];
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
    } sp;
    f32 *temp_s0;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    s32 temp_v0_2;

    temp_s0 = arg0 + 0x28;
    *temp_s0 += random_float() * 20.0f * 1e-9f * D_800BE9A4 * 3.6447764e7f;
    if (*temp_s0 > 1.0f) {
        temp_v0 = func_15144B34(D_80082FA4);
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0));
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 8));
        if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) > 2500000.0f) {
            sp.uB4 = 0x6231;
            sp.uB6 = 0x1A4D;
            sp.uBA = 0;
            sp.uBB = 0;
            sp.uBC = 0;
            sp.uBD = 0xFF;
            sp.uC1 = 0xFF;
            sp.uC2 = 0x14;
            sp.uC3 = 1;
            sp.uC4 = 4;
            sp.uBE = 1;
            sp.uC8 = 0x19;
            sp.u98 = -390.0f;
            sp.uD4 = 0.045f;
            sp.uD8 = 0.7f;
            sp.uD0 = 0.0f;
            do {
                sp.u8C = (random_float() * 5.8659425f) + 0.957204f;
                if (func_15144C8C(func_150484A0((*(f32 *)((u8 *)temp_v0 + 0)), (*(f32 *)((u8 *)temp_v0 + 8))), sp.u8C) < 0.4f) {
                    func_1514373C(sp.u8C, (random_float() * 1278.0f) + 3900.0f, &sp.u94, &sp.u9C);
                    temp_f20 = ((random_float() * 1991.0f) + 1985.0f) * 0.001f;
                    temp_f6 = random_float() * 1493.0f;
                    sp.uA0 = 22.6f * temp_f20;
                    sp.uA8 = 13.786f * temp_f20;
                    temp_f2_2 = (temp_f6 + 3000.0f) * 0.001f;
                    sp.uA4 = 57.969f * temp_f2_2;
                    sp.uAC = 42.714f * temp_f2_2;
                    sp.uB0 = 118.763f * temp_f2_2;
                    sp.uB8 = (random_int() % 151U) + 0x32;
                    sp.uCC = random_float() * 500.0f * 0.001f;
                    sp.uC0 = (random_int() % 156U) + 0x64;
                    temp_v0_2 = func_15149AC0(&sp.u94, 0xA, 1, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                    if (temp_v0_2 != 0) {
                        memcpy(temp_v0_2 + 0x160, &sp.u8C, 4);
                    }
                }
                *temp_s0 -= 1.0f;
            } while (*temp_s0 > 1.0f);
            return;
        }
        do {
            *temp_s0 -= 1.0f;
        } while (*temp_s0 > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/fx_distant_burst_update.s")
#endif
/* was func_150C2FCC */
s32 smoke_puff_shrink_rise(struct_eu_EF410_b *arg0) {
    arg0->unk2C -= arg0->unk2C * arg0->unk150;
    arg0->unk30 -= arg0->unk30 * arg0->unk150;
    arg0->unk38 += arg0->unk50 * D_800BE9A4 + 0.5f * arg0->unk4C * D_800BE9A4 * D_800BE9A4;
    arg0->unk50 += arg0->unk4C * D_800BE9A4;
    if (arg0->unk2C < 10.0f || arg0->unk30 < 10.0f) {
        return 0;
    }
    return 1;
}
/* was func_150C308C */
s32 fx_wake_near_camera(struct_eu_EF410_d *arg0) {
    u8 flag = FALSE;
    struct17 *v;
    f32 d;

    if (arg0->unk1C >= 6) {
        v = (struct17 *)func_15144B34(D_80082FA4);
        d = v->unk0 * v->unk0 + v->unk8 * v->unk8;
        if (d < 2500000.0f) {
            flag = TRUE;
        } else if (0.4f < func_15144C8C(func_150484A0(v->unk0, v->unk8), arg0->unk160)) {
            flag = TRUE;
        }
    }
    if (flag) {
        arg0->unk1C = 5;
    }
    return 1;
}
// ? fx_wake_near_camera(void *arg0) {
//     u8 sp1F;
//     f32 temp_f0;
//     f32 temp_f2;
//     u8 temp_a1;
//     void *temp_v0;
//     u8 phi_a1;
//
//     phi_a1 = (u8)0U;
//     if ((s32) arg0->unk1C >= 6) {
//         sp1F = 0;
//         temp_v0 = func_15144B34(D_80082FA4, (u8)0U);
//         temp_f0 = temp_v0->unk0;
//         temp_f2 = temp_v0->unk8;
//         temp_a1 = sp1F;
//         if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) < D_800A0310) {
// block_4:
//             phi_a1 = (u8)1U;
//         } else {
//             sp1F = temp_a1;
//             phi_a1 = temp_a1;
//             if (D_800A0314 < func_15144C8C(func_150484A0(temp_v0->unk0, temp_v0->unk8, temp_a1), arg0->unk160)) {
//                 goto block_4;
//             }
//         }
//     }
//     if (phi_a1 != 0) {
//         arg0->unk1C = (u16)5;
//     }
//     return 1;
// }

/* was func_150C3160 */
Gfx *obj_timer_scroll_tex_dl(Gfx *gfx, struct_eu_EF410_c *arg1) {
    f32 r;
    s32 v;
    s32 t;

    if (arg1->unk2E8 != 0) {
        r = (f32)arg1->unk2E4 / (f32)arg1->unk2E8;
    } else {
        r = 1.0f;
    }
    r = 1.0f - r;
    v = 500.0f * r + 2.0f;
    t = 2 - arg1->unk2EC;
    arg1->unk2EC = v / 3;
    while (t < 0) {
        t += 0x40;
    }
    gDPSetTileSize(gfx++, 4, v, t, 0x1FE, 0x3E);
    return gfx;
}
#ifdef NON_MATCHING
void obj_update_ground_tilt(struct127 *);
void obj_apply_gravity(struct127 *);
void func_1507C700(struct127 *, struct127 *);
void func_1506B04C(struct127 *, s32, void *);

// carried_object_update: update of an object that another one (unk65, 1-based D_800CC2D0 slot) can carry: always
// flag 0x4000000 in unkF8; when a carrier was set (unk222) and none is now, it restarts from its owner's position
// (unk124); then the usual movement steps (obj_update_ground_tilt / obj_apply_gravity / obj_update_floor / obj_land_on_floor), half the
// speed when unk28 is 0, the animation (obj_start_anim mode 0, or 2 / 3 / 1 by the carrier's unk84 0x1F9 / 0x1FB /
// other) and the carrier link (func_1507C700). With a timer (unk2E4): a carrier in state 5 drops it; the timer stops
// when nothing (D_800BE616 / D_800C35EA / carrier) holds it; while running it counts down by D_800BE9E4 (sound
// func_1508B20C when D_800BE616); when it runs out the carrier is released (stunned / immune cleared, health 1) and
// the object sends event 0xB (D_800BE616) or 0xE (func_1506B04C, its owner, position, carrier) and goes to state 1.
/* was func_150C3230 */
void carried_object_update(struct127 *obj) {
    struct {
        struct127 *owner;
        f32 pos[3];
        s32 carrier;
    } msg;
    struct127 *owner;
    struct127 *carrier;
    u16 id;
    u16 mode;

    obj->unkF8 |= 0x4000000;
    if (obj->unk222 != 0 && obj->unk65 == 0) {
        owner = &D_800CC2D0[obj->unk124 - 1];
        obj->old_x_position = owner->x_position;
        obj->old_y_position = owner->y_position;
        obj->old_z_position = owner->z_position;
        obj->unk222 = 0;
    }
    obj_update_ground_tilt(obj);
    obj_apply_gravity(obj);
    obj_update_floor(obj, obj->old_y_position);
    obj_land_on_floor(obj, obj->unk180);
    if (obj->unk28 == 0.0f) {
        obj->xz_velocity *= 0.5f;
    }
    if (obj->unk65 != 0) {
        obj->unk222 = obj->unk65;
        id = D_800CC2D0[obj->unk65 - 1].unk84.uh;
        if (id == 0x1F9) {
            mode = 2;
        } else if (id == 0x1FB) {
            mode = 3;
        } else {
            mode = 1;
        }
    } else {
        mode = 0;
    }
    obj_start_anim(obj, mode, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (obj->unk65 != 0) {
        func_1507C700(obj, &D_800CC2D0[obj->unk65 - 1]);
    }
    if (obj->unk2E4 == 0) {
        return;
    }
    carrier = NULL;
    if (obj->unk65 != 0) {
        carrier = &D_800CC2D0[obj->unk65 - 1];
        if (carrier->interaction_state == 5) {
            obj->unk65 = 0;
            obj->unk2E4 = 0;
        }
    }
    if (D_800BE616 == 0 && D_800C35EA == 0 && obj->unk65 == 0) {
        obj->unk2E4 = 0;
    }
    if (D_800BE9E4 < obj->unk2E4) {
        obj->unk2E4 -= D_800BE9E4;
        if (D_800BE616 != 0) {
            func_1508B20C(obj->x_position, obj->y_position, obj->z_position, 900.0f);
        }
        return;
    }
    msg.pos[0] = obj->x_position;
    msg.pos[1] = obj->y_position;
    msg.pos[2] = obj->z_position;
    msg.owner = &D_800CC2D0[obj->unk124 - 1];
    msg.carrier = obj->unk65;
    if (carrier != NULL) {
        carrier->stunned = 0;
        carrier->immune = 0;
        if (carrier->health != 0) {
            carrier->health = 1;
        }
    }
    func_1506B04C(obj, D_800BE616 ? 0xB : 0xE, &msg);
    obj_remove(obj, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/carried_object_update.s")
#endif
#ifdef NON_MATCHING
void move_xz_towards(f32, f32, f32, f32 *, f32 *);
f32 obj_approach_speed(f32, struct127 *, f32, f32, u8);
u8 obj_turn_towards(struct127 *, u8, u16);
void func_1001091C(u8 *, s32);

// rolling_object_update: per-frame update of a rolling object (barrel / ball; kinds 0x25, 0x10, 0xAC): unk80 = 10;
// kind 0x25 first damps its push vector (move_xz_towards, 0.15) and, when unk87 bit 0, keeps its height in unk224;
// friction (obj_approach_speed, 2 / 0.1 or 0.25), gravity 3, the move (obj_walk_update, water obj_carried_update) and animation.
// Its frame velocity (unkBC / unk148 = position delta x D_800BEDC8) gives the speed d; xz_velocity is capped at 2d
// when it exceeds 2(d + 4). unk87 == 4 (a hit) fires event 0xFF020133 as the player (objev_sound_alt_300_1800) and stores the
// velocity as the push vector. unk87 shifts left each frame. Moving faster than 0.5 on land turns the heading unk78
// towards the motion (math_atan2_u16) and the facing towards it or its opposite (obj_turn_towards). The roll speed unk44
// decays by 0.9 in the air (unk28 > 30), else is 2d (0 in water) and spins the model (func_15052490, scale
// (2 - xz_scale) x 0.375 / 0.28125 / 1.125 by kind). Below 0.2 the rolling sound stops (func_100109D0); otherwise it
// is started (objev_sound_300_1800 with sound 0x630 / 0x67A / 0x62A by kind) or its pitch set to unk44 x 2500 (max 28000,
// halved for kind 0x25, func_1001091C).
/* was func_150C3574 */
void rolling_object_update(struct127 *obj) {
    f32 scale;
    f32 friction;
    f32 d;
    u16 heading;
    s32 pitch;
    u8 flags;

    scale = 0.5f;
    obj->unk80 = 10;
    if (obj->id == 0x25) {
        move_xz_towards(0.0f, 0.0f, 0.15f, &obj->unk164, &obj->unk168);
        friction = 0.1f;
        if (obj->unk87 & 1) {
            obj->unk224 = (s32) obj->y_position;
        }
        obj->unk160 = 0;
    } else {
        friction = 0.25f;
    }
    obj_approach_speed(0.0f, obj, 2.0f, friction, 0);
    obj->gravity = 3.0f;
    if (obj->id == 0x10) {
        scale = 0.375f;
    }
    if (obj->id == 0xAC) {
        scale = 1.5f;
    }
    scale *= 0.75f;
    obj_walk_update(obj);
    if (obj->unk13D != 0) {
        obj_carried_update(obj);
    }
    obj_physics_step(obj);
    obj->unkBC = (obj->x_position - obj->old_x_position) * D_800BEDC8;
    obj->unk148 = (obj->z_position - obj->old_z_position) * D_800BEDC8;
    d = sqrtf(obj->unkBC * obj->unkBC + obj->unk148 * obj->unk148);
    if ((d + 4.0f) + (d + 4.0f) < obj->xz_velocity) {
        obj->xz_velocity = d + d;
    }
    flags = obj->unk87;
    if (flags == 4) {
        D_800D1580 = 0xFF020133;
        D_800D154C = D_800CC2D0;
        objev_sound_alt_300_1800();
        D_800D154C = obj;
        obj->unk164 = obj->unkBC;
        obj->unk168 = obj->unk148;
        obj->xz_velocity = 0.0f;
        flags = obj->unk87;
    }
    obj->unk87 = flags << 1;
    if (0.5f < d && obj->unk13D == 0) {
        obj->unk78 = math_atan2_u16(obj->x_position - obj->old_x_position, obj->old_z_position - obj->z_position, 0);
    }
    heading = obj->unk78;
    if ((obj->unk7A - heading - 0x4000) & 0x8000) {
        obj_turn_towards(obj, 2, heading);
    } else {
        obj_turn_towards(obj, 2, heading ^ 0x8000);
    }
    if (30.0f < obj->unk28) {
        obj->unk44 *= 0.9f;
    } else {
        obj->unk44 = d + d;
    }
    if (obj->unk13D != 0) {
        obj->unk44 = 0.0f;
    }
    func_15052490(obj, obj->unk78, obj->unk44, (2.0f - obj->xz_scale) * scale);
    if (obj->unk44 < 0.2f) {
        func_100109D0(obj);
    } else if (func_100107F8(obj) == 0) {
        if (obj->id == 0xAC) {
            D_800D1580 = 0x630;
        } else if (obj->id == 0x25) {
            D_800D1580 = 0x67A;
        } else {
            D_800D1580 = 0x62A;
        }
        objev_sound_300_1800();
    } else {
        pitch = (s32) (obj->unk44 * 2500.0f);
        if (pitch > 28000) {
            pitch = 28000;
        }
        if (obj->id == 0x25) {
            pitch >>= 1;
        }
        func_1001091C((u8 *) obj, pitch);
    }
    if (obj->unk44 < 0.2f) {
        func_100109D0(obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/rolling_object_update.s")
#endif
#ifdef NON_MATCHING
void func_15188D80(struct127 *, s32, s32);
s32 func_150C1B60(f32, f32, f32, s32);
void bomb_explode(struct127 *);
void func_151BA1A0(s32, s32, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

// bouncing_bomb_update: per-frame update of a falling / bouncing object. In state 20 it spawns a small dust puff
// (func_151BA1A0 effect 0x2F) at its position, or with a timer (unk2E4) shows it (func_15188D80). On a fast enough
// landing (falling, unk28 > 20 and unk28 < -20 x vy) it plays sound 0x92 once (unk136). On the first frame (unk83 0)
// it sets the spin speed unk148 = 70, spawns a big puff plus a light (func_150C1B60) and sends event 6, or with a
// timer shows it, plays sound 0x1A9, sets unkD0, flags 0x1008000 and unk114 = 500. Each frame: unk83 counts up,
// immune 0xFF, flag 0x8000 cleared from frame 11; facing unk40 from unk7A, animation, spin unkB8 += unk148 with
// unk148 x 0.96. It ends (bomb_explode, sound 0x93, state 1) once it rests (unk28 0) after frame 20 with unkCC 0,
// or when unk107 is set or its health is 0.
/* was func_150C3994 */
void bouncing_bomb_update(struct127 *obj) {
    if (obj->interaction_state == 20) {
        if (obj->unk2E4 == 0) {
            func_151BA1A0(0x2F, 1, (s16) (s32) obj->x_position, (s16) (s32) (obj->y_position + 30.0f),
                          (s32) obj->z_position, 2000, 1000, 400, 200, 0xC00, 0xC00, 1, 1, 0, 0xFF, 0);
        } else {
            func_15188D80(obj, 100, 0);
        }
    }
    if (obj->y_velocity < 0.0f && 20.0f < obj->unk28 && obj->unk136 == 0 &&
        obj->unk28 < -20.0f * obj->y_velocity) {
        func_10010630(0x92, obj, 0x7D00, 200, 2500);
        obj->unk136 = 1;
    }
    if (obj->unk83 == 0) {
        obj->unk148 = 70.0f;
        if (obj->unk2E4 == 0) {
            func_151BA1A0(0x2F, 1, (s16) (s32) obj->x_position, (s16) (s32) (obj->y_position + 30.0f),
                          (s32) obj->z_position, 2200, 1280, 800, 700, 0xC00, 0xC00, 20, 1, 0, 0xFF, 0);
            func_150C1B60(obj->x_position, obj->y_position + 30.0f, obj->z_position, 0xFF);
            func_1506B04C(obj, 6, NULL);
        } else {
            func_15188D80(obj, 100, 0);
        }
        func_10010344(0x1A9, obj, 0x7FFF, 1000, 2000);
        obj->unkD0 = 1;
        obj->unkF8 |= 0x1008000;
        obj->unk114 = 500.0f;
    }
    obj->immune = 0xFF;
    obj->unk83++;
    if (obj->unk83 >= 11) {
        obj->unkF8 &= ~0x8000;
    }
    obj->unk40 = (f32) (obj->unk7A + 0x4000) * 0.0054931640625f;
    obj_physics_step(obj);
    obj->unkB8 += obj->unk148;
    obj->unk148 *= 0.96f;
    if ((obj->unk28 == 0.0f && obj->unk83 >= 21 && obj->unkCC == 0) || obj->unk107 != 0 || obj->health == 0) {
        bomb_explode(obj);
        func_10010630(0x93, obj, 0x7D00, 200, 2500);
        obj_remove(obj, 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/bouncing_bomb_update.s")
#endif

/* was func_150C3D48 */
s32 checksum_key_offset(s32 arg0) {
    return arg0 + 0xEDCBA988;
}

s32 func_1516DF0C(s16, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15170F24(s32, s32, s32, s32, f32, s32, s32);
void func_15171770(s32, s32, f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
#ifdef NON_MATCHING // the definition is void (P284)
void func_151BA1A0(s32, s32, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#else
s32 func_151BA1A0(s32, s32, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#endif
s32 checksum_key_offset(s32 arg0);
s32 func_151EF800(u32, u32 *);
#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32);
#else
s32 func_10004074(s32);
#endif

/* was func_150C3D5C */
void bomb_explode(struct127 *arg0) {
    s32 sum;
    s32 pad[2]; // fakematch: unused 8-byte slot above the Header locals
    Header header;
    Header2 header2;

    func_151BA1A0(0x2F, 1, arg0->x_position, arg0->y_position, arg0->z_position, 0x578, 0x500, 0x320, 0x4B0, 0x200, 0x200, 0x1E, 1, 0, 0xFF, 0);
    ((s32 (*)(u32, u32 *))func_151EF800)(checksum_key_offset(sum = 0xC23459B8), (u32 *)&sum);
    if (sum != 0x0330C820) {
        ((u32 *)&func_10004074)[0] = 0x03E00008;
        ((u32 *)&func_10004074)[1] = 0;
    }
    func_15171770(3, 0xCB, arg0->x_position, arg0->y_position, arg0->z_position, 10.0f, 1.0f, 2.0f, 60.0f, 3, 0x3C, -0.7f, 0xFF, 0);
    func_15170F24(arg0->x_position, arg0->y_position + 20.0f, arg0->z_position, 0xA, 2000.0f, 0xFF, 0);
    func_1516DF0C(arg0->x_position, arg0->y_position, arg0->z_position, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0, 0, 0, 0x14, 0x14, 2, 0, 0, 0, 0, 0x51, 0x51, 0x51, 0x51, 0xA, 1, 0, 0xFF, 0xA, 0x578, 0x190, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0xFF, 0);
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (random_int() % 11U) + 0xA;
    header.unk4 = 0;
    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position;
    header2.unk8 = arg0->z_position;
    light_create_with_ctrl(&header, &header2, (random_int() % 52U) + 0x28, 0xFF, 0xFF, 0x5A, 0xFF, 0, 0, 0xFF, 1);
}
