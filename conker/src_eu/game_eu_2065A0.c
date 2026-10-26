#include <ultra64.h>
#include "functions.h"
#include "variables.h"
void rumble_strength_by_distance(u8 *arg0, f32 *arg1);


extern u8 D_800BED64[];
/* was func_151D8D90 */
s32 rumble_mask_has_pak(u8 arg0) {
    u8 i;
    u8 t;
    for (i = 0; i < 4; i++) {
        if (arg0 & (1 << i)) {
            t = D_800843F0[i];
            if (t >= 4) {
                return 0;
            }
            if (D_800BED64[t] != 0) {
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
extern u8 D_800BEEE3;

/* was func_151D8E18 */
s32 rumble_request(structEU_151D8E18 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_v1;
    u8 *temp_v0;

    if (D_800E0B94 != 0) {
        return 0;
    }
    if (rumble_mask_has_pak(arg0->unk5) == 0) {
        return 0;
    }
    if ((g_game_paused != 0) || (D_800BEAC1 != 0) || (g_unpause_settle_frames != 0) || (D_800BEEE3 != 0)) {
        return 0;
    }
    var_s1 = 0;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
loop_10:
        if ((arg0->unk5 & (1 << var_s0)) && ((hud_lens_is_off(var_s0) == 0) || (screen_fade_alpha(var_s0) != 0))) {
            return 0;
        }
        var_s0 = (var_s1 + 1) & 0xFF;
        var_s1 = var_s0;
        if (D_80082FA0 < var_s0) {
            goto block_15;
        }
        goto loop_10;
    }
block_15:
    temp_v0 = node_alloc(0x3F, arg3, arg1 + 0x18, 1, (u8) (s32) arg2, 1U);
    if (temp_v0 == NULL) {
        return 0;
    }
    memcpy(temp_v0 + 0xE, arg0, 8);
    var_s0_2 = 0;
    var_v1 = 0;
    do {
        if ((*(u8 *)((u8 *)temp_v0 + 0x13)) & (1 << var_v1)) {
            rumble_start_strength(var_s0_2 & 0xFF, arg0->unk4);
        }
        var_v1 = (var_s0_2 + 1) & 0xFF;
        var_s0_2 = var_v1;
    } while (var_v1 < 4);
    (*(u8 *)((u8 *)temp_v0 + 0x16)) = (u8) arg0->unk4;
    return (s32) temp_v0;
}
/* P241: readable C for rumble_record_update (game_eu_2065A0, 64 insns). */
// rumble_effect_update: update of the kind-0x3F effect made by rumble_request (rumble for the players in the mask
// +0x13, strength +0x12 0..8). With flag +0xE bit 0 the s16 life +0x10 counts down by D_800BE9E4 and the effect ends
// (node_destroy, after the rest) once it is negative. Runs the D_80090060 handler of index +0x14 (-1 = none); when
// the strength changed since the last frame (+0x16), restarts the rumble of every player in the mask
// (rumble_stop, rumble_start_strength) and remembers the new strength. rumble_start_strength is declared in the rumble_request block above.
extern void (*D_80090060[])(u8 *);
void rumble_stop(u8);
/* was func_eu_151D8FD4 */
void rumble_record_update(u8 *fx) {
    u8 done = FALSE;
    u8 i;

    if (fx[0xE] & 1) {
        *(s16 *) (fx + 0x10) -= D_800BE9E4;
        if (*(s16 *) (fx + 0x10) < 0) {
            done = TRUE;
        }
    }
    if ((s8) fx[0x14] != -1) {
        D_80090060[(s8) fx[0x14]](fx);
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
    node_broadcast_types(&D_800AB6E0, 1, arg0, arg1);
}

extern s8 D_eu_800E0E30;

/* was func_151D9398 */
void rumble_records_clear_all(void) {
    D_eu_800E0E30 = 1;
    rumble_broadcast(0, 0x58U);
}
