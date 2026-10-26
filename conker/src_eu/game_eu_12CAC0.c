#include <ultra64.h>
#include "functions.h"
#include "variables.h"


u8 *obj_muzzle_node_get(s32 arg0);
void obj_muzzle_frame_get(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void beam_aim_compute(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 argA, s32 argB, u8 *argC, u8 *argD, s32 argE);
void beam_impact_sparks(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
s32 tracer_spawn(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32, f32, f32, s32, u8 *, s32, s32, s32, s32, s32, s32,
                  s32, s32, f32, s32, s32, s32, s32, s32);
void muzzle_light_small_spawn(u8 *arg0, u8 arg1, s32 arg2);
void bone_streak_fx_start(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void weapon_count_shot(u8 *arg0);

// object_bolt_fire: like object_beam_fire (object_beam_fire) but fires a lightning bolt: reads the muzzle frame of the
// object's muzzle node (obj_muzzle_node_get / weapon_count_shot / obj_muzzle_frame_get; nothing without a node), aims (beam_aim_compute,
// aim flag set when the object has a matrix block +0x1D4 and its +0x74 low nibble is not 0xF), spawns the bolt
// (tracer_spawn: length 300, 1/300, width 25..35, 600..800, 50, life 100..255, kind 0x35 when D_800BE616 else
// 0x1A, direction 1 for object type 0x98 else -1) and, when aimed, the muzzle flash, node glow and impact.
/* was func_150FF2B0 */
void object_bolt_fire(struct127 *obj, u8 arg1, s32 arg2) {
    u8 aimed;
    u8 *node;
    s32 surface;
    s32 target;
    s32 hit[18];
    f32 axisEC[3];
    f32 axisF8[3];
    f32 dir104[3];
    f32 pos110[3];
    f32 axis11C[3];
    f32 axis128[3];
    f32 pos134[3];
    f32 end140[3];
    f32 start14C[3];
    f32 r1, r2;
    s32 r3;
    s32 kind;
    s32 dir;

    node = obj_muzzle_node_get((s32) obj);
    if (node == NULL) {
        return;
    }
    weapon_count_shot((u8 *) obj);
    obj_muzzle_frame_get((s32) obj, (s32) pos134, (s32) axis128, (s32) axis11C);
    if (obj->unk1D4 != NULL && (((u8 *) obj)[0x74] & 0xF) != 0xF) {
        aimed = 1;
    } else {
        aimed = 0;
    }
    beam_aim_compute(&aimed, (s32) hit, (u8 *) start14C, (s32) pos110, (s32) dir104, (u8 *) pos134, (s32) axis128,
                  (s32) axis11C, (s32) axisF8, (s32) axisEC, (s32) &target, (s32) &surface, (u8 *) end140, (u8 *) obj,
                  (s32) node);
    r1 = random_float();
    r2 = random_float();
    r3 = random_int();
    kind = D_800BE616 ? 0x35 : 0x1A;
    dir = (((u8 *) obj)[4] == 0x98) ? 1 : -1;
    tracer_spawn(end140, pos134, target, surface, 1, 0, 300.0f, 0.0033333334f /* D_800A24E0 */, r1 * 10.0f + 25.0f,
                  r2 * 200.0f + 600.0f, 50.0f, (u32) r3 % 156 + 100, (u8 *) obj, 0x63, 1, 1, 1, 0, 1, 0, kind, 0.0f,
                  0xFF, dir, 0, arg1, arg2);
    if (aimed == 0) {
        return;
    }
    muzzle_light_small_spawn((u8 *) start14C, arg1, arg2);
    bone_streak_fx_start((u8 *) pos110, (u8 *) dir104, (s32) ((u8 *) obj->unk1D4 + node[2] * 64), (u8 *) obj, 1.0f, arg1,
                  arg2);
    beam_impact_sparks((u8 *) start14C, (s32) hit, arg1, arg2);
}

extern s32 g_beam_joint_name_a; /* was D_800A2420 */
/* was func_150FF550 */
void obj_joint_point_get(u8 *arg0, s16 arg1, u8 *arg2) {
    s32 *sp34;
    u8 *sp30;
    s32 temp_v0;
    if (arg1 == -1) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    temp_v0 = attachment_find_by_slot(arg0, arg1, 0);
    if (temp_v0 == 0) {
        *(f32 *)(arg2 + 0) = *(f32 *)(arg0 + 0x14);
        *(f32 *)(arg2 + 4) = *(f32 *)(arg0 + 0x18);
        *(f32 *)(arg2 + 8) = *(f32 *)(arg0 + 0x1C);
        return;
    }
    sp34 = &g_beam_joint_name_a;
    sp30 = arg2;
    model_node_points_to_world(arg0, temp_v0, 0, &sp34, &sp30, 1);
}

u8 *obj_muzzle_node_get(s32 arg0);
void obj_muzzle_frame_get(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void beam_aim_compute(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 argA, s32 argB, u8 *argC, u8 *argD, s32 argE);
void beam_impact_sparks(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
void beam_light_effect_spawn(f32 *, void *, void *, void *, u8, u8 *, f32, f32, f32, u8 *, u8, u8, u8, u8, s32, s8, s32, u8, u8,
                   s32);
void muzzle_light_small_spawn(u8 *arg0, u8 arg1, s32 arg2);
void bone_streak_fx_start(u8 *, u8 *, s32, u8 *, f32, u8, s32);
void weapon_count_shot(u8 *arg0);

// object_beam_fire: for an object with a muzzle node (obj_muzzle_node_get, model node 0x82; nothing without one): updates the
// node (weapon_count_shot), reads the muzzle frame (obj_muzzle_frame_get: position, two axes), aims the beam (beam_aim_compute fills
// the start / end points, the aim flag and the hit target / surface), spawns the beam effect (beam_light_effect_spawn: width 54,
// 1/54, length 300, id 0x327 + rand % 5, hit flag = surface found) and, when the object has a matrix block (+0x1D4),
// also the muzzle flash (muzzle_light_small_spawn), the node-attached glow (bone_streak_fx_start on the node's matrix) and the impact
// (beam_impact_sparks).
/* was func_150FF604 */
void object_beam_fire(struct127 *obj, u8 arg1, s32 arg2) {
    u8 aimed;
    u8 *node;
    s32 surface;
    s32 target;
    s32 hit[18];
    f32 axisC4[3];
    f32 axisD0[3];
    f32 dirDC[3];
    f32 posE8[3];
    f32 axisF4[3];
    f32 axis100[3];
    f32 pos10C[3];
    f32 end118[3];
    f32 start124[3];
    s32 has_surface;

    node = obj_muzzle_node_get((s32)obj);
    if (node == NULL) {
        return;
    }
    weapon_count_shot((u8 *)obj);
    obj_muzzle_frame_get((s32)obj, (s32)pos10C, (s32)axis100, (s32)axisF4);
    if (obj->unk1D4 != NULL) {
        aimed = 1;
    } else {
        aimed = 0;
    }
    beam_aim_compute((u8 *)&aimed, (s32)hit, (u8 *)start124, (s32)posE8, (s32)dirDC, (u8 *)pos10C, (s32)axis100,
                  (s32)axisF4, (s32)axisD0, (s32)axisC4, (s32)&target, (s32)&surface, (u8 *)end118, (u8 *)obj,
                  (s32)node);
    has_surface = 1;
    if (surface == 0) {
        has_surface = 0;
    }
    beam_light_effect_spawn(start124, pos10C, (void *)target, (void *)surface, has_surface, NULL, 54.000004f, 0.018518517f,
                  300.0f, (u8 *)obj, 1, 1, 1, 0, 0x1A, 1, (u32)random_int() % 5 + 0x327, 0, arg1, arg2);
    if (aimed == 0) {
        return;
    }
    muzzle_light_small_spawn((u8 *)start124, arg1, arg2);
    bone_streak_fx_start((u8 *)posE8, (u8 *)dirDC, (s32)((u8 *)obj->unk1D4 + node[2] * 64), (u8 *)obj, 1.0f, arg1, arg2);
    beam_impact_sparks((u8 *)start124, (s32)hit, arg1, arg2);
}

/* was func_150FF808 */
u8 *obj_muzzle_node_get(s32 arg0) {
    return attachment_find_by_slot(arg0, 0x82, 0);
}

/* was func_150FF82C */
void obj_muzzle_frame_get(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    obj_get_aim_vectors(arg0, arg1, arg2, arg3, 0.81100005f);
}

s32 model_points_find(f32 *, f32 *, f32 *, f32 *, f32 *, u8 *, s32); /* P209: C, returns 1 / 0 */
void weapon_find_aim_target(u8 *, u8 *, void *, void *, void *, u8 *, u8 *, u8 **, u8 **, u8 *);

/* was func_150FF854 */
void beam_aim_compute(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, u8 *argC, u8 *argD, s32 argE) {
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f16;
    f32 var_f18;
    u8 temp_v0;
    u8 var_v1;

    var_v1 = *arg0;
    if (var_v1 != 0) {
        temp_v0 = model_points_find((f32 *) arg1, (f32 *) arg2, (f32 *) arg3, (f32 *) arg4, (f32 *) argC, argD, argE);
        var_v1 = temp_v0 & 0xFF;
        *arg0 = temp_v0;
    }
    if (var_v1 == 0) {
        temp_f14 = (*(f32 *)((u8 *)arg5 + 0));
        if ((fabsf(temp_f14) > 0.0001f) || (fabsf((*(f32 *)((u8 *)arg5 + 8))) > 0.0001f)) {
            temp_f2 = (*(f32 *)((u8 *)arg5 + 8));
            temp_f12 = 1.0f / sqrtf((temp_f14 * temp_f14) + (temp_f2 * temp_f2));
            var_f16 = temp_f2 * temp_f12;
            var_f18 = -temp_f14 * temp_f12;
        } else {
            var_f16 = 1.0f;
            var_f18 = 0.0f;
        }
        (*(f32 *)((u8 *)arg2 + 0)) = (f32) ((*(f32 *)((u8 *)argD + 0x14)) + (34.0f * var_f18));
        (*(f32 *)((u8 *)arg2 + 4)) = (f32) ((*(f32 *)((u8 *)argD + 0x18)) + 49.0f);
        (*(f32 *)((u8 *)arg2 + 8)) = (f32) ((*(f32 *)((u8 *)argD + 0x1C)) + (34.0f * var_f16));
        (*(f32 *)((u8 *)argC + 0)) = (f32) (*(f32 *)((u8 *)arg2 + 0));
        (*(f32 *)((u8 *)argC + 4)) = (f32) (*(f32 *)((u8 *)arg2 + 4));
        (*(f32 *)((u8 *)argC + 8)) = (f32) (*(f32 *)((u8 *)arg2 + 8));
    }
    weapon_find_aim_target(argD, arg2, arg5, arg6, arg7, arg8, arg9, argA, argB, argC);
}
typedef struct { s32 x, y, z; } V3i;
/* was func_150FF9F4 */
void beam_impact_sparks(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {

    s32 var_s0;
    s32 var_v0;
    u8 *temp_t4;
    struct {
        s8 u84;
        s8 u85;
        s16 u86;
        s16 u88;
        u8 pad8A[0x2];
        s32 u8C;
        s32 u90;
        u8 u94;
        u8 u95;
        u8 u96;
        u8 u97;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        u8 uC9;
        s8 uCA;
        s8 uCB;
        s32 uCC;
        u8 uD0;
    } sp;

    sp.u84 = 0x5F;
    sp.u85 = 5;
    sp.u86 = 0x2203;
    sp.u8C = 0;
    sp.u90 = 0;
    sp.u94 = 0xFF;
    sp.u95 = 0xFF;
    sp.u96 = 0xFF;
    sp.u97 = 0xFF;
    *(V3i *) &sp.uA0 = *(V3i *) arg0;
    sp.uB8 = 0.0f;
    sp.uBC = 0.0f;
    sp.uC0 = 0.0f;
    sp.uC4 = 0x40CC0009;
    sp.uC9 = 0xFF;
    sp.uCA = 0;
    sp.uCB = 7;
    sp.uD0 = 0xFF;
    sp.uCC = 0;
    sp.u88 = (random_int() & 3) + 3;
    for (var_s0 = 0; var_s0 < 6; var_s0 = (var_s0 + 1) & 0xFF) {
        sp.u98 = (random_float() * 11.1f) + 5.0f;
        temp_t4 = (0, arg1) + (var_s0 * 0xC); // fakematch: comma puts arg1 first in addu
        sp.u9C = (random_float() * 0.9990001f) + 2.483f;
        *(V3i *) &sp.uAC = *(V3i *) temp_t4;
        sp.uC8 = (random_int() % 156U) + 0x64;
        if (random_int() & 1) {
            var_v0 = 2;
        } else {
            var_v0 = 0;
        }
        effect3d_spawn_full(&sp.u84, (s32) &D_800A4AA0, 0U, 0U, 0U, 0x1BU, (u8) (var_v0 + 1), 0, 0, 0, arg2, arg3);
    }
}

/* was func_150FFC34 */
s32 beam_target_filter(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x98) {
        return 0;
    }
    return 1;
}

extern char g_beam_joint_name_b[]; /* joint names, 12 bytes each (g_beam_joint_name_a is declared s32 above); was D_800A2420; was D_800A242C */
extern char g_beam_joint_name_ref[]; /* was D_800A2438 */
extern char g_beam_joint_name_out[]; /* was D_800A2444 */
extern char g_beam_joint_name_sets[2][6][12]; /* two sets of 6 point joint names; was D_800A2450 */
/* model_node_points_to_world (model, s32, 0, names, outs, n): implicitly declared by the matched object_beam_fire above */
s32 random_int(void);

// model_points_find: looks up 10 joints of `model` by name in one model_node_points_to_world call: g_beam_joint_name_a -> a,
// g_beam_joint_name_ref -> ref, g_beam_joint_name_out -> out, g_beam_joint_name_b -> b, and one of the two g_beam_joint_name_sets sets (random) -> the 6
// vectors of `points`. On success `out` is made relative to `ref` and the result is 1, else 0.
/* was func_150FFC60 */
s32 model_points_find(f32 *points, f32 *a, f32 *ref, f32 *out, f32 *b, u8 *model, s32 arg6) {
    struct {
        void *outs[10];   /* sp+0x34 */
        char *names[10];  /* sp+0x5C */
    } q;
    s32 set;
    s32 i;

    set = random_int() & 1;
    q.names[0] = (char *) &g_beam_joint_name_a;
    q.names[1] = g_beam_joint_name_ref;
    q.names[2] = g_beam_joint_name_out;
    q.names[3] = g_beam_joint_name_b;
    for (i = 0; i < 6; i++) {
        q.names[4 + i] = g_beam_joint_name_sets[set][i];
        q.outs[4 + i] = points + i * 3;
    }
    q.outs[0] = a;
    q.outs[1] = ref;
    q.outs[2] = out;
    q.outs[3] = b;
    if (model_node_points_to_world(model, arg6, 0, q.names, q.outs, 10) != 0) {
        out[0] -= ref[0];
        out[1] -= ref[1];
        out[2] -= ref[2];
        return 1;
    }
    return 0;
}
