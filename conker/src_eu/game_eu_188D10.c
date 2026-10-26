#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 memcpy(s32, f32 *, s32);
s32 func_15046C6C(f32 *, s32, f32, f32 *);

/* func_15046C6C ground probe: start position, hit height in/out (+0xC) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 hit;
    /* 0x10 */ u8 pad10[0x14];
    /* 0x24 */ s32 u24;
    /* 0x28 */ u8 u28;
    /* 0x29 */ u8 u29;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ s32 u2C;
} Probe1515B500;

// character_dust_drop_spawn: one call in 16 (random_int() & 0xF == 0) spawns a falling dust object near character
// idx (D_800DBFF0 entries of 0x9A0 bytes: position +0x2F8, yaw +0x380). The spot is 107..2010 units away at the yaw
// (in 256ths of a turn, 256 / 360 per degree) +-20; it needs ground under it: a probe from y 19500 down to the
// character's y gives the ground height, a second probe from the character's y down 250 more gives the start height
// (else y - 250). The func_151491F4 object (5..65, -1, 0xC, 1, 7, 0x18 bytes, 0xFF, 0) gets the record
// {x, start y, z, 195 * 0.001, 0, ground y} at +0x28.
void func_1515B500(s16 idx) {
    Probe1515B500 q2;
    Probe1515B500 q;
    s16 angle;
    f32 rec[6]; /* x, y, z, speed, 0, ground */
    u8 ok;
    f32 dist;
    f32 c;
    f32 s;
    f32 *pos;
    s32 yaw;
    f32 y0;
    struct260 *obj;

    if (random_int() & 0xF) {
        return;
    }
    ok = 1;
    pos = (f32 *) ((u8 *) D_800DBFF0 + idx * 0x9A0 + 0x2F8);
    yaw = *(f32 *) ((u8 *) D_800DBFF0 + idx * 0x9A0 + 0x380) * 0.7111111f;
    angle = (u32) random_int() % 41 + yaw - 20;
    dist = random_float() * 1903.0f + 107.0f;
    c = angle_byte_cos((u8) angle);
    s = angle_byte_cos((u8) (angle - 0x40));
    rec[0] = pos[0] - dist * s;
    rec[2] = pos[2] - dist * c;
    q.pos[0] = rec[0];
    q.u24 = 0;
    q.u28 = 0;
    q.u29 = 0;
    q.u2C = 0;
    q.pos[1] = 19500.0f;
    q.pos[2] = rec[2];
    q.hit = -10000.0f;
    if (func_15046C6C(q.pos, 0, pos[1], &q.hit) != 0) {
        rec[5] = q.hit;
    } else {
        ok = 0;
    }
    if (ok) {
        y0 = pos[1] + -250.0f;
        q2.u2C = 0;
        q2.u29 = 0;
        q2.u28 = 0;
        q2.u24 = 0;
        q2.hit = -10000.0f;
        q2.pos[0] = rec[0];
        q2.pos[1] = pos[1];
        q2.pos[2] = rec[2];
        if (func_15046C6C(q2.pos, 0, y0, &q2.hit) != 0) {
            rec[1] = q2.hit;
        } else {
            rec[1] = y0;
        }
    }
    random_float(); /* result unused */
    rec[4] = 0.0f;
    rec[3] = 195.0f * 0.001f;
    if (!ok) {
        return;
    }
    obj = func_151491F4((s16) ((u32) random_int() % 61 + 5), -1, 0xC, 1, 7, 0x18, 0xFF, 0);
    if (obj != NULL) {
        memcpy((s32) obj + 0x28, rec, 0x18);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B500.s")
#endif

#ifdef NON_MATCHING
s32 memcpy(s32, f32 *, s32);

void func_1515B78C(u8 *arg0) {
    struct {
        f32 u6C;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
        s32 u98;
        s16 u9C;
        s16 u9E;
        s32 uA0;
        s32 uA4;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        u8 padC8[0x8];
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        u8 padF0[0x4];
        s8 uF4;
        s8 uF5;
        s8 uF6;
        s8 uF7;
    } sp;
    f32 temp_f2;
    s32 temp_v0;
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x34)) * D_800BE9A4));
    temp_s0 = arg0 + 0x28;
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        sp.uB1 = 0x2F;
        sp.u9C = 0xC01;
        sp.u94 = 0x200005;
        sp.u98 = 0;
        sp.uAE = 0;
        sp.uAD = 0;
        sp.uAC = 0;
        sp.uAB = 0;
        sp.uAA = 0;
        sp.uA9 = 0;
        sp.uA8 = 0;
        sp.uA4 = 0;
        sp.uA0 = 0;
        sp.uB0 = 0xFF;
        sp.uB6 = 0;
        sp.uB8 = 0.0f;
        sp.uEC = 0x3207;
        sp.uF4 = 5;
        sp.uF5 = 5;
        sp.uF6 = 4;
        sp.uF7 = -1;
        (*(s32 *)((u8 *)(&sp.uC4) + 0)) = (s32) (*(s32 *)((u8 *)temp_s0 + 0));
        (*(s32 *)((u8 *)(&sp.uC4) + 4)) = (s32) (*(s32 *)((u8 *)temp_s0 + 4));
        (*(s32 *)((u8 *)(&sp.uC4) + 8)) = (s32) (*(s32 *)((u8 *)temp_s0 + 8));
        sp.uD0 = 0.0f;
        sp.uD4 = 0.0f;
        sp.uD8 = 0.0f;
        sp.uB2 = 0x32;
        sp.uB4 = 5;
        sp.u70 = 0;
        sp.u71 = 0;
        sp.u84 = 0;
        sp.u85 = 0;
        sp.uDC = 0.0f;
        sp.uE4 = 0.0f;
        sp.u7C = 1.2f;
        sp.u80 = 0.8333333f;
        sp.u90 = (*(f32 *)((u8 *)temp_s0 + 0x14));
        if (random_int() & 1) {
            sp.uEC |= 0x40;
        }
        if (random_int() & 1) {
            sp.uEC |= 0x80;
        }
        do {
            sp.uE0 = random_float() * 12.0f * 0.1f;
            sp.u9E = (random_int() % 152U) + 0x96;
            sp.uAF = (random_int() % 151U) + 0x37;
            temp_f2 = (random_float() * 200.0f) + 100.0f;
            sp.uBC = temp_f2;
            sp.u6C = temp_f2;
            sp.uC0 = temp_f2;
            sp.u72 = (random_int() % 5U) + 4;
            sp.u73 = (random_int() % 5U) + 4;
            sp.u74 = ((random_float() * 0.25f) + 0.15f) * sp.u6C;
            sp.u78 = ((random_float() * 0.25f) + 0.15f) * sp.u6C;
            sp.u86 = (random_int() & 3) + 2;
            sp.u87 = (random_int() & 3) + 2;
            sp.u88 = ((random_float() * 0.07f) + 0.06f) * sp.u6C;
            sp.u8C = ((random_float() * 0.07f) + 0.06f) * sp.u6C;
            sp.uE8 = ((random_float() * 1005.0f) + 600.0f) * 0.001f;
            temp_v0 = func_1513092C(&sp.u94, 2, 0x28);
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u6C, 0x28);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515B78C.s")
#endif
void func_1515BB64(s16 arg0) {
    s16 sp1C[2];

    sp1C[0] = arg0;
    func_15155C9C((f32 *)sp1C, 0xB);
}

void func_1515BB9C(u8 *arg0, s16 *arg1, u8 arg2) {
    if (arg2 == 0xB) {
        if (*(s16 *)(arg0 + 0x70) == *arg1) {
            node_destroy((struct102 *)arg0);
        }
    }
}

#ifdef NON_MATCHING
u8 impact_current_kind(void);
s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);
extern u8 (*D_800900A4[])(void);

// smoke_cloud_burst: spawns 10 drifting smoke sprites (func_151559FC list 2, 0x18 / 0xFF / 1) tagged with id (the
// sprite's +0x70 gets the 0x18-byte block {id, speed (105..210) * 0.001, spin 0..3008 * 0.001, size, size 2
// ((94..395) * 0.01), ...}; size = (489..2068) * 0.01. Each starts at (-100..100, -100..48), with the texture byte of
// the current kind's D_800900A4 handler (impact_current_kind), life 50..100, alpha 100..200 and random flip flags 2 / 4.
// The first random_int call's result is not used.
void func_1515BBE4(s16 id) {
    struct {
        s16 id;             /* 0x00 */
        u8 pad2[2];
        f32 speed;          /* 0x04 */
        f32 spin;           /* 0x08 */
        f32 size;           /* 0x0C */
        f32 size2;          /* 0x10 */
        u8 pad14[4];
    } blk;
    struct {
        f32 x;              /* 0x00 */
        f32 y;              /* 0x04 */
        f32 w;              /* 0x08 */
        f32 h;              /* 0x0C */
        u8 tex;             /* 0x10 */
        u8 pad11;
        s16 life;           /* 0x12 */
        u16 flags;          /* 0x14 */
        s16 u16;            /* 0x16 */
        s16 u18;            /* 0x18 */
        u8 u1A;             /* 0x1A */
        u8 colour[5];       /* 0x1B: FF FF FF alpha FF */
        u8 u20[4];          /* 0x20 */
        s32 u24;            /* 0x24 */
        s32 u28;            /* 0x28 */
        s32 u2C;            /* 0x2C */
        s32 u30;            /* 0x30 */
        s32 u34;            /* 0x34 */
        s32 u38;            /* 0x38 */
        s32 u3C;            /* 0x3C */
        u8 u40;             /* 0x40 */
        u8 u41;             /* 0x41 */
        u8 pad42[2];
        u8 id;              /* 0x44 */
    } spr;
    f32 size;
    s32 n;
    u8 *e;

    random_int(); /* result unused */
    spr.flags = 0x19;
    spr.u1A = 1;
    spr.u16 = 0x14;
    spr.u18 = 0xC;
    spr.colour[0] = 0xFF;
    spr.colour[1] = 0xFF;
    spr.colour[2] = 0xFF;
    spr.colour[4] = 0xFF;
    blk.id = id;
    spr.id = id;
    spr.u20[0] = 0xFF;
    spr.u20[1] = 0xFF;
    spr.u20[2] = 0xFF;
    spr.u20[3] = 0xFF;
    spr.u24 = 0;
    spr.u28 = 0;
    spr.u2C = 0;
    spr.u40 = 0;
    spr.u41 = 9;
    spr.u30 = 7;
    spr.u34 = 0x3C;
    spr.u38 = 0x80;
    spr.u3C = 0x20;
    for (n = 10; n != 0; n--) {
        blk.speed = (random_float() * 105.0f + 105.0f) * 0.001f;
        blk.spin = random_float() * 3008.0f * 0.001f;
        size = (random_float() * 1579.0f + 489.0f) * 0.01f;
        spr.w = size;
        spr.h = size;
        blk.size = size;
        blk.size2 = (random_float() * 301.0f + 94.0f) * 0.01f;
        spr.x = random_float() * 200.0f + -100.0f;
        spr.y = random_float() * 148.0f + -100.0f;
        spr.tex = D_800900A4[impact_current_kind()]();
        spr.life = (u32) random_int() % 51 + 50;
        spr.colour[3] = (u32) random_int() % 101 + 100;
        if (random_int() & 1) {
            spr.flags |= 2;
        }
        if (random_int() & 1) {
            spr.flags |= 4;
        }
        e = (u8 *) func_151559FC(&spr, 2, 0, 0, 0x18, 0xFF, 1);
        if (e != NULL) {
            memcpy((s32) (e + 0x70), (f32 *) &blk, 0x18);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BBE4.s")
#endif

#ifdef NON_MATCHING
s32 func_1515BF04(u8 *arg0) {
    f32 temp_f14;
    f32 temp_f2;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x78));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x74));
    (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + ((temp_f2 * D_800BE9A4) + (0.5f * temp_f14 * D_800BE9A4)));
    (*(f32 *)((u8 *)arg0 + 0x78)) = (f32) (temp_f2 + (temp_f14 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + ((*(f32 *)((u8 *)arg0 + 0x80)) * ((*(f32 *)((u8 *)arg0 + 0x78)) + temp_f2) * 0.5f));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_188D10/func_1515BF04.s")
#endif
void func_1515BF80(s32 arg0) {
}

void func_1515BF8C(s16 arg0) {
    func_1515B500(arg0);
}

void func_1515BFB8(s32 arg0) {
}

void func_1515BFC4(s16 arg0) {
    func_1515BBE4(arg0);
}

void func_1515BFF0(s16 arg0) {
    func_1515BB64(arg0);
}

void func_1515C01C(s16 arg0) {
    func_1515BB64(arg0);
}
