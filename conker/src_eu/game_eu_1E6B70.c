#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P289: func_151B8DB0's records (the N64 layouts: the callees copy / read them by offset) */
typedef struct {            /* func_15132FBC's particle spec (0x76 bytes; same layout as game_eu_201240's ImpactParticle) */
    f32 scale[4];           /* 0x00 */
    f32 rot[3];             /* 0x10 */
    f32 one[3];             /* 0x1C */
    f32 pos[3];             /* 0x28 */
    f32 vel[3];             /* 0x34 */
    f32 spin[4];            /* 0x40 */
    s32 flags;              /* 0x50 */
    s16 life;               /* 0x54 */
    s16 kind;               /* 0x56 */
    u8 b58, pad59[3];       /* 0x58 */
    s32 w5C;                /* 0x5C */
    u8 b60, b61;            /* 0x60 */
    u8 b62[6];              /* 0x62 */
    u8 b68, pad69;          /* 0x68 */
    u8 b6A, pad6B;          /* 0x6A */
    s32 w6C;                /* 0x6C */
    u8 b70, pad71;          /* 0x70 */
    s16 h72, h74;           /* 0x72 */
} DripParticle;
typedef struct {            /* func_151407D0's spawn block (0x58 bytes, game_3E890's layout) */
    u8 b0;                  /* 0x00 */
    u8 kind;                /* 0x01 */
    u16 flags;              /* 0x02 */
    u16 life;               /* 0x04 */
    u8 pad6[2];
    s32 u8_;                /* 0x08 */
    s32 uC;                 /* 0x0C */
    u8 rgba[4];             /* 0x10 */
    f32 size[2];            /* 0x14 */
    f32 pos0[3];            /* 0x1C */
    f32 pos1[3];            /* 0x28 */
    f32 scale[3];           /* 0x34 */
    s32 u40;                /* 0x40 */
    u8 u44[4];              /* 0x44 */
    s32 u48;                /* 0x48 */
    u8 u4C;                 /* 0x4C */
    u8 pad4D[0xB];
} DripSpawn;
typedef struct {            /* func_151407D0's emitter block (0x60 bytes) */
    f32 range[4];           /* 0x00 */
    f32 u10;                /* 0x10 */
    f32 u14[4];             /* 0x14 */
    s32 u24[8];             /* 0x24 */
    s32 u44;                /* 0x44 */
    f32 u48;                /* 0x48 */
    s16 u4C[4];             /* 0x4C */
    u8 u54[6];              /* 0x54 */
    u8 pad5A[6];
} DripEmit;
typedef struct {            /* copied to the func_1516037C object's +0x18 (0xC bytes) */
    u8 *particle;
    s32 emitter;            /* the func_151407D0 result, stored afterwards */
    f32 invScale;
} DripLink;
u8 *func_15132FBC(DripParticle *spec, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
u8 *func_1516037C(Header *header, s32 arg1, s32 size, u8 arg3, s32 arg4);
s32 func_151407D0(DripEmit *emit, s32 emitSize, DripSpawn *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8,
                  s32 arg9);
void func_1510F800(s32);
void *memcpy(void *, const void *, s32);
static const f32 sDripPos[6][3] = { /* D_800AA8C0 */
    { 1993.0f, 367.0f, 7294.0f }, { 1993.0f, 367.0f, 6183.0f }, { 695.0f, 737.0f, -2.0f },
    { -453.0f, 737.0f, -2.0f },   { -1860.0f, 737.0f, 1650.0f }, { -1830.0f, 737.0f, 3017.0f },
};
static const f32 sDripScale[6] = { 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f }; /* D_800AA908 */

// level_drip_spawn: spawns drip `which` (0..5) of a level at its fixed place (D_800AA8C0, size D_800AA908): a
// swinging particle (func_15132FBC, kind 0x22, 9-float swing block at +0x170, flag 0x400 when func_1510FD20 finds
// the place in water), a link object (func_1516037C, type 7) holding the particle and 1 / size, and a falling
// emitter (func_151407D0) from the place to 500 below whose handle goes into the link.
void func_151B8DB0(s32 arg0, u8 which, u8 arg2, u8 arg3) {
    DripParticle part;
    DripSpawn spawn;
    DripEmit emit;
    DripLink link;
    Header header;
    f32 swing[9];
    const f32 *scale;
    u8 *p;
    u8 *obj;
    s32 water;
    f32 rnd;

    swing[0] = 0.0f;
    swing[1] = 17.316f;
    swing[4] = 17.316f;
    rnd = func_150ADA68();
    scale = &sDripScale[which];
    swing[2] = rnd * 6.2831855f;
    swing[3] = 0.088f;
    swing[5] = 0.088f;
    swing[6] = 0.0f;
    swing[7] = 0.0f;
    swing[8] = 0.0f;
    part.scale[0] = 1.0f;
    part.scale[1] = 1.0f;
    part.scale[2] = *scale;
    part.scale[3] = *scale;
    part.rot[0] = part.rot[1] = part.rot[2] = 0.0f;
    part.one[0] = part.one[1] = part.one[2] = 1.0f;
    part.pos[0] = sDripPos[which][0];
    part.pos[1] = sDripPos[which][1];
    part.pos[2] = sDripPos[which][2];
    part.life = 300;
    part.kind = 0x22;
    part.vel[0] = part.vel[1] = part.vel[2] = 0.0f;
    part.spin[0] = part.spin[1] = part.spin[2] = part.spin[3] = 0.0f;
    func_1510F800(0);
    water = func_1510FD20((s32)part.pos[0], (s32)part.pos[2]);
    part.w5C = water;
    part.flags = (water != 0 ? 0x400 : 0) | 0x900;
    part.b58 = 0;
    part.b60 = 0xFF;
    part.b61 = 9;
    part.b62[0] = part.b62[1] = part.b62[2] = part.b62[3] = part.b62[4] = part.b62[5] = 0;
    part.b68 = 4;
    part.b6A = 2;
    part.w6C = 0;
    part.b70 = 0;
    part.h72 = 1;
    part.h74 = 0xFF;
    p = func_15132FBC(&part, 3, 0xFF, 0x24, arg2, arg3);
    if (p == NULL) {
        return;
    }
    memcpy(p + 0x170, swing, sizeof(swing));
    link.particle = p;
    link.emitter = 0;
    link.invScale = 1.0f / *scale;
    header.unk0 = 0;
    header.unk1 = 7;
    header.unk2 = 300;
    header.unk4 = 0x12;
    obj = func_1516037C(&header, arg0, sizeof(link), arg2, arg3);
    if (obj == NULL) {
        return;
    }
    memcpy(obj + 0x18, &link, sizeof(link));
    emit.range[0] = *scale * 43.3f;
    emit.range[1] = *scale * 43.3f;
    emit.range[2] = *scale * 30.2f;
    emit.range[3] = *scale * 30.2f;
    emit.u10 = 0.2f;
    emit.u14[0] = 0.25f;
    emit.u14[1] = 0.8f;
    emit.u14[2] = 0.6f;
    emit.u14[3] = 1e-06f;
    emit.u24[0] = emit.u24[1] = emit.u24[2] = emit.u24[3] = -1;
    emit.u24[4] = emit.u24[5] = emit.u24[6] = emit.u24[7] = -1;
    emit.u44 = 0;
    emit.u48 = 1.0f;
    emit.u4C[0] = emit.u4C[1] = emit.u4C[2] = emit.u4C[3] = 0;
    emit.u54[0] = emit.u54[1] = emit.u54[2] = emit.u54[3] = emit.u54[4] = 0;
    emit.u54[5] = 0xFF;
    spawn.b0 = 0x69;
    spawn.kind = 3;
    spawn.flags = 0x3403;
    spawn.life = 300;
    spawn.u8_ = 0;
    spawn.uC = 0;
    spawn.rgba[0] = spawn.rgba[1] = spawn.rgba[2] = spawn.rgba[3] = 0xFF;
    spawn.size[0] = spawn.size[1] = 100.0f;
    spawn.pos0[0] = part.pos[0];
    spawn.pos0[1] = part.pos[1];
    spawn.pos0[2] = part.pos[2];
    spawn.pos1[0] = part.pos[0];
    spawn.pos1[1] = part.pos[1] - 500.0f;
    spawn.pos1[2] = part.pos[2];
    spawn.scale[0] = spawn.scale[1] = spawn.scale[2] = 1.0f;
    spawn.u40 = 0x1CD2006;
    spawn.u44[0] = 0xFF;
    spawn.u44[1] = 0xFF;
    spawn.u44[2] = 0;
    spawn.u44[3] = 6;
    spawn.u48 = water;
    spawn.u4C = 0xFF;
    ((DripLink *)(obj + 0x18))->emitter = func_151407D0(&emit, 0x60, &spawn, 0, 0, 0, 0, -1, arg2, arg3);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B8DB0.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800AA944;   /* ~0.0234f (rodata) */
s32 func_151B97C4(u8 *arg0) {
    u8 *temp_v0;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f0_2;
    f32 temp_f0;
    u8 *sp18;

    (*(f32 *)((u8 *)arg0 + 0x178)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x178)) + ((*(f32 *)((u8 *)arg0 + 0x17C)) * D_800BE9A4));
    temp_f0 = func_15144B68((*(f32 *)((u8 *)arg0 + 0x178)));
    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)temp_v0 + 8)) = temp_f0;
    sp18 = temp_v0;
    temp_f2 = (*(f32 *)((u8 *)sp18 + 4));
    temp_f12 = (*(f32 *)((u8 *)sp18 + 0x18));
    (*(f32 *)((u8 *)sp18 + 0)) = (f32) (sinf(temp_f0) * temp_f2);
    if (temp_f12 > 0.0f) {
        (*(f32 *)((u8 *)sp18 + 0x18)) = (f32) (temp_f12 - D_800BE9A4);
        (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) + ((*(f32 *)((u8 *)sp18 + 0x20)) * D_800BE9A4));
        (*(f32 *)((u8 *)sp18 + 4)) = (f32) (temp_f2 + ((*(f32 *)((u8 *)sp18 + 0x1C)) * D_800BE9A4));
    } else {
        temp_f0_2 = (*(f32 *)((u8 *)sp18 + 0xC));
        (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)sp18 + 0x14)) - temp_f0_2) * D_800AA944));
        (*(f32 *)((u8 *)sp18 + 4)) = (f32) (temp_f2 + (((*(f32 *)((u8 *)sp18 + 0x10)) - temp_f2) * D_800AA944));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B97C4.s")
#endif
s32 func_151B98C0(Mtx *arg0, u8 *arg1) {
    f32 mf[4][4];
    u8 *p;

    p = arg1;
    func_150A8050(mf, 0.0f, 0.0f, *(f32 *)(p + 0x170));
    mf[3][0] = *(f32 *)(p + 0x38);
    mf[3][1] = *(f32 *)(p + 0x3C);
    mf[3][2] = *(f32 *)(p + 0x40);
    mf[0][0] *= *(f32 *)(p + 0x18);
    mf[0][1] *= *(f32 *)(p + 0x18);
    mf[0][2] *= *(f32 *)(p + 0x18);
    mf[1][0] *= *(f32 *)(p + 0x1C);
    mf[1][1] *= *(f32 *)(p + 0x1C);
    mf[1][2] *= *(f32 *)(p + 0x1C);
    mf[2][0] *= *(f32 *)(p + 0x18);
    mf[2][1] *= *(f32 *)(p + 0x18);
    mf[2][2] *= *(f32 *)(p + 0x18);
    guMtxF2L(mf, arg0);
    return 1;
}

#ifdef NON_MATCHING
void func_150A7E40(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
/* searchlight_light_update: P237. D_8008B0F0 handler of the swinging searchlight (object at effect +0x18, which
 * func_151B97C4 swings: angle +0x170, position +0x38, scale +0x18 / +0x1C). The lamp point (0, -150, 0) of the
 * object's model matrix (func_151B98C0's matrix: rotation by +0x170, x / z scaled by +0x18, y by +0x1C, at +0x38)
 * becomes the light position (+0xE / +0x10 / +0x12 of effect +0x14). When the effect has a beam record (+0x1C), its
 * two points run from the object along the direction object -> lamp (scaled by effect +0x20 / 150): the first at
 * 65 * y scale from the object, the second 500 further. Returns 1. */
#define B9B8_BEAM (*(u8 **) ((u8 *) arg0 + 0x1C))
s32 func_151B99B8(struct225 *arg0) {
    u8 *obj = *(u8 **) ((u8 *) arg0 + 0x18);
    f32 mf[4][4];
    f32 x, y, z;
    f32 k, s, dx, dy, dz;

    func_150A8050(mf, 0.0f, 0.0f, *(f32 *) (obj + 0x170));
    mf[3][0] = *(f32 *) (obj + 0x38);
    mf[3][1] = *(f32 *) (obj + 0x3C);
    mf[3][2] = *(f32 *) (obj + 0x40);
    mf[0][0] *= *(f32 *) (obj + 0x18);
    mf[0][1] *= *(f32 *) (obj + 0x18);
    mf[0][2] *= *(f32 *) (obj + 0x18);
    mf[1][0] *= *(f32 *) (obj + 0x1C);
    mf[1][1] *= *(f32 *) (obj + 0x1C);
    mf[1][2] *= *(f32 *) (obj + 0x1C);
    mf[2][0] *= *(f32 *) (obj + 0x18);
    mf[2][1] *= *(f32 *) (obj + 0x18);
    mf[2][2] *= *(f32 *) (obj + 0x18);
    func_150A7E40(mf, 0.0f, -150.0f, 0.0f, &x, &y, &z);
    arg0->unk14->unkE = x;
    arg0->unk14->unk10 = y;
    arg0->unk14->unk12 = z;
    if (B9B8_BEAM == NULL) {
        return 1;
    }
    k = *(f32 *) (obj + 0x1C) * 65.0f;
    s = *(f32 *) ((u8 *) arg0 + 0x20) * -0.0066666668f; /* D_800AA948 */
    dx = -(x - *(f32 *) (obj + 0x38)) * s;
    dy = -(y - *(f32 *) (obj + 0x3C)) * s;
    dz = -(z - *(f32 *) (obj + 0x40)) * s;
    /* the beam pointer is re-read for every store, as in the asm */
    *(f32 *) (B9B8_BEAM + 0x34) = *(f32 *) (obj + 0x38) + dx * k;
    *(f32 *) (B9B8_BEAM + 0x38) = *(f32 *) (obj + 0x3C) + dy * k;
    *(f32 *) (B9B8_BEAM + 0x3C) = *(f32 *) (obj + 0x40) + dz * k;
    *(f32 *) (B9B8_BEAM + 0x40) = *(f32 *) (B9B8_BEAM + 0x34) + dx * 500.0f;
    *(f32 *) (B9B8_BEAM + 0x44) = *(f32 *) (B9B8_BEAM + 0x38) + dy * 500.0f;
    *(f32 *) (B9B8_BEAM + 0x48) = *(f32 *) (B9B8_BEAM + 0x3C) + dz * 500.0f;
    return 1;
}
#undef B9B8_BEAM
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1E6B70/func_151B99B8.s")
#endif

void func_151B9C10(f32 *arg0) {
    arg0[0x188 / 4] = 5.0f;
    arg0[0x18C / 4] = D_800AA94C;
    arg0[0x190 / 4] = D_800AA950;
}
