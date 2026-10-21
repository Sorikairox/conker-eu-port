#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15040D90(s32 arg0) {

}

#ifdef NON_MATCHING
void func_15040D9C(s32 arg0) {
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_t0;
    s32 temp_t8;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;

    var_v1 = D_8002AAE8[D_800BE9C0 == 0];
    var_a1 = 0;
    do {
        var_v0 = 0;
        var_a2 = arg0;
        temp_t0 = var_a1 + 0xE1;
loop_2:
        var_v0 += 4;
        (*(s16 *)((u8 *)((var_v1 + (var_a2 * 2) + (D_800BE620 * temp_t0 * 2))) + 0x190)) = 0xF800;
        (*(s16 *)((u8 *)((D_8002AAE8[D_800BE9C0] + (var_a2 * 2) + (D_800BE620 * temp_t0 * 2))) + 0x190)) = 0xF800;
        temp_a3 = D_800BEDE4 + (var_a2 * 2);
        (*(s16 *)((u8 *)((temp_a3 + (D_800BE620 * temp_t0 * 2))) + 0x190)) = 0;
        (*(s16 *)((u8 *)((temp_a3 + (D_800BE620 * temp_t0 * 2))) + 0x192)) = 0xF800;
        (*(s16 *)((u8 *)((D_8002AAE8[D_800BE9C0] + (var_a2 * 2) + (D_800BE620 * temp_t0 * 2))) + 0x192)) = 0xF800;
        temp_a3_2 = D_800BEDE4 + (var_a2 * 2);
        (*(s16 *)((u8 *)((temp_a3_2 + (D_800BE620 * temp_t0 * 2))) + 0x192)) = 0;
        (*(s16 *)((u8 *)((temp_a3_2 + (D_800BE620 * temp_t0 * 2))) + 0x194)) = 0xF800;
        (*(s16 *)((u8 *)((D_8002AAE8[D_800BE9C0] + (var_a2 * 2) + (D_800BE620 * temp_t0 * 2))) + 0x194)) = 0xF800;
        temp_a3_3 = D_800BEDE4 + (var_a2 * 2);
        (*(s16 *)((u8 *)((temp_a3_3 + (D_800BE620 * temp_t0 * 2))) + 0x194)) = 0;
        (*(s16 *)((u8 *)((temp_a3_3 + (D_800BE620 * temp_t0 * 2))) + 0x196)) = 0xF800;
        (*(s16 *)((u8 *)((D_8002AAE8[D_800BE9C0] + (var_a2 * 2) + (D_800BE620 * temp_t0 * 2))) + 0x196)) = 0xF800;
        var_v1 = D_800BEDE4;
        temp_t8 = var_v1 + (var_a2 * 2);
        var_a2 += 4;
        (*(s16 *)((u8 *)((temp_t8 + (D_800BE620 * temp_t0 * 2))) + 0x196)) = 0;
        if (var_v0 != 8) {
            goto loop_2;
        }
        var_a1 += 1;
    } while (var_a1 != 8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040D9C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040FCC.s")

void func_1504129C(void) {
    s32 i = 0;
    do {} while (++i < 0x18000000);
}
