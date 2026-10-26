#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1500EF20 */
void level_setup_scroll_fx_points(void) {
    struct102 *temp_v0;
    struct174 tmp;

    level_dl_add_texture_scroll(g_level_part_dls[0], g_tex_scroll_id_02b8, 1, -1, 0, 0, 0, -8);
    level_dl_add_texture_scroll(g_level_part_dls[1], g_tex_scroll_id_02b8, 1, -1, 0, 1, 0, -8);

    tmp.unk0 = g_scroll_fx_pt0_x;
    tmp.unk4 = g_scroll_fx_pt0_y;
    tmp.unkC = g_scroll_fx_pt0_z;
    tmp.unk8 = 400.0f;
    temp_v0 = (struct102 *)effect_node_create_nodraw((s16) ((random_int() % 0x33U) + 0x19), 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }

    tmp.unk0 = g_scroll_fx_pt1_x;
    tmp.unk4 = g_scroll_fx_pt1_y;
    tmp.unkC = g_scroll_fx_pt1_z;
    temp_v0 = (struct102 *)effect_node_create_nodraw((s16) ((random_int() % 0x33U) + 0x19), 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }

    tmp.unk4 = g_scroll_fx_pt2_y;
    temp_v0 = (struct102 *)effect_node_create_nodraw((s16) ((random_int() % 0x33U) + 0x19), 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }

    tmp.unk0 = g_scroll_fx_pt3_x;
    tmp.unk4 = g_scroll_fx_pt3_y;
    tmp.unkC = g_scroll_fx_pt3_z;
    temp_v0 = (struct102 *)effect_node_create_nodraw((s16) ((random_int() % 0x33U) + 0x19), 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }

    temp_v0 = (struct102 *)&g_level_light_colour;
    g_level_colour_ease_r = temp_v0->unk0;
    g_level_colour_ease_g = temp_v0->unk1;
    g_level_colour_ease_b = temp_v0->unk2;
    g_level_colour_cycle = 0.0f;
}
