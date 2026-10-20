typedef struct { f32 x, y, z; } V3;

s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, s32 arg4, s32 arg5, f32 *arg6, f32 *arg7) {
    f32 dx, dy, dz;
    V3 dir;
    V3 org;
    f32 b, dd, d, t, t0, t1;

    dx = arg2->unk0 - arg0->unk0;
    dy = arg2->unk4 - arg0->unk4;
    dz = arg2->unk8 - arg0->unk8;
    dir = *(V3 *)arg1;
    org = *(V3 *)arg0;
    b = dx * dir.x + dy * dir.y + dz * dir.z;
    dd = dx * dx + dy * dy + dz * dz;
    d = dd - b * b;
    if ((arg3 * arg3) < d) {
        return 0;
    }
    t = sqrtf((arg3 * arg3) - d);
    if (b < t) {
        t = -t;
    }
    t0 = b - t;
    t1 = b + t;
    ((V3 *)arg4)->x = t0 * dir.x + org.x;
    ((V3 *)arg4)->y = t0 * dir.y + org.y;
    ((V3 *)arg4)->z = t0 * dir.z + org.z;
    *arg6 = t0;
    ((V3 *)arg5)->x = t1 * dir.x + org.x;
    ((V3 *)arg5)->y = t1 * dir.y + org.y;
    ((V3 *)arg5)->z = t1 * dir.z + org.z;
    *arg7 = t1;
    {
        V3 diff;

        diff.x = ((V3 *)arg4)->x - arg0->unk0;
        diff.y = ((V3 *)arg4)->y - arg0->unk4;
        diff.z = ((V3 *)arg4)->z - arg0->unk8;
        if (func_15144A74((struct17 *)&diff, arg1) < 0.0f) {
            return 0;
        }
    }
    return 1;
}
