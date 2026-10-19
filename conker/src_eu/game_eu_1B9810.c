#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C000.s")

void func_1518C164(u8 *arg0) {
    s32 i;
    struct_eu_node *node;

    if (arg0 != NULL) {
        for (i = 0; i < 2; i++) {
            u8 *new_var; // fakematch: permuter temp, turns the loop tail into bnel
            node = D_800DD280[i][0x1F];
            D_800DD5C0++;
            while (node != NULL) {
                D_800DD5C8[D_800DD5C0] = node->next;
                new_var = (u8 *)node;
                *(u8 **)(new_var + 0x24) = arg0;
                if ((arg0 != NULL) || (arg0[0x3B] == *((u8 *)node + 0x28))) {
                    func_1516972C((struct102 *)node);
                }
                node = D_800DD5C8[D_800DD5C0];
            }
            D_800DD5C0--;
        }
    }
}

s32 memcpy(u8 *, s32, s32);

u8 *func_1518C240(s32 arg0, u8 arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x1F, arg2, 0x44, 1, (u8) (s32) arg1, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0x10, arg0, 0x1C);
    (*(s32 *)((u8 *)temp_v0 + 0x2C)) = (s32) (func_150ADA20() & 0x1F);
    (*(s32 *)((u8 *)temp_v0 + 0x30)) = (s32) (func_150ADA20() & 0x1F);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C2D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518C628.s")

s32 func_1518CAB0(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    temp_v0[0x1B] = var_v1;
    if (temp_v0[0x1B] < 0) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CAEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CC0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B9810/func_1518CDC0.s")
