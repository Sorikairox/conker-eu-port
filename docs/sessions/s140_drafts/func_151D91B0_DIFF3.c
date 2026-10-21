f32 func_15143E64(f32 *, f32 *);

void func_151D91B0(u8 *arg0, f32 *arg1) {
    f32 *p;
    f32 d[3];
    f32 dist;
    f32 lo;
    f32 v;

    p = func_15144B34(((u8 *)arg1)[0x18]);
    d[0] = arg1[0] - p[0];
    d[1] = arg1[1] - p[1];
    d[2] = arg1[2] - p[2];
    dist = func_15143E64(d, arg1);
    lo = arg1[3];
    if (dist < lo) {
        v = 1.0f;
    } else if ((lo + arg1[4]) < (0, dist)) {
        v = 0.0f;
    } else {
        v = 1.0f - ((dist - lo) * arg1[5]);
    }
    arg0[0x12] = v * 8.0f;
}
