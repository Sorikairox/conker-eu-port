#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_1503E4E4(s32 arg0, s32 arg1);
void func_1503E550(s32 arg0);
extern u8 D_80098CC4[];
#endif


#ifdef NON_MATCHING
void func_1503E1FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 *D_800847FC[];

/*
 * P71 (EU 0x1503E160): sets the flags of entry `entry` of flag set D_800847FC[set] on object obj's record
 * (func_1503E1FC with its slot index); entry -1 sets all bits.
 */
void func_1503DE70(struct127 *obj, s32 set, s32 entry) {
    s32 *e;

    if (entry != -1) {
        e = &D_800847FC[set][entry * 2];
        func_1503E1FC(obj - D_800CC2D0, set, e[0], e[1]);
    } else {
        func_1503E1FC(obj - D_800CC2D0, set, -1, -1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503DE70.s")
#endif

void func_1503E1FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct106 *temp_v0;
    temp_v0 = &D_800C6660[arg0];
    temp_v0->unk4 |= arg2;
    temp_v0->unk8 |= arg3;
    temp_v0->pad[2] = arg1;
    temp_v0->unkF = 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E238.s")

extern s32 D_800C6A84;
extern s32 D_800C6A88;
s32 func_1503E4E4(s32 arg0, s32 arg1)
{
  if (arg0 < 0x20) {
    if ((*(s32 *)((u8 *)&D_800C6A84 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  } else {
    if ((*(s32 *)((u8 *)&D_800C6A88 + arg1 * 0x10)) & (1 << arg0)) {
      return 1;
    }
  }
  return 0;
}

#ifdef NON_MATCHING
void func_10004074(s32);
extern s32 D_800847F0;

void func_1503E550(s32 arg0) {
    struct127 *sp3C;
    s32 temp_v1_2;
    s32 var_s0;
    struct106 *temp_s7;
    struct127 *temp_v0_2;
    struct127 *temp_v0_3;
    u8 *temp_v0;
    u8 *var_s1;
    u8 temp_s6;
    u8 temp_v1;

    temp_s7 = &D_800C6660[arg0];
    if (temp_s7->unkF != 0) {
        temp_v1 = (u8) temp_s7->pad[2];
        temp_v0 = *(s32 *)((u8 *)&D_800847F0 + (temp_v1 * 4));
        if (temp_v0 != NULL) {
            temp_s6 = D_80098CC4[temp_v1];
            var_s0 = 0;
            var_s1 = temp_v0;
            if ((s32) temp_s6 > 0) {
                do {
                    if ((*var_s1 != 0xFF) && (func_1503E4E4(var_s0, arg0) != 0)) {
                        temp_v0_2 = &D_800CC2D0[arg0];
                        temp_v0_2->unk94 |= 1 << *var_s1;
                    }
                    var_s0 += 1;
                    var_s1 += 1;
                } while (var_s0 != temp_s6);
            }
        }
        temp_v1_2 = temp_s7->unk0;
        temp_s7->unkF = 0;
        temp_v0_3 = &D_800CC2D0[arg0];
        if (temp_v1_2 != 0) {
            sp3C = temp_v0_3;
            func_10004074(temp_v1_2);
        }
        temp_s7->unk0 = 0;
        temp_v0_3->unk74 &= 0xFF7F;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E550.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E6B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503E5F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EB1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503ED44.s")

#ifdef NON_MATCHING
extern f32 D_80098CD4;
void func_1503EE68(s32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    struct {
        f32 u50;
        f32 u54;
        f32 u58;
        s32 u5C;
    } sp;
    f32 *var_s1;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f8;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;

    if (arg3 != 0) {
        var_s3 = 0x80;
        var_s4 = 0x7F;
    } else {
        var_s3 = 0xFF;
        var_s4 = 0;
    }
    temp_f0 = arg1 * 0.02745098f;
    var_s0 = arg0;
    var_s1 = &sp.u50;
    sp.u50 = temp_f0;
    sp.u58 = temp_f0;
    sp.u54 = arg2 * 0.02745098f;
    do {
        temp_f8 = *var_s1;
        temp_f18 = (*(f32 *)((u8 *)var_s0 + 0x48));
        var_s1 = (f32 *)((u8 *)var_s1 + (4));
        var_s0 += 4;
        (*(f32 *)((u8 *)var_s0 + 0x44)) = (f32) (temp_f18 * (((f32) (s32) ((func_150ADA20() & var_s3) + var_s4) * temp_f8) + 2.0f));
    } while ((u32) var_s1 < (u32) &sp.u5C);
    var_s2 = 0;
    var_s0_2 = arg0;
    do {
        var_s2 += 1;
        var_s0_2 += 4;
        (*(f32 *)((u8 *)var_s0_2 + 0x50)) = (f32) ((f32) (s32) ((func_150ADA20() & 0xFF) - 0x80) * 0.03125f);
    } while (var_s2 != 3);
    *(f32 *)((u8 *)arg0 + 0x60) = D_80098CD4;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EE68.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503EF90.s")

void func_1503F1A8(void) {
}

void func_1503EF90(s32);
void func_1503F1B0(s32 arg0) {
    s32 temp_v0;
    struct106 *temp_v1;

    func_1503EF90(arg0);
    temp_v1 = &D_800C6660[arg0];
    temp_v0 = *(s16 *)((u8 *)temp_v1 + 0xC);
    temp_v0 = temp_v0 - D_800BE9E4; // fakematch: split load/subtract (permuter) gives the ref register order
    (*(s16 *)((u8 *)temp_v1 + 0xC)) = temp_v0;
    if (temp_v0 <= 0) {
        func_15060F28(&D_800CC2D0[arg0], 1);
    }
}

#ifdef NON_MATCHING
extern s32 *D_800847FC[];

/*
 * P71: entry (flagsA, flagsB) of flag set D_800847FC[set] is satisfied by object slot i when every non-zero word
 * shares a bit with the slot's flags D_800C6A84 / D_800C6A88 (the +4 / +8 words of its 16-byte record, as in
 * func_1503E4E4). Returns 1 / 0.
 */
s32 func_1503F23C(s32 set, s32 entry, s32 i) {
    s32 *e = &D_800847FC[set][entry * 2];

    if (e[0] != 0 && !(e[0] & *(s32 *) ((u8 *) &D_800C6A84 + i * 0x10))) {
        return 0;
    }
    if (e[1] != 0 && !(e[1] & *(s32 *) ((u8 *) &D_800C6A88 + i * 0x10))) {
        return 0;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F23C.s")
#endif

extern u8 D_80098CC4[];

void func_1503F2B4(s32 arg0) {
    struct106 *p;
    s32 n;
    s32 i;

    p = &D_800C6660[arg0];
    *(s16 *)&p->pad[0] = 0x78;
    n = D_80098CC4[(u8)p->pad[2]];
    for (i = 0; i < n; i++) {
        *(f32 *)(p->unk0 + i * 0x68 + 0x4C) = (s32)(func_150ADA20() % 20U) - 5;
    }
}

void func_1503F368(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 2.0f, 2.0f, 0);
}

void func_1503F39C(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 1.0f, 2.0f, 1);
}

void func_1503F3C8(s32 arg0, s32 arg1) {
    func_1503EE68(arg0, 2.06f, 3.0f, 1);
}

extern s32 D_800CC784;

void func_1503F3F8(s32 arg0) {
    struct106 *temp_v0;

    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = 0x8C;
    *(s32 *)((u8 *)&D_800CC784 + (arg0 * 0x32C)) = 6;
    (*(f32 *)((u8 *)(temp_v0->unk0) + 0x1EC)) = 10.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6B970/func_1503F45C.s")

#ifndef NON_MATCHING
s32 func_1503E550(s32);
#endif
void func_1503EF90(s32);
s32 func_1503F23C(s32, s32, s32);

void func_1503F5A0(s32 arg0) {
    struct106 *temp_v0;
    struct127 *temp_v0_2;
    struct127 *temp_v0_3;
    struct127 *temp_v0_4;

    func_1503EF90(arg0);
    temp_v0 = &D_800C6660[arg0];
    (*(s16 *)((u8 *)temp_v0 + 0xC)) = (s16) ((*(s16 *)((u8 *)temp_v0 + 0xC)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)temp_v0 + 0xC)) <= 0) {
        func_1503E550(arg0);
        if (func_1503F23C(2, 0, arg0) != 0) {
            temp_v0_2 = &D_800CC2D0[arg0];
            temp_v0_2->unk94 |= 8;
        }
        if (func_1503F23C(2, 1, arg0) != 0) {
            temp_v0_3 = &D_800CC2D0[arg0];
            temp_v0_3->unk94 |= 4;
        }
        if (func_1503F23C(2, 2, arg0) != 0) {
            temp_v0_4 = &D_800CC2D0[arg0];
            temp_v0_4->unk94 |= 2;
        }
    }
}

s32 func_1503E5F8(f32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1503F6F4(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    f32 sp30[16];
    if (D_800C42B0 != 0) {
        guMtxL2F((f32 (*)[4]) sp30, arg0);
    } else {
        memcpy(sp30, arg0, 0x40);
    }
    func_1503E5F8(sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
