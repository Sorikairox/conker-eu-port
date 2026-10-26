#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_151734E0 */
u8 *screen_flash_overlay_draw(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_800DD2D0 != 0) {
        temp_a0 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xD9E0FFFE;
        (*(s32 *)((u8 *)var_a0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_a0 + 0)) = 0xD9FFFFFF;
        (*(s32 *)((u8 *)temp_a0 + 4)) = 0x200004;
        temp_a0_2 = temp_a0 + 8;
        (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0;
        temp_a0_3 = temp_a0_2 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xE3000A01;
        (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0;
        temp_a0_4 = temp_a0_3 + 8;
        (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xFA000000;
        (*(s32 *)((u8 *)temp_a0_4 + 4)) = (s32) ((D_800DD2D0 & 0xFF) | ~0xFF);
        temp_a0_5 = temp_a0_4 + 8;
        (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xE200001C;
        (*(s32 *)((u8 *)temp_a0_5 + 4)) = 0x504340;
        temp_a0_6 = temp_a0_5 + 8;
        (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xE3000C00;
        (*(s32 *)((u8 *)temp_a0_6 + 4)) = 0;
        temp_a0_7 = temp_a0_6 + 8;
        (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xE3000F00;
        (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0;
        temp_a0_8 = temp_a0_7 + 8;
        (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xFCFFFFFF;
        (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0xFFFDF6FB;
        temp_a0_9 = temp_a0_8 + 8;
        var_a0 = temp_a0_9 + 8;
        (*(s32 *)((u8 *)temp_a0_9 + 0)) = (s32) ((((u32) (*(f32 *)((u8 *)D_800BE628 + 0x28)) & 0x3FF) * 4) | 0xF6000000 | (((u32) (*(f32 *)((u8 *)D_800BE628 + 0x30)) & 0x3FF) << 0xE));
        (*(s32 *)((u8 *)temp_a0_9 + 4)) = (s32) ((((u32) (*(f32 *)((u8 *)D_800BE628 + 0x24)) & 0x3FF) * 4) | (((u32) (*(f32 *)((u8 *)D_800BE628 + 0x2C)) & 0x3FF) << 0xE));
    }
    return var_a0;
}