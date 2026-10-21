#include <ultra64.h>
#include "functions.h"
#include "variables.h"
typedef struct { s16 x; s16 y; s16 z; s16 unk6; u8 pad8[8]; f32 unk10; u8 unk14; u8 unk15; u8 unk16; u8 unk17; s32 unk18; s32 unk1C; s32 unk20; f32 unk24; f32 unk28; f32 unk2C; f32 unk30; } Unk34B8; // 0x34 bytes, D_800D34B8[]
extern u64 D_800D3510[][3];


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A09D0.s")

extern f32 D_8009F970;
extern f32 D_8009F974;
void func_150A11F4(u8 *arg0)
{
  f32 temp_f20;
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0xC))) * D_8009F970;
  *((f32 *) (((u8 *) arg0) + 0x24)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x28)) = func_150AD780(temp_f20);
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0x10))) * D_8009F974;
  *((f32 *) (((u8 *) arg0) + 0x2C)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x30)) = func_150AD780(temp_f20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A126C.s")

u8 *func_150A1520(u8 *arg0) {
    return arg0 + 0x400;
}

s32 func_150A2280(struct127 *, u8 *, s32);
extern f32 D_8009F97C;

void func_150A152C(struct108 *arg0, u8 **arg1, s32 arg2) {
    struct127 sp;

    sp.x_position = arg0->unk2F8;
    sp.y_position = arg0->unk2FC;
    sp.z_position = arg0->unk300;
    sp.unk180 = sp.y_position;
    sp.old_x_position = arg0->unk304;
    sp.old_y_position = arg0->unk308;
    sp.old_z_position = arg0->unk30C;
    arg0->unk364 = D_8009F97C;
    arg0->unk84 &= ~0x40000;
    for (; arg2 != 0; arg2--, arg1++) {
        if (*arg1 == NULL) {
            continue;
        }
        if (func_150A2280(&sp, *arg1, 0) != 0) {
            continue;
        }
        if (((*arg1)[0x15] >> 2) != 1) {
            continue;
        }
        switch ((*arg1)[0x17]) {
        case 2:
            if (1) { // fakematch: if (1) block from the permuter (constant allocation order)
                arg0->unk364 = *(s16 *)(*arg1 + 2) + *(s16 *)(*arg1 + 8);
            }
            break;
        case 0:
            arg0->unk84 |= 0x40000;
            break;
        case 6:
            arg0->unk84 &= ~0x40000;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A16A4.s")

#ifdef NON_MATCHING
s32 func_150AD9A0(s32, s32, s32);
s32 func_150ADE40(s16, s16, s32, s32);

s32 func_150A2280(struct127 *arg0, u8 *arg1, s32 arg2) {
    s16 sp5E;
    s16 sp5C;
    s16 sp5A;
    s16 sp58;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp2C;
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f10_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f16_4;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f6;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_t0;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f4_3;
    s32 temp_f6_2;
    s32 temp_f8;
    s32 temp_f8_2;
    s32 temp_t2;

    if (((*(u8 *)((u8 *)arg1 + 0x14)) == 1) || (arg0 == NULL) || (arg1 == NULL)) {
        goto block_35;
    }
    var_t0 = 0;
    sp2C = (f32) (*(s16 *)((u8 *)arg1 + 0));
    sp5E = (s16) (s32) (arg0->x_position - sp2C);
    temp_f0 = arg0->y_position;
    sp24 = (f32) (*(s16 *)((u8 *)arg1 + 2));
    sp5C = (s16) (s32) (temp_f0 - sp24);
    sp20 = (f32) (*(s16 *)((u8 *)arg1 + 4));
    sp5A = (s16) (s32) (arg0->z_position - sp20);
    if (arg2 != 0) {
        var_t0 = arg0->unkE4;
    }
    if (!((*(u8 *)((u8 *)arg1 + 0x16)) & 1) || (((f32) (s32) temp_f0 - arg0->unk180) <= 5.0f)) {
        temp_t2 = (*(u8 *)((u8 *)arg1 + 0x15)) & 3;
        switch (temp_t2) {                          /* irregular */
        case 0:
            if (((*(f32 *)((u8 *)arg1 + 0xC)) > 0.01f) || ((*(f32 *)((u8 *)arg1 + 0x10)) > 0.01f)) {
                temp_f12 = (*(f32 *)((u8 *)arg1 + 0x30));
                temp_f0_2 = (f32) sp5E;
                temp_f2 = (*(f32 *)((u8 *)arg1 + 0x2C));
                temp_f14 = (f32) sp5A;
                sp44 = temp_f0_2;
                sp5E = (s16) (s32) ((temp_f0_2 * temp_f12) - (temp_f14 * temp_f2));
                temp_f18 = (temp_f14 * temp_f12) + (sp44 * temp_f2);
                temp_f12_2 = (*(f32 *)((u8 *)arg1 + 0x28));
                temp_f2_2 = (*(f32 *)((u8 *)arg1 + 0x24));
                temp_f16 = (f32) sp5C;
                sp5A = (s16) (s32) ((temp_f18 * temp_f12_2) - (temp_f16 * temp_f2_2));
                sp5C = (s16) (s32) ((temp_f16 * temp_f12_2) + (temp_f18 * temp_f2_2));
            }
            sp58 = var_t0;
            if ((func_150ADE40(sp5E, sp5A, 0, 0) < ((*(s16 *)((u8 *)arg1 + 6)) + var_t0)) && (sp5C > 0) && (sp5C < (*(s16 *)((u8 *)arg1 + 8)))) {
                return 0;
            }
            goto block_35;
        case 1:
            sp58 = var_t0;
            if (func_150AD9A0(sp5E, sp5C, sp5A) < ((*(s16 *)((u8 *)arg1 + 6)) + var_t0)) {
                return 0;
            }
            goto block_35;
        case 2:
            temp_f12_3 = (*(f32 *)((u8 *)arg1 + 0x30));
            temp_f0_3 = (f32) sp5E;
            temp_f2_3 = (*(f32 *)((u8 *)arg1 + 0x2C));
            temp_f14_2 = (f32) sp5A;
            sp44 = temp_f0_3;
            temp_f4 = (s32) ((temp_f0_3 * temp_f12_3) - (temp_f14_2 * temp_f2_3));
            sp5E = (s16) temp_f4;
            temp_v0 = (*(s16 *)((u8 *)arg1 + 6));
            if (((s16) temp_f4 < (temp_v0 + var_t0)) && ((-temp_v0 - var_t0) < (s16) temp_f4)) {
                temp_f12_4 = (*(f32 *)((u8 *)arg1 + 0x28));
                temp_f2_4 = (*(f32 *)((u8 *)arg1 + 0x24));
                temp_f16_2 = (f32) sp5C;
                temp_f18_2 = (temp_f14_2 * temp_f12_3) + (sp44 * temp_f2_3);
                sp44 = temp_f16_2;
                temp_v1 = (*(s16 *)((u8 *)arg1 + 0xA));
                temp_f4_2 = (s32) ((temp_f18_2 * temp_f12_4) - (temp_f16_2 * temp_f2_4));
                if (((s16) temp_f4_2 < (temp_v1 + var_t0)) && ((-temp_v1 - var_t0) < (s16) temp_f4_2)) {
                    temp_f10 = (s32) ((sp44 * temp_f12_4) + (temp_f18_2 * temp_f2_4));
                    if (((s16) temp_f10 < (*(s16 *)((u8 *)arg1 + 8))) && ((s16) temp_f10 > 0)) {
                        return 0;
                    }
                }
            }
            goto block_35;
        case 3:
            temp_f12_5 = (*(f32 *)((u8 *)arg1 + 0x30));
            temp_f2_5 = (*(f32 *)((u8 *)arg1 + 0x2C));
            temp_f0_4 = (f32) sp5E;
            temp_f14_3 = (f32) sp5A;
            sp44 = temp_f0_4;
            temp_f16_3 = (f32) (s16) (s32) (arg0->old_x_position - sp2C);
            temp_f18_3 = (f32) (s16) (s32) (arg0->old_z_position - sp20);
            sp38 = temp_f16_3;
            temp_f8 = (s32) ((temp_f0_4 * temp_f12_5) - (temp_f14_3 * temp_f2_5));
            sp5E = (s16) temp_f8;
            temp_f10_2 = (s32) ((temp_f16_3 * temp_f12_5) - (temp_f18_3 * temp_f2_5));
            temp_f10_3 = (temp_f14_3 * temp_f12_5) + (sp44 * temp_f2_5);
            sp40 = temp_f10_3;
            temp_f6 = (temp_f18_3 * temp_f12_5) + (sp38 * temp_f2_5);
            sp34 = temp_f6;
            temp_f16_4 = (f32) sp5C;
            temp_f12_6 = (*(f32 *)((u8 *)arg1 + 0x28));
            temp_f2_6 = (*(f32 *)((u8 *)arg1 + 0x24));
            sp44 = temp_f16_4;
            temp_f0_5 = (f32) (s16) (s32) (arg0->old_y_position - sp24);
            temp_f8_2 = (s32) ((temp_f10_3 * temp_f12_6) - (temp_f16_4 * temp_f2_6));
            sp38 = temp_f0_5;
            temp_f6_2 = (s32) ((temp_f6 * temp_f12_6) - (temp_f0_5 * temp_f2_6));
            if (((s16) temp_f6_2 < 0) && ((s16) temp_f8_2 >= 0)) {
                temp_f14_4 = (f32) (s16) temp_f6_2 / (f32) ((s16) temp_f6_2 - (s16) temp_f8_2);
                if (fabsf((f32) (s16) temp_f10_2 + (temp_f14_4 * (f32) ((s16) temp_f8 - (s16) temp_f10_2))) < (f32) (*(s16 *)((u8 *)arg1 + 6))) {
                    temp_f4_3 = (s32) ((sp38 * temp_f12_6) + (sp34 * temp_f2_6));
                    temp_f0_6 = (f32) (s16) temp_f4_3 + (temp_f14_4 * (f32) ((s16) (s32) ((sp44 * temp_f12_6) + (temp_f10_3 * temp_f2_6)) - (s16) temp_f4_3));
                    if ((temp_f0_6 >= 0.0f) && (temp_f0_6 < (f32) (*(s16 *)((u8 *)arg1 + 8)))) {
                        return 0;
                    }
                }
            }
            goto block_35;
        }
    } else {
block_35:
        return 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2280.s")
#endif
void func_150A28C4(u8 *arg0)
{
  int new_var;
  s32 var_t0;
  s32 var_v1;
  u32 temp_v0;
  u8 temp_t1;
  if ((*((s32 *) (((u8 *) arg0) + 0x20))) == 0)
  {
    var_v1 = 0;
    var_t0 = 8;
    if (!((*((u8 *) (((u8 *) arg0) + 0x15))) & 3))
    {
      var_v1 = 0x8000;
    }
    temp_t1 = *((u8 *) (((u8 *) arg0) + 0x17));
    if ((((s32) temp_t1) >> (new_var = 7)) != 0)
    {
      var_t0 = 0x108;
    }
    temp_v0 = *((u32 *) (((u8 *) arg0) + 0x1C));
    func_1000FA64((temp_v0 >> 0x10) & ((short) 0xFFFF), *((s16 *) (((u8 *) arg0) + 0)), *((s16 *) (((u8 *) arg0) + 2)), *((s16 *) (((u8 *) arg0) + 4)), (temp_t1 & 0x7F) * 0x147, (u16) ((*((s32 *) (((u8 *) arg0) + 0x18))) | var_v1), (s16) (temp_v0 & 0xFFFF), 0, 0, 0, var_t0, 0);
    *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
 dummy_label_636436: ;
    return;
  }
  *((s32 *) (((u8 *) arg0) + 0x20)) = 1;
}

s32 func_15183800(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150A29A0(Unk34B8 *arg0, s32 arg1) {
    s32 v;
    s32 r;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 w;

    if (arg1 != 0xFF) {
        w = arg0->unk1C;
        v = w & 0xFF;
        if (v == 0 || arg0->unk17 == 9) {
            g = arg0->unk17;
            a = arg0->unk18 & 0xFF;
            b = *(s16 *)&arg0->unk18;
            c = ((u8 *)&arg0->unk18)[2];
            d = ((u8 *)&arg0->unk1C)[0];
            e = ((u8 *)&arg0->unk1C)[1];
            f = arg0->unk20;
            r = func_15183800(arg0->x, arg0->y + (e << 4), arg0->z, a, g, arg0->unk6, arg1, b, c, d, f);
            if (r != -1 && arg0->unk17 != 9) {
                arg0->unk1C = ((r << 8) | 0xF0) | (arg0->unk1C & 0xFFFF0000);
            }
        } else {
            r = v;
            w = arg0->unk1C; // fakematch: re-read of the word swaps v/r into a0/v0
            if (v < 2) {
                r = 2;
            }
            arg0->unk1C = (w & ~0xFF) | r;
        }
    }
}

#ifdef NON_MATCHING
s32 func_150E6E30(struct127 *, s32, u8 *, u8);
s32 func_151CEACC(struct127 *, u8 *);
extern u8 D_800D34B0;
extern s32 D_800DA2D8;

void func_150A2AB4(u8 *arg0, struct127 *arg1, s32 arg2, s32 arg5) {
    u16 temp_v0_2;
    u8 temp_t1;
    u8 temp_t6;
    u8 *temp_v0;

    temp_t6 = (*(u8 *)((u8 *)arg0 + 0x17));
    switch (temp_t6) {
    case 1:
        if (arg2 != 0xFF) {
            func_150E7810(arg2, 0xFF, 0);
            return;
        }
    default:
        return;
    case 2:
        if (arg2 != 0xFF) {
            temp_v0 = ((s32 *)((u8 *)&D_800DA2D8 + (arg2 * 3)));
            (*(s8 *)((u8 *)temp_v0 + 0)) = (s8) (*(s32 *)((u8 *)arg0 + 0x18));
            (*(s8 *)((u8 *)temp_v0 + 1)) = (s8) (*(s32 *)((u8 *)arg0 + 0x1C));
            (*(s8 *)((u8 *)temp_v0 + 2)) = (s8) (*(s32 *)((u8 *)arg0 + 0x20));
            return;
        }
        break;
    case 3:
        if (arg2 != 0xFF) {
            func_150E6E30(arg1, arg2, arg0, (*(u8 *)((u8 *)arg0 + 0x1B)));
            return;
        }
        break;
    case 6:
        if (!(arg5 & 1)) {
            D_800D34B0 = 0x19;
            func_10010344(0x66FU, arg1, 0x5DC0, 0x190, 0x1F4U);
        }
        temp_t1 = (D_800D34B0 + D_800BE9E4) & 0xFF;
        D_800D34B0 = temp_t1;
        if ((s32) temp_t1 >= 0x1A) {
            temp_v0_2 = arg1->unkB2;
            if ((s32) temp_v0_2 >= 0x5A1) {
                arg1->unkB2 = 0x4B0;
            } else if ((s32) temp_v0_2 < 0xF1) {
                arg1->unkB2 = 0x5A;
            } else {
                arg1->unkB2 = temp_v0_2 - 0xF0;
            }
            D_800D34B0 = 0;
            return;
        }
        break;
    case 8:
        func_151C8C24(arg1, arg0);
        return;
    case 9:
        func_1515F7E0(arg1, arg0);
        return;
    case 10:
        func_151CEACC(arg1, arg0);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2AB4.s")
#endif
s32 func_150A2280(struct127 *, u8 *, s32);
s32 func_151733EC(struct127 *, u8, s32);

void func_150A2C6C(u8 *arg0)
{
  int new_var;
  s32 var_s0;
  u32 var_s1;
  u8 *temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0x65))) == 0)
  {
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0)
    {
      do
      {
        new_var = var_s0 ^ 0;
        if (((((s32) (*((u8 *) (((u8 *) (&D_800D34B8[new_var])) + 0x15)))) >> 2) == 8) && (func_150A2280(arg0, &D_800D34B8[var_s0 & 0xFFFFFFFF], 0) == 0))
        {
          temp_v0 = &D_800D34B8[var_s0];
          func_151733EC(arg0, *((u8 *) (((u8 *) temp_v0) + 0x17)), *((s32 *) (((u8 *) temp_v0) + 0x18)));
        }
        var_s1 += 1;
        var_s0 += 0x34;
      }
      while (var_s1 < ((u32) D_800D3094));
    }
  }
}

void func_150A2D44(s32 arg0, s32 arg1) {
    s32 i;

    arg0 &= 0xFFF;
    if ((u32)arg0 < (u32)D_800D3094) {
        ((Unk34B8 *)D_800D34B8)[arg0].unk14 = arg1;
    }
    if (arg1 == 1) {
        for (i = 0; i < 16; i++) {
            D_800D3510[i][(u32)arg0 >> 6] &= ~(1ULL << ((u32)arg0 & 0x3F));
        }
    }
}

void func_150A2E20(s32 arg0, s32 arg1, int arg2)
{
  s32 temp_v0;
  int new_var;
  int new_var2;
  new_var = 1;
  arg0 = arg0 & 0xFFF;
  if (arg0 < ((u32) D_800D3094))
  {
    new_var2 = -new_var;
    if (arg1 != (-new_var))
    {
      *((s32 *) (((u8 *) (D_800D34B8 + ((13 * arg0) * 4))) + 0x18)) = arg1;
    }
    temp_v0 = arg0 * 0x34;
    if (arg2 != new_var2)
    {
      *((s8 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x17)) = arg2;
    }
    *((s32 *) (((u8 *) (D_800D34B8 + temp_v0)) + 0x1C)) = 0;
  }
}

extern u64 D_800D3510[][3];

s32 func_150A29C8(s32 arg0, s32 arg1) {
    arg1 &= 0xFFF;
    if ((u32)D_800D3094 < (u32)arg1) {
        return 1;
    }
    if ((u32)arg0 < 16 && ((u16)D_800D2340 & (1 << arg0))) {
        if ((D_800D3510[(u32)arg0][(u32)arg1 >> 6] >> ((u32)arg1 & 0x3F)) & 1) {
            return 0;
        }
        return 1;
    }
    return func_150A2280(&D_800CC2D0[arg0], D_800D34B8 + arg1 * 0x34, 1);
}

s32 func_150A2FCC(u32 arg0, s32 arg1, s32 *arg2) {
    s32 i;
    u32 v;

    if (arg0 < 16 && ((u16)D_800D2340 & (1 << arg0))) {
        for (i = 0; i < arg1; i++) {
            v = arg2[i] & 0xFFF;
            if (v < (u32)D_800D3094) {
                if ((D_800D3510[arg0][v >> 6] >> (v & 0x3F)) & 1) {
                    return v;
                }
            }
        }
    } else {
    for (i = 0; i < arg1; i++) {
        v = arg2[i] & 0xFFF;
        if (v < (u32)D_800D3094) {
            if (func_150A2280(&D_800CC2D0[arg0], D_800D34B8 + v * 0x34, 1) == 0) {
                return v;
            }
        }
    }
    }
    return -1;
}

s32 func_150A3184(s32 arg0) {
    s32 i;

    arg0 &= 0xFFF;
    if ((u32)D_800D3094 < arg0) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (*(u16 *)((u8 *)&D_800D2138 + 0x208) & (1 << i)) {
            if ((D_800D3510[i][(u32)arg0 >> 6] >> ((u32)arg0 & 0x3F)) & 1) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_150A2280(struct127 *, u8 *, s32);

s32 func_150A3264(s32 arg0, u32 arg1) {
    struct108 *e;
    struct127 sp;

    e = &D_800DBFF0[arg0];
    arg1 &= 0xFFF;
    if ((u32)D_800D3094 < arg1) {
        return 1;
    }
    sp.x_position = e->unk2F8;
    sp.y_position = e->unk2FC;
    sp.z_position = e->unk300;
    sp.unk180 = sp.y_position;
    sp.old_x_position = e->unk304;
    sp.old_y_position = e->unk308;
    sp.old_z_position = e->unk30C;
    return func_150A2280(&sp, D_800D34B8 + arg1 * 0x34, 0);
}

#ifdef NON_MATCHING
s32 func_150A332C(Unk34B8 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_f14;

    temp_f14 = arg2 - (f32) arg0->y;
    arg3 = temp_f14 - (f32) arg0->z;
    if (((((arg3 * arg0->unk30) + ((arg1 - (f32) arg0->x) * arg0->unk2C)) * arg0->unk28) - (temp_f14 * arg0->unk24)) <= 0.0f) {
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A332C.s")
#endif
s32 func_150A332C(Unk34B8 *, f32, f32, f32);
s32 func_150A33C4(s32 arg0, s32 arg1) {
    arg1 &= 0xFFF;
    if ((u32) D_800D3094 < arg1) {
        return 1;
    }
    if ((((Unk34B8 *) D_800D34B8)[arg1].unk15 & 3) == 3) {
        return func_150A332C(arg1 + (Unk34B8 *) D_800D34B8, D_800CC2D0[arg0].x_position, D_800CC2D0[arg0].y_position, D_800CC2D0[arg0].z_position);
    }
    return 0;
}

s32 func_150A332C(Unk34B8 *, f32, f32, f32);
s32 func_150A3484(s32 arg0, s32 arg1) {
    struct108 *v = &D_800DBFF0[arg0];

    arg1 &= 0xFFF;
    if ((u32) D_800D3094 < arg1) {
        return 1;
    }
    if ((((Unk34B8 *) D_800D34B8)[arg1].unk15 & 3) == 3) {
        return func_150A332C(arg1 + (Unk34B8 *) D_800D34B8, v->unk2F8, v->unk2FC, v->unk300);
    }
    return 0;
}


s32 func_150A3538(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u32 i;
    struct127 sp;

    sp.x_position = sp.old_x_position = (f32)arg1;
    sp.y_position = sp.old_y_position = (f32)arg2;
    sp.z_position = sp.old_z_position = (f32)arg3;
    sp.unk180 = sp.y_position;
    for (i = 0; i < (u32)D_800D3094; i++) {
        if (((Unk34B8 *)D_800D34B8)[i].unk14 == 0 && (((Unk34B8 *)D_800D34B8)[i].unk15 >> 2) == 3 && ((Unk34B8 *)D_800D34B8)[i].unk17 == arg0 && func_150A2280(&sp, D_800D34B8 + i * 0x34, 0) == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_150A2280(struct127 *, u8 *, s32);

u8 *func_150A3674(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 i;
    struct127 sp;

    sp.x_position = sp.old_x_position = (f32)arg2;
    sp.y_position = sp.old_y_position = (f32)arg3;
    sp.z_position = sp.old_z_position = (f32)arg4;
    sp.unk180 = sp.y_position;
    for (i = 0; i < (u32)D_800D3094; i++) {
        if (((Unk34B8 *)D_800D34B8)[i].unk14 == 0 && (((Unk34B8 *)D_800D34B8)[i].unk15 >> 2) == arg0 && ((Unk34B8 *)D_800D34B8)[i].unk17 == arg1 && func_150A2280(&sp, D_800D34B8 + i * 0x34, 0) == 0) {
            return D_800D34B8 + i * 0x34;
        }
    }
    return NULL;
}

s32 func_150A3794(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct127 sp24;
    u8 *new_var; // fakematch: pointer to the local struct for the 0x180 store
    s32 pad[2];
    sp24.x_position = (sp24.old_x_position = (f32)arg1);
    sp24.y_position = (sp24.old_y_position = (f32)arg2);
    sp24.z_position = (sp24.old_z_position = (f32)arg3);
    new_var = (u8 *)&sp24;
    *(f32 *)(new_var + 0x180) = sp24.y_position;
    if (0 == func_150A2280((u8 *)&sp24, arg0, 0)) {
        return (unsigned int)1; // fakematch: permuter artifact (cast)
    }
    return 0;
}

void func_150A3810(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *arg1 = (s32) (*(u8 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x17));
    *arg2 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x18));
    *arg3 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x1C));
    *arg4 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x20));
}

void func_150A3878(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 & 1) {
        *(s8 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x17) = arg2;
    }
    if (arg1 & 2) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x18) = arg3;
    }
    if (arg1 & 4) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x1C) = arg4;
    }
    if (arg1 & 8) {
        *(s32 *)((u8 *)(D_800D34B8 + (arg0 * 0x34)) + 0x20) = arg5;
    }
}

void func_150A3924(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *(s16 *)(D_800D34B8 + temp_v0) = arg1;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 2)) = arg2;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 4)) = arg3;
}

s32 func_150A39E4();

s32 func_150A3990(u8 *arg0) {
    if (arg0[0x14] == 1) {
        return 0;
    }
    if (!(arg0[0x15] & 3)) {
        return func_150A39E4();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A39E4.s")
