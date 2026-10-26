#include <ultra64.h>
/* P132 / P137: effect3d_spawn_default returns the new record; functions.h declares it `struct210 *` under NON_MATCHING
 * (port-b P128 definition in game_169510.c), so no local prototype override is needed. */
#include "functions.h"
#include "variables.h"


// particle_emitter_spawn: spawns a particle record from the spawn block (type byte 1 = 3, flags 0x40400000 set
// first) through effect3d_spawn_default, copies the emitter block (emitSize bytes) to rec + 0x110, clears its word +0x44,
// stores arg7 at +0x59 and counts the record in g_particle_emitter_count. Returns the record or NULL. level_fire_emitters_create passes
// (emit, 0x7C, spawn, 0, 0x20, 0, 0, -1, 0xFF, 1).
/* was func_151407D0 */
struct210 *particle_emitter_spawn(void *emit, s32 emitSize, u8 *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                         s32 arg9) {
    struct210 *rec;
    u8 *e;

    spawn[1] = 3;
    *(u32 *) (spawn + 0x40) |= 0x40400000;
    rec = effect3d_spawn_default((s32) spawn, arg3, arg4, arg5, 1, arg6, emitSize, arg8, arg9);
    if (rec == NULL) {
        return NULL;
    }
    e = (u8 *) rec + 0x110;
    memcpy(e, emit, emitSize);
    *(s32 *) (e + 0x44) = 0;
    e[0x59] = arg7;
    if (rec != NULL) {
        g_particle_emitter_count++;
    }
    return rec;
}

s32 world_to_screen(f32 *pos, f32 *scr, f32 *oz, f32 *ow, f32 *oinv, u8 view);
void vtx_slot_buffer_get(s32 *, s16, s32, s32 *, u8 *);
extern s32 (*g_effect_kind_check_fns[])(u8 *, s16); /* was D_8008A330 */
extern s32 D_800899D0[8][2];   /* z-buffer decode per exponent (code >> 13): {shift, add} */
// particle_glow_update: per-player update of a light-flare particle (record from particle_emitter_spawn, emitter block at
// +0x110). Runs the kind check g_effect_kind_check_fns[+0x169] (-1 = none), clears the player's screen cell (+0x134 / +0x144),
// needs flag 2 (+0x58), projects the source (+0x34) with world_to_screen and drops it outside the player's viewport
// (D_800BE628[player] +0x24..+0x30). Gets 4 vertices from vtx_slot_buffer_get (copying the 0x40-byte template at +0xC0
// into a fresh buffer), normalises the axis (+0x40 = source + 500 * dir, once, flag 4), takes the facing term
// dot(axis, camera - source) (0 = drop unless flag 0x10000), fades with distance (1 - e[0x20] * dist), and with
// flag 0x10 tests occlusion: the projected depth (viewport scale 0x44 / 0x4C, x32) against the z-buffer code at
// e[0x4C + 2 * player] decoded through D_800899D0 (visible if depth - zbuf < 0x1F); the per-player intensity
// e[0x54 + player] eases towards 0xFF or 0 by 1/8 per frame (0xFF without flag 0x10). The quad is centred between
// the source and the camera (lerp e[0x14]..e[0x10]), sized lerp e[8]..e[0] / e[0xC]..e[4] times e[0x48], laid
// out perpendicular to the view direction; alpha +0x5C = intensity * lerp(e[0x1C]..e[0x18]) * 255 >> 8, copied
// (scaled by +0x2B) into the linked object's +0x30. Returns the vertex buffer or NULL.
/* was func_151408A4 */
u8 *effect_flare_update(u8 *obj, s16 player) {
    u8 *e;
    f32 *cam;
    f32 *view;
    u8 *verts;
    u8 *link;
    u8 reload;
    f32 scr[2];
    f32 oz;
    f32 ow;
    f32 oinv;
    f32 dx, dy, dz, d2, s;
    f32 r0, r1, r2;
    f32 ax, ay, az;
    f32 facing, dist, fade, inv, horiz, ih;
    f32 t, px, py, pz, w, h, hh, wh;
    f32 ux, uy, uz, vx, vz;
    s32 vis;
    s32 visible;
    s16 depth = 0;
    u32 code;
    u32 zbuf;
    s16 alpha;

    if ((s8) obj[0x169] != -1) {
        if (g_effect_kind_check_fns[(s8) obj[0x169]](obj, player) == 0) {
            return NULL;
        }
    }
    e = obj + 0x110;
    *(s32 *) (e + player * 4 + 0x34) = -1;
    *(s32 *) (e + player * 4 + 0x24) = -1;
    if (!(*(s32 *) (obj + 0x58) & 2)) {
        return NULL;
    }
    vis = world_to_screen((f32 *) (obj + 0x34), scr, &oz, &ow, &oinv, player);
    if (vis == 0) {
        return NULL;
    }
    view = (f32 *) ((u8 *) D_800BE628 + player * 0x180);
    if (scr[0] < view[0x2C / 4] || view[0x30 / 4] < scr[0] || scr[1] < view[0x24 / 4] || view[0x28 / 4] < scr[1]) {
        return NULL;
    }
    cam = camera_get_pos(player);
    vtx_slot_buffer_get((s32 *) (obj + 0x100), player, 0x40, (s32 *) &verts, &reload);
    if (verts == NULL) {
        return NULL;
    }
    if (reload) {
        memcpy(*(u8 **) (obj + player * 4 + 0x100), obj + 0xC0, 0x40);
        memcpy(*(u8 **) (obj + player * 4 + 0x100) + 0x40, obj + 0xC0, 0x40);
    }
    if (!(*(s32 *) (obj + 0x58) & 4)) {
        dy = *(f32 *) (obj + 0x44) - *(f32 *) (obj + 0x38);
        dx = *(f32 *) (obj + 0x40) - *(f32 *) (obj + 0x34);
        dz = *(f32 *) (obj + 0x48) - *(f32 *) (obj + 0x3C);
        d2 = dx * dx + dy * dy + dz * dz;
        if (d2 == 0.0f) {
            *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C) + 500.0f;
        } else {
            s = 500.0f / sqrtf(d2);
            *(f32 *) (obj + 0x40) = *(f32 *) (obj + 0x34) + dx * s;
            *(f32 *) (obj + 0x44) = *(f32 *) (obj + 0x38) + dy * s;
            *(f32 *) (obj + 0x48) = *(f32 *) (obj + 0x3C) + dz * s;
        }
        *(s32 *) (obj + 0x58) |= 4;
    }
    r0 = cam[0] - *(f32 *) (obj + 0x34);
    r1 = cam[1] - *(f32 *) (obj + 0x38);
    r2 = cam[2] - *(f32 *) (obj + 0x3C);
    ax = *(f32 *) (obj + 0x40) - *(f32 *) (obj + 0x34);
    ay = *(f32 *) (obj + 0x44) - *(f32 *) (obj + 0x38);
    az = *(f32 *) (obj + 0x48) - *(f32 *) (obj + 0x3C);
    facing = ax * r0 + ay * r1 + az * r2;
    if (facing < 0.0f) {
        facing = 0.0f;
    }
    if (facing == 0.0f && !(*(s32 *) (obj + 0x58) & 0x10000)) {
        return NULL;
    }
    if (!(fabsf(r0) > 0.0001f) && !(fabsf(r2) > 0.0001f)) {
        return NULL;
    }
    dist = sqrtf(r0 * r0 + r1 * r1 + r2 * r2);
    fade = 1.0f - *(f32 *) (e + 0x20) * dist;
    if (!(fade > 0.0f)) {
        return NULL;
    }
    code = *(u16 *) (e + player * 2 + 0x4C);
    zbuf = (u32) (D_800899D0[code >> 13][1] + (((code >> 2) & 0x7FF) << D_800899D0[code >> 13][0])) >> 3;
    if (*(s32 *) (obj + 0x58) & 0x10) {
        visible = 1;
        if (vis != 0) {
            *(s32 *) (e + player * 4 + 0x24) = (s32) scr[0];
            *(s32 *) (e + player * 4 + 0x34) = (s32) scr[1];
            view = (f32 *) ((u8 *) D_800BE628 + player * 0x180 + D_800BE9C0 * 0x10);
            depth = (s32) (((f32) *(s16 *) ((u8 *) view + 0x4C) + oz * oinv * (f32) *(s16 *) ((u8 *) view + 0x44)) *
                           32.0f);
        } else {
            *(s32 *) (e + player * 4 + 0x24) = -1;
            *(s32 *) (e + player * 4 + 0x34) = -1;
            visible = 0;
        }
        if (depth - (s32) zbuf >= 0x1F) {
            visible = 0;
        }
        if (visible) {
            e[0x54 + player] += (0xFF - e[0x54 + player]) >> 3;
        } else {
            e[0x54 + player] -= e[0x54 + player] >> 3;
        }
    } else {
        e[0x54 + player] = 0xFF;
    }
    inv = 1.0f / dist;
    horiz = sqrtf(r0 * r0 + r2 * r2);
    facing = facing * (fade * inv * 0.002f);
    t = *(f32 *) (e + 0x14) + (*(f32 *) (e + 0x10) - *(f32 *) (e + 0x14)) * facing;
    px = *(f32 *) (obj + 0x34) + t * r0;
    py = *(f32 *) (obj + 0x38) + t * r1;
    pz = *(f32 *) (obj + 0x3C) + t * r2;
    w = (*(f32 *) (e + 8) + (*(f32 *) (e + 0) - *(f32 *) (e + 8)) * facing) * *(f32 *) (e + 0x48);
    h = (*(f32 *) (e + 0xC) + (*(f32 *) (e + 4) - *(f32 *) (e + 0xC)) * facing) * *(f32 *) (e + 0x48);
    ih = 1.0f / horiz;
    wh = w * ih;
    hh = h * (ih * inv);
    ux = -r0 * r1 * hh;  /* up vector (perpendicular to the view, in the vertical plane) */
    uy = h * horiz * inv;
    uz = -r2 * r1 * hh;
    vx = -r2 * wh;       /* side vector (horizontal) */
    vz = -r0 * wh;
    *(s16 *) (verts + 0) = (s32) (ux + vx + px);
    *(s16 *) (verts + 2) = (s32) (uy + py);
    *(s16 *) (verts + 4) = (s32) (uz - vz + pz);
    *(s16 *) (verts + 6) = 0;
    *(s16 *) (verts + 0x10) = (s32) (ux - vx + px);
    *(s16 *) (verts + 0x12) = (s32) (uy + py);
    *(s16 *) (verts + 0x14) = (s32) (uz + vz + pz);
    *(s16 *) (verts + 0x16) = 0;
    *(s16 *) (verts + 0x20) = (s32) (-ux - vx + px);
    *(s16 *) (verts + 0x22) = (s32) (py - uy);
    *(s16 *) (verts + 0x24) = (s32) (-uz + vz + pz);
    *(s16 *) (verts + 0x26) = 0;
    *(s16 *) (verts + 0x30) = (s32) (-ux + vx + px);
    *(s16 *) (verts + 0x32) = (s32) (py - uy);
    *(s16 *) (verts + 0x34) = (s32) (-uz - vz + pz);
    *(s16 *) (verts + 0x36) = 0;
    alpha = (s32) ((*(f32 *) (e + 0x1C) + (*(f32 *) (e + 0x18) - *(f32 *) (e + 0x1C)) * facing) * 255.0f);
    obj[0x5C] = (e[0x54 + player] * alpha) >> 8;
    link = *(u8 **) (e + 0x44);
    if (link != NULL) {
        link[0x30] = (obj[0x5C] * obj[0x2B]) >> 8;
    }
    return verts;
}

/* was func_151411A4 */
void effect_free_buffers_retire(struct210 *arg0) {
    effect3d_retire(arg0);
}

/* was func_151411C4 */
void effect_free_buffers_delete(struct210 *arg0) {
    effect3d_free(arg0);
}

/* was func_151411E4 */
void effect_destroy_retire(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        flare_node_remove(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    g_particle_emitter_count -= 1;
    g_effect_retire_fns[arg0->unk168](arg0);
}

/* was func_15141250 */
void effect_destroy_delete(structEU_16DC80 *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        flare_node_remove(*(f32 **)((u8 *)arg0 + 0x154), arg0);
    }
    g_particle_emitter_count -= 1;
    g_effect_delete_fns[arg0->unk168](arg0);
}

/* Per-frame grid-cell lookup for the scene nodes (P13, hand C). For the two node tables g_node_lists[2][104]
 * and the four list heads named by the index table g_fx_broadcast_types_a[0..3], walk each list (next at 0x08). A node with
 * flag 0x2000 (word 0x58) clears its four per-player cell values (u16 at 0x15C); with flag 0x10 too, each
 * player's (x, y) cell (s32 at 0x134 / 0x144) inside the D_800BE620 x D_800BE624 grid looks up the u16 grid
 * g_zbuffer[y][x]; out of range gives 0x7FFF. */
/* was func_151412BC */
void effect_sample_zbuffer_cells(void) {
    u8 *row;
    u8 *node;
    u8 k;
    u8 i;
    s32 x;
    s32 y;
    s32 flags;

    for (row = (u8 *)g_node_lists; row != (u8 *)&g_node_iter_depth; row += 0x1A0) {
        for (k = 0; k < 4; k++) {
            node = ((u8 **)row)[((s32 *)&g_fx_broadcast_types_a)[k]];
            for (; node != NULL; node = *(u8 **)(node + 0x8)) {
                flags = *(s32 *)(node + 0x58);
                if (!(flags & 0x2000)) {
                    continue;
                }
                *(s16 *)(node + 0x162) = 0;
                *(s16 *)(node + 0x160) = 0;
                *(s16 *)(node + 0x15E) = 0;
                *(s16 *)(node + 0x15C) = 0;
                if (!(flags & 0x10)) {
                    continue;
                }
                for (i = 0; i <= D_80082FA0; i++) {
                    x = *(s32 *)(node + 0x134 + i * 4);
                    y = *(s32 *)(node + 0x144 + i * 4);
                    if (x < 0 || x >= D_800BE620 || y < 0 || y >= D_800BE624) {
                        *(u16 *)(node + 0x15C + i * 2) = 0x7FFF;
                    } else {
                        *(u16 *)(node + 0x15C + i * 2) =
                            *(u16 *)((u8 *)g_zbuffer + (y * D_800BE620) * 2 + x * 2);
                    }
                }
            }
        }
    }
}
/* was func_1514143C */
s32 effect_sync_link_pos(u8 *arg0)
{
  u8 *p;
  if (*((s32 *) (arg0 + 0x154)))
  {
    p = arg0 + 0x111;
 if (0) { } // fakematch: empty if, scheduling
    p--;  // fakematch: dead addiu kept (p = arg0 + K+1; p--;)
    (*((f32 **) (p + 0x44)))[0] = *((f32 *) (arg0 + 0x34));
    (*((f32 **) (p + 0x44)))[1] = *((f32 *) (arg0 + 0x38));
    (*((f32 **) (p + 0x44)))[2] = *((f32 *) (arg0 + 0x3C));
  }
}

/* was func_15141478 */
s32 effect_flicker_update(u8 *arg0) {
    u8 *sp24;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    (*(f32 *)((u8 *)arg0 + 0x180)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x180)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x180)) < 0.0f) {
        temp_v1 = arg0 + 0x170;
        (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) (random_float() * (*(f32 *)((u8 *)temp_v1 + 0x14)));
        sp24 = temp_v1;
        if (random_int() & 3) {
            sp24 = temp_v1;
            temp_f2 = (*(f32 *)((u8 *)temp_v1 + 4));
            (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((random_float() * ((*(f32 *)((u8 *)temp_v1 + 0)) - temp_f2)) + temp_f2);
        } else {
            sp24 = temp_v1;
            temp_f2_2 = (*(f32 *)((u8 *)temp_v1 + 0));
            (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((random_float() * ((*(f32 *)((u8 *)temp_v1 + 8)) - temp_f2_2)) + temp_f2_2);
        }
    }
    temp_a0 = arg0 + 0x110;
    temp_v1_2 = arg0 + 0x170;
    temp_f0 = (*(f32 *)((u8 *)temp_a0 + 0x48));
    (*(f32 *)((u8 *)temp_a0 + 0x48)) = (f32) (temp_f0 + (((*(f32 *)((u8 *)temp_v1_2 + 0xC)) - temp_f0) * (*(f32 *)((u8 *)temp_v1_2 + 0x18))));
    return 1;
}
/* was func_15141564 */
s32 effect_pulse_sine_update(structEU_16DC80 *arg0) {
    struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; } *temp = &arg0->unk170.f;
    f32 s;
    s32 pad;

    s = sinf(temp->unk8);
    arg0->unk158 = temp->unk0 + (temp->unk4 * s);
    temp->unk8 += temp->unkC * D_800BE9A4;
    temp->unk8 = wrap_angle_rad(temp->unk8);
    return 1;
}

typedef struct {
    f32 v0;
    f32 base;
    f32 amp;
    f32 t;
    f32 t0;
    f32 t1;
    f32 t2;
    f32 period;
    f32 scale;
} Env15D4;

/* was func_151415D4 */
s32 effect_pulse_envelope_update(u8 *arg0) {
    Env15D4 *e = (Env15D4 *)(arg0 + 0x170);
    f32 period;
    f32 f;

    if (e->t < e->t0) {
        *(f32 *)(arg0 + 0x158) = e->base;
    } else if (e->t < e->t1) {
        f = (e->t - e->t0) * e->scale;
        *(f32 *)(arg0 + 0x158) = e->base + e->amp * f;
    dummy: // fakematch: the label keeps the store out of the branch delay slot
        ;
    } else if (e->t < e->t2) {
        *(f32 *)(arg0 + 0x158) = e->v0;
    } else {
        f = 1.0f - (e->t - e->t2) * e->scale;
        *(f32 *)(arg0 + 0x158) = e->base + e->amp * f;
    }
    period = e->period;
    e->t += D_800BE9A4;
    while (period < e->t) {
        e->t -= period;
    }
    return 1;
}

extern void (*g_effect_msg_fns[])(u8 *, u8 *, s32); /* was D_8008A3CC */

// effect_message_dispatch: message handler of an effect record (P151). Forwards (rec, msg, code) to the type's
// handler g_effect_msg_fns[rec +0x168] when there is one; then for messages addressed to this type (msg[0] == +0x168):
// 0x22 frees the record (node_destroy), 0x24 / 0x25 set its state +0x169 to -1 / 2.
/* was func_151416E8 */
void effect_handle_message(u8 *rec, u8 *msg, s32 code) {
    u8 c = code;

    if (g_effect_msg_fns[rec[0x168]] != NULL) {
        g_effect_msg_fns[rec[0x168]](rec, msg, c);
    }
    if ((c == 0x22 || c == 0x24 || c == 0x25) && msg[0] == rec[0x110 + 0x58]) {
        if (c == 0x22) {
            node_destroy((struct102 *)rec);
        } else if (c == 0x24) {
            rec[0x110 + 0x59] = -1;
        } else {
            rec[0x110 + 0x59] = 2;
        }
    }
}

// ???
/* was func_151417C4 */
void effect_broadcast_message(u8 arg0, u8 arg1) {
    u8 sp24[4];
    s32 sp1C[2] = {0x1C, 0x56};

    sp24[0] = arg0;
    node_broadcast_types(sp1C, 2, (s32)sp24, arg1);
}

/* was func_15141818 */
s32 effect_check_false(s32 arg0, s32 arg1) {
    return 0;
}

/* was func_1514182C */
void effect_set_orbit_pos(structEU_16DC80 *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5) {
    f32 z;
    f32 y;
    f32 x;
    f32 mf[4][4];

    mtxf_rotate_xyz_deg(mf, arg4, 0.0f, arg5);
    mf[3][0] = ((f32 *)arg1)[0];
    mf[3][1] = ((f32 *)arg1)[1];
    mf[3][2] = ((f32 *)arg1)[2];
    mtxf_transform_point(mf, 0.0f, *(f32 *)&arg2, 0.0f, &arg0->unk34, &arg0->unk38, &arg0->unk3C);
    x = *(f32 *)&arg3 * (arg0->unk34 - ((f32 *)arg1)[0]);
    y = *(f32 *)&arg3 * (arg0->unk38 - ((f32 *)arg1)[1]);
    z = *(f32 *)&arg3 * (arg0->unk3C - ((f32 *)arg1)[2]);
    *(f32 *)((u8 *)arg0 + 0x40) = arg0->unk34 + x * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x44) = arg0->unk38 + y * 500.0f;
    *(f32 *)((u8 *)arg0 + 0x48) = arg0->unk3C + z * 500.0f;
}
// f32 effect_set_orbit_pos(void *arg0, void *arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     ? sp34;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f2;
//
//     mtxf_rotate_xyz_deg(&sp34, arg4, 0, arg5);
//     sp64 = arg1->unk0;
//     sp68 = arg1->unk4;
//     sp6C = arg1->unk8;
//     func_150A7960(&sp34, 0, arg2, 0, arg0 + 0x34, arg0 + 0x38, arg0 + 0x3C);
//     temp_f0 = arg0->unk34;
//     temp_f2 = arg0->unk38;
//     temp_f12 = arg0->unk3C;
//     arg0->unk40 = (f32) (temp_f0 + ((temp_f0 - arg1->unk0) * arg3 * 500.0f));
//     arg0->unk44 = (f32) (temp_f2 + ((temp_f2 - arg1->unk4) * arg3 * 500.0f));
//     arg0->unk48 = (f32) (temp_f12 + ((temp_f12 - arg1->unk8) * arg3 * 500.0f));
//     return temp_f0;
// }

/* was func_15141928 */
s32 effect_orbit_update(structEU_16DC80 *arg0) {
    f32 *temp_v0 = arg0->unk170.i.unk8;

    effect_set_orbit_pos(arg0, arg0->unk170.i.unkC, arg0->unk170.i.unk0, arg0->unk170.i.unk4, temp_v0[0], temp_v0[2]);
    return 1;
}
// s32 effect_orbit_update(void *arg0) {
//     void *temp_v0 = arg0->unk178;
//     effect_set_orbit_pos(arg0, arg0->unk17C, arg0->unk170, arg0->unk174, temp_v0->unk0, temp_v0->unk8);
//     return 1;
// }
