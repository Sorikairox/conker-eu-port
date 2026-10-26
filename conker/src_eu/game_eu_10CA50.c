#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 mdl_particle_spawn_ex(void *, s32, s32, s32, s32, u8, s32);
void water_ring_spawn(s32, s32, s32, s32, s32, s32, s32, u8, s32);
void cam_shake_all_players(f32 *, f32, f32, f32, u8, u8, s32);
s32 smoke_cloud_spawn(f32 *, u8, s32);
void explosion_light_spawn(f32 *, u8, s32);
s32 spark_shower_spawn(f32 *, f32, f32, f32, f32, u8, s32);
s32 debris_spray_spawn(void *, s32, u8, s32);
s32 memcpy(void *, void *, s32);

extern f32 D_80088D00[];        /* fragment base speed by kind */
extern f32 D_80088D0C[];        /* fragment random speed by kind */
extern f32 D_800A1130[15][3];   /* fragment offsets */
extern f32 D_800A11E4[15];
extern f32 D_800A1220[15];
extern f32 D_800A125C[15];
extern f32 D_800A1298[15];      /* fragment kind (float, read as an unsigned byte) */

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A12D4_c[1] = { 0.7111111f };     /* 0x3F360B61 */
static const f32 D_800A12D8_c[1] = { 0.2f };           /* 0x3E4CCCCD */
static const f32 D_800A12DC_c[1] = { -1.0320001f };    /* 0xBF841894 */
static const f32 D_800A12E0_c[1] = { 0.208f };         /* 0x3E54FDF4 */
static const f32 D_800A12E4_c[1] = { 0.019000001f };   /* 0x3C9BA5E4 */
static const f32 D_800A12E8_c[1] = { 1013.0f };        /* 0x447D4000 */
static const f32 D_800A12EC_c[1] = { 0.0009871669f };  /* 0x3A8163D3 */
static const f32 D_800A12F0_c[1] = { -0.7f };          /* 0xBF333333 */
static const f32 D_800A12F4_c[1] = { -0.62f };         /* 0xBF1EB852 */

/* mdl_particle_spawn_ex fragment request (0x7C bytes on the stack; unset pad bytes stay stack garbage like the asm's) */
typedef struct {
    f32 u0;         /* 0x00 15 */
    f32 u4;         /* 0x04 0.2 */
    f32 u8;         /* 0x08 1 */
    f32 uC;         /* 0x0C 1 */
    f32 org[3];     /* 0x10 D_800A5860 */
    f32 scale[3];   /* 0x1C 1, 1, 1 */
    f32 pos[3];     /* 0x28 */
    f32 vel[3];     /* 0x34 */
    f32 spin[3];    /* 0x40 */
    f32 u4C;        /* 0x4C */
    s32 u50;        /* 0x50 0x29E9 */
    s16 life;       /* 0x54 */
    s16 tex;        /* 0x56 0xC4 / 0xC5 */
    u8 u58;         /* 0x58 */
    u8 pad59[3];
    s32 u5C;        /* 0x5C */
    u8 u60[4];      /* 0x60 */
    u8 u64[4];      /* 0x64 */
    u8 u68;         /* 0x68 */
    u8 pad69;
    u8 u6A;         /* 0x6A */
    u8 pad6B;
    s32 u6C;        /* 0x6C */
    u8 u70;         /* 0x70 */
    u8 pad71;
    s16 u72;        /* 0x72 */
    s16 u74;        /* 0x74 */
    u8 pad76[2];
    s32 u78;        /* 0x78 */
} Frag240;

/* debris_spray_spawn shock ring request (0x5C bytes on the stack) */
typedef struct {
    s16 count;      /* 0x00 3..6 */
    u8 pad2[2];
    f32 pos[3];     /* 0x04 */
    s16 u10;        /* 0x10 0xBE */
    u8 pad12[2];
    f32 u14;        /* 0x14 250 */
    s16 u18;        /* 0x18 camera value - 0x40 */
    s16 u1A;        /* 0x1A 0x80 */
    s16 u1C;        /* 0x1C -0x3F */
    s16 u1E;        /* 0x1E 0x5A */
    f32 u20[13];    /* 0x20 shape parameters */
    u8 u54;         /* 0x54 1 */
    u8 u55;         /* 0x55 1 */
    s16 u56;        /* 0x56 100 */
    s16 u58;        /* 0x58 50 */
    u8 pad5A[2];
} Ring240;

typedef struct {
    f32 v[3];
} Vec240;

// big_explosion_spawn: explosion at pos: 15 fragments (mdl_particle_spawn_ex; offsets D_800A1130, kind D_800A1298 picks the
// speed D_80088D00 + D_80088D0C * random, spin from D_800A1220 / D_800A11E4 * D_800A125C * 0.019), then the light
// (water_ring_spawn), two shock waves (rumble_all_players_at / cam_shake_all_players), smoke_cloud_spawn, explosion_light_spawn, the sound
// (spark_shower_spawn), a 3..6 piece shock ring (debris_spray_spawn, scaled by the current camera's +0x380) and a type 0xF
// object whose +0x28 gets the position. Callers: event_effect_command (asm) and game_eu_CA630's C, both (pos, 0xFF, 1).
/* was func_150DF240 */
void big_explosion_spawn(f32 *pos, u8 room, s32 arg2) {
    Frag240 fr;
    Ring240 ring;
    Vec240 at;
    s32 camv;
    s32 i;
    u32 kind;
    f32 f;
    u8 *e;

    camv = (s32) (*(f32 *) ((u8 *) D_800DBFF0 + D_80082FA4 * 0x9A0 + 0x380) * D_800A12D4_c[0]);
    fr.u0 = 15.0f;
    fr.u4 = D_800A12D8_c[0];
    fr.u8 = 1.0f;
    fr.uC = 1.0f;
    *(Vec240 *) fr.org = *(Vec240 *) D_800A5860;
    fr.scale[0] = 1.0f;
    fr.scale[1] = 1.0f;
    fr.scale[2] = 1.0f;
    fr.spin[1] = 0.0f;
    fr.u50 = 0x29E9;
    fr.u58 = 0;
    fr.u5C = 0;
    fr.u60[0] = 0xFF;
    fr.u60[1] = 0xD;
    fr.u60[2] = 0;
    fr.u60[3] = 0xA;
    fr.u64[0] = 0;
    fr.u64[1] = 0;
    fr.u64[2] = 0;
    fr.u64[3] = 0;
    fr.u68 = 2;
    fr.u6A = 2;
    fr.u6C = 0;
    fr.u70 = 0;
    fr.u72 = 0x23;
    fr.u74 = 7;
    fr.u78 = 0;
    fr.vel[0] = 0.0f;
    fr.vel[2] = 0.0f;
    for (i = 0; i < 15; i++) {
        kind = (u8) (u32) D_800A1298[i];
        fr.pos[0] = D_800A1130[i][0] + pos[0];
        fr.pos[1] = D_800A1130[i][1] + pos[1];
        fr.pos[2] = D_800A1130[i][2] + pos[2];
        fr.vel[1] = D_80088D0C[kind] * random_float() + D_80088D00[kind];
        fr.spin[0] = D_800A1220[i] * D_800A125C[i] * D_800A12E4_c[0];
        fr.spin[2] = D_800A11E4[i] * D_800A125C[i] * D_800A12E4_c[0];
        fr.u4C = random_float() * D_800A12E0_c[0] + D_800A12DC_c[0];
        fr.life = (u32) random_int() % 111 + 0x82;
        fr.tex = (random_int() & 1) ? 0xC4 : 0xC5;
        mdl_particle_spawn_ex(&fr, 3, 0xFF, 0, 0, room, arg2);
    }
    water_ring_spawn(-1, (s32) pos[0], (s32) pos[1], (s32) pos[2], 0x1E, 0x32, 0, room, arg2);
    rumble_all_players_at((struct17 *) pos, 506.0f, D_800A12E8_c[0], D_800A12EC_c[0], 0xF, 0x14, room, arg2);
    cam_shake_all_players(pos, 506.0f, D_800A12E8_c[0], D_800A12EC_c[0], 5, room, arg2);
    smoke_cloud_spawn(pos, room, arg2);
    explosion_light_spawn(pos, room, arg2);
    f = random_float();
    spark_shower_spawn(pos, f * 4.0f + 12.0f, 1.6409999f, (f32) ((u32) random_int() % 56 + 0xC8), 0.0f, room, arg2);

    ring.count = (random_int() & 3) + 3;
    ring.u10 = 0xBE;
    ring.u18 = camv - 0x40;
    ring.u1A = 0x80;
    ring.u1C = -0x3F;
    ring.u1E = 0x5A;
    ring.u14 = 250.0f;
    *(Vec240 *) ring.pos = *(Vec240 *) pos;
    ring.u20[0] = 5.0f;
    ring.u20[2] = 15.0f;
    ring.u20[3] = 15.0f;
    ring.u20[4] = 0.0f;
    ring.u20[5] = 0.0f;
    ring.u54 = 1;
    ring.u55 = 1;
    ring.u56 = 100;
    ring.u58 = 50;
    ring.u20[1] = 10.0f;
    ring.u20[12] = 10.0f;
    ring.u20[6] = 0.0f;
    ring.u20[7] = 0.25f;
    ring.u20[8] = 0.5f;
    ring.u20[9] = D_800A12F0_c[0];
    ring.u20[10] = D_800A12F4_c[0];
    ring.u20[11] = -5.0f;
    debris_spray_spawn(&ring, 0, room, arg2);

    at = *(Vec240 *) pos;
    e = (u8 *) effect_node_create(0xF, 8, -1, -1, 1, 0, (struct37 *) 0xC, room, arg2);
    if (e != NULL) {
        memcpy(e + 0x28, &at, 0xC);
    }
}

s32 collision_floor_all(f32 *, s32, f32, f32 *);
void fx_debris_emitter_spawn(f32 *, s16, u8, s32);
void ground_scatter_spawn(f32 *, f32, f32, void *, s32, u8, s32, u8, s32);
// ground_burst_effect: P253. Handler (void (u8 *), function table at ELF file offset 0x24A880, next to fx_ring_particle_spawn /
// light_groups_send_msg22_all) of an effect object at p (+0x28 position, +0xC / +1 passed on to the spawners). Probes the ground
// from 500 above the position down to 500 below (collision_floor_all; the hit record's first word is the ground height):
// on a hit the effect sits on the ground (x, ground, z), else at the object's own position. Spawns
// fx_debris_emitter_spawn(pos, 120..181) there, then ground_scatter_spawn from 500 above pos down to 500 below it (radius 250,
// 3..5 pieces).
/* was func_150DF8B4 */
void ground_burst_effect(u8 *p) {
    f32 hit[10];
    f32 top[3];
    f32 probe[3];
    f32 ground[3];
    u8 found = 0;
    f32 *pos;

    probe[0] = *(f32 *) (p + 0x28);
    probe[1] = *(f32 *) (p + 0x2C) + 500.0f;
    probe[2] = *(f32 *) (p + 0x30);
    if (collision_floor_all(probe, 0, probe[1] - 1000.0f, hit) != 0) {
        ground[0] = *(f32 *) (p + 0x28);
        ground[1] = hit[0];
        ground[2] = *(f32 *) (p + 0x30);
        found = 1;
    }
    pos = found ? ground : (f32 *) (p + 0x28);
    fx_debris_emitter_spawn(pos, (s16) ((random_int() % 62U) + 120), p[0xC], p[1]);
    pos = found ? ground : (f32 *) (p + 0x28);
    *(s32 *) &top[0] = *(s32 *) &pos[0];   /* copied as words, like the asm */
    *(s32 *) &top[1] = *(s32 *) &pos[1];
    *(s32 *) &top[2] = *(s32 *) &pos[2];
    top[1] += 500.0f;
    ground_scatter_spawn(top, top[1] - 1000.0f, 250.0f, hit, (random_int() % 3U) + 3, 1, 0, p[0xC], p[1]);
}

s32 spark_spawn_from_desc(f32 *, s32, s32, s32, s32, s32);

void vec2_from_angle_byte(s16, f32, f32 *, f32 *); /* P95 */
/* was func_150DFA38 */
void puff_cluster_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct {
        f32 u88;
        u8 pad8C[0x4];
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s32 uB8;
        s8 uBC;
        u8 padBD[0x3];
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
    } sp;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_s7;
    s32 var_s0;

    temp_s7 = arg3 & 0xFF;
    (*(f32 *)((u8 *)(&sp.u88) + 0)) = (*(f32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(f32 *)((u8 *)(&sp.u88) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
    temp_f20 = (random_float() * 0.5f) + 1.0f;
    temp_f10 = random_float() * 0.5f;
    sp.u94 = 22.6f * temp_f20;
    sp.u9C = 13.786f * temp_f20;
    temp_f2 = temp_f10 + 1.0f;
    sp.uAA = 0x1A4D;
    sp.uA8 = 0x6231;
    sp.u98 = 57.969f * temp_f2;
    sp.uA0 = 42.714f * temp_f2;
    sp.uA4 = 118.763f * temp_f2;
    sp.uAC = (random_int() % 151U) + 0x96;
    sp.uAE = 0;
    sp.uAF = 0;
    sp.uB0 = 0;
    sp.uB1 = 0xFF;
    sp.uB2 = 1;
    sp.uB4 = (random_int() % 156U) + 0x64;
    sp.uB5 = 0xFF;
    sp.uB6 = 0;
    sp.uB7 = 1;
    sp.uB8 = 0;
    sp.uBC = 0xF;
    sp.uC4 = 10000.0f;
    sp.uC8 = 0.045f;
    sp.uC0 = 0.0f;
    sp.uCC = 0.7f;
    spark_spawn_from_desc(&sp.u88, 0xA, 0, 0, temp_s7, arg4);
    var_s0 = (random_int() % 3U) + 1;
    if (var_s0 > 0) {
        do {
            vec2_from_angle_byte((s16) (random_int() & 0xFF), 30.0f, &sp.u88, &sp.u90); /* P95: was 0x41F00000 as an int */
            sp.u88 += (*(f32 *)((u8 *)arg0 + 0));
            sp.u90 += (*(f32 *)((u8 *)arg0 + 8));
            temp_f20_2 = (random_float() * 0.5f) + 0.75f;
            temp_f18 = random_float() * 0.5f;
            sp.u94 = 22.6f * temp_f20_2;
            sp.u9C = 13.786f * temp_f20_2;
            temp_f2_2 = temp_f18 + 0.75f;
            sp.u98 = 57.969f * temp_f2_2;
            sp.uA0 = 42.714f * temp_f2_2;
            sp.uA4 = 118.763f * temp_f2_2;
            sp.uAC = (random_int() % 151U) + 0x96;
            sp.uB4 = (random_int() % 156U) + 0x64;
            sp.uB7 = 0;
            spark_spawn_from_desc(&sp.u88, 0xA, 0, 0, temp_s7, arg4);
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}