#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_15045AF0(u8 *arg0, u16 arg1, f32 arg2, u8 *arg3);
void func_151AC3F0(struct17 *, s32 *, s32, u8, s32);
void func_10010FFC(s32, s32, s32, s32, s32, u8 *);
void func_151AC3B0(u8 *);
void func_151AA814(u8 *, u8 *);
extern f32 D_800A9354;
void func_151A9F80(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9354 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
    }
}

extern f32 D_800A9358;
void func_151AA054(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9358 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
        func_10010FFC(0, 17, 21000, 0, 0, obj);
    }
    func_151AC3B0(obj);
}

extern f32 D_800A935C;
void func_151AA150(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A935C < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 1, arg0[0xC], arg0[1]);
        func_10010FFC(0, 17, 21000, 0, 0, obj);
    }
}

extern f32 D_800A9360;
void func_151AA250(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if (*(u8 **)(obj + 0x31C) != NULL && (*(u8 **)(obj + 0x31C))[0x95] != 0) {
        return;
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9360 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 1, arg0[0xC], arg0[1]);
        func_10010FFC(0, 8, 27000, 0, 0, obj);
    }
    func_151AA814(obj, arg0 + 0x34);
    func_151AC3B0(obj);
}

extern f32 D_800A9364;
void func_151AA370(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9364 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 2, arg0[0xC], arg0[1]);
        func_10010FFC(0, 17, 21000, 0, 0, obj);
    }
}

extern f32 D_800A9368;
void func_151AA470(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9368 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 2, arg0[0xC], arg0[1]);
        func_10010FFC(0, 8, 27000, 0, 0, obj);
    }
    func_151AA814(obj, arg0 + 0x34);
    func_151AC3B0(obj);
}

extern f32 D_800A936C;
void func_151AA578(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A936C < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 4, arg0[0xC], arg0[1]);
    }
}

extern f32 D_800A9370;
void func_151AA64C(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A9370 < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    if (func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34)) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 4, arg0[0xC], arg0[1]);
    }
}

void func_151AA720(s32 arg0) {
}

void func_151AA72C(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    func_151482D4((s32)&sp1C, 0xA);
    func_151494E0((s32)&sp1C, 0xA);
    func_1519F928(arg0);
}

void func_151AA780(void) {
    func_1519F970();
}

void func_151AA7A0(void) {
    func_1519F970();
}

void func_151AA7C0(u8 *arg0) {
    s32 temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
    } sp1C;

    temp_v0 = *(s32 *)(arg0 + 0x18);
    sp1C.unk0 = temp_v0;
    sp1C.unk4 = arg0[0x1C];
    func_151482D4((s32)&sp1C, 0xA);
    func_151494E0((s32)&sp1C, 0xA);
    func_1519F928(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AA814.s")

extern f32 D_800A9378;
extern f32 D_800A937C;
extern f32 D_800A9380;
void func_1515A7A8(f32 *, f32 *, f32, s32, s32, f32, s32, s32, s32, s32, s32);
s32 func_1515AE90(u8 *, s32 *);
void func_151AA8BC(f32 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, s32 arg5, u8 *arg6) {
    f32 pos[3];
    f32 vel[3];
    u8 *obj;
    s32 sp48;

    obj = *(u8 **)(arg6 + 0x1C);
    if (!(*(f32 *)(obj + 0x118) < arg1)) {
        if (func_1515AE90(obj, &sp48) == 0) {
            sp48 = 0;
        }
        vel[0] = 0.0f;
        vel[1] = -((func_150ADA68() * 196.0f + 199.0f) * D_800A9378 * arg4);
        vel[2] = 0.0f;
        pos[0] = arg0;
        pos[1] = arg1;
        pos[2] = arg2;
        func_1515A7A8(pos, vel, (func_150ADA68() * D_800A937C + 454.0f) * D_800A9380, 0x3F7901C1, sp48,
            func_150ADA68() * 101.0f + 101.0f, func_150ADA20() % 31U + 0x32, func_150ADA20() % 101U + 0x64, 1, arg6[0xC], arg6[1]);
    }
}

typedef struct {
    u8 u0;
    u8 *u4;
    s8 u8_;
    f32 uC;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    s8 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s8 u2E;
    s8 u2F;
    s8 u30;
    f32 u34;
    s8 u38;
    s8 u39;
} SpA3C;
typedef struct {
    s32 a;
    u8 b;
    s32 c;
    s32 d;
    f32 e;
    f32 f;
} SpB3C;
s32 func_15134DAC(SpA3C *, s32, ...);
extern f32 D_800A9384;
extern f32 D_800A9388;

s32 func_151AAA3C(u8 *arg0, s32 arg1) {
    SpA3C s;
    s32 v;
    SpB3C b;

    b.a = arg1;
    b.b = 1;
    s.u0 = arg0[0x3B];
    s.u4 = arg0;
    s.u8_ = 15;
    s.uC = -11.0f;
    s.u10 = -2.0f;
    s.u14 = 8.0f;
    s.u18 = -11.0f;
    s.u1C = -2.0f;
    s.u20 = 20.0f;
    s.u24 = 0;
    s.u26 = 60;
    s.u28 = 60;
    s.u2A = 300;
    s.u2E = 1;
    s.u2F = 0;
    s.u30 = 1;
    s.u34 = 0.5f;
    s.u38 = 1;
    s.u39 = 0;
    b.c = 0;
    b.d = 0x11111;
    b.e = D_800A9384;
    b.f = D_800A9388;
    v = func_15134DAC(&s, 0x18);
    if (v != 0) {
        memcpy((void *)(v + 0x80), &b, 0x18);
    }
    return v;
}

s32 func_151EFDD0();

s32 func_151AAB54(u8 *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x88)) = 0;
    if (func_150ADA20() & 1) {
        func_10010F88(0xA, 0x55F0U, (s16) ((func_151EFDD0() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    } else {
        func_10010F88(0xB, 0x55F0U, (s16) ((func_151EFDD0() % 1200) - 0x258), 0U, 0, (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x58)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x5C)), (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x60)), 0x1F4, 0x9C4);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AAC88.s")

f32 func_151AAFFC(u8 *arg0) {
    u8 **q;
    u8 *p;
    f32 r;

    q = &arg0;
    r = func_151423D8((((u32) (*(u32 *)((u8 *)arg0 + 0x88)) >> 0x10) - 0x40));
    p = *q;
    r = (*(f32 *)((u8 *)p + 0x90)) + ((*(f32 *)((u8 *)p + 0x94)) * (0, r)); // fakematch: (0, x) comma flips commutative operand order
    p += 0x80;
    *(s32 *)(p + 8) = (*(s32 *)((u8 *)p + 0xC)) * D_800BE9E4 + (*(u32 *)((u8 *)p + 8));
    return r;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB06C.s")

void func_151AB100(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_151352EC(arg0);
}

void func_151AB128(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x80) + 0x58;
    *(s32 *)(temp_v0 + 0x14) = 0;
    func_1513530C(arg0);
}

s32 func_151AB150(u8 *arg0) {
    s32 ret = 1;
    if (arg0[0x84] == 0) {
        ret = 0;
    }
    arg0[0x84] = 0;
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AABC4.s")

s32 func_151AB36C(u8 *arg0) {
    u8 *temp_v0;
    s32 temp_v1;
    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = *(s16 *)(arg0 + 0x1C) << 4;
    if (temp_v1 >= 0x100) {
        temp_v1 = 0xFF;
    }
    if (temp_v1 < temp_v0[0x1B]) {
        temp_v0[0x1B] = temp_v1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB3A8.s")

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 pad1A;
    f32 unk1C;
} struct_C630;
s8 func_151AB640(u8 *arg0) {
    s8 ret;
    struct_C630 *p;
    ret = 1;
    p = (struct_C630 *)(arg0 + 0xB0);
    if (p->unk4 == 0) {
        ret = 0;
    }
    p->unk4 = 0;
    p->unk14 -= D_800BE9E4;
    if (p->unk14 < 0) {
        p->unk14 = ((u32)func_150ADA20() % (u32)(p->unk18 + 1)) + p->unk16;
        p->unk10 = (func_150ADA68() * p->unkC) + p->unk8;
    }
    *(s32 *)(arg0 + 0x24) += (s32)((p->unk10 - (f32)*(s32 *)(arg0 + 0x24)) * p->unk1C);
    return ret;
}

s32 func_1513F6C0(u8 *, s32, s32);
s32 func_151AB730(u8 *arg0)
{
  u8 *p;
  p = *((u8 **) (arg0 + 0xB0));
  p += 0x59;  // fakematch: keeps the dead addiu (p += K+1; p--;)
  p--;  // fakematch: pairs with p += K+1
  *((s32 *) (p + 0x18)) = 0;
  *((s32 *) (arg0 + 0xB0)) = 0;
  *((s32 *) (arg0 + 0x18)) = (*((s32 *) (arg0 + 0x18))) | 2;
  func_1513F6C0(arg0, 0, 0);
  return 0;
}

extern f32 D_800A93CC;
void func_151AB774(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x18);
    struct17 pos;
    s32 ret;

    if ((obj && obj) && obj) { // fakematch: scheduling barrier after the obj load (permuter)
    }
    pos.unk0 = *(f32 *)(obj + 0x14);
    if (D_800A93CC < *(f32 *)(obj + 0x118)) {
        pos.unk4 = *(f32 *)(obj + 0x118) + 100.0f;
    } else {
        pos.unk4 = *(f32 *)(obj + 0x18) + 150.0f;
    }
    pos.unk8 = *(f32 *)(obj + 0x1C);
    ret = func_15045AF0((u8 *)&pos, 0, pos.unk4 - 300.0f, arg0 + 0x34);
    if (ret) {
        pos.unk4 = *(f32 *)(arg0 + 0x34);
        func_151AC3F0(&pos, (s32 *)(arg0 + 0x34), 3, arg0[0xC], arg0[1]);
        func_10010FFC(0, 17, 21000, 0, 0, obj);
    }
    func_151AA814(obj, arg0 + 0x34);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB874.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151AB954.s")

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    u16 unk6;
} SndC68;

u8 func_151ABC68(u8 *arg0) {
    u8 ret;
    SndC68 *s;

    ret = 1;
    s = (SndC68 *)(arg0 + 0x58);
    if (s->unk6 != 0 && !(D_800DBFF0->unk5F0 & 1)) {
        func_100111C8(*(s16 *)&s->unk6);
        s->unk6 = 0;
    } else if (s->unk6 == 0 && (D_800DBFF0->unk5F0 & 1)) {
        s->unk6 = func_10010F30(0x355, 0x7D00, 0x40, 0, 0);
    }
    if (s->unk4 == 0) {
        ret = 0;
    }
    s->unk4 = 0;
    return ret;
}

void func_151ABD38(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        func_100111C8(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    func_151346EC(arg0);
}

void func_151ABD88(u8 *arg0) {
    s32 pad;
    s32 *temp_v0;

    temp_v0 = (s32 *)(*(u8 **)(arg0 + 0x58) + 0x58);
    if (*(u16 *)(arg0 + 0x5E) != 0) {
        func_100111C8(*(s16 *)(arg0 + 0x5E));
    }
    temp_v0[7] = 0;
    func_1513470C(arg0);
}

void func_151ABDD8(void **arg0) {
    func_15141DA4(arg0[0x18 / 4], 0, 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABE04.s")

void func_151AB920(s32 arg0, s32 arg1) {
}

u8 func_151D8E20(void);
extern f32 D_800A93F4;

void func_151AB930(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        u8 *unk0;
        u8 unk4;
        s32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        u8 unk18;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk8 = *(u16 *)(arg0 + 0x84);
    tmp.unkC = 0.0f;
    tmp.unk10 = D_800A93F4;
    tmp.unk14 = 3.0f;
    tmp.unk18 = func_151D8E20();
    temp_v0 = func_151491F4(0x3C, -1, 0xE, 1, 9, 0x1C, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x1C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1D7790/func_151ABF78.s")

void func_151AC304(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0x28;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0x28;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}

void func_151AC3B0(u8 *arg0)
{
  struct { u8 *unk0; u8 unk4; } sp18;
  sp18.unk0 = arg0;
  sp18.unk4 = arg0[0x3B];
  func_1516944C(0x20, (s32) &sp18, 0xCU);
}
