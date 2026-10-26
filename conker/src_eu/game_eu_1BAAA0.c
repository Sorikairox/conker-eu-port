#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} struct_eu_vec3;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ struct_eu_vec3 unk34;
} struct_eu_1BAAA0_c;

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ struct_eu_1BAAA0_c *unk2C;
} struct_eu_1BAAA0_d;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8 pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x28];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0x2C];
    /* 0x089 */ s8 unk89;
    /* 0x08A */ u8 pad8A[0x9A];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 unk126;
    /* 0x128 */ u8 pad128[0x2C];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
} struct_eu_1BAAA0_e;

typedef struct {
    u8 unk0[4];
} struct_eu_bytes4b;

extern struct_eu_bytes4b D_800A78B4;

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;


/* P292 */
void vec2_from_angle_rad(f32, f32, f32 *, f32 *);
void xform_points_array(u8 *, f32 *, f32 *, s32);
s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void *memcpy(void *, const void *, s32);

/* rodata D_800A7830..3C (bit-exact copies: the NM link drops this file's .late_rodata) */
static const f32 sRingPi[1] = { 3.1415927f };       /* 0x40490FDB */
static const f32 sRingU24[1] = { 1.040569f };       /* 0x3F85315D */
static const f32 sRingExtra[1] = { 0.853381f };     /* 0x3F5A772D */
static const f32 sRingScale[1] = { 0.001f };        /* 0x3A83126F */

// object_ring_burst_particles: spawns 25..35 particles (texture 0x6C, kind 0x200005) on a half ring around obj:
// the ring points (angle pi..2pi, radius 114, then x + 111, y = -90; the last point is the centre (111, -90, 0)) go
// through obj's transform (xform_points_array) into world space, and each particle starts on its point and moves away
// from the centre with a random speed, size, life, alpha and flip bits, for owner / ownerArg (particle_spawn_ex); each
// new particle's +0xA8 gets 0.853381f. Does nothing when an allocation fails (the first buffer is then leaked).
/* was func_1518D290 */
void object_ring_burst_particles(u8 *obj, u8 owner, s32 ownerArg) {
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

    count = random_int() % 11U + 25;
    if (count <= 0) {
        return;
    }
    ring = (f32 *) heap_alloc_tagged((count + 1) * 12, 3, 1, 0, 1);
    world = (f32 *) heap_alloc_tagged((count + 1) * 12, 3, 1, 0, 1);
    if (ring == NULL || world == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        pt = ring + i * 3;
        vec2_from_angle_rad(random_float() * sRingPi[0] + sRingPi[0], 114.0f, &pt[0], &pt[2]);
        pt[1] = -90.0f;
        pt[0] = pt[0] + 111.0f;
    }
    pt = ring + count * 3;
    pt[0] = 111.0f;
    pt[1] = -90.0f;
    pt[2] = 0.0f;
    xform_points_array(obj, ring, world, count + 1);

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
        flipB = (random_int() & 1) ? 0x80 : 0;
        flipA = (random_int() & 1) ? 0x40 : 0;
        req.flags = (req.flags & ~0xC0) | (flipA | flipB);
        speed = (random_float() * 202.0f + 250.0f) * sRingScale[0];
        life = random_int() % 26U + 25;
        req.u22 = life;
        req.life = life;
        req.halfH = req.halfW = random_float() * 105.0f + 150.0f;
        pt = world + i * 3;
        req.pos[0] = ((s32 *) pt)[0];
        req.pos[1] = ((s32 *) pt)[1];
        req.pos[2] = ((s32 *) pt)[2];
        req.vel[0] = (pt[0] - centre[0]) * speed;
        req.vel[1] = (pt[1] - centre[1]) * speed;
        req.vel[2] = (pt[2] - centre[2]) * speed;
        req.value = (random_float() * 880.0f + 13.0f) * sRingScale[0];
        req.alpha = random_int() % 176U + 0x50;
        p = (u8 *) particle_spawn_ex((s32) &req, 1, 0, 4, owner, ownerArg);
        if (p != NULL) {
            memcpy(p + 0xA8, &extra, 4);
        }
    }
}
