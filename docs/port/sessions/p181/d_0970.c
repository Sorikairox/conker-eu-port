void func_15143794(s16, s16, f32, void *);
s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
s32 memcpy(s32, f32 *, s32);

// spark_burst_spawn: P181: spawns def +0 + rand % (def +4 + 1) particles (0 = none) from the burst definition
// `arg0`: each at a random direction (angles ang[0] + rand % (ang[1] + 1), ang[2] + rand % (ang[3] + 1)) at
// distance def +0x54 from the centre def +8, moving that way at def +0x14 + random x +0x18, random rotation 0..360
// on all axes, spin +-def +0x30 about x / z, fade def +0x1C + random x +0x20, life def +0x24 + rand % (+0x26 + 1),
// texture ((s32 *)def +0x48)[k] for a random k < def +0x50 with size ((f32 *)def +0x4C)[k] x (def +0x28 + random x
// +0x2C) (+0 = def +0x44 x size), +4 = def +0x3C + random x +0x40. With chance def +0x38 the particle is solid
// (+0x61 = 13, +0x63 = def +0x59), else +0x61 = 8. Flags 0x121E9, plus 0x800 and effect kind 3 (else 0) when
// def +0x58 bit 0 is set. Effect via func_15132BBC (def +0x34, extra bytes def +0x5C copied from def +0x60 to
// +0x170, owner arg2 / arg3). The asm leaves a stale v0; the callers ignore it (s32 matches their prototype).
s32 func_15150970(s32 *arg0, s16 *ang, u8 arg2, s32 arg3) {
    u8 *def = (u8 *)arg0;
    struct {
        f32 u00;       /* +0x00 */
        f32 u04;       /* +0x04 */
        f32 sizeX;     /* +0x08 */
        f32 sizeY;     /* +0x0C */
        f32 rot[3];    /* +0x10 */
        f32 u1C[3];    /* +0x1C */
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
        u8 u61;        /* +0x61 */
        u8 u62;
        u8 u63;        /* +0x63 */
        u8 u64[4];
        u8 u68;
        s8 u69;
        u8 u6A;
        s32 u6C;
        u8 u70;
        s16 u72;
        s16 u74;
        s32 u78;
    } p;
    s32 n;
    s16 angA;
    s16 angB;
    u32 k;
    u8 *e;

    p.u1C[0] = 1.0f;
    p.u1C[1] = 1.0f;
    p.u1C[2] = 1.0f;
    p.spinY = 0.0f;
    p.flags = ((def[0x58] & 1) ? 0x800 : 0) | 0x21E9 | 0x10000;
    p.u58 = 0;
    p.u5C = 0;
    p.u60 = 0xFF;
    p.u62 = 0;
    p.u64[0] = 0;
    p.u64[1] = 0;
    p.u64[2] = 0;
    p.u64[3] = 0;
    p.u68 = 2;
    p.u69 = -1;
    p.u6A = 0;
    p.u6C = 0;
    p.u70 = 0;
    p.u72 = 0xC;
    p.u74 = 0x15;
    p.u78 = 0;
    n = (u32) func_150ADA20() % (u32) (*(s32 *)(def + 4) + 1) + *(s32 *)(def + 0);
    while (n != 0) {
        angA = (u32) func_150ADA20() % (u32) (ang[1] + 1) + ang[0];
        angB = (u32) func_150ADA20() % (u32) (ang[3] + 1) + ang[2];
        if (func_150ADA68() < *(f32 *)(def + 0x38)) {
            p.u61 = 13;
            p.u63 = def[0x59];
        } else {
            p.u61 = 8;
            p.u63 = 0;
        }
        p.u04 = func_150ADA68() * *(f32 *)(def + 0x40) + *(f32 *)(def + 0x3C);
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        func_15143794(angA, angB, func_150ADA68() * *(f32 *)(def + 0x18) + *(f32 *)(def + 0x14), p.vel);
        p.spinX = func_150ADA68() * (*(f32 *)(def + 0x30) + *(f32 *)(def + 0x30)) - *(f32 *)(def + 0x30);
        p.spinZ = func_150ADA68() * (*(f32 *)(def + 0x30) + *(f32 *)(def + 0x30)) - *(f32 *)(def + 0x30);
        p.fade = func_150ADA68() * *(f32 *)(def + 0x20) + *(f32 *)(def + 0x1C);
        p.life = (u32) func_150ADA20() % (u32) (*(s16 *)(def + 0x26) + 1) + *(s16 *)(def + 0x24);
        func_15143794(angA, angB, *(f32 *)(def + 0x54), p.pos);
        p.pos[0] += *(f32 *)(def + 0x8);
        p.pos[1] += *(f32 *)(def + 0xC);
        p.pos[2] += *(f32 *)(def + 0x10);
        k = (u32) func_150ADA20() % *(u32 *)(def + 0x50);
        p.texture = (*(s32 **)(def + 0x48))[k];
        p.sizeY = (*(f32 **)(def + 0x4C))[k] * (*(f32 *)(def + 0x28) + func_150ADA68() * *(f32 *)(def + 0x2C));
        p.sizeX = p.sizeY;
        p.u00 = *(f32 *)(def + 0x44) * p.sizeX;
        e = (u8 *)func_15132BBC(&p, (def[0x58] & 1) ? 3 : 0, 0xFF, *(s32 *)(def + 0x34), *(s32 *)(def + 0x5C), arg2,
                                arg3);
        if (*(s32 *)(def + 0x5C) > 0 && e != NULL) {
            memcpy((s32)(e + 0x170), *(f32 **)(def + 0x60), *(s32 *)(def + 0x5C));
        }
        n--;
    }
    return 0;
}
