#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_15081120.s")

extern u16 D_8009C100;
extern u16 D_8009C104;
extern u16 D_8009C108;
extern u16 D_8009C10C[][2];
s32 func_1508148C(u8 *arg0) {
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

#ifdef NON_MATCHING
/* P150 */
extern u8 *D_80087000[];
extern u8 D_8009CF9C[];
// object_ray_hit_model: intersects the ray start + t * dir with an object's hit spheres. The object's model kind
// (func_1508148C, -1 = none) selects a sphere list D_80087000[k] of D_8009CF9C[k] entries of 10 bytes: +0 bone,
// +1 priority, +2 radius (u16, times the object scale +0x14C), +4 / +6 / +8 centre (s16, bone space; the bone
// matrices are at +0x1D4, 64 bytes each). A bounding sphere around the object (height and radius from its
// D_800D1C90 type, times +0x150) is tested first. Spheres whose bone bit is set in +0x9C are skipped; the nearest
// hit wins, but a later sphere of lower priority than the current best never replaces it. Returns -1 when the
// object has no bones or no sphere list, 0 on a miss, 1 on a hit: point / exitPoint = entry / exit point, normal
// (optional) = the sphere centre, *dist = the last tested sphere's entry distance (as the original), *index /
// *bone / *priority = the sphere, centre[3] = its bone-space centre.
s32 func_1508154C(u8 *obj, f32 *start, f32 *dir, f32 *point, f32 *exitPoint, f32 *normal, f32 *dist, s32 *index,
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
    kind = func_1508148C(obj);
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
    if (func_151452C4((struct17 *)start, (struct17 *)dir, (struct17 *)sphere,
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
        func_15143134(local, sphere, *(u8 **)(obj + 0x1D4) + e[0] * 64);
        if (func_151452C4((struct17 *)start, (struct17 *)dir, (struct17 *)sphere,
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_1508154C.s")
#endif

#ifdef NON_MATCHING
s32 func_15081120(s32, u8 *, u8, f32, f32, s32);

s32 func_15081974(s32 arg0, f32 arg1, f32 arg2, u8 **arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 temp_v0_2;
    struct127 *var_s0;

    *arg3 = NULL;
    var_s0 = D_800CC2D0;
loop_1:
    if ((var_s0->interaction_state != 0) && (var_s0->unk1D4 != NULL) && (arg5 == var_s0->id)) {
        temp_v0_2 = func_1508148C((u8 *) var_s0);
        if (temp_v0_2 != -1) {
            temp_v0 = func_15081120(arg0, (u8 *) var_s0, (*(u8 *)((u8 *)((((u8 *)&D_8009C100) + (temp_v0_2 * 4))) + 2)), arg1, arg2, arg4);
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AE930/func_15081974.s")
#endif