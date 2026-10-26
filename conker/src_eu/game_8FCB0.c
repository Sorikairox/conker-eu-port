#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void character_hit_react(struct127 *obj, struct127 *target, u8 attached);


void obj_water_buoyancy(struct127 *arg0, f32, f32);
u8   obj_turn_towards(struct127 *arg0, u8 arg1, u16 arg2);
void move_xz_towards(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  obj_approach_speed(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  obj_apply_hit(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 obj_receive_hit(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

// EU: split from game_83300.c, EU pads to a file boundary before this.

void attachment_swap_owner_ids(s32, s32);
// object_slots_swap: P259: swaps the objects `a` and `b` of g_objects (after obj_broadcast_replace(a, b)), then fixes up
// what is tied to the slot rather than the object: each object's index fields (+0x127 / +0x13F = index, unique_id =
// index + 1) and its +0x144 pointer (kept in the slot); `b` gets the camera record g_player_views[index of b] (whose
// +0x3D4 takes b's +0x31C, and that record's byte +0x197 is cleared), `a` none; attachment_swap_owner_ids swaps the unique ids;
// both objects' +0x2D4 handles are released (node_destroy); other live objects' +0x65 links (unique id) to either
// slot are swapped; when b's +0x13C names a carrier (>= 100), that object's +0x13D = 100 + b's index; then
// obj_fade_reset(b) / obj_model_reset(b).
/* was func_15062800 */
void obj_slots_swap(struct127 *a, struct127 *b) {
    struct127 tmp;
    struct129 *p144;
    struct127 *obj;
    s32 ia;
    s32 ib;
    s32 i;
    u8 link;

    obj_broadcast_replace(a, b);
    bcopy(b, &tmp, sizeof(struct127));
    bcopy(a, b, sizeof(struct127));
    bcopy(&tmp, a, sizeof(struct127));
    ib = b - g_objects;
    ia = a - g_objects;
    b->unk127 = ib;
    b->unique_id = ib + 1;
    b->unk13F = ib;
    b->camera = &g_player_views[ib];
    a->unk127 = ia;
    a->unique_id = ia + 1;
    a->unk13F = ia;
    a->camera = NULL;
    p144 = b->unk144;
    b->unk144 = a->unk144;
    a->unk144 = p144;
    *(struct126 **) ((u8 *) &g_player_views[ib] + 0x3D4) = b->unk31C;
    *((u8 *) b->unk31C + 0x197) = 0;
    attachment_swap_owner_ids(b->unique_id, a->unique_id);
    if (b->unk2D4 != NULL) {
        node_destroy((struct102 *) b->unk2D4);
        b->unk2D4 = NULL;
    }
    if (a->unk2D4 != NULL) {
        node_destroy((struct102 *) a->unk2D4);
        a->unk2D4 = NULL;
    }
    obj_fade_reset(b);
    for (i = 0; i < 25; i++) {
        if (i == ib || i == ia) {
            continue;
        }
        obj = &g_objects[i];
        if (obj->interaction_state == 0 || obj->unk65 == 0) {
            continue;
        }
        link = obj->unk65 - 1;
        if (link == ib) {
            obj->unk65 = ia + 1;
        } else if (link == ia) {
            obj->unk65 = ib + 1;
        }
    }
    if (b->unk13C >= 100) {
        g_objects[(u8) (b->unk13C - 100)].unk13D = ib + 100;
    }
    obj_model_reset(b);
}

/* was func_15062AC4 */
void obj_update_inner_extent_ratios(struct127 *arg0) {
    if (arg0->unkE6 && arg0->unkE4) {
        f32 tmp = arg0->unkE4;
        arg0->unkEC = tmp / arg0->unkE6;
        arg0->unkF0 = arg0->unkE6 / tmp;
    } else {
        arg0->unkF0 = arg0->unkEC = 0.0f;
    }
}

/* was func_15062B1C */
void obj_set_inner_extent_width(struct127 *arg0, f32 arg1) {
    arg0->unkE4 = arg0->xz_scale * arg1;
    obj_update_inner_extent_ratios(arg0);
}

/* was func_15062B50 */
void obj_set_inner_extent_height(struct127 *arg0, f32 arg1) {
    arg0->unkE6 = arg0->y_scale * arg1;
    obj_update_inner_extent_ratios(arg0);
}

/* was func_15062B84 */
void obj_update_outer_extent_ratios(struct127 *arg0) {
    if (arg0->unkD4 && arg0->unkD2) {
        f32 tmp = arg0->unkD2;
        arg0->unkDC = tmp / arg0->unkD4;
        arg0->unkE0 = arg0->unkD4 / tmp;
    } else {
        arg0->unkDC = 0.0f;
        arg0->unkE0 = 0.0f;
    }
}

/* was func_15062BDC */
void obj_set_scale(struct127 *arg0, f32 arg1, f32 arg2) {
    struct124 *temp_v0;

    arg0->xz_scale = arg1;
    arg0->y_scale = arg2;
    if (arg0->id != 255) {
        temp_v0 = g_type_descs[arg0->id];
        arg0->unkD2 = (s32) (temp_v0->unk20 * arg0->xz_scale);
        arg0->unkD4 = (s32) (temp_v0->unk22 * arg0->y_scale);
        arg0->unkD6 = (s32) (temp_v0->unk24 * arg0->y_scale);
        arg0->unkE4 = (s32) (temp_v0->unk1A * arg0->xz_scale);
        arg0->unkE6 = (s32) (temp_v0->unk1C * arg0->y_scale);
        arg0->unkE8 = (s32) (temp_v0->unk1E * arg0->y_scale);
        obj_update_inner_extent_ratios(arg0);
        obj_update_outer_extent_ratios(arg0);
    }
}

extern s32 g_model_dl_tables; /* was D_800C48A8 */

/* was func_15062D10 */
void gfx_tile_scroll_coords(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    if ((&g_model_bases)[arg0] != 0) {
        temp_a3 = *(s32 *)(*(s32 *)((u8 *)&g_model_dl_tables + (arg0 * 4)) + (arg4 * 4)) + (arg1 * 8);
        temp_a2 = (*(s32 *)((u8 *)temp_a3 + 4));
        temp_v1 = ((temp_a2 >> 0xC) & 0xFFF) + 2;
        temp_a0 = (temp_a2 & 0xFFF) + 2;
        temp_a2_2 = (*(s32 *)((u8 *)temp_a3 + 0));
        if (arg5 != 0) {
            var_v0 = arg2 & 0xFFF;
        } else {
            temp_a1 = ((temp_a2_2 >> 0xC) & 0xFFF) + arg2;
            var_v0 = temp_a1;
            if (temp_v1 < temp_a1) {
                var_v0 = temp_a1 - temp_v1;
            } else if (temp_a1 < 0) {
                var_v0 = temp_a1 + temp_v1;
            }
        }
        if (arg5 != 0) {
            var_v1 = arg3 & 0xFFF;
        } else {
            temp_a1_2 = (temp_a2_2 & 0xFFF) + arg3;
            var_v1 = temp_a1_2;
            if (temp_a0 < temp_a1_2) {
                var_v1 = temp_a1_2 - temp_a0;
            } else if (temp_a1_2 < 0) {
                var_v1 = temp_a1_2 + temp_a0;
            }
        }
        (*(s32 *)((u8 *)temp_a3 + 0)) = (s32) ((temp_a2_2 & 0xFF000000) | (var_v1 & 0xFFF) | ((var_v0 & 0xFFF) << 0xC));
    }
}
extern u8 *g_model_tex_entries[]; /* per object type: 12-byte texture entries, u16 size at +8 / +0xA; was D_800C5758 */
void uv_rotate(u8 *, s32 *, s32, f32, s32, s32);

// type_texture_scroll_apply: for every live object (+0x0) of `type` (+0x4) with +0x2FA set and a display list
// for the current screen (+0x28C[g_dl_buf_index]), calls uv_rotate on entry `dl` (16-byte steps) of it with the
// type's texture-command table g_model_vtx_ptr_tables[type] at `cmd`, `arg2`, the amount `amount`, and the size of texture
// `tex` of g_model_tex_entries[type] (doubled when `twice`).
/* was func_15062E24 */
void obj_type_tex_scroll_apply(s32 type, s32 dl, s32 arg2, s32 cmd, s32 amount, s32 tex, s32 twice) {
    s32 *table;
    struct127 *o;
    u8 *entry;
    u8 *list;
    s32 w;
    s32 h;
    s32 i;

    if (g_model_vtx_ptr_tables[type] == 0) {
        return;
    }
    for (i = 0, o = g_objects; i < 25; i++, o++) {
        if (*(s32 *) o == 0 || type != *((u8 *) o + 4) || o->unk2FA == 0) {
            continue;
        }
        entry = g_model_tex_entries[type] + tex * 12;
        w = *(u16 *) (entry + 8);
        h = *(u16 *) (entry + 0xA);
        if (twice) {
            w *= 2;
            h *= 2;
        }
        list = ((u8 **) &g_objects[i].unk28C)[g_dl_buf_index];
        if (list != NULL) {
            table = (s32 *) g_model_vtx_ptr_tables[type];
            uv_rotate(list + dl * 16, &table[cmd], arg2, (f32) amount, h, w);
        }
    }
}
extern s32 g_model_part_tables; /* was D_800C4440 */

/* was func_15062FC0 */
void obj_vtx_scroll_uv(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s16 temp_a1;
    s16 temp_a3;
    s16 temp_t5;
    s16 temp_t9;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t4;
    s32 temp_t7;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v1;
    u8 *temp_a2;
    u8 *var_t1;
    u8 *var_t1_2;
    u8 *var_t2;
    u8 *var_t2_2;
    u8 *var_v0;

    temp_a2 = arg0 + ((*(u8 *)((u8 *)arg0 + 0x1C8)) * 8);
    var_v0 = (*(u8 **)((u8 *)((temp_a2 + (g_dl_buf_index * 4))) + 0x28C));
    var_v1 = (*(s32 *)((u8 *)((temp_a2 + ((g_dl_buf_index == 0) * 4))) + 0x28C));
    if (var_v0 != NULL) {
        if (arg1 != -1) {
            temp_t7 = *(s32 *)(*(s32 *)(((s32 *)((u8 *)&g_model_part_tables + ((*(u8 *)((u8 *)arg0 + 4)) * 4)))) + (arg1 * 4)) * 0x10;
            var_v0 += temp_t7;
            var_v1 += temp_t7;
        }
        var_a0 = arg6;
        if (var_a0 != 0) {
            temp_a1 = (*(s16 *)((u8 *)var_v0 + 8));
            if (arg3 < temp_a1) {
                var_a0 -= arg3;
            } else if (temp_a1 < 0) {
                var_a0 += arg3;
            }
        }
        var_a1 = arg7;
        if (var_a1 != 0) {
            temp_a3 = (*(s16 *)((u8 *)var_v0 + 0xA));
            if (arg4 < temp_a3) {
                var_a1 -= arg4;
            } else if (temp_a3 < 0) {
                var_a1 += arg4;
            }
        }
        var_a2 = 0;
        temp_t4 = arg5 & 3;
        if (arg5 > 0) {
            if (temp_t4 != 0) {
                temp_t0 = 0 * 0x10;
                var_t1 = var_v0 + temp_t0;
                var_t2 = var_v1 + temp_t0;
                do {
                    var_a2 += 1;
                    var_t1 += 0x10;
                    (*(s16 *)((u8 *)var_t1 + -8)) = (s16) ((*(s16 *)((u8 *)var_t2 + 8)) + var_a0);
                    temp_t5 = (*(s16 *)((u8 *)var_t2 + 0xA));
                    var_t2 += 0x10;
                    (*(s16 *)((u8 *)var_t1 + -6)) = (s16) (temp_t5 + var_a1);
                } while (temp_t4 != var_a2);
                if (var_a2 != arg5) {
                    goto block_18;
                }
            } else {
block_18:
                temp_t0_2 = var_a2 * 0x10;
                var_t1_2 = var_v0 + temp_t0_2;
                var_t2_2 = var_v1 + temp_t0_2;
                do {
                    var_a2 += 4;
                    var_t1_2 += 0x40;
                    (*(s16 *)((u8 *)var_t1_2 + -0x38)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + 8)) + var_a0);
                    temp_t9 = (*(s16 *)((u8 *)var_t2_2 + 0xA));
                    var_t2_2 += 0x40;
                    (*(s16 *)((u8 *)var_t1_2 + -0x36)) = (s16) (temp_t9 + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -0x28)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x28)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -0x26)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x26)) + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -0x18)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x18)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -0x16)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x16)) + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -8)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -8)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -6)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -6)) + var_a1);
                } while (var_a2 != arg5);
            }
        }
    }
}
/* was func_15063168 */
void obj_hit_react_other_players(struct127 *arg0) {
    s32 i;

    for (i = 0; i < g_player_count; i++) {
        if ((i != (arg0 - g_objects)) && ((1 << i) & g_obj_contact_mask)) {
            if ((g_objects[i].unk31C != NULL) && (((u8 *)g_objects[i].unk31C)[0x1AC] == 0)) {
                character_hit_react(arg0, &g_objects[i], 1);
            }
        }
    }
}
void obj_remove(struct127 *obj, s32 mode);
s32 setup_entry_spawn(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

// obj_model_swap_keep_pose: sets the object's model record (+0x144: +4 = `a1`, +3 = `a2`, +0x20 / +0x24 = `scale`,
// +2 = 0), resets the object (obj_remove mode 0) and reloads model slot +0x13F (setup_entry_spawn, owner = object
// index + 1), then puts back what the reset clears: position (+0x14..+0x1C, copied to +0x2C..+0x34, y also to
// +0x1CC), +0x318 (whose +0x3D4 gets the object's +0x31C), +0xB8, +0x40, +0xC4 and the yaw (+0x76, also +0x7A).
/* was func_15063254 */
void obj_model_swap_keep_pose(struct127 *obj, s32 a1, s32 a2, f32 scale) {
    u8 *o = (u8 *) obj;
    u8 slot = o[0x13F];
    u8 *e = *(u8 **) (o + 0x144);
    u8 *link;
    f32 x;
    f32 y;
    f32 z;
    f32 fB8;
    f32 f40;
    f32 fC4;
    u16 yaw;

    e[4] = a1;
    e[3] = a2;
    *(f32 *) (e + 0x20) = scale;
    *(f32 *) (e + 0x24) = scale;
    e[2] = 0;
    link = *(u8 **) (o + 0x318);
    x = *(f32 *) (o + 0x14);
    y = *(f32 *) (o + 0x18);
    z = *(f32 *) (o + 0x1C);
    fB8 = *(f32 *) (o + 0xB8);
    f40 = *(f32 *) (o + 0x40);
    fC4 = *(f32 *) (o + 0xC4);
    yaw = *(u16 *) (o + 0x76);
    obj_remove(obj, 0);
    setup_entry_spawn(e, slot, 0, 0, (obj - g_objects) + 1);
    *(f32 *) (o + 0x14) = x;
    *(f32 *) (o + 0x18) = y;
    *(u8 **) (o + 0x318) = link;
    *(f32 *) (o + 0x1C) = z;
    *(f32 *) (o + 0xB8) = fB8;
    *(f32 *) (o + 0x40) = f40;
    *(u16 *) (o + 0x76) = yaw;
    *(u16 *) (o + 0x7A) = yaw;
    *(f32 *) (o + 0x2C) = x;
    *(f32 *) (o + 0x30) = y;
    *(f32 *) (o + 0x1CC) = *(f32 *) (o + 0x18);
    *(f32 *) (o + 0x34) = *(f32 *) (o + 0x1C);
    *(f32 *) (o + 0xC4) = fC4;
    *(s32 *) (link + 0x3D4) = *(s32 *) (o + 0x31C);
}
