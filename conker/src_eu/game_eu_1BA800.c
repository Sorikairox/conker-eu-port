#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BA800/func_1518CFF0.s")

extern void (*D_8008D970[])();

void func_1518D218(u8 *arg0) {
    s32 *new_var; // fakematch: permuter temporaries pin the lw register
    u16 new_var2; // fakematch: permuter temporary
    s32 idx;

    *(s16 *)(arg0 + 0x34) += (u32)(*(s32 *)(arg0 + 0x14) & 0xFFFF0000) >> 16;
    new_var = (s32 *)(arg0 + 0x14);
    new_var2 = *new_var;
    *(s16 *)(arg0 + 0x36) += new_var2;
    if (*(s16 *)(arg0 + 0x38) == 0) {
        idx = arg0[0x3B] & 0xF;
        if (idx != 0) {
            D_8008D970[idx]();
        }
    }
}
