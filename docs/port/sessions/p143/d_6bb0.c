f32 func_15144528(f32, f32, f32);
void func_15143874(s16, f32, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
extern f32 D_800A9180;
extern f32 D_800A9184;
extern f32 D_800A9188;
extern f32 D_800A918C;
// bubble_emitter_update: update handler (D_8008A100 slot 40) of a particle emitter effect. Optional sound / light
// probe (func_1508B20C, radius 500) when +0x127 is set; +0x114 angle advances by +0x118 * dt (wrapped by
// func_15144528 to 2048); the pulse phase byte +0x124 advances by +0x125 per tick and sets the brightness +0x126
// (192 + 63 * sin). Unless func_151464B8(+0x60) says the emitter is off, the spawn accumulator +0x128 grows by
// (D_800A9180 + rand * D_800A9184) * dt and each whole unit spawns one particle (func_151307F0) at a random point of
// the disc in the s16 {x, y, z, radius} at *(+0x110), with random size, life, velocity (func_15143794) and fade.
// Always returns 1.
s32 func_151A6BB0(u8 *fx) {
    struct {
        s32 render[2];  /* 0x200005, 0x1F0600 */
        s16 u8;         /* 0x2203 */
        s16 sprite;     /* 0x19 + rand & 0xF */
        s32 uC;
        s32 u10;
        u8 color[6];    /* 0xFF */
        u8 u1A;
        u8 life;        /* 100..200 */
        u8 u1C;
        u8 u1D;         /* 0x28 */
        s16 u1E;        /* 0xC */
        s16 u20;        /* 0x15 */
        s16 u22;        /* 1 */
        f32 u24;        /* 1.0 */
        f32 size[2];
        f32 pos[3];
        f32 u3C[3];
        f32 vel[3];
        f32 fade;
        s32 u58;        /* 0xC207 */
        s32 u5C;
        s8 u60[6];      /* 6, 8, -1, -1, -1, 0 */
    } req;
    f32 *mv = (f32 *)(fx + 0x110);
    s16 *src;
    s32 r0, r1;
    f32 rf;

    if (fx[0x127] != 0) {
        func_1508B20C(*(f32 *)(fx + 0x34), *(f32 *)(fx + 0x38), *(f32 *)(fx + 0x3C), 500.0f);
    }
    mv[1] += mv[2] * D_800BE9A4;
    mv[1] = func_15144528(mv[1], 2048.0f, 0.0f);
    fx[0x124] += fx[0x125] * D_800BE9E4;
    fx[0x126] = (u32)(func_151423D8(fx[0x124] - 0x40) * 63.0f + 192.0f);
    if (func_151464B8(*(s32 *)(fx + 0x60)) != 0) {
        return 1;
    }
    mv[6] += (D_800A9180 + func_150ADA68() * D_800A9184) * D_800BE9A4;
    if (mv[6] > 1.0f) {
        req.u1D = 0x28;
        req.u8 = 0x2203;
        req.render[0] = 0x200005;
        req.render[1] = 0x1F0600;
        req.color[0] = 0xFF;
        req.color[1] = 0xFF;
        req.color[2] = 0xFF;
        req.color[3] = 0xFF;
        req.color[4] = 0xFF;
        req.color[5] = 0xFF;
        req.u3C[0] = 0.0f;
        req.u3C[1] = 0.0f;
        req.u3C[2] = 0.0f;
        req.uC = 0;
        req.u10 = 0;
        req.u1A = 0xFF;
        req.u1E = 0xC;
        req.u20 = 0x15;
        req.u22 = 1;
        req.u24 = 1.0f;
        req.u58 = 0xC207;
        req.u60[0] = 6;
        req.u60[1] = 8;
        req.u60[2] = -1;
        req.u60[3] = -1;
        req.u60[4] = -1;
        req.u60[5] = 0;
        do {
            r0 = func_150ADA20();
            src = *(s16 **)(fx + 0x110);
            func_15143874(r0 & 0xFF, func_150ADA68() * src[3], &req.pos[0], &req.pos[2]);
            src = *(s16 **)(fx + 0x110);
            req.pos[0] += src[0];
            req.pos[1] = src[1];
            req.pos[2] += src[2];
            req.sprite = (func_150ADA20() & 0xF) + 0x19;
            req.life = (func_150ADA20() % 101U) + 100;
            req.size[0] = req.size[1] = func_150ADA68() * 205.0f + 98.0f;
            r0 = func_150ADA20();
            r1 = func_150ADA20();
            rf = func_150ADA68();
            func_15143794(r0 & 0xFF, ((u32)r1 % 35U) - 0x40, rf * 10.0f + 10.0f, req.vel);
            req.fade = func_150ADA68() * D_800A918C + D_800A9188;
            func_151307F0((s32)&req, 1, 0, 0, fx[0xC], fx[1]);
            mv[6] -= 1.0f;
        } while (mv[6] > 1.0f);
    }
    return 1;
}
