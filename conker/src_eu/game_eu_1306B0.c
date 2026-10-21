#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15102EA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151030B8.s")

void func_151032D0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
s32 func_15031C4C(u8 *, s16, s32);
void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3);
s32 func_1514654C(u8 *, s32, s32, u8 **, u8 **, s32);

s32 func_15103310(u8 *arg0) {
    u8 *sp44;
    u8 *sp40;
    u8 *sp3C;
    u8 *sp38;
    s16 temp_a1;
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x110));
    (*(u8 *)((u8 *)arg0 + 0x124)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x124)) & 0xFFFE);
    if (((*(u8 *)((u8 *)arg0 + 0x114)) != (*(u8 *)((u8 *)temp_s1 + 0x3B))) || ((*(s32 *)((u8 *)temp_s1 + 0)) == 0)) {
        return 0;
    }
    if (((*(s32 *)((u8 *)temp_s1 + 0x1D4)) == 0) || (((*(u8 *)((u8 *)temp_s1 + 0x74)) & 0xF) == 0xF)) {
        return 1;
    }
    temp_s0 = arg0 + 0x110;
    sp40 = arg0 + 0x34;
    sp44 = arg0 + 0x40;
    sp38 = temp_s0 + 0x18;
    sp3C = temp_s0 + 0x24;
    temp_a1 = (*(s16 *)((u8 *)temp_s0 + 0xC));
    if (temp_a1 != -1) {
        temp_v0 = func_15031C4C(temp_s1, temp_a1, 0);
        if (temp_v0 == 0) {
            return 0;
        }
        if (func_1514654C(temp_s1, temp_v0, (*(s32 *)((u8 *)temp_s0 + 0x10)), &sp40, &sp38, 2) == 0) {
            return 0;
        }
        goto block_12;
    }
    func_15145EA4(&sp40, &sp38, (*(s32 *)((u8 *)temp_s1 + 0x1D4)) + (*(s32 *)((u8 *)temp_s0 + 8)), 2);
block_12:
    (*(u8 *)((u8 *)temp_s0 + 0x14)) = (u8) ((*(u8 *)((u8 *)temp_s0 + 0x14)) | 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103310.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_15103438.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1306B0/func_151037D4.s")
