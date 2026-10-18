#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 (*D_800D3040)[4];
s32 func_15094DAC(s32, u8 **);
void func_15094CD0(s32 arg0, u8 *arg1) {
    u8 *sp50[16];
    u8 *v;
    u8 *p;
    s32 i;
    func_15094DAC(arg0, sp50);
    for (i = 0; i < 16; i++) {
        p = sp50[i];
        if (p != NULL) {
            v = arg1 + i * 0xC;
            func_150A7E40(D_800D3040, (f32) *(s16 *)(p + 0), (f32) *(s16 *)(p + 2), (f32) *(s16 *)(p + 4), (f32 *)v, (f32 *)(v + 4), (f32 *)(v + 8));
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C24E0/func_15094DAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C24E0/func_15094EC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C24E0/func_150952B0.s")
