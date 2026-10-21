#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_150DFDA0(struct108 *arg0) {
    s32 temp_t1;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t9;

    temp_t7 = arg0->unk84 & ~0x4000;
    temp_t9 = temp_t7 | 4;
    arg0->unk84 = temp_t7;
    arg0->unk84 = temp_t9;
    temp_t1 = temp_t9 & ~0x1010;
    arg0->unk84 = temp_t1;
    temp_t5 = temp_t1 | 0x1010;
    if (arg0->unk3D0->in_water != 0) {
        arg0->unk84 = temp_t5;
        arg0->unk84 = temp_t5 & ~4;
        arg0->unk374 = 750.0f;
        return;
    }
    if (arg0->unk374 == 750.0f) {
        arg0->unk1B4 = 3;
        func_15124B18(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10D5B0/func_150DFDA0.s")
#endif