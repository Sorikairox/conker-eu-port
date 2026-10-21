#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15089BB0(void) {
    D_800D27D0 = NULL;
}

#ifdef NON_MATCHING
s32 func_1508C07C(s32);
s8 *func_1509B570(s32);
extern s32 D_80087650;
extern s32 D_80087690;
extern s32 D_80087698;
extern s32 D_800D3268;
extern s8 D_800E1000;

s32 func_1508A040(void) {
    s32 sp1C;
    s32 temp_a0;
    s32 var_v0;
    s8 *temp_v0;

    temp_a0 = D_800D3268;
    sp1C = temp_a0;
    temp_v0 = func_1509B570(temp_a0);
    if (temp_v0 == NULL) {
        return 0;
    }
    switch (temp_a0) {
    case 0xB9:
        D_800D27D0 = temp_v0;
block_12:
        sp1C = temp_a0;
        func_1508C07C(temp_a0);
        (*(s8 *)((u8 *)D_800D27D0 + 0x1700)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1701)) = 0;
        var_v0 = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1703)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1702)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1704)) = 0;
        (*(s16 *)((u8 *)D_800D27D0 + 0x16BC)) = (s16) temp_a0;
        (*(f32 *)((u8 *)D_800D27D0 + 0x16B8)) = (f32) *(s32 *)((u8 *)&D_80087650 + (D_800E1000 * 4));
        (*(s8 *)((u8 *)D_800D27D0 + 0x1745)) = 0;
        (*(s32 *)((u8 *)D_800D27D0 + 0x16C0)) = 0;
        (*(f32 *)((u8 *)D_800D27D0 + 0x1868)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        if (0 != 0x30) {
            do {
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17A8)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17E8)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1828)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C4)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x186C)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17AC)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17EC)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x182C)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C8)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1870)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B0)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F0)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1830)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16CC)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1874)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B4)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F4)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1834)) = 0.0f;
                var_v0 += 0x10;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C0)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1868)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
            } while (var_v0 != 0x30);
        }
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17A8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17E8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1828)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C4)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x186C)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17AC)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17EC)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x182C)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C8)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1870)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B0)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F0)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1830)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16CC)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1874)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B4)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F4)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1834)) = 0.0f;
        (*(s32 *)((u8 *)D_800D27D0 + 0xC)) = (s32) *(&D_80087690 + D_800E1000);
        return 0;
    case 0xB8:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBB:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBA:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xB7:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBD:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBE:
        D_800D27D0 = temp_v0;
        goto block_12;
    default:
        D_800D27D0 = NULL;
        return 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A040.s")
#endif
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

#ifdef NON_MATCHING
s32 func_1508DF48(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a1;
    struct127 *temp_v1_2;
    u8 *temp_a1;
    u8 *temp_t0;

    temp_a1 = D_800D27D0 + (arg0 * 4);
    if (D_800D27D0 == NULL) {
        return 0;
    }
    temp_v1 = (*(s32 *)((u8 *)temp_a1 + 0xEB0));
    if (temp_v1 >= 0) {
        if (arg1 < 0) {
            return 1;
        }
        (*(s32 *)((u8 *)temp_a1 + 0xEB0)) = -1;
        temp_a3 = temp_v1 * 4;
        temp_t0 = D_800D27D0 + temp_a3;
        if (!((*(s32 *)((u8 *)temp_t0 + 0x11F4)) & 2)) {
            (*(s32 *)((u8 *)temp_t0 + 0xF70)) = -1;
            (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x10F0)) = -1;
            var_a1 = (*(s32 *)((u8 *)D_800D27D0 + 0xEAC));
            if (arg1 == 1) {
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x12F4)) = 0xFA;
                temp_v1_2 = &D_800CC2D0[arg0];
                var_a1 = 4;
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1374)) = (s32) temp_v1_2->x_position;
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x13F4)) = (s32) (temp_v1_2->y_position + 50.0f);
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1474)) = (s32) temp_v1_2->z_position;
            }
            (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1070)) = var_a1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DF48.s")
#endif
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
