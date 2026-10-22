#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *func_15096D44(Gfx *arg0);
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx D_800903D8[];
u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
extern s32 D_80090410;
extern s32 D_80091BA8;
#endif


Gfx *func_151ED998(Gfx *gdl);
void func_15042D94(s32, s32, s32, void *);
extern Gfx *(*D_800903A4[])(Gfx *);
extern u8 D_800BEB60;

Gfx *func_151E8C60(Gfx *gdl) {
    s32 msg;
    Gfx *(*fn)(Gfx *);

    D_8003C8E0 = 0x09000001;
    msg = 0;
    gdl = func_151ED998(gdl);
    fn = D_800903A4[D_800E0B94];
    if (fn != NULL) {
        gdl = fn(gdl);
    }
    if (D_80000300 == 0) {
        if (D_800BE616 != 0 && D_80090130 >= 2) {
            if ((D_800BEB60 & 0xF) == 0) {
                if (D_800E1003 == 1) {
                    msg = 0x33;
                } else if (D_800E1003 == 2) {
                    msg = 0x16;
                }
            }
        } else if ((D_800BEB60 & 1) == 0) {
            if (D_800E1003 == 1) {
                msg = 0x32;
            } else if (D_800E1003 == 2) {
                msg = 0x15;
            }
        }
    }
    if (msg != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, ((void **)D_800E1008)[msg]);
    }
    D_8003C8E0 = 0;
    return gdl;
}

extern Gfx *(*D_80090370[])(Gfx *);
extern s32 D_80090408;
extern s32 D_800BEFC4;
extern s16 D_800E10A8;
Gfx *func_151E8620(Gfx *arg0) {
    Gfx *(*temp_a1)(Gfx *);
    Gfx *temp_a2;
    s32 var_v0;
    u8 temp_v1;
    temp_v1 = D_800E0B94;
    temp_a2 = arg0;
    D_8003C8E0 = 0x09000000;
    temp_a1 = D_80090370[temp_v1];
    if (temp_a1 != NULL) {
        arg0 = temp_a1(arg0);
    }
    if (D_800E0B94 != 0) {
        D_80090408 = 0;
        D_800E10A8 = 0;
    }
    D_8003C8E0 = 0;
    if (D_800BEFC4 < (arg0 - D_800BEDE8[D_800BE9C0])) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        return temp_a2;
    }
    return arg0;
}

#ifdef NON_MATCHING
extern f32 D_800901BC;
extern f32 D_800901C0;

u8 *func_151E8E94(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a0;
    u8 *temp_a0_2;

    var_a2 = arg2;
    if (D_800901BC != 1.0f) {
        arg1 = (s32) ((f32) arg1 * D_800901BC);
        arg3 = (s32) ((f32) arg3 * D_800901BC);
        var_a2 = (s32) ((f32) var_a2 * D_800901C0);
        arg4 = (s32) ((f32) arg4 * D_800901C0);
        arg8 = (s32) ((f32) arg8 / D_800901BC);
        arg9 = (s32) ((f32) arg9 / D_800901C0);
    }
    temp_a0_2 = arg0 + 8;
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) var_a2 > 0) {
        var_t1_2 = (s16) var_a2;
    } else {
        var_t1_2 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE1000000;
    temp_a0 = temp_a0_2 + 8;
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (var_a2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    return temp_a0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8E94.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA4C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA90C.s")

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E8E94(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090424;
extern s32 D_8009044C;

u8 *func_151EB5AC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 u7C;
        u8 pad80[0x14];
        s32 u94;
    } sp;
    s32 *var_s1;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *var_s0;

    var_s0 = arg0;
    var_s3 = arg3;
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0xC)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0xC));
    (*(s32 *)((u8 *)(&sp.u7C) + 0x10)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x10));
    temp_t4 = arg2 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x18)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x18));
    var_s2 = arg1 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x14)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x14));
    if (var_s3 >= 0x989680) {
        var_s3 = 0x98967F;
    }
    var_s4 = 0;
    if (var_s3 < 0) {
        var_s3 = 0;
    }
    var_s1 = &sp.u94;
    do {
        temp_v0 = *var_s1;
        temp_v1 = var_s3 / temp_v0;
        var_s3 = var_s3 % temp_v0;
        if ((temp_v1 > 0) || (var_s4 != 0) || (var_s1 == &sp.u7C)) {
            var_s4 = 1;
            temp_v0_2 = func_1510D66C(*(s32 *)((u8 *)&D_80090424 + (temp_v1 * 4)), 0, 3, 0);
            if (temp_v0_2 != 0x80000000) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xFD180000;
                (*(s32 *)((u8 *)var_s0 + 4)) = temp_v0_2;
                temp_s0 = var_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF5180000;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x07094250;
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xE6000000;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
                temp_s0_3 = temp_s0_2 + 8;
                (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x073FF000;
                (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xF3000000;
                temp_s0_4 = temp_s0_3 + 8;
                (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0;
                temp_s0_5 = temp_s0_4 + 8;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5181000;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x94250;
                temp_s0_6 = temp_s0_5 + 8;
                (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF2000000;
                (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x7C07C;
                var_s0 = func_151E8E94(temp_s0_6 + 8, var_s2, temp_t4, var_s2 + 0x80, temp_t4 + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            var_s2 += 0x60;
        }
        var_s1 = (s32 *)((u8 *)var_s1 - (4));
    } while ((u32) var_s1 >= (u32) &sp.u7C);
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB5AC.s")
#endif
#ifdef NON_MATCHING
/* Table D_80090370 slot 0 (the in-game HUD pass): pause/fade overlay, and with D_800BEAC0 set the
 * money/lives counter screen (texture ids 0x7D3.. loaded through func_1510D66C, counters drawn by
 * func_151EB5AC). */
u8 * func_150900F0(Gfx *, s32);
void func_151EE310(u8 *arg0);
void func_151F0114(void *, float, float, float, float, float, float, float);
s8 func_151E5DF8(void);
void func_1510DC14(s32);
u8 *func_1509B570(s32);
u8 *func_151EB5AC(u8 *, s32, s32, s32);
s32 func_1509BE40(s32, s32, s32);
u8 * func_151E9150(u8 *, s32, s32);
u8 * func_151EA90C(Gfx *, s32, s16, s32);
s32 func_151EE0C4(s32, s32, s32, f32);
u8 * func_151EE394(u8 *, s32, f32, f32, f32);
extern s32 D_8008955C;
extern s8 D_8009029C;
extern s32 D_8009040C;
extern s8 D_80090468;
extern s16 D_800C40BE;
extern s16 D_800E1060;
extern s32 D_800E1068;

u8 *func_151EB81C(u8 *arg0) {
    struct {
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x4];
        s32 u84;
        s32 u88;
        s32 u8C;
        s32 u90;
    } sp;
    u8 *var_s0_2;
    u8 *var_s0;
    u8 *temp_v0_2;
    u8 *temp_s0_6;
    u8 *temp_s0_5;
    u8 *temp_s0;
    u8 temp_v1;
    s32 var_v1_4;
    s32 var_v1_3;
    s32 var_v1;
    s32 var_v0_3;
    s32 var_v0_2;
    s32 var_v0;
    s32 var_t0;
    s32 var_a3;
    s32 var_a0;
    s32 temp_v1_2;
    s32 temp_v0_3;
    s32 temp_v0;
    s32 temp_t9;
    f32 temp_f2;
    f32 temp_f0;
    Gfx *temp_s0_4;
    Gfx *temp_s0_3;
    Gfx *temp_s0_2;
    Gfx *sp34;
    s32 sp3C;

    var_s0 = arg0;
    temp_t9 = (D_800D2E4C->unk19 & 4) != 0;
    sp3C = temp_t9;
    if (temp_t9 == 0) {
        sp3C = D_8008FDA8 < 0;
    }
    if ((D_800BE616 != 0) && (D_800BEAC0 == 0) && (D_800BEAC1 == 0)) {
        if ((func_151E5DF8() == 0) || ((*(s8 *)((u8 *)D_80090174 + 0x42)) == 1)) {
            var_s0 = func_151E9150(var_s0, 0, 0xFF);
        }
    } else {
        D_800E10A8 = 0;
    }
    if ((D_800BEAC0 == 0) || (D_8009029C != 0)) {
        if (D_80090408 != 0) {
            func_151EE310((u8 *) D_80090408);
            func_151EE310((u8 *) D_8009040C);
            D_80090408 = 0;
        }
        D_8009016C = 0;
        D_80090468 = 0;
    } else {
        if ((D_800B0DF0->unk8 == 4) && (D_80090468 == 0)) {
            var_v1 = 0;
            if (D_800BE9F0 == 0x13) {
                var_a0 = (*(s32 *)((u8 *)(*(s32 *)((u8 *)&D_8008955C + (D_800B0DF0->unk9 * 4))) + 8));
                /* texture ids 0x1649-0x164B and 0x1655-0x1657 stay loaded */
                for (var_v0 = 0; var_v0 != 0x48; var_v0++, var_a0++) {
                    if (var_a0 != 0x1649 && var_a0 != 0x164A && var_a0 != 0x164B && var_a0 != 0x1655 &&
                        var_a0 != 0x1656 && var_a0 != 0x1657) {
                        func_1510DC14(var_a0);
                    }
                }
                var_v1 = 0x4E;
            }
            var_v0_2 = var_v1;
            if (var_v1 < 0x168) {
                do {
                    sp.u84 = var_v0_2;
                    func_1510DC14((*(s32 *)((u8 *)(*(s32 *)((u8 *)&D_8008955C + (D_800B0DF0->unk9 * 4))) + 8)) + var_v0_2);
                    var_v0_2 = sp.u84 + 1;
                } while (var_v0_2 != 0x168);
            }
        }
        if (D_80090468 < 5) {
            D_80090468 += 1;
        } else {
            temp_s0 = var_s0 + 8;
            D_8009016C += 0x20;
            if (D_8009016C >= 0x100) {
                D_8009016C = 0xFF;
            }
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xDE000000;
            (*(Gfx **)((u8 *)var_s0 + 4)) = D_800903D8;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xFB000000;
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
            D_80090410 = 0x891;
            sp34 = D_800903D8;
            func_1510D66C(0x7D3, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7D4, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7FC, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7FD, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7F1, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7F2, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x82F, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x830, (s32) &sp.u70, 3, 0);
            temp_v1 = D_800BE616;
            if (temp_v1 != 0) {
                func_1510D66C(0x80E, (s32) &sp.u70, 3, 0);
                func_1510D66C(0x80F, (s32) &sp.u70, 3, 0);
            }
            if (temp_v1 == 0) {
                temp_v0 = func_150859AC(0, 6);
                var_v1_3 = temp_v0;
                if (temp_v0 == 0x7D00) {
                    var_v1_3 = 0xF4240;
                }
                sp.u90 = var_v1_3;
                if ((func_1509BE40(0, 0x5082, 0x1A) != 0) && (func_1509BE40(0, 0x5083, 0x1A) == 0)) {
                    temp_v0_2 = func_1509B570(0x83);
                    if (temp_v0_2 != NULL) {
                        temp_v1_2 = (*(s32 *)((u8 *)temp_v0_2 + 0x64));
                        if (temp_v1_2 == 0) {
                            sp.u90 = 0;
                        } else if (temp_v1_2 < 3) {
                            sp.u90 = (s32) (sp.u90 * temp_v1_2) / 3;
                        }
                    } else {
                        sp.u90 = 0;
                    }
                }
                var_v1_4 = sp.u90;
                if ((D_800C35EA == 1) && (D_800C40BE != -1)) {
                    if (D_800C40BE == 0) {
                        var_v1_4 = 0;
                    } else {
                        var_v1_4 -= D_800C40BE;
                        if (D_800C40BE == 0x7D00) {
                            var_v1_4 = 0xF4240;
                        }
                    }
                }
                if (var_v1_4 > 0) {
                    sp.u88 = 1;
                } else {
                    sp.u88 = 0;
                }
                sp.u90 = var_v1_4;
                temp_s0_3 = func_151EDBE8(temp_s0_2, &D_80090410, 0x94, 0x3C, 3, 1, 1.0f, 0);
                if (D_80090408 == 0) {
                    D_80090408 = func_151EE0C4(0xA4, 0x17, 0, 1.0f);
                    D_8009040C = func_151EE0C4(0xA2, 8, 0, 1.0f);
                }
                temp_s0_3->words.w0 = 0xD9FFFFFF;
                temp_s0_3->words.w1 = 0x220404;
                temp_s0_4 = temp_s0_3 + 1;
                temp_s0_4->words.w1 = -1U;
                temp_s0_4->words.w0 = 0xFB000000;
                temp_f0 = (*(f32 *)((u8 *)D_800BE628 + 4)) * 0.5f;
                temp_f2 = (*(f32 *)((u8 *)D_800BE628 + 8)) * 0.5f;
                var_s0_2 = func_150900F0(temp_s0_4 + 1, 1);
                func_151F0114(&D_800E1068, -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, 20000.0f, 1.0f);
                D_800E1060 = D_8009016C;
                if (D_80090408 != 0) {
                    var_v0_3 = 0xA;
                    if (sp.u88 != 0) {
                        var_t0 = -0x10;
                        if (sp.u90 >= 0xB) {
                            do {
                                var_t0 -= 0x10;
                                var_v0_3 *= 0xA;
                            } while (var_v0_3 < sp.u90);
                        }
                        sp.u8C = var_t0;
                        var_s0_2 = func_151EE394(var_s0_2, D_80090408, (f32) var_t0 + -10.0f, -83.0f, 0.26999998f);
                    }
                }
                if ((D_8009040C != 0) && (sp3C != 0)) {
                    var_s0_2 = func_151EE394(var_s0_2, D_8009040C, 70.0f, 80.0f, 0.3f);
                }
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xDE000000;
                temp_s0_5 = var_s0_2 + 8;
                (*(Gfx **)((u8 *)var_s0_2 + 4)) = sp34;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xEF002C3F;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x504244;
                var_s0 = temp_s0_5 + 8;
                if (sp3C != 0) {
                    temp_v0_3 = func_150859AC(0, 3);
                    var_a3 = temp_v0_3;
                    if (temp_v0_3 != 0) {
                        var_a3 = temp_v0_3 - 1;
                    }
                    if (var_a3 >= 0x64) {
                        var_a3 = 0x63;
                    }
                    (*(s32 *)((u8 *)var_s0 + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)var_s0 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
                    var_s0 = func_151EB5AC(var_s0 + 8, 0xEC, 0x1E, var_a3);
                }
                if (sp.u88 != 0) {
                    (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
                    temp_s0_6 = var_s0 + 8;
                    (*(s32 *)((u8 *)var_s0 + 4)) = 0;
                    (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)temp_s0_6 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
                    D_80090410 = 0x7F6;
                    var_s0 = func_151EB5AC(func_151EDBE8(temp_s0_6 + 8, &D_80090410, sp.u8C + 0xA5, 0xAA, 1, 1, 1.0f, 0), sp.u8C + 0xAD, 0x9B, sp.u90);
                }
            } else {
                var_s0 = func_151EA90C(func_151EDBE8(temp_s0_2, &D_80090410, 0x94, 0x12, 3, 1, 1.0f, 0), 0x85, D_8009016C, 1);
            }
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB81C.s")
#endif
s32 func_151EC0E0(s32 arg0) {
    if (D_8009016C != 0) {
        arg0 = func_151EA90C(arg0, 0x6A, D_8009016C, 0);
    }
    return arg0;
}

#ifdef NON_MATCHING
extern s16 D_800E0EB0;

/* Table D_80090370 slot 21: centred text screen. Lines D_800E1008[D_800E0EB0...] up to a "*" line;
 * the first line is red, an extra 12 px gap follows it. Fades in over D_800E0EC0 0..63, out at 287..350. */
Gfx *func_151EC11C(Gfx *gdl) {
    s32 pad[2];
    s16 a;
    s16 i;
    s32 n;
    s32 step;
    s32 y;
    s32 y0;
    u8 *s;

    if (D_800E0EB0 < 0) {
        return gdl;
    }
    if (D_800E0EC0 < 300) {
        a = D_800E0EC0 << 2;
        if (a >= 0x100) {
            a = 0xFF;
        }
    } else {
        a = (350 - D_800E0EC0) << 2;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
    }
    n = 0;
    for (i = D_800E0EB0; ((u8 **)D_800E1008)[i][0] != '*'; i++) {
        n++;
    }
    if (n < 14) {
        step = 0x11;
    } else {
        step = 0xB;
    }
    func_1504332C(0xFF, 0, 0, a);
    i = D_800E0EB0;
    y0 = y = (0xD0 - n * step) >> 1;
    while ((s = ((u8 **)D_800E1008)[i])[0] != '*') {
        func_15042D94(0x94, y, 1, s);
        func_1504332C(0xFF, 0xFF, 0xFF, a);
        if (y == y0) {
            y += 0xC;
        }
        i++;
        y += step;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC11C.s")
#endif
#ifdef NON_MATCHING
extern s32 D_80091B9C;
extern f32 D_800ABEF8;
extern u8 D_85D[];
extern u8 D_89C[];


/* Table D_80090370 slot 11: three-phase intro/credits screen on a black background, driven by the timer
 * D_800E0EC0. t < 200: one red text line (D_800E1008 + 0x238), zooming from scale 0.75 to 1.5.
 * 200 <= t < 450: two sprites (D_80091BA8 at 1/4 alpha, D_80091B9C), 14 text lines, the 16x16 D_89C icon.
 * t >= 450: the 64x64 D_85D image. D_80090410 is a shared sprite descriptor (texture, size, format)
 * that is reset to its 32x32 default afterwards. Skipped (after the clear) when D_80000300 != 0. */
Gfx *func_151EC300(Gfx *gdl) {
    s32 t;
    s32 a;
    s32 i;
    f32 scale;
    s32 envcol;
    u8 *desc = (u8 *) &D_80090410;

    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, 0xFF);
    gdl = (Gfx *) func_1501A6CC((u8 *) gdl, 0, 0, D_800BE620, D_800BE624);
    if (D_80000300 != 0) {
        return gdl;
    }
    gSPDisplayList(gdl++, D_800903D8);
    t = D_800E0EC0;
    if (t < 200) {
        a = 0xFF - (t - 150) * 8;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
        scale = (f32) t / 180.0f + 0.75f;
        if (scale > 1.5f) {
            scale = 1.5f;
        }
        func_150432BC(scale);
        func_1504332C(0xFF, 0, 0, a & 0xFF);
        func_15042D94(0x94, 0x69, 1, *(u8 **) ((u8 *) D_800E1008 + 0x238));
        func_150432BC(1.0f);
    } else if (t < 450) {
        if (t < 250) {
            a = (t - 200) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 400) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, (a >> 2) & 0xFF);
        gdl = func_151EDBE8(gdl, &D_80091BA8, 0x92, 0x67, 5, 6, 1.0f, 0);
        envcol = (a & 0xFF) | ~0xFF;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        gdl = func_151EDBE8(gdl, &D_80091B9C, 0x92, 0x1C, 2, 1, 1.0f, 0);
        func_1504332C(0xFF, 0xFF, 0xFF, a & 0xFF);
        func_15042D94(0x94, 0x9D, 1, *(u8 **) ((u8 *) D_800E1008 + 0x204));
        func_15042D94(0x94, 0xAA, 1, *(u8 **) ((u8 *) D_800E1008 + 0x208));
        func_15042D94(0x94, 0xBC, 1, *(u8 **) ((u8 *) D_800E1008 + 0x20C));
        func_150432BC(D_800ABEF8);
        for (i = 0; i < 10; i++) {
            func_15042D94(0x94, 0x2D + i * 10, 1, *(u8 **) ((u8 *) D_800E1008 + 0x210 + i * 4));
        }
        func_150432BC(1.0f);
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        *(u8 **) (desc + 0) = D_89C;
        *(s16 *) (desc + 6) = 0x10;
        *(s16 *) (desc + 8) = 0x10;
        gdl = func_151EDBE8(gdl, desc, 0xC7, 0xB0, 1, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
    } else {
        if (t < 500) {
            a = (t - 450) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 650) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = (a & 0xFF) | 0xFF000000;
        gdl++;
        desc[0xA] = 4;
        desc[0xB] = 1;
        *(u8 **) (desc + 0) = D_85D;
        *(s16 *) (desc + 6) = 0x40;
        *(s16 *) (desc + 8) = 0x40;
        gdl = func_151EDBE8(gdl, desc, 0x94, 0x69, 3, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
        desc[0xA] = 0;
        desc[0xB] = 3;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC300.s")
#endif
#ifdef NON_MATCHING
s32 func_151EC928(s32 arg0) {
    s32 temp_t6;
    s32 var_v0;

    if (D_800E0EC0 >= 0x5DD) {
        temp_t6 = (D_800E0EC0 - 0x5DC) * 8;
        var_v0 = temp_t6;
        if (temp_t6 >= 0x100) {
            var_v0 = 0xFF;
        }
        func_1504332C(0xFFU, 0xFFU, 0xFFU, var_v0 & 0xFF);
        func_15042D94(0xDC, 0x130, 1, (*(u8 **)((u8 *)D_800E1008 + 0x1D0)));
    }
    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC928.s")
#endif
#ifdef NON_MATCHING
extern s32 D_80091BA8;
extern s32 D_80091BB4;
extern s32 D_80091BC0;
extern s32 D_800E0EA4;
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }

Gfx *func_151EC9A0(Gfx *gdl) {
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_t0;
    s32 temp_a;

    if (D_800BE9F0 == 0x21) {
        return gdl;
    }
    gSPDisplayList(gdl++, D_800903D8);
    if (D_800E0EC0 >= 0x12D) {
        temp_v1 = 0x1AC - D_800E0EC0;
        temp_a = temp_v1 * 2;
        var_v1 = temp_a;
        if (temp_a < 0) {
            var_v1 = 0;
        }
    } else {
        var_v1 = D_800E0EC0 * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0xFF;
        }
    }
    if (var_v1 != 0) {
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, var_v1);
        gdl = func_151EDBE8(gdl, &D_80091BA8, 0x92, 0x63, 5, 6, 1.0f, 0);
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
    gdl = func_151EDBE8(gdl, &D_80091BB4, 0x92, 0xCB, 5, 2, 1.0f, 0);
    MW(gdl++, 0xFCFFD3FF, 0xFFA6FF7F);
    MW(gdl++, 0xFB000000, (u8) D_800E0FC7 | 0x20FF2000);
    gdl = func_151EDBE8(gdl, &D_80091BC0, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gdl = func_15096D44(gdl);
    temp_v1 = 0x1EA - D_800E0EA4;
    if (temp_v1 < 0) {
        var_v1_2 = 0;
    } else {
        temp_t0 = temp_v1 * 0x10;
        var_v1_2 = temp_t0;
        if (temp_t0 >= 0x100) {
            var_v1_2 = 0xFF;
        }
    }
    D_800E0FC6 = 0xFF - var_v1_2;
        return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC9A0.s")
#endif
#ifdef NON_MATCHING
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *func_151ECE00(Gfx *);
Gfx *func_151EE93C(Gfx *);
Gfx *func_151EF3A0(Gfx *, s32);
extern Gfx D_800903D8[];
extern u8 D_80090484;
extern s8 D_800902A4;
extern s8 D_800902A8;
extern u8 D_800E0EC5;
extern s32 D_80090410;
extern s32 D_8009046C[];

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x20];
    s8 x2C;
    u8 pad2D[0x11];
    s8 x3E;
} Ent174;

Gfx *func_151ECB98(Gfx *gdl) {
    Ent174 *p;
    s32 a;
    s32 v;
    s32 k;
    s32 t;
    struct_eu_BE818 *e;

    if (D_800C35EA == 1) {
        D_80090484 = 0;
        return gdl;
    }
    a = D_80090484 + D_800BE9E4 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    D_80090484 = a;
    gSPDisplayList(gdl++, D_800903D8);
    p = (Ent174 *)D_80090174;
    k = p->x3E;
    if (k == 1) {
        return func_151ECE00(gdl);
    }
    if (k != 0) {
        return gdl;
    }
    t = p->x2C;
    if (t == 1 && D_800902A4 != 0) {
        gdl = func_151EE93C(gdl);
    } else if (t != 1 || D_800902A8 == 0) {
        v = (p->x0 - 0.5f) * 512.0f;
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x100) {
            v = 0xFF;
        }
        if (D_80090484 < v) {
            v = D_80090484;
        }
        if (t == 1) {
            v = (D_800E0EC5 * v) >> 8;
            if (v >= 0xFE) {
                v = 0xFF;
            }
        }
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        D_80090410 = D_8009046C[((Ent174 *)D_80090174)->x2C];
        gdl = func_151EDBE8(gdl, &D_80090410, 0x94, 0x1E, 3, 1, 1.0f, 0);
    }
    p = (Ent174 *)D_80090174;
    if (0.5f <= p->x8) {
        if (p->x2C >= 3) {
            e = &D_800BE818[p->x2C - 3];
            if (e->unk8 != -1) {
                gdl = func_151EF3A0(gdl, e->padC[0]);
            }
        }
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECB98.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECE00.s")

#ifndef NON_MATCHING
void func_15096D44(Gfx *);
#endif
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx D_800903D8[];
extern u8 D_80091BCC[];
extern u8 D_80091BD8[];

/* Table D_80090370 slot 17. The original is void in C but its v0 is func_15096D44's return value, which
 * func_151E8620 uses as the new display-list pointer: under NON_MATCHING it returns it explicitly. */
#ifdef NON_MATCHING
Gfx *func_151ED854(Gfx *gdl) {
#else
void func_151ED854(Gfx *gdl) {
#endif
    s32 a;

    gSPDisplayList(gdl++, D_800903D8);
    a = D_800E0EC0 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
    gdl = func_151EDBE8(gdl, D_80091BCC, 0x92, 0x6C, 8, 3, 1.0f, 0);
    gDPPipeSync(gdl++);
    gDPSetCombine(gdl++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gdl++, 0xFF, 0x80, 0x20, ((u8)D_800E0FC7 * (a + 1)) >> 8);
#ifdef NON_MATCHING
    return func_15096D44(func_151EDBE8(gdl, D_80091BD8, 0x92, 0x6C, 8, 3, 1.0f, 0));
#else
    func_15096D44(func_151EDBE8(gdl, D_80091BD8, 0x92, 0x6C, 8, 3, 1.0f, 0));
#endif
}

u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
Gfx *func_151ED998(Gfx *gdl) {
    if ((u8)D_800E0FC6 == 0) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, (u8)D_800E0FC6);
    return (Gfx *)func_1501A6CC((u8 *)gdl, 0, 0, D_800BE620, D_800BE624);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDA54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE0C4.s")

void func_151EE310(u8 *arg0) {
    s32 i;

    if (arg0 != NULL) {
        func_1503FAA8(*(s32 *)(arg0 + 0x24));
        func_100043B4(arg0, 4);
        for (i = 0; i < arg0[0x14]; i++) {
            func_100043B4(((s32 **)(arg0 + 4))[i], 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE93C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EF3A0.s")
