#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_151AD010
s32 func_151AD0E8(u8 *, u8 *);


#ifdef NON_MATCHING
/* P155 */
u8 func_151D8E20(void);
void func_1514CBE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9,
                   s32 argA, u8 argB);
void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 *arg4, s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9);
typedef struct {
    f32 size;         /* 0x0 */
    s16 count;        /* 0x4 */
    u16 countRange;   /* 0x6 */
} DebrisDefAC3F0;
typedef struct {
    f32 u0;           /* 0x0 */
    s16 u4;           /* 0x4 */
    f32 u8;           /* 0x8 */
} FlashDefAC3F0;
extern s8 D_800A9400[][5];          /* per kind: chunk def, dust def, flash def (-1 = none) */
extern DebrisDefAC3F0 D_800A9420[]; /* chunks (type 0xB) */
extern DebrisDefAC3F0 D_800A9538[]; /* dust (type 0xC) */
extern FlashDefAC3F0 D_800A963C[];  /* flash */

// debris_burst_spawn: P153: the debris of a broken object of `kind` at pos (src = the owner): per D_800A9400[kind]
// a chunk burst (func_1514CBE8 type 0xB, def D_800A9420) and a dust burst (type 0xC, D_800A9538) with count
// +4 + random [0, +6], each with the owner block {src, arg4, light} (light = func_151D8E20()), and when src +0x1C
// bit 0 is set a flash (func_151DBE80, D_800A963C, 150) at pos, src + 4.
void func_151AC3F0(f32 *pos, u8 *src, s32 kind, u8 arg3, s32 arg4) {
    struct {
        u8 *src;
        s32 arg;
        u8 light;
    } chunkOwner, dustOwner;
    s8 *def;
    DebrisDefAC3F0 *d;
    FlashDefAC3F0 *fl;
    u8 light;

    light = func_151D8E20();
    if (src == NULL) {
        return;
    }
    def = D_800A9400[kind];
    if (def[0] != -1) {
        chunkOwner.src = src;
        chunkOwner.light = light;
        chunkOwner.arg = arg4;
        d = &D_800A9420[def[0]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xB, kind, 0.0f, (s32) &chunkOwner, arg3);
    }
    if (def[2] != -1) {
        dustOwner.src = src;
        dustOwner.arg = arg4;
        dustOwner.light = light;
        d = &D_800A9538[def[2]];
        func_1514CBE8(pos[0], pos[1], pos[2], d->size, 0, 0xFF, (u32) func_150ADA20() % (u32) (d->countRange + 1) + d->count,
                      0xC, kind, 0.0f, (s32) &dustOwner, arg3);
    }
    if (def[4] != -1 && (src[0x1C] & 1)) {
        fl = &D_800A963C[def[4]];
        func_151DBE80(light, fl->u0, fl->u8, fl->u4, (u8 *) pos, (s32) (src + 4), 0x96, 0, arg3, arg4);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC3F0.s")
#endif

#ifdef NON_MATCHING
/* P191 */
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s8 D_800A9400[][5];
extern u8 D_800AB7D4[];
extern u8 D_800AB7E4[];
/* owner block the debris spawner func_151AC3F0 passes through the burst emitter (argA of the D_8008ADA0 handlers) */
typedef struct {
    s32 src;   /* 0x0 */
    s32 arg;   /* 0x4 */
    u8 light;  /* 0x8 */
} SpawnOwnerAC628;
/* chunk particle definition (D_800A9448, 0x30 bytes, index D_800A9400[kind][1]) */
typedef struct {
    u8 colBase;        /* 0x00: colour byte 2 = colBase + random [0, colRange] */
    u8 colRange;       /* 0x01 */
    s16 pitchBase;     /* 0x02: byte angle from vertical */
    u16 pitchRange;    /* 0x04 */
    f32 speedBase;     /* 0x08 */
    f32 speedRange;    /* 0x0C */
    s32 b15Base;       /* 0x10 */
    s32 b15Range;      /* 0x14 */
    s16 lifeBase;      /* 0x18 */
    u16 lifeRange;     /* 0x1A */
    f32 widthBase;     /* 0x1C */
    f32 widthRange;    /* 0x20 */
    f32 v10Base;       /* 0x24 */
    f32 v10Range;      /* 0x28 */
    f32 trailChance;   /* 0x2C */
} ChunkDefAC628;
extern ChunkDefAC628 D_800A9448[];

// debris_chunk_emit: P191: D_8008ADA0 handler 0xB (the chunk bursts of debris_burst_spawn func_151AC3F0, emitted by
// func_1514CBE8 / the ring, line and arc emitters): spawns one chunk particle (func_15148310, update kind 8) at
// (x, y, z) with the definition D_800A9448[D_800A9400[kind][1]]: speed (random in the def range) along the byte angle
// a (x / z) tilted by a random pitch (y = -speed * cos(pitch)); colour bytes D_800AB7D4[light], 0xFF, random; flag
// 0x20 when D_800AB7E4[light]; with probability trailChance flags 3 and the trail args (6, 2). y is also stored in
// the shape (+0x14). The owner block argA gives the owner (src, arg) and the light. Returns 1 (keep emitting).
s32 func_151AC628(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 kind,
                  f32 arg9, s32 argA, s32 argB) {
    SpawnOwnerAC628 *owner = (SpawnOwnerAC628 *) argA;
    ChunkDefAC628 *def = &D_800A9448[D_800A9400[kind][1]];
    struct {
        s32 w[7];   /* 0x00 */
        u8 b1C;
        u8 b1D;
    } style;
    struct {
        f32 width;  /* 0x00 */
        f32 vel[3]; /* 0x04 */
        f32 v10;    /* 0x10 */
        f32 y;      /* 0x14 */
        u8 flags;   /* 0x18 */
        u8 col[3];  /* 0x19 */
    } shape;
    struct {
        f32 x;      /* 0x00 */
        f32 y;
        f32 z;
        s16 life;   /* 0x0C */
        s16 sE;
        s32 s10;
        u8 b14;
        u8 b15;
    } at;
    f32 sinA, cosA, sinP, cosP, speed, hv;
    s32 trailA, trailB;
    s16 pitch;

    sinA = func_151423D8(a & 0xFF);
    cosA = func_151423D8((a - 0x40) & 0xFF);
    style.w[0] = 0;
    style.w[1] = 1;
    style.w[2] = 0x160600;
    style.w[3] = 1;
    style.w[4] = 0x10;
    style.w[5] = 0x80;
    style.w[6] = 0x20;
    style.b1C = 0;
    style.b1D = 9;
    at.s10 = 1;
    at.sE = 1;
    at.y = y;
    shape.y = y;
    at.x = x;
    at.z = z;
    shape.col[0] = D_800AB7D4[owner->light];
    shape.col[1] = 0xFF;
    shape.flags = (D_800AB7E4[owner->light] ? 0x20 : 0) | 8;
    if (func_150ADA68() < def->trailChance) {
        shape.flags |= 3;
        trailA = 6;
        trailB = 2;
    } else {
        trailA = 0;
        trailB = 0;
        shape.flags &= ~3;
    }
    shape.col[2] = (u32) func_150ADA20() % (u32) (def->colRange + 1) + def->colBase;
    pitch = (u32) func_150ADA20() % (u32) (def->pitchRange + 1) + def->pitchBase;
    sinP = func_151423D8(pitch & 0xFF);
    cosP = func_151423D8((pitch - 0x40) & 0xFF);
    speed = func_150ADA68() * def->speedRange + def->speedBase;
    hv = speed * sinP;
    shape.vel[0] = hv * cosA;
    shape.vel[1] = -speed * cosP;
    shape.vel[2] = hv * sinA;
    at.b15 = (u32) func_150ADA20() % (u32) (def->b15Range + 1) + def->b15Base;
    at.life = (u32) func_150ADA20() % (u32) (def->lifeRange + 1) + def->lifeBase;
    shape.width = func_150ADA68() * def->widthRange + def->widthBase;
    shape.v10 = func_150ADA68() * def->v10Range + def->v10Base;
    func_15148310((u8 *) &at, (s32) &shape, 0, 1, 8, 0, trailA, trailB, 0, 0, 0, (u8 *) &style, owner->src, argB & 0xFF,
                  owner->arg);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AC628.s")
#endif

s32 func_151AC97C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    s32 var_v1 = *(s16 *)(arg0 + 0x1C) * 8;

    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = var_v1;
    }
    return 1;
}

typedef struct { f32 x, y, z; s32 a, b; } Node14;
u8 func_151D8E20(void);
void func_151DAB58(u8, f32, u8, f32 *, u8, u8, s32);
s32 func_151AC9B8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    u8 *tbl;
    u8 *obj;
    f32 pos[3];
    u8 id;

    tbl = *(u8 **)(arg0 + 0x94);
    obj = *(u8 **)(arg0 + 0x98);
    pos[0] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].x;
    pos[1] = arg4;
    pos[2] = ((Node14 *)tbl)[*(s8 *)(arg0 + 0x2D)].z;
    id = func_151D8E20();
    if (func_150ADA20() & 1) {
        func_151D9B8C(id, *(f32 *)(obj + 0) * 6.0f, *(u8 *)(obj + 0x1B), arg5, (struct17 *)pos, func_150ADA20() % 41U + 0x50, 1, 1, 0, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    } else {
        func_151DAB58(id, *(f32 *)(obj + 0) * 1.5f, *(u8 *)(obj + 0x1B), pos, 1, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    }
    *(s8 *)(obj + 0x20) = 4;
    return 1;
}

s32 func_151ACB00(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    u8 *sp44;
    f32 (*tab)[5];
    f32 sp34[3];
    sp44 = *(u8 **)(arg0 + 0x98);
    tab = *(f32 (**)[5])(arg0 + 0x94);
    sp34[0] = tab[*(s8 *)(arg0 + 0x2D)][0];
    sp34[1] = arg4;
    sp34[2] = tab[*(s8 *)(arg0 + 0x2D)][2];
    func_151DBCBC(func_151D8E20(), *(f32 *)(sp44 + 0) * 7.0f, *(u8 *)(sp44 + 0x1B), arg5, sp34, *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    *(s8 *)(sp44 + 0x20) = 4;
    return 1;
}

#ifdef NON_MATCHING
/* P191 */
void func_15143794(s16, s16, f32, void *);
extern s8 D_800A9400[][5];
/* owner block the debris spawner func_151AC3F0 passes through the burst emitter (argA of the D_8008ADA0 handlers) */
typedef struct {
    s32 src;   /* 0x0 */
    s32 arg;   /* 0x4 */
    u8 light;  /* 0x8 */
} SpawnOwnerACBCC;
/* dust particle definition (D_800A9560, 0x2C bytes, index D_800A9400[kind][3]) */
typedef struct {
    s16 u0;              /* 0x00: not read here */
    s16 u2;              /* 0x02 */
    s16 pitchBase;       /* 0x04 */
    u16 pitchRange;      /* 0x06 */
    f32 speedBase;       /* 0x08 */
    f32 speedRange;      /* 0x0C */
    s16 lifeBase;        /* 0x10 */
    u16 lifeRange;       /* 0x12 */
    u8 alphaBase;        /* 0x14 */
    u8 alphaRange;       /* 0x15 */
    f32 sizeBase;        /* 0x18 */
    f32 sizeRange;       /* 0x1C */
    f32 valBase;         /* 0x20 */
    f32 valRange;        /* 0x24 */
    f32 additiveChance;  /* 0x28 */
} DustDefACBCC;
extern DustDefACBCC D_800A9560[];

// debris_dust_emit: P191: D_8008ADA0 handler 0xC (the dust bursts of debris_burst_spawn func_151AC3F0): spawns one
// dust particle (particle_spawn func_151D9014, kind = the owner's light) at (x, y, z) with the definition
// D_800A9560[D_800A9400[kind][3]]: velocity from func_15143794(yaw = a, random pitch, random speed); random value,
// life, alpha and size from the def ranges; additive with probability additiveChance; grow 1.0 / 1.0, lit, group =
// the owner's src word, no fade, room argB, owner = the owner's arg. Returns 1 (keep emitting).
s32 func_151ACBCC(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 kind,
                  f32 arg9, s32 argA, s32 argB) {
    SpawnOwnerACBCC *owner = (SpawnOwnerACBCC *) argA;
    DustDefACBCC *def = &D_800A9560[D_800A9400[kind][3]];
    f32 pos[3];
    f32 vel[3];
    f32 speed;
    f32 fVal, fSize, fAdd;
    s32 rPitch, rLife, rAlpha;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    rPitch = func_150ADA20();
    speed = func_150ADA68() * def->speedRange + def->speedBase;
    func_15143794(a, (u32) rPitch % (u32) (def->pitchRange + 1) + def->pitchBase, speed, vel);
    fVal = func_150ADA68();
    rLife = func_150ADA20();
    rAlpha = func_150ADA20();
    fSize = func_150ADA68();
    fAdd = func_150ADA68();
    func_151D9014(pos, vel, owner->light, fVal * def->valRange + def->valBase,
                  (u32) rLife % (u32) (def->lifeRange + 1) + def->lifeBase,
                  (u32) rAlpha % (u32) (def->alphaRange + 1) + def->alphaBase, fSize * def->sizeRange + def->sizeBase,
                  fAdd < def->additiveChance, 1.0f, 1.0f, 1, owner->src, 1, 0, argB & 0xFF, owner->arg);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBCC.s")
#endif

s32 func_151D6310(s32, s16, s32, u8 **, u8 *);
extern f32 D_800DD608[];
extern f32 D_800DD618[];

u8 *func_151ACDC0(u8 *arg0, s16 arg1) {
    u8 *sp4C;
    u8 *sp48;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f14;
    u8 sp37;

    func_151D6310((s32)(arg0 + 0x100), arg1, 0x40, &sp4C, &sp37);
    sp48 = sp4C;
    if (sp4C != NULL) {
        if (sp37 != 0) {
            memcpy(((u8 **)(arg0 + 0x100))[arg1], arg0 + 0xC0, 0x40);
            memcpy(((u8 **)(arg0 + 0x100))[arg1] + 0x40, arg0 + 0xC0, 0x40);
        }
    } else {
        return NULL;
    }
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0x4C)) * (*(f32 *)((u8 *)arg0 + 0x2C));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x50)) * (*(f32 *)((u8 *)arg0 + 0x30));
    temp_f2 = D_800DD608[arg1] * temp_f0;
    temp_f12 = D_800DD618[arg1] * temp_f0;
    *(s16 *)(sp4C + 6) = 0;
    *(s16 *)(sp4C + 0x16) = 0;
    *(s16 *)(sp4C + 0x26) = 0;
    *(s16 *)(sp4C + 0x36) = 0;
    *(s16 *)(sp4C + 0) = *(s16 *)(sp4C + 0x30) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + temp_f12);
    *(s16 *)(sp4C + 2) = *(s16 *)(sp4C + 0x12) = (s32) (*(f32 *)((u8 *)arg0 + 0x38));
    *(s16 *)(sp4C + 4) = *(s16 *)(sp4C + 0x34) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - temp_f2);
    *(s16 *)(sp4C + 0x10) = *(s16 *)(sp4C + 0x20) = (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - temp_f12);
    *(s16 *)(sp4C + 0x22) = *(s16 *)(sp4C + 0x32) = (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f14);
    *(s16 *)(sp4C + 0x14) = *(s16 *)(sp4C + 0x24) = (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + temp_f2);
    return sp48;
}

s32 func_151ACF9C(f32 *arg0) {
    f32 temp_f0 = arg0[0x4C / 4] * D_800BE9A4;

    arg0[0x2C / 4] += temp_f0;
    arg0[0x30 / 4] += temp_f0;
    return 1;
}

s32 func_151ACFD0(u8 *arg0) {
    s32 var_v0 = 0xFF;
    s16 temp_v1 = *(s16 *)(arg0 + 0x1C);

    if (temp_v1 < 0x10) {
        var_v0 = (s16)(temp_v1 * 16);
    }
    if (var_v0 < arg0[0x5C]) {
        arg0[0x5C] = var_v0;
    }
    return 1;
}

u8 *func_151AD010(u8 *arg0, f32 arg1, s32 arg2) {
    u8 *temp_v0;

    if (arg0 == NULL) {
        return NULL;
    }
    temp_v0 = func_15167A68(0x30, 0, arg2 + 0x30, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    if (func_151AD0E8(arg0, temp_v0 + 0x18) == 0) {
        func_1516979C((struct102 *)temp_v0);
        return NULL;
    }
    *(u8 **)(temp_v0 + 0x1C) = arg0;
    temp_v0[0x20] = arg0[0x3B];
    *(s32 *)(temp_v0 + 0x24) = (struct127 *)arg0 - D_800CC2D0;
    *(f32 *)(temp_v0 + 0x28) = arg1;
    *(s32 *)(temp_v0 + 0x10) = 1;
    *(s32 *)(temp_v0 + 0x14) = 0;
    return temp_v0;
}

s32 func_151AD0E8(u8 *arg0, u8 *arg1) {
    s32 ret = 0;

    if (arg0[0x3B] == 1) {
        *arg1 = 1;
        ret = 1;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_151AE958(u8 *arg0);
#else
s32 func_151AE958();
#endif

void func_151AD110(u8 *arg0) {
    s32 temp = *(s32 *)(*(u8 **)(*(u8 **)(arg0 + 0x1C) + 0x31C) + 0x9C);
    if (temp != 0) {
        func_151AE958(arg0);
    }
    if (arg0) {} // keeps arg0 live past the call (home-slot store); likely a stripped debug macro
}

void func_151AD144(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x1C), (s32)(arg0 + 0x20), (s32)arg0);
}

#ifdef NON_MATCHING
/* P183 */
void *allocate_memory(s32, s32, s32, s32);

// light_column_create: P183: creates the light-column effect (func_15167A68 kind 0x4E in level 0x2C, else 0x2F;
// layer arg1 + 0x58) from the 0x24-byte zone record arg0 (copied to +0x10: point +0x14..+0x1C, bottom y +0x24,
// +0x2C scale -> +0x34 = 1 / scale). +0x38 = 20 points (0x18 bytes) up the column from y = bottom to the top
// (+0x18) in 19 steps at the point's x / z, +0x3C = step height, +0x48 = 2 x 20 quads of 4 Vtx (texture 0x37 in
// level 0xB, else 0x36: s = 0 / w/4 / w/2 / 3w/4 (+0x100, << 5), t = (0x100 + i * (h - 1)) << 5 (<< 4 for 0x37),
// flag 0, colour (0x58, 0x4B, 0x2C) in level 0x39 else white, alpha 0xFF). Returns the effect (0 without one).
s32 func_151ACBD4(s8 *arg0, s32 arg1) {
    u8 *e;
    f32 *pt;
    Vtx *v;
    s32 x, top, bottom, z, dy;
    s32 i, k;
    s32 shift;
    s32 tw, th;
    s32 t;
    s32 s1, s2, s3;
    u8 r, g, b;
    struct_eu_80090F10 *tex;

    e = func_15167A68((D_800BE9F0 == 0x2C) ? 0x4E : 0x2F, 0, arg1 + 0x58, 1, 0xFF, 1);
    if (e == NULL) {
        return 0;
    }
    memcpy(e + 0x10, arg0, 0x24);
    *(s32 *) (e + 0x44) = 0;
    *(s16 *) (e + 0x52) = 0;
    *(f32 *) (e + 0x34) = 1.0f / *(f32 *) (e + 0x2C);
    *(f32 **) (e + 0x38) = allocate_memory(0x1E0, 1, 0, 0);
    x = *(f32 *) (e + 0x14);
    top = *(f32 *) (e + 0x18);
    z = *(f32 *) (e + 0x1C);
    bottom = *(f32 *) (e + 0x24);
    e[0x42] = 20;
    dy = top - bottom;
    for (i = 0; i < 20; i++) {
        pt = *(f32 **) (e + 0x38) + i * 6;
        pt[0] = x;
        pt[1] = (dy * i) / 19 + bottom;
        pt[2] = z;
        pt[3] = 0.0f;
        pt[4] = 0.0f;
        pt[5] = 0.0f;
    }
    *(f32 *) (e + 0x3C) = (f32) (top - bottom) / 19.0f;
    *(Vtx **) (e + 0x48) = allocate_memory(0xA00, 1, 2, 0);

    if (D_800BE9F0 == 0xB) {
        *(u16 *) (e + 0x40) = 0x37;
        shift = 4;
    } else {
        *(u16 *) (e + 0x40) = 0x36;
        shift = 5;
    }
    if (D_800BE9F0 == 0x39) {
        r = 0x58;
        g = 0x4B;
        b = 0x2C;
    } else {
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
    }
    tex = &D_80090F10[*(u16 *) (e + 0x40)];
    tw = tex->unk6 >> 2;
    th = tex->unk8 - 1;
    s1 = (tw + 0x100) << 5;
    s2 = (tw * 2 + 0x100) << 5;
    s3 = (tw * 3 + 0x100) << 5;
    for (k = 0; k < 2; k++) {
        v = *(Vtx **) (e + 0x48) + k * 80;
        t = 0x100;
        for (i = 0; i < 20; i++, v += 4) {
            s32 tt = t << shift;

            t += th;
            v[0].v.flag = 0;
            v[0].v.tc[0] = 0x2000;
            v[0].v.tc[1] = tt;
            v[0].v.cn[0] = r;
            v[0].v.cn[1] = g;
            v[0].v.cn[2] = b;
            v[0].v.cn[3] = 0xFF;
            v[1].v.flag = 0;
            v[1].v.tc[0] = s1;
            v[1].v.tc[1] = tt;
            v[1].v.cn[0] = r;
            v[1].v.cn[1] = g;
            v[1].v.cn[2] = b;
            v[1].v.cn[3] = 0xFF;
            v[2].v.flag = 0;
            v[2].v.tc[0] = s2;
            v[2].v.tc[1] = tt;
            v[2].v.cn[0] = r;
            v[2].v.cn[1] = g;
            v[2].v.cn[2] = b;
            v[2].v.cn[3] = 0xFF;
            v[3].v.flag = 0;
            v[3].v.tc[0] = s3;
            v[3].v.tc[1] = tt;
            v[3].v.cn[0] = r;
            v[3].v.cn[1] = g;
            v[3].v.cn[2] = b;
            v[3].v.cn[3] = 0xFF;
        }
    }
    *(f32 *) (e + 0x4C) = 0.0f;
    return (s32) e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ACBD4.s")
#endif

#ifdef NON_MATCHING
f32 func_150489B0(u8);

// rope_update: per-node update of the hanging rope (render layers 0x2F / 0x4E, built by func_151ACBD4): counts
// down the +0x52 timer, applies the push of the attached object +0x44 (its controller +0x31C: point +0xAE gets
// strength +0xA8 * 1.9 along angle +0xAC + the object's heading, the object's own speed +0x3C * 19 along the heading,
// and -1000 vertical; the controller's +0xAD frame count ends the push), then the decaying kick +0x4C (angle +0x50,
// point +0x51, * 0.9 per frame). The points (+0x38, 6 floats each: position, velocity) are relaxed from the
// second-last up to the first: gravity -9 split along the segment, velocity damping 0.96, a bending pull towards the
// neighbours' midpoint, a 1150 x limit in level 0x39 and a fixed segment length +0x3C to the point below. When the
// summed x / z speed exceeds 250 a creak sound (0x507 + random 0..8) starts unless the last one (+0x54) still plays.
void func_151AD724(u8 *e) {
    f32 pos[20][3];
    f32 cur[3];
    f32 vel[3];
    f32 acc[3];
    f32 total;
    f32 amp, dx, dy, dz, len, horiz, side, side2, s, bend;
    f32 *p;
    u8 *obj;
    u8 *ctl;
    u8 ang;
    s32 last, i, j, k, frames;

    total = 0.0f;
    if (*(s16 *) (e + 0x52) != 0) {
        *(s16 *) (e + 0x52) -= D_800BE9E4;
        if (*(s16 *) (e + 0x52) < 0) {
            *(s16 *) (e + 0x52) = 0;
        }
    }
    last = e[0x42] - 1;
    obj = *(u8 **) (e + 0x44);
    if (obj != NULL) {
        ctl = *(u8 **) (obj + 0x31C);
        i = ctl[0xAE];
        ang = ctl[0xAC] + (*(u16 *) (obj + 0x76) >> 8);
        amp = *(f32 *) (ctl + 0xA8) * 1.9f;
        p = *(f32 **) (e + 0x38) + i * 6;
        p[3] += amp * func_150489B0(ang);
        p = *(f32 **) (e + 0x38) + i * 6;
        p[5] -= amp * func_15048A40(ang);
        obj = *(u8 **) (e + 0x44);
        ang = *(u16 *) (obj + 0x76) >> 8;
        amp = *(f32 *) (obj + 0x3C) * 19.0f;
        p = *(f32 **) (e + 0x38) + i * 6;
        p[3] += amp * func_150489B0(ang);
        p = *(f32 **) (e + 0x38) + i * 6;
        p[5] -= amp * func_15048A40(ang);
        p = *(f32 **) (e + 0x38) + i * 6;
        p[4] -= 1000.0f;
        ctl = *(u8 **) (*(u8 **) (e + 0x44) + 0x31C);
        frames = ctl[0xAD] - 1;
        if (frames > 0) {
            ctl[0xAD] = frames;
        } else {
            *(f32 *) (ctl + 0xA8) = 0.0f;
            ctl = *(u8 **) (*(u8 **) (e + 0x44) + 0x31C);
            ctl[0xAD] = 0;
        }
    }
    if (*(f32 *) (e + 0x4C) != 0.0f) {
        p = *(f32 **) (e + 0x38) + e[0x51] * 6;
        p[3] -= *(f32 *) (e + 0x4C) * func_150489B0(e[0x50]);
        p = *(f32 **) (e + 0x38) + e[0x51] * 6;
        p[5] += *(f32 *) (e + 0x4C) * func_15048A40(e[0x50]);
        *(f32 *) (e + 0x4C) *= 0.9f;
    }
    for (i = 0; i < last + 1; i++) {
        for (k = 0; k < 3; k++) {
            pos[i][k] = (*(f32 **) (e + 0x38))[i * 6 + k];
        }
    }
    for (j = last - 1; j >= 0; j--) {
        for (k = 0; k < 3; k++) {
            cur[k] = pos[j][k];
            vel[k] = (*(f32 **) (e + 0x38))[j * 6 + 3 + k];
        }
        dx = cur[0] - pos[j + 1][0];
        dy = cur[1] - pos[j + 1][1];
        dz = cur[2] - pos[j + 1][2];
        len = sqrtf(dx * dx + dy * dy + dz * dz);
        horiz = sqrtf(dx * dx + dz * dz);
        if (len == 0.0f) {
            len = 1.0f;
        }
        side = 9.0f * (horiz / len);
        side2 = side * side;
        s = 9.0f * 9.0f - side2;
        if (side2 <= 9.0f * 9.0f) {
            s = sqrtf(s);
        } else {
            s = 0.0f;
        }
        s /= len;
        acc[0] = 0.0f - dx * s;
        acc[1] = -9.0f - dy * s;
        acc[2] = 0.0f - dz * s;
        for (k = 0; k < 3; k++) {
            vel[k] += acc[k];
            vel[k] *= 0.96f;
            if (j != 0) {
                bend = (pos[j - 1][k] + pos[j + 1][k]) * 0.5f - cur[k];
                vel[k] += bend * 1.24;
            }
            cur[k] += vel[k];
            if (D_800BE9F0 == 0x39 && cur[0] > 1150.0f) {
                cur[0] = 1150.0f;
            }
        }
        p = *(f32 **) (e + 0x38) + j * 6;
        dz = cur[2] - p[8];
        dx = cur[0] - p[6];
        dy = cur[1] - p[7];
        total += fabsf(vel[0]);
        total += fabsf(vel[2]);
        len = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (len == 0.0f) {
            s = 1.0f;
        } else {
            s = *(f32 *) (e + 0x3C) / len;
        }
        for (k = 0; k < 3; k++) {
            p = *(f32 **) (e + 0x38) + j * 6;
            p[k] = (cur[k] - p[6 + k]) * s + p[6 + k];
            p = *(f32 **) (e + 0x38) + j * 6;
            p[3 + k] = p[k] - pos[j][k];
        }
    }
    if (total > 250.0f) {
        if (*(u16 *) (e + 0x54) == 0 || func_1000F3D0(*(u16 *) (e + 0x54)) == 0) {
            *(u16 *) (e + 0x54) = func_10010E78(0, (u32) func_150ADA20() % 9 + 0x507, 30000, 0, 0, 0, (s32) cur[0],
                                                (s32) cur[1], (s32) cur[2], 250, -0x7E0C);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AD724.s")
#endif

#ifdef NON_MATCHING
s32 func_150953F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800D30BC;

// rope_draw: render-layer draw callback of the rope (layers 0x2F / 0x4E): writes 4 vertices per point into vertex
// buffer D_800BE9C0 of +0x48 (a cross of two 4-unit offsets perpendicular to the segment to the next point; the
// last point uses an upward segment), loads texture +0x40 (func_150953F8) and draws each segment as 8 triangles
// from 8 vertices, setting the t coordinates of vertices 0 / 4 (0x100 + k * (height - 1), << 5 for texture 0x36
// else << 4); the first segment also closes the top end.
Gfx *func_151ADEDC(Gfx *gfx, u8 *e, s16 player) {
    struct_eu_80090F10 *tex;
    Vtx *v;
    f32 *p;
    f32 x, y, z, dx, dy, ndy, dz, len, inv, ox, oy, oz;
    s32 n, th, tw, shift, i, s, tTop, tBot;

    tex = &D_80090F10[*(u16 *) (e + 0x40)];
    n = e[0x42];
    th = tex->unk8 - 1;
    tw = tex->unk6;
    if (*(u16 *) (e + 0x40) == 0x36) {
        shift = 5;
    } else {
        shift = 4;
    }
    for (i = 0; i < n; i++) {
        p = *(f32 **) (e + 0x38) + i * 6;
        x = p[0];
        y = p[1];
        z = p[2];
        if (i + 1 == n) {
            dx = 0.0f;
            dy = 1.0f;
            dz = 0.0f;
        } else {
            dx = p[6] - x;
            dy = p[7] - y;
            dz = p[8] - z;
        }
        ndy = -dy;
        len = sqrtf(dz * dz + ndy * ndy);
        if (len == 0.0f) {
            ox = 100.0f;
            oy = 0.0f;
            oz = 0.0f;
        } else {
            inv = 1.0f / len;
            ox = 0.0f;
            oy = dz * inv;
            oz = ndy * inv;
        }
        ox *= 4.0f;
        oy *= 4.0f;
        oz *= 4.0f;
        v = *(Vtx **) (e + 0x48) + (D_800BE9C0 * n + i) * 4;
        v[0].v.ob[0] = (s32) (x + ox);
        v[0].v.ob[1] = (s32) (y + oy);
        v[0].v.ob[2] = (s32) (z + oz);
        v[2].v.ob[0] = (s32) (x - ox);
        v[2].v.ob[1] = (s32) (y - oy);
        v[2].v.ob[2] = (s32) (z - oz);
        len = sqrtf(ndy * ndy + dx * dx);
        if (len == 0.0f) {
            ox = 1.0f;
            oy = 0.0f;
            oz = 1.0f;
        } else {
            inv = 1.0f / len;
            ox = ndy * inv;
            oy = dx * inv;
            oz = 0.0f;
        }
        ox *= 4.0f;
        oy *= 4.0f;
        oz *= 4.0f;
        v[1].v.ob[0] = (s32) (x + ox);
        v[1].v.ob[1] = (s32) (y + oy);
        v[1].v.ob[2] = (s32) (z + oz);
        v[3].v.ob[0] = (s32) (x - ox);
        v[3].v.ob[1] = (s32) (y - oy);
        v[3].v.ob[2] = (s32) (z - oz);
    }
    gSPSetGeometryMode(gfx++, G_CULL_BACK);
    gSPClearGeometryMode(gfx++, G_CULL_FRONT);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(gfx++);
    gfx = (Gfx *) func_150953F8((s32) gfx, (s32) &D_80090F10[*(u16 *) (e + 0x40)], 0, 0, 0, 0, 0, 0, 0x100, 0x100,
                                0x3E);
    gfx->words.w0 = 0xFC121824; /* combine mode */
    gfx->words.w1 = 0xFF33FFFF;
    gfx++;
    gDPSetOtherMode(gfx++, D_800D30BC | 0x80000 | 0x2C0F, 0x552078);
    s = ((tw + 0x100) << 5) << 16;
    tTop = 0x100;
    tBot = th + 0x100;
    for (i = 1; i < n; i++) {
        gSPVertex(gfx++, *(Vtx **) (e + 0x48) + (D_800BE9C0 * n + (i - 1)) * 4, 8, 0);
        gSP1Triangle(gfx++, 0, 1, 4, 0);
        gSP1Triangle(gfx++, 1, 5, 4, 0);
        gSP1Triangle(gfx++, 1, 2, 5, 0);
        gSP1Triangle(gfx++, 2, 6, 5, 0);
        gSP1Triangle(gfx++, 2, 3, 7, 0);
        gSP1Triangle(gfx++, 2, 7, 6, 0);
        gSPModifyVertex(gfx++, 0, G_MWO_POINT_ST, s | (tTop << shift));
        gSPModifyVertex(gfx++, 4, G_MWO_POINT_ST, s | (tBot << shift));
        gSP1Triangle(gfx++, 3, 0, 7, 0);
        gSP1Triangle(gfx++, 0, 4, 7, 0);
        if (i == 1) {
            gSP1Triangle(gfx++, 2, 1, 0, 0);
            gSP1Triangle(gfx++, 3, 2, 0, 0);
        }
        tTop += th;
        tBot += th;
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151ADEDC.s")
#endif

void func_151AE814(u8 *);
void func_151AE694(u8 *, u8);
void func_151AE61C(u8 *arg0, u8 *arg1) {
    u8 sp1F;
    u8 a;
    u8 sp1E;
    if (func_151AD0E8(arg0, &sp1F) != 0) {
        a = arg1[0x1B];
        if ((*(u8 **)(arg0 + 0x31C))[0x98] == 0) {
            func_151AE694(arg0, a);
        } else if (a != (*(u8 **)(arg0 + 0x31C))[0x98]) {
            sp1E = a;
            func_151AE814(arg0);
            func_151AE694(arg0, sp1E);
        }
    }
}

#ifdef NON_MATCHING
/* P150 */
struct_eu_node *func_151AEB40(s32);
void func_151AE86C(f32 *, u8 *, s32, f32);
// path_try_attach: attaches obj to path node `id` (func_151AEB40; the original hangs when there is none, the port returns) unless the
// path is busy (+0x52), obj cannot ride (+0x1CA == 0) or is busy (+0x104). The rider record (+0x31C) gets its
// progress along the path at +0xA0 (func_151AE86C from obj's height); when the path point at that progress
// (points +0x38, 24 bytes each, count +0x42, spacing +0x3C, 140 units kept free at the end) is within 100 units
// of obj, the record takes the path (+0x98 id, +0x9C path), obj state +0x8A = 0x12 and the path's rider +0x44 = obj.
void func_151AE694(u8 *obj, u8 id) {
    u8 *path;
    u8 *rec;
    f32 *point;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 spare;
    s32 index;

    path = (u8 *)func_151AEB40(id);
    if (path == NULL) {
        // Deliberate port divergence (coordinator decision, P155): the N64 code spins here forever (the console
        // hangs) when no path object with this id is spawned. In the port that would freeze the browser tab, so
        // the attach is simply skipped. The NM build has no port log hook to report it; the normal path is
        // unchanged.
        return;
    }
    if (*(s16 *)(path + 0x52) != 0 || obj[0x1CA] == 0 || obj[0x104] != 0) {
        return;
    }
    func_151AE86C((f32 *)(*(u8 **)(obj + 0x31C) + 0xA0), path, *(s32 *)(obj + 0x14), *(f32 *)(obj + 0x18));
    spare = 140.0f / *(f32 *)(path + 0x3C);
    rec = *(u8 **)(obj + 0x31C);
    index = (f32)(path[0x42] - spare - 1) * *(f32 *)(rec + 0xA0);
    point = (f32 *)(*(u8 **)(path + 0x38) + index * 24);
    dx = point[0] - *(f32 *)(obj + 0x14);
    dy = point[1] - *(f32 *)(obj + 0x18);
    dz = point[2] - *(f32 *)(obj + 0x1C);
    if (dz * dz + (dx * dx + dy * dy) > 10000.0f) {
        return;
    }
    (*(u8 **)(obj + 0x31C))[0x98] = id;
    obj[0x8A] = 0x12;
    *(u8 **)(*(u8 **)(obj + 0x31C) + 0x9C) = path;
    *(u8 **)(path + 0x44) = obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE694.s")
#endif

void func_151AE814(u8 *arg0) {
    u8 *temp_v0;
    f32 f;

    temp_v0 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C));
    f = (*(f32 *)((u8 *)arg0 + 0x3C)) * 0.89f;
    (*(f32 *)((u8 *)temp_v0 + 0x4C)) = f;
    (*(u8 *)((u8 *)temp_v0 + 0x50)) = (*(u16 *)((u8 *)arg0 + 0x76)) >> 8;
    (*(u8 *)((u8 *)temp_v0 + 0x51)) = (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0xAE));
    (*(s16 *)((u8 *)temp_v0 + 0x52)) = 0x14;
    (*(s32 *)((u8 *)temp_v0 + 0x44)) = 0;
    (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x98)) = 0;
    (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x9C)) = NULL;
}

#ifdef NON_MATCHING
void func_151AE86C(f32 *arg0, u8 *arg1, s32 arg2, f32 arg3) {
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f0;
    s32 temp_a2;
    s32 var_v1;
    u8 temp_v0;
    u8 *temp_a0;
    u8 *var_a0;

    temp_v0 = (*(u8 *)((u8 *)arg1 + 0x42));
    var_v1 = 0;
    temp_a2 = temp_v0 - 1;
    if (temp_a2 > 0) {
        var_a0 = (*(u8 **)((u8 *)arg1 + 0x38));
loop_2:
        if (!(arg3 <= (*(f32 *)((u8 *)var_a0 + 4)))) {
            var_v1 += 1;
            var_a0 += 0x18;
            if (var_v1 != temp_a2) {
                goto loop_2;
            }
        }
    }
    if (var_v1 >= (temp_v0 - 2)) {
        *arg0 = 1.0f;
        return;
    }
    if (var_v1 == 0) {
        *arg0 = 0.0f;
        return;
    }
    temp_a0 = (*(u8 **)((u8 *)arg1 + 0x38)) + (var_v1 * 0x18);
    temp_f2 = (*(f32 *)((u8 *)temp_a0 + -0x14));
    temp_f0 = (*(f32 *)((u8 *)temp_a0 + 4)) - temp_f2;
    if (temp_f0 != 0.0f) {
        var_f0 = (arg3 - temp_f2) / temp_f0;
    } else {
        var_f0 = 0.0f;
    }
    *arg0 = ((f32) (var_v1 - 1) / (f32) (temp_v0 - 3)) + (var_f0 / (f32) temp_a2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE86C.s")
#endif
#ifdef NON_MATCHING
/* P153 */
s32 func_15143E08(struct127 *arg0);
f32 func_151423D8(u8);
// path_ride_place: P153: places the rider obj (arg0 + 0x1C) on its path (record +0x31C, path +0x9C): the rider's
// progress (+0xA0) picks a segment of the path points (+0x38, 24 bytes each, count +0x42, 140 units kept free at
// the end as in func_151AE694); the record's +0xAE gets the segment index, and obj's position becomes the point
// between that segment's two ends, moved sideways by arg0 +0x28 along obj's yaw (func_15143E08) - 0x80.
void func_151AE958(u8 *arg0) {
    u8 *obj;
    u8 *path;
    u8 *rec;
    f32 *p;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 side;
    f32 sinYaw;
    f32 cosYaw;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    s32 spare;
    s32 index;
    u8 yaw;

    obj = *(u8 **) (arg0 + 0x1C);
    path = *(u8 **) (*(u8 **) (obj + 0x31C) + 0x9C);
    yaw = func_15143E08((struct127 *) obj) - 0x80;
    sinYaw = func_151423D8((yaw - 0x40) & 0xFF);
    cosYaw = func_151423D8(yaw);
    rec = *(u8 **) (obj + 0x31C);
    oldY = *(f32 *) (obj + 0x18);
    oldX = *(f32 *) (obj + 0x14);
    side = *(f32 *) (arg0 + 0x28);
    oldZ = *(f32 *) (obj + 0x1C);
    spare = 140.0f / *(f32 *) (path + 0x3C);
    index = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0);
    rec[0xAE] = index;
    t = (f32) (path[0x42] - spare - 1) * *(f32 *) (rec + 0xA0) - (f32) index;
    p = (f32 *) (*(u8 **) (path + 0x38) + index * 24);
    x = (p[6] - p[0]) * t + p[0] + side * sinYaw;
    y = (p[7] - p[1]) * t + p[1];
    z = (p[8] - p[2]) * t + p[2] + side * cosYaw;
    *(f32 *) (obj + 0x14) = (x - oldX) + oldX;
    *(f32 *) (obj + 0x18) = (y - oldY) + oldY;
    *(f32 *) (obj + 0x1C) = (z - oldZ) + oldZ;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AE958.s")
#endif

#ifdef NON_MATCHING
extern s32 D_800A9650;

struct_eu_node *func_151AEB40(s32 arg0) {
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    s32 var_v1;
    struct_eu_node *temp_a2;
    struct_eu_node *var_a0;

    var_v0 = 0;
loop_1:
    var_v1 = 0;
loop_2:
    var_a0 = D_800DD280[var_v1][*(s32 *)((u8 *)&D_800A9650 + (var_v0 * 4))];
    temp_t4 = (var_v1 + 1) & 0xFF;
    if (var_a0 != NULL) {
loop_3:
        temp_a2 = var_a0->next;
        if ((arg0 & 0xFF) == (*(u8 *)((u8 *)var_a0 + 0x10))) {
            return var_a0;
        }
        var_a0 = temp_a2;
        if (temp_a2 == NULL) {
            goto block_6;
        }
        goto loop_3;
    }
block_6:
    var_v1 = temp_t4;
    if (temp_t4 >= 2) {
        temp_t5 = (var_v0 + 1) & 0xFF;
        var_v0 = temp_t5;
        if (temp_t5 >= 2) {
            return NULL;
        }
        goto loop_1;
    }
    goto loop_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D9C00/func_151AEB40.s")
#endif
void func_151AEBF0(u8 *arg0, s32 *arg1, u8 arg2)
{
  s32 a;
  if (arg2 == 0) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x44)) {
      s32 *p = (s32 *)(arg0 + 0x44); // a declaration in the arm = basic-block boundary (unfilled jr ra delay slot, s69)
      *p = 0;
    }
    return;
  }
  if (arg2 == 0x2D) {
    a = arg1[0];
    if (a == *(s32 *)(arg0 + 0x44)) { *(s32 *)(arg0 + 0x44) = arg1[1]; return; }
    if (arg1[1] == *(s32 *)(arg0 + 0x44)) { *(s32 *)(arg0 + 0x44) = a; }
  }
}
