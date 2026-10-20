#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1517F470();

typedef struct {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x1B];
    /* 0x2B */ s8 unk2B;
    /* 0x2C */ u8 pad2C[0x2];
    /* 0x2E */ s16 unk2E;
} struct_eu_1ACBC0;


extern u8 D_800DE1D0[][3];
extern u8 D_800DE1F0[];
void func_1517F3B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5) {
    s8 *p;
    p = &((s8 *)&D_800DDDAC)[arg5];
    if ((arg4 != *p) || (((s32 *)&D_800DDDB0)[arg5] < ((s32 *)&D_800DDE28)[arg5]) || (D_800DE1F0[arg5] != 0)) {
        D_800DE1D0[arg5][1] = arg1;
        D_800DE1D0[arg5][2] = arg2;
        D_800DE1D0[arg5][0] = arg0;
        ((s32 *)&D_800DDE28)[arg5] = arg3;
        ((s32 *)&D_800DDDB0)[arg5] = 0;
        *p = arg4;
        D_800DE1F0[arg5] = 0;
    }
}

extern u8 D_800DE1F0[];
s32 func_1517F470(arg0)
s32 arg0;
{
    s32 d;
    s32 *new_var; // fakematch: base pointer temp
    s32 r;
    s32 b;

    r = (((s32 *)&D_800DDDB0)[arg0] * 0xFF) / d; // fakematch: dead store (d unset), permuter artifact that fixes the register roles
    b = D_800DE1F0[arg0];
    if (b != 0) {
        r = b;
    } else {
        d = (new_var = (s32 *)&D_800DDE28)[arg0];
        if (d != 0) {
            r = (((s32 *)&D_800DDDB0)[arg0] * 0xFF) / d;
            if (r >= 0x100) {
                r = 0xFF;
            }
        } else {
            r = 0xFF;
        }
        if (((s8 *)&D_800DDDAC)[arg0] == 0) {
            r = 0xFF - r;
        }
    }
    return r;
}

s32 func_1517F51C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_1517F470(arg0, arg1, arg2, arg3) == 0xFF) {
        return 1;
    }
    return 0;
}

s32 func_1517F54C(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = -1;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
        do {
            if ((func_1517F470(var_s0) > 0) || ((&D_800DDDC8)[var_s0] > 0.0f)) {
                var_s1 += 1;
            }
            var_s0 += 1;
        } while (D_80082FA0 >= var_s0);
    }
    if (var_s1 == D_80082FA0) {
        return 1;
    }
    return 0;
}

#define VP(i, o) (*(f32 *)((u8 *)D_800BE628 + (i) * 0x180 + (o)))
Gfx *func_1517F5FC(Gfx *gfx, s32 a, s32 r, s32 g, s32 b, s32 i) {
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);
    gDPSetOtherMode(gfx++, 0x2CFF, 0x504344);
    gDPFillRectangle(gfx++, VP(i, 0x2C), VP(i, 0x24), VP(i, 0x30), VP(i, 0x28));
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F910.s")

s32 func_1517F40C(s32 arg0) {
    if ((&D_800DDDB0)[arg0] >= (&D_800DDE28)[arg0]) {
        return 1;
    }
    return 0;
}

void func_1517F448(s32 arg0) {
    if ((&D_800DDDB0)[arg0] != (&D_800DDE28)[arg0]) {
        (&D_800DDDB0)[arg0] += D_800BE9E4;
    }
}

void func_1517F9F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *temp_v0 = D_800DE1C0[arg5];

    temp_v0[0] = arg0;
    temp_v0[1] = arg1;
    temp_v0[2] = arg2;
    D_800DE1CC[arg5] = arg3;
    D_800DE240[arg5] = arg4;
}

Gfx *func_1517F5FC(Gfx *, s32, s32, s32, s32, s32);
s32 func_1517FA48(s32 arg0, s32 arg1) {
    u8 *temp_v0;
    s32 temp_a1;
    if ((u16)D_800DE240[arg1] == 0) {
        return arg0;
    }
    temp_a1 = D_800DE1CC[arg1];
    if (temp_a1 == 0) {
        return arg0;
    }
    temp_v0 = D_800DE1C0[arg1];
    return (s32)func_1517F5FC((u8 *)arg0, temp_a1, temp_v0[0], temp_v0[1], temp_v0[2], arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FAD4.s")

void func_1517FC90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DE1B8 = arg2;
    D_800DE1B9 = 0;
    D_800DE1BA = arg0;
    D_800DE1BB = arg3;
    D_800DE1BC = arg4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FCCC.s")

void func_1517FD24(void)
{
  s32 new_var;
  if (D_800DDE08 != 0)
  {
    if (D_800BE9E4 < ((s32) D_800DDE08))
    {
      new_var = D_800BE9E4;
      D_800DDE08 -= new_var;
    }
    else
    {
      D_800DDE08 = 0;
    }
    D_800DE1B9 += D_800DE1B8 * D_800BE9E4;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FD84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FF64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1518010C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15180AF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15181A6C.s")

s32 func_15182238(s32 arg0) {
    if ((&D_800DDDC8)[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}

extern f32 D_800A768C;

void func_15182270(s32 arg0, s32 arg1) {
    f32 *p;

    if (arg1 == 0) {
        (&D_800DDDC8)[arg0] = 0.0f;
    } else {
        (&D_800DDDD8)[arg0] = 0.0f;
        p = D_800DE218[arg0];
        (&D_800DDDC8)[arg0] = D_800A768C;
        p[0] = 0.0f;
        p[1] = 0.0f;
    }
    (&D_800DDE1C)[arg0] = arg1;
}

extern f32 D_800A7690;

void func_15181D70(s32 arg0) {
    f32 *temp_v1;

    (&D_800DDDD8)[arg0] = D_800A7690;
    (&D_800DDDC8)[arg0] = 0.0f;
    temp_v1 = D_800DE218[arg0];
    (*(f32 *)temp_v1) = 0.0f;
    temp_v1[1] = 0.0f;
    (&D_800DDE20)[arg0] = 1;
}

void func_15182338(s32 arg0) {
    (&D_800DDDD8)[arg0] = 0.0;
    (&D_800DDDC8)[arg0] = 0.0f;
    D_800DE218[arg0][0] = 0.0f;
    D_800DE218[arg0][1] = 0.0f;
    (&D_800DDE20)[arg0] = 0;
}

extern u8 D_800DE1D0[][3];
extern u8 D_800DE1F0[];
extern f32 D_800A7694;
void func_15182388(s32 arg0) {
    f32 *p;
    if (D_800BE616 != 0) {
        D_800DE1D0[arg0][0] = 0;
        D_800DE1D0[arg0][1] = 0;
        D_800DE1D0[arg0][2] = 0;
        ((s32 *)&D_800DDE28)[arg0] = 0x19;
        ((s32 *)&D_800DDDB0)[arg0] = 0;
        ((u8 *)&D_800DDDAC)[arg0] = 0;
        D_800DE1F0[arg0] = 0;
        return;
    }
    (&D_800DDE3C)[arg0] = 1;
    (&D_800DDDC8)[arg0] = 1.0f;
    p = D_800DE218[arg0];
    p[0] = 0.0f;
    p[1] = 0.0f;
    (&D_800DDDD8)[arg0] = D_800A7694;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182BE0.s")

void func_15182CB8(struct_eu_1ACBC0 *arg0) {
    arg0->unk2B = arg0->unk2E * arg0->unkE;
}

Gfx *func_1517F5FC(Gfx *, s32, s32, s32, s32, s32);
u8 *func_15182CD8(u8 *arg0, u8 *arg1, s16 arg2) {
    u8 *v;
    v = arg1 + 0x28;
    if (arg2 == arg1[0x2C]) {
        arg0 = func_1517F5FC(arg0, v[3], v[0], v[1], v[2], v[4]);
    }
    return arg0;
}
