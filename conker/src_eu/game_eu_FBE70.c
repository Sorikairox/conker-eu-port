#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FBE70/func_150CE960.s")

void func_150CEBA4(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x18;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                func_1516972C(arg0);
            }
        }
    }
}
