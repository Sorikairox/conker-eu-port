s32 func_1507C7C0(s32, s16 *, s16 *, s16 *);
s32 func_15145128(f32 *, f32 *, f32 *, s32 *);
s32 func_151451F0(f32 *, f32 *, f32 *, f32, f32, f32 *, f32 *, s32 *, s32 *);
#define p ((u8 *)arg0)
s32 func_151C8D90(s32 arg0, u8 *arg1) {
    f32 r;
    f32 pos[3];
    f32 a[3];
    f32 half;
    f32 k;
    f32 x;
    f32 d[3];
    f32 len;
    f32 o1[3];
    f32 o2[3];
    s32 o3;
    s32 o4;
    s16 h;
    s16 w;
    s16 l;
    s32 t;

    if (p[4] < 0xBB && p[4] != 0xFF) {
        r = D_800D1C90[p[4]]->unk1A * *(f32 *)(p + 0x14C);
    } else {
        r = 50.0f;
    }
    func_1507C7C0(arg0, &h, &w, &l);
    if ((f32)h == 0.0f) {
        return 0;
    }
    half = (f32)h * 0.5f;
    pos[0] = *(f32 *)(p + 0x14);
    pos[1] = *(f32 *)(p + 0x18) + half;
    k = r / half;
    pos[2] = *(f32 *)(p + 0x1C);
    a[0] = *(f32 *)(arg1 + 0x34);
    a[1] = (*(f32 *)(arg1 + 0x38) - pos[1]) * k + pos[1];
    a[2] = *(f32 *)(arg1 + 0x3C);
    d[0] = *(f32 *)(arg1 + 0x40) - a[0];
    d[1] = ((*(f32 *)(arg1 + 0x44) - pos[1]) * k + pos[1]) - a[1];
    d[2] = *(f32 *)(arg1 + 0x48) - a[2];
    if (func_15145128(d, d, &len, &t) == 0) {
        return 0;
    }
    if (func_151451F0(a, d, pos, r, len, o1, o2, &o3, &o4) != 0) {
        return 1;
    }
    return 0;
}
#undef p
