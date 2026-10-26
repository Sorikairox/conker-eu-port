#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void object_hit_burst(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4);

typedef struct {
    /* 0x000 */ u8  unk0;
    /* 0x001 */ u8  unk1;
    /* 0x002 */ u8  pad2[0xA];
    /* 0x00C */ u8  unkC;
    /* 0x00D */ u8  padD[0x3];
    /* 0x010 */ s32 unk10;
    /* 0x014 */ u8  pad14[0x4];
    /* 0x018 */ u8  unk18;
    /* 0x019 */ u8  pad19[0x3];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8  pad20[0x1D];
    /* 0x03D */ u8  unk3D;
    /* 0x03E */ u8  pad3E[0x6];
    /* 0x044 */ u16 unk44;
    /* 0x046 */ u8  pad46[0xA];
    /* 0x050 */ u8  unk50;
    /* 0x051 */ u8  pad51[0xF];
    /* 0x060 */ s32 unk60;
    /* 0x064 */ u8  pad64[0x10];
    /* 0x074 */ f32 unk74;
    /* 0x078 */ u8  pad78[0xF8];
    /* 0x170 */ s32 unk170;
    /* 0x174 */ u8  pad174[0x60];
    /* 0x1D4 */ s32 unk1D4;
} struct161520;

typedef struct {
    s32 unk0;
    union {
        s32 w;
        u8  b;
    } unk4;
    u8  unk8;
    u8  unk9;
} struct161520_msg;

typedef struct {
    /* 0x000 */ u8  pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8  pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8  pad34[0x28];
    /* 0x05C */ u8  unk5C;
    /* 0x05D */ u8  pad5D[0xCB];
    /* 0x128 */ f32 unk128;
} struct161520_b;

typedef struct {
    /* 0x000 */ u8  pad0[0x14];
    /* 0x014 */ f32 unk14;
    /* 0x018 */ f32 unk18;
    /* 0x01C */ f32 unk1C;
    /* 0x020 */ u8  pad20[0xE];
    /* 0x02E */ u8  unk2E;
    /* 0x02F */ u8  pad2F[0x41];
    /* 0x070 */ f32 unk70;
    /* 0x074 */ f32 unk74;
} struct161520_c;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ struct17 unk8;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} struct161520_e; // size 0x3C

void bone_emitter_on_msg_kind2(struct161520 *arg0, struct161520_msg *arg1, u8 arg2);
void bone_emitter_on_msg_kind1(struct161520 *arg0, struct161520_msg *arg1, u8 arg2);
s32 obj_get_hit_kind(struct127 *arg0);
void impact_burst(s32 arg0, u8 arg1, s32 arg2);
s32 object_hit_kind_effect_spawn(struct127 *arg0, s32 arg1, u8 arg2);
void object_hit_kind_sparks(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4);
void object_hit_smoke_puff(struct127 *arg0, f32 *arg1, s32 arg2, void *arg3, u8 arg4, s32 arg5); /* P282: void */
void bone_emitter_spark_params(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC);

// requires jump table
/* was func_15134070 */
s32 obj_get_hit_kind(struct127 *arg0) {
    switch (((u8 *)arg0)[4]) {
    case 0x87:
    case 0xB0:
        return 0xE;
    case 0xB1:
        return 0xF;
    case 0xB4:
        return 0x10;
    case 0x70:
    case 0xB2:
        return 0x11;
    case 0xAB:
        return 0x12;
    case 0x38:
    case 0x91:
    case 0x10:
        return 0xD;
    case 0x98:
        return 0xC;
    case 0x34:
        return 0xB;
    case 0x47:
        return 0xA;
    case 0x3B:
    case 0x11:
    case 0x14:
        return 0x1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        return 0x2;
    case 0x58:
    case 0x5B:
    case 0x80:
        return 0x3;
    case 0x88:
    case 0x90:
    case 0x16:
        return 0x4;
    case 0x9C:
        return 0x5;
    case 0x9D:
        return 0x6;
    case 0x96:
        return 0x7;
    case 0xA0:
        return 0x8;
    case 0x9F:
        return 0x9;
    case 0x9A:
        return 0x13;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        return 0;
    default:
        return 0x63;
    }
}

/* was func_1513416C */
s32 fx_fade_alpha_by_life(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        arg0->unk28 = temp_v0 * 8;
    }
    return 1;
}

s32 memcpy(u8 *, u8 *, s32);

/* was func_1513418C */
struct102 *emitter_trail_spawn(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *e;
    u8 *v;
    u8 *m;

    e = node_alloc(0x28, arg3, arg1 + 0x58, 1, arg2, 1);
    if (e == NULL) {
        return NULL;
    }
    memcpy(e + 0x10, arg0, 0x30);
    if (e[0x3A] & 2) {
        v = *(u8 **)(e + 0x1C);
        if (*(s32 *)v == 0 || e[0x18] != v[0x3B]) {
            node_destroy((struct102 *)e);
            return NULL;
        }
        if (*(u8 **)(v + 0x1D4) != NULL && (v[0x74] & 0xF) != 0xF) {
            m = *(u8 **)(v + 0x1D4);
            m += e[0x20] << 6;
            mtx_transform_point_or_origin(e + 0x24, e + 0x40, m);
        } else {
            e[0x3A] |= 8;
        }
    } else {
        e[0x3A] |= 0x18;
    }
    *(f32 *)(e + 0x4C) = 1.0f / (*(f32 *)(e + 0x30) + *(f32 *)(e + 0x30));
    *(f32 *)(e + 0x50) = 0.0f;
    return (struct102 *)e;
}
// void *emitter_trail_spawn(s32 arg0, s32 arg1 /* size/offset */, u8 arg2, s32 arg3) {
//     void *sp24;
//     s32 temp_v1;
//     u8 temp_a0;
//     void *temp_ret;
//     void *temp_v0;
//     struct127 *temp_v0_2;
//
//     temp_ret = node_alloc(0x28, arg3, arg1 + 0x58, 1, arg2, 1);
//     temp_v0 = temp_ret;
//     if (temp_v0 == 0) {
//         return NULL;
//     }
//     sp24 = temp_v0;
//     memcpy(&temp_v0->unk10, arg0, 0x30); //, temp_v0);
//     temp_a0 = temp_v0->unk3A;
//     if ((temp_a0 & 2) != 0) {
//         temp_v0_2 = temp_v0->unk1C;
//         if ((temp_v0_2->unk0 == 0) || (temp_v0->unk18 != temp_v0_2->unk3B)) {
//             node_destroy(temp_v0);
//             return NULL;
//         }
//         temp_v1 = temp_v0_2->unk1D4;
//         if ((temp_v1 != 0) && ((temp_v0_2->unk74 & 0xF) != 0xF)) {
//             sp24 = temp_v0;
//             mtx_transform_point_or_origin(temp_v0->unk24, temp_v0->unk40, temp_v1 + (temp_v0->unk20 << 6), temp_v0);
//         } else {
//             temp_v0->unk3A = (u8) (temp_a0 | 8);
//         }
//     } else {
//         temp_v0->unk3A = (u8) (temp_a0 | 0x18);
//     }
//     temp_ret->unk50 = 0.0f;
//     temp_ret->unk4C = (f32) (1.0f / (2.0f * temp_ret->unk30));
//     return temp_ret;
// }

/* trail_emitter_update: per-frame update of a trail / particle emitter object (list type 0x28, made by
 * emitter_trail_spawn). Lifetime +0x38 counts down by D_800BE9E4 when flag 4 is set (dies below 0). Position: the
 * parent's position (+0x1C, flag 1), the parent model's bone matrix obj[0x20] (flag 2; the emitter dies when the
 * parent is gone or its slot id changed), or its own double-buffered matrix +0x10/+0x14 (no flag 0x10); the point
 * +0x24 is transformed by mtx_transform_point_or_origin. The accumulator +0x50 grows with the distance moved since the last frame
 * (+0x40; flag 8 = no previous position) and the rate +0x4C / +0x34 (capped at 7); one g_emitter_trail_spawn_fns[obj[0x3B]]
 * spawn per whole unit, spread along the movement and jittered by the size +0x30. Then the per-type handler
 * g_emitter_trail_type_fns[(s8) obj[0x3C]] (-1 = none); a 0 result (or the lifetime) frees the emitter (node_destroy). */
typedef void (*EmitterSpawnFn)(f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *obj);
typedef s32 (*EmitterTypeFn)(u8 *obj);
extern EmitterSpawnFn g_emitter_trail_spawn_fns[]; /* was D_80089E10 */
extern EmitterTypeFn g_emitter_trail_type_fns[]; /* was D_80089E40 */
/* was func_151342BC */
void emitter_trail_update(u8 *obj) {
    u8 dead;
    f32 *prev;
    u8 *parent;
    u8 *matrix;
    f32 pos[3];
    f32 dx, dy, dz;
    f32 dist;
    f32 size2;
    f32 t, jx, jy, jz;
    u8 flags;

    dead = FALSE;
    prev = (f32 *) (obj + 0x40);
    if (obj[0x3A] & 4) {
        *(s16 *) (obj + 0x38) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x38) < 0) {
            dead = TRUE;
        }
    }
    flags = obj[0x3A];
    if (flags & 8) {
        prev = pos;
    }
    if (flags & 1) {
        parent = *(u8 **) (obj + 0x1C);
        pos[0] = *(f32 *) (parent + 0x14);
        pos[1] = *(f32 *) (parent + 0x18);
        pos[2] = *(f32 *) (parent + 0x1C);
    } else if (flags & 2) {
        parent = *(u8 **) (obj + 0x1C);
        if (*(s32 *) parent == 0 || *(s32 *) parent == 8 || obj[0x18] != parent[0x3B]) {
            node_destroy((struct102 *) obj);
            return;
        }
        matrix = *(u8 **) (parent + 0x1D4);
        if (matrix == NULL || (parent[0x74] & 0xF) == 0xF) {
            obj[0x3A] = flags | 8;
            return;
        }
        mtx_transform_point_or_origin(obj + 0x24, pos, matrix + (obj[0x20] << 6));
    } else {
        if (flags & 0x10) {
            return;
        }
        mtx_transform_point_or_origin(obj + 0x24, pos, *(u8 **) (obj + 0x10 + (D_800BE9C0 ? 0 : 1) * 4));
    }

    dx = prev[0] - pos[0];
    dy = prev[1] - pos[1];
    dz = prev[2] - pos[2];
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    *(f32 *) (obj + 0x50) += (*(f32 *) (obj + 0x4C) * dist + 1.0f) * D_800BE9A4 * *(f32 *) (obj + 0x34);
    if (*(f32 *) (obj + 0x50) > 7.0f) {
        *(f32 *) (obj + 0x50) = 7.0f;
    }
    if ((obj[0x3A] & 0x20) && D_800C35EA == 1) {
        // no spawning (D_800C35EA == 1): drop the whole units
        while (*(f32 *) (obj + 0x50) > 1.0f) {
            *(f32 *) (obj + 0x50) -= 1.0f;
        }
    } else {
        while (*(f32 *) (obj + 0x50) > 1.0f) {
            size2 = *(f32 *) (obj + 0x30) + *(f32 *) (obj + 0x30);
            t = random_float();
            if (g_emitter_trail_spawn_fns[obj[0x3B]] != NULL) {
                jx = random_float();
                jy = random_float();
                jz = random_float();
                g_emitter_trail_spawn_fns[obj[0x3B]](pos[0] + dx * t + *(f32 *) (obj + 0x30) - jx * size2,
                                      pos[1] + dy * t + *(f32 *) (obj + 0x30) - jy * size2,
                                      pos[2] + dz * t + *(f32 *) (obj + 0x30) - jz * size2, dx, dy, dz, obj);
            }
            *(f32 *) (obj + 0x50) -= 1.0f;
        }
    }
    ((f32 *) (obj + 0x40))[0] = pos[0];
    ((f32 *) (obj + 0x40))[1] = pos[1];
    ((f32 *) (obj + 0x40))[2] = pos[2];
    obj[0x3A] &= ~8;
    if (!dead && (s8) obj[0x3C] != -1) {
        if (g_emitter_trail_type_fns[(s8) obj[0x3C]](obj) == 0) {
            dead = TRUE;
        }
    }
    if (dead) {
        node_destroy((struct102 *) obj);
    }
}

/* was func_151346D0 */
s32 emitter_trail_clear_flag10(s32 arg0, struct102 *arg1, s32 arg2) {
    arg1->unk3A &= 0xFFEF;
    return arg0;
}

/* object_list_move_1: g_emitter_trail_type_fns table entry (emitter_trail_update calls the entries as s32 (*)(obj) and runs
 * node_destroy on the object when the result is 0): moves the object to list 1 (node_retire). The asm returns
 * what node_list_insert leaves in v0: the object's byte +1 (its type, read as the list index). */
/* was func_151346EC */
s32 object_list_move_1(struct102 *arg0) {
    node_retire(arg0);
    return ((u8 *) arg0)[1];
}

/* object_list_free: g_emitter_trail_type_fns table entry: unlinks and frees the object (node_unlink_free). The asm returns the free
 * function's v0 (osSetIntMask's previous mask, never 0), so emitter_trail_update never touches the freed object: 1. */
/* was func_1513470C */
s32 object_list_free(struct102 *arg0) {
    node_unlink_free(arg0);
    return 1;
}

/* object_state_dispatch_a / _b: run the object's state handler (+0x3D, 0..9, else 0) from g_object_state_fns_a / g_object_state_fns_b on
 * the object. The asm leaves the object in a0 for the handler (all entries are s32 (*)(obj): object_list_move_1,
 * object_list_free, ground_trail_a_retire / 6938, ground_trail_b_retire / 7268, char_sound_obj_retire / D88) and returns the handler's v0. */
/* was func_1513472C */
s32 object_state_dispatch_a(struct102 *arg0) {
    s32 idx = arg0->unk3D;

    if (idx < 0) {
        idx = 0;
    }
    if (idx >= 10) {
        idx = 0;
    }
    return ((s32 (*)(struct102 *)) g_object_state_fns_a[idx])(arg0);
}

// object_state_dispatch_b: as object_state_dispatch_a with the table g_object_state_fns_b.
/* was func_1513477C */
s32 object_state_dispatch_b(struct102 *arg0) {
    s32 idx = arg0->unk3D;

    if (idx < 0) {
        idx = 0;
    }
    if (idx >= 10) {
        idx = 0;
    }
    return ((s32 (*)(struct102 *)) g_object_state_fns_b[idx])(arg0);
}

/* was func_151347CC */
void emitter_trail_on_msg(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
  s32 *key = &arg0->unk1C;
    if ((arg2 == 0) || (arg2 == 3)) {
        if ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18)) { node_destroy((struct102 *)arg0); }
    } else if (arg2 == 0x11) {
        if ((arg0->unk3D == 5) && ((arg1->unk0 == arg0->unk1C) || (arg1->unk4.b == arg0->unk18))) { node_destroy((struct102 *)arg0); }
    } else if (arg2 == 0x16) {
        if ((s32)arg1 == arg0->unk1C) { node_destroy((struct102 *)arg0); }
    } else if (arg2 == 0x2D) {
        if (arg1->unk0 == *key) { arg0->unk1C = arg1->unk4.w; arg0->unk18 = arg1->unk9; }
        else if (arg1->unk4.w == *key) { arg0->unk1C = arg1->unk0; arg0->unk18 = arg1->unk8; }
    }
}

/* was func_151348F0 */
void emitter_spawn_none(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
}

s32 memcpy(u8 *, u8 *, s32);
/* was func_15134908 */
s32 point_emitter_spawn(struct_eu_EF410 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;
    u8 *sp24; // fakematch: temp_v0 copy kept in a stack slot
    temp_v0 = node_alloc(0x2A, arg3, arg1 + 0x40, 1, arg2, 1);
    if (temp_v0 == NULL) {
        return 0;
    }
    *((u8 *)arg0 + 0x16) |= 2;
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x10, (u8 *)arg0, 0x1C);
    *(f32 *)(sp24 + 0x2C) = **(f32 **)(sp24 + 0x10);
    *(f32 *)(sp24 + 0x30) = **(f32 **)(sp24 + 0x14);
    *(f32 *)(sp24 + 0x34) = **(f32 **)(sp24 + 0x18);
    *(f32 *)(sp24 + 0x38) = 1.0f / (2.0f * *(f32 *)(sp24 + 0x1C));
    *(f32 *)(sp24 + 0x3C) = 0.0f;
    return (s32)sp24;
}

/* point_emitter_update: per-frame update of a point emitter (list type 0x2A, made by point_emitter_spawn; type table
 * entry 0x8008C0D0). The emitter follows a point given as three f32 pointers (+0x10 / +0x14 / +0x18, x / y / z).
 * With flag 4 (+0x26) and a handler g_point_emitter_type_fns[(s8) +0x29] (-1 = none), a 0 handler result frees it
 * (node_destroy) at once. Flag 2 = no previous position this frame (cleared, nothing spawned). Otherwise the
 * accumulator +0x3C grows with the distance moved since the last frame (+0x2C) times +0x38 (= 1 / (2 * size)) plus
 * 1, scaled by D_800BE9A4 and the rate +0x20 (capped at 7); one g_point_emitter_spawn_fns[+0x27] spawn per whole unit, spread
 * along the movement and jittered by the size +0x1C. Then the position is kept for the next frame; with flag 1 the
 * lifetime +0x24 counts down by D_800BE9E4 and the emitter is freed below 0. */
typedef void (*PointEmitterSpawnFn)(f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *obj);
typedef s32 (*PointEmitterTypeFn)(u8 *obj);
extern PointEmitterSpawnFn g_point_emitter_spawn_fns[]; /* was D_80089E9C */
extern PointEmitterTypeFn g_point_emitter_type_fns[]; /* was D_80089EB8 */
/* was func_151349D0 */
void point_emitter_update(u8 *obj) {
    f32 pos[3];
    f32 dx, dy, dz;
    f32 dist;
    f32 size2;
    f32 t, jx, jy, jz;
    f32 size;

    pos[0] = **(f32 **) (obj + 0x10);
    pos[1] = **(f32 **) (obj + 0x14);
    pos[2] = **(f32 **) (obj + 0x18);
    if ((obj[0x26] & 4) && (s8) obj[0x29] != -1) {
        if (g_point_emitter_type_fns[(s8) obj[0x29]](obj) == 0) {
            node_destroy((struct102 *) obj);
            return;
        }
    }
    if (obj[0x26] & 2) {
        obj[0x26] &= ~2;
    } else {
        dx = *(f32 *) (obj + 0x2C) - pos[0];
        dy = *(f32 *) (obj + 0x30) - pos[1];
        dz = *(f32 *) (obj + 0x34) - pos[2];
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        *(f32 *) (obj + 0x3C) += (*(f32 *) (obj + 0x38) * dist + 1.0f) * D_800BE9A4 * *(f32 *) (obj + 0x20);
        if (*(f32 *) (obj + 0x3C) > 7.0f) {
            *(f32 *) (obj + 0x3C) = 7.0f;
        }
        while (*(f32 *) (obj + 0x3C) > 1.0f) {
            size2 = *(f32 *) (obj + 0x1C) + *(f32 *) (obj + 0x1C);
            t = random_float();
            if (g_point_emitter_spawn_fns[obj[0x27]] != NULL) {
                jx = random_float();
                jy = random_float();
                jz = random_float();
                size = *(f32 *) (obj + 0x1C);
                g_point_emitter_spawn_fns[obj[0x27]](pos[0] + dx * t + size - jx * size2, pos[1] + dy * t + size - jy * size2,
                                      pos[2] + dz * t + size - jz * size2, dx, dy, dz, obj);
            }
            *(f32 *) (obj + 0x3C) -= 1.0f;
        }
    }
    *(f32 *) (obj + 0x2C) = pos[0];
    *(f32 *) (obj + 0x30) = pos[1];
    *(f32 *) (obj + 0x34) = pos[2];
    if (obj[0x26] & 1) {
        *(s16 *) (obj + 0x24) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x24) < 0) {
            node_destroy((struct102 *) obj);
        }
    }
}

/* was func_15134C98 */
void fx_forward_msg_if_kind1(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg0->unk28 == 1) {
        point_emitter_handle_message(arg0, arg1, arg2);
    }
}

/* was func_15134CD4 */
void emitter_stub(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

/* was func_15134CEC */
s32 fx_rising_particle_update(struct161520_c *arg0) {
    s32 temp_v1 = arg0->unk2E;

    arg0->unk70 += 0.125f * D_800BE9A4;
    arg0->unk74 += 0.08f * D_800BE9A4;
    arg0->unk14 += arg0->unk70 * D_800BE9A4;
    arg0->unk1C += arg0->unk74 * D_800BE9A4;
    if (arg0->unk14 > 130.0f) {
        return 0;
    }
    temp_v1 -= D_800BE9E4 * 2;
    if (temp_v1 < 0) {
        return 0;
    }
    arg0->unk2E = temp_v1;
    return 1;
}

s32 memcpy(u8 *, u8 *, s32);

/* was func_15134DAC */
u8 *bone_emitter_spawn(u8 *arg0, s32 arg1) {
    u8 *temp_v0;
    u8 *sp24;

    temp_v0 = node_alloc(0x29, 0, arg1 + 0x80, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp24 = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x3C);
    (*(s16 *)((u8 *)sp24 + 0x54)) = (s16) -(*(s16 *)((u8 *)arg0 + 0x28));
    (*(s32 *)((u8 *)sp24 + 0x10)) = 1;
    (*(s32 *)((u8 *)sp24 + 0x14)) = 0;
    (*(f32 *)((u8 *)sp24 + 0x70)) = 0.0f;
    (*(f32 *)((u8 *)sp24 + 0x74)) = 0.0f;
    (*(f32 *)((u8 *)sp24 + 0x78)) = 0.0f;
    return sp24;
}

/* P247: bone-attached particle emitter made by bone_emitter_spawn (+0x18..+0x53 = the 0x3C-byte spec it copies). */
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s32 active;          /* bit 0: emitting */
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 objId;            /* the object's +0x3B id when attached */
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ u8 *obj;             /* object the emitter rides on */
    /* 0x20 */ u8 bone;             /* matrix index in the object's model (+0x1D4) */
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ f32 offsetA[3];      /* emission points in bone space */
    /* 0x30 */ f32 offsetB[3];
    /* 0x3C */ u8 flags;            /* bit 1: limited lifetime (+0x42) */
    /* 0x3D */ u8 pad3D;
    /* 0x3E */ s16 restart;         /* timer value after a (re)start */
    /* 0x40 */ s16 period;          /* the timer restarts below -period */
    /* 0x42 */ s16 life;
    /* 0x44 */ u16 sound;
    /* 0x46 */ s8 startFn;          /* g_bone_emitter_start_fns index (-1: none): called on restart, 0 = stop */
    /* 0x47 */ s8 emitFn;           /* g_bone_emitter_emit_fns index (-1: none): emits one particle */
    /* 0x48 */ s8 rateFn;           /* g_bone_emitter_rate_fns index (-1: none): sets rateScale */
    /* 0x49 */ u8 pad49[3];
    /* 0x4C */ f32 rate;            /* particles per frame unit */
    /* 0x50 */ u8 kind;
    /* 0x51 */ s8 tickFn;           /* g_bone_emitter_tick_fns index (-1: none): per-frame check, 0 = stop */
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ s16 timer;
    /* 0x56 */ u8 pad56[2];
    /* 0x58 */ f32 posA[3];         /* world positions of the emission points at the last emission */
    /* 0x64 */ f32 posB[3];
    /* 0x70 */ f32 count;           /* particles owed */
    /* 0x74 */ f32 rateScale;
    /* 0x78 */ f32 phase;
} BoneEmitter;

extern s32 (*g_bone_emitter_start_fns[])(BoneEmitter *); /* was D_80089EBC */
extern void (*g_bone_emitter_emit_fns[])(f32 *, f32 *, f32 *, f32 *, f32, BoneEmitter *); /* was D_80089ED8 */
extern f32 (*g_bone_emitter_rate_fns[])(BoneEmitter *); /* was D_80089EFC */
extern s32 (*g_bone_emitter_tick_fns[])(BoneEmitter *); /* was D_80089F0C */
void bone_emitter_send_pair(s32, s32, s32, s32, s32);

// bone_emitter_update: per-frame update (pointer at 0x8008C09C, next to EU 0x15134C9C / 0x15134CEC) of a
// particle emitter attached to a bone of an object (made by bone_emitter_spawn). While emitting
// (+0x10 bit 0) and the object is alive, unchanged (id byte), has a model and is not hidden: counts the timer down
// by D_800BE9E4; when it passes -period it restarts at `restart`, re-reads the two emission points from the bone
// matrix (bone_emitter_send_pair) and calls the start callback (0 stops the emitter). While the timer is positive it adds
// rate * D_800BE9A4 to the owed count (the rate callback only stores rateScale for the emit callbacks) and, when more
// than one particle is owed, emits them evenly spaced along the path both points moved since the last emission:
// each call gets the interpolated points, the points' velocities (step * D_800BEDC8) and a phase that runs from
// phase + D_800BE9A4 down by equal steps; the points and phase are kept for the next frame. Then the tick callback
// and the lifetime (+0x42, flag 2) can stop it. A stopped emitter, or one whose object is gone, is freed
// (node_destroy).
/* was func_15134E48 */
void bone_emitter_update(BoneEmitter *e) {
    u8 stop = 0;
    u8 *obj = e->obj;
    u8 *mtx;
    u8 *bone;
    f32 newA[3];
    f32 newB[3];
    f32 curA[3];
    f32 curB[3];
    f32 velA[3];
    f32 velB[3];
    f32 stepA[3];
    f32 stepB[3];
    f32 inv;
    f32 phase;
    f32 phaseStep;
    f32 dA[3];
    f32 dB[3];

    if (*(s32 *) obj == 0 || e->objId != obj[0x3B]) {
        stop = 1;
    }
    if (e->active & 1) {
        if (!stop && (mtx = *(u8 **) (obj + 0x1D4)) != NULL && (obj[0x74] & 0xF) != 0xF) {
            e->timer -= D_800BE9E4;
            bone = mtx + e->bone * 0x40;
            if (e->timer < -e->period) {
                e->timer = e->restart;
                bone_emitter_send_pair((s32) bone, (s32) e->offsetA, (s32) e->offsetB, (s32) e->posA, (s32) e->posB);
                if (e->startFn != -1 && g_bone_emitter_start_fns[e->startFn](e) == 0) {
                    stop = 1;
                    e->timer = -1;
                }
            }
            if (e->timer > 0) {
                if (e->rateFn != -1) {
                    e->rateScale = g_bone_emitter_rate_fns[e->rateFn](e);
                }
                e->count += e->rate * D_800BE9A4;
                if (e->count > 1.0f) {
                    inv = 1.0f / e->count;
                    phase = e->phase + D_800BE9A4;
                    phaseStep = phase * inv;
                    curA[0] = e->posA[0];
                    curA[1] = e->posA[1];
                    curA[2] = e->posA[2];
                    curB[0] = e->posB[0];
                    curB[1] = e->posB[1];
                    curB[2] = e->posB[2];
                    bone_emitter_send_pair((s32) bone, (s32) e->offsetA, (s32) e->offsetB, (s32) newA, (s32) newB);
                    dA[0] = newA[0] - e->posA[0];
                    dA[1] = newA[1] - e->posA[1];
                    dA[2] = newA[2] - e->posA[2];
                    dB[0] = newB[0] - e->posB[0];
                    dB[1] = newB[1] - e->posB[1];
                    dB[2] = newB[2] - e->posB[2];
                    velA[0] = dA[0] * D_800BEDC8;
                    velA[1] = dA[1] * D_800BEDC8;
                    velA[2] = dA[2] * D_800BEDC8;
                    velB[0] = dB[0] * D_800BEDC8;
                    velB[1] = dB[1] * D_800BEDC8;
                    velB[2] = dB[2] * D_800BEDC8;
                    stepA[0] = dA[0] * inv;
                    stepA[1] = dA[1] * inv;
                    stepA[2] = dA[2] * inv;
                    stepB[0] = dB[0] * inv;
                    stepB[1] = dB[1] * inv;
                    stepB[2] = dB[2] * inv;
                    do {
                        if (e->emitFn != -1) {
                            g_bone_emitter_emit_fns[e->emitFn](curA, curB, velA, velB, phase, e);
                        }
                        curA[0] += stepA[0];
                        curA[1] += stepA[1];
                        curA[2] += stepA[2];
                        curB[0] += stepB[0];
                        curB[1] += stepB[1];
                        curB[2] += stepB[2];
                        phase -= phaseStep;
                        e->count -= 1.0f;
                    } while (e->count > 1.0f);
                    e->posA[0] = curA[0];
                    e->posA[1] = curA[1];
                    e->posA[2] = curA[2];
                    e->posB[0] = curB[0];
                    e->posB[1] = curB[1];
                    e->posB[2] = curB[2];
                    e->phase = phase;
                }
            }
        }
        if (e->tickFn != -1 && g_bone_emitter_tick_fns[e->tickFn](e) == 0) {
            stop = 1;
        }
        if (e->flags & 2) {
            e->life -= D_800BE9E4;
            if (e->life < 0) {
                stop = 1;
            }
        }
    }
    if (stop) {
        node_destroy((struct102 *) e);
    }
}

/* was func_151352EC */
void bone_emitter_retire(struct102 *arg0) {
    node_retire(arg0);
}

/* was func_1513530C */
void bone_emitter_free(struct102 *arg0) {
    node_unlink_free(arg0);
}

/* was func_1513532C */
void bone_emitter_stop_dispatch_a(struct161520 *arg0) {
    s32 pad;
    s32 idx = arg0->unk50;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    if (arg0->unk44 != 0) {
        sound_voice_stop(arg0->unk44);
        arg0->unk44 = 0;
    }
    g_bone_emitter_stop_fns_a[idx](arg0);
}

/* was func_151353A8 */
void bone_emitter_stop_dispatch_b(struct161520 *arg0) {
    s32 pad;
    s32 idx = arg0->unk50;

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 6) {
        idx = 0;
    }
    if (arg0->unk44 != 0) {
        sound_voice_stop(arg0->unk44);
        arg0->unk44 = 0;
    }
    g_bone_emitter_stop_fns_b[idx](arg0);
}

s32 mtx_transform_points(s32 *, s32 *, s32, s32);
/* was func_15135424 */
void bone_emitter_send_pair(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp20[2];
    s32 sp18[2];
    sp20[0] = arg1;
    sp20[1] = arg2;
    sp18[0] = arg3;
    sp18[1] = arg4;
    mtx_transform_points(sp20, sp18, arg0, 2);
}

/* was func_15135480 */
void bone_emitter_on_msg(struct161520 *arg0, struct161520_msg *arg1, u8 arg2)
{
  s32 t;
  s32 k;
  if (arg2 == 0x2D)
  {
    if (arg0->unk1C == arg1->unk0)
    {
      arg0->unk1C = arg1->unk4.w;
      arg0->unk18 = arg1->unk9;
    }
    else
      if (arg0->unk1C == arg1->unk4.w)
    {
      t = arg1->unk0;
      arg0->unk1C = t;
      arg0->unk18 = arg1->unk8;
    }
  }
  switch (arg0->unk50)
  {
    case 1:
      bone_emitter_on_msg_kind1(arg0, arg1, arg2);
      break;

    case 2:
      bone_emitter_on_msg_kind2(arg0, arg1, arg2);
      break;

    default:
      if (arg2 == 0)
    {
      k = arg0->unk1C;
      if (((k ^ 0) == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) // fakematch: (k ^ 0) keeps the key in v0 (s71/s72)
      {
        node_destroy((struct102 *) arg0);
      }
    }
      break;

  }

}

/* was func_1513555C */
void bone_emitter_on_msg_kind2(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 0x12)) {
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            node_destroy(arg0);
        }
    }
}

/* was func_151355B8 */
void bone_emitter_on_msg_kind1(struct161520 *arg0, struct161520_msg *arg1, u8 arg2) {
    switch (arg2) {
    case 0:
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            node_destroy(arg0);
        }
        break;
    case 3:
        if ((arg0->unk1C == arg1->unk0) || (arg0->unk18 == arg1->unk4.b)) {
            arg0->unk10 &= ~1;
            arg0->unk10 = arg0->unk10;
        }
        break;
    }
}

/* was func_15135658 */
s32 bone_emitter_rate_one(struct161520 *arg0) {
    arg0->unk74 = 1.0f;
    return 1;
}

/* was func_15135670 */
f32 blood_get_power(s32 arg0) {
    // "power", "../Effects/Blood/blood.c"
    return debug_tweak_int(0, &g_str_blood_power, 0, 2000, 1000, &g_str_blood_c_path, 2938) * 0.001f;
}

/* sprite2d_spawn's sprite spec (0x58 bytes; same layout as game_eu_127840's SpriteSpecFB398). */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 scaleA;
    /* 0x0C */ f32 scaleB;
    /* 0x10 */ u8 kind;
    /* 0x12 */ s16 span;
    /* 0x14 */ u16 flags;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ u8 u1A;
    /* 0x1B */ u8 col[9];
    /* 0x24 */ s32 u24;
    /* 0x28 */ s32 u28;
    /* 0x2C */ s32 u2C;
    /* 0x30 */ s32 u30;
    /* 0x34 */ s32 u34;
    /* 0x38 */ s32 u38;
    /* 0x3C */ s32 u3C;
    /* 0x40 */ u8 u40;
    /* 0x41 */ u8 u41;
    /* 0x42 */ u8 pad42[2]; /* P282: player is at 0x44 (it sat at 0x42 without this pad) */
    /* 0x44 */ u8 player;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
} SpriteSpec356D4;

typedef struct {
    u8 kind[2];
} KindPair356D4;

s32 sprite2d_spawn(void *spec, s32 list, void *, s32, s32, s32, s32);
f32 angle_byte_cos(u8);
s32 random_int(void);
f32 random_float(void);
s32 memcpy(u8 *, u8 *, s32); /* as declared earlier in game_161520 */
extern KindPair356D4 g_blood_splash_kinds; /* main sprite kinds; was D_80089F40 */
extern s32 g_blood_splash_u00; /* was D_80089F44 */
extern KindPair356D4 g_blood_spark_kinds; /* spark kinds; was D_80089F48 */

// sprite_splash_spawn: spawns a screen sprite (list 3, kind g_blood_splash_kinds[random], flags 9 | random 2 (| random 4 for
// kind 0x3A), colour bytes `colA` / `colB`) at `pos` (x, y) with scale `scale`, for `span`; its +0x70 gets a 0x18
// block (`life`, random growth (100..200) x scale x 0.001, random drift 0..6 x pos x 0.001, `fadeA`, `fadeB`). When it
// exists, adds (100..400) x scale x 0.001 spark sprites (list 0, kind g_blood_spark_kinds[random], random flip bits 2 / 4)
// spread around `pos` at random angles and distances, sized from the main sprite's scale.
/* was func_151356D4 */
void blood_splash_spawn(f32 *pos, f32 scale, f32 fadeA, f32 fadeB, u8 colA, u8 colB, s16 life, s16 span, s16 u16,
                   s16 u18, u8 flag, s32 owner) {
    SpriteSpec356D4 sprite;
    struct {
        s32 u00;
        KindPair356D4 kinds;
        u8 pad06[2];
        s16 life;   /* +0x08: from here 0x18 bytes go to the sprite's +0x70 */
        f32 grow;
        f32 driftX;
        f32 driftY;
        f32 fadeA;
        f32 fadeB;
    } blk;
    SpriteSpec356D4 spark;
    KindPair356D4 sparkKinds;
    s32 rec;
    f32 mid;
    f32 n;
    f32 s;
    f32 c;
    f32 d;
    u8 a;

    blk.kinds = g_blood_splash_kinds;
    blk.u00 = g_blood_splash_u00;
    blk.life = life;
    blk.grow = (random_float() * 100.0f + 100.0f) * scale * 0.001f;
    blk.driftX = random_float() * 6.0f * pos[0] * 0.001f;
    blk.driftY = random_float() * 6.0f * pos[1] * 0.001f;
    blk.fadeA = fadeA;
    blk.fadeB = fadeB;
    sprite.x = pos[0];
    sprite.y = pos[1];
    sprite.scaleA = scale;
    sprite.scaleB = scale;
    sprite.kind = blk.kinds.kind[random_int() & 1];
    sprite.span = span;
    sprite.flags = (random_int() & 1) ? 2 : 0;
    sprite.flags |= ((sprite.kind == 0x3A) ? ((random_int() & 1) ? 4 : 0) : 0) | 9;
    sprite.u16 = u16;
    sprite.u18 = u18;
    sprite.u1A = 2;
    sprite.col[0] = 0xFF;
    sprite.col[1] = 0xFF;
    sprite.col[2] = 0xFF;
    sprite.col[3] = colA;
    sprite.col[4] = 0xFF;
    sprite.col[5] = 0xFF;
    sprite.col[6] = 0xFF;
    sprite.col[7] = 0xFF;
    sprite.col[8] = colB;
    sprite.u24 = 0;
    sprite.u28 = 0;
    sprite.u2C = 0;
    sprite.u40 = 0;
    sprite.u41 = 9;
    sprite.u30 = 7;
    sprite.u34 = 0x3C;
    sprite.u38 = 0x80;
    sprite.u3C = 0x20;
    rec = sprite2d_spawn(&sprite, 3, &blk, 1, 0x18, flag, owner);
    if (rec == 0) {
        return;
    }
    memcpy((u8 *)rec + 0x70, (u8 *)&blk.life, 0x18);

    mid = (sprite.scaleA + sprite.scaleB) * 0.5f;
    n = (random_float() * 300.0f + 100.0f) * scale * 0.001f;
    spark.span = 0x32;
    spark.flags = 9;
    spark.u16 = 0x10;
    spark.u18 = 0xF;
    spark.u1A = 3;
    spark.col[0] = 0xFF;
    spark.col[1] = 0xFF;
    spark.col[2] = 0xFF;
    spark.col[3] = colA;
    spark.col[4] = 0xFF;
    spark.col[5] = 0xFF;
    spark.col[6] = 0xFF;
    spark.col[7] = 0xFF;
    spark.col[8] = colB;
    spark.u24 = 0;
    spark.u28 = 0;
    spark.u2C = 0;
    spark.u40 = 0;
    spark.u41 = 9;
    spark.u30 = 7;
    spark.u34 = 0x3C;
    spark.u38 = 0x40;
    spark.u3C = 0;
    spark.scaleA = (random_float() * 120.0f + 80.0f) * (scale * mid) * 0.0001f;
    spark.scaleB = (random_float() * 120.0f + 80.0f) * (scale * mid) * 0.0001f;
    for (; n > 1.0f; n -= 1.0f) {
        sparkKinds = g_blood_spark_kinds;
        a = random_int();
        c = angle_byte_cos(a - 0x40);
        s = angle_byte_cos(a);
        d = (random_float() * 300.0f + 1300.0f) * mid * 0.001f;
        spark.x = pos[0] + d * s;
        spark.y = pos[1] + d * c;
        spark.flags &= ~6;
        spark.kind = sparkKinds.kind[random_int() & 1];
        if (random_int() & 1) {
            spark.flags |= 2;
        }
        if (random_int() & 1) {
            spark.flags |= 4;
        }
        sprite2d_spawn(&spark, 0, 0, 0, 0, flag, owner);
    }
}

/* was func_15135BF8 */
s32 blood_drop_update(u8 *arg0) {
    struct {
        f32 u8;
        f32 uC;
        u8 pad10[0x8];
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f4;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    if ((*(s16 *)((u8 *)arg0 + 0x70)) > 0) {
        temp_v0 = arg0 + 0x70;
        (*(s16 *)((u8 *)temp_v0 + 0)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0)) - D_800BE9E4);
        (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + ((*(f32 *)((u8 *)temp_v0 + 8)) * D_800BE9A4));
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + ((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4));
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + ((*(f32 *)((u8 *)temp_v0 + 4)) * D_800BE9A4));
        var_f4 = (*(f32 *)((u8 *)arg0 + 0x1C)) + ((*(f32 *)((u8 *)temp_v0 + 4)) * D_800BE9A4);
    } else {
        temp_v0_2 = arg0 + 0x70;
        (*(f32 *)((u8 *)(&sp.u8) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 8));
        (*(f32 *)((u8 *)(&sp.u8) + 4)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC));
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + (((*(f32 *)((u8 *)temp_v0_2 + 0xC)) * D_800BE9A4) + ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * D_800BE9A4 * D_800BE9A4 * 0.5f)));
        (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 0xC)) + ((*(f32 *)((u8 *)temp_v0_2 + 0x10)) * D_800BE9A4));
        temp_f8 = sp.u8 + (*(f32 *)((u8 *)temp_v0_2 + 8));
        sp.u8 = temp_f8;
        temp_f10 = temp_f8 * 0.5f;
        temp_f6 = sp.uC + (*(f32 *)((u8 *)temp_v0_2 + 0xC));
        sp.uC = temp_f6;
        sp.u8 = temp_f10;
        sp.uC = temp_f6 * 0.5f;
        temp_f12 = fabsf(temp_f10) * (*(f32 *)((u8 *)temp_v0_2 + 0x14));
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + (temp_f12 * D_800BE9A4));
        var_f4 = (*(f32 *)((u8 *)arg0 + 0x1C)) + (temp_f12 * D_800BE9A4);
    }
    (*(f32 *)((u8 *)arg0 + 0x1C)) = var_f4;
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x10));
    if ((temp_f0 > 200.0f) || (temp_f0 < -200.0f) || (temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x14)), (temp_f0_2 > 200.0f)) || (temp_f0_2 < -200.0f)) {
        var_v1 = 0;
    }
    return var_v1;
}
/* collision_floor_dynamic's hit record (game_eu_71E70 HitInfo: t, 9 s16 position words, +0x18, flags +0x1C, surface kind +0x1D) */
typedef struct {
    /* 0x00 */ f32 t;
    /* 0x04 */ s16 pos[9];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 surface;
    /* 0x1E */ u8 pad1E[2];
    /* 0x20 */ s32 unk20;
} Hit5DD0;
s32 collision_floor_dynamic(f32 *, u16, f32, Hit5DD0 *);
void vec3_from_angles_byte(s16, s16, f32, f32 *);
s32 impact_tinted_particle_spawn(u8, struct17 *, f32 *, f32, f32, f32, f32, s16, u8, s16, s16, u8, u8, s32);
u8 *impact_spark_spawn(struct17 *, f32 *, f32, s16, u8, f32, s32, u8, f32, f32, u8, u8, s32, s16, s16, s32, u8, s32);
s32 random_int(void);
f32 random_float(void);

// beam_impact_effects: effects along a beam from `from` to `to` (dir = to - from); called by obj_bone_beam_impact (game_eu_1DD290)
// with two bone points of an object and a random scale. A vertical probe (collision_floor_dynamic from (from.x, 10000, from.z)
// down to from.y) decides: on a hit whose surface kind (+0x1D) is 3, 10..20 impact_tinted_particle_spawn particles fly from `from`
// along dir * (67 r + 86) / 1000 and nothing else is spawned. Otherwise 3..7 impact_spark_spawn sprites (velocity: a random
// direction of length `scale` (vec3_from_angles_byte) plus dir * (618 r + 201) / 1000) and 10..20 impact_dust_cloud_spawn puffs (random
// direction plus dir * 200 r / 1000). kind (u8) and owner are passed through to every spawn. Returns the last
// spawn's result (the asm leaves it in v0; obj_bone_beam_impact does not read it).
/* was func_15135DD0 */
s32 beam_impact_effects(struct17 *from, struct17 *to, f32 scale, u8 kind, s32 owner) {
    Hit5DD0 hit;
    f32 probe[3];
    f32 dir[3];
    f32 vel[3];
    f32 puff[3];
    s32 n;
    s32 ret;
    f32 f;
    f32 r0;
    f32 r1;
    f32 r2;
    s16 life;
    s32 a;
    s32 b;
    s32 c;

    hit.t = -10000.0f;
    hit.unk18 = 0;
    hit.flags = 0;
    hit.surface = 0;
    hit.unk20 = 0;
    dir[0] = to->unk0 - from->unk0;
    dir[1] = to->unk4 - from->unk4;
    dir[2] = to->unk8 - from->unk8;
    probe[0] = from->unk0;
    probe[1] = 10000.0f;
    probe[2] = from->unk8;
    if (collision_floor_dynamic(probe, 0, from->unk4, &hit) != 0 && hit.surface == 3) {
        for (n = (u32)random_int() % 11 + 10; n > 0; n--) {
            f = (random_float() * 67.0f + 86.0f) * 0.001f;
            vel[0] = dir[0] * f;
            vel[1] = dir[1] * f;
            vel[2] = dir[2] * f;
            life = (u32)random_int() % 52 + 99;
            r0 = random_float();
            r1 = random_float();
            r2 = random_float();
            a = (u32)random_int() % 156 + 100;
            ret = impact_tinted_particle_spawn(0, from, vel, r0 * 50.0f + 30.0f, r1 * 0.0f + 1.01f, 1.0f, r2 * 0.041f, life, a, life,
                                255 / life, 1, kind, owner);
        }
        return ret;
    }
    for (n = (u32)random_int() % 5 + 3; n > 0; n--) {
        f = (random_float() * 618.0f + 201.0f) * 0.001f;
        a = random_int();
        b = random_int();
        vec3_from_angles_byte(a & 0xFF, (b & 0x7F) - 63, scale, vel);
        vel[0] += dir[0] * f;
        vel[1] += dir[1] * f;
        vel[2] += dir[2] * f;
        r0 = random_float();
        a = random_int();
        b = random_int();
        r1 = random_float();
        c = random_int();
        impact_spark_spawn(from, vel, r0 * 1.013f, (u32)a % 21 + 20, (u32)b % 101 + 100, r1 * 4.2000003f + 1.9f, (u32)c % 3 + 3,
                      0, 1.0f, 1.0f, 0, 0, 0, 16, 15, 0, kind, owner);
    }
    for (n = (u32)random_int() % 11 + 10; n > 0; n--) {
        f = random_float() * 200.0f * 0.001f;
        a = random_int();
        b = random_int();
        vec3_from_angles_byte(a & 0xFF, (b & 0x7F) - 63, scale, puff);
        puff[0] += dir[0] * f;
        puff[1] += dir[1] * f;
        puff[2] += dir[2] * f;
        r0 = random_float();
        a = random_int();
        b = random_int();
        r1 = random_float();
        ret = impact_dust_cloud_spawn(from, puff, 0, r0 * 0.147f + -0.30200002f, (u32)a % 52 + 31, (u32)b % 101 + 155,
                            r1 * 50.0f + 50.0f, 0, 1.0f, 1.0f, 0, 0, 1, 0, kind, owner);
    }
    return ret;
}

s32 collision_floor_probe(f32 *, s32, f32, f32 *);
void hitinfo_from_obj_floor(void *, u8 *);
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);

/* was func_15136404 */
void fx_ground_splats_around(struct127 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s32 uB8;
        u8 padBC[0x15];
        s32 uD1;
    } sp;
    f32 temp_f20;
    f32 var_f22;
    s32 temp_s0;
    s32 temp_s0_2;

    if (arg0 != NULL) {
        var_f22 = ((random_float() * 305.0f) + 108.0f) * 0.000001f * (3.1415927f * arg1 * arg1);
        hitinfo_from_obj_floor(&sp.uB4, arg0);
        if (var_f22 > 1.0f) {
            do {
                temp_s0 = random_int();
                vec2_from_angle_byte((s16) (temp_s0 & 0xFF), random_float() * arg1, &sp.uA8, &sp.uB0);
                sp.uA8 += arg0->x_position;
                sp.uB0 += arg0->z_position;
                sp.uAC = arg0->y_position + 500.0f;
                if ((collision_floor_probe(&sp.uA8, 0, arg0->y_position - 5000.0f, &sp.uB4) != 0) && (sp.uD1 != 3)) {
                    sp.u9C = sp.uA8;
                    sp.uA0 = sp.uB4;
                    sp.uA4 = sp.uB0;
                    temp_f20 = random_float();
                    temp_s0_2 = random_int();
                    impact_debris_spawn(0U, (temp_f20 * 20.0f) + 10.0f, (((u32) temp_s0_2 % 101U) + 0x64) & 0xFF, (s32) &sp.uB8, (struct17 *) &sp.u9C, (s16) ((random_int() % 201U) + 0x190), 1U, 1U, 0U, (u8) (s32) arg2, arg3);
                }
                var_f22 -= 1.0f;
            } while (var_f22 > 1.0f);
        }
    }
}
typedef struct {
    s32 v[4];
} Tbl6698;

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x02 */ s16 u2;
    /* 0x04 */ s16 u4;
    /* 0x08 */ s32 u8_;
    /* 0x0C */ s32 uC;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 u11;
    /* 0x12 */ u8 u12;
    /* 0x13 */ u8 u13;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ struct17 pos;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 u3C;
    /* 0x40 */ s32 u40;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 pad46[0x12];
} Blk6698;

extern Tbl6698 g_fx_splash_sprite_ids; /* was D_80089F4C */

/* was func_15136698 */
s32 fx_splash_spawn(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA) {
    s32 obj;
    Blk6698 b;
    f32 scale;
    Tbl6698 tbl;
    s32 a;
    s32 c;

    tbl = g_fx_splash_sprite_ids;
    scale = arg1;
    b.id = tbl.v[random_int() & 3];
    b.u2 = (arg7 ? 2 : 1) + 0x300;
    b.u8_ = 0;
    b.uC = 0;
    b.u10 = 0;
    b.u11 = 0;
    b.u12 = 0;
    b.u13 = 0xFF;
    b.u18 = arg0;
    b.u14 = arg0;
    b.pos = *arg6;
    b.u40 = 0;
    b.u28 = 0.0f;
    b.u2C = 0.0f;
    b.u30 = 0.0f;
    b.u34 = 1.0f;
    b.u38 = 1.0f;
    b.u3C = 1.0f;
    if (arg4 == -1) {
        b.u4 = 300;
    } else {
        b.u4 = arg4 + 0x20;
        b.u40 = 1;
    }
    b.u44 = arg2;
    b.u45 = arg3;
    if (arg8) {
        a = 3;
        c = 0xFF;
    } else {
        a = 0;
        c = 0;
    }
    obj = effect3d_spawn_oriented((s32)&b, 0, 0, 0x1A, 0, (random_int() & 1) + (random_int() & 1), random_int() & 0xFF, 500.0f, 500.0f, 0, arg5, a, c, 0, 4, arg9, argA);
    if (obj != 0) {
        memcpy((void *)(obj + 0x128), &scale, 4);
    }
    return obj;
}

/* was func_151368A8 */
s32 fx_splash_update(struct161520_b *arg0) {
    s16 temp_v0 = arg0->unk1C;
    f32 *temp_v1 = &arg0->unk128;

    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0->unk5C) {
            arg0->unk5C = temp_v0 * 8;
        }
    }
    arg0->unk2C += *temp_v1 * D_800BE9A4;
    arg0->unk30 += *temp_v1 * D_800BE9A4;
    return 1;
}

typedef struct {
    s32 u48;
    s16 u4C;
    u8 u4E;
    s32 u50;
    s32 u54;
    u8 u58;
    u8 u59;
    u8 u5A;
    u8 u5B;
    u8 u5C;
    u8 u5D;
    u8 u5E;
    u8 u5F;
    s32 u60;
    u8 pad64[0xC];
} Blk6918;

/* was func_15136918 */
void fx_glow_spawn(f32 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4, s32 arg5, f32 *arg6, u8 arg7, s32 arg8) {
    Blk6918 s;
    s32 pad; // fakematch: frame slot below the block

    s.u4E = 0x55;
    s.u48 = 0x300;
    s.u50 = 0;
    s.u54 = 0;
    s.u58 = arg1;
    s.u59 = arg2;
    s.u5A = 0;
    s.u5B = 0;
    s.u5C = 0;
    s.u5D = 0;
    s.u60 = 0x280001;
    s.u5E = 1;
    s.u5F = 1;
    if (arg3 == -1) {
        s.u4C = 300;
    } else {
        s.u48 = 0x301;
        s.u4C = arg3 + 0x20;
    }
    sprite_fx_spawn_cam((s32)&s, 0xD, 0, arg5, arg6[0], arg6[1], arg6[2], arg0, arg0, arg4, 0, 0, arg7, arg8);
}

/* was func_15136A1C */
s32 fx_fade_alpha_cap_by_life(struct102 *arg0) {
    s16 temp_v0 = arg0->unk1C;
    if (temp_v0 < 32) {
        if ((temp_v0 * 8) < arg0->unk28) {
            arg0->unk28 = temp_v0 * 8;
        }
    }
    return 1;
}

/* was func_15136A50 */
void point_emitter_spawn_preset(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    struct_eu_EF410 sp1C;

    sp1C.unkC = 10.3f;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg1;
    sp1C.unk8 = arg2;
    sp1C.unk10 = 0.5009f;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 5;
    sp1C.unk18 = 2;
    sp1C.unk19 = -1;
    point_emitter_spawn(&sp1C, 0, arg4, arg5);
}

extern f32 g_spark_emit_speed_scale; /* was D_800A4A04 */
extern f32 g_spark_dust_size_scale; /* was D_800A4A08 */
extern f32 g_spark_dust_size_bias; /* was D_800A4A0C */
/* was func_15136AE4 */
void emitter_spawn_spark(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, struct161520 *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 temp_f2;
    s32 pad;
    u32 sp54;
    u32 sp50;
    f32 sp4C;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_f2 = ((random_float() * 112.0f) + 247.0f) * g_spark_emit_speed_scale;
    sp60[0] = -arg3 * temp_f2;
    sp60[1] = -arg4 * temp_f2;
    sp60[2] = -arg5 * temp_f2;
    sp4C = random_float();
    sp50 = random_int();
    sp54 = random_int();
    impact_dust_cloud_spawn(sp6C, sp60, 0, (sp4C * g_spark_dust_size_scale) + g_spark_dust_size_bias, (sp50 & 0xF) + 0x19, (sp54 % 101) + 0x9B, (random_float() * 119.0f) + 129.0f, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg6->unkC, arg6->unk1);
}

/* emit_debris_on_near_surfaces smoke spec (0x2D bytes used) */
typedef struct {
    /* 0x00 */ s32 u00;
    /* 0x04 */ s32 u04;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;
    /* 0x2C */ u8  dark;
} HitSmokeSpec;
void hitinfo_from_obj_floor(void *, u8 *);
void obj_get_fx_point_b(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void emit_debris_on_near_surfaces(u8 *arg0, u8 arg1, s32 arg2);
void hit_debris_ring_burst(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void object_debris_spawn(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds, u8 arg9, s32 argA);
void impact_burst_small(struct17 *arg0, u8 arg1, s32 arg2);
void ground_scatter_spawn(f32 *arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
extern s32 *g_debris_model_lists[];       /* per hit kind: debris model ids; was D_80089DC0 */
extern s32 g_debris_scales[];        /* debris scales (all 1.0); was D_800A4010 */
extern s32 g_debris_list_counts[];        /* per hit kind: debris kinds; was D_800A42F4 */
extern s32 g_debris_spec_bytes[];        /* per hit kind: debris spec byte +0x40; was D_800A4344 */
extern u8 g_hit_kind_info[][16];     /* per hit kind: +0xE == 2: debris only; was D_800A43B8 */

// object_hit_effects: the hit / break effects of an object by its hit kind (obj_get_hit_kind, 0x63: none), at its
// effect position (obj_get_fx_point_b): debris pieces (debris; two kinds fewer with fewer, or for kind 4 unless the
// object type is 0x16), then unless the kind's +0xE is 2: a smoke puff (smoke; dark for kinds 2 / 15 / 18),
// 18..23 floor splats within 300 below (splats), and the finishing effect (finish: hit_debris_ring_burst for kinds 2 / 15,
// else impact_burst_small). arg6 / arg7 are passed on to every spawner. The asm's v0 is left over from a callee; every
// caller ignores it (obj_impact_burst returns it to its asm caller, which does not read it).
/* was func_15136C3C */
s32 object_hit_effects(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7) {
    HitSmokeSpec spec;
    s32 bounds[9];
    f32 pos[3];
    f32 sizeY;
    f32 sizeX;
    f32 size;
    s32 kind;
    s32 n;
    u8 *info;
    u8 dark;

    if (obj == NULL) {
        return 0;
    }
    size = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
    obj_get_fx_point_b(obj, pos, &sizeX, &sizeY);
    kind = obj_get_hit_kind((struct127 *)obj);
    if (kind == 0x63) {
        return 0;
    }
    hitinfo_from_obj_floor(bounds, obj);
    if (debris) {
        if (fewer || (kind == 4 && obj[4] != 0x16)) {
            n = g_debris_list_counts[kind] - 2;
        } else {
            n = g_debris_list_counts[kind];
        }
        object_debris_spawn(pos, g_debris_model_lists[kind], g_debris_scales, n, size, kind, g_debris_spec_bytes[kind], obj, bounds, arg6, arg7);
    }
    info = g_hit_kind_info[kind];
    if (info[0xE] == 2) {
        return 0;
    }
    if (smoke) {
        spec.u00 = 0xC;
        spec.u04 = 3;
        spec.pos[0] = pos[0];
        spec.pos[1] = pos[1];
        spec.pos[2] = pos[2];
        spec.u14 = 0;
        spec.u16 = 0xFF;
        spec.u18 = -0x40;
        spec.u1A = 0x45;
        spec.u28 = 0x96;
        spec.u2A = 0x64;
        spec.u1C = 998.0f;
        spec.u20 = 25.0f;
        spec.u24 = 10.0f;
        spec.dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        emit_debris_on_near_surfaces((u8 *)&spec, arg6, arg7);
    }
    if (splats) {
        dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        ground_scatter_spawn(pos, pos[1] - 300.0f, 300.0f, bounds, (random_int() % 6U) + 18, 0, (s32)&dark,
                      arg6, arg7);
    }
    if (finish) {
        if (kind == 2 || kind == 15) {
            hit_debris_ring_burst((s32)pos, (s32)bounds, arg6, arg7);
            return 0;
        }
        impact_burst_small((struct17 *)pos, arg6, arg7);
    }
    return 0;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec37C64;
s32 impact_setup_segment(Vec37C64 *a, Vec37C64 *b, Vec37C64 *dir, s32 arg3, s32 arg4, Vec37C64 *p, Vec37C64 *q, Vec37C64 *d);

s32 impact_glow_spawn(f32 *pos, f32 size, u8 alpha, s16 life, u8 type, u8 arg5, s32 arg6);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32 *, s32, f32);
u8 prop_is_flagged(s32);

// impact_burst_effects: hit effect between the points p / q along d (impact_setup_segment sets from = a, to = b, the unit
// direction dir and two side axes; result 0 = nothing, 2 = no sparks / splashes). A impact_glow_spawn flash at a (size
// 192..384, alpha 155..255, life 15..22), 4..7 impact_tinted_particle_spawn debris pieces from b (velocity (dir * 100 + a random
// side offset of up to 50) * (0.093 r + 0.064)), then, unless the result was 2: 4..7 impact_spark_spawn sparks at a
// (random side direction, speed 6..8), and, when D_800BE616 is set, 3..6 rays (collision_ray_cast) from b along dir * 100
// plus a side offset of up to 140: each that hits an object accepted by prop_is_flagged closer than 1999 leaves a
// impact_debris_spawn splash on the hit surface. `type` goes to every spawn as its first / type byte; kind / owner too.
/* was func_15136F50 */
void impact_burst_effects(Vec37C64 *p, Vec37C64 *q, Vec37C64 *d, u8 type, u8 kind, s32 owner) {
    Vec37C64 a;
    Vec37C64 b;
    Vec37C64 dir;
    Vec37C64 side;
    u8 sparks;
    u8 splash;
    Vec37C64 up;
    f32 sc[2];
    f32 vel[3];
    f32 sc2[2];
    f32 v[3];
    f32 sc3[2];
    s16 surf[9];
    struct17 hit;
    f32 dist;
    s32 obj;
    s32 res;
    s32 n;
    s16 m;
    s32 x;
    s32 y;
    f32 r;
    f32 r2;

    splash = 1;
    sparks = 1;
    res = impact_setup_segment(&a, &b, &dir, (s32) &side, (s32) &up, p, q, d);
    if (res == 0) {
        return;
    }
    if (res == 2) {
        sparks = 0;
        splash = 0;
    }
    r = random_float();
    x = random_int();
    y = random_int();
    impact_glow_spawn(&a.x, r * 192.0f + 192.0f, (u32) x % 101 + 155, (y & 7) + 15, type, kind, owner);

    for (n = (random_int() & 3) + 4; n > 0; n--) {
        r = random_float() * 0.0929f + 0.0643f;
        x = random_int();
        vec2_from_angle_byte(x & 0xFF, random_float() * 50.0f, &sc[0], &sc[1]);
        vel[0] = (dir.x * 100.0f + side.x * sc[0] + up.x * sc[1]) * r;
        vel[1] = (dir.y * 100.0f + side.y * sc[0] + up.y * sc[1]) * r;
        vel[2] = (dir.z * 100.0f + side.z * sc[0] + up.z * sc[1]) * r;
        r2 = random_float();
        r = random_float();
        x = random_int();
        y = random_int();
        impact_tinted_particle_spawn(type, (struct17 *) &b, vel, r2 * 80.0f + 120.0f, 1.033618f, 0.959544f, r * 0.0f,
                      (u32) x % 31 + 30, (u32) y % 156 + 100, 0x2E, 5, 0, kind, owner);
    }

    if (sparks) {
        for (m = (random_int() & 3) + 4; m != 0; m--) {
            x = random_int();
            vec2_from_angle_byte(x & 0xFF, random_float() * 2.0f + 6.0f, &sc2[0], &sc2[1]);
            v[0] = side.x * sc2[0] + up.x * sc2[1];
            v[1] = side.y * sc2[0] + up.y * sc2[1];
            v[2] = side.z * sc2[0] + up.z * sc2[1];
            x = random_int();
            r = random_float();
            y = random_int();
            impact_spark_spawn((struct17 *) &a, v, 0.0f, (u32) x % 6 + 8, 0xFF, r * 1.3000001f + 1.9f,
                          (u32) y % 3 + 4, 0, 1.0f, 1.0f, 1, type, 0, 0x10, 0xF, 0, kind, owner);
        }
    }

    if (!splash || !D_800BE616) {
        return;
    }
    for (n = (random_int() & 3) + 3; n != 0; n--) {
        x = random_int();
        vec2_from_angle_byte(x & 0xFF, random_float() * 140.0f, &sc3[0], &sc3[1]);
        if (collision_ray_cast(b.x, b.y, b.z, dir.x * 100.0f + side.x * sc3[0] + up.x * sc3[1],
                          dir.y * 100.0f + side.y * sc3[0] + up.y * sc3[1],
                          dir.z * 100.0f + side.z * sc3[0] + up.z * sc3[1], 0, surf, &hit.unk0, &hit.unk4, &hit.unk8,
                          &dist, &obj, 0, 0.0f) != 0
            && prop_is_flagged(obj) != 0 && dist < 1999.0f) {
            r = random_float();
            x = random_int();
            y = random_int();
            impact_debris_spawn(type, r * 16.0f + 25.0f, (u32) x % 156 + 100, (s32) surf, &hit, (u32) y % 101 + 100, 1, 1, 1,
                          kind, owner);
        }
    }
}

typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x6F];
    /* 0x074 */ u8 unk74;
    /* 0x075 */ u8 pad75[0x8F];
    /* 0x104 */ u8 unk104;
    /* 0x105 */ u8 pad105[0x20];
    /* 0x125 */ u8 unk125;
    /* 0x126 */ u8 pad126[0xA4];
    /* 0x1CA */ u8 unk1CA;
    /* 0x1CB */ u8 pad1CB[9];
    /* 0x1D4 */ s32 unk1D4;
} Obj7610;

void impact_burst_effects(Vec37C64 *arg0, Vec37C64 *arg1, Vec37C64 *arg2, u8 arg3, u8 arg4, s32 arg5); /* P282: as the definition */
void impact_glow_sparks_spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7);
void pos_debris_burst_spawn(s32 arg0, u8 arg1, s32 arg2);

/* was func_15137610 */
void object_impact_effects(Obj7610 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    s32 v;

    if (arg0 != NULL) {
        if (arg0->unk1D4 == 0) {
            return;
        }
        if ((arg0->unk74 & 0xF) == 0xF) {
            return;
        }
        if (arg0->unk1CA <= 0) {
            return;
        }
        switch (arg0->unk4) {
        case 0x5:
        case 0xAD:
        case 0xAE:
        case 0xAF:
            v = 3;
            break;
        case 0x5B:
        case 0x70:
        case 0xA6:
        case 0xB2:
        case 0xB4:
            pos_debris_burst_spawn(arg1, arg4, arg5);
            v = 2;
            break;
        case 0x28:
        case 0x77:
        case 0x8A:
        case 0x8C:
            if (random_int() & 1) {
                return;
            }
            v = 2;
            break;
        case 0x42:
            if (random_int() & 3) {
                return;
            }
            v = 2;
            break;
        case 0x5A:
        case 0x5F:
        case 0x74:
        case 0x75:
        case 0x7A:
        case 0x8D:
        case 0xB1:
            if (arg0->unk125 == 0xFF) {
                if (random_int() & 0x1F) {
                    return;
                }
                v = 1;
            } else {
                if (arg0->unk125 != 0) {
                    return;
                }
                if (arg0->unk104 != 0) {
                    return;
                }
                v = 1;
            }
            break;
        default:
            if (arg0->unk125 != 0) {
                return;
            }
            if (arg0->unk104 != 0) {
                return;
            }
            v = 0;
            break;
        }
    } else {
        v = 0;
    }
    switch (v) {
    case 1:
        impact_glow_sparks_spawn(arg1, arg2, arg3, 1, 1, 1, arg4, arg5);
        break;
    case 2:
        fire_embers_spawn((void *)arg1, arg4, arg5);
        break;
    case 3:
        impact_burst_effects((Vec37C64 *) arg1, (Vec37C64 *) arg2, (Vec37C64 *) arg3, 1, arg4, arg5);
        break;
    case 0:
    default:
        impact_burst_effects((Vec37C64 *) arg1, (Vec37C64 *) arg2, (Vec37C64 *) arg3, 0, arg4, arg5);
        break;
    }
}

s32 obj_get_hit_kind(struct127 *arg0);
void obj_get_fx_point_b(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void hitinfo_from_obj_floor(void *, u8 *);
s32 pos_in_world_bounds(f32 *);
s32 collision_floor_probe(f32 *, s32, f32, f32 *);
void object_debris_spawn(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds, u8 arg9, s32 argA);
void impact_burst_small(struct17 *arg0, u8 arg1, s32 arg2);
s32 fx_splash_spawn(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
typedef struct { f32 x, y, z; } V3; /* as game_eu_1E3DD0 */
s32 ripple_spawn_flat(V3 *arg0, V3 *arg1, f32 arg2, V3 *arg3, V3 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD);
s32 ripple_spawn_alt(V3 *arg0, V3 *arg1, f32 arg2, V3 *arg3, V3 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD);
void obj_set_destroyed(struct127 *arg0);
f32 random_float(void);
s32 random_int(void);
extern s32 *g_debris_model_lists[];       /* per hit kind: debris model ids; was D_80089DC0 */
extern s32 g_debris_scales[];        /* debris scales (all 1.0); was D_800A4010 */
extern s32 g_debris_list_counts[];        /* per hit kind: debris kinds; was D_800A42F4 */
extern s32 g_debris_spec_bytes[];        /* per hit kind: debris spec byte +0x40; was D_800A4344 */
extern u8 g_hit_kind_info[][16];     /* per hit kind: +0xE == 2: debris only; was D_800A43B8 */

// object_break_effects: the break effects of `obj` (called by game_83300 with (obj, 0xFF, 1)): nothing for hit kind
// 0x63 (obj_get_hit_kind) or when no floor is found under the effect position + 100 (pos_in_world_bounds). The floor
// (collision_floor_probe within 500 below, bounds record) sets the drop height; then debris without the first two models
// (object_debris_spawn, two kinds fewer) at the effect position (obj_get_fx_point_b). Unless the kind's g_hit_kind_info +0xE is 2:
// impact_burst_small at the position and, on a floor with bounds +0x1C bit 0 (water), a splash (fx_splash_spawn, random
// sizes / alpha / life) and a ripple model (ripple_spawn_flat or ripple_spawn_alt at random, 10 above the floor, random
// rotation, scale 0.6..0.7). Ends with obj_set_destroyed(obj). arg1 / arg2 are passed on to every spawner.
/* was func_1513783C */
void object_break_effects_floor(struct127 *obj, s32 arg1, s32 arg2) {
    u8 *o = (u8 *)obj;
    s32 bounds[9];
    f32 pos[3];
    f32 sizeX;
    f32 sizeY;
    f32 size;
    struct17 drop;
    V3 at;
    V3 vel;
    V3 rot;
    V3 zero;
    s32 (*ripple)(V3 *, V3 *, f32, V3 *, V3 *, f32, s16, u8, s32, f32, u8, u8, u8, s32);
    s32 kind;
    s32 water;
    f32 r1, r2;
    u32 i1, i2, i3;

    if (obj == NULL) {
        return;
    }
    kind = obj_get_hit_kind(obj);
    if (kind == 0x63) {
        return;
    }
    size = (*(f32 *)(o + 0x14C) + *(f32 *)(o + 0x150)) * 0.5f;
    obj_get_fx_point_b(o, pos, &sizeX, &sizeY);
    hitinfo_from_obj_floor(bounds, o);
    drop.unk0 = pos[0];
    drop.unk4 = pos[1] + 100.0f;
    drop.unk8 = pos[2];
    if (pos_in_world_bounds((f32 *)&drop) == 0) {
        return;
    }
    if (collision_floor_probe((f32 *)&drop, 0, drop.unk4 - 500.0f, (f32 *)bounds) != 0) {
        water = (((u8 *)bounds)[0x1C] & 1) ? 1 : 0;
        drop.unk4 = *(f32 *)&bounds[0];
    } else {
        drop.unk0 = pos[0];
        drop.unk4 = pos[1];
        drop.unk8 = pos[2];
        water = 0;
    }
    object_debris_spawn(pos, g_debris_model_lists[kind] + 2, g_debris_scales, g_debris_list_counts[kind] - 2, size, kind, g_debris_spec_bytes[kind], o, bounds,
                  arg1, arg2);
    if (g_hit_kind_info[kind][0xE] != 2) {
        impact_burst_small((struct17 *)pos, arg1, arg2);
        if (water) {
            r1 = random_float();
            r2 = random_float();
            i1 = random_int();
            i2 = random_int();
            i3 = random_int();
            fx_splash_spawn((r1 * 25.0f + 75.0f) * 0.001f, (r2 * 106.0f + 75.0f) * 1e-05f, i1 % 101 + 0x9B,
                          i2 % 101 + 0x64, i3 % 56 + 0xCB, (s32)&bounds[1], &drop, 1, 1, arg1, arg2);
            ripple = (random_int() & 1) ? ripple_spawn_flat : ripple_spawn_alt;
            at.x = drop.unk0;
            at.y = drop.unk4 + 10.0f;
            at.z = drop.unk8;
            vel.x = 0.0f;
            vel.y = 0.0f;
            vel.z = 0.0f;
            rot.x = random_float() * 360.0f;
            rot.y = random_float() * 360.0f;
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            rot.z = random_float() * 360.0f;
            ripple(&at, &vel, (random_float() * 101.0f + 600.0f) * 0.001f, &rot, &zero, 0.0f, 1000, 0xFF, 0xFF, 1.0f,
                   3, 0, arg1, arg2);
        }
    }
    obj_set_destroyed(obj);
}

s32 vec3_normalize_len(Vec37C64 *, Vec37C64 *, s32 *, s32 *);
s32 vec3_make_basis(Vec37C64 *, s32, s32);

/* was func_15137C64 */
s32 impact_setup_segment(Vec37C64 *a, Vec37C64 *b, Vec37C64 *dir, s32 arg3, s32 arg4, Vec37C64 *p, Vec37C64 *q, Vec37C64 *d) {
    s32 sp2C;
    s32 sp28;

    if (p != NULL && q != NULL) {
        *a = *p;
        *b = *q;
    } else if (p != NULL) {
        *a = *p;
        *b = *p;
    } else if (q != NULL) {
        *a = *q;
        *b = *q;
    } else {
        return 0;
    }
    if (d == NULL) {
        dir->x = b->x - a->x;
        dir->y = b->y - a->y;
        dir->z = b->z - a->z;
        if (vec3_normalize_len(dir, dir, &sp2C, &sp28) == 0) {
            return 0;
        }
    } else {
        *dir = *d;
    }
    if (vec3_make_basis(dir, arg3, arg4) == 0) {
        return 2;
    }
    return 1;
}

/* was func_15137E10 */
s32 bone_emitter_rate_random(struct161520 *arg0) {
    arg0->unk74 = ((random_float() * 50.0f) + 580.0f) * 0.001f;
    return 1;
}

/* was func_15137E60 */
void bone_emitter_emit_spark(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 sp54[3];
    f32 sp50;
    s16 sp4E;
    u8 sp4D;
    f32 sp48;

    bone_emitter_spark_params(arg0, arg1, arg2, arg3, arg4, arg5, sp6C, sp60, sp54, &sp50, &sp4E, &sp4D, &sp48);
    impact_dust_cloud_spawn(sp6C, sp54, 0, sp50, sp4E, sp4D, sp48, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg5->unkC, arg5->unk1);
}
/* was func_15137F30 */
void bone_emitter_spark_params(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, struct161520 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s16 *argA, u8 *argB, f32 *argC) {
    (*(f32 *)((u8 *)arg6 + 0)) = ((*(f32 *)((u8 *)arg2 + 0)) * arg4) + (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)arg6 + 4)) = ((*(f32 *)((u8 *)arg2 + 4)) * arg4) + (*(f32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)arg6 + 8)) = ((*(f32 *)((u8 *)arg2 + 8)) * arg4) + (*(f32 *)((u8 *)arg0 + 8));
    (*(f32 *)((u8 *)arg7 + 0)) = ((*(f32 *)((u8 *)arg3 + 0)) * arg4) + (*(f32 *)((u8 *)arg1 + 0));
    (*(f32 *)((u8 *)arg7 + 4)) = ((*(f32 *)((u8 *)arg3 + 4)) * arg4) + (*(f32 *)((u8 *)arg1 + 4));
    (*(f32 *)((u8 *)arg7 + 8)) = ((*(f32 *)((u8 *)arg3 + 8)) * arg4) + (*(f32 *)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)arg8 + 0)) = ((*(f32 *)((u8 *)arg7 + 0)) - (*(f32 *)((u8 *)arg6 + 0))) * arg5->unk74;
    (*(f32 *)((u8 *)arg8 + 4)) = (f32) (((*(f32 *)((u8 *)arg7 + 4)) - (*(f32 *)((u8 *)arg6 + 4))) * arg5->unk74);
    (*(f32 *)((u8 *)arg8 + 8)) = (f32) (((*(f32 *)((u8 *)arg7 + 8)) - (*(f32 *)((u8 *)arg6 + 8))) * arg5->unk74);
    *arg9 = ((random_float() * 217.0f) + -456.0f) * 0.001f;
    *argA = (random_int() % 31U) + 0x1E;
    *argB = (random_int() % 156U) + 0x64;
    *argC = (random_float() * 35.0f) + 40.0f;
}

/* was func_151380B4 */
s32 obj_get_hit_effect_pos(struct127 *arg0, s32 arg1, void *arg2) {
    struct255 *temp_v0 = arg0->unk1D4;

    if (temp_v0 == NULL) {
        return 0;
    }
    if ((arg0->unk74 & 0xF) == 0xF) {
        return 0;
    }
    mtx_transform_point_or_origin(g_hit_kind_info[arg1], arg2, (u8 *)temp_v0 + 0x300);
    return 1;
}

/* The 0x3C-byte spec bone_emitter_spawn copies into a new type-0x29 effect (+0x18 there). */
typedef struct {
    /* 0x00 */ u8 u00;          /* the object's +0x3B byte */
    /* 0x04 */ u8 *obj;
    /* 0x08 */ u8 u08;          /* 0xC with the flag, else 1 */
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;         /* 20.0 */
    /* 0x20 */ f32 u20;
    /* 0x24 */ u8 u24;
    /* 0x26 */ s16 u26;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;         /* 100 / 200 for hit kinds 8 / 9, else 500 */
    /* 0x2C */ s16 sound;       /* sfx_emitter_start handle */
    /* 0x2E */ u8 u2E;
    /* 0x2F */ u8 u2F;          /* 5 when the kind's +0xE is 0, else 6 */
    /* 0x30 */ s8 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ u8 u38;
    /* 0x39 */ s8 u39;
} HitKindEffectSpec;

// object_hit_kind_effect_spawn: unless hit kind `kind`'s g_hit_kind_info row has +0xE == 2 (debris only), starts sound
// 0x4FE at the object's position and spawns the type-0x29 hit effect (bone_emitter_spawn) attached to the object; `flag`
// selects variant 0xC (else 1), kinds 8 / 9 get a shorter life (100 when the object's +0x94 has any of bits 1..3, else
// 200; other kinds 500). Returns what the asm leaves in v0: the new effect, or the kind's row when nothing is spawned
// (s32 as game_eu_1C1A20 declares it; every caller ignores it).
/* was func_15138120 */
s32 object_hit_kind_effect_spawn(struct127 *arg0, s32 kind, u8 flag) {
    HitKindEffectSpec spec;
    u8 *obj = (u8 *)arg0;
    u8 *info = g_hit_kind_info[kind];

    if (info[0xE] == 2) {
        return (s32)info;
    }
    spec.u00 = obj[0x3B];
    spec.obj = obj;
    spec.u08 = flag ? 0xC : 1;
    spec.u0C = 0.0f;
    spec.u10 = 0.0f;
    spec.u14 = 0.0f;
    spec.u18 = 0.0f;
    spec.u1C = 20.0f;
    spec.u20 = 0.0f;
    spec.u24 = 2;
    spec.u26 = 0x28;
    spec.u28 = 0x10;
    if (kind == 8 || kind == 9) {
        spec.u2A = (*(s32 *)(obj + 0x94) & 0xE) ? 100 : 200;
    } else {
        spec.u2A = 500;
    }
    spec.u2E = 5;
    spec.u2F = (info[0xE] == 0) ? 5 : 6;
    spec.u30 = -1;
    spec.u34 = 1.0f;
    spec.u38 = 0;
    spec.u39 = -1;
    spec.sound = sfx_emitter_start(0x4FE, (s16)(s32)(*(f32 *)(obj + 0x14)), (s16)(s32)(*(f32 *)(obj + 0x18)),
                               (s16)(s32)(*(f32 *)(obj + 0x1C)), 0x5DC0, 0x258, 0x12C, (s32)&sfx_cb_fade_out,
                               (void *)100, 0, 0, 0);
    return (s32)bone_emitter_spawn((u8 *)&spec, 0);
}

extern u8 D_800A43C6[];
/* was func_151382E0 */
void object_hit_kind_sparks(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    struct_eu_15154488 sp24;
    s32 kind;

    kind = D_800A43C6[arg1 * 16];
    if (kind == 2) {
        return;
    }
    sp24.unk8 = *(struct17 *)arg0;
    sp24.unk14 = 1.9799999f;
    sp24.unk18 = 2.01f;
    sp24.unk1C = 0.202f;
    sp24.unk20 = 0.646f;
    sp24.unk24 = 4.0f;
    sp24.unk28 = 9.0f;
    sp24.unk2C = 0x12;
    sp24.unk2E = 7;
    sp24.unk0 = 0;
    sp24.unk2 = 0xFF;
    sp24.unk4 = -0x3F;
    sp24.unk6 = 0x4E;
    sp24.unk30 = 3;
    sp24.unk32 = 3;
    sp24.unk34 = 0x14;
    sp24.unk36 = 0x1E;
    sp24.unk38 = 0x9B;
    sp24.unk3A = 0x64;
    sp24.unk44 = 0x10;
    sp24.unk46 = 0xF;
    sp24.unk48 = 0;
    sp24.unk40 = 0.3f;
    if (kind == 1) {
        sp24.unk3C = 1;
    } else {
        sp24.unk3C = 0;
    }
    emit_sparks_in_angle_range(&sp24, &sp24.unk8, (s32) arg2, arg3, arg4);
}

/* mdl_particle_spawn / mdl_particle_spawn_ex particle request (0x7C bytes on the stack; layout as in game_eu_E9450) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 pos[3];
    /* 0x1C */ f32 scl[3];
    /* 0x28 */ f32 at[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ s32 u50;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 u56;
    /* 0x58 */ u8 u58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[8];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ struct127 *obj;
    /* 0x70 */ u8 uid;
    /* 0x71 */ u8 pad71;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x76 */ u8 pad76[6];
} Spark9768;
s32 mdl_particle_spawn(Spark9768 *, s32, s32, s32, u8, s32);
s32 mdl_particle_spawn_ex(Spark9768 *, s32, s32, s32, s32, u8, s32);
void mtx_decompose(void *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void vec3_from_angles_byte(s16, s16, f32, f32 *);
u8 *attachment_find_by_slot(struct127 *, s32, s32);
extern s32 g_hit4_sounds[3];       /* hit kind 4: sounds tried in order (attachment_find_by_slot); was D_800A44F8 */
extern s32 g_hit4_spark_sprites[3];       /* hit kind 4: spark sprite per sound found; was D_800A4504 */
extern s32 g_hit5_flag_bits[4];       /* hit kind 5: +0x94 flag bits, a spark for each clear one; was D_800A4510 */
extern s32 g_hit5_spark_sprites[4];       /* hit kind 5: spark sprites; was D_800A4520 */
extern s32 g_hit6_flag_bits[2];       /* hit kind 6: +0x94 flag bits; was D_800A4530 */
extern s32 g_hit6_spark_sprites[2];       /* hit kind 6: spark sprites; was D_800A4538 */

// object_hit_smoke_puff: generic hit effect of object_hit_effect_generic. A mdl_particle_spawn_ex smoke puff (sprite = hit kind row
// g_hit_kind_info[hit] +0xC, life 250..300, size (xz_scale + y_scale) / 2, x 0.6 for hit kind 15) from the model's
// translation (model matrix +0x300, mtx_decompose) aimed at `pos`; y scale 1.0 for row type (+0xE) 1, 2.0 for type 2,
// else 0. Then, reusing the request, mdl_particle_spawn sparks: hit kind 4: the sprite g_hit4_spark_sprites[i] of the first
// g_hit4_sounds[i] sound the object has (attachment_find_by_slot); kind 5 / 6: one per clear +0x94 flag bit (g_hit5_flag_bits /
// g_hit6_flag_bits) with sprite g_hit5_spark_sprites / g_hit6_spark_sprites. kind (a byte) and owner go to every spawn. The asm returns a
// leftover v0 that its only caller (object_hit_effect_generic, void) ignores.
/* was func_15138424 */
void object_hit_smoke_puff(struct127 *obj, f32 *pos, s32 hit, void *arg3, u8 kind, s32 owner) {
    f32 trans[3];
    f32 scl[3];
    f32 rot[3];
    Spark9768 req;
    u8 *info;
    s32 a;
    s32 b;
    u8 i;
    u8 found;

    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    info = g_hit_kind_info[hit];
    req.scl[0] = 1.0f;
    req.u00 = 20.0f;
    req.u04 = 0.56100005f;
    if (info[0xE] == 1) {
        req.scl[1] = 1.0f;
    } else {
        req.scl[1] = 0.0f;
    }
    if (info[0xE] == 2) {
        req.scl[1] = 2.0f;
    }
    req.scl[2] = 1.0f;
    req.u50 = 0x39E9;
    req.u44 = 0.0f;
    req.life = (u32) random_int() % 51 + 250;
    req.u56 = *(u16 *) (info + 0xC);
    req.u0C = ((info == g_hit_kind_info[15]) ? 0.6f : 1.0f) * ((obj->xz_scale + obj->y_scale) * 0.5f);
    req.u08 = req.u0C;
    req.u4C = (random_float() * 292.0f + -1099.0f) * 0.001f;
    req.at[0] = pos[0];
    req.at[1] = pos[1];
    req.at[2] = pos[2];
    a = random_int();
    b = random_int();
    vec3_from_angles_byte(a & 0xFF, (u32) b % 21 - 83, random_float() * 8.0f + 9.0f, req.vel);
    req.pos[0] = trans[0];
    req.pos[1] = trans[1];
    req.pos[2] = trans[2];
    req.u40 = (random_float() * 24496.0f + -12248.0f) * 0.001f;
    req.u48 = (random_float() * 24496.0f + -12248.0f) * 0.001f;
    req.u58 = 0;
    req.u5C = 0;
    req.u60[0] = 0xFF;
    req.u60[1] = 13;
    req.u60[2] = 0;
    req.u60[3] = 8;
    req.u60[4] = 0;
    req.u60[5] = 0;
    req.u60[6] = 0;
    req.u60[7] = 0;
    req.u68 = 2;
    req.u6A = 1;
    req.obj = obj;
    req.uid = obj->unique_id;
    req.u72 = 12;
    req.u74 = 21;
    mdl_particle_spawn_ex(&req, 3, 0xFF, (s32) arg3, 0, kind, owner);

    if (info == g_hit_kind_info[4]) {
        found = FALSE;
        for (i = 0; i < 3; i++) {
            if (attachment_find_by_slot(obj, g_hit4_sounds[i], 0) != NULL) {
                found = TRUE;
                break;
            }
        }
        if (found) {
            req.u56 = g_hit4_spark_sprites[i];
            mdl_particle_spawn(&req, 3, 0xFF, 0, kind, owner);
        }
    } else if (info == g_hit_kind_info[5]) {
        for (i = 0; i < 4; i++) {
            if (!(g_hit5_flag_bits[i] & obj->unk94)) {
                req.u56 = g_hit5_spark_sprites[i];
                mdl_particle_spawn(&req, 3, 0xFF, 0, kind, owner);
            }
        }
    } else if (info == g_hit_kind_info[6]) {
        for (i = 0; i < 2; i++) {
            if (!(g_hit6_flag_bits[i] & obj->unk94)) {
                req.u56 = g_hit6_spark_sprites[i];
                mdl_particle_spawn(&req, 3, 0xFF, 0, kind, owner);
            }
        }
    }
}

// bone_bounce_splash_b: handler 8 of D_80089CD4 (`s32 (u8 *, f32, f32, f32, f32, u8 *)`), twin of bone_bounce_splash:
// bounces the object on the ground (y velocity +0x48 flipped, velocities +0x44..+0x58 scaled by +0x14, y +0x3C =
// +0x10 + ground; under a bounce speed of 4 velocities +0x44..+0x5C cleared and flags 0x69 of +0x60 dropped). Unless
// +0x30 is 2.0 it spawns a splash (impact_debris_spawn) at (+0x38, ground, +0x40): kind 1 when +0x30 != 0, size (39.8 +
// 25.4 * random) * mean of +0x18 / +0x1C, alpha 100..200, life 80..180, then clears +0x2C. Returns 1.
/* was func_151389A8 */
s32 bone_bounce_splash_b(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 ground, u8 *bone) {
    f32 fac = *(f32 *) (arg0 + 0x14);
    struct17 pos;
    s32 kind;
    f32 r;
    u32 alpha;
    u32 life;

    *(f32 *) (arg0 + 0x48) = *(f32 *) (arg0 + 0x48) * -fac;
    *(f32 *) (arg0 + 0x3C) = *(f32 *) (arg0 + 0x10) + ground;
    *(f32 *) (arg0 + 0x44) *= fac;
    *(f32 *) (arg0 + 0x4C) *= fac;
    *(f32 *) (arg0 + 0x50) *= fac;
    *(f32 *) (arg0 + 0x54) *= fac;
    *(f32 *) (arg0 + 0x58) *= fac;
    if (fabsf(*(f32 *) (arg0 + 0x48)) < 4.0f) {
        *(f32 *) (arg0 + 0x44) = 0.0f;
        *(s32 *) (arg0 + 0x60) &= ~0x69;
        *(f32 *) (arg0 + 0x48) = 0.0f;
        *(f32 *) (arg0 + 0x4C) = 0.0f;
        *(f32 *) (arg0 + 0x50) = 0.0f;
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    if (*(f32 *) (arg0 + 0x30) == 2.0f) {
        return 1;
    }
    pos.unk0 = *(f32 *) (arg0 + 0x38);
    pos.unk4 = ground;
    pos.unk8 = *(f32 *) (arg0 + 0x40);
    kind = (*(f32 *) (arg0 + 0x30) == 0.0f) ? 0 : 1;
    r = random_float();
    alpha = random_int();
    life = random_int();
    impact_debris_spawn(kind, (r * 25.4f + 39.8f) * ((*(f32 *) (arg0 + 0x18) + *(f32 *) (arg0 + 0x1C)) * 0.5f),
                  alpha % 101 + 100, (s32) bone, &pos, life % 101 + 80, 1, 1, 0, arg0[0xC], arg0[1]);
    *(f32 *) (arg0 + 0x2C) = 0.0f;
    return 1;
}

/* was func_15138BC0 */
void object_hit_effect_generic(struct127 *arg0, u8 arg1, s32 arg2) {
    s32 temp_v0;
    f32 sp50[3];
    u8 sp4F;
    f32 sp28[9];

    temp_v0 = obj_get_hit_kind(arg0);
    if (temp_v0 != 0x63) {
        sp4F = obj_get_hit_effect_pos(arg0, temp_v0, sp50);
        object_hit_kind_effect_spawn(arg0, temp_v0, 1);
        if (sp4F != 0) {
            hitinfo_from_obj_floor(sp28, arg0);
            object_hit_kind_sparks(sp50, temp_v0, sp28, arg1, arg2);
            object_hit_smoke_puff(arg0, sp50, temp_v0, sp28, arg1, arg2);
        }
    }
}

void object_hit_sparks_flash(struct127 *, s32 *, u8, s32 *, u8, s32); /* P282: void, flag / kind read as bytes */
void object_hit_sparks(struct127 *, s32 *, f32, s32 *, u8, s32); /* P95: f32 (was the bit pattern as an int); P242: void (v0 is a leftover, no caller reads it) */
void object_hit_sparks_small(struct127 *, s32 *, s32 *, s32, s32); /* P282: void (leftover v0, object_hit_effect is void) */
void object_hit_sparks_four(struct127 *, s32 *, s32 *, s32, s32); /* P282: void */
void object_hit_sparks_pair(struct127 *, s32 *, s32, s32 *, u8, s32); /* P282: void, kind read as a byte */
void object_hit_sparks_burst(struct127 *, s32 *, s32 *, s32, s32); /* P282: void */

/* was func_15138C80 */
void object_hit_effect(struct127 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u38;
        u8 pad3C[0x23];
        u8 u5F;
        s32 u60;
        u8 pad64[0x8];
        s32 u6C;
    } sp;
    s32 temp_s1;
    s32 temp_v0;

    temp_s1 = arg1 & 0xFF;
    temp_v0 = obj_get_hit_kind(arg0);
    if ((temp_v0 != 0x63) && (sp.u6C = temp_v0, sp.u5F = obj_get_hit_effect_pos(arg0, temp_v0, &sp.u60), object_hit_kind_effect_spawn(arg0, sp.u6C, 1U), (sp.u5F != 0))) {
        hitinfo_from_obj_floor(&sp.u38, arg0);
        object_hit_kind_sparks(&sp.u60, sp.u6C, &sp.u38, temp_s1 & 0xFF, arg2);
        switch (sp.u6C) {
        case 16:
            object_hit_sparks_burst(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 17:
            pos_debris_burst_spawn((s32) &sp.u60, temp_s1 & 0xFF, arg2);
            return;
        case 0:
        case 7:
            object_hit_sparks_four(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 3:
            object_hit_sparks_flash(arg0, &sp.u60, 1, &sp.u38, temp_s1, arg2);
            return;
        case 5:
        case 6:
            object_hit_sparks_flash(arg0, &sp.u60, 0, &sp.u38, temp_s1, arg2);
            return;
        case 15:
            object_hit_sparks(arg0, &sp.u60, 0.6f, &sp.u38, temp_s1, arg2); /* P95: was 0x3F19999A as an int */
            return;
        case 2:
            object_hit_sparks(arg0, &sp.u60, 1.0f, &sp.u38, temp_s1, arg2); /* P95: was 0x3F800000 as an int */
            return;
        case 4:
            object_hit_burst((u8 *) arg0, (s32) &sp.u60, (s32) &sp.u38, temp_s1 & 0xFF, arg2);
            return;
        case 8:
        case 9:
            object_hit_sparks_pair(arg0, &sp.u60, (sp.u6C == 9) & 0xFF, &sp.u38, temp_s1, arg2);
            return;
        default:
            object_hit_sparks_small(arg0, &sp.u60, &sp.u38, temp_s1 & 0xFF, arg2);
            break;
        }
    }
}
extern u8 g_hit_flash_masks[6];        /* 6 bit masks (one picked at random); was D_800A4540 */
extern s32 g_hit_flash_spark_ids[4];       /* spark sprite ids; was D_800A4548 */
extern s32 g_hit_flash_smoke_ids[4];       /* smoke sprite ids; was D_800A4558 */
extern f32 g_hit_flash_smoke_pts[4][3];    /* smoke start points in model space; was D_800A4568 */
extern f32 g_hit_flash_point[3];       /* flash start point in model space; was D_800A4598 */

// object_hit_sparks_flash: hit types 3 (big = 1) / 5 / 6 (big = 0) of object_hit_effect. As object_hit_sparks_small with four
// sparks / puffs (one of six masks g_hit_flash_masks, spark life 100); when `big` is set and the object has a model, one
// more mdl_particle_spawn_ex puff (sprite 0x48, life 100..160) from the model point g_hit_flash_point, speed 10.9..18.0.
/* was func_15138E98 */
void object_hit_sparks_flash(struct127 *obj, s32 *pos, u8 big, s32 *arg3, u8 kind, s32 owner) {
    Spark9768 flash;
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 a;
    s32 b;
    f32 size;
    u8 *p;

    mask = &g_hit_flash_masks[(u32) random_int() % 6 & 0xFF];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.scl[0] = 1.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_flash_spark_ids[i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    impact_burst((s32) pos, kind, owner);
    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 0.0f;
    smoke.scl[2] = 1.0f;
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_flash_smoke_ids[i];
            mtx_transform_point_or_origin(g_hit_flash_smoke_pts[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg3, 0, kind, owner);
        }
    }

    if (!big) {
        return;
    }
    flash.u00 = 1.0f;
    flash.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    flash.u0C = size;
    flash.u08 = size;
    flash.pos[0] = trans[0];
    flash.pos[1] = trans[1];
    flash.pos[2] = trans[2];
    flash.scl[0] = 1.0f;
    flash.scl[1] = 1.0f;
    flash.scl[2] = 1.0f;
    flash.u44 = 0.0f;
    flash.u58 = 0;
    flash.u5C = 0;
    flash.u60[0] = 0xFF;
    flash.u60[2] = 0;
    flash.u60[4] = 0;
    flash.u60[5] = 0;
    flash.u60[6] = 0;
    flash.u60[7] = 0;
    flash.u6A = 1;
    flash.obj = obj;
    flash.u72 = 12;
    flash.u74 = 21;
    flash.u50 = 0x1039E9;
    flash.u60[1] = 13;
    flash.u68 = 2;
    flash.u60[3] = 11;
    flash.u56 = 0x48;
    flash.uid = obj->unique_id;
    mtx_transform_point_or_origin(g_hit_flash_point, flash.at, (u8 *) obj->unk1D4 + 0x300);
    a = random_int();
    b = random_int();
    vec3_from_angles_byte(a & 0xFF, (b & 0xF) - 60, random_float() * 7.1499996f + 10.889999f, flash.vel);
    flash.u40 = random_float() * 48.158f + -24.079f;
    flash.u48 = random_float() * 48.158f + -24.079f;
    flash.u4C = random_float() * 0.323f + -1.4210001f;
    flash.life = (u32) random_int() % 61 + 100;
    mdl_particle_spawn_ex(&flash, 3, 0xFF, (s32) arg3, 0, kind, owner);
}

// bone_bounce_splash: handler 9 of D_80089CD4 (`s32 (u8 *, f32, f32, f32, f32, u8 *)`, mdl_particle_spawn_ex's dispatcher;
// only `ground` (the 5th argument) and `bone` are used). Bounces the object on the ground: the y velocity +0x48
// flips and every velocity +0x44..+0x58 is scaled by the restitution +0x14, y +0x3C = +0x10 + ground; under a
// bounce speed of 4 the velocities +0x44..+0x5C are cleared and flags 0x69 of +0x60 dropped. Unless +0x30 is 2.0,
// it then spawns a splash (impact_debris_spawn) at (+0x38, ground, +0x40): kind 1 when +0x30 != 0, size (19.7 + 27.6 *
// random) * mean of +0x18 / +0x1C, alpha 100..200, life 80..223, with +0x0C / +0x01 of the object. Returns 1.
/* was func_15139578 */
s32 bone_bounce_splash(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 ground, u8 *bone) {
    f32 fac = *(f32 *) (arg0 + 0x14);
    struct17 pos;
    s32 kind;
    f32 r;
    u32 alpha;
    u32 life;

    *(f32 *) (arg0 + 0x48) = *(f32 *) (arg0 + 0x48) * -fac;
    *(f32 *) (arg0 + 0x3C) = *(f32 *) (arg0 + 0x10) + ground;
    *(f32 *) (arg0 + 0x44) *= fac;
    *(f32 *) (arg0 + 0x4C) *= fac;
    *(f32 *) (arg0 + 0x50) *= fac;
    *(f32 *) (arg0 + 0x54) *= fac;
    *(f32 *) (arg0 + 0x58) *= fac;
    if (fabsf(*(f32 *) (arg0 + 0x48)) < 4.0f) {
        *(f32 *) (arg0 + 0x44) = 0.0f;
        *(s32 *) (arg0 + 0x60) &= ~0x69;
        *(f32 *) (arg0 + 0x48) = 0.0f;
        *(f32 *) (arg0 + 0x4C) = 0.0f;
        *(f32 *) (arg0 + 0x50) = 0.0f;
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    if (*(f32 *) (arg0 + 0x30) == 2.0f) {
        return 1;
    }
    pos.unk0 = *(f32 *) (arg0 + 0x38);
    pos.unk4 = ground;
    pos.unk8 = *(f32 *) (arg0 + 0x40);
    kind = (*(f32 *) (arg0 + 0x30) == 0.0f) ? 0 : 1;
    r = random_float();
    alpha = random_int();
    life = random_int();
    impact_debris_spawn(kind, (r * 27.6f + 19.7f) * ((*(f32 *) (arg0 + 0x18) + *(f32 *) (arg0 + 0x1C)) * 0.5f),
                  alpha % 101 + 100, (s32) bone, &pos, life % 144 + 80, 1, 1, 0, arg0[0xC], arg0[1]);
    return 1;
}

extern u8 g_hit_sparks_masks[4];        /* 4 bit masks (one picked at random): which of the 4 corner sparks / smoke puffs; was D_800A45A4 */
extern s32 g_hit_sparks_spark_ids[4];       /* spark sprite ids (0x61..0x64); was D_800A45A8 */
extern s32 g_hit_sparks_smoke_ids[4];       /* smoke sprite ids (0x5D..0x60); was D_800A45B8 */
extern f32 g_hit_sparks_smoke_pts[4][3];    /* smoke start points in model space; was D_800A45C8 */
s32 mdl_particle_spawn(Spark9768 *, s32, s32, s32, u8, s32);
s32 mdl_particle_spawn_ex(Spark9768 *, s32, s32, s32, s32, u8, s32);
void debris_sprite_spawn(s32, f32 *, f32, f32, s32, s32, f32, s32, s32, u8, s32);
void mtx_decompose(void *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void vec3_from_angles_byte(s16, s16, f32, f32 *);
s32 memcpy(u8 *, u8 *, s32);

// object_hit_sparks: hit effects on object `obj` (object_hit_effect, hit types 15 / 2 with scale 0.6 / 1.0). One of
// four bit masks (g_hit_sparks_masks) is picked at random. For each set bit, a mdl_particle_spawn spark (kind 3, sprite
// g_hit_sparks_spark_ids[i], size (xz_scale + y_scale) / 2 * scale) whose new particle gets the extra byte 12 at +0x170.
// If the object has a model (+0x1D4) and (+0x74 & 0xF) != 0xF: 5..8 debris_sprite_spawn debris pieces from `pos` (random
// direction, speed 6..12) and, for each clear bit, a mdl_particle_spawn_ex smoke puff from the model point
// g_hit_sparks_smoke_pts[i] (model matrix +0x300, mtx_transform_point_or_origin), sprite g_hit_sparks_smoke_ids[i], life 60..160. kind (u8) and owner go to
// every spawn, `arg3` to the debris and the puffs. The asm returns a leftover v0 that no caller reads.
/* was func_15139768 */
void object_hit_sparks(struct127 *obj, s32 *pos, f32 scale, s32 *arg3, u8 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    f32 dir[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 n;
    s32 a;
    s32 b;
    f32 f;
    f32 size;
    u8 *p;

    mask = &g_hit_sparks_masks[random_int() & 3];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f * scale;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.scl[0] = 1.0f;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_sparks_spark_ids[i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    for (n = (random_int() & 3) + 5; n > 0; n--) {
        a = random_int();
        b = random_int();
        f = random_float() * 6.0f + 6.0f;
        vec3_from_angles_byte(a & 0xFF, (u32) b % 71 - 60, f, dir);
        f = random_float();
        a = random_int();
        b = random_int();
        debris_sprite_spawn((s32) pos, dir, f * 0.117000006f + -0.19700001f, 0.950865f, (u32) a % 66 + 190,
                      (u32) b % 45 + 44, random_float() * 20.0f + 50.0f, 0, (s32) arg3, kind, owner);
    }

    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f * scale;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 1.0f;
    smoke.scl[2] = 1.0f;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_sparks_smoke_ids[i];
            mtx_transform_point_or_origin(g_hit_sparks_smoke_pts[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg3, 0, kind, owner);
        }
    }
}

extern u8 g_hit_small_masks[3];        /* 3 bit masks (one picked at random): which of the 3 sparks / smoke puffs; was D_800A45F8 */
extern s32 g_hit_small_spark_ids[3];       /* spark sprite ids; was D_800A45FC */
extern s32 g_hit_small_smoke_ids[3];       /* smoke sprite ids; was D_800A4608 */
extern f32 g_hit_small_smoke_pts[3][3];    /* smoke start points in model space; was D_800A4614 */

// object_hit_sparks_small: default hit effect of object_hit_effect (3-way variant of object_hit_sparks without the debris
// pieces). One of three bit masks (g_hit_small_masks) is picked at random. For each set bit, a mdl_particle_spawn spark (kind 3,
// sprite g_hit_small_spark_ids[i], size (xz_scale + y_scale) / 2, life 400) whose new particle gets the extra byte 12 at +0x170.
// If the object has a model (+0x1D4) and (+0x74 & 0xF) != 0xF: a impact_burst burst at `pos`, then for each clear
// bit a mdl_particle_spawn_ex smoke puff from the model point g_hit_small_smoke_pts[i] (model matrix +0x300, mtx_transform_point_or_origin), sprite
// g_hit_small_smoke_ids[i], life 60..160. The asm returns a leftover v0 that no caller reads (object_hit_effect is void).
/* was func_15139D74 */
void object_hit_sparks_small(struct127 *obj, s32 *pos, s32 *arg2, s32 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 a;
    s32 b;
    f32 size;
    u8 *p;

    kind &= 0xFF;
    mask = &g_hit_small_masks[(u32) random_int() % 3 & 0xFF];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.scl[0] = 1.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 400;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 3; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_small_spark_ids[i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    impact_burst((s32) pos, kind, owner);
    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 0.0f;
    smoke.scl[2] = 1.0f;
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 3; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_small_smoke_ids[i];
            mtx_transform_point_or_origin(g_hit_small_smoke_pts[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg2, 0, kind, owner);
        }
    }
}

/* emit_debris_burst debris burst spec (0x44 bytes) and the 0xC extra bytes copied to each piece (+0x170) */
typedef struct {
    /* 0x00 */ s32 countBase;
    /* 0x04 */ s32 countExtra;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ s16 u2C;
    /* 0x2E */ s16 u2E;
    /* 0x30 */ f32 sizeMin;
    /* 0x34 */ f32 sizeExtra;
    /* 0x38 */ f32 u38;
    /* 0x3C */ f32 solidChance;
    /* 0x40 */ u8  u40;
} DebrisSpec;
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ u16 model;
    /* 0x06 */ u8  u6;
    /* 0x08 */ s32 u8;
} DebrisExtra;
s32 emit_debris_burst(s32 *arg0, s32 *ids, s32 *scales, s32 n, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                  s32 arg9, f32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14);
void mdl_particle_broadcast(s32 arg0, u8 arg1);
extern u16 g_debris_model_ids[4]; /* was D_800A4638 */

// object_debris_burst: 40 debris pieces of the kinds ids[] / scales[] (n kinds) at pos, sized scale (debris spec
// for emit_debris_burst, 0x0D: other spin / speed values; 0x13 in level 0x3C: never solid). Kind 1 adds the extra
// bytes {4, model g_debris_model_ids[obj +0x128, at most 3], 6, 3} and mode 1. Then mdl_particle_broadcast(0, 0x45).
/* was func_1513A24C */
void object_debris_spawn(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds,
                   u8 arg9, s32 argA) {
    DebrisSpec spec;
    DebrisExtra extra;
    u16 models[4];
    s32 mode;
    s32 i;

    spec.countBase = 0x28;
    spec.countExtra = 0;
    spec.pos[0] = pos[0];
    spec.pos[1] = pos[1];
    spec.pos[2] = pos[2];
    spec.sizeMin = 1.0f * scale;
    spec.u14 = 0;
    spec.u16 = 0xFF;
    spec.u2C = 0x190;
    spec.u2E = 0xC8;
    spec.sizeExtra = (f32)0 * scale; /* computed: -0.0 for a negative scale (IDO folds "0.0f * scale") */
    extra.u0 = 4;
    mode = -1;
    spec.u18 = -0x40;
    spec.u1A = 0xC;
    spec.u20 = 5.0f;
    spec.solidChance = 1.0f;
    spec.u1C = 13.0f;
    spec.u24 = -1.0070001f;
    spec.u28 = 0.252f;
    spec.u38 = 16.102001f;
    spec.u40 = arg6;
    if (kind == 1) {
        models[0] = g_debris_model_ids[0];
        models[1] = g_debris_model_ids[1];
        models[2] = g_debris_model_ids[2];
        models[3] = g_debris_model_ids[3];
        mode = 1;
        i = obj[0x128];
        if (i >= 4) {
            i = 3;
        }
        extra.u6 = 6;
        extra.u8 = 3;
        extra.model = models[i];
    } else if (kind == 0xD) {
        spec.u18 = -0x2E;
        spec.u1A = 0x14;
        spec.u1C = 15.0f;
        spec.u20 = 8.0f;
        spec.u24 = -1.2620001f;
        spec.u28 = 0.49f;
        spec.u38 = 12.911f;
    } else if (kind == 0x13 && D_800BE9F0 == 0x3C) {
        spec.solidChance = 0.0f;
    }
    emit_debris_burst((s32 *)&spec, ids, scales, n, (s32)&extra, 0xC, 6, 1, mode, (s32)bounds, 5.0f, 1,
                  (D_800BE616 != 0) ? 1 : 0, arg9, argA);
    mdl_particle_broadcast(0, 0x45);
}

extern u8 g_impact_burst_tex_ids[]; /* was D_800A4648 */
extern u8 g_impact_burst_tex_scales[]; /* was D_800A4650 */

typedef struct {
    s32 u2C;
    s32 u30;
    struct17 pos;
    s16 u40;
    s16 u42;
    s16 u44;
    s16 u46;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
    s16 u58;
    s16 u5A;
    f32 u5C;
    f32 u60;
    f32 u64;
} Blk15152700;

/* was func_1513A48C */
void impact_burst_small(struct17 *arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 8;
    s.u30 = 4;
    s.pos = *arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x37;
    s.u46 = 0x20;
    s.u48 = 10.0f;
    s.u4C = 9.0f;
    s.u50 = -1.00400007f;
    s.u54 = 0.254f;
    s.u58 = 0x28;
    s.u5A = 0x14;
    s.u5C = 0.07f;
    s.u60 = 0.07f;
    s.u64 = 23.4460011f;
    emit_textured_burst(&s, g_impact_small_tex_ids, g_impact_small_tex_scales, 1, 0.0f, 1, arg1, arg2);
}

/* was func_1513A594 */
void object_hit_burst(u8 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    impact_burst(arg1, arg3, arg4);
    if (*(s32 *)(arg0 + 0x1D4) != 0) { if (arg0) {} }
}

/* was func_1513A5E0 */
void impact_burst(s32 arg0, u8 arg1, s32 arg2) {
    Blk15152700 s;

    s.u2C = 7;
    s.u30 = 7;
    s.pos = *(struct17 *)arg0;
    s.u40 = 0;
    s.u42 = 0xFF;
    s.u44 = -0x32;
    s.u46 = 0x1B;
    s.u48 = 4.0f;
    s.u4C = 4.0f;
    s.u50 = -0.43f;
    s.u54 = 0.272f;
    s.u58 = 0x19;
    s.u5A = 0x28;
    s.u5C = 0.0201f;
    s.u60 = 0.0201f;
    s.u64 = 20.187f;
    emit_textured_burst(&s, g_impact_burst_tex_ids, g_impact_burst_tex_scales, 2, 0.0f, 1, arg1, arg2);
}

extern u8 g_hit_four_masks[6];        /* 6 bit masks (one picked at random); was D_800A4658 */
extern s32 g_hit_four_spark_ids[4];       /* spark sprite ids; was D_800A4660 */
extern s32 g_hit_four_smoke_ids[4];       /* smoke sprite ids; was D_800A4670 */
extern f32 g_hit_four_smoke_pts[4][3];    /* smoke start points in model space; was D_800A4680 */

// object_hit_sparks_four: hit types 0 / 7 of object_hit_effect; as object_hit_sparks_small with four sparks / puffs, one of six
// masks (g_hit_four_masks) and spark life 100.
/* was func_1513A6E0 */
void object_hit_sparks_four(struct127 *obj, s32 *pos, s32 *arg2, s32 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 a;
    s32 b;
    f32 size;
    u8 *p;

    kind &= 0xFF;
    mask = &g_hit_four_masks[(u32) random_int() % 6 & 0xFF];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.scl[0] = 1.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_four_spark_ids[i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    impact_burst((s32) pos, kind, owner);
    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 0.0f;
    smoke.scl[2] = 1.0f;
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 4; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_four_smoke_ids[i];
            mtx_transform_point_or_origin(g_hit_four_smoke_pts[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg2, 0, kind, owner);
        }
    }
}

extern u8 g_hit_pair_masks[3];        /* 3 bit masks (one picked at random); was D_800A46B0 */
extern s32 g_hit_pair_spark_ids[2][2];    /* spark sprite ids per variant; was D_800A46B4 */
extern s32 g_hit_pair_smoke_ids[2][2];    /* smoke sprite ids per variant; was D_800A46C4 */
extern f32 g_hit_pair_smoke_pts[2][2][3]; /* smoke start points in model space per variant; was D_800A46D4 */

// object_hit_sparks_pair: hit types 8 / 9 of object_hit_effect (variant = type == 9); as object_hit_sparks_small with two sparks /
// puffs whose sprites and smoke points come from the variant's row, spark life 100. kind is a byte stack argument.
/* was func_1513ABB8 */
void object_hit_sparks_pair(struct127 *obj, s32 *pos, s32 variant, s32 *arg3, u8 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 a;
    s32 b;
    f32 size;
    u8 *p;

    variant &= 0xFF;
    mask = &g_hit_pair_masks[(u32) random_int() % 3 & 0xFF];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.scl[0] = 1.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 2; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_pair_spark_ids[variant][i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    impact_burst((s32) pos, kind, owner);
    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 0.0f;
    smoke.scl[2] = 1.0f;
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 2; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_pair_smoke_ids[variant][i];
            mtx_transform_point_or_origin(g_hit_pair_smoke_pts[variant][i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg3, 0, kind, owner);
        }
    }
}

/* was func_1513B0B8 */
void fx_count_msg_45(struct161520 *arg0, s32 arg1, u8 arg2) {
    s32 *temp_v0 = &arg0->unk170;

    if (arg2 == 0x45) {
        if (--*temp_v0 < 0) {
            arg0->unk60 |= 0x80;
        }
    }
}

extern u8 g_hit_burst_masks[3];        /* 3 bit masks (one picked at random); was D_800A4704 */
extern s32 g_hit_burst_spark_ids[2];       /* spark sprite ids; was D_800A4708 */
extern s32 g_hit_burst_smoke_ids[2];       /* smoke sprite ids; was D_800A4710 */
extern f32 g_hit_burst_smoke_pts[2][3];    /* smoke start points in model space; was D_800A4718 */

// object_hit_sparks_burst: hit type 16 of object_hit_effect; first a pos_debris_burst_spawn burst at `pos`, then as
// object_hit_sparks_small with two sparks / puffs (spark life 100, smoke y scale 2.0, no impact_burst burst).
/* was func_1513B0F8 */
void object_hit_sparks_burst(struct127 *obj, s32 *pos, s32 *arg2, s32 kind, s32 owner) {
    Spark9768 smoke;
    f32 rot[3];
    f32 scl[3];
    Spark9768 spark;
    u8 extra;
    f32 trans[3];
    u8 *mask;
    u8 bit;
    s32 i;
    s32 a;
    s32 b;
    f32 size;
    u8 *p;

    kind &= 0xFF;
    pos_debris_burst_spawn((s32) pos, kind, owner);
    mask = &g_hit_burst_masks[(u32) random_int() % 3 & 0xFF];
    extra = 12;
    spark.u00 = 1.0f;
    spark.u04 = 1.0f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    spark.pos[0] = 0.0f;
    spark.pos[1] = 0.0f;
    spark.pos[2] = 0.0f;
    spark.scl[0] = 1.0f;
    spark.u0C = size;
    spark.u08 = size;
    spark.scl[1] = 1.0f;
    spark.scl[2] = 1.0f;
    spark.at[0] = 0.0f;
    spark.at[1] = 0.0f;
    spark.at[2] = 0.0f;
    spark.vel[0] = 0.0f;
    spark.vel[1] = 0.0f;
    spark.vel[2] = 0.0f;
    spark.u40 = 0.0f;
    spark.u44 = 0.0f;
    spark.u48 = 0.0f;
    spark.u4C = 0.0f;
    spark.u50 = 0x101900;
    spark.life = 100;
    spark.u58 = 5;
    spark.u5C = 0;
    spark.u60[0] = 0xFF;
    spark.u60[1] = 0;
    spark.u60[2] = 0;
    spark.u60[3] = 0;
    spark.u60[4] = 0;
    spark.u60[5] = 0;
    spark.u60[6] = 0;
    spark.u60[7] = 0;
    spark.u68 = 5;
    spark.u6A = 1;
    spark.obj = obj;
    spark.u72 = 12;
    spark.u74 = 21;
    spark.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 2; i++, bit <<= 1) {
        if (*mask & bit) {
            spark.u56 = g_hit_burst_spark_ids[i];
            p = (u8 *) mdl_particle_spawn(&spark, 3, 0xFF, 1, kind, owner);
            if (p != NULL) {
                memcpy(p + 0x170, &extra, 1);
            }
        }
    }

    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    mtx_decompose((u8 *) obj->unk1D4 + 0x300, &scl[0], &scl[1], &scl[2], &trans[0], &trans[1], &trans[2], &rot[0],
                  &rot[1], &rot[2]);
    smoke.u00 = 1.0f;
    smoke.u04 = 0.64900005f;
    size = (obj->xz_scale + obj->y_scale) * 0.5f;
    smoke.u0C = size;
    smoke.u08 = size;
    smoke.pos[0] = trans[0];
    smoke.pos[1] = trans[1];
    smoke.pos[2] = trans[2];
    smoke.scl[0] = 1.0f;
    smoke.scl[1] = 2.0f;
    smoke.scl[2] = 1.0f;
    smoke.u44 = 0.0f;
    smoke.u58 = 0;
    smoke.u5C = 0;
    smoke.u60[0] = 0xFF;
    smoke.u60[2] = 0;
    smoke.u60[4] = 0;
    smoke.u60[5] = 0;
    smoke.u60[6] = 0;
    smoke.u60[7] = 0;
    smoke.u6A = 1;
    smoke.obj = obj;
    smoke.u72 = 12;
    smoke.u74 = 21;
    smoke.u50 = 0x1039E9;
    smoke.u60[1] = 13;
    smoke.u68 = 2;
    smoke.u60[3] = 9;
    smoke.uid = obj->unique_id;
    for (i = 0, bit = 1; i < 2; i++, bit <<= 1) {
        if (!(*mask & bit)) {
            smoke.u56 = g_hit_burst_smoke_ids[i];
            mtx_transform_point_or_origin(g_hit_burst_smoke_pts[i], smoke.at, (u8 *) obj->unk1D4 + 0x300);
            a = random_int();
            b = random_int();
            vec3_from_angles_byte(a & 0xFF, (u32) b % 35 - 84, random_float() * 6.12f + 3.0f, smoke.vel);
            smoke.u40 = random_float() * 30.746002f + -15.373001f;
            smoke.u48 = random_float() * 30.746002f + -15.373001f;
            smoke.u4C = random_float() * 0.208f + -0.708f;
            smoke.life = (u32) random_int() % 101 + 60;
            mdl_particle_spawn_ex(&smoke, 3, 0xFF, (s32) arg2, 0, kind, owner);
        }
    }
}
