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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196560.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15196CB8.s")

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

void func_151991D0(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_151992F8.s")

#ifdef NON_MATCHING
s32 func_15167D84(s32 **, s32, s32, s32, s32, s32);
extern s32 D_800908C4;
extern s32 D_800A8B50;

void func_1519961C(u8 *arg0, u8 *arg1) {
    s16 spC8;
    s8 spC6;
    s8 spC5;
    s8 spC4;
    s8 spC3;
    s8 spC2;
    s8 spC1;
    s8 spC0;
    s8 spBE;
    s16 spBC;
    s16 spBA;
    s16 spB8;
    s16 spB6;
    s16 spB4;
    s8 spB3;
    s8 spB2;
    s8 spB1;
    s8 spB0;
    s16 spAC;
    s16 spAA;
    s16 spA8;
    s16 spA6;
    s16 spA4;
    s16 spA2;
    s16 spA0;
    s32 *sp94;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f2;
    s16 temp_t9;
    s32 temp_s1;
    s32 temp_s2;
    u8 *temp_s0;
    u8 *temp_s4;

    temp_s4 = (*(u8 **)((u8 *)arg0 + 0x98));
    spA4 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x10));
    temp_s0 = ((*(u8 *)((u8 *)temp_s4 + 0x80)) * 0x18) + &D_800A8B50;
    spA6 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14));
    spB0 = 0;
    spB2 = 0;
    spB1 = 0;
    spC0 = 0xFF;
    spC1 = 0xFF;
    spC2 = 0xFF;
    spC4 = 0;
    spC5 = 0;
    spC6 = 0;
    spC3 = 0xFF;
    spB3 = -1;
    spC8 = 0x12;
    spA0 = 0;
    spA2 = 0;
    sp94 = &D_800908C4;
    spBC = 0x12C;
    spA8 = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x18));
    do {
        temp_f20 = (func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 8))) + (*(f32 *)((u8 *)temp_s0 + 4));
        temp_s1 = func_150ADA20() & 0xFF;
        temp_s2 = func_150ADA20() & 0xFF;
        temp_f22 = func_151423D8((temp_s1 - 0x40) & 0xFF);
        temp_f24 = func_151423D8(temp_s1 & 0xFF);
        temp_f26 = func_151423D8((temp_s2 - 0x40) & 0xFF);
        temp_f2 = (*(f32 *)((u8 *)temp_s0 + 0));
        temp_f12 = temp_f2 * func_151423D8(temp_s2 & 0xFF);
        spAA = (s16) (s32) ((((*(f32 *)((u8 *)arg1 + 0)) + (temp_f12 * temp_f22)) - (*(f32 *)((u8 *)arg0 + 0x10))) * temp_f20);
        spB4 = (s16) (s32) ((((*(f32 *)((u8 *)arg1 + 4)) - (temp_f2 * temp_f26)) - (*(f32 *)((u8 *)arg0 + 0x14))) * temp_f20);
        spAC = (s16) (s32) ((((*(f32 *)((u8 *)arg1 + 8)) + (temp_f12 * temp_f24)) - (*(f32 *)((u8 *)arg0 + 0x18))) * temp_f20);
        spB6 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0xE)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0xC));
        spBE = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x12)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x10));
        temp_t9 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x16)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x14));
        spBA = temp_t9;
        spB8 = temp_t9;
        func_15167D84(&sp94, 0, 0, -1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
        (*(f32 *)((u8 *)temp_s4 + 0x88)) = (f32) ((*(f32 *)((u8 *)temp_s4 + 0x88)) - 1.0f);
    } while ((*(f32 *)((u8 *)temp_s4 + 0x88)) > 1.0f);
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

void func_1519C4FC(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_1519CADC.s")

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
