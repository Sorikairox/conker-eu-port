#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_eu_158110;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512A390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B2C4.s")

s32 func_1512B2C4();

void func_1512B670(u8 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 & ~0x100) && (D_800BEAC0 == 0) && (D_800C3671 == 0)) {
        if (temp_v0 != 0x40) {
            temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x84));
            if ((temp_v0_2 & 8) && !(temp_v0_2 & 0x200) && ((*(u8 *)((u8 *)arg0 + 0x23C)) == 0)) {
                temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0x5F0));
                if (!(temp_v0_3 & 0x80) && !(temp_v0_3 & 0x40)) {
                    func_1512B2C4();
                    return;
                }
            }
        }
        (*(s16 *)((u8 *)arg0 + 0x5F8)) = 1;
        (*(s16 *)((u8 *)arg0 + 0x5FC)) = 2;
        (*(s16 *)((u8 *)arg0 + 0x5FE)) = 0x32;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512B728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BAAC.s")

void func_1512BB6C(struct_eu_158110 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2 = arg0->unk1;
    if (arg0->unk4 < arg1) {
        arg0->unk1 = 0;
    } else {
        arg0->unk1 = 1;
    }
    arg0->unk8 = arg2;
    arg0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BBA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512BCA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C080.s")

void func_15123A54(u8 *);
s32 func_1512C6C0(u8 *);

void func_1512C5D8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f14;
    s32 temp_v0;

    if ((*(f32 *)((u8 *)arg0 + 0x390)) < 180.0f) {
        var_f14 = 2.0f;
    } else {
        var_f14 = -2.0f;
    }
    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x2C));
    if ((temp_v0 != 0x80) && (temp_v0 != 0x40)) {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2F8)) - (*(f32 *)((u8 *)arg0 + 0x2BC));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x300)) - (*(f32 *)((u8 *)arg0 + 0x2C4));
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)arg0 + 0x370)) = temp_f0;
        if (temp_f0 < 42.0f) {
            (*(f32 *)((u8 *)arg0 + 0x384)) = (*(f32 *)((u8 *)arg0 + 0x37C)) - 45.0f * var_f14;
            (*(f32 *)((u8 *)arg0 + 0x5CC)) = 0.0f;
            func_15123A54(arg0);
            (*(s32 *)((u8 *)arg0 + 0x240)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x240)) | 2);
        }
    }
    func_1512C6C0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C6C0.s")

void func_1512C770(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_158110/func_1512C77C.s")

s32 func_1512C9EC(s32 arg0) {
    return 1;
}
