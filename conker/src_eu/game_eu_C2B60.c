#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_15095F18(s32, f32, f32, f32, s32, s32 *);
#endif

Gfx *func_15095350(Gfx *arg0) {
    gSPDisplayList(arg0++, D_80087770);
    D_800D30C0 = 0;
    return arg0;
}

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

void func_15095380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, 0x100, 0x100, arg8);
}

void func_15095470(s32, s32, s32);
s32 func_150954E4(s32, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30B0;

void func_150953F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    func_15095470(arg1, arg2, arg3);
    func_150954E4(arg0, &D_800D30B0, arg4, arg5, 0, arg6, arg7, arg8, arg9, argA);
}

void func_15095470(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_v0;
    if (arg2 != 0) {
        (*(s32 **)((u8 *)arg2 + 0x10)) = &D_800D30B0;
    }
    temp_v0 = (*(u32 *)((u8 *)arg0 + 0));
    if (temp_v0 < 0x10000000U) {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = (s32) temp_v0;
    } else {
        (*(s32 *)((u8 *)(&D_800D30B0) + 0)) = *(s32 *)((u8 *)((s32)temp_v0 + ((arg1 >> 8) * 4)));
    }
    (*(u16 *)((u8 *)(&D_800D30B0) + 4)) = (u16) (*(u16 *)((u8 *)arg0 + 6));
    (*(u16 *)((u8 *)(&D_800D30B0) + 6)) = (u16) (*(u16 *)((u8 *)arg0 + 8));
    (*(u8 *)((u8 *)(&D_800D30B0) + 8)) = (u8) (*(u8 *)((u8 *)arg0 + 0xA));
    (*(u8 *)((u8 *)(&D_800D30B0) + 9)) = (u8) (*(u8 *)((u8 *)arg0 + 0xB));
    (*(u8 *)((u8 *)(&D_800D30B0) + 0xA)) = (u8) (*(u8 *)((u8 *)arg0 + 4));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150954E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095A4C.s")

#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095B70(u8 *arg0, u8 *arg1) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_a0;
    u8 *temp_t0;

    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        return arg0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEE000000;
    temp_t0 = D_800BE628 + (D_80082FA4 * 0x180) + (D_800BE9C0 * 0x10);
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((s32) (((f32) (*(s16 *)((u8 *)temp_t0 + 0x4C)) + ((sp.u3C / sp.u38) * (f32) (*(s16 *)((u8 *)temp_t0 + 0x44)))) * 32.0f) << 0x10);
    return func_15095EA0((s32) (temp_a0 + 8), (s32) arg1, sp.u44, sp.u40, sp.u38, 1, 0, 0, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095B70.s")
#endif
#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);

u8 *func_15095CC0(u8 *arg0, u8 *arg1, s32 *arg2) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
    } sp;
    u8 *temp_s0;
    u8 *var_s0;

    var_s0 = arg0;
    if (func_15095A4C((f32) (*(s16 *)((u8 *)arg1 + 0)), (f32) (*(s16 *)((u8 *)arg1 + 2)), (f32) (*(s16 *)((u8 *)arg1 + 4)), &sp.u44, &sp.u40, &sp.u3C, &sp.u38, 4000.0f) == 0) {
        *arg2 = 0;
        return var_s0;
    }
    func_15095F18((s32) arg1, sp.u44, sp.u40, sp.u38, 1, arg2);
    if (*arg2 != 0) {
        temp_s0 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_s0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xEE000000;
        var_s0 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((u32) (((sp.u3C / sp.u38) * 16352.0f) + 16352.0f) << 0x10);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095CC0.s")
#endif
void func_15095E58(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    func_15095EA0(arg0, arg1, arg2, arg3, 4096.0f, 0, 0, 0, 0);
}

s32 func_15095F18(s32, f32, f32, f32, s32, s32 *);
s32 func_15096144(s32, s32, s32, s32, s32);
s32 func_15095EA0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 sp24;
    func_15095F18(arg1, arg2, arg3, arg4, arg5, &sp24);
    if (sp24 != 0) {
        arg0 = func_15096144(arg0, arg1, arg6, arg7, arg8);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15095F18.s")

void func_1509611C(s32 arg0, s32 arg1) {
    func_15096144(arg0, arg1, 0, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_15096144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C2B60/func_150966AC.s")

Gfx *func_15096D44(Gfx *arg0) {
    gSPDisplayList(arg0++, D_800877A8);
    D_800D31CB = 0;
    return arg0;
}
