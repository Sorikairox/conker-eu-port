#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 setup_entry_find_by_id(u8);
struct127 *obj_find_by_setup_id(u8);
s32 setup_entry_spawn(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

/* Object id (0x2000 | n) of script entity `entity` (u8): -1 when it has no record (setup_entry_find_by_id), the live object's
 * +0x13F when it exists (obj_find_by_setup_id), else the record's flag +2 is cleared and the entity is spawned
 * (setup_entry_spawn; -1 when that fails) and looked up again. 0 stays 0. */
/* was func_15097D20 */
s32 script_entity_object_id(s32 entity, s32 unused) {
    s32 idx;
    struct127 *obj;

    idx = setup_entry_find_by_id(entity);
    if (idx != -1) {
        obj = obj_find_by_setup_id(entity);
        if (obj != NULL) {
            idx = ((u8 *)obj)[0x13F];
        } else {
            ((u8 *)D_800D20FC + idx * 0x30)[2] = 0;
            if (setup_entry_spawn((u8 *)D_800D20FC + idx * 0x30, idx, 0, 0, 0) == 0) {
                return -1;
            }
            idx = setup_entry_find_by_id(entity);
        }
    }
    if (idx != 0) {
        idx |= 0x2000;
    }
    return idx;
}

s32 obj_death_resolve(struct127 *);
void obj_remove(struct127 *arg0, s32 arg1);
extern u8 D_800D2520;
extern s32 D_800D3C60;

/* Removes object `id`: sets flag +2 of its entity record (when id < D_800D2520) and kills it with
 * obj_remove(obj, 0), or with obj_death_resolve when called with two words and args[1] != 0. Returns 999999,
 * 0 for a missing object. */
/* was func_15097DDC */
s32 script_object_remove(s32 id, s32 *args) {
    struct127 *obj;

    obj = obj_find_by_spawn(id);
    if (obj == NULL) {
        return 0;
    }
    if (id < D_800D2520) {
        ((u8 *)D_800D20FC + id * 0x30)[2] = 1;
    }
    if (D_800D3C60 == 2 && args[1] != 0) {
        obj_death_resolve(obj);
    } else {
        obj_remove(obj, 0);
    }
    return 999999;
}

f32 sinf(f32);
f32 cosf(f32);
void obj_drop_carried(struct127 *);
s32 rail_node_find_by_tag(s32);
s32 rail_node_position(s32, f32 *, f32 *, f32 *);
s32 obj_slot_by_spawn(s32);
void player_start_index_set(void *, s32);
void player_stat_modify(s16, s16, s32);
s32 player_stat_get(s16, s32);
void text_set_box(s32, s32);
void text_set_pos(s16, s16);
void text_set_flags(u8);
void drip_effect_attach(struct127 *, s32, s32);
void drip_effect_detach(u8 *);
void warp_player_to_entry(u8 *, s32);
void face_clear_default_anim(struct127 *);
void face_set_default_anim(struct127 *, s32);
void context_action_lock(s32, s32, s32, s32);
s32 obj_send_hit(struct127 *, s32, u16, s32);
s32 attack_spawn_at_point(f32, f32, f32, s32, s32, u16, s32, s32);
void breakable_request_flag_entry(struct127 *, s32, s32);
struct127 *obj_find_child_nth(struct127 *, s32);
void obj_set_scale(struct127 *, f32, f32);
void obj_start_anim(struct127 *, u16, f32, f32, f32, f32, s32);
void collision_find_floor(s32, s32, f32 *, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);
s32 random_int(void);
s32 math_angle_diff_deg_int(s32, s32);
s32 obj_setup_run(struct127 *, s32, f32, s32);
s32 obj_setup_undo(struct127 *, s32);
u8 *attachment_find_by_slot(struct127 *, s32, s32);
struct127 *obj_find_by_setup_id(u8);
void obj_fade_command(struct127 *, u8, u8, u8, u8);
void obj_knockdown_start(struct127 *);
void obj_hit_react_start(struct127 *);
void obj_knockdown_clear(struct127 *);
void char_fx_beam_light_setup(struct127 *);
f32 obj_carry_release(struct127 *, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void obj_head_particle_burst(u8 *, u8, s32);
void obj_bone_debris_emitter_attach(u8 *, s32, s32);
void money_collect_popup_spawn(u8 *, u8, s32);
void obj_attach_to_carrier(struct127 *, s32);
void obj_model_swap_keep_pose(struct127 *, s32, s32, f32);
void mp_player_respawn(struct127 *);
void player_lose_life(s32);
s32 player_hit_reaction(struct127 *, s32);
void screen_fade_start(s32, s32, s32, s32, s8, s32);
void obj_remove(struct127 *, s32);
void *aiscript_find_by_kind(s32, s32);
extern s32 D_800D3C60;
extern s32 D_800BE804;
extern u16 D_800BEB30[];
extern s16 D_800C4414[];
extern u16 D_8009015C;

#define E9C_U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define E9C_S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define E9C_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define E9C_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define E9C_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define E9C_F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define E9C_REC(p) (*(u8 **)((u8 *)(p) + 0x31C))
#define E9C_INDEX(p) (((u8 *)(p) - (u8 *)D_800CC2D0) / 0x32C)   /* index in D_800CC2D0 (0x32C each) */
#define E9C_FIX(v) ((f32)(v) * (1.0f / 65536.0f))                 /* 16.16 fixed point argument */
#define E9C_PATH(p, n) ((s16 *)((s32 **)D_800D2104)[E9C_U8(p, 0x13F)] + (n) * 4)  /* point n of path +0x13F */
/* f32 -> u32 as IDO converts it (truncation; negative or NaN give 0xFFFFFFFF) */
#define E9C_TOU32(f) ((f) >= 2147483648.0f ? (((f) - 2147483648.0f < 2147483648.0f) \
                          ? ((u32)(s32)((f) - 2147483648.0f) | 0x80000000) : 0xFFFFFFFF) \
                      : ((f) > -1.0f) ? (u32)(s32)(f) : 0xFFFFFFFF)

// object_run_command: performs one scripted object command (move, turn, animate, spawn, ...) on the object `id`.
/* Object command handler: entry 0 of event_dispatch's handler table (event ids 0x2xxx), called as
 * handler(id, cmd, args) with args = {id, cmd, x1, x2, ...} (args[2] is the first extra argument, D_800D3C60 the
 * number of words; 16.16 fixed point for speeds / scales, degrees for angles). `id` names an object
 * (obj_find_by_spawn); returns 0 when it does not exist or for an unknown command, else 1. */
/* was func_15097E9C */
s32 event_action_object(s32 id, s32 cmd, s32 *args) {
    struct127 *obj;
    u8 *o;
    u8 *rec;
    u8 *p;
    s32 i;
    s32 n;
    s32 x;
    s32 z;
    f32 f;
    f32 px;
    f32 py;
    f32 pz;
    u32 u;

    obj = obj_find_by_spawn(id);
    if (obj == NULL) {
        return 0;
    }
    o = (u8 *)obj;
    switch (cmd) {
    case 0x01: /* set / clear bits args[3] of +0x25C */
        if (args[2] != 0) {
            E9C_S32(o, 0x25C) |= args[3];
        } else {
            E9C_S32(o, 0x25C) &= ~args[3];
        }
        return 1;
    case 0x02:
        E9C_S32(o, 0x25C) |= 8;
        return 1;
    case 0x03:
        E9C_S32(o, 0x25C) &= ~8;
        return 1;
    case 0x04:
        E9C_S32(o, 0x25C) |= 0x10;
        return 1;
    case 0x05:
        E9C_S32(o, 0x25C) |= 1;
        return 1;
    case 0x06:
        E9C_S32(o, 0x25C) |= 4;
        E9C_S32(o, 0x25C) &= ~1;
        return 1;
    case 0x07:
        D_800D154C = obj;
        obj_drop_carried(obj);
        return 1;
    case 0x08: /* position; 0x7FFFFFFF keeps a coordinate */
        if (args[2] != 0x7FFFFFFF) {
            obj->x_position = args[2];
        }
        if (args[3] != 0x7FFFFFFF) {
            obj->y_position = args[3];
        }
        if (args[4] != 0x7FFFFFFF) {
            obj->z_position = args[4];
        }
        return 1;
    case 0x09: /* position = point args[2] */
        n = rail_node_find_by_tag(args[2]);
        if (n != -1) {
            rail_node_position(n, &obj->x_position, &obj->y_position, &obj->z_position);
        }
        return 1;
    case 0x0A:
        E9C_S32(o, 0x25C) &= ~4;
        return 1;
    case 0x0B:
        E9C_U8(o, 0x13D) = args[2];
        return 1;
    case 0x0C:
    case 0x0D:
        obj->xz_velocity = E9C_FIX(args[2]);
        return 1;
    case 0x0E:
        obj->y_velocity = E9C_FIX(args[2]);
        return 1;
    case 0x0F:
        obj->gravity = E9C_FIX(args[2]);
        return 1;
    case 0x10: /* heading in degrees (16.16) */
        f = E9C_FIX(args[2]) * (65536.0f / 360.0f);
        u = E9C_TOU32(f) - 0x4000;
        E9C_U16(o, 0x76) = E9C_U16(o, 0x7A) = u;
        return 1;
    case 0x11: /* heading, raw angle / 256 */
        f = (f32)args[2] * (1.0f / 256.0f);
        u = E9C_TOU32(f);
        E9C_U16(o, 0x76) = E9C_U16(o, 0x7A) = u;
        return 1;
    case 0x12:
        f = (f32)args[2] * (1.0f / 256.0f);
        u = E9C_TOU32(f);
        E9C_U16(o, 0x78) = u;
        return 1;
    case 0x13:
        E9C_U8(o, 0x125) = args[2];
        return 1;
    case 0x14: /* +0x232 = args[2], restart its script (aiscript_find_by_kind) */
        E9C_U8(o, 0x232) = args[2];
        D_800D154C = obj;
        D_800C3E78 = E9C_INDEX(o);
        E9C_S32(o, 0x218) = (s32)aiscript_find_by_kind(0, E9C_U8(o, 0x232));
        E9C_U16(o, 0x21C) = 0;
        return 1;
    case 0x15:
        E9C_F32(o, 0xB8) = E9C_FIX(args[2]);
        return 1;
    case 0x16:
        E9C_F32(o, 0x48) = E9C_FIX(args[2]);
        return 1;
    case 0x17:
        if (args[2] != 0) {
            drip_effect_attach(obj, 0xFF, 0);
        } else {
            drip_effect_detach(o);
        }
        return 1;
    case 0x18:
        E9C_U8(o, 0x247) = args[2];
        return 1;
    case 0x19: /* +0x222 = entity of object args[2] (negative: as is) */
        if (args[2] < 0) {
            E9C_U8(o, 0x222) = args[2];
            return 1;
        }
        if (obj_slot_by_spawn(args[2] & 0xFFFF0FFF) == -1) {
            return 1;
        }
        E9C_U8(o, 0x222) = obj_slot_by_spawn(args[2] & 0xFFFF0FFF);
        return 1;
    case 0x1A:
        E9C_U8(o, 0x20A) = args[2];
        return 1;
    case 0x1B: /* args[2] == 1: set bits args[3] of +0x9C, else clear them */
        if (args[2] == 1) {
            E9C_S32(o, 0x9C) |= args[3];
        } else {
            E9C_S32(o, 0x9C) &= ~args[3];
        }
        return 1;
    case 0x1C:
        E9C_F32(o, 0x154) = E9C_FIX(args[2]);
        E9C_F32(o, 0x158) = E9C_FIX(args[3]);
        E9C_F32(o, 0x15C) = E9C_FIX(args[4]);
        return 1;
    case 0x1D:
        if (args[2] != 0) {
            E9C_U8(o, 0x89) = 0xFF;
            E9C_U8(o, 0x8A) = 0xFF;
            E9C_U8(o, 0x83) = 0xFF;
        } else {
            E9C_U8(o, 0x89) = 0;
            E9C_U8(o, 0x8A) = 0;
            E9C_U8(o, 0x83) = 0;
        }
        return 1;
    case 0x1E:
        if (args[2] != 0) {
            E9C_U8(o, 0x2FA) |= 0x80;
        } else {
            E9C_U8(o, 0x2FA) &= 0x7F;
        }
        return 1;
    case 0x1F:
        player_start_index_set(o, args[2] & 0xFFF);
        return 1;
    case 0x20:
        E9C_U8(o, 0x1CA) = args[2];
        if (D_800D3C60 == 4) {
            D_800D2456 = args[2];
            D_800D2457 = D_800D2456;
        }
        return 1;
    case 0x21:
        player_stat_modify(id, args[2], args[3]);
        return 1;
    case 0x22: /* +0x2D8[i] = fixed args[2 + i] (0x78000000 keeps one) */
        for (i = 0; i < D_800D3C60 - 2; i++) {
            if (args[2 + i] != 0x78000000) {
                E9C_F32(o, 0x2D8 + i * 4) = E9C_FIX(args[2 + i]);
            }
        }
        return 1;
    case 0x23: /* +0x2E4[i] = args[2 + i] (0x7FFFFFFF keeps one) */
        for (i = 0; i < D_800D3C60 - 2; i++) {
            if (args[2 + i] != 0x7FFFFFFF) {
                E9C_S32(o, 0x2E4 + i * 4) = args[2 + i];
            }
        }
        return 1;
    case 0x24:
        if (args[2] == 0) {
            face_clear_default_anim(obj);
            E9C_U16(E9C_REC(o), 0x8) = 0;
            E9C_U8(E9C_REC(o), 0x16) = 0;
            return 1;
        }
        E9C_U16(E9C_REC(o), 0x8) = 1;
        if (args[2] == 1) {
            face_set_default_anim(obj, 0x15);
        } else if (args[2] == 2) {
            face_set_default_anim(obj, 0x2A);
            E9C_U8(E9C_REC(o), 0x16) = 0xFF;
        }
        return 1;
    case 0x25:
        E9C_U16(E9C_REC(o), 0x8) = args[2];
        E9C_U16(E9C_REC(o), 0xE) = 0xA6;
        return 1;
    case 0x26:
        context_action_lock(id, 0, args[2], 0);
        return 1;
    case 0x27:
        context_action_lock(id, 1, args[2], 0);
        if (D_800D3C60 == 3 && args[2] == 0) {
            E9C_U8(E9C_REC(o), 0x78) = 0;
        }
        return 1;
    case 0x28:
        E9C_U8(E9C_REC(o), 0x76) = args[2];
        return 1;
    case 0x29:
        E9C_U8(o, 0x251) = args[2];
        return 1;
    case 0x2A:
        obj_send_hit(obj, args[2], args[3], -1);
        return 1;
    case 0x2B:
        obj_send_hit(obj, args[2], args[3], args[4]);
        return 1;
    case 0x2C: /* spawn at (args[3], args[4], args[5]) */
        attack_spawn_at_point(args[3], args[4], args[5], args[2], args[6], args[7], 0, 0);
        return 1;
    case 0x2D:
        E9C_U8(o, 0x21E) = args[2];
        return 1;
    case 0x2E: /* button word args[2] = args[3] (D_800BEB30 and the pointer table D_800BE728) */
        D_800BEB30[args[2]] = args[3];
        *((u16 **)D_800BE728[0])[args[2]] = args[3];
        return 1;
    case 0x2F: /* attached object args[2] (obj_find_child_nth): 0 scale, 1 move, 2 script */
        p = (u8 *)obj_find_child_nth(obj, args[2]);
        if (p == NULL) {
            return 1;
        }
        if (args[3] == 0) {
            obj_set_scale(obj, E9C_FIX(args[4]), E9C_FIX(args[5]));
        } else if (args[3] == 1) {
            obj_start_anim((struct127 *)p, args[4], E9C_FIX(args[5]), E9C_FIX(args[6]), 0.0f, 0.0f, 0);
        } else if (args[3] == 2) {
            E9C_S32(p, 0x218) = 0;
            E9C_U8(p, 0x232) = args[4];
        }
        return 1;
    case 0x30:
        E9C_U8(o, 0x104) = args[2];
        return 1;
    case 0x31:
        E9C_U8(o, 0x239) = args[2];
        return 1;
    case 0x32:
        E9C_U8(o, 0x10A) = args[2];
        return 1;
    case 0x33:
        D_800D1898[args[2]] = E9C_FIX(args[3]);
        return 1;
    case 0x34: /* place 1800 in front of the camera D_800DBFF0 (+-400 random), mirrored into the box
                * args[2..5] (x lo / hi, z lo / hi), on the floor + args[6] */
        x = E9C_F32(D_800DBFF0, 0x2F8);
        z = E9C_F32(D_800DBFF0, 0x300);
        x = x - sinf(E9C_F32(D_800DBFF0, 0x3A0)) * 1800.0f;
        z = z - cosf(E9C_F32(D_800DBFF0, 0x3A0)) * 1800.0f;
        x += (u32)random_int() % 800 - 400;
        z += (u32)random_int() % 800 - 400;
        if (x < args[2]) {
            x = args[2] - x + args[2];
        } else if (args[3] < x) {
            x = args[3] - x + args[3];
        }
        if (z < args[4]) {
            z = args[4] - z + args[4];
        } else if (args[5] < z) {
            z = args[5] - z + args[5];
        }
        px = x;
        pz = z;
        py = E9C_F32(D_800DBFF0, 0x2FC);
        collision_find_floor(0, 0, &py, 0, 0, 0, px, py, pz, py, 0, 0, -10000.0f, 20000.0f);
        obj->x_position = px;
        obj->z_position = pz;
        obj->y_position = (f32)args[6] + py;
        return 1;
    case 0x35:
        D_800D154C = obj;
        D_800C3E78 = E9C_INDEX(o);
        E9C_S32(o, 0x218) = (s32)aiscript_find_by_kind(0, args[2]);
        E9C_U16(o, 0x21C) = 0;
        return 1;
    case 0x36:
        if (args[2] != 0) {
            E9C_U8(E9C_REC(o), 0x20) |= args[3];
        } else {
            E9C_U8(E9C_REC(o), 0x20) &= ~args[3];
        }
        return 1;
    case 0x37:
        E9C_U8(o, 0x1E4) = args[2];
        return 1;
    case 0x38:
        E9C_U8(o, 0x232) = args[2];
        return 1;
    case 0x39:
        E9C_U8(o, 0x221) = args[2];
        return 1;
    case 0x3A:
        f = E9C_FIX(args[2]);
        obj_set_scale(obj, f, f);
        return 1;
    case 0x3B:
        E9C_U16(E9C_REC(o), 0x32) |= args[2];
        if (D_800D3C60 == 4) {
            E9C_U16(E9C_REC(o), 0x34) = args[3];
        }
        return 1;
    case 0x3C:
        E9C_U8(E9C_REC(o), 0x1A) = (args[2] != 0) ? 1 : 0;
        return 1;
    case 0x3D: /* +0x94: 0 = all but args[3] | 1, 1 = clear args[3], else set args[3] */
        if (args[2] == 0) {
            E9C_S32(o, 0x94) = ~(args[3] | 1);
        } else if (args[2] == 1) {
            E9C_S32(o, 0x94) &= ~args[3];
        } else {
            E9C_S32(o, 0x94) |= args[3];
        }
        return 1;
    case 0x3E:
        breakable_request_flag_entry(obj, args[2], args[3]);
        return 1;
    case 0x3F:
        E9C_U8(o, 0x8A) = args[2];
        return 1;
    case 0x40:
        if (args[2] != 0) {
            E9C_S32(o, 0xF8) |= args[3];
        } else {
            E9C_S32(o, 0xF8) &= ~args[3];
        }
        return 1;
    case 0x41:
        E9C_F32(o, 0x1CC) = args[2];
        return 1;
    case 0x42:
        E9C_U8(o, 0x246) = args[2] >> 8;
        E9C_U8(o, 0x249) = args[2];
        return 1;
    case 0x43: /* point args[2] + 1 of path +0x13F = (args[3], args[4], args[5]) */
        E9C_PATH(o, args[2] + 1)[0] = args[3];
        E9C_PATH(o, args[2] + 1)[1] = args[4];
        E9C_PATH(o, args[2] + 1)[2] = args[5];
        return 1;
    case 0x44: /* point args[2] + 1 of path +0x13F = the position of point args[3] */
        n = rail_node_find_by_tag(args[3]);
        if (n != -1) {
            rail_node_position(n, &px, &py, &pz);
            E9C_PATH(o, args[2] + 1)[0] = (s32)px;
            E9C_PATH(o, args[2] + 1)[1] = (s32)py;
            E9C_PATH(o, args[2] + 1)[2] = (s32)pz;
        }
        return 1;
    case 0x45:
        E9C_U8(E9C_REC(o), 0x7B) = args[2];
        return 1;
    case 0x46:
        E9C_U8(o, 0x234) = args[2];
        E9C_U8(o, 0x236) = args[3];
        E9C_U8(o, 0x237) = args[4];
        return 1;
    case 0x47:
        E9C_U8(E9C_REC(o), 0x1B) = args[2];
        return 1;
    case 0x48:
        E9C_U8(o, 0xD0) = args[2];
        E9C_F32(o, 0x114) = args[3];
        return 1;
    case 0x49:
        E9C_U8(o, 0x1C9) = args[2];
        return 1;
    case 0x4A:
        face_set_default_anim(obj, args[2]);
        return 1;
    case 0x4B:
        obj_setup_run(obj, args[2], 0.0f, 0);
        return 1;
    case 0x4C:
        obj_setup_undo(obj, args[2]);
        return 1;
    case 0x4D:
        p = attachment_find_by_slot(obj, args[2], args[3]);
        if (p != NULL) {
            E9C_S32(p, 0x38) = args[4];
        }
        return 1;
    case 0x4E: /* hold on to entity args[2]: +0x65 = its object number + 1, +0x5C = args[3] */
        p = (u8 *)obj_find_by_setup_id(args[2]);
        if (p == NULL) {
            return 1;
        }
        if (args[4] == 0) {
            E9C_U8(o, 0x101) |= 4;
        }
        E9C_U8(o, 0x65) = E9C_INDEX(p) + 1;
        E9C_S32(o, 0x5C) = args[3];
        return 1;
    case 0x4F:
        E9C_U8(o, 0x3B) = args[2];
        return 1;
    case 0x50: /* +0x74 bits args[3] := args[2] */
        E9C_U8(o, 0x74) = args[2] | (E9C_U8(o, 0x74) & ~args[3]);
        return 1;
    case 0x51:
        E9C_U8(E9C_REC(o), 0x4A) = args[2];
        return 1;
    case 0x52:
    case 0x5E:
        return 1;
    case 0x53:
        E9C_U8(o, 0x89) = args[2];
        return 1;
    case 0x54: /* fade: 3 words = mode 1 to args[2], else mode 2 args[2] / args[3] */
        if (D_800D3C60 == 3) {
            obj_fade_command(obj, 1, args[2], 0, 0);
        } else {
            obj_fade_command(obj, 2, args[2], args[3], 0);
        }
        return 1;
    case 0x55: /* players 0..3: button bit 0x4000 */
        n = E9C_INDEX(o);
        if (n < 4) {
            *((u16 **)D_800BE728[0])[n] |= 0x4000;
            D_800BEB30[n] |= 0x4000;
        }
        return 1;
    case 0x56:
        E9C_U8(o, 0x65) = args[2];
        return 1;
    case 0x57:
        E9C_U16(o, 0x21C) = args[2];
        return 1;
    case 0x58:
        E9C_U8(o, 0x140) = args[2];
        return 1;
    case 0x59:
        E9C_U8(o, 0x20B + args[3]) = args[2];
        return 1;
    case 0x5A:
        warp_player_to_entry(o, -1);
        return 1;
    case 0x5B: /* point args[2] (0xFF for < 0) into +0x211 */
        E9C_U8(o, 0x211) = (args[2] < 0) ? 0xFF : rail_node_find_by_tag(args[2]);
        return 1;
    case 0x5C:
        E9C_U8(o, 0x20F) = (args[2] < 0) ? 0xFF : rail_node_find_by_tag(args[2]);
        return 1;
    case 0x5D:
        E9C_U8(o, 0x212) = (args[2] < 0) ? 0xFF : rail_node_find_by_tag(args[2]);
        return 1;
    case 0x5F: /* lower +0x44 to args[2] */
        f = args[2];
        if (f < E9C_F32(o, 0x44)) {
            E9C_F32(o, 0x44) = f;
        }
        return 1;
    case 0x60: /* target point args[2] (+0x211), no +0x20F, script args[3] */
        E9C_U8(o, 0x211) = (args[2] < 0) ? 0xFF : rail_node_find_by_tag(args[2]);
        E9C_U8(o, 0x20F) = 0xFF;
        E9C_S32(o, 0x25C) &= ~0x800;
        E9C_U8(o, 0x232) = args[3];
        D_800D154C = obj;
        D_800C3E78 = E9C_INDEX(o);
        E9C_S32(o, 0x218) = (s32)aiscript_find_by_kind(0, E9C_U8(o, 0x232));
        E9C_U16(o, 0x21C) = 0;
        return 1;
    case 0x61: /* record +0x8C (args[2], -1 = 0x8000); -1 / 4 / 0x2000 also set +0x8A and mode 2 */
        if (E9C_REC(o) == NULL) {
            return 1;
        }
        n = args[2];
        if (n == -1) {
            n = 0x8000;
        }
        E9C_U16(E9C_REC(o), 0x8C) = n;
        E9C_U8(E9C_REC(o), 0x8F) = 0;
        if (args[2] == -1 || args[2] == 4 || args[2] == 0x2000) {
            E9C_U16(E9C_REC(o), 0x8A) = n;
            E9C_U8(E9C_REC(o), 0x8E) = 2;
        }
        return 1;
    case 0x62: /* the first D_8008FD8C objects: player_stat_modify(index, 10, args[2]); D_800BE804 = player_stat_get */
        n = E9C_INDEX(o);
        if (n >= 0 && n < D_8008FD8C) {
            player_stat_modify(E9C_INDEX(o), 10, args[2]);
        }
        D_800BE804 = player_stat_get(E9C_INDEX(o), 6);
        return 1;
    case 0x63:
        n = E9C_INDEX(o);
        if (n >= 0 && n < D_8008FD8C) {
            player_stat_modify(E9C_INDEX(o), 9, args[2]);
        }
        D_800BE804 = player_stat_get(E9C_INDEX(o), 6);
        return 1;
    case 0x64:
        i = args[2];
        if (D_800BE616 == 0 && (D_800E9D00 & 0x200)) {
            i = 0x33;
        }
        n = E9C_INDEX(o);
        if (n >= 0 && n < D_8008FD8C) {
            player_stat_modify(E9C_INDEX(o), 2, i);
        }
        return 1;
    case 0x65:
        n = E9C_INDEX(o);
        if (n >= 0 && n < D_8008FD8C) {
            player_stat_modify(E9C_INDEX(o), 3, args[2]);
        }
        return 1;
    case 0x66:
        text_set_box((s32)obj, args[2]);
        return 1;
    case 0x67: /* screen position of player args[2] (bit 0: column, >> 1: row) in 2 / 3 player modes */
        n = args[2];
        text_set_flags(0);
        if (D_80082FA0 == 2 || D_80082FA0 == 3) {
            text_set_pos((n & 1) * 150 + 10, (n >> 1) * 115);
        }
        return 1;
    case 0x68:
        E9C_U16(o, 0x10) = args[2];
        return 1;
    case 0x69:
        D_800D18C0 |= args[2];
        return 1;
    case 0x6A:
        if (args[2] != 0) {
            E9C_U8(o, 0x101) |= 1;
        } else {
            E9C_U8(o, 0x101) &= ~1;
        }
        return 1;
    case 0x6B:
        if (args[2] == 1) {
            E9C_U8(o, 0x101) |= args[3];
        } else {
            E9C_U8(o, 0x101) &= ~args[3];
        }
        return 1;
    case 0x6C:
        if (args[2] == 9) {
            obj_knockdown_start(obj);
        } else if (args[2] == 0x3B) {
            obj_hit_react_start(obj);
        }
        return 1;
    case 0x6D:
        if (args[2] == 9) {
            obj_knockdown_clear(obj);
        }
        return 1;
    case 0x6E:
        E9C_U8(o, 0x6C + args[2]) = args[3] + 10;
        return 1;
    case 0x6F:
        E9C_U8(o, 0x68 + args[2]) = args[3];
        return 1;
    case 0x70:
        if (args[3] != 0) {
            E9C_U8(E9C_REC(o), 0x128) |= args[2];
        } else {
            E9C_U8(E9C_REC(o), 0x128) &= ~args[2];
        }
        return 1;
    case 0x71: /* random point around (args[2], args[3]): distance args[4]..args[5], angle args[6]..args[7]
                * (degrees; the bounds are put in order in args) */
        if (!(args[6] < args[7])) {
            n = args[6];
            args[6] = args[7];
            args[7] = n;
        }
        n = math_angle_diff_deg_int((f32)args[6], (f32)args[7]);
        x = (u32)random_int() % (u32)n + args[6];
        z = (u32)random_int() % (u32)(args[5] - args[4]) + args[4];
        f = (f32)x * 0.017453292f;
        obj->x_position = sinf(f) * -(f32)z + (f32)args[2];
        obj->z_position = cosf(f) * -(f32)z + (f32)args[3];
        return 1;
    case 0x72: /* record +0x129, or +0x222 without a record */
        if (E9C_REC(o) != NULL) {
            E9C_U8(E9C_REC(o), 0x129) = args[2];
        } else {
            E9C_U8(o, 0x222) = args[2];
        }
        return 1;
    case 0x73:
        E9C_S32(o, 0) = args[2];
        return 1;
    case 0x74:
        E9C_U8(E9C_REC(o), 0x31) = args[2];
        return 1;
    case 0x75:
        if (args[2] != 0) {
            E9C_U16(o, 0x2F8) |= args[3];
        } else {
            E9C_U16(o, 0x2F8) &= ~args[3];
        }
        return 1;
    case 0x76:
        if (E9C_REC(o) != NULL) {
            E9C_S8(E9C_REC(o), 0x1AE) = args[2];
        }
        return 1;
    case 0x77:
        D_800C4414[0] = args[2];
        D_800C4414[1] = args[3];
        D_800C4414[2] = args[4];
        return 1;
    case 0x78:
        switch ((u32)args[2]) {
        case 0:
            obj_setup_run(obj, 0x79, 0.0f, 0);
            if (E9C_INDEX(o) < D_80090130) {
                E9C_U8(E9C_REC(o), 0x4E) = 2;
                obj_start_anim(obj, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
            }
            break;
        case 1:
            char_fx_beam_light_setup(obj);
            break;
        case 2:
            E9C_U8(E9C_REC(o), 0x17) = 1;
            E9C_U8(o, 0x1C9) = 6;
            break;
        case 3: /* object args[3] */
            p = (u8 *)obj_find_by_spawn(args[3] & 0xFFFF0FFF);
            if (p != NULL) {
                E9C_U8(E9C_REC(o), 0x4E) = 1;
                obj_carry_release((struct127 *)p, 50.0f, 0x17, 4, 0, 1, 0, 0, 1, 0);
            }
            break;
        case 4:
            obj_head_particle_burst(o, 0xFF, 1);
            obj_bone_debris_emitter_attach(o, 0xFF, 1);
            money_collect_popup_spawn(o, 0xFF, 1);
            break;
        case 5:
            obj_start_anim(obj, 0x16, 1.0f, 0.0f, 0.0f, 0.0f, 0);
            break;
        }
        return 1;
    case 0x79:
        E9C_U8(E9C_REC(o), 0x7D) = (args[2] != 0) ? 1 : 0;
        return 1;
    case 0x7A: /* grab entity args[2]: +0x13C = its object number + 100, stop, obj_attach_to_carrier(it, this number) */
        p = (u8 *)obj_find_by_setup_id(args[2]);
        if (p == NULL) {
            return 1;
        }
        E9C_U8(o, 0x13C) = E9C_INDEX(p) + 100;
        obj->xz_velocity = 0.0f;
        obj_attach_to_carrier((struct127 *)p, E9C_INDEX(o));
        return 1;
    case 0x7B:
        E9C_U8(E9C_REC(o), 0x1AF) = args[2];
        return 1;
    case 0x7C:
        E9C_U8(o, 0x23E) = args[2];
        return 1;
    case 0x7D:
        E9C_U8(o, 0x328) = args[2] + 1;
        return 1;
    case 0x7E:
        E9C_U8(E9C_REC(o), 0x7C) = args[2];
        return 1;
    case 0x7F:
        **(u16 **)(o + 0x144) = args[2];
        return 1;
    case 0x80:
        obj_model_swap_keep_pose(obj, args[2], args[3], (f32)args[4] * 0.01f);
        return 1;
    case 0x81:
        E9C_U8(o, 0x275) = args[2];
        return 1;
    case 0x82: /* mp_player_respawn with D_8009015C cleared */
        n = D_8009015C;
        D_8009015C = 0;
        mp_player_respawn(obj);
        D_8009015C = n;
        return 1;
    case 0x83:
        E9C_U8(o, 0x238) = args[2];
        return 1;
    case 0x84:
        E9C_U8(E9C_REC(o), 0x4E) = args[2];
        return 1;
    case 0x85:
        player_lose_life(E9C_INDEX(o));
        return 1;
    case 0x86:
        E9C_U8(o, 0x23D) = args[2];
        return 1;
    case 0x87:
        player_hit_reaction(obj, 0xF);
        return 1;
    case 0x88:
        player_hit_reaction(obj, 9);
        return 1;
    case 0x89:
        E9C_U16(o, 0x22E) = args[2];
        return 1;
    case 0x8A:
        E9C_U8(o, 0xA4) = args[2];
        E9C_U8(o, 0xA5) = args[3];
        E9C_U8(o, 0xA6) = args[4];
        E9C_S32(o, 0xA0) = args[5];
        E9C_U8(o, 0xA7) = args[6];
        return 1;
    case 0x8B: /* players up to D_80082FA0 */
        if (E9C_INDEX(o) <= D_80082FA0) {
            screen_fade_start(args[2], args[3], args[4], args[5], args[6], E9C_INDEX(o));
        }
        return 1;
    case 0x8C:
        E9C_U8(E9C_REC(o), 0x11A) = args[2];
        return 1;
    case 0x8D: /* remove the live objects of kind 5 that belong to this one (+0x124 = its number + 1) */
        for (i = 0; i < 25; i++) {
            p = (u8 *)D_800CC2D0 + i * 0x32C;
            if (E9C_S32(p, 0) != 0 && E9C_U8(p, 0x124) == E9C_INDEX(o) + 1 && E9C_U8(p, 5) == 5) {
                obj_remove((struct127 *)p, 0);
            }
        }
        return 1;
    case 0x8E:
        E9C_F32(o, 0x180) = args[2];
        return 1;
    }
    return 0;
}
/* Object query handler: entry 1 of event_dispatch's handler table D_80088838 (event ids 0x2xxx), called as
 * handler(id & 0xFFF, cmd, args) with args = D_800D3380 = {id, cmd, x1, x2, ...} (args[2] is the first extra
 * argument; D_800D3C60 = the number of words). `id` names an object (obj_find_by_spawn). 0xB7 asks setup_entry_find_by_id,
 * 0xB0 / 0xB1 test whether the object is missing (0xB1: or of kind 8 / 0x27); every other query returns 0 for a
 * missing object and otherwise a field or a derived value (positions packed as x << 16 | z, distances, angles in
 * degrees, ...). Object ids passed as arguments drop bits 12..15 (& 0xFFFF0FFF). */
s32 setup_entry_find_by_id(u8);
s32 obj_slot_by_spawn(s32);
s32 player_start_index_get(struct127 *);
s32 rail_band_for_height(f32 y);
s32 rail_point_pick(f32 x, f32 y, f32 z, s32 count, s32 first, u8 *list, void *sel);
s32 rail_route_next(s32 point, s32 count, s32 first, u8 *list, s8 *sel); /* P203: s32 (asm returns s5; rail_point_pick and game_A28B0 read it) */
s32 rail_node_position(s32 point, f32 *x, f32 *y, f32 *z);
s32 rail_node_find_by_tag(s32 id);
f32 rail_wall_hit(f32 x, f32 y, f32 z, f32 dx, f32 dz);
s32 trigger_find_at_point(s32, s32, s32 x, s32 y, s32 z);
u8 *attachment_find_by_slot(struct127 *, s32, s32);
f32 wrap_angle_deg(f32 angle);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
s32 mp_is_free_for_all(void);
s32 mp_match_check_over(void);
extern s32 D_800D3C60;
extern u8 D_800E0FE8[];
extern s8 D_800E0EF0[];
extern u8 D_80087638;
extern u8 D_8008763C;
extern u8 D_800D1CC9;
extern u16 D_800BEB30[];
extern f32 D_8009E80C;

#define A024_U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define A024_S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define A024_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define A024_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define A024_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define A024_F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define A024_REC(p) (*(u8 **)((u8 *)(p) + 0x31C))
#define A024_OBJ(arg) obj_find_by_spawn((arg) & 0xFFFF0FFF)
#define A024_INDEX(p) (((u8 *)(p) - (u8 *)D_800CC2D0) / 0x32C)   /* index in D_800CC2D0 (0x32C each) */
#define A024_POINT(i) (((u8 *)D_800D2778 + (i) * 0x10)[7])
#define A024_DEG (360.0f / 65536.0f)

/* was func_1509A024 */
s32 event_query_object(s32 id, s32 cmd, s32 *args) {
    struct127 *obj;
    struct127 *other;
    u8 *rec;
    s16 *list;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 d;
    f32 px;
    f32 py;
    f32 pz;
    f32 hit[4];
    s32 r;
    s32 n;
    s32 i;
    s32 best;
    s32 minD;
    s32 maxD;
    s32 ox;
    s32 oz;
    u8 *p;
    u8 found[16];
    s8 count;
    s8 sel;
    u8 none;

    if (cmd == 0xB7) {
        return setup_entry_find_by_id(id & 0xFF);
    }
    obj = obj_find_by_spawn(id);
    if (cmd == 0xB0) {
        return (obj == NULL) ? 1 : 0;
    }
    if (cmd == 0xB1) {
        if (obj == NULL) {
            return 1;
        }
        return (A024_S32(obj, 0) == 8 || A024_S32(obj, 0) == 0x27) ? 1 : 0;
    }
    if (obj == NULL) {
        return 0;
    }

    switch (cmd) {
    case 0x91:
        return A024_U8(obj, 0x232);
    case 0x92:
        return A024_U16(obj, 0x21C);
    case 0x93:
        return obj->health;
    case 0x94:
        return (A024_U8(obj, 0x13D) != 0) ? 1 : 0;
    case 0x95:
        if (A024_U8(obj, 0x13C) == 0) {
            return 0;
        }
        return (A024_U8(obj, 0x13C) == obj_slot_by_spawn(args[2] & 0xFFFF0FFF) + 100) ? 1 : 0;
    case 0x96:
        return (obj->in_water == 1) ? 1 : 0;
    case 0x97:
        return ((s32)obj->x_position << 16) | ((s32)obj->z_position & 0xFFFF);
    case 0x98:
        return (s16)(s32)obj->y_position;
    case 0x99: /* within args[3] of object args[2] (xz) */
        other = A024_OBJ(args[2]);
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return (dx * dx + dz * dz < (f32)(args[3] * args[3])) ? 1 : 0;
    case 0x9A: /* xz distance to object args[2] (32000 when it does not exist) */
        other = A024_OBJ(args[2]);
        if (other == NULL) {
            return 32000;
        }
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return sqrtf(dx * dx + dz * dz);
    case 0x9B: /* xz distance to the point (args[2], args[3]) */
        dz = obj->z_position - (f32)args[3];
        dx = obj->x_position - (f32)args[2];
        return sqrtf(dz * dz + dx * dx);
    case 0x9C: /* heading to object args[2] */
        other = A024_OBJ(args[2]);
        r = math_atan2_u16(other->x_position - obj->x_position, other->z_position - obj->z_position, 0);
        return (f32)(r + 0x4000) * A024_DEG * 65536.0f;
    case 0x9D: /* heading to the point (args[2], args[3]) */
        r = math_atan2_u16((f32)args[2] - obj->x_position, (f32)args[3] - obj->z_position, 0);
        return (f32)(u32)((r - 0x4000) & 0xFFFF) * A024_DEG * 65536.0f;
    case 0x9E: /* within args[4] of the point (args[2], args[3]), integer xz */
        ox = (s32)obj->x_position - args[2];
        oz = (s32)obj->z_position - args[3];
        return (ox * ox + oz * oz < args[4] * args[4]) ? 1 : 0;
    case 0x9F:
        return A024_F32(obj, 0x48);
    case 0xA0:
        return A024_U8(obj, 0x223);
    case 0xA1:
        return A024_U8(obj, 0x234);
    case 0xA2:
        return (A024_U8(A024_REC(obj), 0x57) != 0) ? 1 : 0;
    case 0xA3:
        return A024_S32(obj, 0x25C) & 0x40;
    case 0xA4:
        return A024_U16(obj, 0x7A);
    case 0xA5:
        return player_stat_get(id, (s16)args[2]);
    case 0xA6: /* more than 150 below +0x1CC */
        return (150.0f < A024_F32(obj, 0x1CC) - obj->y_position) ? 1 : 0;
    case 0xA7:
        return player_start_index_get(obj) | 0xD000;
    case 0xA8:
        return (obj->stunned != 0) ? 1 : 0;
    case 0xA9:
        return A024_U8(A024_REC(obj), 0x77);
    case 0xAA:
        return A024_U8(A024_REC(obj), 0x78);
    case 0xAB:
        return A024_U8(A024_REC(obj), 0x79);
    case 0xAC:
        r = trigger_first_touched(A024_INDEX(obj), D_800D3C60 - 2, &args[2]);
        if (r != -1) {
            return r | 0x4000;
        }
        return 0;
    case 0xAD:
        return A024_U8(obj, 0x251);
    case 0xAE:
        return obj->xz_velocity;
    case 0xAF:
        rec = A024_REC(obj);
        if (A024_U8(rec, 0x16) != 0) {
            return 2;
        }
        return (A024_S16(rec, 0x8) != 0) ? 1 : 0;
    case 0xB2:
        return A024_S32(obj, 0x2E4 + args[2] * 4);
    case 0xB3:
        return A024_F32(obj, 0x40) * 65536.0f;
    case 0xB4:
        return A024_U8(obj, 0x10A);
    case 0xB5: /* the object +0x10A refers to (bit 7 set), its +0 */
        n = A024_U8(obj, 0x10A);
        if (n & 0x80) {
            return A024_S32(&D_800CC2D0[n & 0x7F], 0);
        }
        return 0xFFFF;
    case 0xB6: /* read and clear bit 7 of D_800E0FE8[index] */
        p = &D_800E0FE8[A024_INDEX(obj)];
        n = *p;
        *p = n & 0x7F;
        return n;
    case 0xB8:
        return A024_S8(obj, 0x2CA);
    case 0xB9: /* path point args[2] of path +0x13F: x << 16 | z */
        list = (s16 *)D_800D2104[A024_U8(obj, 0x13F)] + args[2] * 4;
        return (list[0] << 16) | (list[2] & 0xFFFF);
    case 0xBA:
        list = (s16 *)D_800D2104[A024_U8(obj, 0x13F)] + args[2] * 4;
        return list[1];
    case 0xBB:
        if (A024_U8(obj, 0x65) == 0) {
            return -1;
        }
        return A024_U8(&D_800CC2D0[A024_U8(obj, 0x65) - 1], 0x13F);
    case 0xBC:
        return A024_U8(obj, 0x13C);
    case 0xBD: /* xz distance to object args[2] */
        other = A024_OBJ(args[2]);
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return sqrtf(dx * dx + dz * dz);
    case 0xBE:
        return A024_F32(obj, 0x20);
    case 0xBF:
        return (f32)(s32)A024_F32(obj, 0x28) * 65536.0f;
    case 0xC0:
        return A024_U8(A024_REC(obj), 0x1B);
    case 0xC1:
        return A024_U8(A024_REC(obj), 0x4E);
    case 0xC2:
        return A024_U8(obj, 0x3B);
    case 0xC3:
        return A024_S32(obj, 0xF4);
    case 0xC4:
        return A024_S32(obj, 0x25C);
    case 0xC5:
        return A024_U8(obj, 0x89);
    case 0xC6: /* player_stat_get(index, 6) for the first D_8008FD8C objects */
        n = A024_INDEX(obj);
        if (n < 0 || n >= D_8008FD8C) {
            return 0;
        }
        return player_stat_get(A024_INDEX(obj), 6);
    case 0xC7:
        if (A024_U8(obj, 0x211) == 0xFF) {
            return 1;
        }
        return A024_S32(obj, 0x25C) & 0x800;
    case 0xC8: /* distance to the point +0x20F (+ +0x216), or to the point +0x211 when that is farther */
        if (A024_U8(obj, 0x20F) == 0xFF || A024_U8(obj, 0x211) == 0xFF) {
            return 0;
        }
        best = -1;
        if (rail_node_position(A024_U8(obj, 0x20F), &px, &py, &pz) != 0) {
            px -= obj->x_position;
            py -= obj->y_position;
            pz -= obj->z_position;
            best = (s32)sqrtf(px * px + py * py + pz * pz) + A024_S16(obj, 0x216);
            if (A024_U8(obj, 0x211) != A024_U8(obj, 0x20F)
                && rail_node_position(A024_U8(obj, 0x211), &px, &py, &pz) != 0) {
                px -= obj->x_position;
                py -= obj->y_position;
                pz -= obj->z_position;
                r = sqrtf(px * px + py * py + pz * pz);
                if (best < r) {
                    return r;
                }
            }
        }
        return best;
    case 0xC9:
        return rail_band_for_height(obj->y_position);
    case 0xCA: /* the point +0x20F, else the nearest one (stored in +0x213) */
        none = 0xFF;
        if (A024_U8(obj, 0x20F) != 0xFF) {
            return A024_POINT(A024_U8(obj, 0x20F));
        }
        D_8008763C = A024_U8(obj, 0x213);
        r = rail_point_pick(obj->x_position, obj->y_position, obj->z_position, 0, 0, &none, &none);
        A024_U8(obj, 0x213) = r;
        if (r != 0xFF) {
            return A024_POINT(r);
        }
        return 0xFF;
    case 0xCB: /* distance to object args[2] if the ray to it is clear */
        other = A024_OBJ(args[2]);
        if (other == NULL) {
            return 0;
        }
        dx = other->x_position - obj->x_position;
        dy = other->y_position - obj->y_position;
        dz = other->z_position - obj->z_position;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (collision_ray_cast(obj->x_position, obj->y_position + 100.0f, obj->z_position, dx, dy, dz, 0, 0,
                          &hit[3], &hit[2], &hit[1], &hit[0], 0, 0, 0.0f) == 0) {
            return dist;
        }
        if (dist < hit[0]) {
            if (0.0f < rail_wall_hit(obj->x_position, obj->y_position, obj->z_position, dx, dz)) {
                return 0;
            }
            return dist;
        }
        return 0;
    case 0xCC: /* index of the D_800D34B8 record (0x34 bytes) at the object's position */
        p = (u8 *)trigger_find_at_point(3, 0xB, obj->x_position, obj->y_position, obj->z_position);
        if (p == NULL) {
            return -1;
        }
        return (p - D_800D34B8) / 0x34;
    case 0xCD: /* angle between the heading +0x40 and the direction to object args[2] (args[3] == 1: absolute) */
        other = A024_OBJ(args[2]);
        r = math_atan2_u16(other->x_position - obj->x_position, other->z_position - obj->z_position, 0);
        dist = A024_F32(obj, 0x40);
        d = wrap_angle_deg((f32)(r + 0x4000) * A024_DEG);
        d = wrap_angle_deg(wrap_angle_deg(dist) - d);
        if (180.0f < d) {
            d += -360.0f;
        }
        if (args[3] == 1 && d < 0.0f) {
            d = -d;
        }
        return d;
    case 0xCE: /* pitch to object args[2] (args[3] == 1: absolute) */
        other = A024_OBJ(args[2]);
        dx = other->x_position - obj->x_position;
        dz = other->z_position - obj->z_position;
        dy = other->y_position - obj->y_position;
        r = math_atan2_u16(sqrtf(dx * dx + dz * dz), dy, 0);
        d = wrap_angle_deg((f32)(u32)r * A024_DEG);
        if (180.0f < d) {
            d += -360.0f;
        }
        if (args[3] == 1 && d < 0.0f) {
            d = -d;
        }
        return d;
    case 0xCF: /* nearest of the args[2] points args[3..] */
        sel = 0;
        count = 0;
        for (i = 0; i < args[2]; i++) {
            found[count] = rail_node_find_by_tag(args[3 + i]);
            if (found[count] != 0xFF) {
                count++;
            }
        }
        best = -1;
        if (count != 0) {
            r = rail_point_pick(obj->x_position, obj->y_position, obj->z_position, count, sel, found, &sel);
            D_80087638 = 0xFF;
            if ((u8)r != 0xFF) {
                rail_route_next((u8)r, count, sel, found, &sel);
            }
            if (D_80087638 != 0xFF) {
                best = A024_POINT(D_80087638);
            }
        }
        return best;
    case 0xD0: /* xz distance to point args[2] (30000 when there is none) */
        if (rail_node_position(rail_node_find_by_tag(args[2]), &px, &py, &pz) == 0) {
            return 30000;
        }
        px -= obj->x_position;
        pz -= obj->z_position;
        return sqrtf(px * px + pz * pz);
    case 0xD1: /* read and clear flag 0x100 of +0x22C */
        n = A024_U16(obj, 0x22C);
        A024_U16(obj, 0x22C) = n & ~0x100;
        return n & 0x100;
    case 0xD2:
        n = A024_U16(obj, 0x22C);
        A024_U16(obj, 0x22C) = n & ~0x200;
        return n & 0x200;
    case 0xD3: /* class of the record's kind (+0x75) */
        rec = A024_REC(obj);
        if (rec == NULL) {
            return 0;
        }
        switch (A024_U8(rec, 0x75) & 0x7F) {
        case 0x03:
        case 0x09:
        case 0x15:
            return 2;
        case 0x21:
        case 0x22:
            return 3;
        case 0x14:
        case 0x16:
        case 0x18:
        case 0x23:
        case 0x24:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3F:
        case 0x41:
            return 1;
        }
        return 0;
    case 0xD4:
        rec = A024_REC(obj);
        if (rec == NULL) {
            return 0;
        }
        return A024_U8(rec, 0x78);
    case 0xD5:
        return mp_is_free_for_all();
    case 0xD6:
        return mp_match_check_over();
    case 0xD7:
        return (600.0f < A024_F32(obj, 0x1CC) - obj->y_position && D_8009E80C == A024_F32(obj, 0x118)) ? 1 : 0;
    case 0xD8:
        return obj->in_water;
    case 0xD9:
        return (A024_U8(obj, 0xA9) == 2) ? 1 : 0;
    case 0xDA:
        return A024_F32(obj, 0x180);
    case 0xDB: /* the point +0x20F (args[2] == 1) or +0x211 */
        if (args[2] == 1) {
            if (A024_U8(obj, 0x20F) == 0xFF) {
                return 0xFF;
            }
            return A024_POINT(A024_U8(obj, 0x20F));
        }
        if (A024_U8(obj, 0x211) == 0xFF) {
            return 0xFF;
        }
        return A024_POINT(A024_U8(obj, 0x211));
    case 0xDC:
        if (A024_S8(A024_REC(obj), 0x195) == 0) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x196) | 0x80;
    case 0xDD:
        if (A024_REC(obj) == NULL) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x23);
    case 0xDE:
        return A024_INDEX(obj);
    case 0xDF:
        if (A024_REC(obj) == NULL) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x1AE);
    case 0xE0:
        return A024_F32(obj, 0x150) * 65536.0f;
    case 0xE1:
        return A024_U8(obj, 0x125);
    case 0xE2:
        return A024_U8(A024_REC(obj), 0x7D);
    case 0xE3:
        return D_800D1CC9;
    case 0xE4:
        return D_800D18A8;
    case 0xE5:
        return A024_U8(obj, 0x275);
    case 0xE6: /* read and clear +0x275 (object number + 1): is that object's +4 byte args[2]? */
        n = A024_U8(obj, 0x275);
        if (n == 0) {
            return 0;
        }
        A024_U8(obj, 0x275) = 0;
        return (A024_U8(&D_800CC2D0[n - 1], 4) == args[2]) ? 1 : 0;
    case 0xE7: /* nearest point of path +0x13F to object args[2], squared xz distance in (args[3]^2, args[4]^2) */
        n = A024_U8(obj, 0x13F);
        list = (s16 *)D_800D2104[n];
        i = D_800D2528[n];
        best = -1;
        if (list == NULL || i == 0) {
            return -1;
        }
        other = A024_OBJ(args[2]);
        ox = other->x_position;
        oz = other->z_position;
        maxD = 100000000;
        minD = -1;
        if (D_800D3C60 >= 4) {
            minD = args[3] * args[3];
            if (D_800D3C60 >= 5) {
                maxD = args[4] * args[4];
            }
        }
        for (n = 0; n < i; n++, list += 4) {
            r = (list[2] - oz) * (list[2] - oz) + (list[0] - ox) * (list[0] - ox);
            if (r < maxD && minD < r) {
                best = n;
                maxD = r;
            }
        }
        return best;
    case 0xE8:
        return A024_U16(obj, 0x84);
    case 0xE9:
        return A024_U8(A024_REC(obj), 0x51);
    case 0xEA:
        p = attachment_find_by_slot(obj, args[2], args[3]);
        if (p != NULL) {
            return A024_S32(p, 0x38);
        }
        return 0;
    case 0xEB: /* the object's xz position clamped to the circle (args[2], args[3]) radius args[4] */
        px = (f32)args[2];
        pz = (f32)args[3];
        d = (f32)args[4];
        dx = obj->x_position - px;
        dz = obj->z_position - pz;
        dist = dz * dz + dx * dx;
        if (dist <= d * d) {
            return ((s32)obj->x_position << 16) | ((s32)obj->z_position & 0xFFFF);
        }
        d = d / sqrtf(dist);
        return ((s32)(dx * d + px) << 16) | ((s32)(dz * d + pz) & 0xFFFF);
    case 0xEC:
        return A024_U8(A024_REC(obj), 0x95);
    case 0xED:
        return D_800BEB30[id];
    case 0xEE: /* the point args[2] ahead of the object (heading +0x7A turned 180 degrees): x << 16 | z */
        vec_from_yaw_pitch(A024_U16(obj, 0x7A) + 0x8000, (f32)args[2], 0.0f, &hit[2], &hit[0], &hit[1]);
        return ((s32)((f32)(s16)(s32)obj->x_position + hit[2]) << 16)
             | ((s32)((f32)(s16)(s32)obj->z_position + hit[0]) & 0xFFFF);
    case 0xEF:
        return A024_S32(obj, 0);
    case 0xF0:
        return D_800E0EF0[A024_U8(obj, 0x128)];
    case 0xF1:
        return ((A024_U8(obj, 0x74) & 0xF) == 0xF) ? 1 : 0;
    case 0xF2:
        if (A024_U8(obj, 0x13C) == 0) {
            return 0;
        }
        return A024_U8(&D_800CC2D0[A024_U8(obj, 0x13C)], 0x13F) | 0x2000;
    case 0xF3:
        return (A024_U8(obj, 0xA9) == 2) ? 1 : 0;
    }
    return 0;
}
