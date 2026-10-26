#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mtxf_look_at_f(f32 mf[4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
// line_of_sight_hit_object: looks from (x0, y0, z0) towards (x1, y1, z1) and finds the live object (g_objects,
// except index `skip`, dead or immune ones and `self`'s own slot unk124 - 1) that math_mtx_box_in_frustum rates lowest
// (non-zero) in that view within the eye-target distance; spawns effect `kind` (attack_spawn_at_point) at that object,
// copies self's heading unk76 to it and returns attack_spawn_at_point's result (0 when nothing was hit).
/* was func_150E1AF0 */
s32 object_ray_hit_nearest(struct127 *self, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, s32 skip, s32 kind) {
    f32 view[4][4];
    struct127 *obj;
    s32 ret = 0;
    s32 best = -1;
    s32 bestScore = 0;
    s32 own;
    s32 score;
    s32 i;
    f32 dx, dy, dz, dist;

    mtxf_look_at_f(view, x0, y0, z0, x1, y1, z1, 0.0f, 1.0f, 0.0f);
    dx = x0 - x1;
    dy = y0 - y1;
    dz = z0 - z1;
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    own = -1;
    if (self != NULL) {
        own = self->unk124 - 1;
    }
    for (i = 0, obj = g_objects; i < 25; i++, obj++) {
        if (obj->interaction_state == 0 || i == skip || obj->health == 0 || obj->immune != 0 || i == own) {
            continue;
        }
        score = math_mtx_box_in_frustum(view, obj->x_position, obj->y_position + (f32)obj->unkD6, obj->z_position,
                              (f32)obj->unkD2, (f32)obj->unkD4, 0.0f, dist, 10.0f, 10.0f);
        if (score == 0) {
            continue;
        }
        if (best == -1 || score < bestScore) {
            best = i;
            bestScore = score;
        }
    }
    if (best != -1) {
        obj = &g_objects[best];
        ret = attack_spawn_at_point(obj->x_position, obj->y_position + (f32)obj->unkD6, obj->z_position, kind, g_cur_obj_index, 0,
                            0, 0);
        obj->unk76 = self->unk76;
    }
    return ret;
}
