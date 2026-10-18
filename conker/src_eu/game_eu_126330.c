#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8B20.s")

void func_150F8DCC(s32 arg0, s32 arg1) {
    s32 tmp[2];
    tmp[0] = arg1;
    func_151494E0(tmp, 0x3F);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8DFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F8EAC.s")

extern u8 D_800A2010[][2];

void func_150F9CA0(u8 arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = D_800A2010[arg0][0];
    func_151494E0(&tmp, 0x42);
    tmp.unk4 = D_800A2010[arg0][1];
    func_151494E0(&tmp, 0x42);
}

void func_150F9D08(s32 arg0) {
}

void func_150F9D14(struct260 *arg0) {
    func_150F9D08(arg0);
    func_1514933C(arg0);
}

void func_150F9D40(struct260 *arg0) {
    func_150F9D08(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_126330/func_150F9D6C.s")

u8 *func_150FF808(u8 *);
s32 func_150FF9F4(s32 *, s32 *, u8, s32);
s32 func_150FFC60(s32 *, s32 *, s32 *, s32 *, s32 *, u8 *, u8 *);
s32 func_151D44C4(s32 *, u8, s32);
s32 func_151D49B8(s32 *, s32 *, s32, u8 *, f32, s32, s32);

void func_150F9ED0(u8 *arg0, u8 arg1, s32 arg2) {
    s32 pad[15]; // fakematch: frame is 0xA8, pad first keeps the vectors at 0x30-0x60
    s32 sp60[3];
    s32 sp54[3];
    s32 sp48[3];
    s32 sp3C[3];
    s32 sp30[3];
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = func_150FF808(arg0);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (func_150FFC60(sp60, sp54, sp48, sp3C, sp30, arg0, temp_v0) != 0) {
            func_151D44C4(sp54, arg1, arg2);
            func_151D49B8(sp48, sp3C, (*(u8 *)(sp2C + 2) << 6) + *(s32 *)(arg0 + 0x1D4), arg0, 1.0f, arg1, arg2);
            func_150FF9F4(sp54, sp60, arg1, arg2);
        }
    }
}
