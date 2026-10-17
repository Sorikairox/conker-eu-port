#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct_eu_node *func_15156544(s32 arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155CF0.s")

struct_eu_node *func_15155CF0(s32, s32);

void func_15155D6C(s32 arg0, s32 arg1, f32 arg2) {
    struct_eu_node *var_v0;

    var_v0 = func_15156544(arg0);
    if (var_v0 == NULL) {
        var_v0 = func_15155CF0(arg0, 0xFF);
    }
    if (var_v0 != NULL) {
        (*(f32 *)((u8 *)var_v0 + 0x98)) = arg2;
        if (*(&D_800CC37D + (arg0 * 0x32C)) != 0) {
            (*(s16 *)((u8 *)var_v0 + 0xE)) = 0;
            (*(s8 *)((u8 *)var_v0 + 0x11)) = 0;
            return;
        }
        (*(s8 *)((u8 *)var_v0 + 0x11)) = 3;
        (*(s16 *)((u8 *)var_v0 + 0xE)) = (s16) arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_1515626C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15156468.s")

void func_151564AC(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 2) {
            temp_v0[0x11] = 0;
        } else if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 2;
        }
    }
}

void func_15156500(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if ((temp_v0 != NULL) && (temp_v0[0x11] == 3)) {
        temp_v0[0x11] = 1;
    }
}

struct_eu_node *func_15156544(s32 arg0) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][80]; node != NULL; node = node->next) {
            if (arg0 == ((u8 *)node)[0x10]) {
                return node;
            }
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15156598.s")
