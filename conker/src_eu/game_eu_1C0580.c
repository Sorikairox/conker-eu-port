#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1510FE4C(s32);
s32 func_15192E20(u8 *, s32 *);
extern void (**D_8008FC00[])(u8 *);
void func_15192800(u8 *arg0, s32 arg1) {
    s32 sp2C;
    s32 sfpad; // fakematch: frame padding
    void (*fn)(u8 *);
    s32 idx;

    if ((arg0 != NULL) && (func_15192E20(arg0, &sp2C) != 0)) {
        switch (func_1510FE4C(*(s32 *)(arg0 + 0x184))) {
        case 5:
            if (D_800BE9F0 == 0x14) {
                idx = 2;
            } else {
                idx = 1;
            }
            break;
        case 6:
            idx = 3;
            break;
        default:
            idx = 1;
            break;
        }
        fn = D_8008FC00[sp2C][idx];
        if (fn != NULL) {
            fn(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C0580/func_15192E20.s")
