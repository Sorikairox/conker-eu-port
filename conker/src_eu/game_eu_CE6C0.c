#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A09D0.s")

extern f32 D_8009F970;
extern f32 D_8009F974;
void func_150A11F4(u8 *arg0)
{
  f32 temp_f20;
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0xC))) * D_8009F970;
  *((f32 *) (((u8 *) arg0) + 0x24)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x28)) = func_150AD780(temp_f20);
  temp_f20 = (*((f32 *) (((u8 *) arg0) + 0x10))) * D_8009F974;
  *((f32 *) (((u8 *) arg0) + 0x2C)) = func_150AD78C(temp_f20);
  *((f32 *) (((u8 *) arg0) + 0x30)) = func_150AD780(temp_f20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A126C.s")

u8 *func_150A1520(u8 *arg0) {
    return arg0 + 0x400;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A152C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A16A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A28C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A29A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2AB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2C6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2D44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A29C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A2FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3264.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A332C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A33C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3538.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3794.s")

void func_150A3810(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *arg1 = (s32) (*(u8 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x17));
    *arg2 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x18));
    *arg3 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x1C));
    *arg4 = (*(s32 *)((u8 *)((D_800D34B8 + temp_v0)) + 0x20));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A3878.s")

void func_150A3924(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x34;
    *(s16 *)(D_800D34B8 + temp_v0) = arg1;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 2)) = arg2;
    (*(s16 *)((u8 *)((D_800D34B8 + temp_v0)) + 4)) = arg3;
}

s32 func_150A39E4();

s32 func_150A3990(u8 *arg0) {
    if (arg0[0x14] == 1) {
        return 0;
    }
    if (!(arg0[0x15] & 3)) {
        return func_150A39E4();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_CE6C0/func_150A39E4.s")
