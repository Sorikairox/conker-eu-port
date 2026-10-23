#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct { f32 x, y, z; } V3;

s32 func_151B65C0(V3 *arg0, V3 *arg1, f32 arg2, V3 *arg3, V3 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD) {
    s32 obj;
    s32 n;
    struct {
        f32 u28[6];
        V3 u40;
        f32 u4C;
        f32 u50;
        f32 u54;
        V3 u58;
        V3 u64;
        V3 u70;
        f32 u7C;
        s32 u80;
        s16 u84;
        s16 u86;
        s8 u88;
        s32 u8C;
        u8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        u8 pad99;
        s8 u9A;
        s32 u9C;
        s8 uA0;
        s16 uA2;
        s16 uA4;
    } sp;

    sp.u28[1] = arg2;
    sp.u28[0] = 0.0f;
    sp.u28[5] = arg2;
    sp.u28[4] = arg2;
    sp.u28[2] = 8.1f * arg2;
    sp.u28[3] = arg9;
    sp.u40 = *arg3;
    sp.u4C = 1.0f;
    sp.u50 = 1.0f;
    sp.u54 = 1.0f;
    sp.u58 = *arg0;
    sp.u80 = 0x3900;
    sp.u7C = arg5;
    if (arg6 == -1) {
        sp.u84 = 0x12C;
        n = 0x100 >> argA;
    } else {
        n = 0x100 >> argA;
        sp.u84 = arg6 + n;
        sp.u80 = 0x3980;
    }
    if (arg1 != NULL) {
        sp.u64 = *arg1;
        sp.u80 |= 0x20;
    } else {
        sp.u64.x = 0.0f;
        sp.u64.y = 0.0f;
        sp.u64.z = 0.0f;
    }
    if (arg4 != NULL) {
        sp.u70 = *arg4;
        sp.u80 |= 0x40;
    } else {
        sp.u70.x = 0.0f;
        sp.u70.y = 0.0f;
        sp.u70.z = 0.0f;
    }
    if (argB != 0) {
        sp.u80 |= 1;
    }
    sp.u86 = 3;
    sp.u88 = 0;
    sp.u8C = 0;
    sp.u90 = arg7;
    sp.u91 = 6;
    sp.u92 = 0;
    sp.u93 = 6;
    sp.u94 = 0;
    sp.u95 = 0;
    sp.u96 = 0;
    sp.u97 = 0;
    sp.u98 = 2;
    sp.u9A = 0;
    sp.u9C = 0;
    sp.uA0 = 0;
    sp.uA2 = n;
    sp.uA4 = 0xFF / n;
    obj = func_15132FBC((u8 *)&sp.u28[2], 3, 0xFF, 8, argC, argD);
    if (obj != 0) {
        memcpy(obj + 0x170, &sp, 8);
    }
    return obj;
}

#ifdef NON_MATCHING
s32 func_15133E04(u8 *); /* P98: the asm reads a0 = the object */

void func_151B6804(u8 *arg0) {
    u8 *sp18;
    f32 *temp_v0;
    f32 temp_f12;
    f32 temp_f2;
    u8 *temp_v0_2;

    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) + (0.55600005f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x170)) > 6.2831855f) {
        do {
            *temp_v0 -= 6.2831855f;
        } while (*temp_v0 > 6.2831855f);
    }
    temp_v0_2 = arg0 + 0x170;
    sp18 = temp_v0_2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0_2 + 4));
    temp_f2 = temp_f12 + (sinf((*(f32 *)((u8 *)temp_v0_2 + 0))) * (0.061000004f * temp_f12));
    (*(f32 *)((u8 *)arg0 + 0x1C)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f2;
    func_15133E04(arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E3DD0/func_151B6804.s")
#endif