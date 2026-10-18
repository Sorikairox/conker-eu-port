#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506A9B0.s")

void func_1506AABC(s32 arg0, s32 arg1) {
    func_150E08C8(arg0, 0xFF, 1);
}

void func_1506AAE4(s32 arg0, s32 arg1) {
    func_151BBBCC(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

void func_1506AB20(s32 arg0, s32 arg1) {
    func_151BC04C(arg0, D_800D1980, D_eu_800D1990, 0xFF, 1);
}

s32 func_151D3A30(f32 *, f32 *, s32, s32, s32, s32);

void func_1506AB5C(u8 *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)(arg0 + 0x14);
    sp2C[1] = *(f32 *)(arg0 + 0x18);
    sp2C[2] = *(f32 *)(arg0 + 0x1C);
    sp20[0] = ((f32 *)D_eu_800D1990)[0] - ((f32 *)D_800D1980)[0];
    sp20[1] = ((f32 *)D_eu_800D1990)[1] - ((f32 *)D_800D1980)[1];
    sp20[2] = ((f32 *)D_eu_800D1990)[2] - ((f32 *)D_800D1980)[2];
    func_151D3A30(sp2C, sp20, 0, 0, 0xFF, 1);
}

void func_1506ABFC(s32 arg0, s32 arg1) {
    func_151BC6B4(arg0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AC24.s")

s32 func_151D3A30(f32 *, f32 *, s32, s32, s32, s32);

void func_1506AD28(u8 *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)(arg0 + 0x14);
    sp2C[1] = *(f32 *)(arg0 + 0x18);
    sp2C[2] = *(f32 *)(arg0 + 0x1C);
    sp20[0] = ((f32 *)D_eu_800D1990)[0] - ((f32 *)D_800D1980)[0];
    sp20[1] = ((f32 *)D_eu_800D1990)[1] - ((f32 *)D_800D1980)[1];
    sp20[2] = ((f32 *)D_eu_800D1990)[2] - ((f32 *)D_800D1980)[2];
    func_151D3A30(sp2C, sp20, 0, 1, 0xFF, 1);
}

void func_1506ADC8(s32 arg0, s32 arg1) {
    func_151B76F4(arg0, 0xFF, 1);
    func_151B68D0(arg0, 0xFF, 1);
}

void func_1506AE08(u8 *arg0, u8 *arg1) {
    typedef struct { s32 w[2]; } Blk8;
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        u8 pad5[3];
        Blk8 unk8;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = *(Blk8 *)arg1;
    temp_v0 = func_15149130(0xA, 7, 0x23, -1, 1, 0x21, 0x10, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506AEA0.s")

void func_1506AF3C(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 1, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AF84(struct127 *arg0, u8 *arg1) {
    func_151043C0(arg0, *(struct127 **)arg1, (f32 *)(arg1 + 4), 2, *(s32 *)(arg1 + 0x10), 0xFF, 1);
}

void func_1506AFCC(u8 *arg0, s32 arg1) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151B78D8(&tmp, 0, 8, 0xFF, 1);
}

void func_1506B018(s32 arg0, s32 arg1) {
    func_151CF05C(arg0, 0, 1, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_981C0/func_1506B04C.s")
