#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7D70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7DE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7E30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7E68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C7EBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F5580/func_150C8190.s")

void func_150C827C(u8 *arg0) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0xC);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) (temp_v0->x_position - 30.0f);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (temp_v0->y_position + 50.0f);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) (temp_v0->z_position + 30.0f);
}
