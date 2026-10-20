#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void func_151AC3F0(struct17 *, s32 *, s32, u8, s32);
void func_10010FFC(s32, s32, s32, s32, s32, u8 *);
void func_151AEC60(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (-9500.0f < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 5, arg0[0xC], arg0[1]);
        func_10010FFC(0, 17, 21000, 0, 0, obj);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AED60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AEE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AEF34.s")

s32 func_151DA6F8(s32, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151AF064(s32 arg0, u8 arg1, u8 arg2)
{
  f32 sp88[4];
  u8 sp87;
  u8 sp86;
  f32 temp_f12;
  f32 sp7C;
  f32 sp78;
  f32 sp74;
  f32 sp70;
  f32 temp_f2;
  f32 sp68;
  s32 sp64;
  s32 sp60;
  f32 sp5C;
  sp87 = func_150ADA20();
  sp86 = ((func_150ADA20() & 0x7F) & 0xFFFF) - 0x3F;
  sp7C = func_151423D8(sp87);
  sp78 = func_151423D8(sp87 - 0x40);
  sp74 = func_151423D8(sp86);
  sp70 = func_151423D8(sp86 - 0x40);
  temp_f2 = ((func_150ADA68() * 80.0f) + 20.0f) * 0.1f;
  temp_f12 = temp_f2 * sp74;
  sp88[0] = temp_f12 * sp78;
  sp88[1] = (-temp_f2) * sp70;
  sp88[2] = temp_f12 * sp7C;
 dummy_label_888456: ; // fakematch: permuter label (splits the basic block before the rand() calls)
  sp5C = func_150ADA68();
  sp60 = func_150ADA20();
  sp64 = func_150ADA20();
  sp68 = func_150ADA68();
  func_151DA6F8(arg0, sp88, (sp5C * 0.40600002f) + 0.21000001f, (s16) ((((u32) sp60) % 41U) + 0x3C), (((u32) sp64) % 101U) + 0x9B, (sp68 * 4.0f) + 3.1000001f, (func_150ADA20() % 5U) + 3, (s32) arg1, 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, (s32) arg2, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AECA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AF820.s")

s32 func_151AF938(f32 *, s32, s32, s32, u8);

void func_151AF8E8(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6)
{
  f32 new_var[2];
  f32 sp24;
  sp24 = arg0;
  new_var[0] = arg1;
  new_var[1] = arg2;
  func_151AF938(&sp24, arg3, arg4, arg5, (s32) (*((u8 *) (((u8 *) arg6) + 0xC))));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1DC470/func_151AF938.s")
