/* Script command: spawn a projectile / effect object from the current object D_800D154C through
 * func_15073118 (owner, type, model, then offsets and speeds; 100 = lifetime). D_800D1580 picks the kind:
 *   0: type 0x17 model 0x1F, flagged 0x1000000 in unkF8. When the owner's camera (unk318) is within 30
 *      of the owner (func_15037988) and a 1-in-5 roll passes, it is aimed at the camera: unk2E4 = 1, no
 *      gravity, heading unk76 / unk7A from func_150484A0 (degrees -> 0x10000 units, -0x4000), vertical
 *      speed = xz speed * dy / horizontal distance. Otherwise unk2E4 = 0.
 *   1: type 0xE model 0x42, offsets jittered by +-20 * owner->unk2E4 / 100.
 *   2: type 9 model 0x35, flagged 0x1000000, unkB8 = 180.
 *   3: type 0xE model 0x88, offsets jittered by +-200.
 * Jitter = (rand % 40 - 20) * scale (func_150ADA20, unsigned modulo). */
s32 func_15037988(s32 index, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, void *out, f32 radius, s32 arg8, s32 arg9);
struct127 *func_15073118(struct127 *owner, s32 type, s32 model, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                         f32 arg8, f32 arg9, s32 life);
#define JITTER(scale) ((f32)((s32)((u32)func_150ADA20() % 40) - 20) * (scale))

void func_1507342C(void) {
    struct127 *obj;
    struct127 *shot;
    u8 *cam;
    s32 aim;
    u8 hitInfo[0x20];   /* sp68, filled by func_15037988 */
    f32 dx, dy, dz;
    f32 angle;
    f32 heading;
    f32 dist;
    f32 scale;
    f32 y, x;
    s16 dir;

    if (D_800D1580 == 0) {
        obj = D_800D154C;
        aim = FALSE;
        cam = (u8 *)obj->camera;
        if (func_15037988(obj - D_800CC2D0, 0x17, 0x17, *(f32 *)(cam + 0x2F8), *(f32 *)(cam + 0x2FC),
                          *(f32 *)(cam + 0x300), hitInfo, 30.0f, 0, 0) != 0) {
            if ((u32)func_150ADA20() % 1000 < 200) {
                aim = TRUE;
            }
        }
        shot = func_15073118(D_800D154C, 0x17, 0x1F, 0.0f, 0.0f, 16.0f, 0.0f, 42.8f, 49.9f, 2.9f, 100);
        shot->unkF8 |= 0x1000000;
        if (!aim) {
            shot->unk2E4 = 0;
            return;
        }
        dx = *(f32 *)(cam + 0x2F8) - shot->x_position;
        dy = *(f32 *)(cam + 0x2FC) - shot->y_position;
        dz = *(f32 *)(cam + 0x300) - shot->z_position;
        angle = func_150484A0(dx, dz) * 57.295776f;
        heading = angle;
        if (180.0f < angle) {
            heading = angle - 360.0f;
        }
        dist = sqrtf(dx * dx + dz * dz);
        shot->gravity = 0.0f;
        shot->unk2E4 = 1;
        shot->y_velocity = shot->xz_velocity * dy / dist;
        dir = (s32)(heading * 182.04445f) - 0x4000;
        shot->unk7A = dir;
        shot->unk76 = dir;
    } else if (D_800D1580 == 1) {
        scale = (f32)D_800D154C->unk2E4 * 0.01f;
        y = 58.4f + JITTER(scale);
        x = 42.8f + JITTER(scale);
        func_15073118(D_800D154C, 0xE, 0x42, 0.0f, 0.0f, 16.0f, JITTER(scale), x, y, 2.9f, 100);
    } else if (D_800D1580 == 2) {
        shot = func_15073118(D_800D154C, 9, 0x35, 0.0f, 27.3f, 0.0f, 180.0f, 23.4f, 45.2f, 3.5f, 100);
        shot->unkF8 |= 0x1000000;
        shot->unkB8 = 180.0f;
    } else if (D_800D1580 == 3) {
        y = 58.4f + JITTER(10.0f);
        x = 42.8f + JITTER(10.0f);
        func_15073118(D_800D154C, 0xE, 0x88, 0.0f, 0.0f, 16.0f, JITTER(10.0f), x, y, 2.9f, 100);
    }
}
