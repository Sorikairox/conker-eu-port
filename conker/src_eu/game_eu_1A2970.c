#include <ultra64.h>
#include "functions.h"
#include "variables.h"
typedef struct { s32 x0; s32 pad[4]; } Row20;
extern Row20 D_800DE2B4[];
extern Row20 D_800DE2B8[];
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A7550[4];
void flyer_update(u8 *);
s32 approx_dist2_int(s32, s32, s32, s32);
#endif


#ifdef NON_MATCHING
s32 collision_level_nearest_height(s32 x, s32 y, s32 z, s32 *tri);
extern s32 D_800DC26C; /* triangle table: 12 bytes per triangle */

// leaf_burst_spawn: spawns up to `count` falling leaves (node_alloc list 0xA, type 3) around (x, y, z) facing away
// from player `player`'s camera position (+0x2F8): position jittered by -63..64 in x / z, life 10..24, yaw = the
// direction +-15 degrees, speed jitter 0.01 * (-128..127), fall -1, size `base` + rand * `scale`, one of the two
// D_800DE2B8 models. Only the first leaf starts sound 0xA2. With `ground` & 1 each leaf records the floor below it
// (collision_level_nearest_height: height +0xC8, surface type +0xE8, colour D_800A7550[(type >> 5) & 3] at +0xEC).
/* was func_15175160 */
void flyer_leaf_burst_spawn(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 player, f32 base, f32 scale, s32 ground) {
    struct { f32 x, y, z; } d;
    s32 tri;
    u8 *pl;
    u8 *p;
    s32 yaw;
    s32 i;
    s32 onGround;
    s32 px, pz;
    s32 a;
    s32 v;
    s32 m;
    f32 fy;

    pl = (u8 *)D_800DBFF0 + player * 0x9A0;
    d.x = (f32)x - *(f32 *)(pl + 0x2F8);
    fy = (f32)y;
    d.y = fy - *(f32 *)(pl + 0x2FC);
    d.z = (f32)z - *(f32 *)(pl + 0x300);
    yaw = (s32)vec3_heading_deg((struct17 *)&d);

    for (i = 0; i < count; i++) {
        p = node_alloc(0xA, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            break;
        }
        onGround = ground & 1;
        px = (random_int() & 0x7F) + x - 0x3F;
        pz = (random_int() & 0x7F) + z - 0x3F;
        *(s16 *)(p + 0x92) = 3;
        *(f32 *)(p + 0x98) = (f32)px;
        *(f32 *)(p + 0x9C) = fy;
        *(f32 *)(p + 0xA0) = (f32)pz;
        p[0x90] = slot;
        *(s16 *)(p + 0xA4) = (u32)random_int() % 15 + 10;
        *(s16 *)(p + 0xA6) = 1;
        a = (random_int() & 0x1F) + yaw - 15;
        if (a < 0) {
            a += 360;
        } else if (a >= 360) {
            a -= 360;
        }
        *(f32 *)(p + 0xA8) = (f32)((random_int() & 0x1F) - 15);
        *(f32 *)(p + 0xAC) = (f32)a;
        *(f32 *)(p + 0xB0) = 0.0f;
        *(f32 *)(p + 0xB4) = -1.0f;
        *(f32 *)(p + 0xB8) = (f32)((random_int() & 0xFF) - 0x80) * 0.01f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(random_int() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        m = random_int() & 1;
        *(s32 *)(p + 0x94) = D_800DE2B8[m].x0;
        p[0xED] = m;
        if (i == 0) {
            *(u16 *)(p + 0xEE) = sound_voice_play_at(0, 0xA2, 0x7D00, 0, 0, 0, px, y, pz, 1000, 4000);
        } else {
            *(u16 *)(p + 0xEE) = 0;
        }
        *(s32 *)(p + 0xE8) = 0;
        if (onGround) {
            *(s16 *)(p + 0x92) |= 0x80;
            *(f32 *)(p + 0xC8) = (f32)collision_level_nearest_height(px, y, pz, &tri);
            v = 0;
            if (tri != 0) {
                v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 12];
            }
            *(s32 *)(p + 0xE8) = v;
            p[0xEC] = D_800A7550[((u32)v >> 5) & 3];
        } else {
            p[0xEC] = 0;
        }
        p[0xF0] = 0;
        p[0xF1] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_leaf_burst_spawn.s")
#endif

#ifdef NON_MATCHING
void collision_select_area(s32 arg0);
s32 floor_collect_level_tris(s32 x, s32 z);
extern s32 D_800D3720; /* floor candidates (16 bytes: +0 height in 24.8) left by floor_collect_level_tris */

// leaf_drop_spawn: spawns up to `count` leaves of model row 7 (node_alloc list 0x13) in a `width` square around
// (x, z) at height y: life 4..6, spin / tilt jitter, size `base` + rand * `scale`. Each leaf takes the lowest floor
// below it (floor_collect_level_tris; none -> the leaf is freed with node_delete). mode 0 (after collision_select_area(0)) puts the
// leaf 10 above that floor in state 1; otherwise it falls from 300..427 above it in state 4 (+0x91 = 2).
// `player` is not used.
/* was func_15175514 */
void flyer_leaf_drop_spawn(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 width, s32 player, s32 mode, f32 base, f32 scale) {
    u8 *p;
    s32 i;
    s32 k;
    s32 n;
    s32 half;
    s32 px, pz;
    s32 floorY;
    s32 h;

    if (mode == 0) {
        collision_select_area(0);
    }
    for (i = 0; i < count; i++) {
        p = node_alloc(0x13, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            break;
        }
        half = width >> 1;
        px = (u32)random_int() % width + x - half;
        pz = (u32)random_int() % width + z - half;
        *(f32 *)(p + 0x98) = (f32)px;
        *(f32 *)(p + 0x9C) = (f32)y;
        *(f32 *)(p + 0xA0) = (f32)pz;
        p[0x90] = slot;
        *(s16 *)(p + 0xA4) = (u32)random_int() % 3 + 4;
        *(s16 *)(p + 0xA6) = 0;
        *(f32 *)(p + 0xA8) = (f32)((random_int() & 0x1F) - 15);
        *(f32 *)(p + 0xAC) = (f32)((u32)random_int() % 360);
        *(f32 *)(p + 0xB0) = (f32)((random_int() & 0x1F) - 15);
        *(f32 *)(p + 0xB4) = 0.0f;
        *(f32 *)(p + 0xB8) = 3.0f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(random_int() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        *(s32 *)(p + 0x94) = D_800DE2B8[7].x0;
        p[0xED] = 7;

        n = floor_collect_level_tris(px, pz);
        if (n == 0) {
            node_delete((struct102 *)p);
            continue;
        }
        floorY = (&D_800D3720)[0];
        for (k = 1; k < n; k++) {
            h = (&D_800D3720)[k * 4];
            if (h < floorY) {
                floorY = h;
            }
        }
        floorY >>= 8;
        *(f32 *)(p + 0xC8) = (f32)floorY;
        if (mode == 0) {
            p[0x91] = 0;
            *(s16 *)(p + 0x92) = 1;
            *(f32 *)(p + 0x9C) = (f32)(floorY + 10);
        } else {
            p[0x91] = 2;
            *(s16 *)(p + 0x92) = 4;
            *(f32 *)(p + 0xE4) = (f32)((random_int() & 0x7F) + floorY + 300);
            *(f32 *)(p + 0x9C) = (f32)((random_int() & 0x7F) + floorY + 300);
        }
        *(f32 *)(p + 0xCC) = 0.0f;
        *(s16 *)(p + 0xD0) = x;
        *(s16 *)(p + 0xD4) = z;
        *(s16 *)(p + 0xD6) = half;
        *(f32 *)(p + 0xE0) = 0.0f;
        *(s16 *)(p + 0xDC) = 0;
        *(s32 *)(p + 0xE8) = 0;
        p[0xEC] = 0;
        p[0xF0] = 0;
        p[0xF1] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_leaf_drop_spawn.s")
#endif

#ifdef NON_MATCHING
s32 collision_level_nearest_height(s32 x, s32 y, s32 z, s32 *tri);
s32 random_int(void);
extern s32 D_800DC26C; /* triangle table: 12 bytes per triangle */

// leaf_field_spawn: spawns up to `count` leaf / debris particles (node_alloc list `list` + rand % `listRand`)
// in a ring around (x, z): each axis offset is rand % (rMax - rMin) pushed out by rMin (away from 0), so |offset| is
// in rMin .. rMax - 1. Height: the floor below the point (collision_level_nearest_height, +0xC8) when `mode` is 0, else
// y + rand % yRange (y when yRange is 0). flags (stored at +0x92): 0x40 = nothing when yRange <= 0; 0x10000 = yaw
// away from player `player`'s camera (+0x2F8) +-15 degrees (else a random yaw); 0x20000 = tilt (rand & 0x1F) - 15
// and fall -1. Model row (D_800DE2B8, +0xED): `model` + (rand & modelMask), + 0 for mask 0 and + the list offset for
// mask -1 (the asm reuses that register). Life 10..24, spin (rand & 0xFF) - 0x80 * 0.01, size base + rand * scale.
// The first particle of list 0xA starts sound 0xA2 (+0xEE). With `ground` & 1 the particle records the floor
// surface (+0xE8, colour D_800A7550[(type >> 5) & 3] at +0xEC; +0x92 |= 0x80). Called by game_eu_1B1010 (effects
// kinds with 18 arguments).
/* was func_15175900 */
void flyer_field_spawn(s32 count, s32 slot, s32 x, s32 y, s32 z, s32 rMax, s32 player, s32 yRange, s32 rMin, s32 flags,
                   s32 list, s32 listRand, s32 model, s32 modelMask, s32 mode, f32 base, f32 scale, s32 ground) {
    struct { f32 x, y, z; } d;
    s32 tri;
    s32 yaw;
    s32 aimed;
    s32 tilt;
    s32 onGround;
    s32 i;
    s32 off;
    s32 range;
    s32 r;
    s32 px, py, pz;
    s32 a;
    u8 *pl;
    u8 *p;
    s32 v;

    if ((flags & 0x40) && yRange <= 0) {
        return;
    }
    aimed = flags & 0x10000;
    if (aimed) {
        pl = (u8 *)D_800DBFF0 + player * 0x9A0;
        d.x = (f32)x - *(f32 *)(pl + 0x2F8);
        d.y = (f32)y - *(f32 *)(pl + 0x2FC);
        d.z = (f32)z - *(f32 *)(pl + 0x300);
        yaw = (s32)vec3_heading_deg((struct17 *)&d);
    }
    for (i = 0; i < count; i++) {
        off = 0;
        if (listRand != 0) {
            off = (u32)random_int() % (u32)listRand;
        }
        p = node_alloc(list + off, 0, 0xF8, 1, 0xFF, 1);
        if (p == NULL) {
            return;
        }
        onGround = ground & 1;
        tilt = flags & 0x20000;
        py = y;
        range = rMax - rMin;
        r = random_int() % range;
        px = (r < 0 ? r - rMin : r + rMin) + x;
        r = random_int() % range;
        pz = (r < 0 ? r - rMin : r + rMin) + z;
        if (mode == 0 || onGround) {
            *(f32 *)(p + 0xC8) = (f32)collision_level_nearest_height(px, y, pz, &tri);
        }
        if (mode == 0) {
            py = (s32)*(f32 *)(p + 0xC8);
        } else if (yRange != 0) {
            py = y + (u32)random_int() % (u32)yRange;
        }
        p[0x90] = slot;
        *(s16 *)(p + 0x92) = flags;
        *(f32 *)(p + 0x98) = (f32)px;
        p[0x91] = mode;
        *(f32 *)(p + 0x9C) = (f32)py;
        *(f32 *)(p + 0xA0) = (f32)pz;
        *(s16 *)(p + 0xA4) = (u32)random_int() % 15 + 10;
        *(s16 *)(p + 0xA6) = 0;
        if (aimed) {
            a = (random_int() & 0x1F) + yaw - 15;
            if (a < 0) {
                a += 360;
            } else if (a >= 360) {
                a -= 360;
            }
        } else {
            a = (u32)random_int() % 360;
        }
        if (tilt) {
            *(f32 *)(p + 0xA8) = (f32)((random_int() & 0x1F) - 15);
            *(f32 *)(p + 0xB4) = -1.0f;
        } else {
            *(f32 *)(p + 0xA8) = 0.0f;
            *(f32 *)(p + 0xB4) = 0.0f;
        }
        *(f32 *)(p + 0xB0) = 0.0f;
        *(f32 *)(p + 0xAC) = (f32)a;
        *(f32 *)(p + 0xB8) = (f32)((random_int() & 0xFF) - 0x80) * 0.01f;
        *(f32 *)(p + 0xBC) = 0.0f;
        *(f32 *)(p + 0xC0) = (f32)(random_int() & 0xFFFF) * (1.0f / 32768.0f) * scale + base;
        if (modelMask == -1) {
            /* off (the list offset) is kept */
        } else if (modelMask == 0) {
            off = 0;
        } else {
            off = random_int() & modelMask;
        }
        off += model;
        p[0xED] = off;
        *(s32 *)(p + 0x94) = D_800DE2B8[off].x0;
        *(s16 *)(p + 0xD0) = x;
        *(s16 *)(p + 0xD2) = y;
        *(s16 *)(p + 0xD4) = z;
        *(s16 *)(p + 0xD8) = rMin;
        *(s16 *)(p + 0xD6) = rMax;
        *(s16 *)(p + 0xDC) = 0;
        *(s16 *)(p + 0xDE) = 0;
        *(s32 *)(p + 0xE8) = 0;
        *(f32 *)(p + 0xE0) = 0.0f;
        *(s16 *)(p + 0xDA) = yRange;
        if (i != 0) {
            *(u16 *)(p + 0xEE) = 0;
        } else if (list == 0xA) {
            *(u16 *)(p + 0xEE) = sound_voice_play_at(0, 0xA2, 0x7D00, 0, 0, 0, px, py, pz, 1000, 4000);
        }
        if (onGround) {
            *(s16 *)(p + 0x92) |= 0x80;
            v = 0;
            if (tri != 0) {
                v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 12];
            }
            *(s32 *)(p + 0xE8) = v;
            p[0xEC] = D_800A7550[((u32)v >> 5) & 3];
        } else {
            p[0xEC] = 0;
        }
        p[0xF0] = 0;
        p[0xF1] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_field_spawn.s")
#endif

#ifdef NON_MATCHING
/* ambient flyer object (the node_alloc particles of flyer_field_spawn / game_eu_1B1010) */
typedef struct {
    u8 kind;            /* 0x00: 0x13 = chirping kind */
    u8 pad1[0x8F];
    u8 slot;            /* 0x90: spawn slot (D_800DDF5C / D_800DDF60 index) */
    u8 state;           /* 0x91: 2 = wander, 3 = turn to targetHeading */
    s16 flags;          /* 0x92 */
    s32 model;          /* 0x94 */
    f32 x, y, z;        /* 0x98 */
    s16 speed;          /* 0xA4 */
    s16 accel;          /* 0xA6 */
    f32 pitch;          /* 0xA8 */
    f32 heading;        /* 0xAC */
    f32 roll;           /* 0xB0 */
    f32 pitchVel;       /* 0xB4: also the circling angle (flag 0x200) */
    f32 turnVel;        /* 0xB8 */
    f32 rollVel;        /* 0xBC: also the circling radius (flag 0x200) */
    u8 padC0[8];
    f32 floorY;         /* 0xC8 */
    u8 padCC[4];
    s16 homeX, homeY, homeZ; /* 0xD0 */
    s16 rangeMax;       /* 0xD6 */
    s16 rangeMin;       /* 0xD8 */
    s16 yRange;         /* 0xDA */
    s16 timer;          /* 0xDC */
    s16 climbTimer;     /* 0xDE */
    f32 targetHeading;  /* 0xE0 */
    f32 targetY;        /* 0xE4 */
    s32 surface;        /* 0xE8 */
    u8 padEC;
    u8 type;            /* 0xED */
    u16 sound;          /* 0xEE */
    u8 alpha;           /* 0xF0 */
    u8 fading;          /* 0xF1 */
} Flyer;

/* D_8008D450: per type, 0x38 bytes */
typedef struct {
    u8 speedMax, speedMin, wanderTime, homeTime;
    f32 rollMax;        /* 0x04 */
    f32 pitchMax;       /* 0x08 */
    f32 pad0C;
    f32 turnMax;        /* 0x10 */
    f32 pad14;
    f32 flapA;          /* 0x18 */
    f32 pad1C;
    f32 flapB;          /* 0x20 */
    u8 pad24[0x14];
} FlyerType;

/* D_800DDE80: per type, 0x14 bytes */
typedef struct {
    s32 enabled;
    s32 modelUp;        /* model while climbing (pitch >= 0) */
    s32 modelDown;
    s32 pad[2];
} FlyerModels;

extern s32 D_8008D450;
extern s32 D_800C39D0;
extern f32 D_800D3A00;
extern f32 D_800D3A04;
extern f32 D_800D9F3C;
extern f32 D_800D9F40;
extern u8 D_800DA030[];
extern u8 D_800DA070[];
s32 vec3_heading_u8(struct17 *);
s32 view_point_cull_test(u8 *, f32, f32, f32, f32, f32, f32, f32, s32, s32);

/* rodata copies (D_800A755C..D_800A7588) */
static const f32 sFlyerCircleX[1] = { -3478.0f };       /* D_800A755C / D_800A757C */
static const f32 sFlyerCircleZ[1] = { 3858.0f };        /* D_800A7560 / D_800A7580 */
static const f32 sFlyerHalfPi[1] = { 1.57079637f };     /* D_800A7564 */
static const f32 sFlyerCircleTurn[1] = { 0.0115f };     /* D_800A7568 */
static const f32 sFlyerTurnMin[1] = { 0.200000003f };   /* D_800A756C */
static const f32 sFlyerCircleTurnMax[1] = { 0.149999991f }; /* D_800A7570 */
static const f32 sFlyerCircleTurnAcc[1] = { 0.00518999994f }; /* D_800A7574 */
static const f32 sFlyerCircleShrink[1] = { 3.20000005f }; /* D_800A7578 */
static const f32 sFlyerCircleFloor[1] = { -3100.0f };   /* D_800A7584 */
static const f32 sFlyerDegToRad[1] = { 0.0174532924f }; /* D_800A7588 */

// ambient_flyer_update: per-frame update of an ambient flyer (bird / bat; render-layer field 0 of layers 10 / 20 /
// 68 / 69, also called by flyer_perched_update / flyer_resting_update). Removed (node_destroy) when its type row is off. Types 8
// and 9 on level 6 during D_800C3A08 == 0xF scatter after 60 frames of D_800C39D0: they start circling (flag 0x200)
// round (-3478, 3858), the radius shrinking to 60 while they sink, and vanish below -3100 or when the event ends.
// Otherwise: fade in / fade out (alpha +0xF0, `fading` once the slot is gone and flag 8 is set), keep the looping
// sound at the flyer (+0xEE), flag 4 = tether to home (turn back past rangeMax, or away inside rangeMin with flag
// 0x10, then wander with random headings), flag 0x80 = follow the floor, flag 0x40 = bob between home y and a random
// height; then pitch / turn / roll / speed integration (limits in D_8008D450), wing model by pitch (flag 1 = fixed),
// a chirp for kind 0x13 and removal when outside both views (flag 2).
/* was func_15175EC8 */
void flyer_update(u8 *arg0) {
    Flyer *f = (Flyer *)arg0;
    FlyerModels *row;
    FlyerType *t;
    s32 alpha;
    s32 near;
    s32 ang;
    s32 dist;
    s32 tri;
    s32 v;
    s16 sp;
    f32 dx, dz;
    f32 step;
    f32 d;
    f32 lim;
    f32 a, h;
    f32 sa, sh, ca, ch;
    f32 s, c;
    struct17 dir;

    row = (FlyerModels *)((u8 *)D_800DDE80 + f->type * 0x14);
    if (row->enabled == 0 || D_800DDF78[f->type] == 0) {
        node_destroy((struct102 *)f);
        return;
    }
    alpha = f->alpha;
    if ((f->type == 8 || f->type == 9) && D_800BE9F0 == 6 && D_800C35EA != 0 && D_800C3A08 == 0xF) {
        f->flags &= 0xFFF7;
        if (D_800C35EA == 0 || D_800C3A08 != 0xF) {
            node_destroy((struct102 *)f);
            return;
        }
        if (D_800C39D0 >= 60 && !(f->flags & 0x200)) {
            f->flags = (f->flags & 0xFFB3) | 0x200;
            dx = f->x - sFlyerCircleX[0];
            dz = f->z - sFlyerCircleZ[0];
            f->pitchVel = sFlyerHalfPi[0] - func_150484A0(dx, dz);
            f->turnVel = sFlyerCircleTurn[0];
            f->rollVel = sqrtf(dx * dx + dz * dz);
        }
    }

    if (f->fading == 0) {
        if ((f->flags & 8) && D_800DDF5C[f->slot] == 0) {
            f->fading = 1;
        } else if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 4;
            if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            f->alpha = alpha;
        }
    } else {
        if (alpha == 0) {
            node_destroy((struct102 *)f);
            return;
        }
        alpha -= D_800BE9E4 * 4;
        if (alpha < 0) {
            alpha = 0;
        }
        f->alpha = alpha;
    }
    row = (FlyerModels *)((u8 *)D_800DDE80 + f->type * 0x14);
    D_800DDF68[f->type] = 1;
    t = (FlyerType *)((u8 *)&D_8008D450 + f->type * 0x38);

    if (f->sound != 0) {
        if (sound_voice_is_playing(f->sound) != 0) {
            sound_voice_update_3d(f->sound, 0x7D00, 0, 0, 0, (s32)f->x, (s32)f->y, (s32)f->z, 1000, 4000);
        } else {
            f->sound = 0;
        }
    }

    if (f->flags & 4) {
        dist = approx_dist2_int((s32)f->x, (s32)f->z, f->homeX, f->homeZ);
        near = 0;
        if ((f->flags & 0x10) && dist < f->rangeMin) {
            near = 1;
        }
        if (dist > f->rangeMax || near) {
            dir.unk0 = (f32)f->homeX - f->x;
            dir.unk8 = f->z - (f32)f->homeZ;
            ang = vec3_heading_u8(&dir);
            if (near) {
                ang += 0x80;
            }
            if (ang >= 0x100) {
                ang -= 0x100;
            }
            f->targetHeading = (f32)ang * 1.40625f;
            f->state = 3;
            f->timer = t->homeTime;
        }
        if (f->state == 3) {
            step = D_800BE9E4 * 0.5f;
            if (f->targetHeading < f->heading) {
                step = -step;
            }
            if (fabsf(f->targetHeading - f->heading) >= 180.0f) {
                step = -step;
            }
            if ((step > 0.0f && f->turnVel < 0.0f) || (step < 0.0f && f->turnVel > 0.0f)) {
                f->state = 2;
            } else {
                f->turnVel += step;
            }
        }
        if (f->state == 2) {
            if (f->turnVel != 0.0f) {
                if (f->turnVel > 0.0f) {
                    f->turnVel -= D_800BE9E4 * 0.5f;
                    if (f->turnVel < 0.0f) {
                        f->turnVel = 0.0f;
                    }
                } else {
                    f->turnVel += D_800BE9E4 * 0.5f;
                    if (f->turnVel > 0.0f) {
                        f->turnVel = 0.0f;
                    }
                }
            }
            f->timer -= D_800BE9E4;
            if (f->timer <= 0) {
                f->targetHeading = (f32)((u32)random_int() % 360);
                f->state = 3;
                f->timer = t->wanderTime;
            }
        }
        if (fabsf(f->turnVel) > t->turnMax) {
            if (f->turnVel > 0.0f) {
                f->turnVel = t->turnMax;
            } else {
                f->turnVel = -t->turnMax;
            }
        }
    }

    if (f->flags & 0x80) {
        f->floorY = (f32)collision_level_nearest_height((s32)f->x, (s32)f->y, (s32)f->z, &tri);
        v = 0;
        if (tri != 0) {
            v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 12];
        }
        f->surface = v;
    }

    if (f->flags & 0x40) {
        if (f->climbTimer >= 0) {
            f->climbTimer -= D_800BE9E4;
            if (f->climbTimer <= 0) {
                f->climbTimer = -1;
                f->targetY = (f32)((u32)random_int() % f->yRange) + (f32)f->homeY;
                if (f->y < f->targetY) {
                    f->pitchVel = -1.0f;
                } else {
                    f->pitchVel = 1.0f;
                }
            } else if (f->pitch > 0.0f) {
                f->pitchVel = -1.0f;
            } else if (f->pitch < 0.0f) {
                f->pitchVel = 1.0f;
            }
        } else if ((f->pitchVel > 0.0f && f->y < f->targetY) || (f->pitchVel < 0.0f && f->targetY < f->y)) {
            f->climbTimer = 120;
            f->pitchVel = -f->pitchVel;
        }
    }

    if (!(f->flags & 0x200)) {
        f->pitch += f->pitchVel;
        lim = t->pitchMax;
        if (f->pitch < -lim) {
            f->pitch = -lim;
        } else {
            f->pitch = (f->pitch > lim) ? lim : f->pitch;
        }
        if (fabsf(f->turnVel) > sFlyerTurnMin[0]) {
            f->heading += f->turnVel;
            if (f->heading < 0.0f) {
                f->heading += 360.0f;
            } else if (f->heading >= 360.0f) {
                f->heading -= 360.0f;
            }
            if (!(f->flags & 0x20)) {
                f->rollVel = -f->turnVel;
                f->roll += f->rollVel;
                lim = t->rollMax;
                if (f->roll < -lim) {
                    f->roll = -lim;
                } else {
                    f->roll = (f->roll > lim) ? lim : f->roll;
                }
            }
        } else {
            if (f->roll > 0.0f) {
                f->rollVel = -1.0f;
            } else if (f->roll < 0.0f) {
                f->rollVel = 1.0f;
            }
            f->roll += f->rollVel;
            if (fabsf(f->roll) < sFlyerTurnMin[0]) {
                f->roll = 0.0f;
            }
        }
        f->speed += f->accel;
        if (f->speed < t->speedMin) {
            f->speed = t->speedMin;
        } else {
            sp = f->speed;
            if (sp > t->speedMax) {
                sp = t->speedMax;
            }
            f->speed = sp;
        }
    }

    if (!(f->flags & 1)) {
        if (f->pitch >= 0.0f) {
            if (row->modelUp == f->model && t->flapA < t->flapB && -t->flapB < t->flapA) {
                f->model = row->modelDown;
            }
        } else if (row->modelDown == f->model && t->flapA < t->flapB && -t->flapB < t->flapA) {
            f->model = row->modelUp;
        }
    }

    if (f->flags & 0x200) {
        d = D_800BE9E4;
        f->pitchVel += f->turnVel * d;
        f->turnVel += sFlyerCircleTurnAcc[0];
        if (f->turnVel > sFlyerCircleTurnMax[0]) {
            f->turnVel = sFlyerCircleTurnMax[0];
        }
        f->rollVel -= sFlyerCircleShrink[0] * d;
        if (f->rollVel < 60.0f) {
            f->rollVel = 60.0f;
        }
        s = func_150AD78C(f->pitchVel);
        c = func_150AD780(f->pitchVel);
        f->x = f->rollVel * c + sFlyerCircleX[0];
        f->z = f->rollVel * s + sFlyerCircleZ[0];
        f->y -= 100.0f / ((f->rollVel - 60.0f) + 4.0f);
        if (f->y < sFlyerCircleFloor[0] || D_800C35EA == 0 || D_800C3A08 != 0xF) {
            node_destroy((struct102 *)f);
            return;
        }
    } else {
        a = f->pitch * sFlyerDegToRad[0];
        h = f->heading * sFlyerDegToRad[0];
        sa = func_150AD78C(a);
        sh = func_150AD78C(h);
        ca = func_150AD780(a);
        ch = func_150AD780(h);
        dir.unk0 = ca * sh;
        dir.unk4 = -sa;
        dir.unk8 = ca * ch;
        d = f->speed * D_800BE9E4;
        f->x += dir.unk0 * d;
        f->y += dir.unk4 * d;
        f->z += dir.unk8 * d;
    }

    if (f->kind == 0x13 && D_800DDF60[f->slot] == 0) {
        sound_play_at(0x10, 0x7FFF, random_int() & 0x7F, 0, 0, (s32)f->x, (s32)f->y, (s32)f->z, 500, 4000);
        D_800DDF60[f->slot] = (random_int() & 0x3F) + 30;
    }
    if ((f->flags & 2)
        && view_point_cull_test(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) != 0
        && (D_800D2138 != 1
            || view_point_cull_test(D_800DA070, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0)
                   != 0)) {
        node_destroy((struct102 *)f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_update.s")
#endif

#ifdef NON_MATCHING
/* was func_15176DCC */
void flyer_perched_update(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    s32 temp_v1;
    u8 temp_v0;

    if (D_800DDF5C[(*(u8 *)((u8 *)arg0 + 0x90))] != 0) {
        D_800DDF68[(*(u8 *)((u8 *)arg0 + 0xED))] = 1;
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x91));
        switch (temp_v0) {                          /* irregular */
        case 0:
            if (approx_dist2_int((s32) D_800CC2D0->x_position, (s32) D_800CC2D0->z_position, (s32) (*(f32 *)((u8 *)arg0 + 0x98)), (s32) (*(f32 *)((u8 *)arg0 + 0xA0))) < 0x190) {
                (*(u8 *)((u8 *)arg0 + 0x91)) = 1U;
                temp_f10 = (f32) (-1 - (random_int() & 3));
                (*(f32 *)((u8 *)arg0 + 0xA8)) = -8.0f;
                (*(f32 *)((u8 *)arg0 + 0xB4)) = temp_f10;
                return;
            }
            temp_f0 = (*(f32 *)((u8 *)arg0 + 0xCC));
            if (temp_f0 != 0.0f) {
                (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xA8)) + temp_f0);
                if (temp_f0 < 0.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xAC)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xAC)) + (*(f32 *)((u8 *)arg0 + 0xB8)));
                }
                temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0xA8));
                if (temp_f0_2 > 45.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = -5.0f;
                } else if (((*(f32 *)((u8 *)arg0 + 0xCC)) < 0.0f) && (temp_f0_2 > 25.0f) && ((random_int() & 0xFF) < 0x33)) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 5.0f;
                }
                if ((*(f32 *)((u8 *)arg0 + 0xA8)) <= 10.0f) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 0.0f;
                    return;
                }
            } else {
                temp_v1 = random_int() & 0xFF;
                if (temp_v1 < 0x19) {
                    (*(f32 *)((u8 *)arg0 + 0xCC)) = 5.0f;
                    if (temp_v1 < 0xD) {
                        (*(f32 *)((u8 *)arg0 + 0xB8)) = (f32) ((random_int() % 6U) - 3);
                        return;
                    }
                    (*(f32 *)((u8 *)arg0 + 0xB8)) = 0.0f;
                    return;
                }
            }
            break;
        case 1:
            if ((300.0f + (*(f32 *)((u8 *)arg0 + 0xC8))) <= (*(f32 *)((u8 *)arg0 + 0x9C))) {
                (*(u8 *)((u8 *)arg0 + 0x91)) = 2U;
                (*(s16 *)((u8 *)arg0 + 0x92)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x92)) & 0xFFFE);
                (*(s16 *)((u8 *)arg0 + 0x92)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x92)) | 4);
                (*(f32 *)((u8 *)arg0 + 0xE4)) = (f32) ((f32) (random_int() & 0x7F) + (300.0f + (*(f32 *)((u8 *)arg0 + 0xC8))));
            }
            flyer_update(arg0);
            return;
        default:
        case 2:
        case 3:
            if ((*(f32 *)((u8 *)arg0 + 0x9C)) < (*(f32 *)((u8 *)arg0 + 0xE4))) {
                (*(f32 *)((u8 *)arg0 + 0xB4)) = -1.5f;
            } else if ((*(f32 *)((u8 *)arg0 + 0xA8)) < 0.0f) {
                (*(f32 *)((u8 *)arg0 + 0xB4)) = 1.5f;
            }
            flyer_update(arg0);
            return;
        }
    } else {
        node_destroy((struct102 *) arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_perched_update.s")
#endif
s32 approx_dist2_int(s32, s32, s32, s32);
void flyer_update(u8 *);

/* was func_151770F4 */
void flyer_resting_update(u8 *arg0) {
    s32 v;

    if (((Row20 *)D_800DDE80)[arg0[0xED]].x0 == 0 || D_800DDF78[arg0[0xED]] == 0) {
        node_destroy((struct102 *)arg0);
        return;
    }
    v = arg0[0xF0];
    if (arg0[0xF1] == 0) {
        if (D_800DDF5C[arg0[0x90]] == 0) {
            arg0[0xF1] = 1;
        } else if (v != 0xFF) {
            v += D_800BE9E4 * 4;
            if (v > 0xFF) {
                v = 0xFF;
            }
            arg0[0xF0] = v;
        }
    } else {
        if (v == 0) {
            node_destroy((struct102 *)arg0);
            return;
        }
        v -= D_800BE9E4 * 4;
        if (v < 0) {
            v = 0;
        }
        arg0[0xF0] = v;
    }
    D_800DDF68[arg0[0xED]] = 1;
    switch (arg0[0x91]) {
        case 0:
            if (approx_dist2_int(*(f32 *)((u8 *)D_800CC2D0 + 0x14), *(f32 *)((u8 *)D_800CC2D0 + 0x1C),
                              *(f32 *)(arg0 + 0x98), *(f32 *)(arg0 + 0xA0)) < 200) {
                arg0[0x91] = 2;
                *(f32 *)(arg0 + 0xE4) = (f32)((u32)random_int() % *(s16 *)(arg0 + 0xDA));
                *(f32 *)(arg0 + 0xE4) += *(s16 *)(arg0 + 0xD2);
                *(s32 *)(arg0 + 0x94) = D_800DE2B8[arg0[0xED]].x0;
            } else {
                *(s32 *)(arg0 + 0x94) = D_800DE2B4[arg0[0xED]].x0;
            }
            return;
        case 2:
        case 3:
            break;
        case 4:
            if (*(f32 *)(arg0 + 0x9C) < *(f32 *)(arg0 + 0xC8)) {
                node_destroy((struct102 *)arg0);
                return;
            }
            break;
    }
    flyer_update(arg0);
}

#ifdef NON_MATCHING
void mtxf_mul(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
Gfx *gfx_other_mode_cached(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);
extern u8 D_800A7550[4];
extern Row20 D_800DE2BC[];

// prop_model_draw: draws the object's model (kinds 1..3 of flyer_draw) unless its row of D_800DDE80 / D_800DDF78
// (index obj[0xED]) is empty: matrix = yaw (+0xAC) after pitch / roll (+0xA8 / +0xB0), scaled by +0xC0, at +0x98..+0xA0
// (into the object's per-frame matrix slot +0x10 + D_800BE9C0 * 0x40), segment 1 = +0x94, render mode
// (gfx_other_mode_cached) and env colour (v, v, v, obj[0xF0]) where v (obj[0xEC]) fades by 4 per frame towards
// D_800A7550[(+0xE8 >> 5) & 3], then the row's display list (D_800DE2BC).
/* was func_15177360 */
Gfx *flyer_model_draw(Gfx *gdl, u8 *obj, s16 arg2) {
    f32 mf[4][4];
    f32 rot[4][4];
    s32 v;
    s32 target;
    u8 flag;

    if (((Row20 *)D_800DDE80)[obj[0xED]].x0 == 0 || D_800DDF78[obj[0xED]] == 0) {
        return gdl;
    }
    mtxf_rotate_xyz_deg(mf, 0.0f, *(f32 *)(obj + 0xAC), 0.0f);
    mtxf_rotate_xyz_deg(rot, *(f32 *)(obj + 0xA8), 0.0f, *(f32 *)(obj + 0xB0));
    mtxf_mul(rot, mf, mf);
    mf[3][0] = *(f32 *)(obj + 0x98);
    mf[3][1] = *(f32 *)(obj + 0x9C);
    mf[3][2] = *(f32 *)(obj + 0xA0);
    mf[0][0] *= *(f32 *)(obj + 0xC0);
    mf[0][1] *= *(f32 *)(obj + 0xC0);
    mf[0][2] *= *(f32 *)(obj + 0xC0);
    mf[1][0] *= *(f32 *)(obj + 0xC0);
    mf[1][1] *= *(f32 *)(obj + 0xC0);
    mf[1][2] *= *(f32 *)(obj + 0xC0);
    mf[2][0] *= *(f32 *)(obj + 0xC0);
    mf[2][1] *= *(f32 *)(obj + 0xC0);
    mf[2][2] *= *(f32 *)(obj + 0xC0);
    guMtxF2L(mf, (Mtx *)(obj + 0x10 + (D_800BE9C0 << 6)));
    gSPMatrix(gdl++, obj + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gdl++, 1, *(s32 *)(obj + 0x94));
    gDPPipeSync(gdl++);

    v = obj[0xEC];
    target = D_800A7550[(*(u32 *)(obj + 0xE8) >> 5) & 3];
    if (v != target) {
        if (v < target) {
            v += D_800BE9E4 * 4;
            if (v > target) {
                v = target;
            }
        } else {
            v -= D_800BE9E4 * 4;
            if (v < 0) {
                v = 0;
            }
        }
        obj[0xEC] = v;
    }
    flag = 0;
    gdl = gfx_other_mode_cached(gdl, 0x82CA0, 0x504A50, &flag);
    gDPSetEnvColor(gdl++, v, v, v, obj[0xF0]);
    gSPDisplayList(gdl++, D_800DE2BC[obj[0xED]].x0);
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_model_draw.s")
#endif

#ifdef NON_MATCHING
s32 view_point_cull_test(u8 *, f32, f32, f32, f32, f32, f32, f32, s32, s32);
#else
s32 view_point_cull_test(u8 *, s32, s32, s32, f32, f32, f32, f32, s32, s32);
#endif
Gfx *flyer_model_draw(Gfx *, u8 *, s16);
extern f32 D_800D3A00;
extern f32 D_800D3A04;
extern f32 D_800D9F40;
extern u8 D_800DA030[];

/* was func_15177638 */
Gfx *flyer_draw(Gfx *gdl, u8 *arg1, s16 arg2) {
    f32 mf[4][4];
    s32 pad[2];

#ifdef NON_MATCHING
    if (view_point_cull_test(&D_800DA030[arg2 << 6], *(f32 *)(arg1 + 0x98), *(f32 *)(arg1 + 0x9C), *(f32 *)(arg1 + 0xA0), D_800D9F40, 4000.0f, D_800D3A00, D_800D3A04, 0, 0) == 0) {
#else
    if (view_point_cull_test(&D_800DA030[arg2 << 6], *(s32 *)(arg1 + 0x98), *(s32 *)(arg1 + 0x9C), *(s32 *)(arg1 + 0xA0), D_800D9F40, 4000.0f, D_800D3A00, D_800D3A04, 0, 0) == 0) {
#endif
        switch (arg1[0x91]) {
        case 0:
            mtxf_rotate_xyz_deg(mf, *(f32 *)(arg1 + 0xA8), *(f32 *)(arg1 + 0xAC), *(f32 *)(arg1 + 0xB0));
            mf[3][0] = *(f32 *)(arg1 + 0x98);
            mf[3][1] = *(f32 *)(arg1 + 0x9C);
            mf[3][2] = *(f32 *)(arg1 + 0xA0);
            guMtxF2L(mf, arg1 + 0x10 + (D_800BE9C0 << 6));
            gSPMatrix(gdl++, arg1 + 0x10 + (D_800BE9C0 << 6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(gdl++, 1, D_800DDE80[0x33]);
            gSPDisplayList(gdl++, D_800DDE80[0x35]);
            break;
        case 1:
        case 2:
        case 3:
        default:
            gdl = flyer_model_draw(gdl, arg1, arg2);
            break;
        }
    }
    return gdl;
}

#ifdef NON_MATCHING
extern s32 D_8008D450;

/* was func_151777CC */
void flyer_wing_flap_animate(u8 arg0) {
    f32 sp28;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    s32 temp_a0;
    s32 temp_f16;
    s32 temp_f18;
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_s1;
    s32 temp_t6;
    u8 *temp_s0;

    temp_t6 = arg0;
    temp_s0 = ((s32 *)((u8 *)&D_8008D450 + (temp_t6 * 0x38)));
    temp_s1 = D_800DE2B8[temp_t6].x0;
    temp_f2 = func_150AD78C((*(f32 *)((u8 *)temp_s0 + 0x24)) * 0.017453292f) * (*(f32 *)((u8 *)temp_s0 + 0x28));
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = temp_f2;
    temp_f20 = temp_f2 * 0.017453292f;
    sp28 = func_150AD78C(temp_f20);
    temp_f2_2 = (*(f32 *)((u8 *)temp_s0 + 0x30));
    temp_f18 = (s32) (temp_f2_2 * func_150AD780(temp_f20));
    temp_f8 = (s32) (temp_f2_2 * sp28);
    temp_a0 = -temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0xA0)) = (s16) temp_a0;
    (*(s16 *)((u8 *)temp_s1 + 0xB0)) = (s16) temp_a0;
    (*(s16 *)((u8 *)temp_s1 + 0x110)) = (s16) temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0x120)) = (s16) temp_f18;
    (*(s16 *)((u8 *)temp_s1 + 0x112)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0x122)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0xA2)) = (s16) temp_f8;
    (*(s16 *)((u8 *)temp_s1 + 0xB2)) = (s16) temp_f8;
    temp_f2_3 = func_150AD78C(((*(f32 *)((u8 *)temp_s0 + 0x24)) - 30.0f) * 0.017453292f) * (*(f32 *)((u8 *)temp_s0 + 0x28));
    (*(f32 *)((u8 *)temp_s0 + 0x18)) = temp_f2_3;
    temp_f20_2 = temp_f2_3 * 0.017453292f;
    sp28 = func_150AD78C(temp_f20_2);
    temp_f2_4 = (*(f32 *)((u8 *)temp_s0 + 0x34));
    temp_f16 = (s32) (temp_f2_4 * func_150AD780(temp_f20_2));
    temp_f6 = (s32) (temp_f2_4 * sp28);
    (*(s16 *)((u8 *)temp_s1 + 0xE0)) = (s16) -temp_f16;
    (*(s16 *)((u8 *)temp_s1 + 0x130)) = (s16) temp_f16;
    (*(s16 *)((u8 *)temp_s1 + 0xE2)) = (s16) temp_f6;
    (*(s16 *)((u8 *)temp_s1 + 0x132)) = (s16) temp_f6;
    (*(f32 *)((u8 *)temp_s0 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x24)) + (*(f32 *)((u8 *)temp_s0 + 0x1C)));
    temp_f12 = (*(f32 *)((u8 *)temp_s0 + 0x24));
    if (temp_f12 >= 360.0f) {
        (*(f32 *)((u8 *)temp_s0 + 0x24)) = (f32) (temp_f12 - 360.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A2970/flyer_wing_flap_animate.s")
#endif