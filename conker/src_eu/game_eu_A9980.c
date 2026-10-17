#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_A9980/func_1507C170.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_A9980/func_1507C608.s")

void func_1507C700(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x2D0));
    temp_v1 = (*(u8 **)((u8 *)arg1 + 0x2D0));
    if ((temp_v0 != NULL) && (temp_v1 != NULL)) {
        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (*(f32 *)((u8 *)temp_v1 + 8));
        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0x18)) - 1.0f;
        if (temp_f0 <= (*(f32 *)((u8 *)temp_v0 + 8))) {
            (*(f32 *)((u8 *)temp_v0 + 8)) = temp_f0;
        }
    }
}
