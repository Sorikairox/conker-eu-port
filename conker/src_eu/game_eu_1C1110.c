#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C1110/func_15193900.s")

void func_15193A24(u8 *arg0) {
    s16 temp_v0;
    f32 sp38[3];

    if ((*(s16 *)((u8 *)arg0 + 0xA4)) < (*(s16 *)((u8 *)arg0 + 0x96))) {
        temp_v0 = (*(s16 *)((u8 *)arg0 + 0xAA));
        (*(s16 *)((u8 *)arg0 + 0xA4)) = (s16) ((s32) ((temp_v0 >> 2) * 0x18) / 3);
        (*(s16 *)((u8 *)arg0 + 0xA2)) = (s16) ((s32) ((temp_v0 >> 2) * 6) / 3);
        (*(s16 *)((u8 *)arg0 + 0xAA)) = (s16) (temp_v0 + D_800BE9E4);
        return;
    }
    (*(s16 *)((u8 *)arg0 + 0x94)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x94)) + 1);
    if ((*(s16 *)((u8 *)arg0 + 0x94)) >= 0x15) {
        (*(s16 *)((u8 *)arg0 + 0x94)) = 0x14;
    }
    (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x9E)) - ((s32) ((*(s16 *)((u8 *)arg0 + 0x94)) * D_800BE9E4) >> 1));
    if ((*(s16 *)((u8 *)arg0 + 0x9E)) < (*(s16 *)((u8 *)arg0 + 0xA6))) {
        if ((*(s8 *)((u8 *)arg0 + 0xB3)) == 1) {
            sp38[0] = (f32) (*(s16 *)((u8 *)arg0 + 0x9C));
            sp38[1] = (f32) (*(s16 *)((u8 *)arg0 + 0xA6));
            sp38[2] = (f32) (*(s16 *)((u8 *)arg0 + 0xA0));
            func_151DBCBC(5U, 30.0f, 0xFF, 0, sp38, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        }
        (*(s16 *)((u8 *)arg0 + 0x98)) = -1;
    }
}
