#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_1500F980 */
void level_fx_spawn_box_b(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct260 *temp_v0;

    temp_v0 = effect_node_create_nodraw((s16) ((random_int() & 0x7F) + 0xA), 1, -1, 1U, 0U, 0xA, 0xFFU, 0);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0x28)) = (s16) arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x2A)) = (s16) arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x2C)) = (s16) arg2;
        (*(s16 *)((u8 *)temp_v0 + 0x2E)) = (s16) arg3;
        (*(s8 *)((u8 *)temp_v0 + 0x30)) = (s8) arg4;
    }
}

s32 rope_create(s8 *, s32);
extern s32 g_level_rope1_ends; /* was D_800966D0 */
extern s32 g_level_rope2_ends; /* was D_800966E8 */
extern s32 g_level_rope3_ends; /* was D_80096700 */
extern s32 g_level_rope4_ends; /* was D_80096718 */
extern s32 g_level_rope5_ends; /* was D_80096730 */
extern f32 g_rope_light_r; /* was D_800DD1D4 */
extern f32 g_rope_light_b; /* was D_800DD1DC */
extern f32 g_rope_tint_r; /* was D_800DD1E0 */
extern f32 g_rope_tint_g; /* was D_800DD1E4 */
extern f32 g_rope_tint_strength_b; /* was D_800DD1EC */
extern f32 g_rope_tint_strength_a; /* was D_800DD1F0 */

/* was func_1500FA14 */
void level_ropes_setup(void) {
    struct {
        s8 u24;
        u8 pad25[0x3];
        s32 u28;
        s32 u2C;
        u8 pad30[0x8];
        s32 u38;
        u8 pad3C[0x4];
        f32 u40;
        s8 u44;
    } sp;
    f32 var_f10;
    f32 var_f10_2;
    f32 var_f18;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f8;
    f32 var_f8_2;

    sp.u44 = 0;
    (*(s32 *)((u8 *)(&sp.u28) + 0)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 0));
    (*(s32 *)((u8 *)(&sp.u28) + 4)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 4));
    (*(s32 *)((u8 *)(&sp.u28) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 0xC));
    (*(s32 *)((u8 *)(&sp.u28) + 8)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 8));
    (*(s32 *)((u8 *)(&sp.u28) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 0x10));
    (*(s32 *)((u8 *)(&sp.u28) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_level_rope1_ends) + 0x14));
    sp.u24 = 1;
    sp.u40 = fabsf(sp.u2C - sp.u38);
    rope_create(&sp.u24, 0);
    (*(s32 *)((u8 *)(&sp.u28) + 0)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 0));
    (*(s32 *)((u8 *)(&sp.u28) + 4)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 4));
    (*(s32 *)((u8 *)(&sp.u28) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 0xC));
    (*(s32 *)((u8 *)(&sp.u28) + 8)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 8));
    (*(s32 *)((u8 *)(&sp.u28) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 0x10));
    (*(s32 *)((u8 *)(&sp.u28) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_level_rope2_ends) + 0x14));
    sp.u24 = 2;
    sp.u40 = fabsf(sp.u2C - sp.u38);
    rope_create(&sp.u24, 0);
    (*(s32 *)((u8 *)(&sp.u28) + 0)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 0));
    (*(s32 *)((u8 *)(&sp.u28) + 4)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 4));
    (*(s32 *)((u8 *)(&sp.u28) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 0xC));
    (*(s32 *)((u8 *)(&sp.u28) + 8)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 8));
    (*(s32 *)((u8 *)(&sp.u28) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 0x10));
    (*(s32 *)((u8 *)(&sp.u28) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_level_rope3_ends) + 0x14));
    sp.u24 = 3;
    sp.u40 = fabsf(sp.u2C - sp.u38);
    rope_create(&sp.u24, 0);
    (*(s32 *)((u8 *)(&sp.u28) + 0)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 0));
    (*(s32 *)((u8 *)(&sp.u28) + 4)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 4));
    (*(s32 *)((u8 *)(&sp.u28) + 8)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 8));
    (*(s32 *)((u8 *)(&sp.u28) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 0xC));
    (*(s32 *)((u8 *)(&sp.u28) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 0x10));
    (*(s32 *)((u8 *)(&sp.u28) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_level_rope4_ends) + 0x14));
    (*(s32 *)((u8 *)(&sp.u28) + 0)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 0));
    (*(s32 *)((u8 *)(&sp.u28) + 4)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 4));
    (*(s32 *)((u8 *)(&sp.u28) + 8)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 8));
    (*(s32 *)((u8 *)(&sp.u28) + 0xC)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 0xC));
    (*(s32 *)((u8 *)(&sp.u28) + 0x10)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 0x10));
    (*(s32 *)((u8 *)(&sp.u28) + 0x14)) = (s32) (*(s32 *)((u8 *)(&g_level_rope5_ends) + 0x14));
    sp.u24 = 5;
    sp.u40 = fabsf(sp.u2C - sp.u38);
    rope_create(&sp.u24, 0);
    level_fx_spawn_box_b(-0x6E7, -0x46A, 0x421, -0x648, 1);
    level_fx_spawn_box_b(-0xA71, 0x71B, 0x82B, -0x602, 2);
    level_fx_spawn_box_b(-0x870, 0x36E, 0x4E1, -0x602, 2);
    level_fx_spawn_box_b(-0xBD5, 0x3F1, 0x659, -0x602, 2);
    level_fx_spawn_box_b(-0xE6B, -0x263, -0x427, -0x647, 1);
    g_rope_light_r = (f32) (*(u8 *)((u8 *)(&g_level_light_colour) + 0));
    var_f8 = (f32) (*(u8 *)((u8 *)(&g_level_light_colour) + 1));
    if ((s32) (*(u8 *)((u8 *)(&g_level_light_colour) + 1)) < 0) {
        var_f8 += 4294967296.0f;
    }
    *g_rope_light_g = var_f8;
    var_f4 = (f32) (*(u8 *)((u8 *)(&g_level_light_colour) + 2));
    if ((s32) (*(u8 *)((u8 *)(&g_level_light_colour) + 2)) < 0) {
        var_f4 += 4294967296.0f;
    }
    g_rope_light_b = var_f4;
    var_f10 = (f32) (*(u8 *)((u8 *)g_level_tint_colour + 0));
    if ((s32) (*(u8 *)((u8 *)g_level_tint_colour + 0)) < 0) {
        var_f10 += 4294967296.0f;
    }
    g_rope_tint_r = var_f10;
    var_f18 = (f32) g_level_tint_colour[1];
    if ((s32) g_level_tint_colour[1] < 0) {
        var_f18 += 4294967296.0f;
    }
    g_rope_tint_g = var_f18;
    var_f8_2 = (f32) g_level_tint_colour[2];
    if ((s32) g_level_tint_colour[2] < 0) {
        var_f8_2 += 4294967296.0f;
    }
    *g_rope_tint_b = var_f8_2;
    var_f4_2 = (f32) g_level_tint_strength_b;
    if ((s32) g_level_tint_strength_b < 0) {
        var_f4_2 += 4294967296.0f;
    }
    g_rope_tint_strength_b = var_f4_2;
    var_f10_2 = (f32) g_level_tint_strength_a;
    if ((s32) g_level_tint_strength_a < 0) {
        var_f10_2 += 4294967296.0f;
    }
    g_rope_tint_strength_a = var_f10_2;
}