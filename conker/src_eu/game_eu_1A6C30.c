#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15179B70(s32 arg0, s32 arg1);
void func_15179A38(void);
#endif


void func_15179420(void) {
    D_800DD864 = 0;
    D_800DD876 = 0;
    D_800DD444 = 600;
    D_800DD862 = 0xF0;
    D_800DD863 = 0x14;
    D_800DD866 = 0;
    D_800DD870 = 0;
}

extern u16 D_800DD860;
#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32 *);
#else
s32 func_10004074(s32 *);
#endif
void func_1517946C(s32 arg0) {
    s32 i;

    if (arg0 == 2) {
        D_800DD864 = 0;
        D_800DD876 = 0;
        if ((s32 *)D_800DD870 != NULL) {
            for (i = 0; i < 300; i++) {
                if (((s32 **)D_800DD870)[i] != NULL) {
                    func_1516972C((struct102 *)((s32 **)D_800DD870)[i]);
                    ((s32 **)D_800DD870)[i] = NULL;
                }
            }
            func_10004074((s32 *)(D_800DD870 & 0xFFFFFFFF)); // fakematch: permuter mask (puts the table in v0)
            D_800DD870 = 0;
        }
        func_100111C8(D_800DD860);
        D_800DD444 = 0;
        D_800DD866 = 0;
    } else if (arg0 == 3) {
        if (*(s8 *)&D_800DD876 == 0) {
            D_800DD444 = 600;
        } else if (*(s8 *)&D_800DD876 == 3) {
            D_800DD876 = 1;
        }
        D_800DD864 = arg0;
    } else {
        D_800DD864 = arg0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179008.s")
extern s32 D_800DD868[];
void func_15179A38(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 pad; // fakematch: frame slot 0x30 (unknown named local)
    f32 vy;
    f32 vz;
    f32 s;
    f32 a;
    f32 c;
    f32 vx;
    s16 *p;

    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    a = D_800DBFF0->unk398;
    s = func_150AD78C(a);
    c = func_150AD780(a);
    vy = 500.0f * s;
    vz = -500.0f * c;
    vx = 0.0f;
    a = D_800DBFF0->unk3A0;
    s = func_150AD78C(a);
    c = func_150AD780(a);
    x += (vx + (vz * s));
    z += ((vz * c) - vx);
    y += vy;
    p = (s16 *)D_800DD868;
    p[0] = x;
    p[2] = z;
    p[1] = y;
}

typedef struct {
    u8 pad0[0x80];
    s32 u80;
    s16 u84;
    u8 pad86[4];
    s16 u8A;
    s16 u8C;
    s16 u8E;
    s16 u90;
    s16 u92;
    s16 u94;
    u8 pad96[2];
    u16 u98;
    u8 pad9A[2];
    s16 u9C;
    s16 u9E;
    s8 uA0;
    s8 uA1;
    s8 uA2;
    u8 padA3[5];
} Spawn9B70;
s32 func_1516865C(Spawn9B70 *, s32, s32, s32, s32);
s32 func_15168800(Spawn9B70 *, u8, u8);
void func_15179B70(s32 arg0, s32 arg1) {
    s32 x2;
    s32 y2;
    s32 z2;
    s32 x;
    s32 y;
    s32 z;
    u32 r;
    s32 v;
    s32 pad[2];
    Spawn9B70 sp;

    sp.uA0 = 0x11;
    sp.u8A = 0x33;
    sp.uA2 = 1;
    sp.u98 = 0;
    func_1516865C(&sp, 0xFF, 0xFF, 0xFF, 0x50);
    if (r) {} // fakematch: empty test of the not yet set r moves D_800DBFF0 to v0 (permuter)
    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    x2 = func_150ADA20() % 500 + x;
    z2 = func_150ADA20() % 500 + z;
    if (arg0 == 0) {
        y2 = y + 500;
    } else {
        y2 = func_150ADA20() % 500 + y;
    }
    r = func_150ADA20() % 10U;
    sp.u8E = y2;
    sp.u8C = x2;
    sp.u90 = z2;
    sp.u9C = 0;
    sp.u9E = 0;
    sp.u92 = 4;
    sp.u94 = r + 0x23;
    sp.u98 = 0x8C00;
    sp.uA1 = r + 0xA;
    sp.u80 = arg1;
    sp.u84 = D_800DD866;
    v = func_15168800(&sp, 0xFF, 0);
    if (v != 0) {
        ((s32 *)D_800DD870)[D_800DD866] = v;
        D_800DD866++;
    }
}

#ifdef NON_MATCHING
f32 func_150489B0(s32, struct102 *);

void func_15179D20(struct102 *arg0) {
    f32 sp24;
    s32 sp1C;
    f32 temp_f12;
    f32 temp_f2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1_2;
    s32 temp_v0_3;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;

    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0xA0)) - D_800DBFF0->unk300;
    temp_f12 = (f32) (*(s16 *)((u8 *)arg0 + 0x9C)) - D_800DBFF0->unk2F8;
    var_a2 = (s32) (80.0f - ((80.0f * sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12))) / 1000.0f));
    if (var_a2 < 0) {
        var_a2 = 0;
    }
    temp_v1 = (*(u16 *)((u8 *)arg0 + 0xAE));
    (*(s8 *)((u8 *)arg0 + 0xB4)) = (s8) var_a2;
    sp1C = (s32) temp_v1;
    var_v1 = (s32) ((f32) (temp_v1 + ((u32) (D_800DD863 * 0x10 * ((func_150ADA20() & 0xFF) + 0x80)) >> 9)) * 0.88889f);
    if (var_v1 >= 0x3201) {
        var_v1 = 0x3200;
    }
    (*(u16 *)((u8 *)arg0 + 0xAE)) = (u16) var_v1;
    sp24 = (f32) ((*(u8 *)((u8 *)arg0 + 0xB1)) * D_800BE9E4);
    (*(s16 *)((u8 *)arg0 + 0x9C)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x9C)) + (sp24 * func_15048A40(((s32) (*(u16 *)((u8 *)arg0 + 0xAE)) >> 8) & 0xFF)));
    temp_v1_2 = (*(s16 *)((u8 *)arg0 + 0x9C));
    var_a3 = 0;
    (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x9E)) - (sp24 * func_150489B0(((s32) (*(u16 *)((u8 *)arg0 + 0xAE)) >> 8) & 0xFF, arg0)));
    if (temp_v1_2 < ((*(s16 *)((u8 *)D_800DD868 + 0)) - 0x1F4)) {
        (*(s16 *)((u8 *)arg0 + 0x9C)) = (s16) (((*(s16 *)((u8 *)D_800DD868 + 0)) * 0) + temp_v1_2 + 0x3E8);
        goto block_8;
    }
    if (((*(s16 *)((u8 *)D_800DD868 + 0)) + 0x1F4) < temp_v1_2) {
        (*(s16 *)((u8 *)arg0 + 0x9C)) = (s16) ((((*(s16 *)((u8 *)D_800DD868 + 0)) + temp_v1_2) - (*(s16 *)((u8 *)D_800DD868 + 0))) - 0x3E8);
block_8:
        var_a3 = 1;
    }
    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x9E));
    if (temp_v0 < ((*(s16 *)((u8 *)D_800DD868 + 2)) - 0x1F4)) {
        (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) (((*(s16 *)((u8 *)D_800DD868 + 2)) * 0) + temp_v0 + 0x3E8);
        goto block_13;
    }
    if (((*(s16 *)((u8 *)D_800DD868 + 2)) + 0x1F4) < temp_v0) {
        (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) ((((*(s16 *)((u8 *)D_800DD868 + 2)) + temp_v0) - (*(s16 *)((u8 *)D_800DD868 + 2))) - 0x3E8);
block_13:
        var_a3 = 1;
    }
    temp_v0_2 = (*(s16 *)((u8 *)arg0 + 0xA0));
    if (temp_v0_2 < ((*(s16 *)((u8 *)D_800DD868 + 4)) - 0x1F4)) {
        (*(s16 *)((u8 *)arg0 + 0xA0)) = (s16) (((*(s16 *)((u8 *)D_800DD868 + 4)) * 0) + temp_v0_2 + 0x3E8);
        goto block_18;
    }
    if (((*(s16 *)((u8 *)D_800DD868 + 4)) + 0x1F4) < temp_v0_2) {
        (*(s16 *)((u8 *)arg0 + 0xA0)) = (s16) ((((*(s16 *)((u8 *)D_800DD868 + 4)) + temp_v0_2) - (*(s16 *)((u8 *)D_800DD868 + 4))) - 0x3E8);
block_18:
        var_a3 = 1;
    }
    temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0x90));
    if ((temp_v0_3 & 2) && (var_a3 != 0)) {
        D_800DD866 -= 1;
        *(s32 *)(D_800DD870 + ((*(s16 *)((u8 *)arg0 + 0x94)) * 4)) = 0;
        func_1516972C(arg0);
        return;
    }
    if (temp_v0_3 & 1) {
        if (var_a3 != 0) {
            (*(s32 *)((u8 *)arg0 + 0x90)) = (s32) (temp_v0_3 ^ 1);
            return;
        }
        (*(s8 *)((u8 *)arg0 + 0xB4)) = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_15179D20.s")
#endif
int func_1517A028(void)
{
  s32 temp_v0;
  s32 var_v1;
  u8 **var_a0;
  s32 temp_a1;
  u8 *temp_v0_2;
  int new_var;
  new_var = D_800DD866 - 1;
  temp_v0 = new_var;
  if (temp_v0 >= 0)
  {
    var_v1 = temp_v0 * 4;
    var_a0 = D_800DD870 + var_v1;
    loop_2:
    temp_v0_2 = *var_a0;

    var_v1 -= 4;
    if (temp_v0_2 != 0)
    {
      if (((*((s32 *) (((u8 *) temp_v0_2) + 0x90))) & 2) == 0)
      {
        *((s32 *) (((u8 *) temp_v0_2) + 0x90)) |= 2;
        return;
      }
    }
    var_a0 -= 1; // fakematch: dead pointer decrement
    if (var_v1 < 0)
    {
    }
    else
    {
      goto loop_2;
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A6C30/func_1517A084.s")

void func_1517A220(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 dist;

    temp_f2 = (f32) *(s16 *)(arg0 + 0xA0) - D_800DBFF0->unk300;
    temp_f12 = (f32) *(s16 *)(arg0 + 0x9C) - D_800DBFF0->unk2F8;
    dist = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    *(u8 *)(arg0 + 0xB4) = (s8)(u32)(255.0f - ((160.0f * dist) / 1000.0f));
}
