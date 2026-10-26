#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15171E60(f32 x, f32 y, f32 z, f32 r, s32 base, f32 scale, s32 colour, s32 n, u8 kind, s32 owner);

#ifdef NON_MATCHING
s32 func_1518C900(s32);
void node_spawn_model_fx(u8 *arg0, u8 arg1, s32 arg2);

/* node_spawn_model_fx's debris template (the same layout as Debris714BC below) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 spin[3];
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 scale[3];
    /* 0x3C */ s32 life;
    /* 0x40 */ s32 model;
    /* 0x44 */ s32 u44; /* not set */
    /* 0x48 */ f32 u48[3];
    /* 0x54 */ u8 u54[6];
    /* 0x5A */ u8 id;
    /* 0x5B */ u8 u5B;
    /* 0x5C */ u8 u5C;
    /* 0x5D */ u8 u5D;
} Debris71100;

extern f32 D_800A7270[6][3]; /* piece offsets */
extern u8 D_800A7360[6];     /* piece ids when flags & 2 */

// crate_break_pieces: breaks the object into 6 node_spawn_model_fx debris pieces at the object position (+0x10 / +0x12 /
// +0x14) plus the D_800A7270 offsets. Piece id: D_800A7360[i] if flags & 2, else id + i if flags & 1, else id;
// model func_1518C900(id). Spin = offset * 0.08 (+7 on |y|) plus random (rand >> 16) / 16384, u24 / u28 / u2C random
// (rand >> 16) * 1.25 / 16384, scale 1, life 60. Then a ring of 10 sparks (func_15171E60) 80 below the object, and
// +0x6E = 1. kind / owner go to every spawn; arg2 is the template's +0x5B byte.
void func_15171100(u8 *obj, s32 id, s32 arg2, s32 flags, s32 kind, s32 owner) {
    Debris71100 t;
    f32 (*off)[3] = D_800A7270;
    f32 x, y, z;
    s32 piece;
    s32 i;

    x = *(s16 *) (obj + 0x10);
    y = *(s16 *) (obj + 0x12);
    z = *(s16 *) (obj + 0x14);
    t.vel[0] = 0.0f;
    t.vel[1] = 0.0f;
    t.vel[2] = 0.0f;
    t.scale[0] = 1.0f;
    t.scale[1] = 1.0f;
    t.scale[2] = 1.0f;
    t.life = 0x3C;
    t.u48[0] = 0.3f;  /* D_800A7368 */
    t.u48[1] = -0.7f; /* D_800A736C */
    t.u48[2] = -0.2f; /* D_800A7370 */
    t.u54[0] = 2;
    t.u54[1] = 0xFF;
    t.u54[2] = 0;
    t.u54[3] = 0;
    t.u54[4] = 0;
    t.u54[5] = 0x3C;
    t.u5B = arg2;
    t.u5C = 0;
    t.u5D = 0;
    for (i = 0; i < 6; i++, off++) {
        if (flags & 2) {
            piece = D_800A7360[i];
        } else if (flags & 1) {
            piece = id + i;
        } else {
            piece = id;
        }
        t.model = func_1518C900(piece);
        t.pos[0] = (*off)[0] + x;
        t.pos[1] = (*off)[1] + y;
        t.pos[2] = (*off)[2] + z;
        t.id = piece;
        t.spin[0] = (*off)[0] * 0.08f;               /* D_800A7374 */
        t.spin[1] = fabsf((*off)[1]) * 0.08f + 7.0f;
        t.spin[2] = (*off)[2] * 0.08f;
        t.spin[0] += (func_150ADA20() >> 16) * 0.00006103515625f;
        t.spin[1] += (func_150ADA20() >> 16) * 0.00006103515625f;
        t.spin[2] += (func_150ADA20() >> 16) * 0.00006103515625f;
        t.u24 = (func_150ADA20() >> 16) * 0.0000762939453125f;
        t.u28 = (func_150ADA20() >> 16) * 0.0000762939453125f;
        t.u2C = (func_150ADA20() >> 16) * 0.0000762939453125f;
        node_spawn_model_fx((u8 *) &t, kind, owner);
    }
    func_15171E60(x, y - 80.0f, z, 70.0f, 500, 0.00457763671875f, 0, 10, kind, owner);
    obj[0x6E] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171100.s")
#endif

void func_15171434(s32 arg0, u8 arg1, s32 arg2) {
    switch (D_800BE9F0) {
    case 2:
        func_15171100((u8 *) arg0, 1, 1, 1, arg1, arg2);
        break;
    case 16:
        func_15171100((u8 *) arg0, 0xA9, 8, 0, arg1, arg2);
        break;
    }
}

#ifdef NON_MATCHING
s32 func_1518C900(s32);
void node_spawn_model_fx(u8 *arg0, u8 arg1, s32 arg2);

/* D_800A72B8: the 6 pieces (model id, offset, velocity) */
typedef struct {
    u16 model;
    u8 pad2[2];
    f32 offset[3];
    f32 vel[3];
} Piece714BC;
extern Piece714BC D_800A72B8[6];

/* node_spawn_model_fx's debris template */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 spin[3];
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 scale[3];
    /* 0x3C */ s32 life;
    /* 0x40 */ s32 model;
    /* 0x44 */ s32 u44; /* not set */
    /* 0x48 */ f32 u48[3];
    /* 0x54 */ u8 u54[6];
    /* 0x5A */ u8 id;
    /* 0x5B */ u8 u5B;
    /* 0x5C */ u8 u5C;
    /* 0x5D */ u8 u5D;
} Debris714BC;

// barrel_break_pieces: breaks the object into the 6 pieces of D_800A72B8 (node_spawn_model_fx debris, model
// func_1518C900(id)) at the object position (+0x10 / +0x12 / +0x14) plus each piece offset, with the piece velocity,
// spin from the offset (x, |y|, z times 0.09 / 0.23 / 0.09), u24 = vel x * 0.1, random u28 -2..2 / u2C -5..5,
// scale 2, life 60; then sets +0x6E to 1. kind / arg2 go to node_spawn_model_fx.
void func_151714BC(u8 *obj, u8 kind, s32 arg2) {
    Debris714BC t;
    Piece714BC *pc = D_800A72B8;
    f32 x, y, z;
    s32 i;

    t.u5C = 2;
    t.u5D = 1;
    t.u5B = 6;
    t.u54[5] = 0;
    x = *(s16 *) (obj + 0x10);
    y = *(s16 *) (obj + 0x12);
    z = *(s16 *) (obj + 0x14);
    t.vel[0] = 0.0f;
    t.vel[1] = 0.0f;
    t.vel[2] = 0.0f;
    t.scale[0] = 2.0f;
    t.scale[1] = 2.0f;
    t.scale[2] = 2.0f;
    t.life = 0x3C;
    t.u54[0] = 2;
    t.u54[1] = 0xFF;
    t.u54[2] = 0;
    t.u54[3] = 0;
    t.u54[4] = 0;
    t.u48[0] = 0.3f;  /* D_800A7378 */
    t.u48[1] = -0.7f; /* D_800A737C */
    t.u48[2] = -0.2f; /* D_800A7380 */
    for (i = 0; i < 6; i++, pc++) {
        t.model = func_1518C900(pc->model);
        t.id = pc->model;
        t.pos[0] = pc->offset[0] + x;
        t.pos[1] = pc->offset[1] + y;
        t.pos[2] = pc->offset[2] + z;
        t.spin[0] = pc->offset[0] * 0.09f;        /* D_800A738C */
        t.spin[1] = fabsf(pc->offset[1]) * 0.23f; /* D_800A7388 */
        t.spin[2] = pc->offset[2] * 0.09f;
        t.vel[0] = pc->vel[0];
        t.u24 = t.vel[0] * 0.1f;                  /* D_800A7384 */
        t.vel[1] = pc->vel[1];
        t.vel[2] = pc->vel[2];
        t.u28 = func_150ADA68() * 4.0f - 2.0f;
        t.u2C = func_150ADA68() * 10.0f - 5.0f;
        node_spawn_model_fx((u8 *) &t, kind, arg2);
    }
    obj[0x6E] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_151714BC.s")
#endif

void func_15171734(u8 *arg0) {
    if (arg0[4] == 0x33) {
        func_150C3D5C(arg0);
    }
    func_15060F28(arg0, 1);
}

#ifdef NON_MATCHING
s32 func_1518C900(s32);
void node_spawn_model_fx(u8 *arg0, u8 arg1, s32 arg2);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A7390_c[1] = { -0.2f };        /* 0xBE4CCCCD */
static const f32 D_800A7394_c[1] = { 6.1035157e-06f }; /* 0x36CCCCCD */
static const f32 D_800A7398_c[1] = { 0.8f };         /* 0x3F4CCCCD */
static const f32 D_800A739C_c[1] = { 6.666667f };    /* 0x40D55556 */

/* node_spawn_model_fx's debris template (the same layout as Debris714BC above) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 spin[3];
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 u28;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 scale[3];
    /* 0x3C */ s32 life;
    /* 0x40 */ s32 model;
    /* 0x44 */ s32 u44; /* not set */
    /* 0x48 */ f32 u48[3];
    /* 0x54 */ u8 u54[6];
    /* 0x5A */ u8 id;
    /* 0x5B */ u8 u5B;
    /* 0x5C */ u8 u5C;
    /* 0x5D */ u8 u5D;
} Debris71770;

// debris_cloud_spawn: spawns count node_spawn_model_fx debris pieces of model func_1518C900(id) scattered around
// (x, y, z) by +-spread/2 (random (rand >> 16) * spread / 65536 per axis), no velocity, random spin
// (x / z: (rand >> 16) * 15 / 65536, y: (rand & 0xFFFF) * spinY * 6.1e-6 + spinY * 0.8), random u24 / u28 / u2C
// ((rand >> 16) * 10 / 65536) and a random scale per axis between scaleMin and scaleMax; u54[5] = scale sum * 6.67
// + 20. u48 = {drift * -0.75, drift, -0.2}; life / u5B / kind / owner pass through.
void func_15171770(s32 count, s32 id, f32 x, f32 y, f32 z, f32 spinY, f32 scaleMin, f32 scaleMax, f32 spread,
                   s32 u5B, s32 life, f32 drift, s32 kind, s32 owner) {
    Debris71770 t;
    f32 spinYRange;
    f32 spinYMin;
    f32 scaleRange;
    f32 scale2;
    s32 i;

    scaleRange = scaleMax - scaleMin;
    spread *= 1.5258789e-05f; /* 1 / 65536 */
    spinYRange = spinY * D_800A7394_c[0];
    spinYMin = spinY * D_800A7398_c[0];
    t.vel[0] = 0.0f;
    t.vel[1] = 0.0f;
    t.vel[2] = 0.0f;
    t.u48[0] = drift * -0.75f;
    t.u48[1] = drift;
    t.u48[2] = D_800A7390_c[0];
    t.u54[0] = 2;
    t.u54[1] = 0xFF;
    t.u54[2] = 0;
    t.u54[3] = 0;
    t.u54[4] = 0;
    t.id = id;
    t.u5B = u5B;
    t.u5C = 1;
    t.u5D = 1;
    t.life = life;
    for (i = 0; i < count; i++) {
        t.pos[0] = (func_150ADA20() >> 16) * spread + x;
        t.pos[1] = (func_150ADA20() >> 16) * spread + y;
        t.pos[2] = (func_150ADA20() >> 16) * spread + z;
        t.model = func_1518C900(id);
        t.spin[0] = (func_150ADA20() >> 16) * 0.00022888184f;
        t.spin[1] = (u32) (func_150ADA20() & 0xFFFF) * spinYRange + spinYMin;
        t.spin[2] = (func_150ADA20() >> 16) * 0.00022888184f;
        t.u24 = (func_150ADA20() >> 16) * 0.00015258789f;
        t.u28 = (func_150ADA20() >> 16) * 0.00015258789f;
        t.u2C = (func_150ADA20() >> 16) * 0.00015258789f;
        t.scale[0] = (u32) (func_150ADA20() & 0xFFFF) * 1.5258789e-05f * scaleRange + scaleMin;
        t.scale[1] = (u32) (func_150ADA20() & 0xFFFF) * 1.5258789e-05f * scaleRange + scaleMin;
        scale2 = (u32) (func_150ADA20() & 0xFFFF) * 1.5258789e-05f * scaleRange + scaleMin;
        t.u54[5] = (u32) ((t.scale[0] + t.scale[1] + scale2) * D_800A739C_c[0] + 20.0f);
        t.scale[2] = scale2;
        node_spawn_model_fx((u8 *) &t, kind, owner);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171770.s")
#endif

void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC);
extern f32 D_800A73A0;
extern f32 D_800A73A4;

void func_15171B70(u8 *arg0, u8 arg1, s32 arg2) {
    switch (arg0[0x72]) {
    case 0xEB:
        func_15171D6C((s16 *)arg0, 400.0f, 500.0f, 0.0f, D_800A73A0, 0.0f, 2, 5, 20, 20, 1.0f, arg1, arg2);
        break;
    case 0xF6:
        func_15171D6C((s16 *)arg0, 200.0f, 400.0f, -1800.0f, -1000.0f, -1200.0f, 2, 5, 4, 10, 1.0f, arg1, arg2);
        break;
    case 0xF8:
        func_15171D6C((s16 *)arg0, 100.0f, 160.0f, -2500.0f, D_800A73A4, 0.0f, 2, 5, 4, 4, 0.5f, arg1, arg2);
        break;
    case 0xF9:
        func_15171D6C((s16 *)arg0, 200.0f, 100.0f, 100.0f, -300.0f, 0.0f, 1, 5, 4, 4, 1.0f, arg1, arg2);
        break;
    }
}

void func_15170648(f32 *, f32, f32, s32, f32, s32, s32, s32, u8, s32);
void func_15171D6C(s16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, u8 argB, s32 argC) {
    f32 pts[4][3];
    f32 x;
    f32 y;
    f32 z;

    x = arg0[8] + arg3;
    y = arg0[9] + arg4;
    z = arg0[10] + arg5;
    pts[0][0] = arg1 + x;
    pts[0][1] = y;
    pts[0][2] = arg2 + z;
    pts[1][0] = x - arg1;
    pts[1][1] = y;
    pts[1][2] = arg2 + z;
    pts[2][0] = x - arg1;
    pts[2][1] = y;
    pts[2][2] = z - arg2;
    pts[3][0] = arg1 + x;
    pts[3][1] = y;
    pts[3][2] = z - arg2;
    func_15170648(pts[0], x, z, arg7, argA, arg6, arg8, arg9, argB, argC);
}

#ifdef NON_MATCHING
f32 func_150489B0(u8);
void func_1516DA58(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA,
                   u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14,
                   u8 arg15, u8 arg16, s16 arg17, s16 arg18, u8 arg19, s16 arg1A, s32 arg1B, s32 arg1C, u8 arg1D,
                   s32 arg1E);

typedef struct {
    u8 rgb[3];
} Colour71E60;
extern Colour71E60 D_8008CFC0; /* {0x45, 0x53, 0x68} */

// spark_ring_spawn: spawns count type-0xD particles (func_1516DA58) evenly around a circle of the given radius
// around (x, z) at height y; each moves outwards (200 * sin / cos of its angle), colour D_8008CFC0 (the asm copies
// it into a one-entry stack table indexed by colour; every caller passes 0), speed rand16 * speedScale + speedBase,
// life 10..25, spread 100 + rand16 / 65536.
void func_15171E60(f32 x, f32 y, f32 z, f32 radius, s32 speedBase, f32 speedScale, s32 colour, s32 count, u8 kind,
                   s32 owner) {
    Colour71E60 colours[1];
    u8 *col;
    s32 angle;
    s32 step;
    s32 i;
    s16 py;
    f32 s, c;
    f32 pz;
    f32 spread;
    s32 speed;
    s32 vx, vz;
    s32 life;

    colours[0] = D_8008CFC0;
    if (count <= 0) {
        return;
    }
    step = 0xFFFF / count;
    py = (s32) y;
    col = colours[colour].rgb;
    for (i = 0, angle = 0; i != count; i++, angle += step) {
        s = func_15048A40((angle >> 8) & 0xFF);
        c = func_150489B0((angle >> 8) & 0xFF);
        pz = radius * c + z;
        vz = (s32) (200.0f * c);
        spread = (func_150ADA20() & 0xFFFF) * 0.0000152587890625f + 100.0f;
        speed = (s32) ((func_150ADA20() & 0xFFFF) * speedScale + (f32) speedBase);
        life = (func_150ADA20() & 0xF) + 10;
        vx = (s32) (200.0f * s);
        func_1516DA58((s32) (radius * s + x), py, (s32) pz, 0xD, 0, col[0], col[1], col[2], 0, 0, 0, 0, 2,
                      (vx >> 8) & 0xFF, vx & 0xFF, (vz >> 8) & 0xFF, vz & 0xFF, 0, 0, 5, 0, 0, 0, speed, speed,
                      life, (s32) spread, 0, 0, kind, owner);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19E910/func_15171E60.s")
#endif

#ifdef NON_MATCHING
void func_150AEEB0(struct127 *, u8);
#else
s32 func_150AEEB0(struct127 *, u8);
#endif
#ifdef NON_MATCHING
void func_150BDC20(struct127 *, u8, s32);
#else
s32 func_150BDC20(struct127 *, u8, s32);
#endif
s32 func_150CE0C0(struct127 *, u8, s32);

void func_15172164(struct127 *arg0, u8 arg1) {
    switch (arg0->id) {
    case 0x13:
    case 0x23:
        func_150AEEB0(arg0, arg1);
        func_10010154(0x69, arg0, 0x7D00, 0xC8, 0x7D0);
        break;
    case 0x1E:
        func_150BDC20(arg0, arg1, 1);
        break;
    case 0x54:
        func_150CE0C0(arg0, arg1, 1);
        break;
    }
}
