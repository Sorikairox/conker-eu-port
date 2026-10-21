#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150BE390(s32 arg0, u8 arg1, s32 arg2) {
    struct {
        s32 unk0;
        s16 unk4;
    } sp38;
    struct260 *temp_v0;

    sp38.unk4 = 0;
    sp38.unk0 = arg0;
    temp_v0 = func_15149130(0x12C, -1, 0x4F, -1, 0, 0x3C, 8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp38, 8);
    }
}

#ifdef NON_MATCHING
s32 func_151559FC(f32 *, s32, s32, s32, s32, s32, s32);

void func_150BE40C(u8 *arg0) {
    struct {
        u8 * u38;
        u8 pad3C[0x8];
        s8 u44;
        s8 u45;
        u8 pad46[0x2];
        f32 u48;
        u8 pad4C[0x48];
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        s8 uA4;
        u8 padA5[0x1];
        s16 uA6;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        u8 padD6[0x2];
        u8 uD8;
        u8 padD9[0x3];
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
    } sp;
    u8 **sp34;
    f32 temp_f6;
    s32 temp_v0;
    u8 **temp_v1;

    (*(s16 *)((u8 *)arg0 + 0x2C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x2C)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x2C)) < 0) {
        temp_f6 = func_150ADA68() * 270.0f;
        sp.u98 = -120.0f;
        sp.u94 = temp_f6 + -135.0f;
        sp.u9C = (func_150ADA68() * 10.0f) + 3.0f;
        sp.uA0 = (func_150ADA68() * 17.0f) + 9.0f;
        sp.uA4 = 0xAB;
        sp.uA6 = 0x3E8;
        sp.uA8 = 0x31;
        sp.uAA = 1;
        sp.uAC = 0xFF;
        sp.uAE = 7;
        sp.uAF = 0xFF;
        sp.uB0 = 0xFF;
        sp.uB1 = 0xFF;
        sp.uB2 = (func_150ADA20() % 156U) + 0x64;
        sp.uB3 = 0xFF;
        sp.uB4 = 0xFF;
        sp.uB5 = 0xFF;
        sp.uB6 = 0xFF;
        sp.uB7 = 0xFF;
        sp.uB8 = 0;
        sp.uBC = 0x200004;
        sp.uC0 = 0x1F0601;
        sp.uC4 = 3;
        sp.uC8 = 0x22;
        sp.uCC = 0x80;
        sp.uD0 = 0x20;
        sp.uD4 = 0;
        sp.uD5 = 7;
        temp_v1 = arg0 + 0x28;
        sp.uDC = 1.0f;
        sp.uE0 = 1.0f;
        sp.uD8 = (*(u8 *)((u8 *)(*temp_v1) + 0x23D));
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.u45 = 0;
        sp.u44 = 0;
        sp34 = temp_v1;
        sp.u38 = *temp_v1;
        sp.u48 = (func_150ADA68() * 4.064f) + 2.513f;
        temp_v0 = func_151559FC(&sp.u94, 0xA, 0, 0, 0x58, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), 0);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x70, &sp.u38, 0x58);
        }
        (*(s16 *)((u8 *)sp34 + 4)) = (s16) ((func_150ADA20() % 151U) + 0x19);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBBA0/func_150BE40C.s")
#endif
void func_150BE650(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x28) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x28) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

s32 func_150BE6C4(f32 *arg0) {
    arg0[5] += arg0[0x20] * D_800BE9A4;
    if (arg0[5] > 120.0f) {
        return 0;
    }
    return 1;
}
