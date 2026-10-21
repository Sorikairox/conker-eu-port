#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151D2C70(s16 arg0) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x3C, 1, 0x18, 0, 0xFFU, 1U);
    (*(s16 *)((u8 *)temp_v0 + 0x14)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x12)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0xE)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x16)) = 1;
    (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg0;
}

void func_151D2CC8(s16 arg0) {
    u8 *var_v0;

    for (var_v0 = D_800DD510; var_v0 != NULL; var_v0 = *(u8 **)(var_v0 + 8)) {
        if (arg0 == *(s16 *)(var_v0 + 0x10)) {
            *(s8 *)(var_v0 + 0x16) = -2;
        }
    }
}

typedef struct {
    u8 pad0[0xE];
    s16 xE;
    s16 x10;
    s16 x12;
    s16 x14;
    s8 x16;
} Obj2D0C;

void func_151D2D0C(Obj2D0C *arg0) {
    arg0->xE += D_800BE9E4 * arg0->x16;
    if (arg0->x16 > 0 && arg0->xE >= 0xED) {
        arg0->x14 = (0x128 - arg0->xE) << 2;
        if (arg0->x14 < 0) {
            arg0->x14 = 0;
        }
    } else {
        arg0->x14 = arg0->xE * 2;
    }
    if (arg0->x14 >= 0x80) {
        arg0->x14 = 0x80;
    }
    arg0->x12++;
    if (arg0->x12 >= 0x100) {
        arg0->x12 -= 0x100;
    }
    if (arg0->xE >= 0x12D || arg0->xE < 0) {
        func_1516972C((struct102 *)arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_200480/func_151D2DE0.s")
