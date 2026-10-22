#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A1D20[];
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F2FE0.s")

void func_150F320C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        f32 unk8;
        u8 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0;
    temp_v0 = func_15149130(300, -1, 0x5C, -1, 0, 0x44, 0x10, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3294.s")

void func_150F3714(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150F3754(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
s32 func_150F3794(u8 *arg0) {
    u8 *sp18;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    temp_v0 = arg0 + 0x110;
    if (((*(s32 *)((u8 *)temp_v1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_v1 + 0x3B))) || (temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x1D4)), (temp_t0 == 0))) {
        return 0;
    }
    sp18 = temp_v0;
    func_15143134(((u8 *)&D_800A1D20), arg0 + 0x34, temp_t0 + 0x3C0);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + D_800BE9A4);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3794.s")
#endif
s32 func_15140410();

void func_150F38FC(u8 *arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F_7 : 7;
    u8 unk4F_0 : 1;
} struct_eu_150F3930;

void func_150F3930(struct_eu_150F3930 *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        arg0->unk4F_0 = 0;
        return;
    }
    arg0->unk4F_0 = 1;
}

extern f32 D_800A1D40;

void func_150F3978(s32 arg0) {
    u8 *e = (u8 *)D_800DBFF0 + arg0 * 0x9A0;

    if (*(f32 *)(e + 0x300) < D_800A1D40) {
        if (*(f32 *)(e + 0x2FC) > 840.0f) {
            **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 | (1 << arg0); // fakematch: D_800D9A40 is declared s32 but holds a pointer; inline casts, no local
            return;
        }
        **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 & ~(1 << arg0);
    }
}

extern f32 D_800A1D50;
extern f32 D_800A1D54;

f32 func_150F3A20(s32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 < -5.0f) {
        var_f2 = (arg1 * D_800A1D50) + D_800A1D54;
    } else {
        var_f2 = 0.75f;
    }
    return var_f2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3A74.s")

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);

void func_150F4970(struct108 *arg0) {
    s32 temp_t0;

    if (arg0->unk23E == 0x3B) {
        func_1509BFB0(0, 0x405C, 1);
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
                temp_t0 = arg0->unk84 | 0x300000;
                arg0->unk84 = temp_t0;
                arg0->unk84 = temp_t0 & ~4;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                func_15124B18(arg0);
            }
            arg0->unk134 = 0;
            arg0->unk348 = 125.0f;
            arg0->unk34C = 125.0f;
            arg0->unk374 = 220.0f;
            arg0->unk190 = 30.0f;
        } else {
            arg0->unk190 = 0.0f;
        }
    } else if ((arg0->unk2C == 8) && (arg0->unk6C8 == 0)) {
        func_151239CC(arg0, 0);
        func_1509BFB0(0, 0x405C, 0);
    }
    if ((func_1509BE40(1, 0x4054, 6, 0x9000) != 0) && (func_1509BE40(1, 0x405E, 6, 0x9000) == 0)) {
        arg0->unk84 |= 0x80000000;
        return;
    }
    arg0->unk84 &= 0x7FFFFFFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F4970.s")
#endif