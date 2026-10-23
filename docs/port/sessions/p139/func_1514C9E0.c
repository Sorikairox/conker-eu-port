extern s32 D_8008ADA0;

/*
 * spawn_line_emit: emits count (a float, at least 2) evenly spaced points on the segment from (x0, y0, z0) to
 * (x1, y1, z1), step = (end - start) * (1 / (count - 1)) per axis. Each point goes to the spawn handler kind of
 * D_8008ADA0 as (0, i, x, y, z, x0, y0, z0, 0, 0, 0.0f, arg8, arg9, argA, argB) (mode 0 = line; the ring emitter
 * func_1514C860 uses mode 1); the walk stops early when a handler returns 0, a missing handler skips the point.
 * The loop counts count down by 1 while it stays > 0. (The asm tests the parity of (s32) count and computes the
 * same step in both branches.)
 */
void func_1514C9E0(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 count, u8 kind, s32 arg8, f32 arg9, s32 argA,
                   u8 argB) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    f32 inv;
    f32 dx, dy, dz;
    f32 x, y, z;
    s16 i = 0;

    if (count < 2.0f) {
        return;
    }
    inv = 1.0f / (count - 1.0f);
    dx = (x1 - x0) * inv;
    dy = (y1 - y0) * inv;
    dz = (z1 - z0) * inv;
    x = x0;
    y = y0;
    z = z0;
    do {
        handler = ((void **) &D_8008ADA0)[kind];
        if (handler != NULL && handler(0, i, x, y, z, x0, y0, z0, 0, 0, 0.0f, arg8, arg9, argA, argB) == 0) {
            break;
        }
        count -= 1.0f;
        x += dx;
        i++;
        y += dy;
        z += dz;
    } while (count > 0.0f);
}
