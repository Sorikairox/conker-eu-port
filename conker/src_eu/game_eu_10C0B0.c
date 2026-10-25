#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150DE8A0(s32 arg0) {
}

#ifdef NON_MATCHING
extern u8 D_80088CF0[8];
extern u8 D_80088CF8[8];
s32 func_150A3794(u8 *, s32, s32, s32);
u8 *func_151149AC(u8);
void func_150A2D44(s32, s32);

// trigger_zones_check: hit callback (D_800E0D64, set in game_3DC30) for the point (x, y, z): for each of
// the 8 zones D_80088CF0 (D_800D34B8 records of 0x34 bytes) that contains it (func_150A3794), the matching
// D_80088CF8 object id gets state 3 in its +0x73 low bits (func_151149AC), or the zone itself is triggered
// (func_150A2D44(zone, 1)) when the id is 0. Returns 0 (the asm leaves the last helper's v0; the caller
// ignores it).
s32 func_150DE8AC(s32 x, s32 y, s32 z) {
    u8 *obj;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (func_150A3794(D_800D34B8 + D_80088CF0[i] * 0x34, x, y, z) != 0) {
            if (D_80088CF8[i] != 0) {
                obj = func_151149AC(D_80088CF8[i]);
                obj[0x73] = (obj[0x73] & ~3) | 3;
            } else {
                func_150A2D44(D_80088CF0[i], 1);
            }
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE8AC.s")
#endif

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32 *, s32, s32);
void func_1510DDF4(s32, s32, s32, s32, s32);
extern s32 D_800905B4;

void func_150DE9D8(u8 *arg0) {
    struct {
        s32 u54;
    } sp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    s32 *var_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s2;

    if (((*(u8 *)((u8 *)arg0 + 0x73)) & 3) == 3) {
        temp_f12 = (f32) D_800BE9E4;
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + ((*(f32 *)((u8 *)arg0 + 0x60)) * temp_f12));
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
        if (temp_f0 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 + 360.0f);
        } else if (temp_f0 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x64)) * temp_f12));
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 4));
        if (temp_f0_2 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 + 360.0f);
        } else if (temp_f0_2 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_2 - 360.0f);
        }
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x68)) * temp_f12));
        temp_f0_3 = (*(f32 *)((u8 *)arg0 + 8));
        if (temp_f0_3 < 0.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 + 360.0f);
        } else if (temp_f0_3 >= 360.0f) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0_3 - 360.0f);
        }
        (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x5C)) - ((*(s32 *)((u8 *)arg0 + 0x3C)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x10)) + ((*(s16 *)((u8 *)arg0 + 0x5A)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) + ((*(s16 *)((u8 *)arg0 + 0x5C)) * D_800BE9E4));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x14)) + ((*(s16 *)((u8 *)arg0 + 0x5E)) * D_800BE9E4));
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x8A)) - D_800BE9E4;
        if (temp_v0 > 0) {
            (*(u8 *)((u8 *)arg0 + 0x8A)) = (u8) temp_v0;
        } else {
            (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
        }
    }
    if (((*(u16 *)((u8 *)arg0 + 0x54)) & 0xFFFF7FFF) == 0xC) {
        var_s2 = 4;
        var_s1 = (s32 *) ((u8 *) &D_800905B4 + (*(s32 *)((u8 *)arg0 + 0x7C)) * 8);
        var_s0 = 5;
        do {
            temp_v0_2 = func_1510D66C(*var_s1, &sp.u54, 3, 0);
            func_1510DDF4(arg0, temp_v0_2, (sp.u54 + temp_v0_2) - 0x200, var_s2, var_s0);
            var_s0 += 2;
            var_s1++;
            var_s2 += 2;
        } while (var_s0 != 9);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DE9D8.s")
#endif
#ifdef NON_MATCHING
void func_150DEC58(u8 *arg0) {
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x7C)) >> 3) & 0xFF) * 10.2f) + 1130.0f);
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) (func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x80)) >> 3) & 0xFF) * 1.1f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) (func_15048A40(((s32) (*(s32 *)((u8 *)arg0 + 0x84)) >> 3) & 0xFF) * 1.1f);
    (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x7C)) + (D_800BE9E4 * 0xC));
    (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x80)) + (D_800BE9E4 * 0x10));
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) + (D_800BE9E4 * 0x18));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DEC58.s")
#endif
#ifdef NON_MATCHING
void func_1514470C(u8 *, f32 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 memcpy(u8 *, void *, s32);

// beam_link_fire: timer handler of a link effect p (timer s16 at p+0x28, two objects at p+0x2C / p+0x30). When the
// timer runs out (minus D_800BE9E4) it fires a bolt (func_1513D2F0 template, kind 0xBE or 0xBF at random, size 706,
// at the first object's position) towards the second object at speed 25..55 (x0.18 for kind 0xBF); the bolt's +0x110
// gets {velocity, travel time = distance / speed, the flat side vector (-z, 0, x) and flat direction (x, 0, z) of the
// normalised horizontal offset}. The timer restarts at 200..400.
void func_150DED40(u8 *p) {
    struct {
        u8 kind;            /* 0x00 */
        u8 u1;              /* 0x01 */
        s16 u2;             /* 0x02 */
        s16 u4;             /* 0x04 */
        u8 pad6[2];
        s32 u8;             /* 0x08 */
        s32 uC;             /* 0x0C */
        u8 colour[4];       /* 0x10 */
        f32 size[2];        /* 0x14 */
        f32 pos[3];         /* 0x1C */
        f32 u28[3];         /* 0x28 */
        f32 scale[3];       /* 0x34 */
        s32 mode;           /* 0x40 */
        u8 u44[4];          /* 0x44 */
        s32 u48;            /* 0x48 */
        u8 u4C;             /* 0x4C */
        u8 pad4D[3];
        s32 u50;            /* 0x50 */
        s16 u54;            /* 0x54 */
        s16 u56;            /* 0x56 */
    } t;
    struct {
        f32 vel[3];         /* 0x00 */
        f32 time;           /* 0x0C */
        f32 side[3];        /* 0x10 */
        f32 flat[3];        /* 0x1C */
    } rec;
    s32 kinds[2];
    f32 to[3];
    f32 d[3];
    f32 len;
    f32 unused;
    f32 speed;
    f32 spd;
    s16 *timer;
    u8 *e;

    *(s16 *) (p + 0x28) -= D_800BE9E4;
    if (*(s16 *) (p + 0x28) >= 0) {
        return;
    }
    kinds[0] = 0xBE;
    kinds[1] = 0xBF;
    t.kind = kinds[func_150ADA20() & 1];
    timer = (s16 *) (p + 0x28);
    func_1514470C(*(u8 **) (p + 0x2C), t.pos);
    func_1514470C(*(u8 **) (p + 0x30), to);
    d[0] = to[0] - t.pos[0];
    d[1] = to[1] - t.pos[1];
    d[2] = to[2] - t.pos[2];
    func_15145128(d, rec.vel, &len, &unused);
    speed = func_150ADA68() * 30.0f + 25.0f;
    spd = speed;
    if (t.kind == 0xBF) {
        spd = speed * 0.18f;
    }
    rec.vel[0] *= spd;
    rec.vel[1] *= spd;
    rec.vel[2] *= spd;
    rec.time = len / spd;
    rec.flat[0] = d[0];
    rec.flat[1] = 0.0f;
    rec.flat[2] = d[2];
    func_15145128(rec.flat, rec.flat, NULL, NULL);
    rec.side[0] = -rec.flat[2];
    rec.side[1] = 0.0f;
    rec.side[2] = rec.flat[0];
    t.u28[0] = ((f32 *) D_800A5860)[0];
    t.u28[1] = ((f32 *) D_800A5860)[1];
    t.u28[2] = ((f32 *) D_800A5860)[2];
    t.u1 = 0;
    t.u2 = 0x3B03;
    t.u4 = 300;
    t.u8 = 0;
    t.uC = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    func_150ADA68(); /* result unused */
    t.size[1] = 706.0f;
    t.size[0] = 706.0f;
    t.u28[0] = ((f32 *) D_800A5860)[0];
    t.u28[1] = ((f32 *) D_800A5860)[1];
    t.u28[2] = ((f32 *) D_800A5860)[2];
    t.mode = 0x65C0000;
    t.u44[0] = 0xFF;
    t.u44[1] = 0xFF;
    t.u44[2] = 0;
    t.u44[3] = 7;
    t.u48 = 0;
    t.u4C = 0xFF;
    t.u50 = 0;
    t.u54 = 1;
    t.u56 = 0xFF;
    t.scale[0] = 1.0f;
    t.scale[1] = 1.0f;
    t.scale[2] = 1.0f;
    e = func_1513D2F0(&t, (s32) &D_800A4AA0, 0x28, 0, 0, 0x26, 0, 3, 0xFF, 0x28, p[0xC], p[1]);
    if (e != NULL) {
        memcpy(e + 0x110, &rec, 0x28);
    }
    *timer = (u32) func_150ADA20() % 201 + 200;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10C0B0/func_150DED40.s")
#endif

s32 func_150DF04C(u8 *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x34)) += ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x38)) += ((*(f32 *)((u8 *)arg0 + 0x114)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x3C)) += ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4);
    (*(f32 *)((u8 *)arg0 + 0x11C)) -= D_800BE9A4;
    if ((*(f32 *)((u8 *)arg0 + 0x11C)) < 0.0f) {
        return 0;
    }
    return 1;
}

s32 func_15140410(s32, s32, s32, s16);
s32 func_150DF0D8(s32 arg0, s16 arg1) {
    if (D_800DBFF0[D_80082FA0].unk388 < 5.0f) {
        return 0;
    }
    return func_15140410(arg0, arg0 + 0x120, arg0 + 0x12C, arg1);
}

void func_150DF1A8(u8 arg0, s32 arg1);

void func_150DF160(s32 arg0) {
    u8 i;

    for (i = 0; i < 4; i++) {
        func_150DF1A8(i, 1);
    }
}

extern u8 D_800A10DB[];
extern u8 D_800A10FB[];
void func_150DF1A8(u8 arg0, s32 arg1) {
    s32 i = arg0 * 4;
    func_151616D0(D_800A10DB[i], 0x22, 0);
    func_151417C4(D_800A10FB[i], 0x22);
}
