#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 memcpy(s32, u8 **, s32);
s32 func_1519E874(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
#endif


void func_1519D4E0(u8 arg0) {
    u8 sp1C[4];
    sp1C[0] = arg0;
    func_151482D4(sp1C, 6);
}

void func_1519D510(u8 *arg0)
{
  u8 *temp_v0;
  temp_v0 = *((u8 **) (arg0 + 0x98));
  arg0[0x30] = 0;
  *((u16 *) (arg0 + 0x1E)) = *((u16 *) (arg0 + 0x1E)) & 0xFFFD;
  temp_v0[6] |= 1;
  temp_v0[6] |= 4;
}

void func_1519D540(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E64(arg0);
}

void func_1519D570(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
extern s32 D_800A8F60;

s32 func_1519D5A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        s32 u4C;
        u8 u50;
        u8 u51;
        s8 u52;
        s8 u53;
        s32 u54;
        u8 pad58[0x8];
        s32 u60;
        u8 pad64[0x8];
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        u8 u8C;
        u8 pad8D[0x1];
        s16 u8E;
        s16 u90;
        s16 u92;
        s16 u94;
        s16 u96;
        s8 u98;
        u8 pad99[0x3];
        f32 u9C;
        f32 uA0;
        f32 uA4;
        u8 uA8;
        u8 uA9;
        u8 uAA;
        u8 uAB;
        f32 uAC;
        u8 padB0[0x8];
        s16 uB8;
        u16 uBA;
        s32 uBC;
        u8 padC0[0x1];
        s8 uC1;
    } sp;
    u8 *sp48;
    s32 var_v1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_v1;

    if (arg0 == 0) {
        return 0;
    }
    sp.u6C = 0.0f;
    var_v1_2 = 0;
    sp.u9C = (*(f32 *)((u8 *)arg0 + 0x14));
    temp_v0 = ((s32 *)((u8 *)&D_800A8F60 + (arg1 << 6)));
    sp.uA0 = (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u4C = arg0;
    sp.uA4 = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u52 = 2;
    sp.u53 = 0;
    sp.u98 = (s8) arg1;
    sp.uB8 = (s16) arg2;
    sp.u78 = 0.0f;
    sp.u50 = (*(u8 *)((u8 *)arg0 + 0x3B));
    if (arg3 & 0xFF) {
        var_v1_2 = 1;
    }
    sp.uBA = var_v1_2 | 2;
    sp.u70 = (*(f32 *)((u8 *)temp_v0 + 0));
    sp.u74 = (*(f32 *)((u8 *)temp_v0 + 4));
    sp.u8C = (*(u8 *)((u8 *)temp_v0 + 8));
    sp.uC1 = (s8) (*(s32 *)((u8 *)temp_v0 + 0xC));
    sp.u51 = (*(u8 *)((u8 *)temp_v0 + 0x10));
    (*(s32 *)((u8 *)(&sp.u54) + 0)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x14));
    (*(s32 *)((u8 *)(&sp.u54) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x18));
    (*(s32 *)((u8 *)(&sp.u54) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x1C));
    sp.u8E = (*(s16 *)((u8 *)temp_v0 + 0x20));
    sp.u90 = (*(s16 *)((u8 *)temp_v0 + 0x22));
    sp.u92 = (*(s16 *)((u8 *)temp_v0 + 0x24));
    sp.u84 = (*(f32 *)((u8 *)temp_v0 + 0x28));
    sp.u80 = (*(f32 *)((u8 *)temp_v0 + 0x2C));
    sp.u7C = (*(f32 *)((u8 *)temp_v0 + 0x30));
    sp.u88 = (*(f32 *)((u8 *)temp_v0 + 0x34));
    sp.u94 = (*(s16 *)((u8 *)temp_v0 + 0x38));
    sp.u96 = (*(s16 *)((u8 *)temp_v0 + 0x3A));
    sp.uA8 = (*(u8 *)((u8 *)temp_v0 + 0x3C));
    sp.uA9 = (*(u8 *)((u8 *)temp_v0 + 0x3D));
    sp.uAA = (*(u8 *)((u8 *)temp_v0 + 0x3E));
    sp.uAB = (*(u8 *)((u8 *)temp_v0 + 0x3F));
    if (func_1519E874((u8 *) &sp.u4C, &sp.uAC, 0.0f, 0.0f, 0.0f, 1.0f) != 0) {
        (*(f32 *)((u8 *)(&sp.u60) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uAC) + 0));
        (*(s32 *)((u8 *)(&sp.u60) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 4));
        (*(s32 *)((u8 *)(&sp.u60) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 8));
        sp.uBA |= 4;
    }
    sp.uBC = 4;
    temp_v0_2 = func_15147FF0(&sp.uAC, 0x60, 0x24, 3, 3, 3, 0, 0, 0, (u8) (s32) (u8) arg4, arg5);
    var_v1 = temp_v0_2;
    if (temp_v0_2 != NULL) {
        sp48 = temp_v0_2;
        memcpy((*(s32 *)((u8 *)temp_v0_2 + 0x98)), &sp.u4C, 0x60);
        var_v1 = sp48;
    }
    return (s32) var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D5A0.s")
#endif
typedef struct { f32 x, y, z; } V3;
typedef struct {
    V3 pos;
    V3 vel;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    u8 unk20;
    u8 pad21[3];
} Trail;
typedef struct {
    u8 pad0[6];
    u8 flags;
    u8 pad7[0x1D];
    f32 unk24;
    u8 pad28[8];
    f32 unk30;
    f32 unk34;
    u8 pad38[0xE];
    s16 unk46;
} TrailDef;
typedef struct {
    u8 pad0[0x25];
    u8 count;
    u8 pad26[6];
    s8 n;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    V3 pos;
    u8 pad60[0x34];
    Trail *trails;
    TrailDef *def;
} TrailObj;

s32 func_1519D7B0(TrailObj *arg0) {
    TrailDef *def = arg0->def;
    Trail *trails = arg0->trails;
    s32 i;
    Trail *t;
    s16 life;

    if (arg0->n < 2 && (def->flags & 1)) {
        return 0;
    }
    i = arg0->tail;
    while (i != arg0->head) {
        i--;
        if (i < 0) {
            i = arg0->count - 1;
        }
        t = &trails[i];
        t->unk20 = 0xFF;
        t->vel.x *= def->unk30;
        t->vel.y += def->unk24 * D_800BE9A4;
        t->vel.z *= def->unk30;
        t->pos.x += trails[i].vel.x * D_800BE9A4;
        t->pos.y += trails[i].vel.y * D_800BE9A4;
        life = t->unk1E;
        t->pos.z += trails[i].vel.z * D_800BE9A4;
        if (life > 0) {
            t->unk1E = life - D_800BE9E4;
        } else {
            t->unk1C -= D_800BE9E4 * def->unk46;
        }
        t->unk18 += D_800BE9A4 * def->unk34;
        if (t->unk1C < 0) {
            def->flags &= ~2;
            while (i != arg0->head) {
                arg0->head++;
                if (arg0->head == arg0->count) {
                    arg0->head = 0;
                }
                arg0->n--;
            }
            trails[arg0->head].unk1C = 0;
        }
    }
    if (arg0->n > 0) {
        arg0->pos = trails[arg0->head].pos;
    } else {
        arg0->pos.x = 0.0f; arg0->pos.y = 0.0f; arg0->pos.z = 0.0f;
    }
    return 1;
}

#ifdef NON_MATCHING
s32 func_1514F2AC(struct_eu_link *, u8 *, s32);
s32 func_1514F18C(void *arg0, struct127 *arg1, s16 arg2);
void func_1519D510(u8 *arg0);

/* +0x94 ring of trail points (0x24 bytes each) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 vel[3];
    /* 0x18 */ f32 height;
    /* 0x1C */ s16 u1C;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ u8 alpha;
    /* 0x21 */ u8 frame;
    /* 0x22 */ u8 pad22[2];
} PointD9C4;

/* 12-byte payload of the lost-track marker (func_151491F4) */
typedef struct {
    /* 0x00 */ s32 owner;
    /* 0x04 */ u8 id;
    /* 0x05 */ u8 pad05[3];
    /* 0x08 */ s32 u08;
} MarkD9C4;

// spray_trail_record: entry 3 of D_8008A5DC (`s32 (*)(u8 *)`, 0 = drop). State = +0x98 {target, byte 4 = the
// target's +0x3B, frame byte 7, last point +0x14, time +0x20, gravity +0x24, rate +0x28, pending +0x2C, rise +0x34 /
// base +0x38, +0x3C, s16 +0x42 / +0x44 / +0x48 / +0x4A, target position +0x50}. Returns 0 when the target has gone or
// changed. First call (flag 4 clear) waits for func_1519E874 to place the position (+0x10), then starts there. Later
// calls follow with func_1519E874 (none: func_1519D510 and a func_151491F4 type-8 marker {target, id, +0x4C} hooked
// to the target's link, return 1). Each frame adds rate * frame time to the pending count and emits one point per
// whole unit, interpolated from the last point to the position: position, velocity (move * D_800BEDC8, y 0),
// height base + rise * t, frame st[7] (advanced by +0x48 + random % (+0x4A + 1)), then moved by its velocity
// (+ gravity) * t, t stepping down; ring write index +0x2E / count +0x2C / read index +0x2D (size +0x25). Finally
// shifts all live points by the target's move since last frame (+0x50).
s32 func_1519D9C4(u8 *obj) {
    u8 *st = *(u8 **) (obj + 0x98);
    PointD9C4 *ring = *(PointD9C4 **) (obj + 0x94);
    u8 *tgt = *(u8 **) st;
    PointD9C4 *e;
    MarkD9C4 mark;
    struct260 *marker;
    s32 placed;
    f32 cur[3];
    f32 move[3];
    f32 vel[3];
    f32 step[3];
    f32 x, z;
    f32 inv, t, dt0, h, dh;
    f32 dx, dy, dz;
    s32 i;

    if (*(s32 *) tgt == 0) {
        return 0;
    }
    if (st[4] != tgt[0x3B]) {
        return 0;
    }
    placed = 0;
    if (!(*(u16 *) (obj + 0x1E) & 4)) {
        if (func_1519E874(st, (f32 *) (obj + 0x10), 0.0f, 0.0f, 0.0f, 1.0f) == 0) {
            return 1;
        }
        *(f32 *) (st + 0x14) = *(f32 *) (obj + 0x10);
        *(f32 *) (st + 0x18) = *(f32 *) (obj + 0x14);
        *(f32 *) (st + 0x1C) = *(f32 *) (obj + 0x18);
        *(u16 *) (obj + 0x1E) |= 4;
        placed = 1;
    }
    x = *(f32 *) (obj + 0x10);
    z = *(f32 *) (obj + 0x18);
    if (!placed && func_1519E874(st, (f32 *) (obj + 0x10), x, *(f32 *) (obj + 0x14), z, *(f32 *) (st + 0x3C)) == 0) {
        func_1519D510(obj);
        mark.owner = *(s32 *) st;
        mark.id = (*(u8 **) st)[0x3B];
        mark.u08 = st[0x4C];
        marker = func_151491F4(*(s16 *) (obj + 0x1C), -1, 8, (*(u16 *) (obj + 0x1E) & 1) ? 1 : 0, 2, 0xC, 0xFF, 0);
        if (marker != NULL) {
            memcpy((s32) ((u8 *) marker + 0x28), (u8 **) &mark, 0xC);
            if (func_1514F2AC(*(struct_eu_link **) (*(u8 **) st + 0x2F4), obj, 0) != 0) {
                func_1514F18C(marker, *(struct127 **) st, 0x11);
            }
        }
        return 1;
    }
    *(f32 *) (st + 0x2C) += *(f32 *) (st + 0x28) * D_800BE9A4;
    if (1.0f < *(f32 *) (st + 0x2C)) {
        inv = 1.0f / *(f32 *) (st + 0x2C);
        cur[0] = *(f32 *) (st + 0x14);
        cur[1] = *(f32 *) (st + 0x18);
        cur[2] = *(f32 *) (st + 0x1C);
        t = *(f32 *) (st + 0x20) + D_800BE9A4;
        move[0] = *(f32 *) (obj + 0x10) - *(f32 *) (st + 0x14);
        h = *(f32 *) (st + 0x38) + *(f32 *) (st + 0x34) * t;
        move[1] = *(f32 *) (obj + 0x14) - *(f32 *) (st + 0x18);
        move[2] = *(f32 *) (obj + 0x18) - *(f32 *) (st + 0x1C);
        dh = *(f32 *) (st + 0x38) - h;
        vel[1] = 0.0f;
        vel[0] = (*(f32 *) (obj + 0x10) - x) * D_800BEDC8;
        vel[2] = (*(f32 *) (obj + 0x18) - z) * D_800BEDC8;
        dt0 = t * inv;
        step[0] = move[0] * inv;
        step[1] = move[1] * inv;
        step[2] = move[2] * inv;
        dh *= inv;
        do {
            e = &ring[(s8) obj[0x2E]];
            e->pos[0] = cur[0];
            e->pos[1] = cur[1];
            e->pos[2] = cur[2];
            e->vel[0] = vel[0];
            e->vel[1] = vel[1];
            e->vel[2] = vel[2];
            e->height = h;
            e->frame = st[7];
            e->u1C = *(s16 *) (st + 0x42);
            e->u1E = *(s16 *) (st + 0x44);
            st[7] += *(s16 *) (st + 0x48) + (u32) func_150ADA20() % (*(s16 *) (st + 0x4A) + 1);
            e->alpha = 0xFF;
            e->vel[1] += *(f32 *) (st + 0x24) * t;
            e->pos[0] += e->vel[0] * t;
            e->pos[1] += e->vel[1] * t;
            e->pos[2] += e->vel[2] * t;
            t -= dt0;
            obj[0x2E]++;
            if (obj[0x25] == (s8) obj[0x2E]) {
                obj[0x2E] = 0;
            }
            obj[0x2C]++;
            if ((s8) obj[0x2D] == (s8) obj[0x2E]) {
                obj[0x2D]++;
                if (obj[0x25] == (s8) obj[0x2D]) {
                    obj[0x2D] = 0;
                }
                obj[0x2C]--;
            }
            cur[0] += step[0];
            cur[1] += step[1];
            cur[2] += step[2];
            h += dh;
            *(f32 *) (st + 0x2C) -= 1.0f;
        } while (1.0f < *(f32 *) (st + 0x2C));
        *(f32 *) (st + 0x14) = cur[0];
        *(f32 *) (st + 0x18) = cur[1];
        *(f32 *) (st + 0x1C) = cur[2];
        *(f32 *) (st + 0x20) = t;
    }
    tgt = *(u8 **) st;
    dx = *(f32 *) (tgt + 0x14) - *(f32 *) (st + 0x50);
    dy = *(f32 *) (tgt + 0x18) - *(f32 *) (st + 0x54);
    dz = *(f32 *) (tgt + 0x1C) - *(f32 *) (st + 0x58);
    i = (s8) obj[0x2E];
    if (i != (s8) obj[0x2D]) {
        do {
            i--;
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            ring[i].pos[0] += dx;
            ring[i].pos[1] += dy;
            ring[i].pos[2] += dz;
        } while (i != (s8) obj[0x2D]);
        tgt = *(u8 **) st;
    }
    *(f32 *) (st + 0x50) = *(f32 *) (tgt + 0x14);
    *(f32 *) (st + 0x54) = *(f32 *) (tgt + 0x18);
    *(f32 *) (st + 0x58) = *(f32 *) (tgt + 0x1C);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D9C4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519DF64.s")

void func_1519E764(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 temp_a0;
  s32 temp_t6;
  s32 temp_v1;
  u8 *temp_v0;
  temp_t6 = arg2;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x98));
  if (temp_t6 == 0)
  {
    if (((*((s32 *) (((u8 *) temp_v0) + 0))) == (*((s32 *) (((u8 *) arg1) + 0)))) || ((*((u8 *) (((u8 *) temp_v0) + 4))) == (*((u8 *) (((u8 *) arg1) + 4)))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 6)
  {
    if ((*arg1) == (*((u8 *) (((u8 *) temp_v0) + 0x4C))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 7)
  {
    if (((*((s32 *) (((u8 *) temp_v0) + 0))) == (*((s32 *) (((u8 *) arg1) + 0)))) || ((*((u8 *) (((u8 *) temp_v0) + 4))) == (*((u8 *) (((u8 *) arg1) + 4)))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 0x2D)
  {
    ;
    temp_a0 = *((s32 *) (((u8 *) arg1) + 0));
    if (temp_a0 == (*((s32 *) (((u8 *) temp_v0) + 0))))
    {
      *((s32 *) (((u8 *) temp_v0) + 0)) = *((s32 *) (((u8 *) arg1) + 4));
      *((u8 *) (((u8 *) temp_v0) + 4)) = (u8) (*((u8 *) (((u8 *) arg1) + 9)));
      return;
    }
    if ((*((s32 *) (((u8 *) arg1) + 4))) == (*((s32 *) (((u8 *) temp_v0) + 0))))
    {
      *((s32 *) (((u8 *) temp_v0) + 0)) = temp_a0;
      *((u8 *) (((u8 *) temp_v0) + 4)) = (u8) (*((u8 *) (((u8 *) arg1) + 8)));
    }
  }
}

s32 func_1519E874(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p = arg0;
    f32 sp1C[2];
    if (*(s32 *)(*(u8 **)p + 0x1D4) == 0) {
        return 0;
    }
    func_15143134(p + 8, sp1C, (p[5] << 6) + *(s32 *)(*(u8 **)p + 0x1D4));
    arg1[0] = ((sp1C[0] - arg2) * arg5) + arg2;
    arg1[1] = ((sp1C[1] - arg3) * arg5) + arg3;
    arg1[2] = ((sp1C[2] - arg4) * arg5) + arg4;
    return 1;
}

void func_1519E688(void);
s32 func_1519D5A0(s32, s32, s32, s32, s32, s32);
// fakematch: volatile arg2 reloads the byte after each call like the original
void func_1519E92C(s32 arg0, s16 arg1, volatile u8 arg2, s32 arg3) {
    func_1519E688();
    func_1519D5A0(arg0, 3, 0x12C, 0, arg2, arg3);
    func_1519D5A0(arg0, 4, 0x12C, 0, arg2, arg3);
    func_151491F4(arg1, 6, -1, 1, 3, 0, arg2, arg3);
}

#ifdef NON_MATCHING
s32 func_1514F2AC(struct_eu_link *, u8 *, s32);

void func_1519E9D4(u8 *arg0) {
    u8 sp33;
    s32 sp2C;
    u8 *sp28;
    s32 temp_v0;
    s32 var_t0;
    struct127 *temp_a0;
    u8 *temp_v1;

    var_t0 = 0;
    temp_v1 = arg0 + 0x28;
    if (*(*(s32 **)((u8 *)arg0 + 0x28)) == 0) {
        var_t0 = 1;
    }
    temp_a0 = (*(struct127 **)((u8 *)temp_v1 + 0));
    if ((*(u8 *)((u8 *)temp_v1 + 4)) != temp_a0->unique_id) {
        var_t0 = 1;
    }
    if ((var_t0 == 0) && (temp_a0->unk1D4 != NULL)) {
        sp33 = 1;
        sp28 = temp_v1;
        temp_v0 = func_1519D5A0((s32) temp_a0, (*(s32 *)((u8 *)temp_v1 + 8)), (s32) (*(s16 *)((u8 *)arg0 + 0xE)), (*(u8 *)((u8 *)arg0 + 0xD)) & 1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        var_t0 = 1;
        if (temp_v0 != 0) {
            sp33 = 1;
            sp2C = temp_v0;
            sp28 = temp_v1;
            var_t0 = 1;
            if (func_1514F2AC((*(struct127 **)((u8 *)temp_v1 + 0))->unk2F4, arg0, 0) != 0) {
                sp33 = 1;
                func_1514F18C((u8 *) sp2C, (*(struct127 **)((u8 *)temp_v1 + 0)), 0x10);
                var_t0 = 1;
            }
        }
    }
    if (var_t0 != 0) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E9D4.s")
#endif
void func_1519EAE0(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

void func_1519EB8C(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 9)) {
        func_1516972C(arg0);
    }
}

void func_1519EBCC(s32 arg0) {
    func_1519D4E0(3);
    func_1519D4E0(4);
}

void func_1519E688(void) {
    func_1519D4E0(3);
    func_1519D4E0(4);
    func_151482D4(0, 9);
}

#ifdef NON_MATCHING
s32 memcpy(s32, u8 **, s32);

// buddy_marker_create: clears the old markers (func_1519E688) and, if none is active (D_800E0D50), creates a
// marker effect (func_151491F4, type 9) whose 12-byte payload at +0x28 is {owner arg0, owner id arg0[0x3B], 0}.
// P124: the payload is one struct (m2c had 3 locals and memcpy'd 12 bytes from the first).
void func_1519E6BC(u8 *arg0) {
    struct {
        u8 *u0;
        u8 u4;
        s32 u8;
    } t;
    s32 fx;

    func_1519E688();
    if (D_800E0D50 == 0) {
        t.u8 = 0;
        t.u0 = arg0;
        t.u4 = arg0[0x3B];
        fx = func_151491F4(0x12C, -1, 9, 0U, 4U, 0xC, 0xFFU, 0);
        D_800E0D50 = fx;
        if (fx != 0) {
            memcpy(fx + 0x28, (u8 **) &t, 0xC);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E6BC.s")
#endif
#ifdef NON_MATCHING
void func_1519ECC4(u8 *arg0) {
    u8 sp23;
    s32 temp_t2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_v0;

    var_v1 = 0;
    temp_v0 = arg0 + 0x28;
    if (*(*(s32 **)((u8 *)arg0 + 0x28)) == 0) {
        var_v1 = 1;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_v0 + 0));
    if ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_a0 + 0x3B))) {
        var_v1 = 1;
    }
    if (var_v1 == 0) {
        temp_t2 = (*(s32 *)((u8 *)temp_v0 + 8)) + D_800BE9E4;
        (*(s32 *)((u8 *)temp_v0 + 8)) = temp_t2;
        if ((*(u16 *)((u8 *)temp_a0 + 0x84)) != 0x7C) {
            var_v1 = 1;
            if (temp_t2 >= 0xC9) {
                sp23 = 1;
                func_1519E92C((s32) temp_a0, 0x12C, (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                var_v1 = 1;
            }
        }
    }
    if (var_v1 != 0) {
        D_800E0D50 = 0;
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519ECC4.s")
#endif
void func_1519ED88(u8 *arg0, s32 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  if (arg2 == 0) {
    if (*(s32 *)v == arg1[0] || v[4] == ((u8 *)arg1)[4]) {
      func_1516972C((struct102 *)arg0);
      {
        s32 t; // fakematch: block-local declaration = basic-block boundary (unfilled b delay slot, s69)
        D_800E0D50 = 0;
      }
    }
  } else if (arg2 == 0x2D) {
    
    if (arg1[0] == *(s32 *)v) {
      *(s32 *)v = arg1[1];
      v[4] = ((u8 *)arg1)[9];
    } else if (arg1[1] == *(s32 *)v) {
      *(s32 *)v = arg1[0];
      v[4] = ((u8 *)arg1)[8];
    }
  }
}

void func_1519EE3C(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_1514933C(arg0);
}

void func_1519EE68(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_15149368(arg0);
}

void func_1519EE94(struct260 *arg0) {
    D_800E0D50 = 0;
    func_1514933C(arg0);
}

void func_1519EEB8(struct260 *arg0) {
    D_800E0D50 = 0;
    func_15149368(arg0);
}
