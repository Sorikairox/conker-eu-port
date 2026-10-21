#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509C850.s")

#ifdef NON_MATCHING
extern u8 D_800C3A92;
extern u8 D_800C40B8;

void func_1509CBD8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        if (D_800C35C4 != 0) {
            return;
        }
        if (D_800C35EA == 0) {
            return;
        }
        if (arg0 == D_800C40B8) {
            return;
        }
        return;
    case 2:
        if ((D_800C35EA == 1) && (arg0 == D_800C40B8)) {
            return;
        }
        return;
    case 3:
        if ((D_800C35EA == 1) && (arg0 == D_800C3A08)) {
            return;
        }
        return;
        return;
        return;
    case 6:
        if ((D_800C35EA == 1) && (arg0 == D_800C3A08)) {
            return;
        }
    default:
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509CBD8.s")
#endif
#ifdef NON_MATCHING
void func_15022238(s16, s16, s16, f32);
void func_15022290(s16, s16, s16, f32);

void func_1509CD0C(s32 arg0, s32 arg1) {
    f32 var_f0;
    struct127 *temp_v0;

    temp_v0 = func_1505EEF4(arg0 & 0xFFF);
    if (temp_v0 != NULL) {
        if (D_800DBFF0->unk2C & 0x100) {
            var_f0 = (*(f32 *)((u8 *)D_800DBFF0 + 0x760));
        } else {
            var_f0 = D_800DBFF0->unk37C;
        }
        if (arg1 != 0) {
            func_15022290((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
            return;
        }
        func_15022238((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CA060/func_1509CD0C.s")
#endif