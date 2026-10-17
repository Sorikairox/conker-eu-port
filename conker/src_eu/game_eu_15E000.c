#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ f32 unk58[2];
    /* 0x60 */ u8 pad60[0x48];
    /* 0xA8 */ f32 unkA8;
} struct_eu_15E000;

void func_15131E58(f32 *arg0, f32 arg1);
void func_15131E88(f32 *arg0, f32 arg1);
void func_15131EC8(f32 *arg0, f32 arg1);


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151307F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151308E4.s")

void func_151308E4(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1513092C(s32 arg0, u8 arg1, s32 arg2) {
    func_151308E4(arg0, arg1, arg2, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_1513095C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_1513100C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151318EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15131A84.s")

s32 func_151318EC(s32, s32, s32, s32, s32);
s32 func_15131A84(s32, s32, s32, s32, s32);

void func_15131BBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_15131A84(arg4, arg5, arg6, arg7, arg8);
    func_151318EC(arg0, arg1, arg2, arg3, arg8);
}

s32 func_15131C1C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E58(arg0->unk58, arg0->unkA8);
    return 1;
}

s32 func_15131C4C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E88(arg0->unk58, arg0->unkA8);
    return 1;
}

s32 func_15131C7C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131EC8(arg0->unk58, arg0->unkA8);
    return 1;
}

void func_15131CAC(struct102 *arg0) {
    func_15169804(arg0);
}

void func_15131CCC(struct102 *arg0) {
    func_15169824(arg0);
}

void func_15131CEC(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    D_80089BB4[idx](arg0);
}

void func_15131D38(u8 *arg0) {
    s32 idx = (*(s32 *)(arg0 + 0x68) & 0x4000) ? arg0[0x75] : 0;
    D_80089BE4[idx](arg0);
}

s32 func_15131D84(s32 arg0, s32 arg1) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15131D98.s")

void func_15131E58(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[1] *= arg1;
    }
}

void func_15131E88(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[2] *= arg1;
    }
}

void func_15131EC8(f32 *arg0, f32 arg1) {
    s32 i = D_800BE9E4;

    while (i > 0) {
        i--;
        arg0[0] *= arg1;
        arg0[1] *= arg1;
        arg0[2] *= arg1;
    }
}

void func_15131F14(s32 arg0, s32 arg1) {
    func_15131F34(arg0, arg1, arg0 + 0xA8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15131F34.s")

void func_1513206C(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131EC8(arg0->unk58, arg0->unkA8);
    func_15131F34(arg0, arg1, (u8 *)arg0 + 0xB0);
}

void func_151320AC(struct_eu_15E000 *arg0, s32 arg1) {
    func_15131E88(arg0->unk58, arg0->unkA8);
    func_15131F34(arg0, arg1, (u8 *)arg0 + 0xB0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151320EC.s")

extern void (*D_80089C18[])(u8 *, u8 *, u8);
void func_1513219C(u8 *arg0, u8 *arg1, u8 arg2) {
    void (*f)(u8 *, u8 *, u8);
    if (*(s32 *)(arg0 + 0x68) & 0x4000) {
        f = D_80089C18[arg0[0x75]];
        if (f != NULL) {
            f(arg0, arg1, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151321F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_151322BC.s")

s32 func_1513230C(u8 *arg0, s32 arg1) {
    func_151321F4(arg0 + 0xA8, arg0 + 0xAA, *(s32 *)(arg0 + 0xAC), arg0 + 0xB0, arg0 + 0x38, arg0 + 0x3C);
    return 1;
}

s32 func_1513235C(u8 *arg0, s32 arg1) {
    f32 temp_f12;
    f32 temp_f2;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0xA8));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0xB0)) * sqrtf(temp_f2);
    (*(f32 *)((u8 *)arg0 + 0x3C)) = temp_f12;
    (*(f32 *)((u8 *)arg0 + 0x38)) = temp_f12;
    (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) ((*(f32 *)((u8 *)arg0 + 0xB4)) - ((*(f32 *)((u8 *)arg0 + 0xB8)) * temp_f2 * temp_f2));
    (*(f32 *)((u8 *)arg0 + 0xA8)) = (f32) (temp_f2 + D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0xAC)) < (*(f32 *)((u8 *)arg0 + 0xA8))) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15E000/func_15132454.s")
