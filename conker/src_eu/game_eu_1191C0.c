#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_150EBA04
s32 func_150EBA04(u8 *arg0, f32 *arg1, s32 arg2);



void func_150EB430(void *arg0, void *arg1, s32 arg2) {
    f32 sp1C[3];

    sp1C[0] = ((f32 *)arg1)[0] + ((f32 *)arg0)[0];
    sp1C[1] = ((f32 *)arg1)[1] + ((f32 *)arg0)[1];
    sp1C[2] = ((f32 *)arg1)[2] + ((f32 *)arg0)[2];
    func_150EBA04(arg0, sp1C, arg2);
}

s32 func_150A2D44(s32, s32);
s32 func_150EC200(u8 *, s32, s32);
extern s32 D_80088E40[];
extern s32 D_80088E50[];
extern s32 D_80088E70;

s32 func_150EBA04(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 pad[2]; // fakematch: unused 8 bytes, the ref frame is 0x50
    struct127 *sp44;
    s32 *var_s0;
    s32 temp_lo;
    s32 temp_s2;
    s32 var_s1;

    sp44 = func_15083E90(9U);
    if (sp44 != NULL) {
        for (var_s1 = 0; var_s1 < 4; var_s1++) {
            temp_s2 = D_80088E40[var_s1];
            temp_lo = temp_s2 * 0x34;
            if (func_150A3990(temp_lo + D_800D34B8, arg0, arg1, arg2) != 0) {
                func_150A2D44(temp_s2, 1);
                sp44->unk2E8 = var_s1 + 1;
                func_150EC200(temp_lo + D_800D34B8, 0xFF, 1);
                return 1;
            }
        }
        for (var_s1 = 0; var_s1 < 8; var_s1++) {
            if (func_150A3990((D_80088E50[var_s1] * 0x34) + D_800D34B8, arg0, arg1, arg2) != 0) {
                return 1;
            }
        }
        return 0;
    }
    if (func_150A3990(D_800D34B8 + 0xF70, arg0, arg1, arg2) != 0) {
        (*(s32 *)((u8 *)D_800D34B8 + 0xF88)) = 1;
    }
    return 0;
}

#ifdef NON_MATCHING
void func_15117CF0(f32 *arg0);
float sqrtf(float);

// tilt_spring_update: spring-driven angle at obj +0x0 (velocity +0x84, damping +0x7C, stiffness +0x80; state in the
// low 2 bits of +0x73). State 3: idle. State 2: func_15117CF0 steps the angle; once it stops changing the state
// becomes 3 and the angle 0. States 0 / 1: the target is -40, or, for objects with +0x4F bit 2, -40 plus 0.0108 *
// the distance to the player (D_800CC2D0[0] position +0x14..+0x1C, at most 740); when the player's +0x31C
// record has +0x57 set, the state becomes 2 with damping 0.5, stiffness 0.3, velocity 0 and +0x3C = 0. The angle
// moves by velocity * D_800BE9E4, the velocity by +-|diff| * stiffness (diff = func_15048A70(angle, target)) and is
// damped; it snaps to the target when both |diff| and |velocity| are below 0.01, else wraps into [0, 360).
void func_150EBB94(u8 *obj) {
    u8 *player = (u8 *) D_800CC2D0;
    f32 target;
    f32 dx, dy, dz;
    f32 dist;
    f32 angle;
    f32 vel;
    f32 damping;
    f32 stiffness;
    f32 diff;
    u8 state = obj[0x73];

    if ((state & 3) == 3) {
        return;
    }
    if ((state & 3) == 2) {
        angle = *(f32 *) obj;
        func_15117CF0((f32 *) obj);
        if (angle == *(f32 *) obj) {
            obj[0x73] = (obj[0x73] & ~3) | 3;
            *(f32 *) obj = 0.0f;
        }
        return;
    }
    if (obj[0x4F] & 4) {
        if ((*(u8 **) (player + 0x31C))[0x57] != 0) {
            obj[0x73] = (state & ~3) | 2;
            *(s32 *) (obj + 0x3C) = 0;
            *(f32 *) (obj + 0x7C) = 0.5f;
            *(f32 *) (obj + 0x80) = 0.3f; /* D_800A18AC */
            *(f32 *) (obj + 0x84) = 0.0f;
        }
        dz = *(s16 *) (obj + 0x14) - *(f32 *) (player + 0x1C);
        dx = *(s16 *) (obj + 0x10) - *(f32 *) (player + 0x14);
        dy = *(s16 *) (obj + 0x12) - *(f32 *) (player + 0x18);
        dist = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (740.0f < dist) {
            dist = 740.0f;
        }
        target = dist * 0.010810811f /* D_800A18B0 */ + -40.0f;
    } else {
        target = -40.0f;
    }
    angle = *(f32 *) obj;
    damping = *(f32 *) (obj + 0x7C);
    stiffness = *(f32 *) (obj + 0x80);
    vel = *(f32 *) (obj + 0x84);
    if (angle == target && vel == 0.0f) {
        return;
    }
    angle += vel * D_800BE9E4;
    diff = func_15048A70(angle, target);
    if (0.0f < diff) {
        vel += fabsf(diff) * stiffness;
    } else {
        vel -= fabsf(diff) * stiffness;
    }
    vel *= damping;
    if (fabsf(diff) < 0.01f /* D_800A18B4 */ && fabsf(vel) < 0.01f) {
        vel = 0.0f;
        angle = target;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    } else if (360.0f <= angle) {
        angle -= 360.0f;
    }
    *(f32 *) (obj + 0x84) = vel;
    *(f32 *) obj = angle;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBB94.s")
#endif

#ifdef NON_MATCHING
/* func_15132BBC spark template (func_150EBE44); pad bytes stay unset like the asm's */
typedef struct {
    f32 u0;         /* 0x00 9.0 */
    f32 u4;         /* 0x04 D_800A18B8 (0.435) */
    f32 u8;         /* 0x08 */
    f32 uC;         /* 0x0C */
    f32 pos[3];     /* 0x10 D_800A5860 */
    f32 scale[3];   /* 0x1C */
    f32 dir[3];     /* 0x28 D_800A1878[i] */
    f32 vel[3];     /* 0x34 func_15143794 */
    f32 u40;        /* 0x40 */
    f32 u44;        /* 0x44 */
    f32 u48;        /* 0x48 */
    f32 u4C;        /* 0x4C */
    s32 u50;        /* 0x50 0x29E9 */
    s16 life;       /* 0x54 */
    s16 u56;        /* 0x56 D_800A18A8[i] */
    u8 u58;         /* 0x58 */
    u8 pad59[3];
    s32 u5C;        /* 0x5C */
    u8 u60[8];      /* 0x60 */
    u8 u68;         /* 0x68 */
    u8 pad69;
    u8 u6A;         /* 0x6A */
    u8 pad6B;
    s32 u6C;        /* 0x6C */
    u8 u70;         /* 0x70 */
    u8 pad71;
    s16 u72;        /* 0x72 */
    s16 u74;        /* 0x74 */
    u8 pad76[2];
    s32 u78;        /* 0x78 */
} SparkBE44;

typedef struct {
    f32 v[3];
} VecBE44;

extern u8 D_800BEE0B;
extern f32 D_800A1860[];
extern f32 D_800A186C[];
extern VecBE44 D_800A1878[];
extern u8 D_800A18A8[];
#endif

#ifdef NON_MATCHING
void func_150E892C(void *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
void func_151D45A4(u8 *, u8, s32);
s32 func_151D5AC4(f32 *, s32, s32);
s32 func_15132BBC(f32 *, s32, s32, s32, s32, s32, s32);
void func_15143794(s16, s16, f32, void *);

// fireworks_burst: sound (func_1516547C 2), a flash at D_800A186C (func_150E892C, size 120..181) and the effects at
// D_800A1860 (func_151D5AC4 / func_151D45A4 / func_15154728 radius 12..16), then four spark showers (func_15132BBC
// type 3), one per D_800A1878 direction, each with a random launch velocity (func_15143794: angle 45..70, yaw
// -25..-10, speed 15..45), sizes and a life of 50..100 frames. Returns the last func_15132BBC result; `arg0` (the
// event id the dispatcher func_1509DB90 passes) is unused.
s32 func_150EBE44(s32 arg0) {
    SparkBE44 t;
    f32 f;
    u8 i;
    u32 a;
    u32 b;
    s32 ret;

    func_1516547C(2, D_800BEE0B, 0, 0xFF, 1);
    func_150E892C(D_800A186C, (u32) func_150ADA20() % 62 + 120, 0xFF, 1);
    func_151D5AC4(D_800A1860, 0xFF, 1);
    func_151D45A4((u8 *) D_800A1860, 0xFF, 1);
    f = func_150ADA68();
    func_15154728(D_800A1860, f * 4.0f + 12.0f, 1.64099991f, (u32) func_150ADA20() % 56 + 200, 0.0f, 0xFF, 1);
    t.u8 = 1.0f;
    t.uC = 1.0f;
    t.u0 = 9.0f;
    t.u4 = 0.435000032f;  /* D_800A18B8 */
    *(VecBE44 *) t.pos = *(VecBE44 *) D_800A5860;
    t.u44 = 0.0f;
    t.scale[0] = 1.0f;
    t.scale[1] = 1.0f;
    t.scale[2] = 1.0f;
    t.u50 = 0x29E9;
    t.u58 = 0;
    t.u5C = 0;
    t.u60[0] = 0xFF;
    t.u60[1] = 0xD;
    t.u60[2] = 0;
    t.u60[3] = 0xC;
    t.u60[4] = 0;
    t.u60[5] = 0;
    t.u60[6] = 0;
    t.u60[7] = 0;
    t.u68 = 2;
    t.u6A = 2;
    t.u6C = 0;
    t.u70 = 0;
    t.u72 = 0x19;
    t.u74 = 0xA;
    t.u78 = 0;
    for (i = 0; i < 4; i++) {
        *(VecBE44 *) t.dir = D_800A1878[i];
        a = func_150ADA20();
        b = func_150ADA20();
        f = func_150ADA68();
        func_15143794(a % 26 + 45, (b & 0xF) - 25, f * 30.0f + 15.0f, t.vel);
        t.u40 = func_150ADA68() * 15.1080008f + -7.55400038f; /* D_800A18C8, D_800A18C4 */
        t.u48 = func_150ADA68() * 15.1080008f + -7.55400038f;
        t.u4C = func_150ADA68() * 0.617000043f + -1.62100005f; /* D_800A18C0, D_800A18BC */
        t.life = (u32) func_150ADA20() % 51 + 50;
        t.u56 = D_800A18A8[i];
        ret = func_15132BBC((f32 *) &t, 3, 0xFF, 0, 0, 0xFF, 1);
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EBE44.s")
#endif

#ifdef NON_MATCHING
void func_150E892C(void *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_1516547C(s32, s32, s32, s32, s32);
void func_151D45A4(u8 *, u8, s32);
s32 func_151D5AC4(f32 *, s32, s32);

s32 func_150EC200(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s8 u7C;
        u8 pad7D[0x1];
        s16 u7E;
        s8 u80;
        s8 u81;
        s8 u82;
        u8 pad83[0x9];
        f32 u8C;
        f32 u90;
        f32 u94;
    } sp;
    f32 temp_f20;
    f32 temp_f30;
    f32 var_f18;
    s32 temp_at;
    s32 temp_s1;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_s0;

    temp_s1 = arg1 & 0xFF;
    sp.u8C = (f32) (*(s16 *)((u8 *)arg0 + 0));
    sp.u90 = (f32) (*(s16 *)((u8 *)arg0 + 2));
    sp.u94 = (f32) (*(s16 *)((u8 *)arg0 + 4));
    temp_f30 = (f32) (*(s16 *)((u8 *)arg0 + 8)) * 0.5f;
    func_150E892C(&sp.u8C, (s16) ((func_150ADA20() % 101U) + 0x12C), temp_s1 & 0xFF, arg2);
    sp.u7C = 1;
    sp.u7E = (func_150ADA20() % 21U) + 0xF;
    sp.u80 = 0;
    sp.u82 = -1;
    sp.u81 = 1;
    func_151D8E18((structEU_151D8E18 *) &sp.u7C, 0, temp_s1 & 0xFF, arg2);
    func_1516547C(0, 0, 0, temp_s1 & 0xFF, arg2);
    var_s0 = 0;
    do {
        func_151D45A4(&sp.u8C, temp_s1 & 0xFF, arg2);
        func_151D5AC4(&sp.u8C, temp_s1 & 0xFF, arg2);
        temp_f20 = func_150ADA68();
        temp_t8 = (func_150ADA20() % 56U) + 0xC8;
        var_f18 = (f32) temp_t8;
        if (temp_t8 < 0) {
            var_f18 += 4294967296.0f;
        }
        temp_v0 = func_15154728(&sp.u8C, (temp_f20 * 4.0f) + 12.0f, 1.6409999f, var_f18, 0.0f, temp_s1, arg2);
        temp_t9 = (var_s0 + 1) & 0xFF;
        temp_at = temp_t9 < 2;
        var_s0 = temp_t9;
        sp.u90 += temp_f30;
    } while (temp_at != 0);
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1191C0/func_150EC200.s")
#endif