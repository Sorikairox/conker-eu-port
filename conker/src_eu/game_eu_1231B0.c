#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F59A0.s")

void func_150F5B10(u8 *arg0) {
    s32 temp_v0 = 0x1000 - *(s16 *)(arg0 + 0x24) * 4;

    *(s16 *)(arg0 + 0x38) = temp_v0;
    *(s16 *)(arg0 + 0x3A) = *(s16 *)(arg0 + 0x38);
    func_150F5B48(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5B48.s")

void func_150F5C0C(s32 arg0) {
    func_15179008(0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5C30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F5FD4.s")

void func_150F6188(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        u8 *unk0;
        u8 unk4;
        f32 unk8;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = 0.0f;
    temp_v0 = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, 0xC, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6218.s")

void func_150F66B8(u8 *arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F66F8.s")

void func_150F689C(u8 *arg0) {
    struct102 *temp_a0;

    if (*(s32 *)(arg0 + 0x30) != 0) {
        func_1516972C(*(struct102 **)(arg0 + 0x30));
    }
    temp_a0 = *(struct102 **)(arg0 + 0x34);
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
}

void func_150F68E8(void *arg0) {
    func_150F689C(arg0);
    func_1514933C(arg0);
}

void func_150F6914(void *arg0) {
    func_150F689C(arg0);
    func_15149368(arg0);
}

void func_150F6940(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

void func_150F6980(u8 *arg0)
{
  int new_var;
  s32 *new_var3;
  int new_var2;
  new_var3 = &(*((s32 *) (((u8 *) arg0) + 0x160)));
  if ((*((s32 *) (((u8 *) arg0) + 0x160))) != 0)
  {
    new_var = 0x28;
    *((s32 *) (((u8 *) (new_var2 = (*new_var3) + new_var)) + 8)) = 0;
  }
}

void func_150F69A0(void *arg0) {
    func_150F6980(arg0);
    func_1513CA6C(arg0);
}

void func_150F69CC(void *arg0) {
    func_150F6980(arg0);
    func_1513CAA0(arg0);
}

void func_150F69F8(s32 arg0) {
}

void func_150F6A04(void *arg0) {
    func_150F69F8(arg0);
    func_151411A4(arg0);
}

void func_150F6A30(void *arg0) {
    func_150F69F8(arg0);
    func_151411C4(arg0);
}

s32 func_1510819C(u8 *, s32, f32 *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, u8, u8);
extern f32 D_800A1F00[];

typedef struct {
    u8 *o;
    u8 id;
    u8 pad5;
    s16 t6;
} Sub6A5C;

void func_150F6A5C(u8 *arg0) {
    Sub6A5C *s;
    u8 *obj;
    s8 n;
    f32 pos[3];
    Header header;
    Header2 header2;
    u8 col[4];

    s = (Sub6A5C *)(arg0 + 0x28);
    obj = s->o;
    if ((*(s32 *)obj == 0) || (s->id != obj[0x3B])) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if ((*(s32 *)(obj + 0x1D4) != 0) && !(*(s32 *)(obj + 0x94) & 2)) {
        s->t6 -= D_800BE9E4;
        if (s->t6 < 0) {
            func_10010F88(0x679, 0x18CE, 0, 0, 0, *(f32 *)(obj + 0x14), *(f32 *)(obj + 0x18), *(f32 *)(obj + 0x1C), 0x7918, 0x7D00);
            n = (func_150ADA20() & 1) + 2;
            goto lbl; // fakematch: scheduling barrier (permuter)
            lbl:
            func_15143134(D_800A1F00, pos, *(u8 **)(obj + 0x1D4));
            header.unk0 = 3;
            header.unk1 = -1;
            header.unk2 = (func_150ADA20() % 9U) + 0xA;
            header.unk4 = 0;
            header2.unk0 = pos[0];
            header2.unk4 = pos[1];
            header2.unk8 = pos[2];
            func_151602C0(&header, &header2, (func_150ADA20() % 61U) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
            do {
                col[0] = 0xA0;
                col[1] = 0xA0;
                col[2] = 0xFF;
                col[3] = (func_150ADA20() % 101U) + 0x9B;
                func_1510819C(obj, 0, D_800A1F00, func_150ADA20() & 0xFF, (func_150ADA20() % 43U) - 0x32, (func_150ADA20() % 18U) + 5, 4, 27.0f, (func_150ADA68() * 16.0f) + 20.0f, 0, 2, col, arg0[0xC], arg0[1]);
                n--;
            } while (n > 0);
            s->t6 = (func_150ADA20() % 91U) + 0x5A;
        }
    }
}

void func_150F6DD0(u8 *arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, (s32)(arg0 + 0x28), (s32)(arg0 + 0x2C), (s32)arg0);
}

extern f32 D_800A1F40;
s32 func_15134DAC(void *, s32, u8 *, s16);

void func_150F6E10(u8 *arg0, s16 arg1, f32 arg2, u8 arg3) {
    struct {
        u8 u2C;
        u8 *u30;
        u8 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        u8 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        u8 u5A;
        u8 u5B;
        s8 u5C;
        f32 u60;
        u8 u64;
        s8 u65;
    } sp;

    sp.u2C = arg0[0x3B];
    sp.u30 = arg0;
    sp.u34 = 3;
    sp.u38 = 0.0f;
    sp.u3C = 0.0f;
    sp.u40 = 0.0f;
    sp.u44 = 0.0f;
    sp.u50 = 2;
    sp.u52 = 0x28;
    sp.u54 = 0x10;
    sp.u56 = arg1;
    sp.u5A = 5;
    sp.u5B = 8;
    sp.u5C = -1;
    sp.u64 = 0;
    sp.u65 = -1;
    sp.u58 = 0;
    sp.u48 = D_800A1F40;
    sp.u4C = 8.5f;
    sp.u60 = 1.0f;
    func_15134DAC(&sp, 0, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1231B0/func_150F6EDC.s")
