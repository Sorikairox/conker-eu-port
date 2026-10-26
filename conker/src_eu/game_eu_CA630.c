#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A6440[];


/* was func_1509CE20 */
s32 event_table_get_block(s32 arg0) {
    return D_800877D0[arg0].unk0;
}

/* was func_1509CE40 */
u16 event_table_get_u16_8(s32 arg0) {
    return D_800877D0[arg0].unk8;
}

/* was func_1509CE60 */
s32 event_table_get_id_field(s32 arg0) {
    return *(u16 *)((u8 *)&D_800877D0[arg0] + 0xA) & 0xFFF;
}

/* was func_1509CE88 */
s32 event_table_get_word4(s32 arg0) {
    return D_800877D0[arg0].unk4;
}

/* was func_1509CEA8 */
s32 event_table_find_by_word4(s32 arg0)
{
  s32 var_v1;
  struct_eu_800877D0 *var_v0;
  var_v1 = 0;
 var_v0 = D_800877D0; loop_1: if ((var_v0->unk0 != 0) && (arg0 == ((var_v0->unk4 & 0x1FFFFFFF) + 1))) { return var_v1;
  }

  if (((*((s32 *) (((u8 *) var_v0) + 0x14))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x18))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 1;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x28))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x2C))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 2;
  }
  if (((*((s32 *) (((u8 *) var_v0) + 0x3C))) != 0) && (arg0 == (((*((s32 *) (((u8 *) var_v0) + 0x40))) & 0x1FFFFFFF) + 1)))
  {
    return var_v1 + 3;
  }
  var_v1 += 4;
  var_v0 += 4;
  if (var_v1 == 0xCC)
  {
    return 0xCC;
  }
  goto loop_1;
}

/* was func_1509CF78 */
s32 event_table_count(void) {
    s32 n = 0;
    s32 i;
    for (i = 0; i < 204; i++) {
        if (D_800877D0[i].unk0 != 0) {
            n++;
        }
    }
    return n;
}

/* event_prereqs_met: D_800877D0[id] +0xC is a 0xFFFF-terminated list of event ids. The event may start when every
 * prerequisite has its save bit set (bit field at g_save_progress_bits) and its own prerequisites hold. Empty list: 1. */
/* was func_1509CBD4 */
s32 event_prereqs_met(s32 id) {
    u16 *p = *(u16 **) ((u8 *) D_800877D0 + id * 0x14 + 0xC);
    u16 e;
    s32 ok;

    e = *p;
    while (e != 0xFFFF) {
        ok = event_prereqs_met(e);
        e = *p;
        if (!(((u8 *) g_save_progress_bits)[e >> 3] & (1 << (e & 7))) || ok == 0) {
            return 0;
        }
        p++;
        e = *p;
    }
    return 1;
}

void event_unlock_chain_rec(s32 arg0);

/* was func_1509D0A4 */
void event_unlock_chain(s32 arg0) {
    event_unlock_chain_rec(arg0);
}

void event_list_unlock(s32 listp, void (*cb)(s32), s32 arg2);
extern s32 D_800877DC;

/* was func_1509D0C4 */
void event_unlock_chain_rec(s32 arg0) {
    event_list_unlock(*(s32 *)((u8 *)&D_800877DC + (arg0 * 0x14)), event_unlock_chain_rec, arg0);
}

extern u16 *D_800877E0[][5];

/* was func_1509D104 */
s32 save_unlocks_apply(s32 arg0) {
    s32 cnt;
    u16 *p;
    s32 *new_var2; // fakematch: permuter temp
    u16 *new_var; // fakematch: permuter temp
    u8 *q; // fakematch: permuter temp (dead)

    p = D_800877E0[arg0][0];
    cnt = 0;
    if (*p != 0xFFFF) {
        do {
            ((u8 *)g_save_progress_bits)[*p >> 3] |= 1 << (*p & 7);
            new_var = p;
            q = *new_var + (u8 *)(new_var2 = &g_event_states);
            if (*((u8 *)&g_event_states + *new_var) != 3) {
                *((u8 *)new_var2 + *new_var) = 3;
                event_unlock_chain_rec(*new_var);
                cnt++;
            }
            p++;
        } while (*p != 0xFFFF);
    }
    return cnt;
}

// save_unlocks_propagate: unlocks arg0's list (save_unlocks_apply), then keeps expanding every entry of the state bytes
// g_event_states (0xCC of them) that is in state 3 until a whole pass unlocks nothing new. The asm returns no value.
/* was func_1509D1EC */
void save_unlocks_propagate(s32 arg0) {
    s32 added;
    s32 i;

    save_unlocks_apply(arg0);
    do {
        added = 0;
        for (i = 0; i < 0xCC; i++) {
            if (((u8 *) &g_event_states)[i] == 3) {
                added += save_unlocks_apply(i);
            }
        }
    } while (added != 0);
}

// event_list_unlock: for each id of the 0xFFFF-terminated u16 list: calls cb(id) (event_unlock_chain_rec recurses into the
// event's own list), sets its state byte g_event_states[id] to 3 and its save bit in g_save_progress_bits. arg2 is unused; the
// asm returns no value.
/* was func_1509D274 */
void event_list_unlock(s32 listp, void (*cb)(s32), s32 arg2) {
    u16 *list = (u16 *)listp;

    while (*list != 0xFFFF) {
        cb(*list);
        ((u8 *)&g_event_states)[*list] = 3;
        ((u8 *)g_save_progress_bits)[*list >> 3] |= 1 << (*list & 7);
        list++;
    }
}

/* P132: the save-route table asset_load_with_subfiles loads (asset 3, 8-byte records): record 0's info word gets the record
 * count - 1; record i >= 1 points at its own block, a list of (offset, flags) pairs ended by flag 0x80000000. */
typedef struct SaveRouteRec {
    u32 *data;
    u32 info;
} SaveRouteRec;
s32 asset_load_with_subfiles(s32 *, s32, s32 *, s32, ...);

// save_route_table_load: loads the save-route table into D_800D33D0 (arg0 selects it), stores the number of routes
// (records - 1) in record 0 and *count, and relocates each route block: every pair's first word gets the block
// address added (up to the pair flagged 0x80000000; the flags are cleared), and the block's word 3 becomes
// (word 3 & 0x0FFFFFFF) >> 1. Returns 0 (and *count = 0) when nothing was loaded, else 1.
/* was func_1509D338 */
s32 save_route_table_load(s32 arg0, s32 *count) {
    u32 n;
    u32 i;
    u32 *p;
    s32 last;
    SaveRouteRec *tbl;

    n = 0;
    D_800D33D0 = asset_load_with_subfiles(NULL, 0, (s32 *) &n, 3, 8, 0, arg0);
    tbl = (SaveRouteRec *) D_800D33D0;
    if (tbl == NULL) {
        *count = 0;
        return 0;
    }
    tbl[0].info = n - 1;
    *count = n - 1;
    for (i = 1; i < n; i++) {
        p = tbl[i].data;
        last = 0;
        do {
            p[0] += (u32) tbl[i].data;
            if (p[1] & 0x80000000) {
                last = 1;
            }
            p[1] &= 0x0FFFFFFF;
            p += 2;
        } while (!last);
        p = tbl[i].data;
        p[3] = (p[3] & 0x0FFFFFFF) >> 1;
    }
    return 1;
}

// the definition is void (asm: v0 is not a result); one signature for wasm
void heap_free(s32);
/* was func_1509D464 */
void save_route_table_free(void) {
    s32 r;
    if (D_800D33D0 != 0) {
        r = D_800D33D0;
        heap_free(r);
        D_800D33D0 = 0;
    }
}

// save_route_check: route arg1 of the table D_800D33D0 (record arg1 + 1, relocated by save_route_table_load): writes the
// first id of its requirement list through outA and the id its word 0 points at through outB (0xBF / 0 when there
// is no table or no route; NULL out-pointers are skipped) and returns 1 when every id of the list (word 2, count
// word 3, s16 each) has its bit set in g_save_progress_bits, else 0. arg0 is unused.
/* was func_1509D49C */
s32 save_route_check(s8 arg0, u8 arg1, s32 *outA, s32 *outB) {
    SaveRouteRec *rec;
    u32 *route;
    s16 *ids;
    u32 i;
    u32 n;
    s32 id;

    rec = &((SaveRouteRec *) D_800D33D0)[arg1];
    if (D_800D33D0 == 0 || rec[1].data == NULL) {
        if (outA != NULL) {
            *outA = 0xBF;
        }
        if (outB != NULL) {
            *outB = 0;
        }
        return 0;
    }
    if (outA != NULL) {
        *outA = *(s16 *) rec[1].data[2];
    }
    if (outB != NULL) {
        *outB = *(s16 *) rec[1].data[0];
    }
    route = rec[1].data;
    n = route[3];
    if (n == 0) {
        return 1;
    }
    ids = (s16 *) route[2];
    for (i = 0; i < n; i++) {
        id = ids[i];
        if (!(((u8 *) g_save_progress_bits)[id >> 3] & (1 << (id & 7)))) {
            return 0;
        }
    }
    return 1;
}

extern u8 D_8009F4A0;            /* the one-entry effect table of command 0x18 */
extern s8 D_800D9D40;
void light_ctrl_broadcast(u8, u8, s32);
void music_post_event_request(u32, s32);
s32 collision_floor_probe(void *, u16, f32, void *);
struct260 *obj_electrify_fx_spawn(u8 *, s16, u8, s32);
void blast_debris_and_smoke(u8, s32);
void twin_particle_emitters_spawn(s32);
void debris_burst_destroyed_object(struct127 *, s32, s32);
void big_explosion_spawn(f32 *, u8, s32);
void water_effect_start_once(void);
struct260 *fx_model_emitter_spawn(u8, u8, s32);
s32 zap_bolt_spawn_between(s32, s32, s32, s32, s32, s32, s32, s32);
s32 zap_bolt_spawn_follow(s32, s32, s32, s32, s32, f32);
s32 zap_bolt_spawn_with_sound(s32, s32, s32, s32, s32, s32, s32, s32, f32);
void fx_scripted_blast(s32, u8, s32);
void storm_lightning_strike(void);
void obj_hit_green_tint(s32, u8, s32);
void *glow_pair_spawn(struct127 *);
void arc_bolts_spawn_once(u8, s32);
void level_cue_switch_on(void);
void level_cue_switch_off(void);
void view_spots_flash_event(void);
void bound_cloud_spawn(struct127 *, u8, s32);
void obj_impact_burst(struct127 *, u8, s32);
s32 object_hit_effects(u8 *, u8, u8, u8, u8, u8, u8, s32);
void head_icon_show_timed(s32, s32, f32);
struct225 *light_create_obj_pulse(u8, u8, s32);
void rain_request(s32);
s32 bone_sparks_attach_preset(s32, u8, s16, s8, s8, s8, u8, s32, u8, s32);
void impact_effects_spawn(u8 *, f32 *, f32 *, u8, u8, s32);
void explosion_ground_effects(u8 *, s32, u8, s32, s32);
void spout_broadcast_start(s32);
void scroll_banner_spawn(s16);
/* event_effect_command: handler 14 of the event VM's native table D_800887C0 (id = the command word without its
 * nibble, args = the operands, args[1] mostly an object id resolved with obj_find_by_spawn & 0xFFF). Starts effects /
 * spawns: 0 obj_electrify_fx_spawn, 1 twin_particle_emitters_spawn (returns 1), 2 sets D_800D9D40, 3 rain_request, 4 / 5 / 6 spawn through
 * zap_bolt_spawn_between / zap_bolt_spawn_follow (at an object) / zap_bolt_spawn_with_sound (at the player) and return the handle as
 * (h << 6) | 0xE004, 7 big_explosion_spawn at a point (args[1] == 999) or fx_scripted_blast, 0x10 / 0x16 light_ctrl_broadcast
 * pairs, 0x18 bone_sparks_attach_preset on character args[1], 0x21 explosion_ground_effects 50 above an object, 0x22 impact_effects_spawn at the
 * ground below (args[1], args[2]) found by collision_floor_probe, 0x24 char_fx_attach (0x1B), others single calls. Returns 0
 * unless noted. */
/* was func_1509D590 */
s32 event_effect_command(s32 id, s32 *args, s32 *operand) {
    struct {
        u8 pad[0x14];
        s32 u14;
        s8 u18;
        s8 u19;
        s32 u1C;
    } hit;
    f32 pos[3];
    f32 dir[3];
    f32 ground;
    u8 tbl[1];
    struct127 *obj;
    s32 ret = 0;

    switch ((u32) id) {
    case 0x00:
        obj_electrify_fx_spawn((u8 *) obj_find_by_spawn(args[1] & 0xFFF), (s16) args[2], 0xFF, 1);
        break;
    case 0x01:
        twin_particle_emitters_spawn(args[1]);
        return 1;
    case 0x02:
        D_800D9D40 = 1;
        break;
    case 0x03:
        rain_request(args[1]);
        break;
    case 0x04:
        ret = zap_bolt_spawn_between(args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
        if (ret != 0) {
            ret = (ret << 6) | 0xE004;
        }
        break;
    case 0x05:
        obj = obj_find_by_spawn(args[4] & 0xFFF);
        if (obj != NULL) {
            ret = zap_bolt_spawn_follow(args[1], args[2], args[3], (s32) obj, args[5], (f32) args[7]);
            if (ret != 0) {
                ret = (ret << 6) | 0xE004;
            }
        }
        break;
    case 0x06:
        ret = zap_bolt_spawn_with_sound(args[1], args[2], args[3], args[4], args[5], args[6], (s32) g_objects, args[7],
                            (f32) args[8]);
        if (ret != 0) {
            ret = (ret << 6) | 0xE004;
        }
        break;
    case 0x07:
        if (args[1] == 999) {
            pos[0] = (f32) args[2];
            pos[1] = (f32) args[3];
            pos[2] = (f32) args[4];
            big_explosion_spawn(pos, 0xFF, 1);
        } else {
            fx_scripted_blast(args[1] & 0xFF, 0xFF, 1);
        }
        break;
    case 0x0F:
        storm_lightning_strike();
        break;
    case 0x10:
        music_post_event_request(0x10, 0);
        light_ctrl_broadcast(0x16, 0x1F, 0);
        break;
    case 0x12:
        spout_broadcast_start(args[1]);
        break;
    case 0x13:
        scroll_banner_spawn((s16) args[1]);
        break;
    case 0x14:
        fx_model_emitter_spawn((u8) args[1], 0xFF, 1);
        break;
    case 0x16:
        light_ctrl_broadcast(0x23, 0x27, 0);
        light_ctrl_broadcast(0x24, 0x27, 0);
        break;
    case 0x17:
        light_create_obj_pulse((u8) args[1], 0xFF, 1);
        break;
    case 0x18:
        tbl[0] = D_8009F4A0;
        bone_sparks_attach_preset((s32) obj_find_by_setup_id((u8) args[1]), tbl[args[2]], (s16) args[3], -1, -1, -1, 0, 0, 0xFF, 1);
        break;
    case 0x1B:
        view_spots_flash_event();
        break;
    case 0x20:
        debris_burst_destroyed_object(obj_find_by_spawn(args[1] & 0xFFF), 0xFF, 1);
        break;
    case 0x21:
        obj = obj_find_by_spawn(args[1] & 0xFFF);
        if (obj != NULL) {
            pos[0] = obj->x_position;
            pos[1] = obj->y_position + 50.0f;
            pos[2] = obj->z_position;
            explosion_ground_effects((u8 *) pos, (s32) obj, 1, 0xFF, 1);
        }
        break;
    case 0x22:
        ground = -10000.0f;
        hit.u14 = 0;
        hit.u18 = 0;
        hit.u19 = 0;
        hit.u1C = 0;
        pos[0] = (f32) args[1];
        pos[1] = 20000.0f;
        pos[2] = (f32) args[2];
        if (collision_floor_probe(pos, 0, -10000.0f, &ground) != 0) {
            pos[1] = ground;
            dir[0] = 0.0f;
            dir[1] = -1.0f;
            dir[2] = 0.0f;
            impact_effects_spawn((u8 *) &hit, pos, dir, 1, 0xFF, 1);
        }
        break;
    case 0x23:
        object_hit_effects((u8 *) obj_find_by_spawn(args[1] & 0xFFF), 1, 1, 1, 1, 0, 0xFF, 1);
        break;
    case 0x24:
        obj = obj_find_by_spawn(args[1] & 0xFFF);
        if (obj != NULL) {
            char_fx_attach(glow_pair_spawn(obj), obj, 0x1B);
        }
        break;
    case 0x25:
        head_icon_show_timed(args[1] & 0xFFF, 0x78, (f32) args[2]);
        break;
    case 0x2A:
        obj = obj_find_by_spawn(args[1] & 0xFFF);
        if (obj != NULL) {
            bound_cloud_spawn(obj, 0xFF, 1);
        }
        break;
    case 0x2B:
        water_effect_start_once();
        break;
    case 0x2C:
        level_cue_switch_off();
        break;
    case 0x2E:
        obj = obj_find_by_spawn(args[1] & 0xFFF);
        if (obj != NULL) {
            obj_hit_green_tint((s32) obj, 0xFF, 1);
        }
        break;
    case 0x2F:
        obj = obj_find_by_spawn(args[1] & 0xFFF);
        if (obj != NULL) {
            obj_impact_burst(obj, 0xFF, 1);
        }
        break;
    case 0x30:
        arc_bolts_spawn_once(0xFF, 1);
        break;
    case 0x31:
        level_cue_switch_on();
        break;
    case 0x33:
        blast_debris_and_smoke(0xFF, 1);
        break;
    }
    return ret;
}

void water_jets_stop_all(void);
void fx_slots_9cf0_clear(void);
void char_fx_event15_stop(s32);
void zap_bolt_free_slot(s32);
s32 fx_fireworks_burst(s32);
void glow_pair_post_remove_event(u8 *);
void fire_post_finish_events(u8);
void light_ctrl_broadcast(u8, u8, s32);
void spout_broadcast_stop(s32);
void scroll_banner_stop(s16);
extern s8 D_800D9D40;

/* was func_1509DB90 */
void event_effect_stop(s32 arg0, u8 *arg1) {
    struct127 *temp_v0;
    struct127 *temp_v0_2;

    switch (arg0) {
    case 41:
        fx_fireworks_burst(arg0);
        return;
    case 39:
        fire_post_finish_events((*(u8 *)((u8 *)arg1 + 7)));
        return;
    case 38:
        light_ctrl_broadcast(0x29, 0x18, 0);
        return;
    case 36:
        temp_v0 = obj_find_by_spawn((*(s32 *)((u8 *)arg1 + 4)) & 0xFFF);
        if (temp_v0 != NULL) {
            glow_pair_post_remove_event(temp_v0);
            return;
        }
    default:
        return;
    case 26:
        light_ctrl_broadcast(0x26, 0x18, 0);
        return;
    case 18:
        spout_broadcast_stop((*(s32 *)((u8 *)arg1 + 4)));
        return;
    case 2:
        D_800D9D40 = 0;
        return;
    case 4:
    case 5:
    case 6:
        zap_bolt_free_slot(arg0 >> 6);
        return;
    case 8:
        water_jets_stop_all();
        return;
    case 9:
        temp_v0_2 = obj_find_by_spawn((*(s32 *)((u8 *)arg1 + 4)) & 0xFFF);
        if (temp_v0_2 == NULL) {
            return;
        }
        char_fx_event15_stop(temp_v0_2);
        return;
    case 10:
        fx_slots_9cf0_clear();
        return;
    case 19:
        scroll_banner_stop((*(s16 *)((u8 *)arg1 + 6)));
        return;
    case 21:
        light_ctrl_broadcast(0x20, 0x18, 0);
        return;
    case 22:
        light_ctrl_broadcast(0x23, 0x28, 0);
        light_ctrl_broadcast(0x24, 0x28, 0);
        break;
    }
}
extern s32 D_800A0D30;

// P176: s32 like the D_80088874 handler table. The asm sets v0 only on the case 0x1C / 5 out-of-range path (1);
// elsewhere v0 is a callee's result (undefined): 0 here.
/* was func_1509DD0C */
s32 event_action_effect(s32 arg0, s32 arg1, u8 *arg2) {
    struct {
        f32 u2C;
        s8 u30;
        s8 u31;
        s8 u32;
        s8 u33;
        s8 u34;
        u8 pad35[0x3];
        s8 u38;
    } sp;
    s32 var_a0;
    s32 var_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    switch (arg0) {
    case 0x34:
        if (arg1 == 3) {
            emitter_stop_for_obj(obj_find_by_spawn((*(s32 *)((u8 *)arg2 + 4)) & 0xFFF));
            return 0;
        }
    default:
        return 0;
    case 0x32:
        if (arg1 == 2) {
            fx_lists_broadcast_a(0, 0x53U);
            return 0;
        }
        if (arg1 == 3) {
            fx_lists_broadcast_a(0, 0x54U);
            return 0;
        }
        break;
    case 0x2D:
        level_set_lights_mode((arg1 == 6) & 0xFF);
        return 0;
    case 0x28:
        if (arg1 == 2) {
            light_group_set_disabled(4, 1);
            light_group_set_disabled(5, 0);
            return 0;
        }
        if (arg1 == 3) {
            light_group_set_disabled(4, 0);
            light_group_set_disabled(5, 1);
            return 0;
        }
        break;
    case 0x1F:
        if (arg1 == 5) {
            sp.u38 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            fx_lists_broadcast_a((s32) &sp.u38, 0x36U);
        }
        /* fallthrough */
    case 0x1E:
        if (arg1 == 2) {
            sp.u34 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            effect_nodes_broadcast((s32) &sp.u34, 0x34U);
            return 0;
        }
        break;
    case 0x1D:
        if (arg1 == 5) {
            sp.u2C = (f32) (*(s32 *)((u8 *)arg2 + 0xC));
            sp.u30 = (s8) (*(s32 *)((u8 *)arg2 + 8));
            sp.u31 = (s8) (*(s32 *)((u8 *)arg2 + 0x10));
            sp.u32 = (s8) (*(s32 *)((u8 *)arg2 + 0x14));
            sp.u33 = (s8) (*(s32 *)((u8 *)arg2 + 0x18));
            node_broadcast_type(0x35, (s32) &sp.u2C, 0x33U);
            return 0;
        }
        break;
    case 0x1C:
        if (arg1 == 5) {
            temp_v0 = (*(s32 *)((u8 *)arg2 + 8));
            if ((temp_v0 < 0) || (temp_v0 >= 3)) {
                return 1;
            }
            effect_nodes_broadcast((s32) ((u8 *) &D_800A0D30 + temp_v0 * 0x10), 0x32U);
            return 0;
        }
        break;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        temp_v0_2 = arg0 & 0x3F;
        if (temp_v0_2 == 0xB) {
            var_a0 = 1;
        } else if (temp_v0_2 == 0xC) {
            var_a0 = 2;
        } else if (temp_v0_2 == 0xD) {
            var_a0 = 3;
        } else {
            var_a0 = 0;
            if (temp_v0_2 == 0xE) {
                var_a0 = 4;
            }
        }
        if (arg1 == 2) {
            var_a1 = 0x17;
        } else {
            var_a1 = 0x17;
            if (arg1 == 3) {
                var_a1 = 0x18;
            }
        }
        light_ctrl_broadcast(var_a0, var_a1, 0);
        return 0;
    case 0x11:
        light_group_send_msg22((*(u8 *)((u8 *)arg2 + 0xB)), (arg1 == 3) & 0xFF);
        break;
    }
    return 0;
}
void zap_bolt_get_pos(s32, s32 *, s32 *, s32 *);

/* was func_1509DFCC */
s32 event_query_effect(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u34;
        s32 u38;
        s32 u3C;
    } sp;
    s32 temp_a0;
    s32 temp_t8;
    s32 var_t0;
    s32 var_v0;
    s8 var_a1;
    struct_eu_node *temp_v1;
    struct_eu_node *var_v0_2;

    var_v0 = 4;
    sp.u3C = 0;
    sp.u38 = 0;
    sp.u34 = 0;
    if ((arg0 != 4) && (arg0 != 5) && (arg0 != 6)) {
        if (arg0 == 0x19) {
            var_t0 = 0;
            if (arg1 == 4) {
loop_6:
                var_a1 = 0;
loop_7:
                var_v0_2 = g_node_lists[var_t0][*(s32 *)((u8 *)&D_800A6440 + var_a1 * 4)];
                var_a1 += 1;
                /* P176 (browser P174): test +0x48 of every node, then move to next (the m2c body advanced first:
                 * it skipped each list's first node and read NULL + 0x48 at the end) */
                for (; var_v0_2 != NULL; var_v0_2 = temp_v1) {
                    temp_v1 = var_v0_2->next;
                    if ((*(u8 *)((u8 *)var_v0_2 + 0x48)) == 2) {
                        return 0;
                    }
                }
                if (var_a1 >= 3) {
                    temp_t8 = (var_t0 + 1) & 0xFF;
                    var_t0 = temp_t8;
                    if (temp_t8 >= 2) {
                        return 1;
                    }
                    goto loop_6;
                }
                goto loop_7;
            }
        }
        /* Duplicate return node #20. Try simplifying control flow for better match */
        return var_v0;
    }
    if ((arg1 == 0) || (arg1 == 1)) {
        temp_a0 = arg0 >> 6;
        if (temp_a0 != 0) {
            zap_bolt_get_pos(temp_a0, &sp.u3C, &sp.u38, &sp.u34);
            if (arg1 == 0) {
                sp.u38 = (sp.u3C << 0x10) | (sp.u34 & 0xFFFF);
            }
            var_v0 = sp.u38;
        }
    }
    return var_v0;
}