#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 memcpy(u8 *, s32, s32);

u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE) {
    u8 *sp3C;
    u8 *sp38;
    u8 *temp_a0;
    u8 *temp_v0;

    (*(s32 *)((u8 *)arg0 + 0x10)) = 1;
    temp_v0 = func_15147FF0(arg0, arg2 + 0x48, 0x14, 1, 0, 1, arg9, argA, argC, (u8) (s32) argD, argE);
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_v0 + 0x98));
    sp3C = temp_v0;
    sp38 = temp_a0;
    memcpy(temp_a0, arg1, 0x20);
    (*(s8 *)((u8 *)temp_a0 + 0x20)) = (s8) arg3;
    (*(s8 *)((u8 *)temp_a0 + 0x21)) = (s8) arg4;
    (*(s8 *)((u8 *)temp_a0 + 0x22)) = (s8) arg5;
    (*(s8 *)((u8 *)temp_a0 + 0x23)) = (s8) arg6;
    (*(s8 *)((u8 *)temp_a0 + 0x24)) = (s8) arg7;
    (*(s8 *)((u8 *)temp_a0 + 0x25)) = (s8) arg8;
    (*(s32 *)((u8 *)temp_a0 + 0x28)) = (s32) (*(s32 *)((u8 *)argB + 0));
    (*(s32 *)((u8 *)temp_a0 + 0x2C)) = (s32) (*(s32 *)((u8 *)argB + 4));
    (*(s32 *)((u8 *)temp_a0 + 0x30)) = (s32) (*(s32 *)((u8 *)argB + 8));
    (*(s32 *)((u8 *)temp_a0 + 0x34)) = (s32) (*(s32 *)((u8 *)argB + 0xC));
    (*(s32 *)((u8 *)temp_a0 + 0x38)) = (s32) (*(s32 *)((u8 *)argB + 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0x3C)) = (s32) (*(s32 *)((u8 *)argB + 0x14));
    (*(s32 *)((u8 *)temp_a0 + 0x40)) = (s32) (*(s32 *)((u8 *)argB + 0x18));
    (*(s32 *)((u8 *)temp_a0 + 0x44)) = (s32) (*(s32 *)((u8 *)argB + 0x1C));
    return sp3C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148310.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148428.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_151485AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15148E34.s")

typedef struct { f32 x; f32 y; f32 z; f32 vy; s16 a; s16 pad12; } Part9064;
s32 func_15149064(u8 *arg0) {
    Part9064 *base;
    f32 *v;
    s32 i;
    Part9064 *p;

    base = *(Part9064 **)(arg0 + 0x94);
    v = *(f32 **)(arg0 + 0x98);
    i = *(s8 *)(arg0 + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = *(u8 *)(arg0 + 0x25) - 1;
        }
            base[i].vy -= v[4] * D_800BE9A4;
        base[i].x += v[1] * D_800BE9A4;
        base[i].y += base[i].vy * D_800BE9A4;
        base[i].z += v[3] * D_800BE9A4;
    } while (i != *(s8 *)(arg0 + 0x2D));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15149114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_15149350.s")

s32 func_15149468(u8 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp = arg0[0x98 / 4];
    temp[0x20] = 4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_175B20/func_1514948C.s")

s32 func_15149638(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) * 8;
    if (temp_v1 >= 256) {
        temp_v1 = 255;
    }
    temp_v0[0x1B] = temp_v1;
    if ((u8)temp_v1 < 0) {
        return 0;
    }
    return 1;
}

void func_15149674(s32 arg0) {
    func_15147E64(arg0);
}
