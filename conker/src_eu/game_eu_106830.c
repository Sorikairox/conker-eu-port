#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D9020(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[5];
    arg1[1] = arg0[6] + 20.0f;
    arg1[2] = arg0[7];
}

void func_150D904C(s32 arg0, s32 arg1) {
    f32 sp34[3];
    f32 sp28[3];

    func_15145740(arg0, (s32)sp34, (s32)sp28, arg1, D_800BE616 ? D_800A0F10 : D_800A0F14);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D9098.s")

extern f32 D_800A0F1C;
extern f32 D_800A0F20;

void func_150D9304(f32 *arg0, f32 *arg1, f32 arg2) {
    vertex sp4 = *(vertex *)arg1;

    arg1[1] += D_800A0F1C * arg2;
    arg0[0] += sp4.x * arg2;
    arg0[1] += sp4.y * arg2 + D_800A0F20 * arg2 * arg2;
    arg0[2] += sp4.z * arg2;
}

void func_150D939C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
    *(u16 *)(arg0 + 0x1E) |= 1;
    *(u16 *)(arg0 + 0x1C) = 0x28;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D93CC.s")

#ifdef NON_MATCHING
extern f32 D_800A0F24;
extern f32 D_800A0F28;
extern f32 D_800A0F2C;
extern f32 D_800A0F34;
s32 func_150D952C(u8 *arg0) {
    struct {
        f32 uAC;
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        u8 padE0[0xC];
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
    } sp;
    u8 *sp88;
    u8 *sp84;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp60;
    f32 *temp_a0;
    f32 *temp_s2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f20;
    f32 var_f2;
    s32 temp_s5;
    s8 temp_v1_2;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s5 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_s2 = (*(f32 **)((u8 *)temp_s1 + 0));
    if (((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x78)) != 3) || ((s32) (*(u8 *)((u8 *)temp_s2 + 0x1CA)) <= 0)) {
        func_150D939C(arg0);
    }
    if (((*(s32 *)((u8 *)temp_s2 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s1 + 4)) != (*(u8 *)((u8 *)temp_s2 + 0x3B)))) {
        return 0;
    }
    func_150D9020(temp_s2, &sp.uF8);
    func_150D904C((s32) temp_s2, (s32) &sp.uEC);
    temp_v1 = temp_s1 + 0x20;
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)(&sp.uF8) + 0));
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 4));
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.uF8) + 8));
    if ((*(u8 *)((u8 *)temp_s1 + 0x4C)) & 1) {
        if ((*(u16 *)((u8 *)((*(u8 **)((u8 *)temp_s2 + 0x31C))) + 0x8A)) & 0x2000) {
            var_f0 = D_800A0F24;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) + (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) > D_800A0F24) {
                goto block_11;
            }
        } else {
            var_f0 = D_800A0F2C;
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) - (D_800A0F28 * D_800BE9A4));
            if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) < D_800A0F2C) {
block_11:
                (*(f32 *)((u8 *)temp_s1 + 0x3C)) = var_f0;
            }
        }
    }
    temp_v0 = temp_s1 + 0x14;
    (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) + (D_800A0F34 * D_800BE9A4));
    temp_f2 = (*(f32 *)((u8 *)temp_s1 + 0x34));
    if (temp_f2 > 1.0f) {
        (*(f32 *)((u8 *)(&sp.uB8) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
        var_f20 = (*(f32 *)((u8 *)temp_s1 + 0x2C)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.uB8) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        temp_f0 = 1.0f / temp_f2;
        (*(s32 *)((u8 *)(&sp.uB8) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (*(f32 *)((u8 *)temp_v1 + 0));
        (*(s32 *)((u8 *)(&sp.uAC) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1 + 4));
        (*(s32 *)((u8 *)(&sp.uAC) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1 + 8));
        var_f16 = var_f20 * temp_f0;
        temp_f4 = sp.u100 - (*(f32 *)((u8 *)temp_s1 + 0x1C));
        temp_f26 = (sp.uF8 - (*(f32 *)((u8 *)temp_s1 + 0x14))) * temp_f0;
        sp.uD8 = temp_f4;
        temp_f28 = (sp.uFC - (*(f32 *)((u8 *)temp_s1 + 0x18))) * temp_f0;
        temp_f6 = sp.uEC - (*(f32 *)((u8 *)temp_s1 + 0x20));
        sp.uC4 = temp_f6;
        sp60 = temp_f4;
        temp_f8 = sp.uF0 - (*(f32 *)((u8 *)temp_s1 + 0x24));
        sp.uC8 = temp_f8;
        sp84 = temp_v1;
        sp88 = temp_v0;
        temp_f10 = sp.uF4 - (*(f32 *)((u8 *)temp_s1 + 0x28));
        sp.uCC = temp_f10;
        var_f2 = temp_f6 * temp_f0;
        var_f12 = temp_f8 * temp_f0;
        var_f14 = temp_f10 * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x24) + temp_s5;
            (*(f32 *)((u8 *)temp_a0 + 0)) = (*(f32 *)((u8 *)(&sp.uB8) + 0));
            (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uAC);
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB0);
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x1C)) = 0xFF;
            (*(f32 *)((u8 *)temp_a0 + 0x20)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) * sp.uB4);
            sp.uDC = var_f16;
            sp70 = var_f14;
            sp74 = var_f12;
            sp78 = var_f2;
            func_150D9304(temp_a0, ((f32 *)((u8 *)temp_a0 + 0xC)), var_f20);
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f20 -= var_f16;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1_2 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1_2 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.uB8 += temp_f26;
            sp.uBC += temp_f28;
            sp.uC0 += temp_f4 * temp_f0;
            sp.uAC += var_f2;
            sp.uB0 += var_f12;
            sp.uB4 += var_f14;
            (*(f32 *)((u8 *)temp_s1 + 0x34)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x34)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x34)) > 1.0f);
        (*(f32 *)((u8 *)sp88 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uB8) + 0));
        (*(s32 *)((u8 *)sp88 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 4));
        (*(s32 *)((u8 *)sp88 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uB8) + 8));
        (*(f32 *)((u8 *)sp84 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.uAC) + 0));
        (*(s32 *)((u8 *)sp84 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 4));
        (*(s32 *)((u8 *)sp84 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uAC) + 8));
        (*(f32 *)((u8 *)temp_s1 + 0x2C)) = var_f20;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D952C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150D99AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DA1FC.s")

void func_150DAA04(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x30);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

void func_150DAA34(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E64(arg0);
}

void func_150DAA60(s32 arg0) {
    func_150DAA04(arg0);
    func_15147E98(arg0);
}

void func_150DAA8C(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0x44) {
        if ((u16)(*(s32 *)v == *(s32 *)arg1 || v[4] == arg1[4])) { // fakematch: permuter artifact (u16 cast of the condition)
            *(f32 *)(v + 0x3C) = *(f32 *)(arg1 + 8);
dummy_label: ; // fakematch: permuter artifact (unused label)
        }
    } else if (arg2 == 0) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || arg1[4] == v[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
            *(s32 *)v = *(s32 *)arg1;
            v[4] = arg1[8];
        }
    }
}

void func_150DAB6C(u8 *arg0, f32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = arg1;
    func_151482D4(&tmp, 0x44);
}

s32 func_15131D98(s32, s32, u8 *, s32);
void func_15131EC8(s32, s32, u8 *);

s32 func_150DABA8(s32 arg0, s32 arg1) {
    u8 *sp20;
    u8 *temp_a2;

    temp_a2 = arg0 + 0xA8;
    sp20 = temp_a2;
    func_15131D98(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131EC8(arg0 + 0x58, (*(s32 *)((u8 *)temp_a2 + 0xC)), temp_a2);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_106830/func_150DABFC.s")
