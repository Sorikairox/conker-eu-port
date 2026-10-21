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

#ifdef NON_MATCHING
s32 func_15081120(s32, u8 *, u8, s32, f32, s32);

s32 func_15081974(s32 arg0, s32 arg1, f32 arg2, u8 **arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 temp_v0_2;
    struct127 *var_s0;

    *arg3 = NULL;
    var_s0 = D_800CC2D0;
loop_1:
    if ((var_s0->interaction_state != 0) && (var_s0->unk1D4 != NULL) && (arg5 == var_s0->id)) {
        temp_v0_2 = func_1508148C((u8 *) var_s0);
        if (temp_v0_2 != -1) {
            temp_v0 = func_15081120(arg0, (u8 *) var_s0, (*(u8 *)((u8 *)((((u8 *)&D_8009C100) + (temp_v0_2 * 4))) + 2)), arg1, arg2, arg4);
            if (temp_v0 != 0) {
                *arg3 = var_s0;
                return temp_v0;
            }
        }
    }
    var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    if ((s32)var_s0 == (s32)&D_800D121C) {
        return 0;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_15081974.s")
#endif