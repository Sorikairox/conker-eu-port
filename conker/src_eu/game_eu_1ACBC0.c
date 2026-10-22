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

#ifdef NON_MATCHING
/* func_1517F470 takes one argument; the matching code passes a1-a3 through unused */
s32 func_1517F51C(s32 arg0) {
    if (func_1517F470(arg0) == 0xFF) {
#else
s32 func_1517F51C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_1517F470(arg0, arg1, arg2, arg3) == 0xFF) {
#endif
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

#ifdef NON_MATCHING
Gfx *func_1517F910(Gfx *gdl, s32 arg1) {
    s32 r = func_1517F470(arg1);

    if (r == 0) {
        return gdl;
    }
    return func_1517F5FC(gdl, r, D_800DE1D0[arg1][0], D_800DE1D0[arg1][1], D_800DE1D0[arg1][2], arg1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517F910.s")
#endif
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

#ifdef NON_MATCHING
extern u8 D_8008D3B0[][6];

/* Pulsing overlay: alpha D_800DE1BB (scaled by a 0..1 wave from func_15048A40 when D_800DE1BC is set),
 * colour D_8008D3B0[D_800DE1BA] (first of its two RGB triples). */
Gfx *func_1517FAD4(Gfx *gdl) {
    u8 *c;
    s32 a;
    f32 t;

    if (D_800DDE08 == 0) {
        return gdl;
    }
    a = D_800DE1BB;
    if (a == 0) {
        return gdl;
    }
    /* the asm leaves t uninitialised (a stale stack word) when D_800DE1BC == 0 and sets 0 on the wave path:
     * use 0 on both paths (UNVERIFIED for the non-wave path) */
    t = 0.0f;
    if (D_800DE1BC != 0) {
        a = (f32)D_800DE1BB * ((func_15048A40(D_800DE1B9) + 1.0f) * 0.5f);
    }
    c = D_8008D3B0[D_800DE1BA];
    return func_1517F5FC(gdl, a, (s32)((c[3] - c[0]) * t + c[0]), (s32)((c[4] - c[1]) * t + c[1]),
                         (s32)((c[5] - c[2]) * t + c[2]), 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_1517FAD4.s")
#endif
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

#ifdef NON_MATCHING
/* P38: m2c draft (ctx K&R header fixed), func_1517FF64 calls fixed by hand */
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_1517FF64(u8 *, s16, s16, s16, s16, s32);
extern s32 D_80090678;
extern s32 D_8009067C;

u8 *func_15182450(u8 *arg0) {
    s16 spF4;
    s16 spF2;
    s16 spF0;
    s32 spEC;
    s32 spE8;
    s32 spDC;
    f32 spD0;
    u8 *spA8;
    u8 *sp88;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp2C;
    f32 temp_f12;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f2;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_t6;
    s16 temp_t7;
    s16 temp_t8;
    s16 temp_t8_2;
    s16 temp_t9_3;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v0_4;
    s16 var_v1;
    s16 var_v1_2;
    s16 var_v1_5;
    s16 var_v1_6;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f16;
    s32 temp_f4;
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_t9_4;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_7;
    s32 var_v1_8;
    u8 *temp_a0;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_11;
    u8 *temp_s0_12;
    u8 *temp_s0_13;
    u8 *temp_s0_14;
    u8 *temp_s0_15;
    u8 *temp_s0_16;
    u8 *temp_s0_17;
    u8 *temp_s0_18;
    u8 *temp_s0_19;
    u8 *temp_s0_20;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_v0;
    u8 *var_s0;

    var_s0 = arg0;
    if (D_800DDE18 == 0) {

    } else {
        temp_f2 = *(f32 *) D_800DDE18 * 0.01f;
        if (temp_f2 < 0.0f) {
            var_f2 = 0.0f;
        } else {
            if (temp_f2 > 1.0f) {
                var_f0 = 1.0f;
            } else {
                var_f0 = temp_f2;
            }
            var_f2 = var_f0;
        }
        if (var_f2 == 0.0f) {

        } else {
            temp_s0 = var_s0 + 8;
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)var_s0 + 4)) = 0;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF7000000;
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0x10001;
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xD9E0FFFE;
            (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
            temp_s0_3 = temp_s0_2 + 8;
            (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xD9FFFFFF;
            (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x200004;
            temp_s0_4 = temp_s0_3 + 8;
            (*(s32 *)((u8 *)temp_s0_4 + 4)) = 4;
            (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xEF302C0F;
            temp_f12 = (*(f32 *)((u8 *)D_800BE628 + 0x24));
            temp_f4 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x28));
            temp_f16 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x2C));
            spF2 = (s16) temp_f4;
            spF4 = (s16) temp_f16;
            temp_f8 = (s32) (*(f32 *)((u8 *)D_800BE628 + 0x30));
            spD0 = var_f2;
            spF0 = (s16) temp_f8;
            temp_f6 = (s32) ((temp_f12 - 30.0f) + ((((*(f32 *)((u8 *)D_800BE628 + 8)) * 0.7f) + 30.0f) * var_f2));
            sp40 = (s32) (s16) temp_f6;
            spEC = temp_f6;
            temp_a0 = func_1517FF64(temp_s0_4 + 8, (s16) temp_f16, (s16) (s32) temp_f12, (s16) temp_f8, (s16) temp_f6, 0);
            temp_f10 = (s32) (((*(f32 *)((u8 *)D_800BE628 + 0x28)) + 30.0f) - ((((*(f32 *)((u8 *)D_800BE628 + 8)) * (1.0f - 0.7f)) + 30.0f) * var_f2));
            sp3C = (s32) (s16) temp_f10;
            spE8 = temp_f10;
            temp_v0 = func_1517FF64(temp_a0, spF4, (s16) temp_f10, spF0, spF2, 0);
            (*(s32 *)((u8 *)temp_v0 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_v0 + 4)) = 0;
            (*(s32 *)((u8 *)temp_v0 + 0xC)) = -1;
            (*(s32 *)((u8 *)temp_v0 + 8)) = 0xD7000002;
            (*(s32 *)((u8 *)temp_v0 + 0x10)) = 0xEF002CFF;
            (*(s32 *)((u8 *)temp_v0 + 0x14)) = 0x5011C4;
            (*(s32 *)((u8 *)temp_v0 + 0x1C)) = -0xC07;
            (*(s32 *)((u8 *)temp_v0 + 0x18)) = 0xFCFFFFFF;
            spA8 = temp_v0 + 0x20;
            (*(s32 *)((u8 *)temp_v0 + 0x20)) = 0xFD900000;
            temp_s0_5 = temp_v0 + 0x28;
            (*(s32 *)((u8 *)spA8 + 4)) = func_1510D66C(D_80090678, 0, 3, 0);
            (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x07000000;
            (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5900000;
            temp_s0_6 = temp_s0_5 + 8;
            (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF3000000;
            (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x077FF000;
            temp_s0_7 = temp_s0_6 + 8;
            (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xF5801000;
            (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0x9C270;
            temp_s0_8 = temp_s0_7 + 8;
            (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xF2002002;
            (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0x1FE0FE;
            temp_s0_9 = temp_s0_8 + 8;
            temp_s0_10 = temp_s0_9 + 8;
            temp_t7 = (s16) temp_f8 * 4;
            temp_s0_11 = temp_s0_10 + 8;
            temp_f10_2 = (s32) ((128.0f / (*(f32 *)((u8 *)D_800BE628 + 4))) * 1024.0f);
            if (temp_t7 > 0) {
                var_v0 = temp_t7;
            } else {
                var_v0 = 0;
            }
            temp_t8 = (spEC + 0x1E) * 4;
            if (temp_t8 > 0) {
                var_v1 = temp_t8;
            } else {
                var_v1 = 0;
            }
            temp_t6 = spF4 * 4;
            (*(s32 *)((u8 *)temp_s0_9 + 0)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_v0 & 0xFFF) << 0xC));
            if (temp_t6 > 0) {
                var_v0_2 = temp_t6;
            } else {
                var_v0_2 = 0;
            }
            temp_t8_2 = sp40 * 4;
            if (temp_t8_2 > 0) {
                var_v1_2 = temp_t8_2;
            } else {
                var_v1_2 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_9 + 4)) = (s32) ((var_v1_2 & 0xFFF) | ((var_v0_2 & 0xFFF) << 0xC));
            (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xE1000000;
            if (temp_t6 < 0) {
                if ((s16) temp_f10_2 < 0) {
                    temp_t8_3 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                    if (temp_t8_3 > 0) {
                        var_t3 = temp_t8_3;
                    } else {
                        var_t3 = 0;
                    }
                } else {
                    var_v1_3 = 0;
                    temp_t9 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                    if (temp_t9 < 0) {
                        var_v1_3 = temp_t9;
                    }
                    var_t3 = var_v1_3;
                }
            } else {
                var_t3 = 0;
            }
            if (sp40 & 0x20000000) {
                temp_t6_2 = (s32) (temp_t8_2 * 0x222) >> 7;
                var_v1_4 = 0;
                if (temp_t6_2 < 0) {
                    var_v1_4 = temp_t6_2;
                }
            } else {
                var_v1_4 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_10 + 4)) = (s32) ((-var_v1_4 & 0xFFFF) | (var_t3 * -0x10000));
            temp_t9_2 = (temp_f10_2 << 0x10) | 0x222;
            (*(s32 *)((u8 *)temp_s0_11 + 0)) = 0xF1000000;
            sp2C = temp_t9_2;
            (*(s32 *)((u8 *)temp_s0_11 + 4)) = temp_t9_2;
            temp_s0_12 = temp_s0_11 + 8;
            (*(s32 *)((u8 *)temp_s0_12 + 0)) = 0xFD900000;
            spDC = temp_f10_2;
            sp38 = (s32) temp_t7;
            sp34 = (s32) temp_t6;
            sp88 = temp_s0_12;
            temp_s0_13 = temp_s0_12 + 8;
            (*(s32 *)((u8 *)temp_s0_12 + 4)) = func_1510D66C(D_8009067C, 0, 3, 0);
            (*(s32 *)((u8 *)temp_s0_13 + 4)) = 0x07000000;
            (*(s32 *)((u8 *)temp_s0_13 + 0)) = 0xF5900000;
            temp_s0_14 = temp_s0_13 + 8;
            (*(s32 *)((u8 *)temp_s0_14 + 0)) = 0xF3000000;
            (*(s32 *)((u8 *)temp_s0_14 + 4)) = 0x077FF000;
            temp_s0_15 = temp_s0_14 + 8;
            (*(s32 *)((u8 *)temp_s0_15 + 0)) = 0xF5801000;
            (*(s32 *)((u8 *)temp_s0_15 + 4)) = 0x9C270;
            temp_s0_16 = temp_s0_15 + 8;
            (*(s32 *)((u8 *)temp_s0_16 + 0)) = 0xF2002002;
            (*(s32 *)((u8 *)temp_s0_16 + 4)) = 0x1FE0FE;
            temp_s0_17 = temp_s0_16 + 8;
            temp_s0_18 = temp_s0_17 + 8;
            if (temp_t7 > 0) {
                var_v0_3 = temp_t7;
            } else {
                var_v0_3 = 0;
            }
            temp_t9_3 = sp3C * 4;
            if (temp_t9_3 > 0) {
                var_v1_5 = temp_t9_3;
            } else {
                var_v1_5 = 0;
            }
            (*(s32 *)((u8 *)temp_s0_17 + 0)) = (s32) ((var_v1_5 & 0xFFF) | 0xE4000000 | ((var_v0_3 & 0xFFF) << 0xC));
            if (temp_t6 > 0) {
                var_v0_4 = temp_t6;
            } else {
                var_v0_4 = 0;
            }
            temp_s0_19 = temp_s0_18 + 8;
            var_v1_6 = 0;
            temp_a2 = spE8 - 0x1E;
            temp_a2_2 = temp_a2 * 4;
            if (temp_a2_2 > 0) {
                var_v1_6 = temp_a2_2;
            }
            (*(s32 *)((u8 *)temp_s0_17 + 4)) = (s32) ((var_v1_6 & 0xFFF) | ((var_v0_4 & 0xFFF) << 0xC));
            (*(s32 *)((u8 *)temp_s0_18 + 0)) = 0xE1000000;
            if (temp_t6 < 0) {
                temp_t9_4 = (s32) (temp_t6 * (s16) temp_f10_2) >> 7;
                if ((s16) temp_f10_2 < 0) {
                    if (temp_t9_4 > 0) {
                        var_t3_2 = temp_t9_4;
                    } else {
                        var_t3_2 = 0;
                    }
                } else {
                    var_v1_7 = 0;
                    if (temp_t9_4 < 0) {
                        var_v1_7 = temp_t9_4;
                    }
                    var_t3_2 = var_v1_7;
                }
            } else {
                var_t3_2 = 0;
            }
            var_v1_8 = 0;
            if (temp_a2 & 0x20000000) {
                temp_t6_3 = (s32) (temp_a2_2 * 0x222) >> 7;
                var_v1_8 = 0;
                if (temp_t6_3 < 0) {
                    var_v1_8 = temp_t6_3;
                }
            }
            (*(s32 *)((u8 *)temp_s0_18 + 4)) = (s32) ((-var_v1_8 & 0xFFFF) | (var_t3_2 * -0x10000));
            (*(s32 *)((u8 *)temp_s0_19 + 0)) = 0xF1000000;
            temp_s0_20 = temp_s0_19 + 8;
            (*(s32 *)((u8 *)temp_s0_19 + 4)) = sp2C;
            (*(s32 *)((u8 *)temp_s0_20 + 4)) = 1;
            (*(s32 *)((u8 *)temp_s0_20 + 0)) = 0xD9FFFFFF;
            var_s0 = temp_s0_20 + 8;
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ACBC0/func_15182450.s")
#endif
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
