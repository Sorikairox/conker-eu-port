#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


s32 __osSiGetAccess();
s32 __osSiRelAccess();
s32 func_10025B60(s32, s32 *);
s32 func_151F03CC();
extern s32 D_80042DA0;
extern s32 D_80042DDC;
extern u8 D_80042DE0;

s32 func_151F0260(OSMesgQueue *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0;
    __osSiGetAccess();
    if (D_80042DE0 != 1) {
        func_151F03CC();
        sp1C = func_10025B60(1, &D_80042DA0);
        osRecvMesg(arg0, NULL, 1);
    }
    for (sp18 = 0; sp18 < 0x10; sp18++) {
        *(s32 *)((u8 *)&D_80042DA0 + (sp18 * 4)) = 0xFF;
    }
    D_80042DDC = 0;
    sp1C = func_10025B60(0, &D_80042DA0);
    D_80042DE0 = 1;
    __osSiRelAccess();
    return sp1C;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21DA70/func_151F0324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_21DA70/func_151F03CC.s")
