#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void cutscene_focus_on_object(s32 arg0, s32 arg1);
void cutscene_set_focus_point2(s16, s16, s16, f32);
void cutscene_set_focus_point(s16, s16, s16, f32);


void cutscene_scene_load(s32, s32, s32, s32, s32);
extern s8 g_cutscene_next_scene; /* was D_800C39E2 */
extern s8 g_cutscene_return_level; /* was D_800C39E3 */
extern s8 g_cutscene_chain_skip; /* was D_800C40B9 */
extern s8 g_cutscene_no_skip; /* was D_800C40BC */
extern s32 g_event_arg_count; /* was D_800D3C60 */

// event_action_scene: event-script scene actions (ids 0x1xxx). P176: s32 like the handler table; cases 1 / 3 / 4
// (start a scene) return 1, or 0 while a scene is playing (g_cutscene_slot_state), as the asm does. The asm leaves v0
// undefined in cases 2 / 5 / 6 / other (a callee's result or g_event_arg_count): 0 here.
/* was func_1509C850 */
s32 event_action_scene(s32 arg0, s32 arg1, u8 *arg2) {
    s32 sp3C;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v1;

    switch (arg1) {
    case 1:
        if (g_cutscene_slot_state == 0) {
            sp3C = g_level_id;
            if (g_event_arg_count == 6) {
                cutscene_set_focus_point((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            } else if (g_event_arg_count == 3) {
                temp_a0 = (*(s32 *)((u8 *)arg2 + 8));
                if ((temp_a0 & 0xF000) == 0x2000) {
                    cutscene_focus_on_object(temp_a0, 0);
                } else {
                    sp3C = temp_a0;
                }
            }
            cutscene_scene_load(sp3C, arg0, 0, 0, 0);
            return 1;
        }
        return 0;
    case 4:
        if (g_cutscene_slot_state == 0) {
            if (g_event_arg_count == 6) {
                cutscene_set_focus_point((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            }
            temp_s0 = g_level_id;
            g_level_id = 0x25;
            cutscene_scene_load(0x25, arg0, 0, 0, 0);
            g_level_id = temp_s0;
            return 1;
        }
        return 0;
    case 3:
        if (g_cutscene_slot_state == 0) {
            sp30 = (*(s32 *)((u8 *)arg2 + 8));
            temp_v1 = (*(s32 *)((u8 *)arg2 + 0xC));
            sp34 = g_level_id;
            if (g_event_arg_count == 8) {
                sp2C = temp_v1;
                cutscene_set_focus_point((*(s16 *)((u8 *)arg2 + 0x12)), (*(s16 *)((u8 *)arg2 + 0x16)), (*(s16 *)((u8 *)arg2 + 0x1A)), (f32) (*(s32 *)((u8 *)arg2 + 0x1C)) * 0.000015258789f);
            } else if (g_event_arg_count == 5) {
                sp34 = (*(s32 *)((u8 *)arg2 + 0x10));
            }
            cutscene_scene_load(sp34, arg0, 0, sp30, temp_v1);
            return 1;
        }
        return 0;
    case 2:
        g_cutscene_next_scene = arg0 + 1;
        g_cutscene_return_level = (s8) g_level_id;
        g_cutscene_chain_skip = 1;
        if (g_event_arg_count == 6) {
            cutscene_set_focus_point2((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        if (g_event_arg_count == 3) {
            temp_a0_2 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_a0_2 & 0xF000) == 0x2000) {
                cutscene_focus_on_object(temp_a0_2, 1);
                return 0;
            }
            g_cutscene_return_level = (s8) temp_a0_2;
            return 0;
        }
    default:
        return 0;
    case 5:
        g_cutscene_next_scene = arg0 + 1;
        g_cutscene_return_level = 0x25;
        if (g_event_arg_count == 6) {
            cutscene_set_focus_point2((*(s16 *)((u8 *)arg2 + 0xA)), (*(s16 *)((u8 *)arg2 + 0xE)), (*(s16 *)((u8 *)arg2 + 0x12)), (f32) (*(s32 *)((u8 *)arg2 + 0x14)) * 0.000015258789f);
            return 0;
        }
        break;
    case 6:
        g_cutscene_no_skip = 1;
        break;
    }
    return 0;
}
extern u8 g_cutscene_skipped; /* was D_800C3A92 */
extern u8 g_cutscene_scene_id; /* was D_800C40B8 */

// event_query_scene: event-script scene queries (ids 0x1xxx; arg0 = scene, arg1 = query). P176 (browser P174):
// returns the asm's per-case answer (jtbl_8009E828); the m2c body was void and the s32 handler table read 0.
// 1: scene arg0 no longer playing (0 while g_cutscene_pending is set), 2: scene arg0 playing (g_cutscene_scene_id), 3 / 6: cutscene
// arg0 playing (g_cutscene_scene), 4: no scene playing, 5: g_cutscene_skipped (debug skip). Other queries: the asm leaves v0
// unchanged (0 here).
/* was func_1509CBD8 */
s32 event_query_scene(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        if (g_cutscene_pending != 0) {
            return 0;
        }
        if (g_cutscene_slot_state == 0) {
            return 1;
        }
        if (arg0 == g_cutscene_scene_id) {
            return 0;
        }
        return 1;
    case 2:
        if (g_cutscene_slot_state == 1 && arg0 == g_cutscene_scene_id) {
            return 1;
        }
        return 0;
    case 3:
        if (g_cutscene_slot_state == 1 && arg0 == g_cutscene_scene) {
            return 1;
        }
        return 0;
    case 4:
        return g_cutscene_slot_state != 1;
    case 5:
        return g_cutscene_skipped;
    case 6:
        if (g_cutscene_slot_state == 1 && arg0 == g_cutscene_scene) {
            return 1;
        }
        return 0;
    }
    return 0;
}
void cutscene_set_focus_point(s16, s16, s16, f32);
void cutscene_set_focus_point2(s16, s16, s16, f32);

/* was func_1509CD0C */
void cutscene_focus_on_object(s32 arg0, s32 arg1) {
    f32 var_f0;
    struct127 *temp_v0;

    temp_v0 = obj_find_by_spawn(arg0 & 0xFFF);
    if (temp_v0 != NULL) {
        if (g_player_views->unk2C & 0x100) {
            var_f0 = (*(f32 *)((u8 *)g_player_views + 0x760));
        } else {
            var_f0 = g_player_views->unk37C;
        }
        if (arg1 != 0) {
            cutscene_set_focus_point2((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
            return;
        }
        cutscene_set_focus_point((s16) (s32) temp_v0->x_position, (s16) (s32) temp_v0->y_position, (s16) (s32) temp_v0->z_position, var_f0 + 180.0f);
    }
}