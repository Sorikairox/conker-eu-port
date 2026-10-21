#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150BF470(s32 arg0) {
}

#ifdef NON_MATCHING
void func_1516DF0C(s16, s16, s16, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, s16, s16, s16, s16, u16, u8, u8, u8, u8, s16, u16, u16, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32);

void func_150BF47C(s32 arg0) {
    s16 var_s0;
    s32 var_s1;

    var_s0 = 0x17C;
    var_s1 = 0;
    do {
        func_1516DF0C(0x1FDB, 0x25, var_s0, 0xD, 0, 0x50, 0x8F, 0, 0, 0, 0, 0, 8, 0xC8, 0xA, 0, 0, 0, 0, 0, 0x28, 0x28, 4, 0, 0, 0, 0, 0x555, 0x555, 0x555, 0x555, arg0 & 0xFFFF, 0x32, 0, 0xFF, 0x14, 0xFA0, 0x7D0, 1, 6, 0, 1, 0, 0, 0, 0, 3, 0xFF, 0);
        var_s1 += 1;
        var_s0 = -var_s0;
    } while (var_s1 != 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF47C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF5F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF71C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BFC60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BFF7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C04E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C06DC.s")

#ifdef NON_MATCHING
s32 func_15150970(s32 *, s16 *, u8, s32);
extern s32 D_800A04D8;

void func_150C04C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    struct {
        f32 u20;
        s32 u24;
        s32 u28;
        s16 u2C;
        s16 u2E;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 pad40[0x8];
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
        s32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        s32 * u7C;
        s32 * u80;
        s32 u84;
        f32 u88;
        s8 u8C;
        s8 u8D;
        u8 pad8E[0x2];
        s32 u90;
        f32 * u94;
    } sp;
    s8 var_v0;

    sp.u24 = D_800A04D8;
    sp.u28 = arg2;
    sp.u34 = 9;
    sp.u38 = 4;
    sp.u20 = 0.65000004f;
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u48 = 4.0f;
    sp.u4C = 7.0f;
    sp.u50 = -1.2800001f;
    sp.u54 = 0.33600003f;
    sp.u5C = 0.6f;
    sp.u60 = 0.45000002f;
    sp.u58 = 0x50;
    sp.u5A = 0x3C;
    sp.u68 = arg1;
    sp.u7C = &sp.u28;
    sp.u80 = &sp.u24;
    sp.u84 = 1;
    sp.u64 = 17.077002f;
    sp.u6C = 0.75200003f;
    sp.u70 = 0.20400001f;
    sp.u74 = 0.164f;
    sp.u78 = 10.0f;
    sp.u88 = 78.0f;
    if (arg3 & 0xFF) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    sp.u8C = var_v0;
    sp.u8D = 0xE;
    sp.u90 = 4;
    sp.u94 = &sp.u20;
    sp.u2C = 0;
    sp.u2E = 0xFF;
    sp.u30 = -0x32;
    sp.u32 = 0x23;
    func_15150970(&sp.u34, &sp.u2C, arg4, arg5);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C04C0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C0B48.s")
