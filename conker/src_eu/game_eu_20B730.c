#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151DDF20(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        D_800E1010[i] = D_800901F4[i];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DDF6C.s")

s32 func_151DE074(s32 arg0) {
    return ~arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEBB4.s")

void func_151DED3C(void);

void func_151DECB4(void) {
    D_800E0EC0 = 0;
    D_800E0FC7 = 0;
    D_800E0FC8 = 0;
    D_800E0EBC = 0;
    D_800901C8 = 2;
    func_151DED3C();
}

void func_151DECFC(void) {
    D_80090114 = 4;
    D_800E0FC6 = 0;
    if (D_800901D0 == 0) {
        func_1500764C();
    }
}

s32 func_1501C710(s32, s32, s32, s32, s32);
extern s8 D_80090144;
extern s8 D_800D3260;

void func_151DED3C(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090120 = 1;
    D_800901C8 = 2;
    D_80090144 = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 5;
    (*(s8 *)((u8 *)D_80090174 + 0x2C)) = (s8) (*(s8 *)((u8 *)D_80090174 + 0x2B));
}

void func_151DEDC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEDD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DF6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DFD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E06D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1EDC.s")

void func_151E5AB8(void);
void func_151E4B40(void);

void func_151E2A1C(void) {
    D_80090120 = 3;
    func_151E5AB8();
    func_151E4B40();
    D_80090120 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3864.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3A1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E49C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4A78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E533C.s")

void func_151E5528(void) {
    D_800E0B94 = 10;
}

void func_151E553C(void) {
    if (D_800E0FCA & 0x8020) {
        D_800E0B94 = 4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E55C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E564C.s")

void func_151E5798(void) {
    (*(f32 *)D_80090174) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 4)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 0;
    (*(s16 *)((u8 *)D_80090174 + 0x20)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3F)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x41)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x43)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x44)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2A)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x14)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x18)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 8)) = 0.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E582C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5AB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5B94.s")

void func_151E5D28(void) {
    D_800843F0[0] = 0;
    D_800843F0[1] = 1;
    D_800843F0[2] = 2;
    D_800843F0[3] = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5D54.s")

void func_151E5DD8(void) {
    if (D_800E0EBC != 0) {
        D_800E0EBC = 0;
    }
}

s8 func_151E5DF8(void) {
    return D_80090168;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5E08.s")

s32 func_151E6710(s32 arg0) {
    s8 var_v1;
    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E1030[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E6758(void) {
    if (D_800E101B != 0) {
        if (D_8008FD8C >= 5) {
            return D_80090130;
        }
        return D_8008FD8C;
    }
    return D_80090130;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E67A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E7110.s")

void func_151E73A8(void) {
    D_800E1003 = 0;
    D_800E1004 = 0;
    D_80090178 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E856C.s")

extern s8 D_800E1019;

void func_151E8648(void) {
    if (D_800E1019 == 2) {
        func_10017870(1U);
        return;
    }
    if (D_800E1019 == 0) {
        func_10017870(2U);
        return;
    }
    func_10017870(4U);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E86A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E870C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E89C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8A64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8B94.s")
