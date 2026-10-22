#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15121C68(u8 *arg0);
#endif


#ifdef NON_MATCHING
s32 func_151CA150(u8 *, u8, u8 *);

void func_151201D0(u8 *arg0) {
    s32 sp20;
    u8 *sp1C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 *var_v1;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x23E));
    (*(s16 *)((u8 *)arg0 + 0x84A)) = 0x32;
    if (((*(s32 *)((u8 *)arg0 + 0x5F0)) & 2) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (var_v1 = arg0 + 0x740, (temp_v0 == 0x3B))) {
        var_v1 = arg0 + 0x740;
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 0;
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 1;
    } else {
        (*(s8 *)((u8 *)var_v1 + 0x4D)) = 1;
    }
    (*(s8 *)((u8 *)arg0 + 0x84C)) = 0;
    if ((*(s32 *)((u8 *)arg0 + 0x34)) == 0x40) {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
    } else if ((*(u8 *)((u8 *)var_v1 + 0x4D)) != 0) {
        temp_v0_2 = (*(u8 *)((u8 *)arg0 + 0x23E));
        if ((temp_v0_2 == 9) || (temp_v0_2 == 0x38) || (temp_v0_2 == 0x39) || (temp_v0_2 == 0x37) || (temp_v0_2 == 0x3B) || (temp_v0_2 == 0x15) || (temp_v0_2 == 0x26) || (temp_v0_2 == 0x3A)) {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((f32) (((*(u16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x7A)) - (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D4))) + 0x12))) + 0xC000) * 0.005493164f);
        } else if ((D_800D1940 == 0x42) && (temp_v0 == 0x1A)) {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40));
        } else {
            (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) - 180.0f);
        }
    } else {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x280);
    }
    if ((temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A)) {
        (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0x3C)) = 0.0f;
        sp20 = (s32) temp_v0;
        sp1C = var_v1;
        func_151CA150(arg0, temp_v0, arg0);
        (*(s8 *)((u8 *)arg0 + 0x84C)) = 1;
    } else {
        if ((temp_v0 == 2) || (temp_v0 == 0x13)) {
            (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
            goto block_43;
        }
        if (temp_v0 != 0x1C) {
            if (temp_v0 == 0x34) {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
                goto block_43;
            }
            if (temp_v0 == 0xF) {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 27.0f;
                (*(f32 *)((u8 *)var_v1 + 0x3C)) = 27.0f;
                (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) + 225.0f);
            } else {
                (*(f32 *)((u8 *)var_v1 + 0x38)) = 0.0f;
block_43:
                (*(f32 *)((u8 *)var_v1 + 0x3C)) = 0.0f;
            }
        }
    }
    sp1C = var_v1;
    sp20 = (s32) temp_v0;
    func_15121C68(arg0);
    func_15048758(var_v1 + 0x34);
    if ((*(u8 *)((u8 *)var_v1 + 0x4C)) != 0) {
        temp_f0 = (*(f32 *)((u8 *)var_v1 + 0x50));
        (*(f32 *)((u8 *)var_v1 + 0x38)) = temp_f0;
        (*(f32 *)((u8 *)var_v1 + 0x3C)) = temp_f0;
        (*(f32 *)((u8 *)var_v1 + 0x44)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x58));
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)var_v1 + 0x34)) + (*(f32 *)((u8 *)var_v1 + 0x54)));
    }
    (*(f32 *)((u8 *)var_v1 + 0x20)) = (f32) (*(f32 *)((u8 *)arg0 + 0x37C));
    (*(f32 *)((u8 *)var_v1 + 0x2C)) = (f32) (*(s32 *)((u8 *)arg0 + 0x134));
    if ((*(u8 *)((u8 *)arg0 + 0x92C)) != 0) {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x2BC)) - (*(f32 *)((u8 *)arg0 + 0x2F8));
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x2C4)) - (*(f32 *)((u8 *)arg0 + 0x300));
        (*(f32 *)((u8 *)var_v1 + 0x24)) = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)var_v1 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x344));
        (*(f32 *)((u8 *)var_v1 + 0x30)) = (f32) (*(f32 *)((u8 *)arg0 + 0x354));
    } else {
        (*(f32 *)((u8 *)var_v1 + 0x24)) = (f32) (*(f32 *)((u8 *)arg0 + 0x374));
        (*(f32 *)((u8 *)var_v1 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x348));
        (*(f32 *)((u8 *)var_v1 + 0x30)) = (f32) (*(f32 *)((u8 *)arg0 + 0x354));
    }
    temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x2C0));
    (*(f32 *)((u8 *)arg0 + 0x35C)) = temp_f0_2;
    (*(f32 *)((u8 *)arg0 + 0x354)) = temp_f0_2;
    (*(f32 *)((u8 *)var_v1 + 0x44)) = 110.0f;
    (*(f32 *)((u8 *)arg0 + 0x348)) = 30.0f;
    (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D4))) + 0x16C)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x34));
    if ((temp_v0 == 0) || (temp_v0 == 0xC) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A)) {
        (*(f32 *)((u8 *)arg0 + 0x348)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x348)) + 30.0f);
    }
    (*(s32 *)((u8 *)var_v1 + 0x64)) = 0;
    (*(s16 *)((u8 *)arg0 + 0x73C)) = 1;
    if ((*(u8 *)((u8 *)arg0 + 0x23C)) != 0) {
        (*(f32 *)((u8 *)var_v1 + 0x34)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)) - 180.0f);
        (*(f32 *)((u8 *)arg0 + 0x37C)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x34));
        (*(f32 *)((u8 *)arg0 + 0x194)) = (f32) (*(f32 *)((u8 *)arg0 + 0x198));
        (*(f32 *)((u8 *)arg0 + 0x18C)) = (f32) (*(f32 *)((u8 *)arg0 + 0x190));
        (*(f32 *)((u8 *)arg0 + 0x39C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x37C)) * 0.017453292f);
    }
    temp_f0_3 = (*(f32 *)((u8 *)var_v1 + 0x44));
    if (temp_f0_3 < (*(f32 *)((u8 *)arg0 + 0x370))) {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = -1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (temp_f0_3 * 1.2f);
    } else {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = 1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (temp_f0_3 * 0.666666f);
    }
    if ((temp_v0 == 0xA) || (temp_v0 == 2) || (temp_v0 == 0x12) || (temp_v0 == 3) || (temp_v0 == 0x34)) {
        (*(s8 *)((u8 *)var_v1 + 0x4E)) = -1;
        (*(f32 *)((u8 *)var_v1 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x374));
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x280);
    (*(f32 *)((u8 *)arg0 + 0x374)) = (f32) (*(f32 *)((u8 *)var_v1 + 0x44));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151201D0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_151206C8.s")

#ifdef NON_MATCHING
void func_15121A00(struct127 *arg0, u16 *arg1) {
    struct {
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
    } sp;
    f32 sp24;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f6;
    f32 temp_f6_2;
    struct126 *temp_v1;
    u8 temp_v0;

    arg0->unk31C->unk198 = 0;
    if ((*arg1 & 0x10) && ((temp_v1 = arg0->unk31C, temp_v0 = temp_v1->unk78, (temp_v0 == 9)) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A))) {
        sp.u44 = arg0->x_position;
        temp_f12 = (arg0->unk40 - 90.0f) * 0.017453292f;
        sp.u48 = arg0->y_position + ((f32) (s16) temp_v1->unk114 * 0.75f);
        sp.u4C = arg0->z_position;
        (*(f32 *)((u8 *)(&sp.u38) + 0)) = (*(f32 *)((u8 *)(&sp.u44) + 0));
        (*(s32 *)((u8 *)(&sp.u38) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 4));
        (*(s32 *)((u8 *)(&sp.u38) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 8));
        sp.u34 = temp_f12;
        temp_f6 = sinf(temp_f12) * 100.0f;
        sp.u48 = sp.u3C;
        sp.u44 = temp_f6 + sp.u38;
        sp.u4C = (cosf(temp_f12) * 100.0f) + sp.u40;
        sp.u3C += arg0->y_position - arg0->old_y_position;
        (*(f32 *)((u8 *)temp_v1 + 0x13C)) = (f32) (*(f32 *)((u8 *)(&sp.u38) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x140)) = (s32) (*(s32 *)((u8 *)(&sp.u38) + 4));
        (*(s32 *)((u8 *)temp_v1 + 0x144)) = (s32) (*(s32 *)((u8 *)(&sp.u38) + 8));
        (*(f32 *)((u8 *)temp_v1 + 0x148)) = (f32) (*(f32 *)((u8 *)(&sp.u44) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x14C)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 4));
        temp_v1->unk198 = 1;
        (*(s32 *)((u8 *)temp_v1 + 0x150)) = (s32) (*(s32 *)((u8 *)(&sp.u44) + 8));
        sp.u28 = 1.0f;
        sp24 = cosf((*(f32 *)((u8 *)temp_v1 + 0x170)) * -0.017453292f) * sp.u28;
        temp_f16 = sinf((*(f32 *)((u8 *)temp_v1 + 0x170)) * -0.017453292f) * sp.u28;
        sp.u28 = sp24;
        sp.u2C = temp_f16;
        sp24 = cosf((*(f32 *)((u8 *)temp_v1 + 0x16C)) * -0.017453292f) * sp.u28;
        temp_f6_2 = sinf((*(f32 *)((u8 *)temp_v1 + 0x16C)) * -0.017453292f) * sp.u28;
        sp.u28 = sp24;
        sp.u30 = temp_f6_2;
        (*(f32 *)((u8 *)temp_v1 + 0x130)) = (f32) (*(f32 *)((u8 *)(&sp.u28) + 0));
        (*(s32 *)((u8 *)temp_v1 + 0x134)) = (s32) (*(s32 *)((u8 *)(&sp.u28) + 4));
        (*(s32 *)((u8 *)temp_v1 + 0x138)) = (s32) (*(s32 *)((u8 *)(&sp.u28) + 8));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_14D9E0/func_15121A00.s")
#endif
void func_15121C68(u8 *arg0) {
    if (arg0[0x23E] != 0) {
        if (arg0[0x23E] == 0x34) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 80.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 350.0f;
            return;
        }
        if ((arg0[0x23E] == 0x3B) && ((D_800BE9F0 == 0x41) || (D_800BE9F0 == 0x3C))) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = -12.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = -28.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 106.0f;
            return;
        }
        if ((arg0[0x23E] == 2) || (arg0[0x23E] == 0xA) || (arg0[0x23E] == 0x13)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 135.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80);
            return;
        }
        if ((arg0[0x23E] == 0x12) && (D_800BE9F0 == 0x3C)) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 180.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0xF) {
            (*(f32 *)((u8 *)arg0 + 0x190)) = 10.0f;
            (*(f32 *)((u8 *)arg0 + 0x784)) = 480.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x38) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        if (arg0[0x23E] == 0x15) {
            (*(f32 *)((u8 *)arg0 + 0x784)) = 110.0f;
            (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
            (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
            return;
        }
        (*(f32 *)((u8 *)arg0 + 0x190)) = 5.0f;
        (*(f32 *)((u8 *)arg0 + 0x784)) = 75.0f;
        (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
        return;
    }
    (*(f32 *)((u8 *)arg0 + 0x784)) = 90.0f;
    (*(f32 *)((u8 *)arg0 + 0x190)) = 25.0f;
    (*(f32 *)((u8 *)arg0 + 0x99C)) = 0.0f;
}

#ifdef NON_MATCHING
void func_151CA484(u8 *arg0);
#else
s32 func_151CA484(u8 *);
#endif

void func_15121E34(u8 *arg0)
{
  u8 *new_var;
  u8 *temp_v0;
  new_var = arg0 + 0x740;
  if (!((*(*((u16 **) (((u8 *) arg0) + 0x36C)))) & 0x10))
  {
    if ((*((s32 *) (((u8 *) arg0) + 0x34))) == 0x40)
    {
      if ((*((s32 *) (((u8 *) arg0) + 0x6FC))) == 0xF)
      {
        *((f32 *) (((u8 *) arg0) + 0x898)) = 0.0f;
        *((f32 *) (((u8 *) arg0) + 0x89C)) = 0.0f;
      }
      *((s8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D4)))) + 0x198)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x73C)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
    }
    else
    {
      *((s16 *) (((u8 *) arg0) + 0x84A)) = 0x32;
      if (1)
      {
        *((s16 *) (((u8 *) arg0) + 0x73C)) = 3;
      }
    }
    temp_v0 = new_var;
    *((f32 *) (((u8 *) arg0) + 0x374)) = 200.0f;
    *((f32 *) (((u8 *) arg0) + 0x348)) = 100.0f;
    *((s32 *) (((u8 *) arg0) + 0x134)) = (s32) (*((f32 *) (((u8 *) temp_v0) + 0x2C)));
    *((s8 *) (((u8 *) temp_v0) + 0x4C)) = 0;
    *((f32 *) (((u8 *) arg0) + 0x190)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x99C)) = 0.0f;
    *((f32 *) (((u8 *) arg0) + 0x198)) = 0.0f;
    func_1506160C(*((struct127 **) (((u8 *) arg0) + 0x3D0)), 2U, 0xFFU, 0x20U, (s32) (*((u8 *) (((u8 *) arg0) + 0x23D))));
    if ((*((u8 *) (((u8 *) arg0) + 0x84C))) != 0)
    {
      func_151CA484(arg0);
      *((u8 *) (((u8 *) arg0) + 0x84C)) = 0U;
    }
  }
}
