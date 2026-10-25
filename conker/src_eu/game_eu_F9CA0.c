#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
#include "libc/string.h"
void func_1504715C(void *, u8 *);
s32 func_15046F70(u8 *, u16, f32, u8 *);
void func_150CD2A0(f32, f32 *, f32 *, f32 *);
u8 *func_150C8DD0(u8 *spec, s32 extra, s32 view, s32 arg3);
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);

typedef struct {
    u8 kind;            /* +0x00 the puff's kind (blk +0x00) */
    u8 bone;            /* +0x01 matrix index in obj +0x1D4 (64 bytes each) */
    u8 pad02[2];
    f32 point[3];       /* +0x04 local offset in that bone's space */
    u8 shadeBase;       /* +0x10 blk +0x44 = shadeBase + rand % (shadeRange + 1) */
    u8 shadeRange;      /* +0x11 */
    s16 lifeCut;        /* +0x12 rec.life = life - rand % (lifeCutRange + 1) - lifeCut */
    s16 lifeCutRange;   /* +0x14 */
    u8 pad16[2];
    f32 sizeBase;       /* +0x18 size = rand * sizeRange + sizeBase */
    f32 sizeRange;      /* +0x1C */
    f32 growBase;       /* +0x20 rec.grow = (rand * growRange + growBase) * size */
    f32 growRange;      /* +0x24 */
    s16 yaw;            /* +0x28 added to the object's facing (obj +0x7A >> 8) */
    u8 pad2A[2];
} GroundPuffSrc;        /* 0x2C bytes, D_800A0A10[3] */

/* copy of D_800A0A10 (the asm's injected .rodata; the NM link has no such symbol) */
static const GroundPuffSrc sGroundPuffSrc[3] = {
    { 0x4E, 0x1B, { 0, 0 }, { -68.0f, 0.0f, -3.0f }, 0xBE, 0x41, 0xC, 6, { 0, 0 }, 0.18f, 0.040000003f, 0.1f,
      0.060000002f, -0x72, { 0, 0 } },
    { 0x4E, 0x1B, { 0, 0 }, { -68.0f, 0.0f, -3.0f }, 0xBE, 0x41, 0x11, 6, { 0, 0 }, 0.18f, 0.040000003f, 0.09f,
      0.05f, -0x72, { 0, 0 } },
    { 0x4D, 0x1B, { 0, 0 }, { 0.0f, 0.0f, 40.0f }, 0x96, 0x32, 0xF, 8, { 0, 0 }, 0.2f, 0.1f, 0.080000006f, 0.040000003f,
      0, { 0, 0 } },
};
/* D_800A0A94: the ring's span (divided by its point / step counts at run time, as the asm) */
static const f32 sGroundRingSpan[1] = { 13.900001f };

typedef struct {
    s16 rgb[3];
    s16 a;
    s16 z;
} GroundPuffColour;     /* 10 bytes, one per corner */

typedef struct {
    u8 kind;            /* +0x00 */
    u8 u01;
    s16 u02;            /* +0x02 0x2601 */
    s16 life;           /* +0x04 rand % 51 + 0x84 */
    s32 u08;            /* +0x08 0 */
    s32 u0C;            /* +0x0C 0 */
    u8 u10[4];          /* +0x10 0xFF */
    f32 size[2];        /* +0x14 */
    f32 pos[3];         /* +0x1C */
    f32 u28[3];         /* +0x28 0 */
    f32 u34[3];         /* +0x34 1.0f */
    s32 u40;            /* +0x40 0x1C0001 */
    u8 shade;           /* +0x44 */
    u8 u45;             /* +0x45 0xFF */
    u8 u46;             /* +0x46 0 */
    u8 u47;             /* +0x47 6 */
    u8 pad48[0x10];     /* +0x48 not set */
} GroundPuffBlk;        /* 0x58 bytes, func_1513D668's spec */

typedef struct {
    s16 life;           /* +0x00 */
    u8 pad02[2];
    f32 grow;           /* +0x04 */
} GroundPuffRec;        /* copied to the record's +0x128 */

typedef struct {
    f32 pos[3];         /* +0x00 */
    u8 b0C;             /* +0x0C 1 */
    s8 b0D;             /* +0x0D -1 */
    u8 pad0E[2];
    f32 f10;            /* +0x10 70.6 */
    s32 n;              /* +0x14 12 points */
    s16 s18, s1A;       /* +0x18 40, 30 */
    f32 f1C;            /* +0x1C span / 10 */
    s16 s20;            /* +0x20 25 */
    u8 pad22[2];
    f32 f24, f28;       /* +0x24 span / 25, 0 */
    s8 b2C, b2D;        /* +0x2C -1, -1 */
    u8 pad2E[2];
} GroundPuffRing;       /* func_150C8DD0's spec */

// ground_puff_spawn: a dust puff where the character's bone point `which` (0..2 of D_800A0A10: bone 0x1B, offset
// / kind / size ranges per entry) meets the floor. Nothing without the object or its matrices (+0x1D4), or when no
// floor lies within 200 above / 2000 below the point (func_15046F70). The floor colour (func_150CD2A0 at z) tints a
// func_1513D668 puff (class 0x18, facing obj +0x7A >> 8 plus the entry's yaw, arg2 / arg3 passed on) whose record
// gets a life / growth tail at +0x128, then two debris sprays (func_1514CBE8 kinds 0x11 and 0x12, the second in the
// floor colour), a 12-point ring (func_150C8DD0) and func_151D5404 at the point. arg3 = alpha for the sprays.
void func_150CBF80(struct127 *obj, u8 which, s32 arg2, u8 arg3) {
    const GroundPuffSrc *src;
    f32 pos[3];
    f32 probe[3];
    f32 hit[9];
    f32 r, g, b;
    u8 cr, cg, cb;
    GroundPuffColour col[4];
    GroundPuffBlk blk;
    GroundPuffRec rec;
    GroundPuffRing ring;
    u8 rgb[4];
    u8 *p;
    s16 n;
    s32 i;

    if (obj == NULL || obj->unk1D4 == NULL) {
        return;
    }
    func_1504715C(hit, (u8 *) obj);
    src = &sGroundPuffSrc[which];
    func_15143134((void *) src->point, pos, (u8 *) obj->unk1D4 + src->bone * 64);
    probe[0] = pos[0];
    probe[1] = pos[1] + 200.0f;
    probe[2] = pos[2];
    if (func_15046F70((u8 *) probe, 0, pos[1] - 2000.0f, (u8 *) hit) == 0) {
        return;
    }
    pos[1] = hit[0];
    func_150CD2A0(pos[2], &r, &g, &b);
    cr = (u32) r;
    cg = (u32) g;
    cb = (u32) b;
    for (i = 0; i < 4; i++) {
        col[i].rgb[0] = cr;
        col[i].rgb[1] = cg;
        col[i].rgb[2] = cb;
        col[i].a = 0xFF;
        col[i].z = 0;
    }

    blk.kind = src->kind;
    blk.u02 = 0x2601;
    blk.life = (u32) func_150ADA20() % 51 + 0x84;
    blk.u08 = 0;
    blk.u0C = 0;
    blk.u10[0] = 0xFF;
    blk.u10[1] = 0xFF;
    blk.u10[2] = 0xFF;
    blk.u10[3] = 0xFF;
    blk.size[0] = blk.size[1] = func_150ADA68() * src->sizeRange + src->sizeBase;
    blk.pos[0] = pos[0];
    blk.pos[1] = pos[1] + 10.0f;
    blk.pos[2] = pos[2];
    blk.u28[0] = blk.u28[1] = blk.u28[2] = 0.0f;
    blk.u34[0] = blk.u34[1] = blk.u34[2] = 1.0f;
    blk.u40 = 0x1C0001;
    blk.shade = (u32) func_150ADA20() % (src->shadeRange + 1) + src->shadeBase;
    blk.u45 = 0xFF;
    blk.u46 = 0;
    blk.u47 = 6;
    rec.life = blk.life - (u32) func_150ADA20() % (src->lifeCutRange + 1) - src->lifeCut;
    rec.grow = (func_150ADA68() * src->growRange + src->growBase) * blk.size[0];
    p = (u8 *) func_1513D668((s32) &blk, (s32) col, 0, 0x18, 0, 0, (obj->unk7A >> 8) + src->yaw, 500.0f, 500.0f, 0,
                             (s32) &hit[1], 1, 8, arg3, arg2);
    if (p != NULL) {
        memcpy(p + 0x128, &rec, 8);
    }

    func_150ADA20(); /* drawn and dropped */
    func_1514CBE8(pos[0], pos[1], pos[2], func_150ADA68() * 50.0f + 80.0f, 0, 0xFF, 0x29, 0x11, 0, 0.0f, 0, arg3);

    ring.pos[0] = pos[0];
    ring.pos[1] = pos[1];
    ring.pos[2] = pos[2];
    ring.f10 = 70.6f;
    ring.b0C = 1;
    ring.b0D = -1;
    ring.n = 12;
    ring.s18 = 40;
    ring.s1A = 30;
    ring.s20 = 25;
    ring.b2C = -1;
    ring.b2D = -1;
    ring.f28 = 0.0f;
    ring.f1C = sGroundRingSpan[0] / 10.0f;
    ring.f24 = sGroundRingSpan[0] / 25.0f;
    func_150C8DD0((u8 *) &ring, 0, 0xFF, 1);

    n = (u32) func_150ADA20() % 14 + 15;
    rgb[0] = cr;
    rgb[1] = cg;
    rgb[2] = cb;
    func_1514CBE8(pos[0], pos[1], pos[2], func_150ADA68() * 70.0f + 70.0f, 0, 0xFF, n, 0x12, 0, 0.0f, (s32) rgb, arg3);
    func_151D5404((struct17 *) pos, 500.0f, 5000.0f, 0.0002f, 0xC, 0xF, 0xFF, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F9CA0/func_150CBF80.s")
#endif

s32 func_150CCB48(u8 *arg0)
{
  f32 temp_f0;
  s32 temp_v1;
  u8 *p;
  p = arg0 + 0x128;
  if ((*((s32 *) (((u8 *) arg0) + 0x58))) & 1)
  {
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    if (temp_v1 < 0x20)
    {
      if ((temp_v1 * 8) < ((s32) (*((u8 *) (((u8 *) arg0) + 0x5C)))))
      {
        *((u8 *) (((u8 *) arg0) + 0x5C)) = (u8) (temp_v1 * 8);
      }
    }
    temp_v1 = *((s16 *) (((u8 *) arg0) + 0x1C));
    temp_f0 = temp_f0;
    if ((*((s16 *) p)) < temp_v1)
    {
      temp_f0 = (*((f32 *) (p + 4))) * D_800BE9A4;
      *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x2C))) + temp_f0);
      *((f32 *) (((u8 *) arg0) + 0x30)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x30))) + temp_f0);
    }
  }
  return 1;
}

void func_15143794(s16, s16, f32, void *);
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150CCBC8(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        s8 u48;
        s8 u49;
        s8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        s8 u4E;
        s8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0xC];
        s32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x10];
    } sp;
    s32 obj;
    f32 scale;

    sp.u51 = 0x29;
    sp.u3C = 0xE03;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u3E = (func_150ADA20() & 0xF) + 0x14;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4C = 0xB0;
    sp.u4D = 0xA0;
    sp.u4E = 0x2A;
    sp.u48 = 0x40;
    sp.u49 = 0xB;
    sp.u4A = 0x6A;
    sp.u4B = 0xFF;
    sp.u4F = (func_150ADA20() % 156U) + 0x64;
    sp.u50 = 0xFF;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u5C = sp.u60 = (func_150ADA68() * 401.0f) + 300.0f;
    sp.u64 = arg2;
    sp.u68 = arg3;
    sp.u6C = arg4;
    func_15143794(arg8, (s16) ((func_150ADA20() % 21U) - 0x19), ((func_150ADA68() * 200.0f) + 350.0f) * 0.1f, sp.u7C);
    sp.u8C = 0xE05;
    sp.u88 = 0.0f;
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x40;
    }
    if (func_150ADA20() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u96 = 8;
    sp.u97 = -1;
    sp.u52 = 0xA;
    sp.u54 = 0x19;
    sp.u56 = 0x1B;
    sp.u58 = 1.04f;
    scale = 0.901f;
    obj = func_151308E4(&sp, 1, 4, argE, 1);
    if (obj != 0) {
        memcpy(obj + 0xA8, &scale, 4);
    }
    return 1;
}

s32 func_150CCDE4(u8 *arg0, s32 arg1) {
    s32 i;
    f32 *p = (f32 *)(arg0 + 0xA8);
    for (i = D_800BE9E4; i != 0; i--) {
        *(f32 *)(arg0 + 0x58) *= *p;
        *(f32 *)(arg0 + 0x60) *= *p;
    }
    return 1;
}

void func_15143794(s16, s16, f32, void *);

s32 func_150CCF8C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct {
        f32 u28[13];
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp;

    sp.u28[10] = arg2;
    sp.u28[11] = arg3;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u78 = 0x29E8;
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u6C = 0.0f;
    sp.u28[0] = 1.0f;
    sp.u7E = 0x20;
    sp.u28[12] = arg4;
    sp.u28[1] = 0.2f;
    func_15143794(arg8, (s16) (((u32) func_150ADA20() % 44U) - 0x3F), ((func_150ADA68() * 200.0f) + 300.0f) * 0.1f, &sp.u5C);
    sp.u68 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u70 = ((func_150ADA68() * 260.0f) + -130.0f) * 0.1f;
    sp.u7C = (func_150ADA20() % 51U) + 0x32;
    sp.u74 = ((func_150ADA68() * 1500.0f) + -3500.0f) * 0.001f;
    sp.u28[3] = ((func_150ADA68() * 500.0f) + 100.0f) * 0.001f;
    sp.u28[2] = sp.u28[3];
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = (func_150ADA20() % 101U) + 0x9B;
    sp.u89 = 3;
    sp.u8A = 0;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 0;
    sp.u92 = 2;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 0x20;
    sp.u9C = 7;
    func_15132FBC(&sp, 3, 0xFF, 0, (s32) argE, 0);
    return 1;
}

s32 func_150CD1C4(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}
