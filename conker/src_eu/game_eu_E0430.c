#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P197 */
s32 debris_spray_spawn(void *spray, s32 mode, u8 view, s32 arg3);
void spawn_arc_emit(f32 x, f32 y, f32 z, f32 r, s16 yaw, s16 a0, s16 a1, s16 count, u8 kind, s32 arg9, f32 argA,
                   s32 argB, u8 argC);
void emit_line_sparks_by_angles(u8 *arg0, u8 arg1);
void emit_sparks_by_angles_b(u8 *arg0, s32 arg1);
u8 *water_jet_spawn(s32 *arg0, u8 *arg1, s16 arg2);

extern s32 D_800BEE08;

/* the three pipes (position, facing angle) */
typedef struct {
    f32 pos[3];
    u8 angle;
    u8 pad[3];
} PipeSpot;
static const PipeSpot D_8009FCF0[3] = {
    { { 975.0f, 351.0f, 1723.0f }, 0x94 },
    { { 1005.0f, 351.0f, -1706.0f }, 0xEA },
    { { -1980.0f, 351.0f, -17.0f }, 0x3F },
};

// pipe_explode_effects: P197 (difftest as a void variant, d_2c20.c): the effects of pipe `pipe` (0..2, D_8009FCF0: position and facing angle) bursting in
// view `view` ("../Effects/PipeExploded/pipeexploded.c"): camera_shake_start on the current player's state (7, 1), a spray
// of 3..4 pieces (debris_spray_spawn), 1..2 debris bursts (spawn_arc_emit, radius 31..104, 4..6 pieces), a smoke cloud
// (emit_line_sparks_by_angles), two spark bursts (emit_sparks_by_angles_b), clears the pipe's two earlier effects of type 0x17
// (effect_nodes_broadcast, keys 2 * pipe and 2 * pipe + 1), a water / steam jet 150 units in front of the pipe
// (water_jet_spawn, 20) and the sounds 0xE7 / 0x22 at the pipe (sound_play_at).
/* was func_150B2C20 */
s32 pipe_explode_effects(s32 pipe, s32 view) {
    struct {
        s16 count;       /* 0x00 */
        u8 pad2[2];
        f32 pos[3];      /* 0x04 */
        s16 u10;         /* 0x10 */
        u8 pad12[2];
        f32 u14;         /* 0x14 */
        s16 u18[4];      /* 0x18 */
        f32 u20[12];     /* 0x20 */
        f32 u50;         /* 0x50 */
        u8 u54;          /* 0x54 */
        u8 u55;          /* 0x55 */
        s16 u56;         /* 0x56 */
        s16 u58;         /* 0x58 */
        u8 pad5A[2];
    } spray;
    struct {
        s16 base, range; /* 0x00 particle count base + rand % (range + 1) */
        f32 pos[3];      /* 0x04 */
        s16 u10[4];      /* 0x10 */
        f32 u18[4];      /* 0x18 */
        u8 c[8];         /* 0x28 */
        u8 u30;          /* 0x30 */
        u8 pad31;
        s16 u32, u34;    /* 0x32 */
        u16 u36;         /* 0x36 */
        f32 u38, u3C;    /* 0x38 */
        u8 u40, u41;     /* 0x40 */
        s16 u42, u44;    /* 0x42 */
        u8 u46;          /* 0x46 */
    } smoke;
    struct {
        f32 pos[3];      /* 0x00 */
        f32 u0C[6];      /* 0x0C */
        s16 u24[10];     /* 0x24 */
        u8 u38, u39;     /* 0x38 */
        u8 pad3A[2];
        s32 u3C[6];      /* 0x3C */
        u8 u54, u55;     /* 0x54 */
    } sparks;
    struct {
        f32 vel[3];      /* 0x00 */
        f32 u0C;         /* 0x0C */
        u8 u10;          /* 0x10 */
        u8 pad11[3];
        f32 u14, u18;    /* 0x14 */
        u8 u1C;          /* 0x1C */
        u8 pad1D[3];
        f32 u20;         /* 0x20 */
        u8 u24;          /* 0x24 */
        u8 pad25;
        s16 u26;         /* 0x26 */
        f32 u28, u2C;    /* 0x28 */
        u8 u30[6];       /* 0x30 */
        s16 u36;         /* 0x36 */
        u8 u38;          /* 0x38 */
        u8 pad39[3];
        f32 u3C;         /* 0x3C */
    } jet;
    f32 at[3];
    u8 key[8];
    const PipeSpot *p;
    s16 n;
    f32 r, s, c;

    camera_shake_start((struct108 *) ((u8 *) D_800DBFF0 + D_800BEE08 * 0x9A0), 7, 1);

    /* spray of pieces */
    spray.count = (random_int() & 1) + 3;
    p = &D_8009FCF0[(u8) pipe];
    spray.pos[0] = p->pos[0];
    spray.pos[1] = p->pos[1];
    spray.pos[2] = p->pos[2];
    spray.u10 = 300;
    spray.u14 = 170.0f;
    spray.u18[0] = p->angle - 0x20;
    spray.u18[1] = 0x41;
    spray.u18[2] = -0x28;
    spray.u18[3] = 0x50;
    spray.u20[0] = 16.2f;
    spray.u20[1] = 17.6f;
    spray.u20[2] = 19.300001f;
    spray.u20[3] = 21.300001f;
    spray.u20[4] = 0.0f;
    spray.u20[5] = 0.0f;
    spray.u20[6] = 0.0f;
    spray.u20[7] = 0.467f;
    spray.u20[8] = 0.514f;
    spray.u20[9] = -1.0f;
    spray.u20[10] = -2.6000001f;
    spray.u20[11] = -5.0f;
    spray.u50 = 10.0f;
    spray.u54 = 1;
    spray.u55 = 0;
    spray.u56 = 0x32;
    spray.u58 = 0x19;
    debris_spray_spawn(&spray, 0, view, 1);

    /* debris bursts */
    n = (random_int() & 1) + 1;
    while (n-- != 0) {
        r = random_float() * 73.0f + 31.0f;
        spawn_arc_emit(p->pos[0], p->pos[1], p->pos[2], r, p->angle + 0x40, 0, 0xFF, (u32) random_int() % 3 + 4,
                      9, 0, 0.009615385f, 0, view);
    }

    /* smoke */
    smoke.base = 0x1E;
    smoke.range = 0xF;
    smoke.pos[0] = p->pos[0];
    smoke.pos[1] = p->pos[1];
    smoke.pos[2] = p->pos[2];
    smoke.u10[0] = p->angle - 0x40;
    smoke.u10[1] = -0x2D;
    smoke.u10[2] = 0x80;
    smoke.u10[3] = 0x5A;
    smoke.u18[0] = 6.0f;
    smoke.u18[1] = 2.55f;
    smoke.u18[2] = 2.7f;
    smoke.u18[3] = 3.4199998f;
    smoke.c[0] = 0xFF;
    smoke.c[1] = 0xFF;
    smoke.c[2] = 0xFF;
    smoke.c[3] = 0xFF;
    smoke.c[4] = 0xFF;
    smoke.c[5] = 0xFF;
    smoke.c[6] = 0xFF;
    smoke.c[7] = 0xFF;
    smoke.u30 = 9;
    smoke.u32 = 0x10;
    smoke.u34 = 0x16;
    smoke.u36 = 0x1601;
    smoke.u38 = 4.14f;
    smoke.u3C = 4.8599997f;
    smoke.u40 = 0x7F;
    smoke.u41 = 0x7F;
    smoke.u42 = 0xA;
    smoke.u44 = 0x19;
    smoke.u46 = 0;
    emit_line_sparks_by_angles((u8 *) &smoke, view);

    /* sparks, twice */
    sparks.pos[0] = p->pos[0];
    sparks.pos[1] = p->pos[1];
    sparks.pos[2] = p->pos[2];
    sparks.u0C[0] = 10.0f;
    sparks.u0C[1] = 30.0f;
    sparks.u0C[2] = 1.5f;
    sparks.u0C[3] = 1.0f;
    sparks.u0C[4] = 20.0f;
    sparks.u0C[5] = 40.0f;
    sparks.u24[0] = 0xF;
    sparks.u24[1] = 8;
    sparks.u24[2] = p->angle - 0x19;
    sparks.u24[3] = 0x32;
    sparks.u24[4] = -0x32;
    sparks.u24[5] = 0x3C;
    sparks.u24[6] = 3;
    sparks.u24[7] = 2;
    sparks.u24[8] = 0x3C;
    sparks.u24[9] = 0x14;
    sparks.u38 = 6;
    sparks.u39 = 8;
    sparks.u3C[0] = 1;
    sparks.u3C[1] = 7;
    sparks.u3C[2] = 0;
    sparks.u3C[3] = 0;
    sparks.u3C[4] = 0;
    sparks.u3C[5] = 0;
    sparks.u54 = 0xFF;
    sparks.u55 = 0xA0;
    emit_sparks_by_angles_b((u8 *) &sparks, (u8) view);
    sparks.u24[0] = 0xA;
    sparks.u24[1] = 6;
    sparks.u24[8] = 0x64;
    sparks.u24[9] = 0;
    sparks.u39 = 9;
    sparks.u3C[3] = 5;
    emit_sparks_by_angles_b((u8 *) &sparks, (u8) view);

    /* jet from 150 units in front of the pipe */
    s = angle_byte_cos(p->angle);
    c = angle_byte_cos((u8) (p->angle - 0x40));
    at[0] = p->pos[0] - 150.0f * c;
    at[1] = p->pos[1];
    at[2] = p->pos[2] - 150.0f * s;
    jet.u24 = 0x80;
    jet.u26 = 0xFF;
    jet.vel[0] = 10.0f * c;
    jet.vel[1] = 3.0f;
    jet.vel[2] = 10.0f * s;
    jet.u0C = -3.71f;
    jet.u30[0] = 2;
    jet.u30[1] = 5;
    jet.u10 = 4;
    jet.u38 = 0;
    jet.u36 = 0x1E;
    jet.u1C = 6;
    jet.u30[2] = 5;
    jet.u30[3] = 0x33;
    jet.u30[4] = 3;
    jet.u30[5] = 0x55;
    jet.u20 = 0.4f;
    jet.u2C = 47.0f;
    jet.u28 = 1.84f;
    jet.u14 = 3.3f;
    jet.u18 = 0.7f;
    jet.u3C = 0.3f;
    key[0] = (u8) pipe * 2;          /* D_8009FD20 {0, 2, 4} */
    effect_nodes_broadcast((s32) key, 0x17);
    key[0] = (u8) pipe * 2 + 1;      /* D_8009FD2C {1, 3, 5} */
    effect_nodes_broadcast((s32) key, 0x17);
    water_jet_spawn((s32 *) &jet, (u8 *) at, 20);

    sound_play_at(0xE7, 0x7FFF, 0, 2, 0, (s32) p->pos[0], (s32) p->pos[1], (s32) p->pos[2], 1000, 3000);
    sound_play_at(0x22, 0x7FFF, 0, 0, 0, (s32) p->pos[0], (s32) p->pos[1], (s32) p->pos[2], 1000, 3000);
    return 0; /* s32 for the caller game_eu_142E40.c (s32 (s32, s32)); nobody reads it (the asm leaves func_10010F88s v0) */
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/pipe_explode_effects.s")
#endif

#ifdef NON_MATCHING
/* P139 */
/* P139: particle request passed to mdl_particle_spawn by the pipe-explode spawn handlers (0x7C bytes; same layout as
 * game_eu_103160.c's DebrisParticle). */
typedef struct {
    /* 0x00 */ f32 scale[4];
    /* 0x10 */ f32 rot[3];
    /* 0x1C */ f32 one[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 alpha;
    /* 0x61 */ u8 u61;
    /* 0x62 */ u8 u62[6];
    /* 0x68 */ u8 u68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ void *owner;
    /* 0x70 */ u8 ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} PipeParticleReq;

s32 mdl_particle_spawn(void *req, s32, s32, s32, s32, s32);
f32 random_float(void);
f32 angle_byte_cos(u8);
/*
 * pipe_explode_spawn_chunk: D_8008ADA0 spawn handler 9 (called per ring point by spawn_ring_emit with (mode, index,
 * px, py, pz, cx, cy, cz, a, angle0, r, arg8, arg9, argA, argB)). Spawns one particle (mdl_particle_spawn, request
 * (3, 0xFF, 0, argB, 0)) at the point (px, py, pz): sprite 0x1C, life 100, flags 0x9E8, scale (1, 0.2, s, s) with
 * s random in 29.8..102.3, random x / z spin in -40..40 and gravity -0.837..-2.589. It flies outwards at a random
 * speed 18..49 in the direction yaw = angle0 + 60 * sin(a) * r * arg9 - 0x40, pitch = 48 * cos(a) - 0x14 (byte
 * angles, angle_byte_cos = sine). Returns 1 (keep emitting).
 */
/* was func_150B3394 */
s32 pipe_explode_spawn_chunk(s32 mode, s16 index, f32 px, f32 py, f32 pz, f32 cx, f32 cy, f32 cz, s32 a, s32 angle0, f32 r,
                  s32 arg8, f32 arg9, s32 argA, s32 argB) {
    PipeParticleReq req;
    f32 cosA;
    f32 sinA;
    f32 speed;
    f32 cosYaw;
    f32 sinYaw;
    f32 cosPitch;
    f32 horiz;
    f32 size;
    s16 yaw;
    s16 pitch;

    cosA = angle_byte_cos((a - 0x40) & 0xFF);
    sinA = angle_byte_cos(a & 0xFF);
    req.flags = 0x9E8;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.rot[0] = 0.0f;
    req.rot[1] = 0.0f;
    req.rot[2] = 0.0f;
    req.pos[0] = px;
    req.pos[1] = py;
    req.pos[2] = pz;
    req.scale[1] = 0.2f;
    speed = random_float() * 31.0f + 18.0f;
    yaw = angle0 + (s32) (60.0f * sinA * r * arg9) - 0x40;
    cosYaw = angle_byte_cos((yaw - 0x40) & 0xFF);
    sinYaw = angle_byte_cos(yaw & 0xFF);
    pitch = (s32) (48.0f * cosA) - 0x14;
    cosPitch = angle_byte_cos((pitch - 0x40) & 0xFF);
    horiz = speed * angle_byte_cos(pitch & 0xFF);
    req.vel[0] = horiz * cosYaw;
    req.vel[1] = -speed * cosPitch;
    req.vel[2] = horiz * sinYaw;
    req.spinX = random_float() * 80.0f - 40.0f;
    req.spinY = 0.0f;
    req.spinZ = random_float() * 80.0f - 40.0f;
    req.life = 100;
    req.gravity = random_float() * -1.7520001f - 0.837f;
    req.scale[0] = 1.0f;
    size = random_float() * 72.5f + 29.800001f;
    req.sprite = 0x1C;
    req.u58 = 0;
    req.scale[2] = size;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 1;
    req.u62[0] = 0;
    req.u62[1] = 0;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 0;
    req.u6A = 2;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    req.scale[3] = size;
    mdl_particle_spawn(&req, 3, 0xFF, 0, argB & 0xFF, 0);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/pipe_explode_spawn_chunk.s")
#endif

#ifdef NON_MATCHING
/* P139 */
extern char D_8009FD38[];   /* "life" */
extern char D_8009FD40[];   /* "../Effects/PipeExplode/pipeexplode.c" (one copy per tunable) */
extern char D_8009FD68[];   /* "min grav" */
extern char D_8009FD74[];
extern char D_8009FD9C[];   /* "grav range" */
extern char D_8009FDA8[];
extern char D_8009FDD0[];   /* "min speed" */
extern char D_8009FDDC[];
extern char D_8009FE04[];   /* "speeed range" */
extern char D_8009FE14[];
extern char D_8009FE3C[];   /* "min scale" */
extern char D_8009FE48[];
extern char D_8009FE70[];   /* "scale  range" */
extern char D_8009FE80[];
extern char D_8009FEA8[];   /* "xz angle" */
extern char D_8009FEB4[];
extern char D_8009FEDC[];   /* "yz angle" */
extern char D_8009FEE8[];
s32 debug_tweak_int(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

/*
 * pipe_explode_spawn_debris: D_8008ADA0 spawn handler 10 (pipeexplode.c; called per ring point by spawn_ring_emit
 * with (mode, index, px, py, pz, cx, cy, cz, a, angle0, r, arg8, arg9, argA, argB)). Reads its tunables through
 * debug_tweak_int (id, name, min, max, default, file, line): life (300), min grav / grav range (/1000), min speed /
 * speed range, min scale / scale range (/10), xz angle, yz angle. Spawns one particle (mdl_particle_spawn, request
 * (3, 0xFF, 4, argB, 0)) at (px, py, pz): sprite 0x1C, life + 0x20, flags 0x29E9, scale (s / 10, 0.2, s, s) with
 * s = min scale + random * scale range, random x / z spin in -2..2, gravity min grav + random * grav range. It
 * flies at min speed + random * speed range in the direction yaw = angle0 + xz * sin(a) * r * arg9 - 0x40,
 * pitch = yz * cos(a) - 0x14 (byte angles, angle_byte_cos = sine). The new particle's +0x170 gets -18.0
 * (memcpy). Returns 1 (keep emitting).
 */
/* was func_150B3668 */
s32 pipe_explode_spawn_debris(s32 mode, s16 index, f32 px, f32 py, f32 pz, f32 cx, f32 cy, f32 cz, s32 a, s32 angle0, f32 r,
                  s32 arg8, f32 arg9, s32 argA, s32 argB) {
    PipeParticleReq req;
    f32 floorY;
    f32 cosA;
    f32 sinA;
    s16 life;
    f32 minGrav;
    f32 gravRange;
    f32 minSpeed;
    f32 speedRange;
    f32 minScale;
    f32 scaleRange;
    f32 xzAngle;
    f32 yzAngle;
    f32 speed;
    f32 cosYaw;
    f32 sinYaw;
    f32 cosPitch;
    f32 horiz;
    f32 size;
    s16 yaw;
    s16 pitch;
    s32 p;

    cosA = angle_byte_cos((a - 0x40) & 0xFF);
    sinA = angle_byte_cos(a & 0xFF);
    life = debug_tweak_int(6, (s32) D_8009FD38, 1, 500, 300, (s32) D_8009FD40, 1858);
    minGrav = debug_tweak_int(7, (s32) D_8009FD68, -5000, 0, 0, (s32) D_8009FD74, 1872) * 0.001f;
    gravRange = debug_tweak_int(8, (s32) D_8009FD9C, -5000, 0, 0, (s32) D_8009FDA8, 1874) * 0.001f;
    minSpeed = debug_tweak_int(9, (s32) D_8009FDD0, 0, 500, 0, (s32) D_8009FDDC, 1882);
    speedRange = debug_tweak_int(10, (s32) D_8009FE04, 0, 500, 0, (s32) D_8009FE14, 1884);
    minScale = debug_tweak_int(11, (s32) D_8009FE3C, 0, 5000, 1000, (s32) D_8009FE48, 1889) * 0.1f;
    scaleRange = debug_tweak_int(12, (s32) D_8009FE70, 0, 5000, 0, (s32) D_8009FE80, 1891) * 0.1f;
    xzAngle = debug_tweak_int(13, (s32) D_8009FEA8, -255, 255, 0, (s32) D_8009FEB4, 1897);
    yzAngle = debug_tweak_int(14, (s32) D_8009FEDC, -255, 255, 0, (s32) D_8009FEE8, 1903);
    req.flags = 0x29E9;
    req.one[0] = 1.0f;
    req.one[1] = 1.0f;
    req.one[2] = 1.0f;
    req.rot[0] = 0.0f;
    req.rot[1] = 0.0f;
    req.rot[2] = 0.0f;
    floorY = -18.0f;
    req.pos[0] = px;
    req.pos[1] = py;
    req.pos[2] = pz;
    req.scale[1] = 0.2f;
    speed = random_float() * speedRange + minSpeed;
    yaw = angle0 + (s32) (xzAngle * sinA * r * arg9) - 0x40;
    cosYaw = angle_byte_cos((yaw - 0x40) & 0xFF);
    sinYaw = angle_byte_cos(yaw & 0xFF);
    pitch = (s32) (yzAngle * cosA) - 0x14;
    cosPitch = angle_byte_cos((pitch - 0x40) & 0xFF);
    horiz = speed * angle_byte_cos(pitch & 0xFF);
    req.vel[0] = horiz * cosYaw;
    req.vel[1] = -speed * cosPitch;
    req.vel[2] = horiz * sinYaw;
    req.spinX = random_float() * 4.0f - 2.0f;
    req.spinY = 0.0f;
    req.spinZ = random_float() * 4.0f - 2.0f;
    req.life = life + 0x20;
    req.gravity = random_float() * gravRange + minGrav;
    size = random_float() * scaleRange + minScale;
    req.scale[2] = size;
    req.sprite = 0x1C;
    req.u58 = 0;
    req.u5C = 0;
    req.alpha = 0xFF;
    req.u61 = 1;
    req.scale[0] = size * 0.1f;
    req.u62[0] = 0;
    req.u62[1] = 5;
    req.u62[2] = 0;
    req.u62[3] = 0;
    req.u62[4] = 0;
    req.u62[5] = 0;
    req.u68 = 0;
    req.u6A = 2;
    req.owner = NULL;
    req.ownerId = 0;
    req.u72 = 0x20;
    req.u74 = 7;
    req.scale[3] = size;
    p = mdl_particle_spawn(&req, 3, 0xFF, 4, argB & 0xFF, 0);
    if (p != 0) {
        memcpy((u8 *) p + 0x170, &floorY, 4);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/pipe_explode_spawn_debris.s")
#endif

#ifdef NON_MATCHING
/* P317: NM signature = D_80089CD4's dispatcher type (wasm call_indirect); args 1..3 / 5 unused */
/* was func_150B3B8C */
s32 debris_ground_stop_update(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 *arg5) {
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t9;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x48));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) + arg4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) < temp_f0) {
        temp_t7 = (*(s32 *)((u8 *)arg0 + 0x60)) & ~7;
        temp_t9 = temp_t7 & ~8;
        temp_t1 = temp_t9 & ~0x40;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t7;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t9;
        (*(s32 *)((u8 *)arg0 + 0x60)) = temp_t1;
        (*(s32 *)((u8 *)arg0 + 0x60)) = (s32) (temp_t1 & ~0x20);
        (*(f32 *)((u8 *)arg0 + 0x44)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x48)) = 0.0f;
        (*(f32 *)((u8 *)arg0 + 0x4C)) = 0.0f;
        if ((*(s16 *)((u8 *)arg0 + 0x64)) >= 0x21) {
            (*(s16 *)((u8 *)arg0 + 0x64)) = 0x20;
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x14));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) (-temp_f0 * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x4C)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x54)) * temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x58)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x58)) * temp_f2);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/debris_ground_stop_update.s")
#endif
/* was func_150B3C6C */
s32 trail_alpha_fade(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 16;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

#ifdef NON_MATCHING
struct210 *sprite_fx_spawn_cam(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD);
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s16 D_80088AA0[3];   /* splash colours (15, 16, 17) */

/* trail_hit_splash: trail hit handler (D_8008A7D0 [5]) of particle `obj` hitting the ground at height `y`: the trail
 * record (obj +0x98) goes to state 4 (shrink); a splash sprite (sprite_fx_spawn_cam kind 0x11, life 150, a random colour
 * of D_80088AA0, size 50..100, the record's alpha bytes +0x1A / +0x1B) at the trail's current point (obj +0x94,
 * 20-byte points, index +0x2D) and a falling child trail (trail_spawn: 3/4 of the record's +0 width, +4, random
 * length 15..30, +0xC / +0x10, colour bytes +0x19..+0x1B, life 60, the obj's +0x25) are spawned. Returns 1. */
/* was func_150B3CA8 */
s32 trail_hit_splash(u8 *obj, s32 arg1, s32 arg2, s32 arg3, f32 y, s32 arg5) {
    u8 *pts = *(u8 **)(obj + 0x94);
    u8 *rec = *(u8 **)(obj + 0x98);
    s16 colours[3];
    f32 size;
    s32 r1;
    s32 r2;
    s32 r3;
    struct {
        s32 kind;       /* 0x00 */
        s16 life;       /* 0x04 */
        u8 colour;      /* 0x06 */
        s32 u8_;        /* 0x08 */
        s32 uC;         /* 0x0C */
        u8 alpha0;      /* 0x10 */
        u8 alpha1;      /* 0x11 */
        u8 u12;
        u8 u13;
        u8 u14;
        u8 u15;         /* 0x15 = 0xFF */
        s32 flags;      /* 0x18 */
    } splash;
    struct {
        s32 w[7];       /* 0x00 */
        u8 b1C;
        u8 b1D;
    } style;
    struct {
        f32 width;      /* 0x00 */
        f32 v4;
        f32 length;
        f32 vC;
        f32 v10;
        f32 v14;
        u8 b18;
        u8 col[3];      /* 0x19..0x1B */
    } shape;
    struct {
        f32 x;          /* 0x00 */
        f32 y;
        f32 z;
        s16 life;       /* 0x0C */
        s16 sE;
        s32 s10;
        u8 b14;
        u8 b15;
    } at;

    colours[0] = D_80088AA0[0];
    colours[1] = D_80088AA0[1];
    colours[2] = D_80088AA0[2];
    rec[0x20] = 4;
    size = random_float() * 50.0f + 50.0f;
    splash.colour = colours[(u32)random_int() % 3];
    splash.u8_ = 0;
    splash.uC = 0;
    splash.kind = 0x11;
    splash.life = 150;
    splash.alpha0 = rec[0x1B];
    splash.u12 = 0;
    splash.u13 = 0;
    splash.u14 = 0;
    splash.u15 = 0xFF;
    splash.flags = 0x30002;
    splash.alpha1 = rec[0x1A];
    r1 = random_int();
    r2 = random_int();
    r3 = random_int();
    sprite_fx_spawn_cam((s32)&splash, 1, 0, arg5, *(f32 *)(pts + (s8)obj[0x2D] * 20), y,
                  *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8), size, size, r1 & 0xFF, (r3 & 1) + (r2 & 1), 0, obj[0xC],
                  obj[1]);

    style.w[0] = 0;
    style.w[1] = 1;
    style.w[2] = 0x160600;
    style.w[3] = 3;
    style.w[4] = 0x10;
    style.w[5] = 0x80;
    style.w[6] = 0x20;
    style.b1C = 0;
    style.b1D = 9;
    at.s10 = 1;
    at.sE = 1;
    shape.col[0] = rec[0x19];
    shape.b18 = 8;
    shape.col[1] = rec[0x1A];
    shape.col[2] = rec[0x1B];
    at.y = y;
    at.x = *(f32 *)(pts + (s8)obj[0x2D] * 20);
    at.z = *(f32 *)(pts + (s8)obj[0x2D] * 20 + 8);
    at.life = 60;
    at.b15 = obj[0x25];
    shape.width = *(f32 *)(rec + 0x0) * 0.75f;
    shape.v10 = *(f32 *)(rec + 0x10);
    shape.v4 = *(f32 *)(rec + 0x4);
    shape.length = random_float() * 15.0f + 15.0f;
    shape.vC = *(f32 *)(rec + 0xC);
    trail_spawn((u8 *)&at, (s32)&shape, 0, 1, 7, 0, 0, 0, 0, 0, 0, (u8 *)&style, 0, obj[0xC], obj[1]);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E0430/trail_hit_splash.s")
#endif