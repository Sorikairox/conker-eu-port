#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BC58.s")

s32 func_1517BD18(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    if (*arg2 >= 0x300) {
        if (*arg2 >= 0x501) {
            *arg2 -= 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BD68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517C11C.s")

s32 func_10004074(s32);
s32 func_10006530(s32, s32, u32);

void func_1517D534(void)
{
  int pad;
  s32 *var_s0;
  s32 temp_a0;
  s32 temp_a1;
  s32 var_s1;
 do { var_s0 = &D_800DDA90; var_s1 = 0; do { temp_a0 = *((s32 *) (((u8 *) var_s0) + 8)); if (temp_a0 != 0) { temp_a1 = (&D_800DD478)[var_s1 * 0x1A]; if (temp_a1 != 0) { func_10006530(temp_a0, temp_a1, D_8003809C); func_10004074(*((s32 *) (((u8 *) var_s0) + 8))); } *((s32 *) (((u8 *) var_s0) + 8)) = 0; } var_s1 += 1; var_s0 += 4; } while (var_s1 != 0xF); } while (0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D5E4.s")

extern u8 D_800DE158[];

void func_1517DAE8(s16 arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    u8 *p;
    s32 i = D_8008CEB0;

    if (i < 3) {
        p = D_800DE158 + i * 16;
        *(s16 *)(p + 0) = arg0;
        *(s16 *)(p + 2) = arg1;
        *(s16 *)(p + 4) = arg2;
        *(f32 *)(p + 0xC) = arg3;
        *(s16 *)(p + 8) = arg4;
        *(s16 *)(p + 0xA) = arg5;
        p[6] = arg6;
        D_8008CEB0 = i + 1;
    }
}


void func_1517DB6C(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_1517DAE8(arg0, arg1, arg2, D_800DBFF0[arg3].unk380, arg4, arg5, (s32) D_800DDD1C >> 3);
}

typedef struct { s16 x, y, z; u8 idx; u8 pad7; u16 a; u16 b; f32 s; } EntDC00;
extern s32 D_800DE188;
s32 func_1517D5E4(s32, s16, s16, s16, f32, s32, s32, s32, s32, s32);

s32 func_1517DC00(s32 arg0, u16 *arg1) {
    s32 saved;

    saved = D_800DE188;
    D_800DDD1C += 5;
    
    if (D_800DDD1C >= 200) {
        D_800DDD1C -= 200;
    }
    while (D_8008CEB0 != 0) {
        D_8008CEB0--;
        if (arg1 != 0) {
            arg0 = func_1517D5E4(arg0, ((EntDC00 *)D_800DE158)[D_8008CEB0].x, ((EntDC00 *)D_800DE158)[D_8008CEB0].y, ((EntDC00 *)D_800DE158)[D_8008CEB0].z, ((EntDC00 *)D_800DE158)[D_8008CEB0].s, ((EntDC00 *)D_800DE158)[D_8008CEB0].a, ((EntDC00 *)D_800DE158)[D_8008CEB0].b, 16, 32, (s32)(arg1 + ((EntDC00 *)D_800DE158)[D_8008CEB0].idx * 640));
        }
    }
    D_800DE188 = saved;
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D7B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517E3CC.s")

void func_1517E5CC(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD8A0[0] = arg0;
    D_800DD8A0[1] = arg1;
    D_800DD8A0[2] = arg2;
}
