#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B78C.s")

void func_1515BB64(s16 arg0) {
    s16 sp1C[2];

    sp1C[0] = arg0;
    func_15155C9C((f32 *)sp1C, 0xB);
}

void func_1515BB9C(u8 *arg0, s16 *arg1, u8 arg2) {
    if (arg2 == 0xB) {
        if (*(s16 *)(arg0 + 0x70) == *arg1) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BBE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BF04.s")

void func_1515BF80(s32 arg0) {
}

void func_1515BF8C(s16 arg0) {
    func_1515B500(arg0);
}

void func_1515BFB8(s32 arg0) {
}

void func_1515BFC4(s16 arg0) {
    func_1515BBE4(arg0);
}

void func_1515BFF0(s16 arg0) {
    func_1515BB64(arg0);
}

void func_1515C01C(s16 arg0) {
    func_1515BB64(arg0);
}
