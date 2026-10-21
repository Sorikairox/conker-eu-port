#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A1940;
extern f32 D_800A1944;
u8 func_151464B8(s32);
void func_151432BC(s32, f32 *, f32 *, f32 *, f32 *);

void func_150ECAA0(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } tmp;
    f32 sp68;
    f32 *v;

    if (func_151464B8(*(s32 *)(arg0 + 0x30)) != 0) {
        return;
    }
    v = (f32 *)(arg0 + 0x28);
    v[3] += (D_800A1940 + func_150ADA68() * D_800A1944) * v[1] * D_800BE9A4;
    if (v[3] > 1.0f) {
        tmp.w = 0.0f;
        do {
            func_151432BC(*(s32 *)v, &tmp.x, &tmp.z, &sp68, &tmp.y);
            temp_v0 = func_15149130((func_150ADA20() % 131U) + 80, -1, 0x5A, -1, 1, 0, 0x10, arg0[0xC], arg0[1]);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
            }
            v[3] -= 1.0f;
        } while (v[3] > 1.0f);
    }
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

void func_150ECC30(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f10;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((1352.0f + (func_150ADA68() * 1698.0f)) * 0.0001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x46;
        sp.uBC = 3;
        sp.uF4 = 0x80DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uFE = 0x16;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x46;
        sp.uB0 = 0x47;
        sp.uB1 = 0xC2;
        sp.uB2 = 0;
        sp.uB3 = 0xFF;
        sp.uB4 = 0xC0;
        sp.uB5 = 0x49;
        sp.uB6 = 0;
        sp.uB8 = 0xFF;
        sp.u98 = 0.97047f;
        sp.uC0 = 1.021029f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u8E = (func_150ADA20() % 5U) + 4;
            sp.u8F = (func_150ADA20() % 5U) + 4;
            sp.u90 = func_150ADA68() * 11.0f;
            sp.u94 = func_150ADA68() * 11.0f;
            temp_f10 = func_150ADA68() * 0.172f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = temp_f10 + 0.098000005f;
            var_s0 = 0;
            if (func_150ADA20() & 1) {
                var_s0 = 0x80;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (func_150ADA20() % 101U) + 0x64;
            sp.uA6 = (func_150ADA20() % 51U) + 0x50;
            temp_f6 = (func_150ADA68() * 80.0f) + 92.0f;
            sp.uC8 = temp_f6;
            sp.uC4 = temp_f6;
            temp_v0 = func_151307F0(&sp.u9C, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ECC30.s")
#endif
void func_150ECFE8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, u8 arg7, s32 arg8) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        u8 unk6;
        u8 unk7;
        u8 unk8;
        u8 unk9;
        u8 padA[2];
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = arg1;
    tmp.unk6 = arg2;
    tmp.unk7 = arg3;
    tmp.unk8 = arg4;
    tmp.unk9 = arg5;
    temp_v0 = func_15149130((arg6 == -1) ? 300 : arg6, -1, 0x5D, -1, (arg6 == -1) ? 0 : 1, 0x45, 0xC, arg7, arg8);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

void func_150ED0CC(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);

void func_150ED10C(u8 *arg0) {
    u8 *sp28;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_t6 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_v0 = arg0 + 0x28;
    sp28 = temp_t6;
    if (((*(s32 *)temp_t6) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_t6 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    func_1502ED88(sp28, (*(u8 *)((u8 *)temp_v0 + 5)), (*(u8 *)((u8 *)temp_v0 + 6)), (*(u8 *)((u8 *)temp_v0 + 7)), (s32) (*(u8 *)((u8 *)temp_v0 + 8)), 0, (s32) (*(u8 *)((u8 *)temp_v0 + 9)));
}

void func_150ECFE8(u8 *, u8, u8, u8, u8, u8, s16, u8, s32);
s32 func_151CA070(struct127 *, u8, s32);

void func_150ED180(s32 arg0, u8 arg1, s32 arg2) {
    func_151CA070(arg0, arg1, arg2);
    func_150ECFE8((u8 *)arg0, 0, 0xFF, 0, 0xFF, 4, -1, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ED1F0.s")
