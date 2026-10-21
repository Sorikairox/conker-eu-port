#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern u8 D_800BE9B0;
extern u16 D_800BE9B8;
extern s32 D_800BE9C8;
extern u8 D_800D2520;

void func_15016800(void) {
    struct {
        s32 u50;
    } sp;
    s32 var_a1;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    u16 *var_v1_2;
    u8 temp_a2;
    u8 temp_s0;

    D_800BE9B0 = 0;
    temp_a2 = D_800D2520;
    sp.u50 = 0;
    var_s1 = 0;
    if ((s32) temp_a2 > 0) {
        do {
            var_a1 = 0;
            temp_s0 = D_800D20FC->pad4[var_s1];
            var_v0 = 0;
            if ((s32) D_800BE9B0 > 0) {
                var_v1_2 = &D_800BE9B8;
loop_4:
                var_v0 += 1;
                if (temp_s0 == *var_v1_2) {
                    var_a1 = 1;
                } else {
                    var_v1_2 += 2;
                    if (var_v0 < (s32) D_800BE9B0) {
                        goto loop_4;
                    }
                }
            }
            if (var_a1 != 0) {
                var_v1 = temp_a2 * 0x30;
            } else {
                if ((s32) temp_s0 < 0xBB) {
                    func_1502B7F0(&sp.u50, 2, 0x12, temp_s0);
                }
                var_v1 = temp_a2 * 0x30;
                if (sp.u50 != 0) {
                    *(s32 *)((u8 *)&D_800BE9C8 + (D_800BE9B0 * 4)) = sp.u50;
                    (&D_800BE9B8)[D_800BE9B0] = (u16) temp_s0;
                    D_800BE9B0 += 1;
                }
            }
            var_s1 += 0x30;
        } while (var_s1 < var_v1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_15016800.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_15016950.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_44010/func_150170C4.s")
