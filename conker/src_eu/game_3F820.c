#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_151F0114(void *, float, float, float, float, float, float, float);

void func_15012370(void) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_s0;
    u8 *temp_v0;

    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = D_800BE628 + (var_s0 * 0x180);
            temp_f0 = (*(f32 *)((u8 *)temp_v0 + 4)) * 0.5f;
            temp_f2 = (*(f32 *)((u8 *)temp_v0 + 8)) * 0.5f;
            func_151F0114(D_800DD040 + (var_s0 << 6), -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, 20000.0f, 1.0f);
            temp_t0 = (var_s0 + 1) & 0xFF;
            var_s0 = temp_t0;
        } while (D_80082FA0 >= temp_t0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_15012370.s")
#endif
// void func_15012370(void) {
//     f32 temp_f0;
//     f32 temp_f2;
//     u8 i;
//
//     f32 foo = D_80096560; // 20000.0f
//     f32 **tmp = D_800BE628;
//
//     for (i = 0; i <= D_80082FA0; i++) {
//         temp_f0 = tmp[i][1] * 0.5f;
//         temp_f2 = tmp[i][2] * 0.5f;
//         func_151EF954(D_800DCC10[i], -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, foo, 1.0f);
//     }
// }

void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 300, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_150124A0.s")
