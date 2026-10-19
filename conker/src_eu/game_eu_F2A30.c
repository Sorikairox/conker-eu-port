#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C5220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F2A30/func_150C539C.s")

extern struct102 *D_800D9CF0[];
void func_150C572C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800D9CF0[i] != 0) {
            func_1516972C(D_800D9CF0[i]);
        }
        D_800D9CF0[i] = 0;
    }
}

s32 func_150C5780(void) {
    if ((D_800C35EA == 1) && ((D_800C3A08 == 0xB) || (D_800C3A08 == 0xC) || (D_800C3A08 == 0xD))) {
        return 1;
    }
    return 0;
}

s32 func_150C5780(void);

s32 func_150C57CC(s32 arg0) {
    if (func_150C5780() != 0) {
        return 0;
    }
    return D_8008B148(arg0);
}

s32 func_150C5780();

s32 func_150C5810(u8 *arg0) {
    if (func_150C5780() != 0) {
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x60)) | 0x20000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x60)) & 0xFFFDFFFF);
    }
    return 1;
}
