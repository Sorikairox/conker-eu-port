void mtx_transform_points(f32 **, f32 **, void *, s32);
s32 vec3_normalize_len(f32 *, f32 *, f32 *, f32 *);
s32 ray_cast_world(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
typedef struct {
    struct127 *obj; /* first object hit */
    f32 t;          /* hit distance along the ray (fraction of dir) */
    f32 x, y, z;    /* hit point */
    u8 pad14[0x45];
    u8 hit;         /* +0x59: what was hit (0 = nothing, 1 = world, >= 2 = an object) */
    u8 pad5A[2];
} Ray_60E30;
/* data at +0x18 (light_create_obj_beam): object, its unique id, attach point, offset (+8), ray end (+0x14), scale (+0x20),
 * flags (+0x24: 1 = cast, 2 = poke kind 0x9E). */

/* light_beam_update: P237. g_light_effect_update_fns handler for the beam lights of light_create_obj_beam. Ends the light (0) when its
 * object is gone or was reused (unique id). Without attach matrices (+0x1D4), without flag 1, or for a hidden
 * object (+0x74 & 0xF == 0xF), the light sits at the object position (light +0xE / +0x10 / +0x12) with brightness
 * +0x2F = 0 and +9 = 1. Else the offset and end points go through attach matrix `point` (mtx_transform_points), and when
 * the direction between them is not degenerate (vec3_normalize_len) a ray is cast from the start along it
 * (ray_cast_world): no hit = as above; a hit moves the light to the hit point with brightness
 * clamp(scale * t, 0, 255) and +9 = 0, and with flag 2 a hit object of kind 0x9E gets +0x2E4 = 1. Returns 1. */
s32 light_beh_beam_raycast(struct225 *arg0) {
    u8 *obj = *(u8 **) ((u8 *) arg0 + 0x18);
    u8 *s = (u8 *) arg0 + 0x18;
    f32 *src[2];
    f32 *dst[2];
    f32 start[3];
    f32 dir[3];
    f32 tmp0, tmp1;
    Ray_60E30 ray;
    f32 f;

    if (*(s32 *) obj == 0) {
        return 0;
    }
    if (s[4] != obj[0x3B]) {
        return 0;
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (s[0x24] & 1) && (obj[0x74] & 0xF) != 0xF) {
        src[0] = (f32 *) (s + 8);
        src[1] = (f32 *) (s + 0x14);
        dst[0] = start;
        dst[1] = dir;
        mtx_transform_points(src, dst, *(u8 **) (obj + 0x1D4) + (s[5] << 6), 2);
        dir[0] = dir[0] - start[0];
        dir[1] = dir[1] - start[1];
        dir[2] = dir[2] - start[2];
        if (vec3_normalize_len(dir, dir, &tmp0, &tmp1) != 0) {
            ray_cast_world((struct127 *) obj, start[0], start[1], start[2], dir[0], dir[1], dir[2], (u8 *) &ray, 0.0f,
                          0, 0, 1, -1, 0, 0);
            if (ray.hit != 0) {
                if ((s[0x24] & 2) && ray.hit >= 2 && ((u8 *) ray.obj)[4] == 0x9E) {
                    *(s32 *) ((u8 *) ray.obj + 0x2E4) = 1;
                }
                arg0->unk14->unkE = ray.x;
                arg0->unk14->unk10 = ray.y;
                arg0->unk14->unk12 = ray.z;
                f = *(f32 *) (s + 0x20) * ray.t;
                if (255.0f < f) {
                    f = 255.0f;
                }
                if (f < 0.0f) {
                    f = 0.0f;
                }
                arg0->unk14->unk2F = (u32) f;
                arg0->unk14->unk9 = 0;
                return 1;
            }
        }
    }
    arg0->unk14->unkE = *(f32 *) (obj + 0x14);
    arg0->unk14->unk10 = *(f32 *) (obj + 0x18);
    arg0->unk14->unk12 = *(f32 *) (obj + 0x1C);
    arg0->unk14->unk2F = 0;
    arg0->unk14->unk9 = 1;
    return 1;
}
