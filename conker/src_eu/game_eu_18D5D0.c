#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for light_add_point
s32 light_add_point(s32, s32, s32, s32, s32, s32, s32, s32, s32, u8);

void light_store_int(f32, s32);

f32 mtx_fixed_get_element(s16 *, s32);

s32 obj_send_hit();

/* was func_1515FDC0 */
void light_cycle_level_colour(s32 arg0, s32 arg1) {
    f32 s;
    f32 r;
    f32 g;
    f32 b;
    u8 c[3];
    c[0] = ((u8 *)&g_level_light_colour)[0];
    c[1] = ((u8 *)&g_level_light_colour)[1];
    c[2] = ((u8 *)&g_level_light_colour)[2];
    s = sinf(g_level_colour_cycle);
    r = (s * 29.5f) + 127.5f;
    g = (s * 71.0f) + 109.0f;
    b = (s * 26.0f) + 26.0f;
    g_level_colour_cycle += 0.071f * g_frame_step_f;
    g_level_colour_cycle = wrap_angle_rad(g_level_colour_cycle);
    if (r != g_level_colour_ease_r) {
        g_level_colour_ease_r += (r - g_level_colour_ease_r) * 0.5f;
        c[0] = g_level_colour_ease_r;
    }
    if (g != g_level_colour_ease_g) {
        g_level_colour_ease_g += (g - g_level_colour_ease_g) * 0.5f;
        c[1] = g_level_colour_ease_g;
    }
    if (b != g_level_colour_ease_b) {
        g_level_colour_ease_b += (b - g_level_colour_ease_b) * 0.5f;
        c[2] = g_level_colour_ease_b;
    }
    light_set_level_colour(c[0], c[1], c[2], 0U);
}

// effect_noop_check: P237. Does nothing: the asm only loads obj +0x3B and arg1 +0x1C and tests them (an empty if,
// probably a stripped debug check). No caller reads v0 (no jal callers; v0 is a load or garbage).
/* was func_151600E0 */
void obj_kind_check_stub(u8 *obj, u8 *arg1) {
}

/* was func_15160104 */
void obj_send_hit_6002d(u8 *arg0, s32 arg1) {
    obj_send_hit(arg0, 0x6002D, *(u16 *)(arg0 + 0x7A), -1);
}

u8 *scene_node_find_type2e(s32);

/* was func_15160134 */
void obj_send_hit_6002e(u8 *arg0, s32 arg1) {
    s32 pad; // fakematch: unused local moves v to sp18
    struct127 *v = NULL;
    u8 *t;
    s32 a3;
    t = scene_node_find_type2e(arg1);
    if (t != NULL) {
        v = *(struct127 **)(t + 0x98);
    }
    if (v != NULL) {
        a3 = v - g_objects;
    } else {
        a3 = -1;
    }
    obj_send_hit(arg0, 0x6002E, *(u16 *)(arg0 + 0x7A), a3);
}

/* was func_151601A4 */
void obj_send_hit_33(s32 arg0, s32 arg1) {
    obj_send_hit(arg0, 0x33, 0xC000, -1);
}

s32 player_hit_reaction(struct127 *, s32);
s32 approx_dist2_int(s16, s16, s32, s32);
s32 object_hit_effects(struct127 *, s32, s32, s32, s32, s32, s32, s32);
/* was func_151601D0 */
void obj_zone_kill(struct127 *arg0, u8 *arg1) {
    s32 pad[2]; // fakematch: frame
    f32 scale;
    f32 dist; // fakematch: assigned inside the comparison

    if (arg0->unk31C != NULL && arg0->unk31C->unk120 == 0) {
        if (*(u32 *)(arg1 + 0x1C) != 0) {
            scale = *(u32 *)(arg1 + 0x1C) * 0.01f;
            if (approx_dist2_int(*(s16 *)(arg1 + 0), *(s16 *)(arg1 + 4), arg0->x_position, arg0->z_position) < (dist = *(s16 *)(arg1 + 6) * scale - arg0->unkE4)) {
                return;
            }
        }
        obj_send_hit(arg0, 0x2F, 0, -1);
        object_hit_effects(arg0, 1, 1, 1, 1, 0, 0xFF, 1);
        obj_set_destroyed(arg0);
        player_hit_reaction(arg0, 6);
    }
}
