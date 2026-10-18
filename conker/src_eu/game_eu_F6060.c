#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8850.s")

void func_150C89F4(s32 arg0) {
    if (arg0 == 0) {
        func_150C8850();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C851C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8B00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8C30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C8F68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C92B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150C9EB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA0DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA2C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA57C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CA150.s")

s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);

void func_150CAE30(u8 *arg0) {
    s16 sp3E;

    sp3E = (func_150ADA20() % 21U) + 0xA;
    func_1514CBE8((*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(s32 *)((u8 *)arg0 + 8)), (func_150ADA68() * 59.0f) + 170.0f, 0, 0xFF, (s32) sp3E, 0x13, 0, 0.0f, 0, 0xFF);
}

s32 func_150CAED0(u8 *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x1C));
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) (*(u8 *)((u8 *)arg0 + 0x28))) {
            (*(u8 *)((u8 *)arg0 + 0x28)) = (u8) temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CAF04.s")

s32 func_150CB128(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CB2D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F6060/func_150CB508.s")
