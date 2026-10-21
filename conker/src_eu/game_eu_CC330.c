#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151F2BA8(void);
void func_151F2D6C(s32, s32);
extern s32 D_800D3C60;

s32 func_1509EB20(s32 arg0, s32 arg1, u8 *arg2) {
    s32 var_a1;

    switch (arg1) {                                 /* irregular */
    case 0:
        var_a1 = 0x7FFF;
        if (D_800D3C60 >= 3) {
            var_a1 = (*(s32 *)((u8 *)arg2 + 8));
        }
        func_1001263C(arg0, var_a1, 0x40);
        return 1;
    case 1:
        if (D_800D3C60 == 4) {
    s32 pad;
            func_151F2D6C((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
            return 1;
        }
        func_151F2D6C((*(s32 *)((u8 *)arg2 + 8)), 0);
        return 1;
    case 2:
        func_151F2BA8();
        return 1;
    default:
        return 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC330/func_1509EB20.s")
#endif
s32 func_1509EBD0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret = 0;

    if (arg1 == 3) {
        return func_151F2CDC() == 1;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
extern s32 D_800D3C60;

s32 func_1509EC10(s32 arg0, u32 arg1, u8 *arg2) {
    s32 temp_a0;
    s32 var_a1;

    switch (arg1) {
    case 0:
        func_1000D96C(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
        return 1;
    case 2:
        func_1000DF68(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), 0);
        return 1;
    case 5:
        func_1000DF68(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), 1);
        return 1;
    case 1:
        func_1000DE1C(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)));
        return 1;
    case 3:
        if (D_800D3C60 == 5) {
            return func_1000E46C(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(s32 *)((u8 *)arg2 + 0x10)));
        }
        return func_1000E46C(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), 0x3C);
    case 4:
        temp_a0 = arg0 & 0xFFF;
        if (D_800D3C60 == 5) {
            return func_1000E654(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(s32 *)((u8 *)arg2 + 0x10)) & 0xFFF);
        }
        return func_1000E654(temp_a0, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), temp_a0);
    case 6:
        var_a1 = 1;
        if (D_800D3C60 == 3) {
            var_a1 = (*(s32 *)((u8 *)arg2 + 8));
        }
        func_1000E054(arg0 & 0xFFF, var_a1);
        return 1;
    default:
        return 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CC330/func_1509EC10.s")
#endif
s32 func_1509ED80(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 7:
        return func_1000E0F8(arg0);
    case 8:
        return func_1000E8F0(arg0);
    }
    return 0;
}
