#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern s32 D_800C6A70;
extern u32 D_800C6A74;

void func_1503E0C0(s32 arg0) {
    u32 temp_t5;
    u32 var_v0;
    u8 *var_v1;

    if ((arg0 >= 0) && ((u32) arg0 < (u32) D_800C6A74)) {
        (*(s16 *)((u8 *)((D_800C6A70 + (arg0 * 0x14))) + 6)) = 2;
        var_v0 = D_800C6A74;
        if (var_v0 != 0) {
            var_v1 = D_800C6A70 + ((var_v0 - 1) * 0x14);
            if ((*(u16 *)((u8 *)var_v1 + 6)) & 2) {
loop_4:
                temp_t5 = var_v0 - 1;
                D_800C6A74 = temp_t5;
                var_v0 = temp_t5;
                var_v1 -= 0x14;
                if (temp_t5 != 0) {
                    if ((*(u16 *)((u8 *)var_v1 + 6)) & 2) {
                        goto loop_4;
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B8D0/func_1503E0C0.s")
#endif