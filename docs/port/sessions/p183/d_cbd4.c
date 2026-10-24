void *allocate_memory(s32, s32, s32, s32);

// light_column_create: P183: creates the light-column effect (func_15167A68 kind 0x4E in level 0x2C, else 0x2F;
// layer arg1 + 0x58) from the 0x24-byte zone record arg0 (copied to +0x10: point +0x14..+0x1C, bottom y +0x24,
// +0x2C scale -> +0x34 = 1 / scale). +0x38 = 20 points (0x18 bytes) up the column from y = bottom to the top
// (+0x18) in 19 steps at the point's x / z, +0x3C = step height, +0x48 = 2 x 20 quads of 4 Vtx (texture 0x37 in
// level 0xB, else 0x36: s = 0 / w/4 / w/2 / 3w/4 (+0x100, << 5), t = (0x100 + i * (h - 1)) << 5 (<< 4 for 0x37),
// flag 0, colour (0x58, 0x4B, 0x2C) in level 0x39 else white, alpha 0xFF). Returns the effect (0 without one).
s32 func_151ACBD4(s8 *arg0, s32 arg1) {
    u8 *e;
    f32 *pt;
    Vtx *v;
    s32 x, top, bottom, z, dy;
    s32 i, k;
    s32 shift;
    s32 tw, th;
    s32 t;
    s32 s1, s2, s3;
    u8 r, g, b;
    struct_eu_80090F10 *tex;

    e = func_15167A68((D_800BE9F0 == 0x2C) ? 0x4E : 0x2F, 0, arg1 + 0x58, 1, 0xFF, 1);
    if (e == NULL) {
        return 0;
    }
    memcpy(e + 0x10, arg0, 0x24);
    *(s32 *) (e + 0x44) = 0;
    *(s16 *) (e + 0x52) = 0;
    *(f32 *) (e + 0x34) = 1.0f / *(f32 *) (e + 0x2C);
    *(f32 **) (e + 0x38) = allocate_memory(0x1E0, 1, 0, 0);
    x = *(f32 *) (e + 0x14);
    top = *(f32 *) (e + 0x18);
    z = *(f32 *) (e + 0x1C);
    bottom = *(f32 *) (e + 0x24);
    e[0x42] = 20;
    dy = top - bottom;
    for (i = 0; i < 20; i++) {
        pt = *(f32 **) (e + 0x38) + i * 6;
        pt[0] = x;
        pt[1] = (dy * i) / 19 + bottom;
        pt[2] = z;
        pt[3] = 0.0f;
        pt[4] = 0.0f;
        pt[5] = 0.0f;
    }
    *(f32 *) (e + 0x3C) = (f32) (top - bottom) / 19.0f;
    *(Vtx **) (e + 0x48) = allocate_memory(0xA00, 1, 2, 0);

    if (D_800BE9F0 == 0xB) {
        *(u16 *) (e + 0x40) = 0x37;
        shift = 4;
    } else {
        *(u16 *) (e + 0x40) = 0x36;
        shift = 5;
    }
    if (D_800BE9F0 == 0x39) {
        r = 0x58;
        g = 0x4B;
        b = 0x2C;
    } else {
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
    }
    tex = &D_80090F10[*(u16 *) (e + 0x40)];
    tw = tex->unk6 >> 2;
    th = tex->unk8 - 1;
    s1 = (tw + 0x100) << 5;
    s2 = (tw * 2 + 0x100) << 5;
    s3 = (tw * 3 + 0x100) << 5;
    for (k = 0; k < 2; k++) {
        v = *(Vtx **) (e + 0x48) + k * 80;
        t = 0x100;
        for (i = 0; i < 20; i++, v += 4) {
            s32 tt = t << shift;

            t += th;
            v[0].v.flag = 0;
            v[0].v.tc[0] = 0x2000;
            v[0].v.tc[1] = tt;
            v[0].v.cn[0] = r;
            v[0].v.cn[1] = g;
            v[0].v.cn[2] = b;
            v[0].v.cn[3] = 0xFF;
            v[1].v.flag = 0;
            v[1].v.tc[0] = s1;
            v[1].v.tc[1] = tt;
            v[1].v.cn[0] = r;
            v[1].v.cn[1] = g;
            v[1].v.cn[2] = b;
            v[1].v.cn[3] = 0xFF;
            v[2].v.flag = 0;
            v[2].v.tc[0] = s2;
            v[2].v.tc[1] = tt;
            v[2].v.cn[0] = r;
            v[2].v.cn[1] = g;
            v[2].v.cn[2] = b;
            v[2].v.cn[3] = 0xFF;
            v[3].v.flag = 0;
            v[3].v.tc[0] = s3;
            v[3].v.tc[1] = tt;
            v[3].v.cn[0] = r;
            v[3].v.cn[1] = g;
            v[3].v.cn[2] = b;
            v[3].v.cn[3] = 0xFF;
        }
    }
    *(f32 *) (e + 0x4C) = 0.0f;
    return (s32) e;
}
