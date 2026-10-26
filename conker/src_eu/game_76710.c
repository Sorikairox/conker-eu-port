#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// wtf?
/* P20: the asm caller quadtree_filter_box_tris tests v0, which is collision_tri_box_test's return value passed through */
/* was func_15049260 */
s32 quadtree_tri_box_test(struct_eu_bytes24 arg0) {
    return collision_tri_box_test(arg0);
}

/* was func_150492CC */
void quadtree_set_test_box(f32 arg0, f32 arg1, f32 arg2) {
    g_quadtree_box_x = arg0;
    g_quadtree_box_y = arg1;
    g_quadtree_box_z = arg2;
    g_quadtree_box_half_x = arg0 / 2;
    g_quadtree_box_half_y = arg1 / 2;
    g_quadtree_box_half_z = arg2 / 2;
    if (arg0 == 0.0f) {
        arg0 = g_quadtree_box_min_x;
    }
    g_quadtree_box_ratio_yx = arg1 / arg0;
    g_quadtree_box_ratio_zx = arg2 / arg0;
}

// too many temp vars
extern f32 g_tri_plane_nx; /* was D_800CC630 */
extern f32 g_tri_plane_ny; /* was D_800CC634 */
extern f32 g_tri_plane_nz; /* was D_800CC638 */
extern f32 g_tri_plane_d; /* was D_800CC63C */

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
    g_tri_plane_nx = temp_f6;
    sp10 = temp_f6;
    spC = (-temp_f0 * temp_f18) + (temp_f12 * temp_f14);
    g_tri_plane_ny = spC;
    sp8 = (temp_f0 * temp_f16) - (temp_f2 * temp_f14);
    g_tri_plane_nz = sp8;
    g_tri_plane_d = (arg2 * sp8) + ((temp_f6 * (*(f32 *)&(arg0))) + (spC * sp4));
}