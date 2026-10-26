#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P153 */
s32 func_150A3538(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 func_150ACEA0(f32 x0, f32 y0, f32 z0, f32 dx, f32 dy, f32 dz, s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11,
                  s32 a12, s32 a13, f32 a14);
u8 func_15145C90(s32 arg0);
void func_1515176C(u8 *arg0, s32 arg1, s32 arg2);

/* the stack blocks of func_150BA3B0 in one struct so the layout is the N64 one (offsets = original sp offsets) */
typedef struct {
    struct {                  /* sp70: splash ring, func_1515176C argument 0 (0x74 bytes) */
        s16 u0;               /* 0x00 */
        s16 u2;               /* 0x02 */
        f32 pos[3];           /* 0x04: ray hit point */
        f32 dir[3];           /* 0x10: ray direction, negated */
        s16 hit[9];           /* 0x1C: hit record of func_150ACEA0 */
        u8 pad2E[2];
        f32 u30;              /* 0x30 */
        u8 u34;               /* 0x34 */
        u8 u35;               /* 0x35 */
        s16 u36;              /* 0x36 */
        s16 u38;              /* 0x38 */
        s16 u3A;              /* 0x3A */
        f32 u3C;              /* 0x3C */
        f32 u40;              /* 0x40 */
        s32 u44;              /* 0x44 */
        u8 u48;               /* 0x48 */
        u8 u49;               /* 0x49 */
        u8 pad4A[2];
        f32 u4C[4];           /* 0x4C */
        u8 u5C;               /* 0x5C */
        u8 u5D;               /* 0x5D */
        u8 pad5E[2];
        s32 u60;              /* 0x60 */
        s32 u64;              /* 0x64 */
        s16 u68;              /* 0x68 */
        s16 u6A;              /* 0x6A */
        f32 u6C[2];           /* 0x6C */
    } ring;
    struct {                  /* spE4: drop spawn block, sprite_fx_spawn_cam_at argument 0 (0x28 bytes) */
        s32 kindFlags;        /* 0x00: kind 0, flags 0x9F01 */
        s16 life;             /* 0x04 */
        u8 u6;                /* 0x06 */
        u8 u7;                /* 0x07 */
        s32 u8_;              /* 0x08 */
        s32 uC;               /* 0x0C */
        u8 u10[8];            /* 0x10 */
        s32 u18;              /* 0x18 */
        u8 pad1C[6];
        s16 u22;              /* 0x22 */
        s16 u24;              /* 0x24 */
        u8 pad26[2];
    } drop;
    s32 surface;              /* sp10C: surface of the ray hit */
    s16 hit[9];               /* sp110 */
    u8 pad122[2];
    f32 pos[3];               /* sp124 */
} Frame3B0;

// water_splash_spawn: P153: splash where obj (pos +0x14) meets the water between it and (x, z): when neither
// func_150A3538 test (2, 1) holds at the object's position, casts a ray from 80 units above the object towards
// (x, z) (func_150ACEA0); on a hit whose surface passes func_15145C90 it spawns a drop record (sprite_fx_spawn_cam_at,
// random life 100..150, alpha 155..255, random size 40..60 and flips) and always a ring (func_1515176C) at the hit
// point. The original first checksums the code range func_151E86A4..func_151E870C (anti-tamper: sets
// D_800843F0[0] = 0xFF unless the sum of ~words is 0x38424614); the port's code is not N64 code, so that check
// is left out (it passes on an unmodified cartridge).
void func_150BA3B0(u8 *obj, f32 x, f32 z, u8 arg3, s32 arg4) {
    Frame3B0 f;
    f32 dx;
    f32 dz;
    f32 size0;
    f32 size1;
    s32 alpha;
    s32 flip;

    if (obj == NULL) {
        return;
    }
    if (func_150A3538(2, (s32) *(f32 *) (obj + 0x14), (s32) *(f32 *) (obj + 0x18), (s32) *(f32 *) (obj + 0x1C)) != 0) {
        return;
    }
    if (func_150A3538(1, (s32) *(f32 *) (obj + 0x14), (s32) *(f32 *) (obj + 0x18), (s32) *(f32 *) (obj + 0x1C)) != 0) {
        return;
    }
    dx = -(*(f32 *) (obj + 0x14) - x);
    dz = -(*(f32 *) (obj + 0x1C) - z);
    if (func_150ACEA0(*(f32 *) (obj + 0x14), *(f32 *) (obj + 0x18) + 80.0f, *(f32 *) (obj + 0x1C), dx, 0.0f, dz, 0,
                      (s32) f.hit, (s32) &f.pos[0], (s32) &f.pos[1], (s32) &f.pos[2], 0, (s32) &f.surface, 0,
                      0.0f) == 0) {
        return;
    }
    if (func_15145C90(f.surface) != 0) {
        f.drop.u6 = 6;
        f.drop.u7 = 0;
        f.drop.kindFlags = 0x9F01;
        f.drop.life = (u32) random_int() % 51 + 100;
        f.drop.u8_ = 0;
        f.drop.uC = 0;
        f.drop.u10[0] = (u32) random_int() % 101 + 155;
        f.drop.u10[1] = 0xFF;
        f.drop.u10[2] = 0xFF;
        f.drop.u10[3] = 0xFF;
        f.drop.u10[4] = 0xFF;
        f.drop.u10[5] = 0xFF;
        f.drop.u18 = 0x3B0002;
        f.drop.u10[6] = 0;
        f.drop.u10[7] = 7;
        f.drop.u22 = 0x19;
        f.drop.u24 = 0xA;
        size0 = random_float();
        size1 = random_float();
        alpha = random_int();
        flip = random_int();
        sprite_fx_spawn_cam_at((s32) &f.drop, 0, 0, (s32) f.hit, f.pos[0], f.pos[1], f.pos[2], size0 * 20.0f + 40.0f,
                      size1 * 20.0f + 40.0f, alpha & 0xFF, (random_int() & 1) + (flip & 1) * 2, 3, 0xFF, 0, arg3,
                      arg4);
    }
    f.ring.u0 = 0xF;
    f.ring.u2 = 0xA;
    f.ring.pos[0] = f.pos[0];
    f.ring.pos[1] = f.pos[1];
    f.ring.pos[2] = f.pos[2];
    f.ring.dir[1] = -0.0f;
    f.ring.dir[0] = -dx;
    f.ring.dir[2] = -dz;
    f.ring.hit[0] = f.hit[0];
    f.ring.hit[1] = f.hit[1];
    f.ring.hit[2] = f.hit[2];
    f.ring.hit[3] = f.hit[3];
    f.ring.hit[4] = f.hit[4];
    f.ring.hit[5] = f.hit[5];
    f.ring.hit[6] = f.hit[6];
    f.ring.hit[7] = f.hit[7];
    f.ring.hit[8] = f.hit[8];
    f.ring.u30 = 675.0f;
    f.ring.u3C = 7.0f;
    f.ring.u40 = 10.0f;
    f.ring.u4C[0] = -1.0220001f; /* 0xBF82D0E6 */
    f.ring.u4C[1] = 0.54200006f; /* 0x3F0AC084 */
    f.ring.u34 = 7;
    f.ring.u36 = 0x3B01;
    f.ring.u35 = 0;
    f.ring.u38 = 0x1A;
    f.ring.u3A = 0x14;
    f.ring.u44 = 0x5C0001;
    f.ring.u48 = 100;
    f.ring.u49 = 155;
    f.ring.u5C = 0;
    f.ring.u5D = 7;
    f.ring.u60 = 3;
    f.ring.u64 = 0xFF;
    f.ring.u68 = 0xA;
    f.ring.u6A = 0x19;
    f.ring.u4C[2] = 0.0374f;
    f.ring.u4C[3] = 0.0235f;
    f.ring.u6C[0] = 0.940404f;
    f.ring.u6C[1] = 1.0840001f; /* 0x3F8AC084 */
    func_1515176C((u8 *) &f.ring, arg3, arg4);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA3B0.s")
#endif

s32 func_150BA83C(u8 *arg0) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
    if (temp_v0 < 0x40) {
        (*(s8 *)((u8 *)arg0 + 0x28)) = (s8) (temp_v0 * 4);
    }
    return 1;
}

s32 func_150BA85C(f32 *arg0) {
    arg0[0x114 / 4] += D_800A01FC * D_800BE9A4;
    arg0[0x34 / 4] += arg0[0x110 / 4] * D_800BE9A4;
    arg0[0x38 / 4] += arg0[0x114 / 4] * D_800BE9A4;
    arg0[0x3C / 4] += arg0[0x118 / 4] * D_800BE9A4;
    arg0[0x40 / 4] += arg0[0x11C / 4] * D_800BE9A4;
    arg0[0x44 / 4] += arg0[0x120 / 4] * D_800BE9A4;
    return 1;
}

#ifdef NON_MATCHING
/* P143 */
// effect_fade_by_height: update handler (D_8008A100 slot 2) of a sprite effect: alpha +0x5C = min(life +0x1C * 16,
// height above +0x124 (y +0x38 minus floor) * 4, 255). Returns 0 (effect ends) once it is below the floor, else 1.
s32 func_150BA904(u8 *fx) {
    f32 height = *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x124);
    s32 byLife;
    s32 byHeight;

    if (height < 0.0f) {
        return 0;
    }
    byLife = *(s16 *)(fx + 0x1C) << 4;
    if (byLife >= 0x100) {
        byLife = 0xFF;
    }
    byHeight = (s32)height << 2;
    if (byHeight >= 0x100) {
        byHeight = 0xFF;
    }
    fx[0x5C] = (byHeight < byLife) ? byHeight : byLife;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E7BC0/func_150BA904.s")
#endif
