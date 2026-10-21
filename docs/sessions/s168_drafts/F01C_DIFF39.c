void func_151108E0(s32, f32 (*)[4], f32, f32, f32);
void func_150A7EE0(f32 (*)[4], f32, f32, s32, f32 *, f32 *, s32 *, f32 *);

s32 func_1517F01C(f32 arg0, f32 arg1, s32 arg2, f32 *arg3, f32 *arg4) {
    s32 pad[2];
    f32 dx;
    f32 dz;
    s32 unk;
    f32 dist;
    f32 mtx[4][4];
    struct108 *p;
    u8 *e;
    f32 x;
    f32 z;
    f32 inv;

    p = &D_800DBFF0[D_80082FA4];
    func_151108E0(D_80082FA4, mtx, -p->unk388, -p->unk380, *(f32 *)&p->pad5EC);
    e = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
    x = *(f32 *)(e + 0xC);
    z = *(f32 *)(e + 0x10);
    func_150A7EE0(mtx, arg0, arg1, arg2, &dx, &dz, &unk, &dist);
    if (dist > 10.0f) {
        inv = 1.0f / dist;
        dx = dx * x * inv;
        dz = dz * z * inv;
        *arg3 = x + dx;
        *arg4 = z - dz;
        return 1;
    }
    *arg3 = 0.0f;
    *arg4 = 0.0f;
    return 0;
}
