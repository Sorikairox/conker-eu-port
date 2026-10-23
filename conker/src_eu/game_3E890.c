#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#if 0
f32 D_800964C0 = 175.5;
f32 D_800964C4 = 115.4000015258789;
f32 D_800964C8 = 1.0420000553131104;
f32 D_800964CC = 0.9010000228881836;
f32 D_800964D0 = 1.2009999752044678;
f32 D_800964D4 = 0.7023000121116638;
f32 D_800964D8 = 2337.0;
f32 D_800964DC = 2220.0;
f32 D_800964E0 = 0.4099999964237213;
f32 D_800964E4 = 0.20000000298023224;
f32 D_800964E8 = 0.3499999940395355;
f32 D_800964EC = 0.3499999940395355;
f32 D_800964F0 = 9.999999974752427e-07;
f32 D_800964F4 = 2337.0;
f32 D_800964F8 = 2220.0;
f32 D_800964FC = 926.0;
f32 D_80096500 = -710.0;
f32 D_80096504 = -339.0;
// dont think these belong here?
f32 D_80096508 = 15.045271873474121;
f32 D_8009650C = 5.8676557540893555;
#endif

// typedef struct {
//     f32 sp38;
//     f32 sp3C;
//     f32 sp40;
//     f32 sp44;
//     f32 sp48;
//     f32 sp4C;
//     f32 sp50;
//     s8  sp54;
//     s8  pad55[0x1];
//     s16 sp56;
//     s16 sp58;
//     u8  pad5A[0x2];
//     s32 sp5C;
//     s32 sp60;
//     s8  sp64;
//     s8  sp65;
//     s8  sp66;
//     s8  sp67;
//     f32 sp68;
//     f32 sp6C;
//     f32 sp70;
//     f32 sp74;
//     f32 sp78;
//     f32 sp7C;
//     f32 sp80;
//     f32 sp84;
//     f32 sp88;
//     f32 sp8C;
//     f32 sp90;
//     s32 sp94;
//     s8  sp98;
//     s8  sp99;
//     s8  sp9A;
//     s8  sp9B;
//     f32 spAC;
//     f32 spB0;
//     f32 spB4;
//     f32 spB8;
//     f32 spBC;
//     f32 spC0;
//     f32 spC4;
//     f32 spC8;
//     f32 spCC;
//     u8  padD0[0x24];
//     f32 spF4;
//     u8 padF8[0x8];
//     s8 sp100;
//     s8 sp101;
//     s8 sp102;
//     s8 sp103;
//     s8 sp104;
// } structaaa;

#ifdef NON_MATCHING
/* P127: the stack blocks of func_150113E0, one struct so the layout is the N64 one (sp38 / sp54 / spAC) */
typedef struct {
    f32 tail[7];            /* 0x00 (sp38): copied to the emitter's +0x170 */
    struct {                /* 0x1C (sp54): spawn block, func_151407D0 argument 2 (0x58 bytes) */
        u8 kind;            /* 0x00 */
        u8 pad1;
        u16 flags;          /* 0x02 */
        u16 life;           /* 0x04 */
        u8 pad6[2];
        s32 u8_;            /* 0x08 */
        s32 uC;             /* 0x0C */
        u8 rgba[4];         /* 0x10 */
        f32 size[2];        /* 0x14 */
        f32 pos0[3];        /* 0x1C: from (x, y, z) */
        f32 pos1[3];        /* 0x28: to (x, y, z) */
        f32 scale[3];       /* 0x34 */
        s32 u40;            /* 0x40 */
        u8 u44[4];          /* 0x44 */
        u8 pad48[0x10];
    } spawn;
    struct {                /* 0x74 (spAC): emitter block, func_151407D0 argument 0 (0x7C bytes) */
        f32 range[4];       /* 0x00 */
        f32 u10;            /* 0x10 */
        f32 u14[4];         /* 0x14 */
        u8 pad24[0x24];
        f32 u48;            /* 0x48 */
        u8 pad4C[8];
        u8 u54[5];          /* 0x54 */
        u8 pad59[0x23];
    } emit;
} Fire150113E0;
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9);

// level_fire_emitters_create: P127: level start (new game, level 0x18): creates four particle emitters
// (func_151407D0, flags 0x20) with one spawn block whose from / to positions change per emitter ((+-520, 72,
// 2337 / 2220), (-710 / -584, 70, 926), (506, 47, -339 / -208)); each new emitter gets the 7-float tail at +0x170.
void func_150113E0(void) {
    Fire150113E0 b;
    u8 *e;

    b.tail[0] = 1.042f;
    b.tail[1] = 0.901f;
    b.tail[2] = 1.201f;
    b.tail[4] = 0.0f;
    b.tail[5] = 7.0f;
    b.tail[6] = 0.7023f;
    b.spawn.pos0[2] = 2337.0f;
    b.spawn.pos1[2] = 2220.0f;
    b.emit.u10 = 0.41f;
    b.spawn.kind = 3;
    b.spawn.flags = 0x3403;
    b.spawn.life = 300;
    b.spawn.rgba[0] = 0xE6;
    b.tail[3] = 1.0f;
    b.spawn.u8_ = 0;
    b.spawn.uC = 0;
    b.spawn.rgba[1] = 100;
    b.spawn.rgba[2] = 0;
    b.spawn.rgba[3] = 0xFF;
    b.spawn.size[0] = 100.0f;
    b.spawn.size[1] = 100.0f;
    b.spawn.pos0[0] = 520.0f;
    b.spawn.pos0[1] = 72.0f;
    b.spawn.pos1[0] = 520.0f;
    b.spawn.pos1[1] = 72.0f;
    b.spawn.scale[0] = 1.0f;
    b.spawn.scale[1] = 1.0f;
    b.spawn.scale[2] = 1.0f;
    b.spawn.u40 = 0xD2012;
    b.spawn.u44[1] = 0xFF;
    b.spawn.u44[0] = 0xFF;
    b.spawn.u44[2] = 0;
    b.spawn.u44[3] = 6;
    b.emit.range[1] = 175.5f;
    b.emit.range[0] = 175.5f;
    b.emit.range[3] = 115.4f;
    b.emit.range[2] = 115.4f;
    b.emit.u54[0] = 0;
    b.emit.u54[1] = 0;
    b.emit.u54[2] = 0;
    b.emit.u54[3] = 0;
    b.emit.u48 = 1.0f;
    b.emit.u54[4] = 0;
    b.emit.u14[0] = 0.2f;
    b.emit.u14[1] = 0.35f;
    b.emit.u14[2] = 0.35f;
    b.emit.u14[3] = 0.000001f;
    e = func_151407D0(&b.emit, 0x7C, &b.spawn, 0, 0x20, 0, 0, -1, 0xFF, 1);
    if (e != NULL) {
        memcpy(e + 0x170, b.tail, 0x1C);
    }

    b.spawn.pos0[0] = -520.0f;
    b.spawn.pos1[0] = -520.0f;
    b.spawn.pos0[1] = 72.0f;
    b.spawn.pos1[1] = 72.0f;
    b.spawn.pos0[2] = 2337.0f;
    b.spawn.pos1[2] = 2220.0f;
    e = func_151407D0(&b.emit, 0x7C, &b.spawn, 0, 0x20, 0, 0, -1, 0xFF, 1);
    if (e != NULL) {
        memcpy(e + 0x170, b.tail, 0x1C);
    }

    b.spawn.pos0[1] = 70.0f;
    b.spawn.pos1[1] = 70.0f;
    b.spawn.pos0[2] = 926.0f;
    b.spawn.pos1[2] = 926.0f;
    b.spawn.pos0[0] = -710.0f;
    b.spawn.pos1[0] = -584.0f;
    e = func_151407D0(&b.emit, 0x7C, &b.spawn, 0, 0x20, 0, 0, -1, 0xFF, 1);
    if (e != NULL) {
        memcpy(e + 0x170, b.tail, 0x1C);
    }

    b.spawn.pos0[0] = 506.0f;
    b.spawn.pos1[0] = 506.0f;
    b.spawn.pos0[1] = 47.0f;
    b.spawn.pos1[1] = 47.0f;
    b.spawn.pos0[2] = -339.0f;
    b.spawn.pos1[2] = -208.0f;
    e = func_151407D0(&b.emit, 0x7C, &b.spawn, 0, 0x20, 0, 0, -1, 0xFF, 1);
    if (e != NULL) {
        memcpy(e + 0x170, b.tail, 0x1C);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_150113E0.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_1501175C.s")

void func_15011A78(struct127 *arg0, u8 arg1, s32 arg2) {
    struct182 tmp;
    struct37 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unique_id;
    tmp.unk6 = 0;

    temp_v0 = func_15149130(300, -1, 85, -1, 0, 66, 8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 8);
    }
}
