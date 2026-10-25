#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151CA398(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151CA484(u8 *arg0);
s32 func_151559FC(void *, s32, s32, s32, s32, s32, s32);
#endif
void *memcpy(void *, const void *, unsigned int);

void func_151CD444(u8 *arg0);
#ifndef NON_MATCHING
s32 func_151CA398(u8 *, s32, s32, s32, s32);
#endif
#ifndef NON_MATCHING
s32 func_151CA484(u8 *);
#endif
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

#ifdef NON_MATCHING
void func_150BE390(s32, u8, s32);
s32 func_151CD4B8(u8 *, s32, s8, s32);

void func_151CA398(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s1 = arg3 & 0xFF;
    temp_s2 = arg1 & 0xFF;
    func_151CA4E8(arg0, 4, temp_s2 & 0xFF, (s32) (s8) arg2, temp_s1);
    func_151CCAD4(arg0, 0U, 0x32U, 0xFFU, (u8) temp_s2, (u8) temp_s1);
    func_151CCDF0(arg0, 0, 0x32, 0xFF, temp_s2, temp_s1);
    func_151CD4B8(arg0, temp_s2 & 0xFF, (s8) arg2, temp_s1 & 0xFF);
    func_150BE390(arg0, temp_s1 & 0xFF, arg4);
    func_151CBBAC(arg0, 2U, temp_s2 & 0xFF, (s8) arg2, (u8) temp_s1);
    if (D_800BE9F0 == 0x27) {
        D_8008D0A0 = 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA398.s")
#endif
#ifdef NON_MATCHING
void func_151607E4(s32, u8);
void func_151A5BCC(s32, u8);

void func_151CA484(u8 *arg0) {
    struct {
        u8 * u24;
    } sp;

    sp.u24 = arg0;
    func_151607E4(&sp.u24, 0x21);
    func_15155C9C(&sp.u24, 0x21U);
    func_151A5BCC(&sp.u24, 0x21);
    func_151494E0((s32) &sp.u24, 0x21U);
    D_8008D0A0 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA484.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CA4E8.s")

#ifdef NON_MATCHING
s32 func_151CAC50(u8 *arg0, s32 arg1) {
    struct {
        u8 * u44;
        f32 u48;
        f32 u4C;
        s8 u50;
        s8 u51;
        u8 pad52[0xA];
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        u8 pad70[0x30];
        f32 uA0;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        s8 uB0;
        u8 padB1[0x1];
        s16 uB2;
        u16 uB4;
        s16 uB6;
        s16 uB8;
        s8 uBA;
        s8 uBB;
        s8 uBC;
        s8 uBD;
        s8 uBE;
        s8 uBF;
        s8 uC0;
        s8 uC1;
        s8 uC2;
        s8 uC3;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s8 uE0;
        s8 uE1;
        u8 padE2[0x2];
        u8 uE4;
    } sp;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u16 temp_t2;
    u16 temp_t6;

    temp_s0 = arg1 & 0xFF;
    sp.u51 = 0;
    sp.u50 = 0;
    sp.uAC = 25.0f;
    sp.uA8 = 25.0f;
    sp.u44 = arg0;
    sp.u48 = 0.0f;
    sp.u4C = 130.0f;
    if (D_80082FA0 > 0) {
        sp.uB0 = 0x73;
    } else {
        sp.uB0 = 0x5D;
    }
    sp.uB2 = 0x12C;
    temp_t6 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uB6 = 1;
    sp.uBA = 7;
    sp.uBC = 0xFF;
    sp.uBE = 0x82;
    sp.uBF = 0xFF;
    sp.uC0 = 0xFF;
    sp.uC1 = 0xFF;
    sp.uC2 = 0xFF;
    sp.uD0 = 8;
    sp.uB4 = temp_t6;
    sp.uB8 = 0xFF;
    sp.uBB = 0;
    sp.uBD = 0;
    sp.uC3 = 0xFF;
    sp.uC4 = 0;
    sp.uC8 = 0x200004;
    sp.uCC = 0x1F0601;
    sp.uD4 = 0x44;
    sp.uD8 = 0x80;
    sp.uDC = 0x20;
    sp.uE0 = 0;
    sp.uE1 = 0xA;
    temp_t2 = temp_t6 & 0xFFF9;
    sp.uB4 = temp_t2;
    sp.uB4 = temp_t2 | 6;
    sp.uA0 = 25.0f;
    sp.uA4 = 25.0f;
    sp.uE4 = (*(u8 *)((u8 *)arg0 + 0x23D));
    if (temp_s0 != 0) {
        var_v0_2 = 4;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = func_151559FC(&sp.uA0, var_v0_2 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 = (sp.uB4 & 0xFFF9) | 4;
    sp.uA0 = -25.0f;
    sp.uA4 = 25.0f;
    if (temp_s0 != 0) {
        var_v0_3 = 4;
    } else {
        var_v0_3 = 0;
    }
    temp_v0_2 = func_151559FC(&sp.uA0, var_v0_3 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 &= 0xFFF9;
    sp.uA0 = -25.0f;
    sp.uA4 = -25.0f;
    if (temp_s0 != 0) {
        var_v0_4 = 4;
    } else {
        var_v0_4 = 0;
    }
    temp_v0_3 = func_151559FC(&sp.uA0, var_v0_4 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u44, 0x58U);
    }
    sp.uB4 = (sp.uB4 & 0xFFF9) | 2;
    sp.uA0 = 25.0f;
    sp.uA4 = -25.0f;
    if (temp_s0 != 0) {
        var_v0_5 = 4;
    } else {
        var_v0_5 = 0;
    }
    temp_v0_4 = func_151559FC(&sp.uA0, var_v0_5 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_4 != 0) {
        memcpy(temp_v0_4 + 0x70, &sp.u44, 0x58U);
    }
    sp.uA0 = 0.0f;
    sp.uA4 = 0.0f;
    sp.uAC = 3.0f;
    sp.uA8 = 3.0f;
    sp.uB0 = 0x99;
    sp.uB4 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uD0 = 8;
    sp.uD4 = 0x44;
    sp.u6C = 99999.0f;
    if (D_80082FA0 == 1) {
        sp.u5C = -62.0f;
    } else {
        sp.u5C = -50.0f;
    }
    sp.u60 = 0.0f;
    if (D_80082FA0 == 1) {
        sp.u64 = 0.016129032f;
    } else {
        sp.u64 = 0.02f;
    }
    var_s0 = 0;
    sp.u68 = 0.0f;
    do {
        var_v0 = func_151559FC(&sp.uA0, 7, 0, 0, 0x58, 0xFF, 1);
        if (var_v0 != 0) {
            var_v0 = memcpy(var_v0 + 0x70, &sp.u44, 0x58U);
        }
        var_s0 += 1;
        sp.u68 += 0.5235988f;
    } while (var_s0 != 0xC);
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CAC50.s")
#endif
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

#ifdef NON_MATCHING
s32 func_151604E4(s8 *, s32, s32, s32);

s32 func_151CB2D8(u8 *arg0, u8 arg1) {
    struct {
        u8 * u30;
        u8 * u34;
        s32 u38;
        s32 u3C;
        s32 u40;
        s8 u44;
        s8 u45;
        s8 u46;
        u8 pad47[0x1];
        s16 u48;
        s8 u4A;
        u8 pad4B[0x1];
        u8 * u4C;
        f32 u50;
        f32 u54;
        s8 u58;
        s8 u59;
        u8 pad5A[0x4E];
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
        s8 uB8;
        u8 padB9[0x1];
        s16 uBA;
        u16 uBC;
        s16 uBE;
        s16 uC0;
        s8 uC2;
        s8 uC3;
        s8 uC4;
        s8 uC5;
        s8 uC6;
        s8 uC7;
        s8 uC8;
        s8 uC9;
        s8 uCA;
        s8 uCB;
        s32 uCC;
        s32 uD0;
        s32 uD4;
        s32 uD8;
        s32 uDC;
        s32 uE0;
        s32 uE4;
        s8 uE8;
        s8 uE9;
        u8 padEA[0x2];
        u8 uEC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u16 temp_t2;
    u16 temp_t6;
    u8 *temp_t5;

    sp.u59 = 0;
    sp.u58 = 0;
    sp.uB4 = 25.0f;
    sp.uB0 = 25.0f;
    sp.u4C = arg0;
    sp.u50 = 0.0f;
    sp.u54 = 130.0f;
    if (D_80082FA0 > 0) {
        sp.uB8 = 0x72;
    } else {
        sp.uB8 = 0x65;
    }
    sp.uBA = 0x12C;
    temp_t6 = (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB)) | 0x50;
    sp.uBE = 1;
    sp.uC2 = 7;
    sp.uC4 = 0xFF;
    sp.uC6 = 0x82;
    sp.uC8 = 0xFF;
    sp.uC7 = 0xFF;
    sp.uC9 = 0xFF;
    sp.uCA = 0xFF;
    sp.uD8 = 8;
    sp.uE0 = 0x80;
    sp.uBC = temp_t6;
    sp.uC0 = 0xFF;
    sp.uC3 = 0;
    sp.uC5 = 0;
    sp.uCB = 0xFF;
    sp.uCC = 0;
    sp.uD0 = 0x200004;
    sp.uD4 = 0x1F0601;
    sp.uDC = 0x44;
    sp.uE4 = 0x20;
    sp.uE8 = 0;
    sp.uE9 = 0xA;
    temp_t2 = temp_t6 & 0xFFF9;
    sp.uBC = temp_t2;
    sp.uBC = temp_t2 | 6;
    sp.uA8 = 25.0f;
    sp.uAC = 25.0f;
    sp.uEC = (*(u8 *)((u8 *)arg0 + 0x23D));
    if (arg1 != 0) {
        var_v0_2 = 4;
    } else {
        var_v0_2 = 0;
    }
    temp_v0 = func_151559FC(&sp.uA8, var_v0_2 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC = (sp.uBC & 0xFFF9) | 4;
    sp.uA8 = -25.0f;
    sp.uAC = 25.0f;
    if (arg1 != 0) {
        var_v0_3 = 4;
    } else {
        var_v0_3 = 0;
    }
    temp_v0_2 = func_151559FC(&sp.uA8, var_v0_3 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC &= 0xFFF9;
    sp.uA8 = -25.0f;
    sp.uAC = -25.0f;
    if (arg1 != 0) {
        var_v0_4 = 4;
    } else {
        var_v0_4 = 0;
    }
    temp_v0_3 = func_151559FC(&sp.uA8, var_v0_4 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u4C, 0x58U);
    }
    sp.uBC = (sp.uBC & 0xFFF9) | 2;
    sp.uA8 = 25.0f;
    sp.uAC = -25.0f;
    if (arg1 != 0) {
        var_v0_5 = 4;
    } else {
        var_v0_5 = 0;
    }
    var_v0 = func_151559FC(&sp.uA8, var_v0_5 & 0xFF, 0, 0, 0x58, 0xFF, 1);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x70, &sp.u4C, 0x58U);
    }
    if (D_800BE616 == 0) {
        sp.u30 = arg0;
        temp_t5 = ((*(u8 *)((u8 *)arg0 + 0x23D)) * 0x180) + D_800BE628;
        sp.u34 = temp_t5;
        sp.u3C = (s32) ((*(f32 *)((u8 *)temp_t5 + 0x34)) - 12.0f);
        sp.u44 = 0xE;
        sp.u45 = -1;
        sp.u46 = 1;
        sp.u48 = 0x12C;
        sp.u4A = 1;
        sp.u40 = (s32) ((*(f32 *)((u8 *)temp_t5 + 0x38)) - 12.0f) * D_800BE620;
        var_v0 = func_151604E4(&sp.u44, 0x498, 0xFF, 1);
        if (var_v0 != 0) {
            sp.u38 = var_v0 + 0x30;
            var_v0 = memcpy(var_v0 + 0x18, &sp.u30, 0x14U);
        }
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB2D8.s")
#endif
#ifdef NON_MATCHING
extern u8 D_800BEAC0;
extern u8 D_800BEAC1;
extern u8 D_800BEEE2;
extern s32 D_800BE620;
f32 func_15145A0C(f32, f32, f32);

/*
 * fb_lens_warp_draw: framebuffer handler 1 of the type-0x34 effect list (called through D_8008B478 by
 * func_15160310 just before the buffer swap, args (effect, framebuffer)). Saves the 24x24 pixel block at
 * effect+0x24 + effect+0x28 into the effect's buffer (effect+0x20), then writes it back mirrored in the four
 * quadrants around the target's screen point (target = effect+0x1C, x / y floats at +0x34 / +0x38) with a
 * radial lens falloff from func_15145A0C, sampling the saved block at 12 + offset * scale.
 * Skipped while D_800BEAC0 / D_800BEAC1 / D_800BEEE2 are set.
 */
void func_151CB6C0(u8 *arg0, u16 *fb) {
    u8 *target;
    u16 *buf;
    s32 src;
    s32 i;
    f32 y, x;
    f32 ry, inv, k;
    f32 r, s;
    f32 dy, dx, sx, sy;
    s32 rowA, rowB, colA, colB;
    s32 u0, u1, v0, v1;

    if (D_800BEAC0 != 0 || D_800BEAC1 != 0 || D_800BEEE2 != 0) {
        return;
    }
    target = *(u8 **)(arg0 + 0x1C);
    src = *(s32 *)(arg0 + 0x24) + *(s32 *)(arg0 + 0x28);
    for (i = 0; i < 24; i++) {
        memcpy(*(u16 **)(arg0 + 0x20) + i * 24, fb + src, 48);
        src += D_800BE620;
    }
    for (y = -1.0f; y < 0.0f; y += 0.083333336f) {
        ry = func_15145A0C(fabsf(y), 1.0f, 1.0f);
        if (ry == 0.0f) {
            continue;
        }
        dy = y * 12.0f;
        rowA = (s32)(*(f32 *)(target + 0x38) + dy) * D_800BE620;
        rowB = (s32)(*(f32 *)(target + 0x38) - dy) * D_800BE620;
        x = -ry;
        if (!(x < 0.0f)) {
            continue;
        }
        inv = 1.0f / ry;
        k = 1.0f - (1.0f - ry * 0.669312179f);
        do {
            r = func_15145A0C(fabsf(x), ry, inv);
            dx = x * 12.0f;
            colA = (s32)(*(f32 *)(target + 0x34) + dx);
            colB = (s32)(*(f32 *)(target + 0x34) - dx);
            s = 1.0f - r * k;
            sx = x * s * 12.0f;
            sy = y * s * 12.0f;
            u0 = (s32)(sx + 12.0f);
            v0 = (s32)(sy + 12.0f) * 24;
            u1 = (s32)(12.0f - sx);
            v1 = (s32)(12.0f - sy) * 24;
            buf = *(u16 **)(arg0 + 0x20);
            fb[rowA + colA] = buf[u0 + v0];
            fb[rowA + colB] = buf[u1 + v0];
            fb[rowB + colB] = buf[u1 + v1];
            fb[rowB + colA] = buf[u0 + v1];
            x += 0.083333336f;
        } while (x < 0.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CB6C0.s")
#endif

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

#ifdef NON_MATCHING
s32 func_151CC210(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;

    temp_f0 = func_151CC784(arg0);
    if (temp_f0 != (*(f32 *)((u8 *)(&arg0[0x70]) + 0x28))) {
        temp_f2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x4C));
        (*(f32 *)((u8 *)(&arg0[0x70]) + 0x28)) = temp_f0;
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((temp_f2 - ((temp_f0 - (*(f32 *)((u8 *)(&arg0[0x70]) + 0x18))) * (*(f32 *)((u8 *)(&arg0[0x70]) + 0x20)) * temp_f2)) + 1.0f);
    }
    if ((*(u8 *)((u8 *)(&arg0[0x70]) + 0xC)) & 2) {
        (*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) = (f32) ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) - D_800BE9A4);
        temp_f18 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x50));
        if (temp_f18 <= 0.0f) {
            (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x3C));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x40));
            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x44));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) (u32) (*(f32 *)((u8 *)(&arg0[0x70]) + 0x48));
            (*(s8 *)((u8 *)(&arg0[0x70]) + 0xC)) = (s8) ((*(u8 *)((u8 *)(&arg0[0x70]) + 0xC)) & 0xFFFD);
        } else {
            temp_f0_2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x3C));
            (*(s8 *)((u8 *)arg0 + 0x2B)) = (s8) (u32) (temp_f0_2 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x2C)) - temp_f0_2) * (temp_f18 * 0.028571429f)));
            temp_f2_2 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x40));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) (u32) (temp_f2_2 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x30)) - temp_f2_2) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
            temp_f12 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x44));
            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (u32) (temp_f12 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x34)) - temp_f12) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
            temp_f14 = (*(f32 *)((u8 *)(&arg0[0x70]) + 0x48));
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) (u32) (temp_f14 + (((*(f32 *)((u8 *)(&arg0[0x70]) + 0x38)) - temp_f14) * ((*(f32 *)((u8 *)(&arg0[0x70]) + 0x50)) * 0.028571429f)));
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC210.s")
#endif
#ifdef NON_MATCHING
/*
 * obj_height_in_range: P190. A height clamped to [obj +0x88, obj +0x8C]: with flag 4 of obj[0x7C] the point
 * D_800C3958[(s8)obj[0xC4]] +0x28 percent of the way from +0x88 to +0x8C, else the middle of +0x19C / +0x1A0 of
 * the object at obj +0x70.
 */
f32 func_151CC784(u8 *arg0) {
    f32 lo, hi, h;
    u8 *o;

    if (arg0[0x7C] & 4) {
        lo = *(f32 *)(arg0 + 0x88);
        h = lo + (*(f32 *)(arg0 + 0x8C) - lo) * (*(f32 *)((u8 *)D_800C3958 + (s8)arg0[0xC4] * 0x44 + 0x28) * 0.01f);
    } else {
        o = *(u8 **)(arg0 + 0x70);
        lo = *(f32 *)(arg0 + 0x88);
        h = (*(f32 *)(o + 0x19C) + *(f32 *)(o + 0x1A0)) * 0.5f;
    }
    if (h < lo) {
        return lo;
    }
    hi = *(f32 *)(arg0 + 0x8C);
    if (hi < h) {
        return hi;
    }
    return h;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC784.s")
#endif

void func_151CC840(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_15155C9C((f32 *) &sp1C, 0x46);
}

#ifdef NON_MATCHING
// glow_colour_on_message: message handler (same table row as func_151CBEC8). On message 0x46 whose key (*arg1)
// matches the record's (+0x70): sets flag 2 at +0x7C, the fade value +0xC0 to 35, and copies the four colour floats
// +0x9C .. +0xA8 (as u32 bytes) to the colour bytes +0x2B .. +0x2E.
void func_151CC86C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *rec = arg0 + 0x70;

    if (arg2 != 0x46 || *(s32 *) arg1 != *(s32 *) rec) {
        return;
    }
    rec[0xC] |= 2;
    *(f32 *) (rec + 0x50) = 35.0f;
    arg0[0x2B] = (u32) *(f32 *) (rec + 0x2C);
    arg0[0x2C] = (u32) *(f32 *) (rec + 0x30);
    arg0[0x2D] = (u32) *(f32 *) (rec + 0x34);
    arg0[0x2E] = (u32) *(f32 *) (rec + 0x38);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CC86C.s")
#endif

#ifdef NON_MATCHING
void func_151CCAD4(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    struct {
        u8 * u2C;
        f32 u30;
        f32 u34;
        s8 u38;
        s8 u39;
        u8 pad3A[0x4E];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        s16 u9E;
        s16 uA0;
        s8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        u8 uCC;
        u8 padCD[0x3];
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    sp.u30 = 0.0f;
    sp.u39 = 0;
    sp.u38 = 0;
    sp.uD8 = 0.0f;
    sp.uDC = 0.0f;
    sp.u9A = 0x12C;
    sp.u2C = arg0;
    sp.u34 = 130.0f;
    if (arg4 != 0) {
        var_v0 = 0x40;
    } else {
        var_v0 = 0;
    }
    sp.u9E = 1;
    sp.u9C = var_v0 | 0x390 | (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB));
    sp.uA3 = arg1;
    sp.uA4 = arg2;
    sp.uA2 = 7;
    sp.uA6 = 0x82;
    sp.uA7 = 0xFF;
    sp.uA8 = 0xFF;
    sp.uA9 = 0xFF;
    sp.uA5 = arg3;
    sp.uA0 = 0xFF;
    sp.uAA = 0xFF;
    sp.uAB = 0xFF;
    sp.uAC = 0;
    sp.uB0 = 0x200004;
    sp.uB4 = 0x1F0601;
    sp.uB8 = 8;
    sp.uBC = 0x44;
    sp.uC0 = 0x80;
    sp.uC4 = 0x20;
    sp.uC8 = 0;
    sp.uC9 = 0xA;
    sp.u98 = 0x9A;
    sp.u88 = 0.0f;
    sp.uD0 = 0.2f;
    sp.uCC = (*(u8 *)((u8 *)arg0 + 0x23D));
    sp.uD4 = 1.0f;
    sp.u90 = 28.0f;
    sp.u94 = 4.2f;
    sp.u8C = -37.0f;
    temp_v0 = func_151559FC(&sp.u88, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9B;
    sp.u8C = 0.0f;
    sp.uD0 = 1.0f;
    sp.uD4 = 0.2f;
    sp.u90 = 4.2f;
    sp.u94 = 28.0f;
    sp.u88 = -37.0f;
    temp_v0_2 = func_151559FC(&sp.u88, 9, 0, 0, 0x58, (s32) arg5, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u2C, 0x58U);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCAD4.s")
#endif
#ifdef NON_MATCHING
void func_15145974(void *, f32 *, f32 *);

s32 func_151CCD2C(u8 *arg0) {
    struct {
        f32 u20;
        f32 u24;
    } sp;
    s32 temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)((*(u8 **)((u8 *)arg0 + 0x70))) + 0x3D0));
    if (temp_v1 == NULL) {
        return 0;
    }
    temp_v0 = (*(s32 *)((u8 *)temp_v1 + 0x31C));
    if (temp_v0 == 0) {
        return 0;
    }
    func_15145974(temp_v0 + 0x130, &sp.u24, &sp.u20);
    if ((*(u8 *)((u8 *)arg0 + 0x20)) == 0x9A) {
        (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) (2.0f * -(sp.u24 * 0.0027777778f * 2560.0f));
        return 1;
    }
    (*(f32 *)((u8 *)arg0 + 0x64)) = (f32) (2.0f * (sp.u20 * 0.0027777778f * 2560.0f));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCD2C.s")
#endif
#ifdef NON_MATCHING
s32 func_151CCDF0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct {
        u8 * u2C;
        f32 u30;
        f32 u34;
        s8 u38;
        s8 u39;
        u8 pad3A[0x4E];
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        u16 u9C;
        s16 u9E;
        s16 uA0;
        s8 uA2;
        u8 uA3;
        u8 uA4;
        u8 uA5;
        s8 uA6;
        s8 uA7;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s32 uAC;
        s32 uB0;
        s32 uB4;
        s32 uB8;
        s32 uBC;
        s32 uC0;
        s32 uC4;
        s8 uC8;
        s8 uC9;
        u8 padCA[0x2];
        u8 uCC;
    } sp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_v0;
    s32 var_v0_2;

    sp.u30 = 0.0f;
    sp.u39 = 0;
    sp.u38 = 0;
    sp.u9A = 0x12C;
    sp.u2C = arg0;
    sp.u34 = 130.0f;
    if ((u8) arg4 != 0) {
        var_v0_2 = 0x40;
    } else {
        var_v0_2 = 0;
    }
    sp.u9E = 1;
    sp.u9C = var_v0_2 | 0x10 | (1 << ((*(u8 *)((u8 *)arg0 + 0x23D)) + 0xB));
    sp.uA3 = (u8) arg1;
    sp.uA4 = (u8) arg2;
    sp.uA2 = 7;
    sp.uA6 = 0xB4;
    sp.uA7 = 0xFF;
    sp.uA8 = 0xFF;
    sp.uA9 = 0xFF;
    sp.uA5 = (u8) arg3;
    sp.uA0 = 0xFF;
    sp.uAA = 0xFF;
    sp.uAB = 0xFF;
    sp.uAC = 0;
    sp.uB0 = 0x200004;
    sp.uB4 = 0x1F0601;
    sp.uB8 = 8;
    sp.uBC = 0x44;
    sp.uC0 = 0x80;
    sp.uC4 = 0x20;
    sp.uC8 = 0;
    sp.uC9 = 0xA;
    sp.u88 = 0.0f;
    sp.u8C = 0.0f;
    sp.u98 = 0x64;
    sp.uCC = (*(u8 *)((u8 *)arg0 + 0x23D));
    sp.u94 = 12.0f;
    sp.u90 = 12.0f;
    temp_v0 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0 != 0) {
        memcpy(temp_v0 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9D;
    sp.u9C &= 0xFFF9;
    sp.u94 = 7.0f;
    sp.u90 = 7.0f;
    sp.u88 = 55.0f;
    sp.u8C = 0.0f;
    temp_v0_2 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_2 != 0) {
        memcpy(temp_v0_2 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 2;
    sp.u88 = -55.0f;
    sp.u8C = 0.0f;
    temp_v0_3 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_3 != 0) {
        memcpy(temp_v0_3 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9C;
    sp.u9C = (sp.u9C & 0xFFF9) | 4;
    sp.u88 = 0.0f;
    sp.u8C = 55.0f;
    temp_v0_4 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_4 != 0) {
        memcpy(temp_v0_4 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C &= 0xFFF9;
    sp.u88 = 0.0f;
    sp.u8C = -55.0f;
    temp_v0_5 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_5 != 0) {
        memcpy(temp_v0_5 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u98 = 0x9E;
    sp.u9C |= 6;
    sp.u94 = 6.0f;
    sp.u90 = 6.0f;
    sp.u88 = 44.0f;
    sp.u8C = 44.0f;
    temp_v0_6 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_6 != 0) {
        memcpy(temp_v0_6 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 4;
    sp.u88 = -44.0f;
    sp.u8C = 44.0f;
    temp_v0_7 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_7 != 0) {
        memcpy(temp_v0_7 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C &= 0xFFF9;
    sp.u88 = -44.0f;
    sp.u8C = -44.0f;
    temp_v0_8 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (temp_v0_8 != 0) {
        memcpy(temp_v0_8 + 0x70, &sp.u2C, 0x58U);
    }
    sp.u9C = (sp.u9C & 0xFFF9) | 2;
    sp.u88 = 44.0f;
    sp.u8C = -44.0f;
    var_v0 = func_151559FC(&sp.u88, 0, 0, 0, 0x58, (s32) (u8) arg5, 1);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x70, &sp.u2C, 0x58U);
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1F7960/func_151CCDF0.s")
#endif
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
