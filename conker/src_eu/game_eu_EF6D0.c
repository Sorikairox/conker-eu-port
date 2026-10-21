#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15142314(void *, s32, void *);

s32 func_150C1EC0(s32 arg0, u8 *arg1, s32 arg2) {
    s32 sp1C;
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {                              /* irregular */
    case 1:
        sp1C = 0x18;
        break;
    case 2:
        sp1C = 0x15;
        break;
    }
    func_15142314((*(s32 *)((u8 *)arg1 + 0x1D4)), sp1C, arg0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF6D0/func_150C1EC0.s")
#endif
s32 func_150C1F2C(s32 arg0, s32 arg1) {
    return 7;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF6D0/func_150C1F40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EF6D0/func_150C2334.s")
