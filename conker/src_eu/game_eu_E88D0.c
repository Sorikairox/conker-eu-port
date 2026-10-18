#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8  pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u8  pad1E[0xA];
    /* 0x28 */ u8  unk28;
    /* 0x29 */ u8  pad29[0x81 - 0x29];
    /* 0x81 */ u8  unk81;
    /* 0x82 */ u8  pad82[0xB0 - 0x82];
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
} struct_eu_E88D0;

void func_1513F6C0();


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BABE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BB4CC.s")

s32 func_150BB740(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_150BB8E8(struct_eu_E88D0 *arg0) {
    arg0->unk18 |= 1;
    arg0->unk1C = 50;
    arg0->unkB0 = arg0->unk1C;
    arg0->unkB2 = 5;
    func_1513F6C0(arg0, 6, arg0->unk81);
}

s32 func_150BB930(struct_eu_E88D0 *arg0) {
    if (arg0->unk1C < arg0->unkB0) {
        s16 temp_lo = arg0->unk1C * arg0->unkB2;
        if (temp_lo < arg0->unk28) {
            arg0->unk28 = temp_lo;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E88D0/func_150BB978.s")
