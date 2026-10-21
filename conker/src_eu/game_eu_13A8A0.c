#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D090.s")

Gfx *func_1510D338(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetPrimColor(gdl++, 0xF2, 0, D_800D9F88[arg3 * 3], D_800D9F88[arg3 * 3 + 1], D_800D9F88[arg3 * 3 + 2], arg1);
    gDPSetEnvColor(gdl++, D_800D9F98[arg3 * 3], D_800D9F98[arg3 * 3 + 1], D_800D9F98[arg3 * 3 + 2], arg2);
    return gdl;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D3E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D66C.s")

extern u16 D_800920D0[];
extern s32 D_1A3B40;
s32 func_1510D8F4(s32 arg0) {
    s32 sum;
    s32 i;

    sum = (s32)&D_1A3B40;
    for (i = 0; i < arg0; i++) {
        sum += D_800920D0[i];
    }
    return sum;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510D984.s")

void func_1510DB88(s32 arg0, s32 arg1) {
    s8 *p = &D_800BC860[arg0];
    s8 v = *p;
    if (v != 0) {
        *p = (v & 0x40) | arg1;
    }
}

void func_1510DC14(s32);
void func_10004074(s16 *);
void func_1510DBB0(s16 *arg0)
{
  s16 *new_var;
  s16 *q = arg0;
  s16 *p;
  s16 *end;
  s16 n = q[0];
  p = q + 1;
  new_var = p + n; // fakematch: hoists p + n before the guard
  if (n > 0)
  {
    end = new_var;
    do
    {
      func_1510DC14(*p);
      p++;
    }
    while (end != p);
  }
  func_10004074(q);
}

void func_1510DC14(s32 arg0) {
    u8 *temp_v0 = &D_800DA388[arg0];
    if (D_800BC860[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < D_800DA378) {
                    D_800DA378 = arg0;
                }
                if (D_800DA37C < arg0) {
                    D_800DA37C = arg0;
                }
                func_1510DB88(arg0, 3);
            }
        }
    }
}

void func_1510DCA0(s32 arg0) {
    u8 *temp_v0 = &D_800DA388[arg0];
    if (D_800BC860[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < D_800DA378) {
                    D_800DA378 = arg0;
                }
                if (D_800DA37C < arg0) {
                    D_800DA37C = arg0;
                }
                func_1510DB88(arg0, 2);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DD2C.s")

extern s8 D_800DA2F0;

void func_1510DDE4(void) {
    D_800DA2F0 = 0;
}

extern u8 D_800DA2F8[];

void func_1510DDF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;
    s32 i = (u8)D_800DA2F0;

    if (i < 8) {
        p = D_800DA2F8 + i * 16;
        *(s32 *)(p + 0) = arg0;
        *(s32 *)(p + 4) = arg1;
        *(s32 *)(p + 8) = arg2;
        p[0xC] = arg3;
        p[0xD] = arg4;
        D_800DA2F0 = i + 1;
    }
}

#ifdef NON_MATCHING
u8 *func_1510DE40(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *var_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_a2;

    var_a2 = arg0;
    var_a0 = D_800DA2F8;
    var_v0 = 0;
    if ((s32) (u8) D_800DA2F0 > 0) {
        do {
            var_v0 += 1;
            if (arg1 == (*(s32 *)((u8 *)var_a0 + 0))) {
                temp_v1 = var_a2;
                var_a2 += 8;
                (*(s32 *)((u8 *)temp_v1 + 0)) = (s32) ((((*(u8 *)((u8 *)var_a0 + 0xC)) * 4) & 0xFFFF) | 0xDB060000);
                (*(s32 *)((u8 *)temp_v1 + 4)) = (s32) (*(s32 *)((u8 *)var_a0 + 4));
                if ((*(s32 *)((u8 *)var_a0 + 8)) != 0) {
                    temp_v1_2 = var_a2;
                    var_a2 += 8;
                    (*(s32 *)((u8 *)temp_v1_2 + 0)) = (s32) ((((*(u8 *)((u8 *)var_a0 + 0xD)) * 4) & 0xFFFF) | 0xDB060000);
                    (*(s32 *)((u8 *)temp_v1_2 + 4)) = (s32) (*(s32 *)((u8 *)var_a0 + 8));
                }
            }
            var_a0 += 0x10;
        } while (var_v0 < (s32) (u8) D_800DA2F0);
    }
    return var_a2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13A8A0/func_1510DE40.s")
#endif