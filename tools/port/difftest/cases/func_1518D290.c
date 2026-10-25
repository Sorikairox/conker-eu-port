#ifdef NON_MATCHING
/* P292 */
void func_1514373C(f32, f32, f32 *, f32 *);
void func_15145DB4(u8 *, f32 *, f32 *, s32);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void *memcpy(void *, const void *, s32);

/* rodata D_800A7830..3C (bit-exact copies: the NM link drops this file's .late_rodata) */
static const f32 sRingPi[1] = { 3.1415927f };       /* 0x40490FDB */
static const f32 sRingU24[1] = { 1.040569f };       /* 0x3F85315D */
static const f32 sRingExtra[1] = { 0.853381f };     /* 0x3F5A772D */
static const f32 sRingScale[1] = { 0.001f };        /* 0x3A83126F */

// object_ring_burst_particles: spawns 25..35 particles (texture 0x6C, kind 0x200005) on a half ring around obj:
// the ring points (angle pi..2pi, radius 114, then x + 111, y = -90; the last point is the centre (111, -90, 0)) go
// through obj's transform (func_15145DB4) into world space, and each particle starts on its point and moves away
// from the centre with a random speed, size, life, alpha and flip bits, for owner / ownerArg (func_151307F0); each
// new particle's +0xA8 gets 0.853381f. Does nothing when an allocation fails (the first buffer is then leaked).
void func_1518D290(u8 *obj, u8 owner, s32 ownerArg) {
    struct {
        s32 handlers;   /* +0x00 */
        s32 u04;
        s16 texSet;     /* +0x08 */
        s16 life;       /* +0x0A */
        s32 u0C;
        s32 u10;
        u8 color[4];    /* +0x14 */
        u8 u18[3];
        u8 alpha;       /* +0x1B */
        u8 u1C;
        u8 texture;     /* +0x1D */
        s16 fadeStart;  /* +0x1E */
        s16 fadeRate;   /* +0x20 */
        s16 u22;
        f32 u24;
        f32 halfW;      /* +0x28 */
        f32 halfH;      /* +0x2C */
        s32 pos[3];     /* +0x30 */
        f32 angle[3];   /* +0x3C */
        f32 vel[3];     /* +0x48 */
        f32 value;      /* +0x54 */
        s32 flags;      /* +0x58 */
        s32 u5C;
        u8 draw;        /* +0x60 */
        u8 update;      /* +0x61 */
        u8 blend;       /* +0x62 */
        s8 u63;
        s8 u64;
        u8 u65;
        u8 u66;
    } req;
    f32 extra;
    f32 *ring;
    f32 *world;
    f32 *pt;
    f32 *centre;
    f32 speed;
    s32 flipA;
    s32 flipB;
    s32 life;
    u8 *p;
    s16 count;
    s16 i;

    count = func_150ADA20() % 11U + 25;
    if (count <= 0) {
        return;
    }
    ring = (f32 *) func_10003C6C((count + 1) * 12, 3, 1, 0, 1);
    world = (f32 *) func_10003C6C((count + 1) * 12, 3, 1, 0, 1);
    if (ring == NULL || world == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        pt = ring + i * 3;
        func_1514373C(func_150ADA68() * sRingPi[0] + sRingPi[0], 114.0f, &pt[0], &pt[2]);
        pt[1] = -90.0f;
        pt[0] = pt[0] + 111.0f;
    }
    pt = ring + count * 3;
    pt[0] = 111.0f;
    pt[1] = -90.0f;
    pt[2] = 0.0f;
    func_15145DB4(obj, ring, world, count + 1);

    req.u24 = sRingU24[0];
    extra = sRingExtra[0];
    req.u18[2] = 0x62;
    req.texture = 0x6C;
    req.texSet = 0x5103;
    req.handlers = 0x200005;
    req.color[0] = 0xE7;
    req.color[1] = 0xE7;
    req.color[2] = 0xB6;
    req.u18[0] = 0x9E;
    req.u18[1] = 0x9E;
    req.u04 = 0;
    req.u0C = 0;
    req.u10 = 0;
    req.color[3] = 0xFF;
    req.u1C = 0xFF;
    req.angle[0] = 0.0f;
    req.angle[1] = 0.0f;
    req.angle[2] = 0.0f;
    req.fadeStart = 0x19;
    req.fadeRate = 0xA;
    req.draw = 8;
    req.update = 6;
    req.blend = 0x10;
    req.u63 = -1;
    req.u64 = -1;
    req.u65 = 0;
    req.flags = 0x80CE07;
    centre = world + count * 3;
    for (i = 0; i < count; i++) {
        flipB = (func_150ADA20() & 1) ? 0x80 : 0;
        flipA = (func_150ADA20() & 1) ? 0x40 : 0;
        req.flags = (req.flags & ~0xC0) | (flipA | flipB);
        speed = (func_150ADA68() * 202.0f + 250.0f) * sRingScale[0];
        life = func_150ADA20() % 26U + 25;
        req.u22 = life;
        req.life = life;
        req.halfH = req.halfW = func_150ADA68() * 105.0f + 150.0f;
        pt = world + i * 3;
        req.pos[0] = ((s32 *) pt)[0];
        req.pos[1] = ((s32 *) pt)[1];
        req.pos[2] = ((s32 *) pt)[2];
        req.vel[0] = (pt[0] - centre[0]) * speed;
        req.vel[1] = (pt[1] - centre[1]) * speed;
        req.vel[2] = (pt[2] - centre[2]) * speed;
        req.value = (func_150ADA68() * 880.0f + 13.0f) * sRingScale[0];
        req.alpha = func_150ADA20() % 176U + 0x50;
        p = (u8 *) func_151307F0((s32) &req, 1, 0, 4, owner, ownerArg);
        if (p != NULL) {
            memcpy(p + 0xA8, &extra, 4);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BAAA0/func_1518D290.s")
#endif
