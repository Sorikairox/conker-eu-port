#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted forward declaration(s) for func_15191970
void func_15191970(u8 *arg0);

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} struct_eu_vec3;

typedef struct {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ struct_eu_vec3 unk34;
} struct_eu_1BAAA0_c;

typedef struct {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ struct_eu_1BAAA0_c *unk2C;
} struct_eu_1BAAA0_d;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C];
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ u8 pad1E[0xE];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x28];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0x2C];
    /* 0x089 */ s8 unk89;
    /* 0x08A */ u8 pad8A[0x9A];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 unk126;
    /* 0x128 */ u8 pad128[0x2C];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
} struct_eu_1BAAA0_e;

typedef struct {
    u8 unk0[4];
} struct_eu_bytes4b;

extern struct_eu_bytes4b D_800A78B4;

typedef struct {
    /* 0x00 */ u8 pad0[0x84];
    /* 0x84 */ s32 unk84;
} struct_eu_1BAAA0_b;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x24];
    /* 0x40 */ struct_eu_1BAAA0_b *unk40;
} struct_eu_1BAAA0;

void func_15190DB0(void *arg0) {
    func_15191970(arg0);
    func_15169804(arg0);
}

void func_15190DDC(void *arg0) {
    func_15191970(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15190E08.s")

s32 func_1519150C(u8 *arg0) {
    s32 pad;
    u8 *p;
    f32 s;
    f32 c;

    arg0[0x131] += (s8)arg0[0x133] * D_800BE9E4;
    arg0[0x132] += (s8)arg0[0x134] * D_800BE9E4;
    p = arg0 + 0x110;
    s = func_151423D8((u8)(arg0[0x131] - 0x40));
    c = func_151423D8((u8)(p[0x22] - 0x40));
    *(f32 *)(arg0 + 0x2C) += ((*(f32 *)(p + 0x28) + (*(f32 *)(p + 0x30) * s)) - *(f32 *)(arg0 + 0x2C)) * 0.5f;
    *(f32 *)(arg0 + 0x30) += ((*(f32 *)(p + 0x2C) + (*(f32 *)(p + 0x34) * c)) - *(f32 *)(arg0 + 0x30)) * 0.5f;
    return 1;
}

#ifdef NON_MATCHING
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
s32 memcpy(s32, f32 *, s32);
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151915FC(u8 *arg0, s16 arg1) {
    struct {
        u8 u37;
        f32 u38;
        u8 pad3C[0x10];
        f32 u4C;
        f32 u50;
        u8 pad54[0x4];
        f32 u58;
        u8 pad5C[0x4];
        u8 * u60;
        u8 * u64;
    } sp;
    u8 *sp30;
    f32 *sp2C;
    f32 *sp28;
    f32 *temp_a0;
    f32 *temp_a1;
    f32 *temp_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 temp_t0;
    u8 *temp_v0;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u64, &sp.u37);
    sp.u60 = sp.u64;
    if (sp.u64 != NULL) {
        if (sp.u37 != 0) {
            temp_v0 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp2C = temp_a1;
            sp30 = temp_v0;
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40);
            memcpy((*(s32 *)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_t0 = arg1 * 4;
        temp_v1 = temp_t0 + &D_800DD618;
        temp_a0 = temp_t0 + &D_800DD608;
        var_f14 = -1.0f;
        var_f2 = ((*temp_v1 * ((*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34)))) - (*temp_a0 * ((*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C))))) * D_800BEDC8;
        if (var_f2 < 0.0f) {
            var_f14 = 1.0f;
            var_f2 = -var_f2;
        }
        var_f12 = sqrtf(var_f2) * (*(f32 *)((u8 *)arg0 + 0x12C));
        if (var_f12 > 1.5707964f) {
            var_f12 = 1.5707964f;
        }
        temp_f12 = var_f12 * var_f14;
        sp2C = temp_v1;
        sp28 = temp_a0;
        sp.u38 = temp_f12;
        sp.u58 = sinf(temp_f12);
        temp_f0 = cosf(temp_f12);
        temp_f12_2 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_f14 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f2 = temp_f12_2 * temp_f0;
        temp_f18 = temp_f12_2 * sp.u58;
        temp_f16 = -temp_f2;
        sp.u50 = temp_f14 * temp_f0;
        sp.u4C = temp_f14 * sp.u58;
        (*(s16 *)((u8 *)sp.u64 + 0)) = (s16) (s32) ((*temp_v1 * temp_f16) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f16));
        (*(s16 *)((u8 *)sp.u64 + 6)) = 0;
        (*(s16 *)((u8 *)sp.u64 + 0x10)) = (s16) (s32) ((*temp_v1 * temp_f2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18);
        (*(s16 *)((u8 *)sp.u64 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f2));
        (*(s16 *)((u8 *)sp.u64 + 0x16)) = 0;
        temp_f0_2 = temp_f2 - sp.u4C;
        (*(s16 *)((u8 *)sp.u64 + 0x20)) = (s16) (s32) ((*temp_v1 * temp_f0_2) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) - temp_f18) - sp.u50);
        (*(s16 *)((u8 *)sp.u64 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_2));
        (*(s16 *)((u8 *)sp.u64 + 0x26)) = 0;
        temp_f0_3 = -(temp_f2 + sp.u4C);
        (*(s16 *)((u8 *)sp.u64 + 0x30)) = (s16) (s32) ((*temp_v1 * temp_f0_3) + (*(f32 *)((u8 *)arg0 + 0x34)));
        (*(s16 *)((u8 *)sp.u64 + 0x32)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_f18) - sp.u50);
        (*(s16 *)((u8 *)sp.u64 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (*temp_a0 * temp_f0_3));
        (*(s16 *)((u8 *)sp.u64 + 0x36)) = 0;
        return sp.u60;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_151915FC.s")
#endif
typedef struct { s16 base; s16 range; u8 pad4[0x10]; } Rng14;
extern Rng14 D_800AA120[];
s32 func_1513F680(u8 *, s32, s32, s32, s32);
void func_15191970(u8 *arg0) {
    s32 i;
    u8 **p;
    u8 *q;
    Rng14 *r;

    *(f32 *)(arg0 + 0x1C) = 0.0f;
    *(s32 *)(arg0 + 0x20) = 0;
    p = *(u8 ***)(arg0 + 0x24);
    for (i = 0; i != 0x3C; i++, p += 3) {
        if (*p != NULL) {
            q = *p + 0x110;
            *(f32 *)(q + 0) = 0.0f;
            *(f32 *)(q + 4) = 0.0f;
            *(f32 *)(q + 8) = 0.0f;
            r = &D_800AA120[*(u8 *)(q + 0x20)];
            func_1513F680(*p, 0xD, 0x12, 0, 0xD);
            *(s16 *)(*p + 0x1C) = func_150ADA20() % (u32)(r->range + 1) + r->base;
            *(s32 *)(*p + 0x58) |= 1;
        }
    }
    bzero(*(u8 ***)(arg0 + 0x24), 0x2D0);
}

#ifdef NON_MATCHING
/* P143 */
s32 func_1514672C(u8 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_151DAB58(u8, f32, u8, f32 *, u8, u8, s32);
void func_151DBCBC(u8, f32, s16, s32, void *, u8, s32);
extern f32 D_800A83FC;
extern f32 D_800A8400;
// drop_fall_update: update handler (D_8008A058 slot 13) of a falling drop / debris sprite. Motion block at +0x110:
// velocity x/y/z, gravity +0x11C, drag +0x120 (x / z speeds times drag * dt each frame), trail easing +0x128 (the
// trail point +0x40 follows the position +0x34). Ends (0) when func_1514672C rejects the new position (out of the
// level); a floor probe (func_15046F70, floor y to +0x148) that hits also ends it and spawns a splash at the floor,
// sized by width +0x2C * height +0x30: kind +0x165 == 3 -> func_151DBCBC (0.25), else randomly func_151D9B8C
// (D_800A83FC, life 80..120) or the ring func_151DAB58 (D_800A8400), of type +0x16C, owner data +0x14C.
s32 func_15191A90(u8 *fx) {
    f32 *mv = (f32 *)(fx + 0x110);
    f32 probe[3];
    f32 y0, vx0, vz0, vy, dvy;
    f32 dx, dy, dz;
    f32 x, y, z;
    s8 ret;

    y0 = *(f32 *)(fx + 0x38);
    vx0 = mv[0];
    vz0 = mv[2];
    ret = 1;
    mv[0] = vx0 * (mv[4] * D_800BE9A4);
    mv[2] = vz0 * (mv[4] * D_800BE9A4);
    dx = (mv[0] + vx0) * 0.5f * D_800BE9A4;
    vy = mv[1];
    dvy = mv[3] * D_800BE9A4;
    dy = vy * D_800BE9A4 + dvy * D_800BE9A4 * 0.5f;
    dz = (mv[2] + vz0) * 0.5f * D_800BE9A4;
    mv[1] = vy + dvy;
    *(f32 *)(fx + 0x34) += dx;
    *(f32 *)(fx + 0x38) = y0 + dy;
    *(f32 *)(fx + 0x3C) += dz;
    *(f32 *)(fx + 0x40) += dx;
    *(f32 *)(fx + 0x44) += dy;
    *(f32 *)(fx + 0x48) += dz;
    x = *(f32 *)(fx + 0x34);
    y = *(f32 *)(fx + 0x38);
    z = *(f32 *)(fx + 0x3C);
    *(f32 *)(fx + 0x40) = x + (*(f32 *)(fx + 0x40) - x) * mv[6];
    *(f32 *)(fx + 0x44) = y + (*(f32 *)(fx + 0x44) - y) * mv[6];
    *(f32 *)(fx + 0x48) = z + (*(f32 *)(fx + 0x48) - z) * mv[6];
    probe[0] = x;
    probe[1] = y0 - *(f32 *)(fx + 0x30);
    probe[2] = *(f32 *)(fx + 0x3C);
    if (func_1514672C((u8 *)probe) == 0) {
        return 0;
    }
    if (func_15046F70(probe, 0, *(f32 *)(fx + 0x38) - *(f32 *)(fx + 0x30), (f32 *)(fx + 0x148)) != 0) {
        probe[1] = *(f32 *)(fx + 0x148);
        if (fx[0x165] == 3) {
            func_151DBCBC(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * 0.25f, fx[0x5C], (s32)(fx + 0x14C),
                          probe, fx[0xC], fx[1]);
        } else if (func_150ADA20() & 1) {
            func_151D9B8C(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A83FC, fx[0x5C],
                          (s32)(fx + 0x14C), (struct17 *)probe, (func_150ADA20() % 41U) + 0x50, 1, 1, 0, fx[0xC],
                          fx[1]);
        } else {
            func_151DAB58(fx[0x16C], *(f32 *)(fx + 0x2C) * *(f32 *)(fx + 0x30) * D_800A8400, fx[0x5C], probe, 1,
                          fx[0xC], fx[1]);
        }
        ret = 0;
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191A90.s")
#endif

s32 func_15191DEC(struct_eu_1BAAA0_e *arg0) {
    s16 temp_v0 = arg0->unk1C;
    s32 temp_v1;

    if (temp_v0 < arg0->unk124) {
        temp_v1 = temp_v0 * arg0->unk126;
        if (temp_v1 < arg0->unk5C) {
            arg0->unk5C = temp_v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191E2C.s")

#ifdef NON_MATCHING
void func_15191EF0(struct102 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0xD) {
        if (((*(s32 *)((u8 *)arg0 + 0x10)) == (*(s32 *)((u8 *)arg1 + 0))) || (arg0->unk14 == (*(u8 *)((u8 *)arg1 + 4)))) {
            (*(s16 *)((u8 *)arg0 + 0x16)) = 0x64;
            arg0->unk18 |= 1;
        }
    } else if ((arg2 == 0xC) || (arg2 == 0x50) || (arg2 == 0xE)) {
        if (((*(s32 *)((u8 *)arg0 + 0x10)) == (*(s32 *)((u8 *)arg1 + 0))) || (arg0->unk14 == (*(u8 *)((u8 *)arg1 + 4)))) {
            func_1516972C(arg0);
        }
    } else {
        if (arg2 == 0x4E) {
            func_1516972C(arg0);
            return;
        }
        func_15169850((s32) arg1, arg2, (s32) &arg0->unk10, (s32) &arg0->unk14, (s32) arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191EF0.s")
#endif
#ifdef NON_MATCHING
void func_15191FF4(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_a2_3;

    if ((arg2 == 0xC) || (arg2 == 0xE) || (arg2 == 0x50)) {
        temp_a2 = &arg0->unk28;
        if (((*(s32 *)((u8 *)temp_a2 + 0)) == (*(s32 *)((u8 *)arg1 + 0))) || ((*(u8 *)((u8 *)temp_a2 + 4)) == (*(u8 *)((u8 *)arg1 + 4)))) {
            func_1516972C(arg0);
        }
    } else {
        if (arg2 == 0x4E) {
            func_1516972C(arg0);
            return;
        }
        if (arg2 == 0xD) {
            temp_a2_2 = &arg0->unk28;
            if (((*(s32 *)((u8 *)temp_a2_2 + 0)) == (*(s32 *)((u8 *)arg1 + 0))) || ((*(u8 *)((u8 *)temp_a2_2 + 4)) == (*(u8 *)((u8 *)arg1 + 4)))) {
                (*(s16 *)((u8 *)arg0 + 0xE)) = 0x64;
                (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
            }
        } else {
            temp_a2_3 = &arg0->unk28;
            func_15169850((s32) arg1, arg2, (s32) temp_a2_3, (s32) (temp_a2_3 + 4), (s32) arg0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1BE5C0/func_15191FF4.s")
#endif
extern s32 D_800A83F0;

void func_151920FC(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A83F0;
    func_151494E0(arg0, arg1);
    func_15169260(&sp1C, 1, arg0, arg1);
}
