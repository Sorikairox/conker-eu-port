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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ECC30.s")

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
