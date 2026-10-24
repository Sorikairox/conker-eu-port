#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800AB364[];
extern u8 D_800AB370[];
extern u8 D_800A4EA8[];
#endif

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

#ifdef NON_MATCHING
s32 func_151CDA70(s32, u8, s32, u8, s32);
#else
s32 func_151CDA70(s32, u8, s32, u8, u8);
#endif
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

#ifdef NON_MATCHING
// splash_effect_spawn: spawns a 300-frame effect object (kind 0x34 / 11 / 7 / 0x23) at the s16 point src[0..2]
// (y raised by src[4]) sized by src[3]; its 0x50-byte parameter block (sizes, rates, centre, owner arg2 / arg1)
// is copied to the object's data (+0x98). Returns the object (0 if none).
s32 func_151CDA70(s32 src_p, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s16 *src = (s16 *)src_p;
    struct {
        f32 size_x;     /* 0x00 */
        f32 size_y;     /* 0x04 */
        f32 u08;
        f32 u0C;
        f32 rate0;      /* 0x10 */
        f32 rate1;      /* 0x14 */
        f32 x;          /* 0x18 */
        f32 z;          /* 0x1C */
        f32 u20;
        f32 radius;     /* 0x24 */
        f32 grow;       /* 0x28 */
        f32 u2C;
        f32 rate2;      /* 0x30 */
        f32 radius2;    /* 0x34 */
        f32 min0;       /* 0x38 */
        f32 min1;       /* 0x3C */
        f32 u40;
        f32 y;          /* 0x44 */
        s32 owner;      /* 0x48 */
        u8 owner_id;    /* 0x4C */
    } params;
    struct {
        f32 x, y, z;    /* 0x00 */
        s16 life;       /* 0x0C */
        s16 kind;       /* 0x0E */
        s32 type;       /* 0x10 */
        u8 u14;
        u8 u15;
        s32 u18;
    } rec;
    f32 size;
    u8 *obj;

    size = src[3];
    rec.u15 = 0x23;
    rec.x = src[0];
    rec.y = src[1] + src[4];
    rec.z = src[2];
    rec.life = 300;
    rec.kind = 0x34;
    rec.type = 11;
    params.radius = size * 0.875f;
    params.size_x = size * 0.125f;
    params.size_y = size * 0.125f;
    params.rate0 = 0.0300000012f;
    params.rate1 = 0.0400000028f;
    params.u08 = 0.0f;
    params.u0C = 0.0f;
    params.y = src[1];
    params.x = rec.x;
    params.z = rec.z;
    params.radius2 = params.radius;
    params.grow = size * 0.0625f;
    params.u2C = 0.0f;
    params.rate2 = 0.0550000034f;
    params.u40 = 0.0f;
    params.owner = arg2;
    params.min0 = -16384.0f;
    params.min1 = -16384.0f;
    params.u20 = 0.0f;
    params.owner_id = arg1;
    rec.u18 = 0;
    rec.u14 = 7;
    obj = func_15147FF0(&rec, 0x50, 0x1C, 9, 9, 9, 0, 0, 0, arg3, arg4);
    if (obj != NULL) {
        memcpy(*(void **)(obj + 0x98), &params, 0x50);
    }
    return (s32)obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CDA70.s")
#endif

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

#ifdef NON_MATCHING
s32 func_1513F4E4(s32, s32, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142E24(u8 *, struct_eu_80090F10 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *func_15142FBC(s32, s32, s32, s8 *);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800AB2C0;
extern s32 D_800D30BC;
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151CE3D0(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        u8 padA8[0xB];
        s8 uB3;
        u8 padB4[0x8];
        s16 * uBC;
    } sp;
    f32 *sp70;
    f32 *sp6C;
    s32 *temp_v1;
    f32 *var_a3;
    f32 *var_t0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s16 *temp_t2;
    s16 *temp_t2_2;
    s16 *temp_t6;
    s32 temp_s4;
    s32 temp_s6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_s2;
    s32 var_s4;
    u8 *temp_s3;
    u8 *temp_s3_2;
    u8 *var_a2;
    u8 *var_s0;
    u8 *var_s3;

    var_s3 = arg1;
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        func_151D6310(arg0 + 0x84, arg2, ((*(u8 *)((u8 *)arg0 + 0x25)) << 5) + 0xA0, &sp.uBC, 0);
        if (sp.uBC != NULL) {
            temp_s6 = (*(s32 *)((u8 *)arg0 + 0x94));
            sp.uB3 = 1;
            temp_v0 = *(s32 *) ((u8 *) &D_800AB2C0 + (*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x98))) + 0x4C)) * 4);
            temp_v1 = ((u8 *)&D_800A4EA8);
            var_s3 = func_15142FBC(func_15142B7C(func_1513F4E4(func_15142E24(var_s3, &D_80090F10[temp_v0], 0, 0, 0, 0, temp_v0, 0, 0, &sp.uB3, 3), 0x4E, &sp.uB3), 0x200005, 0x1F0600), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1 + 0x1C)) | (*(s32 *)((u8 *)temp_v1 + 0x18)), &sp.uB3);
            if ((*(u16 *)((u8 *)arg0 + 0x1E)) & 2) {
                var_s2 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
                if (var_s2 < 0) {
                    var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                (*(f32 *)((u8 *)(&sp.u90) + 0)) = (*(f32 *)((u8 *)arg0 + 0x10));
                (*(s32 *)((u8 *)(&sp.u90) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
                var_a2 = temp_s6 + (var_s2 * 0x1C);
                (*(s32 *)((u8 *)(&sp.u90) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
            } else {
                var_s4 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
                if (var_s4 < 0) {
                    var_s4 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                var_s2 = var_s4 - 1;
                if (var_s2 < 0) {
                    var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                var_a2 = temp_s6 + (var_s4 * 0x1C);
                (*(f32 *)((u8 *)(&sp.u90) + 0)) = (*(f32 *)((u8 *)var_a2 + 0));
                (*(s32 *)((u8 *)(&sp.u90) + 4)) = (s32) (*(s32 *)((u8 *)var_a2 + 4));
                (*(s32 *)((u8 *)(&sp.u90) + 8)) = (s32) (*(s32 *)((u8 *)var_a2 + 8));
            }
            var_s0 = temp_s6 + (var_s2 * 0x1C);
            (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (*(f32 *)((u8 *)var_s0 + 0));
            temp_v0_2 = arg2 * 4;
            var_a3 = temp_v0_2 + &D_800DD608;
            (*(s32 *)((u8 *)(&sp.u9C) + 4)) = (s32) (*(s32 *)((u8 *)var_s0 + 4));
            (*(s32 *)((u8 *)(&sp.u9C) + 8)) = (s32) (*(s32 *)((u8 *)var_s0 + 8));
            temp_f0 = (*(f32 *)((u8 *)var_a2 + 0x10));
            var_t0 = temp_v0_2 + &D_800DD618;
            temp_f2 = temp_f0 * *var_a3;
            temp_f12 = temp_f0 * *var_t0;
            (*(s16 *)((u8 *)sp.uBC + 0)) = (s16) (s32) (sp.u90 + temp_f12);
            (*(s16 *)((u8 *)sp.uBC + 2)) = (s16) (s32) sp.u94;
            (*(s16 *)((u8 *)sp.uBC + 4)) = (s16) (s32) (sp.u98 - temp_f2);
            (*(s16 *)((u8 *)sp.uBC + 8)) = 0;
            (*(s16 *)((u8 *)sp.uBC + 0xA)) = (s16) (s32) (*(f32 *)((u8 *)var_a2 + 0x18));
            (*(s8 *)((u8 *)sp.uBC + 0xC)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xD)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xE)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xF)) = (s8) (*(s16 *)((u8 *)var_a2 + 0x14));
            (*(s16 *)((u8 *)sp.uBC + 6)) = 0;
            temp_t6 = sp.uBC + 0x10;
            sp.uBC = temp_t6;
            *temp_t6 = (s16) (s32) (sp.u90 - temp_f12);
            (*(s16 *)((u8 *)sp.uBC + 2)) = (s16) (s32) sp.u94;
            (*(s16 *)((u8 *)sp.uBC + 4)) = (s16) (s32) (sp.u98 + temp_f2);
            (*(s16 *)((u8 *)sp.uBC + 8)) = 0x7FF;
            (*(s16 *)((u8 *)sp.uBC + 0xA)) = (s16) (s32) (*(f32 *)((u8 *)var_a2 + 0x18));
            (*(s8 *)((u8 *)sp.uBC + 0xC)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xD)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xE)) = 0xFF;
            (*(s8 *)((u8 *)sp.uBC + 0xF)) = (s8) (*(s16 *)((u8 *)var_a2 + 0x14));
            (*(s16 *)((u8 *)sp.uBC + 6)) = 0;
            sp.uBC += 0x10;
            do {
                temp_f0_2 = (*(f32 *)((u8 *)var_s0 + 0x10));
                temp_f2_2 = temp_f0_2 * *var_a3;
                temp_f12_2 = temp_f0_2 * *var_t0;
                (*(s16 *)((u8 *)sp.uBC + 0)) = (s16) (s32) (sp.u9C + temp_f12_2);
                (*(s16 *)((u8 *)sp.uBC + 2)) = (s16) (s32) sp.uA0;
                (*(s16 *)((u8 *)sp.uBC + 4)) = (s16) (s32) (sp.uA4 - temp_f2_2);
                (*(s16 *)((u8 *)sp.uBC + 8)) = 0;
                (*(s16 *)((u8 *)sp.uBC + 0xA)) = (s16) (s32) (*(f32 *)((u8 *)var_s0 + 0x18));
                (*(s8 *)((u8 *)sp.uBC + 0xC)) = 0xFF;
                (*(s8 *)((u8 *)sp.uBC + 0xD)) = 0xFF;
                (*(s8 *)((u8 *)sp.uBC + 0xE)) = 0xFF;
                (*(s8 *)((u8 *)sp.uBC + 0xF)) = (s8) (*(s16 *)((u8 *)var_s0 + 0x14));
                (*(s16 *)((u8 *)sp.uBC + 6)) = 0;
                temp_t2 = sp.uBC + 0x10;
                sp.uBC = temp_t2;
                (*(s16 *)((u8 *)temp_t2 + 0)) = (s16) (s32) (sp.u9C - temp_f12_2);
                (*(s16 *)((u8 *)temp_t2 + 2)) = (s16) (s32) sp.uA0;
                (*(s16 *)((u8 *)temp_t2 + 8)) = 0x7FF;
                (*(s16 *)((u8 *)temp_t2 + 4)) = (s16) (s32) (sp.uA4 + temp_f2_2);
                (*(s8 *)((u8 *)temp_t2 + 0xC)) = 0xFF;
                (*(s8 *)((u8 *)temp_t2 + 0xD)) = 0xFF;
                (*(s8 *)((u8 *)temp_t2 + 0xE)) = 0xFF;
                (*(s16 *)((u8 *)temp_t2 + 0xA)) = (s16) (s32) (*(f32 *)((u8 *)var_s0 + 0x18));
                (*(s16 *)((u8 *)temp_t2 + 6)) = 0;
                (*(s8 *)((u8 *)temp_t2 + 0xF)) = (s8) (*(s16 *)((u8 *)var_s0 + 0x14));
                sp.uBC = temp_t2 + 0x10;
                (*(s32 *)((u8 *)var_s3 + 0)) = 0x01004008;
                temp_s3 = var_s3 + 8;
                (*(s16 **)((u8 *)var_s3 + 4)) = (s16 *) (sp.uBC - 0x40);
                temp_s3_2 = temp_s3 + 8;
                (*(s32 *)((u8 *)temp_s3 + 0)) = 0x05000204;
                (*(s32 *)((u8 *)temp_s3 + 4)) = 0;
                (*(s32 *)((u8 *)temp_s3_2 + 0)) = 0x05020604;
                (*(s32 *)((u8 *)temp_s3_2 + 4)) = 0;
                var_s3 = temp_s3_2 + 8;
                var_a1 = 0;
                if ((*(f32 *)((u8 *)var_a2 + 0x18)) < (*(f32 *)((u8 *)var_s0 + 0x18))) {
                    var_a1 = 1;
                }
                temp_s4 = var_s2;
                if (var_a1 != 0) {
                    sp70 = var_a3;
                    sp6C = var_t0;
                    memcpy(temp_f12_2, sp.uBC, sp.uBC - 0x20);
                    (*(s16 *)((u8 *)sp.uBC + -0x16)) = (s16) ((*(s16 *)((u8 *)sp.uBC + -0x16)) - 0x4000);
                    temp_t2_2 = sp.uBC + 0x10;
                    sp.uBC = temp_t2_2;
                    (*(s16 *)((u8 *)temp_t2_2 + -0x16)) = (s16) ((*(s16 *)((u8 *)temp_t2_2 + -0x16)) - 0x4000);
                    sp.uBC += 0x10;
                }
                var_s2 -= 1;
                var_s0 -= 0x1C;
                if (var_s2 < 0) {
                    var_s2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                    var_s0 = temp_s6 + (var_s2 * 0x1C);
                }
                var_a2 = temp_s6 + (temp_s4 * 0x1C);
                (*(f32 *)((u8 *)(&sp.u90) + 0)) = (*(f32 *)((u8 *)var_a2 + 0));
                (*(s32 *)((u8 *)(&sp.u90) + 4)) = (s32) (*(s32 *)((u8 *)var_a2 + 4));
                (*(s32 *)((u8 *)(&sp.u90) + 8)) = (s32) (*(s32 *)((u8 *)var_a2 + 8));
                (*(f32 *)((u8 *)(&sp.u9C) + 0)) = (*(f32 *)((u8 *)var_s0 + 0));
                (*(s32 *)((u8 *)(&sp.u9C) + 4)) = (s32) (*(s32 *)((u8 *)var_s0 + 4));
                (*(s32 *)((u8 *)(&sp.u9C) + 8)) = (s32) (*(s32 *)((u8 *)var_s0 + 8));
            } while (temp_s4 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    return var_s3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CE3D0.s")
#endif
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
#ifdef NON_MATCHING
// node_find_kind11_by_id: searches the node lists D_800DD280[0..1][list] for the two lists named in D_800A5B40
// (s32 words 0x4D, 0x22) for a node of kind 11 (+0x20) whose sub-object (+0x98) has id (+0x48) == id; NULL if none
u8 *func_151CEBE4(s32 id) {
    u8 i;
    s32 group;
    u8 *node;

    for (i = 0; i < 2; i++) {
        for (group = 0; group < 2; group++) {
            for (node = (u8 *)D_800DD280[group][((s32 *)D_800A5B40)[i]]; node != NULL; node = *(u8 **)(node + 8)) {
                if (*(s32 *)(node + 0x20) == 11 && *(s32 *)(*(u8 **)(node + 0x98) + 0x48) == id) {
                    return node;
                }
            }
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CEBE4.s")
#endif

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

#ifdef NON_MATCHING
f32 func_15143E64(f32 *);

s32 func_151CF204(u8 *arg0) {
    struct {
        f32 u38;
        f32 u3C;
        u8 pad40[0x8];
        f32 u48;
        f32 u4C;
        u8 pad50[0x4];
        f32 u54;
        u8 pad58[0x30];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        u8 padA0[0x8];
        s32 uA8;
        u8 * uAC;
    } sp;
    f32 sp34;
    struct_151CF1C0 *sp2C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f8;
    s16 temp_v0;
    s16 var_a2;
    s16 var_v1;
    s16 var_v1_2;
    s32 temp_t0;
    s8 temp_a0_3;
    struct_151CF1C0 *temp_a0;
    u8 *temp_a1;
    u8 temp_a0_2;
    u8 *temp_a0_4;
    u8 *temp_a1_2;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_t0 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_a1 = (*(u8 **)((u8 *)temp_v1 + 0));
    if ((temp_a1 != NULL) && (((*(s32 *)((u8 *)temp_a1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v1 + 4)) != (*(u8 *)((u8 *)temp_a1 + 0x3B))))) {
        return 0;
    }
    temp_a0 = arg0 + 0x10;
    if (D_800BE9E4 > 0) {
        (*(f32 *)((u8 *)(&sp.u94) + 0)) = temp_a0->x;
        (*(f32 *)((u8 *)(&sp.u94) + 4)) = (f32) temp_a0->y;
        (*(f32 *)((u8 *)(&sp.u94) + 8)) = (f32) temp_a0->z;
        sp.uA8 = temp_t0;
        sp2C = temp_a0;
        sp.uAC = temp_v1;
        if (func_151CF1C0(temp_a0, temp_a1, (*(u8 **)((u8 *)temp_v1 + 8))) != 0) {
            if (!((*(u16 *)((u8 *)arg0 + 0x1E)) & 4)) {
                (*(f32 *)((u8 *)(&sp.u94) + 0)) = sp2C->x;
                (*(f32 *)((u8 *)(&sp.u94) + 4)) = (f32) sp2C->y;
                (*(f32 *)((u8 *)(&sp.u94) + 8)) = (f32) sp2C->z;
            } else {
                temp_a0_2 = (*(u8 *)((u8 *)temp_v1 + 0x1C));
                if (!(temp_a0_2 & 1)) {
                    temp_f16 = (*(f32 *)((u8 *)arg0 + 0x10)) - sp.u94;
                    temp_f18 = (*(f32 *)((u8 *)arg0 + 0x18)) - sp.u9C;
                    temp_f0 = sqrtf((temp_f16 * temp_f16) + (temp_f18 * temp_f18));
                    if (temp_f0 != 0.0f) {
                        temp_f2 = 1.0f / temp_f0;
                        (*(u8 *)((u8 *)temp_v1 + 0x1C)) = (u8) (temp_a0_2 | 1);
                        temp_f14 = -(temp_f18 * temp_f2);
                        (*(f32 *)((u8 *)temp_v1 + 0x14)) = temp_f14;
                        temp_f12 = temp_f16 * temp_f2;
                        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) (temp_f14 * 51.0f);
                        (*(f32 *)((u8 *)temp_v1 + 0x18)) = temp_f12;
                        (*(f32 *)((u8 *)temp_v1 + 0x10)) = (f32) (temp_f12 * 51.0f);
                    }
                }
            }
            (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) | 4);
            sp.u88 = (*(f32 *)((u8 *)arg0 + 0x10)) - sp.u94;
            sp.u8C = (*(f32 *)((u8 *)arg0 + 0x14)) - sp.u98;
            sp.uA8 = temp_t0;
            sp.uAC = temp_v1;
            sp.u90 = (*(f32 *)((u8 *)arg0 + 0x18)) - sp.u9C;
            temp_f0_2 = func_15143E64(&sp.u88);
            if (temp_f0_2 > 0.0001f) {
                temp_a1_2 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x28) + sp.uA8;
                (*(f32 *)((u8 *)temp_a1_2 + 0)) = (f32) sp2C->x;
                (*(f32 *)((u8 *)temp_a1_2 + 4)) = (f32) sp2C->y;
                (*(f32 *)((u8 *)temp_a1_2 + 0xC)) = temp_f0_2;
                (*(f32 *)((u8 *)temp_a1_2 + 8)) = (f32) sp2C->z;
                temp_f0_3 = sqrtf((sp.u88 * sp.u88) + (sp.u90 * sp.u90));
                if (temp_f0_3 == 0.0f) {
                    (*(f32 *)((u8 *)temp_a1_2 + 0x10)) = 1.0f;
                } else {
                    (*(f32 *)((u8 *)temp_a1_2 + 0x10)) = (f32) (1.0f / temp_f0_3);
                }
                (*(f32 *)((u8 *)temp_a1_2 + 0x14)) = 0.0f;
                (*(s32 *)((u8 *)temp_a1_2 + 0x18)) = (s32) (*(s32 *)((u8 *)sp.uAC + 0xC));
                (*(s32 *)((u8 *)temp_a1_2 + 0x1C)) = (s32) (*(s32 *)((u8 *)sp.uAC + 0x10));
                (*(s32 *)((u8 *)temp_a1_2 + 0x20)) = (s32) (*(s32 *)((u8 *)sp.uAC + 0x14));
                (*(s32 *)((u8 *)temp_a1_2 + 0x24)) = (s32) (*(s32 *)((u8 *)sp.uAC + 0x18));
                (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
                }
                temp_a0_3 = (*(s8 *)((u8 *)arg0 + 0x2D));
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
                if (temp_a0_3 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_a0_3 + 1);
                    if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                    }
                    (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                }
                if (((*(u8 *)((u8 *)sp.uAC + 0x1C)) & 2) && ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 3)) {
                    var_v1 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
                    if (var_v1 < 0) {
                        var_v1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                    }
                    var_v1_2 = var_v1 - 1;
                    if (var_v1_2 < 0) {
                        var_v1_2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                    }
                    temp_v0 = var_v1_2 - 1;
                    var_a2 = temp_v0;
                    if (temp_v0 < 0) {
                        var_a2 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                    }
                    temp_f0_4 = (*(f32 *)((u8 *)temp_a1_2 + 0x10));
                    temp_v0_2 = (var_v1_2 * 0x28) + sp.uA8;
                    temp_f12_2 = (*(f32 *)((u8 *)temp_v0_2 + 0));
                    temp_f14_2 = (*(f32 *)((u8 *)temp_v0_2 + 8));
                    temp_f2_2 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
                    temp_f4 = ((*(f32 *)((u8 *)temp_a1_2 + 8)) - temp_f14_2) * temp_f0_4;
                    temp_a0_4 = (var_a2 * 0x28) + sp.uA8;
                    sp.u54 = temp_f4;
                    temp_f8 = ((*(f32 *)((u8 *)temp_a0_4 + 0)) - temp_f12_2) * temp_f2_2;
                    sp.u48 = temp_f8;
                    temp_f10 = ((*(f32 *)((u8 *)temp_a0_4 + 8)) - temp_f14_2) * temp_f2_2;
                    sp.u4C = temp_f10;
                    temp_f4_2 = -(temp_f4 - temp_f10);
                    sp.u3C = (((*(f32 *)((u8 *)temp_a1_2 + 0)) - temp_f12_2) * temp_f0_4) - temp_f8;
                    sp.u38 = temp_f4_2;
                    temp_f16_2 = (temp_f4_2 * temp_f4_2) + (sp.u3C * sp.u3C);
                    sp34 = temp_f16_2;
                    if (temp_f16_2 > 0.0001f) {
                        temp_f2_3 = 1.0f / sqrtf(sp34);
                        sp.u38 = temp_f4_2 * temp_f2_3;
                        sp.u3C *= temp_f2_3;
                        (*(f32 *)((u8 *)temp_v0_2 + 0x20)) = (f32) (*(f32 *)((u8 *)(&sp.u38) + 0));
                        (*(s32 *)((u8 *)temp_v0_2 + 0x24)) = (s32) (*(s32 *)((u8 *)(&sp.u38) + 4));
                        (*(f32 *)((u8 *)temp_v0_2 + 0x18)) = (f32) (sp.u38 * 51.0f);
                        (*(f32 *)((u8 *)temp_v0_2 + 0x1C)) = (f32) (sp.u3C * 51.0f);
                    } else {
                        (*(f32 *)((u8 *)temp_v0_2 + 0x18)) = 0.0f;
                        (*(f32 *)((u8 *)temp_v0_2 + 0x1C)) = 0.0f;
                        (*(f32 *)((u8 *)temp_v0_2 + 0x20)) = 0.0f;
                        (*(s32 *)((u8 *)temp_v0_2 + 0x24)) = 0;
                    }
                }
            }
            goto block_35;
        }
        (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) & 0xFFFB);
        return 1;
    }
block_35:
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CF204.s")
#endif
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

#ifdef NON_MATCHING
/* P170 */
void func_1503F6F4(Mtx *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_15143794(s16, s16, f32, void *);
s32 func_15132FBC(void *, s32, s32, s32, u8, s32);
void func_15151FA8(u8 *, u8, s32);
void func_1515128C(u8 *, u8, s32);
void func_1504715C(void *, u8 *);
void func_151A9DE4(f32 *, f32, f32, void *, s32, u8, s32, u8, s32);
extern f32 D_800AB2CC[7][3]; /* spark offsets in the model's space */
extern s32 D_800AB320[7];    /* spark kinds 0x6F..0x75 (the asm copies it to the stack: a local initializer) */

/* func_15132FBC spark block */
typedef struct {
    f32 scale[2];     /* +00 */
    f32 size[2];      /* +08 */
    f32 pos[3];       /* +10 */
    f32 axis[3];      /* +1C */
    f32 offset[3];    /* +28: func_15143134 output */
    f32 dir[3];       /* +34: func_15143794 output */
    f32 u40;
    f32 u44;
    f32 u48;
    f32 u4C;
    s32 u50;
    s16 life;         /* +54 */
    s16 kind;         /* +56 */
    u8 u58;
    s32 u5C;
    u8 u60[8];
    u8 u68;
    u8 pad69;
    u8 u6A;
    u8 *owner;        /* +6C */
    u8 u70;
    s16 u72;
    s16 u74;
} SparkBlockFFFC;

/* func_15151FA8 flash block */
typedef struct {
    f32 pos[3];       /* +00 */
    f32 f0C[6];
    s16 s24[10];
    u8 b38[3];
    s32 w3C[6];
    u8 b54[3];
    s32 w58[9];
    u8 b7C[2];
    u8 pad7E[2];
    s16 s80[2];
} FlashBlockFFFC;

/* func_1515128C ring block */
typedef struct {
    s32 u00;
    s32 u04;
    f32 pos[3];       /* +08 */
    s16 s14[4];
    f32 f1C[3];
    s16 s28[2];
    u8 u2C;
} RingBlockFFFC;

// object_shatter_effects: the break-up effects of an object with a model (+0x1D4; nothing without one): 7 sparks
// (func_15132FBC, kinds 0x6F..0x75) from the model's root point (func_1503F6F4) at the D_800AB2CC offsets
// (func_15143134) with random directions (func_15143794), sizes from +0x14C / +0x150; then a flash (func_15151FA8)
// and a ring (func_1515128C) 200 units above the object's position, and 7..10 debris pieces (func_151A9DE4, kind
// 2) dropped from there onto the floor up to 2000 units below.
void func_151CFFFC(u8 *obj, u8 arg1, s32 arg2) {
    SparkBlockFFFC s;
    FlashBlockFFFC f;
    RingBlockFFFC r;
    s32 ground[9];
    f32 pos[3];
    f32 rot[3];
    f32 root[3];
    f32 scl[3];
    u32 a;
    u32 b;
    u8 debrisKind;
    u8 i;

    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 200.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    if (*(Mtx **) (obj + 0x1D4) == NULL) {
        return;
    }
    func_1503F6F4(*(Mtx **) (obj + 0x1D4), &rot[0], &rot[1], &rot[2], &root[0], &root[1], &root[2], &scl[0], &scl[1],
                  &scl[2]);
    s.scale[0] = 1.0f;
    s.scale[1] = 0.649000049f;
    s.size[1] = s.size[0] = (*(f32 *) (obj + 0x14C) + *(f32 *) (obj + 0x150)) * 0.5f;
    s.pos[0] = root[0];
    s.pos[1] = root[1];
    s.pos[2] = root[2];
    s.axis[0] = 1.0f;
    s.axis[1] = 0.0f;
    s.axis[2] = 1.0f;
    s.u44 = 0.0f;
    s.u58 = 0;
    s.u5C = 0;
    s.u60[0] = 0xFF;
    s.u60[1] = 0xD;
    s.u60[2] = 0;
    s.u60[3] = 7;
    s.u60[4] = 0;
    s.u60[5] = 0;
    s.u60[6] = 0;
    s.u60[7] = 0;
    s.u68 = 2;
    s.u6A = 1;
    s.owner = obj;
    s.u70 = obj[0x3B];
    s.u72 = 0xC;
    s.u74 = 0x15;
    s.u50 = 0x39E9;
    for (i = 0; i < 7; i++) {
        s.kind = D_800AB320[i];
        func_15143134(D_800AB2CC[i], s.offset, *(void **) (obj + 0x1D4));
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794((u8) a, b % 25 - 64, func_150ADA68() * 11.45f + 16.93f, s.dir);
        s.u40 = func_150ADA68() * 19.752f + -9.876f;
        s.u48 = func_150ADA68() * 19.752f + -9.876f;
        s.u4C = func_150ADA68() * 0.518f + -1.539f;
        s.life = (u32) func_150ADA20() % 101 + 100;
        func_15132FBC(&s, 3, 0xFF, 0, arg1, arg2);
    }

    f.pos[0] = pos[0];
    f.pos[1] = pos[1];
    f.pos[2] = pos[2];
    f.f0C[0] = 8.0f;
    f.f0C[1] = 13.0f;
    f.f0C[2] = 0.8f;
    f.f0C[3] = 0.4f;
    f.f0C[4] = 23.0f;
    f.f0C[5] = 7.0f;
    f.s24[0] = 0xD;
    f.s24[1] = 6;
    f.s24[2] = 0;
    f.s24[3] = 0xFF;
    f.s24[4] = -0x40;
    f.s24[5] = 0x32;
    f.s24[6] = 3;
    f.s24[7] = 2;
    f.s24[8] = 0x28;
    f.s24[9] = 0x19;
    f.b38[0] = 9;
    f.b38[1] = 1;
    f.b38[2] = 0x48;
    f.w3C[0] = 1;
    f.w3C[1] = 0;
    f.w3C[2] = 0;
    f.w3C[3] = 0;
    f.w3C[4] = 0;
    f.w3C[5] = 0;
    f.b54[0] = 0;
    f.b54[1] = 0x96;
    f.b54[2] = 0x69;
    f.w58[0] = 3;
    f.w58[1] = 0xFF;
    f.w58[2] = 0;
    f.w58[3] = 0x220005;
    f.w58[4] = 0x1D0600;
    f.w58[5] = 3;
    f.w58[6] = 0x3B;
    f.w58[7] = 0x80;
    f.w58[8] = 0x20;
    f.b7C[0] = 0;
    f.b7C[1] = 7;
    f.s80[0] = 10;
    f.s80[1] = 0x19;
    func_15151FA8((u8 *) &f, arg1, arg2);

    r.u00 = 0xF;
    r.u04 = 6;
    r.pos[0] = pos[0];
    r.pos[1] = pos[1];
    r.pos[2] = pos[2];
    r.s14[0] = 0;
    r.s14[1] = 0xFF;
    r.s14[2] = -0x1D;
    r.s14[3] = 0x28;
    r.f1C[0] = 375.0f;
    r.f1C[1] = 20.0f;
    r.f1C[2] = 40.0f;
    r.s28[0] = 0x78;
    r.s28[1] = 0x78;
    r.u2C = 2;
    func_1515128C((u8 *) &r, arg1, arg2);

    func_1504715C(ground, obj);
    debrisKind = 2;
    func_151A9DE4(pos, pos[1] - 2000.0f, 200.0f, ground, (func_150ADA20() & 3) + 7, 0, (s32) &debrisKind, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151CFFFC.s")
#endif

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

#ifdef NON_MATCHING
void func_1504715C(void *, u8 *);
u8 *func_151307F0(s32 *, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_1514FC58(s8 *);
s32 func_1514FD78(s8 *, f32, s32 *);
s32 func_151504B4(s8 *, s32 *, s32 *, s32, s32);
void func_1515423C(u8 *, s32, s32, u8, s32);

void func_151D09A8(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s32 u64;
        u8 pad68[0x10];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s32 u84;
        s32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        s8 u91;
        s8 u92;
        s8 u93;
        s8 u94;
        s8 u95;
        s16 u96;
        s16 u98;
        s16 u9A;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        s32 uA8;
        u8 padAC[0x8];
        s32 uB4;
        u8 padB8[0x8];
        s32 uC0;
        u8 padC4[0x8];
        f32 uCC;
        s32 uD0;
        s32 uD4;
        s8 uD8;
        s8 uD9;
        s8 uDA;
        s8 uDB;
        s8 uDC;
        s8 uDD;
        s8 uDE;
        u8 padDF[0x1];
        s16 uE0;
        u8 padE2[0x2];
        f32 uE4;
        u8 padE8[0x4];
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
        s16 u110;
        s16 u112;
        s16 u114;
        s16 u116;
        s16 u118;
        s16 u11A;
        s16 u11C;
        s16 u11E;
        s8 u120;
        u8 pad121[0x3];
        f32 u124;
        s16 u128;
        s16 u12A;
        s32 u12C;
        s32 u130;
        u8 pad134[0x8];
        s16 u13C;
        s16 u13E;
        f32 u140;
        f32 u144;
        s16 u148;
        s16 u14A;
        f32 u14C;
        f32 u150;
        s8 u154;
        s8 u155;
        u8 pad156[0x2];
        f32 u158;
        f32 u15C;
        s8 u160;
        s8 u161;
        u8 pad162[0x2];
        f32 u164;
        s8 u168;
        u8 pad169[0x3];
        f32 u16C;
        f32 * u170;
        f32 * u174;
        s32 * u178;
        s32 * u17C;
        s8 u180;
        u8 pad181[0x3];
        s32 u184;
        u8 pad188[0x8];
        s32 u190;
        u8 pad194[0x8];
        s32 u19C;
        u8 pad1A0[0x8];
        f32 u1A8;
        s32 u1AC;
        u8 pad1B0[0x20];
        f32 u1D0;
        f32 u1D4;
        f32 u1D8;
        f32 u1DC;
        f32 u1E0;
        f32 u1E4;
    } sp;
    s32 temp_s2;
    s32 var_s1;
    u32 temp_hi;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s2 = arg1 & 0xFF;
    if ((*(s32 *)((u8 *)arg0 + 0x1D4)) != 0) {
        sp.u178 = ((u8 *)&D_800AB364);
        sp.u17C = ((u8 *)&D_800AB370);
        sp.u170 = &sp.u1DC;
        sp.u174 = &sp.u1D0;
        func_15145EA4(&sp.u178, &sp.u170, (*(s32 *)((u8 *)arg0 + 0x1D4)) + 0x80, 2);
        sp.u1D0 -= sp.u1DC;
        sp.u1D4 -= sp.u1E0;
        sp.u1D8 -= sp.u1E4;
        func_1504715C(&sp.u1AC, arg0);
        sp.u180 = 0;
        temp_s0 = ((u8 *)&D_800A5860);
        (*(f32 *)((u8 *)(&sp.u184) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u1D0) + 0));
        (*(s32 *)((u8 *)(&sp.u184) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u1D0) + 4));
        (*(s32 *)((u8 *)(&sp.u184) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u1D0) + 8));
        (*(s32 *)((u8 *)(&sp.u64) + 0)) = (s32) (*(s32 *)((u8 *)temp_s0 + 0));
        (*(s32 *)((u8 *)(&sp.u64) + 4)) = (s32) (*(s32 *)((u8 *)temp_s0 + 4));
        (*(s32 *)((u8 *)(&sp.u64) + 8)) = (s32) (*(s32 *)((u8 *)temp_s0 + 8));
        (*(s32 *)((u8 *)(&sp.u19C) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 0));
        (*(s32 *)((u8 *)(&sp.u19C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 4));
        (*(s32 *)((u8 *)(&sp.u19C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 8));
        (*(s32 *)((u8 *)(&sp.u190) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 0));
        (*(s32 *)((u8 *)(&sp.u190) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 4));
        (*(s32 *)((u8 *)(&sp.u190) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u64) + 8));
        (*(f32 *)((u8 *)(&sp.u130) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u1DC) + 0));
        (*(s32 *)((u8 *)(&sp.u130) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 4));
        (*(s32 *)((u8 *)(&sp.u130) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 8));
        sp.u13C = 6;
        sp.u13E = 8;
        sp.u140 = 0.04f;
        sp.u148 = 0x1E;
        sp.u14A = 0x1E;
        sp.u154 = 0x9B;
        sp.u155 = 0x64;
        sp.u160 = 1;
        sp.u161 = 2;
        sp.u164 = 0.0f;
        sp.u168 = 1;
        sp.u16C = 0.0f;
        sp.u1A8 = 750.0f;
        sp.u144 = 0.03f;
        sp.u14C = -1.4670001f;
        sp.u150 = 0.75600004f;
        sp.u158 = 403.0f;
        sp.u15C = 455.0f;
        func_151504B4(&sp.u180, &sp.u130, &sp.u1AC, temp_s2 & 0xFF, arg2);
        (*(f32 *)((u8 *)(&sp.uEC) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u1DC) + 0));
        (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 4));
        (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 8));
        sp.u110 = 0xF;
        sp.u112 = 8;
        sp.u114 = 3;
        sp.u116 = 2;
        sp.u118 = 0x1E;
        sp.u11A = 0x19;
        sp.u11C = 0x9B;
        sp.u11E = 0x64;
        sp.u124 = 0.0f;
        sp.u128 = 0x10;
        sp.u12A = 0xF;
        sp.u12C = 0;
        sp.u120 = 2;
        sp.u1A8 = 750.0f;
        sp.uF8 = 10.0f;
        sp.uFC = 25.0f;
        sp.u100 = 1.253f;
        sp.u104 = 0.823f;
        sp.u108 = 0.035f;
        sp.u10C = 0.031999998f;
        func_1515423C(&sp.u180, &sp.uEC, &sp.u1AC, temp_s2 & 0xFF, arg2);
        if (func_1514FC58(&sp.u180) != 0) {
            sp.u1A8 = 1000.0f;
            temp_hi = func_150ADA20() % 6U;
            sp.u95 = 0x3E;
            sp.u80 = 0x2203;
            sp.u78 = 0x200005;
            sp.u7C = 0;
            sp.u84 = 0;
            sp.u88 = 0;
            sp.u8C = 0;
            sp.u8D = 0;
            sp.u8E = 0;
            sp.u8F = 0xFF;
            sp.u90 = 0;
            sp.u91 = 0;
            sp.u92 = 0;
            sp.u93 = 0;
            sp.u94 = 0xFF;
            (*(f32 *)((u8 *)(&sp.uA8) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u1DC) + 0));
            (*(s32 *)((u8 *)(&sp.uA8) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 4));
            var_s1 = temp_hi + 5;
            (*(s32 *)((u8 *)(&sp.uA8) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u1DC) + 8));
            (*(s32 *)((u8 *)(&sp.uB4) + 0)) = (s32) (*(s32 *)((u8 *)temp_s0 + 0));
            (*(s32 *)((u8 *)(&sp.uB4) + 4)) = (s32) (*(s32 *)((u8 *)temp_s0 + 4));
            (*(s32 *)((u8 *)(&sp.uB4) + 8)) = (s32) (*(s32 *)((u8 *)temp_s0 + 8));
            sp.u9A = 1;
            sp.uD0 = 0xC007;
            sp.u9C = 1.0f;
            sp.u82 = (func_150ADA20() % 11U) + 0x28;
            sp.u96 = 1;
            sp.u98 = 0xFF;
            sp.uD8 = 6;
            sp.uD9 = 8;
            sp.uDC = -1;
            sp.uDA = -1;
            sp.uDB = -1;
            sp.uDD = 0xB;
            sp.uD4 = 0;
            sp.uDE = 0xFF;
            sp.uE0 = 0;
            sp.uA4 = 0.0f;
            sp.uA0 = 0.0f;
            sp.uE4 = 10000.0f;
            if (var_s1 != 0) {
                do {
                    func_1514FD78(&sp.u180, (func_150ADA68() * 0.04f) + 0.049999997f, &sp.uC0);
                    sp.uCC = (func_150ADA68() * 1.34f) + -2.329f;
                    temp_v0 = func_151307F0(&sp.u78, 1, 0, 4, temp_s2, arg2);
                    if (temp_v0 != NULL) {
                        (*(u8 **)((u8 *)temp_v0 + 0xA8)) = func_151CF05C(NULL, temp_v0, 0U, temp_s2 & 0xFF, arg2);
                    }
                    var_s1 -= 1;
                } while (var_s1 != 0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D09A8.s")
#endif
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

#ifdef NON_MATCHING
s32 func_151D1694(u8 *obj, f32 *out, u8 which);

/* P162: D_8008FFD0 entries 1 / 2. func_151D16E8 (asm) and func_151D1510 test the result ("point found"), so these
   return func_151D1694's s32 like entry 0 (func_151D1624) instead of void. */
// object_offset_point_0: entry 1 of D_8008FFD0: object's matrix applied to offset 0 (100, 8, -20)
s32 func_151D1654(u8 *obj, f32 *out) {
    return func_151D1694(obj, out, 0);
}

// object_offset_point_1: entry 2 of D_8008FFD0: object's matrix applied to offset 1 (-100, 8, -20)
s32 func_151D1674(u8 *obj, f32 *out) {
    return func_151D1694(obj, out, 1);
}
#else
void func_151D1654(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 0);
}

void func_151D1674(s32 arg0, s32 arg1) {
    func_151D1694(arg0, arg1, 1);
}
#endif

#ifdef NON_MATCHING
extern f32 D_800AB37C[2][3];

// object_offset_point: transforms the fixed offset D_800AB37C[which] by the object's matrix (obj + 0x1D4) into
// out; returns 0 (out untouched) when the object has no matrix, 1 otherwise
s32 func_151D1694(u8 *obj, f32 *out, u8 which) {
    void *mtx = *(void **)(obj + 0x1D4);

    if (mtx == NULL) {
        return 0;
    }
    func_15143134(D_800AB37C[which], out, mtx);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1FB080/func_151D1694.s")
#endif

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
