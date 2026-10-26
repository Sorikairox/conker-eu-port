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

extern void (*D_8008D0A4[])(s32);
extern u16 D_800CC16E;
s32 func_15196560(s32, s32);
s32 tex_scroll_update();
#ifdef NON_MATCHING
void func_1517E3CC(void);
#else
s32 func_1517E3CC();
#endif
s32 func_15188630();

void func_15174F68(s32 arg0, s32 arg1) {
    func_15165F70();
    func_15196560(D_800B0E00[0], D_800B0E00[1]);
    tex_scroll_update();
    if (D_800B0DF0->padB[0] != 0) {
        D_8008D0A4[D_800B0DF0->padB[0]](arg1);
    }
    if (D_800BE616 == 0) {
        func_1517E3CC();
        func_15188630();
    }
    D_800CC16E += D_800BE9E4 << 6;
}

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
