#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15115244();


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110420.s")

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[4][4];
    func_150A8050(arg0, 0.0f, arg2, 0.0f);
    func_150A8050(sp28, arg1, 0.0f, 0.0f);
    func_150A7A48(arg0, sp28, arg0);
    func_150A8050(sp28, 0.0f, 0.0f, arg3);
    func_150A7A48(arg0, sp28, arg0);
}

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*)[4], f32, f32, f32);
void func_151108E0(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4) {
    func_1511084C(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, (f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110948.s")

Gfx *func_15110AC4(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b) {
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x302C0F, 4);
    gdl = func_1501A680(gdl);
    gDPSetFillColor(gdl++, (GPACK_RGBA5551(r, g, b, 1) << 16) | GPACK_RGBA5551(r, g, b, 1));
    return func_1501A6CC(gdl, arg1, arg2, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110C28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_1511127C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111CAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113000.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113700.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113798.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113B44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113D54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114208.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151143D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151145D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114644.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114708.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151148C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114CBC.s")

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_15114E28(f32 (*arg0)[4], u8 *arg1) {
    f32 sp18[4][4];
    func_150A8050(arg0, 0.0f, *(f32 *)(arg1 + 4), 0.0f);
    func_150A8050(sp18, *(f32 *)arg1, 0.0f, *(f32 *)(arg1 + 8));
    func_150A7A48(sp18, arg0, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114E8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151149AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114F9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15115114.s")

s32 func_15115244(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && ((*arg2 != 0) || ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 1;
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x10));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x12));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14));
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151152A4.s")

void func_15115484(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15115244, arg0, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151154C4.s")
