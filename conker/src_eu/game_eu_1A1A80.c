#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1A80/func_15174270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A1A80/func_1517485C.s")

typedef struct {
    f32 x, y, z;
    u8 state;
    u8 pad[3];
    struct_eu_bytes24 info;
    s8 b34;
    s32 v38;
} Ent_DD778; // size 0x3C
extern Ent_DD778 D_800DD778[];

s32 func_15174B60(f32 arg0, f32 arg1, f32 arg2, struct_eu_bytes24 *arg3, s8 arg4, s32 arg5) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_800DD778[i].state == 0) {
            D_800DD778[i].x = arg0;
            D_800DD778[i].y = arg1;
            D_800DD778[i].state = 3;
            D_800DD778[i].z = arg2;
            D_800DD778[i].b34 = arg4;
            D_800DD778[i].v38 = arg5;
            if (arg3 != NULL) {
                D_800DD778[i].info = *arg3;
            }
            return 0;
        }
    }
    return 1;
}
