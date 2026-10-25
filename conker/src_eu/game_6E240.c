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
#ifdef NON_MATCHING
// debug_marker_box_draw: draws an 8x8 box at (200 + x, 225) straight into both framebuffers (D_8002AAE8, the
// other one first, row stride D_800BE620 pixels) and the D_800BEDE4 buffer: a red (0xF800) outline with a black
// inside in the framebuffers, 0 everywhere in D_800BEDE4.
#define MARKER_PIXEL(col, row) (x + (col) + D_800BE620 * ((row) + 225) + 200)
void func_15040FCC(s32 x) {
    u16 *other = (u16 *) D_8002AAE8[D_800BE9C0 == 0];
    u16 *current = (u16 *) D_8002AAE8[D_800BE9C0];
    u16 *aux = (u16 *) D_800BEDE4;
    s32 row;
    s32 col;

    for (col = 0; col < 8; col++) {
        other[MARKER_PIXEL(col, 0)] = 0xF800;
        current[MARKER_PIXEL(col, 0)] = 0xF800;
        aux[MARKER_PIXEL(col, 0)] = 0;
    }
    for (row = 1; row < 7; row++) {
        for (col = 0; col < 8; col += 7) {
            other[MARKER_PIXEL(col, row)] = 0xF800;
            current[MARKER_PIXEL(col, row)] = 0xF800;
            aux[MARKER_PIXEL(col, row)] = 0;
        }
    }
    for (row = 1; row < 7; row++) {
        for (col = 1; col < 7; col++) {
            other[MARKER_PIXEL(col, row)] = 0;
            current[MARKER_PIXEL(col, row)] = 0;
            aux[MARKER_PIXEL(col, row)] = 0;
        }
    }
    for (col = 0; col < 8; col++) {
        other[MARKER_PIXEL(col, 7)] = 0xF800;
        current[MARKER_PIXEL(col, 7)] = 0xF800;
        aux[MARKER_PIXEL(col, 7)] = 0;
    }
}
#undef MARKER_PIXEL
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E240/func_15040FCC.s")
#endif

void func_1504129C(void) {
    s32 i = 0;
    do {} while (++i < 0x18000000);
}
