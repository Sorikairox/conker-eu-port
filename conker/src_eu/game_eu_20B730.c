#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151E5D28(void);

extern u8 D_800D3260;

extern s8 D_80090144;

void func_1501C710(s32, s32, s32, s32, s32);


void func_151DDF20(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        D_800E1010[i] = D_800901F4[i];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DDF6C.s")

s32 func_151DE074(s32 arg0) {
    return ~arg0;
}

s32 func_1000E934();
s32 func_1000F1A8();

void func_151DE080(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_800BEAC1 = 0;
    func_151E5D28();
    func_1000F1A8();
    func_1000E934();
    D_8008FD8C = 1;
    D_80090130 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")

void func_151E5AB8(void);
void func_151DEBB4(void) {
    func_151E5AB8();
    *(s32 *)((u8 *)D_800CC2D0 + 0x25C) |= 0x200;
    D_800CC2D0[0].y_position = 1000.0f;
    if (D_80000300 != 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x119 && (D_800E0FCA & 0x8000)) {
        if (D_800E0EC0 < 0x190) {
            D_800E0EC0 = 0x190;
        }
        if (D_800E0EC0 >= 0x1F5 && D_800E0EC0 < 0x258) {
            D_800E0EC0 = 0x258;
        }
    }
    if (D_800E0EC0 >= 0x2C7) {
        D_800901C8 = 2;
        D_800E0B94 = 1;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
        *(u8 *)&D_800E0FC6 = 0xFF;
    }
}

void func_151DED3C(void);

void func_151DECB4(void) {
    D_800E0EC0 = 0;
    D_800E0FC7 = 0;
    D_800E0FC8 = 0;
    D_800E0EBC = 0;
    D_800901C8 = 2;
    func_151DED3C();
}

void func_151DECFC(void) {
    D_80090114 = 4;
    D_800E0FC6 = 0;
    if (D_800901D0 == 0) {
        func_1500764C();
    }
}


void func_151DED3C(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090120 = 1;
    D_800901C8 = 2;
    D_80090144 = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 5;
    (*(s8 *)((u8 *)D_80090174 + 0x2C)) = (s8) (*(s8 *)((u8 *)D_80090174 + 0x2B));
}

void func_151DEDC8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEDD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DF6A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DFD0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E06D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1EDC.s")

void func_151E5AB8(void);
void func_151E4B40(void);

void func_151E2A1C(void) {
    D_80090120 = 3;
    func_151E5AB8();
    func_151E4B40();
    D_80090120 = 0;
}

#ifdef NON_MATCHING
s32 func_151DDF6C(s8, s8);
extern s32 D_80082F4C;
extern s32 D_800ABA74;

void func_151E2A54(void) {
    s8 temp_a1;
    u8 var_v1;
    u8 *temp_v0;

    temp_a1 = *(s8 *)((u8 *)&D_800ABA74 + *(s8 *)((u8 *)D_80090174 + 0x42) * 0xA);
    temp_v0 = (temp_a1 * 0xA) + D_80082F4C;
    var_v1 = (*(u8 *)((u8 *)temp_v0 + 3));
    if ((s32) var_v1 >= 5) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 4U;
        var_v1 = 4 & 0xFF;
    }
    if ((s32) var_v1 < 0) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 0U;
    }
    if ((*(s8 *)((u8 *)temp_v0 + 1)) <= 0) {
        (*(s8 *)((u8 *)temp_v0 + 1)) = 1;
    }
    (*(s8 *)((u8 *)D_800E1010 + 2)) = (*(s8 *)((u8 *)temp_v0 + 1));
    (*(s8 *)((u8 *)D_800E1010 + 0xB)) = 0;
    (*(s8 *)((u8 *)D_800E1010 + 3)) = (s8) (*(s8 *)((u8 *)temp_v0 + 2));
    (*(u8 *)((u8 *)D_800E1010 + 0x10)) = (u8) (*(u8 *)((u8 *)temp_v0 + 3));
    (*(u8 *)((u8 *)D_800E1010 + 0x11)) = (u8) (*(u8 *)((u8 *)temp_v0 + 4));
    if (temp_a1 == 0) {
        (*(u8 *)((u8 *)D_800E1010 + 4)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 1 || temp_a1 == 2) {
        (*(u8 *)((u8 *)D_800E1010 + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)D_800E1010 + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    } else if (temp_a1 == 7) {
        (*(u8 *)((u8 *)D_800E1010 + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 5) {
        (*(u8 *)((u8 *)D_800E1010 + 0x11)) = 0U;
        (*(u8 *)((u8 *)D_800E1010 + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 8 || temp_a1 == 9) {
        (*(u8 *)((u8 *)D_800E1010 + 7)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)D_800E1010 + 0x11)) = 1U;
        (*(s8 *)((u8 *)D_800E1010 + 3)) = 2;
        (*(u8 *)((u8 *)D_800E1010 + 0x13)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    }
    (*(u8 *)((u8 *)D_800E1010 + 0x16)) = (u8) (*(u8 *)((u8 *)temp_v0 + 8));
    (*(u8 *)((u8 *)D_800E1010 + 6)) = (u8) (*(u8 *)((u8 *)temp_v0 + 9));
    func_151DDF6C((*(s8 *)((u8 *)temp_v0 + 1)), temp_a1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2A54.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")

#ifdef NON_MATCHING
extern s8 D_800901E4;
extern s32 D_800901E8;
extern s32 D_800ABA78;
extern u8 D_800BEB60;
extern s32 D_800E0FFE;
extern s8 D_800E101E;

s8 func_151E2C88(s32 arg0) {
    struct {
        s8 u28;
        u8 pad29[0x3];
        s8 u2C;
        u8 pad2D[0x3];
        s32 u30;
        u8 pad34[0xC];
    } sp;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t5;
    s32 var_a2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a3;
    s32 var_a3_5;
    s8 *var_a2_2;
    s8 *var_a3_2;
    s8 *var_a3_3;
    s8 *var_t0;
    s8 *var_t0_2;
    s8 *var_t0_3;
    s8 *var_t0_4;
    s8 *var_t0_5;
    s8 *var_t0_6;
    s8 *var_t2;
    s8 *var_t2_2;
    s8 *var_t3;
    s8 *var_t3_2;
    s8 temp_a3;
    s8 temp_t6;
    s8 temp_t6_2;
    s8 temp_t9;
    s8 temp_t9_2;
    s8 var_a2_5;
    s8 var_a3_4;
    s8 var_v1;

    if (arg0 == 0) {
        (*(s8 *)((u8 *)(&D_800E0FFE) + 0)) = 0;
        (*(s8 *)((u8 *)(&D_800E0FFE) + 1)) = 0;
    }
    if (*(&D_800ABA78 + ((*(s8 *)((u8 *)D_80090174 + 0x42)) * 0xA)) == 8) {
        var_a2 = 0;
        var_v1 = 0;
        var_t0 = &sp.u2C;
        if (D_800E101E != 0) {
            do {
                var_t0 += 1;
                (*(s8 *)((u8 *)var_t0 + -1)) = 0;
            } while ((u32) var_t0 < (u32) &sp.u30);
            var_t0_2 = &D_800901E4;
            do {
                temp_a3 = *var_t0_2;
                var_t0_2 += 1;
                if (temp_a3 >= 0) {
                    var_v1 += 1;
                    (&sp.u2C)[temp_a3] = 1;
                    var_a2 = (var_a2 | (1 << temp_a3)) & 0xFF;
                }
            } while ((u32) var_t0_2 < (u32) &D_800901E8);
            if (var_v1 < 3) {
                var_a3 = 0;
                if (D_800BEB60 & ~var_a2 & 0xFF) {
                    var_a2_2 = &sp.u28;
                    do {
                        *var_a2_2 = 1;
                        if ((var_v1 == 1) && !(D_800BEB60 & (1 << var_a3))) {
                            *var_a2_2 = 0;
                        }
                        var_a3 += 1;
                        var_a2_2 += 1;
                    } while (var_a3 < 4);
                    var_a2_3 = 0;
                    if (arg0 == 0) {
                        temp_a1 = var_v1 * 2;
                        var_a2_4 = 0x10;
                        if (temp_a1 < 0x11) {
                            temp_t5 = -((0x11 - temp_a1) & 3);
                            if (temp_t5 != 0) {
                                temp_t1 = 0x10 - var_v1;
                                var_t2 = D_800E1030 + 0x10;
                                var_t3 = &D_800E1030[temp_t1];
                                var_t0_3 = &(&D_800901E4)[temp_t1];
                                var_a3_2 = &D_800901E4 + 0x10;
                                do {
                                    temp_t9 = *var_t0_3;
                                    temp_t6 = *var_t3;
                                    var_a2_4 -= 1;
                                    var_a3_2 -= 1;
                                    var_t0_3 -= 1;
                                    var_t2 -= 1;
                                    var_t3 -= 1;
                                    (*(s8 *)((u8 *)var_a3_2 + 1)) = temp_t9;
                                    (*(s8 *)((u8 *)var_t2 + 1)) = temp_t6;
                                } while ((temp_t5 + 0x10) != var_a2_4);
                                if ((var_a2_4 + 1) != temp_a1) {
                                    goto block_23;
                                }
                            } else {
block_23:
                                temp_t1_2 = var_a2_4 - var_v1;
                                var_t0_4 = &(&D_800901E4)[temp_t1_2];
                                var_t3_2 = &D_800E1030[temp_t1_2];
                                var_a3_3 = &(&D_800901E4)[var_a2_4];
                                var_t2_2 = &D_800E1030[var_a2_4];
                                do {
                                    var_t2_2 -= 4;
                                    *var_a3_3 = (*(s8 *)((u8 *)var_t0_4 + 0));
                                    (*(s8 *)((u8 *)var_t2_2 + 4)) = (s8) (*(s8 *)((u8 *)var_t3_2 + 0));
                                    var_a3_3 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 3)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -1));
                                    (*(s8 *)((u8 *)var_a3_3 + 3)) = (s8) (*(s8 *)((u8 *)var_t0_4 + -1));
                                    temp_t6_2 = (*(s8 *)((u8 *)var_t0_4 + -2));
                                    var_t0_4 -= 4;
                                    (*(s8 *)((u8 *)var_a3_3 + 2)) = temp_t6_2;
                                    (*(s8 *)((u8 *)var_t2_2 + 2)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -2));
                                    temp_t9_2 = (*(s8 *)((u8 *)var_t3_2 + -3));
                                    var_t3_2 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 1)) = temp_t9_2;
                                    (*(s8 *)((u8 *)var_a3_3 + 1)) = (s8) (*(s8 *)((u8 *)var_t0_4 + 1));
                                } while (var_t2_2 != (temp_a1 - 1 + D_800E1030));
                            }
                        }
                        var_a2_5 = var_v1;
                        var_a3_4 = 0;
                        if (var_v1 < temp_a1) {
                            var_t0_5 = &sp.u2C;
loop_27:
                            if (*var_t0_5 == 0) {
                                temp_t1_3 = var_a2_5 - var_v1;
                                if ((&sp.u28)[var_a3_4] != 0) {
                                    (&D_800901E4)[var_a2_5] = var_a3_4;
                                    D_800E1030[var_a2_5] = D_800E1030[temp_t1_3];
                                    *(&D_800E0FFE + temp_t1_3) = var_a2_5;
                                    D_80087270[var_a2_5] = 0xA;
                                    var_a2_5 += 1;
                                }
                            }
                            var_a3_4 += 1;
                            var_t0_5 += 1;
                            if (var_a3_4 < 4) {
                                if (var_a2_5 >= temp_a1) {
                                    return var_v1;
                                }
                                goto loop_27;
                            }
                            goto block_40;
                        }
                        goto block_40;
                    }
                    var_a3_5 = 0;
                    if (var_v1 > 0) {
                        var_t0_6 = &sp.u2C;
loop_35:
                        if ((*var_t0_6 == 0) && ((&sp.u28)[var_a3_5] != 0)) {
                            *(s32 *)(arg0 + (var_a2_3 * 4)) = var_a3_5;
                            var_a2_3 += 1;
                        }
                        var_a3_5 += 1;
                        var_t0_6 += 1;
                        if ((var_a3_5 < 4) && (var_a2_3 < var_v1)) {
                            goto loop_35;
                        }
                    }
block_40:
                    return var_v1;
                }
            }
            goto block_41;
        }
    }
block_41:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2C88.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")

void func_151E86A4(void);
extern s8 D_800E0FE1;
extern s8 D_800BEA38;
extern s8 D_80090134;
extern u8 D_800E0FC9;
extern s16 D_8009015C;
extern s8 D_800D27C8;
s32 func_1509D1EC(s32);
s32 func_1509D338(s8, s32 *);
s32 func_1509D49C(s8, u8, s32 *, s32 *);
extern s8 D_80090110;
extern s16 D_8009014C;
extern u8 D_80090154;
extern s8 D_800902B0;
extern u8 D_800902B4;
extern s32 D_800BE804;
extern u8 D_800E1001;

void func_151E3864(void) {

    s32 sp24[3];

    sp24[0] = 0;
    if (D_80090154 != 0) {
        sp24[1] = (s32) D_8009014C;
    } else {
        func_1509D338(D_800902B0, &sp24[2]);
        func_1509D49C(D_800902B0, D_800902B4, &sp24[1], sp24);
        func_1509D464();
    }
    func_15017790();
    func_1509D0A4(sp24[1]);
    func_1509D1EC(sp24[1]);
    D_800BE9F4 = func_1509CE40(sp24[1]);
    func_15085710(0, 9, sp24[0]);
    D_800BE804 = sp24[0];
    D_800DD2C0 = func_1509CE60(sp24[1]);
    if (D_80090154 == 2) {
        D_800DD2C0 = D_800E1001;
    }
    D_80090110 = 0;
    D_800D27C8 = 0;
    D_8009015C = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    D_800E0FC9 = 1;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_800BEA38 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0FE1 = 1;
    func_151E86A4();
    D_800D3260 = 1;
    func_1501C710(6, (s32) D_800BE9F4, func_1509CE60(sp24[1]), 0, 1);
}

void func_151E86A4(void);
extern s8 D_80090134;
extern s16 D_8009015C;
extern s8 D_800BEA38;
extern s8 D_800D27C8;
extern u8 D_800E0FC9;
extern s8 D_800E0FE1;

void func_151E3A1C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_8009015C = 0;
    D_800BEA38 = 1;
    D_800D27C8 = 0;
    D_800E0B94 = 0;
    D_800D3260 = 0;
    func_1501C710(6, (s32) (s8) D_800BE3DF, (s32) D_800BE800, 0, 1);
    D_800E0FC9 = 1;
    D_800E0FE1 = 1;
    func_151E86A4();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")

s32 func_151F2CDC();
void func_151F2D6C(s32, s32);
extern s32 *D_800E0EB8;
void func_151E2FCC(void);

void func_151E49C8(void) {
    if ((u8) D_80090120 != 0) {
        D_80090120 = 0;
        return;
    }
    func_151E5AB8();
    if ((D_800E0FCA != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x370C);
        }
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E2FCC;
        D_80090114 = 8;
    }
}

void func_1501D348(s32, s32, s32, s32, s32);
extern u8 D_800ABA76[][10];
extern s16 D_800ABB88[][2];
void func_151E4A78(void) {
    s8 *p;
    s8 temp_v1;
    s8 var_a1;
    temp_v1 = D_800ABA76[((s8 *)D_80090174)[0x42]][0];
    if (temp_v1 >= 0) {
        if (D_800E1030[0] != 0) {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[3];
        } else {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[2];
        }
        func_1501D348(*(s16 *)p, var_a1, 0, 0, 0);
        *(u8 *)&D_80090120 = 1; // fakematch: u8 store keeps the constant out of the CSE
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_80090130 = 1;
        return;
    }
    func_151E2FCC();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E533C.s")

void func_151E5528(void) {
    D_800E0B94 = 10;
}

void func_151E553C(void) {
    if (D_800E0FCA & 0x8020) {
        D_800E0B94 = 4;
    }
}

void func_151E5564(void) {
    D_8009016C = 0;
    func_151E5D28();
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_80090120 = 0;
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
}

s32 func_151E5D54();
extern s32 *D_800E0EB8;
void func_151E5564(void);

void func_151E55C8(void) {
    func_151E5AB8();
    func_151E5D54();
    if (D_800E0EC0 >= 0x3E9) {
        D_800E0FCA |= 0x8000;
    }
    if (D_800E0FCA != 0) {
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E5564;
        D_80090114 = 8;
    }
}

extern f32 D_80090170;
extern f32 D_800ABE30;
extern f32 D_800ABE34;
extern f32 D_800ABE38;

void func_151E564C(void)
{
  unsigned int n; // fakematch: permuter temp
  int ff; // fakematch: constant in a register gives beq a2,v0 operand order
  s32 v;
  f32 f;
  v = *((u8 *) (&D_800E0FC6));
  ff = 0xFF; // fakematch
  D_80090170 = 1.0f - (((u32) v) / 255.0f);
  if (((u8) D_80090114) == 0xFF)
  {
    f = D_800DDDC8;
    if (D_800ABE30 < f)
    {
      v = (u8) (D_800E0FC6 = v + D_800BE9E4);
      if (v < 0x55)
      {
        D_800DDDD8 = D_800ABE34;
      }
      else
      {
        D_800DDDD8 = D_800ABE38;
      }
    }
    if (f < ((float) 1.0f))
    {
      return;
    }
    if (v < 0x6E)
    {
      return;
    }
  }
  else
  {
    n = (u8) D_80090114;
    if (v != ff)
    {
      v += D_800BE9E4 * n;
      if (v >= 0x100)
      {
        v = 0xFF;
      }
      D_800E0FC6 = v;
      return;
    }
  }
  *((u8 *) (&D_800E0FC6)) = 0xFF;
  D_80090114 = 8;
  D_80090170 = 1.0f;
  if (1) // fakematch: empty ifs on separate lines
  {
  }
  if (1)
  {
  }
  ((void (*)(void)) D_800E0EB8)();
}

void func_151E5798(void) {
    (*(f32 *)D_80090174) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 4)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 0;
    (*(s16 *)((u8 *)D_80090174 + 0x20)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3F)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x41)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x43)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x44)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2A)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x14)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x18)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 8)) = 0.0f;
}

void func_151E73A8(void);
extern u8 D_800E0F20[];
extern u8 D_800AB950[];
extern u8 D_800E0FC5;

void func_151E582C(void) {
    s32 i;

    i = 0;
    do {
        D_800E1010[i] = D_800901F4[i];
        i++;
    } while (i < 0x1C);
    D_800E0EC0 = 0;
    func_151E73A8();
    if (D_80090174 == NULL) {
        D_80090174 = D_800E0F20;
        func_151E5798();
        if (*(s8 *)(D_80090174 + 0x3E) == 1) {
            *(s8 *)(D_80090174 + 0x2C) = D_800AB950[*(s8 *)(D_80090174 + 0x2C)];
        }
    }
    func_15017790();
    D_800E0B94 = 11;
    D_800D3260 = 0;
    func_1501C710(6, 0x25, 0, 0, 1);
    D_800E0FC5 = D_800E0B94;
}

#ifdef NON_MATCHING
// Per-frame game-mode step: screen offset/scale from the D_800E1010 settings, input snapshot,
// the mode's handler from the table D_8009018C[D_800E0B94], and the time-in-mode counter
// D_800E0EC0 (reset and the previous mode kept in D_800E0FC5 when the mode changed; mode 7 keeps it).
extern f32 D_800ABE3C;
extern s8 D_800E100C;
extern u16 D_800BED50;
extern u8 D_800E0FC5;
extern void (*D_8009018C[])(void);
void func_10003C10(s32 x, s32 y, f32 scaleY, f32 scaleX);
void func_151E7110(s32 arg0);

void func_151E5928(void) {
    u8 prevMode = D_800E0B94;

    func_10003C10((D_800E1010[0x17] - 16) * 2, (D_800E1010[0x18] - 8) * 2, D_800E1010[0x1A] * D_800ABE3C + 1.0f,
                  D_800E1010[0x1B] * D_800ABE3C + 1.0f);
    D_8003C8E0 = 0x08000000;
    D_800E100C = 0xFF;
    func_15042D78(0x81);
    D_800E0FCA = D_800BED50;
    if (D_800901C8 != 0) {
        D_800901C8--;
        D_800E0FCA = 0;
    }
    if (D_800E0B94 == 0) {
        func_151E7110(2);
    } else if (D_800E0B94 == 8) {
        func_151E7110(4);
    } else {
        func_151E7110(1);
    }
    D_8009018C[D_800E0B94]();
    if (D_800E0B94 != 7) {
        D_800E0EC0 += D_800BE9E4;
        if (prevMode != D_800E0B94) {
            D_800E0FC5 = prevMode;
            D_800E0EC0 = 0;
        }
    }
    D_8003C8E0 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5928.s")
#endif
void func_151E5AB8(void)
{
  f32 temp_f0;
  s32 var_v1_2;
  if (D_800E0B94 != 2)
  {
    if (((u8) D_800E0FC6) != 0)
    {
      var_v1_2 = ((u8) D_800E0FC6) - (D_800BE9E4 * ((u8) D_80090114));
      if (var_v1_2 < 0)
      {
        var_v1_2 = 0;
      }
      D_800E0FC6 = var_v1_2;
    }
    if (((D_80090174 != 0) && ((*((s8 *) (((u8 *) D_80090174) + 0x2B))) == 0)) && ((*((f32 *) (((u8 *) D_80090174) + 0xC))) > 0.0f))
    {
      temp_f0 = *((f32 *) (((u8 *) D_80090174) + 8));
      if (temp_f0 > 0.5f)
      {
        var_v1_2 = (s32) ((temp_f0 - 0.5f) * 524.0f);
        if (var_v1_2 >= 0x100)
        {
          var_v1_2 = 0xFF;
        }
        D_800E0FC6 = (s8) var_v1_2;
      }
    }
  }
}

void func_151E533C(void);
extern u8 D_800901CC;
extern u16 D_80090160;
extern u8 D_800E0EB6;
extern s8 D_800ABA70[][10];

void func_151E5B94(s32 arg0) {
    s32 i;

    D_800E0EC0 = 0;
    D_800901CC = 0;
    D_80087270[0] = 0;
    if (D_800BE616 != 0) {
        D_800E0B94 = 7;
        D_80090114 = 8;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] != -1) {
            D_80090174[0x3F] = 4;
            D_800E0EB8 = (s32 *)&func_151E533C;
        } else {
            D_80090174[0x3F] = 3;
            D_800E0EB8 = (s32 *)&func_151DE080;
        }
        for (i = 0; i < D_80090130; i++) {
            *(s16 *)(D_80090174 + i * 12 + 0x6C) = *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0[i] + 0x31C) + 0x1AA);
        }
        D_80090160 &= 0xE35F;
        D_800E0EB6 = arg0;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] == -2) {
            if (arg0 == 0) {
                func_151E533C();
            } else {
                D_800E0EB8 = (s32 *)&func_151DE080;
                D_80090174[0x3F] = 3;
            }
        }
    } else {
        D_800E0B94 = 4;
    }
}

void func_151E5D28(void) {
    D_800843F0[0] = 0;
    D_800843F0[1] = 1;
    D_800843F0[2] = 2;
    D_800843F0[3] = 3;
}

s32 func_151E5D54(void) {
    s32 d;
    s32 v;

    if ((u8)D_800E0FC8 == 0) {
        d = D_800BE9E4 * 8;
    } else {
        d = -D_800BE9E4 * 8;
    }
    v = (u8)D_800E0FC7;
    v += d;
    if (v >= 0x100) {
        v = 0x1FE - v;
        D_800E0FC8 = (u8)D_800E0FC8 ^ 1;
    } else if (v < 0) {
        v = -v;
        D_800E0FC8 = (u8)D_800E0FC8 ^ 1;
    }
    D_800E0FC7 = v;
}

void func_151E5DD8(void) {
    if (D_800E0EBC != 0) {
        D_800E0EBC = 0;
    }
}

s8 func_151E5DF8(void) {
    return D_80090168;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5E08.s")

s32 func_151E6710(s32 arg0) {
    s8 var_v1;
    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E1030[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E6758(void) {
    if (D_800E101B != 0) {
        if (D_8008FD8C >= 5) {
            return D_80090130;
        }
        return D_8008FD8C;
    }
    return D_80090130;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E67A0.s")

#ifdef NON_MATCHING
/* Load the text bank `bank` (1, 2, 4: picked per game mode by func_151E5928) for the current language.
 * D_800E101A = language, D_800BEECB = language of the loaded banks, D_800E1003 = loaded bank (0 = none).
 * A bank is a block of NUL-terminated strings (runs of NULs between them), loaded with func_1502B5C8
 * (asset group 3, type 0x1C, language, entry bank - 1) into D_800E1004; D_800E1008 = its string pointer table.
 * Bank 1 also loads entry 2 into D_80090178 with an 80-entry table D_800E0FB8. The old banks are freed
 * with func_10004074 first (the bank-1 extras only when they exist). */
extern u8 D_800BEECB;
extern s8 D_800E101A;
extern u8 **D_800E0FB8;
u8 *func_1502B5C8(s32 *size, s32 group, s32 type, s32 lang, s32 entry);
void *allocate_memory(s32, s32, s32, s32);
void func_10004074(s32);

void func_151E7110(s32 bank) {
    s32 size;
    s32 entry;
    s32 count;
    s32 i;
    u8 *p;
    u8 *end;

    if (D_800BEECB != D_800E101A) {
        D_800BEECB = D_800E101A;
        D_800E1003 = 0;
    }
    if (bank == D_800E1003) {
        return;
    }
    if (D_800E1004 != 0) {
        func_10004074(D_800E1004);
        D_800E1004 = 0;
        if (D_80090178 != 0) {
            func_10004074(D_80090178);
            func_10004074((s32)D_800E0FB8);
            func_10004074((s32)D_800E1008);
            D_80090178 = 0;
        }
    }
    D_800E1003 = bank;
    if (D_800E1003 == 0) {
        return;
    }

    entry = bank - 1;
    p = func_1502B5C8(&size, 3, 0x1C, D_800BEECB, entry);
    D_800E1004 = (s32)p;
    end = p + size;
    count = 0;
    do {
        while (*p != 0) p++;
        while (*p == 0) p++;
        count++;
    } while (p < end);

    D_800E1008 = allocate_memory((count + 1) * 4, 1, 0, 0);
    p = (u8 *)D_800E1004;
    end = p + size;
    i = 0;
    do {
        ((u8 **)D_800E1008)[i++] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    } while (p < end);

    if (entry != 0) {
        return;
    }
    D_80090178 = (s32)func_1502B5C8(&size, 3, 0x1C, D_800BEECB, 2);
    D_800E0FB8 = allocate_memory(80 * sizeof(u8 *), 1, 0, 0);
    p = (u8 *)D_80090178;
    for (i = 0; i != 80; i++) {
        D_800E0FB8[i] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E7110.s")
#endif

void func_151E73A8(void) {
    D_800E1003 = 0;
    D_800E1004 = 0;
    D_80090178 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")

extern f32 D_800ABE94;
u8 *func_151149AC(u8);
extern u8 D_80090360[][6];

void func_151E856C(void)
{
  s32 var_s0;
  u8 var_a0;
  u8 *temp_v0;
 var_s0 = 0; if ((!((*((f32 *) (((u8 *) D_80090174) + 8))) < D_800ABE94)) || ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) != 0)) { do { if ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) == 0) { var_a0 = D_80090360[var_s0][*((s8 *) (((u8 *) D_80090174) + 0x2C))];
      }
      else
      {
        var_a0 = D_80090360[var_s0][0];
      }
      temp_v0 = func_151149AC(var_a0);
      var_s0 += 1;
      if (temp_v0 != 0)
      {
        *((s32 *) (((u8 *) temp_v0) + 0x80)) = 2;
      }
    }
    while (var_s0 != 2);
  }
}

extern s8 D_800E1019;

void func_151E8648(void) {
    if (D_800E1019 == 2) {
        func_10017870(1U);
        return;
    }
    if (D_800E1019 == 0) {
        func_10017870(2U);
        return;
    }
    func_10017870(4U);
}

extern s32 func_151DE100;
void func_151E86A4(void) {
    void (*new_var)(OSTask *tp); // fakematch: permuter temp pinning osSpTaskLoad address
    s32 var_v1;
    s32 *var_v0;
    func_151E8648();
    new_var = osSpTaskLoad; // fakematch
    var_v1 = 0;
    for (var_v0 = &func_151DE100; (u32) var_v0 < (u32) func_151DECB4; var_v0++) {
        var_v1 += *var_v0;
        if (!new_var) { } // fakematch
    }
    if (var_v1 != 0xBB9FE01C) {
        *((s32 *) new_var) = 0;
        if (func_151DECB4) { } // fakematch
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E870C.s")

#ifdef NON_MATCHING
extern s32 D_800E0FD0;
extern s32 D_800E0FD4;
extern s32 D_800E0FD8;
extern s32 D_800E0FDC;
extern s8 D_80090124;

void func_151E8998(void) {
    D_800E0FD4 = 0;
    D_800E0FD0 = 0;
    D_800E0FD8 = 0;
    D_800E0FDC = 0;
    D_80090124 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8998.s")
#endif
s32 func_1517F54C();
extern s16 D_800E0EB0;

void func_151E89C0(void) {
    if (D_800E0B94 != 8) {
        if (func_1517F54C() == 0) {
            D_800E0EC0 = 0;
        }
        if (D_800E0EC0 >= 0xA1) {
            D_8009016C = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_80090130 = 1;
            D_80090144 = 0;
            D_800E0EB0 = -2;
            D_800E0EC0 = 0;
            D_800D2E43 = 1;
        }
    }
}

void func_151E5AB8(void);

void func_151E8A64(void) {
    func_151E5AB8();
    if (D_800E0EB0 == -1 && D_800E0EC0 >= 0x79) {
        D_800E0B94 = 9;
        D_800E0EC0 = 0;
        D_8009016C = 0xFF;
        D_800E0EB0 = 0;
        func_1501C710(6, 0x1D, 0, 0, 1);
        return;
    }
    if (D_800E0EB0 == -2) {
        D_800E0EB0 = 0;
    }
    if (D_800E0EC0 >= 0x173 && D_800E0EB0 >= 0) {
        while (((u8 **)D_800E1008)[D_800E0EB0][0] != 0x2A) {
            D_800E0EB0++;
        }
        D_800E0EB0++;
        if (((u8 **)D_800E1008)[D_800E0EB0][0] == 0x3D) {
            D_800E0EB0 = -1;
        }
        D_800E0EC0 = 0;
    }
}

void func_1501D348(s32, s32, s32, s32, s32);

void func_151E8B94(void) {
    if (D_800E0EB0 == 0) {
        D_800E0EB0 = -1;
        func_1501D348(0x1D, 6, 0, 0, 0);
    }
    func_151E5AB8();
    if (func_1517F54C() == 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x65) {
        func_151E5798();
        D_80090144 = 0;
        D_800E0B94 = 1;
        D_800E0EC0 = 0;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
    }
}
