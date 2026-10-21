typedef struct { f32 x, y, z; } V3_151B402C;
typedef struct { V3_151B402C a; V3_151B402C b; } Ent_151B402C;
typedef struct { u8 pad0[0x10]; u8 flags; u8 pad11[3]; V3_151B402C p0; V3_151B402C p1; u8 pad2C[0x1C]; Ent_151B402C e[10]; } Obj_151B402C;
extern f32 D_800AA774;
extern f32 D_800AA778;
extern f32 D_800AA77C;
s32 func_151B402C(Obj_151B402C *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;
    V3_151B402C p;

    dx = arg0->p1.x - arg0->p0.x;
    dy = arg0->p1.y - arg0->p0.y;
    dz = arg0->p1.z - arg0->p0.z;
    p = arg0->p0;
    arg0->e[0].a = p;
    arg0->e[0].b.z = arg0->e[0].b.y = arg0->e[0].b.x = 0.0f;
    dx *= D_800AA774;
    dy *= D_800AA778;
    dz *= D_800AA77C;
    for (i = 1; i < 10; i++) {
        p.x += dx;
        p.y += dy;
        p.z += dz;
        arg0->e[i].a = p;
        arg0->e[i].b.z = arg0->e[i].b.y = arg0->e[i].b.x = 0.0f;
    }
    arg0->flags &= ~2;
    return 1;
}
