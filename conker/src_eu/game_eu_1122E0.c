#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/func_150E4AD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/func_150E4EA8.s")

typedef struct {
    u8 pad0[0x90];
    s32 u90;
    s16 u94;
    s16 u96;
    s16 u98;
    u8 pad9A[0x8];
    s16 uA2;
    s16 uA4;
    u8 padA6[0xE];
    u8 uB4;
} E523S;

void func_150E523C(E523S *arg0) {
    if (arg0->u90 < 9) {
        arg0->uA4 = (((arg0->u90 * 90) / 9) * arg0->u96) * 0.00390625f;
    } else {
        arg0->uA4 = ((90 - ((arg0->u90 * 90) - 810) / 600) * arg0->u96) * 0.00390625f;
        if (D_800BE9E4 * 17 < arg0->uB4) {
            arg0->uB4 -= D_800BE9E4 * 17;
        } else {
            arg0->u98 = -1;
        }
    }
    arg0->uA2 = (s32)(arg0->u94 * 14.0f) >> 8;
    if (arg0->u90 >= 0x261) {
        arg0->u98 = -1;
    }
    arg0->u90 += D_800BE9E4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/func_150E5384.s")

s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
s32 func_151EFDD0(void);

void func_150E5AD8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
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
        u8 u88;
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
        u8 padA0[0x6];
    } sp;
    f32 a;
    f32 b;
    f32 t;

    bzero(&sp, sizeof(sp));
    if (arg4 != 0.0f) {
        a = func_150484A0(arg3, arg4) * 57.295776f;
    } else {
        a = 90.0f;
    }
    if (arg5 != 0.0f) {
        b = func_150484A0(arg3, arg5) * 57.295776f;
    } else {
        b = 90.0f;
    }
    sp.u28[5] = b;
    sp.u28[6] = a;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u28[0] = 1.0f;
    sp.u28[2] = 0.17f;
    sp.u28[3] = 0.17f;
    sp.u28[10] = arg0;
    sp.u28[11] = arg1;
    sp.u28[12] = arg2;
    sp.u28[4] = 0.0f;
    if (arg6 == 4) {
        sp.u28[1] = 0.6f;
        sp.u7E = 6;
    } else if (arg6 == 9) {
        sp.u28[1] = 0.3f;
        sp.u7E = 8;
    } else {
        sp.u28[1] = 0.3f;
        sp.u7E = 7;
    }
    sp.u7C = (func_151EFDD0() % 60) + 60;
    sp.u78 = 0x29E9;
    t = (func_150ADA68() * 4.6f) + 1.5f;
    sp.u74 = -0.78f;
    sp.u5C = t * arg3;
    sp.u60 = -t * arg4;
    sp.u64 = t * arg5;
    sp.u68 = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u70 = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u6C = (func_150ADA68() * 6.0f) + -3.0f;
    sp.u80 = 0;
    sp.u84 = 0;
    sp.u88 = 0xFF;
    sp.u89 = 1;
    sp.u8A = 0;
    sp.u8B = 3;
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
    func_15132FBC(&sp, 3, 0xFF, 0, 0xFF, 0);
}

#ifdef NON_MATCHING
void func_15049350(s32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
f32 func_150ADDE0(f32 *a, f32 *b);
extern f32 D_800CC630, D_800CC634, D_800CC638; /* plane of the last func_15049350 triangle */

// debris_ground_bounce: ground handler 4 of D_80089CD4 (`s32 (u8 *, f32, f32, f32, f32, u8 *)`, func_15132BBC's
// dispatcher; x / y / z unused). Puts the object on the ground (+0x3C = +0x10 * 1.1 + ground). Slower than 2 downwards
// it stops: velocities +0x44..+0x4C cleared, flags 0x6F of +0x60 dropped. Otherwise it bounces: with the ground
// triangle `tri` (nine s16) the velocity is reflected about the triangle's normal (v - 2 (v.n) n, from the
// func_15049350 plane D_800CC630; skipped when the normal is shorter than 1e-5) and scaled by +0x14 (x / z also
// by 0.8); without a triangle only the y velocity is flipped. The spin +0x50..+0x58 is scaled by +0x14 too.
// Returns 1 (keep the object).
s32 func_150E5D90(u8 *p, f32 x, f32 y, f32 z, f32 ground, s16 *tri) {
    f32 vy = *(f32 *) (p + 0x48);
    f32 v[3][3];
    f32 n[3];
    f32 unit[3];
    f32 vel[3];
    f32 len;
    f32 fac;
    s32 i;

    *(f32 *) (p + 0x3C) = *(f32 *) (p + 0x10) * 1.1f + ground;
    if (-2.0f < vy) {
        *(f32 *) (p + 0x44) = 0.0f;
        *(s32 *) (p + 0x60) &= ~0x6F;
        *(f32 *) (p + 0x48) = 0.0f;
        *(f32 *) (p + 0x4C) = 0.0f;
        return 1;
    }
    if (tri != NULL) {
        for (i = 0; i < 3; i++) {
            v[i][0] = tri[i * 3 + 0];
            v[i][1] = tri[i * 3 + 1];
            v[i][2] = tri[i * 3 + 2];
        }
        func_15049350(*(s32 *) &v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]);
        n[0] = -D_800CC630;
        n[1] = -D_800CC634;
        n[2] = -D_800CC638;
        len = func_150AD930(n);
        if (1e-05f < len) {
            func_15049148((struct17 *) n, 1.0f / len, (struct17 *) unit);
            vel[0] = *(f32 *) (p + 0x44);
            vel[1] = *(f32 *) (p + 0x48);
            vel[2] = *(f32 *) (p + 0x4C);
            len = func_150ADDE0(unit, vel);
            func_15049148((struct17 *) unit, len + len, (struct17 *) n);
            func_15048F58((struct17 *) vel, (struct17 *) n, (struct17 *) n);
            fac = *(f32 *) (p + 0x14);
            *(f32 *) (p + 0x44) = fac * n[0] * 0.8f;
            *(f32 *) (p + 0x48) = fac * n[1];
            *(f32 *) (p + 0x4C) = fac * n[2] * 0.8f;
        }
        fac = *(f32 *) (p + 0x14);
    } else {
        fac = *(f32 *) (p + 0x14);
        *(f32 *) (p + 0x44) *= fac;
        *(f32 *) (p + 0x48) = -vy * fac;
        *(f32 *) (p + 0x4C) *= fac;
    }
    *(f32 *) (p + 0x50) *= fac;
    *(f32 *) (p + 0x54) *= fac;
    *(f32 *) (p + 0x58) *= fac;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1122E0/func_150E5D90.s")
#endif
