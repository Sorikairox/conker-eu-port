s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];
f32 func_150489B0();

u8 *func_1518ECAC(u8 *arg0, s16 arg1) {
    u8 *sp74;
    u8 *sp70;
    f32 c;
    f32 s;
    f32 t;
    f32 r;
    f32 sn;
    f32 cs;
    f32 a;
    f32 b;
    f32 d;
    f32 e;
    f32 f;
    f32 m;
    s32 pos;
    u8 ang;
    u8 sp3F;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp74, &sp3F);
    sp70 = sp74;
    if (sp74 != NULL) {
        if (sp3F != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    c = D_800DD608[arg1];
    s = D_800DD618[arg1];
    t = ((*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x34)) * s - c * (*(f32 *)(arg0 + 0x48) - *(f32 *)(arg0 + 0x3C))) * D_800BEDC8;
    pos = -1;
    if (t < 0.0f) {
        t = -t;
        pos = 0;
    }
    r = sqrtf(t) * *(f32 *)(arg0 + 0x160);
    if (r > 1.5707964f) {
        r = 1.5707964f;
    }
    if (pos) {
        r = -r;
    }
    ang = r * 40.743664f;
    sn = func_15048A40(ang);
    cs = func_150489B0(ang);
    a = *(f32 *)(arg0 + 0x2C) * cs;
    b = *(f32 *)(arg0 + 0x2C) * sn;
    d = *(f32 *)(arg0 + 0x30) * sn;
    e = *(f32 *)(arg0 + 0x30) * cs;
    *(s16 *)(sp74 + 0) = *(f32 *)(arg0 + 0x34) + a * s;
    *(s16 *)(sp74 + 2) = *(f32 *)(arg0 + 0x38) + b;
    *(s16 *)(sp74 + 4) = *(f32 *)(arg0 + 0x3C) - a * c;
    m = -a;
    *(s16 *)(sp74 + 0x10) = *(f32 *)(arg0 + 0x34) + m * s;
    *(s16 *)(sp74 + 0x12) = *(f32 *)(arg0 + 0x38) - b;
    *(s16 *)(sp74 + 0x14) = *(f32 *)(arg0 + 0x3C) - m * c;
    f = -(a + d);
    *(s16 *)(sp74 + 0x20) = *(f32 *)(arg0 + 0x34) + f * s;
    *(s16 *)(sp74 + 0x22) = *(f32 *)(arg0 + 0x38) + e - b;
    *(s16 *)(sp74 + 0x24) = *(f32 *)(arg0 + 0x3C) - f * c;
    f = a - d;
    *(s16 *)(sp74 + 0x30) = *(f32 *)(arg0 + 0x34) + f * s;
    *(s16 *)(sp74 + 0x32) = *(f32 *)(arg0 + 0x38) + e + b;
    *(s16 *)(sp74 + 0x34) = *(f32 *)(arg0 + 0x3C) - f * c;
    return sp70;
}
