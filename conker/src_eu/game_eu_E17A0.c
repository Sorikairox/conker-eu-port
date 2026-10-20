#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1514CDC8(f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, f32, s32, s32);
void func_151D45A4(f32 *, u8, s32);
extern s32 D_800BEE08;
extern u8 D_8009FF90[];
void func_150B3AB0(struct127 *arg0, u8 arg1) {
    s16 angle;
    struct17 pos;
    structEU_151D8E18 blk;

    if (arg0 != NULL && arg0->unk1D4 != NULL) {
        func_1512D748(&D_800DBFF0[D_800BEE08], 6, 1);
        angle = (*(u16 *)((u8 *)arg0 + 0x7A) >> 8) + 0x40;
        func_15143134(D_8009FF90, &pos, (u8 *)arg0->unk1D4 + 0x640);
        func_1514CDC8(pos.unk0, pos.unk4, pos.unk8, 10.0f, angle, 0, 0xFF, (u32)func_150ADA20() % 31 + 0x28, 8, 0, 0.0f, 0, arg1);
        blk.unk0 = 1;
        blk.unk2 = (func_150ADA20() & 0xF) + 0xC;
        blk.unk4 = (func_150ADA20() & 3) + 5;
        blk.unk6 = -1;
        blk.unk5 = 1;
        func_151D8E18(&blk, 0, arg1, 0);
        func_151D45A4((f32 *)&pos, arg1, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_E17A0/func_150B40EC.s")
