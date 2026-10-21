extern u8 D_8008D450[];
extern f32 D_800A758C;
extern f32 D_800A7590;
extern f32 D_800A7594;
extern f32 D_800A7598;

void func_151777CC(u8 arg0) {
    f32 s;
    u8 *e;
    u8 *m;
    f32 t;
    f32 a;
    f32 r;
    s32 x;
    s32 y;

    e = D_8008D450 + arg0 * 0x38;
    m = (u8 *)D_800DE2B8[arg0].x0;
    t = func_150AD78C(*(f32 *)(e + 0x24) * D_800A758C) * *(f32 *)(e + 0x28);
    *(f32 *)(e + 0x18) = t;
    a = t * D_800A7590;
    s = func_150AD78C(a);
    r = *(f32 *)(e + 0x30);
    x = r * func_150AD780(a);
    y = r * s;
    *(s16 *)(m + 0xA0) = -x;
    *(s16 *)(m + 0xB0) = -x;
    *(s16 *)(m + 0x110) = x;
    *(s16 *)(m + 0x120) = x;
    *(s16 *)(m + 0x112) = y;
    *(s16 *)(m + 0x122) = y;
    *(s16 *)(m + 0xA2) = y;
    *(s16 *)(m + 0xB2) = y;
    t = func_150AD78C((*(f32 *)(e + 0x24) - 30.0f) * D_800A7594) * *(f32 *)(e + 0x28);
    *(f32 *)(e + 0x18) = t;
    a = t * D_800A7598;
    s = func_150AD78C(a);
    r = *(f32 *)(e + 0x34);
    x = r * func_150AD780(a);
    y = r * s;
    *(s16 *)(m + 0xE0) = -x;
    *(s16 *)(m + 0x130) = x;
    *(s16 *)(m + 0xE2) = y;
    *(s16 *)(m + 0x132) = y;
    *(f32 *)(e + 0x24) += *(f32 *)(e + 0x1C);
    if (*(f32 *)(e + 0x24) >= 360.0f) {
        *(f32 *)(e + 0x24) -= 360.0f;
    }
}
