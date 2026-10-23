#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_800A8E7C;

void func_1519C7C8(u8 *arg0);


typedef struct DNode { struct DNode *next; struct DNode *prev; } DNode;
DNode *func_15195D20(s32 arg0, DNode **arg1, DNode **arg2) {
    DNode *node = allocate_memory(arg0, 1, 0, 0);
    if (node != NULL) {
        node->prev = NULL;
        if (*arg2 != NULL) {
            node->next = *arg2;
            (*arg2)->prev = node;
            *arg2 = node;
        } else {
            node->next = NULL;
            *arg2 = node;
            *arg1 = node;
        }
    }
    return node;
}

void func_eu_15195D94(void) {}

extern s32 D_800E0D10, D_800E0D14, D_800E0D18, D_800E0D1C, D_800E0D20;
void func_15195D9C(void) {
    D_800E0D10 = D_800E0D14 = 0;
    D_800E0D18 = D_800E0D1C = 0;
    D_800E0D20 = -2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195DD8.s")

typedef struct {
    DNode node;
    s16 x8;
    s16 w;
    s16 h;
    u16 xE;
    u16 x10;
    u8 x12;
    u8 x13;
    u8 x14;
    s32 x18;
    s16 a[5];
    s16 b[5];
    s16 x30[6];
} Ent3C;

Ent3C *func_15195EF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ent3C *p;
    s32 i;
    s32 w;
    s32 h;
    s32 x;
    s32 y;

    p = (Ent3C *)func_15195D20(0x3C, (DNode **)&D_800E0D18, (DNode **)&D_800E0D1C);
    if (p != NULL) {
        p->x18 = 0;
        for (i = 0; i < 5; i++) {
            p->a[i] = -1;
        }
        for (i = 0; i < 5; i++) {
            p->b[i] = -1;
        }
        p->x8 = arg0;
        w = ((arg1 >> 12) & 0xFFF) + 2;
        h = (arg1 & 0xFFF) + 2;
        if (arg3 != 0) {
            w *= 2;
            h *= 2;
        }
        p->w = w;
        p->h = h;
        p->xE = (arg2 >> 12) & 0xFFF;
        p->x10 = arg2 & 0xFFF;
        p->xE <<= 3;
        p->x10 <<= 3;
        p->x14 = 1;
    }
    return p;
}

s32 func_15195FF4(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15195AA8.s")

typedef struct Ent6270 {
    struct Ent6270 *dnext;
    struct Ent6270 *dprev;
    s32 id;
    u16 sub;
    u8 flag;
    u8 padF;
    struct Ent6270 *next;
} Ent6270;

s32 func_15196270(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) // fakematch: non-void return type with bare returns (void gives a different reg copy; remote permuter)
{
  Ent6270 *e;
  Ent6270 *n;
  Ent6270 *nx;
  nx = *((Ent6270 **) (arg0 + 0x18));
  e = nx;
  if (nx != 0)
  {
    do
    {
      if ((arg1 == e->id) && (arg2 == e->sub))
      {
        return;
      }
      nx = e->next;
      if (nx != 0)
      {
        e = nx;
        nx = nx->next;
      }
    }
    while (nx != 0);
    n = (Ent6270 *) func_15195D20(0x14, (DNode **) (&D_800E0D10), (DNode **) (&D_800E0D14));
    e->next = n;
  }
  else
  {
    n = (Ent6270 *) func_15195D20(0x14, (DNode **) (&D_800E0D10), (DNode **) (&D_800E0D14));
    *((Ent6270 **) (arg0 + 0x18)) = n;
  }
  n->id = arg1;
  n->sub = arg2;
  n->flag = arg3;
  n->next = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196344.s")

void func_15195FB0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_15196344(*(s32 *)(arg0 + 0x1C), arg1, arg2, arg3, arg4, arg5, arg6);
}

#ifdef NON_MATCHING
/* P43: texture scrolling. For each entry of the D_800E0D18 list (next at +4): the scroll position (+0xE, +0x10, u16)
 * gives up to 8 (+0x14) G_SETTILESIZE words (0xF2000000 | s << 12 | t, s and t halved per mip level), written to the
 * level DLs arg0 (indices +0x1C[5], counts +0x30[5]) and arg1 (+0x26[5], +0x35[5]) and to the +0x18 chain of extra
 * DLs (+8 base, +0xC index, +0xE count, next at +0x10); then the position moves by speed (+0x12, +0x13, s8) times
 * D_800BE9E4 unless D_800BEAC0, wrapping once at the texture size (+0xA, +0xC) * 8. A count above the number of
 * words built reads stale stack in the asm (C: uninitialised tbl[]). The asm returns no value. */
s32 func_15196560(s32 arg0, s32 arg1) {
    s32 tbl[8];  /* sp5C */
    u8 *e;
    u8 *p;
    s32 u, v, w, h;
    s32 su, sv;
    s32 n, j, k;
    s16 idx;

    for (e = (u8 *)D_800E0D18; e != NULL; e = *(u8 **)(e + 4)) {
        u = *(u16 *)(e + 0xE);
        v = *(u16 *)(e + 0x10);
        w = *(s16 *)(e + 0xA);
        h = *(s16 *)(e + 0xC);
        su = u / 8 + 2;
        sv = v / 8 + 2;
        if (su >= w) {
            su -= w;
        }
        if (sv >= h) {
            sv -= h;
        }
        n = 0;
        if (e[0x14] > 0) {
            do {
                tbl[n++] = 0xF2000000 | ((su & 0xFFF) << 12) | (sv & 0xFFF);
                su /= 2;
                sv /= 2;
            } while (n < 8 && n < e[0x14]);
        }
        w *= 8;
        h *= 8;
        if (D_800BEAC0 == 0) {
            u += *(s8 *)(e + 0x12) * D_800BE9E4;
            v += *(s8 *)(e + 0x13) * D_800BE9E4;
        }
        if (u < 0) {
            u += w;
        } else if (u >= w) {
            u -= w;
        }
        if (v < 0) {
            v += h;
        } else if (v >= h) {
            v -= h;
        }
        *(u16 *)(e + 0xE) = u;
        *(u16 *)(e + 0x10) = v;
        if (*(s16 *)(e + 0x1C) != -1) {
            k = 0;
            do {
                idx = *(s16 *)(e + 0x1C + k * 2);
                for (j = 0; j < e[0x30 + k]; j++) {
                    *(s32 *)(arg0 + idx * 8 + j * 16) = tbl[j];
                }
                k++;
            } while (k < 5 && *(s16 *)(e + 0x1C + k * 2) != -1);
        }
        if (*(s16 *)(e + 0x26) != -1) {
            k = 0;
            do {
                idx = *(s16 *)(e + 0x26 + k * 2);
                for (j = 0; j < e[0x35 + k]; j++) {
                    *(s32 *)(arg1 + idx * 8 + j * 16) = tbl[j];
                }
                k++;
            } while (k < 5 && *(s16 *)(e + 0x26 + k * 2) != -1);
        }
        for (p = *(u8 **)(e + 0x18); p != NULL; p = *(u8 **)(p + 0x10)) {
            for (j = 0; j < p[0xE]; j++) {
                *(s32 *)(*(s32 *)(p + 8) + *(u16 *)(p + 0xC) * 8 + j * 16) = tbl[j];
            }
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196560.s")
#endif

void func_15196888(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        arg0[0x12] = arg1;
        arg0[0x13] = arg2;
    }
}

extern void (*D_8008FC38[])(void *);
extern void (*D_8008FC2C[])(void *);
s32 func_15147E64(u8 *);
void func_151968A0(u8 *arg0) {
    u8 *o = *(u8 **)(arg0 + 0x98);
    s8 i = o[0x65];
    s8 j;
    if (i != -1) {
        D_8008FC38[i](arg0);
    }
    j = o[0x62];
    if (j != -1) {
        D_8008FC2C[j](arg0);
    }
    func_15147E64(arg0);
}

extern void (*D_8008FC38[])(void *);
extern void (*D_8008FC2C[])(void *);
s32 func_15147E98(u8 *);
void func_15196924(u8 *arg0) {
    u8 *o = *(u8 **)(arg0 + 0x98);
    s8 i = o[0x65];
    s8 j;
    if (i != -1) {
        D_8008FC38[i](arg0);
    }
    j = o[0x62];
    if (j != -1) {
        D_8008FC2C[j](arg0);
    }
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196438.s")

#ifdef NON_MATCHING
s32 func_15198680(u8 *, s8, f32 *, u8 *);
extern s32 D_8008FC20;
extern s32 D_8008FC34;
extern s32 D_8008FC3C;

s32 func_15196CB8(u8 *arg0) {
    u8 *sp34;
    s32 sp30;
    u8 *sp20;
    s16 var_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 var_a1;
    s32 var_s1_3;
    s32 var_t2;
    s8 temp_v0_3;
    s8 temp_v0_4;
    s8 temp_v0_5;
    s8 temp_v1;
    s8 var_s1;
    s8 var_s1_2;
    s8 var_v1_2;
    u8 var_a0;
    u8 var_a0_2;
    u8 *temp_t5;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_a3;

    var_a3 = (*(u8 **)((u8 *)arg0 + 0x98));
    var_t2 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) && ((*(u8 *)((u8 *)var_a3 + 6)) & 1)) {
        return 0;
    }
    var_s1 = (*(s8 *)((u8 *)arg0 + 0x2E));
    if (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
        do {
            var_s1 -= 1;
            if (var_s1 < 0) {
                var_s1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v0 = var_t2 + (var_s1 * 0x24);
            temp_v1 = (*(s8 *)((u8 *)temp_v0 + 0x1E));
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) + ((*(f32 *)((u8 *)var_a3 + 0x40)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0)) + ((*(f32 *)((u8 *)temp_v0 + 0xC)) * D_800BE9A4));
            (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 4)) + ((*(f32 *)((u8 *)temp_v0 + 0x10)) * D_800BE9A4));
            (*(s8 *)((u8 *)temp_v0 + 0x1F)) = 0xFF;
            (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + ((*(f32 *)((u8 *)temp_v0 + 0x14)) * D_800BE9A4));
            if (temp_v1 > 0) {
                (*(s8 *)((u8 *)temp_v0 + 0x1E)) = (s8) (temp_v1 - D_800BE9E4);
            } else {
                (*(s16 *)((u8 *)temp_v0 + 0x1C)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0x1C)) - ((*(u8 *)((u8 *)var_a3 + 0x52)) * D_800BE9E4));
            }
            var_v1 = (*(s16 *)((u8 *)temp_v0 + 0x1C));
            if ((var_v1 < (s32) (*(u8 *)((u8 *)var_a3 + 0x6A))) && ((*(u8 *)((u8 *)temp_v0 + 0x21)) == 0)) {
                sp20 = temp_v0;
                sp34 = var_a3;
                sp30 = var_t2;
                func_15198680(arg0, var_s1, &D_800BE9A4, var_a3);
                var_v1 = (*(s16 *)((u8 *)temp_v0 + 0x1C));
            }
            (*(f32 *)((u8 *)temp_v0 + 0x18)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x18)) + ((*(f32 *)((u8 *)var_a3 + 0x58)) * D_800BE9A4));
            if (var_v1 < 0) {
                (*(u8 *)((u8 *)var_a3 + 6)) = (u8) ((*(u8 *)((u8 *)var_a3 + 6)) & 0xFFFD);
                if (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    do {
                        (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                        if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                        }
                        (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                    } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                }
                (*(s16 *)((u8 *)((var_t2 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24))) + 0x1C)) = 0;
            }
        } while (var_s1 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    var_s1_2 = (*(s8 *)((u8 *)arg0 + 0x2D));
    if ((*(u8 *)((u8 *)var_a3 + 6)) & 2) {
        var_v1_2 = 0;
        var_a0 = (*(u8 *)((u8 *)var_a3 + 0x8C));
loop_22:
        temp_lo = var_s1_2 * 0x24;
        var_s1_2 += 1;
        var_a0 = (u8) (s16) (var_a0 - 1);
        (*(s8 *)((u8 *)((var_t2 + temp_lo)) + 0x1F)) = var_v1_2;
        var_v1_2 = (var_v1_2 + (*(u8 *)((u8 *)var_a3 + 0x8D))) & 0xFF;
        if (var_s1_2 == (*(u8 *)((u8 *)arg0 + 0x25))) {
            var_s1_2 = 0;
        }
        if ((var_a0 != 0) && (var_s1_2 != (*(s8 *)((u8 *)arg0 + 0x2E)))) {
            goto loop_22;
        }
    }
    if ((*(u8 *)((u8 *)var_a3 + 6)) & 4) {
        var_a1 = 0;
        var_a0_2 = (*(u8 *)((u8 *)var_a3 + 0x8E));
        var_s1_3 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_s1_3 < 0) {
            var_s1_3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
loop_30:
        temp_lo_2 = var_s1_3 * 0x24;
        var_s1_3 -= 1;
        var_a0_2 = (u8) (s16) (var_a0_2 - 1);
        temp_v0_2 = var_t2 + temp_lo_2;
        (*(u8 *)((u8 *)temp_v0_2 + 0x1F)) = (u8) ((s32) ((*(u8 *)((u8 *)temp_v0_2 + 0x1F)) * var_a1) >> 8);
        var_a1 = (var_a1 + (*(u8 *)((u8 *)var_a3 + 0x8F))) & 0xFF;
        if (var_s1_3 < 0) {
            var_s1_3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if ((var_a0_2 != 0) && (var_s1_3 != (*(s8 *)((u8 *)arg0 + 0x2E)))) {
            goto loop_30;
        }
    }
    temp_v0_3 = (*(s8 *)((u8 *)var_a3 + 0x64));
    if (temp_v0_3 != -1) {
        sp34 = var_a3;
        sp30 = var_t2;
        (*(s32 (**)())((u8 *)&D_8008FC34 + (temp_v0_3 * 4)))(arg0);
    }
    temp_v0_4 = (*(s8 *)((u8 *)var_a3 + 0x68));
    if (temp_v0_4 != -1) {
        sp34 = var_a3;
        sp30 = var_t2;
        (*(s32 (**)())((u8 *)&D_8008FC3C + (temp_v0_4 * 4)))(arg0);
    }
    temp_v0_5 = (*(s8 *)((u8 *)var_a3 + 0x61));
    if (temp_v0_5 != -1) {
        sp30 = var_t2;
        if ((*(s32 (**)())((u8 *)&D_8008FC20 + (temp_v0_5 * 4)))(arg0) == 0) {
            return 0;
        }
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) > 0) {
        temp_t5 = var_t2 + ((*(s8 *)((u8 *)arg0 + 0x2D)) * 0x24);
        (*(s32 *)((u8 *)arg0 + 0x54)) = (s32) (*(s32 *)((u8 *)temp_t5 + 0));
        (*(s32 *)((u8 *)arg0 + 0x58)) = (s32) (*(s32 *)((u8 *)temp_t5 + 4));
        (*(s32 *)((u8 *)arg0 + 0x5C)) = (s32) (*(s32 *)((u8 *)temp_t5 + 8));
        return 1;
    }
    (*(s32 *)((u8 *)arg0 + 0x54)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x58)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x5C)) = 0;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196CB8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151970BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151976B8.s")

f32 func_15197F68(s32 arg0) {
    return 1.32f;
}

f32 func_15197F7C(s32 arg0) {
    return (f32) func_151422C0(0xA, (s32) "power", 1, 0x1F4, "../Effects/CharacterFlameThrower/characterflamethrower.c", 0x8CC) * 0.01f;
}

f32 func_15197FD8(s32 arg0) {
    return 10.9f;
}

void func_15197A7C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 8);
    }
}

s32 func_15198024(u8 *arg0) {
    *(f32 *)(arg0 + 0x140) *= *(f32 *)(arg0 + 0x15C);
    *(f32 *)(arg0 + 0x144) += *(f32 *)(arg0 + 0x158) * D_800BE9A4;
    *(f32 *)(arg0 + 0x148) *= *(f32 *)(arg0 + 0x15C);
    *(f32 *)(arg0 + 0x14C) *= *(f32 *)(arg0 + 0x160);
    *(f32 *)(arg0 + 0x150) += *(f32 *)(arg0 + 0x158) * D_800BE9A4;
    *(f32 *)(arg0 + 0x154) *= *(f32 *)(arg0 + 0x160);
    *(f32 *)(arg0 + 0x34) += *(f32 *)(arg0 + 0x140) * D_800BE9A4;
    *(f32 *)(arg0 + 0x38) += *(f32 *)(arg0 + 0x144) * D_800BE9A4;
    *(f32 *)(arg0 + 0x3C) += *(f32 *)(arg0 + 0x148) * D_800BE9A4;
    *(f32 *)(arg0 + 0x40) += *(f32 *)(arg0 + 0x14C) * D_800BE9A4;
    *(f32 *)(arg0 + 0x44) += *(f32 *)(arg0 + 0x150) * D_800BE9A4;
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg0 + 0x154) * D_800BE9A4;
    return 1;
}

typedef struct {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xE];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
    u8 pad5D[0x107];
    f32 unk164;
    s16 unk168;
    s16 unk16A;
} struct_1519812C;

s32 func_1519812C(struct_1519812C *arg0) {
    arg0->unk30 -= arg0->unk30 * arg0->unk164;
    arg0->unk2C -= arg0->unk2C * arg0->unk164;
    if (arg0->unk1C < arg0->unk168) {
        arg0->unk5C = arg0->unk1C * arg0->unk16A;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198180.s")

void func_15199924(u8 *arg0);
void func_151985C4(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    s32 cur;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0 || arg2 == 2 || arg2 == 0x8) {
        if (*(s32 *)p == arg1[0] || p[4] == ((u8 *)arg1)[4]) {
            func_15199924(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)p) {
            *(s32 *)p = arg1[1];
            p[4] = ((u8 *)arg1)[9];
        } else if (arg1[1] == *(s32 *)p) {
            *(s32 *)p = arg1[0];
            p[4] = ((u8 *)arg1)[8];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198D3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198EEC.s")

#ifdef NON_MATCHING
/* P163: D_8008FC30 is the one-entry start-sound table (FC34 / FC38 / FC3C are separate update / stop / extra tables,
   each indexed by its own record byte, -1 = none); func_15196438 (asm) stores the entry's v0 as the record's u16 voice handle (`sh $v0, 0xB2($sp) = record + 0x66`), so this returns func_10010F30's handle. */
// emitter_sound_start: starts sound 0x1AA at full volume and returns its voice handle
u16 func_151991D0(void) {
    return func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#else
void func_151991D0(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#endif

void func_15199200(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;
    u16 temp_a0;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(u8 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        temp_a0 = *(u16 *)(temp_v0 + 0x66);
        if (temp_a0 != 0) {
            func_1000F91C(temp_a0, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 0)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 4)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x24 + (0, temp_v1))) + 8)), 0x1F4, 0x1388); // fakematch: (0, x) comma flips commutative operand order
        }
    }
}

void func_151992B0(u8 *arg0) {
    u8 *p;
    u16 t;
    p = *(u8 **)(arg0 + 0x98);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        t = *(u16 *)(p + 0x66);
        if (t != 0) {
            func_100111C8(t);
        }
    }
}

void func_151992EC(s32 arg0) {
}

#ifdef NON_MATCHING
u8 *func_15148310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern s32 D_800A8B08;

void func_151992F8(u8 *arg0, u8 *arg1) {
    struct {
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        u8 padDC[0x4];
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        u8 padE4[0x4];
        s32 uE8;
        u8 padEC[0x8];
        s16 uF4;
        s16 uF6;
        u8 padF8[0x5];
        s8 uFD;
        u8 padFE[0xA];
        s32 u108;
        s32 u10C;
        s32 u110;
        s32 u114;
        s32 u118;
        s32 u11C;
        s32 u120;
        s8 u124;
        s8 u125;
    } sp;
    f32 spBC;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s4;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x98));
    sp.uF6 = 1;
    sp.uE1 = 0xA;
    sp.uE2 = 0xFF;
    sp.uE0 = 0x28;
    sp.uE3 = 0x82;
    (*(f32 *)((u8 *)(&sp.uE8) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
    (*(f32 *)((u8 *)(&sp.uE8) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    temp_s0 = (u8 *) &D_800A8B08 + (*(u8 *)((u8 *)temp_s4 + 0x74)) * 0x24;
    (*(f32 *)((u8 *)(&sp.uE8) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
    sp.u108 = 0;
    sp.u10C = 1;
    sp.u110 = 0x160600;
    sp.u114 = 3;
    sp.u118 = 0x10;
    sp.u11C = 0x80;
    sp.u120 = 0x20;
    sp.u124 = 0;
    sp.u125 = 9;
    do {
        temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 8))) + (*(f32 *)((u8 *)temp_s0 + 4));
        temp_s1 = func_150ADA20() & 0xFF;
        temp_s2 = func_150ADA20() & 0xFF;
        temp_f22 = func_151423D8((temp_s1 - 0x40) & 0xFF);
        temp_f24 = func_151423D8(temp_s1 & 0xFF);
        temp_f26 = func_151423D8((temp_s2 - 0x40) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0));
        temp_f12 = temp_f2 * func_151423D8(temp_s2 & 0xFF);
        temp_f28 = (*(f32 *)((u8 *)arg1 + 0)) + (temp_f12 * temp_f22);
        temp_f30 = (*(f32 *)((u8 *)arg1 + 4)) - (temp_f2 * temp_f26);
        spBC = (*(f32 *)((u8 *)arg1 + 8)) + (temp_f12 * temp_f24);
        sp.uFD = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x22)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x20));
        sp.uF4 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
        sp.uC8 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x10))) + (*(f32 *)((u8 *)temp_s0 + 0xC));
        sp.uD8 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x18))) + (*(f32 *)((u8 *)temp_s0 + 0x14));
        sp.uCC = (temp_f28 - (*(f32 *)((u8 *)arg0 + 0x10))) * temp_f20;
        sp.uD0 = (temp_f30 - (*(f32 *)((u8 *)arg0 + 0x14))) * temp_f20;
        sp.uD4 = (spBC - (*(f32 *)((u8 *)arg0 + 0x18))) * temp_f20;
        func_15148310(&sp.uE8, &sp.uC8, 0, 1, 0, 0, 0, 0, 0, 0, 0, &sp.u108, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(f32 *)((u8 *)temp_s4 + 0x7C)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 0x7C)) - 1.0f);
    } while ((*(f32 *)((u8 *)temp_s4 + 0x7C)) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151992F8.s")
#endif
#ifdef NON_MATCHING
void *func_15167D84(void *, s32, s32, s32, s32, s32);
extern s32 D_800908C4;
extern u8 D_800A8B50[]; /* 0x18-byte burst descriptors: f32 radius, speed base, speed range; s16 pairs (base, range) */

// spray_particles_burst: while the owner's counter (+0x88 of arg0's data) is above 1, spawns one particle per unit
// (func_15167D84, the 0x38-byte template below, P124: one struct instead of m2c's 26 separate locals): random
// direction on a sphere of the descriptor's radius around arg1, velocity = offset from arg0's position times a
// random speed, random life / size / scale from the descriptor (D_800A8B50[data[0x80]]).
void func_1519961C(u8 *arg0, u8 *arg1) {
    struct {
        void *u0;
        s32 u4;
        s32 u8;
        s16 uC;
        s16 uE;
        s16 u10;
        s16 u12;
        s16 u14;
        s16 u16;
        s16 u18;
        s16 u1A;
        s8 u1C;
        s8 u1D;
        s8 u1E;
        s8 u1F;
        s16 u20;
        s16 u22;
        s16 u24;
        s16 u26;
        s16 u28;
        u8 u2A;
        u8 u2B;
        u8 u2C;
        u8 u2D;
        u8 u2E;
        u8 u2F;
        u8 u30;
        u8 u31;
        u8 u32;
        u8 pad33;
        s16 u34;
        u8 pad36[2];
    } t;
    u8 *data;
    u8 *desc;
    f32 speed;
    f32 radius;
    f32 ring;
    f32 sinA;
    f32 cosA;
    f32 sinB;
    s32 a;
    s32 b;
    s16 v;

    data = *(u8 **)(arg0 + 0x98);
    t.u10 = *(f32 *)(arg0 + 0x10);
    desc = &D_800A8B50[data[0x80] * 0x18];
    t.u12 = *(f32 *)(arg0 + 0x14);
    t.u1C = 0;
    t.u1E = 0;
    t.u1D = 0;
    t.u2C = 0xFF;
    t.u2D = 0xFF;
    t.u2E = 0xFF;
    t.u30 = 0;
    t.u31 = 0;
    t.u32 = 0;
    t.u2F = 0xFF;
    t.u1F = -1;
    t.u34 = 0x12;
    t.uC = 0;
    t.uE = 0;
    t.u0 = &D_800908C4;
    t.u28 = 300;
    t.u14 = *(f32 *)(arg0 + 0x18);
    do {
        speed = func_150ADA68() * *(f32 *)(desc + 8) + *(f32 *)(desc + 4);
        a = func_150ADA20() & 0xFF;
        b = func_150ADA20() & 0xFF;
        sinA = func_151423D8((a - 0x40) & 0xFF);
        cosA = func_151423D8(a);
        sinB = func_151423D8((b - 0x40) & 0xFF);
        radius = *(f32 *)(desc + 0);
        ring = radius * func_151423D8(b);
        t.u16 = ((*(f32 *)(arg1 + 0) + ring * sinA) - *(f32 *)(arg0 + 0x10)) * speed;
        t.u20 = ((*(f32 *)(arg1 + 4) - radius * sinB) - *(f32 *)(arg0 + 0x14)) * speed;
        t.u18 = ((*(f32 *)(arg1 + 8) + ring * cosA) - *(f32 *)(arg0 + 0x18)) * speed;
        t.u22 = func_150ADA20() % (u32) (*(s16 *)(desc + 0xE) + 1) + *(s16 *)(desc + 0xC);
        t.u2A = func_150ADA20() % (u32) (*(s16 *)(desc + 0x12) + 1) + *(s16 *)(desc + 0x10);
        v = func_150ADA20() % (u32) (*(s16 *)(desc + 0x16) + 1) + *(s16 *)(desc + 0x14);
        t.u26 = v;
        t.u24 = v;
        func_15167D84(&t, 0, 0, -1, arg0[0xC], arg0[1]);
        *(f32 *)(data + 0x88) -= 1.0f;
    } while (*(f32 *)(data + 0x88) > 1.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519961C.s")
#endif
void func_15199924(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);

    arg0[0x30] = 0;
    *(u16 *)(arg0 + 0x1E) &= 0xFFFD;
    temp_v0[6] |= 1;
    temp_v0[6] |= 4;
}

void func_15199954(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 0;
    }
}

void func_151999BC(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199A28.s")

void func_15199834(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } sp18;

    if (arg0 != NULL) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg0[0x3B];
        func_151482D4(&sp18, 0x26);
    }
}

void func_15199DDC(struct102 *arg0, s32 *arg1, u8 arg2) {
    s32 id;
    s32 cur;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x98);
    if (arg2 == 0 || arg2 == 2 || arg2 == 0x26) {
        if (*(s32 *)p == arg1[0] || p[4] == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)p) {
            *(s32 *)p = arg1[1];
            p[4] = ((u8 *)arg1)[9];
        } else if (arg1[1] == *(s32 *)p) {
            *(s32 *)p = arg1[0];
            p[4] = ((u8 *)arg1)[8];
        }
    }
}

void func_15199EF0(void *);
void func_15199E98(void *arg0) {
    func_15199EF0(arg0);
    func_15147E64(arg0);
}

void func_15199EC4(void *arg0) {
    func_15199EF0(arg0);
    func_15147E98(arg0);
}

extern s32 D_8008FC54;
extern s32 D_8008FC60;

void func_15199EF0(void *arg0) {
    u8 *v = *(u8 **)((u8 *)arg0 + 0x98);
    s8 i = v[0x39];
    u8 *t;
    if (i != -1) {
        ((void (**)(u8 *))&D_8008FC60)[i](arg0);
    }
    i = v[0x36];
    if (i != -1) {
        ((void (**)(u8 *))&D_8008FC54)[i](arg0);
    }
    t = *(u8 **)(v + 0x148);
    if (t != NULL) {
        func_1516972C(t);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15199F80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519A1A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519AF14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519BA28.s")

void func_1519C38C(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    vertex sp4 = *(vertex *)arg1;

    arg1[1] += arg2 * arg3;
    arg0[0] += sp4.x * arg3;
    arg0[1] += sp4.y * arg3 + 0.5f * arg2 * arg3 * arg3;
    arg0[2] += sp4.z * arg3;
}

void func_1519C428(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 0;
    }
}

void func_1519C490(u8 *arg0) {
    u8 **q = *(u8 ***)(arg0 + 0x98); // fakematch: q/r temps and u32 key (permuter) pin registers
    u8 *r = *q;
    s32 i = 0;
    s32 found = 0;
    u32 key = r[0x3B]; // fakematch: u32 (not u8) key picks the register
    u8 *p = &D_800A8E7C;

    do {
        if (key == *p) {
            found = 1;
        } else {
            i++;
            p++;
        }
    } while (found == 0 && i < 6);
    if (found != 0) {
        ((u8 **)D_800E0900)[i][0x14] = 1;
    }
}

#ifdef NON_MATCHING
/* P163: D_8008FC58 is the one-entry start-sound table (FC5C / FC64 are separate tables used by func_15199F80);
   func_15199A28 (asm) stores the entry's v0 as the record's u16 voice handle (`sh $v0, 0x130($t5) = record + 0x130`), so this returns func_10010F30's handle. */
// emitter2_sound_start: starts sound 0x1AA at full volume and returns its voice handle
u16 func_1519C4FC(void) {
    return func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#else
void func_1519C4FC(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}
#endif

void func_1519C52C(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;
    u16 temp_a0;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(u8 **)(arg0 + 0x94);
    if (*(s8 *)(arg0 + 0x2C) != 0) {
        temp_a0 = *(u16 *)(temp_v0 + 0x130);
        if (temp_a0 != 0) {
            func_1000F91C(temp_a0, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 0)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 4)), (s16) (s32) (*(f32 *)(((u8 *)((*(s8 *)(arg0 + 0x2D)) * 0x28 + (0, temp_v1))) + 8)), 0x1F4, 0x1388); // fakematch: (0, x) comma flips commutative operand order
        }
    }
}

void func_1519C5DC(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x98);
    u16 temp_a1 = *(u16 *)(temp_v0 + 0x130);

    if (temp_a1 != 0) {
        func_100111C8(temp_a1);
    }
}

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
void *memcpy(void *, const void *, s32);

struct225 *func_1519C60C(s32 arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    Header2 header2;
    s32 tmp;
    f32 data[8];

    tmp = arg0;
    header.unk0 = 2;
    header.unk1 = 2;
    header.unk2 = 300;
    header.unk4 = 0x22;
    data[0] = 35.0f;
    data[1] = 5.0f;
    data[2] = 110.0f;
    data[3] = 1.0f;
    data[4] = 0.0f;
    data[5] = 7.0f;
    data[6] = 0.2489f;
    data[7] = 127.0f;
    header2.unk0 = arg1[0];
    header2.unk4 = arg1[1];
    header2.unk8 = arg1[2];
    temp_v0 = func_151602C0(&header, &header2, arg2, arg3, arg4, arg5, 0xFF, 0, 0x24, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, data, sizeof(data));
        memcpy((u8 *)temp_v0 + 0x38, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

void func_1519C770(void *arg0) {
    func_1519C7C8(arg0);
    func_151617C4(arg0);
}

void func_1519C79C(void *arg0) {
    func_1519C7C8(arg0);
    func_151617E4(arg0);
}

void func_1519C7C8(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(*(u8 **)(arg0 + 0x38) + 0x98);
    *(s32 *)(temp_v0 + 0x148) = 0;
}

#ifdef NON_MATCHING
s32 func_1519C7DC(u8 *arg0) {
    struct {
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
    } sp;
    f32 sp2C;
    f32 sp28;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f8;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x110;
    (*(f32 *)((u8 *)(&sp.u48) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
    temp_f0 = D_800BE9A4 * D_800BE9A4;
    (*(f32 *)((u8 *)(&sp.u48) + 4)) = (f32) (*(f32 *)((u8 *)temp_v0 + 4));
    (*(f32 *)((u8 *)(&sp.u48) + 8)) = (f32) (*(f32 *)((u8 *)temp_v0 + 8));
    (*(f32 *)((u8 *)(&sp.u3C) + 0)) = (*(f32 *)((u8 *)arg0 + 0x11C));
    (*(f32 *)((u8 *)(&sp.u3C) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x120));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x124));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x128));
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x114)) + (temp_f12 * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x120)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x120)) + (temp_f12 * D_800BE9A4));
    var_v1 = D_800BE9E4;
    if (var_v1 > 0) {
        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 0x1C));
        temp_f12_2 = (*(f32 *)((u8 *)temp_v0 + 0x20));
        do {
            var_v1 -= 1;
            (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 4)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) * temp_f2);
            (*(f32 *)((u8 *)temp_v0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0xC)) * temp_f12_2);
            (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x10)) * temp_f12_2);
            (*(f32 *)((u8 *)temp_v0 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) * temp_f12_2);
        } while (var_v1 > 0);
    }
    temp_f8 = ((*(f32 *)((u8 *)temp_v0 + 0x10)) - sp.u40) * D_800BEDC8;
    sp28 = temp_f8;
    sp2C = ((*(f32 *)((u8 *)temp_v0 + 0x14)) - sp.u44) * D_800BEDC8;
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((sp.u48 * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 0)) - sp.u48) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((sp.u4C * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 4)) - sp.u4C) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((sp.u50 * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 8)) - sp.u50) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + ((sp.u3C * D_800BE9A4) + (0.5f * (((*(f32 *)((u8 *)temp_v0 + 0xC)) - sp.u3C) * D_800BEDC8) * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + ((sp.u40 * D_800BE9A4) + (0.5f * temp_f8 * temp_f0)));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + ((sp.u44 * D_800BE9A4) + (0.5f * sp2C * temp_f0)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519C7DC.s")
#endif
s32 func_1519CA54(u8 *arg0) {
    u8 *p;
    s32 i;
    s32 v;

    p = arg0 + 0x110;
    for (i = D_800BE9E4; i > 0; i--) {
        *(f32 *)(arg0 + 0x2C) -= *(f32 *)(arg0 + 0x2C) * *(f32 *)(p + 0x24);
        *(f32 *)(arg0 + 0x30) -= *(f32 *)(arg0 + 0x30) * *(f32 *)(p + 0x24);
    }
    if (*(s16 *)(arg0 + 0x1C) < *(s16 *)(p + 0x28)) {
        v = *(s16 *)(p + 0x2A) * *(s16 *)(arg0 + 0x1C);
        if (v < arg0[0x5C]) {
            arg0[0x5C] = v;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
s16 *func_1519CADC(u8 *arg0, s16 arg1) {
    struct {
        u8 u3F;
        f32 u40;
        s32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        u8 pad54[0x18];
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 * u84;
        s16 * u88;
        s16 * u8C;
    } sp;
    u8 *sp34;
    u8 *sp30;                                     /* compiler-managed */
    f32 sp2C;
    f32 *temp_a2;
    f32 *temp_v0;
    f32 temp_f0;
    f32 temp_f0_2;
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
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_t2;
    s16 *temp_t4;
    s16 *temp_t5;
    u8 *temp_a1;
    u8 *temp_v1;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &sp.u8C, &sp.u3F);
    sp.u88 = sp.u8C;
    if (sp.u8C != NULL) {
        if (sp.u3F != 0) {
            temp_v1 = arg0 + (arg1 * 4);
            temp_a1 = arg0 + 0xC0;
            sp30 = temp_a1;
            sp34 = temp_v1;
            memcpy((*(u8 **)((u8 *)temp_v1 + 0x100)), temp_a1, 0x40);
            memcpy((*(u8 **)((u8 *)temp_v1 + 0x100)) + 0x40, temp_a1, 0x40);
        }
        temp_v0 = func_15144B34((s32) arg1);
        temp_a2 = temp_v0;
        sp.u78 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34));
        sp.u7C = (*(f32 *)((u8 *)arg0 + 0x44)) - (*(f32 *)((u8 *)arg0 + 0x38));
        temp_f4 = (*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C));
        sp.u80 = temp_f4;
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x34));
        temp_f12 = temp_f2 + (sp.u78 * temp_f0);
        temp_f14 = (*(f32 *)((u8 *)arg0 + 0x38)) + (sp.u7C * temp_f0);
        sp.u78 = temp_f12 - temp_f2;
        temp_f16 = (*(f32 *)((u8 *)arg0 + 0x3C)) + (temp_f4 * temp_f0);
        sp.u7C = temp_f14 - (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u74 = temp_f16;
        sp.u70 = temp_f14;
        sp.u6C = temp_f12;
        sp.u84 = temp_v0;
        sp.u80 = temp_f16 - (*(f32 *)((u8 *)arg0 + 0x3C));
        func_15145548(temp_f12, temp_f14, arg0 + 0x34, &sp.u78, temp_a2, &sp.u48, &sp.u44);
        temp_f0_2 = sp.u48 - (*(f32 *)((u8 *)sp.u84 + 0));
        temp_f2_2 = sp.u4C - (*(f32 *)((u8 *)sp.u84 + 4));
        temp_f12_2 = sp.u50 - (*(f32 *)((u8 *)sp.u84 + 8));
        temp_f18 = (sp.u7C * temp_f12_2) - (temp_f2_2 * sp.u80);
        temp_f16_2 = (sp.u80 * temp_f0_2) - (temp_f12_2 * sp.u78);
        sp30 = (u8 *)(s32)temp_f16_2;
        temp_f8 = (sp.u78 * temp_f2_2) - (temp_f0_2 * sp.u7C);
        sp2C = temp_f8;
        temp_f14_2 = (temp_f18 * temp_f18) + (temp_f16_2 * temp_f16_2) + (temp_f8 * temp_f8);
        sp.u40 = temp_f14_2;
        if (temp_f14_2 != 0.0f) {
            temp_f2_3 = (*(f32 *)((u8 *)arg0 + 0x2C)) / sqrtf(sp.u40);
            var_f12 = temp_f18 * temp_f2_3;
            var_f14 = (s32)sp30 * (s32)temp_f2_3;
            var_f16 = temp_f8 * temp_f2_3;
        } else {
            var_f16 = 0.0f;
            var_f12 = 0.0f;
            var_f14 = 0.0f;
        }
        (*(s16 *)((u8 *)sp.u8C + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t2 = sp.u8C + 0x10;
        sp.u8C = temp_t2;
        *temp_t2 = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) - var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t4 = sp.u8C + 0x10;
        sp.u8C = temp_t4;
        *temp_t4 = (s16) (s32) (sp.u6C - var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) (sp.u70 - var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.u74 - var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        temp_t5 = sp.u8C + 0x10;
        sp.u8C = temp_t5;
        *temp_t5 = (s16) (s32) (sp.u6C + var_f12);
        (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) (sp.u70 + var_f14);
        (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.u74 + var_f16);
        (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
        return sp.u88;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CADC.s")
#endif
s32 func_1519CE80(u8 *arg0)
{
  u8 *new_var;
  u16 temp_a1;
  u8 *temp_v0;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x98));
  new_var = (u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)));
  ;
  if ((*((s32 *) (((u8 *) temp_v0) + 0x158))) != (*((u16 *) (new_var + 0x84))))
  {
    if ((*((s32 *) (((u8 *) temp_v0) + 0x15C))) != (*((u16 *) (new_var + 0x84))))
    {
      return 0;
      return 1;
    }
  }
  return 1;
}

s32 func_1519CEB8(s32 arg0) {
    func_1519D320(arg0, 0.25f, 0x1C);
    return 0;
}

s32 func_1519CEE0(s32 arg0) {
    func_1519D320(arg0, 0.5f, 0x1D);
    return 0;
}

s32 func_1519CF08(s32 arg0) {
    func_1519D320(arg0, 0.2f, 0x1D);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CF34.s")

void func_1519D2D4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x28);

    if ((*(s32 *)temp_v0 == 0) || (temp_v0[4] == 0xFF) || (arg0[0x2C] != temp_v0[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519D320.s")
