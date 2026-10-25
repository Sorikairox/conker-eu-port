#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* func_150C4620 records (stack images; pad bytes stay unset like the asm's) */
typedef struct {
    u8 *obj;        /* 0x00 */
    u8 room;        /* 0x04 obj +0x3B */
    u8 pad5[3];
    f32 u8;         /* 0x08 */
    void *glow;     /* 0x0C func_151307F0 result */
    f32 u10;        /* 0x10 */
    s16 u14;        /* 0x14 -1, 0x54 for a type 0x34 owner */
    u8 u16;         /* 0x16 */
    u8 pad17;
    s32 u18;        /* 0x18 */
} Link4620;         /* 0x1C, copied to the new object +0x28 */

typedef struct {
    u8 u0;          /* 0x00 */
    u8 u1;          /* 0x01 */
    u8 u2;          /* 0x02 5..10 */
    u8 u3;          /* 0x03 5..10 */
    f32 radius;     /* 0x04 700 */
    f32 u8;         /* 0x08 */
    f32 uC;         /* 0x0C */
} Tail4620;         /* 0x10, copied to the glow +0xA8 */

typedef struct {
    s32 u0;         /* 0x00 0x200005 */
    s32 u4;         /* 0x04 */
    s16 u8;         /* 0x08 0x2203 */
    s16 uA;         /* 0x0A 0x12C */
    s32 uC;         /* 0x0C */
    s32 u10;        /* 0x10 */
    u8 rgba[4];     /* 0x14 */
    u8 rgba2[4];    /* 0x18 */
    u8 u1C;         /* 0x1C */
    u8 colour;      /* 0x1D D_800A0710[rand & 3] */
    s16 u1E;        /* 0x1E */
    s16 u20;        /* 0x20 */
    s16 u22;        /* 0x22 */
    f32 u24;        /* 0x24 */
    f32 u28;        /* 0x28 */
    f32 u2C;        /* 0x2C */
    f32 pos[3];     /* 0x30 D_800A5860 */
    f32 pos2[3];    /* 0x3C */
    f32 pos3[3];    /* 0x48 */
    f32 u54;        /* 0x54 */
    s32 flags;      /* 0x58 */
    s32 u5C;        /* 0x5C */
    u8 u60;         /* 0x60 */
    u8 u61;         /* 0x61 */
    u8 u62;         /* 0x62 */
    s8 u63;         /* 0x63 */
    s8 u64;         /* 0x64 */
    u8 u65;         /* 0x65 */
    u8 u66;         /* 0x66 */
    u8 pad67;
    s16 u68;        /* 0x68 */
    u8 pad6A[2];
    f32 u6C;        /* 0x6C D_800A0784 */
} Glow4620;         /* func_151307F0 request */

typedef struct {
    f32 v[3];
} Vec4620;

extern u32 D_800A0710[4];
s32 memcpy(void *, void *, s32);
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
#endif

#ifdef NON_MATCHING
// object_glow_spawn: spawns a type `kind` object (0x12C when kind is -1; func_15149130) linked to obj (record at +0x28:
// obj, room, the glow at +0xC; field +0x14 = 0x54 / +0x16 = 1 for a type 0x34 owner, else -1 / 0), then a glow
// (func_151307F0 type 1, radius 700, a random colour of D_800A0710, random flag bits 0x40 / 0x80) whose +0xA8 tail
// gets two random bytes, two counts 5..10 and two scales (0.2 + [0, 0.25)) * 700.
void func_150C4620(u8 *obj, s16 kind, u8 flag, s32 arg3) {
    Link4620 link;
    Tail4620 tail;
    Glow4620 g;
    u8 *rec;
    Link4620 *l;
    u8 *e;
    s32 lo;
    s32 hi;

    link.obj = obj;
    link.u8 = 0.0f;
    link.glow = NULL;
    link.u10 = 0.0f;
    link.u14 = -1;
    link.u16 = 0;
    link.u18 = 0;
    link.room = obj[0x3B];
    if (obj[4] == 0x34) {
        link.u14 = 0x54;
        link.u16 = 1;
    }
    rec = (u8 *) func_15149130(kind == -1 ? 0x12C : kind, -1, 0x53, -1, kind != -1, 0x40, (struct37 *) 0x1C, flag, arg3);
    if (rec == NULL) {
        return;
    }
    l = (Link4620 *) (rec + 0x28);
    memcpy(l, &link, 0x1C);
    tail.u0 = func_150ADA20();
    tail.u1 = func_150ADA20();
    g.u2C = 700.0f;
    g.u28 = 700.0f;
    tail.radius = 700.0f;
    tail.u2 = (u32) func_150ADA20() % 6 + 5;
    tail.u3 = (u32) func_150ADA20() % 6 + 5;
    tail.u8 = (func_150ADA68() * 0.25f + 0.2f) * tail.radius;   /* D_800A077C */
    tail.uC = (func_150ADA68() * 0.25f + 0.2f) * tail.radius;   /* D_800A0780 */
    g.colour = D_800A0710[func_150ADA20() & 3];
    g.u8 = 0x2203;
    g.u0 = 0x200005;
    g.u4 = 0;
    g.uC = 0;
    g.u10 = 0;
    g.rgba[0] = 0;
    g.rgba[1] = 0;
    g.rgba[2] = 0;
    g.rgba[3] = 0xFF;
    g.rgba2[0] = 0;
    g.rgba2[1] = 0;
    g.rgba2[2] = 0;
    g.rgba2[3] = 0xFF;
    g.u1C = 0xFF;
    *(Vec4620 *) g.pos = *(Vec4620 *) D_800A5860;
    *(Vec4620 *) g.pos2 = *(Vec4620 *) D_800A5860;
    *(Vec4620 *) g.pos3 = *(Vec4620 *) D_800A5860;
    g.u22 = 1;
    g.u54 = 0.0f;
    g.u24 = 1.0f;
    lo = (func_150ADA20() & 1) ? 0x40 : 0;
    hi = (func_150ADA20() & 1) ? 0x80 : 0;
    g.flags = hi | lo | 0xC000;
    g.uA = 0x12C;
    g.u6C = 10000.0f;   /* D_800A0784 */
    g.u1E = 1;
    g.u20 = 0xFF;
    g.u60 = 6;
    g.u61 = 8;
    g.u64 = -1;
    g.u62 = 0x26;
    g.u63 = -1;
    g.u65 = 0;
    g.u5C = 0;
    g.u66 = 0xFF;
    g.u68 = 0;
    e = (u8 *) func_151307F0((s32) &g, 1, 0, 0x10, flag, arg3);
    l->glow = e;
    if (e != NULL) {
        memcpy(e + 0xA8, &tail, 0x10);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F1E30/func_150C4620.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F1E30/func_150C49A4.s")

void func_150C4FD8(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0x34) != 0) { func_1516972C(*(struct102 **)(p + 0x34)); } }

void func_150C5008(struct260 *arg0) {
    func_150C4FD8(arg0);
    func_1514933C(arg0);
}

void func_150C5034(struct260 *arg0) {
    func_150C4FD8(arg0);
    func_15149368(arg0);
}

void func_150C5060(u8 *arg0, s32 arg1, u8 arg2) {
    u8 **q = &arg0; // fakematch: address-taken arg0 forces the home-slot reload (shape C)
    u8 *p;
    if (arg2 == 0x55) {
        p = *q + 0x28; p[0x16] = p[0x16] & 0xFFFD;
    } else if (arg2 == 0x56) {
        p = *q + 0x28; p[0x16] = p[0x16] | 2;
    } else {
        p = *q + 0x28;
        func_15149514(arg1, arg2, (s32)p, (s32)(p + 4), (s32)*q);
    }
}
