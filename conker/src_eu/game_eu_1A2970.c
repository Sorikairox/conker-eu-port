#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175160.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175514.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15175EC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15176DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_151770F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_15177360.s")

s32 func_1510B460(u8 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);
Gfx *func_15177360(Gfx *, u8 *, s16);
extern f32 D_800D3A00;
extern f32 D_800D3A04;
extern f32 D_800D9F40;
extern u8 D_800DA030[];

Gfx *func_15177638(Gfx *gdl, u8 *arg1, s16 arg2) {
    f32 mf[4][4];
    s32 pad[2];

    if (func_1510B460(&D_800DA030[arg2 << 6], *(s32 *)(arg1 + 0x98), *(s32 *)(arg1 + 0x9C), *(s32 *)(arg1 + 0xA0), D_800D9F40, 4000.0f, D_800D3A00, D_800D3A04, 0, 0) == 0) {
        switch (arg1[0x91]) {
        case 0:
            func_150A8050(mf, *(f32 *)(arg1 + 0xA8), *(f32 *)(arg1 + 0xAC), *(f32 *)(arg1 + 0xB0));
            mf[3][0] = *(f32 *)(arg1 + 0x98);
            mf[3][1] = *(f32 *)(arg1 + 0x9C);
            mf[3][2] = *(f32 *)(arg1 + 0xA0);
            guMtxF2L(mf, arg1 + 0x10 + (D_800BE9C0 << 6));
            gSPMatrix(gdl++, arg1 + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gdl++, 1, D_800DDE80[0x33]);
            gSPDisplayList(gdl++, D_800DDE80[0x35]);
            break;
        case 1:
        case 2:
        case 3:
        default:
            gdl = func_15177360(gdl, arg1, arg2);
            break;
        }
    }
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/func_151777CC.s")
