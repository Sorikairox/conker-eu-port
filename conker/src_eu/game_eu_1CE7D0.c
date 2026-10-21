#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151A177C(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);


s32 func_1510FE4C(s32);

void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        u8 unkC;
        u8 padD[3];
        f32 unk10;
    } tmp;

    if (arg0 != NULL) {
        tmp.unk0 = *(f32 *)(arg0 + 0x14);
        tmp.unk8 = *(f32 *)(arg0 + 0x1C);
        if (D_800C35EA != 1) {
            tmp.unk4 = *(f32 *)(arg0 + 0x180);
            tmp.unk10 = 0.0f;
            switch (func_1510FE4C(*(s32 *)(arg0 + 0x184))) {
            case 0xA:
                tmp.unkC = 0;
                break;
            case 0xF:
            case 0x11:
                tmp.unkC = 1;
                break;
            default:
                tmp.unkC = 0;
                break;
            }
            temp_v0 = func_151491F4(arg1, -1, 1, 1, 0, 0x14, arg2, arg3);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
            }
        }
    }
}

#ifdef NON_MATCHING
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#else
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#endif
void func_151A10A8(u8 *arg0) {
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (0.17500001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        temp_s0 = arg0 + 0x28;
        do {
#ifdef NON_MATCHING
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(f32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
#else
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(s32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
#endif
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A11BC.s")

void func_151A13F0(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

void func_151A14D8(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

#ifdef NON_MATCHING
void func_151A15C0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7) {
    s16 temp_v0;
    s16 var_t4;
    s32 temp_f10;
    s32 temp_f18;
    s32 temp_f4;
    s32 temp_f8;

    temp_v0 = arg3 - 0x20;
    var_t4 = temp_v0;
    if (temp_v0 <= 0) {
        var_t4 = 1;
    }
    temp_f18 = (s32) (70.0f * arg5);
    temp_f8 = (s32) (30.0f * arg5);
    temp_f4 = (s32) (1500.0f * arg4);
    temp_f10 = (s32) (100.0f * arg4);
    func_151A177C(arg0, arg1, arg2, 250.0f * arg4, 1.0f, (s32) (s16) temp_f18, (s32) (s16) temp_f8, (s32) (s16) temp_f4, (s32) (s16) temp_f10, 0x12, 1.0f, (s32) (90.0f * arg5), (s32) (20.0f * arg5), (s32) (s16) temp_f4, (s32) (s16) temp_f10, (s32) var_t4, 0x10, 1.0f, (s32) (s16) temp_f18, (s32) (s16) temp_f8, (s32) (s16) temp_f4, (s32) (s16) temp_f10, (s32) (15.0f * arg4), (s32) (10.0f * arg4), 0x12, temp_v0 + 0x10, (u8) (s32) arg6, arg7);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A15C0.s")
#endif
void func_151A177C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF, s32 arg10, f32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, u8 arg1A, s32 arg1B) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1794.s")

#ifdef NON_MATCHING
void func_151A1D0C(u8 *arg0) {
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xC)) < temp_v1) {
        temp_t7 = (((*(s16 *)((u8 *)arg0 + 0x20)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2C))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0xE)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x14))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x20)) = (s16) (temp_t7 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2C)) = (u8) temp_t7;
        temp_t6 = (((*(s16 *)((u8 *)arg0 + 0x22)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2E))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0x10)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x16))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x22)) = (s16) (temp_t6 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2E)) = (u8) temp_t6;
        temp_t5 = (((*(s16 *)((u8 *)arg0 + 0x24)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2D))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0x12)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x18))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x24)) = (s16) (temp_t5 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2D)) = (u8) temp_t5;
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x1A))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) ((*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0x1C)));
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x1E))) {
        temp_lo_2 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0x20));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo_2;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo_2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1D0C.s")
#endif
void func_151A1E8C(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct260 *temp_v0;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
    } tmp;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 3, 1, 0, 0x20, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

#ifdef NON_MATCHING
s32 func_15167D84(s32 **, s32, s32, s32, s32, s32);
extern s32 D_800910E4;

void func_151A1F48(u8 *arg0) {
    struct {
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s16 uA6;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        s32 * uB4;
        s32 uB8;
        u8 padBC[0x4];
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        s16 uCC;
        u8 padCE[0x2];
        s8 uD0;
        s8 uD1;
        s8 uD2;
        s8 uD3;
        s16 uD4;
        s16 uD6;
        s16 uD8;
        s16 uDA;
        s16 uDC;
        s8 uDE;
        u8 padDF[0x1];
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        u8 padE7[0x1];
        u16 uE8;
    } sp;
    f32 sp80;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t5;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x3C)) * D_800BE9A4));
    temp_s0 = arg0 + 0x28;
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        sp.uE0 = 0xFF;
        sp.uE1 = 0xFF;
        sp.uE2 = 0xFF;
        sp.uE4 = 0;
        sp.uE5 = 0;
        sp.uE6 = 0;
        sp.uD3 = 0x11;
        sp.uE8 = 0x120;
        sp.uB8 = 0xC0001;
        sp.uC0 = 0;
        sp.uB4 = &D_800910E4;
        sp.uCA = 0;
        sp.uD4 = 0;
        sp.uCC = 0;
        sp.uD6 = 0;
        sp.uDE = 0;
        sp.uE3 = 0;
        sp.uD8 = 0x7D0;
        sp.uDA = 0x7D0;
        do {
            temp_s1 = func_150ADA20() & 0xFF;
            temp_s2 = func_150ADA20() & 0xFF;
            temp_f20 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f22 = func_151423D8(temp_s1 & 0xFF);
            temp_f24 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f26 = func_151423D8(temp_s2 & 0xFF);
            temp_f2 = func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0xC));
            temp_f12 = temp_f2 * temp_f26;
            temp_f28 = (*(f32 *)((u8 *)temp_s0 + 0)) + (temp_f12 * temp_f20);
            temp_f30 = (*(f32 *)((u8 *)temp_s0 + 4)) - (temp_f2 * temp_f24);
            sp80 = (*(f32 *)((u8 *)temp_s0 + 8)) + (temp_f12 * temp_f22);
            if (func_150ADA20() & 1) {
                sp.uE8 |= 4;
            }
            if (func_150ADA20() & 1) {
                sp.uE8 |= 8;
            }
            temp_t5 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1A)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x18));
            sp.uC2 = temp_t5;
            temp_t1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
            sp.uDC = (*(u8 *)((u8 *)D_80090F10 + 0x1D8)) * (0x100 / temp_t5);
            temp_v1 = sp.uDC >> 2;
            temp_t2 = sp.uDC - temp_v1;
            temp_t0 = sp.uDC >> 1;
            sp.uAA = (s16) temp_t0;
            sp.uA4 = temp_t2;
            sp.uA0 = (s16) (0xFF / (s32) (sp.uDC - temp_t2));
            sp.uA2 = sp.uDC;
            sp.uA8 = sp.uDC;
            sp.uA6 = (s16) (temp_t1 / (s32) (sp.uDC - sp.uAA));
            sp.uAC = (s16) temp_v1;
            sp.uC6 = (s16) (s32) temp_f30;
            sp.uAE = (s16) (0xFF / (s16) temp_v1);
            sp.uB0 = (s16) temp_t0;
            sp.uB2 = (s16) (temp_t1 / (s16) temp_t0);
            sp.uC4 = (s16) (s32) temp_f28;
            sp.uC8 = (s16) (s32) sp80;
            sp.uD0 = (s8) (s32) (temp_f28 * 256.0f);
            sp.uD2 = (s8) (s32) (temp_f30 * 256.0f);
            sp.uD1 = (s8) (s32) (sp80 * 256.0f);
            temp_v0 = func_15167D84(&sp.uB4, 0, 0x14, -1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0x50, &sp.uA0, 0x14);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1F48.s")
#endif
void func_151A23E4(u8 *arg0)
{
  s16 temp_lo;
  u8 *new_var;
  s16 temp_lo_2;
  u8 *new_var2;
  s16 temp_v1;
  u8 *temp_v0;
  u8 *temp_v0_2;
  new_var = (0, arg0 + 0x50); // fakematch: (0, x) comma flips commutative operand order
  temp_v1 = *((s16 *) (((u8 *) arg0) + 0x38));
  temp_v0 = new_var;
  if ((*((s16 *) (((u8 *) arg0) + 0x54))) < temp_v1)
  {
    new_var2 = ((u8 *) temp_v0) + 2;
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0) + 0))) * ((*((s16 *) new_var2)) - temp_v1));
  }
  temp_v0_2 = new_var;
  if ((*((s16 *) (((u8 *) temp_v0_2) + 0xA))) < temp_v1)
  {
    temp_lo = (*((s16 *) (((u8 *) temp_v0_2) + 6))) * ((*((s16 *) (((u8 *) temp_v0_2) + 8))) - temp_v1);
    *((s16 *) (((u8 *) arg0) + 0x36)) = temp_lo;
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo;
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) + 0xC))))
  {
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0_2) + 0xE))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) - (-0x10)))))
  {
    temp_lo_2 = (*((s16 *) (((u8 *) arg0) + 0x36)) = (*((s16 *) (((u8 *) temp_v0_2) + 0x12))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo_2;
  }
}

void func_151A2498(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
        s16 unk20;
        s16 unk22;
        u8 pad24[4];
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    tmp.unk20 = *(s16 *)(arg0 + 0x46);
    tmp.unk22 = *(s16 *)(arg0 + 0x48);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 4, 1, 0, 0x24, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x24);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2564.s")

#ifdef NON_MATCHING
void func_151A2A58(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x10))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * (*(s16 *)((u8 *)temp_v0_2 + 0x12)));
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x14))) {
        temp_lo_2 = (*(s16 *)((u8 *)temp_v0_2 + 0x16)) * D_800BE9E4;
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x34)) + temp_lo_2);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x36)) + temp_lo_2);
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0xC))) {
        (*(s8 *)((u8 *)arg0 + 0x2F)) = 0x13;
        (*(u16 *)((u8 *)arg0 + 0x44)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x44)) | 0x101);
        temp_lo_3 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0xE));
        (*(s32 *)((u8 *)arg0 + 0x14)) = 0x520003;
        (*(s8 *)((u8 *)arg0 + 0x42)) = temp_lo_3;
        (*(s8 *)((u8 *)arg0 + 0x41)) = temp_lo_3;
        (*(s8 *)((u8 *)arg0 + 0x40)) = temp_lo_3;
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x18))) {
        (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (*(s16 *)((u8 *)temp_v0_2 + 0x1A));
        (*(s16 *)((u8 *)temp_v0_2 + 0x18)) = -0x270F;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2A58.s")
#endif
#ifdef NON_MATCHING
void func_151A2B90(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x10))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * (*(s16 *)((u8 *)temp_v0_2 + 0x12)));
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x14))) {
        temp_lo_2 = (*(s16 *)((u8 *)temp_v0_2 + 0x16)) * D_800BE9E4;
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x34)) + temp_lo_2);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x36)) + temp_lo_2);
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x18))) {
        (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (*(s16 *)((u8 *)temp_v0_2 + 0x1A));
        (*(s16 *)((u8 *)temp_v0_2 + 0x18)) = -0x270F;
    }
    temp_lo_3 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0xE));
    (*(s8 *)((u8 *)arg0 + 0x42)) = temp_lo_3;
    (*(s8 *)((u8 *)arg0 + 0x41)) = temp_lo_3;
    (*(s8 *)((u8 *)arg0 + 0x40)) = temp_lo_3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2B90.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2C9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2F10.s")

s32 func_151A31D4(s32, s32, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32, u8);

s32 func_151A2FC4(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s16 argC, s16 argD, s16 argE, s16 argF, s16 arg10, s8 arg11, u8 arg12, s32 arg13) {
    return func_151A31D4(arg0, 0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, argE, argF, arg10, arg11, arg12, arg13, 1);
}

#ifdef NON_MATCHING
void func_151A3084(s32 arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s16 arg9, s16 argA, s16 argB, s16 argC, s16 argD, s16 argE, s8 argF, u8 arg10, s32 arg11) {
    func_151A31D4(arg0, arg1, 0, 0, 0.0f, arg2, arg3, arg4, arg5, arg6, arg7, arg8, (s16) (s32) arg9, (s16) (s32) argA, (s16) (s32) argB, (s16) (s32) argC, (s16) (s32) argD, (s16) (s32) argE, (s8) (s32) argF, (u8) (s32) arg10, arg11, 0U);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3084.s")
#endif
void func_151A3134(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 *arg5) {
    f32 temp_f0 = 1.0f - arg4;

    arg5[0] = arg0[0] * temp_f0;
    arg5[1] = arg0[1] * temp_f0;
    arg5[2] = arg0[2] * temp_f0;
}

s32 func_15143794(s16, s16, f32, s32);
void func_151A3180(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15143794(arg1, arg2, (1.0f - arg4) * arg3, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A31D4.s")

#ifdef NON_MATCHING
s32 func_151530A8(s32 *, u8, u8, u8 *);

void func_151A34BC(u8 *arg0) {
    struct {
        s32 u1C;
        s32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 8;
    sp.u20 = 6;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x44));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x48));
    if ((*(s32 *)((u8 *)arg0 + 0x68)) & 0x1000) {
        sp.u24 += (*(f32 *)((u8 *)arg0 + 0x4C));
        sp.u28 += (*(f32 *)((u8 *)arg0 + 0x50));
        sp.u2C += (*(f32 *)((u8 *)arg0 + 0x54));
    }
    sp.u30 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.02f;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u54 = 1;
    sp.u58 = 0x11;
    sp.u4E = 0x56;
    sp.u50 = 3;
    sp.u5A = 0x12;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u64 = 0xFF;
    sp.u66 = 0x37;
    sp.u61 = 0xFF;
    sp.u62 = 0xC8;
    sp.u63 = 0xC8;
    sp.u67 = 0x37;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u71 = 0xFF;
    sp.u34 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.035299998f;
    sp.u48 = 0;
    sp.u65 = 0;
    sp.u68 = 0;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u72 = 0;
    sp.u73 = 1;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 7;
    sp.u82 = 0x24;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u38 = -0.268f;
    sp.u40 = 8.0f;
    sp.u44 = 10.0f;
    sp.u3C = 0.0f;
    sp.u88 = 1.0f;
    func_151530A8(&sp.u1C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)), arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A34BC.s")
#endif
#ifdef NON_MATCHING
s32 func_151530A8(s32 *, u8, u8, u8 *);

void func_151A3700(u8 *arg0) {
    struct {
        s32 u1C;
        s32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 0xA;
    sp.u20 = 0xF;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x44));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x48));
    if ((*(s32 *)((u8 *)arg0 + 0x68)) & 0x1000) {
        sp.u24 += (*(f32 *)((u8 *)arg0 + 0x4C));
        sp.u28 += (*(f32 *)((u8 *)arg0 + 0x50));
        sp.u2C += (*(f32 *)((u8 *)arg0 + 0x54));
    }
    sp.u30 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.0212f;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u54 = 2;
    sp.u58 = 0xF;
    sp.u4E = 0x56;
    sp.u50 = 3;
    sp.u5A = 0x1E;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u64 = 0xFF;
    sp.u66 = 0x37;
    sp.u61 = 0xFF;
    sp.u62 = 0xC8;
    sp.u63 = 0xC8;
    sp.u67 = 0x37;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u71 = 0xFF;
    sp.u34 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.0532f;
    sp.u48 = 0;
    sp.u65 = 0;
    sp.u68 = 0;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u72 = 0;
    sp.u73 = 1;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 0xF;
    sp.u82 = 0x11;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u40 = 8.0f;
    sp.u44 = 8.0f;
    sp.u38 = -1.031f;
    sp.u3C = 0.0f;
    sp.u88 = 1.0f;
    func_151530A8(&sp.u1C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)), arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3700.s")
#endif