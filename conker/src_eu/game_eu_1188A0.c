#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15134DAC(void *, s32, u8 *, s16);

float sqrtf(float);
#pragma intrinsic(sqrtf)
typedef struct { f32 x, z; } V2s99;
typedef struct {
    f32 p0[4];
    f32 d[4];
    f32 u20;
    f32 u24;
    f32 rate;
    f32 rrate;
    f32 acc;
    f32 min;
    f32 range;
    u8 u3C;
    u8 u3D;
    u8 u3E;
    u8 u3F;
} P_EB090;
extern f32 D_800BE9A4;
void func_150EB090(u8 *arg0) {
    P_EB090 *p;
    struct {
        u8 u0;
        u8 u1;
        s16 u2;
        u8 u4;
        struct {
            V2s99 pos;
            f32 dx;
            f32 dz;
            f32 uCC;
            f32 uD0;
            f32 uD4;
            f32 uD8;
            u8 padDC[0x14];
            s32 uF0;
            u8 uF4;
            u8 uF5;
            s32 uF8;
        } t;
    } h;
    f32 r;
    V2s99 b;
    V2s99 a;
    f32 f;
    f32 len;
    f32 inv;
    Header2 h2;
    struct225 *obj;
    f32 g;

    p = (P_EB090 *)(arg0 + 0x28);
    p->acc += (p->rate + func_150ADA68() * p->rrate) * D_800BE9A4;
    if (p->acc > 1.0f) {
        h.t.uF0 = 0;
        h.t.uF4 = 0;
        h.t.uF5 = 0;
        h.t.uF8 = 0;
        h.t.uD8 = -10000.0f;
        h.t.uCC = p->u20;
        h.t.uD0 = p->u24;
        h.u0 = 2;
        h.u1 = 0x13;
        h.u2 = 300;
        h.u4 = 0;
        do {
            r = func_150ADA68() * p->range + p->min;
            if (r != 0.0f) {
                f = func_150ADA68();
                a.x = p->p0[0] + p->d[0] * f;
                a.z = p->p0[1] + p->d[1] * f;
                g = func_150ADA68();
                b.x = p->p0[2] + p->d[2] * g;
                b.z = p->p0[3] + p->d[3] * g;
                h.t.dx = b.x - a.x;
                h.t.dz = b.z - a.z;
                len = sqrtf(h.t.dx * h.t.dx + h.t.dz * h.t.dz);
                if (len != 0.0f) {
                    inv = 1.0f / len;
                    h.t.dx *= inv;
                    h.t.dz *= inv;
                    if (func_150ADA20() & 1) {
                        h.t.pos = a;
                    } else {
                        h.t.pos = b;
                        h.t.dx = -h.t.dx;
                        h.t.dz = -h.t.dz;
                    }
                    h.t.dx *= r;
                    h.t.dz *= r;
                    h.t.uD4 = len / r;
                    h2.unk0 = h.t.pos.x;
                    h2.unk4 = p->u20;
                    h2.unk8 = h.t.pos.z;
                    obj = func_151602C0((Header *)&h, &h2, p->u3F, p->u3C, p->u3D, p->u3E, 0xFF, 0, 0x40, arg0[0xC], arg0[1]);
                    if (obj != NULL) {
                        memcpy((u8 *)obj + 0x18, &h.t, 0x40);
                    }
                }
            }
            p->acc -= 1.0f;
        } while (p->acc > 1.0f);
    }
}

#ifdef NON_MATCHING
s32 func_15046F70(f32 *, s32, f32, s32 *);

/* drifting_sprite_update: moves an effect over the ground: x +0x18 / z +0x1C advance by the velocities +0x20 / +0x24
 * times the frame time D_800BE9A4 and go to the sprite (+0x14) s16 x / z (+0xE / +0x12); the sprite's s16 y (+0x10)
 * is the ground height func_15046F70 finds at (x, +0x28, z) (range +0x2C, result in +0x34), or +0x28 when there is
 * none. The lifetime +0x30 counts down by the frame time; returns 0 once it is <= 0 (done), else 1. Table word
 * 0x8008B4AC (dispatcher not identified; neighbours func_15190940 / func_150F2B20 take one u8 *). */
s32 func_150EB3A4(u8 *o) {
    f32 pt[3];

    *(f32 *) (o + 0x18) += *(f32 *) (o + 0x20) * D_800BE9A4;
    *(f32 *) (o + 0x1C) += *(f32 *) (o + 0x24) * D_800BE9A4;
    pt[0] = *(f32 *) (o + 0x18);
    pt[1] = *(f32 *) (o + 0x28);
    pt[2] = *(f32 *) (o + 0x1C);
    *(s16 *) (*(u8 **) (o + 0x14) + 0xE) = (s32) *(f32 *) (o + 0x18);
    *(s16 *) (*(u8 **) (o + 0x14) + 0x12) = (s32) *(f32 *) (o + 0x1C);
    if (func_15046F70(pt, 0, *(f32 *) (o + 0x2C), (s32 *) (o + 0x34)) != 0) {
        *(s16 *) (*(u8 **) (o + 0x14) + 0x10) = (s32) *(f32 *) (o + 0x34);
    } else {
        *(s16 *) (*(u8 **) (o + 0x14) + 0x10) = (s32) *(f32 *) (o + 0x28);
    }
    *(f32 *) (o + 0x30) -= D_800BE9A4;
    if (*(f32 *) (o + 0x30) <= 0.0f) {
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1188A0/func_150EB3A4.s")
#endif
