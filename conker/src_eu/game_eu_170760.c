#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
#endif

void func_15142314(Mtx *, s32, f32 *);

void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *temp_v1 = &D_8008A500[(func_150ADA20() & 3) * 3 + arg0 * 12];

    *arg1 = temp_v1[0];
    *arg2 = temp_v1[1];
    *arg3 = temp_v1[2];
}
s32 func_15142A5C(struct127 *arg0) {
    u8 *temp_v0 = (u8 *)arg0->unk2D0;
    if (*(s16 *)(temp_v0 + 0x3C) > 0) {
        return 1;
    }
    return 0;
}
f32 func_15142A80(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * 0.16666667f;
}
f32 func_15142AC0(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
f32 func_15142B44(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * 0.16666667f;
}
Gfx *func_15142B7C(Gfx *gfx, s32 set, s32 clear) {
    if (~D_800DD630 & clear) {
        gSPClearGeometryMode(gfx++, clear);
        D_800DD630 |= clear;
    }
    if (~D_800DD62C & set) {
        gSPSetGeometryMode(gfx++, set);
        D_800DD62C |= set;
    }
    return gfx;
}
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5) {
    if ((r != D_800DD5F8) || (g != D_800DD5FA) || (b != D_800DD5FC) || (a != D_800DD5FE)) {
        if (*arg5 == 1) {
            gDPPipeSync(gfx++);
            *arg5 = 0;
        }
        gDPSetEnvColor(gfx++, r, g, b, a);
        D_800DD5F8 = r;
        D_800DD5FA = g;
        D_800DD5FC = b;
        D_800DD5FE = a;
    }
    return gfx;
}
Gfx *func_15142CF0(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *arg7) {
    if ((m != D_800DD634) || (l != D_800DD636) || (r != D_800DD5F0) || (g != D_800DD5F2) || (b != D_800DD5F4) || (a != D_800DD5F6)) {
        if (*arg7 == 1) {
            gDPPipeSync(gfx++);
            *arg7 = 0;
        }
        gDPSetPrimColor(gfx++, m, l, r, g, b, a);
        D_800DD634 = m;
        D_800DD636 = l;
        D_800DD5F0 = r;
        D_800DD5F2 = g;
        D_800DD5F4 = b;
        D_800DD5F6 = a;
    }
    return gfx;
}
s32 func_150953F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_1514306C(s32, s32, s32, u8);
extern s32 D_800DD638;
extern s32 D_800DD63C;
extern s32 D_800DD640;
extern s32 D_800DD644;

s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_1514306C(arg1, arg6, arg2 >> 0x10, arg7);
    if ((temp_v0 != D_800DD5E0) || (arg3 != D_800DD638) || (arg4 != D_800DD63C) || (arg5 != D_800DD640) || (arg8 != D_800DD644)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x13) || (D_800BE9F0 == 6) || (D_800BE9F0 == 0x3B) || (D_800BE9F0 == 2) || (D_800BE616 != 0)) {
            argA = 3;
        }
        temp_v0_2 = func_150953F8(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, argA);
        D_800DD5E0 = temp_v0;
        D_800DD638 = arg3;
        D_800DD63C = arg4;
        D_800DD640 = arg5;
        arg0 = temp_v0_2;
        D_800DD644 = D_800DD644;
    }
    return arg0;
}
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3) {
    if ((arg1 != D_800DD648) || (arg2 != D_800DD64C)) {
        if (*arg3 == 1) {
            gDPPipeSync(gfx++);
            *arg3 = 0;
        }
        gDPSetOtherMode(gfx++, arg1 | 0xF, arg2);
        D_800DD648 = arg1;
        D_800DD64C = arg2;
    }
    return gfx;
}
s16 func_15143044(u8 arg0, s32 arg1) {
    return 0x7FFF - arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514306C.s")
void func_15143134(void *arg0, void *arg1, void *arg2) {
    D_800DCE30 = 1;
    if ((arg0 != NULL) && ((((struct17 *)arg0)->unk0 != 0.0f) || (((struct17 *)arg0)->unk4 != 0.0f) || (((struct17 *)arg0)->unk8 != 0.0f))) {
        D_800DCE30 = 2;
        D_800DCE38 = ((struct17 *)arg0)->unk0;
        D_800DCE3C = ((struct17 *)arg0)->unk4;
        D_800DCE40 = ((struct17 *)arg0)->unk8;
        if (D_800C42B0 != 0) {
            f32 mf[4][4];

            D_800DCE30 = 3;
            D_800DCE34 = arg2;
            guMtxL2F(mf, arg2);
            func_150A7E40(mf, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            D_800DCE30 = 4;
        } else {
            D_800DCE30 = 5;
            D_800DCE34 = arg2;
            func_150A7E40(arg2, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            D_800DCE30 = 6;
        }
    } else {
        D_800DCE30 = 7;
        func_15142314(arg2, 0, arg1);
        D_800DCE30 = 8;
    }
    D_800DCE30 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151432BC.s")

// void func_151432BC(struct208 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
//     struct209 tmp;
//     f32 temp_f2;
//     f32 temp_f6;
//     f32 temp_ret;
//     s32 temp_t6;
//     u8 temp_a0;
//
//     temp_t6 = (arg0->unk15) & 3;
//     if (temp_t6 == 0) {
//         tmp.unk1B = func_150ADA20();
//         tmp.unk14 = func_151423D8((tmp.unk1B - 64) & 0xFF);
//         tmp.unk10 = func_151423D8(tmp.unk1B);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk10));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk14));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = arg0->unk2;
//     } else if (temp_t6 != 1) {
//         if (temp_t6 == 2) {
//             tmp.unk2F = (u32) (arg0->unk10 * D_800A5644); // 0.7111111283302307
//             tmp.unk28 = func_151423D8((tmp.unk2F - 64));
//             tmp.unk24 = func_151423D8(tmp.unk2F);
//             tmp.unk20 = (func_150ADA68() * (2.0f * (f32) arg0->unk6)) + (f32) -(s32) arg0->unk6;
//             temp_f2 = (func_150ADA68() * (2.0f * (f32) arg0->unkA)) + (f32) -(s32) arg0->unkA;
//             temp_f6 = temp_f2 * tmp.unk24;
//             *arg1 = (arg0->unk0 + ((tmp.unk20 * tmp.unk24) + (temp_f2 * tmp.unk28)));
//             *arg2 = (arg0->unk4 + (temp_f6 - (tmp.unk20 * tmp.unk28)));
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = arg0->unk2;
//         } else {
//             *arg1 = arg0->unk0;
//             *arg2 = arg0->unk4;
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = (arg0->unk2 - arg0->unk8);
//         }
//     } else {
//         tmp.unkB = func_150ADA20();
//         tmp.unk4 = func_151423D8((tmp.unkB - 64));
//         tmp.unk0 = func_151423D8(tmp.unkB);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * (f32) arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk0));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk4));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = (arg0->unk2 - arg0->unk8);
//     }
// }


void func_151436B4(f32 arg0, f32 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = cosf(arg0);
    sp20 = sinf(arg0);
    sp1C = cosf(arg1);
    temp_f0 = sinf(arg1);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 c = cosf(arg0);
    f32 s = sinf(arg0);
    *arg2 = arg1 * s;
    *arg3 = arg1 * c;
}
void func_15143794(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = func_151423D8(arg0);
    sp20 = func_151423D8(arg0 - 0x40);
    sp1C = func_151423D8(arg1);
    temp_f0 = func_151423D8(arg1 - 0x40);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
void func_15143834(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C = func_151423D8(arg0);
    f32 s = func_151423D8(arg0 - 0x40);
    *arg2 = arg1 * s;
    *arg3 = arg1 * sp1C;
}
#ifdef NON_MATCHING
u8 *func_151438D8(s32 arg0, s32 arg1, u16 arg2, u8 *arg3) {
    u8 *sp58;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_t0;

    if (arg3 == NULL) {
        return NULL;
    }
    sp58 = NULL;
    func_15143D18(&arg0, &arg1, 0, D_800D3094);
    var_a1 = arg0;
    var_t0 = NULL;
    if (var_a1 < arg1) {
        sp30 = arg2 & 0x80;
        sp34 = arg2 & 0x40;
        sp28 = arg2 & 0x200;
        sp2C = arg2 & 0x100;
        sp20 = arg2 & 0x1000;
        sp24 = arg2 & 0x400;
        do {
            var_v0 = 0;
            var_a0 = 0;
            if (arg2 & 1) {
                temp_v1 = D_800D34B8 + (var_a1 * 0x34);
                if (((*(s16 *)((u8 *)arg3 + 0)) == (*(s16 *)((u8 *)temp_v1 + 0))) && ((*(s16 *)((u8 *)arg3 + 2)) == (*(s16 *)((u8 *)temp_v1 + 2))) && ((*(s16 *)((u8 *)arg3 + 4)) == (*(s16 *)((u8 *)temp_v1 + 4)))) {
                    var_v0 = 1;
                    var_a0 = 1;
                }
            } else {
                var_v0 = 1;
            }
            if (arg2 & 2) {
                temp_v1_2 = D_800D34B8 + (var_a1 * 0x34);
                if (((*(s16 *)((u8 *)arg3 + 6)) == (*(s16 *)((u8 *)temp_v1_2 + 6))) && ((*(s16 *)((u8 *)arg3 + 8)) == (*(s16 *)((u8 *)temp_v1_2 + 8))) && ((*(s16 *)((u8 *)arg3 + 0xA)) == (*(s16 *)((u8 *)temp_v1_2 + 0xA)))) {
                    var_v0 = (var_v0 | 2) & 0xFFFF;
                    var_a0 = (var_a0 | 2) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 2) & 0xFFFF;
            }
            if (arg2 & 4) {
                if ((*(f32 *)((u8 *)arg3 + 0xC)) == (*(f32 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0xC))) {
                    var_v0 = (var_v0 | 4) & 0xFFFF;
                    var_a0 = (var_a0 | 4) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 4) & 0xFFFF;
            }
            if (arg2 & 8) {
                if ((*(f32 *)((u8 *)arg3 + 0x10)) == (*(f32 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x10))) {
                    var_v0 = (var_v0 | 8) & 0xFFFF;
                    var_a0 = (var_a0 | 8) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 8) & 0xFFFF;
            }
            if (arg2 & 0x10) {
                if ((*(u8 *)((u8 *)arg3 + 0x14)) == (*(u8 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x14))) {
                    var_v0 = (var_v0 | 0x10) & 0xFFFF;
                    var_a0 = (var_a0 | 0x10) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x10) & 0xFFFF;
            }
            if (arg2 & 0x20) {
                if ((*(u8 *)((u8 *)arg3 + 0x15)) == ((s32) (*(u8 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x15)) >> 2)) {
                    var_v0 = (var_v0 | 0x20) & 0xFFFF;
                    var_a0 = (var_a0 | 0x20) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x20) & 0xFFFF;
            }
            if (sp34 != 0) {
                if ((*(u8 *)((u8 *)arg3 + 0x16)) == (*(u8 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x16))) {
                    var_v0 = (var_v0 | 0x40) & 0xFFFF;
                    var_a0 = (var_a0 | 0x40) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x40) & 0xFFFF;
            }
            if (sp30 != 0) {
                if ((*(u8 *)((u8 *)arg3 + 0x17)) == (*(u8 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x17))) {
                    var_v0 = (var_v0 | 0x80) & 0xFFFF;
                    var_a0 = (var_a0 | 0x80) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x80) & 0xFFFF;
            }
            if (sp2C != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x18)) == (*(s32 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x18))) {
                    var_v0 = (var_v0 | 0x100) & 0xFFFF;
                    var_a0 = (var_a0 | 0x100) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x100) & 0xFFFF;
            }
            if (sp28 != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x1C)) == (*(s32 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x1C))) {
                    var_v0 = (var_v0 | 0x200) & 0xFFFF;
                    var_a0 = (var_a0 | 0x200) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x200) & 0xFFFF;
            }
            if (sp24 != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x20)) == (*(s32 *)((u8 *)((D_800D34B8 + (var_a1 * 0x34))) + 0x20))) {
                    var_v0 = (var_v0 | 0x400) & 0xFFFF;
                    var_a0 = (var_a0 | 0x400) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x400) & 0xFFFF;
            }
            if (sp20 != 0) {
                if (var_v0 == 0x7FF) {
                    var_t0 = (var_a1 * 0x34) + D_800D34B8;
                }
            } else if (var_a0 != 0) {
                var_t0 = (var_a1 * 0x34) + D_800D34B8;
            }
            var_a1 += 1;
        } while (var_a1 != arg1);
    }
    return var_t0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151438D8.s")
#endif
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg2) {
        arg2 ^= arg3 ^= arg2 ^= arg3;
    }
    if (*arg1 < *arg0) {
        *arg0 ^= *arg1 ^= *arg0 ^= *arg1;
    }
    if (*arg0 < arg2) {
        *arg0 = arg2;
    }
    if (arg3 < *arg1) {
        *arg1 = arg3;
    }
}
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    if (arg2 < arg1) {
        arg1 ^= arg2 ^= arg1 ^= arg2;
    }
    if (*arg0 < arg1) {
        *arg0 = arg1;
        return 1;
    }
    if (arg2 < *arg0) {
        *arg0 = arg2;
        return 2;
    }
    return 0;
}

s32 func_15143E08(struct127 *arg0) {
    return (((s32) arg0->unk7A >> 8) + 64) & 0xFF;
}

s16 func_15143E24(struct127 *arg0) {
    if (arg0->unk31C != NULL) {
        return (arg0->unk7A - arg0->unk31C->unk12) >> 8;
    }
    return arg0->unk7A >> 8;
}
f32 func_15143E64(struct17 *arg0) {
    return sqrtf((arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8));
}
extern s32 D_800BEE08;
u8 func_15143E94(s32 arg0, s32 arg1)
{
  u8 ret;
  s8 i;
  u8 found;
  s8 n;
  s32 found2;
  structEU_151D8E18 sp28;
  ret = 0;
  if (((!found2) && (!found2)) && (!found2)) // fakematch: dummy test of the uninitialised found2 (permuter)
  {
  }
  n = D_80082FA0 + 1;
  i = 0;
  found = 0;
  while ((!found) && (i < n))
  {
    if (D_800CC2D0[i].health != 0)
    {
      found = 1;
    }
    else
    {
      i++;
    }
  }

  if (found)
  {
    i = 0;
    found2 = 0;
    while ((!found2) && (i < n))
    {
      if (func_150A29C8(i, arg1) == 0)
      {
        found2 = 1;
      }
      else
      {
        i++;
      }
    }

    if (found2)
    {
      func_1512D748(&D_800DBFF0[D_800BEE08], arg0, 1);
      sp28.unk0 = 1;
      sp28.unk2 = (func_150ADA20() & 0xF) + 20;
      sp28.unk4 = (func_150ADA20() & 3) + 4;
      sp28.unk6 = -1;
      sp28.unk5 = 1;
      func_151D8E18(&sp28, 0, 0xFF, 0);
      ret = 1;
    }
  }
  return ret;
}
#ifdef NON_MATCHING
s32 func_1514401C(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t5_3;
    s32 temp_t7;
    s32 var_t1;
    s32 var_v1;

    temp_t7 = arg3 & 0xFF;
    var_v1 = 0;
    temp_t0 = (*D_80090F14[arg0 & 0xFF] << 0x10) - 1;
    temp_t5 = *arg2 + (*arg1 * D_800BE9E4);
    *arg2 = temp_t5;
    var_t1 = temp_t5;
    if (temp_t0 < temp_t5) {
        if (temp_t7 & 1) {
            var_v1 = 1;
        } else if (temp_t7 & 2) {
            *arg1 = 0;
            *arg2 = temp_t0;
        } else if (temp_t7 & 4) {
            *arg2 = temp_t0 - (var_t1 % temp_t0);
            *arg1 = -*arg1;
        } else {
            do {
                temp_t5_2 = var_t1 - temp_t0;
                *arg2 = temp_t5_2;
                var_t1 = temp_t5_2;
            } while (temp_t0 < temp_t5_2);
        }
    } else if ((var_t1 < 0) && !(temp_t7 & 8)) {
        if (temp_t7 & 0x10) {
            *arg1 = 0;
            *arg2 = 0;
        } else if (temp_t7 & 4) {
            *arg2 = (s32) -var_t1 % temp_t0;
            *arg1 = -*arg1;
        } else {
            do {
                temp_t5_3 = var_t1 + temp_t0;
                *arg2 = temp_t5_3;
                var_t1 = temp_t5_3;
            } while (temp_t5_3 < 0);
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514401C.s")
#endif
// NON-MATCHING: regalloc only (flags copy in v0, limit in t0)
// s32 func_1514401C(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
//     s32 max;
//     s32 pos;
//     s32 ret;
//
//     ret = 0;
//     max = (D_80090F14[arg0][0] << 16) - 1;
//     *arg2 += *arg1 * D_800BE9E4;
//     pos = *arg2;
//     if (max < pos) {
//         if (arg3 & 1) {
//             ret = 1;
//         } else if (arg3 & 2) {
//             *arg1 = 0;
//             *arg2 = max;
//         } else if (arg3 & 4) {
//             *arg2 = max - (pos % max);
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos - max;
//             } while (max < pos);
//         }
//     } else if ((pos < 0) && !(arg3 & 8)) {
//         if (arg3 & 0x10) {
//             *arg1 = 0;
//             *arg2 = 0;
//         } else if (arg3 & 4) {
//             *arg2 = -pos % max;
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos + max;
//             } while (pos < 0);
//         }
//     }
//     return ret;
// }
void func_151441A4(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD) {
    s16 temp_v0;
    s16 temp_v0_2;

    switch (argD) {
    case 2:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) argB;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) argB;
        return;
    case 3:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    case 4:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    }
}
void func_151442FC(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (argD) {
    case 2:
    case 3:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg7;
        return;
    case 13:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = 0;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = 0;
        return;
    case 7:
    case 12:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) argB;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg7;
        return;
    case 4:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 5:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 6:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) argB;
        return;
    case 10:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) argB;
        return;
    case 11:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) arg7;
        return;
    case 9:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) argB;
        return;
    default:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    }
}
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 range;

    if (arg1 < arg0) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 -= range;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 += range;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    while (arg1 < arg0) {
        arg0 -= arg1 - arg2;
    }
    while (arg0 < arg2) {
        arg0 += arg1 - arg2;
    }
    return arg0;
}
f32 func_15144598(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = (arg0->unk6 * arg0->unkA) * 4.0f;
        break;
    case 0:
    case 1:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
f32 func_1514462C(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = arg0->unk6 * arg0->unk8 * arg0->unkA;
        break;
    case 0:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f * arg0->unk8;
        break;
    case 1:
        var_f2 = (f32)arg0->unk6 * 1.0471976f * (f32)arg0->unk6 * (f32)arg0->unk6;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
#ifdef NON_MATCHING
void func_1514470C(u8 *arg0, u8 *arg1) {
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp64;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp48;
    u8 sp47;
    struct17 sp38;
    f32 sp2C;
    f32 sp28;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f8;
    f32 var_f6;
    s32 temp_t9;
    u8 temp_v0;

    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 6));
    sp90 = (f32) (*(s16 *)((u8 *)arg0 + 8));
    sp88 = (*(f32 *)((u8 *)arg0 + 0x24));
    sp84 = (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f18 = (f32) (*(s16 *)((u8 *)arg0 + 0xA));
    sp80 = (*(f32 *)((u8 *)arg0 + 0x2C));
    sp7C = (*(f32 *)((u8 *)arg0 + 0x30));
    temp_t9 = (*(u8 *)((u8 *)arg0 + 0x15)) & 3;
    switch (temp_t9) {                              /* irregular */
    default:
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) (*(s16 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)arg0 + 2));
        var_f6 = (f32) (*(s16 *)((u8 *)arg0 + 4));
block_7:
        (*(f32 *)((u8 *)arg1 + 8)) = var_f6;
        return;
    case 2:
        sp8C = temp_f2;
        sp94 = temp_f18;
        temp_f14 = (func_150ADA68() * (2.0f * temp_f2)) - temp_f2;
        sp70 = temp_f14;
        temp_f16 = func_150ADA68() * sp90;
        sp74 = temp_f16;
        temp_f8 = func_150ADA68() * (2.0f * temp_f18);
        sp64 = temp_f14;
        temp_f2_2 = temp_f8 - temp_f18;
        temp_f12 = (temp_f16 * sp88) + (temp_f2_2 * sp84);
        sp6C = temp_f12;
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + ((temp_f14 * sp7C) + (temp_f12 * sp80)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + ((temp_f16 * sp84) - (temp_f2_2 * sp88)));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + ((sp6C * sp7C) - (sp64 * sp80)));
        return;
    case 0:
        sp8C = temp_f2;
        sp48 = func_150ADA68() * temp_f2;
        temp_v0 = func_150ADA20();
        sp47 = temp_v0;
        sp58 = func_151423D8((temp_v0 - 0x40) & 0xFF) * sp48;
        temp_f16_2 = func_150ADA68() * sp90;
        sp5C = temp_f16_2;
        temp_f2_3 = func_151423D8(temp_v0) * sp48;
        temp_f12_2 = (temp_f16_2 * sp88) + (temp_f2_3 * sp84);
        sp54 = temp_f12_2;
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + ((sp58 * sp7C) + (temp_f12_2 * sp80)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + ((temp_f16_2 * sp84) - (temp_f2_3 * sp88)));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + ((sp54 * sp7C) - (sp58 * sp80)));
        return;
    case 1:
        sp8C = temp_f2;
        sp28 = func_150ADA68();
        sp2C = func_150ADA68();
        func_151436B4(sp28 * 6.2831855f, sp2C * 6.2831855f, func_150ADA68() * temp_f2, &sp38);
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + (*(f32 *)&(sp38)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + sp38.unk4);
        var_f6 = (f32) (*(s16 *)((u8 *)arg0 + 4)) + sp38.unk8;
        goto block_7;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514470C.s")
#endif
f32 func_15144A74(struct17 *arg0, struct17 *arg1) {
    return (arg0->unk0 * arg1->unk0) + (arg0->unk4 * arg1->unk4) + (arg0->unk8 * arg1->unk8);
}
f32 func_15144AA8(s32 arg0) {
    f32 var_f2 = D_800DBFF0[arg0].unk380;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}
f32 *func_15144B34(s32 arg0) {
    return &D_800DBFF0[arg0].unk2F8;
}
f32 func_15144B68(f32 arg0) {
    f32 var_f2;

    var_f2 = arg0;
    if (arg0 > 6.2831855f) {
        do {
            var_f2 -= 6.2831855f;
        } while (var_f2 > 6.2831855f);
    }
    if (var_f2 < 0.0f) {
        do {
            var_f2 += 6.2831855f;
        } while (var_f2 < 0.0f);
    }
    return var_f2;
}
f32 func_15144BC8(f32 arg0) {
    f32 var_f2 = arg0;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}

s32 func_15144C2C(s16 arg0) {
    s16 tmp1 = arg0;

    while (tmp1 >= 256)
    {
        tmp1 -= 255;
    }
    while (tmp1 < 0)
    {
        tmp1 += 255;
    }

    return tmp1;
}

f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 tmp;

    arg0 = func_15144B68(arg0);
    tmp = fabsf(arg0 - func_15144B68(arg1));
    if (3.1415927f < tmp) {
        tmp = 6.2831855f - tmp;
    }
    return tmp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15144CEC.s")
#ifdef NON_MATCHING
s32 func_15144E80(u8 *arg0, struct17 *arg1, u8 *arg2, struct17 *arg3) {
    struct {
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        struct17 u30;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
    } sp;
    f32 temp_f10;
    struct17 *var_a3;

    var_a3 = arg3;
    if (var_a3 == NULL) {
        var_a3 = &sp.u30;
    }
    sp.u3C = (f32) (*(s16 *)((u8 *)arg0 + 0));
    sp.u40 = (f32) (*(s16 *)((u8 *)arg0 + 2));
    sp.u44 = (f32) (*(s16 *)((u8 *)arg0 + 4));
    temp_f10 = (f32) (*(s16 *)((u8 *)arg0 + 6));
    sp.u48 = temp_f10;
    sp.u4C = (f32) (*(s16 *)((u8 *)arg0 + 8));
    sp.u50 = (f32) (*(s16 *)((u8 *)arg0 + 0xA));
    sp.u54 = (f32) (*(s16 *)((u8 *)arg0 + 0xC));
    sp.u58 = (f32) (*(s16 *)((u8 *)arg0 + 0xE));
    sp.u5C = (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    if ((sp.u3C == temp_f10) && (sp.u40 == sp.u4C) && (sp.u44 == sp.u50)) {
        return 0;
    }
    if ((sp.u3C == sp.u54) && (sp.u40 == sp.u58) && (sp.u44 == sp.u5C)) {
        return 0;
    }
    if ((sp.u48 == sp.u54) && (sp.u4C == sp.u58) && (sp.u50 == sp.u5C)) {
        return 0;
    }
    sp.u24 = sp.u3C - sp.u48;
    sp.u18 = sp.u54 - sp.u48;
    sp.u2C = sp.u44 - sp.u50;
    sp.u28 = sp.u40 - sp.u4C;
    sp.u1C = sp.u58 - sp.u4C;
    arg3 = var_a3;
    sp.u20 = sp.u5C - sp.u50;
    func_151450B4((struct17 *) &sp.u24, (struct17 *) &sp.u18, var_a3);
    func_151450B4((struct17 *) &sp.u24, arg3, arg1);
    (*(f32 *)((u8 *)arg2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u24) + 0));
    (*(s32 *)((u8 *)arg2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u24) + 4));
    (*(s32 *)((u8 *)arg2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u24) + 8));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15144E80.s")
#endif
void func_151450B4(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk4 * arg1->unk8 - arg0->unk8 * arg1->unk4;
    arg2->unk4 = arg0->unk8 * arg1->unk0 - arg0->unk0 * arg1->unk8;
    arg2->unk8 = arg0->unk0 * arg1->unk4 - arg0->unk4 * arg1->unk0;
}

s32 func_15145128(struct17 *arg0, struct17 *arg1, f32 *arg2, f32 *arg3) {
    f32 lenSq;
    f32 sp0;

    if (arg3 == NULL) {
        arg3 = &sp0;
    }
    lenSq = (arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8);
    if (lenSq == 0.0f) {
        return 0;
    }
    if (arg2 != NULL) {
        *arg2 = sqrtf(lenSq);
        *arg3 = 1.0f / *arg2;
    } else {
        *arg3 = 1.0f / sqrtf(lenSq);
    }
    arg1->unk0 = *arg3 * arg0->unk0;
    arg1->unk4 = *arg3 * arg0->unk4;
    arg1->unk8 = *arg3 * arg0->unk8;
    return 1;
}
s32 func_151451F0(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, f32 *arg7, f32 *arg8) {
    if (func_151452C4(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8)) {
        if ((*arg7 < 0.0f) && (*arg8 < 0.0f)) {
            return 0;
        }
        if ((*arg7 >= 0.0f) && (*arg8 < 0.0f)) {
            return 1;
        }
        if (*arg7 < arg4) {
            return 1;
        }
        return 0;
    }
    return 0;
}
typedef struct { f32 x, y, z; } V3;

s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, s32 arg4, s32 arg5, f32 *arg6, f32 *arg7) {
    f32 dx, dy, dz;
    V3 dir;
    V3 org;
    f32 b, dd, d, t, t0, t1;

    dx = arg2->unk0 - arg0->unk0;
    dy = arg2->unk4 - arg0->unk4;
    dz = arg2->unk8 - arg0->unk8;
    dir = *(V3 *)arg1;
    org = *(V3 *)arg0;
    b = dx * dir.x + dy * dir.y + dz * dir.z;
    dd = dx * dx + dy * dy + dz * dz;
    d = dd - b * b;
    if ((arg3 * arg3) < d) {
        return 0;
    }
    t = sqrtf((arg3 * arg3) - d);
    if (b < t) {
        t = -t;
    }
    t0 = b - t;
    t1 = b + t;
    ((V3 *)arg4)->x = t0 * dir.x + org.x;
    ((V3 *)arg4)->y = t0 * dir.y + org.y;
    ((V3 *)arg4)->z = t0 * dir.z + org.z;
    *arg6 = t0;
    ((V3 *)arg5)->x = t1 * dir.x + org.x;
    ((V3 *)arg5)->y = t1 * dir.y + org.y;
    ((V3 *)arg5)->z = t1 * dir.z + org.z;
    *arg7 = t1;
    {
        V3 diff;

        diff.x = ((V3 *)arg4)->x - arg0->unk0;
        diff.y = ((V3 *)arg4)->y - arg0->unk4;
        diff.z = ((V3 *)arg4)->z - arg0->unk8;
        if (func_15144A74((struct17 *)&diff, arg1) < 0.0f) {
            return 0;
        }
    }
    return 1;
}

s32 func_151454BC(u8 arg0, f32 arg1, struct17 *arg2) {
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;
    struct17 *temp_v0;

    temp_v0 = func_15144B34(arg0);
    tmp1 = arg2->unk0 - temp_v0->unk0;
    tmp2 = arg2->unk4 - temp_v0->unk4;
    tmp3 = arg2->unk8 - temp_v0->unk8;

    if ((arg1 * arg1) < ((tmp1 * tmp1) + (tmp2 * tmp2) + (tmp3 * tmp3))) {
        return 0;
    }
    return 1;
}

void func_15145548(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp24;

    if (arg4 == NULL) {
        arg4 = &sp24;
    }
    if (func_1514563C(arg0, arg1, arg2, arg3, arg4)) {
        if (*arg4 < 0.0f) {
            *arg3 = *arg0;
        } else if (*arg4 > 1.0f) {
            arg3->unk0 = arg0->unk0 + arg1->unk0;
            arg3->unk4 = arg0->unk4 + arg1->unk4;
            arg3->unk8 = arg0->unk8 + arg1->unk8;
        }
    } else {
        *arg3 = *arg0;
    }
}

#ifdef NON_MATCHING
s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    struct {
        f32 u10;
        u8 pad14[0xC];
    } sp;
    f32 sp0;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;

    if (arg4 == NULL) {
        arg4 = &sp.u10;
    }
    temp_f2 = arg1->unk0;
    temp_f12 = arg1->unk4;
    temp_f14 = arg1->unk8;
    temp_f0 = (temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f14 * temp_f14);
    if (temp_f0 == 0.0f) {
        return 0;
    }
    temp_f6 = (((temp_f2 * arg2->unk0) + (temp_f12 * arg2->unk4) + (temp_f14 * arg2->unk8)) - ((temp_f2 * arg0->unk0) + (temp_f12 * arg0->unk4) + (temp_f14 * arg0->unk8))) / temp_f0;
    sp0 = temp_f6;
    *arg4 = temp_f6;
    arg3->unk0 = (temp_f6 * arg1->unk0) + arg0->unk0;
    arg3->unk4 = (*arg4 * arg1->unk4) + arg0->unk4;
    arg3->unk8 = (*arg4 * arg1->unk8) + arg0->unk8;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514563C.s")
#endif
// NON-MATCHING: t is also stored to an unused stack slot at sp+0 (frame 0x20); closest draft:
// s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
//     f32 sp10;
//     f32 lenSq;
//     f32 dotO;
//     f32 dotP;
//     f32 t;
//
//     if (arg4 == NULL) {
//         arg4 = &sp10;
//     }
//     lenSq = (arg1->unk0 * arg1->unk0) + (arg1->unk4 * arg1->unk4) + (arg1->unk8 * arg1->unk8);
//     if (lenSq == 0.0f) {
//         return 0;
//     }
//     dotO = (arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk4) + (arg1->unk8 * arg0->unk8);
//     dotP = (arg1->unk0 * arg2->unk0) + (arg1->unk4 * arg2->unk4) + (arg1->unk8 * arg2->unk8);
//     *arg4 = t = (dotP - dotO) / lenSq;
//     arg3->unk0 = (t * arg1->unk0) + arg0->unk0;
//     arg3->unk4 = (*arg4 * arg1->unk4) + arg0->unk4;
//     arg3->unk8 = (*arg4 * arg1->unk8) + arg0->unk8;
//     return 1;
// }

#ifdef NON_MATCHING
void func_15145740(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s16 sp3E;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp24;
    f32 sp20;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f6;
    s16 var_t0;
    s16 var_v1;
    struct126 *temp_v0;
    struct126 *temp_v0_2;
    u8 temp_v1;

    temp_v1 = arg0->id;
    if ((temp_v1 == 0x96) && (temp_v0 = arg0->unk31C, (temp_v0->matrix_physics != 0))) {
        var_t0 = arg0->unk7A + temp_v0->unk80;
    } else {
        temp_v0_2 = arg0->unk31C;
        if (temp_v0_2 != NULL) {
            var_t0 = arg0->unk7A - temp_v0_2->unk12;
        } else {
            var_t0 = (s16) arg0->unk7A;
        }
    }
    if ((temp_v1 == 0x96) && (arg0->unk31C->matrix_physics != 0)) {
        var_v1 = arg0->unk31C->unk82 + 0x400;
    } else {
        var_v1 = arg0->unk1D1 * 0xC8;
    }
    temp_f2 = (f32) var_v1 * 0.005493164f;
    sp38 = temp_f2;
    sp3E = var_t0;
    sp20 = temp_f2 * 0.017453292f;
    func_1505A184(var_t0 & 0xFFFF, 2000.0f, temp_f2, (f32 *) arg1, arg1 + 8, arg1 + 4);
    if (arg2 != 0) {
        sp3E = var_t0;
        (*(f32 *)((u8 *)arg2 + 4)) = (f32) (cosf(sp20) * 1000.0f);
        temp_f6 = sinf(sp20) * 1000.0f;
        sp30 = temp_f6;
        temp_f12 = (f32) var_t0 * 0.0000958738f;
        sp24 = temp_f12;
        (*(f32 *)((u8 *)arg2 + 0)) = (f32) (cosf(temp_f12) * sp30);
        (*(f32 *)((u8 *)arg2 + 8)) = (f32) (sinf(temp_f12) * -temp_f6);
        if (arg3 != 0) {
            temp_f12_2 = sp20 + arg4;
            sp34 = temp_f12_2;
            (*(f32 *)((u8 *)arg3 + 4)) = (f32) (cosf(temp_f12_2) * 1000.0f);
            sp30 = sinf(temp_f12_2) * 1000.0f;
            (*(f32 *)((u8 *)arg3 + 0)) = (f32) (cosf(sp24) * sp30);
            (*(f32 *)((u8 *)arg3 + 8)) = (f32) (sinf(sp24) * -sp30);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15145740.s")
#endif
// NON-MATCHING: 90% there
// void func_15145740(struct127 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 arg4) {
//     struct194 tmp;
//     f32 temp_f6;
//     s16 phi_v1;
//     s16 phi_t0;
//
//     if ((arg0->unk4 == 0x96) && ((arg0->unk31C->unk7D != 0))) {
//         phi_t0 = arg0->unk7A + arg0->unk31C->unk80;
//     } else {
//         if (arg0->unk31C != 0) {
//             phi_t0 = arg0->unk7A - arg0->unk31C->unk12;
//         } else {
//             phi_t0 = arg0->unk7A;
//         }
//     }
//     if ((arg0->unk4 == 0x96) && (arg0->unk31C->unk7D != 0)) {
//         phi_v1 = arg0->unk31C->unk82 + 1024;
//     } else {
//         phi_v1 = arg0->unk1D1 * 200;
//     }
//     tmp.unk14 = phi_t0;
//     tmp.unk10 = phi_v1 * 0.005493164f;
//     tmp.unk0 = tmp.unk10 * D_800A56B4;
//     func_1505A184(phi_t0, 2000.0f, tmp.unk10, &arg1->unk0, &arg1->unk8, &arg1->unk4);
//     if (arg2 != 0) {
//         arg2->unk4 = cosf(tmp.unk0) * 1000.0f;
//         temp_f6 = sinf(tmp.unk0) * 1000.0f;
//         tmp.unk8 = temp_f6;
//         tmp.unk4 = phi_t0 * D_800A56B8;
//         arg2->unk0 = cosf(tmp.unk4) * tmp.unk8;
//         arg2->unk8 = sinf(tmp.unk4) * -temp_f6;
//         if (arg3 != 0) {
//             tmp.unkC = tmp.unk0 + arg4;
//             arg3->unk4 = cosf(tmp.unkC) * 1000.0f;
//             tmp.unk8 = sinf(tmp.unkC) * 1000.0f;
//             arg3->unk0 = cosf(tmp.unk4) * tmp.unk8;
//             arg3->unk8 = sinf(tmp.unk4) * -tmp.unk8;
//         }
//     }
// }

void func_15145974(struct17 *arg0, f32 *arg1, f32 *arg2) {
    *arg1 = func_150484A0(arg0->unk0, arg0->unk8) * 57.295776f;
    if (arg2 != NULL) {
        *arg2 = (func_150484A0(sqrtf(arg0->unk0 * arg0->unk0 + arg0->unk8 * arg0->unk8), arg0->unk4) * 57.295776f) - 90.0f;
    }
}

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32)(arg0 * arg2 * 100.0f)] * arg1;
}


void func_15145A50(struct127 *arg0) {
    arg0->unk5 = 3;
    if (D_800BE9F0 != 51) {
        if ((D_800BE616 != 0) || (arg0->interaction_state == 5) || (arg0->interaction_state == 1) || (arg0->interaction_state == 21)) {
            arg0->interaction_state = 5;
            if (arg0->unk31C != NULL) {
                arg0->unk31C->unk78 = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}

#ifdef NON_MATCHING
void func_1515C710(u8 *, f32 *, f32 *, f32 *);

s32 func_15145AD8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, f32 *arg5, f32 *arg6, s32 *arg7) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C;
    } sp;
    s32 *var_s0;
    f32 *var_a3;
    f32 temp_f0;

    if (arg5 != NULL) {
        arg5 = &sp.u78;
    }
    var_a3 = arg6;
    var_s0 = arg7;
    if (var_a3 != NULL) {
        var_a3 = &sp.u74;
    }
    if (var_s0 != NULL) {
        var_s0 = &sp.u7C;
    }
    arg6 = var_a3;
    func_1515C710(arg2, var_s0, arg5, var_a3);
    if (*arg6 == 0.0f) {
        return 0;
    }
    if (*arg5 == 0.0f) {
        return 0;
    }
    temp_f0 = (*(f32 *)((u8 *)arg2 + 0xDC));
    sp.u3C = (*(f32 *)((u8 *)arg2 + 0xE0));
    sp.u68 = (*(f32 *)((u8 *)arg0 + 0));
    sp.u6C = (*(f32 *)((u8 *)arg0 + 4)) * temp_f0;
    sp.u70 = (*(f32 *)((u8 *)arg0 + 8));
    sp.u5C = (*(f32 *)((u8 *)arg1 + 0));
    sp.u60 = (*(f32 *)((u8 *)arg1 + 4)) * temp_f0;
    sp.u64 = (*(f32 *)((u8 *)arg1 + 8));
    sp.u40 = temp_f0;
    if (func_15145128((struct17 *) &sp.u5C, (struct17 *) &sp.u5C, &sp.u4C, &sp.u38) == 0) {
        return 0;
    }
    sp.u50 = (*(f32 *)((u8 *)var_s0 + 0));
    sp.u54 = (*(f32 *)((u8 *)var_s0 + 4)) * sp.u40;
    sp.u58 = (*(f32 *)((u8 *)var_s0 + 8));
    if (func_151451F0((struct17 *) &sp.u68, (struct17 *) &sp.u5C, (struct17 *) &sp.u50, *arg5, sp.u4C, arg3, arg4, &sp.u48, &sp.u44) == 0) {
        return 0;
    }
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) ((*(f32 *)((u8 *)arg3 + 4)) * sp.u3C);
    (*(f32 *)((u8 *)arg4 + 4)) = (f32) ((*(f32 *)((u8 *)arg4 + 4)) * sp.u3C);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15145AD8.s")
#endif
u8 func_15145C90(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    } else {
        return (D_800DBEF4[arg0].unk6F & 0x80) == 0x80;
    }
}

void func_15145CD0(struct_eu_xform *arg0, struct17 **arg1, struct17 **arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    func_150A8050(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        func_150A7E40(mf, arg1[i]->unk0, arg1[i]->unk4, arg1[i]->unk8, &arg2[i]->unk0, &arg2[i]->unk4, &arg2[i]->unk8);
    }
}
void func_15145DB4(struct_eu_xform *arg0, struct17 *arg1, struct17 *arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    func_150A8050(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        func_150A7E40(mf, arg1[i].unk0, arg1[i].unk4, arg1[i].unk8, &arg2[i].unk0, &arg2[i].unk4, &arg2[i].unk8);
    }
}

void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3) {
    f32 **p;
    f32 mtx[4][4];
    f32 **q;
    f32 *v;
    f32 *o;

    if (D_800C42B0 != 0) {
        guMtxL2F(mtx, arg2);
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if (!arg3) {} // fakematch: extends arg3's live range (count in s1, not s2)
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    func_150A7E40(mtx, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    func_15142314(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    } else {
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    func_150A7E40((f32 (*)[4]) arg2, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    func_15142314(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_15146078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_151462C8.s")
u8 func_151464B8(s16 *arg0) {
    s32 i;
    s16 mask;

    for (i = 0, mask = 0; i <= D_80082FA0; i++) {
        mask |= 1 << i;
    }
    return !(arg0[1] & mask);
}

void func_15146508(struct127 *arg0, struct127 *arg1) {
    struct193 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg1;
    tmp.unk8 = arg0->unique_id;
    tmp.unk9 = arg1->unique_id;
    func_15169040(&tmp, 45, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_170760/func_1514654C.s")

s32 func_1514672C(u8 *arg0) {
    f32 temp_f0;

    if ((fabsf((*(f32 *)((u8 *)arg0 + 0))) > 19500.0f) || (fabsf((*(f32 *)((u8 *)arg0 + 8))) > 19500.0f) || (temp_f0 = (*(f32 *)((u8 *)arg0 + 4)), (temp_f0 > 19500.0f)) || (temp_f0 < -9500.0f)) {
        return 0;
    }
    return 1;
}
// NON-MATCHING: JUSTREG: first 3 statements are out of order
// s32 func_1514672C(struct17 *arg0) {
//     if ((D_800A56C4 < fabsf(arg0->unk0)) || (D_800A56C4 < fabsf(arg0->unk8)) || (D_800A56C4 < arg0->unk4) || (arg0->unk4 < D_800A56C8)) {
//         return 0;
//     } else {
//         return 1;
//     }
// }

void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    *arg0 = *arg0 - D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if ((func_150ADA20() & 3) != 0) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    *arg7 = ((*arg2 - *arg7) * arg6) + *arg7;
}
