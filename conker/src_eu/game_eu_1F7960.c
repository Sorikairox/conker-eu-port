#include <ultra64.h>
#include "functions.h"
#include "variables.h"
void *memcpy(void *, const void *, unsigned int);

void func_151CD444(u8 *arg0);
s32 func_151CA398(u8 *, s32, s32, s32, s32);
s32 func_151CA484(u8 *);
s32 func_151CA4E8(u8 *, s32, s32, s32, s32);
s32 func_151CAC50(u8 *, s32);
void func_151CB128(u8 *, u8);
s32 func_151CB2D8(u8 *, u8);
void func_151CBBAC(u8 *, u8, u8, s8, u8);
void func_151CCAD4(u8 *, u8, u8, u8, u8, u8);
s32 func_151CCDF0(u8 *, s32, s32, s32, s32, s32);
void func_151CD2CC(u8 *, u8, u8, u8);
extern u8 D_800CC3C8[];

void func_151CA150(u8 *arg0, s32 arg1)
{
  s32 v; s32 t;
  func_151CA484(arg0);
  v = *((u8 *) (((u8 *) (*((u8 **) (((u8 *) arg0) + 0x3D0)))) + 0x65));
  if (v != 0) { t = D_800CC3C8[v * 0x32C]; if ((t == 0x23) || (t == 0x8A)) arg1 = 0x1B; }
  switch (arg1)
  {
    case 0x23:
      func_151CA4E8(arg0, 1, 1, -1, 0xFF);
      func_151CAC50(arg0, 0);
      return;

    case 0x1F:

    case 0x29:
      func_151CA4E8(arg0, 2, 1, -1, 0xFF);
      func_151CB2D8(arg0, 0);
      return;

    case 0xC:

    case 0x16:
      func_151CB2D8(arg0, 0);
      func_151CD444(arg0);
      return;

    case 0x1B:
      if (D_800BE9F0 == 0x27)
    {
      func_151CA398(arg0, 1, -1, 0xFF, 1);
      return;
    }
      if (D_80082FA0 == 0)
    {
      func_151CCAD4(arg0, 0xFF, 0, 0, 1, 0xFF);
      func_151CCDF0(arg0, 0xFF, 0, 0, 1, 0xFF);
    }
    else
    {
      func_151CD2CC(arg0, 0xFF, 0, 0);
    }
      func_151CA4E8(arg0, 3, 1, -1, 0xFF);
      func_151CBBAC(arg0, 1, 1, -1, 0xFF);
      return;

    case 0x24:
      func_151CA4E8(arg0, 0, 1, -1, 0xFF);
      func_151CAC50(arg0, 0);
      return;

    case 0x12:

    case 0x18:

    case 0x38:

    case 0x3B:
      break;

    case 9:

    default:
      func_151CB128(arg0, 0);
      break;

  }

}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA398.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA484.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA4E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CAC50.s")

void func_151CB07C(struct102 *arg0, u8 **arg1, u8 arg2) {
    void (*f)(void *, u8 **, u8);
    u8 *v;

    if (arg2 == 0x21) {
        if (*(s32 *)((u8 *)arg0 + 0x70) == (s32)arg1[0]) {
            func_1516972C(arg0);
        }
    dummy_label: ; // fakematch: empty label after the first arm makes IDO fill the b delay slot like the original
    } else if (arg2 == 0) {
        v = arg1[0];
        if (*(s32 *)((u8 *)arg0 + 0x70) == *(s32 *)(v + 0x318)) {
            func_1516972C(arg0);
        }
    }
    f = D_8008FFB0[*(u8 *)((u8 *)arg0 + 0x7D)];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 u0;
    f32 u4;
    f32 u8;
    f32 uC;
    u8 u10;
    s16 u12;
    u16 u14;
    s16 u16;
    s16 u18;
    u8 u1A;
    u8 u1B;
    u8 u1C;
    u8 u1D;
    u8 u1E;
    u8 u1F;
    u8 u20;
    u8 u21;
    u8 u22;
    u8 u23;
    s32 u24;
    s32 u28;
    s32 u2C;
    s32 u30;
    s32 u34;
    s32 u38;
    s32 u3C;
    u8 u40;
    u8 u41;
    u8 pad42[2];
    u8 u44;
    f32 u48;
    f32 u4C;
    f32 u50;
    f32 u54;
} Spawn559A;

typedef struct {
    u8 *u0;
    f32 u4;
    f32 u8;
    u8 uC;
    u8 uD;
    u8 uE;
    u8 padF;
    f32 u10;
    f32 u14;
    f32 u18;
    f32 u1C;
    f32 u20;
    u8 pad24[0x30];
    s8 u54;
    u8 pad55[3];
} Spawn559B;

void func_151CB128(u8 *arg0, u8 arg1) {
    Spawn559A a;
    s32 pad2; // fakematch: 4-byte hole between blocks
    Spawn559B b;
    f32 f;
    s32 ret;

    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uD = 0;
    b.uC = 0;
    if (D_80082FA0 > 0) {
        f = 2.0f;
    } else {
        f = 1.0f;
    }
    a.u10 = 0x64;
    a.u12 = 0x12C;
    a.uC = f * 12.0f;
    a.u8 = a.uC;
    a.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = 0xFF;
    a.u1C = 0xC8;
    a.u1D = 0;
    a.u1E = 0x82;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x44;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u0 = 0.0f;
    a.u4 = 0.0f;
    a.u44 = arg0[0x23D];
    ret = func_151559FC(&a, (u8)(arg1 ? 4 : 0), 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB2D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB6C0.s")

void func_151CBA4C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x18) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x18) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

void func_151CBAC0(u8 *arg0) {
    f32 target;
    u8 *t;
    u8 *p;

    p = arg0 + 0x70;
    t = *(u8 **)p;
    if ((**(u16 **)(t + 0x36C) & 0x2000) && *(u16 *)(*(u8 **)(t + 0x3D4) + 0x19E) == 0) {
        target = *(f32 *)(p + 8);
    } else {
        target = 0.0f;
    }
    *(f32 *)(p + 4) += (target - *(f32 *)(p + 4)) * 0.4f;
    arg0[0x2E] = *(f32 *)(p + 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CBBAC.s")

void func_151CBEC8(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0 = arg0 + 0x70;
    if ((arg2 == 0x37) && (arg1[0] == temp_v0[0xE]) && (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0)) {
        *(f32 *)(temp_v0 + 0x10) = 0.0f;
        temp_v0[0xC] |= 1;
        *(f32 *)(temp_v0 + 0x14) = 0.0f;
    }
}

f32 func_151CC784(u8 *);
typedef struct { u8 pad0[0xC]; u8 unkC; u8 unkD; u8 padE[2]; f32 unk10; f32 unk14; f32 unk18; f32 unk1C; f32 unk20; } Sub151CBF20;
s32 func_151CBF20(u8 *arg0) {
    s32 pad; // frame padding
    Sub151CBF20 *v;
    f32 t;
    f32 k;
    f32 lo;
    u8 a;

    v = (Sub151CBF20 *)(arg0 + 0x70);
    k = (1.0f - ((func_151CC784(arg0) - v->unk18) * v->unk20)) * 75.0f;
    if (v->unkC & 1) {
        lo = 91.0f + k;
        *(f32 *)(arg0 + 0x14) = (sinf(v->unk10) * ((112.0f + k) - lo)) + lo;
        v->unk10 += 0.505f * D_800BE9A4;
        if (v->unk10 >= 3.1415927f) {
            *(f32 *)(arg0 + 0x14) = lo;
            v->unkC &= 0xFFFE;
        }
    } else {
        *(f32 *)(arg0 + 0x14) = 91.0f + k;
    }
    if (v->unkD == 2) {
        *(f32 *)(arg0 + 0x14) -= 20.0f;
    }
    a = v->unk14;
    if (arg0[0x20] == 0x7C) {
        arg0[0x2E] = 0xFF - a;
    } else {
        arg0[0x2E] = a;
    }
    v->unk14 += (255.0f - v->unk14) * 0.67600006f;
    return 1;
}

void func_151CC11C(struct102 *arg0, u8 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(u8 **)((u8 *)arg0 + 0x20) == *arg1) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        u8 *p = *arg1;
        if (*(u8 **)((u8 *)arg0 + 0x20) == *(u8 **)(p + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

f32 func_151CC784(u8 *arg0);
void func_1514373C(f32 arg0, f32 arg1, u8 *arg2, u8 *arg3);

typedef struct {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} Sub151CC190;

s32 func_151CC190(u8 *arg0) {
    f32 temp;
    f32 prod;
    Sub151CC190 *v;

    v = (Sub151CC190 *)(arg0 + 0x70);
    temp = func_151CC784(arg0);
    if (temp != v->unk28) {
        v->unk28 = temp;
        prod = (temp - v->unk18) * v->unk20 * 6.283186f;
        func_1514373C(v->unk24 + prod, 55.0f, arg0 + 0x10, arg0 + 0x14);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC784.s")

void func_151CC840(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_15155C9C((f32 *) &sp1C, 0x46);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC86C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCD2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCDF0.s")

void func_151CD2CC(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    Spawn559A a;
    s32 pad2; // fakematch: 4-byte hole between blocks
    Spawn559B b;
    s32 ret;

    b.u0 = arg0;
    b.u4 = 0.0f;
    b.u8 = 130.0f;
    b.uD = 0;
    b.uC = 0;
    a.u12 = 0x12C;
    a.u14 = (1 << (arg0[0x23D] + 0xB)) | 0x50;
    a.u16 = 1;
    a.u18 = 0xFF;
    a.u1A = 7;
    a.u1B = arg1;
    a.u1C = arg2;
    a.u1D = arg3;
    a.u1E = 0xB4;
    a.u1F = 0xFF;
    a.u20 = 0xFF;
    a.u21 = 0xFF;
    a.u22 = 0xFF;
    a.u23 = 0xFF;
    a.u24 = 0;
    a.u28 = 0x200004;
    a.u2C = 0x1F0601;
    a.u30 = 8;
    a.u34 = 0x44;
    a.u38 = 0x80;
    a.u3C = 0x20;
    a.u40 = 0;
    a.u41 = 0xA;
    a.u0 = 0.0f;
    a.u4 = 0.0f;
    a.u44 = arg0[0x23D];
    a.u10 = 0xB4;
    a.u8 = 65.0f;
    a.uC = 65.0f;
    ret = func_151559FC(&a, 0, 0, 0, 0x58, 0xFF, 1);
    if (ret != 0) {
        memcpy((void *)(ret + 0x70), &b, 0x58);
    }
}

s32 func_151A5580(s32, s32, s32, s32, s32, s32, u8, s32);

void func_151CD444(u8 *arg0) {
    s32 temp_v0;
    u8 *sp28;

    if (D_800BE616 != 0) {
        sp28 = arg0;
        temp_v0 = func_151A5580(0, 0, 0, 0xFF, 0, (s32) (*(u8 *)((u8 *)arg0 + 0x23D)), 1, 4);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x20, &sp28, 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CD4B8.s")

f32 func_151CC784(u8 *);
typedef struct { u8 pad0[0xD]; u8 unkD; u8 padE[0xA]; f32 unk18; f32 unk1C; f32 unk20; } SubCD;
void func_151CD7D4(u8 *arg0) {
    f32 k;
    SubCD *v;

    v = (SubCD *)(arg0 + 0x70);
    k = (1.0f - ((func_151CC784(arg0) - v->unk18) * v->unk20)) * 75.0f;
    if (v->unkD == 5) {
        *(f32 *)(arg0 + 0x14) = 92.0f + k;
    } else if (v->unkD == 4) {
        *(f32 *)(arg0 + 0x14) = -92.0f - k;
    }
}
