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

void func_1516DF0C(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30) {
    s32 var_a0;
    u8 *temp_v0;

    if (arg2C != 0) {
        var_a0 = 0x66;
    } else {
        var_a0 = 0x11;
    }
    temp_v0 = func_15167A68(var_a0, arg30, 0x4C, 0, arg2F, 1);
    if (temp_v0 != NULL) {
        *(s16 *)(temp_v0 + 0xE) = arg0;
        *(s16 *)(temp_v0 + 0x10) = arg1;
        *(s16 *)(temp_v0 + 0x12) = arg2;
        *(s16 *)(temp_v0 + 0x14) = arg1B;
        *(s16 *)(temp_v0 + 0x16) = arg1C;
        *(s16 *)(temp_v0 + 0x18) = arg1D;
        *(s16 *)(temp_v0 + 0x1A) = arg1E;
        *(u8 *)(temp_v0 + 0x24) = arg3;
        *(u8 *)(temp_v0 + 0x25) = arg4;
        *(u8 *)(temp_v0 + 0x26) = arg5;
        *(u8 *)(temp_v0 + 0x27) = arg6;
        *(u8 *)(temp_v0 + 0x28) = arg7;
        *(u8 *)(temp_v0 + 0x2A) = arg9;
        *(u8 *)(temp_v0 + 0x2B) = argA;
        *(u8 *)(temp_v0 + 0x2C) = argB;
        *(u8 *)(temp_v0 + 0x29) = arg8;
        *(u8 *)(temp_v0 + 0x2D) = argC;
        *(u8 *)(temp_v0 + 0x2E) = argD;
        *(u8 *)(temp_v0 + 0x2F) = argE;
        *(u8 *)(temp_v0 + 0x30) = argF;
        *(u8 *)(temp_v0 + 0x31) = arg10;
        *(u8 *)(temp_v0 + 0x32) = arg11;
        *(u8 *)(temp_v0 + 0x33) = arg12;
        *(u8 *)(temp_v0 + 0x34) = arg13;
        *(u8 *)(temp_v0 + 0x35) = arg14;
        *(u8 *)(temp_v0 + 0x36) = arg15;
        *(u8 *)(temp_v0 + 0x37) = arg16;
        *(u8 *)(temp_v0 + 0x38) = arg17;
        *(u8 *)(temp_v0 + 0x39) = arg18;
        *(u8 *)(temp_v0 + 0x3A) = arg19;
        *(u8 *)(temp_v0 + 0x3B) = arg1A;
        *(u16 *)(temp_v0 + 0x20) = arg1F;
        *(s8 *)(temp_v0 + 0x3C) = arg1F;
        *(u8 *)(temp_v0 + 0x3D) = arg20;
        *(u8 *)(temp_v0 + 0x3E) = arg21;
        *(u8 *)(temp_v0 + 0x3F) = arg22;
        *(u8 *)(temp_v0 + 0x40) = arg23;
        *(s16 *)(temp_v0 + 0x1C) = arg24;
        *(u16 *)(temp_v0 + 0x1E) = arg25;
        *(u16 *)(temp_v0 + 0x22) = arg26;
        *(u8 *)(temp_v0 + 0x41) = arg27;
        *(s8 *)(temp_v0 + 0x42) = 0;
        *(u8 *)(temp_v0 + 0x43) = arg28;
        if ((arg2C != 0) && (arg29 >= 4)) {
            arg29 = 3;
        }
        *(u8 *)(temp_v0 + 0x44) = arg29;
        *(u8 *)(temp_v0 + 0x45) = arg2A;
        *(u8 *)(temp_v0 + 0x46) = arg2B;
        *(u8 *)(temp_v0 + 0x47) = arg2D;
        *(u8 *)(temp_v0 + 0x48) = arg2E;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516E100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516ECE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EE3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F21C.s")

void func_1516F2D8(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 t;

    t = D_800CC2D4[arg0 * 0x32C];
    if (t == 0x3A) {
        func_1516DF0C(5, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0x124, 0x124, 0, 0, arg1, 0, 0, arg0, 0xC, 0, 0, 0x81, 2, 0, 1, 0, 0, 0, 5, 0, arg2, arg3);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516EED4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516F594.s")

void func_1516DF0C(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, s16 arg1E, u16 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, s16 arg24, u16 arg25, u16 arg26, u8 arg27, u8 arg28, u8 arg29, u8 arg2A, u8 arg2B, s32 arg2C, u8 arg2D, u8 arg2E, u8 arg2F, s32 arg30);

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
    func_1516DF0C(arg0, arg1, arg2, 0x1B, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x400, 0x400, 0, 0, 2, 0, 0, 0xFF, 0xF, 0, 0, 9, 0, 0xFF, 0xA, 0x5A, 5, arg3, 0, 0, (s32) arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1517013C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_151702C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_1516FE1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_151705A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_19B180/func_15170D50.s")

s32 func_151705A4(s32, f32 *, f32 *, f32 *);
void func_15170F24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    s32 q0; // fakematch: unused locals pad the frame to 0xF8
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 a;
    s32 b;
    s32 p0, p1; // fakematch: unused locals pad the frame

    for (i = 0; i < arg3; i++) {
        func_151705A4(0x40, &x, &y, &z);
        x *= arg4;
        y *= 2.0f * arg4;
        z *= arg4;
        a = x;
        b = z;
        func_1516DA58(arg0, arg1, arg2, 0x2F, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 7, a >> 8, a & 0xFF, b >> 8, b & 0xFF, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0x28, y, 0, 0, arg5, arg6);
    }
}
