#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_8009FB60[];
#endif

u8 *func_151149AC(u8);

// The callee (game_eu_1FB080.c) takes only the first three arguments.
void func_151CFE48(s32 arg0, f32 arg1, f32 arg2, s16 *arg3);


extern s32 * D_800DC3C4;
void func_150AF6E0(s32 arg0, u8 arg1) {
    s32 i;
    if (D_800CC3D4[0] == 0) {
        i = (struct131 *)func_151149AC(arg0) - D_800DBEF4;
        if (D_800DC3C4[i] & 1) {
            func_1505D024(D_800CC2D0, 0x3F, 0x6E00, -1);
            return;
        }
        i = (struct131 *)func_151149AC(arg1) - D_800DBEF4;
        if (D_800DC3C4[i] & 1) {
            func_1505D024(D_800CC2D0, 0x3F, 0xEE00, -1);
        }
    }
}

void func_150AF7C0(s32 arg0, s16 *arg1) {
    func_151CFE48(arg0, (f32)(arg1[4] + arg1[1]), (f32)arg1[1], arg1);
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
s32 memcpy(s32, s8 *, s32);

void func_150AF808(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f10;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((1352.0f + (func_150ADA68() * 1698.0f)) * 0.0001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x46;
        sp.uBC = 3;
        sp.uF4 = 0x80DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.uFE = 0x16;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x46;
        sp.uB0 = 0xC7;
        sp.uB1 = 0x78;
        sp.uB2 = 8;
        sp.uB3 = 0xFF;
        sp.uB4 = 0x30;
        sp.uB5 = 0xE;
        sp.uB6 = 0;
        sp.uB8 = 0xFF;
        sp.u98 = 0.97047f;
        sp.uC0 = 1.021029f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u8E = (func_150ADA20() % 5U) + 4;
            sp.u8F = (func_150ADA20() % 5U) + 4;
            sp.u90 = func_150ADA68() * 11.0f;
            sp.u94 = func_150ADA68() * 11.0f;
            temp_f10 = func_150ADA68() * 0.172f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = temp_f10 + 0.098000005f;
            var_s0 = 0;
            if (func_150ADA20() & 1) {
                var_s0 = 0x80;
            }
            if (func_150ADA20() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (func_150ADA20() % 101U) + 0x64;
            sp.uA6 = (func_150ADA20() % 51U) + 0x50;
            temp_f6 = (func_150ADA68() * 71.0f) + 80.0f;
            sp.uC8 = temp_f6;
            sp.uC4 = temp_f6;
            temp_v0 = func_151307F0(&sp.u9C, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AF808.s")
#endif
#ifdef NON_MATCHING
// P230 (implicit_scan): func_15131EC8 takes (f32 *, f32); the matching C below calls it without a prototype and
// passes the f32's bit pattern as an int (lands in a1 either way on N64, wrong type on the port).
void func_15131D98(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void func_15131EC8(f32 *arg0, f32 arg1);
s32 func_150AFBC4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8((f32 *)(arg0 + 0x58), *(f32 *)(p + 0xC));
    return 1;
}
#else
s32 func_150AFBC4(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0xA8;

    func_15131D98(arg0, arg0 + 0xAC, p, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, *(s32 *)(p + 0xC));
    return 1;
}
#endif

u8 * func_151604E4(void *arg0, s32 arg1, u8 arg2, s32 arg3);

void func_150AFC18(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        s8 unk0;
        s8 unk1;
        s8 unk2;
        s16 unk4;
        s8 unk6;
    } sp18;

    sp18.unk0 = 1;
    sp18.unk1 = -1;
    sp18.unk2 = 2;
    sp18.unk6 = 0;
    sp18.unk4 = arg0;
    func_151604E4(&sp18, 0, arg1, arg2);
}

void func_150B2290(u16 *start, u16 *end);

void func_150AFC70(s32 arg0, s32 arg1) {
    func_150B2290((u16 *)arg1, (u16 *)(arg1 + 0x1ECC0));
}

#ifdef NON_MATCHING
s32 func_151559FC(f32 *, s32, s32, s32, s32, s32, s32);
u8 func_151D8E6C(void);

void func_150AFCA4(u8 *arg0) {
    struct {
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s8 u50;
        u8 pad51[0x1];
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s32 u64;
        s32 u68;
        s32 u6C;
        s32 u70;
        s32 u74;
        s32 u78;
        s32 u7C;
        s8 u80;
        s8 u81;
        u8 pad82[0x2];
        s8 u84;
        u8 pad85[0x17];
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        s8 uBC;
        u8 padBD[0x1];
        s16 uBE;
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        s8 uCD;
        s8 uCE;
        s8 uCF;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s32 uE4;
        s32 uE8;
        s8 uEC;
        s8 uED;
        u8 padEE[0x2];
        s8 uF0;
    } sp;
    s32 sp38;
    u8 *sp34;
    f32 temp_f10;
    f32 temp_f2;
    s16 temp_t2;
    s16 temp_t5;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_v0_2;

    (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x28)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x28)) < 0) {
        sp.u9C = (func_150ADA68() * 280.0f) + -140.0f;
        sp.uA0 = func_150ADA68() * 50.0f;
        sp.uA4 = 2.0f * (func_150ADA68() * 3.1415927f);
        temp_f10 = func_150ADA68() * 0.268f;
        sp.uAC = 0.0f;
        sp.uB0 = 0.0f;
        sp.uA8 = temp_f10;
        func_150ADA68();
        sp.uBC = 0xFF;
        sp.uB4 = 1.0f;
        sp.uB8 = 115.0f;
        temp_t2 = (func_150ADA20() % 71U) + 0x14;
        sp.uBE = temp_t2;
        temp_v1 = (*(s16 *)((u8 *)arg0 + 0xE));
        if (temp_v1 < temp_t2) {
            sp.uBE = temp_v1;
        }
        sp.uC0 = 0x21;
        sp.uC2 = 1;
        sp.uC4 = 0xFF;
        sp.uC6 = 0;
        sp.uC7 = 0xFF;
        sp.uC8 = 0xFF;
        sp.uC9 = 0xFF;
        sp.uCA = (func_150ADA20() % 71U) + 0x28;
        sp.uCB = 0xFF;
        sp.uCC = 0xFF;
        sp.uCD = 0xFF;
        sp.uCE = 0xFF;
        sp.uCF = 0xFF;
        sp.uD0 = 0;
        sp.uD4 = 0x200004;
        sp.uD8 = 0x1F0601;
        sp.uDC = 0x19;
        sp.uE0 = 0x54;
        sp.uE4 = 0x80;
        sp.uE8 = 0x20;
        sp.uEC = 0;
        sp.uED = 0xA;
        sp.uF0 = 0;
        temp_v0 = func_151559FC(&sp.uAC, 6, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x70, (s8 *) &sp.u9C, 0x10);
        }
        (*(s16 *)((u8 *)arg0 + 0x28)) = (s16) ((func_150ADA20() % 41U) + 0x2D);
    }
    temp_v0_2 = arg0 + 0x28;
    (*(s16 *)((u8 *)temp_v0_2 + 2)) = (s16) ((*(s16 *)((u8 *)temp_v0_2 + 2)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_v0_2 + 2)) < 0) {
        sp34 = temp_v0_2;
        sp.u40 = (func_150ADA68() * 280.0f) + -140.0f;
        sp.u44 = (func_150ADA68() * 200.0f) + -100.0f;
        temp_f2 = (2.0f * func_150ADA68()) + 1.0f;
        sp.u48 = temp_f2;
        sp.u4C = temp_f2;
        sp.u50 = func_151D8E6C();
        temp_t5 = (func_150ADA20() % 7U) + 5;
        sp.u52 = temp_t5;
        temp_v1_2 = (*(s16 *)((u8 *)arg0 + 0xE));
        if (temp_v1_2 < temp_t5) {
            sp.u52 = temp_v1_2;
        }
        var_v1 = 0;
        if (func_150ADA20() != 0) {
            var_v1 = 2;
        }
        sp38 = var_v1;
        if (func_150ADA20() != 0) {
            var_v0 = 4;
        } else {
            var_v0 = 0;
        }
        sp.u54 = var_v0 | 1 | var_v1 | 0x20;
        sp.u56 = 1;
        sp.u58 = 0xFF;
        sp.u5A = 0;
        sp.u5B = 0xFF;
        sp.u5C = 0xFF;
        sp.u5D = 0xFF;
        sp.u5E = (func_150ADA20() % 121U) + 0x50;
        sp.u5F = 0xFF;
        sp.u60 = 0xFF;
        sp.u61 = 0xFF;
        sp.u62 = 0xFF;
        sp.u63 = 0xFF;
        sp.u64 = 0;
        sp.u68 = 0x200004;
        sp.u6C = 0x1F0601;
        sp.u70 = 0x19;
        sp.u74 = 0x55;
        sp.u78 = 0x80;
        sp.u7C = 0x20;
        sp.u80 = 0;
        sp.u81 = 7;
        sp.u84 = 0;
        func_151559FC(&sp.u40, 0, 0, 0, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(s16 *)((u8 *)sp34 + 2)) = (s16) ((func_150ADA20() % 11U) + 3);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150AFCA4.s")
#endif
s32 func_150B00D4(u8 *arg0) {
    u8 *v = arg0 + 0x70;
    *(f32 *)(arg0 + 0x78) = *(f32 *)(arg0 + 0x7C) * D_800BE9A4 + *(f32 *)(arg0 + 0x78);
    *(f32 *)(v + 8) = func_15144B68(*(f32 *)(arg0 + 0x78));
    *(f32 *)(arg0 + 0x10) = *(f32 *)v + *(f32 *)(v + 4) * sinf(*(f32 *)(v + 8));
    return 1;
}

s32 func_1516DF0C(s16, s16, s16, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, s16, s16, s16, s16, u16, u8, u8, u8, u8, s16, u16, u16, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32);

void func_150B0148(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C(1, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 1, 0, 0, 0, 0, 0xAA, 0xAA, 0xAA, 0xAA, arg2, arg3, 0, arg0, 0xF0, 0x50, 0x50, 1, 4, 0, 1, 0, 0, 0, arg1, 0, (s32) arg4, arg5);
}

extern struct_eu_node *D_800DD2C4;
void func_150B0290(void) {
    struct_eu_node *node;

    node = D_800DD2C4;
    D_800DD5C0++;
    while (node != NULL) {
        D_800DD5C8[D_800DD5C0] = node->next;
        if (D_800C3E78 == ((u8 *)node)[0x3F]) {
            func_1516972C((struct102 *)node);
        }
        node = D_800DD5C8[D_800DD5C0];
    }
    D_800DD5C0--;
}

#ifdef NON_MATCHING
s32 func_150E2030(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                  s32, f32, f32, f32, f32, f32, f32);
void func_150E3334(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   s16 argA, s16 argB, u16 argC, u8 argD);

// player_joint_beam_spawn: event-mode helper (D_800D1580 modes 9 / 10). Uses joint matrix 3 (side 0) or 2 (side 1)
// of the player's (D_800D154C) matrix block at +0x1D4 (64 bytes per matrix; nothing when it is NULL); transforms the
// local points (0, 0, -20) and (0, 0, -150) to world space, spawns the line effect func_150E2030 between them
// (40, 0, 2, 120, 60, 35) and attaches effect func_150E3334 to that joint ((0, 0, -39) .. (0, 0, -150), 3, 255, 4).
void func_150B0344(s32 side) {
    u8 *mtx = (u8 *)D_800D154C->unk1D4;
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 (*m)[4];
    s32 joint;

    if (mtx == NULL) {
        return;
    }
    if (side == 0) {
        joint = 3;
    } else {
        joint = 2;
    }
    m = (f32 (*)[4])(mtx + (joint << 6));
    x0 = 0.0f;
    y0 = 0.0f;
    z0 = -20.0f;
    func_150A7E40(m, x0, y0, z0, &x0, &y0, &z0);
    x1 = 0.0f;
    y1 = 0.0f;
    z1 = -150.0f;
    func_150A7E40(m, x1, y1, z1, &x1, &y1, &z1);
    func_150E2030(0, x0, y0, z0, x1, y1, z1, 40.0f, 0.0f, 2.0f, 120.0f, 0x3C, 0x23, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    func_150E3334((s32)D_800D154C, D_800D154C->unique_id, (s16)joint, -1, 0.0f, 0.0f, -39.0f, 0.0f, 0.0f, -150.0f, 3, 0xFF,
                  4, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0344.s")
#endif

void func_150B051C(s32 arg0) {
    if (D_800BE9F0 == 6) {
        func_15179008(0);
        func_150AF6E0(0xE2, 0xE1);
    } else {
        func_150AF6E0(0xDF, 0xDE);
    }
}

#ifdef NON_MATCHING
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
void func_15145974(f32 *, f32 *, f32 *);
u8 *func_15132BBC(u8 *req, s32 nTrails, s32 arg2, s32 *bounds, s32 extraSize, u8 arg5, s32 owner);
u8 *func_151B78D8(void *src, u8 type, s32 size, u8 alpha, s32 arg4);

// beam_trail_spawn: spawns a 3-strand trail (func_15132BBC, request below, 4 extra bytes) from `from` along
// (to - from) when that direction is non-zero (func_15145128): scale (1, 1, 0.7, 0.7), heading / pitch of the
// direction * 80 (func_15145974), colour 1, start `from`, speed (to - from) * 80, life 0x19A0 / 300 / 210; then
// records an effect of type 1 (func_151B78D8, size 8, owner = the trail) in the trail's extra word (+0x170).
void func_150B0574(f32 *from, f32 *to, u8 alpha, s32 arg3) {
    struct {
        f32 u00;
        f32 u04;
        f32 u08;
        f32 u0C;
        f32 pitch;
        f32 yaw;
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 pos[3];
        f32 vel[3];
        f32 u40[3];
        f32 u4C;
        s32 u50;
        s16 u54;
        s16 u56;
        u8 u58;
        u8 pad59[3];
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62;
        u8 u63;
        u8 u64;
        u8 u65;
        u8 u66;
        u8 u67;
        u8 u68;
        u8 pad69;
        u8 u6A;
        u8 pad6B;
        s32 u6C;
        u8 u70;
        u8 pad71;
        s16 u72;
        s16 u74;
        u8 pad76[2];
        s32 u78;
    } req;
    f32 dir[3];
    s32 o44;
    s32 o40;
    s32 zero;
    u8 *src;
    u8 *trail;

    zero = 0;
    dir[0] = to[0] - from[0];
    dir[1] = to[1] - from[1];
    dir[2] = to[2] - from[2];
    if (func_15145128(dir, dir, &o44, &o40) == 0) {
        return;
    }
    req.u00 = 1.0f;
    req.u04 = 1.0f;
    req.u0C = 0.7f;
    req.u08 = 0.7f;
    req.pos[0] = from[0];
    req.pos[1] = from[1];
    req.pos[2] = from[2];
    req.vel[0] = dir[0] * 80.0f;
    req.vel[1] = dir[1] * 80.0f;
    req.vel[2] = dir[2] * 80.0f;
    func_15145974(req.vel, &req.yaw, &req.pitch);
    req.u1C = 1.0f;
    req.u20 = 1.0f;
    req.u24 = 1.0f;
    req.u18 = 0.0f;
    req.u40[0] = ((f32 *)D_800A5860)[0];
    req.u40[1] = ((f32 *)D_800A5860)[1];
    req.u40[2] = ((f32 *)D_800A5860)[2];
    req.u50 = 0x19A0;
    req.u54 = 0x12C;
    req.u56 = 0xD2;
    req.u58 = 7;
    req.u5C = 0;
    req.u60 = 0xFF;
    req.u61 = 8;
    req.u62 = 0;
    req.u63 = 0;
    req.u64 = 0;
    req.u65 = 0;
    req.u66 = 0;
    req.u67 = 0;
    req.u68 = 2;
    req.u6A = 0;
    req.u6C = 0;
    req.u70 = 0;
    req.u72 = 1;
    req.u74 = 0xFF;
    req.u78 = 0;
    req.u4C = 0.0f;
    trail = func_15132BBC((u8 *)&req, 3, 0xFF, NULL, 4, alpha, arg3);
    if (trail == NULL) {
        return;
    }
    memcpy((s32)(trail + 0x170), (s8 *)&zero, 4);
    src = trail;
    *(u8 **)(trail + 0x170) = func_151B78D8(&src, 1, 8, alpha, arg3);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0574.s")
#endif

void func_150B07A0(struct102 **arg0) {
    if (*(s32 *)&arg0[0x170 / 4] != 0) {
        func_1516972C(arg0[0x170 / 4]);
    }
}

void func_150B07D0(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132AE0(arg0);
}

void func_150B07FC(u8 *arg0) {
    func_150B07A0(arg0);
    func_15132B0C(arg0);
}

#ifdef NON_MATCHING
void func_15153BA4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_8009FB74;

void func_150B0828(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u2C;
        s32 u30;
        s32 u34;
        u8 pad38[0x8];
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s8 u6C;
        u8 pad6D[0x1];
        s16 u6E;
        s32 u70;
        s32 u74;
        s16 u78;
        s16 u7A;
        s32 u7C;
        s32 u80;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s16 u8E;
        s16 u90;
        s16 u92;
        f32 u94;
        f32 u98;
        f32 u9C;
        s32 uA0;
        u8 padA4[0x8];
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s8 uCC;
        u8 padCD[0x3];
        f32 uD0;
        s32 uD4;
        f32 uD8;
        f32 uDC;
    } sp;

    sp.uD4 = (*(s32 *)((u8 *)arg0 + 0x14));
    sp.uD8 = (*(f32 *)((u8 *)arg0 + 0x18)) + 30.0f;
    sp.uDC = (*(f32 *)((u8 *)arg0 + 0x1C));
    sp.u68 = 0xA;
    sp.u6A = 7;
    sp.u6C = 0x6C;
    sp.u6E = 0x5103;
    sp.u70 = 0x200005;
    sp.u78 = 0x1E;
    sp.u7A = 0xF;
    sp.u87 = 0xFF;
    sp.u84 = 0x7F;
    sp.u86 = 6;
    sp.u74 = 0;
    sp.u7C = 0;
    sp.u80 = 0;
    sp.u85 = 0x4B;
    sp.u88 = 0x80;
    sp.u89 = 0x53;
    sp.u8A = 0;
    sp.u8B = 0x64;
    sp.u8C = 0x64;
    sp.u8D = 0xFF;
    sp.u8E = 0x20;
    sp.u90 = 7;
    sp.u92 = 0x20;
    sp.u94 = 1.025729f;
    sp.u98 = 351.0f;
    sp.u9C = 200.0f;
    (*(s32 *)((u8 *)(&sp.uA0) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.uA0) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.uA0) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.uAC = 0;
    sp.uAE = -0x19;
    sp.uB0 = 0xFF;
    sp.uB2 = 0x15;
    sp.uC4 = 0x40E07;
    sp.uC8 = 0x10;
    sp.uC9 = -1;
    sp.uCA = 8;
    sp.uCB = 6;
    sp.uCC = 1;
    sp.uB4 = 5.0f;
    sp.uB8 = 25.0f;
    sp.uBC = 0.008f;
    sp.uC0 = 0.266f;
    sp.uD0 = 0.938608f;
    func_15153BA4(&sp.u68, 0xFF, arg1, arg2);
    sp.u2C = 0x24;
    sp.u30 = 0xA;
    (*(s32 *)((u8 *)(&sp.u34) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 0));
    (*(s32 *)((u8 *)(&sp.u34) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 4));
    (*(s32 *)((u8 *)(&sp.u34) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uD4) + 8));
    sp.u48 = 11.0f;
    sp.u4C = 8.0f;
    sp.u40 = 0;
    sp.u42 = 0xFF;
    sp.u44 = -0x28;
    sp.u46 = 0x14;
    sp.u58 = 0x22;
    sp.u5A = 0xF;
    sp.u50 = -1.09f;
    sp.u54 = 0.37100002f;
    sp.u5C = 0.30200002f;
    sp.u60 = 0.31800002f;
    sp.u64 = 9.687f;
    func_15152700(&sp.u2C, ((u8 *)&D_8009FB60), &D_8009FB74, 5, 65.0f, 0U, (u8) (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DCEF0/func_150B0828.s")
#endif
s32 func_150B0AEC(u8 arg0, u8 *arg1) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = func_151149AC(arg0);
    (*(u8 **)((u8 *)arg1 + 8)) = temp_v0;
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_v1 = (*(u8 **)((u8 *)arg1 + 8));
    (*(f32 *)((u8 *)arg1 + 0)) = -150.0f;
    (*(f32 *)((u8 *)arg1 + 4)) = 4.5f;
    (*(f32 *)((u8 *)arg1 + 0xC)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x10));
    (*(f32 *)((u8 *)arg1 + 0x10)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x12));
    (*(f32 *)((u8 *)arg1 + 0x14)) = (f32) (*(s16 *)((u8 *)temp_v1 + 0x14));
    return 1;
}
