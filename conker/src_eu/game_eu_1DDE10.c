#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15143794(s16, s16, f32, void *);
s32 func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_151B0600(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s16 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    f32 v[3];
    f32 sp68[3];
    f32 r;

    v[0] = arg2;
    v[1] = arg3;
    v[2] = arg4;
    r = func_150ADA68();
    func_15143794(arg9, arg8, (r * 5.3f) + 4.4f, sp68);
    func_151DA6F8(v, sp68, (func_150ADA68() * (f32)0) + 0.68f, (func_150ADA20() % 20U) + 0x1F, (func_150ADA20() % 101U) + 0x9B, (func_150ADA68() * 2.33f) + 6.7f, (func_150ADA20() & 1) + 3, 1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, argE, 1); // fakematch: (f32)0 keeps the rand * 0 multiply (0.0f folds it)
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B01B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B03B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B09BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1138.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B173C.s")

s32 func_151B1A28(u8 *arg0) {
    s16 temp_v0 = *(s16 *)(arg0 + 0x1C);
    s32 temp_v1;

    if (temp_v0 < 32) {
        temp_v1 = temp_v0 << 3;
        if (temp_v1 < arg0[0x5C]) {
            arg0[0x5C] = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1A5C.s")

s32 func_151B1DD8(u8 *arg0) {
    s32 pad;
    u8 *p;
    f32 s;
    f32 c;

    arg0[0x120] += (s8)arg0[0x122] * D_800BE9E4;
    arg0[0x121] += (s8)arg0[0x123] * D_800BE9E4;
    p = arg0 + 0x110;
    s = func_151423D8((u8)(arg0[0x120] - 0x40));
    c = func_151423D8((u8)(p[0x11] - 0x40));
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(p + 0x14) + (*(f32 *)(p + 0x1C) * s)) - *(f32 *)(arg0 + 0x2C)) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(p + 0x18) + (*(f32 *)(p + 0x20) * c)) - *(f32 *)(arg0 + 0x30)) * 0.5f;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DDE10/func_151B1EC8.s")

void func_151B1F54(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 cur;
    u8 *temp_v0;
    cur = *(s32 *)((u8 *)arg0 + 0x28);
    if ((arg2 == 0) || (arg2 == 0x13)) {
        if (cur == (*(s32 *)((u8 *)arg1 + 0)) || ((*(u8 *)((u8 *)arg0 + 0x2C)) == (*(u8 *)((u8 *)arg1 + 4)))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (u8 *)arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
                return;
            }
            if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
                *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
                *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
            }
        }
    }
}

void func_151B2008(void *arg0) {
    func_151B1EC8(arg0);
    func_1514933C(arg0);
}

void func_151B2034(void *arg0) {
    func_151B1EC8(arg0);
    func_15149368(arg0);
}

void func_151B2060(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    if (arg0 == NULL) {
        return;
    }
    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

extern f32 D_800BE9A4;
typedef struct { f32 x, y, z; } V3_20E4;
extern V3_20E4 D_8008FE70, D_8008FE7C;
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_151308E4(void *, s32, s32, u8, s32);
void func_15143794(s16, s16, f32, void *);
void func_151B20E4(u8 *arg0) {
    u8 *p;
    V3_20E4 *q;
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
        f32 u64[3];
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C[3];
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0x8];
    } sp;
    s32 obj;
    f32 scale;
    V3_20E4 b;
    V3_20E4 a;

    p = arg0 + 0x28;
    *(f32 *)(p + 8) += (697.0f + func_150ADA68() * 342.0f) * 0.001f * D_800BE9A4;
    if (*(f32 *)(p + 8) > 1.0f) {
        if (*(s32 *)(*(u8 **)p + 0x1D4) != 0) {
            V3_20E4 c = D_8008FE70;
            func_15143134(&c, &b, *(s32 *)(*(u8 **)p + 0x1D4) + 0x800);
            {
                V3_20E4 d = D_8008FE7C;
                func_15143134(&d, &a, *(s32 *)(*(u8 **)p + 0x1D4) + 0x640);
            }
            sp.u51 = 0x29;
            sp.u3C = 0xE03;
            sp.u34 = 0x200005;
            sp.u4C = 0xB0;
            sp.u4D = 0xA0;
            sp.u4E = 0x2A;
            sp.u48 = 0x40;
            sp.u49 = 0xB;
            sp.u4A = 0x6A;
            sp.u38 = 0;
            sp.u40 = 0;
            sp.u44 = 0;
            sp.u4B = 0xFF;
            sp.u50 = 0xFF;
            sp.u94 = 3;
            sp.u95 = 3;
            sp.u88 = 0.0f;
            sp.u8C = 0xE05;
            sp.u96 = 0xA;
            sp.u97 = -1;
            sp.u52 = 0x1E;
            sp.u54 = 8;
            sp.u56 = 0x32;
            sp.u58 = 1.02700007f;
            scale = 0.924f;
            do {
                s32 base;
                s16 ang;

                sp.u3E = (func_150ADA20() % 41U) + 0x1E;
                sp.u4F = (func_150ADA20() % 156U) + 0x64;
                sp.u5C = sp.u60 = (func_150ADA68() * 104.0f) + 199.0f;
                if (func_150ADA20() & 1) {
                    q = &b;
                } else {
                    q = &a;
                }
                base = ((*(u16 *)(*(u8 **)p + 0x7A) >> 8) + 0x40) & 0xFF;
                ang = ((func_150ADA20() % 100U) + base) - 0x31;
                func_15143874(ang, 36.0f, &sp.u64[0], &sp.u64[2]);
                sp.u64[1] = 0.0f;
                sp.u64[0] += q->x;
                sp.u64[1] = q->y;
                sp.u64[2] += q->z;
                func_15143874(ang, ((func_150ADA68() * 1497.0f) + 995.0f) * 0.01f, &sp.u7C[0], &sp.u7C[2]);
                sp.u7C[1] = 0.0f;
                if (!p && !p && !p) { // fakematch: basic-block boundary (remote permuter)
                }
                sp.u8C &= ~0xC0;
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x40;
                }
                if (func_150ADA20() & 1) {
                    sp.u8C |= 0x80;
                }
                obj = func_151308E4(&sp, 1, 4, arg0[0xC], arg0[1]);
                if (obj != 0) {
                    memcpy(obj + 0xA8, &scale, 4);
                }
                *(f32 *)(p + 8) -= 1.0f;
            } while (*(f32 *)(p + 8) > 1.0f);
            return;
        }
        while (*(f32 *)(p + 8) > 1.0f) {
            *(f32 *)(p + 8) -= 1.0f;
        }
    }
}

void func_151B255C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x2D) {
        if (*(s32 *)(arg1 + 0) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 0);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
        goto dummy_label; dummy_label: ; // fakematch: b + target-copied lw ra
    } else if (arg2 == 0) {
        temp_v1 = *(s32 *)(arg1 + 0);
        if (temp_v1 == *(s32 *)(temp_v0 + 0) || *(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4)) {
            func_1516972C(arg0);
        }
    }
}
