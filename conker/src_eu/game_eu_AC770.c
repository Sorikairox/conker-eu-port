#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1508039C(u8 *arg0);
#endif


void func_1507EF60(u8 *arg0, s32 *arg1, u8 arg2) {
    if ((*arg1 + 1) < 40) {
        arg0[*arg1] = arg2;
        (*arg1)++;
    }
}

extern u8 *D_80086FC4[];
extern u8 D_8009BFC0[];
void func_1507EF98(s32 arg0, s32 *arg1, s32 arg2) {
    u8 *src;
    s32 len;
    s32 v;
    src = D_80086FC4[arg2];
    len = D_8009BFC0[arg2];
    v = *arg1;
    if (v + len < 0x28) {
        bcopy(src, v + arg0, len);
        *arg1 += len;
    }
}

#ifdef NON_MATCHING
s32 func_1507F018(u8 *arg0, s32 arg1, u8 *arg2, s32 *arg3, u8 *arg4) {
    struct {
        s32 u2C;
    } sp;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_t1;
    u8 *var_t2;
    u8 *var_t4;
    u8 *var_t5;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 *var_v0_3;

    var_v1 = 0;
    *arg3 = 0;
    var_v0 = 0;
    if (arg1 > 0) {
        do {
            temp_t1 = *arg3;
            var_a0 = 0;
            var_t0 = 0;
            var_t2 = arg2;
            if (temp_t1 > 0) {
loop_4:
                var_t0 += 1;
                if (*var_t2 == *(arg0 + var_v0)) {
                    var_a0 = 1;
                } else {
                    var_t2 += 1;
                    if (var_t0 < temp_t1) {
                        goto loop_4;
                    }
                }
            }
            if (var_a0 == 0) {
                temp_t2 = *(arg0 + var_v0);
                var_t0_2 = 0;
                var_t5 = arg4;
loop_9:
                var_t0_2 += 1;
                if (*var_t5 == temp_t2) {
                    var_a0 = 1;
                } else {
                    var_t5 += 1;
                    if (var_t0_2 != 5) {
                        goto loop_9;
                    }
                }
                if (var_a0 == 0) {
                    *(arg2 + temp_t1) = temp_t2;
                    *arg3 += 1;
                }
            }
            var_v0 += 1;
        } while (var_v0 != arg1);
    }
    var_a0_2 = 0;
    var_v0_2 = 0;
    if (*arg3 == 0) {
        var_t1 = arg4;
        do {
            temp_t2_2 = *var_t1;
            var_v0_2 += 1;
            if (temp_t2_2 != 0) {
                var_t0_3 = 0;
                if (arg1 > 0) {
                    var_t4 = arg0;
loop_20:
                    var_t0_3 += 1;
                    if (temp_t2_2 == *var_t4) {
                        *(&sp.u2C + var_a0_2) = temp_t2_2;
                        var_a0_2 += 1;
                    } else {
                        var_t4 += 1;
                        if (var_t0_3 != arg1) {
                            goto loop_20;
                        }
                    }
                }
            }
            var_t1 += 1;
        } while (var_v0_2 < 5);
        if (var_a0_2 == 0) {
            *arg2 = 0;
            *arg3 = 1;
        } else {
            var_v1_2 = var_a0_2 >> 1;
            if (var_v1_2 == 0) {
                var_v1_2 = 1;
            }
            if (var_v1_2 != 0) {
                temp_a1 = -(var_v1_2 & 3);
                var_v0_3 = var_a0_2 + &sp.u2C;
                if (temp_a1 != 0) {
                    temp_a0 = temp_a1 + var_v1_2;
                    do {
                        var_v1_2 -= 1;
                        *(arg2 + *arg3) = (*(u8 *)((u8 *)var_v0_3 + -1));
                        var_v0_3 -= 1;
                        *arg3 += 1;
                    } while (temp_a0 != var_v1_2);
                    if (var_v1_2 != 0) {
                        goto loop_33;
                    }
                } else {
                    do {
loop_33:
                        var_v1_2 -= 4;
                        *(arg2 + *arg3) = (*(u8 *)((u8 *)var_v0_3 + -1));
                        var_v0_3 -= 4;
                        temp_t8 = *arg3 + 1;
                        *arg3 = temp_t8;
                        *(arg2 + temp_t8) = (*(u8 *)((u8 *)var_v0_3 + 2));
                        temp_t9 = *arg3 + 1;
                        *arg3 = temp_t9;
                        *(arg2 + temp_t9) = (*(u8 *)((u8 *)var_v0_3 + 1));
                        temp_t7 = *arg3 + 1;
                        *arg3 = temp_t7;
                        *(arg2 + temp_t7) = (*(u8 *)((u8 *)var_v0_3 + 0));
                        *arg3 += 1;
                    } while (var_v1_2 != 0);
                }
            }
            var_v1 = 1;
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F018.s")
#endif
void func_1507F238(u8 arg0, u8 *arg1) {
    func_1507F298(arg0, arg1);
    if (arg0 == 0x11) {
        func_1507F298(0x12, arg1);
    } else if (arg0 == 0x12) {
        func_1507F298(0x11, arg1);
    }
}

void func_1507F298(u8 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i > 0; i--) {
        arg1[i] = arg1[i - 1];
    }
    arg1[0] = arg0;
}

void func_1507F2D4(void)
{
  u8 *p;
  s32 type;
  p = (u8 *)D_800D154C->unk31C;
  type = p[0x64];
  p += 0x58;
  if (type == 0) {
    p[0xC] = 1;
    p[0xD] = 0;
  } else if (type == 1) {
    func_150ADA20();
    if (p[0xD] >= 3) {
      p[0xC] = 2;
      p[0xD] = 0;
    }
  } else {
    if (p[0xD] >= (func_150ADA20() & 3) + 8) {
      p[0xC] = 1;
      p[0xD] = 0;
    }
  }
}

void func_1507F380(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 4; i >= 0; i--) {
        if (arg0 == arg1[i]) {
            arg1[i] = 0;
            return;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F3B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F834.s")

s32 func_1507F8A0(s32 arg0) {
    s32 pad;
    s32 var_v1;
    u32 var_a0;

    if (arg0 == 0) {
        var_v1 = 0x96;
        var_a0 = 0x32;
        goto block_7;
    }
    if (D_800BE9F0 == 0x31) {
        return 0;
    }
    var_v1 = 0;
    if (arg0 == 1) {
        var_v1 = 0x32;
        var_a0 = 0x32;
    } else {
        var_a0 = 0x1E;
    }
block_7:
    return (func_150ADA20() % var_a0) + var_v1;
}

extern u8 D_800B89C4[];

void func_1507F92C(struct127 *arg0) {
    s32 v;

    if (arg0->unk13C >= 0x64) {
        switch (D_800B89C4[arg0->unk13C * 0x32C]) {
        case 0x57:
            v = 0x115;
            break;
        case 0x8C:
            v = 0x1A5;
            break;
        case 0xA8:
        case 0xA9:
            v = 0x1AF;
            break;
        case 0x89:
        case 0xBA:
            v = 0x1FA;
            break;
        default:
            v = 0xD8;
            break;
        }
        func_1505E650(arg0, v, 1.0f, 4.0f, 0.0f, 0.0f, 0);
    } else {
        func_1505E650(arg0, 0xF, 1.0f, 3.0f, 0.0f, 0.0f, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1507F640.s")

#ifdef NON_MATCHING
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_1000E7A0(u32, s32);
void func_1000E8C4(s32);
void func_100109D0(struct127 *arg0);
extern u8 *D_80086F40[];
extern u8 D_8009BC80[][8];
extern s32 D_80041C50[];
extern u8 D_80041D40;
extern s32 D_800D1CE4;

/* Per-frame surface effects of the record's current floor material (ctl = rec->unk31C + 0x58: +4 material set,
 * +5 index, +6 the flags applied last frame). Flags (D_8009BC80[mat][6]): 0x10 scales the model's +0x08 by the
 * D_80041C50 level, and on change 1 = record flag unk2F8 bit 0, 2 = func_1000E7A0 / func_1000E8C4, 4 = ambient
 * loop 0x15 / 0x16 (D_800D1CE4) start / stop, 8 cleared = func_100109D0. */
void func_1508000C(struct127 *rec) {
    u8 *ctl = (u8 *)rec->unk31C + 0x58;
    u8 set = ctl[4];
    u8 flags = 0;
    u8 old;
    u8 changed, gained, lost;
    f32 k;

    if (set != 0) {
        flags = D_8009BC80[D_80086F40[set][ctl[5]]][6];
    }
    if (flags & 0x10) {
        k = ((f32)D_80041C50[D_80041D40 * 16] - 5462.0f) * 1.2f;
        if (k < 0.0f) {
            k = 0.0f;
        }
        rec->unk2D0->unk8 = ((rec->unk2D0->unk18 - 1.0f) * (32768.0f - k)) / 32768.0f;
    }
    old = ctl[6];
    if (flags == old) {
        return;
    }
    changed = flags ^ old;
    gained = changed & flags;
    lost = changed & old;
    if (gained & 1) {
        rec->unk2F8 |= 1;
    } else if (lost & 1) {
        rec->unk2F8 &= ~1;
    }
    if (gained & 2) {
        func_1000E7A0(1, 0);
    } else if (lost & 2) {
        func_1000E8C4(1);
    }
    if (gained & 4) {
        if (D_800D1CE4 == 0) {
            D_800D1CE4 = 0x15;
        } else if (D_800D1CE4++ == 0x17) { /* 0x15 -> 0x16 -> 0x17 -> 0x15 */
            D_800D1CE4 = 0x15;
        }
        func_1000D96C(D_800D1CE4, 0, 0);
    } else if (lost & 4) {
        func_1000DE1C(D_800D1CE4, 0);
    }
    if (lost & 8) {
        func_100109D0(rec);
    }
    ctl[6] = flags;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_1508000C.s")
#endif
#ifdef NON_MATCHING
void func_1508000C(struct127 *);

void func_150802A8(struct127 *arg0) {
    s16 temp_v0_2;
    struct126 *temp_a1;
    struct126 *temp_a1_3;
    u16 temp_a1_2;
    u8 *temp_v0;
    u8 temp_v1;

    temp_a1 = arg0->unk31C;
    if ((temp_a1 != NULL) && (arg0->unk127 != 0xFF)) {
        temp_v1 = arg0->unk13A;
        temp_v0 = &temp_a1->unk58;
        if (temp_v1 != 0) {
            arg0->unk13A = temp_v1 - 1;
        }
        if (((*(u8 *)((u8 *)temp_v0 + 0)) == 1) && (D_800C35EA != 1)) {
            temp_a1_2 = (*(u16 *)((u8 *)temp_v0 + 2));
            if ((s32) temp_a1_2 < (0xFFFF - D_800BE9E4)) {
                (*(u16 *)((u8 *)temp_v0 + 2)) = (u16) (temp_a1_2 + D_800BE9E4);
            }
        } else {
            (*(u16 *)((u8 *)temp_v0 + 2)) = 0U;
            (*(s8 *)((u8 *)temp_v0 + 4)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 5)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 0xC)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 0xD)) = 0;
        }
        temp_a1_3 = arg0->unk31C;
        temp_v0_2 = (s16) temp_a1_3->unk66;
        if (temp_v0_2 != 0) {
            if (D_800BE9E4 < temp_v0_2) {
                temp_a1_3->unk66 = temp_v0_2 - D_800BE9E4;
            } else {
                func_1508039C((u8 *) arg0);
                arg0->unk31C->unk66 = 0;
            }
        }
        func_1508000C(arg0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150802A8.s")
#endif
void func_1508039C(u8 *arg0)
{
  u8 *sp20[2];
  s32 sp1C;
  sp1C = 1;
  sp20[0] = arg0;
 if (0) { }
  if (sp1C)
  {
    sp1C = (s32) sp20;
    ((u8 *) sp20)[4] = arg0[0x3B];
    func_151920FC(sp1C, 0xD);
  }
  func_151494E0(0xFFFFFFFFFFFFFFFF & sp1C, 0xD);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_AC770/func_150803E0.s")
