#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_800DD835;
extern u8 D_800DD836;

void func_15174F10(s32 arg0, s32 arg1) {
    D_800DD836 += D_800BE9E4;
    if (arg0 < D_800DD836) {
        D_800DD835++;
        if (D_800DD835 >= arg1) {
            D_800DD835 = 0;
        }
        D_800DD836 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2720/func_15174F68.s")

extern Gfx *(*D_8008D114[])(Gfx *, s32);

Gfx *func_15174AA4(Gfx *gdl, s32 arg1, s32 arg2) {
    gDPPipeSync(gdl++);
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (*((u8 *)D_800B0DF0 + 0xC) != 0) {
        gdl = D_8008D114[*((u8 *)D_800B0DF0 + 0xC)](gdl, arg2);
    }
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}

extern Gfx *(*D_8008D11C[])(Gfx *, s32);

Gfx *func_15174B48(Gfx *gdl, s32 arg1, s32 arg2) {
    gDPPipeSync(gdl++);
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (*((u8 *)D_800B0DF0 + 0xD) != 0) {
        gdl = D_8008D11C[*((u8 *)D_800B0DF0 + 0xD)](gdl, arg2);
    }
    gSPMatrix(gdl++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
