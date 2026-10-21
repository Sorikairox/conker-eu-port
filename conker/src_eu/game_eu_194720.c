#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15166F10(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;
    s32 var_s0;
    s32 var_s2;
    u8 *var_s1;
    s32 temp;

    temp_v0 = func_15167A68(0xD, arg5, 0xE0, 1, (u8) (s32) arg4, 1U);
    if (temp_v0 != NULL) {
        (*(s8 *)((u8 *)temp_v0 + 0xD0)) = 0xA;
        (*(s16 *)((u8 *)temp_v0 + 0xD2)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0xD4)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0xD6)) = (s16) arg2;
        (*(f32 *)((u8 *)temp_v0 + 0xD8)) = arg3;
        var_s0 = func_150ADA20() & 0x7F;
        var_s2 = 0;
        var_s1 = temp_v0 + 0x10;
        do {
            if (arg3 != 1.0f) {
                func_15043D90((Mtx *)var_s1, 0.0f, (f32) var_s0, 0.0f, arg3, arg3, arg3, (f32) arg0, (f32) arg1, (f32) arg2);
            } else {
                func_15043E68((Mtx *)var_s1, 0.0f, (f32) var_s0, 0.0f, (f32) arg0, (f32) arg1, (f32) arg2);
            }
            temp = func_150ADA20() & 0x3F; // fakematch: temp + split increments reproduce the schedule
            var_s2 += 0x40;
            var_s0 += temp;
            var_s1 += 0x40;
            var_s0 += 0x5A;
        } while (var_s2 != 0xC0);
        func_1517E5CC(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_194720/func_eu_151670C0.s")

extern Vtx D_8008B780[];

Gfx *func_151672D8(Gfx *gdl, u8 *arg1, s32 arg2) {
    s32 i;
    s32 t;

    for (i = 0; i < 3; i++) {
        gSPMatrix(gdl++, arg1 + 0x10 + i * 0x40, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPVertex(gdl++, D_8008B780, 6, 0);
        t = 0x2800 - (arg1[0xD0] << 12) / 10;
        gSPModifyVertex(gdl++, 0, G_MWO_POINT_ST, (t << 16) + 0x2000);
        gSPModifyVertex(gdl++, 1, G_MWO_POINT_ST, (t << 16) + 0x2000);
        gSPModifyVertex(gdl++, 2, G_MWO_POINT_ST, (t << 16) + 0x2400);
        gSPModifyVertex(gdl++, 3, G_MWO_POINT_ST, ((t + 0x800) << 16) + 0x2000);
        gSPModifyVertex(gdl++, 4, G_MWO_POINT_ST, ((t + 0x800) << 16) + 0x2000);
        gSPModifyVertex(gdl++, 5, G_MWO_POINT_ST, ((t + 0x800) << 16) + 0x2400);
        gSP1Triangle(gdl++, 5, 3, 0, 0);
        gSP1Triangle(gdl++, 2, 5, 0, 0);
        gSP1Triangle(gdl++, 1, 4, 5, 0);
        gSP1Triangle(gdl++, 1, 5, 2, 0);
    }
    return gdl;
}

extern u8 D_800908FC[];
extern u8 *D_800DD658;
extern s32 D_800DD650;
extern s32 D_800DD654;
extern u8 D_800DD660[];
void func_151674DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 **p = &D_800DD658;

    *p = D_800908FC;
    func_15095380(arg0, *p, D_800DD650, D_800DD660, 0, 0, 0, D_800DD654, 3);
}

Gfx *func_15167548(Gfx *arg0, s32 arg1, s32 arg2) {
    gSPMatrix(arg0++, D_80089810, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return arg0;
}
