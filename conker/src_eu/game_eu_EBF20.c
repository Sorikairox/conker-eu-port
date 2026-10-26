#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A03E0[];
extern u8 D_800A0430[];
#endif

#ifdef NON_MATCHING
void scenery_platform_drift_update(u8 *, s32, s32, f32); /* P95: f32 parameter */
#else
void scenery_platform_drift_update(u8 *, s32, s32, s32);
#endif

void func_150BE710(u8 *arg0)
{
  u8 temp_t2;
  u8 *new_var2;
  int new_var3;
  u8 *new_var;
  new_var2 = arg0;
  if (((*((u8 *) (((u8 *) arg0) + 0x73))) & 3) != 3)
  {
#ifdef NON_MATCHING
    scenery_platform_drift_update(arg0, 1, 0x62C, 500.0f); /* P95: float literal (asm passes the bits 0x43FA0000) */
#else
    scenery_platform_drift_update(arg0, 1, 0x62C, 0x43FA0000);
#endif
    if ((*((u8 *) (((u8 *) arg0) + 0x4F))) & 4)
    {
      new_var3 = 0x64;
      *((f32 *) (((u8 *) arg0) + 0x84)) = (f32) ((*((f32 *) (((u8 *) arg0) + new_var3))) + (*((f32 *) (((u8 *) arg0) + 0x84))));
    }
    else
      if ((*((f32 *) (((u8 *) arg0) + 0x84))) > 270.0f)
    {
      *((f32 *) (((u8 *) arg0) + 0x84)) = 270.0f;
    }
    if ((*((f32 *) (((u8 *) arg0) + 0x84))) > 360.0f)
    {
      temp_t2 = 0xFFFC;
      temp_t2 = (*((u8 *) (((u8 *) new_var2) + 0x73))) & temp_t2;
      new_var = (u8 *) arg0;
      *((u8 *) (new_var + 0x73)) = (*((u8 *) (new_var + 0x73))) & 0xFFFC;
      *((u8 *) (new_var + 0x73)) = (u8) ((*((u8 *) (new_var + 0x73))) | 3);
      *((f32 *) (new_var + 0x64)) = 0.0f;
      func_100111C8(*((u16 *) (new_var + 0x74)));
      *((u16 *) (new_var + 0x74)) = 0U;
    }
  }
}

#ifdef NON_MATCHING
void func_150BE7E8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f2;
    f32 var_f22;

    temp_f12 = (f32) (*(s16 *)((u8 *)arg0 + 0x80));
    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 0x7E));
    temp_f0 = (f32) (*(s16 *)((u8 *)arg0 + 0x7C));
    temp_f20 = (f32) (*(s16 *)((u8 *)arg0 + 0x3C)) * 0.000061035156f;
    temp_f20_2 = temp_f20 - (temp_f20 * 0.128f);
    var_f22 = ((f32) (*(s16 *)((u8 *)arg0 + 0x3E)) * 0.000061035156f) + (temp_f20_2 * (f32) D_800BE9E4);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x82)) - temp_f0) * var_f22) + temp_f0);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x84)) - temp_f2) * var_f22) + temp_f2);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)arg0 + 0x86)) - temp_f12) * var_f22) + temp_f12);
    if (var_f22 > 1.0f) {
        var_f22 = 1.0f;
    }
    (*(s16 *)((u8 *)arg0 + 0x3C)) = (s16) (s32) (temp_f20_2 * 16384.0f);
    (*(s16 *)((u8 *)arg0 + 0x3E)) = (s16) (s32) (var_f22 * 16384.0f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE7E8.s")
#endif
s16 *func_150BE938(s16 *arg0, s32 arg1) {
    u8 *p = (u8 *)&D_800CC2D0[arg1];

    arg0[0] = 0x68;
    arg0[1] = *(s32 *)(p + 0x2E8);
    arg0[2] = 0xE;
    arg0[3] = *(s32 *)(p + 0x2E4);
    return arg0 + 4;
}

#ifdef NON_MATCHING
void func_1504715C(void *, u8 *);
s32 func_15150D7C(s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32 *, f32, s32, s32, s32, s32);
void func_1515C7B4(u8 *, f32 *, f32 *, f32 *);
extern s32 D_800A0408;
extern s32 D_800A0434;

void func_150BE994(u8 *arg0, s32 arg1, s32 arg2) {
    struct {
        s16 u58;
        s16 u5A;
        s16 u5C;
        s16 u5E;
        struct17 u60;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        s16 u84;
        s16 u86;
        s16 u88;
        s16 u8A;
        s16 u8C;
        s16 u8E;
        s16 u90;
        s16 u92;
        s8 u94;
        u8 pad95[0x3];
        f32 u98;
        s16 u9C;
        s16 u9E;
        s32 uA0;
        s32 uA4;
        s32 uA8;
        s32 uAC;
        u8 padB0[0x8];
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        s16 uD0;
        s16 uD2;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        s32 uE0;
        s32 uE4;
        s32 uE8;
        u8 padEC[0x8];
        s16 uF4;
        s16 uF6;
        s16 uF8;
        s16 uFA;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        s16 u10C;
        s16 u10E;
        f32 u110;
        f32 u114;
        f32 u118;
        f32 u11C;
        s8 u120;
        u8 pad121[0x3];
        s32 u124;
        u8 pad128[0x20];
        f32 u148;
        s32 u14C;
        s32 u150;
        s32 u154;
    } sp;
    s32 temp_s1;

    temp_s1 = arg1 & 0xFF;
    if (arg0 != NULL) {
        sp.u148 = ((*(f32 *)((u8 *)arg0 + 0x14C)) + (*(f32 *)((u8 *)arg0 + 0x150))) * 0.5f;
        func_1515C7B4(arg0, &sp.u154, &sp.u150, &sp.u14C);
        func_1504715C(&sp.u124, arg0);
        sp.uE0 = 0xA;
        sp.uE4 = 0;
        (*(f32 *)((u8 *)(&sp.uE8) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 0));
        (*(f32 *)((u8 *)(&sp.uE8) + 4)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 4));
        (*(f32 *)((u8 *)(&sp.uE8) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 8));
        sp.uFC = 13.0f;
        sp.u100 = 9.0f;
        sp.u104 = -1.3260001f;
        sp.uF4 = 0;
        sp.uF6 = 0xFF;
        sp.uF8 = -0x40;
        sp.uFA = 0x32;
        sp.u10C = 0x4B;
        sp.u10E = 0x28;
        sp.u120 = 0xB;
        sp.u114 = 0.0f;
        sp.u108 = 0.441f;
        sp.u118 = 14.098001f;
        sp.u11C = 1.0f;
        sp.u110 = sp.u148;
        func_15150D7C(&sp.uE0, ((u8 *)&D_800A03E0), &D_800A0408, 0xA, 0, 0, 0, 1, -1, &sp.u124, 55.0f, 0, 0, temp_s1, arg2);
        sp.uA4 = 0x11;
        sp.uA8 = 9;
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 0));
        (*(f32 *)((u8 *)(&sp.uAC) + 4)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 4));
        (*(f32 *)((u8 *)(&sp.uAC) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.u154) + 8));
        sp.uC0 = 14.0f;
        sp.uC4 = 11.0f;
        sp.uB8 = 0;
        sp.uBA = 0xFF;
        sp.uBC = -0x3F;
        sp.uBE = 0x4B;
        sp.uD0 = 0x28;
        sp.uD2 = 0x14;
        sp.uC8 = -0.8f;
        sp.uCC = 0.303f;
        sp.uD4 = 0.15100001f;
        sp.uD8 = 0.15900001f;
        sp.uDC = 29.787f;
        func_15152700(&sp.uA4, ((u8 *)&D_800A0430), &D_800A0434, 1, 10.0f, 0U, (u8) temp_s1, arg2);
        sp.u60.unk0 = (*(f32 *)((u8 *)(&sp.u154) + 0));
        sp.u60.unk4 = (*(f32 *)((u8 *)(&sp.u154) + 4));
        sp.u60.unk8 = (*(f32 *)((u8 *)(&sp.u154) + 8));
        sp.u6C = 6.9f;
        sp.u84 = 4;
        sp.u86 = 3;
        sp.u5A = 0xFF;
        sp.u58 = 0;
        sp.u5C = -0x2B;
        sp.u5E = 0x1A;
        sp.u88 = 3;
        sp.u8A = 3;
        sp.u8C = 0x1E;
        sp.u8E = 0x14;
        sp.u90 = 0x9B;
        sp.u92 = 0x64;
        sp.u9C = 0x10;
        sp.u9E = 0xF;
        sp.uA0 = 0;
        sp.u94 = 0;
        sp.u70 = 14.900001f;
        sp.u74 = 1.281f;
        sp.u78 = 0.54300004f;
        sp.u7C = 15.7f;
        sp.u80 = 18.9f;
        sp.u98 = 0.5f;
        func_15154488((struct_eu_15154488 *) &sp.u58, &sp.u60, (s32) &sp.u124, temp_s1 & 0xFF, arg2);
        sp.u94 = 2;
        func_15154488((struct_eu_15154488 *) &sp.u58, &sp.u60, (s32) &sp.u124, temp_s1 & 0xFF, arg2);
        sp.u94 = 0xA;
        func_15154488((struct_eu_15154488 *) &sp.u58, &sp.u60, (s32) &sp.u124, temp_s1 & 0xFF, arg2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EBF20/func_150BE994.s")
#endif