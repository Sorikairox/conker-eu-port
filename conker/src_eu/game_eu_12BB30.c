#include <ultra64.h>
#include "functions.h"
#include "variables.h"
s32 func_150FDF38(struct127 *, u8, s32, s32 *, s32 *);
s32 func_151C284C(s32 *, s32, s32 *, s32 *, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_150FDDA0(s32 arg0, u8 arg1, s32 arg2) {
    s32 pad; // fakematch: unused local moves the unnamed f32 spill temps down (frame layout)
    s32 spB0[3];
    s32 spA4[3];
    s32 sp98[3];
    s32 sp8C[3];

    if (arg0 == 0) {
        return 0;
    }
    func_15145740(arg0, (s32) sp98, (s32) spB0, 0, 0.0f);
    func_150FDF38(arg0, arg1, arg2, spA4, sp8C);
    return func_151C284C(sp8C, 0, sp8C, sp98, 0, 0, 300.0f, 0.0033333334f, (func_150ADA68() * 10.0f) + 25.0f, (func_150ADA68() * 201.0f) + 601.0f, 50.0f, (func_150ADA20() % 56U) + 0xC8, arg0, 1, 1, 0, 0xFF, 1, 1, 0, (D_800BE9F0 == 0x2B) ? 0x27 : 0x1A, 0.0f, 0xFF, -1, 0, (s32) arg1, arg2);
}

const u32 rodata_12BB30_FDF38[] = { 0x40E00000, 0xC3080000, 0x42340000, 0x40E00000, 0xC3290000, 0x424C0000, 0x40E00000, 0x42200000, 0x41500000 }; // D_800A2340 = [0], D_800A234C = [3], D_800A2358 = [6]
void func_150FE638(struct127 *, s32, u8, s32);
s32 func_15145EA4(u8 **, struct17 **, s32, s32);
void func_151D441C(struct127 *, struct17 *, struct17 *, s32);
void func_151D44C4(struct17 *, u8, s32);
void func_150FE808(u8 *);
extern u8 D_80088F20;

s32 func_150FDF38(struct127 *arg0, u8 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    struct17 pos;
    struct17 pos2;
    u8 *tbl[2];
    struct17 *out[2];

    if (arg0 != NULL) {
        if (arg0->unk1D4 != 0) {
            tbl[0] = D_800A2340;
            tbl[1] = D_800A2340 + 0x18;
            out[0] = &pos;
            out[1] = &pos2;
            func_15145EA4(tbl, out, (s32) arg0->unk1D4 + (D_80088F20 << 6), 2);
        } else {
            pos.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
            pos.unk4 = *(f32 *)((u8 *)arg0 + 0x18) + 56.0f;
            pos.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);
            pos2 = pos;
        }
        func_151D441C(arg0, &pos, &pos2, (D_800BE9F0 == 0x2B) ? 0x28 : 0x1E);
        func_151D44C4(&pos, arg1, arg2);
        func_150FE638(arg0, (s32) &pos, arg1, arg2);
        func_150FE808((u8 *) arg0);
        if (arg3 != NULL) {
            *(struct17 *)arg3 = pos;
        }
        if (arg4 != NULL) {
            *(struct17 *)arg4 = pos2;
        }
    }
}

s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, s32, s32, s32, s32, s32, s32);
extern s32 D_800A234C;

void func_150FE638(struct127 *arg0, s32 arg1, u8 arg2, s32 arg3)
{
  f32 sp60[2];
  u8 sp5F;
  if ((arg0->unk1D4 != 0) && ((arg0->unk74 & 0xF) != 0xF))
  {
    sp60[1] = (func_150ADA68() * 1.5f) + 2.0f;
    sp60[0] = (func_150ADA68() * 10.1f) + 2.06f;
    if (((arg0->unk31C != 0) && (arg0->unk31C->unk197 != 0)) && (arg0->camera != 0))
    {
      sp5F = (~(1 << arg0->camera->unk23D)) & 0xFFFFu;
    }
    else
    {
      sp5F = 0xFF;
    }

    func_151030B8(arg0, D_80088F20, D_800A2340, &D_800A234C, sp60, (func_150ADA20() % 5U) + 6, (((u32) func_150ADA20()) % 101U) + 0x9B, (func_150ADA68() * 199.0f) + 501.0f, arg1, (s32) sp5F, 0, -1, (s32) arg2, arg3);
  }
}

void func_150FE7C8(s32 arg0, s32 arg1, s32 arg2) {
    func_151D43B4(arg0, arg2, &D_800A2340, D_80088F20, 0.0f);
}

void func_150FE808(u8 *arg0) {
    s8 sp18[8];
    if (*(s32 *)(arg0 + 0x318) != 0) {
        sp18[0] = 1;
        *(s16 *)(sp18 + 2) = ((u32)func_150ADA20() % 9) + 0xF;
        sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D];
        sp18[4] = (func_150ADA20() & 3) + 3;
        sp18[6] = -1;
        func_151D8E18(sp18, 0, 0xFF, 1);
    }
}
