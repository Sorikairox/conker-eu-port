#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ECAA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ECC30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ECFE8.s")

void func_150ED0CC(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

s32 func_1502ED88(u8 *, u8, u8, u8, s32, s32, s32);

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

s32 func_150ECFE8(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_151CA070(s32, u8, s32);

void func_150ED180(s32 arg0, u8 arg1, s32 arg2) {
    func_151CA070(arg0, arg1, arg2);
    func_150ECFE8(arg0, 0, 0xFF, 0, 0xFF, 4, -1, (s32) arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_11A2B0/func_150ED1F0.s")
