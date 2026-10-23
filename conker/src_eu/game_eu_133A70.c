#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15108060(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_15107FA0(u8 *arg0, s16 arg1, s16 arg2, u8 *arg3, u8 *arg4);
void func_151084D4(u8 *arg0, u8 arg1, void *arg2, void *arg3);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106260.s")

typedef struct { f32 x, y, z; } V3_133A70;
s32 func_15106794(struct102 *);
void func_15106B90(struct102 *);
extern s32 D_80088FB0;

void func_1510660C(struct102 *arg0) {
    s32 (*temp_v1)(struct102 *, u8 *);
    u8 sp2B;
    s8 temp_v0;
    u8 *temp_v0_3;

    sp2B = 0;
    temp_v0 = (*(s8 *)((u8 *)arg0 + 0x44));
    if (temp_v0 != -1) {
        temp_v1 = *(s32 *)((u8 *)&D_80088FB0 + (temp_v0 * 4));
        if ((temp_v1 != NULL) && (temp_v1(arg0, &sp2B) == 0)) {
            func_1516972C(arg0);
        }
    }
    if (arg0->unk12 & 1) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            func_1516972C(arg0);
        }
    }
    if (sp2B != 0) {
        func_15106794(arg0);
    }
    (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x68)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x68)) < 0) {
        func_15106B90(arg0);
        (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) (((*(s16 *)((u8 *)arg0 + 0x54)) + (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x56)) + 1))));
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x6C));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x14);
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x70));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x38);
    }
}

s32 func_15106760(s32 arg0) {
    return arg0 + 0x88;
}

typedef struct {
    u8 pad0[0x34];
} struct_eu_133A70_elem;

typedef struct {
    u8 pad0[0x48];
    s32 unk48;
    u8 pad4C[0x3C];
    struct_eu_133A70_elem unk88[1];
} struct_eu_133A70;

struct_eu_133A70_elem *func_1510676C(struct_eu_133A70 *arg0) {
    s32 temp_v1 = arg0->unk48;

    return &arg0->unk88[temp_v1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106794.s")

f32 func_15106A34(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return temp_f2 * temp_f2 * temp_f2;
}

f32 func_15106A5C(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return 3.0f * arg0 * temp_f2 * temp_f2;
}

f32 func_15106A90(f32 arg0) {
    return 3.0f * arg0 * arg0 * (1.0f - arg0);
}

f32 func_15106AC0(f32 arg0) {
    return arg0 * arg0 * arg0;
}

f32 func_15106AD8(f32 arg0) {
    f32 temp_f2 = 1.0f - arg0;
    return -3.0f * temp_f2 * temp_f2;
}

f32 func_15106B04(f32 arg0) {
    return ((9.0f * arg0 * arg0) - (12.0f * arg0)) + 3.0f;
}

f32 func_15106B3C(f32 arg0) {
    return (-9.0f * arg0 * arg0) + (6.0f * arg0);
}

f32 func_15106B6C(f32 arg0) {
    return 3.0f * arg0 * arg0;
}

// PERMUTER CHANGED DECL: voidfunc_15106B90(struct102*) (base: voidfunc_15106B90(struct102*arg0))
void func_15143874(s16, f32, f32 *, f32 *);

void func_15106B90(struct102 *arg0)
{
  s32 i;
  u8 *src;
  V3_133A70 *d;
  V3_133A70 *dst;
  u8 *q;
  src = (u8 *) func_15106760((s32) arg0);
  d = (V3_133A70 *) func_1510676C((struct_eu_133A70 *) arg0);
  d[0] = *((V3_133A70 *) (((u8 *) arg0) + 0x14));
  d[(*((s32 *) (((u8 *) arg0) + 0x48))) + 1] = *((V3_133A70 *) (((u8 *) arg0) + 0x38));
  for (i = 1; i < ((*((s32 *) (((u8 *) arg0) + 0x48))) + 1); i++)
  {
    s32 pad; // fakematch: frame slot below s, c
    f32 s;
    f32 c;
    dst = &d[i];
    q = src + ((i - 1) * 0x34);
    if (!arg0) { // fakematch: permuter (s-register order of i / dst / src)
    }
    func_15143874(func_150ADA20() & 0xFF, (*((f32 *) (((u8 *) arg0) + 0x4C))) * func_150ADA68(), &c, &s);
    dst->x = (*((f32 *) (q + 4))) + (((*((f32 *) (q + 0x28))) * s) + ((*((f32 *) (q + 0x1C))) * c));
    dst->y = (*((f32 *) (q + 8))) + (((*((f32 *) (q + 0x2C))) * s) + ((*((f32 *) (q + 0x20))) * c));
    dst->z = (*((f32 *) (q + 0xC))) + (((*((f32 *) (q + 0x30))) * s) + ((*((f32 *) (q + 0x24))) * c));
  }

}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106D38.s")

extern void (*D_80088FB8[])(u8 *);
void func_151073F8(u8 *arg0)
{
  void (*fn)(u8 *) = D_80088FB8[arg0[0x5C]];
  struct102 *a;
  struct102 *b;
  if (fn != NULL) {
    fn(arg0);
  }
  a = *(struct102 **)(arg0 + 0x6C);
  if (a != NULL) {
    func_1516972C(a);
  }
  b = *(struct102 **)(arg0 + 0x70);
  if (b != NULL) {
    func_1516972C(b);
  }
  func_151D5E30(arg0 + 0x74);
}

void func_15107478(struct102 *arg0) {
    func_151073F8(arg0);
    func_15169804(arg0);
}

void func_151074A4(struct102 * arg0) {
    func_151073F8(arg0);
    func_15169824(arg0);
}

void func_151074D0(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088FC8[arg0[0x5C]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107518.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510783C.s")

void func_15107B84(s32 ***arg0) {
    s32 **temp_v0 = arg0[0x18];
    s32 *temp_v1 = *temp_v0;

    temp_v1 += 0x28 / 4;
    temp_v1[2] = 0;
}

void func_15107B9C(u8 *arg0) { u8 *p = arg0; if (*(s32 *)(p + 0x30) != 0) { func_1516972C(*(struct102 **)(p + 0x30)); } }

void func_15107BCC(struct260 * arg0) {
    func_15107B9C(arg0);
    func_1514933C(arg0);
}

void func_15107BF8(struct260 * arg0) {
    func_15107B9C(arg0);
    func_15149368(arg0);
}

extern void (*D_80088FD8[])(u8 *, s32, u8);
void func_15107C24(u8 *arg0, s32 arg1, u8 arg2)
{
  int new_var;
  void (**tab)(u8 *, s32, u8) = D_80088FD8;
  new_var = 0x68; // fakematch: constant index in a variable stops the CSE of the table index load
  if (tab[arg0[new_var]] != 0)
  {
    tab[arg0[new_var]](arg0, arg1, arg2);
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107C80.s")

void func_15107E64(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    func_15169850(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}

#ifdef NON_MATCHING
s32 func_15107EA4(u8 *arg0, s8 *arg1) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        u8 * u38;
    } sp;
    u8 *sp28;
    u8 *temp_a3;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x60));
    temp_t6 = (*(u8 **)((u8 *)temp_v0 + 0));
    sp.u38 = temp_t6;
    if (((*(s32 *)((u8 *)temp_t6 + 0)) == 0) || (temp_a3 = arg0 + 0x14, ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_t6 + 0x3B))))) {
        return 0;
    }
    *arg1 = 0;
    (*(f32 *)((u8 *)(&sp.u2C) + 0)) = (*(f32 *)((u8 *)temp_a3 + 0));
    (*(s32 *)((u8 *)(&sp.u2C) + 4)) = (s32) (*(s32 *)((u8 *)temp_a3 + 4));
    (*(s32 *)((u8 *)(&sp.u2C) + 8)) = (s32) (*(s32 *)((u8 *)temp_a3 + 8));
    sp28 = temp_a3;
    func_15107FA0(sp.u38, (*(s16 *)((u8 *)temp_v0 + 6)), (*(s16 *)((u8 *)temp_v0 + 8)), temp_a3, NULL);
    if ((sp.u2C != (*(f32 *)((u8 *)arg0 + 0x14))) || (sp.u30 != (*(f32 *)((u8 *)arg0 + 0x18))) || (sp.u34 != (*(f32 *)((u8 *)arg0 + 0x1C)))) {
        *arg1 = 1;
        func_15108060((f32 *) sp28, arg0 + 0x38, arg0 + 0x20, arg0 + 0x2C);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15107EA4.s")
#endif
#ifdef NON_MATCHING
s32 func_15143794(s16, s16, f32, u8 *); /* P95: f32 (float bits were passed as an int) */
#else
s32 func_15143794(s16, s16, s32, u8 *);
#endif
s32 func_1515C7B4(u8 *, f32 *, s32 *, s32 *);

void func_15107FA0(u8 *arg0, s16 arg1, s16 arg2, u8 *arg3, u8 *arg4) {
    f32 sp2C[3];
    s32 sp28;
    s32 sp24;

    func_1515C7B4(arg0, sp2C, &sp28, &sp24);
#ifdef NON_MATCHING
    func_15143794(arg1, arg2, *(f32 *)&sp28, arg3); /* P95: f32 (float bits were passed as an int) */
#else
    func_15143794(arg1, arg2, sp28, arg3);
#endif
    *(f32 *)(arg3 + 4) *= *(f32 *)(arg0 + 0xF0);
    *(f32 *)(arg3 + 0) += sp2C[0];
    *(f32 *)(arg3 + 4) += sp2C[1];
    *(f32 *)(arg3 + 8) += sp2C[2];
    if (arg4 != NULL) {
        *(vertex *)arg4 = *(vertex *)sp2C;
    }
}

void func_15108060(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 dx = arg1[0] - arg0[0];
    f32 dy = arg1[1] - arg0[1];
    f32 dz = arg1[2] - arg0[2];

    arg2[0] = arg0[0] + dx * 0.333f;
    arg2[1] = arg0[1] + dy * 0.333f;
    arg2[2] = arg0[2] + dz * 0.333f;
    arg3[0] = arg0[0] + dx * 0.6667f;
    arg3[1] = arg0[1] + dy * 0.6667f;
    arg3[2] = arg0[2] + dz * 0.6667f;
}

void func_151080F8(u8 *arg0, s16 arg1, s16 arg2, u8 arg3, s32 arg4) {
    f32 sp2C[3];
    f32 sp20[3];
    s32 sp1C;
    s32 sp18;

    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        func_1515C7B4(arg0, sp20, &sp1C, &sp18);
#ifdef NON_MATCHING
        func_15143794(arg1, arg2, *(f32 *)&sp1C, sp2C); /* P95: f32 (float bits were passed as an int) */
#else
        func_15143794(arg1, arg2, sp1C, sp2C);
#endif
        sp2C[1] *= *(f32 *)(arg0 + 0xF0);
        sp2C[0] += sp20[0];
        sp2C[1] += sp20[1];
        sp2C[2] += sp20[2];
        func_151C384C(sp2C, arg3, arg4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_1510819C.s")

#ifdef NON_MATCHING
s32 func_151083C8(u8 *arg0, s8 *arg1) {
    struct {
        f32 u24;
        f32 u28;
        f32 u2C;
    } sp;
    f32 *sp20;
    f32 *temp_a3;
    u8 *temp_s1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x60));
    temp_s1 = (*(u8 **)((u8 *)temp_v0 + 0));
    if (((*(s32 *)((u8 *)temp_s1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_s1 + 0x3B)))) {
        return 0;
    }
    temp_a3 = arg0 + 0x14;
    if ((*(s32 *)((u8 *)temp_s1 + 0x1D4)) == 0) {
        return 0;
    }
    *arg1 = 0;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)temp_a3 + 0));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)temp_a3 + 4));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)temp_a3 + 8));
    sp20 = temp_a3;
    func_151084D4(temp_s1, (*(u8 *)((u8 *)temp_v0 + 0x14)), temp_v0 + 8, temp_a3);
    if ((sp.u24 != (*(f32 *)((u8 *)arg0 + 0x14))) || (sp.u28 != (*(f32 *)((u8 *)arg0 + 0x18))) || (sp.u2C != (*(f32 *)((u8 *)arg0 + 0x1C)))) {
        *arg1 = 1;
        func_15108060(sp20, arg0 + 0x38, arg0 + 0x20, arg0 + 0x2C);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_151083C8.s")
#endif
void func_151084D4(u8 *arg0, u8 arg1, void *arg2, void *arg3) {
    func_15143134(arg2, arg3, *(u8 **)(arg0 + 0x1D4) + (arg1 << 6));
}

void func_15108518(u8 *arg0, s32 arg1, u8 arg2) {
    s32 temp_a2 = *(s32 *)(arg0 + 0x60);

    func_15169850(arg1, arg2, temp_a2, temp_a2 + 4, (s32)arg0);
}
