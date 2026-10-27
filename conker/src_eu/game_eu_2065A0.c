#include <ultra64.h>
#include "functions.h"
#include "variables.h"
void rumble_strength_by_distance(u8 *arg0, f32 *arg1);


extern u8 g_rumble_pak_present[]; /* was D_800BED64 */
/* was func_151D8D90 */
s32 rumble_mask_has_pak(u8 arg0) {
    u8 i;
    u8 t;
    for (i = 0; i < 4; i++) {
        if (arg0 & (1 << i)) {
            t = g_player_pad_map[i];
            if (t >= 4) {
                return 0;
            }
            if (g_rumble_pak_present[t] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

s32 rumble_start_strength(s32, u8);
s32 screen_fade_alpha(s32);
s32 hud_lens_is_off(s32);
s32 memcpy(u8 *, structEU_151D8E18 *, s32);
extern u8 g_unpause_settle_frames; /* was D_800BEEE2 */
extern u8 g_rumble_stop_request; /* was D_800BEEE3 */

/* was func_151D8E18 */
s32 rumble_request(structEU_151D8E18 *req /* was arg0 */, s32 extra_size /* was arg1 */, u8 node_arg /* was arg2 */,
                   s32 owner /* was arg3 */) {
    s32 p; /* was var_s0 */
    s32 player; /* was var_s0_2 */
    s32 next; /* was var_s1 */
    s32 next_player; /* was var_v1 */
    u8 *fx; /* was temp_v0 */

    if (g_game_mode != 0) {
        return 0;
    }
    if (rumble_mask_has_pak(req->player_mask) == 0) {
        return 0;
    }
    if ((g_game_paused != 0) || (g_pause_open != 0) || (g_unpause_settle_frames != 0) || (g_rumble_stop_request != 0)) {
        return 0;
    }
    next = 0;
    p = 0;
    if (g_last_player_index >= 0) {
loop_10:
        if ((req->player_mask & (1 << p)) && ((hud_lens_is_off(p) == 0) || (screen_fade_alpha(p) != 0))) {
            return 0;
        }
        p = (next + 1) & 0xFF;
        next = p;
        if (g_last_player_index < p) {
            goto block_15;
        }
        goto loop_10;
    }
block_15:
    fx = node_alloc(0x3F, owner, extra_size + 0x18, 1, (u8) (s32) node_arg, 1U);
    if (fx == NULL) {
        return 0;
    }
    memcpy(fx + 0xE, req, 8);
    player = 0;
    next_player = 0;
    do {
        if ((*(u8 *)((u8 *)fx + 0x13)) & (1 << next_player)) {
            rumble_start_strength(player & 0xFF, req->strength);
        }
        next_player = (player + 1) & 0xFF;
        player = next_player;
    } while (next_player < 4);
    (*(u8 *)((u8 *)fx + 0x16)) = (u8) req->strength;
    return (s32) fx;
}
/* P241: readable C for rumble_record_update (game_eu_2065A0, 64 insns). */
// rumble_effect_update: update of the kind-0x3F effect made by rumble_request (rumble for the players in the mask
// +0x13, strength +0x12 0..8). With flag +0xE bit 0 the s16 life +0x10 counts down by g_frame_ticks and the effect ends
// (node_destroy, after the rest) once it is negative. Runs the g_rumble_rec_update_fns handler of index +0x14 (-1 = none); when
// the strength changed since the last frame (+0x16), restarts the rumble of every player in the mask
// (rumble_stop, rumble_start_strength) and remembers the new strength. rumble_start_strength is declared in the rumble_request block above.
extern void (*g_rumble_rec_update_fns[])(u8 *); /* was D_80090060 */
void rumble_stop(u8);
/* was func_eu_151D8FD4 */
void rumble_record_update(u8 *fx) {
    u8 done = FALSE;
    u8 i;

    if (fx[0xE] & 1) {
        *(s16 *) (fx + 0x10) -= g_frame_ticks;
        if (*(s16 *) (fx + 0x10) < 0) {
            done = TRUE;
        }
    }
    if ((s8) fx[0x14] != -1) {
        g_rumble_rec_update_fns[(s8) fx[0x14]](fx);
    }
    if (fx[0x12] != fx[0x16]) {
        for (i = 0; i < 4; i++) {
            if (fx[0x13] & (1 << i)) {
                rumble_stop(i);
                rumble_start_strength(i, fx[0x12]);
            }
        }
        fx[0x16] = fx[0x12];
    }
    if (done) {
        node_destroy((struct102 *) fx);
    }
}

void rumble_stop(u8);
/* was func_151D90D4 */
void rumble_stop_players(u8 *arg0) {
    u8 i;
    for (i = 0; i < 4; i++) {
        if (arg0[0x13] & (1 << i)) {
            rumble_stop(i);
        }
    }
}

/* was func_151D9138 */
void rumble_die_retire(void *arg0) {
    rumble_stop_players(arg0);
    node_retire(arg0);
}

/* was func_151D9164 */
void rumble_die_free(void *arg0) {
    rumble_stop_players(arg0);
    node_unlink_free(arg0);
}

/* was func_151D9190 */
void rumble_falloff_update(u8 *arg0) {
    rumble_strength_by_distance(arg0, (f32 *)(arg0 + 0x18));
}

f32 vec3_length(f32 *, f32 *);

/* was func_151D91B0 */
void rumble_strength_by_distance(u8 *arg0, f32 *arg1) {
    f32 *p;
    f32 d[3];
    f32 dist;
    f32 lo;
    f32 v;

    p = camera_get_pos(((u8 *)arg1)[0x18]);
    d[0] = arg1[0] - p[0];
    d[1] = arg1[1] - p[1];
    d[2] = arg1[2] - p[2];
    dist = vec3_length(d, arg1);
    lo = arg1[3];
    if (dist < lo) {
        v = 1.0f;
    } else if ((lo + arg1[4]) < (0, dist)) { // fakematch: comma orders the add.s
        v = 0.0f;
    } else {
        v = 1.0f - (arg1[5] * (0, dist - lo)); // fakematch: comma swaps the f-regs
    }
    arg0[0x12] = v * 8.0f;
}

/* was func_151D930C */
void rumble_on_message(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x58) {
        node_destroy(arg0);
    } else if (arg2 == 0x47) {
        node_destroy(arg0);
    }
}

/* was func_151D9364 */
void rumble_broadcast(s32 arg0, u8 arg1) {
    node_broadcast_types(&g_rumble_bcast_types, 1, arg0, arg1);
}

extern s8 g_rumble_clear_request; /* was D_eu_800E0E30 */

/* was func_151D9398 */
void rumble_records_clear_all(void) {
    g_rumble_clear_request = 1;
    rumble_broadcast(0, 0x58U);
}
