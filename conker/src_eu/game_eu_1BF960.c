#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_15192150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151922C4.s")

u8 *func_151308E4(void *, s32, s32, u8, s32);
extern u8 (*D_80090070[])(void);
extern f32 D_800A84D4;
extern f32 D_800A84D8;
typedef struct { f32 x, y, z; } V3_25AC;
typedef struct { s16 h[9]; } H12_25AC;
typedef struct {
    s32 u0;
    s32 u4;
    s16 u8;
    s16 uA;
    s32 uC;
    s32 u10;
    u8 u14[4];
    u8 u18;
    u8 u19;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    s16 u1E;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    f32 u2C;
    V3_25AC u30;
    f32 u3C;
    f32 u40;
    f32 u44;
    V3_25AC u48;
    f32 u54;
    s32 u58;
    s32 u5C;
    u8 u60;
    u8 u61;
    u8 u62;
    s8 u63;
    s8 u64;
    u8 u65;
} Blk_25AC;
typedef struct {
    f32 u0;
    u8 u4;
    u8 u5;
    u8 u6;
    u8 u7;
    f32 u8;
    f32 uC;
    f32 u10;
    H12_25AC u14;
    u8 u26;
} Tmp_25AC;

u8 *func_151925AC(V3_25AC *arg0, V3_25AC *arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6, s32 arg7, f32 arg8, H12_25AC *arg9, u8 argA, u8 argB, s32 argC) {
    u8 *ret;
    s32 pad[2]; // fakematch: hole above the block
    Blk_25AC blk;
    Tmp_25AC tmp;
    s32 pad2; // fakematch: spill slot below tmp
    s32 a;

    blk.u8 = 0x4401;
    blk.u0 = 0x200005;
    blk.u4 = 0;
    blk.uC = 0;
    blk.u10 = 0;
    blk.u14[0] = 0;
    blk.u14[1] = 0;
    blk.u14[2] = 0;
    blk.u14[3] = 0xFF;
    blk.u18 = 0;
    blk.u19 = 0;
    blk.u1A = 0;
    blk.u1B = arg4;
    blk.u1C = arg5;
    blk.u30 = *arg0;
    blk.u3C = 0.0f;
    blk.u40 = 0.0f;
    blk.u44 = 0.0f;
    blk.u48 = *arg1;
    blk.u54 = arg2;
    blk.u22 = 1;
    blk.u24 = 1.0f;
    if (func_150ADA20() & 1) {
        a = 0x40;
    } else {
        a = 0;
    }
    blk.u58 = ((func_150ADA20() & 1) ? 0x80 : 0) | 0xC207 | a | 0x10000;
    blk.uA = arg3 + 0x12;
    blk.u1E = 0x12;
    blk.u20 = 0xE;
    blk.u60 = 6;
    blk.u61 = 8;
    blk.u62 = 0xF;
    blk.u63 = -1;
    blk.u64 = -1;
    blk.u65 = 3;
    tmp.u4 = (s16)func_150ADA20(); // fakematch: s16 cast of the rand result (permuter)
    tmp.u5 = func_150ADA20();
    blk.u1D = D_80090070[argA]();
    blk.u2C = arg6;
    blk.u28 = arg6;
    tmp.u0 = arg6;
    tmp.u6 = (func_150ADA20() % 6U) + 5;
    tmp.u7 = (func_150ADA20() % 6U) + 5;
    tmp.u8 = ((func_150ADA68() * 0.25f) + D_800A84D4) * tmp.u0;
    tmp.uC = ((func_150ADA68() * 0.25f) + D_800A84D8) * tmp.u0;
    tmp.u10 = arg8;
    tmp.u14 = *arg9;
    tmp.u26 = argA;
    ret = func_151308E4(&blk, 1, 0x28, argB, argC);
    if (ret != NULL) {
        memcpy(ret + 0xA8, &tmp, 0x28);
    }
    return ret;
}

#ifdef NON_MATCHING
s32 func_151321F4(u8 *, u8 *, f32, u8 *, u8 *, u8 *); /* P95: f32 (float bits were passed as an int) */
#else
s32 func_151321F4(u8 *, u8 *, s32, u8 *, u8 *, u8 *);
#endif

s32 func_15192878(u8 *arg0, s32 arg1) {
#ifdef NON_MATCHING
    func_151321F4(arg0 + 0xAC, arg0 + 0xAE, (*(f32 *)((u8 *)arg0 + 0xA8)), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C); /* P95: f32 (float bits were passed as an int) */
#else
    func_151321F4(arg0 + 0xAC, arg0 + 0xAE, (*(s32 *)((u8 *)arg0 + 0xA8)), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C);
#endif
    return 1;
}

#ifdef NON_MATCHING
extern f32 D_800A84DC;
extern f32 D_800A84E0;
extern f32 D_800A84E4;
extern f32 D_800A84E8;
extern f32 D_800A84EC;
extern f32 D_800A84F0;
extern f32 D_800A84F4;
extern f32 D_800A84F8;
void func_151436B4(f32, f32, f32, struct17 *);
u8 *func_151DA6F8(u8 *, u8 *, f32, s16, u8, f32, s32, u8, f32, f32, u8, u8, s32, s16, s16, s32, u8, s32);

// water_drop_splash_update: update handler 14 of the particle tick func_1513095C for drops spawned by func_151925AC.
// The extra block at +0xA8 (scale f32, ..., water level f32 at +0x10, splash ring H12 at +0x14, type at +0x26) stays
// unused while the drop is above the water. On the first tick its y (+0x44) is below the water level it spawns a
// splash ring (func_151D9B8C) at (x, level + 2, z) and one spray droplet (func_151DA6F8) with a random direction,
// and returns 0 (the drop dies); otherwise returns 1 (keep alive).
s32 func_151928C8(u8 *arg0, s32 arg1) {
    u8 *ext = arg0 + 0xA8;
    struct17 pos;
    struct17 vel;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;
    u32 sprite;
    u32 tint;
    u8 alive = 1;

    if (*(f32 *)(arg0 + 0x44) < *(f32 *)(ext + 0x10)) {
        alive = 0;
        pos.unk0 = *(f32 *)(arg0 + 0x40);
        pos.unk4 = *(f32 *)(ext + 0x10) + 2.0f;
        pos.unk8 = *(f32 *)(arg0 + 0x48);
        func_151D9B8C(ext[0x26], *(f32 *)ext * D_800A84DC, arg0[0x2B], (s32)(ext + 0x14), &pos, 0x64, 0, 1, 0,
                      arg0[0xC], arg0[0x1]);
        r0 = func_150ADA68();
        r1 = func_150ADA68();
        r2 = func_150ADA68();
        func_151436B4(r0 * D_800A84E4, (r1 * 1000.0f + D_800A84E8) * D_800A84E0, (r2 * D_800A84EC + D_800A84F0) * D_800A84E0,
                      &vel);
        r3 = func_150ADA68();
        sprite = func_150ADA20();
        tint = func_150ADA20();
        func_151DA6F8((u8 *)&pos, (u8 *)&vel, r3 * D_800A84F4 + D_800A84F4, (s16)(sprite % 21 + 0x23), arg0[0x2B],
                      *(f32 *)ext * D_800A84F8, tint % 7 + 5, 0, 1.0f, 1.0f, 1, ext[0x26], 0, 0x10, 0xF, 0, arg0[0xC],
                      arg0[0x1]);
    }
    return alive;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151928C8.s")
#endif

s32 func_151928C8(u8 *, s32);

s32 func_15192AEC(u8 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_15192878(arg0, arg1);
    var_v1 = temp_v0 & 0xFF;
    if (temp_v0 != 0) {
        var_v1 = func_151928C8(arg0, arg1) & 0xFF;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BF960/func_151925C4.s")

void func_15192CEC(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
