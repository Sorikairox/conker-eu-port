s32 func_15132FBC(void *, s32, s32, s32, s32, s32);
void func_15143794(s16, s16, f32, void *);

// particle_burst_spawn: P179: spawns def +0 + random [0, def +4] kind-3 particles (func_15132FBC record block,
/* 0x76 bytes) from the burst definition `arg0`: each at a random direction (angles def +0x14 + random [0, +0x16],
 * +0x18 + random [0, +0x1A]) `dist` from the centre def +8, moving that way at def +0x1C + random x +0x20, spin
 * +-def +0x38 about x / z, random rotation 0..360 on all axes, life def +0x2C + random [0, +0x2E], fade
 * def +0x24 + random x +0x28, texture tex[k] for a random k < ntex with size scale[k] x (def +0x30 + random x
 * +0x34). Flags 0x29E8, plus 0x100000 when `flag`; owner / owner arg arg6 / arg7. */
void func_15152700(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7) {
    u8 *def = arg0;
    s32 *tex = arg1;
    f32 *scale = arg2;
    struct {
        f32 u00[2];
        f32 sizeX;     /* +0x08 */
        f32 sizeY;     /* +0x0C */
        f32 rot[3];    /* +0x10 */
        f32 u1C[3];
        f32 pos[3];    /* +0x28 */
        f32 vel[3];    /* +0x34 */
        f32 spinX;     /* +0x40 */
        f32 spinY;     /* +0x44 */
        f32 spinZ;     /* +0x48 */
        f32 fade;      /* +0x4C */
        s32 flags;     /* +0x50 */
        s16 life;      /* +0x54 */
        s16 texture;   /* +0x56 */
        u8 u58;
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[6];
        u8 u68;
        u8 u6A;        /* +0x6A */
        s32 u6C;
        u8 u70;
        s16 u72;
        s16 u74;
    } p;
    s32 n;
    s16 angA;
    s16 angB;
    u32 k;

    p.u00[0] = 1.0f;
    p.u00[1] = 1.0f;
    p.u1C[0] = 1.0f;
    p.u1C[1] = 1.0f;
    p.u1C[2] = 1.0f;
    p.spinY = 0.0f;
    p.flags = (arg5 ? 0x100000 : 0) | 0x29E8;
    p.u58 = 0;
    p.u5C = 0;
    p.u60 = 0xFF;
    p.u61 = 8;
    p.u62[0] = 0;
    p.u62[1] = 0;
    p.u62[2] = 0;
    p.u62[3] = 0;
    p.u62[4] = 0;
    p.u62[5] = 0;
    p.u68 = 2;
    p.u6A = 0;
    p.u6C = 0;
    p.u70 = 0;
    p.u72 = 0xC;
    p.u74 = 0x15;
    n = (u32) func_150ADA20() % (u32) (*(s32 *)(def + 4) + 1) + *(s32 *)(def + 0);
    while (n != 0) {
        angA = (u32) func_150ADA20() % (u32) (*(s16 *)(def + 0x16) + 1) + *(s16 *)(def + 0x14);
        angB = (u32) func_150ADA20() % (u32) (*(s16 *)(def + 0x1A) + 1) + *(s16 *)(def + 0x18);
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        func_15143794(angA, angB, func_150ADA68() * *(f32 *)(def + 0x20) + *(f32 *)(def + 0x1C), p.vel);
        p.spinX = func_150ADA68() * (*(f32 *)(def + 0x38) + *(f32 *)(def + 0x38)) - *(f32 *)(def + 0x38);
        p.spinZ = func_150ADA68() * (*(f32 *)(def + 0x38) + *(f32 *)(def + 0x38)) - *(f32 *)(def + 0x38);
        p.fade = func_150ADA68() * *(f32 *)(def + 0x28) + *(f32 *)(def + 0x24);
        p.life = (u32) func_150ADA20() % (u32) (*(s16 *)(def + 0x2E) + 1) + *(s16 *)(def + 0x2C);
        func_15143794(angA, angB, arg4, p.pos);
        p.pos[0] += *(f32 *)(def + 0x8);
        p.pos[1] += *(f32 *)(def + 0xC);
        p.pos[2] += *(f32 *)(def + 0x10);
        k = (u32) func_150ADA20() % (u32) arg3;
        p.texture = tex[k];
        p.sizeY = scale[k] * (*(f32 *)(def + 0x30) + func_150ADA68() * *(f32 *)(def + 0x34));
        p.sizeX = p.sizeY;
        func_15132FBC(&p, 3, 0xFF, 0, arg6, arg7);
        n--;
    }
}
