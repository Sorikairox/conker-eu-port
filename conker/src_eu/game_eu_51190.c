#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15023980(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023988.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023C60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15023EC4.s")

s32 func_1502AB94(s32, u8, u16, s32, s32);

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u16 unkA;
} struct_150243AC; // size 0xC

extern struct_150243AC *D_800C4170;

void func_150243AC(s32 arg0, s32 arg1) {
    s32 i;
    struct_150243AC *temp_v0;

    for (i = 0; i < arg0; i++) {
        temp_v0 = (struct_150243AC *)((u8 *)D_800C4170 + i * 0xC);
        func_1502AB94(temp_v0->unk0, temp_v0->unk8, temp_v0->unkA, temp_v0->unk4 >> 8, arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024438.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502457C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15024910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_150268BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_15029EA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_51190/func_1502AB94.s")
