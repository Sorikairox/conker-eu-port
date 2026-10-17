#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct_eu_node *func_15156544(s32 arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155CF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155D6C.s")

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
