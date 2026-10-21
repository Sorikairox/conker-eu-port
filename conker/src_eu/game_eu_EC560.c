#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern f32 D_800A0480;
extern f32 D_800A0484;
s32 func_1509BE40(s32, s32, s32);

void func_150BED50(struct108 *arg0) {
    s32 sp28;
    s32 temp_t0;
    s32 temp_v0;

    sp28 = func_1509BE40(0, func_1509BE40(0, 0x2006, 0xB7) | 0x2000, 0xBC);
    temp_v0 = func_1509BE40(0, 0x2000, 0xBB);
    if ((sp28 != 0) && (temp_v0 != -1)) {
        func_1509BFB0(0, 0x400E, 1);
        if (arg0->unk2C != 8) {
            func_1512868C(arg0);
        }
        if (func_15123934(arg0, 8, 0, arg0->unk134, 3) != 0) {
            func_151254F4(arg0, D_800CC335 - 1);
            temp_t0 = arg0->unk84 | 0x01000200;
            arg0->unk84 = temp_t0;
            arg0->unk73C = 0;
            arg0->unk84 = temp_t0 & ~4;
            arg0->unk674 = 0.0f;
        }
        arg0->unk348 = D_800A0480;
        arg0->unk34C = D_800A0480;
        arg0->unk374 = D_800A0484;
        arg0->unk190 = 0.0f;
        func_15123070(arg0);
        return;
    }
    if (func_151239CC(arg0, 3) != 0) {
    s32 pad;
        func_151254F4(arg0, 0);
        arg0->unk674 = 0.0f;
        func_1509BFB0(0, 0x400E, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EC560/func_150BED50.s")
#endif