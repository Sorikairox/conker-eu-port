extern s32 D_8008ADA0;

/*
 * spawn_arc_emit: emits count random points on a vertical circle of radius r around (x, y, z) whose plane faces
 * the byte angle yaw: each point takes a random byte angle a in [min(a0, a1), max(a0, a1)] and goes to the spawn
 * handler kind of D_8008ADA0 as (3, i, x + r * sin(yaw - 0x40) * sin(a), y - r * sin(a - 0x40),
 * z + r * sin(yaw) * sin(a), x, y, z, a & 0xFF, yaw, r, arg9, argA, argB, argC) (mode 3 = arc; func_151423D8 =
 * byte-angle sine). The walk stops when a handler returns 0; a missing handler skips the point.
 */
void func_1514CDC8(f32 x, f32 y, f32 z, f32 r, s16 yaw, s16 a0, s16 a1, s16 count, u8 kind, s32 arg9, f32 argA,
                   s32 argB, u8 argC) {
    s32 (*handler)(s32, s16, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, f32, s32, s32);
    f32 cosYaw = func_151423D8((yaw - 0x40) & 0xFF);
    f32 sinYaw = func_151423D8(yaw & 0xFF);
    f32 rc;
    f32 rs;
    f32 c, s;
    f32 px, pz;
    s16 n;
    s16 lo;
    s16 i;
    s32 a;
    s32 b;

    if (a1 < a0) {
        n = a0 - a1 + 1;
        lo = a1;
    } else {
        n = a1 - a0 + 1;
        lo = a0;
    }
    if (count <= 0) {
        return;
    }
    rc = r * cosYaw;
    rs = r * sinYaw;
    i = 0;
    do {
        a = (u32) func_150ADA20() % (u32) n + lo;
        b = a & 0xFF;
        c = func_151423D8((a - 0x40) & 0xFF);
        s = func_151423D8(b);
        handler = ((void **) &D_8008ADA0)[kind];
        px = rc * s + x;
        pz = rs * s + z;
        if (handler != NULL && handler(3, i, px, y - r * c, pz, x, y, z, b, yaw, r, arg9, argA, argB, argC) == 0) {
            return;
        }
        i++;
    } while (i < count);
}
