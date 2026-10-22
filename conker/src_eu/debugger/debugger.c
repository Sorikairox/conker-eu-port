#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
u8 *func_160014F0(s16 *arg0, s32 arg1);
void func_16001678(void);
#endif

s32 func_1600160C(s32);
void func_16001044(s32 arg0, s32 arg1, s32 arg2);


void func_16000000(void) {
    func_160012B0(278, &D_160046AC);
}

s32 func_16000028(void) {
    if (D_16003890 & 0xC000) {
        D_16003AF4 = 1;
        return 3;
    }
    return 0;
}

void func_16000058(void) {
    s32 i;
    s32 phi_s2;

    func_16001338(255, 255, 255);
    func_160012B0(44, &D_160046D0); // "MAIN MENU"
    phi_s2 = 108;
    for(i = 0; i < 2; i++) {
        if (D_16003B1C == i) {
            func_16001338(255, 0, 0);     // red
        } else {
            func_16001338(255, 255, 255); // white
        }
        func_160012B0(phi_s2, D_16003B20[i]);
        phi_s2 += 32;
    }
    if (D_16003B1C == 2) {
        func_16001338(255, 0, 0);     // red
    } else {
        func_16001338(255, 255, 255); // white
    }
    if (D_16003AF0 != 0) {
        if ((D_1600389C->unk120 == 32) && (D_160038A4 == 0)) {
            func_160012B0(phi_s2, &D_160046DC);
        } else if (D_16003AF0 != 0) {
            func_160012B0(phi_s2, &D_160046E8);
        }
    } else {
        func_160012B0(phi_s2, &D_160046F4); // "RETRY CODE"
    }
    func_16001338(255, 255, 255);
    func_160012B0(611, &D_16004700); // "Version"
    func_16001044(619, 1, 19);
    func_160012B0(643, &D_16004708); // "Built"
    func_160012B0(651, &D_16004710); // "Dec 19 2000"
    func_160012B0(663, &D_1600471C); // "09:57:42"
}

s32 func_16000224(void) {
    s32 res = 0;

    if (D_16003890 & 0x40000) { // D_JPAD is 0x0400
        D_16003B1C -= 1;
        res = 1;
    }
    if (D_16003890 & 0x80000) { // U_JPAD is 0x0800
        D_16003B1C += 1;
        res = 1;
    }
    if (D_16003B1C >= 3) {
        D_16003B1C = 0;
    }
    if (D_16003B1C < 0) {
        D_16003B1C = 2;
    }
    if (D_16003890 & A_BUTTON) {
        switch(D_16003B1C) {
            case 0:
                res = 3;
                D_16003AF4 = 2;
                break;
            case 1:
                res = 3;
                D_16003AF4 = 3;
                break;
            case 2:
                res = 4;
                break;
        }
    }
    return res;
}

void func_16000304(void) {
}

void func_1600030C(void) {
}

void func_16000314(void) {
    switch(D_16003B28) {
        case 0:
            func_16000424(D_1600389C);
            func_160006CC(D_1600389C);
            break;
        case 1:
        case 2:
            func_16000590(D_1600389C);
            break;
    }
}

s32 func_16000384(void) {
    s32 res = 0;

    if (D_16003890 & (R_CBUTTONS | D_CBUTTONS)) {
        D_16003B28 += 1;
        if (D_16003B28 >= 3) {
            D_16003B28 = 0;
        }
        return 3;
    }
    if (D_16003890 & (L_CBUTTONS | U_CBUTTONS)) {
        D_16003B28 -= 1;
        if (D_16003B28 < 0) {
            D_16003B28 = 2;
        }
        return 3;
    }
    if (D_16003890 & B_BUTTON) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

void func_16000424(struct118 *arg0) {
    // TODO is this a RGB struct?
    u32 tmp0;
    u32 tmp1;
    s32 pad;

    func_16001338(255, 255, 255);
    func_160012B0(35, &D_16004728);     // "Pc"
    func_16001044(43, 0, arg0->unk11C);
    func_160012B0(67, &D_1600472C);     // "Cause"
    func_16001044(75, 0, arg0->unk120);
    func_16001338(128, 128, 255);
    tmp0 = arg0->unk120;
    tmp1 = (tmp0 >> 2) & 0xF;

    func_160012B0(107, D_16003848[tmp1]);
    if (tmp1 == 11) {
        func_16001044(111, 1, (tmp0 >> 28) & 3);
    }
    func_16001338(255, 255, 255);
    func_160012B0(131, &D_16004734);      // "Sr"
    func_16001044(139, 0, arg0->unk118);
    func_160012B0(163, &D_16004738);      // "Badvadr"
    func_16001044(171, 0, arg0->unk124);
    func_160012B0(195, &D_16004740);      // "Thread"
    func_16001044(203, 1, arg0->unk14);
    if (D_160038A4 != 0) {
        func_160012B0(52, &D_16004748);   // "Lockup_Now"
    }
}

#ifdef NON_MATCHING
void func_16000590(struct118 *arg0) {
    s32 temp_s2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_v0;
    u32 var_s2;
    u8 *var_s3;

    var_s4 = 0;
    temp_s2 = (*(s32 *)((u8 *)arg0 + 0x12C));
    func_160012B0(3, D_160047A4);
    func_16001044(0xA, 0, temp_s2);
    var_s2 = (u32) temp_s2 >> 0xC;
    var_s0 = 0x2C;
    var_s1 = 0;
    do {
        if (var_s2 & 1) {
            func_160012B0(var_s0, (u8 *) D_16003B30[var_s1]);
            var_s0 += 0x20;
        }
        var_s1 += 1;
        var_s2 = var_s2 >> 1;
    } while (var_s1 < 6);
    var_s1_2 = 0;
    var_s0_2 = 0xC3;
    if (D_16003B28 == 1) {
        var_v0 = 0x4C;
    } else {
        var_v0 = 0x6C;
        var_s4 = 0x10;
    }
    var_s2_2 = var_s4;
    var_s3 = ((struct118 *)((u8 *)arg0 + (var_v0 * 4)));
    do {
        func_160012B0(var_s0_2, D_160047AC);
        func_16001044(var_s0_2 + 2, 1, var_s2_2);
        func_16001044(var_s0_2 + 5, 2, (*(s32 *)((u8 *)var_s3 + 4)));
        var_s1_2 += 1;
        var_s3 += 8;
        var_s0_2 += 0x20;
        var_s2_2 += 1;
    } while (var_s1_2 < 0x10);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000590.s")
#endif
typedef struct {
    u8 c[4];
} struct_16003B48;
extern struct_16003B48 D_16003B48;
extern u8 D_160037F0[];

void func_160006CC(struct118 *arg0) {
    struct_16003B48 name;
    s32 pad;
    s32 pos = 0x123;
    u8 *p = D_160037F0;
    s32 idx;

    name = D_16003B48;
    func_16001338(0xC0, 0xC0, 0xFF);
    do {
        name.c[0] = p[0];
        name.c[1] = p[1];
        func_160012B0(pos, name.c);
        pos += 3;
        idx = p[2];
        func_16001044(pos, 0, ((s32 *)arg0)[idx + 1]);
        pos += 0xD;
        p += 3;
    } while (p[0] != 0);
}
extern u8 D_8002D810[];
extern u8 D_8002DC10[];

void func_1600078C(void)
{
    u32 mask;
  s32 base;
  u32 addr;
  u32 lo;
  s32 x;
  u32 i;
  u32 val;
  u8 prefix;
  base = *((s32 *) (((u8 *) D_1600389C) + 0xF4));
  func_16001338(0, 255, 0);
  func_160012B0(11, D_160047B0);
  addr = 4;
  addr = (D_16003B4C * addr) + base;
  i = 3;
  if ((((((char) addr) & i) == 0) && (addr >= 0x80000000U)) && (addr < 0x80800001U))
  {
    if (D_16003B4C == 0)
    {
      func_16001338(255, 0, 0);
      lo = (u32) D_8002D810;
    }
    else
    {
      lo = (u32) D_8002D810;
      if ((addr >= lo) && (addr < (lo + 0x400)))
      {
        func_16001338(128, 128, 255);
      }
      else
        if ((addr >= ((u32) D_8002DC10)) && (addr < (((u32) D_8002DC10) + 0x4000)))
      {
        func_16001338(255, 128, 128);
      }
      else
      {
        func_16001338(255, 255, 255);
      }
    }
    x = 0x61;
    for (i = 0; i < 22; i++)
    {
      func_16001044(x, 0, addr);
      func_160012B0(x + 8, D_160047BC);
      val = *((u32 *) addr);
      prefix = val >> 24;
      if (prefix == 0x80)
      {
        func_16001338(128, 128, 255);
      }
      else
        if (prefix == 0x15)
      {
        func_16001338(255, 0, 0);
      }
      else
        if (prefix == 0x16)
      {
        func_16001338(128, 255, 128);
      }
      else
        if (prefix == 0x10)
      {
        func_16001338(255, 0, 0);
      }
      else
      {
        func_16001338(255, 255, 255);
      }
      mask = 0xFFFFFFFFu; // fakematch: an all-ones mask in a register (permuter)
      func_16001044(x + 0xC, 0, val);
      func_160012B0((x + 0x16) & mask, D_160047C0);
      func_16001338(255, 255, 255);
      func_16001044(x + 0x16, 1, val);
      if ((addr >= lo) && (addr < (lo + 0x400)))
      {
        func_16001338(128, 128, 255);
      }
      else
        if ((addr >= ((u32) D_8002DC10)) && (addr < (((u32) D_8002DC10) + 0x4000)))
      {
        func_16001338(255, 128, 128);
      }
      else
      {
        func_16001338(255, 255, 255);
      }
      x += 0x20;
      addr += 4;
    }

 dummy_label_509389: ; // fakematch: permuter label
  }
}
// NON-MATCHING: close but still some stuff to figure out
// void func_1600078C(void) {
//     s32 temp_s0;
//     u8 range_prefix;
//     u32 temp_s2;
//     s32 temp_s5;
//     s32 phi_s1;
//     u32 *phi_s2;
//     u32 phi_s5;
//     s32 i;
//
//     temp_s0 = D_1600389C->unkF4;
//     func_16001338(0, 255, 0); // green
//     func_160012B0(11, &D_160047B0);
//     temp_s2 = (D_16003B4C * 4) + temp_s0;
//     if (((temp_s2 & 3) == 0) && (temp_s2 >= 0x80000000U) && (temp_s2 < 0x80800001U)) {
//         if (D_16003B4C == 0) {
//             func_16001338(255, 0, 0); // red
//             phi_s5 = &D_8002D4B0;
//         } else {
//             temp_s5 = &D_8002D4B0 - 0x2B50; // 11088 ?
//             if ((temp_s2 >= temp_s5) && (temp_s2 < (temp_s5 + 0x400))) {
//                 func_16001338(128, 128, 255); // purple
//                 phi_s5 = temp_s5;
//             } else if ((temp_s2 >= (u32) &D_8002D8B0) && (temp_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128); // light red
//                 phi_s5 = temp_s5;
//             } else {
//                 func_16001338(255, 255, 255);
//                 phi_s5 = temp_s5;
//             }
//         }
//         phi_s1 = 97; // "a"
//         phi_s2 = temp_s2;
//         for (i = 0; i < 22; i++) {
//             func_16001044(phi_s1, 0, phi_s2);
//             func_160012B0(phi_s1 + 8, &D_160047BC);
//             range_prefix = (*phi_s2 >> 24);
//             if (range_prefix == 0x80) {                   // 0x80000000
//                 func_16001338(128, 128, 255);
//             } else if (range_prefix == 0x15) {            // 0x15000000
//                 func_16001338(255, 0, 0);
//             } else if (range_prefix == 0x16) {            // 0x16000000
//                 func_16001338(128, 255, 128);
//             } else if (range_prefix == 0x10) {            // 0x10000000
//                 func_16001338(255, 0, 0);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             func_16001044(phi_s1 + 0xC, 0, *phi_s2);
//             func_160012B0(phi_s1 + 0x16, &D_160047C0);
//             func_16001338(255, 255, 255);
//             func_16001044(phi_s1 + 0x16, 1, *phi_s2);
//             if (((u32) phi_s2 >= phi_s5) && ((u32) phi_s2 < (phi_s5 + 0x400))) {
//                 func_16001338(128, 128, 0xFF);
//             } else if (((u32) phi_s2 >= (u32) &D_8002D8B0) && ((u32) phi_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             phi_s1 += 0x20;
//             phi_s2 += 4;
//         }
//     }
// }

s32 func_16000A5C(void) {
    s32 res = 0;

    if ((D_160036F3 >= 41) || (D_16003890 & U_CBUTTONS)) {
        D_16003B4C -= 1;
        if (D_16003B4C < 0) {
            D_16003B4C = 0;
        } else {
            res = 3;
        }
    } else if ((D_160036F3 < -40) || (D_16003890 & D_CBUTTONS)) {
        D_16003B4C += 1;
        if (D_16003B4C >= 201) {
            D_16003B4C = 200;
        }
        res = 3;
    }
    if ((D_16003890 & B_BUTTON)) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

// called from func_10007DAC
#ifdef NON_MATCHING
s32 func_16001700(void);
void func_16001830(void *);
s32 func_16003650();
extern s32 D_16003894;
extern s32 D_16003898;
extern s32 D_160038AC;
extern s32 D_1600392C;
extern s32 D_160039AC;
extern s32 D_160039E8;
extern s32 D_16003A2C;
extern s32 D_16003A68;
extern s32 D_16003AF8;
extern s32 D_16003B08;
extern u8 *D_8002C130;
extern s32 D_8003CC88;
void func_150ADC50(void); /* code (asm/D5E90.s), compared by address below */
extern s32 func_160036F0;

s32 func_16000B14(OSThread *arg0) {
    s32 sp40;
    s32 (*temp_v0)();
    s32 *var_a0;
    s32 (*temp_v1)();
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t4;
    s32 temp_t5;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    u32 temp_t1;

    var_s3 = 0;
    sp40 = 1;
    if (D_8002AC5C != 0) {
        return 0;
    }
    D_16003888 = 0;
    if (((*(s32 *)((u8 *)D_8002AAE8 + 0)) == 0) || (D_8002AAE8[1] == 0)) {
        (*(s32 *)((u8 *)D_8002AAE8 + 0)) = 0x80350000;
        D_8002AAE8[1] = 0x80350000;
        return 0;
    }
    func_16003650();
    (*(s32 *)((u8 *)(&D_160038AC) + 0x3C)) = (s32) (*(s32 *)((u8 *)(&D_8003CC88) + 0));
    (*(s32 *)((u8 *)(&D_1600392C) + 0x3C)) = (s32) (*(s32 *)((u8 *)(&D_8003CC88) + 4));
    D_160039E8 = (*(s32 *)((u8 *)(&D_8003CC88) + 8));
    D_16003A68 = (*(s32 *)((u8 *)(&D_8003CC88) + 0xC));
    temp_t1 = arg0->context.pc;
    if ((temp_t1 & 0xFF000000) != 0x15000000) {
        D_16003AF0 = 1;
    } else {
        temp_a1 = temp_t1 & ~0xFFF;
        temp_a2 = temp_a1 & 0x1000;
        temp_t4 = temp_a1 & ~0x1000;
        D_16003AF0 = 0;
        var_a0 = &D_160039AC;
        var_v1 = 0;
        do {
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 0))) {
                if (temp_a2 != 0) {
                    var_v0_2 = *(&D_1600392C + var_v1);
                } else {
                    var_v0_2 = *(&D_160038AC + var_v1);
                }
                if (var_v0_2 & 2) {
                    D_16003AF0 = 1;
                }
            }
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 4))) {
                if (temp_a2 != 0) {
                    var_v0_3 = (*(s32 *)((u8 *)((&D_1600392C + var_v1)) + 4));
                } else {
                    var_v0_3 = (*(s32 *)((u8 *)((&D_160038AC + var_v1)) + 4));
                }
                if (var_v0_3 & 2) {
                    D_16003AF0 = 1;
                }
            }
            if (temp_t4 == (*(s32 *)((u8 *)var_a0 + 8))) {
                if (temp_a2 != 0) {
                    var_v0_4 = (*(s32 *)((u8 *)((&D_1600392C + var_v1)) + 8));
                } else {
                    var_v0_4 = (*(s32 *)((u8 *)((&D_160038AC + var_v1)) + 8));
                }
                if (var_v0_4 & 2) {
                    D_16003AF0 = 1;
                }
            }
            temp_t5 = (*(s32 *)((u8 *)var_a0 + 0xC));
            var_a0 += 0x10;
            if (temp_t4 == temp_t5) {
                if (temp_a2 != 0) {
                    var_v0_5 = (*(s32 *)((u8 *)((&D_1600392C + var_v1)) + 0xC));
                } else {
                    var_v0_5 = (*(s32 *)((u8 *)((&D_160038AC + var_v1)) + 0xC));
                }
                if (var_v0_5 & 2) {
                    D_16003AF0 = 1;
                }
            }
            var_v1 += 0x10;
        } while (var_a0 != &D_16003A2C);
    }
    if ((((u32) D_8003C8E0 >> 0x18) & 0xFF) == 0xC) {
        arg0 = &D_80031AE0;
    }
    if ((*(s32 *)((u8 *)D_8002C130 + 4)) == D_8002AAE8[1]) {
        D_16003888 = 1;
    }
    D_1600389C = (struct118 *) arg0;
    D_160038A4 = 0;
    if ((arg0->context.cause == 0x20) && ((s32)func_150ADC50 == arg0->context.pc)) {
        D_160038A4 = 1;
    }
    do {
        if ((sp40 == 0) && (var_s3 & 2)) {
            func_16001678();
        }
        temp_v0 = *(s32 *)((u8 *)&D_16003AF8 + (D_16003AF4 * 4));
        if (temp_v0 != NULL) {
            temp_v0();
        }
        osWritebackDCacheAll();
loop_47:
        var_s3 = 0;
        D_16003898 = D_16003894;
        func_16001700();
        func_16001830(&func_160036F0);
        if (sp40 != 0) {
            D_16003898 = D_16003894;
        }
        D_16003894 = (s32) (*(u16 *)((u8 *)(&func_160036F0) + 0));
        if ((*(s8 *)((u8 *)(&func_160036F0) + 2)) >= 0x33) {
            D_16003894 = (*(u16 *)((u8 *)(&func_160036F0) + 0)) | 0x20000;
        }
        if ((*(s8 *)((u8 *)(&func_160036F0) + 2)) < -0x32) {
            D_16003894 |= 0x10000;
        }
        if ((*(s8 *)((u8 *)(&func_160036F0) + 3)) >= 0x33) {
            D_16003894 |= 0x40000;
        }
        if ((*(s8 *)((u8 *)(&func_160036F0) + 3)) < -0x32) {
            D_16003894 |= 0x80000;
        }
        D_16003890 = (D_16003894 ^ D_16003898) & D_16003894;
        temp_v1 = *(s32 *)((u8 *)&D_16003B08 + (D_16003AF4 * 4));
        if (temp_v1 != NULL) {
            var_s3 = temp_v1();
        }
        if (!(var_s3 & 5)) {
            goto loop_47;
        }
        sp40 = 0;
    } while (!(var_s3 & 4));
    if (D_16003AF0 == 0) {
        arg0->state = 4;
        arg0->flags = 0;
        return 1;
    }
    var_v0 = 0;
    if ((arg0->context.cause == 0x20) && (D_160038A4 == 0)) {
        var_v0 = 1;
        arg0->context.pc += 4;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000B14.s")
#endif
s32 func_16001B34(u8 *, u8 *, u8 *, u8 *, f64);
void func_16000F8C(s32 arg0, f32 arg1)
{
  f32 sp54;
  s32 bits;
  u8 sp28[0x28];
  u32 exp;
  if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 0x341))
  {
    sp54 = arg1;
    bits = *((s32 *) (&sp54));
    exp = ((u32) (bits & 0x7F800000)) >> 0x17;
    do { } while (0); // fakematch: permuter register assignment
    if (((exp == 0) || (exp >= 0xFFU)) && ((bits * 2) != 0))
    {
      if ((!bits) && (!bits)) { } // fakematch: permuter register assignment
      func_160012B0(arg0, D_160047D0);
      return;
    }
    func_16001B34(sp28, D_160047D4, D_160047DC, D_160047E0, (f64) arg1);
    func_160012B0(arg0, sp28);
  }
}
// NON-MATCHING: lots to figure out
// void func_16000F8C(s32 arg0, f32 arg1) {
//     struct165 tmp;
//     s32 temp_v1;
//     u32 temp_t9;
//
//     if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
//         tmp.unk18 = arg1;
//         temp_v1 = *(s32*)&tmp.unk18;
//         temp_t9 = (u32) (temp_v1 & 0x7F800000) >> 0x17;
//         if ((temp_t9 == 0) || (temp_t9 >= 0x255U)) {
//             if ((temp_v1 * 2) != 0) {
//                 func_160012B0(arg1, &D_160047D0); // arg0,
//                 return;
//             }
//         }
//         func_16001B34(&arg0, &tmp.unk0, &D_160047D4, &D_160047DC, &D_160047E0); // , (f64) arg1
//         func_160012B0(arg0, &tmp.unk0);
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16001044.s")

void func_160012B0(s32 arg0, u8 *arg1) {
    if (arg1 && (arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
        s32 fb = func_1600160C(arg0);   /* P80: a0 still holds arg0 at the jal (the text cell) */
        while (*arg1 != 0) {
            fb = func_160014F0(fb, *arg1 & 0xFF);
            *arg1++;
        }
    }
}
// convert rgb to rgba16
void func_16001338(u8 arg0, u8 arg1, u8 arg2) {
    D_1600388C = ((arg0 & 0xF8) << 8) | ((arg1 & 0xF8) << 3) | ((arg2 & 0xF8) >> 2) | 1;
}

void func_16001390(s16 x0, s16 y0, s16 x1, s16 y1) {
    s32 base;
    u16 *fb;
    s32 i;

    if (x1 < x0) {
        return;
    }
    if (y1 < y0) {
        return;
    }
    if (x0 < 0) {
        return;
    }
    if (y0 < 0) {
        return;
    }
    x1++;
    y1++;
    base = func_1600160C(0);
    fb = (u16 *)base + (x0 + y0 * D_160038A8);
    x1 -= x0;
    y1 -= y0;
    for (; y1 > 0;) {
        for (i = x1; i > 0; i--) {
            *fb++ = D_1600388C;
        }
        y1--;
        fb += D_160038A8 - x1;
    }
}
#ifdef NON_MATCHING
extern s32 D_16003CE0;

u8 *func_160014F0(s16 *arg0, s32 arg1) {
    s16 *temp_v0;
    s16 *temp_v0_2;
    s16 *temp_v0_3;
    s16 *var_v0;
    s16 var_t2;
    s16 var_t2_2;
    s16 var_t2_3;
    s16 var_t2_4;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t6;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    u8 *var_t0;
    u8 var_a2_2;

    temp_t6 = arg1 & 0xFF;
    var_v0 = arg0;
    var_a2 = temp_t6;
    if (temp_t6 < 0x20) {
        var_a2 = 0x20;
    }
    var_t0 = ((s32 *)((u8 *)&D_16003CE0 + ((var_a2 - 0x20) * 8)));
    var_a3 = 0;
    do {
        var_a1 = 0;
        var_a2_2 = *var_t0;
loop_4:
        if (var_a2_2 & 0x80) {
            var_t2 = D_1600388C & 0xFFFF;
        } else {
            var_t2 = 1;
        }
        temp_t1 = (var_a2_2 * 2) & 0xFFFF;
        *var_v0 = var_t2;
        temp_v0 = ((s16 *)((u8 *)var_v0 + 2));
        if (temp_t1 & 0x80) {
            var_t2_2 = D_1600388C & 0xFFFF;
        } else {
            var_t2_2 = 1;
        }
        temp_t1_2 = (temp_t1 * 2) & 0xFFFF;
        *temp_v0 = var_t2_2;
        temp_v0_2 = ((s16 *)((u8 *)temp_v0 + 2));
        if (temp_t1_2 & 0x80) {
            var_t2_3 = D_1600388C & 0xFFFF;
        } else {
            var_t2_3 = 1;
        }
        temp_t1_3 = (temp_t1_2 * 2) & 0xFFFF;
        *temp_v0_2 = var_t2_3;
        temp_v0_3 = ((s16 *)((u8 *)temp_v0_2 + 2));
        if (temp_t1_3 & 0x80) {
            var_t2_4 = D_1600388C & 0xFFFF;
        } else {
            var_t2_4 = 1;
        }
        var_a1 += 4;
        var_a2_2 = (temp_t1_3 * 2) & 0xFFFF;
        *temp_v0_3 = var_t2_4;
        var_v0 = ((s16 *)((u8 *)temp_v0_3 + 2));
        if (var_a1 != 8) {
            goto loop_4;
        }
        var_a3 += 1;
        var_t0 += 1;
        var_v0 = (s16 *)((u8 *)var_v0 + ((D_160038A8 - 8) * 2));
    } while (var_a3 != 8);
    return ((s16 *)((u8 *)arg0 + 0x10));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_160014F0.s")
#endif
// NON-MATCHING: only glyph/j registers swapped (t0/a1)
// extern u8 D_16003CE0[];
//
// u16 *func_160014F0(fb, c)
//     u16 *fb;
//     u8 c;
// {
//     u16 *p = fb;
//     s32 color = D_1600388C;
//     u16 bits;
//     u16 val;
//     s32 ch;
//     s32 i;
//     u8 *glyph;
//     s32 j;
//
//     ch = c;
//     if (ch < 0x20) {
//         ch = 0x20;
//     }
//     glyph = D_16003CE0 + ((ch - 0x20) << 3);
//     for (i = 0; i < 8; i++) {
//         bits = *glyph;
//         for (j = 0; j < 8; j++) {
//             if (bits & 0x80) {
//                 val = color;
//             } else {
//                 val = 1;
//             }
//             bits <<= 1;
//             *p++ = val;
//         }
//         glyph++;
//         p += D_160038A8 - 8;
//     }
//     return fb + 8;
// }

// framebuffer address of a text cell
s32 func_1600160C(s32 arg0) {
    s32 y = arg0 & 0xFFE0;
    s32 v1 = y;

    if (D_160038A8 != 0x124) {
        v1 = (y >> 2) + y;
    }
    v1 = (u32)(v1 >> 2) * (D_160038A8 * 2);
    v1 += (arg0 & 0x1F) * 16;
    v1 += D_160038A8 * 4;
    v1 += 0x10;
    return D_8002AAE8[D_16003888] + v1;
}

// clear the framebuffer
void func_16001678(void) {
    u32 *fb = D_8002AAE8[D_16003888];
    s32 h;
    u32 *end;

    if (D_160038A8 == 0x124) {
        h = 0xD7;
    } else {
        h = 0x108;
    }
    end = (u32 *)(((u32)(D_160038A8 >> 1) * h * 4) + (u32)fb);
    while (fb < end) {
        fb[0] = 0x10001;
        fb[1] = 0x10001;
        fb[2] = 0x10001;
        fb[3] = 0x10001;
        fb += 4;
    }
}

s32 func_160016F4(s32 arg0) {
    return arg0;
}
