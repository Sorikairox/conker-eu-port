#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// wtf?
#ifdef NON_MATCHING
/* P20: the asm caller func_15002248 tests v0, which is func_150AB278's return value passed through */
/* was func_15049260 */
s32 quadtree_tri_box_test(struct_eu_bytes24 arg0) {
    return func_150AB278(arg0);
}
#else
void quadtree_tri_box_test(struct_eu_bytes24 arg0) {
    func_150AB278(arg0);
}
#endif

/* was func_150492CC */
void quadtree_set_test_box(f32 arg0, f32 arg1, f32 arg2) {
    D_800CC640 = arg0;
    D_800CC644 = arg1;
    D_800CC648 = arg2;
    D_800CC64C = arg0 / 2;
    D_800CC650 = arg1 / 2;
    D_800CC654 = arg2 / 2;
    if (arg0 == 0.0f) {
        arg0 = D_80099430;
    }
    D_800CC658 = arg1 / arg0;
    D_800CC65C = arg2 / arg0;
}

// too many temp vars
#ifdef NON_MATCHING
extern f32 D_800CC630;
extern f32 D_800CC634;
extern f32 D_800CC638;
extern f32 D_800CC63C;

/* was func_15049350 */
void tri_compute_plane(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 sp4;
    s32 sp0;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f6;

    temp_f0 = (*(f32 *)&(arg0)) - arg3;
    sp0 = arg0;
    temp_f2 = arg1 - arg4;
    sp4 = arg1;
    temp_f12 = arg2 - arg5;
    temp_f14 = (*(f32 *)&(arg0)) - arg6;
    temp_f16 = arg1 - arg7;
    temp_f18 = arg2 - arg8;
    temp_f6 = (temp_f2 * temp_f18) - (temp_f12 * temp_f16);
    D_800CC630 = temp_f6;
    sp10 = temp_f6;
    spC = (-temp_f0 * temp_f18) + (temp_f12 * temp_f14);
    D_800CC634 = spC;
    sp8 = (temp_f0 * temp_f16) - (temp_f2 * temp_f14);
    D_800CC638 = sp8;
    D_800CC63C = (arg2 * sp8) + ((temp_f6 * (*(f32 *)&(arg0))) + (spC * sp4));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/tri_compute_plane.s")
#endif