#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800D33E0[];
extern f32 D_800D33F8[];
extern u8 D_800D340C[];
extern s32 D_800D3C60;
/* was func_1509E330 */
void rail_script_set_ease(s32 arg0, u8 *arg1) {
    if (*(s32 *)(arg1 + 4) == 1 && D_800D3C60 == 3) {
        D_800D33E0[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D33F8[*(s32 *)(arg1 + 8)] = (f32)*(s32 *)(arg1 + 0xC) * 0.000015258789f;
        D_800D340C[*(s32 *)(arg1 + 8)] = 1;
    }
}

/* was func_1509E3C4 */
void rail_script_nop(s32 arg0, s32 arg1) {
}

s32 rail_state_init(void);
s32 rail_rank_rivals(void);
s32 rail_racers_update(void);
s32 rail_assign_targets(void);
s32 rail_cmd_stub(s32);
s32 rail_racer_steer(s32, s32, s32, s32, s32, s32);
s32 rail_state_reset(void);
s32 rail_weapons_update(void);
s32 rail_pickup_slot_release(s32, s32);
s32 rail_pick_chase_target(void);
s32 rail_rival_pace(s32);
s32 rail_racer_take_over(s32, s32);
s32 rail_node_find_by_tag(s32);
s32 rail_node_position(s32, f32 *, f32 *, f32 *);
void rail_records_init(s32, s32, s32);
void rail_track_update(s32, s32, f32);
void rail_record_set_alt(s32, s32);
void rail_record_set_target_pos(s32, s32);
void rail_record_set_player(s32, s32);
s32 rail_record_start(s32, s32);
void mp_human_counter_clear(s32);
void hud_lens_start_zoom_in(s32);
void text_printf_at(s32, s32, u8, s32, ...);
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);
void math_spring_approach_angle(f32 *, f32, f32 *, f32, f32, f32);
extern char D_8009F6D0[]; /* "%d" */
extern s32 g_hud_clock_frames; /* was D_800D2870 */
extern u16 g_mp_game_flags; /* was D_8009015C */

// rail_script_command: script command handler (pointer table at ROM 0x22DB2C, next to event_query_rail) for the rail
// race / camera commands. cmd selects the action; args is the command record (s32 words, parameters from +0x8).
// Commands 4..15 and 22 return the callee's result, 25 / 26 return the eased value * 65536, the rest return 0.
/* was func_1509E3D4 */
s32 event_action_rail(s32 arg0, u32 cmd, u8 *args) {
    s32 *a = (s32 *) args;
    f32 x;
    f32 y;
    f32 z;
    s32 point;
    struct127 *obj;

    switch (cmd) {
    case 0:
        hud_lens_start_zoom_in(0);
        return 0;
    case 1:
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(0x96, 0x56, 1, (s32) D_8009F6D0, (a[2] + 59) / 60);
        g_mp_game_flags |= 0x80;
        break;
    case 2:
        g_hud_clock_frames = a[2];
        break;
    case 3:
        hud_clock_set_enabled(a[2]);
        return 0;
    case 4:
        return rail_state_init();
    case 5:
        return rail_rank_rivals();
    case 6:
        return rail_racers_update();
    case 7:
        return rail_assign_targets();
    case 8:
        return rail_cmd_stub(a[2]);
    case 9:
        return rail_racer_steer(a[2], a[3], a[4], a[5], 0, 0);
    case 10:
        return rail_state_reset();
    case 11:
        return rail_weapons_update();
    case 12:
        return rail_pickup_slot_release(a[2], a[3]);
    case 13:
        return rail_pick_chase_target();
    case 14:
        return rail_rival_pace(a[2]);
    case 15:
        return rail_racer_take_over(a[2], a[3]);
    case 16:
        point = rail_node_find_by_tag(a[2]);
        if (point != 0xFF) {
            rail_node_position(point, &x, &y, &z);
            rail_event_add(x, y, z, (f32) a[3]);
            return 0;
        }
        break;
    case 17:
        rail_records_init(a[2], a[3], a[4]);
        return 0;
    case 18:
        rail_track_update(a[2], a[3], 0.1f);
        return 0;
    case 19:
        rail_record_set_alt(a[2], a[3]);
        return 0;
    case 20:
        rail_record_set_target_pos(a[2], a[3]);
        return 0;
    case 21:
        rail_record_set_player(a[2], a[3]);
        return 0;
    case 22:
        return rail_record_start(a[2], a[3]);
    case 23:
        mp_human_counter_clear(a[2]);
        return 0;
    case 24:
        obj = obj_find_by_setup_id(args[0xB]);
        if (obj != NULL) {
            obj_remove(obj, 0);
        }
        break;
    case 25:
        math_spring_approach(&D_800D33F8[a[2]], a[3] * (1.0f / 65536.0f), &D_800D33E0[a[2]], a[4] * (1.0f / 65536.0f),
                      a[5] * (1.0f / 65536.0f), *(f32 *) ((u8 *) g_player_views + 0x7B4));
        return (s32) (D_800D33F8[a[2]] * 65536.0f);
    case 26:
        math_spring_approach_angle(&D_800D33F8[a[2]], a[3] * (1.0f / 65536.0f), &D_800D33E0[a[2]], a[4] * (1.0f / 65536.0f),
                      a[5] * (1.0f / 65536.0f), *(f32 *) ((u8 *) g_player_views + 0x7B4));
        return (s32) (D_800D33F8[a[2]] * 65536.0f);
    }
    return 0;
}

s32 rail_record_get_pos(s32);
s32 rail_record_get_progress(s32);
s32 rail_record_get_speed(s32);
s32 rail_record_get_lap(s32);
s32 player_place_gap(s32, s32);
s32 rail_first_record_idle(void);
s32 mode_pick_mid_range_object(s32);
s32 mp_human_counter_get(s32);
s32 rail_pair_rivals(s32, s32);
s32 player_next_active();
s32 rail_human_cursor_next(void);
s32 rail_weapon_range(s32);
f32 math_angle_offset_scaled(s32, s32);
extern u16 g_mp_game_flags; /* was D_8009015C */
extern s32 D_800CCA1C;
extern s8 D_800E1000;

/* was func_1509E7EC */
s32 event_query_rail(s32 arg0, u32 arg1, u8 *arg2) {
    s32 *var_v0;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_v1;
    struct127 *temp_v0;
    struct127 *temp_v0_2;

    switch (arg1) {
    case 0:
        return (s32) math_angle_offset_scaled((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 1:
        temp_v1 = (*(s32 *)((u8 *)arg2 + 8)) - (*(s32 *)((u8 *)arg2 + 0x10));
        temp_a0 = (*(s32 *)((u8 *)arg2 + 0xC)) - (*(s32 *)((u8 *)arg2 + 0x14));
        return (s32) sqrtf((f32) ((temp_v1 * temp_v1) + (temp_a0 * temp_a0)));
    case 2:
        return rail_human_cursor_next();
    case 3:
        return player_next_active();
    case 4:
        return rail_pair_rivals((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 5:
        return (s32) D_800E1000;
    case 6:
        return mode_pick_mid_range_object((*(s32 *)((u8 *)arg2 + 8)));
    case 7:
        return rail_weapon_range((*(s32 *)((u8 *)arg2 + 8)));
    default:
block_45:
        return 0;
    case 9:
        return rail_record_get_pos((*(s32 *)((u8 *)arg2 + 8)));
    case 10:
        return rail_record_get_progress((*(s32 *)((u8 *)arg2 + 8)));
    case 11:
        return rail_record_get_speed((*(s32 *)((u8 *)arg2 + 8)));
    case 12:
        return rail_record_get_lap((*(s32 *)((u8 *)arg2 + 8)));
    case 13:
        return player_place_gap((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
    case 14:
        return rail_first_record_idle();
    case 15:
        return g_mp_game_flags & 0x40;
    case 16:
        return (s32) g_settings[(*(s32 *)((u8 *)arg2 + 8))];
    case 17:
        return mp_human_counter_get((*(s32 *)((u8 *)arg2 + 8)));
    case 21:
    case 22:
        return (s32) (D_800D33F8[(*(s32 *)((u8 *)arg2 + 8))] * 65536.0f);
    case 18:
        temp_v0 = obj_find_by_setup_id((*(u8 *)((u8 *)arg2 + 0xB)));
        if (temp_v0 != NULL) {
            return ((s32) temp_v0->x_position << 0x10) | ((s32) temp_v0->z_position & 0xFFFF);
        }
        goto block_45;
    case 19:
        temp_v0_2 = obj_find_by_setup_id((*(u8 *)((u8 *)arg2 + 0xB)));
        if (temp_v0_2 != NULL) {
            return (s32) (s16) (s32) temp_v0_2->y_position;
        }
        goto block_45;
    case 20:
        var_v1 = 0;
        var_v0 = &D_800CCA1C;
        if ((g_objects->interaction_state != 0) && (*g_obj_tab_id == (*(s32 *)((u8 *)arg2 + 8)))) {
            var_v1 = 1;
        }
        do {
            if (((*(s32 *)((u8 *)var_v0 + 0)) != 0) && ((*(u8 *)((u8 *)var_v0 + 4)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x32C)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x330)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x658)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x65C)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            if (((*(s32 *)((u8 *)var_v0 + 0x984)) != 0) && ((*(u8 *)((u8 *)var_v0 + 0x988)) == (*(s32 *)((u8 *)arg2 + 8)))) {
                var_v1 += 1;
            }
            var_v0 = (s32 *) ((u8 *) var_v0 + 0xCB0);
        } while (var_v0 != &g_obj_scratch_rec);
        return var_v1;
    }
}