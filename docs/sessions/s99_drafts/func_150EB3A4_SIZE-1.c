typedef struct {
    f32 x;
    f32 z;
    f32 vx;
    f32 vz;
    f32 y;
    s32 u2C;
    f32 t;
    f32 hit;
} S2_EB3A4;
typedef struct {
    u8 pad0[0x14];
    u8 *obj;
    S2_EB3A4 s;
} S_EB3A4;
extern f32 D_800BE9A4;
s32 func_15046F70(f32 *, s32, s32, f32 *);
s32 func_150EB3A4(S_EB3A4 *arg0) {
    S2_EB3A4 *p;
    f32 v[3];
    s32 r;

    arg0->s.x += arg0->s.vx * D_800BE9A4;
    arg0->s.z += arg0->s.vz * D_800BE9A4;
    v[0] = arg0->s.x;
    v[1] = arg0->s.y;
    v[2] = arg0->s.z;
    *(s16 *)(arg0->obj + 0xE) = arg0->s.x;
    *(s16 *)(arg0->obj + 0x12) = arg0->s.z;
    if (func_15046F70(v, 0, arg0->s.u2C, &arg0->s.hit) != 0) {
        p = &arg0->s;
        *(s16 *)(arg0->obj + 0x10) = p->hit;
    } else {
        p = &arg0->s;
        *(s16 *)(arg0->obj + 0x10) = p->y;
    }
    p->t -= D_800BE9A4;
    r = 1;
    if (p->t <= 0.0f) {
        r = 0;
    }
    return r;
}
