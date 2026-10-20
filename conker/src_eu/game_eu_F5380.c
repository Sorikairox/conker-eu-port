#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A0890;
s32 func_150C7B70(u8 *arg0) {
    f32 t = (u32)(*(u8 **)(*(u8 **)(arg0 + 0x170) + 0x14))[0x2F];
    arg0[0x70] = t * D_800A0890;
    if (!arg0 && !arg0 && !arg0) { // fakematch: permuter; gives the early `li v0,1` and the unfilled `sb; nop; jr ra; nop` tail
    }
    return 1;
}

s32 func_150C7C3C(void *arg0, s32 arg1) {
    memcpy(arg0, &D_80089810, 0x40);
    return 1;
}
