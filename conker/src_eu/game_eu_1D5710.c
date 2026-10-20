#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A7F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8040.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A831C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A88F0.s")

void func_151A8B10(u8 *arg0) {
    func_151D5E30(arg0 + 0x6C, arg0);
}

void func_151A8B34(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCEC[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    func_151A8B10(arg0);
    func_15169804(arg0);
}

void func_151A8B84(u8 *arg0) {
    u8 *new_var; // fakematch: permuter temp
    void (*fn)(void *) = D_8008FCF8[arg0[0x5C]];
    new_var = arg0;
    if (fn != NULL) {
        if (!arg0) { // fakematch: permuter empty branch
        }
        fn(new_var);
    }
    func_151A8B10(arg0);
    func_15169824(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8BD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8DA8.s")

void func_151A8FD0(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx = arg0[0x5C];
    void (*fn)(u8 *, s32, u8);

    if (idx >= 3) {
        idx = 0;
    }
    fn = (void (*)(u8 *, s32, u8))D_8008FD04[idx];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

void func_151A9028(struct102 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a0;
    s32 new_var; // fakematch: key temp pins the v1 register
    s32 temp_t6 = arg2;
    u8 *temp_v0 = *(u8 **)((u8 *)arg0 + 0x60);

    if (arg2 == 0) {
        new_var = *(s32 *)(arg1 + 0);
        if ((new_var == *(s32 *)(temp_v0 + 0)) || (*(u8 *)(arg1 + 4) == *(u8 *)(temp_v0 + 4))) {
            func_1516972C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)(arg1 + 0);
        if (temp_a0 == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)(temp_v0 + 0)) {
            *(s32 *)(temp_v0 + 0) = temp_a0;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A8B20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A929C.s")

s32 func_151432BC(s32, u8 *, u8 *, f32 *, s32);
void func_151A94CC(u8 *arg0, u8 *arg1, f32 *arg2, s32 arg3) {
    func_151432BC(*(s32 *)(arg0 + 0x2C), arg1, arg1 + 8, arg2, arg3);
    *(f32 *)(arg1 + 4) = *arg2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A951C.s")

void func_151A98CC(u8 *, s32, u8);
void func_151A95D4(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg0[0x4C] == 1) {
        func_151A98CC(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9610.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A975C.s")

void func_151A98CC(u8 *arg0, s32 arg1, u8 arg2)
{
  if (arg2 == 0x17) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p |= 1;
    }
  } else if (arg2 == 0x18) {
    u8 *p = arg0 + 0x28;
    if (((u8 *)arg1)[0] == arg0[0x80]) {
      *p &= ~1;
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9BE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D5710/func_151A9DE4.s")
