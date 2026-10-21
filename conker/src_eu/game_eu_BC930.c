#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1508F120(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_t0;
    u16 temp_a1;
    u16 temp_t1;
    u32 var_a2;
    u32 var_v0;
    u32 var_v0_2;
    u8 *temp_t2;
    u8 *var_a0;
    u8 *var_t3;

    var_v0 = 0;
    if (D_80087380 != 0) {
        var_t0 = D_800D23C0;
loop_2:
        temp_t1 = (*(u16 *)((u8 *)var_t0 + 2));
        var_a2 = 0;
        if (temp_t1 != 0) {
            temp_t2 = D_800D23C0 + (var_v0 * 0x18);
            var_t3 = temp_t2;
loop_4:
            if (((((arg0 & 0xFFFF) << 0xC) + (arg1 & 0xFFFF)) & 0xFFFF) == (*(u16 *)((u8 *)var_t3 + 8))) {
                var_v0_2 = 0;
                if (temp_t1 != 0) {
                    var_a0 = temp_t2;
loop_7:
                    temp_a1 = (*(u16 *)((u8 *)var_a0 + 8));
                    if (((arg2 & 0xFFFF) == ((s32) temp_a1 >> 0xC)) && (var_v0_2 != var_a2)) {
                        return temp_a1 & 0xFFF;
                    }
                    var_v0_2 += 1;
                    var_a0 += 2;
                    if (var_v0_2 >= temp_t1) {
                        goto block_11;
                    }
                    goto loop_7;
                }
block_11:
                goto block_14;
            }
            var_a2 += 1;
            var_t3 += 2;
            if (var_a2 >= temp_t1) {
                goto block_13;
            }
            goto loop_4;
        }
block_13:
        var_v0 += 1;
        var_t0 += 0x18;
        if (var_v0 >= (u32) D_80087380) {
            goto block_14;
        }
        goto loop_2;
    }
block_14:
    return -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_BC930/func_1508F120.s")
#endif
void func_1508F21C(u32 arg0) {
    if (arg0 < D_80087380) {
        *(s16 *)(D_800D23C0 + arg0 * 0x18 + 2) = 0;
        *(s32 *)(D_800D23C0 + arg0 * 0x18 + 4) = 0;
        *(s16 *)(D_800D23C0 + arg0 * 0x18) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_BC930/func_1508F26C.s")
