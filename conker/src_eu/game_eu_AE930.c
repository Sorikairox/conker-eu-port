#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_15081120.s")

extern u16 D_8009C100;
extern u16 D_8009C104;
extern u16 D_8009C108;
extern u16 D_8009C10C[][2];
s32 func_1508148C(u8 *arg0) {
    unsigned long i;
    s32 id;
    if ((id = arg0[4]) == D_8009C100) {
        return 0;
    }
    if (id == D_8009C104) {
        return 1;
    }
    if (id == D_8009C108) {
        return 2;
    }
    for (i = 3; i < 0x17; i++) {
        if (id == D_8009C10C[i - 3][0]) {
            return i;
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_1508154C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_15081974.s")
