#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 *func_1513445C(u8 *arg0, u16 arg1, u8 arg2, s32 arg3);
#endif
// hoisted forward declaration(s) for func_151341C8, func_15134290
s32 func_15134108(u8 *, f32, f32, f32, f32, s32);


extern s32 (*D_80089C50[])(u8 *);
extern s32 (*D_80089CB4[])(u8 *);
extern void (*D_80089D1C[])(u8 *);
extern s32 (*D_80089D28[])(u8 *);
s32 func_1514672C(u8 *);

void func_15132740(u8 *arg0) {
    s32 pad;
    u8 done = 0;
    s16 t;

    *(s32 *)(arg0 + 0x60) &= ~0x200000;
    if ((*(s32 *)(arg0 + 0x60) & 0x10) && (arg0[0x148] & 0x18)) {
        if (!D_80089D28[arg0[0x77]](arg0)) {
            done = 1;
        }
    } else if (arg0[0x71] != 0) {
        if (!D_80089C50[arg0[0x71]](arg0)) {
            done = 1;
        }
    }
    if (arg0[0x72] != 0 && !done) {
        if (!D_80089CB4[arg0[0x72]](arg0)) {
            done = 1;
        }
    }
    if ((*(s32 *)(arg0 + 0x60) & 0x80) && !done) {
        *(s16 *)(arg0 + 0x64) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x64) < 0) {
            done = 1;
        }
    }
    if ((*(s32 *)(arg0 + 0x60) & 0x2000) && !done) {
        t = *(s16 *)(arg0 + 0x64);
        if (t < *(s16 *)(arg0 + 0x82)) {
            if ((t * *(s16 *)(arg0 + 0x84)) < arg0[0x70]) {
                if (!(t * *(s16 *)(arg0 + 0x84))) { // fakematch: empty if fixes the multu operand order
                }
                arg0[0x70] = (t * *(s16 *)(arg0 + 0x84));
            }
        }
    }
    if (!done && !(*(s32 *)(arg0 + 0x60) & 0x80000)) {
        done = !func_1514672C(arg0 + 0x38);
    }
    if (done) {
        if (arg0[0x76] != 0) {
            D_80089D1C[arg0[0x76]](arg0);
        }
        func_1516972C((struct102 *)arg0);
    }
}

void func_1513291C(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D50[var_v0](arg0);
}

void func_15132968(u8 *arg0) {
    u8 var_v0 = (*(s32 *)(arg0 + 0x60) & 0x100) ? arg0[0x68] : 0;

    D_80089D74[var_v0](arg0);
}

void func_15132B38(u8 *arg0);
s32 func_1510DBB0(s32, s32 *, u16 *);
extern s32 D_800DCA70[];
typedef struct Node29B4 {
    s32 *data;
    struct Node29B4 *next;
    struct Node29B4 *prev;
    u8 pad0C[2];
    u8 flag;
} Node29B4;
typedef struct {
    u8 pad0[0x66];
    u16 idx;
    u8 pad68[0x24];
    Node29B4 *node;
} Obj29B4;
void func_151329B4(Obj29B4 *arg0) {
    D_800DC63C--;
    ((s16 *)D_800DC468)[arg0->idx]--;
    if (((s16 *)D_800DC468)[arg0->idx] == 0) {
        if (arg0->node->flag != 0) {
            D_800DC468[arg0->idx] = 1;
        } else {
            func_1510DBB0(D_800DCA70[arg0->idx], &D_800DC63C, D_800DC468);
            if (arg0->node->prev == NULL) {
                D_800DC460 = (s32)arg0->node->next;
                if (D_800DC460 != 0) {
                    ((Node29B4 *)D_800DC460)->prev = NULL;
                } else {
                    D_800DC464 = 0;
                }
            } else {
                arg0->node->prev->next = arg0->node->next;
                if (arg0->node->next != NULL) {
                    arg0->node->next->prev = arg0->node->prev;
                } else {
                    D_800DC464 = (s32)arg0->node->prev;
                }
            }
            func_100043B4(arg0->node->data, 4);
            func_100043B4((s32 *)arg0->node, 4);
        }
    }
    func_15132B38((u8 *)arg0);
}

void func_15132AE0(struct102 * arg0) {
    func_151329B4(arg0);
    func_15169804(arg0);
}

void func_15132B0C(struct102 * arg0) {
    func_151329B4(arg0);
    func_15169824(arg0);
}

void func_15132B38(u8 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (((s32 *)(arg0 + 0x154))[i]) {
            func_100043B4(((s32 *)(arg0 + 0x154))[i], 4);
        }
    }
    if (*(s32 *)(arg0 + 0x164) != 0) {
        func_100043B4(*(s32 *)(arg0 + 0x164), 4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15132BBC.s")

void func_15132FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_15132BBC(arg0, arg1, arg2, 0, arg3, arg4, arg5);
}

extern s32 (*D_80089D2C[])(Mtx *);
u8 func_151464B8(s16 *arg0);
typedef struct {
    u8 pad0[0x60];
    u32 flags;
    u8 pad64[8];
    s16 *unk6C;
    u8 pad70[8];
    u8 unk78;
    u8 pad79[0x17];
    Mtx mtx[2];
} Unk15132FF8;

void func_15132FF8(Unk15132FF8 *arg0) {
    s32 r;

    arg0->flags &= ~0x200000;
    if (arg0->flags & 0x20000) {
        return;
    }
    if ((arg0->flags & 0x400) && arg0->unk6C != NULL && func_151464B8(arg0->unk6C) != 0) {
        return;
    }
    if (arg0->flags & 0x80000) {
        arg0->flags |= 0x200000;
        return;
    }
    r = D_80089D2C[arg0->unk78](&arg0->mtx[D_800BE9C0]);
    if (r == -1) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (r == 0) {
        arg0->flags &= ~0x40000;
    } else {
        arg0->flags |= 0x240000;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_151330F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513334C.s")

s32 func_1513384C(u8 *arg0)
{
  f32 cs;
  *((f32 *) (arg0 + 0x2C)) = 1.0f;
  *((f32 *) (arg0 + 0x30)) = 1.0f;
  *((f32 *) (arg0 + 0x34)) = 1.0f;
  if ((*((s32 *) (arg0 + 0x60))) & 0x40)
  {
    *((f32 *) (arg0 + 0x20)) += (*((f32 *) (arg0 + 0x50))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x24)) += (*((f32 *) (arg0 + 0x54))) * D_800BE9A4;
    *((f32 *) (arg0 + 0x28)) += (*((f32 *) (arg0 + 0x58))) * D_800BE9A4;
  }
  arg0[0x149] += ((s32) (576.0f * (*((f32 *) (arg0 + 0x144))))) * D_800BE9E4;
  if (arg0[0x149] < 0x80)
  {
    f32 s;
    s = func_151423D8(arg0[0x149] - 0x40);
    s = ((1.0f - (*((f32 *) (arg0 + 0x144)))) * (1.0f - (*((f32 *) (arg0 + 0x14))))) * s;
    if (arg0[0x148] & 8)
    {
      *((f32 *) (arg0 + 0x2C)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x34)) *= s + 1.0f;
      *((f32 *) (arg0 + 0x3C)) = (*((f32 *) (arg0 + 0x138))) - ((*((f32 *) (arg0 + 0x10))) * (0, s)); // fakematch: comma puts s in fs
    }
    if (arg0[0x148] & 0x10)
    {
      f32 sn;
      f32 d;
      sn = func_151423D8(((s8) arg0[0x14A]) - 0x40);
      cs = func_151423D8((u8) arg0[0x14A]);
      *((f32 *) (arg0 + 0x2C)) *= 1.0f - s;
      *((f32 *) (arg0 + 0x30)) *= 1.0f + s;
      *((f32 *) (arg0 + 0x34)) *= 1.0f - s;
      d = (*((f32 *) (arg0 + 0x10))) * (0, s); // fakematch: comma puts s in fs
      *((f32 *) (arg0 + 0x38)) = (*((f32 *) (arg0 + 0x134))) - (d * cs);
      *((f32 *) (arg0 + 0x40)) = (*((f32 *) (arg0 + 0x13C))) + (d * sn);
    }
  }
  else
  {
    memcpy(arg0 + 0x38, arg0 + 0x134, 0xC);
    arg0[0x149] = 0;
    arg0[0x148] &= ~0x18;
  }
  return 1;
}

s32 func_151424F4(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
s32 func_15133A80(s32 arg0, u8 *arg1) {
    func_151424F4(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x2C), *(f32 *)(arg1 + 0x30), *(f32 *)(arg1 + 0x34), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
    return 1;
}

void func_151B9C10(void *);
extern void (*D_80089D98[])(u8 *, u8 *, u8);
void func_15133AF8(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 idx;
  s32 sel = arg2;
  s32 t;
  s32 k; // fakematch: unused local fixes the arg2-copy spill slot
  if ((arg2 == 0x1B) && (*(u16 *)(arg0 + 0x66) == 0x22))
  {
    func_151B9C10(arg0);
  }
  if (sel == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)(arg0 + 0x7C)) { *(s32 *)(arg0 + 0x7C) = *(s32 *)(arg1 + 4); arg0[0x80] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)(arg0 + 0x7C)) {
      s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
      *(s32 *)(arg0 + 0x7C) = *(s32 *)arg1; arg0[0x80] = arg1[8]; }
  }
  else if (sel == 0)
  {
    t = *(s32 *)arg1;
    if ((t == *(s32 *)(arg0 + 0x7C)) || (arg0[0x80] == arg1[4])) { *(s32 *)(arg0 + 0x7C) = 0; arg0[0x80] = 0; }
  }
  if (*(s32 *)(arg0 + 0x60) & 0x100) { idx = arg0[0x68]; } else { idx = 0; }
  if (D_80089D98[idx] != NULL) { D_80089D98[idx](arg0, arg1, arg2); }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133C18.s")

s32 func_15142838(s32, s32, s32, s32, f32, f32, f32, f32, f32);
s32 func_15133CD0(s32 arg0, u8 *arg1) {
    func_15142838(arg0, *(s32 *)(arg1 + 0x18), *(s32 *)(arg1 + 0x1C), *(s32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x24), *(f32 *)(arg1 + 0x28), *(f32 *)(arg1 + 0x38), *(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x40));
    return 1;
}

s32 func_15133D30(u8 *arg0) {
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x44) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += (*(f32 *)(arg0 + 0x48) * D_800BE9A4) + (*(f32 *)(arg0 + 0x5C) * D_800BE9A4 * D_800BE9A4 * 0.5f);
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x5C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x20) += *(f32 *)(arg0 + 0x50) * D_800BE9A4;
    *(f32 *)(arg0 + 0x24) += *(f32 *)(arg0 + 0x54) * D_800BE9A4;
    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x58) * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15133E04.s")

s32 func_15133F44(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_f0;
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    temp_f0 = *(f32 *)(arg0 + 0x14);
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x44) * temp_f0;
    *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x48) * -temp_f0;
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x4C) * temp_f0;
    *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x50) * temp_f0;
    *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) * temp_f0;
    *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) * temp_f0;
    return 1;
}

s32 func_15133FC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)(arg0 + 0x3C) = *(f32 *)(arg0 + 0x10) + arg4;
    *(f32 *)(arg0 + 0x44) = 0.0f;
    *(f32 *)(arg0 + 0x48) = 0.0f;
    *(f32 *)(arg0 + 0x4C) = 0.0f;
    *(f32 *)(arg0 + 0x50) = 0.0f;
    *(f32 *)(arg0 + 0x54) = 0.0f;
    *(f32 *)(arg0 + 0x58) = 0.0f;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_15134004.s")

s32 func_15134108(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5)
{
  f32 temp_f18;
  f32 temp_f6;
  *((f32 *) (((u8 *) arg0) + 0x3C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x10))) + arg4);
  temp_f18 = *((f32 *) (((u8 *) arg0) + 0x14));
  *((f32 *) (((u8 *) arg0) + 0x48)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x48))) * (-temp_f18));
  *((f32 *) (((u8 *) arg0) + 0x44)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x44))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x4C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x4C))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x50)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x50))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x54)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x54))) * temp_f18);
  *((f32 *) (((u8 *) arg0) + 0x58)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x58))) * temp_f18);
  if (fabsf(*((f32 *) (((u8 *) arg0) + 0x48))) < 4.0f)
  {
    *((f32 *) (((u8 *) arg0) + 0x44)) = 0.0f;
    *((s32 *) (((u8 *) arg0) + 0x60)) = (s32) ((*((s32 *) (((u8 *) arg0) + 0x60))) & (~0x69));
    *((f32 *) (((u8 *) arg0) + 0x48)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x4C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x50)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x54)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x58)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x5C)) = 0.0f;
  }
  return 1;
}

s32 func_151341C8(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88((func_150ADA20() % 9U) + 0x2DE, 0x2EE0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

s32 func_15134290(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15134108(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88((func_150ADA20() % 10U) + 0x1B8, 0x5DC0U, 0, 0U, 0, (s16) (s32) arg1, (s16) (s32) arg2, (s16) (s32) arg3, 0x1F4, 0x3E8);
    }
    return 1;
}

void func_15134358(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    if (arg2 == 0) {
        id = arg1[0];
        if (id == *(s32 *)((u8 *)arg0 + 0x7C) || ((u8 *)arg1)[4] == *((u8 *)arg0 + 0x80)) {
            func_1516972C(arg0);
        }
    }
}

void func_151343AC(s32 arg0, u8 arg1) {
    struct_eu_s32x2 sp18 = D_800A3C40;
    func_15169260(&sp18, 2, arg0, arg1);
}

void func_151343F4(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x170), arg1[0x172], *(s32 *)(arg1 + 0x174));
}

void func_15134428(s32 arg0, u8 *arg1, s32 arg2) {
    func_1513445C(arg0, *(u16 *)(arg1 + 0x174), arg1[0x176], *(s32 *)(arg1 + 0x178));
}

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32 *, s32, s32);

s32 *func_1513445C(u8 *arg0, u16 arg1, u8 arg2, s32 arg3) {
    struct {
        s32 u30;
        u8 pad34[0x6];
        u8 u3A;
        u8 u3B;
    } sp;
    s32 *temp_v1;
    s32 *var_s0;
    s32 temp_t2;
    s32 temp_v0_2;
    s32 var_a0;
    struct_eu_80090F10 *temp_v0;

    temp_v0 = &D_80090F10[arg1];
    sp.u3B = temp_v0->padA[0];
    sp.u3A = temp_v0->padA[1];
    temp_v0_2 = func_1510D66C(*(*(s32 **)((u8 *)temp_v0 + 0)), &sp.u30, arg3, 0);
    (*(s32 *)((u8 *)arg0 + 4)) = temp_v0_2;
    temp_t2 = arg2 * 4;
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((temp_t2 & 0xFFFF) | 0xDB060000);
    var_s0 = arg0 + 8;
    temp_v1 = var_s0;
    if (sp.u3B == 2) {
        (*(s32 *)((u8 *)temp_v1 + 0)) = ((temp_t2 + 4) & 0xFFFF) | 0xDB060000;
        var_s0 = (s32 *)((u8 *)var_s0 + (8));
        if (sp.u3A == 1) {
            var_a0 = 0x200;
        } else {
            var_a0 = 0x20;
        }
        (*(s32 *)((u8 *)temp_v1 + 4)) = (s32) ((temp_v0_2 + sp.u30) - var_a0);
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15FF50/func_1513445C.s")
#endif
s32 func_15134548(s32 arg0, u8 *arg1, s32 arg2) {
    u8 *p = arg1 + 0x170;
    u8 *q = p;
    u8 *e;
    s32 i;

    for (i = 0; i < *q; i = (i + 1) & 0xFF) {
        e = (u8 *)((s32)p + (i << 3));
        arg0 = (s32)func_1513445C((u8 *)arg0, *(u16 *)(e + 4), *(u8 *)(e + 6), *(s32 *)(e + 8));
    }
    return arg0;
}
