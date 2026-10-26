#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 g_vec3_zero[]; /* was D_800A5860 */


s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
extern f32 D_800A0CC0[6][3];  /* beam end points (beam space) */

// beam_rays_update: obj + 0x28 is the source point, +0x34 the beam position (moved by its velocity +0x40 x
// g_frame_step_f), +0x4C six ray parts. While obj + 0x6C bit 0 is set, each ray's end D_800A0CC0[i] is moved to the
// beam's position (mtxf_rotate_xyz_deg / mtxf_transform_point) and traced from the source (collision_ray_cast): on a hit the part's
// sprite (+0x14) is shown at the hit point with alpha +0x64 x hit fraction, otherwise it is hidden. Without the bit
// every ray sprite is hidden.
/* was func_150D2140 */
void beam_rays_update(u8 *obj) {
    f32 mtx[4][4];
    f32 end[3];
    f32 hit[3];
    f32 frac;
    u8 *part;
    u8 *sprite;
    s32 i;

    if (obj[0x6C] & 1) {
        *(f32 *) (obj + 0x34) += *(f32 *) (obj + 0x40) * g_frame_step_f;
        *(f32 *) (obj + 0x38) += *(f32 *) (obj + 0x44) * g_frame_step_f;
        *(f32 *) (obj + 0x3C) += *(f32 *) (obj + 0x48) * g_frame_step_f;
        mtxf_rotate_xyz_deg(mtx, *(f32 *) (obj + 0x34), *(f32 *) (obj + 0x38), *(f32 *) (obj + 0x3C));
        for (i = 0; i < 6; i++) {
            part = ((u8 **) (obj + 0x4C))[i];
            if (part == NULL) {
                continue;
            }
            mtxf_transform_point(mtx, D_800A0CC0[i][0], D_800A0CC0[i][1], D_800A0CC0[i][2], &end[0], &end[1], &end[2]);
            if (collision_ray_cast(*(f32 *) (obj + 0x28), *(f32 *) (obj + 0x2C), *(f32 *) (obj + 0x30), end[0], end[1],
                              end[2], 0, NULL, &hit[0], &hit[1], &hit[2], &frac, 0, 0, 0.0f) != 0) {
                (*(u8 **) (part + 0x14))[9] = 0;
                *(s16 *) (*(u8 **) (part + 0x14) + 0xE) = (s32) hit[0];
                *(s16 *) (*(u8 **) (part + 0x14) + 0x10) = (s32) hit[1];
                *(s16 *) (*(u8 **) (part + 0x14) + 0x12) = (s32) hit[2];
                (*(u8 **) (part + 0x14))[0x2F] = (u32) (*(f32 *) (obj + 0x64) * frac);
            } else {
                (*(u8 **) (part + 0x14))[9] = 1;
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            part = ((u8 **) (obj + 0x4C))[i];
            if (part != NULL) {
                sprite = *(u8 **) (part + 0x14);
                sprite[9] = 1;
            }
        }
    }
}

/* was func_150D247C */
void beam_rays_handle_event(struct102 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_t6;
    u8 *temp_t4;
    u8 *temp_v0_2;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x32) {
        temp_v0 = arg0 + 0x28;
        (*(s32 *)((u8 *)temp_v0 + 0x18)) = (s32) (*(s32 *)((u8 *)arg1 + 0));
        (*(s32 *)((u8 *)temp_v0 + 0x1C)) = (s32) (*(s32 *)((u8 *)arg1 + 4));
        (*(s32 *)((u8 *)temp_v0 + 0x20)) = (s32) (*(s32 *)((u8 *)arg1 + 8));
        (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) (*(f32 *)((u8 *)arg1 + 0xC));
        return;
    }
    if ((temp_t6 == 0x30) || (temp_t6 == 0x31)) {
        temp_v0_2 = &arg0->unk28;
        if ((s32)arg1 == (s32)((*(s32 *)((u8 *)(s32)temp_v0_2 + 0x40)))) {
            if (temp_t6 == 0x30) {
                (*(u8 *)((u8 *)temp_v0_2 + 0x44)) = (u8) ((*(u8 *)((u8 *)temp_v0_2 + 0x44)) | 1);
                return;
            }
            (*(u8 *)((u8 *)temp_v0_2 + 0x44)) = (u8) ((*(u8 *)((u8 *)temp_v0_2 + 0x44)) & 0xFFFE);
        }
    } else {
        temp_t4 = ((u8 *)&g_vec3_zero);
        if (temp_t6 == 0x4E) {
            (*(s32 *)((u8 *)arg0 + 0x40)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
            (*(s32 *)((u8 *)arg0 + 0x44)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
            (*(s32 *)((u8 *)arg0 + 0x48)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
            return;
        }
        if (temp_t6 == 0x4F) {
            node_destroy(arg0);
        }
    }
}
/* was func_150D2564 */
void beam_rays_free_parts(u8 *arg0) {
    u8 *base = arg0 + 0x28;
    u8 i;

    for (i = 0; i < 6; i++) {
        struct102 *p = ((struct102 **)(base + 0x24))[i];

        if (p != NULL) {
            node_destroy(p);
        }
    }
}

/* was func_150D25C0 */
void beam_rays_delete(struct260 *arg0) {
    beam_rays_free_parts(arg0);
    effect_node_free(arg0);
}

/* was func_150D25EC */
void beam_rays_retire(struct260 *arg0) {
    beam_rays_free_parts(arg0);
    effect_node_retire(arg0);
}
