#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_800A8E7C;

void func_1519C7C8(u8 *arg0);
extern s32 D_800B1268[]; /* texture cache: expanded data per texture id */
s32 func_15195DD8(Gfx *dl, s32 texId, s32 skip, s32 *tileCount);
s32 func_15196270(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);


typedef struct DNode { struct DNode *next; struct DNode *prev; } DNode;
DNode *func_15195D20(s32 arg0, DNode **arg1, DNode **arg2) {
    DNode *node = allocate_memory(arg0, 1, 0, 0);
    if (node != NULL) {
        node->prev = NULL;
        if (*arg2 != NULL) {
            node->next = *arg2;
            (*arg2)->prev = node;
            *arg2 = node;
        } else {
            node->next = NULL;
            *arg2 = node;
            *arg1 = node;
        }
    }
    return node;
}

void func_eu_15195D94(void) {}

extern s32 D_800E0D10, D_800E0D14, D_800E0D18, D_800E0D1C, D_800E0D20;
void func_15195D9C(void) {
    D_800E0D10 = D_800E0D14 = 0;
    D_800E0D18 = D_800E0D1C = 0;
    D_800E0D20 = -2;
}

#ifdef NON_MATCHING
// dl_find_scroll_texture: finds, in display list `dl`, the (skip+1)-th G_SETTIMG (0xFD) that loads texture `texId`
// (w1 == D_800B1268[texId]; texId 0 = any texture). Returns the index of the first G_SETTILESIZE (0xF2) after it and
// stores in *tileCount the number of G_SETTILESIZE commands of the run there (1, plus one per following
// G_SETTILE / G_SETTILESIZE pair); returns -1 at G_ENDDL (0xDF) when there is no such texture.
s32 func_15195DD8(Gfx *dl, s32 texId, s32 skip, s32 *tileCount) {
    s32 i = -1;
    s32 j;
    u8 op;
    u8 next;
    u8 next2;

    *tileCount = 0;
    for (;;) {
        do {
            i++;
            op = dl[i].words.w0 >> 24;
        } while (op != 0xFD && op != 0xDF);
        if (op == 0xDF) {
            return -1;
        }
        if (texId == 0 || dl[i].words.w1 == D_800B1268[texId]) {
            if (skip <= 0) {
                break;
            }
            skip--;
        }
    }
    do {
        i++;
    } while ((u8)(dl[i].words.w0 >> 24) != 0xF2);
    j = i;
    do {
        (*tileCount)++;
        next = dl[j + 1].words.w0 >> 24;
        next2 = dl[j + 2].words.w0 >> 24;
        j += 2;
    } while (next == 0xF5 && next2 == 0xF2);
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195DD8.s")
#endif

typedef struct {
    DNode node;
    s16 x8;
    s16 w;
    s16 h;
    u16 xE;
    u16 x10;
    u8 x12;
    u8 x13;
    u8 x14;
    s32 x18;
    s16 a[5];
    s16 b[5];
    s16 x30[6];
} Ent3C;

Ent3C *func_15195EF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ent3C *p;
    s32 i;
    s32 w;
    s32 h;
    s32 x;
    s32 y;

    p = (Ent3C *)func_15195D20(0x3C, (DNode **)&D_800E0D18, (DNode **)&D_800E0D1C);
    if (p != NULL) {
        p->x18 = 0;
        for (i = 0; i < 5; i++) {
            p->a[i] = -1;
        }
        for (i = 0; i < 5; i++) {
            p->b[i] = -1;
        }
        p->x8 = arg0;
        w = ((arg1 >> 12) & 0xFFF) + 2;
        h = (arg1 & 0xFFF) + 2;
        if (arg3 != 0) {
            w *= 2;
            h *= 2;
        }
        p->w = w;
        p->h = h;
        p->xE = (arg2 >> 12) & 0xFFF;
        p->x10 = arg2 & 0xFFF;
        p->xE <<= 3;
        p->x10 <<= 3;
        p->x14 = 1;
    }
    return p;
}

s32 func_15195FF4(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}

#ifdef NON_MATCHING
// level_dl_add_texture_scroll: registers texture scrolling for texture `texId` (0: any texture, with a new id
// from D_800E0D20) in level display list `dl` (s32 address): for the `which`-th matching G_SETTIMG (-1: every one),
// the G_SETTILESIZE index and its tile count go into the first free slot of the scroll entry's level-DL-0 list
// (+0x1C / +0x30) or, with `secondDl`, its level-DL-1 list (+0x26 / +0x35). The entry is the first in D_800E0D18
// (oldest first, link +4) with id 0 (none: a new one from func_15195EF4 with `doubled`, speeds speedS / speedT).
// `unused` is not read. On later matches texId may be the new negative id, which then indexes D_800B1268 below 0
// (as in the asm).
// Returns the last entry used (NULL when dl is NULL, nothing matched or allocation failed).
void *func_15195AA8(s32 dl, s32 texId, s32 doubled, s32 which, s32 unused, s32 secondDl, s32 speedS, s32 speedT) {
    Gfx *gdl = (Gfx *) dl;
    Ent3C *e = NULL;
    s32 skip;
    s32 idx;
    s32 tileCount;
    u32 w0;
    u32 w1;
    s32 k;

    if (gdl == NULL) {
        return NULL;
    }
    skip = which;
    if (which == -1) {
        skip = 0;
    }
    do {
        idx = func_15195DD8(gdl, texId, skip, &tileCount);
        if (idx == -1) {
            which = 0;
            continue;
        }
        if (texId == 0) {
            texId = D_800E0D20;
        }
        w1 = gdl[idx].words.w1;
        w0 = gdl[idx].words.w0;
        for (e = (Ent3C *) D_800E0D18; e != NULL && e->x8 != 0; e = (Ent3C *) e->node.prev) {
        }
        if (e == NULL) {
            e = func_15195EF4(texId, w1, w0, doubled);
            if (e == NULL) {
                return NULL;
            }
            e->x12 = speedS;
            e->x13 = speedT;
        } else {
            idx = func_15195FF4(idx, (s32) e, w1, doubled);
        }
        skip++;
        if (e->x14 < tileCount) {
            e->x14 = tileCount;
        }
        if (!secondDl) {
            for (k = 0; k < 5 && e->a[k] != -1; k++) {
            }
            if (k < 5) {
                e->a[k] = idx;
                ((u8 *) e)[0x30 + k] = tileCount;
            }
        } else {
            for (k = 0; k < 5 && e->b[k] != -1; k++) {
            }
            if (k < 5) {
                e->b[k] = idx;
                ((u8 *) e)[0x35 + k] = tileCount;
            }
        }
    } while (which == -1);
    if (texId == D_800E0D20) {
        D_800E0D20--;
    }
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195AA8.s")
#endif

typedef struct Ent6270 {
    struct Ent6270 *dnext;
    struct Ent6270 *dprev;
    s32 id;
    u16 sub;
    u8 flag;
    u8 padF;
    struct Ent6270 *next;
} Ent6270;

s32 func_15196270(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) // fakematch: non-void return type with bare returns (void gives a different reg copy; remote permuter)
{
  Ent6270 *e;
  Ent6270 *n;
  Ent6270 *nx;
  nx = *((Ent6270 **) (arg0 + 0x18));
  e = nx;
  if (nx != 0)
  {
    do
    {
      if ((arg1 == e->id) && (arg2 == e->sub))
      {
        return;
      }
      nx = e->next;
      if (nx != 0)
      {
        e = nx;
        nx = nx->next;
      }
    }
    while (nx != 0);
    n = (Ent6270 *) func_15195D20(0x14, (DNode **) (&D_800E0D10), (DNode **) (&D_800E0D14));
    e->next = n;
  }
  else
  {
    n = (Ent6270 *) func_15195D20(0x14, (DNode **) (&D_800E0D10), (DNode **) (&D_800E0D14));
    *((Ent6270 **) (arg0 + 0x18)) = n;
  }
  n->id = arg1;
  n->sub = arg2;
  n->flag = arg3;
  n->next = 0;
}

#ifdef NON_MATCHING
// dl_add_texture_scroll: as func_15195AA8 for a model display list `dl` (s32 address): each matching G_SETTIMG
// (`which`-th, -1: every one) is linked to the scroll entry with id texId (or, with `alwaysNew`, a new one for the
// first match) through func_15196270 (+0x18 chain: dl, G_SETTILESIZE index, tile count). New entries get speeds
// speedS / speedT. Does nothing while D_800BEAC0 is set. Returns the last entry used as s32 (0: none).
// The asm returns an uninitialised stack word when the very first search finds nothing (C: 0).
s32 func_15196344(s32 dl, s32 texId, s32 doubled, s32 which, s32 alwaysNew, s32 speedS, s32 speedT) {
    Gfx *gdl = (Gfx *) dl;
    Ent3C *e = NULL;
    s32 skip;
    s32 idx;
    s32 key;
    s32 tileCount;
    u32 w0;
    u32 w1;

    if (gdl == NULL) {
        return 0;
    }
    if (D_800BEAC0 != 0) {
        return 0;
    }
    skip = which;
    if (which == -1) {
        skip = 0;
    }
    do {
        idx = func_15195DD8(gdl, texId, skip, &tileCount);
        if (idx == -1) {
            which = 0;
            continue;
        }
        if (texId == 0) {
            texId = D_800E0D20;
        }
        key = alwaysNew ? -1 : texId;
        for (e = (Ent3C *) D_800E0D18; e != NULL && e->x8 != key; e = (Ent3C *) e->node.prev) {
        }
        w1 = gdl[idx].words.w1;
        w0 = gdl[idx].words.w0;
        if (e == NULL) {
            e = func_15195EF4(texId, w1, w0, doubled);
            if (e == NULL) {
                return 0;
            }
            alwaysNew = 0;
            e->x12 = speedS;
            e->x13 = speedT;
        } else {
            idx = func_15195FF4(idx, (s32) e, w1, doubled);
            alwaysNew = 0;
        }
        if (e->x14 < tileCount) {
            e->x14 = tileCount;
        }
        func_15196270((u8 *) e, dl, idx, tileCount);
        skip++;
    } while (which == -1);
    if (texId == D_800E0D20) {
        D_800E0D20--;
    }
    return (s32) e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196344.s")
#endif

// texture_anim_start_for: starts a texture animation on the model's texture set (arg0 +0x1C) and returns
// func_15196344's handle (asm callers func_15116690 / func_1511D0CC / func_150BFC60 store v0; P172).
s32 func_15195FB0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return func_15196344(*(s32 *)(arg0 + 0x1C), arg1, arg2, arg3, arg4, arg5, arg6);
}

#ifdef NON_MATCHING
/* P43: texture scrolling. For each entry of the D_800E0D18 list (next at +4): the scroll position (+0xE, +0x10, u16)
 * gives up to 8 (+0x14) G_SETTILESIZE words (0xF2000000 | s << 12 | t, s and t halved per mip level), written to the
 * level DLs arg0 (indices +0x1C[5], counts +0x30[5]) and arg1 (+0x26[5], +0x35[5]) and to the +0x18 chain of extra
 * DLs (+8 base, +0xC index, +0xE count, next at +0x10); then the position moves by speed (+0x12, +0x13, s8) times
 * D_800BE9E4 unless D_800BEAC0, wrapping once at the texture size (+0xA, +0xC) * 8. A count above the number of
 * words built reads stale stack in the asm (C: uninitialised tbl[]). The asm returns no value. */
s32 func_15196560(s32 arg0, s32 arg1) {
    s32 tbl[8];  /* sp5C */
    u8 *e;
    u8 *p;
    s32 u, v, w, h;
    s32 su, sv;
    s32 n, j, k;
    s16 idx;

    for (e = (u8 *)D_800E0D18; e != NULL; e = *(u8 **)(e + 4)) {
        u = *(u16 *)(e + 0xE);
        v = *(u16 *)(e + 0x10);
        w = *(s16 *)(e + 0xA);
        h = *(s16 *)(e + 0xC);
        su = u / 8 + 2;
        sv = v / 8 + 2;
        if (su >= w) {
            su -= w;
        }
        if (sv >= h) {
            sv -= h;
        }
        n = 0;
        if (e[0x14] > 0) {
            do {
                tbl[n++] = 0xF2000000 | ((su & 0xFFF) << 12) | (sv & 0xFFF);
                su /= 2;
                sv /= 2;
            } while (n < 8 && n < e[0x14]);
        }
        w *= 8;
        h *= 8;
        if (D_800BEAC0 == 0) {
            u += *(s8 *)(e + 0x12) * D_800BE9E4;
            v += *(s8 *)(e + 0x13) * D_800BE9E4;
        }
        if (u < 0) {
            u += w;
        } else if (u >= w) {
            u -= w;
        }
        if (v < 0) {
            v += h;
        } else if (v >= h) {
            v -= h;
        }
        *(u16 *)(e + 0xE) = u;
        *(u16 *)(e + 0x10) = v;
        if (*(s16 *)(e + 0x1C) != -1) {
            k = 0;
            do {
                idx = *(s16 *)(e + 0x1C + k * 2);
                for (j = 0; j < e[0x30 + k]; j++) {
                    *(s32 *)(arg0 + idx * 8 + j * 16) = tbl[j];
                }
                k++;
            } while (k < 5 && *(s16 *)(e + 0x1C + k * 2) != -1);
        }
        if (*(s16 *)(e + 0x26) != -1) {
            k = 0;
            do {
                idx = *(s16 *)(e + 0x26 + k * 2);
                for (j = 0; j < e[0x35 + k]; j++) {
                    *(s32 *)(arg1 + idx * 8 + j * 16) = tbl[j];
                }
                k++;
            } while (k < 5 && *(s16 *)(e + 0x26 + k * 2) != -1);
        }
        for (p = *(u8 **)(e + 0x18); p != NULL; p = *(u8 **)(p + 0x10)) {
            for (j = 0; j < p[0xE]; j++) {
                *(s32 *)(*(s32 *)(p + 8) + *(u16 *)(p + 0xC) * 8 + j * 16) = tbl[j];
            }
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196560.s")
#endif

void func_15196888(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        arg0[0x12] = arg1;
        arg0[0x13] = arg2;
    }
}

extern void (*D_8008FC38[])(void *);
extern void (*D_8008FC2C[])(void *);
s32 func_15147E64(u8 *);
void func_151968A0(u8 *arg0) {
    u8 *o = *(u8 **)(arg0 + 0x98);
    s8 i = o[0x65];
    s8 j;
    if (i != -1) {
        D_8008FC38[i](arg0);
    }
    j = o[0x62];
    if (j != -1) {
        D_8008FC2C[j](arg0);
    }
    func_15147E64(arg0);
}

extern void (*D_8008FC38[])(void *);
extern void (*D_8008FC2C[])(void *);
s32 func_15147E98(u8 *);
void func_15196924(u8 *arg0) {
    u8 *o = *(u8 **)(arg0 + 0x98);
    s8 i = o[0x65];
    s8 j;
    if (i != -1) {
        D_8008FC38[i](arg0);
    }
    j = o[0x62];
    if (j != -1) {
        D_8008FC2C[j](arg0);
    }
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
typedef struct { f32 x, y, z; } EmitterVec;

/* D_800A8B80: 0x60-byte emitter kind rows (rodata_inject of the GLOBAL_ASM; referenced by symbol, P129 practice). */
typedef struct {
    /* 0x00 */ s16 kind;        /* request +0xC */
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ u8 u0C;
    /* 0x10 */ s32 u10;         /* stored as a byte in the request (+0x15) */
    /* 0x14 */ u8 node;         /* model matrix index (obj +0x1D4 + node * 0x40) */
    /* 0x18 */ EmitterVec at;   /* local points, transformed by the node's matrix */
    /* 0x24 */ EmitterVec at2;
    /* 0x30 */ s8 speedFn;      /* D_8008FC10 index, -1 = none */
    /* 0x31 */ u8 u31;
    /* 0x32 */ u8 u32;
    /* 0x33 */ u8 u33;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 u38;
    /* 0x3C */ s8 initFn;       /* D_8008FC1C index, -1 = none */
    /* 0x3D */ s8 u3D;
    /* 0x3E */ s8 u3E;
    /* 0x3F */ s8 soundFn;      /* D_8008FC30 index (start sound), -1 = none */
    /* 0x40 */ s8 u40;
    /* 0x41 */ s8 u41;
    /* 0x42 */ s8 u42;
    /* 0x44 */ u16 u44;         /* request +0xE */
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ f32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ u8 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ u8 u5C[4];
} EmitterKind;

/* The 0x90-byte record copied into the new emitter's +0x98 buffer (func_151991D0 / func_15199200 read +0x66). */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 objId;        /* obj +0x3B */
    /* 0x05 */ u8 node;
    /* 0x06 */ u8 flags;        /* 2 */
    /* 0x07 */ s8 speedFn;
    /* 0x08 */ EmitterVec at;
    /* 0x14 */ EmitterVec at2;
    /* 0x20 */ EmitterVec pos;  /* world points */
    /* 0x2C */ EmitterVec pos2;
    /* 0x38 */ f32 speed;       /* set after the copy from D_8008FC10 */
    /* 0x3C */ f32 u3C;
    /* 0x40 */ f32 u40;
    /* 0x44 */ f32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ u8 u50;
    /* 0x51 */ u8 u51;
    /* 0x52 */ u8 u52;
    /* 0x53 */ u8 u53;
    /* 0x54 */ u8 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ f32 u5C;
    /* 0x60 */ s8 initFn;
    /* 0x61 */ s8 u61;
    /* 0x62 */ s8 u62;
    /* 0x63 */ s8 soundFn;
    /* 0x64 */ s8 u64;
    /* 0x65 */ s8 u65;
    /* 0x66 */ u16 voice;
    /* 0x68 */ s8 u68;
    /* 0x69 */ u8 u69;
    /* 0x6A */ u8 u6A;
    /* 0x6C */ f32 u6C;
    /* 0x70 */ f32 u70;
    /* 0x74 */ u8 u74;
    /* 0x78 */ f32 u78;
    /* 0x7C */ f32 u7C;
    /* 0x80 */ u8 u80;
    /* 0x84 */ f32 u84;
    /* 0x88 */ f32 u88;
    /* 0x8C */ u8 u8C[4];
} EmitterRecord;

/* The request func_15147FF0 reads (position, kind, life). */
typedef struct {
    /* 0x00 */ EmitterVec pos;
    /* 0x0C */ s16 kind;
    /* 0x0E */ u16 u0E;
    /* 0x10 */ s32 u10;         /* 3 */
    /* 0x14 */ u8 pad14;
    /* 0x15 */ u8 u15;
} EmitterRequest;

void *memcpy(void *, const void *, s32);
extern EmitterKind D_800A8B80[];
extern f32 (*D_8008FC10[])(u8 *);   /* speed: func_15197F68 / func_15197F7C / func_15197FD8 */
extern void (*D_8008FC1C[])(u8 *);  /* init: func_15199954 */
extern u16 (*D_8008FC30[])(void);   /* start sound: func_151991D0 */

// object_emitter_spawn: spawns emitter `kind` (D_800A8B80 row) attached to the object's model node: fills the 0x90-byte
// record (object, node, the row's two local points and their world positions, the row's parameters, the start
// sound's voice handle), asks func_15147FF0 for a 0x90-byte emitter (layer / owner from arg2 / arg3), copies the
// record into it, sets its speed from D_8008FC10 and runs the init handler. Returns the emitter (0 when the object
// or its model matrices are missing, or no emitter is free).
u8 *func_15196438(u8 *obj, s32 kind, u8 arg2, s32 arg3) {
    EmitterRecord rec;
    EmitterRequest req;
    EmitterKind *k;
    EmitterRecord *dst;
    u8 *mtx;
    u8 *e;

    if (obj == NULL) {
        return NULL;
    }
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        return NULL;
    }
    k = &D_800A8B80[kind];
    rec.obj = obj;
    rec.objId = obj[0x3B];
    rec.node = k->node;
    rec.flags = 2;
    rec.speedFn = k->speedFn;
    rec.at = k->at;
    rec.at2 = k->at2;
    rec.u40 = k->u04;
    rec.u48 = k->u08;
    rec.u4C = 0.0f;
    rec.u50 = 0;
    rec.u51 = k->u0C;
    rec.u52 = k->u31;
    rec.u53 = k->u32;
    rec.u54 = k->u33;
    rec.u58 = k->u34;
    rec.u5C = k->u38;
    rec.initFn = k->initFn;
    rec.u61 = k->u3D;
    rec.u62 = k->u3E;
    rec.soundFn = k->soundFn;
    rec.u64 = k->u40;
    rec.u65 = k->u41;
    rec.u68 = k->u42;
    rec.u69 = k->u46;
    rec.u6A = k->u47;
    rec.u6C = k->u48;
    rec.u70 = 0.0f;
    rec.u74 = k->u4C;
    rec.u78 = k->u50;
    rec.u7C = 0.0f;
    rec.u80 = k->u54;
    rec.u84 = k->u58;
    rec.u88 = 0.0f;
    rec.u8C[0] = k->u5C[0];
    rec.u8C[1] = k->u5C[1];
    rec.u8C[2] = k->u5C[2];
    rec.u8C[3] = k->u5C[3];
    req.kind = k->kind;
    req.u0E = k->u44;
    req.u15 = k->u10;

    /* P235 (browser P233 arity_scan): no arguments is right. tablesig: D_8008FC30 has one entry, func_151991D0
       (matching C `void (void)`, NM `u16 (void)`), which sets a0..a3 itself; the asm only leaves them live. */
    if (rec.soundFn != -1) {
        rec.voice = D_8008FC30[rec.soundFn]();
    } else {
        rec.voice = 0;
    }

    mtx = *(u8 **)(rec.obj + 0x1D4) + (rec.node << 6);
    func_15143134(&rec.at, &rec.pos, mtx);
    func_15143134(&rec.at2, &rec.pos2, mtx);
    req.pos.x = rec.pos.x;
    req.pos.y = rec.pos.y;
    req.pos.z = rec.pos.z;
    rec.u3C = 0.0f;
    req.u10 = 3;

    e = func_15147FF0(&req, 0x90, 0x24, 2, 2, 2, 0, 0, 0, arg2, arg3);
    if (e != NULL) {
        dst = *(EmitterRecord **)(e + 0x98);
        memcpy(dst, &rec, sizeof(EmitterRecord));
        if (dst->speedFn != -1) {
            dst->speed = D_8008FC10[dst->speedFn](e);
        } else {
            dst->speed = 0.0f;
        }
        if (rec.initFn != -1) {
            D_8008FC1C[rec.initFn](e);
        }
    }
    return e;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196438.s")
#endif

#ifdef NON_MATCHING
s32 func_15198680(u8 *, s8, f32 *, u8 *);
extern s32 D_8008FC20;
extern s32 D_8008FC34;
extern s32 D_8008FC3C;

s32 func_15196CB8(u8 *arg0) {
    u8 *sp34;
    s32 sp30;
    u8 *sp20;
    s16 var_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 var_a1;
    s32 var_s1_3;
    s32 var_t2;
    s8 temp_v0_3;
    s8 temp_v0_4;
    s8 temp_v0_5;
    s8 temp_v1;
    s8 var_s1;
    s8 var_s1_2;
    s8 var_v1_2;
    u8 var_a0;
    u8 var_a0_2;
    u8 *temp_t5;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_a3;

    var_a3 = (*(u8 **)((u8 *)arg0 + 0x98));
    var_t2 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)var_a3 + 6)) & 1)) {
        return 0;
    }
    var_s1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s1 -= 1;
            if (var_s1 < 0) {
                var_s1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v0 = var_t2 + (var_s1 * 0x24);
            temp_v1 = (*(s8 *)((u8 *)temp_v0 + 0x1E));
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) + ((*(f32 *)((u8 *)var_a3 + 0x40)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0)) + ((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 4)) + ((*(f32 *)((u8 *)temp_v0 + 0x10)) * D_800BE9A4));
            (*(s8 *)((u8 *)temp_v0 + 0x1F)) = 0xFF;
            (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + ((*(f32 *)((u8 *)temp_v0 + 0x14)) * D_800BE9A4));
            if (temp_v1 > 0) {
                (*(s8 *)((u8 *)temp_v0 + 0x1E)) = (s8) (temp_v1 - D_800BE9E4);
            } else {
                (*(s16 *)((u8 *)temp_v0 + 0x1C)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0x1C)) - ((*(u8 *)((u8 *)var_a3 + 0x52)) * D_800BE9E4));
            }
            var_v1 = (*(s16 *)((u8 *)temp_v0 + 0x1C));
            if ((var_v1 < (s32) (*(u8 *)((u8 *)var_a3 + 0x6A))) && ((*(u8 *)((u8 *)temp_v0 + 0x21)) == 0)) {
                sp20 = temp_v0;
                sp34 = var_a3;
                sp30 = var_t2;
                func_15198680(arg0, var_s1, &D_800BE9A4, var_a3);
                var_v1 = (*(s16 *)((u8 *)temp_v0 + 0x1C));
            }
            (*(f32 *)((u8 *)temp_v0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x18)) + ((*(f32 *)((u8 *)var_a3 + 0x58)) * D_800BE9A4));
            if (var_v1 < 0) {
                (*(u8 *)((u8 *)var_a3 + 6)) = (u8) ((*(u8 *)((u8 *)var_a3 + 6)) & 0xFFFD);
                if (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((var_t2 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x1C)) = 0;
            }
        } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    var_s1_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
    if ((*(u8 *)((u8 *)var_a3 + 6)) & 2) {
        var_v1_2 = 0;
        var_a0 = (*(u8 *)((u8 *)var_a3 + 0x8C));
loop_22:
        temp_lo = var_s1_2 * 0x24;
        var_s1_2 += 1;
        var_a0 = (u8) (s16) (var_a0 - 1);
        (*(s8 *)((u8 *)((var_t2 + temp_lo)) + 0x1F)) = var_v1_2;
        var_v1_2 = (var_v1_2 + (*(u8 *)((u8 *)var_a3 + 0x8D))) & 0xFF;
        if (var_s1_2 == (*(u8 *)((u8 *)arg0 + 0x25))) {
            var_s1_2 = 0;
        }
        if ((var_a0 != 0) && (var_s1_2 != (*(s8 *)((u8 *)arg0 + 0x2E)))) {
            goto loop_22;
        }
    }
    if ((*(u8 *)((u8 *)var_a3 + 6)) & 4) {
        var_a1 = 0;
        var_a0_2 = (*(u8 *)((u8 *)var_a3 + 0x8E));
        var_s1_3 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_s1_3 < 0) {
            var_s1_3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
loop_30:
        temp_lo_2 = var_s1_3 * 0x24;
        var_s1_3 -= 1;
        var_a0_2 = (u8) (s16) (var_a0_2 - 1);
        temp_v0_2 = var_t2 + temp_lo_2;
        (*(u8 *)((u8 *)temp_v0_2 + 0x1F)) = (u8) ((s32) ((*(u8 *)((u8 *)temp_v0_2 + 0x1F)) * var_a1) >> 8);
        var_a1 = (var_a1 + (*(u8 *)((u8 *)var_a3 + 0x8F))) & 0xFF;
        if (var_s1_3 < 0) {
            var_s1_3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if ((var_a0_2 != 0) && (var_s1_3 != (*(s8 *)((u8 *)arg0 + 0x2E)))) {
            goto loop_30;
        }
    }
    temp_v0_3 = (*(s8 *)((u8 *)var_a3 + 0x64));
    if (temp_v0_3 != -1) {
        sp34 = var_a3;
        sp30 = var_t2;
        (*(s32 (**)())((u8 *)&D_8008FC34 + (temp_v0_3 * 4)))(arg0);
    }
    temp_v0_4 = (*(s8 *)((u8 *)var_a3 + 0x68));
    if (temp_v0_4 != -1) {
        sp34 = var_a3;
        sp30 = var_t2;
        (*(s32 (**)())((u8 *)&D_8008FC3C + (temp_v0_4 * 4)))(arg0);
    }
    temp_v0_5 = (*(s8 *)((u8 *)var_a3 + 0x61));
    if (temp_v0_5 != -1) {
        sp30 = var_t2;
        if ((*(s32 (**)())((u8 *)&D_8008FC20 + (temp_v0_5 * 4)))(arg0) == 0) {
            return 0;
        }
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_t5 = var_t2 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(s32 *)((u8 *)arg0 + 0x54)) = (s32) (*(s32 *)((u8 *)temp_t5 + 0));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (*(s32 *)((u8 *)temp_t5 + 4));
        (*(s32 *)((u8 *)arg0 + 0x5C)) = (s32) (*(s32 *)((u8 *)temp_t5 + 8));
        return 1;
    }
    (*(s32 *)((u8 *)arg0 + 0x54)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x58)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x5C)) = 0;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196CB8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151970BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151976B8.s")

f32 func_15197F68(s32 arg0) {
    return 1.32f;
}

f32 func_15197F7C(s32 arg0) {
    return (f32) func_151422C0(0xA, (s32) "power", 1, 0x1F4, "../Effects/CharacterFlameThrower/characterflamethrower.c", 0x8CC) * 0.01f;
}

f32 func_15197FD8(s32 arg0) {
    return 10.9f;
}

void func_15197A7C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 8);
    }
}

s32 func_15198024(u8 *arg0) {
    *(f32 *)(arg0 + 0x140) *= *(f32 *)(arg0 + 0x15C);
    *(f32 *)(arg0 + 0x144) += *(f32 *)(arg0 + 0x158) * D_800BE9A4;
    *(f32 *)(arg0 + 0x148) *= *(f32 *)(arg0 + 0x15C);
    *(f32 *)(arg0 + 0x14C) *= *(f32 *)(arg0 + 0x160);
    *(f32 *)(arg0 + 0x150) += *(f32 *)(arg0 + 0x158) * D_800BE9A4;
    *(f32 *)(arg0 + 0x154) *= *(f32 *)(arg0 + 0x160);
    *(f32 *)(arg0 + 0x34) += *(f32 *)(arg0 + 0x140) * D_800BE9A4;
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x144) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += *(f32 *)(arg0 + 0x148) * D_800BE9A4;
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x14C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x150) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x154) * D_800BE9A4;
    return 1;
}

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0x107];
    f32 unk164;
    s16 unk168;
    s16 unk16A;
} struct_1519812C;

s32 func_1519812C(struct_1519812C *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk164;
    arg0->unk2C -= arg0->unk2C * arg0->unk164;
    if (arg0->unk1C < arg0->unk168) {
        arg0->unk5C = arg0->unk1C * arg0->unk16A;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198180.s")

void func_15199924(u8 *arg0);
void func_151985C4(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    s32 cur;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0 || arg2 == 2 || arg2 == 0x8) {
        if (*(s32 *)p == arg1[0] || p[4] == ((u8 *)arg1)[4]) {
            func_15199924(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)p) {
            *(s32 *)p = arg1[1];
            p[4] = ((u8 *)arg1)[9];
        } else if (arg1[1] == *(s32 *)p) {
            *(s32 *)p = arg1[0];
            p[4] = ((u8 *)arg1)[8];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198680.s")

#ifdef NON_MATCHING
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3);
u8 *func_1518D1C0(u8 *obj, s16 type, s16 time, u8 clear, u8 view, s32 arg5, char *name);
// path_flame_touch_player: path handler 0 of D_8008FC20 (`s32 (*)(u8 *)`, result tested by the path updater).
// Walks back from the path's head point +0x2E to the current point +0x2D (ring of +0x25 points of 0x24 bytes at
// +0x94); when player 0 (D_800CC2D0[0]: x +0x14, y +0x18 + s16 +0xE8, z +0x1C) is within its radius s16 +0xE4 of a
// point (the height difference scaled by (1 + r / +0xE6) / 2), it is hurt (func_1505D024 flags 0x60006 with its u16
// +0x7A, by the owner object **(arg0 + 0x98)), gets the flame-thrower effect (func_1518D1C0 type 0xB with the
// emitter's +0x0C / +0x01), and the current point advances to that point (count +0x2C drops by one per step).
// Always returns 1.
s32 func_15198AE0(u8 *arg0) {
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *player = (u8 *) D_800CC2D0;
    f32 *pt;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    i = *(s8 *) (arg0 + 0x2E);
    while (i != *(s8 *) (arg0 + 0x2D)) {
        i--;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        pt = (f32 *) (points + i * 0x24);
        radius = *(s16 *) (player + 0xE4);
        height = *(s16 *) (player + 0xE6);
        dx = pt[0] - *(f32 *) (player + 0x14);
        dz = pt[2] - *(f32 *) (player + 0x1C);
        dy = (pt[1] - (*(f32 *) (player + 0x18) + *(s16 *) (player + 0xE8))) * ((1.0f + radius / height) * 0.5f);
        if (dx * dx + dy * dy + dz * dz < radius * radius) {
            func_1505D024(D_800CC2D0, 0x60006, *(u16 *) (player + 0x7A),
                          (s32) (*(u8 **) owner - (u8 *) D_800CC2D0) / 0x32C);
            func_1518D1C0(player, 0xB, 0, 1, arg0[0xC], arg0[1], "Characterflamethrower");
            while (i != *(s8 *) (arg0 + 0x2D)) {
                (*(s8 *) (arg0 + 0x2D))++;
                if (arg0[0x25] == *(s8 *) (arg0 + 0x2D)) {
                    *(s8 *) (arg0 + 0x2D) = 0;
                }
                (*(s8 *) (arg0 + 0x2C))--;
            }
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198AE0.s")
#endif

#ifdef NON_MATCHING
// path_pass_points_near_objects: path handler 2 of D_8008FC20 (`s32 (*)(u8 *)`, its result is tested by the path
// updater). For every live object of D_800CC2D0 (+0x00 set, not held: +0x65 == 0) whose team byte +0x3B differs
// from the path owner's (**(arg0 + 0x98))[0x3B], it walks back from the path's head point +0x2E to the current
// point +0x2D (ring of +0x25 points of 0x24 bytes at +0x94). When the object (x +0x14, y +0x18 + s16 +0xE8,
// z +0x1C) is within (radius +0xE4)^2 + 2500 of a point (the height difference scaled by (1 + r / +0xE6) / 2),
// the current point advances to it (wrapping at +0x25), and the remaining count +0x2C drops by one per step.
// Always returns 1.
s32 func_15198D3C(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *obj;
    f32 *pt;
    f32 radius;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    for (obj = (u8 *) D_800CC2D0; obj != (u8 *) &D_800D121C; obj += 0x32C) {
        if (*(s32 *) obj == 0 || obj[0x65] != 0 || obj[0x3B] == (*(u8 **) owner)[0x3B]) {
            continue;
        }
        i = *(s8 *) (arg0 + 0x2E);
        while (i != *(s8 *) (arg0 + 0x2D)) {
            i--;
            if (i < 0) {
                i = arg0[0x25] - 1;
            }
            pt = (f32 *) (points + i * 0x24);
            radius = *(s16 *) (obj + 0xE4);
            height = *(s16 *) (obj + 0xE6);
            dx = pt[0] - *(f32 *) (obj + 0x14);
            dz = pt[2] - *(f32 *) (obj + 0x1C);
            dy = (pt[1] - (*(f32 *) (obj + 0x18) + *(s16 *) (obj + 0xE8))) * ((1.0f + radius / height) * 0.5f);
            if (dx * dx + dy * dy + dz * dz < radius * radius + 2500.0f) {
                while (i != *(s8 *) (arg0 + 0x2D)) {
                    (*(s8 *) (arg0 + 0x2D))++;
                    if (arg0[0x25] == *(s8 *) (arg0 + 0x2D)) {
                        *(s8 *) (arg0 + 0x2D) = 0;
                    }
                    (*(s8 *) (arg0 + 0x2C))--;
                }
            }
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198D3C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198EEC.s")

#ifdef NON_MATCHING
/* P163: D_8008FC30 is the one-entry start-sound table (FC34 / FC38 / FC3C are separate update / stop / extra tables,
   each indexed by its own record byte, -1 = none); func_15196438 (asm) stores the entry's v0 as the record's u16 voice handle (`sh $v0, 0xB2($sp) = record + 0x66`), so this returns func_10010F30's handle. */
// emitter_sound_start: starts sound 0x1AA at full volume and returns its voice handle
u16 func_151991D0(void) {
    return func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#else
void func_151991D0(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#endif

void func_15199200(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;
    u16 temp_a0;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(u8 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        temp_a0 = *(u16 *)(temp_v0 + 0x66);
        if (temp_a0 != 0) {
            func_1000F91C(temp_a0, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 0)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 4)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 8)), 0x1F4, 0x1388); // fakematch: (0, x) comma flips commutative operand order
        }
    }
}

void func_151992B0(u8 *arg0) {
    u8 *p;
    u16 t;
    p = *(u8 **)(arg0 + 0x98);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        t = *(u16 *)(p + 0x66);
        if (t != 0) {
            func_100111C8(t);
        }
    }
}

void func_151992EC(s32 arg0) {
}

#ifdef NON_MATCHING
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s32 D_800A8B08;

void func_151992F8(u8 *arg0, u8 *arg1) {
    struct {
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        u8 padDC[0x4];
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        u8 padE4[0x4];
        s32 uE8;
        u8 padEC[0x8];
        s16 uF4;
        s16 uF6;
        u8 padF8[0x5];
        s8 uFD;
        u8 padFE[0xA];
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s32 u11C;
        s32 u120;
        s8 u124;
        s8 u125;
    } sp;
    f32 spBC;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s4;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x98));
    sp.uF6 = 1;
    sp.uE1 = 0xA;
    sp.uE2 = 0xFF;
    sp.uE0 = 0x28;
    sp.uE3 = 0x82;
    (*(f32 *)((u8 *)(&sp.uE8) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
    (*(f32 *)((u8 *)(&sp.uE8) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    temp_s0 = (u8 *) &D_800A8B08 + (*(u8 *)((u8 *)temp_s4 + 0x74)) * 0x24;
    (*(f32 *)((u8 *)(&sp.uE8) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u108 = 0;
    sp.u10C = 1;
    sp.u110 = 0x160600;
    sp.u114 = 3;
    sp.u118 = 0x10;
    sp.u11C = 0x80;
    sp.u120 = 0x20;
    sp.u124 = 0;
    sp.u125 = 9;
    do {
        temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 8))) + (*(f32 *)((u8 *)temp_s0 + 4));
        temp_s1 = func_150ADA20() & 0xFF;
        temp_s2 = func_150ADA20() & 0xFF;
        temp_f22 = func_151423D8((temp_s1 - 0x40) & 0xFF);
        temp_f24 = func_151423D8(temp_s1 & 0xFF);
        temp_f26 = func_151423D8((temp_s2 - 0x40) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0));
        temp_f12 = temp_f2 * func_151423D8(temp_s2 & 0xFF);
        temp_f28 = (*(f32 *)((u8 *)arg1 + 0)) + (temp_f12 * temp_f22);
        temp_f30 = (*(f32 *)((u8 *)arg1 + 4)) - (temp_f2 * temp_f26);
        spBC = (*(f32 *)((u8 *)arg1 + 8)) + (temp_f12 * temp_f24);
        sp.uFD = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x22)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x20));
        sp.uF4 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
        sp.uC8 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 0xC));
        sp.uD8 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x18))) + (*(f32 *)((u8 *)temp_s0 + 0x14));
        sp.uCC = (temp_f28 - (*(f32 *)((u8 *)arg0 + 0x10))) * temp_f20;
        sp.uD0 = (temp_f30 - (*(f32 *)((u8 *)arg0 + 0x14))) * temp_f20;
        sp.uD4 = (spBC - (*(f32 *)((u8 *)arg0 + 0x18))) * temp_f20;
        func_15148310(&sp.uE8, &sp.uC8, 0, 1, 0, 0, 0, 0, 0, 0, 0, &sp.u108, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(f32 *)((u8 *)temp_s4 + 0x7C)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 0x7C)) - 1.0f);
    } while ((*(f32 *)((u8 *)temp_s4 + 0x7C)) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151992F8.s")
#endif
#ifdef NON_MATCHING
void *func_15167D84(void *, s32, s32, s32, s32, s32);
extern s32 D_800908C4;
extern u8 D_800A8B50[]; /* 0x18-byte burst descriptors: f32 radius, speed base, speed range; s16 pairs (base, range) */

// spray_particles_burst: while the owner's counter (+0x88 of arg0's data) is above 1, spawns one particle per unit
// (func_15167D84, the 0x38-byte template below, P124: one struct instead of m2c's 26 separate locals): random
// direction on a sphere of the descriptor's radius around arg1, velocity = offset from arg0's position times a
// random speed, random life / size / scale from the descriptor (D_800A8B50[data[0x80]]).
void func_1519961C(u8 *arg0, u8 *arg1) {
    struct {
        void *u0;
        s32 u4;
        s32 u8;
        s16 uC;
        s16 uE;
        s16 u10;
        s16 u12;
        s16 u14;
        s16 u16;
        s16 u18;
        s16 u1A;
        s8 u1C;
        s8 u1D;
        s8 u1E;
        s8 u1F;
        s16 u20;
        s16 u22;
        s16 u24;
        s16 u26;
        s16 u28;
        u8 u2A;
        u8 u2B;
        u8 u2C;
        u8 u2D;
        u8 u2E;
        u8 u2F;
        u8 u30;
        u8 u31;
        u8 u32;
        u8 pad33;
        s16 u34;
        u8 pad36[2];
    } t;
    u8 *data;
    u8 *desc;
    f32 speed;
    f32 radius;
    f32 ring;
    f32 sinA;
    f32 cosA;
    f32 sinB;
    s32 a;
    s32 b;
    s16 v;

    data = *(u8 **)(arg0 + 0x98);
    t.u10 = *(f32 *)(arg0 + 0x10);
    desc = &D_800A8B50[data[0x80] * 0x18];
    t.u12 = *(f32 *)(arg0 + 0x14);
    t.u1C = 0;
    t.u1E = 0;
    t.u1D = 0;
    t.u2C = 0xFF;
    t.u2D = 0xFF;
    t.u2E = 0xFF;
    t.u30 = 0;
    t.u31 = 0;
    t.u32 = 0;
    t.u2F = 0xFF;
    t.u1F = -1;
    t.u34 = 0x12;
    t.uC = 0;
    t.uE = 0;
    t.u0 = &D_800908C4;
    t.u28 = 300;
    t.u14 = *(f32 *)(arg0 + 0x18);
    do {
        speed = func_150ADA68() * *(f32 *)(desc + 8) + *(f32 *)(desc + 4);
        a = func_150ADA20() & 0xFF;
        b = func_150ADA20() & 0xFF;
        sinA = func_151423D8((a - 0x40) & 0xFF);
        cosA = func_151423D8(a);
        sinB = func_151423D8((b - 0x40) & 0xFF);
        radius = *(f32 *)(desc + 0);
        ring = radius * func_151423D8(b);
        t.u16 = ((*(f32 *)(arg1 + 0) + ring * sinA) - *(f32 *)(arg0 + 0x10)) * speed;
        t.u20 = ((*(f32 *)(arg1 + 4) - radius * sinB) - *(f32 *)(arg0 + 0x14)) * speed;
        t.u18 = ((*(f32 *)(arg1 + 8) + ring * cosA) - *(f32 *)(arg0 + 0x18)) * speed;
        t.u22 = func_150ADA20() % (u32) (*(s16 *)(desc + 0xE) + 1) + *(s16 *)(desc + 0xC);
        t.u2A = func_150ADA20() % (u32) (*(s16 *)(desc + 0x12) + 1) + *(s16 *)(desc + 0x10);
        v = func_150ADA20() % (u32) (*(s16 *)(desc + 0x16) + 1) + *(s16 *)(desc + 0x14);
        t.u26 = v;
        t.u24 = v;
        func_15167D84(&t, 0, 0, -1, arg0[0xC], arg0[1]);
        *(f32 *)(data + 0x88) -= 1.0f;
    } while (*(f32 *)(data + 0x88) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519961C.s")
#endif
void func_15199924(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[6] |= 1;
    temp_v0[6] |= 4;
}

void func_15199954(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 0;
    }
}

void func_151999BC(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199A28.s")

void func_15199834(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 0x26);
    }
}

void func_15199DDC(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    s32 cur;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0 || arg2 == 2 || arg2 == 0x26) {
        if (*(s32 *)p == arg1[0] || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)p) {
            *(s32 *)p = arg1[1];
            p[4] = ((u8 *)arg1)[9];
        } else if (arg1[1] == *(s32 *)p) {
            *(s32 *)p = arg1[0];
            p[4] = ((u8 *)arg1)[8];
        }
    }
}

void func_15199EF0(void *);
void func_15199E98(void *arg0) {
    func_15199EF0(arg0);
    func_15147E64(arg0);
}

void func_15199EC4(void *arg0) {
    func_15199EF0(arg0);
    func_15147E98(arg0);
}

extern s32 D_8008FC54;
extern s32 D_8008FC60;

void func_15199EF0(void *arg0) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x98);
    s8 i = v[0x39];
    u8 *t;
    if (i != -1) {
        ((void (**)(u8 *))&D_8008FC60)[i](arg0);
    }
    i = v[0x36];
    if (i != -1) {
        ((void (**)(u8 *))&D_8008FC54)[i](arg0);
    }
    t = *(u8 **)(v + 0x148);
    if (t != NULL) {
        func_1516972C(t);
    }
}

#ifdef NON_MATCHING
extern s32 (*D_8008FC64[])(u8 *); /* emitter2 check handlers (result 0 = stop) */
extern void (*D_8008FC5C[])(u8 *); /* emitter2 sound update handlers */
void func_1519C38C(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
// emitter2_path_update: entry 12 of D_8008A5A0 (`s32 (u8 *)`). Updates a path emitter: clears flag 0x10 of the
// owner's (+0x98) +0x150; returns 0 if a short path (+0x2C < 2) has flag 8 in +0x1E, or if the owner's check handler
// D_8008FC64[owner +0x48] (-1 = none) returns 0. Else moves every point from the head +0x2E back to the current
// point +0x2D (ring of +0x25 points of 0x28 bytes at +0x94: func_1519C38C with gravity owner +0x20 over
// D_800BE9A4, and +0x18 grows by owner +0x30 per frame), puts the owner's model (+0x148 -> +0x14, s16 +0x0E..+0x12)
// on the current point when the path has 2+ points, runs the sound handler D_8008FC5C[owner +0x38], clears flag 1 of
// +0x150 and copies the current point (or zero when +0x2C <= 0) to +0x54..+0x5C. Returns 1.
s32 func_15199F80(u8 *arg0) {
    u8 *owner = *(u8 **) (arg0 + 0x98);
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *pt;
    s16 *model;
    s32 i;

    owner[0x150] &= ~0x10;
    if (*(s8 *) (arg0 + 0x2C) < 2 && (*(u16 *) (arg0 + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *) (owner + 0x48);
    if (i != -1 && D_8008FC64[i](arg0) == 0) {
        return 0;
    }
    i = *(s8 *) (arg0 + 0x2E);
    while (i != *(s8 *) (arg0 + 0x2D)) {
        i--;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        pt = points + i * 0x28;
        func_1519C38C((f32 *) pt, (f32 *) (pt + 0xC), *(f32 *) (owner + 0x20), D_800BE9A4);
        *(f32 *) (pt + 0x18) += *(f32 *) (owner + 0x30) * D_800BE9A4;
    }
    if (*(u8 **) (owner + 0x148) != NULL && *(s8 *) (arg0 + 0x2C) >= 2) {
        pt = points + *(s8 *) (arg0 + 0x2D) * 0x28;
        model = *(s16 **) (*(u8 **) (owner + 0x148) + 0x14);
        model[7] = (s32) ((f32 *) pt)[0];
        model[8] = (s32) ((f32 *) pt)[1];
        model[9] = (s32) ((f32 *) pt)[2];
    }
    i = *(s8 *) (owner + 0x38);
    if (i != -1) {
        D_8008FC5C[i](arg0);
    }
    owner[0x150] &= ~1;
    if (*(s8 *) (arg0 + 0x2C) > 0) {
        pt = points + *(s8 *) (arg0 + 0x2D) * 0x28;
        *(s32 *) (arg0 + 0x54) = ((s32 *) pt)[0];
        *(s32 *) (arg0 + 0x58) = ((s32 *) pt)[1];
        *(s32 *) (arg0 + 0x5C) = ((s32 *) pt)[2];
    } else {
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199F80.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519A1A4.s")

#ifdef NON_MATCHING
void *memcpy(void *, const void *, s32);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
f32 func_15143E64(struct17 *);
f32 func_15144528(f32, f32, f32);
void func_15143794(s16, s16, f32, void *);
void func_1508B20C(f32, f32, f32, f32);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
extern s32 (*D_8008FC48[])(u8 *); /* func_1519CEB8 / func_1519CEE0 / func_1519CF08: all take the trail object only */

/* One point of a trail ring (obj +0x94, obj +0x25 entries). */
typedef struct {
    /* 0x00 */ f32 x, y, z;
    /* 0x0C */ f32 dir[3];    /* spark velocity direction */
    /* 0x18 */ f32 width;     /* spark rate weight / spread */
    /* 0x1C */ f32 len;       /* length of the segment to the newer neighbour */
    /* 0x20 */ u8 alpha;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ f32 angle;
} TrailPoint;

/* Motion block copied to the new spark +0x110 (stack +0x108, directly below the spec). */
typedef struct {
    /* 0x00 */ f32 vel0[3];
    /* 0x0C */ f32 vel1[3];
    /* 0x18 */ f32 spin;
    /* 0x1C */ f32 u1C, u20, u24;
    /* 0x28 */ s16 u28, u2A;
} TrailSparkMotion;

/* func_1513D2F0 spec (stack +0x134). */
typedef struct {
    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 flags;
    /* 0x04 */ s16 life;
    /* 0x06 */ s16 pad06;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 rgba[4];
    /* 0x14 */ f32 sizeA;
    /* 0x18 */ f32 sizeB;
    /* 0x1C */ f32 p0[3];
    /* 0x28 */ f32 p1[3];
    /* 0x34 */ f32 u34, u38, u3C, u40;
    /* 0x44 */ u8 frame;
    /* 0x45 */ u8 u45, u46, u47;
    /* 0x48 */ s32 u48;
} TrailSparkSpec;

/* Ring index before i (obj +0x25 = ring size). */
#define TRAIL_PREV(i, obj) ((i) - 1 >= 0 ? (i) - 1 : (obj)[0x25] - 1)

// trail_update: per-frame update of a ribbon trail (object handler table D_8008A624 / D_8008A5DC, returns 1).
// obj +0x94 = ring of 0x28-byte TrailPoint, obj +0x98 = state, obj +0x2C = point count, +0x2D = tail (oldest),
// +0x2E = head (next free), +0x25 = ring size; obj +0x1E bit 1: the newest end is the object position (+0x10)
// instead of the point before the head. State: +0x28 max length, +0x14C current length, +0x150 flags.
// 1. flag 4: a ray from the owner (state +0, position +0x14 raised by 48) to the newest end (func_150ACEA0) can
//    shorten the max length to the hit distance (+0x1D4 out).
// 2. Walks from the newest end to the tail: segment lengths (+0x1C) and the total; once the total passes the max
//    length the segment is cut back to fit and the tail moves up (count decremented) to that point.
// 3. Alpha (+0x20): the oldest (1 - state +0x3C) part of the length fades as state +0x140 * the remaining fraction,
//    the rest gets state +0x3A. 4. Angle: state +0x144 spins by state +0x40 per frame, each point gets it plus the
//    distance from the head * state +0x44, wrapped to -16384..16383 (func_15144528).
// 5. With 3+ points (unless state +0x150 bits 0x20 and 0x10 are both set) and the trail at full length, spark
//    credit (+0x134) grows by (+0x4C + rand * +0x50) * tail width * frame time; per whole unit one spark
//    (func_1513D2F0 kind 0x13 / 0x14, motion block at +0x110) starts at the point state +0x84 of the way from the
//    head (interpolated between the two points around it), jittered by func_15143794.
// 6. State +0x35 (if not -1) picks a D_8008FC48 handler (called with obj only: all three handlers take one
//    argument; the asm leaves a stale a1 there). 7. Flag 2: func_1508B20C at the midpoint of newest end and tail with
//    radius half the length.
s32 func_1519AF14(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x98);
    TrailPoint *pts = *(TrailPoint **)(obj + 0x94);
    f32 maxLen = *(f32 *)(st + 0x28);
    f32 *newest;
    TrailPoint *pt;
    TrailPoint *prev;
    struct17 d;
    struct17 jit;
    f32 hit;
    f32 hx, hy, hz;
    f32 acc;
    f32 cut;
    f32 seglen;
    f32 fadeLen;
    f32 fadeSpan;
    f32 fadeInv;
    f32 at;
    f32 where;
    f32 width;
    f32 spread;
    f32 sizeA;
    f32 sizeB;
    f32 speed;
    struct17 pos;
    struct17 seg;
    TrailSparkMotion mot;
    TrailSparkSpec spec;
    TrailPoint *pNew;
    TrailPoint *pOld;
    u8 *spark;
    s32 i;
    s32 found;
    s32 tail;
    s32 next;
    s32 r1;
    s8 h;

    /* 1. ray-shortened max length */
    if ((st[0x150] & 4) && (s8)obj[0x2C] >= 2) {
        u8 *owner = *(u8 **)st;
        f32 sx = *(f32 *)(owner + 0x14);
        f32 sy = *(f32 *)(owner + 0x18) + 48.0f;
        f32 sz = *(f32 *)(owner + 0x1C);
        f32 o1, o2, o3;

        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            newest = &pts[TRAIL_PREV((s8)obj[0x2E], obj)].x;
        }
        if (func_150ACEA0(sx, sy, sz, newest[0] - sx, newest[1] - sy, newest[2] - sz, NULL, NULL, &o1, &o2, &o3,
                          &hit, 0, 0, 0.0f) != 0 &&
            hit < maxLen) {
            maxLen = hit;
        }
    }

    /* 2. segment lengths, cut at the max length */
    if ((s8)obj[0x2C] >= 2) {
        i = (s8)obj[0x2E];
        *(f32 *)(st + 0x14C) = 0.0f;
        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            i = TRAIL_PREV(i, obj);
            newest = &pts[i].x;
        }
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            d.unk0 = pt->x - newest[0];
            d.unk4 = pt->y - newest[1];
            d.unk8 = pt->z - newest[2];
            pt->len = func_15143E64(&d);
            *(f32 *)(st + 0x14C) += pt->len;
            if (maxLen < *(f32 *)(st + 0x14C)) {
                seglen = pt->len;
                if (seglen != 0.0f) {
                    cut = (*(f32 *)(st + 0x14C) - maxLen) / seglen;
                    pt->x -= d.unk0 * cut;
                    pt->y -= d.unk4 * cut;
                    pt->z -= d.unk8 * cut;
                    pt->len = seglen * (1.0f - cut);
                }
                while (i != (s8)obj[0x2D]) {
                    obj[0x2D] = (s8)obj[0x2D] + 1;
                    if ((s8)obj[0x2D] == obj[0x25]) {
                        obj[0x2D] = 0;
                    }
                    obj[0x2C] = (s8)obj[0x2C] - 1;
                }
                *(f32 *)(st + 0x14C) = maxLen;
            }
            newest = &pt->x;
        } while (i != (s8)obj[0x2D]);
    }

    /* 3. alpha fade over the oldest part */
    if ((s8)obj[0x2C] >= 2) {
        fadeLen = *(f32 *)(st + 0x14C) * *(f32 *)(st + 0x3C);
        fadeSpan = *(f32 *)(st + 0x14C) - fadeLen;
        fadeInv = 1.0f / fadeSpan;
        acc = 0.0f;
        i = (s8)obj[0x2E];
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            acc += pt->len;
            if (fadeLen < acc) {
                pt->alpha = (u32)(*(f32 *)(st + 0x140) * ((fadeSpan - (acc - fadeLen)) * fadeInv));
            } else {
                pt->alpha = st[0x3A];
            }
        } while (i != (s8)obj[0x2D]);
    }

    /* 4. twist angle */
    if ((s8)obj[0x2C] >= 2) {
        *(f32 *)(st + 0x144) += *(f32 *)(st + 0x40) * D_800BE9A4;
        *(f32 *)(st + 0x144) = func_15144528(*(f32 *)(st + 0x144), 16383.0f, -16384.0f);
        acc = 0.0f;
        i = (s8)obj[0x2E];
        do {
            i = TRAIL_PREV(i, obj);
            pt = &pts[i];
            acc += pt->len;
            pt->angle = func_15144528(*(f32 *)(st + 0x144) + acc * *(f32 *)(st + 0x44), 16383.0f, -16384.0f);
        } while (i != (s8)obj[0x2D]);
    }

    /* 5. sparks */
    if ((s8)obj[0x2C] >= 3 && !((st[0x150] & 0x20) && (st[0x150] & 0x10)) && maxLen <= *(f32 *)(st + 0x14C)) {
        *(f32 *)(st + 0x134) += (*(f32 *)(st + 0x4C) + func_150ADA68() * *(f32 *)(st + 0x50)) *
                                pts[(s8)obj[0x2D]].width * D_800BE9A4;
        if (1.0f < *(f32 *)(st + 0x134)) {
            tail = (s8)obj[0x2D];
            next = tail + 1;
            if (next == obj[0x25]) {
                next = 0;
            }
            /* the point `where` (state +0x84 of the length) from the newest end. If it is never reached
               (+0x84 > 1) pos / seg stay unset, as in the asm. */
            width = 0.0f;
            acc = 0.0f;
            found = 0;
            prev = NULL;
            where = *(f32 *)(st + 0x14C) * *(f32 *)(st + 0x84);
            i = (s8)obj[0x2E];
            do {
                i = TRAIL_PREV(i, obj);
                pt = &pts[i];
                seglen = pt->len;
                acc += seglen;
                if (where <= acc) {
                    found = 1;
                    if (prev != NULL && seglen != 0.0f) {
                        at = (acc - where) / seglen;
                        pos.unk0 = pt->x + (prev->x - pt->x) * at;
                        pos.unk4 = pt->y + (prev->y - pt->y) * at;
                        pos.unk8 = pt->z + (prev->z - pt->z) * at;
                        width = pt->width + (prev->width - pt->width) * at;
                        seg.unk0 = pt->x - prev->x;
                        seg.unk4 = pt->y - prev->y;
                        seg.unk8 = pt->z - prev->z;
                    } else {
                        pos.unk0 = pt->x;
                        pos.unk4 = pt->y;
                        pos.unk8 = pt->z;
                        width = pt->width;
                        seg.unk0 = 0.0f;
                        seg.unk4 = 0.0f;
                        seg.unk8 = 0.0f;
                    }
                }
                prev = pt;
            } while (i != tail && !found);

            spec.u08 = 0;
            spec.u0C = 0;
            mot.u1C = *(f32 *)(st + 0x78);
            mot.u20 = *(f32 *)(st + 0x7C);
            mot.u24 = *(f32 *)(st + 0x8C);
            mot.u28 = *(s16 *)(st + 0x80);
            mot.u2A = *(s16 *)(st + 0x82);
            spec.flags = 0x2203;
            spec.rgba[0] = 0xFF;
            spec.u01 = 0;
            spec.rgba[1] = 0xFF;
            spec.rgba[2] = 0xFF;
            spec.rgba[3] = 0xFF;
            spec.u38 = 0.0f;
            spec.u34 = 1.0f;
            spec.u3C = 1.0f;
            spec.u40 = 6.3757176f;
            spec.u45 = 0xFF;
            spec.u46 = 0;
            spec.u47 = 7;
            spec.u48 = 0;
            pOld = &pts[tail];
            pNew = &pts[next];
            do {
                sizeA = func_150ADA68() * *(f32 *)(st + 0x60) + *(f32 *)(st + 0x58);
                sizeB = func_150ADA68() * *(f32 *)(st + 0x64) + *(f32 *)(st + 0x5C);
                speed = func_150ADA68() * *(f32 *)(st + 0x6C) + *(f32 *)(st + 0x68);
                spec.sizeA = 24.222889f * sizeA;
                spec.sizeB = 3.4404585f * sizeB;
                mot.vel0[0] = pNew->dir[0] * speed;
                mot.vel0[1] = pNew->dir[1] * speed;
                mot.vel0[2] = pNew->dir[2] * speed;
                mot.vel1[0] = pOld->dir[0] * speed;
                mot.vel1[1] = pOld->dir[1] * speed;
                mot.vel1[2] = pOld->dir[2] * speed;
                mot.spin = func_150ADA68() * *(f32 *)(st + 0x74) + *(f32 *)(st + 0x70);
                spec.kind = (func_150ADA20() & 1) ? 0x13 : 0x14;
                spec.life = (u32)func_150ADA20() % (u32)(*(s16 *)(st + 0x56) + 1) + *(s16 *)(st + 0x54);
                r1 = func_150ADA20();
                func_15143794(r1 & 0xFF, (func_150ADA20() & 0x7F) - 0x3F, width, &jit);
                spec.p0[0] = pos.unk0 + jit.unk0;
                spec.p0[1] = pos.unk4 + jit.unk4;
                spec.p0[2] = pos.unk8 + jit.unk8;
                spec.p1[0] = spec.p0[0] + seg.unk0;
                spec.p1[1] = spec.p0[1] + seg.unk4;
                spec.p1[2] = spec.p0[2] + seg.unk8;
                spec.frame = (u32)func_150ADA20() % (u32)(st[0x89] + 1) + st[0x88];
                spark = func_1513D2F0(&spec, (s32)&D_800A4AA0, 0x1F, 0x22, 0, 0x1A, (func_150ADA20() & 1) | 2, 0, 0,
                                      0x2C, obj[0xC], obj[1]);
                if (spark != NULL) {
                    memcpy(spark + 0x110, &mot, 0x2C);
                }
                *(f32 *)(st + 0x134) -= 1.0f;
            } while (1.0f < *(f32 *)(st + 0x134));
        }
    }

    /* 6. per-kind handler */
    h = (s8)st[0x35];
    if (h != -1) {
        D_8008FC48[h](obj);
    }

    /* 7. bounding sphere */
    if ((st[0x150] & 2) && (s8)obj[0x2C] >= 2) {
        if (*(u16 *)(obj + 0x1E) & 2) {
            newest = (f32 *)(obj + 0x10);
        } else {
            newest = &pts[TRAIL_PREV((s8)obj[0x2E], obj)].x;
        }
        pt = &pts[(s8)obj[0x2D]];
        hx = (pt->x + newest[0]) * 0.5f;
        hy = (pt->y + newest[1]) * 0.5f;
        hz = (pt->z + newest[2]) * 0.5f;
        func_1508B20C(hx, hy, hz, *(f32 *)(st + 0x14C) * 0.5f);
    }
    return 1;
}
#undef TRAIL_PREV
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519AF14.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519BA28.s")

void func_1519C38C(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    vertex sp4 = *(vertex *)arg1;

    arg1[1] += arg2 * arg3;
    arg0[0] += sp4.x * arg3;
    arg0[1] += sp4.y * arg3 + 0.5f * arg2 * arg3 * arg3;
    arg0[2] += sp4.z * arg3;
}

void func_1519C428(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 0;
    }
}

void func_1519C490(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 1;
    }
}

#ifdef NON_MATCHING
/* P163: D_8008FC58 is the one-entry start-sound table (FC5C / FC64 are separate tables used by func_15199F80);
   func_15199A28 (asm) stores the entry's v0 as the record's u16 voice handle (`sh $v0, 0x130($t5) = record + 0x130`), so this returns func_10010F30's handle. */
// emitter2_sound_start: starts sound 0x1AA at full volume and returns its voice handle
u16 func_1519C4FC(void) {
    return func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#else
void func_1519C4FC(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#endif

void func_1519C52C(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;
    u16 temp_a0;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(u8 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        temp_a0 = *(u16 *)(temp_v0 + 0x130);
        if (temp_a0 != 0) {
            func_1000F91C(temp_a0, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 0)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 4)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 8)), 0x1F4, 0x1388); // fakematch: (0, x) comma flips commutative operand order
        }
    }
}

void func_1519C5DC(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x130);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
void *memcpy(void *, const void *, s32);

struct225 *func_1519C60C(s32 arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    Header2 header2;
    s32 tmp;
    f32 data[8];

    tmp = arg0;
    header.unk0 = 2;
    header.unk1 = 2;
    header.unk2 = 300;
    header.unk4 = 0x22;
    data[0] = 35.0f;
    data[1] = 5.0f;
    data[2] = 110.0f;
    data[3] = 1.0f;
    data[4] = 0.0f;
    data[5] = 7.0f;
    data[6] = 0.2489f;
    data[7] = 127.0f;
    header2.unk0 = arg1[0];
    header2.unk4 = arg1[1];
    header2.unk8 = arg1[2];
    temp_v0 = func_151602C0(&header, &header2, arg2, arg3, arg4, arg5, 0xFF, 0, 0x24, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, data, sizeof(data));
        memcpy((u8 *)temp_v0 + 0x38, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

void func_1519C770(void *arg0) {
    func_1519C7C8(arg0);
    func_151617C4(arg0);
}

void func_1519C79C(void *arg0) {
    func_1519C7C8(arg0);
    func_151617E4(arg0);
}

void func_1519C7C8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(*(u8 **)(arg0 + 0x38) + 0x98);
    *(s32 *)(temp_v0 + 0x148) = 0;
}

#ifdef NON_MATCHING
s32 func_1519C7DC(u8 *arg0) {
    struct {
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
    } sp;
    f32 sp2C;
    f32 sp28;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f8;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x110;
    (*(f32 *)((u8 *)(&sp.u48) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
    temp_f0 = D_800BE9A4 * D_800BE9A4;
    (*(f32 *)((u8 *)(&sp.u48) + 4)) = (f32) (*(f32 *)((u8 *)temp_v0 + 4));
    (*(f32 *)((u8 *)(&sp.u48) + 8)) = (f32) (*(f32 *)((u8 *)temp_v0 + 8));
    (*(f32 *)((u8 *)(&sp.u3C) + 0)) = (*(f32 *)((u8 *)arg0 + 0x11C));
    (*(f32 *)((u8 *)(&sp.u3C) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x120));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x124));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x128));
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x114)) + (temp_f12 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x120)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x120)) + (temp_f12 * D_800BE9A4));
    var_v1 = D_800BE9E4;
    if (var_v1 > 0) {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
        temp_f12_2 = (*(f32 *)((u8 *)temp_v0 + 0x20));
        do {
            var_v1 -= 1;
            (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 4)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0xC)) * temp_f12_2);
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) * temp_f12_2);
            (*(f32 *)((u8 *)temp_v0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) * temp_f12_2);
        } while (var_v1 > 0);
    }
    temp_f8 = ((*(f32 *)((u8 *)temp_v0 + 0x10)) - sp.u40) * D_800BEDC8;
    sp28 = temp_f8;
    sp2C = ((*(f32 *)((u8 *)temp_v0 + 0x14)) - sp.u44) * D_800BEDC8;
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u48 * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 0)) - sp.u48) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u4C * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 4)) - sp.u4C) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u50 * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 8)) - sp.u50) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + ((sp.u3C * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 0xC)) - sp.u3C) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + ((sp.u40 * D_800BE9A4) + (0.5f * temp_f8 * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((sp.u44 * D_800BE9A4) + (0.5f * sp2C * temp_f0)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C7DC.s")
#endif
s32 func_1519CA54(u8 *arg0) {
    u8 *p;
    s32 i;
    s32 v;

    p = arg0 + 0x110;
    for (i = D_800BE9E4; i > 0; i--) {
        *(f32 *)(arg0 + 0x2C) -= *(f32 *)(arg0 + 0x2C) * *(f32 *)(p + 0x24);
        *(f32 *)(arg0 + 0x30) -= *(f32 *)(arg0 + 0x30) * *(f32 *)(p + 0x24);
    }
    if (*(s16 *)(arg0 + 0x1C) < *(s16 *)(p + 0x28)) {
        v = *(s16 *)(p + 0x2A) * *(s16 *)(arg0 + 0x1C);
        if (v < arg0[0x5C]) {
            arg0[0x5C] = v;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
s16 *func_1519CADC(u8 *arg0, s16 arg1) {
    struct {
        u8 u3F;
        f32 u40;
        s32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        u8 pad54[0x18];
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 * u84;
        s16 * u88;
        s16 * u8C;
    } sp;
    u8 *sp34;
    u8 *sp30;                                     /* compiler-managed */
    f32 sp2C;
    f32 *temp_a2;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f4;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t2;
    s16 *temp_t4;
    s16 *temp_t5;
    u8 *temp_a1;
    u8 *temp_v1;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u8C, &sp.u3F);
    sp.u88 = sp.u8C;
    if (sp.u8C != NULL) {
        if (sp.u3F != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp30 = temp_a1;
            sp34 = temp_v1;
            memcpy((*(u8 **)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(u8 **)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = func_15144B34((s32) arg1);
        temp_a2 = temp_v0;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u7C = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f4 = (*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        sp.u80 = temp_f4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x34));
        temp_f12 = temp_f2 + (sp.u78 * temp_f0);
        temp_f14 = (*(f32 *)((u8 *)arg0 + 0x38)) + (sp.u7C * temp_f0);
        sp.u78 = temp_f12 - temp_f2;
        temp_f16 = (*(f32 *)((u8 *)arg0 + 0x3C)) + (temp_f4 * temp_f0);
        sp.u7C = temp_f14 - (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u74 = temp_f16;
        sp.u70 = temp_f14;
        sp.u6C = temp_f12;
        sp.u84 = temp_v0;
        sp.u80 = temp_f16 - (*(f32 *)((u8 *)arg0 + 0x3C));
        func_15145548(temp_f12, temp_f14, arg0 + 0x34, &sp.u78, temp_a2, &sp.u48, &sp.u44);
        temp_f0_2 = sp.u48 - (*(f32 *)((u8 *)sp.u84 + 0));
        temp_f2_2 = sp.u4C - (*(f32 *)((u8 *)sp.u84 + 4));
        temp_f12_2 = sp.u50 - (*(f32 *)((u8 *)sp.u84 + 8));
        temp_f18 = (sp.u7C * temp_f12_2) - (temp_f2_2 * sp.u80);
        temp_f16_2 = (sp.u80 * temp_f0_2) - (temp_f12_2 * sp.u78);
        sp30 = (u8 *)(s32)temp_f16_2;
        temp_f8 = (sp.u78 * temp_f2_2) - (temp_f0_2 * sp.u7C);
        sp2C = temp_f8;
        temp_f14_2 = (temp_f18 * temp_f18) + (temp_f16_2 * temp_f16_2) + (temp_f8 * temp_f8);
        sp.u40 = temp_f14_2;
        if (temp_f14_2 != 0.0f) {
            temp_f2_3 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(sp.u40);
            var_f12 = temp_f18 * temp_f2_3;
            var_f14 = (s32)sp30 * (s32)temp_f2_3;
            var_f16 = temp_f8 * temp_f2_3;
        } else {
            var_f16 = 0.0f;
            var_f12 = 0.0f;
            var_f14 = 0.0f;
        }
        (*(s16 *)((u8 *)sp.u8C + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t2 = sp.u8C + 0x10;
        sp.u8C = temp_t2;
        *temp_t2 = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t4 = sp.u8C + 0x10;
        sp.u8C = temp_t4;
        *temp_t4 = (s16) (s32) (sp.u6C - var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) (sp.u70 - var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.u74 - var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t5 = sp.u8C + 0x10;
        sp.u8C = temp_t5;
        *temp_t5 = (s16) (s32) (sp.u6C + var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) (sp.u70 + var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.u74 + var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        return sp.u88;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CADC.s")
#endif
s32 func_1519CE80(u8 *arg0)
{
  u8 *new_var;
  u16 temp_a1;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x98));
  new_var = (u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)));
  ;
  if ((*((s32 *) (((u8 *) temp_v0) + 0x158))) != (*((u16 *) (new_var + 0x84))))
  {
    if ((*((s32 *) (((u8 *) temp_v0) + 0x15C))) != (*((u16 *) (new_var + 0x84))))
    {
      return 0;
      return 1;
    }
  }
  return 1;
}

s32 func_1519CEB8(s32 arg0) {
    func_1519D320(arg0, 0.25f, 0x1C);
    return 0;
}

s32 func_1519CEE0(s32 arg0) {
    func_1519D320(arg0, 0.5f, 0x1D);
    return 0;
}

s32 func_1519CF08(s32 arg0) {
    func_1519D320(arg0, 0.2f, 0x1D);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CF34.s")

void func_1519D2D4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) || (arg0[0x2C] != temp_v0[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

#ifdef NON_MATCHING
// path_trail_spawn_effects: spawns effect `kind` (func_1505D1C4) at even spacing along the path of `arg0` (needs a
// count +0x2C >= 2): walks back from the head point +0x2E to the current point +0x2D (ring of +0x25 points of 0x28
// bytes at +0x94, +0x1C = segment length), starting from the position at +0x10; whenever the walked length reaches
// the next mark (0, then every owner +0x14C * step), one effect is spawned on that segment, interpolated back towards
// the previous point, for the owner's object (**(arg0 + 0x98): its D_800CC2D0 index and u16 +0x76).
void func_1519D320(s32 arg0, f32 step, s32 kind) {
    u8 *self = (u8 *) arg0;
    u8 *owner = *(u8 **) (self + 0x98);
    u8 *points = *(u8 **) (self + 0x94);
    f32 *prev = (f32 *) (self + 0x10);
    f32 *pt;
    u8 *obj;
    f32 spacing;
    f32 walked;
    f32 mark;
    f32 len;
    f32 t;
    s32 i;

    if (*(s8 *) (self + 0x2C) < 2) {
        return;
    }
    walked = 0.0f;
    mark = 0.0f;
    spacing = *(f32 *) (owner + 0x14C) * step;
    i = *(s8 *) (self + 0x2E);
    do {
        i--;
        if (i < 0) {
            i = self[0x25] - 1;
        }
        pt = (f32 *) (points + i * 0x28);
        len = pt[7];
        walked += len;
        if (mark <= walked) {
            obj = *(u8 **) owner;
            t = (walked - mark) / len;
            func_1505D1C4(pt[0] + (prev[0] - pt[0]) * t, pt[1] + (prev[1] - pt[1]) * t, pt[2] + (prev[2] - pt[2]) * t,
                          kind, (s32) (obj - (u8 *) D_800CC2D0) / 0x32C, *(u16 *) (obj + 0x76), 0, 0);
            mark += spacing;
        }
        prev = pt;
    } while (i != *(s8 *) (self + 0x2D));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519D320.s")
#endif
