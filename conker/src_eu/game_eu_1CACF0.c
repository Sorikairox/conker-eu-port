#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1519D4E0(u8 arg0) {
    u8 sp1C[4];
    sp1C[0] = arg0;
    func_151482D4(sp1C, 6);
}

void func_1519D510(u8 *arg0)
{
  u8 *temp_v0;
  temp_v0 = *((u8 **) (arg0 + 0x98));
  arg0[0x30] = 0;
  *((u16 *) (arg0 + 0x1E)) = *((u16 *) (arg0 + 0x1E)) & 0xFFFD;
  temp_v0[6] |= 1;
  temp_v0[6] |= 4;
}

void func_1519D540(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E64(arg0);
}

void func_1519D570(u8 *arg0) {
    s32 *p = *(s32 **)(arg0 + 0x98);
    func_1514EDF0(arg0, *p);
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D5A0.s")

typedef struct { f32 x, y, z; } V3;
typedef struct {
    V3 pos;
    V3 vel;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    u8 unk20;
    u8 pad21[3];
} Trail;
typedef struct {
    u8 pad0[6];
    u8 flags;
    u8 pad7[0x1D];
    f32 unk24;
    u8 pad28[8];
    f32 unk30;
    f32 unk34;
    u8 pad38[0xE];
    s16 unk46;
} TrailDef;
typedef struct {
    u8 pad0[0x25];
    u8 count;
    u8 pad26[6];
    s8 n;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    V3 pos;
    u8 pad60[0x34];
    Trail *trails;
    TrailDef *def;
} TrailObj;

s32 func_1519D7B0(TrailObj *arg0) {
    TrailDef *def = arg0->def;
    Trail *trails = arg0->trails;
    s32 i;
    Trail *t;
    s16 life;

    if (arg0->n < 2 && (def->flags & 1)) {
        return 0;
    }
    i = arg0->tail;
    while (i != arg0->head) {
        i--;
        if (i < 0) {
            i = arg0->count - 1;
        }
        t = &trails[i];
        t->unk20 = 0xFF;
        t->vel.x *= def->unk30;
        t->vel.y += def->unk24 * D_800BE9A4;
        t->vel.z *= def->unk30;
        t->pos.x += trails[i].vel.x * D_800BE9A4;
        t->pos.y += trails[i].vel.y * D_800BE9A4;
        life = t->unk1E;
        t->pos.z += trails[i].vel.z * D_800BE9A4;
        if (life > 0) {
            t->unk1E = life - D_800BE9E4;
        } else {
            t->unk1C -= D_800BE9E4 * def->unk46;
        }
        t->unk18 += D_800BE9A4 * def->unk34;
        if (t->unk1C < 0) {
            def->flags &= ~2;
            while (i != arg0->head) {
                arg0->head++;
                if (arg0->head == arg0->count) {
                    arg0->head = 0;
                }
                arg0->n--;
            }
            trails[arg0->head].unk1C = 0;
        }
    }
    if (arg0->n > 0) {
        arg0->pos = trails[arg0->head].pos;
    } else {
        arg0->pos.x = 0.0f; arg0->pos.y = 0.0f; arg0->pos.z = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519D9C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519DF64.s")

void func_1519E764(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 temp_a0;
  s32 temp_t6;
  s32 temp_v1;
  u8 *temp_v0;
  temp_t6 = arg2;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x98));
  if (temp_t6 == 0)
  {
    if (((*((s32 *) (((u8 *) temp_v0) + 0))) == (*((s32 *) (((u8 *) arg1) + 0)))) || ((*((u8 *) (((u8 *) temp_v0) + 4))) == (*((u8 *) (((u8 *) arg1) + 4)))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 6)
  {
    if ((*arg1) == (*((u8 *) (((u8 *) temp_v0) + 0x4C))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 7)
  {
    if (((*((s32 *) (((u8 *) temp_v0) + 0))) == (*((s32 *) (((u8 *) arg1) + 0)))) || ((*((u8 *) (((u8 *) temp_v0) + 4))) == (*((u8 *) (((u8 *) arg1) + 4)))))
    {
      func_1519D510(arg0);
    }
  }
  else
    if (temp_t6 == 0x2D)
  {
    ;
    temp_a0 = *((s32 *) (((u8 *) arg1) + 0));
    if (temp_a0 == (*((s32 *) (((u8 *) temp_v0) + 0))))
    {
      *((s32 *) (((u8 *) temp_v0) + 0)) = *((s32 *) (((u8 *) arg1) + 4));
      *((u8 *) (((u8 *) temp_v0) + 4)) = (u8) (*((u8 *) (((u8 *) arg1) + 9)));
      return;
    }
    if ((*((s32 *) (((u8 *) arg1) + 4))) == (*((s32 *) (((u8 *) temp_v0) + 0))))
    {
      *((s32 *) (((u8 *) temp_v0) + 0)) = temp_a0;
      *((u8 *) (((u8 *) temp_v0) + 4)) = (u8) (*((u8 *) (((u8 *) arg1) + 8)));
    }
  }
}

s32 func_1519E874(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p = arg0;
    f32 sp1C[2];
    if (*(s32 *)(*(u8 **)p + 0x1D4) == 0) {
        return 0;
    }
    func_15143134(p + 8, sp1C, (p[5] << 6) + *(s32 *)(*(u8 **)p + 0x1D4));
    arg1[0] = ((sp1C[0] - arg2) * arg5) + arg2;
    arg1[1] = ((sp1C[1] - arg3) * arg5) + arg3;
    arg1[2] = ((sp1C[2] - arg4) * arg5) + arg4;
    return 1;
}

void func_1519E688(void);
void func_1519D5A0(s32, s32, s32, s32, s32, s32);
// fakematch: volatile arg2 reloads the byte after each call like the original
void func_1519E92C(s32 arg0, s16 arg1, volatile u8 arg2, s32 arg3) {
    func_1519E688();
    func_1519D5A0(arg0, 3, 0x12C, 0, arg2, arg3);
    func_1519D5A0(arg0, 4, 0x12C, 0, arg2, arg3);
    func_151491F4(arg1, 6, -1, 1, 3, 0, arg2, arg3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E9D4.s")

void func_1519EAE0(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

void func_1519EB8C(struct102 *arg0, s32 arg1, u8 arg2) {
    if ((arg2 == 0) || (arg2 == 9)) {
        func_1516972C(arg0);
    }
}

void func_1519EBCC(s32 arg0) {
    func_1519D4E0(3);
    func_1519D4E0(4);
}

void func_1519E688(void) {
    func_1519D4E0(3);
    func_1519D4E0(4);
    func_151482D4(0, 9);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519E6BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CACF0/func_1519ECC4.s")

void func_1519ED88(u8 *arg0, s32 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x28;
  if (arg2 == 0) {
    if (*(s32 *)v == arg1[0] || v[4] == ((u8 *)arg1)[4]) {
      func_1516972C((struct102 *)arg0);
      {
        s32 t; // fakematch: block-local declaration = basic-block boundary (unfilled b delay slot, s69)
        D_800E0D50 = 0;
      }
    }
  } else if (arg2 == 0x2D) {
    
    if (arg1[0] == *(s32 *)v) {
      *(s32 *)v = arg1[1];
      v[4] = ((u8 *)arg1)[9];
    } else if (arg1[1] == *(s32 *)v) {
      *(s32 *)v = arg1[0];
      v[4] = ((u8 *)arg1)[8];
    }
  }
}

void func_1519EE3C(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_1514933C(arg0);
}

void func_1519EE68(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_15149368(arg0);
}

void func_1519EE94(struct260 *arg0) {
    D_800E0D50 = 0;
    func_1514933C(arg0);
}

void func_1519EEB8(struct260 *arg0) {
    D_800E0D50 = 0;
    func_15149368(arg0);
}
