#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
#endif

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

#ifdef NON_MATCHING
s32 func_15132454(u8 *arg0, f32 arg1, u8 arg2, s32 arg3) {
    struct {
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        s32 u40;
        s32 u44;
        s16 u48;
        s16 u4A;
        s32 u4C;
        s32 u50;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        s8 u58;
        s8 u59;
        s8 u5A;
        s8 u5B;
        s8 u5C;
        s8 u5D;
        s16 u5E;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x8];
        s32 u88;
        u8 pad8C[0x8];
        f32 u94;
        s32 u98;
        s32 u9C;
        s8 uA0;
        s8 uA1;
        s8 uA2;
        s8 uA3;
        s8 uA4;
        s8 uA5;
        s8 uA6;
    } sp;
    s32 sp28;
    s32 sp20;
    f32 temp_f10;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_t4;
    u8 *temp_t6;

    sp.u2C = 0.0f;
    sp.u34 = 594.49f * arg1;
    sp.u30 = (2.0f * func_150ADA68()) + 5.0f;
    temp_f10 = (func_150ADA68() * 15.0f) + 240.0f;
    sp.u38 = temp_f10;
    sp.u3C = temp_f10 / (sp.u30 * sp.u30);
    sp.u44 = 1;
    sp.u5B = (s8) (u32) temp_f10;
    sp.u5D = 0x69;
    sp.u48 = 0x4417;
    sp.u40 = 0x200004;
    sp.u4C = 0;
    sp.u50 = 0;
    sp.u58 = 0xFF;
    sp.u59 = 0xFF;
    sp.u5A = 0xFF;
    sp.u57 = 0xFF;
    sp.u54 = 0xFF;
    sp.u55 = 0xFF;
    sp.u56 = 0xFF;
    sp.u5C = 0xFF;
    temp_t6 = ((u8 *)&D_800A5860);
    (*(s32 *)((u8 *)(&sp.u70) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u70) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u70) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)temp_t6 + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)temp_t6 + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)temp_t6 + 8));
    sp.u5E = 1;
    sp.u60 = 0xFF;
    sp.u62 = 1;
    sp.u64 = 1.0f;
    var_v1_2 = 0;
    if (func_150ADA20() & 1) {
        var_v1_2 = 0x40;
    }
    sp20 = var_v1_2;
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    temp_t4 = ((u8 *)&D_800A5860);
    sp.u98 = var_v0 | 0x4C000 | var_v1_2;
    sp.uA0 = 6;
    sp.uA1 = 6;
    sp.uA2 = 0x27;
    sp.uA3 = -1;
    sp.uA4 = -1;
    sp.uA5 = 0;
    sp.u9C = 0;
    sp.uA6 = 0xFF;
    (*(s32 *)((u8 *)(&sp.u88) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
    (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
    (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
    sp.u4A = 0x12C;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u94 = 0.0f;
    temp_v0 = func_151307F0((s32) &sp.u40, 1U, 0, 0x14, (u8) (s32) arg2, arg3);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        sp28 = temp_v0;
        memcpy(temp_v0 + 0xA8, &sp.u2C, 0x14);
        var_v1 = sp28;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15132454.s")
#endif