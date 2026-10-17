#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF950/func_150D2140.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FF950/func_150D247C.s")

void func_150D2564(u8 *arg0) {
    u8 *base = arg0 + 0x28;
    u8 i;

    for (i = 0; i < 6; i++) {
        struct102 *p = ((struct102 **)(base + 0x24))[i];

        if (p != NULL) {
            func_1516972C(p);
        }
    }
}

void func_150D25C0(struct260 *arg0) {
    func_150D2564(arg0);
    func_15149368(arg0);
}

void func_150D25EC(struct260 *arg0) {
    func_150D2564(arg0);
    func_1514933C(arg0);
}
