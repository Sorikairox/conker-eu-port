typedef struct {
    f32 x;
    f32 y;
} V2BF8;

typedef struct {
    s16 t;
    f32 f4;
    V2BF8 v;
    f32 g;
    f32 k;
} MovBF8;

typedef struct {
    u8 pad0[0x10];
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u8 pad20[0x50];
    MovBF8 m;
} ObjBF8;

s32 func_15135BF8(ObjBF8 *arg0) {
    MovBF8 *m = &arg0->m;
    V2BF8 v;
    f32 s;
    s32 ret = 1;

    if (arg0->m.t > 0) {
        m->t -= D_800BE9E4;
        arg0->x10 += m->v.x * D_800BE9A4;
        arg0->x14 += m->v.y * D_800BE9A4;
        arg0->x18 += m->f4 * D_800BE9A4;
        arg0->x1C += m->f4 * D_800BE9A4;
    } else {
        v = m->v;
        arg0->x14 += m->v.y * D_800BE9A4 + m->g * D_800BE9A4 * D_800BE9A4 * 0.5f;
        m->v.y += m->g * D_800BE9A4;
        v.x += m->v.x;
        v.y += m->v.y;
        v.x *= 0.5f;
        v.y *= 0.5f;
        s = fabsf(v.x) * m->k;
        arg0->x18 += s * D_800BE9A4;
        arg0->x1C += s * D_800BE9A4;
    }
    if (arg0->x10 > 200.0f || arg0->x10 < -200.0f || arg0->x14 > 200.0f || arg0->x14 < -200.0f) {
        ret = 0;
    }
    return ret;
}
