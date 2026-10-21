#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151D1990(u8 *);


struct260 *func_151CD2C0(u8 *arg0, u8 arg1, s32 arg2) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        s32 unk4;
        s32 unk8;
        u8 unkC;
        u8 padD[3];
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = *(s32 *)(arg0 + 0x18);
    tmp.unk8 = 0;
    tmp.unkC = *(s32 *)(arg0 + 0x1C);
    temp_v0 = func_15149130(0x12C, -1, -1, -1, 0, 0x1E, 0x10, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
    return temp_v0;
}

void func_151CD90C(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x17);
    }
}

void func_151CD944(s32 arg0) {
    s32 tmp;
    if ((arg0 >= 0) && (arg0 < 4)) {
        tmp = arg0;
        func_151494E0(&tmp, 0x18);
    }
}

s32 func_151CDA70(s32, u8, s32, u8, u8);
void func_151CEA2C(u8 *);
void func_151CD97C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0x17) {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
        if ((*(s32 *)(v + 4) == *arg1) && (*(s32 *)(v + 8) == 0)) {
            *(s32 *)(v + 8) = func_151CDA70(*(s32 *)v, v[0xC], *(s32 *)(v + 4), arg0[0xC], arg0[1]);
            (*(u8 **)v)[0x14] = 0;
        }
    } else if (arg2 == 0x18) {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
        if (*(s32 *)(v + 4) == *arg1) {
            u8 *p = *(u8 **)(v + 8);
            if (p != NULL) { func_151CEA2C(p); }
        }
    } else if (arg2 == 0x23) {
        if ((*(s32 *)(v + 4) == *arg1)) {
            *(s32 *)(v + 8) = 0;
            (*(u8 **)v)[0x14] = 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDA70.s")

typedef struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; u8 pad10[0xC]; } S1C;
typedef struct { s32 x, y, z; } V3i;
s32 func_151CDC24(u8 *arg0) {
    s32 i;
    u8 *p;
    S1C *e;
    S1C *base;
    f32 v;
    p = *(u8 **)(arg0 + 0x98);
    base = *(S1C **)(arg0 + 0x94);
    if ((*(s8 *)(arg0 + 0x2C) < 2) && (*(u16 *)(arg0 + 0x1E) & 8)) {
        return 0;
    }
    i = *(s8 *)(arg0 + 0x2E);
    while (i != *(s8 *)(arg0 + 0x2D)) {
        i--;
        if (i < 0) {
            i = *(u8 *)(arg0 + 0x25) - 1;
        }
        e = &base[i];
                e->unk4 += (e->unkC * D_800BE9A4) + (-0.12750001f * (D_800BE9A4 * D_800BE9A4));
        e->unkC += -0.25500003f * D_800BE9A4;
        if (e->unk4 < *(f32 *)(p + 0x44)) {
            while (i != *(s8 *)(arg0 + 0x2D)) {
                *(s8 *)(arg0 + 0x2D) += 1;
                if (*(u8 *)(arg0 + 0x25) == *(s8 *)(arg0 + 0x2D)) {
                    *(s8 *)(arg0 + 0x2D) = 0;
                }
                *(s8 *)(arg0 + 0x2C) -= 1;
            }
            base[*(s8 *)(arg0 + 0x2D)].unk4 = *(f32 *)(p + 0x44);
        }
    }
    *(V3i *)(arg0 + 0x54) = *(V3i *)(arg0 + 0x10);
    return 1;
}

#ifdef NON_MATCHING
s32 func_151CDD6C(u8 *arg0) {
    struct {
        f32 u9C;
        f32 uA0;
        u8 padA4[0x4];
        f32 uA8;
        f32 uAC;
        f32 uB0;
    } sp;
    f32 sp90;
    f32 sp84;
    u8 *sp6C;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f28;
    f32 temp_f30;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s32 temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    (*(f32 *)((u8 *)temp_s1 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 8)) + ((*(f32 *)((u8 *)temp_s1 + 0x10)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((*(f32 *)((u8 *)temp_s1 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s1 + 8)) = func_15144B68((*(f32 *)((u8 *)temp_s1 + 8)));
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = func_15144B68((*(f32 *)((u8 *)temp_s1 + 0xC)));
    (*(f32 *)((u8 *)temp_s1 + 0x2C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x2C)) + ((*(f32 *)((u8 *)temp_s1 + 0x30)) * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s1 + 0x2C)) = func_15144B68((*(f32 *)((u8 *)temp_s1 + 0x2C)));
    (*(f32 *)((u8 *)temp_s1 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x40)) + (0.273013f * D_800BE9A4));
    (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) + ((10220.0f + (func_150ADA68() * 9434.0f)) * 0.01f * D_800BE9A4));
    if ((*(f32 *)((u8 *)temp_s1 + 0x3C)) >= 16384.0f) {
        do {
            (*(f32 *)((u8 *)temp_s1 + 0x3C)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x3C)) - 16384.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x3C)) >= 16384.0f);
    }
    temp_f0 = (*(f32 *)((u8 *)temp_s1 + 0x40));
    if (temp_f0 > 1.0f) {
        temp_f28 = 1.0f / temp_f0;
        temp_v0 = temp_s1 + 0x18;
        temp_f16 = (*(f32 *)((u8 *)temp_s1 + 0x20)) + D_800BE9A4;
        sp.uAC = -(temp_f16 * temp_f28);
        (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
        (*(s32 *)((u8 *)(&sp.u9C) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
        sp.uB0 = temp_f16;
        sp6C = temp_v0;
        temp_f30 = ((sinf((*(f32 *)((u8 *)temp_s1 + 8))) * (*(f32 *)((u8 *)temp_s1 + 0))) + (*(f32 *)((u8 *)arg0 + 0x10))) - (*(f32 *)((u8 *)temp_s1 + 0x18));
        sp.uA8 = ((sinf((*(f32 *)((u8 *)temp_s1 + 0xC))) * (*(f32 *)((u8 *)temp_s1 + 4))) + (*(f32 *)((u8 *)arg0 + 0x18))) - (*(f32 *)((u8 *)temp_s1 + 0x1C));
        var_f12 = (*(f32 *)((u8 *)temp_s1 + 0x34));
        var_f16 = temp_f16;
        temp_f8 = ((sinf((*(f32 *)((u8 *)temp_s1 + 0x2C))) * (*(f32 *)((u8 *)temp_s1 + 0x28))) + (*(f32 *)((u8 *)temp_s1 + 0x24))) - var_f12;
        sp90 = temp_f8;
        var_f14 = (*(f32 *)((u8 *)temp_s1 + 0x3C));
        sp84 = var_f14 - (*(f32 *)((u8 *)temp_s1 + 0x38));
        if ((*(f32 *)((u8 *)temp_s1 + 0x40)) > 1.0f) {
            do {
                temp_v0_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + temp_s3;
                (*(f32 *)((u8 *)temp_v0_2 + 0)) = sp.u9C;
                (*(f32 *)((u8 *)temp_v0_2 + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
                (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = -3.772f;
                (*(f32 *)((u8 *)temp_v0_2 + 0x10)) = var_f12;
                (*(s16 *)((u8 *)temp_v0_2 + 0x14)) = 0xFF;
                (*(f32 *)((u8 *)temp_v0_2 + 0x18)) = var_f14;
                (*(f32 *)((u8 *)temp_v0_2 + 8)) = sp.uA0;
                var_f12 += temp_f8 * temp_f28;
                var_f14 += sp84 * temp_f28;
                (*(f32 *)((u8 *)temp_v0_2 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0_2 + 4)) + ((-3.772f * D_800BE9A4) + (-0.12750001f * (D_800BE9A4 * D_800BE9A4))));
                (*(f32 *)((u8 *)temp_v0_2 + 0xC)) = (f32) (-3.772f + (-0.25500003f * D_800BE9A4));
                (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
                }
                temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
                if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                }
                sp.u9C += temp_f30 * temp_f28;
                var_f16 += sp.uAC;
                sp.uA0 += sp.uA8 * temp_f28;
                (*(f32 *)((u8 *)temp_s1 + 0x40)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x40)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s1 + 0x40)) > 1.0f);
        }
        (*(f32 *)((u8 *)sp6C + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u9C) + 0));
        (*(s32 *)((u8 *)sp6C + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u9C) + 4));
        (*(f32 *)((u8 *)temp_s1 + 0x34)) = var_f12;
        (*(f32 *)((u8 *)temp_s1 + 0x38)) = var_f14;
        (*(f32 *)((u8 *)temp_s1 + 0x20)) = var_f16;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDD6C.s")
#endif
typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[0xC];
    s16 unk14;
    u8 pad16[6];
} NodeCE144;

s32 func_151CE144(u8 *arg0) {
    NodeCE144 *nodes;
    NodeCE144 *start;
    NodeCE144 *n;
    s32 prev;
    s32 i;
    f32 len;
    f32 inv;
    f32 d;
    f32 k;

    nodes = *(NodeCE144 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) <= 0) {
        return 1;
    }
    {
        prev = *(s8 *)(arg0 + 0x2E) - 1;
        if (prev < 0) {
            prev = arg0[0x25] - 1;
        }
        start = &nodes[*(s8 *)(arg0 + 0x2D)];
        len = fabsf((prev + nodes)->unk4 - start->unk4);
        if (len == 0.0f) {
            return 1;
        }
        {
            inv = 1.0f / len;
            k = inv * 10.0f;
            i = *(s8 *)(arg0 + 0x2D);
            do {
                n = &nodes[i];
                d = n->unk4 - start->unk4;
                n->unk14 = 0xFF;
                if (d < len * 0.19700001f) {
                    n->unk14 = (u8)(((0, d) * (inv * 5.076142f)) * 255.0f); // fakematch: comma gives the mul.s d, (inv * k) operand order
                } else if (len - len * 0.1f < d) {
                    n->unk14 = (u8)((len - d) * k * 255.0f);
                }
                i++;
                if (i >= arg0[0x25]) {
                    i = 0;
                }
            } while (i != *(s8 *)(arg0 + 0x2E));
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE3D0.s")

void func_151CEA2C(u8 *arg0) {
    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= ~2;
    *(u16 *)(arg0 + 0x1E) |= 8;
}

void func_151CEA4C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E64(arg0);
}

void func_151CEA8C(u8 *arg0) {
    s32 tmp;
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    tmp = *(s32 *)(temp_v0 + 0x48);
    func_151494E0(&tmp, 0x23);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
s32 func_1505D024(s32, s32, s32, s32);
void func_1515C710(u8 *, f32 *, f32 *, f32 *);
u8 *func_151CEBE4(s32);

void func_151CEACC(s32 arg0, u8 *arg1) {
    struct {
        f32 u3C;
        s32 u40;
        s32 u44;
        s32 u48;
    } sp;
    u8 *sp38;
    s32 var_v0;
    u8 *temp_v0;

    temp_v0 = func_151CEBE4((*(s32 *)((u8 *)arg1 + 0x18)));
    if (temp_v0 != NULL) {
        sp38 = temp_v0;
        func_1515C710(arg0, &sp.u44, &sp.u40, &sp.u3C);
        if ((*(u16 *)((u8 *)sp38 + 0x1E)) & 8) {
            if ((*(s8 *)((u8 *)sp38 + 0x2C)) > 0) {
                var_v0 = (*(s8 *)((u8 *)sp38 + 0x2E)) - 1;
                if (var_v0 < 0) {
                    var_v0 = (*(u8 *)((u8 *)sp38 + 0x25)) - 1;
                }
                if ((sp.u48 - sp.u3C) <= (*(f32 *)((u8 *)(((*(s32 *)((u8 *)sp38 + 0x94)) + (var_v0 * 0x1C))) + 4))) {
                    func_1505D024(arg0, 0x60019, 0, -1);
                }
            }
        } else if (((*(s8 *)((u8 *)sp38 + 0x2C)) > 0) && ((*(f32 *)((u8 *)(((*(s32 *)((u8 *)sp38 + 0x94)) + ((*(s8 *)((u8 *)sp38 + 0x2D)) * 0x1C))) + 4)) <= (sp.u48 + sp.u3C))) {
            func_1505D024(arg0, 0x60019, 0, -1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEACC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEBE4.s")

#ifdef NON_MATCHING
s32 func_150455FC(u8 *, f32, u8 *);
s32 func_151432BC(s32, s32 *, s32 *, s32 *, f32 *);

void func_151CEC80(u8 *arg0) {
    struct {
        s32 uA0;
        s8 uA4;
        s8 uA5;
        s16 uA6;
        s16 uA8;
        u8 padAA[0x2];
        s32 uAC;
        s32 uB0;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        f32 uB8;
        f32 uBC;
        s32 uC0;
        f32 uC4;
        s32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        s32 uE4;
        s8 uE8;
        s8 uE9;
        s8 uEA;
        s8 uEB;
        u8 * uEC;
    } sp;
    s16 var_v1;
    s32 temp_t7;
    s32 var_v0;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + ((5624.0f + (func_150ADA68() * 3973.0f)) * 1e-10f * D_800BE9A4 * (*(f32 *)((u8 *)temp_s0 + 4))));
    if ((*(f32 *)((u8 *)temp_s0 + 8)) > 1.0f) {
        var_v0 = 0;
        var_v1 = 0;
        if (D_80082FA0 >= 0) {
            do {
                temp_t7 = 1 << var_v0;
                var_v0 += 1;
                var_v1 |= temp_t7;
            } while (D_80082FA0 >= var_v0);
        }
        if (!((*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 0xC))) + 2)) & var_v1)) {
            do {
                (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s0 + 8)) > 1.0f);
            return;
        }
        sp.uA4 = 0x6A;
        sp.uA5 = 0;
        sp.uA6 = 0x2203;
        sp.uA8 = 0x64;
        sp.uAC = 0;
        sp.uB0 = 0;
        sp.uB4 = 0xFF;
        sp.uB5 = 0xFF;
        sp.uB6 = 0xFF;
        sp.uB7 = 0xFF;
        sp.uD0 = 0.0f;
        sp.uD4 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 1.0f;
        sp.uE4 = 0x01CC0061;
        sp.uE9 = 0xFF;
        sp.uEA = 0;
        sp.uEB = 7;
        sp.uEC = (*(u8 **)((u8 *)temp_s0 + 0xC));
        do {
            sp.uCC = ((func_150ADA68() * 409.0f) + -1308.0f) * 0.001f;
            sp.uD8 = ((func_150ADA68() * 121.0f) + 23.0f) * 0.001f;
            sp.uB8 = (func_150ADA68() * 25.0f) + 10.0f;
            sp.uBC = (func_150ADA68() * 60.0f) + 60.0f;
            func_151432BC((*(s32 *)((u8 *)temp_s0 + 0)), &sp.uC0, &sp.uC8, &sp.uA0, &sp.uC4);
            if (func_150455FC(&sp.uC0, sp.uA0, temp_s0 + 0x10) != 0) {
                sp.uC4 = (*(f32 *)((u8 *)temp_s0 + 0x10));
                sp.uE8 = (func_150ADA20() % 101U) + 0x9B;
                func_1513D2F0(&sp.uA4, (s32) ((u8 *)&D_800A4AA0), 0x1CU, 0U, 0U, 0x22U, 0U, 0, 0, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            }
            (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 8)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEC80.s")
#endif
#ifdef NON_MATCHING
s32 func_151CEFD0(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;

    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x40));
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x44));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) (temp_f2 + (temp_f12 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((temp_f2 + (0.5f * temp_f12 * D_800BE9A4)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x50)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x50)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x50)) > 1.0f) {
        (*(f32 *)((u8 *)arg0 + 0x50)) = 1.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEFD0.s")
#endif
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} struct_151CF1C0;

s32 func_151CF1C0(struct_151CF1C0 *arg0, u8 *arg1, u8 *arg2);
extern f32 D_800AB3E8;
typedef struct {
    u8 *obj;
    u8 b48;
    u8 *other;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    s8 f60;
    f32 f64;
    f32 f68;
    struct_151CF1C0 pos;
    s16 u78;
    s16 u7A;
    s32 u7C;
    s8 u80;
    s8 u81;
    s32 u84;
} SpawnCF05C;

u8 *func_151CF05C(u8 *arg0, u8 *arg1, u8 arg2, u8 arg3, s32 arg4) {
    SpawnCF05C sp;
    u8 *ret;
    s8 fl;

    sp.u81 = 0x19;
    sp.u78 = 0x12C;
    sp.u7A = 0x10;
    sp.u7C = 0x11;
    sp.u80 = 3;
    sp.obj = arg0;
    if (arg0 != NULL) {
        sp.b48 = arg0[0x3B];
    } else {
        sp.b48 = 0;
    }
    sp.f54 = 1.0f;
    sp.f5C = 1.0f;
    sp.other = arg1;
    sp.f50 = 0.0f;
    sp.f58 = 0.0f;
    if (arg2) {
        fl = 2;
    } else {
        fl = 0;
    }
    sp.f60 = fl;
    sp.f64 = func_150ADA68() * 400.0f + 400.0f;
    sp.f68 = 2.0f * func_150ADA68() * D_800AB3E8;
    if (func_151CF1C0(&sp.pos, arg0, arg1) == 0) {
        sp.pos.x = 0.0f;
        sp.pos.y = 0.0f;
        sp.pos.z = 0.0f;
    }
    ret = func_15147FF0(&sp.pos, 0x28, 0x28, 0, 0xF, 0xF, 0, 0, 0, arg3, arg4);
    if (ret != NULL) {
        memcpy(*(void **)(ret + 0x98), &sp, 0x28);
    }
    return ret;
}


s32 func_151CF1C0(struct_151CF1C0 *arg0, u8 *arg1, u8 *arg2) {
    if (arg2 != NULL) {
        *arg0 = *(struct_151CF1C0 *)(arg2 + 0x40);
    } else {
        arg0->x = ((struct_151CF1C0 *)(arg1 + 0x14))->x;
        arg0->y = ((struct_151CF1C0 *)(arg1 + 0x14))->y;
        arg0->z = ((struct_151CF1C0 *)(arg1 + 0x14))->z;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF204.s")

#ifdef NON_MATCHING
s32 func_151CF6D0(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f20;
    f32 var_f22;
    f32 var_f26;
    s32 temp_a1;
    s32 temp_s3;
    s32 var_a0;
    s8 var_s1;
    u8 *temp_s2;
    u8 *temp_s4;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f26 = 0.0f;
        var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_a0 < 0) {
            var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_v1 = (temp_a1 * 0x28) + temp_s3;
                temp_f16 = (*(f32 *)((u8 *)temp_v1 + 0xC));
                var_f26 += temp_f16;
                if ((*(f32 *)((u8 *)temp_s4 + 0x20)) < var_f26) {
                    if (temp_f16 != 0.0f) {
                        temp_f14 = (var_f26 - (*(f32 *)((u8 *)temp_s4 + 0x20))) / temp_f16;
                        temp_v0 = (var_a0 * 0x28) + temp_s3;
                        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0));
                        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
                        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
                        (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) (temp_f0 - ((temp_f0 - (*(f32 *)((u8 *)temp_v1 + 0))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) (temp_f2 - ((temp_f2 - (*(f32 *)((u8 *)temp_v1 + 4))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (temp_f12 - ((temp_f12 - (*(f32 *)((u8 *)temp_v1 + 8))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0xC)) * (1.0f - temp_f14));
                    }
                    if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        do {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                                (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                            }
                            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                        } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                    }
                    var_f26 = (*(f32 *)((u8 *)temp_s4 + 0x20));
                }
            } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f20 = 0.0f;
        var_s1 = (*(s8 *)((u8 *)arg0 + 0x2E));
        var_f22 = (*(f32 *)((u8 *)temp_s4 + 0x24));
        do {
            var_s1 -= 1;
            if (var_s1 < 0) {
                var_s1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_s2 = (var_s1 * 0x28) + temp_s3;
            temp_f2_2 = (*(f32 *)((u8 *)temp_s2 + 0xC));
            (*(f32 *)((u8 *)temp_s2 + 0x14)) = (f32) (sinf(var_f22) * var_f20);
            var_f20 += temp_f2_2 * 0.037499998f;
            var_f22 += temp_f2_2 * 0.0122f;
        } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    (*(f32 *)((u8 *)temp_s4 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 0x24)) + (-0.70900005f * D_800BE9A4));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF6D0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF930.s")

void func_151CFDF4(u8 *arg0, s32 arg1, u8 arg2) {
    s32 *temp_t7;
    s32 *sp24;

    temp_t7 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp24 = temp_t7;
    if (*temp_t7 != 0) {
        func_15169850(arg1, arg2, (s32) temp_t7, (s32) temp_t7 + 4, (s32) arg0);
    }
}

typedef struct { f32 x, y, z; } Vec3CFE48;
f32 func_15144AA8(s32 arg0);
s32 func_15046F70(Vec3CFE48 *, u16, f32, f32 *);
extern f32 D_800D9C80;

void func_151CFE48(s32 arg0, f32 arg1, f32 arg2) {
    u8 *p;
    Vec3CFE48 pos;
    f32 *base;
    f32 a;
    f32 angle;
    f32 dist;
    struct {
        Vec3CFE48 unk0;
        f32 unkC;
    } tmp;
    struct260 *temp_v0;

    p = *(u8 **)((u8 *)arg0 + 0x318);
    if (p != NULL && func_150ADA68() < 0.22200002f) {
        base = func_15144B34(p[0x23D]);
        a = func_15144AA8(p[0x23D]);
        angle = (func_150ADA68() * 80.0f + (a - 40.0f)) * 0.017453292f;
        dist = func_150ADA68() * 2000.0f;
        pos.x = base[0] - sinf(angle) * dist;
        pos.y = arg1;
        pos.z = base[2] - cosf(angle) * dist;
        if (func_15046F70(&pos, 0, arg2, &D_800D9C80) != 0) {
            pos.y = D_800D9C80;
            tmp.unk0 = pos;
            tmp.unkC = 0.0f;
            temp_v0 = func_15149130(func_150ADA20() % 131U + 51, -1, 0x20, -1, 1, 0, 0x10, 0xFF, 1);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CFFFC.s")

void func_151D0024(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x18);
}

void func_151D0058(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[1];
        s16 unk6;
        f32 unk8;
        u8 unkC;
        u8 unkD;
        u8 padE[2];
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = (*(f32 *)(arg0 + 0x150) + *(f32 *)(arg0 + 0x14C)) * 0.5f;
    tmp.unkD = arg1;
    tmp.unkC = (func_150ADA20() % 56U) + 200;
    tmp.unk6 = *(u16 *)(arg0 + 0x84);
    temp_v0 = func_15149130(0x12C, -1, 0x61, 4, 0, 0x31, 0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

void func_151D06D8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D06FC.s")

/* NEAR 2 from func_150D5E7C: sib -li at,#; sib -beq a2,at,T */
void func_151D0EA0(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0 || arg2 == 24) {
        s32 t = *(s32 *)arg1;
        if (t == *(s32 *)v || v[4] == arg1[4]) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D09A8.s")

void func_151D1488(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0xA8) != 0) { func_1516972C(*(struct102 **)(p + 0xA8)); } }

void func_151D14B8(void *arg0) {
    func_151D1488(arg0);
    func_15131CAC(arg0);
}

void func_151D14E4(void *arg0) {
    func_151D1488(arg0);
    func_15131CCC(arg0);
}

typedef struct {
    f32 x, y, z;
} Vec3_151D1510;
extern s32 (*D_8008FFD0[])(u8 *, Vec3_151D1510 *);

void func_151D1510(u8 *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        s32 unk8;
        Vec3_151D1510 unkC;
        Vec3_151D1510 unk18;
        Vec3_151D1510 unk24;
        f32 unk30;
        u8 unk34;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0;
    if (D_8008FFD0[arg1](arg0, &tmp.unk18) == 0) {
        tmp.unk18 = *(Vec3_151D1510 *)D_800A5860;
    }
    tmp.unkC = tmp.unk18;
    tmp.unk24 = *(Vec3_151D1510 *)D_800A5860;
    tmp.unk30 = 0.0f;
    tmp.unk34 = arg1;
    temp_v0 = func_15149130(300, -1, 0x5F, -1, 0, 0x48, 0x38, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x38);
    }
}

s32 func_151D1624(f32 *arg0, f32 *arg1) {
    arg1[0] = arg0[0x14 / 4];
    arg1[1] = arg0[0x180 / 4] + 8.0f;
    arg1[2] = arg0[0x1C / 4];
    return 1;
}

void func_151D1654(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 0);
}

void func_151D1674(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1694.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D16E8.s")

void func_151D18D8(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_151D1918(void *arg0) {
    func_151D1990(arg0);
}

void func_151D1938(void *arg0) {
    func_151D1918(arg0);
    func_1514933C(arg0);
}

void func_151D1964(void *arg0) {
    func_151D1918(arg0);
    func_15149368(arg0);
}

void func_151D1990(u8 *arg0) {
    u8 *v;
    s32 *q;
    v = arg0 + 0x28;
    if (*(s32 *)(arg0 + 0x30) != 0) {
        q = *(s32 **)(*(u8 **)(v + 8) + 0x98);
        *(s8 *)(*(u8 **)(v + 8) + 0x30) = 0;
        *(u16 *)(*(u8 **)(v + 8) + 0x1E) &= 0xFFFD;
        *(u16 *)(*(u8 **)(v + 8) + 0x1E) |= 8;
        *(u16 *)(*(u8 **)(v + 8) + 0x1E) |= 1;
        *(s16 *)(*(u8 **)(v + 8) + 0x1C) = 0x28;
        *q = 0;
        *(u8 **)(v + 8) = NULL;
    }
}

#ifdef NON_MATCHING
void func_151D19F8(u8 *arg0) {
    struct {
        s32 u50;
        u8 pad54[0x8];
        s16 u5C;
        s16 u5E;
        s32 u60;
        s8 u64;
        s8 u65;
        u8 pad66[0x2];
        s32 u68;
        u8 * u6C;
        f32 u70;
        s8 u74;
        u8 pad75[0x3];
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
    } sp;
    u8 *sp44;
    u8 *temp_v0;
    u8 *temp_v1;

    sp.u6C = arg0;
    sp.u74 = 0xFF;
    sp.u70 = 0.0f;
    temp_v1 = arg0 + 0x28;
    if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x28))) + 4)) == 0x25) {
        sp.u78 = 800.0f;
        sp.u7C = 36.0f;
        sp.u80 = 50.0f;
        sp.u84 = 200.0f;
    } else {
        if (D_80082FA0 > 0) {
            sp.u78 = 260.0f;
        } else {
            sp.u78 = 500.0f;
        }
        sp.u7C = 40.0f;
        sp.u80 = 40.0f;
        sp.u84 = 180.0f;
    }
    sp.u65 = 0x19;
    sp.u88 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_v1 + 0))) + 0x14C));
    (*(s32 *)((u8 *)(&sp.u50) + 0)) = (s32) (*(s32 *)((u8 *)temp_v1 + 0x18));
    (*(s32 *)((u8 *)(&sp.u50) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1 + 0x1C));
    (*(s32 *)((u8 *)(&sp.u50) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1 + 0x20));
    sp.u5C = 0x12C;
    sp.u5E = 0x36;
    sp.u60 = 0x13;
    sp.u64 = 6;
    sp.u68 = 0;
    sp44 = temp_v1;
    temp_v0 = func_15147FF0(&sp.u50, 0x20, 0x28, 0, 0x11, 0x12, 0, 0, 0, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x98)), &sp.u6C, 0x20);
        (*(u8 **)((u8 *)sp44 + 8)) = temp_v0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D19F8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1B80.s")

#ifdef NON_MATCHING
s32 func_151D1F2C(u8 *arg0) {
    f32 sp3C;
    f32 sp38;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f26;
    f32 var_f2;
    s32 temp_a1_2;
    s32 temp_v1;
    s32 var_a2;
    s8 var_a1;
    u16 temp_v1_2;
    u8 *temp_a1;
    u8 *temp_a1_3;
    u8 *temp_a2;
    u8 *temp_t0;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_a1 = (*(u8 **)((u8 *)temp_v0 + 0));
    if (temp_a1 != NULL) {
        (*(f32 *)((u8 *)temp_v0 + 0x1C)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)temp_a1 + 0x28))) + 0x14C));
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f26 = 0.0f;
        var_a2 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_a2 < 0) {
            var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
            do {
                temp_a1_2 = var_a2;
                var_a2 -= 1;
                if (var_a2 < 0) {
                    var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_t0 = (temp_a1_2 * 0x28) + temp_v1;
                temp_f16 = (*(f32 *)((u8 *)temp_t0 + 0xC));
                var_f26 += temp_f16;
                if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < var_f26) {
                    if (temp_f16 != 0.0f) {
                        temp_f14 = (var_f26 - (*(f32 *)((u8 *)temp_v0 + 0xC))) / temp_f16;
                        temp_a1_3 = (var_a2 * 0x28) + temp_v1;
                        temp_f0 = (*(f32 *)((u8 *)temp_a1_3 + 0));
                        temp_f2 = (*(f32 *)((u8 *)temp_a1_3 + 4));
                        temp_f12 = (*(f32 *)((u8 *)temp_a1_3 + 8));
                        (*(f32 *)((u8 *)temp_a1_3 + 0)) = (f32) (temp_f0 - ((temp_f0 - (*(f32 *)((u8 *)temp_t0 + 0))) * temp_f14));
                        (*(f32 *)((u8 *)temp_a1_3 + 4)) = (f32) (temp_f2 - ((temp_f2 - (*(f32 *)((u8 *)temp_t0 + 4))) * temp_f14));
                        (*(f32 *)((u8 *)temp_a1_3 + 8)) = (f32) (temp_f12 - ((temp_f12 - (*(f32 *)((u8 *)temp_t0 + 8))) * temp_f14));
                        (*(f32 *)((u8 *)temp_t0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_t0 + 0xC)) * (1.0f - temp_f14));
                    }
                    if (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        do {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                                (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                            }
                            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                        } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                    }
                    var_f26 = (*(f32 *)((u8 *)temp_v0 + 0xC));
                }
            } while (var_a2 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
        if (var_f26 != 0.0f) {
            var_f0 = 1.0f / var_f26;
        } else {
            var_f0 = 0.0f;
        }
        sp38 = var_f0;
        sp3C = var_f26;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_a1 = (*(s8 *)((u8 *)arg0 + 0x2E));
        var_f2 = sp3C;
        do {
            var_a1 -= 1;
            if (var_a1 < 0) {
                var_a1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_a2 = (var_a1 * 0x28) + temp_v1;
            (*(f32 *)((u8 *)temp_a2 + 0x1C)) = (f32) (((*(f32 *)((u8 *)temp_v0 + 0x10)) * (*(f32 *)((u8 *)temp_v0 + 0x1C))) + (var_f2 * ((*(f32 *)((u8 *)temp_v0 + 0x14)) * (*(f32 *)((u8 *)temp_v0 + 0x1C)) * sp38)));
            (*(s8 *)((u8 *)temp_a2 + 0x14)) = (s8) (u32) (var_f2 * ((*(f32 *)((u8 *)temp_v0 + 0x18)) * sp38));
            var_f2 -= (*(f32 *)((u8 *)temp_a2 + 0xC));
        } while (var_a1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    temp_v1_2 = (*(u16 *)((u8 *)arg0 + 0x1E));
    if ((temp_v1_2 & 1) && (temp_v1_2 & 8)) {
        (*(s8 *)((u8 *)temp_v0 + 8)) = (s8) ((*(s16 *)((u8 *)arg0 + 0x1C)) * 6);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1F2C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D2248.s")

void func_151D27EC(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x30 / 4] = 0;
    }
}

void func_151D2808(void *arg0) {
    func_151D27EC(arg0);
    func_15147E64(arg0);
}

void func_151D2834(void *arg0) {
    func_151D27EC(arg0);
    func_15147E98(arg0);
}
