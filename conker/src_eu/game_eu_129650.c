#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FBE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC8E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FC438.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_129650/func_150FCB94.s")

void func_150FCD98(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 new_var; // fakematch: permuter temp
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == (new_var = *(s32 *)v) || arg1[4] == v[4]) {
            func_1516972C(arg0);
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (t == *(s32 *)(v + 0x18) || arg1[4] == v[0x1C]) {
                func_1516972C(arg0);
            }
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        } else if (*(s32 *)(v + 0x18) != 0) {
            if (*(s32 *)arg1 == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)(arg1 + 4);
                v[0x1C] = arg1[9];
            } else if (*(s32 *)(arg1 + 4) == *(s32 *)(v + 0x18)) {
                *(s32 *)(v + 0x18) = *(s32 *)arg1;
                v[0x1C] = arg1[8];
            }
        }
    }
}

s32 func_150FCEB0(u8 *arg0, s32 arg1, s32 arg2) {
    switch (arg0[4]) {
        case 0x12:
        case 0x23:
        case 0x73:
        case 0x8A:
            return 0;
        default:
            return 1;
    }
}

void func_150FCEF4(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x38) != 0) {
        func_1516972C(*(struct102 **)(arg0 + 0x38));
    }
}

void func_150FCF24(void *arg0) {
    func_150FCEF4(arg0);
    func_1514933C(arg0);
}

void func_150FCF50(void *arg0) {
    func_150FCEF4(arg0);
    func_15149368(arg0);
}
