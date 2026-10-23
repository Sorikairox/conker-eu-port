#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1507E1D0(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_1507CD0C(struct127 *arg0);
void func_1507D4F8(s32);
#endif


void func_1507C8E0(struct127 *arg0, s32 arg1) {
    arg0->unk31C->unk120 = (u8)2;
    arg0->unk31C->unk124 = arg1;
}

// "goto" hell
#ifdef NON_MATCHING
void func_1517FD84(s32, f32, f32, f32, s32);
extern u16 D_8009015C;
extern s32 D_800BEB30;
extern u16 D_800D1CC2;

void func_1507C8FC(void) {
    struct {
        f32 u60;
        f32 u64;
        f32 u68;
    } sp;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 var_s2;
    s8 var_v1;
    struct126 *temp_s0;
    struct126 *temp_s0_2;
    struct126 *temp_s0_3;
    struct126 *temp_s0_4;
    struct127 *var_s1;
    u8 var_v0;

    if (D_800BEAC0 == 0) {
        var_v1 = D_8008FD8C;
        var_s1 = D_800CC2D0;
        var_s2 = 0;
        if (var_v1 > 0) {
            do {
                temp_s0 = var_s1->unk31C;
                if (temp_s0 != NULL) {
                    var_v0 = temp_s0->unk120;
                    if (var_v0 == 0) {
                        temp_s0->pad126 = 0;
                        goto block_54;
                    }
                    if (var_v0 != 1) {
                        if (D_80082FA0 >= var_s2) {
                            if ((D_800BE616 != 0) && (D_800D1CC2 & (1 << var_s2))) {
                                temp_s0->unk120 = 2;
                                var_s1->unk31C->unk124 = 0x3C;
                                var_v0 = var_s1->unk31C->unk120;
                            }
                            if (var_v0 == 0xB) {
                                func_1517F3B0(0, 0, 0, 0xF, 1, var_s2);
                                var_s1->unk31C->unk120 = 0xC;
                            } else if (var_v0 == 0xC) {
                                if (func_1517F51C(var_s2, 0) != 0) {
                                    func_1507D4F8(var_s2);
                                }
                            } else {
                                if (var_v0 == 2) {
                                    temp_v0 = var_s1->unk31C->unk124;
                                    if (temp_v0 > 0) {
                                        var_s1->unk31C->unk124 = temp_v0 - D_800BE9E4;
                                    } else {
                                        func_1507CD0C(var_s1);
                                    }
                                } else if (var_v0 == 7) {
                                    temp_v0_2 = var_s1->unk31C->unk124;
                                    if (temp_v0_2 > 0) {
                                        var_s1->unk31C->unk124 = temp_v0_2 - D_800BE9E4;
                                    } else {
                                        var_s1->unk31C->unk120 = 8;
                                        func_1506160C(var_s1, 2U, 0U, 0x3CU, 0U);
                                    }
                                }
                                var_s1->unk31C->pad126 += D_800BE9E4;
                                if ((*(u16 *)((u8 *)&D_800BEB30 + (var_s2 * 2)) & 0x8000) || ((D_800BE616 != 0) && (var_s1->unk31C->unk84 == 0)) || (func_150859AC((s16) var_s2, 3) < 2) || ((temp_s0_2 = var_s1->unk31C, (temp_s0_2->unk84 == 1)) && ((s16) temp_s0_2->pad126 >= 0xB5))) {
                                    var_s1->unk31C->unk122 = 1;
                                }
                                if (D_8009015C & 0x80) {
                                    var_s1->unk31C->unk122 = 0;
                                }
                                func_1507E1D0((u8 *) var_s1, &sp.u68, &sp.u64, &sp.u60);
                                func_1517FD84(0, sp.u68, sp.u64, sp.u60, var_s2);
                                temp_s0_3 = var_s1->unk31C;
                                if ((temp_s0_3->unk122 != 0) && (temp_s0_3->unk120 == 5)) {
                                    temp_s0_3->unk120 = 6;
                                }
                                if (var_s1->unk31C->unk120 == 9) {
                                    func_1507D4F8(var_s2);
                                }
                            }
                        } else if (var_v0 == 0xB) {
                            func_1507D4F8(var_s2);
                        } else if (var_v0 == 2) {
                            temp_v0_3 = temp_s0->unk124;
                            if (temp_v0_3 > 0) {
                                temp_s0->unk124 = temp_v0_3 - D_800BE9E4;
                            } else {
                                temp_s0->unk120 = 7;
                            }
                        } else {
                            temp_s0->pad126 = (s16) temp_s0->pad126 + D_800BE9E4;
                            if ((var_s1->unk7 == 0xFF) && ((s16) var_s1->unk31C->pad126 >= 0x86)) {
                                func_1506160C(var_s1, 2U, 0U, 0x3CU, 0U);
                            }
                            temp_s0_4 = var_s1->unk31C;
                            if (((s16) temp_s0_4->pad126 >= 0x97) && (temp_s0_4->unk120 != 0xA)) {
    s32 pad;
                                func_1507D4F8(var_s2);
                            }
                        }
block_54:
                        var_v1 = D_8008FD8C;
                    }
                }
                var_s2 += 1;
                var_s1 = (struct127 *)((u8 *)var_s1 + (0x32C));
            } while (var_s2 < var_v1);
        }
        D_8009015C &= 0xFF7F;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")
#endif
void func_1507CD0C(struct127 *arg0) {
    s32 temp_lo = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);

    arg0->unk31C->unk120 = 3;

    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 tmp = D_800CC82F[arg0 * 812];
    func_1509BFB0(3, tmp | 0x2000, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")

#ifdef NON_MATCHING
void func_15085710(s16, s16, s32);
s32 func_150859AC(s16 arg0, s32 arg1);
void func_1507D1D8(struct127 *);
void func_1501C710(s32, s32, s32, s32, s32);
void func_1509C3A0(void);
extern u16 D_8009015C;
extern s8 D_8008726C;
extern s8 D_80087260;
extern u8 D_800BE800;
extern s8 D_8008FDA8;
extern s8 D_800E1050;
extern u8 D_800BE616;
extern u16 D_800D18A0;
extern u8 D_800D2E43;
extern u8 D_800D18A8;
extern s8 D_80090134;
extern s8 D_800BEA38;
extern struct127 D_800CC2D0[];

/* A player record (index idx) has lost a life. With lives left (func_150859AC(idx, 3)) the life counter (5) is
 * reset and the record respawns: in multiplayer (D_800BE616) via func_1507D1D8 or a 10-frame timer, else a
 * checkpoint restart (func_1501C710). Out of lives: game over (single player) or the player is marked out in
 * D_800D18A0 (multiplayer); then the active-player counters drop. void: no caller uses a result. */
void func_1507D4F8(s32 idx) {
    struct127 *rec;
    u8 *ctl;

    if (!(D_8009015C & 1)) {
        func_15085710(idx, 4, 1);
    }
    if (func_150859AC(idx, 3) != 0) {
        func_15085710(idx, 5, D_8008726C);
        rec = &D_800CC2D0[idx];
        *(s16 *)((u8 *)rec + 0xB2) = 0;
        if (D_800BE616 != 0) {
            if (D_800E1050 == 0) {
                func_1507D1D8(rec);
                return;
            }
            *((u8 *)rec->unk31C + 0x120) = 10;
            return;
        }
        D_800D18A8 = 1;
        if (!(D_800D2E4C->unk19 & 4) && D_8008FDA8 >= 0) {
            func_1501C710(1, 0x22, 0, 0, 0);
        } else {
            func_1501C710(2, (s8)D_800BE3DF, D_800BE800, 0, 0);
        }
        return;
    }
    if (D_800BE616 == 0) {
        D_800D2E43 = 1;
        func_1509C3A0();
        D_800D18A8 = 1;
        func_15085710(idx, 5, D_8008726C);
        func_15085710(idx, 2, D_80087260);
        func_1501C710(1, 0x18, 0, 0, 0);
    } else {
        D_800D18A0 |= 1 << idx;
    }
    ctl = (u8 *)D_800CC2D0[idx].unk31C;
    if (ctl[0x84] == 0) {
        D_80090134--;
    }
    ctl[0x120] = 10;
    D_800BEA38--;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
#endif
// NON-MATCHING: pretty far away!
// void func_1507D4F8(s16 arg0) { // struct126 *
//     // ?32 sp24;
//     struct127 *temp_a0;
//
//     if ((D_8008FDBC & 1) == 0) {
//         func_15085710(arg0, 4, 1);
//     }
//     // sp24 = (?32) arg0;
//     if (func_150859AC(arg0, 3) != 0) {
//         func_15085710(arg0, 5, D_8008726C); //temp_ret =
//         temp_a0 = &D_800CC2D0[arg0];
//         temp_a0->unkB2 = (u16)0;
//         if (D_800BE616 == 0) {
//             D_800D18A8 = (u8)1;
//             if (((D_800D2E4C->unk19 & 4) != 0) || (D_8008FDA8 < 0)) {
//                 func_1501C730(2, D_800BE3DF, D_800BE3E0, 0, 0);
//                 return;
//             }
//             func_1501C730(1, 0x22, 0, 0, 0);
//             return;
//         }
//         if (D_800E0C20 != 0) {
//             temp_a0->unk31C->unk120 = (u8)0xA;
//             return; // temp_ret;
//         }
//         func_1507D1D8(temp_a0);
//         return;
//     }
//     if (D_800BE616 == 0) {
//         D_800D2E43 = (u8)1;
//         func_1509C3A0();
//         D_800D18A8 = (u8)1;
//         func_15085710(arg0, 5, D_8008726C);
//         func_15085710(arg0, 2, D_80087260);
//         func_1501C730(1, 0x18, 0, 0, 0);
//     } else {
//         D_800D18A0 = (u16) (D_800D18A0 | (1 << (s32) arg0));
//     }
//     // temp_a0 = &D_800CC2D0[arg0];
//     if (temp_a0->unk31C->unk84 == 0) {
//         D_8008FD94 -= 1; //(s8) (D_8008FD94 - 1);
//     }
//     temp_a0->unk31C->unk120 = (u8)0xA;
//     D_800BE618 -= 1; //(s8) (D_800BE618 - 1);
//     //return temp_a0_2->unk31C;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")

void func_1507DB44(s32 arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}

#ifdef NON_MATCHING
s32 func_1510D66C(s32 *, s32, s32, s32);
void func_15182338(s32);
extern s32 D_80086F20;
extern u16 D_800D1CC2;
extern s32 D_800D1CC4;
extern s32 D_D11;

u8 *func_1507DB6C(u8 *arg0, s32 arg1) {
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_a1;
    u16 temp_a2;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 temp_a1;
    u8 temp_t5;
    u8 temp_t8;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_v1;
    u8 *var_s0;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xDE000000;
    (*(s32 **)((u8 *)arg0 + 4)) = &D_80086F20;
    temp_s0 = arg0 + 8;
    temp_v0 = func_1510D66C(&D_D11, 0, 3, 0);
    (*(s32 *)((u8 *)temp_s0 + 0)) = 0xFD180000;
    (*(s32 *)((u8 *)temp_s0 + 4)) = temp_v0;
    temp_s0_2 = temp_s0 + 8;
    (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xF5180000;
    (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0x07080200;
    temp_s0_3 = temp_s0_2 + 8;
    (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0;
    temp_s0_4 = temp_s0_3 + 8;
    (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xF3000000;
    (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0x073FF000;
    temp_s0_5 = temp_s0_4 + 8;
    (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0;
    temp_s0_6 = temp_s0_5 + 8;
    (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF5181000;
    (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x80200;
    temp_s0_7 = temp_s0_6 + 8;
    (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xF2000000;
    (*(s32 *)((u8 *)temp_s0_7 + 4)) = 0x7C07C;
    temp_s0_8 = temp_s0_7 + 8;
    (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xEF002C3F;
    (*(s32 *)((u8 *)temp_s0_8 + 4)) = 0x0F0A4004;
    var_s0 = temp_s0_8 + 8;
    temp_a2 = D_800D1CC2;
    temp_t0 = 1 << arg1;
    if (temp_a2 & temp_t0) {
        temp_v0_2 = ((s32 *)((u8 *)&D_800D1CC4 + arg1));
        temp_a1 = *temp_v0_2;
        temp_t8 = temp_a1 - 4;
        if ((s32) temp_a1 >= 4) {
            *temp_v0_2 = temp_t8;
            var_a1 = temp_t8 & 0xFF;
            goto block_6;
        }
        D_800D1CC2 = temp_a2 & ~temp_t0;
        func_15182338(arg1);
        func_1517F3B0(0, 0, 0, 0x78, 0, arg1);
    } else {
        temp_v0_3 = ((s32 *)((u8 *)&D_800D1CC4 + arg1));
        temp_t5 = *temp_v0_3 + 4;
        var_a1 = temp_t5 & 0xFF;
        *temp_v0_3 = temp_t5;
        if (var_a1 >= 0x3D) {
            *temp_v0_3 = 0x3C;
            var_a1 = 0x3C & 0xFF;
        }
block_6:
        temp_v1 = D_800BE628 + (arg1 * 0x180);
        temp_v0_4 = var_a1 + 4;
        temp_s0_9 = var_s0 + 8;
        temp_s0_10 = temp_s0_9 + 8;
        temp_t2 = (s32) ((*(f32 *)((u8 *)temp_v1 + 0x30)) + (*(f32 *)((u8 *)temp_v1 + 0x2C))) * 2;
        temp_a3 = temp_t2 - temp_v0_4;
        temp_t4 = (s32) ((*(f32 *)((u8 *)temp_v1 + 0x28)) + (*(f32 *)((u8 *)temp_v1 + 0x24))) * 2;
        temp_a2_2 = temp_t2 + temp_v0_4;
        (*(s32 *)((u8 *)var_s0 + 0)) = (s32) (((temp_a2_2 & 0xFFF) << 0xC) | 0xE4000000 | ((temp_t4 + temp_v0_4) & 0xFFF));
        (*(s32 *)((u8 *)var_s0 + 4)) = (s32) (((temp_a3 & 0xFFF) << 0xC) | ((temp_t4 - temp_v0_4) & 0xFFF));
        (*(s32 *)((u8 *)temp_s0_9 + 0)) = 0xE1000000;
        (*(s32 *)((u8 *)temp_s0_9 + 4)) = 0;
        temp_t2_2 = (0x20000 / (s32) (temp_a2_2 - temp_a3)) & 0xFFFF;
        (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xF1000000;
        (*(s32 *)((u8 *)temp_s0_10 + 4)) = (s32) ((temp_t2_2 << 0x10) | temp_t2_2);
        var_s0 = temp_s0_10 + 8;
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")
#endif
void func_1507DE4C(struct127 *arg0) {

    if (arg0->interaction_state == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        arg0->unk9C |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }

    switch(arg0->id) {
        case 0x9F:
        case 0xa0:
            arg0->unk9C |= 0xF000;
            break;
        case 0x5A:
        case 0x74:
        case 0x7A:
            arg0->unk9C |= 0xFF8;
            break;
    }
}


void func_1507DF10(u8 *arg0, s32 arg1) {
    switch (arg1) {
    case 9:
        *(s32 *)(arg0 + 0x94) |= 0x20;
        *(s32 *)(arg0 + 0x9C) |= 0x78;
        *(s32 *)(arg0 + 0x2E4) = 1;
        break;
    case 8:
        *(s32 *)(arg0 + 0x94) |= 0x40;
        *(s32 *)(arg0 + 0x94) &= ~0x200;
        *(s32 *)(arg0 + 0x9C) |= 0xF00;
        *(s32 *)(arg0 + 0x2E4) = 2;
        break;
    case 6:
    case 7:
        *(s32 *)(arg0 + 0x94) |= 0xE;
        *(s32 *)(arg0 + 0x94) &= ~0x410;
        *(s32 *)(arg0 + 0x9C) |= 0xEE0000;
        *(s32 *)(arg0 + 0x2E4) = 4;
        break;
    case 4:
    case 5:
        *(s32 *)(arg0 + 0x94) |= 0x80;
        *(s32 *)(arg0 + 0x94) &= ~0x500;
        *(s32 *)(arg0 + 0x2E4) = 8;
        break;
    }
}
#ifdef NON_MATCHING
s32 func_1501D348(s32, s32, s32, s32, s32);
void func_15022238(s16, s16, s16, f32);
s32 func_150851E0(s32, s32, s32, s16 *, s32 *, s32 *, u8 *, s32 *, s32 *, s32, s32 *);

void func_1507DFE4(s32 arg0, s32 arg1) {
    struct {
        s32 u38;
        s32 u3C;
        u8 pad40[0x4];
        s32 u44;
        s32 u48;
        u8 pad4C[0x2];
        u8 u4E;
        s32 u4F;
        u8 pad53[0x9];
        s16 u5C;
        s32 u5E;
        u8 pad62[0x2];
        s32 u64;
    } sp;
    s32 temp_t8;

    if (D_800C35EA != 1) {
        func_150851E0(0, arg0, 1, &sp.u5C, &(*(s32 *)((u8 *)&sp + 0x18)), &sp.u4F, &sp.u4E, &sp.u44, &sp.u48, 1, &sp.u38);
        if (sp.u38 == 0) {
            sp.u3C = 1;
            goto block_5;
        }
        if (sp.u38 == 1) {
            sp.u3C = 3;
block_5:
            func_15022238(sp.u5C, sp.u5E, (*(s32 *)((u8 *)&sp + 0x28)), ((f32) (sp.u4E - 0x40) * 1.40625f) + 180.0f);
            temp_t8 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            D_800C3671 = 1;
            sp.u64 = temp_t8;
            func_1501D348(0x25, sp.u3C, 0, 0, 0);
            D_800C3670 = 1;
            D_800BE9F0 = sp.u64;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
#endif
s32 func_1507E114(s32 arg0) {
    s32 sp5C;
    s32 sp54[2];
    s32 sp48[3];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;

    if (D_800D18A8 == 0) {
        return 0;
    }
    if ((s32)D_800BE9F4 == 0x22 || (s32)D_800BE9F4 == 0x18) {
        return 0;
    }
    D_800BE9F4 = (u16 *)(s32)(s8)D_800BE3DF;
    func_150851E0(0, D_800BE800, 1, sp54, sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}
void func_1507E1D0(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 *var_a2;
    f32 sp28[3];
    f32 sp1C[3];
    if ((*(u8 **)((u8 *)arg0 + 0x1D4)) != NULL) {
        s32 temp_v0;
        sp28[0] = 0.0f;
        sp28[1] = (*(f32 *)((u8 *)arg0 + 0x150)) * 30.0f;
        sp28[2] = 0.0f;
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0));
        var_a2 = (*(u8 **)((u8 *)arg0 + 0x1D4));
        if (temp_v0 == 1) {
            var_a2 += 0x300;
        } else if (temp_v0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(sp28, sp1C, var_a2);
        *arg1 = sp1C[0];
        *arg2 = sp1C[1];
        *arg3 = sp1C[2];
    } else {
    *arg1 = (*(f32 *)((u8 *)arg0 + 0x14));
    *arg2 = (*(f32 *)((u8 *)arg0 + 0x18));
    *arg3 = (*(f32 *)((u8 *)arg0 + 0x1C));
    }
}
