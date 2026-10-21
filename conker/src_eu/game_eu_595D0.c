#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ u8 unkA4;
    /* 0xA5 */ u8 unkA5;
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
} struct_eu_595D0;


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502BDC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C1D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C494.s")

void func_1502C380(void) {
    D_800C42AC = D_800C42A8 = (&D_800C3E80)[D_800BE9C0];
    D_800C429A = 0;
}

s32 func_1502C6AC(s32 arg0) {
    s32 temp_v1 = (&D_800CC826)[arg0 * 0x32C];

    if (temp_v1 >= 0x46) {
        temp_v1 = 0xB;
    }
    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C6F8.s")

extern u8 *D_8008CDEC[];

void func_1502C8F8(s32 arg0) {
    s32 lim;
    s16 a;
    s16 b;

    if (D_800BEAC0 == 0) {
        a = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60);
        b = *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x62);
        if (D_800CC2D0[arg0].unk7 != 0) {
            lim = D_8008CDEC[func_1502C6AC(arg0)][4] << 8;
            a = a + b;
            if (a >= lim) {
                a = a - lim;
            } else if (a < 0) {
                a = a + lim;
            }
            *(s16 *)((u8 *)&D_800CC2D0[arg0] + 0x60) = a;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502C9D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CC64.s")

s32 func_1502EF24(u8 *, s32 *, s32 *, s32 *, s32 *);

void func_1502CF24(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s32 *argC, s32 *argD) {
    s32 temp_a2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_a2 = arg1 * 3;
    temp_v0 = temp_a2 + D_800D9F88;
    *arg4 = (s32) (*(u8 *)((u8 *)temp_v0 + 0));
    temp_v1 = temp_a2 + D_800D9F98;
    *arg5 = (s32) (*(u8 *)((u8 *)temp_v0 + 1));
    *arg6 = (s32) (*(u8 *)((u8 *)temp_v0 + 2));
    *arg7 = (s32) (*(u8 *)((u8 *)temp_v1 + 0));
    *arg8 = (s32) (*(u8 *)((u8 *)temp_v1 + 1));
    *arg9 = (s32) (*(u8 *)((u8 *)temp_v1 + 2));
    *argA = 0;
    *argB = 0;
    *argC = 0;
    *argD = (*(s32 *)((u8 *)arg3 + 0xC));
    if ((*(u8 *)((u8 *)arg0 + 0xA4)) != 0) {
        func_1502EF24(arg0, argA, argB, argC, argD);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502CFEC.s")

#ifdef NON_MATCHING
void func_1502D83C(s32 arg0, u8 *arg1) {
    s32 temp_t1;
    struct127 *temp_v0;

    temp_v0 = &D_800CC2D0[arg0];
    if ((temp_v0->unk66 & 0xC) == 4) {
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) ((s32) (temp_v0->unk1DD + temp_v0->unk1E0) / 2);
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) ((s32) (temp_v0->unk1DE + temp_v0->unk1E1) / 2);
        temp_t1 = (s32) (temp_v0->unk1DF + temp_v0->unk1E2) / 2;
        (*(s32 *)((u8 *)arg1 + 8)) = temp_t1;
        (*(s32 *)((u8 *)arg1 + 0)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 0)));
        (*(s32 *)((u8 *)arg1 + 4)) = (s32) (0xFF - (*(s32 *)((u8 *)arg1 + 4)));
        (*(s32 *)((u8 *)arg1 + 8)) = (s32) (0xFF - temp_t1);
        return;
    }
    (*(s32 *)((u8 *)arg1 + 8)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 4)) = 0xFF;
    (*(s32 *)((u8 *)arg1 + 0)) = 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D83C.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502D920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DB14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502DE74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E228.s")

void func_1502E764(void) {
    if ((u16)D_800C429A != 0) {
        func_150A9E64((&D_800C3E80)[D_800BE9C0], (u16)D_800C429A);
    }
    D_800C42B0 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502E7B4.s")

void func_1502ECEC(s32 arg0, s32 arg1) {
}

void func_1502ECFC(struct_eu_595D0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->unkA4 = 4;
    arg0->unkA5 = 0;
    arg0->unkA6 = arg5;
    arg0->unkA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    arg0->unkA7 = 0xFF;
}

void func_1502ED40(struct_eu_595D0 *arg0) {
    arg0->unkA4 = 5;
}

void func_1502ED50(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 2;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED6C(struct_eu_595D0 *arg0, s32 arg1) {
    arg0->unkA4 = 3;
    arg0->unkA5 = 0xFF;
    arg0->unkA6 = arg1;
}

void func_1502ED88(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0xA4));
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            (*(u8 *)((u8 *)arg0 + 0xA5)) = 0xFF;
        } else {
            (*(s8 *)((u8 *)arg0 + 0xA5)) = 0;
        }
        (*(s32 *)((u8 *)arg0 + 0xA0)) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        (*(s8 *)((u8 *)arg0 + 0xA6)) = (s8) arg6;
    }
    (*(u8 *)((u8 *)arg0 + 0xA4)) = 6U;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EDEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502EF24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F17C.s")

#ifdef NON_MATCHING
s32 func_1502F17C(s32, s32);
s32 func_1507E7A0(struct127 *);

void func_1502F1E4(s32 arg0) {
    s32 temp_v1;
    s32 var_s1;
    struct127 *var_s0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s0 = &D_800CC2D0[arg0];
    var_s1 = 0;
    do {
        if ((s32) (*(u8 *)((u8 *)var_s0 + 0x6C)) < 0xA) {
            temp_v1 = func_1502F17C(arg0, var_s1) & 0xFF;
            if (temp_v1 == 0) {
                temp_v0 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0 > 0) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0 - 1);
                }
            } else if (temp_v1 == 1) {
                temp_v0_2 = (*(u8 *)((u8 *)var_s0 + 0x6C));
                if ((s32) temp_v0_2 < 2) {
                    (*(u8 *)((u8 *)var_s0 + 0x6C)) = (u8) (temp_v0_2 + 1);
                }
            } else {
                (*(u8 *)((u8 *)var_s0 + 0x6C)) = 1U;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (1));
    } while (var_s1 != 2);
    func_1507E7A0(&D_800CC2D0[arg0]);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F1E4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F30C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F6B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502F780.s")

u8 *allocate_memory(s32, s32, s32, s32);
void func_1502FC38(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;
    if ((*(s32 *)(arg0 + 0xF8) & 0x4000) && *(s32 *)(arg0 + 0x264) != 0 && *(s32 *)(arg0 + 0x1D4) != 0) {
        temp_v1 = arg0[4];
        if (*(s32 *)(arg0 + 0x1D8) == 0) {
            temp_v0 = allocate_memory(D_800C52F0[temp_v1] << 6, 1, 1, 2);
            *(u8 **)(arg0 + 0x1D8) = temp_v0;
            if (temp_v0 == NULL) {
                return;
            }
        }
        bcopy(*(u8 **)(arg0 + 0x1D4), *(u8 **)(arg0 + 0x1D8), D_800C52F0[temp_v1] << 6);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FCEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_595D0/func_1502FED8.s")

void func_15030060(u8 *arg0)
{
  u8 idx = arg0[4];
  u8 *p;
  u8 *s;
  u8 a2;
  s32 v;
  if ((D_80038080 == 0) && (D_800BE9F0 == 0x1D))
  {
    ((u8 *) D_800D2040)[idx] = 2;
    return;
  }
  p = &((u8 *) D_800D2040)[idx];
  if ((*p) != 0xFF)
  {
    s = *((u8 **) (arg0 + 0x144));
    if (s != 0)
    {
      ;
      if (s[0x2E] != 0xFF)
      {
        if (s[0x2E] != 0)
        {
          ;
          if ((*p) < (s[0x2E] * 30))
          {
            *p = s[0x2E] * 30;
          }
        }
        else
        {
          goto set3;
        }
      }
    }
    else
    {
      set3:
      *p = 3;

    }
    if (arg0)
    {
    }
  }
}
