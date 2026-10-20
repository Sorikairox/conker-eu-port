#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_150342D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_150344AC.s")

s16 *func_15034630(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

s16 *func_150346A0(s16 *arg0, s32 arg1)
{
  struct127 *temp_v0;
  temp_v0 = &D_800CC2D0[arg1];
  if (temp_v0->unk1D1 != 0)
  {
    *arg0 = 6;
    arg0 += 2;
    arg0[-1] = (s16) (temp_v0->unk1D1 * 0xC8);
  }
  return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_15034710.s")

extern f32 D_800980CC;
s16 *func_15034790(s16 *arg0, s32 arg1) {
    struct127 *p;
    s32 v;
    f32 k;

    k = D_800980CC;
    {
        s32 blk_t; // fakematch: block boundary keeps the k load first

        arg0[0] = 0x12;
        p = &D_800CC2D0[arg1];
        v = *(s16 *)((u8 *)p + 0x2E6);
        arg0[1] = v * k;
        arg0[2] = 0xE;
        p += 0; // fakematch: register roles of p and v
        v = -*(s16 *)((u8 *)p + 0x2E4);
        arg0[3] = v * k;
    }
    return arg0 + 4;
}

s32 func_1503BCAC();

void func_1503482C(s32 arg0) {
    switch (D_800CC2D4[arg0 * 0x32C]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x80:
    case 0xB0:
        func_1503BCAC();
        break;
    }
}

s32 func_150351A4(struct127 *, s32, s32);
s32 func_15036600(s32, s32, s32, s32);
s32 func_150F1F80(struct127 *);

void func_150348D4(s32 arg0) {

    if (D_800CC2D0[arg0].unk1D4 != NULL) {
        if ((D_800CC2D0[arg0].interaction_state == 1) || (D_800CC2D0[arg0].unk5 == 7)) {
            func_1503482C(arg0);
        }
        if (D_800CC2D0[arg0].interaction_state == 0x22) {
            func_1503482C(arg0);
        }
        switch (D_800CC2D0[arg0].id) {                          /* irregular */
        case 0x4:
            if (D_800BE616 == 0) {
                func_15036600(0, arg0, 9, 0);
                func_15036600(0, arg0, 4, 0);
                return;
            }
            break;
        case 0x70:
            func_150351A4(&D_800CC2D0[arg0], 0xA, 0xB);
            return;
        case 0x7B:
            func_150F1F80(&D_800CC2D0[arg0]);
            return;
        case 0x60:
            func_150E0324(&D_800CC2D0[arg0]);
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_61AE0/func_15034A18.s")

void func_15034AD8(void) {
    struct127 *var_s0;
    var_s0 = D_800CC2D0;
    if (D_800BEAC0 == 0) {
        do {
            if ((var_s0->interaction_state != 0) && (var_s0->unk9C != 0)) {
                func_15034A18(var_s0);
            }
            var_s0++;
        } while (var_s0 != (struct127 *)&D_800D121C);
    }
}
