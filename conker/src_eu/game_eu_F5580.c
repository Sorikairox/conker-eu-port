#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15116A8C(s32, s32, s32, f32);
void func_150C7D70(s32 arg0) {
    if (!((*(u8 *)((u8 *)D_800D2E4C + 0xA)) & 8)) {
        if (!(D_800DBEF4->pad70[3] & 4)) {
            func_15116A8C(arg0, 1, 0x353, 1000.0f);
            return;
        }
        func_15116A8C(arg0, 1, 0x43, 400.0f);
    }
}

void func_1511563C(u8 *);
void func_150C7DE0(u8 *arg0) {
    u8 *p;
    if (!(arg0[0x73] & 4)) {
        p = (u8 *)D_800DBEF4;
        p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
        p--;  // fakematch: pairs with p += K+1
        *(s32 *)(arg0 + 0x3C) = -(*(s32 *)(p + 0x3C) & 0xFFFF0000) & 0xFFFF0000;
        func_1511563C(arg0);
    }
}

void func_150C7E30(u8 *arg0) {
    u8 *p;
    p = (u8 *)D_800DBEF4;
    p += 0x1E1;  // fakematch: keeps the dead addiu (p += K+1; p--;)
    p--;  // fakematch: pairs with p += K+1
    *(s32 *)(arg0 + 0x3C) = *(s32 *)(p + 0x3C) & 0xFFFF0000;
    func_1511563C(arg0);
}

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
