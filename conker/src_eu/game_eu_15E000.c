#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ f32 unk58[2];
    /* 0x60 */ u8 pad60[0x48];
    /* 0xA8 */ f32 unkA8;
} struct_eu_15E000;

void func_15131E58(f32 *arg0, f32 arg1);
void func_15131E88(f32 *arg0, f32 arg1);
void func_15131EC8(f32 *arg0, f32 arg1);


s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *obj;
    s32 type;

    switch (arg1) {
    case 0:
        type = 0x2B;
        break;
    case 1:
        type = 0x52;
        break;
    case 2:
        type = 0x47;
        break;
    default:
        type = 0x2B;
        break;
    }
    obj = func_15167A68(type, arg5, arg3 + 0xA8, 1, arg4, 1);
    if (obj == NULL) {
        return 0;
    }
    memcpy(obj + 0x10, arg0, 0x70);
    if (arg2 != 0) {
        *(struct_eu_bytes24 *)(obj + 0x80) = *(struct_eu_bytes24 *)arg2;
    } else {
        obj[0x9C] = 0;
    }
    return (s32)obj;
}

s32 func_151307F0(s32, u8, s32, s32, u8, s32);
s32 func_151308E4(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    return func_151307F0(arg0, arg1, 0, arg2, arg3, arg4);
}

s32 func_151308E4(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4);

void func_1513092C(s32 arg0, u8 arg1, s32 arg2) {
    func_151308E4(arg0, arg1, arg2, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_1513095C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_1513100C.s")

typedef struct {
    u8 pad0[0x24];
    u8 u24;
    u8 u25;
    u8 u26;
    u8 u27;
    u8 u28;
    u8 u29;
    u8 u2A;
    u8 u2B;
    u8 u2C;
    u8 pad2D[0x43];
    u8 u70;
    u8 u71;
} struct_15E000_col;
void func_151318EC(s32 arg0_, s32 arg1_, s32 arg2_, s32 arg3_, s32 arg4_) {
    s16 *arg0 = (s16 *)arg0_;
    s16 *arg1 = (s16 *)arg1_;
    s16 *arg2 = (s16 *)arg2_;
    s16 *arg3 = (s16 *)arg3_;
    struct_15E000_col *arg4 = (struct_15E000_col *)arg4_;

    switch (arg4->u70) {
    case 1:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 2:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 3:
        *arg0 = arg4->u28;
        *arg1 = arg4->u29;
        *arg2 = arg4->u2A;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    case 4:
    case 6:
        *arg0 = *arg1 = *arg2 = *arg3 = 0;
        break;
    case 5:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = arg4->u2B;
        break;
    case 7:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = arg4->u2B;
        break;
    case 8:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = 0;
        break;
    default:
        *arg0 = (arg4->u24 * arg4->u2C) >> 8;
        *arg1 = (arg4->u25 * arg4->u2C) >> 8;
        *arg2 = (arg4->u26 * arg4->u2C) >> 8;
        *arg3 = 0;
        break;
    }
}

void func_15131A84(s32 arg0_, s32 arg1_, s32 arg2_, s32 arg3_, s32 arg4_) {
    s16 *arg0 = (s16 *)arg0_;
    s16 *arg1 = (s16 *)arg1_;
    s16 *arg2 = (s16 *)arg2_;
    s16 *arg3 = (s16 *)arg3_;
    struct_15E000_col *arg4 = (struct_15E000_col *)arg4_;

    switch (arg4->u71) {
    case 1:
    case 5:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = 0;
        break;
    case 2:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = 0;
        break;
    case 8:
        *arg0 = *arg1 = *arg2 = 0;
        *arg3 = arg4->u2B;
        break;
    case 3:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = 0;
        break;
    case 4:
    case 6:
        *arg0 = arg4->u28;
        *arg1 = arg4->u29;
        *arg2 = arg4->u2A;
        *arg3 = arg4->u2B;
        break;
    case 7:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = arg4->u2B;
        break;
    case 9:
        *arg0 = arg4->u24;
        *arg1 = arg4->u25;
        *arg2 = arg4->u26;
        *arg3 = arg4->u2B;
        break;
    default:
        *arg0 = *arg1 = *arg2 = arg4->u2C;
        *arg3 = (arg4->u27 * arg4->u2B) >> 8;
        break;
    }
}

void func_15131BBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15131A84(arg4, arg5, arg6, arg7, arg8);
    func_151318EC(arg0, arg1, arg2, arg3, arg8);
}

s32 func_15131C1C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E58(arg0->unk58, arg0->unkA8);
    return 1;
}

s32 func_15131C4C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E88(arg0->unk58, arg0->unkA8);
    return 1;
}

s32 func_15131C7C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131EC8(arg0->unk58, arg0->unkA8);
    return 1;
}

void func_15131CAC(struct102 *arg0) {
    func_15169804(arg0);
}

void func_15131CCC(struct102 *arg0) {
    func_15169824(arg0);
}

void func_15131CEC(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    D_80089BB4[idx](arg0);
}

void func_15131D38(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    D_80089BE4[idx](arg0);
}

s32 func_15131D84(s32 arg0, s32 arg1) {
    return 0;
}

void func_15131D98(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    (*(f32 *)((u8 *)arg0 + 0x4C)) = (f32) ((*(f32 *)((u8 *)arg1 + 0)) * func_151423D8((*(u8 *)((u8 *)arg2 + 0)) - 0x40));
    (*(f32 *)((u8 *)arg0 + 0x54)) = (f32) ((*(f32 *)((u8 *)arg1 + 4)) * func_151423D8((*(u8 *)((u8 *)arg2 + 1)) - 0x40));
    (*(u8 *)((u8 *)arg2 + 0)) = (u8) (((*(u8 *)((u8 *)arg3 + 0)) * D_800BE9E4) + (*(u8 *)((u8 *)arg2 + 0)));
    (*(u8 *)((u8 *)arg2 + 1)) = (u8) (((*(u8 *)((u8 *)arg3 + 1)) * D_800BE9E4) + (*(u8 *)((u8 *)arg2 + 1)));
}

void func_15131E58(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[1] *= arg1;
    }
}

void func_15131E88(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[2] *= arg1;
    }
}

void func_15131EC8(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[1] *= arg1;
        arg0[2] *= arg1;
    }
}

void func_15131F14(s32 arg0, s32 arg1) {
    func_15131F34(arg0, arg1, arg0 + 0xA8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15131F34.s")

void func_1513206C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131EC8(arg0->unk58, arg0->unkA8);
    func_15131F34(arg0, arg1, (u8 *)arg0 + 0xB0);
}

void func_151320AC(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E88(arg0->unk58, arg0->unkA8);
    func_15131F34(arg0, arg1, (u8 *)arg0 + 0xB0);
}

s32 func_151320EC(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x3C) * 0.060000002f + *(f32 *)(arg2 + 4);
    *(f32 *)(arg0 + 0x58) *= *(f32 *)(arg3 + 4);
    *(f32 *)(arg0 + 0x5C) = -*(f32 *)(arg3 + 4) * *(f32 *)(arg0 + 0x5C);
    *(f32 *)(arg0 + 0x60) *= *(f32 *)(arg3 + 4);
    if (fabsf(*(f32 *)(arg0 + 0x5C)) < 1.9970001f) {
        *(f32 *)(arg0 + 0x58) = 0.0f;
        *(f32 *)(arg0 + 0x5C) = 0.0f;
        *(f32 *)(arg0 + 0x60) = 0.0f;
        *(f32 *)(arg0 + 0x64) = 0.0f;
        arg3[0] &= ~1;
        *(s32 *)(arg0 + 0x68) &= ~6;
    }
    return 1;
}

extern void (*D_80089C18[])(u8 *, u8 *, u8);
void func_1513219C(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (*(s32 *)(arg0 + 0x68) & 0x4000) {
        f = D_80089C18[arg0[0x75]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

void func_151321F4(u8 *arg0, u8 *arg1, f32 arg2, u8 *arg3, f32 *arg4, f32 *arg5)
{
  u8 temp_a0;
  f32 r;
  temp_a0 = ((*((s8 *) (((u8 *) arg1) + 0))) * D_800BE9E4) + (*((u8 *) (((u8 *) arg0) + 0)));
  temp_a0 = (*((u8 *) (((u8 *) arg0) + 0)) = temp_a0);  // fakematch: chained store assignment pins temp_a0 to a0
  *((u8 *) (((u8 *) arg0) + 1)) = (u8) (((*((s8 *) (((u8 *) arg1) + 1))) * D_800BE9E4) + (*((u8 *) (((u8 *) arg0) + 1))));
  temp_a0 = temp_a0 - 0x40;
  r = func_151423D8(temp_a0);
  *arg4 = ((*((f32 *) (((u8 *) arg3) + 0))) * (0, r)) + arg2;  // fakematch: comma flips mul.s operand order
  r = func_151423D8((*((u8 *) (((u8 *) arg0) + 1))) - 0x40);
  *arg5 = ((*((f32 *) (((u8 *) arg3) + 4))) * (0, r)) + arg2;  // fakematch: comma flips mul.s operand order
}

void func_151322BC(s32 arg0, u8 arg1) {
    const s32 sp1C[3] = {0x2B, 0x47, 0x52};

    func_15169260(sp1C, 0x3, arg0, arg1);
}

s32 func_1513230C(u8 *arg0, s32 arg1) {
    func_151321F4(arg0 + 0xA8, arg0 + 0xAA, *(f32 *)(arg0 + 0xAC), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C);
    return 1;
}

s32 func_1513235C(u8 *arg0, s32 arg1) {
    f32 temp_f12;
    f32 temp_f2;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0xA8));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0xB0)) * sqrtf(temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) = temp_f12;
    (*(f32 *)((u8 *)arg0 + 0x38)) = temp_f12;
    (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) ((*(f32 *)((u8 *)arg0 + 0xB4)) - ((*(f32 *)((u8 *)arg0 + 0xB8)) * temp_f2 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) (temp_f2 + D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0xAC)) < (*(f32 *)((u8 *)arg0 + 0xA8))) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15132454.s")
