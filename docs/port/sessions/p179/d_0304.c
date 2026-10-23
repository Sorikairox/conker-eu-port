extern u32 D_800A2530[4];
void func_15145974(f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_151307F0(s32 *, s32, s32, s32, s32, s32);

// gun_shot_sparks: P179: 10..18 kind-1 spark particles (func_151307F0 block, 0x67 bytes) at `pos`, sprayed around
/* the shot direction `dir` (its yaw from func_15145974; the pitch is forced to 0) within 21 / 256 turns: colour
 * D_800A2530[random 0..3], life 10..22, alpha 155..255, size 75 + random x 155, speed 20 + random x 20,
 * gravity -0.657 + random x 0.621, random mirror flags 0x80 / 0x40 on flags 0x4C207; owner / owner arg `flag` /
 * `arg3`. */
void func_15100304(f32 *pos, f32 *dir, u8 flag, s32 arg3) {
    struct {
        s32 u00;
        s32 u04;
        s16 u08;
        s16 life;      /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 u14[7];
        u8 alpha;      /* +0x1B */
        u8 u1C;
        u8 colour;     /* +0x1D */
        s16 u1E;
        s16 u20;
        s16 u22;
        f32 u24;
        f32 sizeX;     /* +0x28 */
        f32 sizeY;     /* +0x2C */
        f32 pos[3];    /* +0x30 */
        f32 u3C[3];
        f32 vel[3];    /* +0x48 */
        f32 gravity;   /* +0x54 */
        s32 flags;     /* +0x58 */
        s32 u5C;
        u8 u60;
        u8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
    } p;
    u32 colours[4];
    f32 yaw;
    f32 pitch;
    s32 n;
    s16 yawBase;
    s16 pitchBase;
    u32 r1;
    u32 r2;
    s32 mirrorX;
    s32 mirrorY;
    f32 size;

    n = (u32) func_150ADA20() % 9 + 10;
    p.u08 = 0x2203;
    p.u00 = 0x200005;
    p.u04 = 0;
    p.u0C = 0;
    p.u10 = 0;
    p.u14[0] = 0xFF;
    p.u14[1] = 0xFF;
    p.u14[2] = 0xFF;
    p.u14[3] = 0xFF;
    p.u14[4] = 0xFF;
    p.u14[5] = 0xFF;
    p.u14[6] = 0xFF;
    p.u1C = 0xFF;
    p.pos[0] = pos[0];
    p.pos[1] = pos[1];
    p.pos[2] = pos[2];
    p.u3C[0] = ((f32 *) D_800A5860)[0];
    p.u3C[1] = ((f32 *) D_800A5860)[1];
    p.u3C[2] = ((f32 *) D_800A5860)[2];
    p.u1E = 7;
    p.u20 = 0x24;
    p.u22 = 1;
    p.flags = 0x4C207;
    p.u60 = 0;
    p.u61 = 7;
    p.u62 = -1;
    p.u63 = -1;
    p.u64 = -1;
    p.u65 = 0;
    p.u5C = 0;
    p.u66 = 0xFF;
    p.u24 = 1.0f;
    func_15145974(dir, &yaw, &pitch);
    pitch = 0.0f;
    yawBase = ((s16) (yaw * 182.04445f) >> 8) - 0x8A;
    pitchBase = ((s16) (pitch * 182.04445f) >> 8) - 0x8A;
    do {
        colours[0] = D_800A2530[0];
        colours[1] = D_800A2530[1];
        colours[2] = D_800A2530[2];
        colours[3] = D_800A2530[3];
        p.colour = colours[func_150ADA20() & 3];
        p.life = (u32) func_150ADA20() % 13 + 10;
        p.alpha = (u32) func_150ADA20() % 101 + 0x9B;
        size = func_150ADA68() * 155.0f + 75.0f;
        p.sizeX = size;
        p.sizeY = size;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794(r1 % 21 + yawBase, r2 % 21 + pitchBase, func_150ADA68() * 20.0f + 20.0f, p.vel);
        p.gravity = func_150ADA68() * 0.62100005f + -0.657f;
        p.flags &= ~0xC0;
        mirrorX = (func_150ADA20() & 1) ? 0x80 : 0;
        mirrorY = (func_150ADA20() & 1) ? 0x40 : 0;
        p.flags |= mirrorY | mirrorX;
        func_151307F0((s32 *) &p, 1, 0, 0, flag, arg3);
        n--;
    } while (n > 0);
}
