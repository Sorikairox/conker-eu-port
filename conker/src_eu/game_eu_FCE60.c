#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_1504715C(void *, u8 *);
void func_15143794(s16, s16, f32, void *);
void func_1515C7B4(u8 *, f32 *, f32 *, f32 *);

void func_150CF650(u8 *arg0) {
    struct {
        f32 uBC;
        u8 padC0[0x8];
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        s32 uDC;
        u8 padE0[0x20];
        f32 u100;
        f32 u104;
        f32 u108;
        f32 u10C;
    } sp;
    f32 temp_f20;
    s16 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s1;
    u8 *temp_s0;
    u8 *temp_s2;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_s2 = arg0 + 0x28;
    if (((*(s32 *)((u8 *)temp_s0 + 0)) == 0) || ((*(u8 *)((u8 *)temp_s2 + 4)) != (*(u8 *)((u8 *)temp_s0 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    if ((*(s32 *)((u8 *)temp_s0 + 0x1D4)) != 0) {
        (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) + ((0.06f + (func_150ADA68() * 0.0704f)) * D_800BE9A4));
        func_1515C7B4(temp_s0, &sp.u104, &sp.uD8, &sp.uD4);
        sp.u100 = (sp.uD8 + sp.uD4) * 0.5f;
        func_1504715C(&sp.uDC, temp_s0);
        if ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f) {
            do {
                temp_s0_2 = func_150ADA20() & 0xFF;
                func_15143794(temp_s0_2, (s16) ((func_150ADA20() % 76U) - 0x40), sp.u100, &sp.uC8);
                sp.uC8 += sp.u104;
                sp.uCC += sp.u108;
                sp.uD0 += sp.u10C;
                temp_s0_3 = func_150ADA20();
                func_15143794(temp_s0_2, (s16) (((u32) temp_s0_3 % 54U) - 0x38), (func_150ADA68() * 1.4430001f) + 2.2680001f, &sp.uBC);
                temp_f20 = func_150ADA68();
                temp_s1 = func_150ADA20();
                temp_s0_4 = func_150ADA20();
                func_151D9014(&sp.uC8, &sp.uBC, 5U, (temp_f20 * 0.286f) + -0.78700006f, (s16) (((u32) temp_s1 % 21U) + 0x1E), (u8) (((u32) temp_s0_4 % 156U) + 0x64), (func_150ADA68() * 50.0f) + 48.0f, 1U, 1.0f, 1.0f, 0U, (s32) &sp.uDC, 1U, 0U, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                (*(f32 *)((u8 *)temp_s2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s2 + 8)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s2 + 8)) > 1.0f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CF650.s")
#endif
void func_150CF994(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x28;
    if (arg2 == 0) {
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

void func_151CFE48(struct127 *, f32, s32);

void func_150CFA40(s32 arg0) {
    func_151CFE48(D_800CC2D0, D_800CC2D0->y_position + 300.0f, 0xC61C4000);
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
void func_150CFA88(s32 arg0) {
    s32 temp_v1;
    D_80088C30 += D_800BE9E4 * 0x1A;
    temp_v1 = D_800BE9E4 * 0x1C;
    D_80088C34 -= temp_v1;
    D_80088C38 -= temp_v1;
}

extern s32 D_80088C30;
extern s32 D_80088C34;
extern s32 D_80088C38;
extern s32 D_80088C3C;

Gfx *func_150CFAF8(Gfx *gdl) {
    gDPSetTileSize(gdl++, 0, D_80088C30 >> 7, D_80088C34 >> 7, 0x47E, 0x47E);
    gDPSetTileSize(gdl++, 1, D_80088C38 >> 7, D_80088C3C >> 7, 0x47E, 0x47E);
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150CFD10.s")

void func_150D00FC(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if (arg2 == 0x52) {
        temp_v0[0] |= 1;
        *(f32 *)(temp_v0 + 4) = 0.0f;
        *(f32 *)(temp_v0 + 8) = *(f32 *)(arg0 + 0x10);
        *(f32 *)(temp_v0 + 0xC) = *arg1 - *(f32 *)(arg0 + 0x10);
    }
}

void func_150D0148(f32 arg0) {
    f32 sp1C = arg0;
    func_15155C9C(&sp1C, 0x52);
}

s32 func_150D0170(u8 *arg0) {
    f32 *v = (f32 *)(arg0 + 0x70);

    *(f32 *)(arg0 + 0x10) += v[0] * D_800BE9A4;
    *(f32 *)(arg0 + 0x14) += v[1] * D_800BE9A4 + 0.5f * v[2] * D_800BE9A4 * D_800BE9A4;
    v[1] += v[2] * D_800BE9A4;
    if (v[3] < *(f32 *)(arg0 + 0x14)) {
        *(f32 *)(arg0 + 0x14) = v[3];
        v[0] *= 0.3f;
        v[1] = fabsf(v[1]) * -0.15f;
    }
    return 1;
}

u8 *func_150D0230(u8 *arg0) {
    while ((*arg0 != 0xBD) && (*arg0 != 0)) {
        arg0++;
    }
    return arg0;
}

u8 *func_150D026C(u8 *arg0) {
    while (*arg0 != 0) {
        arg0++;
    }
    return arg0;
}

s32 func_150D0294(u8 *arg0, u8 **arg1) {
    u8 *temp_v0 = func_150D0230(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}

s32 func_150D02C8(u8 *arg0)
{
  u8 *end;
  s32 best = 0;
  u8 *next;
  end = func_150D026C(arg0);
  while (arg0 < end) {
    s32 v;
    v = func_150D0294(arg0, &next);
    if (best < v) {
      best = v;
    }
    arg0 = next + 1;
  }
  return best;
}

s32 memcpy(s32, void *, s32);
void func_150D034C(u8 *arg0)
{
  u8 *p = arg0;
  u8 *q;
  memcpy(*((s32 *) ((p + ((*((u8 *) (p + 0x3D))) << 2)) + ((0, 0x40)))), *((void **) (p + 0x34)), *((u8 *) (p + 0x3C)));
  q = p + 0x28;
  p = q;
  *((*((u8 **) ((p + ((*((u8 *) (p + 0x15))) << 2)) + 0x18))) + (*((u8 *) (p + 0x14)))) = 0;
}

void func_150D03A8(u8 *arg0) {
    u8 *v = arg0 + 0x28;

    if (**(u8 **)(arg0 + 0x38) != 0) {
        *(u8 **)(v + 0xC) = *(u8 **)(v + 0x10) + 1;
        *(u8 *)(v + 0x14) = func_150D0294(*(u8 **)(v + 0xC), (u8 **)(v + 0x10));
        *(u8 *)(v + 0x15) = *(u8 *)(v + 0x15) ^ 1;
        func_150D034C(arg0);
        *(u8 *)(v + 8) = *(u8 *)(v + 8) | 1;
    }
}

#ifdef NON_MATCHING
s32 func_150D02C8(u8 *);
void func_150D034C(u8 *);
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s8 unk8;
    /* 0x0C */ u8 *unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
    /* 0x18 */ u8 *unk18;
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ s8 unk24;
    /* 0x25 */ u8 unk25;
} struct150D0420; /* size 0x28 */

u8 *func_150D0420(u8 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct150D0420 sp40;
    u8 *sp3C;
    s32 sp38;
    struct150D0420 *dst;
    s32 n;

    sp40.unk15 = 0;
    sp40.unk8 = 1;
    sp40.unk4 = (u8 *)arg1;
    sp40.unkC = (u8 *)arg1;
    sp40.unk25 = (u8)arg5;
    sp40.unk24 = (s8)arg4;
    sp40.unk0 = arg0;
    sp40.unk14 = func_150D0294((u8 *)arg1, &sp40.unk10);
    sp40.unk18 = NULL;
    sp40.unk1C = NULL;
    sp40.unk20 = NULL;
    n = func_150D02C8((u8 *)arg1);
    sp38 = n + 1;
    sp3C = (u8 *)func_15149130(arg2, -1, -1, 5, 3, 0x47, (struct37 *)(arg3 + n * 2 + 0x2A), arg6, arg7);
    if (sp3C != NULL) {
        dst = (struct150D0420 *)(sp3C + 0x28);
        memcpy((s32)dst, &sp40, sizeof(struct150D0420));
        dst->unk20 = (u8 *)dst + 0x28;
        dst->unk18 = dst->unk20 + arg3;
        dst->unk1C = dst->unk18 + sp38;
        *dst->unk18 = 0;
        *dst->unk1C = 0;
        func_150D034C(sp3C);
    }
    return sp3C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FCE60/func_150D0420.s")
#endif
extern s32 D_80088C40[];

s32 func_150D0544(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *v = arg1 + 0x28;

    if ((*(s8 *)(arg1 + 0x4C) != -1) && (((s32 (**)(u8 *))D_80088C40)[*(volatile s8 *)(arg1 + 0x4C)](arg1) == 0)) { // fakematch: volatile forces the second lb of the index, v defined first so addiu is rematerialised
        *(s16 *)(arg1 + 0xE) = -1;
        return arg0;
    }
    *(u8 *)(v + 8) &= 0xFFFE;
    return arg0;
}

extern void (*D_80088C50[])(u8 *, u8 *, u8);
void func_150D03A8(u8 *);
void func_150D05D0(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (arg2 == 0x51) {
        if (arg0[0x28] == arg1[0]) {
            func_150D03A8(arg0);
        }
    } else {
        f = D_80088C50[arg0[0x4D]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

u8 *func_150D0420(u8, s32, s16, s32, s32, s32, u8, s32);
s32 memcpy(s32, void *, s32);
void func_150D0644(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    s32 sfpad;
    s8 sp30[4];
    u8 *temp_v0;
    sp30[0] = 0;
    temp_v0 = func_150D0420(arg0, arg1, arg2, 8, 0, 0, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0 + 0x48)), sp30, 1);
    }
}
