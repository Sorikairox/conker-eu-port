#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} struct_eu_F3AD0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ struct_eu_F3AD0_b *unk58;
    /* 0x5C */ u8 unk5C;
} struct_eu_F3AD0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C62C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C630C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C63FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C6440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C6494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C65D8.s")

s32 func_150C68EC(struct_eu_F3AD0 *arg0) {
    s32 ret = 1;

    if (arg0->unk5C == 0) {
        ret = 0;
    }
    arg0->unk5C = 0;
    return ret;
}

void func_150C6910(struct_eu_F3AD0 *arg0) {
    s32 *temp_v0 = &arg0->unk58->unk58;

    temp_v0[1] = 0;
    func_151346EC(arg0);
}

void func_150C6938(struct_eu_F3AD0 *arg0) {
    s32 *temp_v0 = &arg0->unk58->unk58;

    temp_v0[1] = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3AD0/func_150C6960.s")
