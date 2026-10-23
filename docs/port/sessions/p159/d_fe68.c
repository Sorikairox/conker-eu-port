void func_15143874(s16, f32, f32 *, f32 *);
void func_151A3084(s32, s32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32);
// spray_particles_spawn: scales `normal` by 1000 (in place) and spawns base + rand % (extra + 1) particles
// (func_151A3084) at p's point, each moving along normal plus a random offset in the plane of axisA / axisB
// (func_15143874: random angle, radius rand * spread), times a random speed; size, life and the rest come from
// the parameter block p (func_151C01F0 fills one).
void func_1514FE68(u8 *p, u8 *normal, s32 *axisA, s32 *axisB, f32 spread, s32 arg5, s32 arg6) {
    typedef struct {
        s32 countBase;     /* 0x00 */
        s32 countExtra;    /* 0x04 */
        f32 pos[3];        /* 0x08 */
        f32 speedBase;     /* 0x14 */
        f32 speedRange;    /* 0x18 */
        f32 sizeBase;      /* 0x1C */
        f32 sizeRange;     /* 0x20 */
        f32 size2Base;     /* 0x24 */
        f32 size2Range;    /* 0x28 */
        s32 lifeBase;      /* 0x2C */
        s32 lifeExtra;     /* 0x30 */
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        s16 u44;
        s16 u46;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s8 u50;
    } SprayParams;
    SprayParams *sp = (SprayParams *)p;
    f32 *n = (f32 *)normal;
    f32 *a = (f32 *)axisA;
    f32 *b = (f32 *)axisB;
    f32 c;
    f32 s;
    f32 speed;
    f32 r1;
    f32 r2;
    f32 vel[3];
    u32 count;
    u32 angle;
    u32 life;

    n[0] *= 1000.0f;
    n[1] *= 1000.0f;
    n[2] *= 1000.0f;
    count = (u32)func_150ADA20() % (u32)(sp->countExtra + 1) + sp->countBase;
    for (; count != 0; count--) {
        speed = func_150ADA68() * sp->speedRange + sp->speedBase;
        angle = func_150ADA20();
        func_15143874(angle & 0xFF, func_150ADA68() * spread, &c, &s);
        vel[0] = (a[0] * c + b[0] * s + n[0]) * speed;
        vel[1] = (a[1] * c + b[1] * s + n[1]) * speed;
        vel[2] = (a[2] * c + b[2] * s + n[2]) * speed;
        r1 = func_150ADA68();
        r2 = func_150ADA68();
        life = (u32)func_150ADA20() % (u32)(sp->lifeExtra + 1) + sp->lifeBase;
        func_151A3084((s32)sp->pos, (s32)vel, r1 * sp->sizeRange + sp->sizeBase, r2 * sp->size2Range + sp->size2Base,
                      life, sp->u34, sp->u38, sp->u3C, sp->u40, sp->u44, sp->u46, sp->u48, sp->u4A, sp->u4C, sp->u4E,
                      sp->u50, (u8)arg5, arg6);
    }
}
