#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_10003ACC(s32 arg0, s32 arg1, s32 arg2);


void func_100039C0(void) {
    D_800BE620 = 292; // screen width px
    D_800BE624 = 216; // screen height px
    D_800380A0 = (f32) D_800BE620 / 292.0f;
    D_800380A4 = (f32) D_800BE624 / 216.0f;
    D_800BE9C4 = allocate_memory(D_800BE620 * D_800BE624 * 2, 255, 3, 0);
    func_10003ACC(0, 0, 0);
    func_15015FBC(D_800BE620, D_800BE624);
    // EU: the VI mode is no longer set here
}

#ifdef NON_MATCHING
void func_10003ACC(s32 arg0, s32 arg1, s32 arg2) {
    s16 *var_v1_2;
    s16 temp_t8;
    s32 temp_a1;
    s32 temp_t0;
    s32 var_t2;
    s32 var_v1;
    u8 *var_v1_3;

    var_v1 = (*(s32 *)((u8 *)D_8002AAE8 + 0));
    var_t2 = 0;
    temp_t0 = (s32) (D_800BE620 * D_800BE624 * 2) >> 1;
    if (var_v1 != 0) {
        if (temp_t0 > 0) {
            do {
                var_t2 += 1;
                var_v1 += 2;
                (*(s16 *)((u8 *)var_v1 + -2)) = (s16) (((arg0 << 8) & 0xF800) | ((arg1 * 8) & 0x7C0) | ((arg2 >> 2) & 0x3E) | 1);
            } while (var_t2 < temp_t0);
            var_t2 = 0;
        }
        if (temp_t0 > 0) {
            temp_t8 = ((arg0 << 8) & 0xF800) | ((arg1 * 8) & 0x7C0) | ((arg2 >> 2) & 0x3E) | 1;
            temp_a1 = temp_t0 & 3;
            if (temp_a1 != 0) {
                var_v1_2 = D_8002AAE8[1] + (0 * 2);
                do {
                    var_t2 += 1;
                    *var_v1_2 = temp_t8;
                    var_v1_2 += 2;
                } while (temp_a1 != var_t2);
                if (var_t2 != temp_t0) {
                    goto block_10;
                }
            } else {
block_10:
                var_v1_3 = D_8002AAE8[1] + (var_t2 * 2);
                do {
                    var_t2 += 4;
                    (*(s16 *)((u8 *)var_v1_3 + 2)) = temp_t8;
                    (*(s16 *)((u8 *)var_v1_3 + 4)) = temp_t8;
                    (*(s16 *)((u8 *)var_v1_3 + 6)) = temp_t8;
                    var_v1_3 += 8;
                    (*(s16 *)((u8 *)var_v1_3 + -8)) = temp_t8;
                } while (var_t2 != temp_t0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_39C0/func_10003ACC.s")
#endif
// EU only
#pragma GLOBAL_ASM("asm/nonmatchings/init_39C0/func_10003C10.s")
