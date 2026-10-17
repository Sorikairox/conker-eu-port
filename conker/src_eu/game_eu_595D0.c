#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ u8 unkA4;
    /* 0xA5 */ u8 unkA5;
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
} struct_eu_595D0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502BDC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C1D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C494.s")

void func_1502C380(void) {
    D_800C42AC = D_800C42A8 = (&D_800C3E80)[D_800BE9C0];
    D_800C429A = 0;
}

s32 func_1502C6AC(s32 arg0) {
    s32 temp_v1 = (&D_800CC826)[arg0 * 0x32C];

    if (temp_v1 >= 0x46) {
        temp_v1 = 0xB;
    }
    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C6F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C8F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C9D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CC64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CF24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CFEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D83C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DB14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E228.s")

void func_1502E764(void) {
    if ((u16)D_800C429A != 0) {
        func_150A9E64((&D_800C3E80)[D_800BE9C0], (u16)D_800C429A);
    }
    D_800C42B0 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E7B4.s")

void func_1502ECEC(s32 arg0, s32 arg1) {
}

void func_1502ECFC(struct_eu_595D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unkA4 = 4;
    arg0->unkA5 = 0;
    arg0->unkA6 = arg5;
    arg0->unkA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    arg0->unkA7 = 0xFF;
}

void func_1502ED40(struct_eu_595D0 *arg0) {
    arg0->unkA4 = 5;
}

void func_1502ED50(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 2;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED6C(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 3;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502ED88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EDEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EF24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F17C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F1E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F30C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F6B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FC38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FCEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_15030060.s")
