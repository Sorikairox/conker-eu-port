#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_1512EA20(u8 *arg0) {
    f32 sp18;
    f32 temp_f12;
    f32 temp_f8;
    s32 var_a1;
    struct127 *temp_v0;

    var_a1 = 0;
    if ((*(u8 *)((u8 *)arg0 + 0x23D)) == 3) {
        var_a1 = 1;
    }
    temp_v0 = &D_800CC2D0[var_a1];
    (*(f32 *)((u8 *)arg0 + 0x2BC)) = (f32) temp_v0->x_position;
    (*(f32 *)((u8 *)arg0 + 0x2C0)) = (f32) (temp_v0->y_position + 150.0f);
    (*(f32 *)((u8 *)arg0 + 0x2C4)) = (f32) temp_v0->z_position;
    temp_f12 = ((f32) (s16) (s32) ((f32) (s16) ((*(s16 *)((u8 *)temp_v0 + 0x2E4)) * -1) + (temp_v0->unk40 * 10.0f)) * 3.1415927f) / 1800.0f;
    sp18 = temp_f12;
    temp_f8 = sinf(temp_f12) * 60.0f;
    (*(f32 *)((u8 *)arg0 + 0x2FC)) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C0));
    (*(f32 *)((u8 *)arg0 + 0x2F8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2BC)) - temp_f8);
    (*(f32 *)((u8 *)arg0 + 0x300)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x2C4)) - (cosf(temp_f12) * 60.0f));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C230/func_1512EA20.s")
#endif