#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_151D6F20(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 == 50) || (D_800BE9F0 == 51)) {
        func_150D6C40(arg0, 0xFF, 1);
    }
}


typedef struct {
    s16 u0[4];
    struct17 pos;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S06E8;

s32 func_151506E8(S06E8 *, struct17 *, f32 *, u8, s32);
void func_1504715C(f32 *, struct127 *);

void func_151D6F64(s16 *arg0, struct127 *arg1) {
    f32 v[9];
    struct_eu_15154488 s;

    func_1504715C(v, arg1);
    s.unk8.unk0 = arg0[8];
    s.unk8.unk4 = arg0[9];
    s.unk8.unk8 = arg0[10];
    s.unk14 = 2.49f;
    s.unk18 = 2.03f;
    s.unk1C = 0.60800004f;
    s.unk20 = 0.257f;
    s.unk24 = 17.0f;
    s.unk28 = 3.5f;
    s.unk2C = 3;
    s.unk2E = 3;
    s.unk2 = 0xFF;
    s.unk4 = -0x2B;
    s.unk6 = 0x20;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 2;
    s.unk34 = 0x28;
    s.unk36 = 0x14;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 0.4f;
    s.unk48 = 0;
    s.unk3C = 9;
    func_15154488(&s, &s.unk8, (s32)v, 0xFF, 1);
    {
    S06E8 t;
    t.pos.unk0 = arg0[8];
    t.pos.unk4 = arg0[9];
    t.pos.unk8 = arg0[10];
    t.u14 = 0xF;
    t.u18 = 10.0f;
    t.u1C = 6.0f;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u24 = -1.506f;
    t.u0[3] = 0xC;
    t.u20 = 0x3C;
    t.u22 = 0x2D;
    t.u28 = 0.814f;
    t.u2C = 0xC8;
    t.u2D = 0x37;
    t.u38 = 1;
    t.u30 = 44.0f;
    t.u39 = 9;
    t.u34 = 88.0f;
    t.u3C = 1.0f;
    t.u40 = 0;
    t.u44 = 1.0f;
    func_151506E8(&t, &t.pos, v, 0xFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D71AC.s")

f32 func_15144AA8(s32);
#define MTX_7410(a) (((f32 (*)[16])((a) + 0x7C))[D_800BE9C0])
s32 func_151D7410(u8 *arg0) {
    func_150A8050(&MTX_7410(arg0), 0.0f, func_15144AA8(0) + 25.0f, 0.0f);
    MTX_7410(arg0)[12] = (*(f32 **)(arg0 + 0x4C))[5];
    MTX_7410(arg0)[13] = (*(f32 **)(arg0 + 0x4C))[6] + 120.0f;
    MTX_7410(arg0)[14] = (*(f32 **)(arg0 + 0x4C))[7];
    MTX_7410(arg0)[0] *= 0.551f;
    MTX_7410(arg0)[1] *= 0.551f;
    MTX_7410(arg0)[2] *= 0.551f;
    MTX_7410(arg0)[4] *= 0.551f;
    MTX_7410(arg0)[5] *= 0.551f;
    MTX_7410(arg0)[6] *= 0.551f;
    MTX_7410(arg0)[8] *= 0.551f;
    MTX_7410(arg0)[9] *= 0.551f;
    MTX_7410(arg0)[10] *= 0.551f;
    return 1;
}
#undef MTX_7410

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204730/func_151D75B0.s")

void func_151D767C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp = *(u8 **)(arg0 + 0x48);
    func_15169850(arg1, arg2, temp, temp + 4, arg0);
}

extern s32 D_80083AD0;
extern s32 D_80083C50;
u8 *func_1513445C(u8 *, s32, s32, s32);
Gfx *func_151D76BC(Gfx *gdl, u8 *arg1, s32 arg2, s32 arg3, s8 *arg4) {
    if (arg1[0x43] < 0xFF) {
        gSPSegment(gdl++, 8, &D_80083AD0);
    } else {
        gSPSegment(gdl++, 8, &D_80083C50);
    }
    gdl = (Gfx *)func_1513445C((u8 *)gdl, 0xC3, 6, 3);
    gdl = (Gfx *)func_1513445C((u8 *)gdl, 0xC3, 7, 3);
    *arg4 = 1;
    return gdl;
}
