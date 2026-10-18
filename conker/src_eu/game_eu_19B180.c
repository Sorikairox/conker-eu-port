#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516D970.s")

s32 func_15044BC0(s32, s32, s32, s32, s32, s32, s32, u8 *, u8 *);

void func_1516DA58(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, s16 arg17, s16 arg18, u8 arg19, s16 arg1A, s32 arg1B, s32 arg1C, u8 arg1D, s32 arg1E) {
    u8 *temp_v0;
    s32 var_a0;
    u8 *sp34;

    if (arg1B != 0) {
        var_a0 = 0x67;
    } else {
        var_a0 = 0x12;
    }
    temp_v0 = func_15167A68(var_a0, arg1E, 0x34, 0, (u8) (s32) arg1D, 1U);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)temp_v0 + 0xE)) = arg0;
        (*(s16 *)((u8 *)temp_v0 + 0x10)) = arg1;
        (*(s16 *)((u8 *)temp_v0 + 0x12)) = arg2;
        (*(u8 *)((u8 *)temp_v0 + 0x1A)) = arg3;
        (*(u8 *)((u8 *)temp_v0 + 0x1B)) = arg4;
        (*(u8 *)((u8 *)temp_v0 + 0x1C)) = arg5;
        (*(u8 *)((u8 *)temp_v0 + 0x1D)) = arg6;
        (*(u8 *)((u8 *)temp_v0 + 0x1E)) = arg7;
        (*(u8 *)((u8 *)temp_v0 + 0x1F)) = arg8;
        (*(u8 *)((u8 *)temp_v0 + 0x20)) = arg9;
        (*(u8 *)((u8 *)temp_v0 + 0x21)) = argA;
        (*(u8 *)((u8 *)temp_v0 + 0x22)) = argB;
        (*(u8 *)((u8 *)temp_v0 + 0x23)) = argC;
        (*(s16 *)((u8 *)temp_v0 + 0x14)) = arg17;
        (*(s16 *)((u8 *)temp_v0 + 0x16)) = arg18;
        (*(u8 *)((u8 *)temp_v0 + 0x24)) = arg19;
        (*(s16 *)((u8 *)temp_v0 + 0x18)) = arg1A;
        (*(s8 *)((u8 *)temp_v0 + 0x25)) = 0;
        (*(u8 *)((u8 *)temp_v0 + 0x26)) = argD;
        (*(u8 *)((u8 *)temp_v0 + 0x27)) = argE;
        (*(u8 *)((u8 *)temp_v0 + 0x28)) = argF;
        (*(u8 *)((u8 *)temp_v0 + 0x29)) = arg10;
        (*(u8 *)((u8 *)temp_v0 + 0x2A)) = arg11;
        (*(u8 *)((u8 *)temp_v0 + 0x2B)) = arg12;
        (*(u8 *)((u8 *)temp_v0 + 0x2C)) = arg13;
        (*(u8 *)((u8 *)temp_v0 + 0x2D)) = arg14;
        (*(u8 *)((u8 *)temp_v0 + 0x2E)) = arg15;
        (*(u8 *)((u8 *)temp_v0 + 0x2F)) = arg16;
        if (arg1C != 0) {
            sp34 = temp_v0;
            (*(s32 *)((u8 *)temp_v0 + 0x30)) = func_15044BC0(-1, 0, arg1C, 0x14, 0x14, 0x14, 0, temp_v0 + 0xE, temp_v0 + 0x14);
            return;
        }
        (*(s32 *)((u8 *)temp_v0 + 0x30)) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516DBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516DCA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516DF0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516E100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516ECE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EE3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F21C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F2D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EED4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F594.s")

s32 func_1516DF0C(s32, s32, s32, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s16, s16, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_1516F730(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    func_1516DF0C(2, 0, 0, 0x2D, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1, 0xA, 0xA, arg0, 0x3C, 0, 0, 0x81, 4, 0, 1, 0, 0, 0, 4, 2, (s32) arg2, arg3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F868.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FAB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FDD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FE5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FE8C.s")

s32 func_1516FE5C(s32, s32);
s32 func_1516FE8C(s32, s32);

void func_1516FEBC(s32 arg0, s32 arg1) {
    func_1516FE5C(arg0, arg1);
    func_1516FE8C(arg0, arg1);
}

void func_1516FEF4(s32 arg0, s32 arg1) {
    s32 v;
    func_1516FEBC(arg0, arg1);
    v = *(s16 *)((u8 *)arg0 + 0x18);
    v = v * arg1;
    *(s16 *)((u8 *)arg0 + 0x18) = v >> 8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FF34.s")

void func_1516FFF8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516DF0C((s32) arg0, (s32) arg1, (s32) arg2, 0x1B, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x400, 0x400, 0, 0, 2, 0, 0, 0xFF, 0xF, 0, 0, 9, 0, 0xFF, 0xA, 0x5A, 5, arg3, 0, 0, (s32) arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1517013C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_151702C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FE1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_151705A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170D50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170F24.s")
