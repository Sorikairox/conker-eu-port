#include <ultra64.h>


#ifdef NON_MATCHING
/* was func_150A7CB0 */
void mtxf_scale(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)arg0 + 0)) = arg1;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    (*(s32 *)((u8 *)arg0 + 8)) = 0;
    (*(s32 *)((u8 *)arg0 + 0xC)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x10)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x14)) = arg2;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x24)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x28)) = arg3;
    (*(s32 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x30)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x34)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = 1.0f;
    (*(s32 *)((u8 *)arg0 + 0x38)) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5160/mtxf_scale.s")
#endif
// NON-MATCHING: sw/jr in wrong order
// void mtxf_scale(f32 mtx[4][4], s32 x, s32 y, s32 z) {
//     ((s32)mtx[0][0]) = x;
//     ((s32)mtx[0][1]) = 0;
//     ((s32)mtx[0][2]) = 0;
//     ((s32)mtx[0][3]) = 0;
//     ((s32)mtx[1][0]) = 0;
//     ((s32)mtx[1][1]) = y;
//     ((s32)mtx[1][2]) = 0;
//     ((s32)mtx[1][3]) = 0;
//     ((s32)mtx[2][0]) = 0;
//     ((s32)mtx[2][1]) = 0;
//     ((s32)mtx[2][2]) = z;
//     ((s32)mtx[2][3]) = 0;
//     ((s32)mtx[3][0]) = 0;
//     ((s32)mtx[3][1]) = 0;
//     mtx[3][3] = 1.0f;
//     // fakematch to "help"...
//     dummy_label_123:;
//     ((s32)mtx[3][2]) = 0;
// }
