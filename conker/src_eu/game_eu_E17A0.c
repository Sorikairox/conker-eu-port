#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1514CDC8(f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, f32, s32, s32);
void func_151D45A4(f32 *, u8, s32);
extern s32 D_800BEE08;
extern u8 D_8009FF90[];
void func_150B3AB0(struct127 *arg0, u8 arg1) {
    s16 angle;
    struct17 pos;
    structEU_151D8E18 blk;

    if (arg0 != NULL && arg0->unk1D4 != NULL) {
        func_1512D748(&D_800DBFF0[D_800BEE08], 6, 1);
        angle = (*(u16 *)((u8 *)arg0 + 0x7A) >> 8) + 0x40;
        func_15143134(D_8009FF90, &pos, (u8 *)arg0->unk1D4 + 0x640);
        func_1514CDC8(pos.unk0, pos.unk4, pos.unk8, 10.0f, angle, 0, 0xFF, (u32)func_150ADA20() % 31 + 0x28, 8, 0, 0.0f, 0, arg1);
        blk.unk0 = 1;
        blk.unk2 = (func_150ADA20() & 0xF) + 0xC;
        blk.unk4 = (func_150ADA20() & 3) + 5;
        blk.unk6 = -1;
        blk.unk5 = 1;
        func_151D8E18(&blk, 0, arg1, 0);
        func_151D45A4((f32 *)&pos, arg1, 0);
    }
}

#ifdef NON_MATCHING
/* P243: readable C for func_150B40EC (game_eu_E17A0, 113 insns). */
// emit_point_spark_ring: D_8008ADA0 spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0,
// s32 a, s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`), the sibling of func_150B2A50 (game_eu_E0170):
// one func_15156700 particle (S_3f24 record) at (x, y, z) heading along the byte angle angle0 and tilted by the point
// angle a: velocity (10 sin(a) sin(angle0 - 0x40), -10 sin(a - 0x40), 10 sin(a) sin(angle0)) (angle_byte_cos =
// byte-angle sine), random sizes 1.953 * r + 3.736 / 0.94 * r + 2.223 / 2.66 * r + 1.85 (rodata D_8009FF9C..B0), two
// palette-8 colour triples with alpha 0xFF, 9, life 15..30 ((rand & 0xF) + 15), 0x1601, -1, 0xA, 0x19; owner byte
// argB; then func_151568F8(&rec, 1, 0) on the same record. Always returns 1 (go on).
typedef struct {
    f32 pos[3];
    f32 vel[3];
    f32 a;
    f32 b;
    u8 c[9];
    s16 d;
    u16 e;
    f32 f;
    s8 g;
    s16 h;
    s16 i;
} Spark40EC;
f32 angle_byte_cos(u8);
void func_151429E0(u8, u8 *, u8 *, u8 *);
s32 func_15156700(Spark40EC *, u8, s32, u8, s32);
void func_151568F8(Spark40EC *, u8, s32);

s32 func_150B40EC(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    Spark40EC sp;
    f32 ch, sh, ct, spd;

    ch = angle_byte_cos((angle0 - 0x40) & 0xFF);
    sh = angle_byte_cos(angle0 & 0xFF);
    ct = angle_byte_cos((a - 0x40) & 0xFF);
    spd = 10.0f * angle_byte_cos(a & 0xFF);
    sp.pos[0] = x;
    sp.pos[1] = y;
    sp.pos[2] = z;
    sp.vel[0] = spd * ch;
    sp.vel[1] = -10.0f * ct;
    sp.vel[2] = spd * sh;
    sp.a = func_150ADA68() * 1.9530001f + 3.736f;
    sp.b = func_150ADA68() * 0.94000006f + 2.223f;
    func_151429E0(8, &sp.c[0], &sp.c[1], &sp.c[2]);
    func_151429E0(8, &sp.c[4], &sp.c[5], &sp.c[6]);
    sp.c[3] = 0xFF;
    sp.c[7] = 0xFF;
    sp.c[8] = 9;
    sp.d = (func_150ADA20() & 0xF) + 0xF;
    sp.f = func_150ADA68() * 2.6599998f + 1.8499999f;
    sp.e = 0x1601;
    sp.g = -1;
    sp.h = 0xA;
    sp.i = 0x19;
    func_15156700(&sp, 1, 0, argB & 0xFF, 1);
    func_151568F8(&sp, 1, 0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E17A0/func_150B40EC.s")
#endif
