#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15089BB0(void) {
    D_800D27D0 = NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A41C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A63C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508AB7C.s")

s32 func_1508B5F0(s32 arg0) {
    if (arg0 >= D_80090130) {
        return 0;
    }
    return *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70);
}

void func_1508B630(s32 arg0) {
    if (arg0 < D_80090130) {
        *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70) = 0;
    }
}

// PERMUTER CHANGED DECL: voidfunc_1508B20C(f32,f32,f32,f32) (base: voidfunc_1508B20C(f32arg0,f32arg1,f32arg2,f32arg3))
void func_1508B20C(f32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
  s32 temp_a1;
  s8 temp_v1;
  u8 *new_var;
  if (D_800D27D0 != 0)
  {
    temp_v1 = *((s8 *) (((u8 *) D_800D27D0) + 0x1745));
    if (temp_v1 < 8)
    {
      new_var = (u8 *) D_800D27D0; // fakematch: pointer copy in a named local (permuter)
      *((s8 *) (new_var + 0x1745)) = (s8) (temp_v1 + 1);
      temp_a1 = temp_v1 * 0xC;
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x174C)) = (s16) ((s32) arg0);
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x174E)) = (s16) ((s32) arg1);
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x1750)) = (s16) ((s32) arg2);
      *((f32 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x1748)) = (f32) (arg3 * arg3);
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508BE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C07C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C370.s")

s32 func_1508C5F0(s32 arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CA14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CE28.s")

s32 func_1508CEE4(void) {
    D_800D27D0[0x1703]++;
    if (D_800D27D0[0x1703] >= D_80090130) {
        D_800D27D0[0x1703] = 0;
    }
    return D_800D27D0[0x1703];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CF34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DCAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DE78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DF48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508E080.s")

void func_1508EB24(void) {
}

s32 func_1508EB2C(s32 arg0) {
    switch (arg0) {
    case 0x3F:
        return 0x708;
    case 0x14:
        return 0xC80;
    case 0x22:
        return 0x1F4;
    case 0x23:
        return 0x2710;
    case 0x16:
        return 0x186A0;
    case 0x15:
        return 0x1F4;
    case 0x21:
        return 0x1F4;
    case 0x24:
        return 0x186A0;
    case 0x19:
    case 0x40:
        return 0x1F4;
    case 0x9:
        return 0x1388;
    case 0x38:
        return 0x1388;
    case 0x18:
    case 0x41:
        return 0x186A0;
    case 0x3:
        return 0x2EE;
    case 0x37:
        return 0x5DC;
    default:
        return 0x186A0;
    }
}

s32 func_1508EBDC(s32 arg0) {
    if ((*(s16 *)((u8 *)D_800D27D0 + 0x16BC)) != 0xB8) {
        switch (arg0) {
        case 0x14:
            return 0x28;
        case 0x3F:
            return 0x2F;
        case 0x22:
            return 0x56;
        case 0x23:
            return 0x16;
        case 0x16:
            return 0x24;
        case 0x15:
            return 0x4B;
        case 0x21:
            return 0x58;
        case 0x24:
            return 0x63;
        case 0x19:
            return 0x57;
        case 0x40:
            return 0x21;
        case 0x9:
            return 0x1D;
        case 0x38:
            return 0x7B;
        case 0x39:
            return 0x82;
        case 0x37:
            return 0x85;
        case 0x18:
            return 0x55;
        case 0x41:
            return 0x2E;
        case 0x25:
            return 0x1060;
        default:
            return -1;
        }
    } else {
        switch (arg0) {                             /* switch 1; irregular */
        case 8:                                     /* switch 1 */
            return -1;
        case 1:                                     /* switch 1 */
            return 0x105C;
        case 16:                                    /* switch 1 */
            return 0x1019;
        case 2:                                     /* switch 1 */
            return 0x1059;
        default:                                    /* switch 1 */
            return -1;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508ECF8.s")

void func_1508EFEC(s32 arg0, s32 arg1, s32 arg2) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, arg1, arg2);
}

void func_1508F054(s32 arg0, s32 arg1) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, 0x14, arg1);
}

void func_1508F0B8(s32 arg0, s32 arg1) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, 0x61, arg1);
}
