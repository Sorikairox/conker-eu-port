#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15044660(void) {
    D_800CC1BC = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504481C.s")

void func_15044948(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044950.s")

u8 *func_15044C54(s32, s32, s32, s32, s32, s32, s32, s32);

u8 *func_15044BC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    u8 *temp_v0;

    temp_v0 = func_15044C54(0x20, 1, arg0, arg1, arg2, 0, 0, 0);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s16 *)((u8 *)temp_v0 + 0x10)) = (s16) arg3;
    (*(s16 *)((u8 *)temp_v0 + 0x12)) = (s16) arg4;
    (*(s16 *)((u8 *)temp_v0 + 0x14)) = (s16) arg5;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = (s8) arg6;
    (*(s32 *)((u8 *)temp_v0 + 0x18)) = arg7;
    (*(s32 *)((u8 *)temp_v0 + 0x1C)) = arg8;
    return temp_v0;
}

u8 *func_15044C54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 var_a0;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = allocate_memory(arg0, 1, 0, 0);
    if (temp_v0 == NULL) {
        return NULL;
    }
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 4)) = (s16) arg2;
    (*(s8 *)((u8 *)temp_v0 + 0xC)) = (s8) arg1;
    (*(s8 *)((u8 *)temp_v0 + 0xD)) = (s8) arg4;
    (*(s8 *)((u8 *)temp_v0 + 0xE)) = (s8) arg3;
    (*(s16 *)((u8 *)temp_v0 + 6)) = (s16) arg5;
    (*(s16 *)((u8 *)temp_v0 + 8)) = (s16) arg6;
    (*(s16 *)((u8 *)temp_v0 + 0xA)) = (s16) arg7;
    if (D_800CBE00 == 0) {
        D_800CBE00 = (s32) temp_v0;
    } else {
        var_v1 = *(s32 *)D_800CBE00;
        var_a0 = D_800CBE00;
        if (var_v1 != 0) {
            do {
                var_a0 = var_v1;
                var_v1 = *(s32 *)var_v1;
            } while (var_v1 != 0);
        }
        *(s32 *)var_a0 = (s32)temp_v0;
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044D18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044E68.s")

void func_15044FD4(u8 *arg0) {
    s16 *temp_v0 = *(s16 **)(arg0 + 0x18);
    s16 temp_t0;

    *(s16 *)(arg0 + 6) = temp_v0[0];
    *(s16 *)(arg0 + 8) = temp_v0[1];
    *(s16 *)(arg0 + 0xA) = temp_v0[2];
    temp_t0 = **(s16 **)(arg0 + 0x1C) / 32;
    *(s16 *)(arg0 + 0x10) = temp_t0;
    *(s16 *)(arg0 + 0x12) = temp_t0;
    *(s16 *)(arg0 + 0x14) = temp_t0;
    func_15044E68(arg0);
}

s32 func_150472F4(u8 *, f32, u8 *);
s32 func_150A44A4(f32, f32, s32, u8 *, f32 *);
s32 func_150473A0(u8 *, f32, u8 *);
s32 func_150451C0(u8 *, f32, u8 *);
s32 func_15046C6C(u8 *, u16, f32, u8 *);
s32 func_15046FF0(u8 *, u16, f32, u8 *);
s32 func_150469E8(u8 *, u16, f32, u8 *);

s32 func_15045030(u8 *arg0) {
    func_1505D1C4((f32)*(s16 *)(arg0 + 6), (f32)*(s16 *)(arg0 + 8), (f32)*(s16 *)(arg0 + 0xA), *(s16 *)(arg0 + 0x10), 0xFF, 0, 0, 0);
    return 0;
}

void func_15045090(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 5, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_150450D8(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            if (D_800C35EA != 1) {
                func_1505D024(D_800CC2D0, 4, D_800CC2D0->unk7A, -1);
            }
        }
    }
}

void func_15045130(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 0x40, D_800CC2D0->unk7A, -1);
        }
    }
}

void func_15045178(void) {
    if (D_800CC2D0->stunned == 0) {
        if (D_800CC2D0->immune == 0) {
            func_1505D024(D_800CC2D0, 1, D_800CC2D0->unk7A, -1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150451C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150453BC.s")

s32 func_150455FC(u8 *arg0, f32 arg1, u8 *arg2) {
    switch (func_150473A0(arg0, arg1, arg2)) {
        case 0:
            return func_150451C0(arg0, arg1, arg2);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504583C.s")

s32 func_150A69E0(s16, s16, s32, u16);
void func_1510F800(s32);

void func_15045A04(u8 *arg0, u16 arg1, s32 *arg2, s32 arg3) {
    func_1510F800(2);
    *arg2 = func_150A69E0((s16) (s32) (*(f32 *)((u8 *)arg0 + 0)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 8)), arg3, arg1);
}

s32 func_1504627C(u8 *, f32, s32 *, u8 *);
s32 func_15045A70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    s32 sp1C;
    s32 sp18;
    if (*(f32 *)(arg0 + 4) < arg2) {
        arg3[0x1C] &= 0xFFFD;
        return 0;
    }
    func_15045A04(arg0, arg1, &sp1C, &sp18);
    return func_1504627C(arg0, arg2, &sp18, arg3);
}

s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15045A70(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15045DD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504627C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150464C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150469E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046C6C.s")

s32 func_15046EF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150473A0(arg0, arg2, arg3)) {
        case 0:
            return func_150469E8(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}

s32 func_15046F70(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15046C6C(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15046FF0.s")

s32 func_15047274(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3) {
    switch (func_150472F4(arg0, arg2, arg3)) {
        case 0:
            return func_15046FF0(arg0, arg1, arg2, arg3);
        case 1:
            return 0;
        case 2:
            return 1;
    }
}


s32 func_150472F4(u8 *arg0, f32 arg1, u8 *arg2) {
    f32 sp24;

    if ((arg2[0x1C] & 4) && (func_150A44A4(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), 0, arg2 + 4, &sp24) != 0)) {
        if ((arg1 <= sp24) && (sp24 <= *(f32 *)(arg0 + 4))) {
            *(f32 *)arg2 = sp24;
            arg2[0x1C] = arg2[0x1C] | 2;
            return 2;
        }
        return 1;
    }
    return 0;
}

s32 func_150A44A4(f32, f32, s32, u8 *, f32 *);

s32 func_150473A0(u8 *arg0, f32 arg1, u8 *arg2) {
    f32 sp24;

    if ((arg2[0x1C] & 4) && (func_150A44A4(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), 0, arg2 + 4, &sp24) != 0)) {
        if ((sp24 <= arg1) && (*(f32 *)(arg0 + 4) <= sp24)) {
            *(f32 *)arg2 = sp24;
            arg2[0x1C] = arg2[0x1C] | 2;
            return 2;
        }
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_1504715C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150475B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15047680.s")

s32 func_15047680(f32 *, f32, f32, s32, f32, f32, f32, f32, f32, f32);

// fakematch: volatile arg3 makes IDO store and reload a3 like the original
void func_15047978(Mtx *arg0, f32 arg1, f32 arg2, volatile s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    f32 sp30[16];
    func_15047680(sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    guMtxF2L((f32 (*)[4]) sp30, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_150479F0.s")

s32 func_150479F0(f32 (*)[4], s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_15047E70(Mtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA) {
    f32 sp38[4][4];
    func_150479F0(sp38, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    guMtxF2L(sp38, arg0);
}
