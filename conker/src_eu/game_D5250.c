#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// setting W values in identity matrix
#ifdef NON_MATCHING
void func_150A7DA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(f32 *)((u8 *)arg0 + 0)) = 1.0f;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0xC)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x14)) = 1.0f;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x24)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x28)) = 1.0f;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x30)) = arg1;
    (*(s32 *)((u8 *)arg0 + 0x34)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x38)) = arg3;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5250/func_150A7DA0.s")
#endif
// NON-MATCHING: same issues as other matrix funcs
// void func_150A7DA0(f32 arg0[4][4], s32 arg1, s32 arg2, s32 arg3) {
//     if (0) {};
//     ((s32)arg0[0][1]) = 0;
//     (arg0[0][0]) = 1.0f;
//     dummy_label_418035: ;
//     ((s32)arg0[0][2]) = 0;
//     ((s32)arg0[0][3]) = 0;
//     ((s32)arg0[1][0]) = 0;
//     (arg0[1][1]) = 1.0f;
//     ((s32)arg0[1][2]) = 0;
//     ((s32)arg0[1][3]) = 0;
//     ((s32)arg0[2][0]) = 0;
//     ((s32)arg0[2][1]) = 0;
//     (arg0[2][2]) = 1.0f;
//     ((s32)arg0[2][3]) = 0;
//     ((s32)arg0[3][0]) = arg1;
//     ((s32)arg0[3][1]) = arg2;
//     ((s32)arg0[3][2]) = arg3;
//     (arg0[3][3]) = 1.0f;
// }
