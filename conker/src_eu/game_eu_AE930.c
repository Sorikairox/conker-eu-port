#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P179 */
extern u8 *D_80087000[];
extern u8 D_8009CF9C[];

// object_reach_hit: P179: whether attacker `arg0`'s reach point hits `target`'s hit spheres; the sphere's bone + 1
/* or 0. The point is `reach` (x attacker scale +0x14C) ahead of the attacker, turned by its angles +0xB8 and +0x40
 * (degrees), from its position +0x14. A bounding sphere around the target (radius D_800D1C90[target +4] +0xE x
 * target +0x14C, centre raised by +0x10 x +0x150) is tested first; then the target's sphere list for model kind
 * `kind` (D_80087000[kind], D_8009CF9C[kind] entries of 10 bytes, same layout as obj_ray_hit_model: +0 bone, +2 radius,
 * +4 centre in bone space, bone matrices at +0x1D4) with each radius x +0x14C plus `grow` (x attacker scale). The
 * first sphere containing the point wins; unless the target's +0x125 is set the hit is reported to it with
 * attack_spawn_at_point(target position, `arg5`, the attacker's index in D_800CC2D0, 0, 0, 0). */
/* was func_15081120 */
s32 obj_reach_hit(s32 arg0, u8 *target, s32 kind, f32 reach, f32 grow, s32 arg5) {
    u8 *att = (u8 *) arg0;
    u8 *type;
    u8 *rec;
    u8 *bones;
    f32 v[3];
    f32 local[3];
    f32 world[3];
    f32 scale;
    f32 angle;
    f32 s;
    f32 c;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    s32 count;
    s32 i;

    scale = *(f32 *)(att + 0x14C);
    reach *= scale;
    grow *= scale;
    angle = *(f32 *)(att + 0xB8) * 0.017453292f;
    s = sinf(angle);
    c = cosf(angle);
    v[0] = 0.0f;
    v[1] = -reach * s;
    v[2] = reach * c;
    angle = *(f32 *)(att + 0x40) * 0.017453292f;
    s = sinf(angle);
    c = cosf(angle);
    x = v[2] * s + v[0] * c;
    v[2] = v[2] * c + -v[0] * s;
    v[0] = x;
    v[0] += *(f32 *)(att + 0x14);
    v[1] += *(f32 *)(att + 0x18);
    v[2] += *(f32 *)(att + 0x1C);

    type = (u8 *) D_800D1C90[target[4]];
    radius = (f32) (u32) *(u16 *)(type + 0xE) * *(f32 *)(target + 0x14C);
    height = *(s16 *)(type + 0x10) * *(f32 *)(target + 0x150);
    dx = v[0] - *(f32 *)(target + 0x14);
    dy = v[1] - (*(f32 *)(target + 0x18) + height);
    dz = v[2] - *(f32 *)(target + 0x1C);
    if (radius * radius < dx * dx + dy * dy + dz * dz) {
        return 0;
    }
    count = D_8009CF9C[kind];
    rec = D_80087000[kind];
    bones = *(u8 **)(target + 0x1D4);
    for (i = 0; i < count; i++, rec += 10) {
        local[0] = *(s16 *)(rec + 4);
        local[1] = *(s16 *)(rec + 6);
        local[2] = *(s16 *)(rec + 8);
        mtx_transform_point_or_origin(local, world, bones + rec[0] * 64);
        dx = v[0] - world[0];
        dy = v[1] - world[1];
        dz = v[2] - world[2];
        radius = (f32) (u32) *(u16 *)(rec + 2) * *(f32 *)(target + 0x14C) + grow;
        if (!(radius * radius < dx * dx + dy * dy + dz * dz)) {
            if (target[0x125] == 0) {
                attack_spawn_at_point(*(f32 *)(target + 0x14), *(f32 *)(target + 0x18), *(f32 *)(target + 0x1C), arg5,
                              (struct127 *) att - D_800CC2D0, 0, 0, 0);
            }
            return rec[0] + 1;
        }
    }
    return 0;
}

extern u16 D_8009C100;
extern u16 D_8009C104;
extern u16 D_8009C108;
extern u16 D_8009C10C[][2];
/* was func_1508148C */
s32 obj_hit_model_kind(u8 *arg0) {
    unsigned long i;
    s32 id;
    if ((id = arg0[4]) == D_8009C100) {
        return 0;
    }
    if (id == D_8009C104) {
        return 1;
    }
    if (id == D_8009C108) {
        return 2;
    }
    for (i = 3; i < 0x17; i++) {
        if (id == D_8009C10C[i - 3][0]) {
            return i;
        }
    }
    return -1;
}

/* P150 */
extern u8 *D_80087000[];
extern u8 D_8009CF9C[];
// object_ray_hit_model: intersects the ray start + t * dir with an object's hit spheres. The object's model kind
// (obj_hit_model_kind, -1 = none) selects a sphere list D_80087000[k] of D_8009CF9C[k] entries of 10 bytes: +0 bone,
// +1 priority, +2 radius (u16, times the object scale +0x14C), +4 / +6 / +8 centre (s16, bone space; the bone
// matrices are at +0x1D4, 64 bytes each). A bounding sphere around the object (height and radius from its
// D_800D1C90 type, times +0x150) is tested first. Spheres whose bone bit is set in +0x9C are skipped; the nearest
// hit wins, but a later sphere of lower priority than the current best never replaces it. Returns -1 when the
// object has no bones or no sphere list, 0 on a miss, 1 on a hit: point / exitPoint = entry / exit point, normal
// (optional) = the sphere centre, *dist = the last tested sphere's entry distance (as the original), *index /
// *bone / *priority = the sphere, centre[3] = its bone-space centre.
/* was func_1508154C */
s32 obj_ray_hit_model(u8 *obj, f32 *start, f32 *dir, f32 *point, f32 *exitPoint, f32 *normal, f32 *dist, s32 *index,
                  s32 *bone, s32 *priority, s16 *centre) {
    f32 local[3];
    f32 hitOut[3];
    f32 hitIn[3];
    f32 sphere[3];
    f32 bestIn[3];
    f32 bestOut[3];
    f32 bestSphere[3];
    f32 tIn;
    f32 tOut;
    s32 bestIndex;
    s32 bestPriority;
    s32 kind;
    s32 count;
    s32 i;
    u8 *list;
    u8 *e;
    u8 *type;

    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return -1;
    }
    kind = obj_hit_model_kind(obj);
    if (kind == -1) {
        return -1;
    }
    kind = ((u8 *)&D_8009C100)[kind * 4 + 2];
    list = D_80087000[kind];
    count = D_8009CF9C[kind];
    *dist = -1.0f;

    type = (u8 *)D_800D1C90[obj[4]];
    sphere[0] = *(f32 *)(obj + 0x14);
    sphere[1] = *(s16 *)(type + 0x10) * *(f32 *)(obj + 0x150) + *(f32 *)(obj + 0x18);
    sphere[2] = *(f32 *)(obj + 0x1C);
    type = (u8 *)D_800D1C90[obj[4]];
    if (ray_sphere_intersect((struct17 *)start, (struct17 *)dir, (struct17 *)sphere,
                      *(u16 *)(type + 0xE) * *(f32 *)(obj + 0x150), (s32)hitIn, (s32)hitOut, &tIn, &tOut) == 0) {
        return 0;
    }

    bestPriority = -1;
    for (i = 0, e = list; i < count; i++, e += 10) {
        if ((1 << e[0]) & *(s32 *)(obj + 0x9C)) {
            continue;
        }
        local[0] = *(s16 *)(e + 4);
        local[1] = *(s16 *)(e + 6);
        local[2] = *(s16 *)(e + 8);
        mtx_transform_point_or_origin(local, sphere, *(u8 **)(obj + 0x1D4) + e[0] * 64);
        if (ray_sphere_intersect((struct17 *)start, (struct17 *)dir, (struct17 *)sphere,
                          *(u16 *)(e + 2) * *(f32 *)(obj + 0x14C), (s32)hitIn, (s32)hitOut, &tIn, &tOut) == 0) {
            continue;
        }
        if (*dist != -1.0f) {
            if (!(tIn < *dist) || e[1] < bestPriority) {
                continue;
            }
        }
        *dist = tIn;
        bestIn[0] = hitIn[0];
        bestIn[1] = hitIn[1];
        bestIn[2] = hitIn[2];
        bestOut[0] = hitOut[0];
        bestOut[1] = hitOut[1];
        bestOut[2] = hitOut[2];
        bestSphere[0] = sphere[0];
        bestSphere[1] = sphere[1];
        bestSphere[2] = sphere[2];
        bestIndex = i;
        bestPriority = e[1];
    }

    if (*dist == -1.0f) {
        return 0;
    }
    *dist = tIn;
    *index = bestIndex;
    e = list + bestIndex * 10;
    *priority = e[1];
    *bone = e[0];
    centre[0] = *(s16 *)(e + 4);
    centre[1] = *(s16 *)(e + 6);
    centre[2] = *(s16 *)(e + 8);
    point[0] = bestIn[0];
    point[1] = bestIn[1];
    point[2] = bestIn[2];
    exitPoint[0] = bestOut[0];
    exitPoint[1] = bestOut[1];
    exitPoint[2] = bestOut[2];
    if (normal != NULL) {
        normal[0] = bestSphere[0];
        normal[1] = bestSphere[1];
        normal[2] = bestSphere[2];
    }
    return 1;
}

s32 obj_reach_hit(s32, u8 *, s32, f32, f32, s32);

/* was func_15081974 */
s32 obj_find_reach_hit(s32 arg0, f32 arg1, f32 arg2, u8 **arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 temp_v0_2;
    struct127 *var_s0;

    *arg3 = NULL;
    var_s0 = D_800CC2D0;
loop_1:
    if ((var_s0->interaction_state != 0) && (var_s0->unk1D4 != NULL) && (arg5 == var_s0->id)) {
        temp_v0_2 = obj_hit_model_kind((u8 *) var_s0);
        if (temp_v0_2 != -1) {
            temp_v0 = obj_reach_hit(arg0, (u8 *) var_s0, (*(u8 *)((u8 *)((((u8 *)&D_8009C100) + (temp_v0_2 * 4))) + 2)), arg1, arg2, arg4);
            if (temp_v0 != 0) {
                *arg3 = var_s0;
                return temp_v0;
            }
        }
    }
    var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    if ((s32)var_s0 == (s32)&D_800D121C) {
        return 0;
    }
    goto loop_1;
}